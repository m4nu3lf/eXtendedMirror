/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_NONINSTANTIABLEEXCEPTION_HPP
#define	EXTMR_NONINSTANTIABLEEXCEPTION_HPP

namespace extmr {

    
class NonInstantiableException : public std::exception
{
public:
    NonInstantiableException(const Type& type) throw();
    
    const char* what() const throw();
    
    virtual ~NonInstantiableException() throw();
    
private:
    const Type* type_;
};


} // namespace extmr

#endif	/* EXTMR_NONINSTANTIABLEEXCEPTION_HPP */

