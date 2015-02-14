/******************************************************************************      
 *      Extended Mirror: NotFoundExceptions.hpp                               *
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


#ifndef XM_NOTFOUNDEXCEPTIONS_HPP
#define	XM_NOTFOUNDEXCEPTIONS_HPP


namespace xm{


class NotFoundException : public std::exception
{
public:
    NotFoundException(const std::string& id, const std::string& category)
            throw();
    
    const char* what() const throw();
    
    ~NotFoundException() throw();
protected:
    std::string id_;
    std::string category_;
};


template<class C>
class ItemNotFoundException : public NotFoundException
{
};

#define _XM_DEFINE_ITEM_NOT_FOUND_EXCEPTION_SPECIALIZATION(_category_)         \
template<>                                                                     \
class ItemNotFoundException<_category_> : public NotFoundException             \
{                                                                              \
public:                                                                        \
    ItemNotFoundException<_category_>(const std::string& name)                 \
        : NotFoundException(name, #_category_){}                               \
};


_XM_DEFINE_ITEM_NOT_FOUND_EXCEPTION_SPECIALIZATION(Item)
_XM_DEFINE_ITEM_NOT_FOUND_EXCEPTION_SPECIALIZATION(Type)
_XM_DEFINE_ITEM_NOT_FOUND_EXCEPTION_SPECIALIZATION(Class)
_XM_DEFINE_ITEM_NOT_FOUND_EXCEPTION_SPECIALIZATION(Template)
_XM_DEFINE_ITEM_NOT_FOUND_EXCEPTION_SPECIALIZATION(Namespace)
_XM_DEFINE_ITEM_NOT_FOUND_EXCEPTION_SPECIALIZATION(Function)
        

template<class C>
class MemberNotFoundException : public NotFoundException
{
};

#define _XM_DEFINE_MEMBER_NOT_FOUND_EXCEPTION_SPECIALIZATION(_category_)       \
template<>                                                                     \
class MemberNotFoundException<_category_> : public NotFoundException           \
{                                                                              \
public:                                                                        \
    MemberNotFoundException(const std::string& id,                             \
                            const std::string& owner,                          \
                            bool idIsSignature = false) throw()                \
        : NotFoundException(id, #_category_), owner_(owner),                   \
          idIsSignature_(idIsSignature) {}                                     \
                                                                               \
    const char* what() const throw()                                           \
    {                                                                          \
        return ("Class " + owner_ + " has no " + category_ + " with "          \
                + (idIsSignature_? "signature " : "name ") + id_).c_str();     \
    }                                                                          \
private:                                                                       \
    std::string owner_;                                                        \
    bool idIsSignature_;                                                       \
};

_XM_DEFINE_MEMBER_NOT_FOUND_EXCEPTION_SPECIALIZATION(Member)
_XM_DEFINE_MEMBER_NOT_FOUND_EXCEPTION_SPECIALIZATION(Property)
_XM_DEFINE_MEMBER_NOT_FOUND_EXCEPTION_SPECIALIZATION(Method)


} // namespace xm

#endif	/* XM_NOTFOUNDEXCEPTIONS_HPP */

