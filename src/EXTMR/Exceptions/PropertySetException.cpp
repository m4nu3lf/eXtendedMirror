/* 
 * File:   PropertySetException.cpp
 * Author: Manuele Finocchiaro
 * 
 * Created on 15 January 2013, 19.16
 */

#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

PropertySetException::PropertySetException(const Property& property)
        : property_(property)
{
}


const char* PropertySetException::what() const throw()
{
    return (string("Attempt to write the non settable property ")
            + property_.getName()
            + "of class "
            + property_.getOwner().getName() + ".").c_str();
}
