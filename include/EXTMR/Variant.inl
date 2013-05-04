/* 
 * File:   Variant.inl
 * Author: Manuele Finocchiaro
 *
 * Created on December 26, 2012, 17.43
 */

#ifndef EXTMR_VARIANT_INL
#define	EXTMR_VARIANT_INL

#include <EXTMR/Exceptions/VariantTypeException.hpp>
#include <EXTMR/Exceptions/VariantCostnessException.hpp>
#include <EXTMR/Variant.hpp>


namespace extmr{

template<typename T>
void Variant::Initialize<T>::operator()(T& data)
{
    // retrieve the type register
    TypeRegister& typeReg = TypeRegister::getSingleton();

    // ensure the type of the data is registered and retrieve it
    variant_.type_ = &typeReg.registerType<T>();

    if (variant_.flags_ & Reference)
    {
        // store the pointer to the data
        variant_.data_ = &data;
    }
    else
    {
        // copy the data and store the pointer to it
        variant_.data_ = new T(data);
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
        Initialize<T*>(variant_)(data);
    }
    
    // A reference to the variant that is being initialized
    Variant& variant_;
};


template<typename T>
Variant::Variant(const T& data)
: flags_(0)
{
    // if the type is a constant array, then the type will be converted to a
    // pointer to constant
    if (IsArray<T>::value) flags_ |= PointerToConst;
    
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
    
    Initialize<NonConstT>(*this)(const_cast<NonConstT&>(data));
}


template<typename T>
Variant::operator T&() const
{
    // retrieve the type register
    TypeRegister& typeReg = TypeRegister::getSingleton();

    // ensure the type of the data is registered and retrieve it
    const Type& targetType = typeReg.registerType<T>();
    
    // check for type compatibility
    if (!canReinterpret(*type_, targetType))
        throw VariantTypeException(targetType, *type_);
    
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

    // return the data
    return *reinterpret_cast<T*>(data_);
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

