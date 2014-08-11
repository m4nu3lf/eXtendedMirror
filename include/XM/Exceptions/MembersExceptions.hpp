/******************************************************************************      
 *      Extended Mirror: NonAssignableException.hpp                           *
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


#ifndef XM_MEMBERSEXCEPTIONS_HPP
#define	XM_MEMBERSEXCEPTIONS_HPP

namespace xm {


class MemberException : public std::exception
{
public:
    MemberException(const Type& type, const std::string& verb,
            const std::string& adjective) throw();
    
    const char* what() const throw();
    
    virtual ~MemberException() throw();

private:
    const Type* type_;
    
    std::string verb_;
    std::string article_;
    std::string adjective_;
    
};


#define _XM_DECLARE_MEMBER_EXCEPTION(_name_)                                   \
                                                                               \
class Non##_name_##Exception : public MemberException                          \
{                                                                              \
public:                                                                        \
    Non##_name_##Exception(const Type& type) throw();                          \
                                                                               \
    virtual ~Non##_name_##Exception() throw();                                 \
                                                                               \
};


_XM_DECLARE_MEMBER_EXCEPTION(Instantiable)
_XM_DECLARE_MEMBER_EXCEPTION(Copyable)
_XM_DECLARE_MEMBER_EXCEPTION(Destructible)


} // namespace xm

#endif	/* XM_MEMBERSEXCEPTIONS_HPP */

