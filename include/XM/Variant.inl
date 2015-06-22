/******************************************************************************      
 *      Extended Mirror: Variant.inl                                         *
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


#ifndef XM_VARIANT_INL
#define	XM_VARIANT_INL

#include <XM/Exceptions/VariantTypeException.hpp>
#include <XM/Exceptions/VariantCostnessException.hpp>
#include <XM/Exceptions/MemberExceptions.hpp>
#include <XM/Variant.hpp>

#include <cstring>

#include "TypeTraits.hpp"


namespace xm{
    

inline
const Type& Variant::getType() const
{
    return *type_;
}
    

inline
bool Variant::isReference() const
{
    return flags_ & Reference;
}
    

inline
bool Variant::isConst() const
{
    return flags_ & Const;
}


inline
void Variant::setConst()
{
    flags_ |= Const;
}
    

template<typename T>    
Variant::Initialize<T>::Initialize(Variant& variant) : variant_(variant){};


template<typename T>
void Variant::Initialize<T>::operator()(T& data)
{
    // ensure type is registered.
    variant_.type_ = &registerType<T>();
    
    if (variant_.flags_ & Reference)
    {
        // store pointer to data
        variant_.data_ = &data;
    }
    else
    {
        void* destPtr;

        if (sizeof(data) > sizeof(variant_.data_))
        {
            // allocate memory TODO: allow custom allocator
            variant_.data_ = ::operator new(sizeof(data));
            
            destPtr = variant_.data_;
        }
        else
        {
            destPtr = reinterpret_cast<void*>(&variant_.data_);
        }
        
        const Class* clazz = dynamic_cast<const Class*>(variant_.type_);
        if (clazz)
        {
            // copy data through copy constructor
            try
            {
                clazz->getCopyConstructor().copy(variant_,
                        Variant(data, Reference));
            }
            catch(NonCopyableException& e)
            {
                if (sizeof(data) > sizeof(variant_.data_))
                    // deallocate memory if cannot copy
                    ::operator delete(variant_.data_);
                throw e;
            }
        }
        else
        {
            // copy raw data
            std::memcpy(destPtr, &data, sizeof(data));
        }
    }

}


/**
 * If the type is an array, create an initializer
 * for a pointer to the element type, and pass it the address of the
 * first element.
 */
template<typename T, std::size_t size>
struct Variant::Initialize<T[size]>
{
    Initialize(Variant& variant) : variant_(variant){};
    
    void operator()(T data[size])
    {
        Initialize<T*> initializer(variant_);
        initializer(data);
    }
    
private:
    // A reference to the variant that is being initialized
    Variant& variant_;
};


template<typename T>
Variant::Variant(const T& data)
: flags_(0)
{
    // if the type is a constant array, then the type will be converted to a
    // reference to const
    if (IsArray<T>::value) flags_ |= Const;
    
    // Call initializer functor
    Initialize<T>(*this)(const_cast<T&>(data));
}


template<typename T>
Variant::Variant(T& data, char flags)
: flags_(flags)
{
    typedef typename RemoveConst<T>::Type NonConstT;
    
    // if the type is a constant one, and a storing is performed by reference,
    // remember constness
    if ((flags & Reference) && IsConst<T>::value) flags_ |= Const;
    
    // if the type is a constant array, then the type will be converted to a
    // reference to constant
    if (IsArray<T>::value && IsConst<T>::value) flags_ |= Const;
    
    // Call initializer functor
    Initialize<NonConstT>(*this)(const_cast<NonConstT&>(data));
}


template<typename T>
Variant::operator T&()
{
    // retrieve the type register
    Register& typeReg = Register::getSingleton();

    // ensure the type of the data is registered and retrieve it
    const Type& targetType = typeReg.registerType<T>();

    // check for constness correctness
    if (!IsConst<T>::value && flags_ & Const)
        throw VariantCostnessException(*type_);
    
    // check for type compatibility
    if (targetType == *type_)
    {
        if ((flags_ & Reference) || (sizeof(T) > sizeof(data_)))
            // just reinterpret the pointer
            return *reinterpret_cast<T*>(data_);
        else
            return const_cast<T&>(reinterpret_cast<const T&>(data_));
    }
    else
    {
        // check if objects
        if (!(targetType.getCategory() & Type::Class
            && type_->getCategory() & Type::Class))
            throw VariantTypeException(targetType, *type_);
        
        // cast to Class object
        const Class& clazz = dynamic_cast<const Class&>(*type_);
        
        // retrieve direct caster if any
        Const_RefCaster_Set casters = clazz.getRefCasters();
        const RefCaster* caster = ptrSet::findByKey(casters, targetType);
        
        // if a caster is found, cast this variant and return
        if (caster)
        {
            try
            {
                return caster->cast(*this);
            }
            catch(std::bad_cast)
            {
                throw VariantTypeException(targetType, *type_);
            }
        }
        else
        {
            // for every ref caster, cast to that, then try to recast to T
            Const_RefCaster_Set::iterator ite = casters.begin();
            while(ite != casters.end())
            {
                try
                {
                    return (*ite)->cast(*this).as<T>();
                }
                catch (VariantTypeException)
                {}
                catch (std::bad_cast)
                {}
                ite ++;
            }
            throw VariantTypeException(targetType, *type_);
        }
    }
}


template<typename T>
inline T& Variant::as()
{
    return *this;
}


template<>
Empty& Variant::as<Empty>();


template<typename T>
const T& Variant::operator=(const T& rvalue)
{       
    // get the Type
    const Type& rtype = xm::getType<T>();
    const Class* clazz = dynamic_cast<const Class*>(type_);
    
    // check if types are the same
    if (!type_ || rtype != *type_)
    {
        // call destructor if class
        if (clazz)
        {
            const Destructor& destructor = clazz->getDestructor();
            destructor.destroy(*this);
        }
        
        // free memory
        ::operator delete(data_); // TODO: allow custom deallocator
        
        // set the new Type
        type_ = &rtype;
        
        // allocate new memory
        ::operator new(sizeof(T)); // TODO: allow custom allocator
        
        // call copy constructor if any
        clazz = dynamic_cast<const Class*>(type_);
        if (clazz)
        {
            const CopyConstructor& cpyC = clazz->getCopyConstructor();
            cpyC.copy(*this, RefVariant(rvalue));
        }
    }
    else
    {
        // call copy constructor if class
        if (clazz)
        {
            const CopyConstructor& cpyC = clazz->getCopyConstructor();
            cpyC.copy(*this, RefVariant(rvalue));
        }
        else
        {
            // raw copy memory
            std::memcpy(data_, &rvalue, sizeof(T));
        }
    }
    
    // return the rvalue
    return rvalue;
}


} // namespace xm

#endif	/* XM_VARIANT_INL */

