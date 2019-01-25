/*
 *******************************************************************************
 *
 * vdm_pl_types.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_pl_types.h
 *
 * \brief	OMA DM Protocol Engine Standard Types and Macros
 *
 * OMA DM Protocol Engine uses platform-independent versions of C built-in types and
 * defines to ensure portability. When implementing the Porting Layer code, do
 * not use C built-in types directly; always use these types.
 *
 * The following types and defines apply to most platforms. Specific definitions
 * may vary for some platforms. For example, on some platforms, <b>int</b> may
 * be defined as <b>IS16</b> rather than <b>IS32</b>. If the definitions do not
 * match your architecture, contact Red Bend Software and request a special
 * version of the Framework to match your platform data types.
 *******************************************************************************
 */


#ifndef VDM_PL_TYPES_H__
#define VDM_PL_TYPES_H__		//!< Internal

/*!
 * @defgroup pl	Porting Layer API
 * Porting Layer APIs
 *
 * @defgroup  pl_system	System
 * @ingroup pl
 */

/*! The handle returned by different objects of the framework */
typedef void *VDM_Handle_t;

/* Is target platform a 64 bit platform */
/* TODO move to SBuild define, and define per platform, instead of detecting */
#if (defined _WIN64) || (defined __amd64__)
#define VDM_X64             //!< 64 bit processor
#else
#define VDM_X32             //!< 32 bit processor
#endif

/*!
 * The following are standard OMA DM Protocol Engine types potentially requiring
 * definitions dependent on the toolset being used to compile the source.
 * The following definitions should work on most modern 32-bit compilers.
 */

#ifndef IS64_DEFINED
#define IS64_DEFINED                    //!< Internal
typedef long long int IS64;             /*!< 64bit integer */
#endif
#ifndef IU64_DEFINED
#define IU64_DEFINED                    //!< Internal
typedef unsigned long long int IU64;    /*!< 64bit integer (unsigned) */
#endif

#ifndef IS32_DEFINED
#define IS32_DEFINED                //!< Internal
typedef long IS32;                  /*!< 32bit integer */
#endif
#ifndef IU32_DEFINED
#define IU32_DEFINED                //!< Internal
typedef unsigned long IU32;         /*!< 32bit integer (unsigned) */
#endif
#ifndef INTU_DEFINED
#define INTU_DEFINED                //!< Internal
typedef unsigned int IU4BY;         /*!< integer (unsigned) */
#endif
#ifndef IS16_DEFINED
#define IS16_DEFINED                //!< Internal
typedef short IS16;                 /*!< 16bit integer */
#endif
#ifndef IU16_DEFINED
#define IU16_DEFINED                //!< Internal
typedef unsigned short IU16;        /*!< 16bit integer (unsigned) */
#endif
#ifndef IS8_DEFINED
#define IS8_DEFINED                 //!< Internal
typedef signed char IS8;            /*!< 8bit integer */
#endif
#ifndef IU8_DEFINED
#define IU8_DEFINED                 //!< Internal
typedef unsigned char IU8;          /*!< 8bit integer (unsigned) */
#endif

#ifndef TIME_T_DEFINED
#define TIME_T_DEFINED              //!< Internal
#ifdef VDM_X64
typedef IU64 TIME_T;                //!< Time on a 64 bit computer
#else
typedef IU32 TIME_T;                //!< Time on a 32 bit computer
#endif
#endif

#ifndef VDM_PRIORITY_DEFINED
#define VDM_PRIORITY_DEFINED        //!< Internal
typedef TIME_T VDM_PRIORITY_T;      //!< Time, referenced by the priority queue
#endif

/*!
 * <b>IBOOL</b> must be at least as wide as the larger of <b>int</b> (the
 * compiler's natural implicit Boolean type), <b>Ix32</b>,
 * to allow bit-wise operations on any OMA DM Protocol Engine type to be stored in an
 * <b>IBOOL</b> without loss of information.
 */
#ifndef IBOOL_DEFINED
#define IBOOL_DEFINED               //!< Internal
typedef IS32 IBOOL;                 /*!< Boolean type */
#endif

