#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

Property::Property(const std::string& name)
{
    this->name = name;
    this->type = NULL;
}

const string& Property::getName() const
{
    return name;
}

const Type& Property::getType() const
{
    return *type;
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

bool Property::getGetByNcRef()
{
    return false;
}

bool Property::getSetByNcRef()
{
    return false;
}

Variant Property::getData(const Variant& objPtr) const
{
    return Variant();
};
