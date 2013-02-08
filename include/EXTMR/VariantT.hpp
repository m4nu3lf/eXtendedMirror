/* 
 * File:   VariantT.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 26 December 2012, 17.43
 */

#ifndef EXTMR_VARIANTT_HPP
#define	EXTMR_VARIANTT_HPP

#include <EXTMR/Exceptions/BadType.hpp>
#include <EXTMR/Exceptions/ConstnessBreak.hpp>
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
        variant.typePtr = &typeReg.registerType<T>();

        if (variant.flags & Variant::Reference)
        {
            // store the pointer to the data
            variant.dataPtr = &data;
        }
        else
        {
            // copy the data and store the pointer to it
            variant.dataPtr = new T(data);
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
    VariantInitializer<T> initializer(*this);
    initializer(const_cast<T&>(data));
}

template<typename T>
Variant::Variant(T& data, char flags)
: flags(flags)
{
    typedef typename RemoveConst<T>::Type NcvT;
    
    // if the type is a constant one, and we are storing by reference, preserve constness
    if ((flags & Reference) && IsConst<T>::value) flags |= Const;
    
    VariantInitializer<NcvT> initializer(*this);
    initializer(const_cast<NcvT&>(data));
}

template<typename T>
Variant::operator T&() const
{
    // retrieve the type register
    TypeRegister& typeReg = TypeRegister::getTypeReg();

    // ensure the type of the data is registered and retrieve it
    const Type& targetType = typeReg.registerType<T>();
    
    // check for type compatibility
    if (!canReinterpret(*typePtr, targetType))
        throw BadType(*typePtr, targetType);
    
    // check for constness correctness
    if (!IsConst<T>::value && flags & Const)
        throw ConstnessBreak(*typePtr);
    
    // check for pointed type's constness correctness
    if (flags & PointerToConst && !IsConst<typename RemovePointer<T>::Type>::value)
        throw ConstnessBreak(typePtr->getPointedType());

    // return the data
    return *reinterpret_cast<T*>(dataPtr);
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
    if (!typePtr || type != *typePtr)
    {
        // remove the previously allocated data if any
        if (dataPtr && typePtr) typePtr->deleteInstance(dataPtr);
        
        // set the new Type
        typePtr = &type;
        
        // allocate a new object
        dataPtr = new T();
    }
    
    // call the assignment operator
    typePtr->assignInstance(dataPtr, &rvalue);
    
    // return the rvalue
    return rvalue;
}

} // namespace extmr

#endif	/* EXTMR_VARIANTT_HPP */

