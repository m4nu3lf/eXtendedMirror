/* 
 * File:   NonAssignableException.cpp
 * Author: manuele
 * 
 * Created on May 1, 2013, 10:12 PM
 */

#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>
#include <EXTMR/Exceptions/NonAssignableException.hpp>

using namespace extmr;


NonAssignableException::NonAssignableException(const Type& type) throw()
        : type_(&type)
{
    
}


const char* NonAssignableException::what() const throw()
{
    return ("Trying call the assign operator between two instance of \""
            + type_->getName() + "\" that is not an assignable type.").c_str();
}


NonAssignableException::~NonAssignableException() throw()
{
    
}

