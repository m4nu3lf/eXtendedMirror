/******************************************************************************
 *      Extended Mirror: Item.cpp                                         *
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
#include <XM/Utils/Names.hpp>

using namespace std;
using namespace xm;

Item::Item(const string& uName, const Namespace& name_space) :
        unqualifiedName_(uName), namespace_(&name_space)
{
}

Item::Item(const string& uName) :
        unqualifiedName_(uName),
        namespace_(NULL)
{
}

const string& Item::getUnqualifiedName() const
{
    return unqualifiedName_;
}


string Item::getName() const
{
    if (namespace_)
        return namespace_->getName() + "::" + unqualifiedName_;
    else
        return unqualifiedName_;
}


const Namespace& Item::getNamespace() const
{
    if (namespace_)
        return *namespace_;
    else
        return Register::getSingleton();
}


Item::Category Item::getItemCategory() const
{
    return AnyItem;
}


bool Item::before(const Item& item) const
{
    if (unqualifiedName_ < item.unqualifiedName_)
        return true;
    if (unqualifiedName_ > item.unqualifiedName_)
        return false;

    // Same name, check for item category
    if (this->getItemCategory() == AnyItem ||
        item.getItemCategory() == AnyItem)
        return false;

    if (this->getItemCategory() < item.getItemCategory())
        return true;
    if (this->getItemCategory() > item.getItemCategory())
        return false;

    // Same item category, use virtual comparer
    return before_(item);
}


bool Item::before_(const Item& item) const
{
    (void) item;
    return false;
}


Item::~Item()
{
}

