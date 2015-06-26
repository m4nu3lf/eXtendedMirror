/******************************************************************************      
 *      Extended Mirror: Variant.cpp                                         *
 ******************************************************************************
 *      Copyright (c) 2012-2015, Manuele Finocchiaro                          *
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
#include <XM/xMirror.hpp>

using namespace std;
using namespace xm;

static void* null = NULL;
Variant Variant::Null = Variant(null, Const);

Variant::Variant() : data_(NULL), type_(&::getType<void*>()), flags_(0)
{
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


Variant::Variant(const Variant& orig)
 : data_(NULL), type_(&::getType<void*>()), flags_(0)
{
    std::size_t size = orig.type_->getSize();

    if (orig.flags_ & CopyByRef)
    {
        // copy by reference
        if (size > sizeof(data_))
            data_ = orig.data_;
        else
            data_ = const_cast<void**>(&orig.data_);
        type_ = orig.type_;
        flags_ = orig.flags_;
        flags_ |= Reference;
    }
    else
    {
        
        //TODO: allow custom allocator
        // allocate memory

        if (size > sizeof(data_))
            data_ = ::operator new(size);
        
        // if class copy with copy constructor
        const Class* clazz = dynamic_cast<const Class*>(orig.type_);
        if (clazz)
        {
            const CopyConstructor& cpyC = clazz->getCopyConstructor();
            
            try
            {
                type_ = orig.type_;
                cpyC.copy(*this, orig);
            }
            catch(NonCopyableException& e)
            {
                if (size > sizeof(data_))
                    ::operator delete(data_); //TODO allow custom allocator
                throw e;
            }
        }
        else
        {
            type_ = orig.type_;

            // perform raw memory copy
            if (size > sizeof(data_))
                std::memcpy(data_, orig.data_, size);
            else
                std::memcpy(&data_, &orig.data_, size);
        }
    }
}


Variant::Variant(Variant&& orig) :
    data_(NULL), type_(&::getType<void*>()), flags_(0)
{
    std::swap(data_, orig.data_);
    std::swap(flags_, orig.flags_);
    std::swap(type_, orig.type_);
}


const Variant& Variant::operator=(Variant other)
{
    std::swap(data_, other.data_);
    std::swap(flags_, other.flags_);
    std::swap(type_, other.type_);
    return *this;
}


bool Variant::recursiveCast(Variant& src,
                            Variant& dst,
                            const Class& targetClass,
                            CastDirection castDir)
{
    const Class& clazz = dynamic_cast<const Class&>(src.getType());

    // retrieve direct caster if any
    Const_RefCaster_Set casters = clazz.getRefCasters();
    const RefCaster* caster = ptrSet::findByKey(casters, targetClass);

    // if a caster is found, cast this variant and return
    if (caster && (caster->getCastDirection() & castDir))
    {
        dst = caster->cast(src);
        return true;
    }
    else
    {
        // for every ref caster, cast to that, then try to cast to T,
        // keeping the same direction to avoid loops
        Const_RefCaster_Set::iterator ite = casters.begin();
        while(ite != casters.end())
        {
            if (((*ite)->getCastDirection() & castDir))
            {
                CastDirection castDir2 = (*ite)->getCastDirection();
                Variant casted = (*ite)->cast(src);
                if (recursiveCast(casted, dst, targetClass, castDir2))
                    return true;
            }
            ite ++;
        }
        return false;
    }
}


Variant::~Variant()
{
    if(!data_) return;
    
    if (!(flags_ & Reference))
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

