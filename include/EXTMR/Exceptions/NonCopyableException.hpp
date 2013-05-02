/* 
 * File:   NonCopyableException.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on May 1, 2013, 10:12 PM
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

