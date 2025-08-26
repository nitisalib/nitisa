// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ErrorInfo.h"

namespace nitisa
{
	namespace platform
	{
		// General
		extern const ErrorInfo ERROR_GENERAL_UNKNOWN;
		extern const ErrorInfo ERROR_GENERAL_INVALID_HANDLE;
		extern const ErrorInfo ERROR_GENERAL_INVALID_SENDER;
		extern const ErrorInfo ERROR_GENERAL_NOT_FOUND;

		// OpenGL
		extern const ErrorInfo ERROR_OPENGL_CALL_FAILED;
		extern const ErrorInfo ERROR_OPENGL_COMPILE_SHADER;
		extern const ErrorInfo ERROR_OPENGL_LINK_PROGRAM;
		extern const ErrorInfo ERROR_OPENGL_LOAD;

		// Renderer
		extern const ErrorInfo ERROR_RENDERER_OPENGL_VERSION;
		extern const ErrorInfo ERROR_RENDERER_REQUESTED_MAX_VERSION;
		extern const ErrorInfo ERROR_RENDERER_GET_WINDOW_DEVICE_CONTEXT;
		extern const ErrorInfo ERROR_RENDERER_CREATE_COMPATIBLE_DEVICE_CONTEXT;
		extern const ErrorInfo ERROR_RENDERER_CREATE_OPENGL;
		extern const ErrorInfo ERROR_RENDERER_OPENGL_VERSION_TOO_LOW;
		extern const ErrorInfo ERROR_RENDERER_WGL_CHOOSE_PIXEL_FORMAT_ARB_UNDEFINED;
		extern const ErrorInfo ERROR_RENDERER_WGL_CREATE_CONTENT_ATTRIBS_ARB_UNDEFINED;
		extern const ErrorInfo ERROR_RENDERER_FIND_PIXEL_FORMAT;
		extern const ErrorInfo ERROR_RENDERER_SET_PIXEL_FORMAT;
		extern const ErrorInfo ERROR_RENDERER_CREATE_CONTEXT;
		extern const ErrorInfo ERROR_RENDERER_ACTIVATE_CONTEXT;
		extern const ErrorInfo ERROR_RENDERER_CREATE_DEFAULT_VERTEX_ARRAY;
		extern const ErrorInfo ERROR_RENDERER_CREATE_GRADIENT_TEXTURES;
		extern const ErrorInfo ERROR_RENDERER_CREATE_MAIN_PROGRAM;
		extern const ErrorInfo ERROR_RENDERER_CREATE_DEFAULT_FRAMEBUFFER;
		extern const ErrorInfo ERROR_RENDERER_WINDOW_NOT_CREATED;
		extern const ErrorInfo ERROR_RENDERER_MASK_WITH_CUSTOM_PROGRAM;
		extern const ErrorInfo ERROR_RENDERER_BLOCK_WITH_CUSTOM_PROGRAM;
		extern const ErrorInfo ERROR_RENDERER_BITMASK_WITH_CUSTOM_PROGRAM;
		extern const ErrorInfo ERROR_RENDERER_SPLINE_LIMITS_WITH_CUSTOM_PROGRAM;
		extern const ErrorInfo ERROR_RENDERER_PRIMITIVE_MATRIX_WITH_CUSTOM_PROGRAM;
		extern const ErrorInfo ERROR_RENDERER_PUSH_MASK_WITH_CUSTOM_PARAMS;
		extern const ErrorInfo ERROR_RENDERER_LINK_CUSTOM_PROGRAM;
		extern const ErrorInfo ERROR_RENDERER_MISSING_UNIFORMS_IN_MINI;
		extern const ErrorInfo ERROR_RENDERER_LINK_MINI_PROGRAM;
		extern const ErrorInfo ERROR_RENDERER_CREATE_FRAMEBUFFER;
		extern const ErrorInfo ERROR_RENDERER_CREATE_VERTEX_ARRAY;
		extern const ErrorInfo ERROR_RENDERER_INVALID_TEXTURE_PARAMS;
		extern const ErrorInfo ERROR_RENDERER_RESIZE_TEXTURE;
		extern const ErrorInfo ERROR_RENDERER_LOCK_TEXTURE_DATA;
		extern const ErrorInfo ERROR_RENDERER_LOADED_PICTURE_EMPTY;
		extern const ErrorInfo ERROR_RENDERER_NO_WINDOW;
		extern const ErrorInfo ERROR_RENDERER_ALREADY_DRAWING;
		extern const ErrorInfo ERROR_RENDERER_NO_DRAWING;
		extern const ErrorInfo ERROR_RENDERER_DRAWING;
		extern const ErrorInfo ERROR_RENDERER_PRESENT_WITH_ACTIVE_TARGET;
		extern const ErrorInfo ERROR_RENDERER_DRAWING_NOT_ALLOWED;
		extern const ErrorInfo ERROR_RENDERER_RELEASE_NON_TEXTURE;
		extern const ErrorInfo ERROR_RENDERER_RELEASE_NON_PLATFORM_FONT;
		extern const ErrorInfo ERROR_RENDERER_RELEASE_NON_PROGRAM;
		extern const ErrorInfo ERROR_RENDERER_RELEASE_NON_FRAMEBUFFER;
		extern const ErrorInfo ERROR_RENDERER_RELEASE_NON_VERTEX_ARRAY;
		extern const ErrorInfo ERROR_RENDERER_MASKS_NOT_REMOVED;
		extern const ErrorInfo ERROR_RENDERER_ADD_EMPTY_TEXTURE;
		extern const ErrorInfo ERROR_RENDERER_ADD_TEXTURE_ALREADY_IN_LIST;
		extern const ErrorInfo ERROR_RENDERER_ADD_EMPTY_PROGRAM;
		extern const ErrorInfo ERROR_RENDERER_ADD_PROGRAM_ALREADY_IN_LIST;
		extern const ErrorInfo ERROR_RENDERER_ADD_EMPTY_FRAMEBUFFER;
		extern const ErrorInfo ERROR_RENDERER_ADD_FRAMEBUFFER_ALREADY_IN_LIST;
		extern const ErrorInfo ERROR_RENDERER_ADD_EMPTY_VERTEX_ARRAY;
		extern const ErrorInfo ERROR_RENDERER_ADD_VERTEX_ARRAY_ALREADY_IN_LIST;
		extern const ErrorInfo ERROR_RENDERER_CREATE_FONT;
		extern const ErrorInfo ERROR_RENDERER_RELEASE_USED_MASK;
		extern const ErrorInfo ERROR_RENDERER_RELEASE_UNKNOWN_TEXTURE;
		extern const ErrorInfo ERROR_RENDERER_RELEASE_UNKNOWN_PLATFORM_FONT;
		extern const ErrorInfo ERROR_RENDERER_RELEASE_UNKNOWN_PROGRAM;
		extern const ErrorInfo ERROR_RENDERER_RELEASE_UNKNOWN_FRAMEBUFFER;
		extern const ErrorInfo ERROR_RENDERER_RELEASE_UNKNOWN_VERTEX_ARRAY;
		extern const ErrorInfo ERROR_RENDERER_NO_MASK_TO_POP;
		extern const ErrorInfo ERROR_RENDERER_EGL_GET_DISPLAY;
		extern const ErrorInfo ERROR_RENDERER_EGL_GET_FORMAT;
		extern const ErrorInfo ERROR_RENDERER_EGL_SET_FORMAT;
		extern const ErrorInfo ERROR_RENDERER_EGL_CREATE_SURFACE;
		extern const ErrorInfo ERROR_RENDERER_GLX_CREATE_CONTENT_ATTRIBS_ARB_UNDEFINED;
		extern const ErrorInfo ERROR_RENDERER_CREATE_TEXTURE_FRAMEBUFFER;
		extern const ErrorInfo ERROR_RENDERER_NGL_INITIALIZE;
		extern const ErrorInfo ERROR_RENDERER_EGL_INITIALIZE;
		extern const ErrorInfo ERROR_RENDERER_RELEASE_NON_TEXTURE_MULTISAMPLE;
		extern const ErrorInfo ERROR_RENDERER_RELEASE_UNKNOWN_TEXTURE_MULTISAMPLE;
		extern const ErrorInfo ERROR_RENDERER_ADD_EMPTY_TEXTURE_MULTISAMPLE;
		extern const ErrorInfo ERROR_RENDERER_ADD_TEXTURE_MULTISAMPLE_ALREADY_IN_LIST;
		extern const ErrorInfo ERROR_RENDERER_INVALID_TEXTURE_MULTISAMPLE_PARAMS;
		extern const ErrorInfo ERROR_RENDERER_TEXTURE_MULTISAMPLE_NOT_SUPPORTED;
		extern const ErrorInfo ERROR_RENDERER_RESIZE_TEXTURE_MULTISAMPLE;
		extern const ErrorInfo ERROR_RENDERER_UNSUPPORTED_WINDOW_INSTANCE;

