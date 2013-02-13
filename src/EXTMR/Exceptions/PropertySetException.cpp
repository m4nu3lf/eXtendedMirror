/* 
 * File:   PropertySetException.cpp
 * Author: Manuele Finocchiaro
 * 
 * Created on 15 January 2013, 19.16
 */

#include <string>

#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

PropertySetException::PropertySetException(const Property& property,
                                           const Class& ownerClass)
        : property(property)
        , ownerClass(ownerClass)
{
}

const char* PropertySetException::what() const throw()
{
    return (string("Attempt to write the non settable property ")
            + property.getName()
            + "of class "
            + ownerClass.getName() + ".").c_str();
}
