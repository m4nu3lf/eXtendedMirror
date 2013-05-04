/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_NONASSIGNABLEEXCEPTION_HPP
#define	EXTMR_NONASSIGNABLEEXCEPTION_HPP

namespace extmr {

    
class NonAssignableException : public std::exception
{
public:
    NonAssignableException(const Type& type) throw();
    
    const char* what() const throw();
    
    virtual ~NonAssignableException() throw();
    
private:
    const Type* type_;
};


} // namespace extmr

#endif	/* EXTMR_NONASSIGNABLEEXCEPTION_HPP */

