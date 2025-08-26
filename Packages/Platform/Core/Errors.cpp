// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace platform
	{
		// General
		const ErrorInfo ERROR_GENERAL_UNKNOWN									{    1, L"Unknown error" };
		const ErrorInfo ERROR_GENERAL_INVALID_HANDLE							{    2, L"Invalid handle" };
		const ErrorInfo ERROR_GENERAL_INVALID_SENDER							{    3, L"Sender type is expected to be '{type}'" };
		const ErrorInfo ERROR_GENERAL_NOT_FOUND									{    4, L"Object isn't found" };

		// OpenGL
		const ErrorInfo ERROR_OPENGL_CALL_FAILED								{ 1001, L"Call of OpenGL function {name}() is failed with error code {code}" };
		const ErrorInfo ERROR_OPENGL_COMPILE_SHADER								{ 1002, L"Compilation of shader has failed with following errors:\n{log}" };
		const ErrorInfo ERROR_OPENGL_LINK_PROGRAM								{ 1003, L"Linking of program has failed with following errors:\n{log}" };
		const ErrorInfo ERROR_OPENGL_LOAD										{ 1004, L"Cannot load OpenGL" };

		// Renderer
		const ErrorInfo ERROR_RENDERER_OPENGL_VERSION							{ 2001, L"Detected version {major}.{minor} of OpenGL is too low. Minimum supported is 3.0" };
		const ErrorInfo ERROR_RENDERER_REQUESTED_MAX_VERSION					{ 2002, L"Requested maximum version {major}.{minor} is too low. Minimum supported is 3.0" };
		const ErrorInfo ERROR_RENDERER_GET_WINDOW_DEVICE_CONTEXT				{ 2003, L"Cannot get windows device context for provided window" };
		const ErrorInfo ERROR_RENDERER_CREATE_COMPATIBLE_DEVICE_CONTEXT			{ 2004, L"Cannot create compatible device context for provided window" };
		const ErrorInfo ERROR_RENDERER_CREATE_OPENGL							{ 2005, L"Cannot create OpenGL graphics object" };
		const ErrorInfo ERROR_RENDERER_OPENGL_VERSION_TOO_LOW					{ 2006, L"OpenGL version is too low to be used with the renderer" };
		const ErrorInfo ERROR_RENDERER_WGL_CHOOSE_PIXEL_FORMAT_ARB_UNDEFINED	{ 2007, L"wglChoosePixelFormatARB function does not exist" };
		const ErrorInfo ERROR_RENDERER_WGL_CREATE_CONTENT_ATTRIBS_ARB_UNDEFINED	{ 2008, L"wglCreateContextAttribsARB function does not exist" };
		const ErrorInfo ERROR_RENDERER_FIND_PIXEL_FORMAT						{ 2009, L"Cannot find agreeable pixel format" };
		const ErrorInfo ERROR_RENDERER_SET_PIXEL_FORMAT							{ 2010, L"Cannot apply found pixel format" };
		const ErrorInfo ERROR_RENDERER_CREATE_CONTEXT							{ 2011, L"Cannot create OpenGL context" };
		const ErrorInfo ERROR_RENDERER_ACTIVATE_CONTEXT							{ 2012, L"Cannot activate OpenGL context" };
		const ErrorInfo ERROR_RENDERER_CREATE_DEFAULT_VERTEX_ARRAY				{ 2013, L"Cannot create default vertex array" };
		const ErrorInfo ERROR_RENDERER_CREATE_GRADIENT_TEXTURES					{ 2014, L"Cannot create default vertex array" };
		const ErrorInfo ERROR_RENDERER_CREATE_MAIN_PROGRAM						{ 2015, L"Cannot create main program" };
		const ErrorInfo ERROR_RENDERER_CREATE_DEFAULT_FRAMEBUFFER				{ 2016, L"Cannot create default framebuffer" };
		const ErrorInfo ERROR_RENDERER_WINDOW_NOT_CREATED						{ 2017, L"Platform window is not created" };
		const ErrorInfo ERROR_RENDERER_MASK_WITH_CUSTOM_PROGRAM					{ 2018, L"Mask cannot be used with custom program activated" };
		const ErrorInfo ERROR_RENDERER_BLOCK_WITH_CUSTOM_PROGRAM				{ 2019, L"Block cannot be used with custom program activated" };
		const ErrorInfo ERROR_RENDERER_BITMASK_WITH_CUSTOM_PROGRAM				{ 2020, L"Bitmask cannot be used with custom program activated" };
		const ErrorInfo ERROR_RENDERER_SPLINE_LIMITS_WITH_CUSTOM_PROGRAM		{ 2021, L"Spline limits cannot be used with custom program activated" };
		const ErrorInfo ERROR_RENDERER_PRIMITIVE_MATRIX_WITH_CUSTOM_PROGRAM		{ 2022, L"Primitive matrix cannot be used with custom program activated" };
		const ErrorInfo ERROR_RENDERER_PUSH_MASK_WITH_CUSTOM_PARAMS				{ 2023, L"Global mask cannot be used with current active state(check: program, vertex array, target, mask)" };
		const ErrorInfo ERROR_RENDERER_LINK_CUSTOM_PROGRAM						{ 2024, L"Cannot link custom program" };
		const ErrorInfo ERROR_RENDERER_MISSING_UNIFORMS_IN_MINI					{ 2025, L"There are missing uniforms in 'Mini' program" };
		const ErrorInfo ERROR_RENDERER_LINK_MINI_PROGRAM						{ 2026, L"Cannot link 'Mini' program" };
		const ErrorInfo ERROR_RENDERER_CREATE_FRAMEBUFFER						{ 2027, L"Cannot create framebuffer" };
		const ErrorInfo ERROR_RENDERER_CREATE_VERTEX_ARRAY						{ 2028, L"Cannot create vertex array" };
		const ErrorInfo ERROR_RENDERER_INVALID_TEXTURE_PARAMS					{ 2029, L"Texture parameters are invalid(check: width, height, level_count)" };
		const ErrorInfo ERROR_RENDERER_RESIZE_TEXTURE							{ 2030, L"Cannot resize texture" };
		const ErrorInfo ERROR_RENDERER_LOCK_TEXTURE_DATA						{ 2031, L"Cannot lock texture data" };
		const ErrorInfo ERROR_RENDERER_LOADED_PICTURE_EMPTY						{ 2032, L"Loaded picture is empty" };
		const ErrorInfo ERROR_RENDERER_NO_WINDOW								{ 2033, L"Window is not assigned" };
		const ErrorInfo ERROR_RENDERER_ALREADY_DRAWING							{ 2034, L"Drawing is already in progress" };
		const ErrorInfo ERROR_RENDERER_NO_DRAWING								{ 2035, L"No drawing is in progress" };
		const ErrorInfo ERROR_RENDERER_DRAWING									{ 2036, L"Drawing is in progress" };
		const ErrorInfo ERROR_RENDERER_PRESENT_WITH_ACTIVE_TARGET				{ 2037, L"Present is not allowed with target activated" };
		const ErrorInfo ERROR_RENDERER_DRAWING_NOT_ALLOWED						{ 2038, L"Drawing is not allowed with custom program and/or custom vertex array activated" };
		const ErrorInfo ERROR_RENDERER_RELEASE_NON_TEXTURE						{ 2039, L"Texture release listener is being used with non-texture object" };
		const ErrorInfo ERROR_RENDERER_RELEASE_NON_PLATFORM_FONT				{ 2040, L"Platform font release listener is being used with non-platform font object" };
		const ErrorInfo ERROR_RENDERER_RELEASE_NON_PROGRAM						{ 2041, L"Program release listener is being used with non-program object" };
		const ErrorInfo ERROR_RENDERER_RELEASE_NON_FRAMEBUFFER					{ 2042, L"Framebuffer release listener is being used with non-framebuffer object" };
		const ErrorInfo ERROR_RENDERER_RELEASE_NON_VERTEX_ARRAY					{ 2043, L"Vertex array release listener is being used with non-vertex array object" };
		const ErrorInfo ERROR_RENDERER_MASKS_NOT_REMOVED						{ 2044, L"Masks were not removed before cleanup" };
		const ErrorInfo ERROR_RENDERER_ADD_EMPTY_TEXTURE						{ 2045, L"Only existing texture can be added" };
		const ErrorInfo ERROR_RENDERER_ADD_TEXTURE_ALREADY_IN_LIST				{ 2046, L"Texture being added is already in list" };
		const ErrorInfo ERROR_RENDERER_ADD_EMPTY_PROGRAM						{ 2047, L"Only existing program can be added" };
		const ErrorInfo ERROR_RENDERER_ADD_PROGRAM_ALREADY_IN_LIST				{ 2048, L"Program being added is already in list" };
		const ErrorInfo ERROR_RENDERER_ADD_EMPTY_FRAMEBUFFER					{ 2049, L"Only existing framebuffer can be added" };
		const ErrorInfo ERROR_RENDERER_ADD_FRAMEBUFFER_ALREADY_IN_LIST			{ 2050, L"Framebuffer being added is already in list" };
		const ErrorInfo ERROR_RENDERER_ADD_EMPTY_VERTEX_ARRAY					{ 2051, L"Only existing vertex array can be added" };
		const ErrorInfo ERROR_RENDERER_ADD_VERTEX_ARRAY_ALREADY_IN_LIST			{ 2052, L"Vertex array being added is already in list" };
		const ErrorInfo ERROR_RENDERER_CREATE_FONT								{ 2053, L"Cannot create system font" };
		const ErrorInfo ERROR_RENDERER_RELEASE_USED_MASK						{ 2054, L"Texture is released while being used as mask. PopMask() should be used first" };
		const ErrorInfo ERROR_RENDERER_RELEASE_UNKNOWN_TEXTURE					{ 2055, L"Texture release listener is being used with unknown texture" };
		const ErrorInfo ERROR_RENDERER_RELEASE_UNKNOWN_PLATFORM_FONT			{ 2056, L"Platform font release listener is being used with unknown platform font" };
		const ErrorInfo ERROR_RENDERER_RELEASE_UNKNOWN_PROGRAM					{ 2057, L"Program release listener is being used with unknown program" };
		const ErrorInfo ERROR_RENDERER_RELEASE_UNKNOWN_FRAMEBUFFER				{ 2058, L"Framebuffer release listener is being used with unknown framebuffer" };
		const ErrorInfo ERROR_RENDERER_RELEASE_UNKNOWN_VERTEX_ARRAY				{ 2059, L"Vertex array release listener is being used with unknown vertex array" };
		const ErrorInfo ERROR_RENDERER_NO_MASK_TO_POP							{ 2060, L"There is no mask to remove. PopMask() should be called exact the same number of times the PushMask() called" };
		const ErrorInfo ERROR_RENDERER_EGL_GET_DISPLAY							{ 2061, L"Cannot obtain default display" };
		const ErrorInfo ERROR_RENDERER_EGL_GET_FORMAT							{ 2062, L"Cannot obtain format of selected EGL configuration" };
		const ErrorInfo ERROR_RENDERER_EGL_SET_FORMAT							{ 2063, L"Cannot set selected from EGL configuration format to native window" };
		const ErrorInfo ERROR_RENDERER_EGL_CREATE_SURFACE						{ 2064, L"Cannot create EGL surface" };
		const ErrorInfo ERROR_RENDERER_GLX_CREATE_CONTENT_ATTRIBS_ARB_UNDEFINED	{ 2065, L"glXCreateContextAttribsARB function does not exist" };
		const ErrorInfo ERROR_RENDERER_CREATE_TEXTURE_FRAMEBUFFER				{ 2066, L"Cannot create texture framebuffer" };
		const ErrorInfo ERROR_RENDERER_NGL_INITIALIZE							{ 2067, L"Cannot initialize NGL (OpenGL/GLES)" };
		const ErrorInfo ERROR_RENDERER_EGL_INITIALIZE							{ 2068, L"Cannot initialize EGL" };
		const ErrorInfo ERROR_RENDERER_RELEASE_NON_TEXTURE_MULTISAMPLE			{ 2069, L"Multi-sample texture release listener is being used with non-texture object" };
		const ErrorInfo ERROR_RENDERER_RELEASE_UNKNOWN_TEXTURE_MULTISAMPLE		{ 2070, L"Multi-sample texture release listener is being used with unknown texture" };
		const ErrorInfo ERROR_RENDERER_ADD_EMPTY_TEXTURE_MULTISAMPLE			{ 2071, L"Only existing multi-sample texture can be added" };
		const ErrorInfo ERROR_RENDERER_ADD_TEXTURE_MULTISAMPLE_ALREADY_IN_LIST	{ 2072, L"Multi-sample texture being added is already in list" };
		const ErrorInfo ERROR_RENDERER_INVALID_TEXTURE_MULTISAMPLE_PARAMS		{ 2073, L"Multi-sample texture parameters are invalid (check: width, height, level_count)" };
		const ErrorInfo ERROR_RENDERER_TEXTURE_MULTISAMPLE_NOT_SUPPORTED		{ 2074, L"Multi-sample texture is not supported due to too low context version (3.2+ is required)" };
		const ErrorInfo ERROR_RENDERER_RESIZE_TEXTURE_MULTISAMPLE				{ 2075, L"Cannot resize multi-sample texture" };
		const ErrorInfo ERROR_RENDERER_UNSUPPORTED_WINDOW_INSTANCE				{ 2076, L"Specified window instance is not supported" };

		// DB
		const ErrorInfo ERROR_DB_GET_DATA_SOURCES								{ 3001, L"Getting data sources failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_GET_DRIVERS									{ 3002, L"Getting drivers failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_ALLOCATE_ENVIRONMENT_HANDLE					{ 3003, L"Allocating environment handle failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_SET_ENVIRONMENT_ATTRIBUTE						{ 3004, L"Setting environment handle attribute failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_UNINITIALIZED									{ 3005, L"Database manager is not initialized yet or it's initialization failed before" };
		const ErrorInfo ERROR_DB_DRIVER_NAME_REQUIRED							{ 3006, L"Driver name is required" };
		const ErrorInfo ERROR_DB_NO_DATA										{ 3007, L"No data" };
		const ErrorInfo ERROR_DB_ALLOCATE_CONNECTION_HANDLE						{ 3008, L"Allocating connection handle failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_SET_CONNECTION_ATTRIBUTE						{ 3009, L"Setting connection attribute failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_ATTRIBUTE_UNDEFINED							{ 3010, L"Attempting to get value of undefined attribute '{attribute}'" };
		const ErrorInfo ERROR_DB_GET_CONNECTION_ATTRIBUTE						{ 3011, L"Getting connection attribute failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_UNKNOWN_ATTRIBUTE_VALUE						{ 3012, L"Got unknown value '{value}' for attribute '{attribute}'" };
		const ErrorInfo ERROR_DB_BUSY											{ 3013, L"Operation is still being executed" };
		const ErrorInfo ERROR_DB_ALLOCATE_STATEMENT_HANDLE						{ 3014, L"Allocating statement handle failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_PREPARE										{ 3015, L"Preparing statement failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_GET_STATEMENT_ATTRIBUTE						{ 3016, L"Getting statement attribute failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_SET_STATEMENT_ATTRIBUTE						{ 3017, L"Setting statement attribute failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_VALIDATE_ROW_EMPTY								{ 3018, L"At least one value in row is required" };
		const ErrorInfo ERROR_DB_VALIDATE_ROWS_EMPTY							{ 3019, L"At least one row in rows is required" };
		const ErrorInfo ERROR_DB_VALIDATE_DIFFERENT_SIZE_ROWS					{ 3020, L"Row #{row} size #{size} is different from first row size #{first}" };
		const ErrorInfo ERROR_DB_EXECUTE										{ 3021, L"Executing statement failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_GET_RESULT_COLUMN_COUNT						{ 3022, L"Get result column count failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_GET_COLUMN_ATTRIBUTE							{ 3023, L"Getting column attribute failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_FETCH											{ 3024, L"Fetching row failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_GET_DATA										{ 3025, L"Getting column data failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_GET_AFFECTED_ROW_COUNT							{ 3026, L"Getting affected row count failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_BIND_PARAMETER									{ 3027, L"Binding parameter failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_PUT_DATA										{ 3028, L"Putting column data failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_PARAM_DATA										{ 3029, L"Getting data parameter failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_UNEXPECTED_PARAM_DATA_AVAILABLE				{ 3030, L"Got data parameter available while shouldn't" };
		const ErrorInfo ERROR_DB_GET_TABLES										{ 3031, L"Getting tables information failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_GET_TABLE_PRIVILEGES							{ 3032, L"Getting table privileges failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_GET_COLUMNS									{ 3033, L"Getting columns information failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_GET_COLUMN_PRIVILEGES							{ 3034, L"Getting column privileges failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_GET_SPECIAL_COLUMNS							{ 3035, L"Getting special columns information failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_GET_PROCEDURE_COLUMNS							{ 3036, L"Getting procedure columns information failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_GET_FOREIGN_KEYS								{ 3037, L"Getting foreign keys failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_GET_PRIMARY_KEYS								{ 3038, L"Getting primary keys failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_GET_PROCEDURES									{ 3039, L"Getting procedures information failed with state '{state}', error code '{code}' and message '{message}'" };
		const ErrorInfo ERROR_DB_GET_STATISTICS									{ 3040, L"Getting statistic information failed with state '{state}', error code '{code}' and message '{message}'" };
	}
}