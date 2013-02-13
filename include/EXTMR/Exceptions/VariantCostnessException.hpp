/* 
 * File:   VariantCostnessException.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on January 22, 2013, 18.56
 */

#ifndef EXTMR_CONSTNESSBREAK_HPP
#define	EXTMR_CONSTNESSBREAK_HPP

namespace extmr{

class VariantCostnessException : public std::exception
{
public:
    VariantCostnessException(const Type& type) throw();
    const char* what() const throw();
private:
    const Type& type;
};

} // namespace extmr

#endif	/* EXTMR_CONSTNESSBREAK_HPP */

