/* 
 * File:   ConstnessBreak.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 22 January 2013, 18.56
 */

#ifndef EXTMR_CONSTNESSBREAK_HPP
#define	EXTMR_CONSTNESSBREAK_HPP

namespace extmr{

class ConstnessBreak : public std::exception
{
public:
    ConstnessBreak(const Type& type) throw();
    const char* what() const throw();
private:
    const Type& type;
};

} // namespace extmr

#endif	/* EXTMR_CONSTNESSBREAK_HPP */

