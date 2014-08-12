/******************************************************************************      
 *      Extended Mirror: NotFoundExceptions.hpp                               *
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


#ifndef XM_NOTFOUNDEXCEPTIONS_HPP
#define	XM_NOTFOUNDEXCEPTIONS_HPP


namespace xm {
    
    
class NotFoundException : public std::exception
{
public:
    NotFoundException(const std::string& name_);
    
private:
    std::string name_;
};


#define _XM_DECLARE_NOT_FOUND_EXCEPTION(_type_)                                \
class _type_##NotFoundException : public NotFoundException                     \
{                                                                              \
public:                                                                        \
    _type_##NotFoundException(const std::string& name)                         \
        : NotFoundException(name) {}                                           \
                                                                               \
    const char* what() const throw();                                          \
};


_XM_DECLARE_NOT_FOUND_EXCEPTION(Namespace)
_XM_DECLARE_NOT_FOUND_EXCEPTION(Type)
_XM_DECLARE_NOT_FOUND_EXCEPTION(Class)
_XM_DECLARE_NOT_FOUND_EXCEPTION(Template)
_XM_DECLARE_NOT_FOUND_EXCEPTION(Property)


class MethodNotFoundException : public NotFoundException
{
public:
    MethodNotFoundException(const std::string& name, bool fullSignature = false)
            throw();
    
    const char* what() const throw();
    
private:
    bool fullSignature_;
};


} // namespace extmr

#endif	/* XM_NOTFOUNDEXCEPTIONS_HPP */

