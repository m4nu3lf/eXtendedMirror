/* 
 * File:   NonInstantiableException.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on May 1, 2013, 10:12 PM
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

