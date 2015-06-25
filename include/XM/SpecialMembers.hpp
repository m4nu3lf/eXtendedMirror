/******************************************************************************      
 *      Extended Mirror: SpecialMembers.hpp                                   *
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


#ifndef XM_SPECIALMEMBERS_HPP
#define	XM_SPECIALMEMBERS_HPP

namespace xm {


class Constructor : public Member
{
public:
    Constructor(const Class& owner = getClass<void>());
    virtual void init(Variant& var) const;
};


class CopyConstructor : public Member
{
public:
    CopyConstructor(const Class& owner = getClass<void>());
    virtual void copy(Variant& copy, const Variant& orig) const;
};


class Destructor : public Member
{
public:
    Destructor(const Class& owner = getClass<void>());
    virtual void destroy(Variant& var) const;
};


class RefCaster : public Member
{
public:

    explicit RefCaster(const Class& dstClass = getClass<void>(),
              const Class& owner = getClass<void>());
    
    const Class& getDstClass() const;
    CastDirection getCastDirection() const;

    virtual
    Variant cast(const Variant& var) const;

protected:
    const Class* dstClass_;
    CastDirection castDir_;
        
    friend bool operator<(const RefCaster&, const RefCaster&);
};


} // namespace xm

#endif	/* XM_SPECIALMEMBERS_HPP */

