/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_PROPERTYSETEXCEPTION_HPP
#define	EXTMR_PROPERTYSETEXCEPTION_HPP

namespace extmr {

class Property;

class PropertySetException : public std::exception
{
public:
    PropertySetException(const Property& property);
    const char* what() const throw();
private:
    const Property& property_;
};

} // namespace extmr

#endif	/* EXTMR_PROPERTYSETEXCEPTION_HPP */

