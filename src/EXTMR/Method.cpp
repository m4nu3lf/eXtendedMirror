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


Method::Method
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
    Member(getClass<void>(), name),
    retType_(&retType),
    fullSignature_(true)
{
        _EXTMR_FUNCTION_PUSH_PARAMS
}


Method::Method
(
    const Class& owner,
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
    Member(owner, name),
    retType_(&retType),
    fullSignature_(true)
{
        _EXTMR_METHOD_PUSH_PARAMS
}


bool Method::isConst() const
{
    return false;
}