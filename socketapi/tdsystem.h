/*
 *  $Id: tdsystem.h,v 1.5 2003/08/02 20:31:57 tuexen Exp $
 *
 * SCTP implementation according to RFC 2960.
 * Copyright (C) 1999-2002 by Thomas Dreibholz
 *
 * Realized in co-operation between Siemens AG
 * and University of Essen, Institute of Computer Networking Technology.
 *
 * Acknowledgement
 * This work was partially funded by the Bundesministerium für Bildung und
 * Forschung (BMBF) of the Federal Republic of Germany (Förderkennzeichen 01AK045).
 * The authors alone are responsible for the contents.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * There are two mailinglists available at http://www.sctp.de which should be
 * used for any discussion related to this implementation.
 *
 * Contact: discussion@sctp.de
 *          dreibh@exp-math.uni-essen.de
 *
 * Purpose: System dependent definitions
 *
 */


#ifndef TDSYSTEM_H
#define TDSYSTEM_H

#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif


// Use TransportInfo
#define USE_TRANSPORTINFO

// Use traffic shaper
// #define USE_TRAFFICSHAPER


// Disable all warning outputs. Not recommended!
// #define DISABLE_WARNINGS


// Some important definitions for usage of reentrant versions.
#ifndef _REENTRANT
 #define _REENTRANT
#endif
#ifndef _THREAD_SAFE
 #define _THREAD_SAFE
#endif

#ifndef _GNU_SOURCE
 #define _GNU_SOURCE
#endif
#ifndef USE_PTHREADS
 #define USE_PTHREADS
#endif


// Use libefence for debugging
// #define USE_EFENCE


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <iostream>


// gcc3.1 and new STL define all standard functions in namespace std!
using namespace std;


// In socket.cc: CMSG_NXTHDR: (__cmsg_nxthdr) is not found,
// if compiled with -O0 -> extern inline definition required.
#if !defined __USE_EXTERN_INLINES
 #define __USE_EXTERN_INLINES 1
#endif

#ifndef HAVE_SOCKLEN_T
 typedef int socklen_t;
 #define HAVE_SOCKLEN_T
#endif

#ifndef max
 #define max(a, b) ((a) < (b) ? (b) : (a))
#endif
#ifndef min
 #define min(a, b) ((a) > (b) ? (b) : (a))
#endif


// ###### Operating system definitions ######################################
#define OS_Linux   1
#define OS_FreeBSD 2
#define OS_Darwin  3
#define OS_SOLARIS 4

#ifdef LINUX
 #define SYSTEM OS_Linux
#endif
#ifdef FreeBSD
 #define SYSTEM OS_FreeBSD
#endif
#ifdef DARWIN
 #define SYSTEM OS_Darwin
 #define MAXDNAME 256
#endif
#ifdef SOLARIS
 #define SYSTEM OS_SOLARIS
#endif

#ifndef SYSTEM
 #warning Variable SYSTEM with operating system name not defined! Use e.g. -DOS_Linux compiler option.
 #warning Trying Linux...
 #define SYSTEM OS_Linux
#endif


// ###### CPU defintions ####################################################
// Set correct number of CPU bits (32 or 64) here!
#if (SYSTEM == OS_Linux)
 #include <endian.h>
 #include <stdint.h>
#elif (SYSTEM == OS_FreeBSD)
 #include <machine/endian.h>
 #include <sys/inttypes.h>
#elif (SYSTEM == OS_Darwin)
 #include <machine/endian.h>
 #include <stdint.h>
#elif (SYSTEM == OS_SOLARIS)
 #include <inttypes.h>
 #include <arpa/nameser_compat.h>
#endif


// ###### sctplib versions ###################################################
//#include <sctp.h>
//#define SCTPLIB_VERSION ((SCTP_MAJOR_VERSION << 16) | SCTP_MINOR_VERSION)
//#define SCTPLIB_1_0_0_PRE19 19
//#define SCTPLIB_1_0_0_PRE20 20
//#define SCTPLIB_1_0_0       0x10000


// ###### Type definitions ##################################################
/**
  * Datatype for storing a signed char.
  */
typedef int8_t sbyte;

/**
  * Datatype for storing an unsigned char.
  */
typedef uint8_t ubyte;

/**
  * Datatype for storing an 8-bit integer.
  */
typedef int8_t int8;

/**
  * Datatype for storing a 8-bit cardinal.
  */
typedef uint8_t card8;

/**
  * Datatype for storing a 16-bit integer.
  */
typedef int16_t int16;

/**
  * Datatype for storing a 16-bit cardinal.
  */
typedef uint16_t card16;

/**
  * Datatype for storing a 32-bit intger.
  */
typedef int32_t int32;

/**
  * Datatype for storing a default-sized integer (32 bits minimum).
  */
#if defined (int_least32_t)
typedef int_least32_t integer;
#else
typedef int32 integer;
#endif

/**
  * Datatype for storing a 32-bit cardinal.
  */
typedef uint32_t card32;

/**
  * Datatype for storing an 64-bit integer.
  */
typedef int64_t int64;

/**
  * Datatype for storing a 64-bit cardinal.
  */
typedef uint64_t card64;

/**
  * Datatype for storing a default-sized cardinal (32 bits minimum).
  */
#if defined (uint_least32_t)
typedef uint_least32_t cardinal;
#else
typedef card32 cardinal;
#endif


#ifdef DMALLOC
#define USE_DMALLOC
#include <dmalloc.h>
#endif


// Include tools.h with libefence replacement for new and delete.
#include "tools.h"


#endif
