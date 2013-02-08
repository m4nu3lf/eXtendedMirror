/* 
 * File:   ConstnessBreak.cpp
 * Author: Manuele Finocchiaro
 * 
 * Created on 22 January 2013, 18.56
 */

#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace extmr;
using namespace std;

ConstnessBreak::ConstnessBreak(const Type& type) throw()
        : type(type)
{
}

const char* ConstnessBreak::what() const throw()
{
    return (string("Cannot convert to type ")
            + type.getName()
            + " from type const "
            + type.getName() + ".").c_str();
}
