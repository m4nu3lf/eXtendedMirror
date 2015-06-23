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


template<class C>
class ConstructorImpl : public Constructor
{
public:
    ConstructorImpl(const Class& owner) : Item("", owner) {};
    void init(Variant& var) const
    {
        new (&var.as<C>()) C();
    }
};


class CopyConstructor : public Member
{
public:
    CopyConstructor(const Class& owner = getClass<void>());
    virtual void copy(Variant& copy, const Variant& orig) const;
};


template<class C>
class CopyConstructorImpl : public CopyConstructor
{
public:
    CopyConstructorImpl(const Class& owner) : Item("", owner) {};
    void copy(Variant& copy, const Variant& orig) const
    {
        Variant& nc_orig = const_cast<Variant&>(orig);
        new (&copy.as<C>()) C(nc_orig.as<C>());
    }
};


class Destructor : Member
{
public:
    Destructor(const Class& owner = getClass<void>());
    virtual void destroy(Variant& var) const;
};


template<typename C>
class DestructorImpl : public Destructor
{
public:
    DestructorImpl(const Class& owner) : Item("", owner) {};
    void destroy(Variant& var) const
    {
        var.as<C>().~C();
    }
};


class RefCaster : public Member
{
public:
    RefCaster(const Type& dstType = getType<void>(),
              const Class& owner = getClass<void>());
    
    const Type& getDstType() const;

    virtual
    Variant cast(const Variant& var) const;

protected:
    const Type* dstType_;
        
    friend bool operator<(const RefCaster&, const RefCaster&);
};


bool inline operator<(const RefCaster& rc1, const RefCaster& rc2)
{
    return *rc1.dstType_ < *rc2.dstType_;
}


template<typename S, typename D>
class RefCasterImpl : public RefCaster
{
public:
    RefCasterImpl()
        : Item("", getClass<S>()),
          RefCaster(getType<D>(), getClass<S>())
    {
    }

    Variant cast(const Variant& var) const
    {
        Variant& nc_var = const_cast<Variant&>(var);
        return Variant(dynamic_cast<D&>(nc_var.as<S>()), Variant::Reference);
    }

};


} // namespace xm

#endif	/* XM_SPECIALMEMBERS_HPP */

