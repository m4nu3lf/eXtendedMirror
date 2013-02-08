/* 
 * File:   BadType.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 3 September 2012, 12.50
 */

#ifndef EXTMR_BADTYPE_HPP
#define	EXTMR_BADTYPE_HPP

namespace extmr{

class BadType : public std::exception
{
public:
    BadType(const Type& givenType, const Type& expectedType) throw();
    const char* what() const throw();
private:
    const Type* givenType;
    const Type* expectedType;
};

} // namespace extmr

#endif	/* EXTMR_BADTYPE_HPP */

