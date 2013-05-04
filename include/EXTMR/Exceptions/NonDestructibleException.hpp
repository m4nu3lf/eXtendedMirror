/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_NONDESTRUCTIBLEEXCEPTION_HPP
#define	EXTMR_NONDESTRUCTIBLEEXCEPTION_HPP

namespace extmr {

    
class NonDestructibleException : public std::exception
{
public:
    NonDestructibleException(const Type& type) throw();
    
    const char* what() const throw();
    
    virtual ~NonDestructibleException() throw();
    
private:
    const Type* type_;
};


} // namespace extmr

#endif	/* EXTMR_NONDESTRUCTIBLEEXCEPTION_HPP */

