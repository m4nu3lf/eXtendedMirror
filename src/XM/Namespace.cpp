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

Namespace::Namespace(const std::string& name, const Namespace& name_space)
    : Item(name_space, name)
{
    
}


Namespace::Namespace()
        : Item("")
{
}


template<typename T>
const T& Namespace::getItem(const string& name) const
{
    pair<string, string> splitName = splitTopNamespace_(name);
    if (splitName.first != "")
    {
        const Item* item = ptrSet::findByKey(items_, splitName.first);
        const Namespace* name_space = dynamic_cast<const Namespace*>(item);
        if (name_space)
            return name_space->getItem<T>(splitName.second);
        else
            throw ItemNotFoundException<T>(getName() + "::" + name);
    }
    else
    {
        const Item* item = ptrSet::findByKey(items_, name);
        const T* castedItem = dynamic_cast<const T*>(item);
        if (castedItem)
            return *castedItem;
        else
            throw ItemNotFoundException<T>(getName() + "::" + name);
    }
}


void Namespace::walkItems(ItemInspector fnc, bool recursive) const
{
    Item_Set::iterator ite = items_.begin();
    while( ite != items_.end() )
    {
        fnc(**ite);
        if (recursive)
        {
            const Namespace* name_space = dynamic_cast<const Namespace*>(*ite);
            if (name_space)
                name_space->walkItems(fnc, recursive);
        }
    }
}


void Namespace::addItem(Item& item, string name)
{
    if (name == "")
        name = item.getName();
    pair<string, string> splitNamespace = splitTopNamespace_(name);
    if (splitNamespace.first != "")
    {
        Namespace* subNameSpace = dynamic_cast<Namespace*>(
                ptrSet::findByKey(items_, splitNamespace.first));
        if (!subNameSpace)
        {
            subNameSpace = new Namespace(splitNamespace.first, *this);
            addItem(*subNameSpace);
        }
        addItem(item, splitNamespace.second);
    }
    else
    {
        items_.insert(&item);
        item.setNamespace(*this);
    }
}


pair<string, string> splitTopNamespace_(const string& name)
{
    pair<string, string> splitName;
    size_t pos = name.find("::");
    if (pos != string::npos)
    {
        splitName.first = name.substr(0, pos);
        splitName.second = name.substr(pos + 2);
    }
    else
    {
        splitName.second = name;
    }
    return splitName;
}


Namespace::~Namespace()
{

}