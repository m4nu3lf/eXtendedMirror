/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef EXTMR_ENABLESTD_HPP
#define	EXTMR_ENABLESTD_HPP

EXTMR_ENABLE_TEMPLATE_1(std::allocator)
template<typename T>
EXTMR_BUILD_CLASS(std::allocator<T>){}


EXTMR_ENABLE_TEMPLATE_1(std::char_traits)
template<typename T>
EXTMR_BUILD_CLASS(std::char_traits<T>){}


EXTMR_ENABLE_TEMPLATE_1(std::equal_to)
template<typename T>
EXTMR_BUILD_CLASS(std::equal_to<T>){}


EXTMR_ENABLE_TEMPLATE_1(std::not_equal_to)
template<typename T>
EXTMR_BUILD_CLASS(std::not_equal_to<T>){}


EXTMR_ENABLE_TEMPLATE_1(std::less)
template<typename T>
EXTMR_BUILD_CLASS(std::less<T>){}


EXTMR_ENABLE_TEMPLATE_1(std::less_equal)
template<typename T>
EXTMR_BUILD_CLASS(std::less_equal<T>){}


EXTMR_ENABLE_TEMPLATE_1(std::greater)
template<typename T>
EXTMR_BUILD_CLASS(std::greater<T>){}


EXTMR_ENABLE_TEMPLATE_1(std::greater_equal)
template<typename T>
EXTMR_BUILD_CLASS(std::greater_equal<T>){}


EXTMR_ENABLE_TEMPLATE_2(std::vector)
template<typename T, typename Allocator>
EXTMR_BUILD_CLASS(std::vector<T, Allocator>){}


EXTMR_ENABLE_TEMPLATE_3(std::basic_string)
template<typename CharT, typename Traits, typename Allocator>
EXTMR_BUILD_CLASS(std::basic_string<CharT, Traits, Allocator>){}


EXTMR_ENABLE_TEMPLATE_3(std::set)
template<typename Key, typename Compare, typename Allocator>
EXTMR_BUILD_CLASS(std::set<Key, Compare, Allocator>){}


EXTMR_ENABLE_TEMPLATE_4(std::map)
template<typename Key, typename T, typename Compare, typename Allocator>
EXTMR_BUILD_CLASS(std::map<Key, T, Compare, Allocator>){}
        
#endif	/* EXTMR_ENABLESTD_HPP */

