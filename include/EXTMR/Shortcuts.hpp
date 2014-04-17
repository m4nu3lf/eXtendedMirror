/******************************************************************************      
 *      Extended Mirror: Shortcuts.hpp                                        *
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


#ifndef EXTMR_SHORTCUTS_HPP
#define	EXTMR_SHORTCUTS_HPP

namespace extmr {


template <typename T>
const Type& registerType()
{
    return TypeRegister::getSingleton().registerType<T>();
}


template <class C>
const Class& registerClass()
{
    return TypeRegister::getSingleton().registerClass<C>();
}


template <typename T>
const Type& getType()
{
    return TypeRegister::getSingleton().getType<T>();
}


inline
const Type& getType(const std::string& name)
{
    return TypeRegister::getSingleton().getType(name);
}


template <typename C>
const Class& getClass()
{
    return TypeRegister::getSingleton().registerClass<C>();
}


inline
const Class& getClass(const std::string& name)
{
    return TypeRegister::getSingleton().getClass(name);
}


template <typename T>
const Type& getTypeOf(T& var)
{
    return TypeRegister::getSingleton().getTypeOf<T>(var);
}


template <typename C>
const Class& getClassOf(C& object)
{
    return TypeRegister::getSingleton().getClassOf<C>(object);
}


inline
const void unregisterType(const std::string& name)
{
    return TypeRegister::getSingleton().unregisterType(name);
}


inline
const void unregisterType(const std::type_info& typeId)
{
    return TypeRegister::getSingleton().unregisterType(typeId);
}


} //namespace extmr


#endif	/* EXTMR_SHORTCUTS_HPP */

