/* 
 * File:   NonInstantiableException.cpp
 * Author: manuele
 * 
 * Created on May 1, 2013, 10:12 PM
 */

#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>
#include <EXTMR/Exceptions/NonInstantiableException.hpp>

using namespace extmr;


NonInstantiableException::NonInstantiableException(const Type& type) throw()
        : type_(&type)
{
    
}


const char* NonInstantiableException::what() const throw()
{
    return ("Trying to instantiate \"" + type_->getName() +
            "\" that is not an instantiable type").c_str();
}


NonInstantiableException::~NonInstantiableException() throw()
{
    
}

