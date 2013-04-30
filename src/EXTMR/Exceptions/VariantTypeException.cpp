/* 
 * File:   VariantTypeException.cpp
 * Author: Manuele Finocchiaro
 * 
 * Created on 3 September 2012, 12.50
 */
#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

VariantTypeException::VariantTypeException
        (
            const Type& givenType, 
            const Type& expectedType
        ) throw()
        : givenType_(&givenType)
        , variantType_(&expectedType)
{
}


const char* VariantTypeException::what() const throw()
{
    return (string("Cannot convert variant of type \"")
            + variantType_->getName()
            + "\" to type \""
            + givenType_->getName()
            + "\".\n").c_str();
}

