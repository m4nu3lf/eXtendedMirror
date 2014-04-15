/* 
 * File:   RefCaster.cpp
 * Author: Manuele Finocchiaro
 * 
 * Created on April 27, 2013, 4:40 PM
 */

#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

RefCaster::RefCaster(const Type& srcType, const Type& dstType) :
        srcType_(&srcType), dstType_(&dstType)
{
}


RefCaster::RefCaster(std::pair<const Type*, const Type*> srcNdstTypes) :
        srcType_(srcNdstTypes.first), dstType_(srcNdstTypes.second)
{
}


const Type& RefCaster::getSrcType() const
{
    return *srcType_;
}


const Type& RefCaster::getDstType() const
{
    return *dstType_;
}


RefVariant RefCaster::cast(const Variant& var) const
{
	return var;
}


RefCaster::~RefCaster()
{
}