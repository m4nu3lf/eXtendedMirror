/* 
 * File:   PropertySetException.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on January 15, 2013, 19.16
 */

#ifndef EXTMR_PROPERTYSETEXCEPTION_HPP
#define	EXTMR_PROPERTYSETEXCEPTION_HPP

namespace extmr {

class Property;

class PropertySetException : public std::exception
{
public:
    PropertySetException(const Property& property, const Class& ownerClass);
    const char* what() const throw();
private:
    const Property& property;
    const Class& ownerClass;
};

} // namespace extmr

#endif	/* EXTMR_PROPERTYSETEXCEPTION_HPP */

