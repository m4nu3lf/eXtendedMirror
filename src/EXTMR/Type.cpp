#include <EXTMR/Utils/Utils.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

Type::Type(const string& name) : name_(name), size_(0), cppType_(typeid(void))
{
}


Type::Type(const type_info& cppType) : name_(""), size_(0), cppType_(cppType)
{
}


Type::Type(const string& name, size_t size, const type_info& cppType)
        : name_(name), size_(size), cppType_(cppType)
{
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
