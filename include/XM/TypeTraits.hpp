/******************************************************************************      
 *      Extended Mirror: TypeTraits.hpp                                       *
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


#ifndef XM_TYPETRAITS_HPP
#define	XM_TYPETRAITS_HPP

#include <sstream>

namespace xm{

    
struct TrueType
{
    static const bool value = true;
};


struct FalseType
{
    static const bool value = false;
};


// Type checks

template<typename T>
struct IsConst : public FalseType {};


template<typename T>
struct IsConst<const T> : public TrueType {};


template<typename T>
struct IsConst<const T&> : public TrueType {};


template<typename T>
struct IsPointer : public FalseType {};


template<typename T>
struct IsPointer<T*> : public TrueType {};


template<typename T>
struct IsReference : public FalseType {};


template<typename T>
struct IsReference<T&> : public TrueType {};


template<typename T>
struct IsArray : public FalseType {};


template<typename T, std::size_t size>
struct IsArray<T[size]> : public TrueType {};


template<typename T>
struct IsNonConstReference : public FalseType {};


template<typename T>
struct IsNonConstReference<const T&> : public FalseType {};


template<typename T>
struct IsNonConstReference<T&> : public TrueType {};

// Type modifications

template<typename T>
struct RemoveConst
{
    typedef T Type;
};


template<typename T>
struct RemoveConst<const T>
{
    typedef T Type;
};


template<typename T>
struct RemoveConst<const T&>
{
    typedef T Type;
};


template<typename T>
struct RemoveAllCVQualifiers
{
    typedef T Type;
};


template<typename T>
struct RemoveAllCVQualifiers<const T>
{
    typedef typename RemoveAllCVQualifiers<T>::Type Type;
};


template<typename T>
struct RemoveAllCVQualifiers<volatile T>
{
    typedef typename RemoveAllCVQualifiers<T>::Type Type;
};


template<typename T>
struct RemoveAllCVQualifiers<const T*>
{
    typedef typename RemoveAllCVQualifiers<T*>::Type Type;
};


template<typename T>
struct RemoveAllCVQualifiers<const T&>
{
    typedef typename RemoveAllCVQualifiers<T&>::Type Type;
};


template<typename T>
struct RemoveAllCVQualifiers<volatile T*>
{
    typedef typename RemoveAllCVQualifiers<T*>::Type Type;
};


template<typename T>
struct RemoveAllCVQualifiers<volatile T&>
{
    typedef typename RemoveAllCVQualifiers<T&>::Type Type;
};


template<typename T>
struct RemovePointer
{
    typedef T Type;
};


template<typename T>
struct RemovePointer<T*>
{
    typedef T Type;
};


template<typename T>
struct RemoveReference
{
    typedef T Type;
};


template<typename T>
struct RemoveReference<T&>
{
    typedef T Type;
};


/**
 * If T is the type ElementType[size_1][size_2]...[size_n] then Type evaluate to
 * ElementType[size_2][size_3]...[size_n].
 * If T is not an array then Type evaluate to T.
 */
template<typename T>
struct RemoveExtent
{
    typedef T Type;
};


template<typename T, std::size_t size>
struct RemoveExtent<T[size]>
{
    typedef T Type;
};


/**
 * If T is the type ElementType[size_1][size_2]...[size_n] then Type evaluate to
 * ElementType.
 * If T is not an array then Type evaluate to T.
 */
template<typename T>
struct RemoveAllExtents
{
    typedef T Type;
};


template<typename T, std::size_t size>
struct RemoveAllExtents<T[size]>
{
    typedef typename RemoveAllExtents<T>::Type Type;
};


/**
 * Given the [size_1][size_2]...[size_n] array the size member
 * evaluate to size_1 or to zero if T is not an array.
 */
template<typename T>
struct ArraySize
{
    static const std::size_t size = 0;
};


template<typename T, std::size_t _size>
struct ArraySize<T[_size]>
{
    static const std::size_t size = _size;
};



/**
 * The inner type Type is the same of T if T is a numerical type, another numerical
 * type if T is not a numerical type.
 */
template<typename T>
struct ToNumerical
{
    typedef char Type;
};


#define XM_TONUMERICAL_SPECIALIZE(getType)\
template<>\
struct ToNumerical<getType>\
{\
    typedef getType Type;\
};


// Specialize the type recognizer for each primitive type
XM_TONUMERICAL_SPECIALIZE(char);
XM_TONUMERICAL_SPECIALIZE(wchar_t);
XM_TONUMERICAL_SPECIALIZE(short);
XM_TONUMERICAL_SPECIALIZE(int);
XM_TONUMERICAL_SPECIALIZE(long);
XM_TONUMERICAL_SPECIALIZE(float);
XM_TONUMERICAL_SPECIALIZE(double);
XM_TONUMERICAL_SPECIALIZE(uchar);
XM_TONUMERICAL_SPECIALIZE(ushort);
XM_TONUMERICAL_SPECIALIZE(uint);
XM_TONUMERICAL_SPECIALIZE(ulong);

} // namespace xm

#endif	/* XM_TYPETRAITS_HPP */

