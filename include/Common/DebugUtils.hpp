/* 
 * File:   DebugUtils.hpp
 * Author: Manuele Finocchiaro
 *
 * Created on 11 August 2012, 18.06
 */

#ifndef DEBUGUTILS_HPP
#define	DEBUGUTILS_HPP

#ifdef DEBUG
#define DEBUG_MSG(msg) std::cout << "debug: " << msg << std::endl;
#else
#define DEBUG_MSG(msg)
#endif

#endif	/* DEBUGUTILS_HPP */

