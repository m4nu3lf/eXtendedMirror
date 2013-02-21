#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

Type::Type(const string& name) : 
    name_(name),
    size_(0),
    cppType_(*reinterpret_cast<type_info*>(NULL)),
    constructor_(NULL),
    copyConstructor_(NULL),
    destructor_(NULL),
    operatorAssign_(NULL),
    category_(Primitive)
{
}

Type::Type(const type_info& cppType) :
    name_(""),
    size_(0),
    cppType_(cppType),
    constructor_(NULL),
    copyConstructor_(NULL),
    destructor_(NULL),
    operatorAssign_(NULL),
    category_(Primitive)
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
    name_(name),
    category_(category_),
    size_(size),
    cppType_(cppType),
    constructor_(constructor),
    copyConstructor_(copyConstructor),
    destructor_(destructor),
    operatorAssign_(operatorAssign),
    relatedType_(&relatedType),
    arraySize_(arraySize)
{
    if (this->relatedType_)
    {
        if (isArray)
            category_ = Array;
        else
            category_ = Pointer;
    }
    else category_ = Primitive;
}

void* Type::newInstance(void* address) const
{
    return constructor_(address);
}

void* Type::copyInstance(void* toBeCopiedPtr, void* address) const
{
    return copyConstructor_(toBeCopiedPtr, address);
}

void Type::deleteInstance(void* toBeDeletedPtr, bool deallocate) const
{
    destructor_(toBeDeletedPtr, deallocate);
}

void Type::assignInstance(void* lvaluePtr, const void* rvaluePtr) const
{
    operatorAssign_(lvaluePtr, rvaluePtr);
}

Type::Category Type::getCategory() const
{
    return category_;
}

const string& Type::getName() const
{
    return name_;
}

std::size_t Type::getSize() const
{
    return size_;
}

const type_info& Type::getCpptype() const
{
    return cppType_;
}

const Type& Type::getPointedType() const
{
    if (category_ == Pointer)
        return *relatedType_;
    else return *reinterpret_cast<Type*>(NULL);
}

const Type& Type::getArrayElementType() const
{
    if (category_ == Array)
        return *relatedType_;
    else return *reinterpret_cast<Type*>(NULL);
}

const std::size_t Type::getArraySize() const
{
    return arraySize_;
}

Type::~Type()
{

}
