/******************************************************************************      
 *      Extended Mirror: Shortcuts.hpp                                        *
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


#ifndef XM_SHORTCUTS_HPP
#define	XM_SHORTCUTS_HPP

namespace xm {

class Constant;
class Enum;
class Function;
class Template;
class Variable;

template <typename T>
const Type& registerType()
{
    return Register::getSingleton().registerType<T>();
}


template <class C>
const Class& registerClass()
{
    return Register::getSingleton().registerClass<C>();
}


inline
Namespace& defineNamespace(const std::string& path)
{
    return Register::getSingleton().defineNamespace(path);
}


inline
const Namespace& getNamespace(const std::string& path)
{
    return Register::getSingleton().getItem<Namespace>(path);
}


template <typename T>
const Type& getType()
{
    return Register::getSingleton().getType<T>();
}


inline
const Type& getType(const std::string& name)
{
    return Register::getSingleton().getItem<Type>(name);
}


template <typename C>
const Class& getClass()
{
    return Register::getSingleton().registerClass<C>();
}


template <typename C>
const CompoundClass& getCompoundClass()
{
    return Register::getSingleton().registerClass<C>();
}


inline
const Class& getClass(const std::string& name)
{
    return Register::getSingleton().getItem<Class>(name);
}


inline
const CompoundClass& getCompoundClass(const std::string& name)
{
    return Register::getSingleton().getItem<CompoundClass>(name);
}


template <typename T>
const Type& getTypeOf(T& var)
{
    return getTypeOf<T>(var);
}


template <typename C>
const Class& getClassOf(C& object)
{
    return Register::getSingleton().getClassOf<C>(object);
}


inline
const Constant& getConstant(const std::string& name)
{
    return Register::getSingleton().getItem<Constant>(name);
}


inline
const Enum& getEnum(const std::string& name)
{
    return Register::getSingleton().getItem<Enum>(name);
}


inline
const Function& getFunction(const std::string& name)
{
    return Register::getSingleton().getItem<Function>(name);
}


inline
const Function& getFunction(const Function& function)
{
    return Register::getSingleton().getItem<Function>(function);
}


inline
const Template& getTemplate(const std::string& name)
{
    return Register::getSingleton().getItem<Template>(name);
}


inline
const Variable& getVariable(const std::string& name)
{
    return Register::getSingleton().getItem<Variable>(name);
}


inline
void unregisterType(const std::string& name)
{
    return Register::getSingleton().unregisterType(name);
}


inline
void unregisterType(const std::type_info& typeId)
{
    return Register::getSingleton().unregisterType(typeId);
}


} //namespace xm


#endif	/* XM_SHORTCUTS_HPP */

