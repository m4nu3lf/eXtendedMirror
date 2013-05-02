/* 
 * File:   NonDestructibleException.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on May 1, 2013, 10:12 PM
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

