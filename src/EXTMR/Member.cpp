/* 
 * File:   Member.cpp
 * Author: Manuele Finocchiaro
 * 
 * Created on April 27, 2013, 4:40 PM
 */

#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

Member::Member(const Class& owner, const string& name) :
        owner_(&owner), name_(name)
{
}


const string& Member::getName() const
{
    return name_;
}


const Class& Member::getOwner() const
{
    return *owner_;
}


Member::~Member()
{
}

