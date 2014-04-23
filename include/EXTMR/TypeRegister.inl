/******************************************************************************      
 *      Extended Mirror: TypeRegister.inl                                     *
 ******************************************************************************
 *      Copyright (c) 2012-2014, Manuele Finocchiaro                          *
 *      All rights reserved.                                                  *
 ******************************************************************************
 * Redistribution and use in source and binary forms, with or without         *
 * modification, are permitted provided that the following conditions         *
 * are met:                                                                   *
 *                                                                            *
 *    1. Redistributions of source code must retain the above copyright       *
 *       notice, this list of conditions and the following disclaimer.        *
 *                                                                            *
 *    2. Redistributions in binary form must reproduce the above copyright    *
 *       notice, this list of conditions and the following disclaimer in      *
 *       the documentation and/or other materials provided with the           *
 *       distribution.                                                        *
 *                                                                            *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"* 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE  *
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE *
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE  *
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR        *
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF       *
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   *
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN    *
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)    *
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF     *
 * THE POSSIBILITY OF SUCH DAMAGE.                                            *
 *****************************************************************************/


#ifndef EXTMR_TYPEREGISTER_INL
#define EXTMR_TYPEREGISTER_INL

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
    
    // push the type object into the type sets
    typesById_.insert(type);
    typesByName_.insert(type);
    
    Class* clazz = dynamic_cast<Class*>(type);
    if (clazz)
    {
        // push the class object into the class set
        classesById_.insert(clazz);
        
        // build class members
        BuildClass<T> buildClass;
        buildClass();
    }
    
    DEBUG_MSG("type \"" << type->getName() << "\" registered")
    
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


/* This specialization is needed because during method registration Empty
 is used as a place holder type for parameters.
 getType is then called on all the parameters types, so Empty too, and the
 result must be Type::Void*/
template<>
inline const Type& TypeRegister::getType<Empty>() const
{   
    return getType<void>();
}


} // namespca extmr

#endif // EXTMR_TYPEREGISTER_INL
