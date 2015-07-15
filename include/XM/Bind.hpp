/******************************************************************************      
 *      Extended Mirror: Bind.hpp                                         *
 ******************************************************************************
 *      Copyright (c) 2012-2015, Manuele Finocchiaro                          *
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


#ifndef XM_BIND_HPP
#define	XM_BIND_HPP


#define XM_MNP(member) #member, &ClassT::member
#define XM_BIND_BASE(BaseT) bindBase<ClassT, BaseT>();
#define XM_BIND_PBASE(BaseT) bindPmBase<ClassT, BaseT>(); // polymorphic base

#include <XM/BindFunction.hpp>
#include <XM/BindGetNSetProperty.hpp>
#include <XM/BindMethod.hpp>

namespace xm{


template<typename T, T val>
Constant& bindConstant(const std::string& name)
{
    // ensure the types are registered
    registerType<T>();

    std::pair<std::string, std::string> nameParts = splitName(name, NameTail);
    Namespace& name_space = defineNamespace(nameParts.first);

    // create the proper Constant
    Constant* xmConstant =
            new ConstantImpl<T, val>(nameParts.second, name_space);
    name_space.addItem(*xmConstant);
    return *xmConstant;
}


template<class ClassT, class BaseT>
void bindBase()
{
    // ensure that base class is registered
    registerType<BaseT>();
    
    Class& clazz = const_cast<Class&>(getClass<ClassT>());
    Class& base = const_cast<Class&>(getClass<BaseT>());
    
    // bind them together
    clazz.addBaseClass(base);
    
    // bind RefCaster to base
    clazz.addMember(*new RefCasterImpl<ClassT, BaseT>());
}


template<class ClassT, class BaseT>
void bindPmBase()
{
    bindBase<ClassT, BaseT>();
    
    // bind RefCast from BaseT to CassT
    RefCaster* refCaster = new RefCasterImpl<BaseT, ClassT>();
    const_cast<Class&>(getClass<BaseT>()).addMember(*refCaster);
}


template<class ClassT, typename FieldT>
Property& bindProperty(const std::string& name, FieldT ClassT::* field)
{
    // ensure that the type is registered
    registerType<FieldT>();
    
    // build the Property and add it to the Class
    Property* xmProperty = new PropertyField<ClassT, FieldT>(name, field);
    const_cast<Class&>(getClass<ClassT>()).addMember(*xmProperty);
    return *xmProperty;
}


template<class ClassT, typename FieldT, std::size_t size>
Property& bindProperty(const std::string& name,
        FieldT (ClassT::* field) [size])
{
    // ensure that the type is registered
    registerType<FieldT[size]>();
    
    // build the Property  and add it to the Class
    Property* xmProperty =
            new PropertyArrayField<ClassT, FieldT[size]>(name, field);
    const_cast<Class&>(getClass<ClassT>()).addMember(*xmProperty);
    return *xmProperty;
}


} // namespace xm

#endif	/* XM_BIND_HPP */

