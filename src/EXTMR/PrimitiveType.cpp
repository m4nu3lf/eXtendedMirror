/* 
 * File:   PrimitiveType.cpp
 * Author: manuele
 * 
 * Created on May 2, 2013, 4:02 PM
 */

#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

PrimitiveType::PrimitiveType(const string& name, size_t size, 
        const type_info& cppType): 
    Type(name, size, cppType)
{
    
}


Type::Category PrimitiveType::getCategory() const
{
    return Type::Primitive;
}


PrimitiveType::~PrimitiveType()
{
    
}

