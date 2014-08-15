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
#include <XM/Utils/String.hpp>

using namespace std;
using namespace xm;

Namespace::Namespace(const std::string& name, const Namespace& name_space)
    : Item(name_space, name)
{
    
}


Namespace::Namespace()
{
}


Item& Namespace::getItem_(const std::string& name,
                          NotFoundHandler notFoundHandler)
{
    pair<string, string> nameParts = splitName(name, NameHead);
    do {
        if (nameParts.first != "")
        {
            Item* item = ptrSet::findByKey(items_, nameParts.first);
            if (item)
            {
                Namespace& name_space = dynamic_cast<Namespace&>(*item);
                return name_space.getItem_(nameParts.second, notFoundHandler);
            }
            else if (notFoundHandler)
                notFoundHandler(*this, nameParts.first);
            else break;
        }
        else
        {
            Item* item = ptrSet::findByKey(items_, name);
            if (item)
                return *item;
            else if (notFoundHandler)
                notFoundHandler(*this, name);
            else break;
        }
    } while (true);
    throw ItemNotFoundException<Item>(getName() + "::" + name);
}


template<typename T>
bool throwNotFoundException(Namespace& where, const string& what)
{
    throw ItemNotFoundException<T>(where.getName() + "::" + what);
}


template<typename T>
const T& Namespace::getItem(const string& name) const
{
    // Const cast can be performed because getItem does not modify anything
    // in this case
    Namespace* ncThis = const_cast<Namespace*>(this);
    Item& item = ncThis->getItem_(name, throwNotFoundException<T>);
    return dynamic_cast<T&>(item);
}
template const Item& Namespace::getItem(const std::string& name) const;
template const Type& Namespace::getItem(const std::string& name) const;
template const Class& Namespace::getItem(const std::string& name) const;
template const Template& Namespace::getItem(const std::string& name) const;
template const Function& Namespace::getItem(const std::string& name) const;


bool Namespace::addNamespace_(Namespace& where, const string& what)
{
    Namespace* name_space = new Namespace(what, where);
    where.addItem(*name_space);
    return true;
}


Namespace& Namespace::defineNamespace(const std::string& name)
{
    if (name == "")
        return Register::getSingleton();
    Item& item = getItem_(name, addNamespace_);
    return dynamic_cast<Namespace&>(item);
}


void Namespace::addItem(Item& item)
{
    if (item.getNamespace() == *this)
        items_.insert(&item);
}


Namespace::~Namespace()
{
    Item_Set::iterator ite = items_.begin();
    while(ite != items_.end())
    {
        delete *ite;
        ite ++;
    }
}