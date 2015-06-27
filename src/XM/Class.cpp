/******************************************************************************      
 *      Extended Mirror: Class.cpp                                            *
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


#include <XM/Utils/Utils.hpp>
#include <XM/xMirror.hpp>
#include <XM/Exceptions/NotFoundException.hpp>

using namespace std;
using namespace xm;


Class::Class(const string& uName) :
        Item(uName),
        Type(uName),
        constructor_(new Constructor(*this)),
        copyConstructor_(new CopyConstructor(*this)),
        destructor_(new Destructor(*this))
{
}


Class::Class(const string& uName, const Namespace& name_space) :
        Item(uName, name_space),
        Type(uName, name_space),
        constructor_(new Constructor(*this)),
        copyConstructor_(new CopyConstructor(*this)),
        destructor_(new Destructor(*this))
{
}


Class::Class
(
    const Namespace& name_space,
    const string& uName,
    size_t size,
    const type_info& cppType,
    const Constructor& constructor,
    const CopyConstructor& copyConstructor,
    const Destructor& destructor,
    bool isAbstract
) :
    Item(uName, name_space),
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


const Const_Class_Set& Class::getBaseClasses(bool indirect) const
{
    if (indirect)
        return indirectBaseClasses_;
    else
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
    indirectBaseClasses_.insert(&baseClass);

    // add indirect base classes of the base as undirect base classes
    indirectBaseClasses_.insert(baseClass.indirectBaseClasses_.begin(),
                                baseClass.indirectBaseClasses_.end());
    
    // insert all the base class properties into the properties set
    const Const_Property_Set& baseClassProperties = baseClass.getProperties();
    properties_.insert(baseClassProperties.begin(), baseClassProperties.end());
    items_.insert(baseClassProperties.begin(), baseClassProperties.end());
    
    // insert all the base class method descriptors into the methods set
    const Const_Method_Set& baseClassMethods = baseClass.getMethods();
    methods_.insert(baseClassMethods.begin(), baseClassMethods.end());
    items_.insert(baseClassMethods.begin(), baseClassMethods.end());
}


void Class::addMember(Member& member)
{
    if (&member.getOwner() == this)
    {
        Property* property = dynamic_cast<Property*>(&member);
        if (property)
        {
            properties_.erase(property);
            properties_.insert(property);
            ownProperties_.insert(property);
            addItem(*property);
            return;
        }
        Method* method = dynamic_cast<Method*>(&member);
        if (method)
        {
            methods_.erase(method);
            methods_.insert(method);
            ownMethods_.insert(method);
            addItem(*method);
            return;
        }
        RefCaster* refCaster = dynamic_cast<RefCaster*>(&member);
        if (refCaster)
        {
            refCasters_.insert(refCaster);
            return;
        }
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
    Const_Class_Set::iterator ite;
    ite = indirectBaseClasses_.find(&baseClass);
    if (ite == indirectBaseClasses_.end())
        return false;
    else
        return true;
}


const Property& Class::getProperty(const string& propertyName) const
{
    return getItem<Property>(propertyName);
}


const Method& Class::getMethod(const string& methodName) const
{
    return getItem<Method>(methodName);
}


const Method& Class::getMethod(const Method& method) const
{
    return getItem<Method>(method);
}


Type::Category Class::getCategory() const
{
    return Type::Class;
}


Namespace& Class::walkTo(const std::string& path, bool create)
{
    pair<string, string> pathParts = splitName(path, NameHead);
    if (pathParts.first == "")
    {
        string name = Item::getNamespace().getName() + "::" + pathParts.second;
        const Class* found = ptrSet::findByKey(indirectBaseClasses_, name);
        if (found)
            return const_cast<Class&>(*found);
        else
            return Namespace::walkTo(path, create);
    }
    else
    {
        string name = Item::getNamespace().getName() + "::" + pathParts.first;
        const Class* found = ptrSet::findByKey(baseClasses_, name);
        if (found)
            return const_cast<Class&>(*found).walkTo(pathParts.second, create);
        else
            return Namespace::walkTo(path, create);
    }
}


Item::Category Class::getItemCategory() const
{
    return TypeItem;
}


Class::~Class()
{
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

    delete constructor_;
    delete copyConstructor_;
    delete destructor_;
    ptrSet::deleteAll(refCasters_);
}

