/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
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
    double givenValue_;
    double minValue_;
    double maxValue_;
};

} // namespace extmr

#endif	/* EXTMR_PROPERTYRANGEEXCEPTION_HPP */

