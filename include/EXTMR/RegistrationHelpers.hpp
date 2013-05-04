/* 
 * File:   TypeCreationHelpers.hpp
 * Author: manuele
 *
 * Created on May 2, 2013, 9:32 PM
 */

#ifndef EXTMR_TYPECREATIONHELPERS_HPP
#define	EXTMR_TYPECREATIONHELPERS_HPP

#include <EXTMR/Exceptions/NotFoundExceptions.hpp>


namespace extmr {
    
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


template<>
struct GetTypeName<void>
{
    std::string operator()()
    {
        return "void";
    }
};


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


template<typename T, std::size_t size>
struct GetTypeName<T(*)[size]>
{
    std::string operator()()
    {
        std::string str = GetTypeName<T>()();
        str += "(*)";
        str += GetArrayExtentsSignature<T[size]>()();
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


template<typename T>
struct CreateType
{
    Type* operator()()
    {
        return new PrimitiveType(GetTypeName<T>()(), sizeof(T),
                typeid(T), GetTypeConstructor<T>()(),
                GetTypeCopyConstructor<T>()(), GetTypeDestructor<T>()(),
                GetTypeAssignOperator<T>()());
    }
};


template<typename T>
struct CreateType<T*>
{
    Type* operator()()
    {
        const Type& pointedType = TypeRegister::getSingleton().registerType<T>();
        
        return new PointerType(GetTypeName<T*>()(), sizeof(T*),
                typeid(T*), GetTypeConstructor<T*>()(),
                GetTypeCopyConstructor<T*>()(), GetTypeDestructor<T*>()(),
                GetTypeAssignOperator<T*>()(), pointedType);
    }
};


template<typename T, std::size_t size>
struct CreateType<T[size]>
{
    Type* operator()()
    {
        const Type& elementType =
                        TypeRegister::getSingleton().registerType<T>();
        
        return new PointerType(GetTypeName<T[size]>()(), sizeof(T[size]),
                typeid(T[size]), GetTypeConstructor<T[size]>()(),
                NULL, GetTypeDestructor<T[size]>()(), NULL, elementType);
    }
};


template<class T>
struct BuildClass
{
    void operator()(Class& clazz) const
    {
        
    }
};


/**
 * This helper function is called from the CreateType functor when registering
 * a non compound class. This function is provided to keep the all the possible
 * code outside of macros.
 * 
 * As a side effect, this function allow the GetConstructor, GetCopyConstructor,
 * GetDestructor and GetAssingOperator to be specialized after CreateType
 * because gcc seems to postpone the function templates instantiations after all
 * the class template specializations are available.
 * However I don't konw if this is a standard behavior.
 */

template<class T>
Type* createClass()
{    
    Class* clazz = new Class(GetTypeName<T>()(), sizeof(T),
            typeid(T), GetTypeConstructor<T>()(),
            GetTypeCopyConstructor<T>()(), GetTypeDestructor<T>()(),
            GetTypeAssignOperator<T>()());
    
    BuildClass<T>()(*clazz);
    
    return clazz;
};


/**
 * This helper function is called from the CreateType functor when registering
 * a compound class. This function is provided to keep the all the possible
 * code outside of macros.
 */
template<class T>
Type* createCompoundClass()
{
    TypeRegister& typeReg = TypeRegister::getSingleton();
                
    ConstTypeVector templateArgs = GetTemplateArgs<T>()();
    
    const Template* tempjate;
    
    try
    {
        tempjate = &typeReg.getTemplate(GetTemplateName<T>()());
    }
    catch(const TemplateNotFoundException& e)
    {
        tempjate = new Template(GetTemplateName<T>()(), templateArgs.size());
        typeReg.addTemplate(*tempjate);
    }
    
    Class* clazz = new CompoundClass(GetTypeName<T>()(), sizeof(T),
            typeid(T), GetTypeConstructor<T>()(),
            GetTypeCopyConstructor<T>()(), GetTypeDestructor<T>()(),
            GetTypeAssignOperator<T>()(), *tempjate, templateArgs);
    
    BuildClass<T>()(*clazz);
    
    return clazz;
};


/**
 * This template class allow a class to be registered without any extra code
 * inside the main() or any other function.
 * Registration is performed by the constructor on instantiation.
 */
template<class T>
class AutoRegisterer
{
    AutoRegisterer()
    {
        TypeRegister::getSingleton().registerType<T>();\
    }
    
    static AutoRegisterer autoregisterer;
};

template<class T>
AutoRegisterer<T> AutoRegisterer<T>::autoregisterer;


} //namespace extmr

#endif	/* EXTMR_TYPECREATIONHELPERS_HPP */

