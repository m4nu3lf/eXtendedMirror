/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_VARIANT_INL
#define	EXTMR_VARIANT_INL

#include <EXTMR/Exceptions/VariantTypeException.hpp>
#include <EXTMR/Exceptions/VariantCostnessException.hpp>
#include <EXTMR/Variant.hpp>

#include "Type.hpp"
#include "RefCaster.hpp"


namespace extmr{
    

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
bool Variant::isPointerToConst() const
{
    return flags_ & PointerToConst;
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
    // retrieve the type register
    TypeRegister& typeReg = TypeRegister::getSingleton();

    // ensure the base type is registered.
    typeReg.registerType<T>();
    
    // if type is polymorphic take the actual type of the object.
    variant_.type_ = &typeReg.getTypeOf(data);

    if (variant_.flags_ & Reference)
    {
        // store the pointer to the data
        variant_.data_ = &data;
    }
    else
    {
        // copy the data and store the pointer to it
        variant_.data_ = variant_.type_->copyInstance(&data);
    }

    // if the type is a pointer to a constant set the proper flag.
    if (IsConst<typename RemovePointer<T>::Type>::value)
        variant_.flags_ |= PointerToConst;
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
Variant::Variant(T data)
: flags_(0)
{
    // if the type is a constant array, then the type will be converted to a
    // pointer to constant
    if (IsArray<T>::value) flags_ |= PointerToConst;
    
    // Call initizlier functor
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
    // pointer to constant
    if (IsArray<T>::value && IsConst<T>::value) flags_ |= PointerToConst;
    
    // Call initializer functor
    Initialize<NonConstT>(*this)(const_cast<NonConstT&>(data));
}


template<typename T>
Variant::operator T&() const
{
    // retrieve the type register
    TypeRegister& typeReg = TypeRegister::getSingleton();

    // ensure the type of the data is registered and retrieve it
    const Type& targetType = typeReg.registerType<T>();
    
    // check for constness correctness
    if (!IsConst<T>::value && flags_ & Const)
        throw VariantCostnessException(*type_);
    
    // check for pointed type's constness correctness
    if (flags_ & PointerToConst &&
            !IsConst<typename RemovePointer<T>::Type>::value)
    {
        const Type& pointedType =
                dynamic_cast<const PointerType&>(*type_).getPointedType();
        throw VariantCostnessException(pointedType);
    }
    
    // check for type compatibility
    if (targetType == *type_)
    {
        // just reinterpret pointer
        return *reinterpret_cast<T*>(data_);
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
        const RefCaster* caster = 
                ptrSet::findByKey(casters, std::make_pair(type_, &targetType));
        
        // if caster found, cast this variant and return
        if (caster)
        {
            return caster->cast(*this).to<T>();
        }
        else
        {
            // for every ref caster, cast to that, then try to recast to T
            Const_RefCaster_Set::iterator ite = casters.begin();
            while(ite != casters.end())
            {
                try
                {
                    return (*ite)->cast(*this).to<T>();
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
inline T& Variant::to() const
{
    return *this;
}


template<>
Empty& Variant::to<Empty>() const;


template<typename T>
const T& Variant::operator=(const T& rvalue)
{   
    // get the type register
    TypeRegister& typeReg = TypeRegister::getSingleton();
    
    // get the Type
    const Type& type = typeReg.getType<T>();
    
    // check if types are the same
    if (!type_ || type != *type_)
    {
        // remove the previously allocated data if any
        if (data_ && type_) type_->deleteInstance(data_);
        
        // set the new Type
        type_ = &type;
        
        // allocate a new object
        data_ = new T();
    }
    
    // call the assignment operator
    type_->assignInstance(data_, &rvalue);
    
    // return the rvalue
    return rvalue;
}


} // namespace extmr

#endif	/* EXTMR_VARIANT_INL */

