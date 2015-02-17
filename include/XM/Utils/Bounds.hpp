/******************************************************************************      
 *      Extended Mirror: Bounds.hpp                                         *
 ******************************************************************************
 *      Copyright (c) 2012-2015, Manuele Finocchiaro                          *
 *      All rights reserved.                                                  *
 ******************************************************************************
 * Redistribution and use in source and binary forms, with or without         *
 * modification, are permitted provided that the following conditions         *
 * are met:                                                                   *
 *                                                                            *
 *    1. Redistributions of source code must retain the above copyright       *
 *       notice, this list of conditions and the following disclaimer.        *
 *                                                                            *
 *    2. Redistributions in binary form must reproduce the above copyright    *
 *       notice, this list of conditions and the following disclaimer in      *
 *       the documentation and/or other materials provided with the           *
 *       distribution.                                                        *
 *                                                                            *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"* 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE  *
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE *
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE  *
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR        *
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF       *
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   *
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN    *
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)    *
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF     *
 * THE POSSIBILITY OF SUCH DAMAGE.                                            *
 *****************************************************************************/


#ifndef XM_UTILS_BOUNDS_HPP
#define	XM_UTILS_BOUNDS_HPP

namespace xm {

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
    (void)(value);
    return 0;
}


#define XM_SPECIALIZE_TO_DOUBLE(getType)                                       \
template<>                                                                     \
inline                                                                         \
double toDouble<getType>(getType& value)                                       \
{                                                                              \
    return static_cast<double>(value);                                         \
}


XM_SPECIALIZE_TO_DOUBLE(char);
XM_SPECIALIZE_TO_DOUBLE(wchar_t);
XM_SPECIALIZE_TO_DOUBLE(short);
XM_SPECIALIZE_TO_DOUBLE(int);
XM_SPECIALIZE_TO_DOUBLE(long);
XM_SPECIALIZE_TO_DOUBLE(float);
XM_SPECIALIZE_TO_DOUBLE(double);
XM_SPECIALIZE_TO_DOUBLE(uchar);
XM_SPECIALIZE_TO_DOUBLE(ushort);
XM_SPECIALIZE_TO_DOUBLE(uint);
XM_SPECIALIZE_TO_DOUBLE(ulong);


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
    (void)(value);
    (void)(min);
    (void)(max);
    return true;
}

#define XM_SPECIALIZE_CHECK_VALUE_BOUNDS(num_type)                             \
template<>                                                                     \
bool inline checkValueBounds<num_type, num_type>(const num_type& value,        \
                                                 const num_type& min,          \
                                                 const num_type& max)          \
{                                                                              \
    return min <= value && value <= max;                                       \
}

XM_SPECIALIZE_CHECK_VALUE_BOUNDS(char);
XM_SPECIALIZE_CHECK_VALUE_BOUNDS(wchar_t);
XM_SPECIALIZE_CHECK_VALUE_BOUNDS(short);
XM_SPECIALIZE_CHECK_VALUE_BOUNDS(int);
XM_SPECIALIZE_CHECK_VALUE_BOUNDS(long);
XM_SPECIALIZE_CHECK_VALUE_BOUNDS(float);
XM_SPECIALIZE_CHECK_VALUE_BOUNDS(double);
XM_SPECIALIZE_CHECK_VALUE_BOUNDS(uchar);
XM_SPECIALIZE_CHECK_VALUE_BOUNDS(ushort);
XM_SPECIALIZE_CHECK_VALUE_BOUNDS(uint);
XM_SPECIALIZE_CHECK_VALUE_BOUNDS(ulong);

} //namespace xm

#endif	/* XM_UTILS_BOUNDS_HPP */

