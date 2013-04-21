#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

const Type Type::Void("void");

Type::Type(const string& name) : 
    name_(name),
    size_(0),
    cppType_(typeid(void)),
    constructor_(NULL),
    copyConstructor_(NULL),
    destructor_(NULL),
    assignOperator_(NULL),
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
    assignOperator_(NULL),
    category_(Primitive)
{
}


Type::Type
(
    const string& name,
    size_t size,
    const type_info& cppType,
    Constructor* constructor,
    CopyConstructor* copyConstructor,
    Destructor* destructor,
    AssignOperator* assignOperator,
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
    assignOperator_(assignOperator),
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


bool Type::isInstatiable()
{
    return constructor_ != NULL;
}


bool Type::isCopyable()
{
    return copyConstructor_ != NULL;
}


bool Type::isLvalue()
{
    return assignOperator_ != NULL;
}


void* Type::newInstance(void* address) const
{
    if (constructor_)
        return (*constructor_)(address);
    else
        return NULL;
}


void* Type::copyInstance(void* toBeCopiedPtr, void* address) const
{
    if (copyConstructor_)
        return (*copyConstructor_)(toBeCopiedPtr, address);
    else
        return NULL;
}


void Type::deleteInstance(void* toBeDeletedPtr, bool deallocate) const
{
    if (destructor_)
        (*destructor_)(toBeDeletedPtr, deallocate);
}


void Type::assignInstance(void* lvaluePtr, const void* rvaluePtr) const
{
    if (assignOperator_)
        (*assignOperator_)(lvaluePtr, rvaluePtr);
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


const type_info& Type::getCppType() const
{
    return cppType_;
}


const Type& Type::getPointedType() const
{
    if (category_ == Pointer)
        return *relatedType_;
    else
        return Type::Void;
}


const Type& Type::getArrayElementType() const
{
    if (category_ == Array)
        return *relatedType_;
    else
        return Type::Void;
}


const std::size_t Type::getArraySize() const
{
    return arraySize_;
}


Type::~Type()
{

}
