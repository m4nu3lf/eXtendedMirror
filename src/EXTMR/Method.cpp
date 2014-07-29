/******************************************************************************      
 *      Extended Mirror: Method.cpp                                         *
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


#include <EXTMR/Utils/Utils.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

Method::Method(const std::string& name) :
        Member(getClass<void>(), name), retType_(&getType<void>()),
        fullSignature_(false)
{
}


Method::Method(const Class& owner, const std::string& name) :
        Member(owner, name), retType_(&getType<void>()), fullSignature_(false)
{
}


#define _EXTMR_METHOD_PUSH_PARAMS                       \
this->retType_ = &retType;                              \
if (paramType1 != getType<void>())                      \
    params_.push_back(new Parameter(paramType1));       \
if (paramType2 != getType<void>())                      \
    params_.push_back(new Parameter(paramType2));       \
if (paramType3 != getType<void>())                      \
    params_.push_back(new Parameter(paramType3));       \
if (paramType4 != getType<void>())                      \
    params_.push_back(new Parameter(paramType4));       \
if (paramType5 != getType<void>())                      \
    params_.push_back(new Parameter(paramType5));       \
if (paramType6 != getType<void>())                      \
    params_.push_back(new Parameter(paramType6));       \
if (paramType7 != getType<void>())                      \
    params_.push_back(new Parameter(paramType7));       \
if (paramType8 != getType<void>())                      \
    params_.push_back(new Parameter(paramType8));


Method::Method
(
    const string& name,
    const Type& retType,
    const Type& paramType1,
    const Type& paramType2,
    const Type& paramType3,
    const Type& paramType4,
    const Type& paramType5,
    const Type& paramType6,
    const Type& paramType7,
    const Type& paramType8
) :
    Member(getClass<void>(), name),
    retType_(&retType),
    fullSignature_(true)
{
        _EXTMR_METHOD_PUSH_PARAMS
}


Method::Method
(
    const Class& owner,
    const string& name,
    const Type& retType,
    const Type& paramType1,
    const Type& paramType2,
    const Type& paramType3,
    const Type& paramType4,
    const Type& paramType5,
    const Type& paramType6,
    const Type& paramType7,
    const Type& paramType8
) :
    Member(owner, name),
    retType_(&retType),
    fullSignature_(true)
{
        _EXTMR_METHOD_PUSH_PARAMS
}


void Method::addParameter(const Parameter& param)
{
    params_.push_back(&param);
}


const Type& Method::getReturnType() const
{
    return *retType_;
}


Method::ReturnMode Method::getReturnMode() const
{
    return Value;
}


const std::vector<const Parameter*>& Method::getParameters() const
{
    return params_;
}


bool Method::isConst() const
{
    return false;
}


Variant Method::call
(
    const RefVariant& self,
    const Variant& arg1,
    const Variant& arg2,
    const Variant& arg3,
    const Variant& arg4,
    const Variant& arg5,
    const Variant& arg6,
    const Variant& arg7,
    const Variant& arg8
) const
{
    if (&arg1 == &Variant::Null)
    {
        return callImpl(self, defaults_[0], defaults_[1], defaults_[2],
                defaults_[3], defaults_[4], defaults_[5], defaults_[6],
                defaults_[7]);
    }
    else if (&arg2 == &Variant::Null)
    {
        return callImpl(self, arg1, defaults_[1], defaults_[2], defaults_[3],
                defaults_[4], defaults_[5], defaults_[6], defaults_[7]);
    }
    else if (&arg3 == &Variant::Null)
    {
        return callImpl(self, arg1, arg2, defaults_[2], defaults_[3],
                defaults_[4], defaults_[5], defaults_[6], defaults_[7]);
    }
    else if (&arg4 == &Variant::Null)
    {
        return callImpl(self, arg1, arg2, arg3, defaults_[3], defaults_[4],
                defaults_[5], defaults_[6], defaults_[7]);
    }
    else if (&arg5 == &Variant::Null)
    {
        return callImpl(self, arg1, arg2, arg3, arg4, defaults_[4],
                defaults_[5], defaults_[6], defaults_[7]);
    }
    else if (&arg6 == &Variant::Null)
    {
        return callImpl(self, arg1, arg2, arg3, arg4, arg5, defaults_[5],
                defaults_[6], defaults_[7]);
    }
    else if (&arg7 == &Variant::Null)
    {
        return callImpl(self, arg1, arg2, arg3, arg4, arg5, arg6,
                defaults_[6], defaults_[7]);
    }
    else if (&arg8 == &Variant::Null)
    {
         return callImpl(self, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                 defaults_[7]);
    }
    else
    {
        return callImpl(self, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    }
}


Variant Method::callV(const RefVariant& self, vector<Variant> args) const
{
    args.resize(EXTMR_METHOD_PARAM_MAX, Variant::Null);
    return call(self, args[0], args[1], args[2], args[3], args[4], args[5],
            args[6], args[7]);
}


Variant Method::callImpl
(
    const RefVariant& self,
    const Variant& arg1,
    const Variant& arg2,
    const Variant& arg3,
    const Variant& arg4,
    const Variant& arg5,
    const Variant& arg6,
    const Variant& arg7,
    const Variant& arg8
) const
{
    return Variant::Null;
}


void Method::setDefaultArgs
(
    const Variant& arg1,
    const Variant& arg2,
    const Variant& arg3,
    const Variant& arg4,
    const Variant& arg5,
    const Variant& arg6,
    const Variant& arg7,
    const Variant& arg8
)
{
    defaults_.clear();
    defaults_.resize(EXTMR_METHOD_PARAM_MAX);
    defaults_[0] = arg1;
    defaults_[1] = arg2;
    defaults_[2] = arg3;
    defaults_[3] = arg4;
    defaults_[4] = arg5;
    defaults_[5] = arg6;
    defaults_[6] = arg7;
    defaults_[7] = arg8;
}
