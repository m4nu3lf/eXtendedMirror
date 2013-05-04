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

Member::Member(const string& name) : name_(name), owner_(&Class::Void)
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

