#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

TypeRegister& TypeRegister::getTypeReg()
{
    static TypeRegister typeReg(getRegCallBack());
    return typeReg;
}

TypeRegister::TypeRegister(void (*callBackFnc)(const Type&))
{
    this->callBackFnc = callBackFnc;
    
    // register the base types
    registerType<char>();
    registerType<short>();
    registerType<int>();
    registerType<float>();
    registerType<double>();
    registerType<uchar>();
    registerType<ushort>();
    registerType<bool>();
}

const Type& TypeRegister::getType(const string& typeName) const
{
    Type type(typeName);
    set<Type*, Type::PtrCmpByName>::const_iterator ite;
    ite = typesByName.find(&type);
    if (ite == typesByName.end()) return *reinterpret_cast<Type*>(NULL);
    return **ite;
}

const Type& TypeRegister::getType(const type_info& cppType) const
{
    Type type(cppType);
    set<Type*, Type::PtrCmpById>::const_iterator ite;
    ite = typesById.find(&type);
    if (ite == typesById.end()) return *reinterpret_cast<Type*>(NULL);
    return **ite;
}

const Class& TypeRegister::getClass(const string& className) const
{
    Class clazz(className);
    set<Class*, Type::PtrCmpByName>::const_iterator ite;
    ite = classesByName.find(&clazz);
    if (ite == classesByName.end()) return *reinterpret_cast<Class*>(NULL);
    return **ite;
}

const Class& TypeRegister::getClass(const type_info& cppType) const
{
    Class clazz(cppType);
    set<Class*, Type::PtrCmpById>::const_iterator ite;
    ite = classesById.find(&clazz);
    if (ite == classesById.end()) return *reinterpret_cast<Class*>(NULL);
    return **ite;
}

const Template& TypeRegister::getTemplate(const string& templateName) const
{
    Template template_(templateName);
    set<Template*, Template::PtrCmp>::const_iterator ite;
    ite = templates.find(&template_);
    if (ite == templates.end()) return *reinterpret_cast<Template*>(NULL);
    return **ite;
}

const set<const Type*, Type::PtrCmpById>& TypeRegister::getTypes()
{
    return (set<const Type*, Type::PtrCmpById>&) typesById;
}

const set<const Class*, Type::PtrCmpById>& TypeRegister::getClasses()
{
    return (set<const Class*, Type::PtrCmpById>&) classesById;
}

const set<const Template*, Template::PtrCmp>& TypeRegister::getTemplates()
{
    return (set<const Template*, Template::PtrCmp>&)templates;
}