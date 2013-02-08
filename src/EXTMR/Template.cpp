/* 
 * File:   Template.cpp
 * Author: Manuele Finocchiaro
 * 
 * Created on 2 January 2013, 13.23
 */

#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;
using namespace extmr;

Template::Template(const string& name, uint argN) :
        name(name), argN(argN)
{
}

const std::string& Template::getName() const
{
    return name;
}

uint Template::getArgN() const
{
    return argN;
}

