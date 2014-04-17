/******************************************************************************      
 *      Extended Mirror: Property.cpp                                         *
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

Property::Property(const std::string& name) :
        Member(getClass<void>(), name), type_(NULL), flags_(0)
{
}


Property::Property(const Class& owner, const std::string& name = "") :
        Member(owner, name), type_(NULL), flags_(0)
{
}


const Type& Property::getType() const
{
    return *type_;
}


char Property::getFlags() const
{
    return 0;
}


Property& Property::setFlags(char flags)
{
    return *this;
}


double Property::getMinValue() const
{
    return numeric_limits<double>::min();
}


Property& Property::setMinValue(double minValue)
{
    return *this;
}


double Property::getMaxValue() const
{
    return numeric_limits<double>::max();
}


Property& Property::setMaxValue(double maxValue)
{
    return *this;
}


Property::GetMode Property::getGetMode()
{
    return None;
}


Property::SetMode Property::getSetMode()
{
    return None;
}


Variant Property::getData(const RefVariant& self) const
{
    return Variant::Null;
};


void Property::setData(const RefVariant& self, const Variant& data) const
{};
