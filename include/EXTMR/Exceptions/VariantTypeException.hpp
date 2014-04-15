/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_VARIANTTYPEEXCEPTION_HPP
#define	EXTMR_VARIANTTYPEEXCEPTION_HPP

namespace extmr{

class VariantTypeException : public std::exception
{
public:
    VariantTypeException(const Type& givenType,const Type& variantType)
            throw();
    const char* what() const throw();
private:
    const Type* givenType_;
    const Type* variantType_;
};

} // namespace extmr

#endif	/* EXTMR_VARIANTTYPEEXCEPTION_HPP */

