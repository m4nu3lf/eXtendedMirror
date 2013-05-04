/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_MISC_HPP
#define	EXTMR_MISC_HPP

namespace extmr{

class Type;

/**
 * Actually an empty class useful for unused template parameters.
 */
struct Empty
{
    Empty(){};
    
    /// Every type can be converted to an Empty.
    template<typename T>
    Empty(T param){};
};

} // namespace extmr

#endif	/* EXTMR_MISC_HPP */

