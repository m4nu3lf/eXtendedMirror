#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>
#include <EXTMR/Exceptions/NonInstantiableException.hpp>
#include <EXTMR/Exceptions/NonCopyableException.hpp>
#include <EXTMR/Exceptions/NonAssignableException.hpp>
#include <EXTMR/Exceptions/NonDestructibleException.hpp>

using namespace std;
using namespace extmr;

const Type Type::Void = TypeRegister::getSingleton().getType<void>();

Type::Type(const string& name) : 
    name_(name),
    size_(0),
    cppType_(typeid(void)),
    constructor_(NULL),
    copyConstructor_(NULL),
    destructor_(NULL),
    assignOperator_(NULL)
{
}


Type::Type(const type_info& cppType) :
    name_(""),
    size_(0),
    cppType_(cppType),
    constructor_(NULL),
    copyConstructor_(NULL),
    destructor_(NULL),
    assignOperator_(NULL)
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
    AssignOperator* assignOperator
) :
    name_(name),
    size_(size),
    cppType_(cppType),
    constructor_(constructor),
    copyConstructor_(copyConstructor),
    destructor_(destructor),
    assignOperator_(assignOperator)
{
}


bool Type::isInstatiable()
{
    return constructor_ != NULL;
}


bool Type::isCopyable()
{
    return copyConstructor_ != NULL;
}


bool Type::isAssignable()
{
    return assignOperator_ != NULL;
}


bool Type::isDestructible()
{
    return destructor_ != NULL;
}


void* Type::newInstance(void* address) const
{
    if (constructor_)
        return (*constructor_)(address);
    else
        throw NonInstantiableException(*this);
}


void* Type::copyInstance(void* toBeCopiedPtr, void* address) const
{
    if (copyConstructor_)
        return (*copyConstructor_)(toBeCopiedPtr, address);
    else
        throw NonCopyableException(*this);
}


void Type::deleteInstance(void* toBeDeletedPtr, bool deallocate) const
{
    if (destructor_)
        (*destructor_)(toBeDeletedPtr, deallocate);
    else
        throw NonDestructibleException(*this);
}


void Type::assignInstance(void* lvaluePtr, const void* rvaluePtr) const
{
    if (assignOperator_)
        (*assignOperator_)(lvaluePtr, rvaluePtr);
    else
        throw NonAssignableException(*this);
}


Type::Category Type::getCategory() const
{
    return static_cast<Type::Category>(0);
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


Type::~Type()
{

}
