/* 
 * File:   ExtendedMirror.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on October 30, 2012, 17.38
 */

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



#include <Common/Common.hpp>
namespace extmr {
DEFINE_POINTER_COMPARER_BY_METHOD(getName, PtrCmpByName)
};

        
#include <EXTMR/TypeTraits.hpp>
#include <EXTMR/Empty.hpp>
#include <EXTMR/Variant.hpp>
#include <EXTMR/MemberWrappers.hpp>
#include <EXTMR/Type.hpp>
#include <EXTMR/PrimitiveType.hpp>
#include <EXTMR/PointerType.hpp>
#include <EXTMR/ArrayType.hpp>
#include <EXTMR/Member.hpp>
#include <EXTMR/Property.hpp>
#include <EXTMR/Method.hpp>
#include <EXTMR/Template.hpp>
#include <EXTMR/Class.hpp>
#include <EXTMR/CompoundClass.hpp>
#include <EXTMR/TypeRegister.hpp>
#include <EXTMR/Registration.hpp>
#include <EXTMR/TypeRecognition.hpp>
#include <EXTMR/PropertyField.hpp>
#include <EXTMR/PropertyArrayField.hpp>
#include <EXTMR/PropertyGetterNSetter.hpp>
#include <EXTMR/Variant.inl>
#include <EXTMR/MethodImpl.hpp>
#include <EXTMR/TypeRegister.inl>
#include <EXTMR/MemberMakeUtils.hpp>
#include <EXTMR/RegistrationMacros.hpp>
#include <EXTMR/Shortcuts.hpp>


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

