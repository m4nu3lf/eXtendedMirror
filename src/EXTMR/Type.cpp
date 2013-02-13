#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

Type::Type(const string& name) : 
    name(name),
    size(0),
    cppType(*reinterpret_cast<type_info*>(NULL)),
    constructor(NULL),
    copyConstructor(NULL),
    destructor(NULL),
    operatorAssign(NULL),
    category(Primitive)
{
}

Type::Type(const type_info& cppType) :
    name(""),
    size(0),
    cppType(cppType),
    constructor(NULL),
    copyConstructor(NULL),
    destructor(NULL),
    operatorAssign(NULL),
    category(Primitive)
{
}

Type::Type
(
    const string& name,
    size_t size,
    const type_info& cppType,
    void* (*constructor)(void*),
    void* (*copyConstructor)(const void*, void*),
    void (*destructor)(void*, bool),
    void (*operatorAssign)(void*, const void*),
    const Type& relatedType,
    bool isArray,
    size_t arraySize
) :
    name(name),
    category(category),
    size(size),
    cppType(cppType),
    constructor(constructor),
    copyConstructor(copyConstructor),
    destructor(destructor),
    operatorAssign(operatorAssign),
    relatedType(&relatedType),
    arraySize(arraySize)
{
    if (this->relatedType)
    {
        if (isArray)
            category = Array;
        else
            category = Pointer;
    }
    else category = Primitive;
}

void* Type::newInstance(void* address) const
{
    return constructor(address);
}

void* Type::copyInstance(void* toBeCopiedPtr, void* address) const
{
    return copyConstructor(toBeCopiedPtr, address);
}

void Type::deleteInstance(void* toBeDeletedPtr, bool deallocate) const
{
    destructor(toBeDeletedPtr, deallocate);
}

void Type::assignInstance(void* lvaluePtr, const void* rvaluePtr) const
{
    operatorAssign(lvaluePtr, rvaluePtr);
}

Type::Category Type::getCategory() const
{
    return category;
}

const string& Type::getName() const
{
    return name;
}

std::size_t Type::getSize() const
{
    return size;
}

const type_info& Type::getCpptype() const
{
    return cppType;
}

const Type& Type::getPointedType() const
{
    if (category == Pointer)
        return *relatedType;
    else return *reinterpret_cast<Type*>(NULL);
}

const Type& Type::getArrayElementType() const
{
    if (category == Array)
        return *relatedType;
    else return *reinterpret_cast<Type*>(NULL);
}

const std::size_t Type::getArraySize() const
{
    return arraySize;
}

Type::~Type()
{

}
