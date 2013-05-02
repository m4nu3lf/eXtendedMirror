/* 
 * File:   NonDestructibleException.cpp
 * Author: manuele
 * 
 * Created on May 1, 2013, 10:12 PM
 */

#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>
#include <EXTMR/Exceptions/NonDestructibleException.hpp>

using namespace extmr;


NonDestructibleException::NonDestructibleException(const Type& type) throw()
        : type_(&type)
{
    
}


const char* NonDestructibleException::what() const throw()
{
    return ("Trying to destroy an instance of \"" + type_->getName() 
            + "\" that is not a destuctible type").c_str();
}


NonDestructibleException::~NonDestructibleException() throw()
{
    
}

