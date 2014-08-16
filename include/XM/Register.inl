/******************************************************************************      
 *      Extended Mirror: Register.inl                                         *
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


#ifndef XM_REGISTER_INL
#define XM_REGISTER_INL

#include <XM/RegistrationHelpers.hpp>

namespace xm{


template<typename T>
const Type& Register::getTypeOf(const T& obj) const
{   
    return getType<T>();
}


template<typename T>
const Class& Register::getClassOf(const T& obj) const
{
    return getClass<T>();
}


template<typename T>
const Type& Register::getType() const
{   
    static const Type& type = getType(typeid(T));
    return type;
}


template<typename T>
const Class& Register::getClass() const
{   
    static const Class& clazz = getClass(typeid(T));
    return clazz;
}


template<typename T>
const Type& Register::registerType()
{
    typedef typename RemoveReference<T>::Type NonRefT;
    typedef typename RemoveAllCVQualifiers<NonRefT>::Type NonQualifiedT;
    
    // call the actual registration method with the unqualified type
    return registerType_<NonQualifiedT>();
}


template<typename T>
const Class& Register::registerClass()
{
    return dynamic_cast<const Class&>(registerType<T>());
}


template<typename T>
Type& Register::registerType_()
{
    // store registered type for subsequent calls
    static Type* type = NULL;
    
    // check for already registered type
    if (type) return *type;
    
    type = &CreateType<T>()();
    
    // add Type to its Namespace
    Namespace& name_space = const_cast<Namespace&>(type->getNamespace());
    addItem(*type);
    
    types_.insert(type);
    
    Class* clazz = dynamic_cast<Class*>(type);
    if (clazz)
    {   
        classes_.insert(clazz);
        
        // build class members
        BuildClass<T> buildClass;
        buildClass();
    }
    
    XM_DEBUG_MSG("type \"" << type->getName() << "\" registered")
    
    // return the type
    return *type;
}


/* This specialization is needed because during method registration Empty
 is used as a place holder type for parameters.
 getType is then called on all the parameters types, so Empty too, and the
 result must be Type::Void*/
template<>
inline const Type& Register::getType<Empty>() const
{   
    return getType<void>();
}


} // namespca xm

#endif // XM_REGISTER_INL
