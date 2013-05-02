/* 
 * File:   NonInstantiableException.cpp
 * Author: manuele
 * 
 * Created on May 1, 2013, 10:12 PM
 */

#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>
#include <EXTMR/Exceptions/NonCopyableException.hpp>

using namespace extmr;


NonCopyableException::NonCopyableException(const Type& type) throw()
        : type_(&type)
{
    
}


const char* NonCopyableException::what() const throw()
{
    return ("Trying to copy an instance of \"" + type_->getName() +
            "\" that is not a copyable type").c_str();
}


NonCopyableException::~NonCopyableException() throw()
{
    
}

