/* 
 * File:   VariantTypeException.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on September 3, 2012, 12.50
 */

#ifndef EXTMR_BADTYPE_HPP
#define	EXTMR_BADTYPE_HPP

namespace extmr{

class VariantTypeException : public std::exception
{
public:
    VariantTypeException(const Type& givenType,const Type& variantType) throw();
    const char* what() const throw();
private:
    const Type* givenType;
    const Type* variantType;
};

} // namespace extmr

#endif	/* EXTMR_BADTYPE_HPP */

