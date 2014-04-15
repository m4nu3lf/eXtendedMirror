/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_REFVARIANT_INL
#define	EXTMR_REFVARIANT_INL

#include <EXTMR/Exceptions/VariantTypeException.hpp>
#include <EXTMR/Exceptions/VariantCostnessException.hpp>
#include <EXTMR/RefVariant.hpp>

#include "Variant.hpp"


namespace extmr{


template<typename T>
RefVariant::RefVariant(T& data) : Variant(data, Reference)
{
}


} // namespace extmr

#endif /* EXTMR_REFVARIANT_INL */