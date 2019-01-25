/*
 *******************************************************************************
 *
 * vdm_components.h
 *
 * Copyright (c) 1999-2017 Redbend. All Rights Reserved.
 *
 *******************************************************************************
 */

/*!
 *******************************************************************************
 * \file	vdm_components.h
 *
 * \brief	Enumeration of all OMA DM Protocol Engine SDK Components
 *
 * When adding a new component to OMA DM Protocol Engine, add an enum value.
 *******************************************************************************
 */

#ifndef VDM_COMPONENTS_H
#define VDM_COMPONENTS_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * OMA DM Protocol Engine components
 */

/*!
 * Component Definitions.
 *
 * \defgroup VDM_componentType Component Definitions
 * @{
 */
typedef enum E_VDM_COMPONENT_TYPE {
	//vDM Framework components (must be first)
	E_VDM_COMPONENT_CLIENT_PL,	///< Client porting layer
	E_VDM_COMPONENT_UTIL,		///< Generic utilities
	E_VDM_COMPONENT_MMI,		///< MMI
	E_VDM_COMPONENT_COMM,		///< Communication
	E_VDM_COMPONENT_HTTP,		///< HTTP Library package
	E_VDM_COMPONENT_SMM,		///< State Machine Manager
	E_VDM_COMPONENT_IPC,		///< SMM IPC
	//vDM Core Engine components
	E_VDM_COMPONENT_CORE,		///< Core component
	E_VDM_COMPONENT_RDM,		///< RDM - General	(was TRACE)
	E_VDM_COMPONENT_RDM_TRG,	///< RDM Trigger (RDM=>DMC) NIA/Bootstrap
	E_VDM_COMPONENT_RDM_SESS,	///< RDM Session Manager
	E_VDM_COMPONENT_RDM_SESSQ,	///< RDM Session Queue
	E_VDM_COMPONENT_RDM_COMM,	///< RDM Session comm	(was: IO)
	E_VDM_COMPONENT_RDM_SYNCML,	///< (was: RTK & XPT)
	E_VDM_COMPONENT_RDM_TREE,	///< RDM Tree
	E_VDM_COMPONENT_RDM_AUTH,	///< RDM Authentication
	E_VDM_COMPONENT_RDM_WBXML,	///< RDM WBXML
	E_VDM_COMPONENT_RDM_DL,		///< RDM Download
	//Packages, extensions and MO components
	E_VDM_COMPONENT_CLIENT,		///< The DM client application
	E_VDM_COMPONENT_FUMO,		///< FUMO component
	E_VDM_COMPONENT_SCOMO,		///< SCOMO component
	E_VDM_COMPONENT_BOOTSTRAP,	///< Bootstrap extension
	E_VDM_COMPONENT_CONNMO,		///< ConnMO component
	E_VDM_COMPONENT_LAWMO,		///< LAWMO component
	E_VDM_COMPONENT_SWMC,		///< SWM Client
	E_VDM_COMPONENT_DESCMO,		///< Dev Settings Configuration MO
	E_VDM_COMPONENT_XML,		///< XML package
	E_VDM_COMPONENT_CSV, 		///< CSV package
	E_VDM_COMPONENT_PACK,       ///< PACK package
	E_VDM_COMPONENT_DP_ACCESS, 	///< DP ACCESS package
    ECU_CLIENT,                 ///< The ECU client application
	// Add new components here.  <<============
	E_VDM_COMPONENT_RDM_TEMP,	///< Internal
	E_VDM_COMPONENT_COUNT		///< Must be last
} E_VDM_COMPONENT_TYPE;

const char *GetStringE_VDM_COMPONENT_TYPE(E_VDM_COMPONENT_TYPE index);

/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif //VDM_COMPONENTS_H

