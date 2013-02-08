/* 
 * File:   SetNotAllowed.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 15 January 2013, 19.16
 */

#ifndef EXTMR_SETNOTALLOWED_HPP
#define	EXTMR_SETNOTALLOWED_HPP

namespace extmr {

class Property;

class SetNotAllowed : public std::exception
{
public:
    SetNotAllowed(const Property& property);
    const char* what() const throw();
private:
    const Property* propertyDescPtr;
};

} // namespace extmr

#endif	/* EXTMR_SETNOTALLOWED_HPP */

