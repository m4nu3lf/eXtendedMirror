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

const Class Class::Void("void");


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
    Constructor* constructor,
    CopyConstructor* copyConstructor,
    Destructor* destructor,
    AssignOperator* assignOperator,
    const Template& tempjate,
    const std::vector<const Type*>& templateParamTypes
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
    ),
    tempjate_(&tempjate),
    templateArgs_(templateParamTypes)
{
    if (this->tempjate_) category_ = CompoundClass;
    else category_ = Type::Class;
}


const Template& Class::getTemplate() const
{
    return *tempjate_;
}


const std::vector<const Type*>& Class::getTemplateArgs() const
{
    return templateArgs_;
}


const set<const Class*, Class::PtrCmpById>& Class::getBaseClasses() const
{
    return baseClasses_;
}


const set<const Class*, Class::PtrCmpById>& Class::getDerivedClasses() const
{
    return derivedClasses_;
}


Class& Class::operator<<(Class& baseClass)
{
    // put this class into the derived list of the base Class
    baseClass.derivedClasses_.insert(this);
    
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
    const ConstPropertySet* propertySelection;
    if (inherited) propertySelection = &properties_;
    else propertySelection = &ownProperties_;
    
    ConstPropertySet::iterator ite;
    Property property(propertyName);
    ite = propertySelection->find(&property);
    if (ite != propertySelection->end()) return true;
    return false;
}


bool Class::hasMethod(const string& methodName, bool inherited) const
{
    const ConstMethodSet* methodSelection;
    if (inherited) methodSelection = &methods_;
    else methodSelection = &ownMethods_;
    
    ConstMethodSet::iterator ite;
    Method method(methodName);
    ite = methodSelection->find(&method);
    if (ite != methodSelection->end()) return true;
    return false;
}


bool Class::hasMethod(const Method& method, bool inherited) const
{
    const ConstMethodSet* methodSelection;
    if (inherited) methodSelection = &methods_;
    else methodSelection = &ownMethods_;
    
    ConstMethodSet::iterator ite;
    ite = methodSelection->find(&method);
    if (ite != methodSelection->end()) return true;
    return false;
}


bool Class::inheritsFrom(const string& baseClassName) const
{
    const Type& baseClass = TypeRegister::getTypeReg().getType(baseClassName);
    if (baseClass.getCategory() != Type::Class) return false;
    return inheritsFrom(reinterpret_cast<const Class&>(baseClass));
}


bool Class::inheritsFrom(const Class& baseClass) const
{
    set<const Class*>::iterator ite = baseClasses_.find(&baseClass);
    if (ite != baseClasses_.end()) return true;
    return false;
}


const Property& Class::getProperty(const string& propertyName) const
{
    ConstPropertySet::iterator ite;
    Property property(propertyName);
    ite = properties_.find(&property);
    if (ite != properties_.end()) return **ite;
    return *reinterpret_cast<Property*>(NULL);
}


const Method& Class::getMethod(const string& methodName) const
{
    ConstMethodSet::iterator ite;
    Method method(methodName);
    ite = methods_.find(&method);
    if (ite != methods_.end()) return **ite;
    return *reinterpret_cast<Method*>(NULL);
}


const Method& Class::getMethod(const Method& method) const
{
    ConstMethodSet::iterator ite;
    ite = methods_.find(&method);
    if (ite != methods_.end()) return **ite;
    return *reinterpret_cast<Method*>(NULL);
}


Class::~Class()
{
    ConstPropertySet::iterator prop_ite = properties_.begin();
    while(prop_ite != properties_.end())
    {
        delete *prop_ite;
        prop_ite++;
    }
    
    ConstMethodSet::iterator meth_ite = methods_.begin();
    while(meth_ite != methods_.end())
    {
        delete *meth_ite;
        meth_ite++;
    }
}

