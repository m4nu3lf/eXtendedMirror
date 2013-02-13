/* 
 * File:   BoundsCheck.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on January 6, 2013, 15.49
 */

#ifndef EXTMR_BOUNDSCHECK_HPP
#define	EXTMR_BOUNDSCHECK_HPP

namespace extmr{

/**
 * Checks whether a value is into the defined bounds.
 * For non numerical values returns true by default.
 * 
 * @param value The value to check.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return True if the value is into the range or if the type is not a numerical value.
 */
template<typename T1, typename T2>
bool inline checkValueBounds(const T1& value, const T2& min, const T2& max)
{
    return true;
}

#define EXTMR_SPECIALIZE_CHECK_VALUE_BOUNDS(num_type)\
template<>\
bool inline checkValueBounds<num_type, num_type>(const num_type& value, const num_type& min, const num_type& max)\
{\
    return min <= value & value <= max;\
}

EXTMR_SPECIALIZE_CHECK_VALUE_BOUNDS(char);
EXTMR_SPECIALIZE_CHECK_VALUE_BOUNDS(wchar_t);
EXTMR_SPECIALIZE_CHECK_VALUE_BOUNDS(short);
EXTMR_SPECIALIZE_CHECK_VALUE_BOUNDS(int);
EXTMR_SPECIALIZE_CHECK_VALUE_BOUNDS(long);
EXTMR_SPECIALIZE_CHECK_VALUE_BOUNDS(float);
EXTMR_SPECIALIZE_CHECK_VALUE_BOUNDS(double);
EXTMR_SPECIALIZE_CHECK_VALUE_BOUNDS(uchar);
EXTMR_SPECIALIZE_CHECK_VALUE_BOUNDS(ushort);
EXTMR_SPECIALIZE_CHECK_VALUE_BOUNDS(uint);
EXTMR_SPECIALIZE_CHECK_VALUE_BOUNDS(ulong);

} //namespace extmr

#endif	/* EXTMR_BOUNDSCHECK_HPP */

