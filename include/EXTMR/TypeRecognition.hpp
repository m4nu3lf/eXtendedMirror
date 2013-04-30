/* 
 * File:   TypeRecognition.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on August 12, 2012, 10.22
 */

#ifndef EXTMR_TYPERECOGNITION_HPP
#define	EXTMR_TYPERECOGNITION_HPP

namespace extmr{

/*
 * Utility templates for type recognition.
 */

/**
 * Specialize for each supported type. Each specialization must provide at least
 * a static std::string getName() method a const Type::Category category
 * field.
 */
template<typename T>
struct TypeRecognizer
{};


/**
 * Specialize for each supported template type.
 * Each specialization must define the template parameters types
 * with names T1, T2, T3, T4, the constant uint argN and the static method 
 * std::string getName();
 * The types of this non specialized version or those unused in a specialization
 * must evaluate to void.
 */
template<class T>
struct TemplateRecognizer
{
    typedef void T1;
    typedef void T2;
    typedef void T3;
    typedef void T4;
    static std::string getName()
    {
        return "";
    }
    static const uint argN = 0;
};


/**
 * Partial template specialization of the TypeRecognizer struct for pointers.
 */
template<typename T>
struct TypeRecognizer<T*>
{
    /**
     * If TypeRecognizer<T>::getName() returns "SomeType" then this method
     * returns "SomeType*".
     * 
     * @return The type name.
     */
    static std::string getName()
    {
        std::string str = TypeRecognizer<T>::getName();
        str += "*";
        return str;
    }
    
    static const Type::Category category = Type::Pointer;
};


/**
 * Partial template specialization of the TypeRecognizer struct for arrays.
 */
template<typename T, uint size>
struct TypeRecognizer<T[size]>
{
    typedef typename RemoveAllExtents<T>::Type NonArrayT;
    
    /**
     * If TypeRecognizer<T>::getName() returns "SomeType" then this method
     * returns "SomeType[size_1][size_2]...[size_n]".
     * 
     * @return The type name.
     */
    static std::string getName()
    {
        return TypeRecognizer<NonArrayT>::getName() +
                ArraySizeSignature<T[size]>::getSizeSignature();
    }
    
    static const Type::Category category = Type::Array;
};


/**
 * Check if a given type is instatiable.
 * Non array types are supposed to be instantiable by default.
 * Specialize this class for each non instantiable class.
 */
template<typename T>
struct IsInstantiable
{
    static const bool value = true;
};


template<typename T, std::size_t size>
struct IsInstantiable<T[size]>
{
    static const bool value = false;
};


/**
 * Check if a given type is copyable.
 * Non array types are supposed to be copyable by default.
 * Specialize this class for each non copyable class.
 */
template<typename T>
struct IsCopyable
{
    static const bool value = true;
};


template<typename T, std::size_t size>
struct IsCopyable<T[size]>
{
    static const bool value = false;
};


/**
 * Check if a given type is copyable.
 * Non array types are supposed to be lvalue by default.
 * Specialize this class for each non lvalue class.
 */
template<typename T>
struct IsAssignable
{
    static const bool value = true;
};


template<typename T, std::size_t size>
struct IsAssignable<T[size]>
{
    static const bool value = false;
};



} // namespace extmr

#endif	/* EXTMR_TYPERECOGNITION_HPP */

