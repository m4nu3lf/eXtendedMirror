/******************************************************************************      
 *      Extended Mirror: TypeRegister.cpp                                     *
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


#include <XM/Utils/Utils.hpp>
#include <XM/ExtendedMirror.hpp>
#include <XM/Exceptions/NotFoundExceptions.hpp>

#include "XM/Namespace.hpp"

using namespace std;
using namespace xm;

TypeRegister& TypeRegister::getSingleton()
{
    static TypeRegister typeReg;
    return typeReg;
}


TypeRegister::TypeRegister()
{   
    // register the base types
    registerType<char>();
    registerType<short>();
    registerType<int>();
    registerType<float>();
    registerType<double>();
    registerType<uchar>();
    registerType<ushort>();
    registerType<bool>();
    
    // a void class is needed in the type register
    Class* voidClass = new Class("void");
    globalNamespace_.add<Type>insert(voidClass);
}


const Type& TypeRegister::getType(const string& typeName) const
{
    globalNamespace_.getType(typeName);
}


const Type& TypeRegister::getType(const type_info& cppType) const
{
    const Type* type = ptrSet::findByKey(types_, cppType);
    if (type)
        return *type;
    else
        throw TypeNotFoundException(cppType.name());
}


const Class& TypeRegister::getClass(const string& className) const
{
    globalNamespace_.getClass(className);
}


const Class& TypeRegister::getClass(const type_info& cppType) const
{
    return dynamic_cast<const Class&>(getType(cppType));
}


const Template& TypeRegister::getTemplate(const string& templateName) const
{
    globalNamespace_.getTemplate(templateName);
}


void TypeRegister::unregisterType(const std::string& typeName)
{
    Type* type = ptrSet::removeByKey(types_, typeName);
    ptrSet::removeByKey(typesById_, type->getId());
    if (!type)
        throw TypeNotFoundException(typeName);
    
    if (type->getCategory() | Type::Class)
    {
        Class* clazz = ptrSet::removeByKey(classesById_, type->gegetCppId);
    }
    
    delete type;
}


void TypeRegister::unregisterType(const std::type_info& cppType)
{
    Type* type = ptrSet::removeByKey(types_, cppType);
    ptrSet::removeByKey(typesByName_, type->getName());
    if (!type)
        throw TypeNotFoundException(cppType.name());
    
    if (type->getCategory() | Type::Class)
    {
        ptrSet::removeByKey(classesById_, cppType);
    }
    
    delete type;
}


TypeRegister::~TypeRegister()
{

}