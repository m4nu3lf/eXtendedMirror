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

/**
 * Initialize a variant. If the type of the variant is an array
 * then the variant will store a pointer to the first element.
 * If the array is multidimensional the elements are considered the inner most
 * ones that are not array (i.e. all extents are removed).
 * In this case flags will be ignored and set to default.
 */
template<typename T>
struct VariantInitializer
{
    VariantInitializer(Variant& variant) : variant(variant){};
    
    void operator()(T& data)
    {
        // retrieve the type register
        TypeRegister& typeReg = TypeRegister::getTypeReg();

        // ensure the type of the data is registered and retrieve it
        variant.type_ = &typeReg.registerType<T>();

        if (variant.flags & Variant::Reference)
        {
            // store the pointer to the data
            variant.data_ = &data;
        }
        else
        {
            // copy the data and store the pointer to it
            variant.data_ = new T(data);
        }
        
        // if the type is a pointer to a constant set the proper flag.
        if (IsConst<typename RemovePointer<T>::Type>::value)
            variant.flags |= Variant::PointerToConst;
    }
    
    // A reference to the variant that is being initialized
    Variant& variant;
};


/**
 * If the type is a multidimensional array, remove one
 * extent from the type, construct an initializer for this type
 * and pass to the initializer the pointer of the first element
 * along the removed dimension.
 */
template<typename T, std::size_t size1, std::size_t size2>
struct VariantInitializer<T[size1][size2]>
{
    VariantInitializer(Variant& variant) : variant(variant){};
    
    void operator()(T data[size1][size2])
    {
        VariantInitializer<T[size2]> initializer(variant);
        initializer(data[0]);
    }
    
    // A reference to the variant that is being initialized
    Variant& variant;
};


/**
 * If the type is a one-dimensional array, create an initializer
 * for a pointer to the element type, and pass it the address of the
 * first element.
 */
template<typename T, std::size_t size>
struct VariantInitializer<T[size]>
{
    VariantInitializer(Variant& variant) : variant(variant){};
    
    void operator()(T data[size])
    {
        VariantInitializer<T*> initializer(variant);
        initializer(data);
    }
    
    // A reference to the variant that is being initialized
    Variant& variant;
};


template<typename T>
Variant::Variant(const T& data)
: flags(0)
{
    // if the type is a constant array, then the type will be converted to a
    // pointer to constant, so remember this constness
    if (IsArray<T>::value) this->flags |= PointerToConst;
    
    VariantInitializer<T> initializer(*this);
    initializer(const_cast<T&>(data));
}


template<typename T>
Variant::Variant(T& data, char flags)
: flags(flags)
{
    typedef typename RemoveConst<T>::Type NonConstT;
    
    // if the type is a constant one, and a storing is performed by reference,
    // remember constness
    if ((flags & Reference) && IsConst<T>::value) this->flags |= Const;
    
    // if the type is a constant array, then the type will be converted to a
    // pointer to constant, so remember this constness
    if (IsArray<T>::value && IsConst<T>::value) this->flags |= PointerToConst;
    
    VariantInitializer<NonConstT> initializer(*this);
    initializer(const_cast<NonConstT&>(data));
}


template<typename T>
Variant::operator T&() const
{
    // retrieve the type register
    TypeRegister& typeReg = TypeRegister::getTypeReg();

    // ensure the type of the data is registered and retrieve it
    const Type& targetType = typeReg.registerType<T>();
    
    // check for type compatibility
    if (!canReinterpret(*type_, targetType))
        throw VariantTypeException(*type_, targetType);
    
    // check for constness correctness
    if (!IsConst<T>::value && flags & Const)
        throw VariantCostnessException(*type_);
    
    // check for pointed type's constness correctness
    if (flags & PointerToConst &&
            !IsConst<typename RemovePointer<T>::Type>::value)
        throw VariantCostnessException(type_->getPointedType());

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
    TypeRegister& typeReg = TypeRegister::getTypeReg();
    
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

