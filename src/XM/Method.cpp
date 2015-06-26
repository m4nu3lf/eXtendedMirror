/******************************************************************************      
 *      Extended Mirror: Method.cpp                                         *
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

Method::Method(const std::string& uName) :
        Item(uName, getClass<void>()),
        Function(uName)
{
}


Method::Method(const std::string& uName, const Class& owner) :
        Item(uName, owner)
{
}


bool Method::hasFullSignature() const
{
    return fullSignature_;
}


std::string Method::getSignature() const
{
    if (fullSignature_)
    {
        string signature;

        switch (getReturnMode())
        {
            case Method::Value:
                signature += getReturnType().getName() + " ";
                break;

            case Method::Reference:
                signature += getReturnType().getName() + "& ";
                break;

            case Method::ConstReference:
                signature += "const " + getReturnType().getName()
                        + " ";
                break;

            case Method::None:
                break;
        }

        signature += getName() + "(";

        Const_Prameter_Vector params = getParameters();
        for (uint i = 1; i < params.size(); i++) {
            const Parameter* param = params[i];
            signature += param->type.getName();
            if (param->byNcReference)
                signature += "&";
            if (i != params.size() - 1)
                signature += ", ";
        }

        signature += ")";

        if (isConst())
            signature += " const";
        
        return signature;
    }
    else
        return getName() + "()";
        
}


bool Method::isConst() const
{
    return false;
}


bool Method::before_(const Item& item) const
{
    const Method& other = dynamic_cast<const Method&>(item);
    if (!fullSignature_ || !other.fullSignature_)
        return false;

    ushort paramN1 = params_.size();
    ushort paramN2 = other.params_.size();
    ushort paramN = std::min(paramN1, paramN2);
    for (uint i = 1; i < paramN; i++)
    {
        if (params_[i]->type
            < other.params_[i]->type)
            return true;
    }
    if (paramN1 < paramN2) return true;
    return false;
}


Item::Category Method::getItemCategory() const
{
    return MethodItem;
}
