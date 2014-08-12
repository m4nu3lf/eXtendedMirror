/******************************************************************************      
 *      Extended Mirror: NotFoundExceptions.cpp                               *
 ******************************************************************************
 *      Copyright (c) 2012-2014, Manuele Finocchiaro                          *
 *      All rights reserved.                                                  *
 ******************************************************************************
 * Redistribution and use in source and binary forms, with or without         *
 * modification, are permitted provided that the following conditions         *
 * are met:                                                                   *
 *                                                                            *
 *    1. Redistributions of source code must retain the above copyright       *
 *       notice, this list of conditions and the following disclaimer.        *
 *                                                                            *
 *    2. Redistributions in binary form must reproduce the above copyright    *
 *       notice, this list of conditions and the following disclaimer in      *
 *       the documentation and/or other materials provided with the           *
 *       distribution.                                                        *
 *                                                                            *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"* 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE  *
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE *
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE  *
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR        *
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF       *
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   *
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN    *
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)    *
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF     *
 * THE POSSIBILITY OF SUCH DAMAGE.                                            *
 *****************************************************************************/


#include <XM/ExtendedMirror.hpp>
#include <XM/Exceptions/NotFoundExceptions.hpp>

using namespace std;
using namespace xm;


NotFoundException::NotFoundException(const string& name)
    : name_(name)
{
}


#define _XM_DEFINE_NOT_FOUND_EXCEPTION(_type_)                                 \
                                                                               \
_type_##NotFoundException::##_type_##NotFoundException(                        \
    const string& name) throw()                                                \
    : NotFoundException(name)                                                  \
{}                                                                             \
                                                                               \
const char* _type_##NotFoundException::what() const throw()                    \
{                                                                              \
    "There is no registered #_type with name " + name_;                        \
}

_XM_DEFINE_NOT_FOUND_EXCEPTION(Namespace)
_XM_DEFINE_NOT_FOUND_EXCEPTION(Type)
_XM_DEFINE_NOT_FOUND_EXCEPTION(Class)
_XM_DEFINE_NOT_FOUND_EXCEPTION(Template)
_XM_DEFINE_NOT_FOUND_EXCEPTION(Propertyn)



MethodNotFoundException::MethodNotFoundException(const string& name,
        bool fullSignature)
    : NotFoundException(name), fullSignature_(fullSiganture)
{
}

const char* MethodNotFoundException::what() const throw()
{
    if (fullSignature_)
    {
        "There is no registered method with signature " + name_;
    }
    else
    {
        "There is no registered method with name " + name_;
    }
    
    

        s = "Class \"" + className_ + "\" has no method with signature \"" +
                signature + "\".";
    }
    else
        s = "Class \"" + className_ + "\" has no method named \"" +
                method_->getName() + "\".";
    
    return s.c_str();
}
