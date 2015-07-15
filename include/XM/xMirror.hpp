/******************************************************************************      
 *      Extended Mirror: xMirror.hpp                                   *
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


#ifndef EXTENDEDMIRROR_HPP
#define	EXTENDEDMIRROR_HPP

#include <typeinfo>
#include <limits>
#include <set>
#include <map>
#include <vector>
#include <utility>

#include <XM/Typedefs.hpp>
#include <XM/Utils/Utils.hpp>

namespace xm {    
_XM_DEFINE_POINTER_COMPARER_BY_METHOD(getName, PtrCmpByName)
_XM_DEFINE_POINTER_COMPARER_BY_METHOD(getId, PtrCmpById)
}


#include <XM/Item.hpp>
#include <XM/Namespace.hpp>
#include <XM/Register.hpp>
#include <XM/Shortcuts.hpp>
#include <XM/TypeTraits.hpp>
#include <XM/Empty.hpp>
#include <XM/Variant.hpp>
#include <XM/Type.hpp>
#include <XM/PrimitiveType.hpp>
#include <XM/PointerType.hpp>
#include <XM/ArrayType.hpp>
#include <XM/Member.hpp>
#include <XM/Property.hpp>
#include <XM/Constant.hpp>
#include <XM/Enum.hpp>
#include <XM/Function.hpp>
#include <XM/Method.hpp>
#include <XM/SpecialMembers.hpp>
#include <XM/Template.hpp>
#include <XM/Class.hpp>
#include <XM/CompoundClass.hpp>
#include <XM/PropertyField.hpp>
#include <XM/PropertyArrayField.hpp>
#include <XM/PropertyGetterNSetter.hpp>
#include <XM/Variant.inl>
#include <XM/SpecialMembersImpl.hpp>
#include <XM/ConstantImpl.hpp>
#include <XM/FunctionImpl.hpp>
#include <XM/MethodImpl.hpp>
#include <XM/Register.inl>
#include <XM/Bind.hpp>
#include <XM/RegistrationMacros.hpp>


// Specialize the type recognizer for each primitive type
XM_DECLARE_PRIMITIVE(char);
XM_DECLARE_PRIMITIVE(wchar_t);
XM_DECLARE_PRIMITIVE(short);
XM_DECLARE_PRIMITIVE(int);
XM_DECLARE_PRIMITIVE(long);
XM_DECLARE_PRIMITIVE(float);
XM_DECLARE_PRIMITIVE(double);
XM_DECLARE_PRIMITIVE(uchar);
XM_DECLARE_PRIMITIVE(ushort);
XM_DECLARE_PRIMITIVE(uint);
XM_DECLARE_PRIMITIVE(ulong);
XM_DECLARE_PRIMITIVE(bool);

#endif	/* EXTENDEDMIRROR_HPP */

