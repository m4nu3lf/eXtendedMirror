/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_TYPEREGISTER_INL
#define EXTMR_TYPEREGISTER_INL

#include <EXTMR/MemberWrappers.hpp>
#include <EXTMR/RegistrationHelpers.hpp>

namespace extmr{


template<typename T>
const Type& TypeRegister::getTypeOf(const T& obj) const
{   
    return getType(typeid(obj));
}


template<typename T>
const Class& TypeRegister::getClassOf(const T& obj) const
{
    return getClass(typeid(obj));
}


template<typename T>
const Type& TypeRegister::getType() const
{   
    static const Type& type = getType(typeid(T));
    return type;
}


template<typename T>
const Class& TypeRegister::getClass() const
{   
    static const Class& clazz = getClass(typeid(T));
    return clazz;
}


template<typename T>
const Type& TypeRegister::registerType()
{
    typedef typename RemoveReference<T>::Type NonRefT;
    typedef typename RemoveAllCVQualifiers<NonRefT>::Type NonQualifiedT;
    
    // call the actual registration method with the unqualified type
    return registerType_<NonQualifiedT>();
}


template<typename T>
const Class& TypeRegister::registerClass()
{
    return dynamic_cast<const Class&>(registerType<T>());
}


template<typename T>
Type& TypeRegister::registerType_()
{
    // store registered type for subsequent calls
    static Type* type = NULL;
    
    // check for already registered type
    if (type) return *type;
    
    type = CreateType<T>()();
    
    if (type->getCategory() & Type::Class)
    {   
        Class* clazz = dynamic_cast<Class*>(type);
        
        // push the class object into the class sets
        classesById_.insert(clazz);
    }
    
    // push the type object into the type sets
    typesById_.insert(type);
    typesByName_.insert(type);
    
    // call the function registered for call back
    if (getRegCallBack())
        getRegCallBack()(*type);
    
    // return the type
    return *type;
}


/*
 * Calling the registerType with a void type has no consequences and a null type
 * reference is returned. This must be ensured because the method registration
 * mechanism call this for the returned method type and this type can be void.
 */
template<>
inline const Type& TypeRegister::registerType<void>()
{
    return getType<void>();
}


} // namespca extmr

#endif // EXTMR_TYPEREGISTER_INL
