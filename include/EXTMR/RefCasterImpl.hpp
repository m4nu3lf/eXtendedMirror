/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_REFCASTERIMPL_HPP
#define	EXTMR_REFCASTERIMPL_HPP

namespace extmr {

template<typename S, typename D>
class RefCasterImpl : public RefCaster
{
public:
	RefCasterImpl()
	{
            dstType_ = &TypeRegister::getSingleton().registerType<D>();
        }
        
        RefCasterImpl(const Class& dstType)
	{
            dstType_ = &dstType;
        }

	RefVariant cast(const Variant& var) const
	{
		return dynamic_cast<D&>(var.as<S>());
	}

};


} // namspace extmr

#endif /* EXTMR_REFCASTERIMPL_HPP */