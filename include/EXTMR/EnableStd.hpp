/* 
 * File:   EnableStd.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 1 January 2013, 20.43
 */

#ifndef EXTMR_ENABLESTD_HPP
#define	EXTMR_ENABLESTD_HPP

EXTMR_ENABLE_N_BUILD_TCLASS_1(std::allocator){}
EXTMR_ENABLE_N_BUILD_TCLASS_1(std::char_traits){}  
EXTMR_ENABLE_N_BUILD_TCLASS_1(std::equal_to){}
EXTMR_ENABLE_N_BUILD_TCLASS_1(std::not_equal_to){}
EXTMR_ENABLE_N_BUILD_TCLASS_1(std::less){}
EXTMR_ENABLE_N_BUILD_TCLASS_1(std::less_equal){}
EXTMR_ENABLE_N_BUILD_TCLASS_1(std::greater){}
EXTMR_ENABLE_N_BUILD_TCLASS_1(std::greater_equal){}
EXTMR_ENABLE_N_BUILD_TCLASS_2(std::vector){}
EXTMR_ENABLE_N_BUILD_TCLASS_3(std::basic_string){}
EXTMR_ENABLE_N_BUILD_TCLASS_3(std::set){}
EXTMR_ENABLE_N_BUILD_TCLASS_4(std::map){}
        
#endif	/* EXTMR_ENABLESTD_HPP */

