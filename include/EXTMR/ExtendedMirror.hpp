/******************************************************************************      
 *      Extended Mirror: ExtendedMirror.hpp                                   *
 ******************************************************************************
 *      Copyright (c) 2012-2014, Manuele Finocchiaro                          *
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


#ifndef EXTENDEDMIRROR_HPP
#define	EXTENDEDMIRROR_HPP

#include <typeinfo>
#include <limits>
#include <set>
#include <map>
#include <vector>

/**
 * This function returns a function pointer to the callback function
 * to call on type registration. This function is used to retrieve the call
 * back function on the TypeRegister singleton instantiation.
 * 
 * @return The callback function
 */


#include <EXTMR/Utils/Utils.hpp>

namespace extmr {
DEFINE_POINTER_COMPARER_BY_METHOD(getName, PtrCmpByName)
};

#include <EXTMR/TypeRegister.hpp>
#include <EXTMR/Shortcuts.hpp>        
#include <EXTMR/TypeTraits.hpp>
#include <EXTMR/Empty.hpp>
#include <EXTMR/Variant.hpp>
#include <EXTMR/RefVariant.hpp>
#include <EXTMR/MethodWrappers.hpp>
#include <EXTMR/Type.hpp>
#include <EXTMR/RefCaster.hpp>
#include <EXTMR/PrimitiveType.hpp>
#include <EXTMR/PointerType.hpp>
#include <EXTMR/ArrayType.hpp>
#include <EXTMR/Member.hpp>
#include <EXTMR/Property.hpp>
#include <EXTMR/Method.hpp>
#include <EXTMR/OtherMembers.hpp>
#include <EXTMR/Template.hpp>
#include <EXTMR/Class.hpp>
#include <EXTMR/Member.inl>
#include <EXTMR/CompoundClass.hpp>
#include <EXTMR/Shortcuts.hpp>
#include <EXTMR/PropertyField.hpp>
#include <EXTMR/PropertyArrayField.hpp>
#include <EXTMR/PropertyGetterNSetter.hpp>
#include <EXTMR/Variant.inl>
#include <EXTMR/RefVariant.inl>
#include <EXTMR/MethodImpl.hpp>
#include <EXTMR/RefCasterImpl.hpp>
#include <EXTMR/TypeRegister.inl>
#include <EXTMR/MemberMakeUtils.hpp>
#include <EXTMR/RegistrationMacros.hpp>


// Specialize the type recognizer for each primitive type
EXTMR_ENABLE_PRIMITIVE(char);
EXTMR_ENABLE_PRIMITIVE(wchar_t);
EXTMR_ENABLE_PRIMITIVE(short);
EXTMR_ENABLE_PRIMITIVE(int);
EXTMR_ENABLE_PRIMITIVE(long);
EXTMR_ENABLE_PRIMITIVE(float);
EXTMR_ENABLE_PRIMITIVE(double);
EXTMR_ENABLE_PRIMITIVE(uchar);
EXTMR_ENABLE_PRIMITIVE(ushort);
EXTMR_ENABLE_PRIMITIVE(uint);
EXTMR_ENABLE_PRIMITIVE(ulong);
EXTMR_ENABLE_PRIMITIVE(bool);

#endif	/* EXTENDEDMIRROR_HPP */