/*! UTF8-encoded Unicode strings, NULL-terminated */
#ifndef UTF8Str_DEFINED
#define UTF8Str_DEFINED             //!< Internal
typedef IU8             *UTF8Str;   /*!< UTF8 encoded Unicode string, NULL-terminated */
#endif
#ifndef UTF8CStr_DEFINED
#define UTF8CStr_DEFINED            //!< Internal
typedef const IU8       *UTF8CStr;  /*!< UTF8 encoded Unicode string constant, NULL-terminated */
#endif

/*! An integer that represents an array of bit flags */
#ifndef IBITFLAGS_DEFINED
#define IBITFLAGS_DEFINED           //!< Internal
typedef IU32 IBITFLAGS;             /*!< An integer representing an array of bit flags */
#endif

/*! True */
#ifndef TRUE
#define TRUE    1
#endif
/*! False */
#ifndef FALSE
#define FALSE   0
#endif

/*! Replacement for NULL when <b>\<stdio.h\></b> is not wanted */
#ifndef NULL
  #ifdef __cplusplus
	#define NULL    0
  #else
	#define NULL    ((void *)0)
  #endif
#endif

/** @defgroup pl_macros Useful Macros
 *  @ingroup pl
 *	@{
 */

/*! Macro to remove warnings relating to unused function arguments */
#ifndef UNUSED
#define UNUSED(x)	do { (void)(x); } while (0)
#endif

#ifndef ALL_UNUSED
#define UNUSED1(a)                  (void)(a)
#define UNUSED2(a,b)                (void)(a),UNUSED1(b)
#define UNUSED3(a,b,c)              (void)(a),UNUSED2(b,c)
#define UNUSED4(a,b,c,d)            (void)(a),UNUSED3(b,c,d)
#define UNUSED5(a,b,c,d,e)          (void)(a),UNUSED4(b,c,d,e)
#define UNUSED6(a,b,c,d,e,f)        (void)(a),UNUSED5(b,c,d,e,f)

#define VA_NUM_ARGS_IMPL(_1,_2,_3,_4,_5, N,...) N
#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__, 5, 4, 3, 2, 1)

#define ALL_UNUSED_IMPL_(nargs) UNUSED ## nargs
#define ALL_UNUSED_IMPL(nargs) ALL_UNUSED_IMPL_(nargs)
#define ALL_UNUSED(...) ALL_UNUSED_IMPL( VA_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__ )
#endif

/*! Macro for min */
#ifndef min
#define min(a, b)    (((a) > (b)) ? (b) : (a))
#endif
/*! Macro for max */
#ifndef max
#define max(a, b)    (((a) < (b)) ? (b) : (a))
#endif

/*! Maximum value for a signed 16-bit integer */
#ifndef MAX_IS16
#define MAX_IS16    0x7FFF
#endif

/*! Maximum value for a signed 32-bit integer */
#ifndef MAX_IS32
#define MAX_IS32    0x7FFFFFFF
#endif
/*! Maximum value for an unsigned 32-bit integer */
#ifndef MAX_IU32
#define MAX_IU32    0xFFFFFFFF
#endif
/*! Maximum value for an unsigned 64-bit integer */
#ifndef MAX_IU64
#define MAX_IU64    0xFFFFFFFFFFFFFFFFull
#endif
/*! Maximum value for an unsigned integer (platform dependent) */
#ifndef MAX_UINT
#ifdef VDM_X64
#define MAX_UINT    MAX_IU64
#else
#define MAX_UINT    MAX_IU32
#endif
#endif

/** Compare pointers */
#define PTR_DIFF(p1, p2) ((IU32)((p1) - (p2)))

/*! Table size */
#define TABLE_SIZE(table)	(sizeof(table)/sizeof((table)[0]))
/*! Boolean equivalence */
#define EQUAL_BOOLEANS(b1, b2)  ((!(b1)) == (!(b2)))

/*! @} */
#ifdef UTEST
	#define STATIC
#else
	#define STATIC static
#endif

#endif

