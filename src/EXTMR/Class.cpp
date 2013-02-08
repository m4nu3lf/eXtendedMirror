/* 
 * File:   Class.cpp
 * Author: Manuele Finocchiaro
 * 
 * Created on 29 dicembre 2012, 11.09
 */

#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

Class::Class(const string& name) : Type(name)
{
}

Class::Class(const type_info& type) : Type(type)
{
}

Class::Class
(
        const string& name,
        uint size,
        const type_info& cppType,
        void* (*constructor)(const void*),
        void (*destructor)(void*),
        void (*operatorAssign)(void*, const void*),
        const Template& tempjate,
        const std::vector<const Type*>& templateParamTypes
) :
        Type
        (
                name,
                size,
                cppType,
                constructor,
                destructor,
                operatorAssign
        ),
        tempjate(&tempjate),
        templateParamTypes(templateParamTypes)
{
    if (this->tempjate) category = CompClass;
    else category = Type::Class;
}

const Template& Class::getTemplate() const
{
    return *tempjate;
}

const std::vector<const Type*>& Class::getTemplateParamTypes() const
{
    return templateParamTypes;
}

const set<const Class*, Class::PtrCmpById>& Class::getBaseClasses() const
{
    return baseClasses;
}

const set<const Class*, Class::PtrCmpById>& Class::getDerivedClasses() const
{
    return derivedClasses;
}

Class& Class::operator<<(Class& baseClass)
{
    // put this class into the derived list of the base Class
    baseClass.derivedClasses.insert(this);
    
    // put the base class into the base list of this Class
    baseClasses.insert(&baseClass);
    
    // insert all the base class properties into the properties set
    const std::set<const Property*, Property::PtrCmp>& baseClassProperties = baseClass.getProperties();
    properties.insert(baseClassProperties.begin(), baseClassProperties.end());
    
    // insert all the base class method descriptors into the methods set
    const std::set<const Method*, Method::PtrCmp>& baseClassMethods = baseClass.getMethods();
    methods.insert(baseClassMethods.begin(), baseClassMethods.end());
    
    return *this;
}

Class& Class::operator<<(Property& property)
{
    // remove previous inserted properties with the same name
    properties.erase(&property);
    
    properties.insert(&property);
    return *this;
}

Class& Class::operator<<(Method& method)
{
    // remove previous inserted methods with the same signature
    methods.erase(&method);
    
    methods.insert(&method);
    return *this;
}

const set<const Property*, Property::PtrCmp>& Class::getProperties(bool inherited) const
{
    if (inherited)
    {
        return properties;
    }
    return ownProperties;
}

const set<const Method*, Method::PtrCmp>& Class::getMethods(bool inherited) const
{
    if (inherited)
    {
        return methods;
    }
    return ownMethods;
}

bool Class::hasProperty(const string& propertyName, bool inherited) const
{
    const set<const Property*, Property::PtrCmp>* propertySelection;
    if (inherited) propertySelection = &properties;
    else propertySelection = &ownProperties;
    
    set<const Property*, Property::PtrCmp>::iterator ite;
    Property property(propertyName);
    ite = propertySelection->find(&property);
    if (ite != propertySelection->end()) return true;
    return false;
}

bool Class::hasMethod(const string& methodName, bool inherited) const
{
    const set<const Method*, Method::PtrCmp>* methodSelection;
    if (inherited) methodSelection = &methods;
    else methodSelection = &ownMethods;
    
    set<const Method*, Method::PtrCmp>::iterator ite;
    Method method(methodName);
    ite = methodSelection->find(&method);
    if (ite != methodSelection->end()) return true;
    return false;
}

bool Class::hasMethod(const Method& method, bool inherited) const
{
    const set<const Method*, Method::PtrCmp>* methodSelection;
    if (inherited) methodSelection = &methods;
    else methodSelection = &ownMethods;
    
    set<const Method*, Method::PtrCmp>::iterator ite;
    ite = methodSelection->find(&method);
    if (ite != methodSelection->end()) return true;
    return false;
}

bool Class::derivesFrom(const string& baseClassName) const
{
    const Type& baseClass = TypeRegister::getTypeReg().getType(baseClassName);
    if (baseClass.getCategory() != Type::Class) return false;
    return derivesFrom(reinterpret_cast<const Class&>(baseClass));
}

bool Class::derivesFrom(const Class& baseClass) const
{
    set<const Class*>::iterator ite = baseClasses.find(&baseClass);
    if (ite != baseClasses.end()) return true;
    return false;
}

const Property& Class::getProperty(const string& propertyName) const
{
    set<const Property*, Property::PtrCmp>::iterator ite;
    Property property(propertyName);
    ite = properties.find(&property);
    if (ite != properties.end()) return **ite;
    return *reinterpret_cast<Property*>(NULL);
}

const Method& Class::getMethod(const string& methodName) const
{
    set<const Method*, Method::PtrCmp>::iterator ite;
    Method method(methodName);
    ite = methods.find(&method);
    if (ite != methods.end()) return **ite;
    return *reinterpret_cast<Method*>(NULL);
}

const Method& Class::getMethod(const Method& method) const
{
    set<const Method*, Method::PtrCmp>::iterator ite;
    ite = methods.find(&method);
    if (ite != methods.end()) return **ite;
    return *reinterpret_cast<Method*>(NULL);
}

Class::~Class()
{
    set<const Property*, Property::PtrCmp>::iterator prop_ite = properties.begin();
    while(prop_ite != properties.end())
    {
        delete *prop_ite;
        prop_ite++;
    }
    
    set<const Method*, Method::PtrCmp>::iterator meth_ite = methods.begin();
    while(meth_ite != methods.end())
    {
        delete *meth_ite;
        meth_ite++;
    }
}

