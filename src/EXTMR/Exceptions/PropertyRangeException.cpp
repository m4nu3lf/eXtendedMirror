/* 
 * File:   PropertyRangeException.cpp
 * Author: Manuele Finocchiaro
 * 
 * Created on 15 January 2013, 18.58
 */

#include <sstream>

#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>
using namespace std;
using namespace extmr;

PropertyRangeException::PropertyRangeException(double givenValue,
                                               double minValue,
                                               double maxValue) throw()
        : givenValue(givenValue)
        , minValue(minValue)
        , maxValue(maxValue)
{
}
const char* PropertyRangeException::what() const throw()
{
    stringstream ss;
    ss << "Given value of " << givenValue 
            << " when expected value into the range from " 
            << minValue << " to " << maxValue << ".";
    return ss.str().c_str(); 
}

