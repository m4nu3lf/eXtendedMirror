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

#include <Common/Common.hpp>
#include <EXTMR/TypeTraits.hpp>
#include <EXTMR/Misc.hpp>
#include <EXTMR/Property.hpp>
#include <EXTMR/Variant.hpp>
#include <EXTMR/Method.hpp>
#include <EXTMR/Type.hpp>
#include <EXTMR/Template.hpp>
#include <EXTMR/Class.hpp>
#include <EXTMR/TypeRegister.hpp>
#include <EXTMR/Registration.hpp>
#include <EXTMR/TypeRecognition.hpp>
#include <EXTMR/PropertyField.hpp>
#include <EXTMR/PropertyArrayField.hpp>
#include <EXTMR/PropertyGetterNSetter.hpp>
#include <EXTMR/Variant.inl>
#include <EXTMR/MethodImpl.hpp>
#include <EXTMR/TypeRegister.inl>
#include <EXTMR/MemberBuildUtils.hpp>
#include <EXTMR/Macros.hpp>

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

