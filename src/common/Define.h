/*
 * This file is part of the FirelandsCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FIRELANDS_DEFINE_H
#define FIRELANDS_DEFINE_H

#include "CompilerDefs.h"

#if FC_COMPILER == FC_COMPILER_GNU
#  if !defined(__STDC_FORMAT_MACROS)
#    define __STDC_FORMAT_MACROS
#  endif
#  if !defined(__STDC_CONSTANT_MACROS)
#    define __STDC_CONSTANT_MACROS
#  endif
#  if !defined(_GLIBCXX_USE_NANOSLEEP)
#    define _GLIBCXX_USE_NANOSLEEP
#  endif
#  if defined(HELGRIND)
#    include <valgrind/helgrind.h>
#    undef _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE
#    undef _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER
#    define _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(A) ANNOTATE_HAPPENS_BEFORE(A)
#    define _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(A)  ANNOTATE_HAPPENS_AFTER(A)
#  endif
#endif

#include <cstddef>
#include <cinttypes>
#include <climits>

#define FIRELANDS_LITTLEENDIAN 0
#define FIRELANDS_BIGENDIAN    1

#if !defined(FIRELANDS_ENDIAN)
#  if defined (BOOST_BIG_ENDIAN)
#    define FIRELANDS_ENDIAN FIRELANDS_BIGENDIAN
#  else
#    define FIRELANDS_ENDIAN FIRELANDS_LITTLEENDIAN
#  endif
#endif

#if FC_PLATFORM == FC_PLATFORM_WINDOWS
#  define FIRELANDS_PATH_MAX 260
#  define _USE_MATH_DEFINES
#  ifndef DECLSPEC_NORETURN
#    define DECLSPEC_NORETURN __declspec(noreturn)
#  endif //DECLSPEC_NORETURN
#  ifndef DECLSPEC_DEPRECATED
#    define DECLSPEC_DEPRECATED __declspec(deprecated)
#  endif //DECLSPEC_DEPRECATED
#else // FC_PLATFORM != FC_PLATFORM_WINDOWS
#  define FIRELANDS_PATH_MAX PATH_MAX
#  define DECLSPEC_NORETURN
#  define DECLSPEC_DEPRECATED
#endif // FC_PLATFORM

#if !defined(COREDEBUG)
#  define FIRELANDS_INLINE inline
#else //COREDEBUG
#  if !defined(FC_DEBUG)
#    define FC_DEBUG
#  endif //FC_DEBUG
#  define FIRELANDS_INLINE
#endif //!COREDEBUG

#if FC_COMPILER == FC_COMPILER_GNU
#  define ATTR_NORETURN __attribute__((__noreturn__))
#  define ATTR_PRINTF(F, V) __attribute__ ((__format__ (__printf__, F, V)))
#  define ATTR_DEPRECATED __attribute__((__deprecated__))
#else //FC_COMPILER != FC_COMPILER_GNU
#  define ATTR_NORETURN
#  define ATTR_PRINTF(F, V)
#  define ATTR_DEPRECATED
#endif //FC_COMPILER == FC_COMPILER_GNU

#ifdef FIRELANDS_API_USE_DYNAMIC_LINKING
#  if FC_COMPILER == FC_COMPILER_MICROSOFT
#    define FC_API_EXPORT __declspec(dllexport)
#    define FC_API_IMPORT __declspec(dllimport)
#  elif FC_COMPILER == FC_COMPILER_GNU
#    define FC_API_EXPORT __attribute__((visibility("default")))
#    define FC_API_IMPORT
#  else
#    error compiler not supported!
#  endif
#else
#  define FC_API_EXPORT
#  define FC_API_IMPORT
#endif

#ifdef FIRELANDS_API_EXPORT_COMMON
#  define FC_COMMON_API FC_API_EXPORT
#else
#  define FC_COMMON_API FC_API_IMPORT
#endif

#ifdef FIRELANDS_API_EXPORT_DATABASE
#  define FC_DATABASE_API FC_API_EXPORT
#else
#  define FC_DATABASE_API FC_API_IMPORT
#endif

#ifdef FIRELANDS_API_EXPORT_SHARED
#  define FC_SHARED_API FC_API_EXPORT
#else
#  define FC_SHARED_API FC_API_IMPORT
#endif

#ifdef FIRELANDS_API_EXPORT_IPC
#  define FC_IPC_API FC_API_EXPORT
#else
#  define FC_IPC_API FC_API_IMPORT
#endif

#ifdef FIRELANDS_API_EXPORT_GAME
#  define FC_GAME_API FC_API_EXPORT
#else
#  define FC_GAME_API FC_API_IMPORT
#endif

#define UI64FMTD "%" PRIu64
#define UI64LIT(N) UINT64_C(N)

#define SI64FMTD "%" PRId64
#define SI64LIT(N) INT64_C(N)

#define SZFMTD "%" PRIuPTR

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

enum DBCFormer
{
    FT_NA = 'x',                                            //not used or unknown, 4 byte size
    FT_NA_BYTE = 'X',                                       //not used or unknown, byte
    FT_STRING = 's',                                        //char*
    FT_FLOAT = 'f',                                         //float
    FT_INT = 'i',                                           //uint32
    FT_BYTE = 'b',                                          //uint8
    FT_LONG = 'l',                                          //uint64
    FT_SORT = 'd',                                          //sorted by this field, field is not included
    FT_IND = 'n',                                           //the same, but parsed to data
    FT_SQL_PRESENT = 'p',                                   //Used in sql format to mark column present in sql dbc
    FT_SQL_ABSENT = 'a'                                     //Used in sql format to mark column absent in sql dbc
};

#endif //FIRELANDS_DEFINE_H
