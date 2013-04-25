#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

TypeRegister& TypeRegister::getTypeReg()
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
}


const Type& TypeRegister::getType(const string& typeName) const
{
    return *ptrSet::findByKey(typesByName_, typeName);
}


const Type& TypeRegister::getType(const type_info& cppType) const
{
    return *ptrSet::findByKey(typesById_, cppType);
}


const Class& TypeRegister::getClass(const string& className) const
{
    return *ptrSet::findByKey(classesByName_, className);
}


const Class& TypeRegister::getClass(const type_info& cppType) const
{
    return *ptrSet::findByKey(classesById_, cppType);
}


const Template& TypeRegister::getTemplate(const string& templateName) const
{
    return *ptrSet::findByKey(templates_, templateName);
}


const ConstTypeSetById& TypeRegister::getTypes() const
{
    return reinterpret_cast<const ConstTypeSetById&>(typesById_);
}


const ConstClassSetById& TypeRegister::getClasses() const
{
    return reinterpret_cast<const ConstClassSetById&>(classesById_);
}


const ConstTemplateSet& TypeRegister::getTemplates() const
{
    return reinterpret_cast<const ConstTemplateSet&>(templates_);
}