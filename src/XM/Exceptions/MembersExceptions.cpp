/******************************************************************************      
 *      Extended Mirror: MemebersException.cpp                                *
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


#include <XM/ExtendedMirror.hpp>
#include <XM/Exceptions/MembersExceptions.hpp>

using namespace xm;


MemberException::MemberException(const Type& type,
        const std::string& verb, const std::string& adjective) throw()
        : type_(&type), verb_(verb), article_("a"), adjective_(adjective)
{
    if (adjective_.length() > 0)
    {
        switch (adjective_[0])
        {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                article_ += "n";
        }
    }
}


const char* MemberException::what() const throw()
{
    return ("Trying to " + verb_ + " object of type\"" + type_->getName()
        + "\" that is not " + article_ + " " + adjective_ + " type").c_str();
}


MemberException::~MemberException() throw()
{
    
}

#define _XM_DEFINE_MEMBER_EXCEPTION(_name_, _verb_, _adjective_)               \
                                                                               \
Non##_name_##Exception::Non##_name_##Exception(const Type& type) throw()       \
        : MemberException(type, #_verb_, #_adjective_)                         \
{}                                                                             \
                                                                               \
Non##_name_##Exception::~Non##_name_##Exception() throw()                      \
{}

_XM_DEFINE_MEMBER_EXCEPTION(Instantiable, instantiate, instantiable)
_XM_DEFINE_MEMBER_EXCEPTION(Copyable, copy, copyable)
_XM_DEFINE_MEMBER_EXCEPTION(Destructible, destroy, destructible)