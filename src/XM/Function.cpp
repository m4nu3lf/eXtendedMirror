/******************************************************************************      
 *      Extended Mirror: Function.cpp                                         *
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

using namespace std;
using namespace xm;

Function::Function(const std::string& uName) :
        Item(uName), retType_(&getType<void>()), fullSignature_(false)
{
}


Function::Function(const std::string& uName, const Namespace& name_space) :
        Item(uName, name_space), retType_(&getType<void>()),
        fullSignature_(false)
{    
}


void Function::addParameter(const Parameter& param)
{
    params_.push_back(&param);
}


const Type& Function::getReturnType() const
{
    return *retType_;
}


Function::ReturnMode Function::getReturnMode() const
{
    return Value;
}


const std::vector<const Parameter*>& Function::getParameters() const
{
    return params_;
}


bool Function::before(const Item& item) const
{
    const Function* other = dynamic_cast<const Function*>(&item);
    bool itemCmpBef = Item::before(item);
    bool itemCmpAft = item.Item::before(*this);
    if (!other || itemCmpBef)
        return true;
    if (itemCmpAft)
        return false;

    if (!fullSignature_ || !other->fullSignature_)
        return false;

    ushort paramN1 = params_.size();
    ushort paramN2 = other->params_.size();
    ushort paramN = std::min(paramN1, paramN2);
    for (uint i = 0; i < paramN; i++)
    {
        if (params_[i]->type
            < other->params_[i]->type)
            return true;
    }
    if (paramN1 < paramN2) return true;
    return false;
}
