/******************************************************************************
 *      Extended Mirror: Namespace.cpp                                        *
 ******************************************************************************
 *      Copyright (c) 2012-2015, Manuele Finocchiaro                          *
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
#include <XM/xMirror.hpp>
#include <XM/Exceptions/NotFoundException.hpp>
#include <XM/Utils/Names.hpp>

using namespace std;
using namespace xm;

Namespace::Namespace(const std::string& name, const Namespace& name_space)
    : Item(name, name_space)
{
    
}


Namespace::Namespace(const std::string& name)
    : Item(name)
{

}


template<typename T>
T& Namespace::getItem_(const string& name)
{
    pair<string, string> nameParts = splitName(name, NameTail);
    return getItem_(nameParts.first, T(nameParts.second, *this));
}


namespace xm {

template<>
Property& Namespace::getItem_<Property>(const string& name)
{
    pair<string, string> nameParts = splitName(name, NameTail);
    const Class* clazz = dynamic_cast<Class*>(this);
    return getItem_(nameParts.first, Property(nameParts.second, *clazz));
}


template<>
Method& Namespace::getItem_<Method>(const string& name)
{
    pair<string, string> nameParts = splitName(name, NameTail);
    const Class* clazz = dynamic_cast<Class*>(this);
    return getItem_(nameParts.first, Method(nameParts.second, *clazz));
}

}


template<typename T>
T& Namespace::getItem_(const T& keyItem)
{
    return getItem_("", keyItem);
}


template<typename T>
T& Namespace::getItem_(const string& path, const T& keyItem)
{
    if (path != "")
    {
        Namespace& ns = walkTo(path);
        return ns.getItem_("", keyItem);
    }


    const Item* keyItemPtr = dynamic_cast<const Item*>(&keyItem);
    Const_Item_Set::iterator ite = items_.find(keyItemPtr);
    if (ite != items_.end())
    {
        const T* found = dynamic_cast<const T*>(*ite);
        return *const_cast<T*>(found);
    }

    throw NotFoundException(*this, keyItem);
}

#include <iostream>
Namespace& Namespace::walkTo(const string& path, bool create)
{
    size_t sepPos = path.find("::");
    pair<string, string> pathParts;
    if (sepPos == 0)
    {
        string relativePath = path.substr(2, path.length());
        return Register::getSingleton().walkTo(relativePath, create);
    }
    else if (path == "")
        return *this;
    else if (sepPos != string::npos)
        pathParts = splitName(path, NameHead);
    else
        pathParts = make_pair<string, string>(path.c_str(), "");

    try {
        Namespace& ns = getItem_<Namespace>(pathParts.first);
        return ns.walkTo(pathParts.second, create);
    } catch (NotFoundException& e) {
        if (create)
        {
            Namespace* ns = new Namespace(pathParts.first, *this);
            items_.insert(ns);
            return ns->walkTo(pathParts.second, create);
        }
        else
        {
            cout << "here" << endl;
            throw e;
        }
    }
}


template<typename T>
const T& Namespace::getItem(const string& name) const
{
    return const_cast<Namespace*>(this)->getItem_<T>(name);
}


template<typename T>
const T& Namespace::getItem(const T& keyItem) const
{
    return const_cast<Namespace*>(this)->getItem_<T>(keyItem);
}


template<typename T>
const T& Namespace::getItem(const string& path, const T& keyItem) const
{
    return const_cast<Namespace*>(this)->getItem_(path, keyItem);
}


template const Item& Namespace::getItem(const std::string& name) const;
template const Namespace& Namespace::getItem(const std::string& name) const;
template const Type& Namespace::getItem(const std::string& name) const;
template const Class& Namespace::getItem(const std::string& name) const;
template const Template& Namespace::getItem(const std::string& name) const;
template const Function& Namespace::getItem(const std::string& name) const;
template const Property& Namespace::getItem(const std::string& name) const;
template const Method& Namespace::getItem(const std::string& name) const;
template const Method& Namespace::getItem(const Method& method) const;


bool Namespace::addNamespace_(Namespace& where, const string& what)
{
    Namespace* name_space = new Namespace(what, where);
    where.addItem(*name_space);
    return true;
}


Namespace& Namespace::defineNamespace(const std::string& path)
{
    return walkTo(path, true);
}


void Namespace::addItem(Item& item)
{
    items_.insert(&item);
    if (item.getNamespace() == *this)
        ownItems_.insert(&item);
}


Namespace::~Namespace()
{
    Const_Item_Set::iterator ite = ownItems_.begin();
    while(ite != ownItems_.end())
    {
        delete *ite;
        ite ++;
    }
}
