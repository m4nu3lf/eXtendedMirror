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
 * Specialize for each supported template type. Each specialization must define the template
 * parameters types with names T1, T2, T3, T4, the constant uint argN and the static method std::string getName();
 * The types of this non specialized version or those unused in a specialization must evaluate to void.
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
     * If TypeRecognizer<T>::getName() returns "SomeType" then this method returns "SomeType*".
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
     * If TypeRecognizer<T>::getName() returns "SomeType" then this method returns "SomeType[size_1][size_2]...[size_n]".
     * 
     * @return The type name.
     */
    static std::string getName()
    {
        return TypeRecognizer<NonArrayT>::getName() + ArraySizeSignature<T[size]>::getSizeSignature();
    }
    
    static const Type::Category category = Type::Array;
};

} // namespace extmr

#endif	/* EXTMR_TYPERECOGNITION_HPP */

