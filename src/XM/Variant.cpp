/******************************************************************************      
 *      Extended Mirror: Variant.cpp                                         *
 ******************************************************************************
 *      Copyright (c) 2012-2014, Manuele Finocchiaro                          *
 *      All rights reserved.                                                  *
 ******************************************************************************
 * Redistribution and use in source and binary forms, with or without         *
 * modification, are permitted provided that the following conditions         *
 * are met:                                                                   *
 *                                                                            *
 *    1. Redistributions of source code must retain the above copyright       *
 *       notice, this list of conditions and the following disclaimer.        *
 *                                                                            *
 *    2. Redistributions in binary form must reproduce the above copyright    *
 *       notice, this list of conditions and the following disclaimer in      *
 *       the documentation and/or other materials provided with the           *
 *       distribution.                                                        *
 *                                                                            *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"* 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE  *
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE *
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE  *
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR        *
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF       *
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   *
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN    *
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)    *
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF     *
 * THE POSSIBILITY OF SUCH DAMAGE.                                            *
 *****************************************************************************/


#include <XM/Utils/Utils.hpp>
#include <XM/ExtendedMirror.hpp>

using namespace std;
using namespace xm;

static void* null = NULL;
Variant Variant::Null = Variant(null, Const);

Variant::Variant() : flags_(0)
{
    data_ = NULL;
    type_ = &xm::getType<void>();
}


Variant Variant::getRefVariant() const
{
    Variant refVar;
    refVar.data_ = data_;
    refVar.type_ = type_;
    refVar.flags_ = flags_ | Reference;
    
    // need a const cast to make compiler choose the copy constructor
    // instead of the template constructor
    return const_cast<const Variant&>(refVar);
}


Variant::Variant(const Variant& orig) : flags_(0)
{
    if (orig.flags_ | CpyByRef)
    {
        // copy by reference
        data_ = orig.data_;
        type_ = orig.type_;
        flags_ = orig.flags_;
        flags_ |= Reference;
    }
    else
    {
        std::size_t size = orig.type_->getSize();
        
        //TODO: allow custom allocator
        // allocate memory
        data_ = ::operator new(size);
        
        // if class copy with copy constructor
        const Class* clazz = dynamic_cast<const Class*>(orig.type_);
        if (clazz)
        {
            const CopyConstructor& cpyC = clazz->getCopyConstructor();
            
            try
            {
                cpyC.copy(*this, orig);
            }
            catch(NonCopyableException& e)
            {
                ::operator delete(data_); //TODO allow custom allocator
                throw e;
            }
        }
        else
        {
            // perform raw memory copy
            std::memcpy(data_, orig.data_, size);
        }
    }
}


Variant::Variant(Variant&& orig)
{
    std::swap(data_, orig.data_);
    std::swap(flags_, orig.flags_);
    std::swap(type_, orig.type_);
}


const Variant& Variant::operator=(const Variant& other)
{
    if (flags_ | Reference)
    {
        // copy reference
        data_ = other.data_;
        type_ = other.type_;
        flags_ = other.flags_;
        flags_ |= Reference;
    }
    else
    {
        std::size_t size = other.type_->getSize();
        
        //TODO: allow custom allocator
        // allocate memory
        data_ = ::operator new(size);
        
        // if class, assign with assign operator
        const Class* clazz = dynamic_cast<const Class*>(other.type_);
        if (clazz)
        {
            const CopyConstructor& copyConstructor =
                clazz->getCopyConstructor();
            
            try
            {
                copyConstructor.copy(*this, other);
            }
            catch(NonCopyableException& e)
            {
                ::operator delete(data_); //TODO allow custom allocator
                throw e;
            }
        }
        else
        {
            // perform raw memory copy
            std::memcpy(data_, other.data_, size);
        }
    }
}

Variant Variant::call
(
    const std::string& methodName,
    const Variant& arg0,
    const Variant& arg1,
    const Variant& arg2,
    const Variant& arg3,
    const Variant& arg4,
    const Variant& arg5,
    const Variant& arg6
)
{   
    const Class* clazz = dynamic_cast<const Class*>(type_);
    if (clazz)
    {
        Method keyMethod
        (
            methodName,
            Register::getSingleton().getType<void>(),
            *type_,
            arg0.getType(),
            arg1.getType(),
            arg2.getType(),
            arg3.getType(),
            arg4.getType(),
            arg5.getType(),
            arg6.getType()
        );
        const Method& callableMethod = clazz->getMethod(keyMethod);
        
        return callableMethod.call(*this, arg0, arg1, arg2, arg3, arg4, arg5,
                arg6);
    }
    else
    {
        // TODO: throw something
    }
}


Variant Variant::callV(const std::string& methodName,
        vector<Variant>& args)
{
    args.resize(XM_FUNCTION_PARAM_MAX, Variant::Null);
    return call(methodName, args[0], args[1], args[2], args[3], args[4],
            args[5], args[6]);
}


Variant::~Variant()
{
    if(!data_) return;
    
    if (!flags_ & Reference)
    {        
        const Class* clazz = dynamic_cast<const Class*>(type_);
        if (clazz)
        {
            // call destructor
            clazz->getDestructor().destroy(*this);
        }
        
        if (type_->getSize() > sizeof(data_))
        {
            //TODO: allow custom allocator
            ::operator delete(data_);
        }
    }
}


// A variant can always be converted to an Empty object. 
template<>
Empty& Variant::as<Empty>()
{
    static Empty empty;
    return empty;
}

