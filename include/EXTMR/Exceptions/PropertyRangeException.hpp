/* 
 * File:   PropertyRangeException.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on January 15, 2013, 18.58
 */

#ifndef EXTMR_PROPERTYRANGEEXCEPTION_HPP
#define	EXTMR_PROPERTYRANGEEXCEPTION_HPP

namespace extmr{

class PropertyRangeException : public std::exception
{
public:
    PropertyRangeException(double minValue,
                           double maxValue,
                           double givenValue) throw();
    const char* what() const throw();
private:
    double givenValue;
    double minValue;
    double maxValue;
};

} // namespace extmr

#endif	/* EXTMR_PROPERTYRANGEEXCEPTION_HPP */

