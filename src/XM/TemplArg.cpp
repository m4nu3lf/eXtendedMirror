/******************************************************************************      
 *      Extended Mirror: TemplArg.cpp                                         *
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
#include <XM/Exceptions/TemplArgException.hpp>

using namespace std;
using namespace xm;
    

TemplArg::TemplArg(const Variant& value)
{
    ptr_.value_ = new Variant(value);
    category_ = ValueArg;
}


TemplArg::TemplArg(const Type& type)
{
    ptr_.type_ = &type;
    category_ = TypeArg;
}


TemplArg::TemplArg(const TemplArg& other)
{
    category_ = other.category_;
    if (category_ == ValueArg) {
        ptr_.value_ = new Variant(*other.ptr_.value_);
    } else {
        ptr_.type_ = other.ptr_.type_;
    }
}


TemplArg::TemplArg(TemplArg&& other)
{
    std::swap(category_, other.category_);
    std::swap(ptr_, other.ptr_);
}


const TemplArg& TemplArg::operator=(TemplArg other)
{
    std::swap(category_, other.category_);
    std::swap(ptr_, other.ptr_);
    return *this;
}


TemplArg::Category TemplArg::getCategory() const
{
    return category_;
}


Variant TemplArg::getValue() const
{
    if (category_ == ValueArg) {
        return *ptr_.value_;
    } else {
        throw TemplArgException(category_);
    }
}


const Type& TemplArg::getType() const
{
    if (category_ == TypeArg) {
        return *ptr_.type_;
    } else {
        throw TemplArgException(category_);
    }
}


TemplArg::~TemplArg()
{
    if (category_ == ValueArg) {
        delete ptr_.value_;
    }
}



