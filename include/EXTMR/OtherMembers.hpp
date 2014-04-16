/* 
 * File:   Constructor.hpp
 * Author: manuele
 *
 * Created on April 16, 2014, 2:11 AM
 */

#ifndef EXTMR_OTHERMEMBERS_HPP
#define	EXTMR_OTHERMEMBERS_HPP

namespace extmr {


class Constructor : public Member
{
public:
    Constructor(const Class& owner);
    virtual void init(const Variant& var) const;
};


template<class C>
class ConstructorImpl : public Constructor
{
public:
    ConstructorImpl(const Class& owner) : Constructor(owner) {};
    void init(const Variant& var) const
    {
        new (&var.as<C>()) C();
    }
};


class CopyConstructor : public Member
{
public:
    CopyConstructor(const Class& owner);
    virtual void copy(const Variant& copy, const Variant& orig) const;
};


template<class C>
class CopyConstructorImpl : public CopyConstructor
{
public:
    CopyConstructorImpl(const Class& owner) : CopyConstructor(owner) {};
    void copy(const Variant& copy, const Variant& orig) const
    {
        new (&copy.as<C>()) C(orig.as<C>());
    }
};


class Destructor : Member
{
public:
    Destructor(const Class& owner);
    virtual void destroy(const Variant& var) const;
};


template<typename C>
class DestructorImpl : public Destructor
{
public:
    DestructorImpl(const Class& owner) : Destructor(owner) {};
    void destroy(const Variant& var) const
    {
        var.as<C>().~C();
    }
};


class AssignOperator : public Member
{
public:
    AssignOperator(const Class& owner);
    virtual void assign(const Variant& lvar, const Variant& rvar) const;
};


template<typename C>
class AssignOperatorImpl : public AssignOperator
{
public:
    AssignOperatorImpl(const Class& owner) : AssignOperator(owner) {}
    void assign(const Variant& lvar, const Variant& rvar) const
    {
        lvar.as<C>() = rvar.as<C>();
    }
};


//TODO: Add all other operators

} // namespace extmr

#endif	/* EXTMR_OTHERMEMBERS_HPP */

