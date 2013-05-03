#include <Common/Common.hpp>
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