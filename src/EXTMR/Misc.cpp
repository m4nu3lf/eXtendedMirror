/* 
 * File:   Misc.cpp
 * Author: Manuele Finocchiaro
 *
 * Created on 23 January 2013, 13.19
 */

#include <string>
#include <EXTMR/ExtendedMirror.hpp>

using namespace std;

namespace extmr{

string getNonQualifiedName(const string& name)
{
    size_t pos = name.find_last_of(':');
    pos ++;
    return name.substr(pos, name.size() - pos);
    return name;
}

} // namespace extmr