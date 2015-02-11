/******************************************************************************      
 *      Extended Mirror: Class.cpp                                         *
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

using namespace std;
using namespace xm;


Class::Class(const string& name) :
        Item(name),
        Type(name),
        constructor_(new Constructor(*this)),
        copyConstructor_(new CopyConstructor(*this)),
        destructor_(new Destructor(*this))
{
}


Class::Class
(
    const Namespace& name_space,
    const string& name,
    size_t size,
    const type_info& cppType,
    const Constructor& constructor,
    const CopyConstructor& copyConstructor,
    const Destructor& destructor,
    bool isAbstract
) :
    Item(name_space, name),
    Type(size, cppType),
    constructor_(&constructor),
    copyConstructor_(&copyConstructor),
    destructor_(&destructor),
    isAbstract_(isAbstract)
{
}


bool Class::isAbstract() const
{
    return isAbstract_;
}


const Constructor& Class::getConstructor() const
{
    return *constructor_;
}


const CopyConstructor& Class::getCopyConstructor() const
{
    return *copyConstructor_;
}


const Destructor& Class::getDestructor() const
{
    return *destructor_;
}


const Const_Class_Set& Class::getBaseClasses() const
{
    return baseClasses_;
}


const Const_RefCaster_Set& Class::getRefCasters() const
{
    return refCasters_;
}


const Const_Class_Set& Class::getDerivedClasses() const
{
    return derivedClasses_;
}


void Class::addBaseClass(Class& baseClass)
{    
    // put this class into the derived list of the base Class
    baseClass.derivedClasses_.insert(this);
    
    // put the base class into the base list of this Class
    baseClasses_.insert(&baseClass);
    
    // insert all the base class properties into the properties set
    const Const_Property_Set& baseClassProperties = baseClass.getProperties();
    properties_.insert(baseClassProperties.begin(), baseClassProperties.end());
    
    // insert all the base class method descriptors into the methods set
    const Const_Method_Set& baseClassMethods = baseClass.getMethods();
    methods_.insert(baseClassMethods.begin(), baseClassMethods.end());
}


void Class::addMember(Member& member)
{
    if (&member.getOwner() == this)
    {
        Property* property = dynamic_cast<Property*>(&member);
        if (property)
        {
            properties_.insert(property);
            ownProperties_.insert(property);
            addItem(*property);
            return;
        }
        Method* method = dynamic_cast<Method*>(&member);
        if (method)
        {
            methods_.insert(method);
            ownMethods_.insert(method);
            addItem(*method);
            return;
        }
        RefCaster* refCaster = dynamic_cast<RefCaster*>(&member);
        if (refCaster)
            refCasters_.insert(refCaster);
    }
    else
        XM_DEBUG_MSG("Adding member to wrong owner");
}


const Const_Property_Set& Class::getProperties(bool inherited) const
{
    if (inherited)
    {
        return properties_;
    }
    return ownProperties_;
}


const Const_Method_Set& Class::getMethods(bool inherited) const
{
    if (inherited)
    {
        return methods_;
    }
    return ownMethods_;
}


bool Class::hasProperty(const string& propertyName, bool inherited) const
{
    if (inherited)
        return ptrSet::findByKey(properties_, propertyName);
    else
        return ptrSet::findByKey(ownProperties_, propertyName);
}


bool Class::hasMethod(const string& methodName, bool inherited) const
{
    if (inherited)
        return ptrSet::findByKey(methods_, methodName);
    else
        return ptrSet::findByKey(ownMethods_, methodName);
}


bool Class::hasMethod(const Method& method, bool inherited) const
{
    if (inherited)
        return (methods_.find(&method) != methods_.end());
    else
        return (ownMethods_.find(&method) != ownMethods_.end());
}


bool Class::inheritsFrom(const string& baseClassName) const
{
    const Type& baseClass = getType(baseClassName);
    
    if (baseClass.getCategory() != Type::Class)
        return false;
    else
        return inheritsFrom(dynamic_cast<const Class&>(baseClass));
}


bool Class::inheritsFrom(const Class& baseClass) const
{    
    Const_Class_Set::iterator ite = baseClasses_.begin();
    while(ite != baseClasses_.end())
    {
        if (**ite == baseClass || (*ite)->inheritsFrom(baseClass))
            return true;
        ite++;
    }
    
    return false;
}


const Property& Class::getProperty(const string& propertyName) const
{
    const Property* property = ptrSet::findByKey(properties_, propertyName);
    if (property)
        return *property;
    else
        throw MemberNotFoundException<Property>(propertyName, getName());
}


const Method& Class::getMethod(const string& methodName) const
{
    const Method* method = ptrSet::findByKey(methods_, methodName);
    if (method)
        return *method;
    else
        throw MemberNotFoundException<Property>(methodName, getName());
}


const Method& Class::getMethod(const Method& method) const
{
    Const_Method_Set::iterator ite;
    ite = methods_.find(&method);
    if (ite != methods_.end()) return **ite;
    
    throw MemberNotFoundException<Method>(method.getSignature(), getName(),
            true);
}


Type::Category Class::getCategory() const
{
    return Type::Class;
}


Class::~Class()
{
    ptrSet::deleteAll(ownProperties_);
    ptrSet::deleteAll(ownMethods_);
    
    Const_Class_Set::iterator ite = baseClasses_.begin();
    
    while(ite != baseClasses_.end())
    {
        const_cast<Class*>(*ite)->derivedClasses_.erase(this);
        ite ++;
    }
    
    ite = derivedClasses_.begin();
    
    while(ite != derivedClasses_.end())
    {
        const_cast<Class*>(*ite)->baseClasses_.erase(this);
        ite ++;
    }
}

