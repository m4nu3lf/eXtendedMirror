/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
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
    
    /** The parameter type. */
    const Type& type;
    
    /** Whether the parameter is passed by a non const reference. */
    const bool byNcReference;
};


typedef std::vector<const Parameter*> ConstPrameterVector;


} //namespace extmr

#endif	/* PARAMETER_HPP */

