#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

Property::Property(const std::string& name) : Member(name), type_(NULL),
        flags_(0)
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


Variant Property::getData(const Variant& objPtr) const
{
    return Variant();
};
