/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_BOUNDSCHECK_HPP
#define	EXTMR_BOUNDSCHECK_HPP

namespace extmr{

/**
 * Set the passed parameters to the numerical limits of the type T.
 * If T is a floating point value min is set to be - max.
 * If T is not a numerical type both value are set to zero.
 * 
 * @param min The variable to set at the minimum value.
 * @param max The variable to set at the maximum value.
 */
template<typename T>
void getTypeBounds(typename ToNumerical<T>::Type& min,
        typename ToNumerical<T>::Type& max)
{
    typedef typename ToNumerical<T>::Type NumT;
    
    if (std::numeric_limits<T>::is_specialized)
    {
        max = std::numeric_limits<NumT>::max();
        if(std::numeric_limits<T>::is_integer)
            min = std::numeric_limits<NumT>::min();
        else
            min = -max;
    }
    else min = max = 0;
}


template<typename T>
double toDouble(T& value)
{
    return 0;
}


#define EXTMR_SPECIALIZE_TO_DOUBLE(getType)                                    \
template<>                                                                     \
inline                                                                         \
double toDouble<getType>(getType& value)                                       \
{                                                                              \
    return static_cast<double>(value);                                         \
}


EXTMR_SPECIALIZE_TO_DOUBLE(char);
EXTMR_SPECIALIZE_TO_DOUBLE(wchar_t);
EXTMR_SPECIALIZE_TO_DOUBLE(short);
EXTMR_SPECIALIZE_TO_DOUBLE(int);
EXTMR_SPECIALIZE_TO_DOUBLE(long);
EXTMR_SPECIALIZE_TO_DOUBLE(float);
EXTMR_SPECIALIZE_TO_DOUBLE(double);
EXTMR_SPECIALIZE_TO_DOUBLE(uchar);
EXTMR_SPECIALIZE_TO_DOUBLE(ushort);
EXTMR_SPECIALIZE_TO_DOUBLE(uint);
EXTMR_SPECIALIZE_TO_DOUBLE(ulong);


/**
 * Checks whether a value is into the defined bounds.
 * For non numerical values returns true by default.
 * 
 * @param value The value to check.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return True if the value is into the range or if the type is not a numerical
 * value.
 */
template<typename T1, typename T2>
bool inline checkValueBounds(const T1& value, const T2& min, const T2& max)
{
    return true;
}

#define EXTMR_SPECIALIZE_CHECK_VALUE_BOUNDS(num_type)                          \
template<>                                                                     \
bool inline checkValueBounds<num_type, num_type>(const num_type& value,        \
                                                 const num_type& min,          \
                                                 const num_type& max)          \
{                                                                              \
    return min <= value & value <= max;                                        \
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

