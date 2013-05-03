/* 
 * File:   TypeRecognition.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on August 12, 2012, 10.22
 */

#ifndef EXTMR_TYPERECOGNITION_HPP
#define	EXTMR_TYPERECOGNITION_HPP

namespace extmr{


template<typename T>
struct GetTypeName
{};


/**
 * The getSizeSignature method returns a string in the form [size_1][size_2]...[size_n]
 * if type T is an array in the form T[size_1][size_2]...[size_n],
 * an empty string if T is not an array.
 */
template<typename T>
struct GetArrayExtentsSignature
{
    std::string operator()()
    {
        return "";
    }
};


template<typename T, std::size_t size>
struct GetArrayExtentsSignature<T[size]>
{
    std::string operator()()
    {
        std::stringstream sstream;
        sstream << "[" << size << "]" << GetArrayExtentsSignature<T>()();
        return sstream.str();
    }
};


template<typename T, uint size>
struct GetTypeName<T[size]>
{
    typedef typename RemoveAllExtents<T>::Type NonArrayT;
    
    /**
     * If GetTypeName<T>::getName() returns "SomeType" then this method
     * returns "SomeType[size_1][size_2]...[size_n]".
     * 
     * @return The type name.
     */
    std::string operator()()
    {
        return GetTypeName<NonArrayT>()() +
                GetArrayExtentsSignature<T[size]>()();
    }
};


template<typename T>
struct GetTemplateName
{};


template<typename T>
struct GetTemplateArgs
{};


template<typename T>
struct GetTypeName<T*>
{
    std::string operator()()
    {
        std::string str = GetTypeName<T>()();
        str += "*";
        return str;
    }
};


template<typename T>
struct GetTypeConstructor
{
    Constructor* operator()()
    {
        return new Create<T>();
    }
};


template<typename T>
struct GetTypeCopyConstructor
{
    CopyConstructor* operator()()
    {
        return new Copy<T>();
    }
};


template<typename T>
struct GetTypeAssignOperator
{
    AssignOperator* operator()()
    {
        return new Assign<T>();
    }
};


template<typename T>
struct GetTypeDestructor
{
    Destructor* operator()()
    {
        return new Destroy<T>();
    }
};


} // namespace extmr

#endif	/* EXTMR_TYPERECOGNITION_HPP */

