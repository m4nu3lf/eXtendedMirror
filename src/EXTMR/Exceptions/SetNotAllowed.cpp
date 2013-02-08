/* 
 * File:   SetNotAllowed.cpp
 * Author: Manuele Finocchiaro
 * 
 * Created on 15 January 2013, 19.16
 */

#include <string>

#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

SetNotAllowed::SetNotAllowed(const Property& property)
        : propertyDescPtr(&property)
{
}

const char* SetNotAllowed::what() const throw()
{
    return (string("Attempt to write the non settable property ")
            + propertyDescPtr->getName()
            + "of class "
            + propertyDescPtr->getType().getName() + ".").c_str();
}
