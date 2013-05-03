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
Type* createClass()
{    
    Class* clazz = new Class(GetTypeName<T>()(), sizeof(T),
            typeid(T), GetTypeConstructor<T>()(),
            GetTypeCopyConstructor<T>()(), GetTypeDestructor<T>()(),
            GetTypeAssignOperator<T>()());
    
    BuildClass<T>()(*clazz);
    
    return clazz;
};


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


} //namespace extmr

#endif	/* EXTMR_TYPECREATIONHELPERS_HPP */