		// DB
		extern const ErrorInfo ERROR_DB_GET_DATA_SOURCES;
		extern const ErrorInfo ERROR_DB_GET_DRIVERS;
		extern const ErrorInfo ERROR_DB_ALLOCATE_ENVIRONMENT_HANDLE;
		extern const ErrorInfo ERROR_DB_SET_ENVIRONMENT_ATTRIBUTE;
		extern const ErrorInfo ERROR_DB_UNINITIALIZED;
		extern const ErrorInfo ERROR_DB_DRIVER_NAME_REQUIRED;
		extern const ErrorInfo ERROR_DB_NO_DATA;
		extern const ErrorInfo ERROR_DB_ALLOCATE_CONNECTION_HANDLE;
		extern const ErrorInfo ERROR_DB_SET_CONNECTION_ATTRIBUTE;
		extern const ErrorInfo ERROR_DB_ATTRIBUTE_UNDEFINED;
		extern const ErrorInfo ERROR_DB_GET_CONNECTION_ATTRIBUTE;
		extern const ErrorInfo ERROR_DB_UNKNOWN_ATTRIBUTE_VALUE;
		extern const ErrorInfo ERROR_DB_BUSY;
		extern const ErrorInfo ERROR_DB_ALLOCATE_STATEMENT_HANDLE;
		extern const ErrorInfo ERROR_DB_PREPARE;
		extern const ErrorInfo ERROR_DB_GET_STATEMENT_ATTRIBUTE;
		extern const ErrorInfo ERROR_DB_SET_STATEMENT_ATTRIBUTE;
		extern const ErrorInfo ERROR_DB_VALIDATE_ROW_EMPTY;
		extern const ErrorInfo ERROR_DB_VALIDATE_ROWS_EMPTY;
		extern const ErrorInfo ERROR_DB_VALIDATE_DIFFERENT_SIZE_ROWS;
		extern const ErrorInfo ERROR_DB_EXECUTE;
		extern const ErrorInfo ERROR_DB_GET_RESULT_COLUMN_COUNT;
		extern const ErrorInfo ERROR_DB_GET_COLUMN_ATTRIBUTE;
		extern const ErrorInfo ERROR_DB_FETCH;
		extern const ErrorInfo ERROR_DB_GET_DATA;
		extern const ErrorInfo ERROR_DB_GET_AFFECTED_ROW_COUNT;
		extern const ErrorInfo ERROR_DB_BIND_PARAMETER;
		extern const ErrorInfo ERROR_DB_PUT_DATA;
		extern const ErrorInfo ERROR_DB_PARAM_DATA;
		extern const ErrorInfo ERROR_DB_UNEXPECTED_PARAM_DATA_AVAILABLE;
		extern const ErrorInfo ERROR_DB_GET_TABLES;
		extern const ErrorInfo ERROR_DB_GET_TABLE_PRIVILEGES;
		extern const ErrorInfo ERROR_DB_GET_COLUMNS;
		extern const ErrorInfo ERROR_DB_GET_COLUMN_PRIVILEGES;
		extern const ErrorInfo ERROR_DB_GET_SPECIAL_COLUMNS;
		extern const ErrorInfo ERROR_DB_GET_PROCEDURE_COLUMNS;
		extern const ErrorInfo ERROR_DB_GET_FOREIGN_KEYS;
		extern const ErrorInfo ERROR_DB_GET_PRIMARY_KEYS;
		extern const ErrorInfo ERROR_DB_GET_PROCEDURES;
		extern const ErrorInfo ERROR_DB_GET_STATISTICS;
	}
}