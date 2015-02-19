/******************************************************************************
 *      Extended Mirror: NotFoundException.cpp                                *
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


#include <XM/xMirror.hpp>
#include <XM/Exceptions/NotFoundException.hpp>

using namespace std;
using namespace xm;


NotFoundException::NotFoundException(const Namespace& name_space,
                                     const Item& item) throw()
{
    string nsCategory;
    if (dynamic_cast<const Class*>(&name_space))
        nsCategory = "Class";
    else
        nsCategory = "Namespace";

    string itemCategory;
    const Method* method = NULL;
    if (dynamic_cast<const Class*>(&item))
        itemCategory = "Class";
    else if (dynamic_cast<const Namespace*>(&item))
        itemCategory = "Namespace";
    else if (dynamic_cast<const Property*>(&item))
        itemCategory = "Property";
    else if (dynamic_cast<const Method*>(&item))
    {
        itemCategory = "Method";
        method = dynamic_cast<const Method*>(&item);
    }
    else if (dynamic_cast<const Function*>(&item))
        itemCategory = "Function";
    else if (dynamic_cast<const Type*>(&item))
        itemCategory = "Type";

    msg = nsCategory + " " + name_space.getName() + " has no " +
          itemCategory;

    if (!method || !method->hasFullSignature())
        msg += " with name " + item.getUnqualifiedName();
    else
        msg += " with signature " + method->getSignature();
}


NotFoundException::NotFoundException(const type_info& cppType) throw()
{
    msg = "Cannot find Type with id ";
    msg += cppType.name();
}


const char* NotFoundException::what() const throw()
{
    return msg.c_str();
}

NotFoundException::~NotFoundException() throw()
{
}
