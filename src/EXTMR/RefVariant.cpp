#include <EXTMR/Utils/Utils.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;


RefVariant::RefVariant()
{
    
}


RefVariant::RefVariant(const RefVariant& orig)
{
    data_ = orig.data_;
    type_ = orig.type_;
    flags_ = orig.flags_;
}


RefVariant::RefVariant(const Variant& var)
{
    *this = var.getRefVariant();
}


const Variant& RefVariant::operator=(const Variant& var)
{
    *this = var.getRefVariant();
    
    return var;
}
