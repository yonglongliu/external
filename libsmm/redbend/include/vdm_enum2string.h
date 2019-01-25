/*
 *******************************************************************************
 *
 * vdm_enum2string.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_enum2string.h
 *
 * \brief	Utility for converting enum to string
 *******************************************************************************
 */

/// @cond EXCLUDE

#ifdef __cplusplus
extern "C" {
#endif

#undef DECL_ENUM_ELEMENT
#undef DECL_ENUM_ELEMENT_VAL
#undef DECL_ENUM_ELEMENT_STR
#undef DECL_ENUM_ELEMENT_VAL_STR
#undef BEGIN_ENUM
#undef END_ENUM
#undef DECL_ENUM_ELEMENT_PRE
#undef DECL_ENUM_ELEMENT_VAL_PRE
#undef DECL_ENUM_ELEMENT_STR_PRE
#undef DECL_ENUM_ELEMENT_VAL_STR_PRE
#undef BEGIN_ENUM_PRE
#undef END_ENUM_PRE

#ifndef GENERATE_ENUM_STRINGS
//declare enum
	#define BEGIN_ENUM( ENUM_NAME ) typedef enum tag ## ENUM_NAME {
	#define DECL_ENUM_ELEMENT( element ) element,
	#define DECL_ENUM_ELEMENT_VAL( element, value ) element = value,
	#define DECL_ENUM_ELEMENT_STR( element, descr ) DECL_ENUM_ELEMENT( element )
	#define DECL_ENUM_ELEMENT_VAL_STR( element, value, descr ) DECL_ENUM_ELEMENT_VAL( element, value )
	#define END_ENUM( ENUM_NAME ) } ENUM_NAME; \
	const char *GetString ## ENUM_NAME(enum tag ## ENUM_NAME index);
#else
//generate enum strings
	#define BEGIN_ENUM( ENUM_NAME) const char *GetString ## ENUM_NAME( enum tag ## ENUM_NAME index ) { \
		switch (index) {
	#define DECL_ENUM_ELEMENT( element ) case element: return #element; break;
	#define DECL_ENUM_ELEMENT_VAL( element, value ) DECL_ENUM_ELEMENT( element )
	#define DECL_ENUM_ELEMENT_STR( element, descr ) case element: return descr; break;
	#define DECL_ENUM_ELEMENT_VAL_STR( element, value, descr ) DECL_ENUM_ELEMENT_STR( element, descr )

	#define END_ENUM( ENUM_NAME ) default: return "Unknown value"; }}

#endif

#ifdef ENUM_PREFIX
	#define DECL_ENUM_ELEMENT_STR_P(prefix, element, descr) DECL_ENUM_ELEMENT_STR(prefix ## _ ## element, descr)
	#define BEGIN_ENUM_P(prefix)                            BEGIN_ENUM(prefix ## _t)
	#define END_ENUM_P(prefix)                              END_ENUM(prefix ## _t)

	#define DECL_ENUM_ELEMENT_STR_PR(prefix, element, descr) DECL_ENUM_ELEMENT_STR_P(prefix, element, descr)
	#define BEGIN_ENUM_PR(prefix)                           BEGIN_ENUM_P(prefix)
	#define END_ENUM_PR(prefix)                             END_ENUM_P(prefix)

	#define DECL_ENUM_ELEMENT_PRE(element)                  DECL_ENUM_ELEMENT_STR_PR(ENUM_PREFIX, element,#element)
	#define DECL_ENUM_ELEMENT_STR_PRE(element, descr)       DECL_ENUM_ELEMENT_STR_PR(ENUM_PREFIX, element, descr)
	#define BEGIN_ENUM_PRE                                  BEGIN_ENUM_PR(ENUM_PREFIX)
	#define END_ENUM_PRE                                    DECL_ENUM_ELEMENT_PRE(count) \
	END_ENUM_PR(ENUM_PREFIX)
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

/// @endcond
