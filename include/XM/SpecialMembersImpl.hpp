#ifndef XM_SPECIALMEMBERSIMPL_HPP
#define	XM_SPECIALMEMBERSIMPL_HPP

namespace xm {


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


template<typename S, typename D>
class RefCasterImpl : public RefCaster
{
public:
    RefCasterImpl()
        : Item("", getClass<S>()),
          RefCaster(getClass<D>(), getClass<S>())
    {
    }

    Variant cast(const Variant& var) const
    {
        Variant& nc_var = const_cast<Variant&>(var);
        return Variant(dynamic_cast<D&>(nc_var.as<S>()), Variant::Reference);
    }

};


} // namespace xm

#endif	/* XM_SPECIALMEMBERSIMPL_HPP */

