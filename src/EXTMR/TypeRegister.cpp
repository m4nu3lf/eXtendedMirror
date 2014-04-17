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


#include <EXTMR/Utils/Utils.hpp>
#include <EXTMR/ExtendedMirror.hpp>
#include <EXTMR/Exceptions/NotFoundExceptions.hpp>

using namespace std;
using namespace extmr;

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
    typesByName_.insert(voidClass);
    typesById_.insert(voidClass);
}


const Type& TypeRegister::getType(const string& typeName) const
{
    const Type* type = ptrSet::findByKey(typesByName_, typeName);
    if (type)
        return *type;
    else
        throw TypeNotFoundException(typeName);
}


const Type& TypeRegister::getType(const type_info& cppType) const
{
    const Type* type = ptrSet::findByKey(typesById_, cppType);
    if (type)
        return *type;
    else
        throw TypeNotFoundException(cppType.name());
}


const Class& TypeRegister::getClass(const string& className) const
{
    return dynamic_cast<const Class&>(getType(className));
}


const Class& TypeRegister::getClass(const type_info& cppType) const
{
    return dynamic_cast<const Class&>(getType(cppType));
}


void TypeRegister::addTemplate(const Template& tempjate)
{
    templates_.insert(&tempjate);
}


const Template& TypeRegister::getTemplate(const string& templateName) const
{
    const Template* tempjate = ptrSet::findByKey(templates_, templateName);
    if (tempjate)
        return *tempjate;
    else
        throw TemplateNotFoundException(templateName);
}


const Const_Type_SetById& TypeRegister::getTypes() const
{
    return reinterpret_cast<const Const_Type_SetById&>(typesById_);
}


const Const_Class_SetById& TypeRegister::getClasses() const
{
    return reinterpret_cast<const Const_Class_SetById&>(classesById_);
}


const Const_Template_Set& TypeRegister::getTemplates() const
{
    return reinterpret_cast<const Const_Template_Set&>(templates_);
}


void TypeRegister::unregisterType(const std::string& typeName)
{
    Type* type = ptrSet::removeByKey(typesByName_, typeName);
    ptrSet::removeByKey(typesById_, type->getCppType());
    if (!type)
        throw TypeNotFoundException(typeName);
    
    if (type->getCategory() | Type::Class)
    {
        Class* clazz = ptrSet::removeByKey(classesById_, type->getCppType());
    }
    
    delete type;
}


void TypeRegister::unregisterType(const std::type_info& cppType)
{
    Type* type = ptrSet::removeByKey(typesById_, cppType);
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