/******************************************************************************      
 *      Extended Mirror: Function.cpp                                         *
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

#define _XM_FUNCTION_NC_PARAMS                                              \
Variant& ncArg0 = const_cast<Variant&>(arg0);                                 \
Variant& ncArg1 = const_cast<Variant&>(arg1);                                 \
Variant& ncArg2 = const_cast<Variant&>(arg2);                                 \
Variant& ncArg3 = const_cast<Variant&>(arg3);                                 \
Variant& ncArg4 = const_cast<Variant&>(arg4);                                 \
Variant& ncArg5 = const_cast<Variant&>(arg5);                                 \
Variant& ncArg6 = const_cast<Variant&>(arg6);                                 \
Variant& ncArg7 = const_cast<Variant&>(arg7);

using namespace std;
using namespace xm;

Function::Function(const std::string& name) :
        Item(name), retType_(&getType<void>()), fullSignature_(false)
{
}


Function::Function(const Namespace& name_space, const std::string& name) :
        Item(name_space, name), retType_(&getType<void>()),
        fullSignature_(false)
{    
}


Function::Function
(
    const string& name,
    const Type& retType,
    const Type& paramType0,
    const Type& paramType1,
    const Type& paramType2,
    const Type& paramType3,
    const Type& paramType4,
    const Type& paramType5,
    const Type& paramType6,
    const Type& paramType7
) :
    Item(name),
    retType_(&retType),
    fullSignature_(true)
{
        _XM_FUNCTION_PUSH_PARAMS
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


Variant Function::call
(
    const Variant& arg0,
    const Variant& arg1,
    const Variant& arg2,
    const Variant& arg3,
    const Variant& arg4,
    const Variant& arg5,
    const Variant& arg6,
    const Variant& arg7
) const
{
    _XM_FUNCTION_NC_PARAMS
    
    // variants are const anyway
    vector<Variant>& defaults = const_cast<vector<Variant>& >(defaults_);
    
    if (&ncArg0 == &Variant::Null)
    {
        return callImpl(defaults[0], defaults[1], defaults[2], defaults[3],
                defaults[4], defaults[5], defaults[6], defaults[7]);
    }
    else if (&ncArg1 == &Variant::Null)
    {
        return callImpl(ncArg0, defaults[1], defaults[2], defaults[3],
                defaults[4], defaults[5], defaults[6], defaults[7]);
    }
    else if (&ncArg2 == &Variant::Null)
    {
        return callImpl(ncArg0, ncArg1, defaults[2], defaults[3],
                defaults[4], defaults[5], defaults[6], defaults[7]);
    }
    else if (&ncArg3 == &Variant::Null)
    {
        return callImpl(ncArg0, ncArg1, ncArg2, defaults[3], defaults[4],
                defaults[5], defaults[6], defaults[7]);
    }
    else if (&ncArg4 == &Variant::Null)
    {
        return callImpl(ncArg0, ncArg1, ncArg2, ncArg3, defaults[4],
                defaults[5], defaults[6], defaults[7]);
    }
    else if (&ncArg5 == &Variant::Null)
    {
        return callImpl(ncArg0, ncArg1, ncArg2, ncArg3, ncArg4,
                defaults[5], defaults[6], defaults[7]);
    }
    else if (&ncArg6 == &Variant::Null)
    {
        return callImpl(ncArg0, ncArg1, ncArg2, ncArg3, ncArg4, ncArg5,
                defaults[6], defaults[7]);
    }
    else if (&ncArg7 == &Variant::Null)
    {
         return callImpl(ncArg0, ncArg1, ncArg2, ncArg3, ncArg4, ncArg5,
                 ncArg6, defaults[7]);
    }
    else
    {
        return callImpl(ncArg0, ncArg1, ncArg2, ncArg3, ncArg4, ncArg5,
                ncArg6, ncArg7);
    }
}


Variant Function::callV(vector<Variant> args) const
{
    args.resize(XM_FUNCTION_PARAM_MAX, Variant::Null);
    return call(args[0], args[1], args[2], args[3], args[4], args[5],
            args[6], args[7]);
}


Variant Function::callImpl
(
    Variant& arg0,
    Variant& arg1,
    Variant& arg2,
    Variant& arg3,
    Variant& arg4,
    Variant& arg5,
    Variant& arg6,
    Variant& arg7
) const
{
    return Variant::Null;
}


void Function::setDefaultArgs
(
    const Variant& arg0,
    const Variant& arg1,
    const Variant& arg2,
    const Variant& arg3,
    const Variant& arg4,
    const Variant& arg5,
    const Variant& arg6,
    const Variant& arg7
)
{
    _XM_FUNCTION_NC_PARAMS
    defaults_.clear();
    defaults_.resize(XM_FUNCTION_PARAM_MAX);
    ncArg0.setConst();
    defaults_[0] = arg0;
    ncArg0.setConst();
    defaults_[1] = arg1;
    ncArg0.setConst();
    defaults_[2] = arg2;
    ncArg0.setConst();
    defaults_[3] = arg3;
    ncArg0.setConst();
    defaults_[4] = arg4;
    ncArg0.setConst();
    defaults_[5] = arg5;
    ncArg0.setConst();
    defaults_[6] = arg6;
    ncArg0.setConst();
    defaults_[7] = arg7;
}