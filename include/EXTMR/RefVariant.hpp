/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_REFVARIANT_HPP
#define	EXTMR_REFVARIANT_HPP

namespace extmr {


class RefVariant : public Variant
{
public:
    RefVariant();
    
    template<typename T>
    RefVariant(T& data);
    
    RefVariant(const RefVariant& orig);
        
    RefVariant(const Variant& var);
    const Variant& operator=(const Variant& var);
};


} // namespace extmr

#endif /* EXTMR_REFVARIANT_HPP */