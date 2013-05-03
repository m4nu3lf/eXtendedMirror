/* 
 * File:   Class.cpp
 * Author: Manuele Finocchiaro
 * 
 * Created on 29 dicembre 2012, 11.09
 */

#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>
#include <EXTMR/Exceptions/NotFoundExceptions.hpp>

using namespace std;
using namespace extmr;

const Class Class::Void = TypeRegister::getSingleton().getClass<void>();


Class::Class(const string& name) : Type(name)
{
}


Class::Class(const type_info& type) : Type(type)
{
}


Class::Class
(
    const string& name,
    size_t size,
    const type_info& cppType,
    Constructor* constructor,
    CopyConstructor* copyConstructor,
    Destructor* destructor,
    AssignOperator* assignOperator
) :
    Type
    (
        name,
        size,
        cppType,
        constructor,
        copyConstructor,
        destructor,
        assignOperator
    )
{
}


const ConstClassSetById& Class::getBaseClasses() const
{
    return baseClasses_;
}


const ConstClassSetById& Class::getDerivedClasses() const
{
    return derivedClasses_;
}


Class& Class::operator<<(const Class& baseClass)
{    
    // put this class into the derived list of the base Class
    const_cast<Class&>(baseClass).derivedClasses_.insert(this);
    
    // put the base class into the base list of this Class
    baseClasses_.insert(&baseClass);
    
    // insert all the base class properties into the properties set
    const ConstPropertySet& baseClassProperties = baseClass.getProperties();
    properties_.insert(baseClassProperties.begin(), baseClassProperties.end());
    
    // insert all the base class method descriptors into the methods set
    const ConstMethodSet& baseClassMethods = baseClass.getMethods();
    methods_.insert(baseClassMethods.begin(), baseClassMethods.end());
    
    return *this;
}


Class& Class::operator<<(Property& property)
{
    // remove previous inserted properties with the same name
    properties_.erase(&property);
    
    property.setOwner(*this);
    
    properties_.insert(&property);
    return *this;
}


Class& Class::operator<<(Method& method)
{
    // remove previous inserted methods with the same signature
    methods_.erase(&method);
    
    methods_.insert(&method);
    return *this;
}


const ConstPropertySet& Class::getProperties(bool inherited) const
{
    if (inherited)
    {
        return properties_;
    }
    return ownProperties_;
}


const ConstMethodSet& Class::getMethods(bool inherited) const
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
    const Type& baseClass = TypeRegister::getSingleton().getType(baseClassName);
    
    if (baseClass.getCategory() != Type::Class)
        return false;
    else
        return inheritsFrom(reinterpret_cast<const Class&>(baseClass));
}


bool Class::inheritsFrom(const Class& baseClass) const
{    
    ConstClassSetById::iterator ite = baseClasses_.begin();
    while(ite != baseClasses_.end())
    {
        if (**ite == *this || (*ite)->inheritsFrom(*this))
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
        throw PropertyNotFoundException(propertyName, name_);
}


const Method& Class::getMethod(const string& methodName) const
{
    const Method* method = ptrSet::findByKey(methods_, methodName);
    if (method)
        return *method;
    else
        throw MethodNotFoundException(*method, name_);
}


const Method& Class::getMethod(const Method& method) const
{
    ConstMethodSet::iterator ite;
    ite = methods_.find(&method);
    if (ite != methods_.end()) return **ite;
    
    throw MethodNotFoundException(method, name_);
}


Class::~Class()
{
    ptrSet::deleteAll(ownProperties_);
    ptrSet::deleteAll(ownMethods_);
    
    ConstClassSetById::iterator ite = baseClasses_.begin();
    
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

