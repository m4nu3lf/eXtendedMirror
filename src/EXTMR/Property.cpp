#include <EXTMR/Utils/Utils.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

Property::Property(const std::string& name) :
        Member(getClass<void>(), name), type_(NULL), flags_(0)
{
}


Property::Property(const Class& owner, const std::string& name = "") :
        Member(owner, name), type_(NULL), flags_(0)
{
}


const Type& Property::getType() const
{
    return *type_;
}


char Property::getFlags() const
{
    return 0;
}


Property& Property::setFlags(char flags)
{
    return *this;
}


double Property::getMinValue() const
{
    return numeric_limits<double>::min();
}


Property& Property::setMinValue(double minValue)
{
    return *this;
}


double Property::getMaxValue() const
{
    return numeric_limits<double>::max();
}


Property& Property::setMaxValue(double maxValue)
{
    return *this;
}


Property::GetMode Property::getGetMode()
{
    return None;
}


Property::SetMode Property::getSetMode()
{
    return None;
}


const Variant& Property::getData(const RefVariant& self) const
{
    return Variant::Null;
};


void Property::setData(const RefVariant& self, const Variant& data) const
{};
