/*
 * Extended Mirror
 * 
 * Copyright (c) 2012-2013 Manuele Finocchiaro (m4nu3lf@gmail.com)
 * 
 */

#ifndef DEBUGUTILS_HPP
#define	DEBUGUTILS_HPP

#ifdef DEBUG
#define DEBUG_MSG(msg) std::cout << "debug: " << msg << std::endl;
#else
#define DEBUG_MSG(msg)
#endif

#endif	/* DEBUGUTILS_HPP */

