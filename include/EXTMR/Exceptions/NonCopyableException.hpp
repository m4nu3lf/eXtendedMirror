/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_NONCOPYABLEEXCEPTION_HPP
#define	EXTMR_NONCOPYABLEEXCEPTION_HPP

namespace extmr {

    
class NonCopyableException : public std::exception
{
public:
    NonCopyableException(const Type& type) throw();
    
    const char* what() const throw();
    
    virtual ~NonCopyableException() throw();
    
private:
    const Type* type_;
};


} // namespace extmr

#endif	/* EXTMR_NONCOPYABLEEXCEPTION_HPP */

