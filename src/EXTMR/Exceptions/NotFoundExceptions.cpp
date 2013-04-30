/* 
 * File:   NotFoundException.cpp
 * Author: manuele
 * 
 * Created on April 30, 2013, 4:14 PM
 */

#include <Common/Common.hpp>
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


ClassNotFoundException::ClassNotFoundException(const string& name) throw()
        : name_(name)
{
    
}


const char* ClassNotFoundException::what() const throw()
{
    string s = "Class \"" + name_ + "\" is not registered.";
    return s.c_str();
}


ClassNotFoundException::~ClassNotFoundException() throw()
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
        
        ConstPrameterVector params = method_->getParameters();            
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
