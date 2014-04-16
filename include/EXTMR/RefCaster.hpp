/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_REFCASTER_HPP
#define	EXTMR_REFCASTER_HPP


namespace extmr {


class RefCaster
{
public:
    RefCaster(const Type& srcType = getType<void>(),
            const Type& dstType = getType<void>());
    
    RefCaster(std::pair<const Type*, const Type*> srcNdstTypes);
    
    const Type& getSrcType() const;
    const Type& getDstType() const;

    virtual
    RefVariant cast(const Variant& var) const;

    virtual
    ~RefCaster();

protected:
    const Type* srcType_;
    const Type* dstType_;
        
    friend bool operator<(const RefCaster&, const RefCaster&);
    
    friend class Class;
};


bool inline operator<(const RefCaster& rc1, const RefCaster& rc2)
{
    if (*rc1.srcType_ < *rc2.srcType_)
        return true;
    else return *rc1.dstType_ < *rc2.dstType_;
}


typedef std::set<const RefCaster*, PtrCmpByVal<RefCaster> > Const_RefCaster_Set;

} // namespace extmr

#endif /* EXTMR_REFCASTER_HPP */