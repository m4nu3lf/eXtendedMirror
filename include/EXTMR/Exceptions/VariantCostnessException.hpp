/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_CONSTNESSBREAK_HPP
#define	EXTMR_CONSTNESSBREAK_HPP

namespace extmr{

class VariantCostnessException : public std::exception
{
public:
    VariantCostnessException(const Type& type) throw();
    const char* what() const throw();
private:
    const Type& type_;
};

} // namespace extmr

#endif	/* EXTMR_CONSTNESSBREAK_HPP */

