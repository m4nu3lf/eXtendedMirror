/* 
 * File:   Parameter.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 26 January 2013, 15.31
 */

#ifndef PARAMETER_HPP
#define	PARAMETER_HPP

namespace extmr{

/**
 * Holds some basic information about a method parameter.
 */
struct Parameter
{
    Parameter(const Type& type, bool byNcReference = false)
    : type(type), byNcReference(byNcReference)
    {};
    
    /// The parameter type.
    const Type& type;
    
    /// Whether the parameter is passed by a non const reference.
    const bool byNcReference;
};

} //namespace extmr

#endif	/* PARAMETER_HPP */

