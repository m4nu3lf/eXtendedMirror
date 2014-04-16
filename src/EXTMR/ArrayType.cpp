/* 
 * File:   ArrayType.cpp
 * Author: manuele
 * 
 * Created on May 2, 2013, 4:00 PM
 */

#include <EXTMR/ExtendedMirror.hpp>

using namespace extmr;
using namespace std;


ArrayType::ArrayType
(
        const string& name,
        size_t size,
        const type_info& cppType,
        size_t arraySize,
        const Type& elementType = getType<void>()
 )
        : Type(name, size, cppType), arraySize_(arraySize),
        elementType_(&elementType)
{
    
}


Type::Category ArrayType::getCategory() const
{
    return Type::Array;
}


const Type& ArrayType::getArrayElementType() const
{
    return *elementType_;
}


const std::size_t ArrayType::getArraySize() const
{
    return arraySize_;
}


ArrayType::~ArrayType()
{
    
}
