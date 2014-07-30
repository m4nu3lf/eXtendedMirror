/******************************************************************************      
 *      Extended Mirror: OtherMembers.cpp                                     *
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
#include <EXTMR/Exceptions/MembersExceptions.hpp>

using namespace extmr;

Constructor::Constructor(const Class& owner) : Member(owner){};


void Constructor::init(const Variant& var) const
{
    if (owner_)
        throw NonInstantiableException(*owner_);
}


CopyConstructor::CopyConstructor(const Class& owner) : Member(owner){};


void CopyConstructor::copy(const Variant& copy, const Variant& orig) const
{
    if (owner_)
        throw NonCopyableException(*owner_);
}


Destructor::Destructor(const Class& owner) : Member(owner){};


void Destructor::destroy(const Variant& var) const
{
    if (owner_)
        throw NonDestructibleException(*owner_);
}


AssignOperator::AssignOperator(const Class& owner) : Member(owner){};


void AssignOperator::assign(const Variant& lvar, const Variant& rvar) const
{
    if (owner_)
        throw NonAssignableException(*owner_);
}

AddressOfOperator::AddressOfOperator(const Class& owner) : Member(owner){};


void AddressOfOperator::addressOf(const Variant& lvar,
        const Variant& rvar) const
{
    if (owner_)
        throw NonAddressableException(*owner_);
}


DereferenceOperator::DereferenceOperator(const Class& owner) : Member(owner){};


void DereferenceOperator::dereference(const Variant& lvar,
        const Variant& rvar) const
{
    if (owner_)
        throw NonDereferenceableException(*owner_);
}