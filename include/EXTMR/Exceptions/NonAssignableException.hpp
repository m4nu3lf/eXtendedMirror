/* 
 * File:   NonAssignableException.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on May 1, 2013, 10:12 PM
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

