/******************************************************************************      
 *      Extended Mirror: Namespace.cpp                                        *
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


#include <XM/Utils/Utils.hpp>
#include <XM/ExtendedMirror.hpp>
#include <XM/Exceptions/NotFoundExceptions.hpp>

using namespace std;
using namespace xm;

Namespace::Namespace(const std::string& name, const Namespace& parent)
    : name_(name), parent_(&parent)
{
    
}


Namespace::Namespace(const std::string& name = "")
        : name_(name), parent_(NULL)
{
    
}


const std::string& Namespace::getName() const
{
    return name_;
}
    

const std::string& Namespace::getFullName() const
{
    if (parent_)
        return parent_.getFullName() + "::" + name_;
    else
        return name_;
}


const Type& Namespace::getType(const string& typeName) const
{
    Const_Type_Map::iterator ite = types_.find(typeName);
    if (ite == types_.end())
        throw TypeNotFoundException(typeName);
    return *ite;
}


const Class& Namespace::getClass(const string& className) const
{
    Const_Class_Map::iterator ite = classes_.find(className);
    if (ite == types_.end())
        throw TypeNotFoundException(className);
    return *ite;
}


const Template& Namespace::getTemplate(const string& templateName) const
{
    Const_Template_Map::iterator ite = templates_.find(typeName);
    if (ite == templates_.end())
        throw TemplateNotFoundException(templateName);
    return *ite;
}


const Const_Type_Map& Namespace::getTypes() const
{
    return types_;
}


const Const_Class_Map& Namespace::getClasses() const
{
    return classes_;
}


const Const_Template_Map& Namespace::getTemplates() const
{
    return templates_;
}


const Const_Template_Map& Namespace::getFunctions() const
{
    return functions_;
}


const Const_Template_Map& Namespace::getNamespaces() const
{
    return namespaces_;
}


template<class T>
void Namespace::add(const T& obj, const string& name)
{
    if (name == "")
        name = obj->getName();
    
    pair<string, string> split_namespace;
    size_t pos = name.find("::");
    if (pos != string::npos)
    {
        split_namespace.first = name.substr(0, pos);
        split_namespace.second = name.substr(pos + 2);
    }
    if (split_namespace.second != "")
    {
        Namespace* sub_name_space = ptrSet::findByKey(split_namespace.first);
        if (!sub_name_space)
        {
            sub_name_space = new Namespace(split_namespace.first);
            namespaces_.insert(sub_name_space);
        }
        sub_name_space.add<T>(obj, split_namespace.second);
    }
    else
    {
        insert_<T>(obj, name);
    }
}


template<typename T>
void Namespace::insert_(T& obj, const string& name)
{
}


template<>
void Namespace::insert_<Type>(Type& type, const string& name)
{
    types_.insert(name, &type);
    if (type.getCategory() == Type::Class)
        classes_.insert(name, &dynamic_cast<Class&>(type));
}


template<>
void Namespace::insert_<Template>(Template& templ, const string& name)
{
    templates_.insert(name, &templ);
}


template<>
void Namespace::insert_<Function>(Function& func, const string& name)
{
    functions_.insert(name, &func);
}


Namespace::~Namespace()
{

}