/* 
 * File:   BadType.cpp
 * Author: Manuele Finocchiaro
 * 
 * Created on 3 September 2012, 12.50
 */
#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

BadType::BadType(const Type& givenType, const Type& expectedType) throw()
        : givenType(&givenType), expectedType(&expectedType)
{
}

const char* BadType::what() const throw()
{
    return (string("Given data of type \"")
            + givenType->getName()
            + "\" when expected data of type \""
            + expectedType->getName()
            + "\".\n").c_str();
}

