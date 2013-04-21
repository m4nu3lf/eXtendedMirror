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
    this->callBackFnc_ = callBackFnc;
    
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
    TypeSetByName::const_iterator ite;
    ite = typesByName_.find(&type);
    if (ite == typesByName_.end()) return *reinterpret_cast<Type*>(NULL);
    return **ite;
}


const Type& TypeRegister::getType(const type_info& cppType) const
{
    Type type(cppType);
    TypeSetById::const_iterator ite;
    ite = typesById_.find(&type);
    if (ite == typesById_.end()) return *reinterpret_cast<Type*>(NULL);
    return **ite;
}


const Class& TypeRegister::getClass(const string& className) const
{
    Class clazz(className);
    set<Class*, Type::PtrCmpByName>::const_iterator ite;
    ite = classesByName_.find(&clazz);
    if (ite == classesByName_.end()) return *reinterpret_cast<Class*>(NULL);
    return **ite;
}


const Class& TypeRegister::getClass(const type_info& cppType) const
{
    Class clazz(cppType);
    ClassSetById::const_iterator ite;
    ite = classesById_.find(&clazz);
    if (ite == classesById_.end()) return *reinterpret_cast<Class*>(NULL);
    return **ite;
}


const Template& TypeRegister::getTemplate(const string& templateName) const
{
    Template template_(templateName);
    set<Template*, Template::PtrCmp>::const_iterator ite;
    ite = templates_.find(&template_);
    if (ite == templates_.end()) return *reinterpret_cast<Template*>(NULL);
    return **ite;
}


const ConstTypeSetById& TypeRegister::getTypes()
{
    return (ConstTypeSetById&) typesById_;
}


const ConstClassSetById& TypeRegister::getClasses()
{
    return (ConstClassSetById&) classesById_;
}


const set<const Template*, Template::PtrCmp>& TypeRegister::getTemplates()
{
    return (set<const Template*, Template::PtrCmp>&)templates_;
}