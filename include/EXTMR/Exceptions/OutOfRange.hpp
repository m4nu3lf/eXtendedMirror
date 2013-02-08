/* 
 * File:   OutOfRange.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 15 January 2013, 18.58
 */

#ifndef EXTMR_OUTOFRANGE_HPP
#define	EXTMR_OUTOFRANGE_HPP

namespace extmr{

class OutOfRange : public std::exception
{
public:
    OutOfRange(double minValue, double maxValue, double givenValue) throw();
    const char* what() const throw();
private:
    double givenValue;
    double minValue;
    double maxValue;
};

} // namespace extmr

#endif	/* EXTMR_OUTOFRANGE_HPP */

