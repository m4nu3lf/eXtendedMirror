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


#include <EXTMR/ExtendedMirror.hpp>
#include <EXTMR/Exceptions/NotFoundExceptions.hpp>

using namespace std;
using namespace extmr;

TypeNotFoundException::TypeNotFoundException(const string& name) throw()
        : name_(name)
{
    
}


const char* TypeNotFoundException::what() const throw()
{
    string s = "Type \"" + name_ + "\" is not registered.";
    return s.c_str();
}


TypeNotFoundException::~TypeNotFoundException() throw()
{
    
}


TemplateNotFoundException::TemplateNotFoundException(const string& name) throw()
                : name_(name)
{
    
}


const char* TemplateNotFoundException::what() const throw()
{
    string s = "Template \"" + name_ + "\" is not registered.";
    return s.c_str();
}


TemplateNotFoundException::~TemplateNotFoundException() throw()
{
    
}


PropertyNotFoundException::PropertyNotFoundException(const string& propertyName,
        const string& className) throw()
        : propertyName_(propertyName), className_(className)
{

}

const char* PropertyNotFoundException::what() const throw()
{
    string s = "Class \"" + className_ + "\" has no property named \"" +
            propertyName_ + "\".";
    return s.c_str();
}


PropertyNotFoundException::~PropertyNotFoundException() throw()
{
    
}


MethodNotFoundException::MethodNotFoundException(const string& methodName,
                                                const string& className) throw()
        : method_(new Method(methodName)), className_(className),
        deleteMethod_(true)
{
    
}


MethodNotFoundException::MethodNotFoundException(const Method& method,
                                                const string& className) throw()
        : method_(&method), className_(className), deleteMethod_(false)
{
    
}


const char* MethodNotFoundException::what() const throw()
{
    string s;
    
    if (method_->fullSignature_)
    {
        string signature;
        
        switch (method_->getReturnMode())
        {
        case Method::Value:
                signature += method_->getReturnType().getName() + " ";
                break;
                
        case Method::Reference:
                signature += method_->getReturnType().getName() + "& ";
                break;
                
        case Method::ConstReference:
                signature += "const " + method_->getReturnType().getName()
                        + " ";
                break;
        }
        
        signature += method_->getName() + "(";
        
        Const_Prameter_Vector params = method_->getParameters();            
        for (uint i = 0; i < params.size(); i++)
        {
            const Parameter* param = params[i];
            signature += param->type.getName();
            if (param->byNcReference)
                signature += "&";
            if (i != params.size() - 1)
                signature += ", ";
        }
        
        signature += ") ";
        
        if (method_->isConst())
            signature += "const";

        s = "Class \"" + className_ + "\" has no method with signature \"" +
                signature + "\".";
    }
    else
        s = "Class \"" + className_ + "\" has no method named \"" +
                method_->getName() + "\".";
    
    return s.c_str();
}


MethodNotFoundException::~MethodNotFoundException() throw()
{
    if (deleteMethod_)
        delete method_;
}
