// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#include "ngl.h"

namespace ngl
{
#if defined(_WIN32) || (defined(__linux__) && !defined(__ANDROID__))
	struct UNIFORM_TYPE_SET
	{
		GLenum      type;
		const char* name;
	} UniformTypes[]{
		GL_INVALID_ENUM,                              "invalid",
		GL_FLOAT,                                     "float",
		GL_INT,                                       "int",
		GL_UNSIGNED_INT,                              "unsigned int",
		GL_DOUBLE,                                    "double",
		GL_FLOAT_VEC2,                                "vec2",
		GL_FLOAT_VEC3,                                "vec3",
		GL_FLOAT_VEC4,                                "vec4",
		GL_INT_VEC2,                                  "ivec2",
		GL_INT_VEC3,                                  "ivec3",
		GL_INT_VEC4,                                  "ivec4",
		GL_BOOL,                                      "bool",
		GL_BOOL_VEC2,                                 "bvec2",
		GL_BOOL_VEC3,                                 "bvec3",
		GL_BOOL_VEC4,                                 "bvec4",
		GL_FLOAT_MAT2,                                "mat2",
		GL_FLOAT_MAT3,                                "mat3",
		GL_FLOAT_MAT4,                                "mat4",
		GL_SAMPLER_1D,                                "sampler1D",
		GL_SAMPLER_2D,                                "sampler2D",
		GL_SAMPLER_3D,                                "sampler3D",
		GL_SAMPLER_CUBE,                              "samplerCube",
		GL_SAMPLER_1D_SHADOW,                         "sampler1DShadow",
		GL_SAMPLER_2D_SHADOW,                         "sampler2DShadow",
		GL_FLOAT_MAT2x3,                              "mat2x3",
		GL_FLOAT_MAT2x4,                              "mat2x4",
		GL_FLOAT_MAT3x2,                              "mat3x2",
		GL_FLOAT_MAT3x4,                              "mat3x4",
		GL_FLOAT_MAT4x2,                              "mat4x2",
		GL_FLOAT_MAT4x3,                              "mat4x3",
		GL_UNSIGNED_INT_VEC2,                         "uvec2",
		GL_UNSIGNED_INT_VEC3,                         "uvec3",
		GL_UNSIGNED_INT_VEC4,                         "uvec4",
		GL_SAMPLER_1D_ARRAY,                          "sampler1DArray",
		GL_SAMPLER_2D_ARRAY,                          "sampler2DArray",
		GL_SAMPLER_1D_ARRAY_SHADOW,                   "sampler1DArrayShadow",
		GL_SAMPLER_2D_ARRAY_SHADOW,                   "sampler2DArrayShadow",
		GL_SAMPLER_CUBE_SHADOW,                       "samplerCubeShadow",
		GL_INT_SAMPLER_1D,                            "isampler1D",
		GL_INT_SAMPLER_2D,                            "isampler2D",
		GL_INT_SAMPLER_3D,                            "isampler3D",
		GL_INT_SAMPLER_CUBE,                          "isamplerCube",
		GL_INT_SAMPLER_1D_ARRAY,                      "isampler1DArray",
		GL_INT_SAMPLER_2D_ARRAY,                      "isampler2DArray",
		GL_UNSIGNED_INT_SAMPLER_1D,                   "usampler1D",
		GL_UNSIGNED_INT_SAMPLER_2D,                   "usampler2D",
		GL_UNSIGNED_INT_SAMPLER_3D,                   "usampler3D",
		GL_UNSIGNED_INT_SAMPLER_CUBE,                 "usamplerCube",
		GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,             "usampler2DArray",
		GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,             "usampler2DArray",
		GL_SAMPLER_BUFFER,                            "samplerBuffer",
		GL_SAMPLER_2D_RECT,                           "sampler2DRect",
		GL_SAMPLER_2D_RECT_SHADOW,                    "sampler2DRectShadow",
		GL_INT_SAMPLER_2D_MULTISAMPLE,                "isampler2DMS",
		GL_INT_SAMPLER_BUFFER,                        "isamplerBuffer",
		GL_INT_SAMPLER_2D_RECT,                       "isampler2DRect",
		GL_UNSIGNED_INT_SAMPLER_BUFFER,               "usamplerBuffer",
		GL_UNSIGNED_INT_SAMPLER_2D_RECT,              "usampler2DRect",
		GL_SAMPLER_2D_MULTISAMPLE,                    "sampler2DMS",
		GL_SAMPLER_2D_MULTISAMPLE_ARRAY,              "sampler2DMSArray",
		GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,          "isampler2DMSArray",
		GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,       "usampler2DMS",
		GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY, "usampler2DMSArray",
		GL_DOUBLE_VEC2,                               "dvec2",
		GL_DOUBLE_VEC3,                               "dvec3",
		GL_DOUBLE_VEC4,                               "dvec4",
		GL_DOUBLE_MAT2,                               "dmat2",
		GL_DOUBLE_MAT3,                               "dmat3",
		GL_DOUBLE_MAT4,                               "dmat4",
		GL_DOUBLE_MAT2x3,                             "dmat2x3",
		GL_DOUBLE_MAT2x4,                             "dmat2x4",
		GL_DOUBLE_MAT3x2,                             "dmat3x2",
		GL_DOUBLE_MAT3x4,                             "dmat3x4",
		GL_DOUBLE_MAT4x2,                             "dmat4x2",
		GL_DOUBLE_MAT4x3,                             "dmat4x3",
		GL_IMAGE_1D,                                  "image1D",
		GL_IMAGE_2D,                                  "image2D",
		GL_IMAGE_3D,                                  "image3D",
		GL_IMAGE_2D_RECT,                             "image2DRect",
		GL_IMAGE_CUBE,                                "imageCube",
		GL_IMAGE_BUFFER,                              "imageBuffer",
		GL_IMAGE_1D_ARRAY,                            "image1DArray",
		GL_IMAGE_2D_ARRAY,                            "image2DArray",
		GL_IMAGE_2D_MULTISAMPLE,                      "image2DMS",
		GL_IMAGE_2D_MULTISAMPLE_ARRAY,                "image2DMSArray",
		GL_INT_IMAGE_1D,                              "iimage1D",
		GL_INT_IMAGE_2D,                              "iimage2D",
		GL_INT_IMAGE_3D,                              "iimage3D",
		GL_INT_IMAGE_2D_RECT,                         "iimage2DRect",
		GL_INT_IMAGE_CUBE,                            "iimageCube",
		GL_INT_IMAGE_BUFFER,                          "iimageBuffer",
		GL_INT_IMAGE_1D_ARRAY,                        "iimage1DArray",
		GL_INT_IMAGE_2D_ARRAY,                        "iimage2DArray",
		GL_INT_IMAGE_2D_MULTISAMPLE,                  "iimage2DMS",
		GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY,            "iimage2DMSArray",
		GL_UNSIGNED_INT_IMAGE_1D,                     "uimage1D",
		GL_UNSIGNED_INT_IMAGE_2D,                     "uimage2D",
		GL_UNSIGNED_INT_IMAGE_3D,                     "uimage3D",
		GL_UNSIGNED_INT_IMAGE_2D_RECT,                "uimage2DRect",
		GL_UNSIGNED_INT_IMAGE_CUBE,                   "uimageCube",
		GL_UNSIGNED_INT_IMAGE_BUFFER,                 "uimageBuffer",
		GL_UNSIGNED_INT_IMAGE_1D_ARRAY,               "uimage1DArray",
		GL_UNSIGNED_INT_IMAGE_2D_ARRAY,               "uimage2DArray",
		GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE,         "uimage2DMS",
		GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY,   "uimage2DMSArray",
		GL_UNSIGNED_INT_ATOMIC_COUNTER,               "atomic_uint"
	};

	void *GetProc(const char *name, int &total, int &loaded);

	void PrintProgramUniforms(GLuint program)
	{
		GLint uniform_count;
		glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniform_count);
		GLchar name[256];
		for (GLint i = 0; i < uniform_count; i++)
		{
			memset(name, '\0', 256);
			GLint  size;
			GLenum type;
			glGetActiveUniform(program, i, 255, nullptr, &size, &type, name);
			GLint location{ glGetUniformLocation(program, name) };
			for (size_t j = 0; j < sizeof(UniformTypes) / sizeof(UNIFORM_TYPE_SET); j++)
			{
				if (UniformTypes[j].type != type)
					continue;
				const char* type_name{ UniformTypes[j].name };
				if (size > 1)
					printf("Uniform %d (loc=%d):\t%20s %-20s <Size: %d>\n", i, location, type_name, name, size);
				else
					printf("Uniform %d (loc=%d):\t%20s %-20s\n", i, location, type_name, name);
				break;
			}
			if (i == (uniform_count - 1))
				printf("\n");
		}
	}

	void LoadCommonProcedures(int &total, int &loaded)
	{
		// 1.0
		total = loaded = 0;
		glCullFace = (PFNGLCULLFACEPROC)GetProc("glCullFace", total, loaded);
		glFrontFace = (PFNGLFRONTFACEPROC)GetProc("glFrontFace", total, loaded);
		glHint = (PFNGLHINTPROC)GetProc("glHint", total, loaded);
		glLineWidth = (PFNGLLINEWIDTHPROC)GetProc("glLineWidth", total, loaded);
		glPointSize = (PFNGLPOINTSIZEPROC)GetProc("glPointSize", total, loaded);
		glPolygonMode = (PFNGLPOLYGONMODEPROC)GetProc("glPolygonMode", total, loaded);
		glScissor = (PFNGLSCISSORPROC)GetProc("glScissor", total, loaded);
		glTexParameterf = (PFNGLTEXPARAMETERFPROC)GetProc("glTexParameterf", total, loaded);
		glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)GetProc("glTexParameterfv", total, loaded);
		glTexParameteri = (PFNGLTEXPARAMETERIPROC)GetProc("glTexParameteri", total, loaded);
		glTexParameteriv = (PFNGLTEXPARAMETERIVPROC)GetProc("glTexParameteriv", total, loaded);
		glTexImage1D = (PFNGLTEXIMAGE1DPROC)GetProc("glTexImage1D", total, loaded);
		glTexImage2D = (PFNGLTEXIMAGE2DPROC)GetProc("glTexImage2D", total, loaded);
		glDrawBuffer = (PFNGLDRAWBUFFERPROC)GetProc("glDrawBuffer", total, loaded);
		glClear = (PFNGLCLEARPROC)GetProc("glClear", total, loaded);
		glClearColor = (PFNGLCLEARCOLORPROC)GetProc("glClearColor", total, loaded);
		glClearStencil = (PFNGLCLEARSTENCILPROC)GetProc("glClearStencil", total, loaded);
		glClearDepth = (PFNGLCLEARDEPTHPROC)GetProc("glClearDepth", total, loaded);
		glStencilMask = (PFNGLSTENCILMASKPROC)GetProc("glStencilMask", total, loaded);
		glColorMask = (PFNGLCOLORMASKPROC)GetProc("glColorMask", total, loaded);
		glDepthMask = (PFNGLDEPTHMASKPROC)GetProc("glDepthMask", total, loaded);
		glDisable = (PFNGLDISABLEPROC)GetProc("glDisable", total, loaded);
		glEnable = (PFNGLENABLEPROC)GetProc("glEnable", total, loaded);
		glFinish = (PFNGLFINISHPROC)GetProc("glFinish", total, loaded);
		glFlush = (PFNGLFLUSHPROC)GetProc("glFlush", total, loaded);
		glBlendFunc = (PFNGLBLENDFUNCPROC)GetProc("glBlendFunc", total, loaded);
		glLogicOp = (PFNGLLOGICOPPROC)GetProc("glLogicOp", total, loaded);
		glStencilFunc = (PFNGLSTENCILFUNCPROC)GetProc("glStencilFunc", total, loaded);
		glStencilOp = (PFNGLSTENCILOPPROC)GetProc("glStencilOp", total, loaded);
		glDepthFunc = (PFNGLDEPTHFUNCPROC)GetProc("glDepthFunc", total, loaded);
		glPixelStoref = (PFNGLPIXELSTOREFPROC)GetProc("glPixelStoref", total, loaded);
		glPixelStorei = (PFNGLPIXELSTOREIPROC)GetProc("glPixelStorei", total, loaded);
		glReadBuffer = (PFNGLREADBUFFERPROC)GetProc("glReadBuffer", total, loaded);
		glReadPixels = (PFNGLREADPIXELSPROC)GetProc("glReadPixels", total, loaded);
		glGetBooleanv = (PFNGLGETBOOLEANVPROC)GetProc("glGetBooleanv", total, loaded);
		glGetDoublev = (PFNGLGETDOUBLEVPROC)GetProc("glGetDoublev", total, loaded);
		glGetError = (PFNGLGETERRORPROC)GetProc("glGetError", total, loaded);
		glGetFloatv = (PFNGLGETFLOATVPROC)GetProc("glGetFloatv", total, loaded);
		glGetIntegerv = (PFNGLGETINTEGERVPROC)GetProc("glGetIntegerv", total, loaded);
		glGetString = (PFNGLGETSTRINGPROC)GetProc("glGetString", total, loaded);
		glGetTexImage = (PFNGLGETTEXIMAGEPROC)GetProc("glGetTexImage", total, loaded);
		glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC)GetProc("glGetTexParameterfv", total, loaded);
		glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC)GetProc("glGetTexParameteriv", total, loaded);
		glGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC)GetProc("glGetTexLevelParameterfv", total, loaded);
		glGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC)GetProc("glGetTexLevelParameteriv", total, loaded);
		glIsEnabled = (PFNGLISENABLEDPROC)GetProc("glIsEnabled", total, loaded);
		glDepthRange = (PFNGLDEPTHRANGEPROC)GetProc("glDepthRange", total, loaded);
		glViewport = (PFNGLVIEWPORTPROC)GetProc("glViewport", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 1.0" << std::endl;
	#endif
		// 1.1
		total = loaded = 0;
		glDrawArrays = (PFNGLDRAWARRAYSPROC)GetProc("glDrawArrays", total, loaded);
		glDrawElements = (PFNGLDRAWELEMENTSPROC)GetProc("glDrawElements", total, loaded);
		glGetPointerv = (PFNGLGETPOINTERVPROC)GetProc("glGetPointerv", total, loaded);
		glPolygonOffset = (PFNGLPOLYGONOFFSETPROC)GetProc("glPolygonOffset", total, loaded);
		glCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC)GetProc("glCopyTexImage1D", total, loaded);
		glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC)GetProc("glCopyTexImage2D", total, loaded);
		glCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC)GetProc("glCopyTexSubImage1D", total, loaded);
		glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC)GetProc("glCopyTexSubImage2D", total, loaded);
		glTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC)GetProc("glTexSubImage1D", total, loaded);
		glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)GetProc("glTexSubImage2D", total, loaded);
		glBindTexture = (PFNGLBINDTEXTUREPROC)GetProc("glBindTexture", total, loaded);
		glDeleteTextures = (PFNGLDELETETEXTURESPROC)GetProc("glDeleteTextures", total, loaded);
		glGenTextures = (PFNGLGENTEXTURESPROC)GetProc("glGenTextures", total, loaded);
		glIsTexture = (PFNGLISTEXTUREPROC)GetProc("glIsTexture", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 1.1" << std::endl;
	#endif
		// 1.2
		total = loaded = 0;
		glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)GetProc("glDrawRangeElements", total, loaded);
		glTexImage3D = (PFNGLTEXIMAGE3DPROC)GetProc("glTexImage3D", total, loaded);
		glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)GetProc("glTexSubImage3D", total, loaded);
		glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)GetProc("glCopyTexSubImage3D", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 1.2" << std::endl;
	#endif
		// 1.3
		total = loaded = 0;
		glActiveTexture = (PFNGLACTIVETEXTUREPROC)GetProc("glActiveTexture", total, loaded);
		glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)GetProc("glSampleCoverage", total, loaded);
		glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)GetProc("glCompressedTexImage3D", total, loaded);
		glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)GetProc("glCompressedTexImage2D", total, loaded);
		glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)GetProc("glCompressedTexImage1D", total, loaded);
		glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)GetProc("glCompressedTexSubImage3D", total, loaded);
		glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)GetProc("glCompressedTexSubImage2D", total, loaded);
		glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)GetProc("glCompressedTexSubImage1D", total, loaded);
		glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)GetProc("glGetCompressedTexImage", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 1.3" << std::endl;
	#endif
		// 1.4
		total = loaded = 0;
		glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)GetProc("glBlendFuncSeparate", total, loaded);
		glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC)GetProc("glMultiDrawArrays", total, loaded);
		glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC)GetProc("glMultiDrawElements", total, loaded);
		glPointParameterf = (PFNGLPOINTPARAMETERFPROC)GetProc("glPointParameterf", total, loaded);
		glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)GetProc("glPointParameterfv", total, loaded);
		glPointParameteri = (PFNGLPOINTPARAMETERIPROC)GetProc("glPointParameteri", total, loaded);
		glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)GetProc("glPointParameteriv", total, loaded);
		glBlendColor = (PFNGLBLENDCOLORPROC)GetProc("glBlendColor", total, loaded);
		glBlendEquation = (PFNGLBLENDEQUATIONPROC)GetProc("glBlendEquation", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 1.4" << std::endl;
	#endif
		// 1.5
		total = loaded = 0;
		glGenQueries = (PFNGLGENQUERIESPROC)GetProc("glGenQueries", total, loaded);
		glDeleteQueries = (PFNGLDELETEQUERIESPROC)GetProc("glDeleteQueries", total, loaded);
		glIsQuery = (PFNGLISQUERYPROC)GetProc("glIsQuery", total, loaded);
		glBeginQuery = (PFNGLBEGINQUERYPROC)GetProc("glBeginQuery", total, loaded);
		glEndQuery = (PFNGLENDQUERYPROC)GetProc("glEndQuery", total, loaded);
		glGetQueryiv = (PFNGLGETQUERYIVPROC)GetProc("glGetQueryiv", total, loaded);
		glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)GetProc("glGetQueryObjectiv", total, loaded);
		glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)GetProc("glGetQueryObjectuiv", total, loaded);
		glBindBuffer = (PFNGLBINDBUFFERPROC)GetProc("glBindBuffer", total, loaded);
		glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)GetProc("glDeleteBuffers", total, loaded);
		glGenBuffers = (PFNGLGENBUFFERSPROC)GetProc("glGenBuffers", total, loaded);
		glIsBuffer = (PFNGLISBUFFERPROC)GetProc("glIsBuffer", total, loaded);
		glBufferData = (PFNGLBUFFERDATAPROC)GetProc("glBufferData", total, loaded);
		glBufferSubData = (PFNGLBUFFERSUBDATAPROC)GetProc("glBufferSubData", total, loaded);
		glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)GetProc("glGetBufferSubData", total, loaded);
		glMapBuffer = (PFNGLMAPBUFFERPROC)GetProc("glMapBuffer", total, loaded);
		glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)GetProc("glUnmapBuffer", total, loaded);
		glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)GetProc("glGetBufferParameteriv", total, loaded);
		glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)GetProc("glGetBufferPointerv", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 1.5" << std::endl;
	#endif
		// 2.0
		total = loaded = 0;
		glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)GetProc("glBlendEquationSeparate", total, loaded);
		glDrawBuffers = (PFNGLDRAWBUFFERSPROC)GetProc("glDrawBuffers", total, loaded);
		glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)GetProc("glStencilOpSeparate", total, loaded);
		glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)GetProc("glStencilFuncSeparate", total, loaded);
		glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)GetProc("glStencilMaskSeparate", total, loaded);
		glAttachShader = (PFNGLATTACHSHADERPROC)GetProc("glAttachShader", total, loaded);
		glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)GetProc("glBindAttribLocation", total, loaded);
		glCompileShader = (PFNGLCOMPILESHADERPROC)GetProc("glCompileShader", total, loaded);
		glCreateProgram = (PFNGLCREATEPROGRAMPROC)GetProc("glCreateProgram", total, loaded);
		glCreateShader = (PFNGLCREATESHADERPROC)GetProc("glCreateShader", total, loaded);
		glDeleteProgram = (PFNGLDELETEPROGRAMPROC)GetProc("glDeleteProgram", total, loaded);
		glDeleteShader = (PFNGLDELETESHADERPROC)GetProc("glDeleteShader", total, loaded);
		glDetachShader = (PFNGLDETACHSHADERPROC)GetProc("glDetachShader", total, loaded);
		glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)GetProc("glDisableVertexAttribArray", total, loaded);
		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)GetProc("glEnableVertexAttribArray", total, loaded);
		glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)GetProc("glGetActiveAttrib", total, loaded);
		glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)GetProc("glGetActiveUniform", total, loaded);
		glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)GetProc("glGetAttachedShaders", total, loaded);
		glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)GetProc("glGetAttribLocation", total, loaded);
		glGetProgramiv = (PFNGLGETPROGRAMIVPROC)GetProc("glGetProgramiv", total, loaded);
		glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)GetProc("glGetProgramInfoLog", total, loaded);
		glGetShaderiv = (PFNGLGETSHADERIVPROC)GetProc("glGetShaderiv", total, loaded);
		glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)GetProc("glGetShaderInfoLog", total, loaded);
		glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)GetProc("glGetShaderSource", total, loaded);
		glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)GetProc("glGetUniformLocation", total, loaded);
		glGetUniformfv = (PFNGLGETUNIFORMFVPROC)GetProc("glGetUniformfv", total, loaded);
		glGetUniformiv = (PFNGLGETUNIFORMIVPROC)GetProc("glGetUniformiv", total, loaded);
		glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)GetProc("glGetVertexAttribdv", total, loaded);
		glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)GetProc("glGetVertexAttribfv", total, loaded);
		glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)GetProc("glGetVertexAttribiv", total, loaded);
		glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)GetProc("glGetVertexAttribPointerv", total, loaded);
		glIsProgram = (PFNGLISPROGRAMPROC)GetProc("glIsProgram", total, loaded);
		glIsShader = (PFNGLISSHADERPROC)GetProc("glIsShader", total, loaded);
		glLinkProgram = (PFNGLLINKPROGRAMPROC)GetProc("glLinkProgram", total, loaded);
		glShaderSource = (PFNGLSHADERSOURCEPROC)GetProc("glShaderSource", total, loaded);
		glUseProgram = (PFNGLUSEPROGRAMPROC)GetProc("glUseProgram", total, loaded);
		glUniform1f = (PFNGLUNIFORM1FPROC)GetProc("glUniform1f", total, loaded);
		glUniform2f = (PFNGLUNIFORM2FPROC)GetProc("glUniform2f", total, loaded);
		glUniform3f = (PFNGLUNIFORM3FPROC)GetProc("glUniform3f", total, loaded);
		glUniform4f = (PFNGLUNIFORM4FPROC)GetProc("glUniform4f", total, loaded);
		glUniform1i = (PFNGLUNIFORM1IPROC)GetProc("glUniform1i", total, loaded);
		glUniform2i = (PFNGLUNIFORM2IPROC)GetProc("glUniform2i", total, loaded);
		glUniform3i = (PFNGLUNIFORM3IPROC)GetProc("glUniform3i", total, loaded);
		glUniform4i = (PFNGLUNIFORM4IPROC)GetProc("glUniform4i", total, loaded);
		glUniform1fv = (PFNGLUNIFORM1FVPROC)GetProc("glUniform1fv", total, loaded);
		glUniform2fv = (PFNGLUNIFORM2FVPROC)GetProc("glUniform2fv", total, loaded);
		glUniform3fv = (PFNGLUNIFORM3FVPROC)GetProc("glUniform3fv", total, loaded);
		glUniform4fv = (PFNGLUNIFORM4FVPROC)GetProc("glUniform4fv", total, loaded);
		glUniform1iv = (PFNGLUNIFORM1IVPROC)GetProc("glUniform1iv", total, loaded);
		glUniform2iv = (PFNGLUNIFORM2IVPROC)GetProc("glUniform2iv", total, loaded);
		glUniform3iv = (PFNGLUNIFORM3IVPROC)GetProc("glUniform3iv", total, loaded);
		glUniform4iv = (PFNGLUNIFORM4IVPROC)GetProc("glUniform4iv", total, loaded);
		glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)GetProc("glUniformMatrix2fv", total, loaded);
		glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)GetProc("glUniformMatrix3fv", total, loaded);
		glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)GetProc("glUniformMatrix4fv", total, loaded);
		glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)GetProc("glValidateProgram", total, loaded);
		glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)GetProc("glVertexAttrib1d", total, loaded);
		glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)GetProc("glVertexAttrib1dv", total, loaded);
		glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)GetProc("glVertexAttrib1f", total, loaded);
		glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)GetProc("glVertexAttrib1fv", total, loaded);
		glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)GetProc("glVertexAttrib1s", total, loaded);
		glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)GetProc("glVertexAttrib1sv", total, loaded);
		glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)GetProc("glVertexAttrib2d", total, loaded);
		glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)GetProc("glVertexAttrib2dv", total, loaded);
		glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)GetProc("glVertexAttrib2f", total, loaded);
		glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)GetProc("glVertexAttrib2fv", total, loaded);
		glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)GetProc("glVertexAttrib2s", total, loaded);
		glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)GetProc("glVertexAttrib2sv", total, loaded);
		glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)GetProc("glVertexAttrib3d", total, loaded);
		glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)GetProc("glVertexAttrib3dv", total, loaded);
		glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)GetProc("glVertexAttrib3f", total, loaded);
		glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)GetProc("glVertexAttrib3fv", total, loaded);
		glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)GetProc("glVertexAttrib3s", total, loaded);
		glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)GetProc("glVertexAttrib3sv", total, loaded);
		glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)GetProc("glVertexAttrib4Nbv", total, loaded);
		glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)GetProc("glVertexAttrib4Niv", total, loaded);
		glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)GetProc("glVertexAttrib4Nsv", total, loaded);
		glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)GetProc("glVertexAttrib4Nub", total, loaded);
		glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)GetProc("glVertexAttrib4Nubv", total, loaded);
		glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)GetProc("glVertexAttrib4Nuiv", total, loaded);
		glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)GetProc("glVertexAttrib4Nusv", total, loaded);
		glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)GetProc("glVertexAttrib4bv", total, loaded);
		glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)GetProc("glVertexAttrib4d", total, loaded);
		glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)GetProc("glVertexAttrib4dv", total, loaded);
		glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)GetProc("glVertexAttrib4f", total, loaded);
		glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)GetProc("glVertexAttrib4fv", total, loaded);
		glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)GetProc("glVertexAttrib4iv", total, loaded);
		glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)GetProc("glVertexAttrib4s", total, loaded);
		glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)GetProc("glVertexAttrib4sv", total, loaded);
		glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)GetProc("glVertexAttrib4ubv", total, loaded);
		glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)GetProc("glVertexAttrib4uiv", total, loaded);
		glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)GetProc("glVertexAttrib4usv", total, loaded);
		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)GetProc("glVertexAttribPointer", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 2.0" << std::endl;
	#endif
		// 2.1
		total = loaded = 0;
		glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)GetProc("glUniformMatrix2x3fv", total, loaded);
		glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)GetProc("glUniformMatrix3x2fv", total, loaded);
		glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)GetProc("glUniformMatrix2x4fv", total, loaded);
		glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)GetProc("glUniformMatrix4x2fv", total, loaded);
		glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)GetProc("glUniformMatrix3x4fv", total, loaded);
		glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)GetProc("glUniformMatrix4x3fv", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 2.1" << std::endl;
	#endif
		// 3.0
		total = loaded = 0;
		glColorMaski = (PFNGLCOLORMASKIPROC)GetProc("glColorMaski", total, loaded);
		glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC)GetProc("glGetBooleani_v", total, loaded);
		glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)GetProc("glGetIntegeri_v", total, loaded);
		glEnablei = (PFNGLENABLEIPROC)GetProc("glEnablei", total, loaded);
		glDisablei = (PFNGLDISABLEIPROC)GetProc("glDisablei", total, loaded);
		glIsEnabledi = (PFNGLISENABLEDIPROC)GetProc("glIsEnabledi", total, loaded);
		glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC)GetProc("glBeginTransformFeedback", total, loaded);
		glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC)GetProc("glEndTransformFeedback", total, loaded);
		glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)GetProc("glBindBufferRange", total, loaded);
		glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)GetProc("glBindBufferBase", total, loaded);
		glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)GetProc("glTransformFeedbackVaryings", total, loaded);
		glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)GetProc("glGetTransformFeedbackVarying", total, loaded);
		glClampColor = (PFNGLCLAMPCOLORPROC)GetProc("glClampColor", total, loaded);
		glBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC)GetProc("glBeginConditionalRender", total, loaded);
		glEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC)GetProc("glEndConditionalRender", total, loaded);
		glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)GetProc("glVertexAttribIPointer", total, loaded);
		glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC)GetProc("glGetVertexAttribIiv", total, loaded);
		glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)GetProc("glGetVertexAttribIuiv", total, loaded);
		glVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC)GetProc("glVertexAttribI1i", total, loaded);
		glVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC)GetProc("glVertexAttribI2i", total, loaded);
		glVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC)GetProc("glVertexAttribI3i", total, loaded);
		glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC)GetProc("glVertexAttribI4i", total, loaded);
		glVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC)GetProc("glVertexAttribI1ui", total, loaded);
		glVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC)GetProc("glVertexAttribI2ui", total, loaded);
		glVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC)GetProc("glVertexAttribI3ui", total, loaded);
		glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC)GetProc("glVertexAttribI4ui", total, loaded);
		glVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC)GetProc("glVertexAttribI1iv", total, loaded);
		glVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC)GetProc("glVertexAttribI2iv", total, loaded);
		glVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC)GetProc("glVertexAttribI3iv", total, loaded);
		glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC)GetProc("glVertexAttribI4iv", total, loaded);
		glVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC)GetProc("glVertexAttribI1uiv", total, loaded);
		glVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC)GetProc("glVertexAttribI2uiv", total, loaded);
		glVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC)GetProc("glVertexAttribI3uiv", total, loaded);
		glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)GetProc("glVertexAttribI4uiv", total, loaded);
		glVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC)GetProc("glVertexAttribI4bv", total, loaded);
		glVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC)GetProc("glVertexAttribI4sv", total, loaded);
		glVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC)GetProc("glVertexAttribI4ubv", total, loaded);
		glVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC)GetProc("glVertexAttribI4usv", total, loaded);
		glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC)GetProc("glGetUniformuiv", total, loaded);
		glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)GetProc("glBindFragDataLocation", total, loaded);
		glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC)GetProc("glGetFragDataLocation", total, loaded);
		glUniform1ui = (PFNGLUNIFORM1UIPROC)GetProc("glUniform1ui", total, loaded);
		glUniform2ui = (PFNGLUNIFORM2UIPROC)GetProc("glUniform2ui", total, loaded);
		glUniform3ui = (PFNGLUNIFORM3UIPROC)GetProc("glUniform3ui", total, loaded);
		glUniform4ui = (PFNGLUNIFORM4UIPROC)GetProc("glUniform4ui", total, loaded);
		glUniform1uiv = (PFNGLUNIFORM1UIVPROC)GetProc("glUniform1uiv", total, loaded);
		glUniform2uiv = (PFNGLUNIFORM2UIVPROC)GetProc("glUniform2uiv", total, loaded);
		glUniform3uiv = (PFNGLUNIFORM3UIVPROC)GetProc("glUniform3uiv", total, loaded);
		glUniform4uiv = (PFNGLUNIFORM4UIVPROC)GetProc("glUniform4uiv", total, loaded);
		glTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC)GetProc("glTexParameterIiv", total, loaded);
		glTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC)GetProc("glTexParameterIuiv", total, loaded);
		glGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC)GetProc("glGetTexParameterIiv", total, loaded);
		glGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC)GetProc("glGetTexParameterIuiv", total, loaded);
		glClearBufferiv = (PFNGLCLEARBUFFERIVPROC)GetProc("glClearBufferiv", total, loaded);
		glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC)GetProc("glClearBufferuiv", total, loaded);
		glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)GetProc("glClearBufferfv", total, loaded);
		glClearBufferfi = (PFNGLCLEARBUFFERFIPROC)GetProc("glClearBufferfi", total, loaded);
		glGetStringi = (PFNGLGETSTRINGIPROC)GetProc("glGetStringi", total, loaded);
		glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)GetProc("glIsRenderbuffer", total, loaded);
		glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)GetProc("glBindRenderbuffer", total, loaded);
		glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)GetProc("glDeleteRenderbuffers", total, loaded);
		glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)GetProc("glGenRenderbuffers", total, loaded);
		glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)GetProc("glRenderbufferStorage", total, loaded);
		glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)GetProc("glGetRenderbufferParameteriv", total, loaded);
		glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)GetProc("glIsFramebuffer", total, loaded);
		glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)GetProc("glBindFramebuffer", total, loaded);
		glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)GetProc("glDeleteFramebuffers", total, loaded);
		glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)GetProc("glGenFramebuffers", total, loaded);
		glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)GetProc("glCheckFramebufferStatus", total, loaded);
		glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)GetProc("glFramebufferTexture1D", total, loaded);
		glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)GetProc("glFramebufferTexture2D", total, loaded);
		glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)GetProc("glFramebufferTexture3D", total, loaded);
		glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)GetProc("glFramebufferRenderbuffer", total, loaded);
		glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)GetProc("glGetFramebufferAttachmentParameteriv", total, loaded);
		glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)GetProc("glGenerateMipmap", total, loaded);
		glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)GetProc("glBlitFramebuffer", total, loaded);
		glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)GetProc("glRenderbufferStorageMultisample", total, loaded);
		glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)GetProc("glFramebufferTextureLayer", total, loaded);
		glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)GetProc("glMapBufferRange", total, loaded);
		glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)GetProc("glFlushMappedBufferRange", total, loaded);
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)GetProc("glBindVertexArray", total, loaded);
		glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)GetProc("glDeleteVertexArrays", total, loaded);
		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)GetProc("glGenVertexArrays", total, loaded);
		glIsVertexArray = (PFNGLISVERTEXARRAYPROC)GetProc("glIsVertexArray", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 3.0" << std::endl;
	#endif
		// 3.1
		total = loaded = 0;
		glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)GetProc("glDrawArraysInstanced", total, loaded);
		glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)GetProc("glDrawElementsInstanced", total, loaded);
		glTexBuffer = (PFNGLTEXBUFFERPROC)GetProc("glTexBuffer", total, loaded);
		glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)GetProc("glPrimitiveRestartIndex", total, loaded);
		glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC)GetProc("glCopyBufferSubData", total, loaded);
		glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)GetProc("glGetUniformIndices", total, loaded);
		glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)GetProc("glGetActiveUniformsiv", total, loaded);
		glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)GetProc("glGetActiveUniformName", total, loaded);
		glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)GetProc("glGetUniformBlockIndex", total, loaded);
		glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)GetProc("glGetActiveUniformBlockiv", total, loaded);
		glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)GetProc("glGetActiveUniformBlockName", total, loaded);
		glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)GetProc("glUniformBlockBinding", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 3.1" << std::endl;
	#endif
		// 3.2
		total = loaded = 0;
		glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)GetProc("glDrawElementsBaseVertex", total, loaded);
		glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)GetProc("glDrawRangeElementsBaseVertex", total, loaded);
		glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)GetProc("glDrawElementsInstancedBaseVertex", total, loaded);
		glMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)GetProc("glMultiDrawElementsBaseVertex", total, loaded);
		glProvokingVertex = (PFNGLPROVOKINGVERTEXPROC)GetProc("glProvokingVertex", total, loaded);
		glFenceSync = (PFNGLFENCESYNCPROC)GetProc("glFenceSync", total, loaded);
		glIsSync = (PFNGLISSYNCPROC)GetProc("glIsSync", total, loaded);
		glDeleteSync = (PFNGLDELETESYNCPROC)GetProc("glDeleteSync", total, loaded);
		glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC)GetProc("glClientWaitSync", total, loaded);
		glWaitSync = (PFNGLWAITSYNCPROC)GetProc("glWaitSync", total, loaded);
		glGetInteger64v = (PFNGLGETINTEGER64VPROC)GetProc("glGetInteger64v", total, loaded);
		glGetSynciv = (PFNGLGETSYNCIVPROC)GetProc("glGetSynciv", total, loaded);
		glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC)GetProc("glGetInteger64i_v", total, loaded);
		glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC)GetProc("glGetBufferParameteri64v", total, loaded);
		glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)GetProc("glFramebufferTexture", total, loaded);
		glTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)GetProc("glTexImage2DMultisample", total, loaded);
		glTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)GetProc("glTexImage3DMultisample", total, loaded);
		glGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC)GetProc("glGetMultisamplefv", total, loaded);
		glSampleMaski = (PFNGLSAMPLEMASKIPROC)GetProc("glSampleMaski", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 3.2" << std::endl;
	#endif
		// 3.3
		total = loaded = 0;
		glBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)GetProc("glBindFragDataLocationIndexed", total, loaded);
		glGetFragDataIndex = (PFNGLGETFRAGDATAINDEXPROC)GetProc("glGetFragDataIndex", total, loaded);
		glGenSamplers = (PFNGLGENSAMPLERSPROC)GetProc("glGenSamplers", total, loaded);
		glDeleteSamplers = (PFNGLDELETESAMPLERSPROC)GetProc("glDeleteSamplers", total, loaded);
		glIsSampler = (PFNGLISSAMPLERPROC)GetProc("glIsSampler", total, loaded);
		glBindSampler = (PFNGLBINDSAMPLERPROC)GetProc("glBindSampler", total, loaded);
		glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC)GetProc("glSamplerParameteri", total, loaded);
		glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC)GetProc("glSamplerParameteriv", total, loaded);
		glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC)GetProc("glSamplerParameterf", total, loaded);
		glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC)GetProc("glSamplerParameterfv", total, loaded);
		glSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC)GetProc("glSamplerParameterIiv", total, loaded);
		glSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC)GetProc("glSamplerParameterIuiv", total, loaded);
		glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC)GetProc("glGetSamplerParameteriv", total, loaded);
		glGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC)GetProc("glGetSamplerParameterIiv", total, loaded);
		glGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC)GetProc("glGetSamplerParameterfv", total, loaded);
		glGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC)GetProc("glGetSamplerParameterIuiv", total, loaded);
		glQueryCounter = (PFNGLQUERYCOUNTERPROC)GetProc("glQueryCounter", total, loaded);
		glGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC)GetProc("glGetQueryObjecti64v", total, loaded);
		glGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC)GetProc("glGetQueryObjectui64v", total, loaded);
		glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)GetProc("glVertexAttribDivisor", total, loaded);
		glVertexAttribP1ui = (PFNGLVERTEXATTRIBP1UIPROC)GetProc("glVertexAttribP1ui", total, loaded);
		glVertexAttribP1uiv = (PFNGLVERTEXATTRIBP1UIVPROC)GetProc("glVertexAttribP1uiv", total, loaded);
		glVertexAttribP2ui = (PFNGLVERTEXATTRIBP2UIPROC)GetProc("glVertexAttribP2ui", total, loaded);
		glVertexAttribP2uiv = (PFNGLVERTEXATTRIBP2UIVPROC)GetProc("glVertexAttribP2uiv", total, loaded);
		glVertexAttribP3ui = (PFNGLVERTEXATTRIBP3UIPROC)GetProc("glVertexAttribP3ui", total, loaded);
		glVertexAttribP3uiv = (PFNGLVERTEXATTRIBP3UIVPROC)GetProc("glVertexAttribP3uiv", total, loaded);
		glVertexAttribP4ui = (PFNGLVERTEXATTRIBP4UIPROC)GetProc("glVertexAttribP4ui", total, loaded);
		glVertexAttribP4uiv = (PFNGLVERTEXATTRIBP4UIVPROC)GetProc("glVertexAttribP4uiv", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 3.3" << std::endl;
	#endif
		// 4.0
		total = loaded = 0;
		glMinSampleShading = (PFNGLMINSAMPLESHADINGPROC)GetProc("glMinSampleShading", total, loaded);
		glBlendEquationi = (PFNGLBLENDEQUATIONIPROC)GetProc("glBlendEquationi", total, loaded);
		glBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC)GetProc("glBlendEquationSeparatei", total, loaded);
		glBlendFunci = (PFNGLBLENDFUNCIPROC)GetProc("glBlendFunci", total, loaded);
		glBlendFuncSeparatei = (PFNGLBLENDFUNCSEPARATEIPROC)GetProc("glBlendFuncSeparatei", total, loaded);
		glDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC)GetProc("glDrawArraysIndirect", total, loaded);
		glDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC)GetProc("glDrawElementsIndirect", total, loaded);
		glUniform1d = (PFNGLUNIFORM1DPROC)GetProc("glUniform1d", total, loaded);
		glUniform2d = (PFNGLUNIFORM2DPROC)GetProc("glUniform2d", total, loaded);
		glUniform3d = (PFNGLUNIFORM3DPROC)GetProc("glUniform3d", total, loaded);
		glUniform4d = (PFNGLUNIFORM4DPROC)GetProc("glUniform4d", total, loaded);
		glUniform1dv = (PFNGLUNIFORM1DVPROC)GetProc("glUniform1dv", total, loaded);
		glUniform2dv = (PFNGLUNIFORM2DVPROC)GetProc("glUniform2dv", total, loaded);
		glUniform3dv = (PFNGLUNIFORM3DVPROC)GetProc("glUniform3dv", total, loaded);
		glUniform4dv = (PFNGLUNIFORM4DVPROC)GetProc("glUniform4dv", total, loaded);
		glUniformMatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC)GetProc("glUniformMatrix2dv", total, loaded);
		glUniformMatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC)GetProc("glUniformMatrix3dv", total, loaded);
		glUniformMatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC)GetProc("glUniformMatrix4dv", total, loaded);
		glUniformMatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC)GetProc("glUniformMatrix2x3dv", total, loaded);
		glUniformMatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC)GetProc("glUniformMatrix2x4dv", total, loaded);
		glUniformMatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC)GetProc("glUniformMatrix3x2dv", total, loaded);
		glUniformMatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC)GetProc("glUniformMatrix3x4dv", total, loaded);
		glUniformMatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC)GetProc("glUniformMatrix4x2dv", total, loaded);
		glUniformMatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC)GetProc("glUniformMatrix4x3dv", total, loaded);
		glGetUniformdv = (PFNGLGETUNIFORMDVPROC)GetProc("glGetUniformdv", total, loaded);
		glGetSubroutineUniformLocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)GetProc("glGetSubroutineUniformLocation", total, loaded);
		glGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC)GetProc("glGetSubroutineIndex", total, loaded);
		glGetActiveSubroutineUniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)GetProc("glGetActiveSubroutineUniformiv", total, loaded);
		glGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)GetProc("glGetActiveSubroutineUniformName", total, loaded);
		glGetActiveSubroutineName = (PFNGLGETACTIVESUBROUTINENAMEPROC)GetProc("glGetActiveSubroutineName", total, loaded);
		glUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC)GetProc("glUniformSubroutinesuiv", total, loaded);
		glGetUniformSubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC)GetProc("glGetUniformSubroutineuiv", total, loaded);
		glGetProgramStageiv = (PFNGLGETPROGRAMSTAGEIVPROC)GetProc("glGetProgramStageiv", total, loaded);
		glPatchParameteri = (PFNGLPATCHPARAMETERIPROC)GetProc("glPatchParameteri", total, loaded);
		glPatchParameterfv = (PFNGLPATCHPARAMETERFVPROC)GetProc("glPatchParameterfv", total, loaded);
		glBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC)GetProc("glBindTransformFeedback", total, loaded);
		glDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC)GetProc("glDeleteTransformFeedbacks", total, loaded);
		glGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC)GetProc("glGenTransformFeedbacks", total, loaded);
		glIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC)GetProc("glIsTransformFeedback", total, loaded);
		glPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC)GetProc("glPauseTransformFeedback", total, loaded);
		glResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC)GetProc("glResumeTransformFeedback", total, loaded);
		glDrawTransformFeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC)GetProc("glDrawTransformFeedback", total, loaded);
		glDrawTransformFeedbackStream = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)GetProc("glDrawTransformFeedbackStream", total, loaded);
		glBeginQueryIndexed = (PFNGLBEGINQUERYINDEXEDPROC)GetProc("glBeginQueryIndexed", total, loaded);
		glEndQueryIndexed = (PFNGLENDQUERYINDEXEDPROC)GetProc("glEndQueryIndexed", total, loaded);
		glGetQueryIndexediv = (PFNGLGETQUERYINDEXEDIVPROC)GetProc("glGetQueryIndexediv", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 4.0" << std::endl;
	#endif
		// 4.1
		total = loaded = 0;
		glReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC)GetProc("glReleaseShaderCompiler", total, loaded);
		glShaderBinary = (PFNGLSHADERBINARYPROC)GetProc("glShaderBinary", total, loaded);
		glGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC)GetProc("glGetShaderPrecisionFormat", total, loaded);
		glDepthRangef = (PFNGLDEPTHRANGEFPROC)GetProc("glDepthRangef", total, loaded);
		glClearDepthf = (PFNGLCLEARDEPTHFPROC)GetProc("glClearDepthf", total, loaded);
		glGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC)GetProc("glGetProgramBinary", total, loaded);
		glProgramBinary = (PFNGLPROGRAMBINARYPROC)GetProc("glProgramBinary", total, loaded);
		glProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC)GetProc("glProgramParameteri", total, loaded);
		glUseProgramStages = (PFNGLUSEPROGRAMSTAGESPROC)GetProc("glUseProgramStages", total, loaded);
		glActiveShaderProgram = (PFNGLACTIVESHADERPROGRAMPROC)GetProc("glActiveShaderProgram", total, loaded);
		glCreateShaderProgramv = (PFNGLCREATESHADERPROGRAMVPROC)GetProc("glCreateShaderProgramv", total, loaded);
		glBindProgramPipeline = (PFNGLBINDPROGRAMPIPELINEPROC)GetProc("glBindProgramPipeline", total, loaded);
		glDeleteProgramPipelines = (PFNGLDELETEPROGRAMPIPELINESPROC)GetProc("glDeleteProgramPipelines", total, loaded);
		glGenProgramPipelines = (PFNGLGENPROGRAMPIPELINESPROC)GetProc("glGenProgramPipelines", total, loaded);
		glIsProgramPipeline = (PFNGLISPROGRAMPIPELINEPROC)GetProc("glIsProgramPipeline", total, loaded);
		glGetProgramPipelineiv = (PFNGLGETPROGRAMPIPELINEIVPROC)GetProc("glGetProgramPipelineiv", total, loaded);
		glProgramUniform1i = (PFNGLPROGRAMUNIFORM1IPROC)GetProc("glProgramUniform1i", total, loaded);
		glProgramUniform1iv = (PFNGLPROGRAMUNIFORM1IVPROC)GetProc("glProgramUniform1iv", total, loaded);
		glProgramUniform1f = (PFNGLPROGRAMUNIFORM1FPROC)GetProc("glProgramUniform1f", total, loaded);
		glProgramUniform1fv = (PFNGLPROGRAMUNIFORM1FVPROC)GetProc("glProgramUniform1fv", total, loaded);
		glProgramUniform1d = (PFNGLPROGRAMUNIFORM1DPROC)GetProc("glProgramUniform1d", total, loaded);
		glProgramUniform1dv = (PFNGLPROGRAMUNIFORM1DVPROC)GetProc("glProgramUniform1dv", total, loaded);
		glProgramUniform1ui = (PFNGLPROGRAMUNIFORM1UIPROC)GetProc("glProgramUniform1ui", total, loaded);
		glProgramUniform1uiv = (PFNGLPROGRAMUNIFORM1UIVPROC)GetProc("glProgramUniform1uiv", total, loaded);
		glProgramUniform2i = (PFNGLPROGRAMUNIFORM2IPROC)GetProc("glProgramUniform2i", total, loaded);
		glProgramUniform2iv = (PFNGLPROGRAMUNIFORM2IVPROC)GetProc("glProgramUniform2iv", total, loaded);
		glProgramUniform2f = (PFNGLPROGRAMUNIFORM2FPROC)GetProc("glProgramUniform2f", total, loaded);
		glProgramUniform2fv = (PFNGLPROGRAMUNIFORM2FVPROC)GetProc("glProgramUniform2fv", total, loaded);
		glProgramUniform2d = (PFNGLPROGRAMUNIFORM2DPROC)GetProc("glProgramUniform2d", total, loaded);
		glProgramUniform2dv = (PFNGLPROGRAMUNIFORM2DVPROC)GetProc("glProgramUniform2dv", total, loaded);
		glProgramUniform2ui = (PFNGLPROGRAMUNIFORM2UIPROC)GetProc("glProgramUniform2ui", total, loaded);
		glProgramUniform2uiv = (PFNGLPROGRAMUNIFORM2UIVPROC)GetProc("glProgramUniform2uiv", total, loaded);
		glProgramUniform3i = (PFNGLPROGRAMUNIFORM3IPROC)GetProc("glProgramUniform3i", total, loaded);
		glProgramUniform3iv = (PFNGLPROGRAMUNIFORM3IVPROC)GetProc("glProgramUniform3iv", total, loaded);
		glProgramUniform3f = (PFNGLPROGRAMUNIFORM3FPROC)GetProc("glProgramUniform3f", total, loaded);
		glProgramUniform3fv = (PFNGLPROGRAMUNIFORM3FVPROC)GetProc("glProgramUniform3fv", total, loaded);
		glProgramUniform3d = (PFNGLPROGRAMUNIFORM3DPROC)GetProc("glProgramUniform3d", total, loaded);
		glProgramUniform3dv = (PFNGLPROGRAMUNIFORM3DVPROC)GetProc("glProgramUniform3dv", total, loaded);
		glProgramUniform3ui = (PFNGLPROGRAMUNIFORM3UIPROC)GetProc("glProgramUniform3ui", total, loaded);
		glProgramUniform3uiv = (PFNGLPROGRAMUNIFORM3UIVPROC)GetProc("glProgramUniform3uiv", total, loaded);
		glProgramUniform4i = (PFNGLPROGRAMUNIFORM4IPROC)GetProc("glProgramUniform4i", total, loaded);
		glProgramUniform4iv = (PFNGLPROGRAMUNIFORM4IVPROC)GetProc("glProgramUniform4iv", total, loaded);
		glProgramUniform4f = (PFNGLPROGRAMUNIFORM4FPROC)GetProc("glProgramUniform4f", total, loaded);
		glProgramUniform4fv = (PFNGLPROGRAMUNIFORM4FVPROC)GetProc("glProgramUniform4fv", total, loaded);
		glProgramUniform4d = (PFNGLPROGRAMUNIFORM4DPROC)GetProc("glProgramUniform4d", total, loaded);
		glProgramUniform4dv = (PFNGLPROGRAMUNIFORM4DVPROC)GetProc("glProgramUniform4dv", total, loaded);
		glProgramUniform4ui = (PFNGLPROGRAMUNIFORM4UIPROC)GetProc("glProgramUniform4ui", total, loaded);
		glProgramUniform4uiv = (PFNGLPROGRAMUNIFORM4UIVPROC)GetProc("glProgramUniform4uiv", total, loaded);
		glProgramUniformMatrix2fv = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC)GetProc("glProgramUniformMatrix2fv", total, loaded);
		glProgramUniformMatrix3fv = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC)GetProc("glProgramUniformMatrix3fv", total, loaded);
		glProgramUniformMatrix4fv = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC)GetProc("glProgramUniformMatrix4fv", total, loaded);
		glProgramUniformMatrix2dv = (PFNGLPROGRAMUNIFORMMATRIX2DVPROC)GetProc("glProgramUniformMatrix2dv", total, loaded);
		glProgramUniformMatrix3dv = (PFNGLPROGRAMUNIFORMMATRIX3DVPROC)GetProc("glProgramUniformMatrix3dv", total, loaded);
		glProgramUniformMatrix4dv = (PFNGLPROGRAMUNIFORMMATRIX4DVPROC)GetProc("glProgramUniformMatrix4dv", total, loaded);
		glProgramUniformMatrix2x3fv = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)GetProc("glProgramUniformMatrix2x3fv", total, loaded);
		glProgramUniformMatrix3x2fv = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)GetProc("glProgramUniformMatrix3x2fv", total, loaded);
		glProgramUniformMatrix2x4fv = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)GetProc("glProgramUniformMatrix2x4fv", total, loaded);
		glProgramUniformMatrix4x2fv = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)GetProc("glProgramUniformMatrix4x2fv", total, loaded);
		glProgramUniformMatrix3x4fv = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)GetProc("glProgramUniformMatrix3x4fv", total, loaded);
		glProgramUniformMatrix4x3fv = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)GetProc("glProgramUniformMatrix4x3fv", total, loaded);
		glProgramUniformMatrix2x3dv = (PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)GetProc("glProgramUniformMatrix2x3dv", total, loaded);
		glProgramUniformMatrix3x2dv = (PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)GetProc("glProgramUniformMatrix3x2dv", total, loaded);
		glProgramUniformMatrix2x4dv = (PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)GetProc("glProgramUniformMatrix2x4dv", total, loaded);
		glProgramUniformMatrix4x2dv = (PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)GetProc("glProgramUniformMatrix4x2dv", total, loaded);
		glProgramUniformMatrix3x4dv = (PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)GetProc("glProgramUniformMatrix3x4dv", total, loaded);
		glProgramUniformMatrix4x3dv = (PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)GetProc("glProgramUniformMatrix4x3dv", total, loaded);
		glValidateProgramPipeline = (PFNGLVALIDATEPROGRAMPIPELINEPROC)GetProc("glValidateProgramPipeline", total, loaded);
		glGetProgramPipelineInfoLog = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC)GetProc("glGetProgramPipelineInfoLog", total, loaded);
		glVertexAttribL1d = (PFNGLVERTEXATTRIBL1DPROC)GetProc("glVertexAttribL1d", total, loaded);
		glVertexAttribL2d = (PFNGLVERTEXATTRIBL2DPROC)GetProc("glVertexAttribL2d", total, loaded);
		glVertexAttribL3d = (PFNGLVERTEXATTRIBL3DPROC)GetProc("glVertexAttribL3d", total, loaded);
		glVertexAttribL4d = (PFNGLVERTEXATTRIBL4DPROC)GetProc("glVertexAttribL4d", total, loaded);
		glVertexAttribL1dv = (PFNGLVERTEXATTRIBL1DVPROC)GetProc("glVertexAttribL1dv", total, loaded);
		glVertexAttribL2dv = (PFNGLVERTEXATTRIBL2DVPROC)GetProc("glVertexAttribL2dv", total, loaded);
		glVertexAttribL3dv = (PFNGLVERTEXATTRIBL3DVPROC)GetProc("glVertexAttribL3dv", total, loaded);
		glVertexAttribL4dv = (PFNGLVERTEXATTRIBL4DVPROC)GetProc("glVertexAttribL4dv", total, loaded);
		glVertexAttribLPointer = (PFNGLVERTEXATTRIBLPOINTERPROC)GetProc("glVertexAttribLPointer", total, loaded);
		glGetVertexAttribLdv = (PFNGLGETVERTEXATTRIBLDVPROC)GetProc("glGetVertexAttribLdv", total, loaded);
		glViewportArrayv = (PFNGLVIEWPORTARRAYVPROC)GetProc("glViewportArrayv", total, loaded);
		glViewportIndexedf = (PFNGLVIEWPORTINDEXEDFPROC)GetProc("glViewportIndexedf", total, loaded);
		glViewportIndexedfv = (PFNGLVIEWPORTINDEXEDFVPROC)GetProc("glViewportIndexedfv", total, loaded);
		glScissorArrayv = (PFNGLSCISSORARRAYVPROC)GetProc("glScissorArrayv", total, loaded);
		glScissorIndexed = (PFNGLSCISSORINDEXEDPROC)GetProc("glScissorIndexed", total, loaded);
		glScissorIndexedv = (PFNGLSCISSORINDEXEDVPROC)GetProc("glScissorIndexedv", total, loaded);
		glDepthRangeArrayv = (PFNGLDEPTHRANGEARRAYVPROC)GetProc("glDepthRangeArrayv", total, loaded);
		glDepthRangeIndexed = (PFNGLDEPTHRANGEINDEXEDPROC)GetProc("glDepthRangeIndexed", total, loaded);
		glGetFloati_v = (PFNGLGETFLOATI_VPROC)GetProc("glGetFloati_v", total, loaded);
		glGetDoublei_v = (PFNGLGETDOUBLEI_VPROC)GetProc("glGetDoublei_v", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 4.1" << std::endl;
	#endif
		// 4.2
		total = loaded = 0;
		glDrawArraysInstancedBaseInstance = (PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)GetProc("glDrawArraysInstancedBaseInstance", total, loaded);
		glDrawElementsInstancedBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)GetProc("glDrawElementsInstancedBaseInstance", total, loaded);
		glDrawElementsInstancedBaseVertexBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)GetProc("glDrawElementsInstancedBaseVertexBaseInstance", total, loaded);
		glGetInternalformativ = (PFNGLGETINTERNALFORMATIVPROC)GetProc("glGetInternalformativ", total, loaded);
		glGetActiveAtomicCounterBufferiv = (PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)GetProc("glGetActiveAtomicCounterBufferiv", total, loaded);
		glBindImageTexture = (PFNGLBINDIMAGETEXTUREPROC)GetProc("glBindImageTexture", total, loaded);
		glMemoryBarrier = (PFNGLMEMORYBARRIERPROC)GetProc("glMemoryBarrier", total, loaded);
		glTexStorage1D = (PFNGLTEXSTORAGE1DPROC)GetProc("glTexStorage1D", total, loaded);
		glTexStorage2D = (PFNGLTEXSTORAGE2DPROC)GetProc("glTexStorage2D", total, loaded);
		glTexStorage3D = (PFNGLTEXSTORAGE3DPROC)GetProc("glTexStorage3D", total, loaded);
		glDrawTransformFeedbackInstanced = (PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)GetProc("glDrawTransformFeedbackInstanced", total, loaded);
		glDrawTransformFeedbackStreamInstanced = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)GetProc("glDrawTransformFeedbackStreamInstanced", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 4.2" << std::endl;
	#endif
		// 4.3
		total = loaded = 0;
		glClearBufferData = (PFNGLCLEARBUFFERDATAPROC)GetProc("glClearBufferData", total, loaded);
		glClearBufferSubData = (PFNGLCLEARBUFFERSUBDATAPROC)GetProc("glClearBufferSubData", total, loaded);
		glDispatchCompute = (PFNGLDISPATCHCOMPUTEPROC)GetProc("glDispatchCompute", total, loaded);
		glDispatchComputeIndirect = (PFNGLDISPATCHCOMPUTEINDIRECTPROC)GetProc("glDispatchComputeIndirect", total, loaded);
		glCopyImageSubData = (PFNGLCOPYIMAGESUBDATAPROC)GetProc("glCopyImageSubData", total, loaded);
		glFramebufferParameteri = (PFNGLFRAMEBUFFERPARAMETERIPROC)GetProc("glFramebufferParameteri", total, loaded);
		glGetFramebufferParameteriv = (PFNGLGETFRAMEBUFFERPARAMETERIVPROC)GetProc("glGetFramebufferParameteriv", total, loaded);
		glGetInternalformati64v = (PFNGLGETINTERNALFORMATI64VPROC)GetProc("glGetInternalformati64v", total, loaded);
		glInvalidateTexSubImage = (PFNGLINVALIDATETEXSUBIMAGEPROC)GetProc("glInvalidateTexSubImage", total, loaded);
		glInvalidateTexImage = (PFNGLINVALIDATETEXIMAGEPROC)GetProc("glInvalidateTexImage", total, loaded);
		glInvalidateBufferSubData = (PFNGLINVALIDATEBUFFERSUBDATAPROC)GetProc("glInvalidateBufferSubData", total, loaded);
		glInvalidateBufferData = (PFNGLINVALIDATEBUFFERDATAPROC)GetProc("glInvalidateBufferData", total, loaded);
		glInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC)GetProc("glInvalidateFramebuffer", total, loaded);
		glInvalidateSubFramebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC)GetProc("glInvalidateSubFramebuffer", total, loaded);
		glMultiDrawArraysIndirect = (PFNGLMULTIDRAWARRAYSINDIRECTPROC)GetProc("glMultiDrawArraysIndirect", total, loaded);
		glMultiDrawElementsIndirect = (PFNGLMULTIDRAWELEMENTSINDIRECTPROC)GetProc("glMultiDrawElementsIndirect", total, loaded);
		glGetProgramInterfaceiv = (PFNGLGETPROGRAMINTERFACEIVPROC)GetProc("glGetProgramInterfaceiv", total, loaded);
		glGetProgramResourceIndex = (PFNGLGETPROGRAMRESOURCEINDEXPROC)GetProc("glGetProgramResourceIndex", total, loaded);
		glGetProgramResourceName = (PFNGLGETPROGRAMRESOURCENAMEPROC)GetProc("glGetProgramResourceName", total, loaded);
		glGetProgramResourceiv = (PFNGLGETPROGRAMRESOURCEIVPROC)GetProc("glGetProgramResourceiv", total, loaded);
		glGetProgramResourceLocation = (PFNGLGETPROGRAMRESOURCELOCATIONPROC)GetProc("glGetProgramResourceLocation", total, loaded);
		glGetProgramResourceLocationIndex = (PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)GetProc("glGetProgramResourceLocationIndex", total, loaded);
		glShaderStorageBlockBinding = (PFNGLSHADERSTORAGEBLOCKBINDINGPROC)GetProc("glShaderStorageBlockBinding", total, loaded);
		glTexBufferRange = (PFNGLTEXBUFFERRANGEPROC)GetProc("glTexBufferRange", total, loaded);
		glTexStorage2DMultisample = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC)GetProc("glTexStorage2DMultisample", total, loaded);
		glTexStorage3DMultisample = (PFNGLTEXSTORAGE3DMULTISAMPLEPROC)GetProc("glTexStorage3DMultisample", total, loaded);
		glTextureView = (PFNGLTEXTUREVIEWPROC)GetProc("glTextureView", total, loaded);
		glBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC)GetProc("glBindVertexBuffer", total, loaded);
		glVertexAttribFormat = (PFNGLVERTEXATTRIBFORMATPROC)GetProc("glVertexAttribFormat", total, loaded);
		glVertexAttribIFormat = (PFNGLVERTEXATTRIBIFORMATPROC)GetProc("glVertexAttribIFormat", total, loaded);
		glVertexAttribLFormat = (PFNGLVERTEXATTRIBLFORMATPROC)GetProc("glVertexAttribLFormat", total, loaded);
		glVertexAttribBinding = (PFNGLVERTEXATTRIBBINDINGPROC)GetProc("glVertexAttribBinding", total, loaded);
		glVertexBindingDivisor = (PFNGLVERTEXBINDINGDIVISORPROC)GetProc("glVertexBindingDivisor", total, loaded);
		glDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC)GetProc("glDebugMessageControl", total, loaded);
		glDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC)GetProc("glDebugMessageInsert", total, loaded);
		glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)GetProc("glDebugMessageCallback", total, loaded);
		glGetDebugMessageLog = (PFNGLGETDEBUGMESSAGELOGPROC)GetProc("glGetDebugMessageLog", total, loaded);
		glPushDebugGroup = (PFNGLPUSHDEBUGGROUPPROC)GetProc("glPushDebugGroup", total, loaded);
		glPopDebugGroup = (PFNGLPOPDEBUGGROUPPROC)GetProc("glPopDebugGroup", total, loaded);
		glObjectLabel = (PFNGLOBJECTLABELPROC)GetProc("glObjectLabel", total, loaded);
		glGetObjectLabel = (PFNGLGETOBJECTLABELPROC)GetProc("glGetObjectLabel", total, loaded);
		glObjectPtrLabel = (PFNGLOBJECTPTRLABELPROC)GetProc("glObjectPtrLabel", total, loaded);
		glGetObjectPtrLabel = (PFNGLGETOBJECTPTRLABELPROC)GetProc("glGetObjectPtrLabel", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 4.3" << std::endl;
	#endif
		// 4.4
		total = loaded = 0;
		glBufferStorage = (PFNGLBUFFERSTORAGEPROC)GetProc("glBufferStorage", total, loaded);
		glClearTexImage = (PFNGLCLEARTEXIMAGEPROC)GetProc("glClearTexImage", total, loaded);
		glClearTexSubImage = (PFNGLCLEARTEXSUBIMAGEPROC)GetProc("glClearTexSubImage", total, loaded);
		glBindBuffersBase = (PFNGLBINDBUFFERSBASEPROC)GetProc("glBindBuffersBase", total, loaded);
		glBindBuffersRange = (PFNGLBINDBUFFERSRANGEPROC)GetProc("glBindBuffersRange", total, loaded);
		glBindTextures = (PFNGLBINDTEXTURESPROC)GetProc("glBindTextures", total, loaded);
		glBindSamplers = (PFNGLBINDSAMPLERSPROC)GetProc("glBindSamplers", total, loaded);
		glBindImageTextures = (PFNGLBINDIMAGETEXTURESPROC)GetProc("glBindImageTextures", total, loaded);
		glBindVertexBuffers = (PFNGLBINDVERTEXBUFFERSPROC)GetProc("glBindVertexBuffers", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 4.4" << std::endl;
	#endif
		// 4.5
		total = loaded = 0;
		glClipControl = (PFNGLCLIPCONTROLPROC)GetProc("glClipControl", total, loaded);
		glCreateTransformFeedbacks = (PFNGLCREATETRANSFORMFEEDBACKSPROC)GetProc("glCreateTransformFeedbacks", total, loaded);
		glTransformFeedbackBufferBase = (PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC)GetProc("glTransformFeedbackBufferBase", total, loaded);
		glTransformFeedbackBufferRange = (PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC)GetProc("glTransformFeedbackBufferRange", total, loaded);
		glGetTransformFeedbackiv = (PFNGLGETTRANSFORMFEEDBACKIVPROC)GetProc("glGetTransformFeedbackiv", total, loaded);
		glGetTransformFeedbacki_v = (PFNGLGETTRANSFORMFEEDBACKI_VPROC)GetProc("glGetTransformFeedbacki_v", total, loaded);
		glGetTransformFeedbacki64_v = (PFNGLGETTRANSFORMFEEDBACKI64_VPROC)GetProc("glGetTransformFeedbacki64_v", total, loaded);
		glCreateBuffers = (PFNGLCREATEBUFFERSPROC)GetProc("glCreateBuffers", total, loaded);
		glNamedBufferStorage = (PFNGLNAMEDBUFFERSTORAGEPROC)GetProc("glNamedBufferStorage", total, loaded);
		glNamedBufferData = (PFNGLNAMEDBUFFERDATAPROC)GetProc("glNamedBufferData", total, loaded);
		glNamedBufferSubData = (PFNGLNAMEDBUFFERSUBDATAPROC)GetProc("glNamedBufferSubData", total, loaded);
		glCopyNamedBufferSubData = (PFNGLCOPYNAMEDBUFFERSUBDATAPROC)GetProc("glCopyNamedBufferSubData", total, loaded);
		glClearNamedBufferData = (PFNGLCLEARNAMEDBUFFERDATAPROC)GetProc("glClearNamedBufferData", total, loaded);
		glClearNamedBufferSubData = (PFNGLCLEARNAMEDBUFFERSUBDATAPROC)GetProc("glClearNamedBufferSubData", total, loaded);
		glMapNamedBuffer = (PFNGLMAPNAMEDBUFFERPROC)GetProc("glMapNamedBuffer", total, loaded);
		glMapNamedBufferRange = (PFNGLMAPNAMEDBUFFERRANGEPROC)GetProc("glMapNamedBufferRange", total, loaded);
		glUnmapNamedBuffer = (PFNGLUNMAPNAMEDBUFFERPROC)GetProc("glUnmapNamedBuffer", total, loaded);
		glFlushMappedNamedBufferRange = (PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC)GetProc("glFlushMappedNamedBufferRange", total, loaded);
		glGetNamedBufferParameteriv = (PFNGLGETNAMEDBUFFERPARAMETERIVPROC)GetProc("glGetNamedBufferParameteriv", total, loaded);
		glGetNamedBufferParameteri64v = (PFNGLGETNAMEDBUFFERPARAMETERI64VPROC)GetProc("glGetNamedBufferParameteri64v", total, loaded);
		glGetNamedBufferPointerv = (PFNGLGETNAMEDBUFFERPOINTERVPROC)GetProc("glGetNamedBufferPointerv", total, loaded);
		glGetNamedBufferSubData = (PFNGLGETNAMEDBUFFERSUBDATAPROC)GetProc("glGetNamedBufferSubData", total, loaded);
		glCreateFramebuffers = (PFNGLCREATEFRAMEBUFFERSPROC)GetProc("glCreateFramebuffers", total, loaded);
		glNamedFramebufferRenderbuffer = (PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC)GetProc("glNamedFramebufferRenderbuffer", total, loaded);
		glNamedFramebufferParameteri = (PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC)GetProc("glNamedFramebufferParameteri", total, loaded);
		glNamedFramebufferTexture = (PFNGLNAMEDFRAMEBUFFERTEXTUREPROC)GetProc("glNamedFramebufferTexture", total, loaded);
		glNamedFramebufferTextureLayer = (PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC)GetProc("glNamedFramebufferTextureLayer", total, loaded);
		glNamedFramebufferDrawBuffer = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC)GetProc("glNamedFramebufferDrawBuffer", total, loaded);
		glNamedFramebufferDrawBuffers = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC)GetProc("glNamedFramebufferDrawBuffers", total, loaded);
		glNamedFramebufferReadBuffer = (PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC)GetProc("glNamedFramebufferReadBuffer", total, loaded);
		glInvalidateNamedFramebufferData = (PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC)GetProc("glInvalidateNamedFramebufferData", total, loaded);
		glInvalidateNamedFramebufferSubData = (PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)GetProc("glInvalidateNamedFramebufferSubData", total, loaded);
		glClearNamedFramebufferiv = (PFNGLCLEARNAMEDFRAMEBUFFERIVPROC)GetProc("glClearNamedFramebufferiv", total, loaded);
		glClearNamedFramebufferuiv = (PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC)GetProc("glClearNamedFramebufferuiv", total, loaded);
		glClearNamedFramebufferfv = (PFNGLCLEARNAMEDFRAMEBUFFERFVPROC)GetProc("glClearNamedFramebufferfv", total, loaded);
		glClearNamedFramebufferfi = (PFNGLCLEARNAMEDFRAMEBUFFERFIPROC)GetProc("glClearNamedFramebufferfi", total, loaded);
		glBlitNamedFramebuffer = (PFNGLBLITNAMEDFRAMEBUFFERPROC)GetProc("glBlitNamedFramebuffer", total, loaded);
		glCheckNamedFramebufferStatus = (PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC)GetProc("glCheckNamedFramebufferStatus", total, loaded);
		glGetNamedFramebufferParameteriv = (PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC)GetProc("glGetNamedFramebufferParameteriv", total, loaded);
		glGetNamedFramebufferAttachmentParameteriv = (PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)GetProc("glGetNamedFramebufferAttachmentParameteriv", total, loaded);
		glCreateRenderbuffers = (PFNGLCREATERENDERBUFFERSPROC)GetProc("glCreateRenderbuffers", total, loaded);
		glNamedRenderbufferStorage = (PFNGLNAMEDRENDERBUFFERSTORAGEPROC)GetProc("glNamedRenderbufferStorage", total, loaded);
		glNamedRenderbufferStorageMultisample = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)GetProc("glNamedRenderbufferStorageMultisample", total, loaded);
		glGetNamedRenderbufferParameteriv = (PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC)GetProc("glGetNamedRenderbufferParameteriv", total, loaded);
		glCreateTextures = (PFNGLCREATETEXTURESPROC)GetProc("glCreateTextures", total, loaded);
		glTextureBuffer = (PFNGLTEXTUREBUFFERPROC)GetProc("glTextureBuffer", total, loaded);
		glTextureBufferRange = (PFNGLTEXTUREBUFFERRANGEPROC)GetProc("glTextureBufferRange", total, loaded);
		glTextureStorage1D = (PFNGLTEXTURESTORAGE1DPROC)GetProc("glTextureStorage1D", total, loaded);
		glTextureStorage2D = (PFNGLTEXTURESTORAGE2DPROC)GetProc("glTextureStorage2D", total, loaded);
		glTextureStorage3D = (PFNGLTEXTURESTORAGE3DPROC)GetProc("glTextureStorage3D", total, loaded);
		glTextureStorage2DMultisample = (PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC)GetProc("glTextureStorage2DMultisample", total, loaded);
		glTextureStorage3DMultisample = (PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC)GetProc("glTextureStorage3DMultisample", total, loaded);
		glTextureSubImage1D = (PFNGLTEXTURESUBIMAGE1DPROC)GetProc("glTextureSubImage1D", total, loaded);
		glTextureSubImage2D = (PFNGLTEXTURESUBIMAGE2DPROC)GetProc("glTextureSubImage2D", total, loaded);
		glTextureSubImage3D = (PFNGLTEXTURESUBIMAGE3DPROC)GetProc("glTextureSubImage3D", total, loaded);
		glCompressedTextureSubImage1D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC)GetProc("glCompressedTextureSubImage1D", total, loaded);
		glCompressedTextureSubImage2D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC)GetProc("glCompressedTextureSubImage2D", total, loaded);
		glCompressedTextureSubImage3D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC)GetProc("glCompressedTextureSubImage3D", total, loaded);
		glCopyTextureSubImage1D = (PFNGLCOPYTEXTURESUBIMAGE1DPROC)GetProc("glCopyTextureSubImage1D", total, loaded);
		glCopyTextureSubImage2D = (PFNGLCOPYTEXTURESUBIMAGE2DPROC)GetProc("glCopyTextureSubImage2D", total, loaded);
		glCopyTextureSubImage3D = (PFNGLCOPYTEXTURESUBIMAGE3DPROC)GetProc("glCopyTextureSubImage3D", total, loaded);
		glTextureParameterf = (PFNGLTEXTUREPARAMETERFPROC)GetProc("glTextureParameterf", total, loaded);
		glTextureParameterfv = (PFNGLTEXTUREPARAMETERFVPROC)GetProc("glTextureParameterfv", total, loaded);
		glTextureParameteri = (PFNGLTEXTUREPARAMETERIPROC)GetProc("glTextureParameteri", total, loaded);
		glTextureParameterIiv = (PFNGLTEXTUREPARAMETERIIVPROC)GetProc("glTextureParameterIiv", total, loaded);
		glTextureParameterIuiv = (PFNGLTEXTUREPARAMETERIUIVPROC)GetProc("glTextureParameterIuiv", total, loaded);
		glTextureParameteriv = (PFNGLTEXTUREPARAMETERIVPROC)GetProc("glTextureParameteriv", total, loaded);
		glGenerateTextureMipmap = (PFNGLGENERATETEXTUREMIPMAPPROC)GetProc("glGenerateTextureMipmap", total, loaded);
		glBindTextureUnit = (PFNGLBINDTEXTUREUNITPROC)GetProc("glBindTextureUnit", total, loaded);
		glGetTextureImage = (PFNGLGETTEXTUREIMAGEPROC)GetProc("glGetTextureImage", total, loaded);
		glGetCompressedTextureImage = (PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC)GetProc("glGetCompressedTextureImage", total, loaded);
		glGetTextureLevelParameterfv = (PFNGLGETTEXTURELEVELPARAMETERFVPROC)GetProc("glGetTextureLevelParameterfv", total, loaded);
		glGetTextureLevelParameteriv = (PFNGLGETTEXTURELEVELPARAMETERIVPROC)GetProc("glGetTextureLevelParameteriv", total, loaded);
		glGetTextureParameterfv = (PFNGLGETTEXTUREPARAMETERFVPROC)GetProc("glGetTextureParameterfv", total, loaded);
		glGetTextureParameterIiv = (PFNGLGETTEXTUREPARAMETERIIVPROC)GetProc("glGetTextureParameterIiv", total, loaded);
		glGetTextureParameterIuiv = (PFNGLGETTEXTUREPARAMETERIUIVPROC)GetProc("glGetTextureParameterIuiv", total, loaded);
		glGetTextureParameteriv = (PFNGLGETTEXTUREPARAMETERIVPROC)GetProc("glGetTextureParameteriv", total, loaded);
		glCreateVertexArrays = (PFNGLCREATEVERTEXARRAYSPROC)GetProc("glCreateVertexArrays", total, loaded);
		glDisableVertexArrayAttrib = (PFNGLDISABLEVERTEXARRAYATTRIBPROC)GetProc("glDisableVertexArrayAttrib", total, loaded);
		glEnableVertexArrayAttrib = (PFNGLENABLEVERTEXARRAYATTRIBPROC)GetProc("glEnableVertexArrayAttrib", total, loaded);
		glVertexArrayElementBuffer = (PFNGLVERTEXARRAYELEMENTBUFFERPROC)GetProc("glVertexArrayElementBuffer", total, loaded);
		glVertexArrayVertexBuffer = (PFNGLVERTEXARRAYVERTEXBUFFERPROC)GetProc("glVertexArrayVertexBuffer", total, loaded);
		glVertexArrayVertexBuffers = (PFNGLVERTEXARRAYVERTEXBUFFERSPROC)GetProc("glVertexArrayVertexBuffers", total, loaded);
		glVertexArrayAttribBinding = (PFNGLVERTEXARRAYATTRIBBINDINGPROC)GetProc("glVertexArrayAttribBinding", total, loaded);
		glVertexArrayAttribFormat = (PFNGLVERTEXARRAYATTRIBFORMATPROC)GetProc("glVertexArrayAttribFormat", total, loaded);
		glVertexArrayAttribIFormat = (PFNGLVERTEXARRAYATTRIBIFORMATPROC)GetProc("glVertexArrayAttribIFormat", total, loaded);
		glVertexArrayAttribLFormat = (PFNGLVERTEXARRAYATTRIBLFORMATPROC)GetProc("glVertexArrayAttribLFormat", total, loaded);
		glVertexArrayBindingDivisor = (PFNGLVERTEXARRAYBINDINGDIVISORPROC)GetProc("glVertexArrayBindingDivisor", total, loaded);
		glGetVertexArrayiv = (PFNGLGETVERTEXARRAYIVPROC)GetProc("glGetVertexArrayiv", total, loaded);
		glGetVertexArrayIndexediv = (PFNGLGETVERTEXARRAYINDEXEDIVPROC)GetProc("glGetVertexArrayIndexediv", total, loaded);
		glGetVertexArrayIndexed64iv = (PFNGLGETVERTEXARRAYINDEXED64IVPROC)GetProc("glGetVertexArrayIndexed64iv", total, loaded);
		glCreateSamplers = (PFNGLCREATESAMPLERSPROC)GetProc("glCreateSamplers", total, loaded);
		glCreateProgramPipelines = (PFNGLCREATEPROGRAMPIPELINESPROC)GetProc("glCreateProgramPipelines", total, loaded);
		glCreateQueries = (PFNGLCREATEQUERIESPROC)GetProc("glCreateQueries", total, loaded);
		glGetQueryBufferObjecti64v = (PFNGLGETQUERYBUFFEROBJECTI64VPROC)GetProc("glGetQueryBufferObjecti64v", total, loaded);
		glGetQueryBufferObjectiv = (PFNGLGETQUERYBUFFEROBJECTIVPROC)GetProc("glGetQueryBufferObjectiv", total, loaded);
		glGetQueryBufferObjectui64v = (PFNGLGETQUERYBUFFEROBJECTUI64VPROC)GetProc("glGetQueryBufferObjectui64v", total, loaded);
		glGetQueryBufferObjectuiv = (PFNGLGETQUERYBUFFEROBJECTUIVPROC)GetProc("glGetQueryBufferObjectuiv", total, loaded);
		glMemoryBarrierByRegion = (PFNGLMEMORYBARRIERBYREGIONPROC)GetProc("glMemoryBarrierByRegion", total, loaded);
		glGetTextureSubImage = (PFNGLGETTEXTURESUBIMAGEPROC)GetProc("glGetTextureSubImage", total, loaded);
		glGetCompressedTextureSubImage = (PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC)GetProc("glGetCompressedTextureSubImage", total, loaded);
		glGetGraphicsResetStatus = (PFNGLGETGRAPHICSRESETSTATUSPROC)GetProc("glGetGraphicsResetStatus", total, loaded);
		glGetnCompressedTexImage = (PFNGLGETNCOMPRESSEDTEXIMAGEPROC)GetProc("glGetnCompressedTexImage", total, loaded);
		glGetnTexImage = (PFNGLGETNTEXIMAGEPROC)GetProc("glGetnTexImage", total, loaded);
		glGetnUniformdv = (PFNGLGETNUNIFORMDVPROC)GetProc("glGetnUniformdv", total, loaded);
		glGetnUniformfv = (PFNGLGETNUNIFORMFVPROC)GetProc("glGetnUniformfv", total, loaded);
		glGetnUniformiv = (PFNGLGETNUNIFORMIVPROC)GetProc("glGetnUniformiv", total, loaded);
		glGetnUniformuiv = (PFNGLGETNUNIFORMUIVPROC)GetProc("glGetnUniformuiv", total, loaded);
		glReadnPixels = (PFNGLREADNPIXELSPROC)GetProc("glReadnPixels", total, loaded);
		glTextureBarrier = (PFNGLTEXTUREBARRIERPROC)GetProc("glTextureBarrier", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 4.5" << std::endl;
	#endif
		// 4.6
		total = loaded = 0;
		glSpecializeShader = (PFNGLSPECIALIZESHADERPROC)GetProc("glSpecializeShader", total, loaded);
		glMultiDrawArraysIndirectCount = (PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC)GetProc("glMultiDrawArraysIndirectCount", total, loaded);
		glMultiDrawElementsIndirectCount = (PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC)GetProc("glMultiDrawElementsIndirectCount", total, loaded);
		glPolygonOffsetClamp = (PFNGLPOLYGONOFFSETCLAMPPROC)GetProc("glPolygonOffsetClamp", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for ver 4.6" << std::endl;
	#endif

		// GL_ARB_ES3_2_compatibility
		total = loaded = 0;
		glPrimitiveBoundingBoxARB = (PFNGLPRIMITIVEBOUNDINGBOXARBPROC)GetProc("glPrimitiveBoundingBoxARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_ES3_2_compatibility" << std::endl;
	#endif
		// GL_ARB_bindless_texture
		total = loaded = 0;
		glGetTextureHandleARB = (PFNGLGETTEXTUREHANDLEARBPROC)GetProc("glGetTextureHandleARB", total, loaded);
		glGetTextureSamplerHandleARB = (PFNGLGETTEXTURESAMPLERHANDLEARBPROC)GetProc("glGetTextureSamplerHandleARB", total, loaded);
		glMakeTextureHandleResidentARB = (PFNGLMAKETEXTUREHANDLERESIDENTARBPROC)GetProc("glMakeTextureHandleResidentARB", total, loaded);
		glMakeTextureHandleNonResidentARB = (PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC)GetProc("glMakeTextureHandleNonResidentARB", total, loaded);
		glGetImageHandleARB = (PFNGLGETIMAGEHANDLEARBPROC)GetProc("glGetImageHandleARB", total, loaded);
		glMakeImageHandleResidentARB = (PFNGLMAKEIMAGEHANDLERESIDENTARBPROC)GetProc("glMakeImageHandleResidentARB", total, loaded);
		glMakeImageHandleNonResidentARB = (PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC)GetProc("glMakeImageHandleNonResidentARB", total, loaded);
		glUniformHandleui64ARB = (PFNGLUNIFORMHANDLEUI64ARBPROC)GetProc("glUniformHandleui64ARB", total, loaded);
		glUniformHandleui64vARB = (PFNGLUNIFORMHANDLEUI64VARBPROC)GetProc("glUniformHandleui64vARB", total, loaded);
		glProgramUniformHandleui64ARB = (PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC)GetProc("glProgramUniformHandleui64ARB", total, loaded);
		glProgramUniformHandleui64vARB = (PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC)GetProc("glProgramUniformHandleui64vARB", total, loaded);
		glIsTextureHandleResidentARB = (PFNGLISTEXTUREHANDLERESIDENTARBPROC)GetProc("glIsTextureHandleResidentARB", total, loaded);
		glIsImageHandleResidentARB = (PFNGLISIMAGEHANDLERESIDENTARBPROC)GetProc("glIsImageHandleResidentARB", total, loaded);
		glVertexAttribL1ui64ARB = (PFNGLVERTEXATTRIBL1UI64ARBPROC)GetProc("glVertexAttribL1ui64ARB", total, loaded);
		glVertexAttribL1ui64vARB = (PFNGLVERTEXATTRIBL1UI64VARBPROC)GetProc("glVertexAttribL1ui64vARB", total, loaded);
		glGetVertexAttribLui64vARB = (PFNGLGETVERTEXATTRIBLUI64VARBPROC)GetProc("glGetVertexAttribLui64vARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_bindless_texture" << std::endl;
	#endif
		// GL_ARB_cl_event
		total = loaded = 0;
		glCreateSyncFromCLeventARB = (PFNGLCREATESYNCFROMCLEVENTARBPROC)GetProc("glCreateSyncFromCLeventARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_cl_event" << std::endl;
	#endif
		// GL_ARB_compute_variable_group_size
		total = loaded = 0;
		glDispatchComputeGroupSizeARB = (PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC)GetProc("glDispatchComputeGroupSizeARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_compute_variable_group_size" << std::endl;
	#endif
		// GL_ARB_debug_output
		total = loaded = 0;
		glDebugMessageControlARB = (PFNGLDEBUGMESSAGECONTROLARBPROC)GetProc("glDebugMessageControlARB", total, loaded);
		glDebugMessageInsertARB = (PFNGLDEBUGMESSAGEINSERTARBPROC)GetProc("glDebugMessageInsertARB", total, loaded);
		glDebugMessageCallbackARB = (PFNGLDEBUGMESSAGECALLBACKARBPROC)GetProc("glDebugMessageCallbackARB", total, loaded);
		glGetDebugMessageLogARB = (PFNGLGETDEBUGMESSAGELOGARBPROC)GetProc("glGetDebugMessageLogARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_debug_output" << std::endl;
	#endif
		// GL_ARB_draw_buffers_blend
		total = loaded = 0;
		glBlendEquationiARB = (PFNGLBLENDEQUATIONIARBPROC)GetProc("glBlendEquationiARB", total, loaded);
		glBlendEquationSeparateiARB = (PFNGLBLENDEQUATIONSEPARATEIARBPROC)GetProc("glBlendEquationSeparateiARB", total, loaded);
		glBlendFunciARB = (PFNGLBLENDFUNCIARBPROC)GetProc("glBlendFunciARB", total, loaded);
		glBlendFuncSeparateiARB = (PFNGLBLENDFUNCSEPARATEIARBPROC)GetProc("glBlendFuncSeparateiARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_draw_buffers_blend" << std::endl;
	#endif
		// GL_ARB_draw_instanced
		total = loaded = 0;
		glDrawArraysInstancedARB = (PFNGLDRAWARRAYSINSTANCEDARBPROC)GetProc("glDrawArraysInstancedARB", total, loaded);
		glDrawElementsInstancedARB = (PFNGLDRAWELEMENTSINSTANCEDARBPROC)GetProc("glDrawElementsInstancedARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_draw_instanced" << std::endl;
	#endif
		// GL_ARB_geometry_shader4
		total = loaded = 0;
		glProgramParameteriARB = (PFNGLPROGRAMPARAMETERIARBPROC)GetProc("glProgramParameteriARB", total, loaded);
		glFramebufferTextureARB = (PFNGLFRAMEBUFFERTEXTUREARBPROC)GetProc("glFramebufferTextureARB", total, loaded);
		glFramebufferTextureLayerARB = (PFNGLFRAMEBUFFERTEXTURELAYERARBPROC)GetProc("glFramebufferTextureLayerARB", total, loaded);
		glFramebufferTextureFaceARB = (PFNGLFRAMEBUFFERTEXTUREFACEARBPROC)GetProc("glFramebufferTextureFaceARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_geometry_shader4" << std::endl;
	#endif
		// GL_ARB_gl_spirv
		total = loaded = 0;
		glSpecializeShaderARB = (PFNGLSPECIALIZESHADERARBPROC)GetProc("glSpecializeShaderARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_gl_spirv" << std::endl;
	#endif
		// GL_ARB_gpu_shader_int64
		total = loaded = 0;
		glUniform1i64ARB = (PFNGLUNIFORM1I64ARBPROC)GetProc("glUniform1i64ARB", total, loaded);
		glUniform2i64ARB = (PFNGLUNIFORM2I64ARBPROC)GetProc("glUniform2i64ARB", total, loaded);
		glUniform3i64ARB = (PFNGLUNIFORM3I64ARBPROC)GetProc("glUniform3i64ARB", total, loaded);
		glUniform4i64ARB = (PFNGLUNIFORM4I64ARBPROC)GetProc("glUniform4i64ARB", total, loaded);
		glUniform1i64vARB = (PFNGLUNIFORM1I64VARBPROC)GetProc("glUniform1i64vARB", total, loaded);
		glUniform2i64vARB = (PFNGLUNIFORM2I64VARBPROC)GetProc("glUniform2i64vARB", total, loaded);
		glUniform3i64vARB = (PFNGLUNIFORM3I64VARBPROC)GetProc("glUniform3i64vARB", total, loaded);
		glUniform4i64vARB = (PFNGLUNIFORM4I64VARBPROC)GetProc("glUniform4i64vARB", total, loaded);
		glUniform1ui64ARB = (PFNGLUNIFORM1UI64ARBPROC)GetProc("glUniform1ui64ARB", total, loaded);
		glUniform2ui64ARB = (PFNGLUNIFORM2UI64ARBPROC)GetProc("glUniform2ui64ARB", total, loaded);
		glUniform3ui64ARB = (PFNGLUNIFORM3UI64ARBPROC)GetProc("glUniform3ui64ARB", total, loaded);
		glUniform4ui64ARB = (PFNGLUNIFORM4UI64ARBPROC)GetProc("glUniform4ui64ARB", total, loaded);
		glUniform1ui64vARB = (PFNGLUNIFORM1UI64VARBPROC)GetProc("glUniform1ui64vARB", total, loaded);
		glUniform2ui64vARB = (PFNGLUNIFORM2UI64VARBPROC)GetProc("glUniform2ui64vARB", total, loaded);
		glUniform3ui64vARB = (PFNGLUNIFORM3UI64VARBPROC)GetProc("glUniform3ui64vARB", total, loaded);
		glUniform4ui64vARB = (PFNGLUNIFORM4UI64VARBPROC)GetProc("glUniform4ui64vARB", total, loaded);
		glGetUniformi64vARB = (PFNGLGETUNIFORMI64VARBPROC)GetProc("glGetUniformi64vARB", total, loaded);
		glGetUniformui64vARB = (PFNGLGETUNIFORMUI64VARBPROC)GetProc("glGetUniformui64vARB", total, loaded);
		glGetnUniformi64vARB = (PFNGLGETNUNIFORMI64VARBPROC)GetProc("glGetnUniformi64vARB", total, loaded);
		glGetnUniformui64vARB = (PFNGLGETNUNIFORMUI64VARBPROC)GetProc("glGetnUniformui64vARB", total, loaded);
		glProgramUniform1i64ARB = (PFNGLPROGRAMUNIFORM1I64ARBPROC)GetProc("glProgramUniform1i64ARB", total, loaded);
		glProgramUniform2i64ARB = (PFNGLPROGRAMUNIFORM2I64ARBPROC)GetProc("glProgramUniform2i64ARB", total, loaded);
		glProgramUniform3i64ARB = (PFNGLPROGRAMUNIFORM3I64ARBPROC)GetProc("glProgramUniform3i64ARB", total, loaded);
		glProgramUniform4i64ARB = (PFNGLPROGRAMUNIFORM4I64ARBPROC)GetProc("glProgramUniform4i64ARB", total, loaded);
		glProgramUniform1i64vARB = (PFNGLPROGRAMUNIFORM1I64VARBPROC)GetProc("glProgramUniform1i64vARB", total, loaded);
		glProgramUniform2i64vARB = (PFNGLPROGRAMUNIFORM2I64VARBPROC)GetProc("glProgramUniform2i64vARB", total, loaded);
		glProgramUniform3i64vARB = (PFNGLPROGRAMUNIFORM3I64VARBPROC)GetProc("glProgramUniform3i64vARB", total, loaded);
		glProgramUniform4i64vARB = (PFNGLPROGRAMUNIFORM4I64VARBPROC)GetProc("glProgramUniform4i64vARB", total, loaded);
		glProgramUniform1ui64ARB = (PFNGLPROGRAMUNIFORM1UI64ARBPROC)GetProc("glProgramUniform1ui64ARB", total, loaded);
		glProgramUniform2ui64ARB = (PFNGLPROGRAMUNIFORM2UI64ARBPROC)GetProc("glProgramUniform2ui64ARB", total, loaded);
		glProgramUniform3ui64ARB = (PFNGLPROGRAMUNIFORM3UI64ARBPROC)GetProc("glProgramUniform3ui64ARB", total, loaded);
		glProgramUniform4ui64ARB = (PFNGLPROGRAMUNIFORM4UI64ARBPROC)GetProc("glProgramUniform4ui64ARB", total, loaded);
		glProgramUniform1ui64vARB = (PFNGLPROGRAMUNIFORM1UI64VARBPROC)GetProc("glProgramUniform1ui64vARB", total, loaded);
		glProgramUniform2ui64vARB = (PFNGLPROGRAMUNIFORM2UI64VARBPROC)GetProc("glProgramUniform2ui64vARB", total, loaded);
		glProgramUniform3ui64vARB = (PFNGLPROGRAMUNIFORM3UI64VARBPROC)GetProc("glProgramUniform3ui64vARB", total, loaded);
		glProgramUniform4ui64vARB = (PFNGLPROGRAMUNIFORM4UI64VARBPROC)GetProc("glProgramUniform4ui64vARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_gpu_shader_int64" << std::endl;
	#endif
		// GL_ARB_indirect_parameters
		total = loaded = 0;
		glMultiDrawArraysIndirectCountARB = (PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC)GetProc("glMultiDrawArraysIndirectCountARB", total, loaded);
		glMultiDrawElementsIndirectCountARB = (PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC)GetProc("glMultiDrawElementsIndirectCountARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_indirect_parameters" << std::endl;
	#endif
		// GL_ARB_instanced_arrays
		total = loaded = 0;
		glVertexAttribDivisorARB = (PFNGLVERTEXATTRIBDIVISORARBPROC)GetProc("glVertexAttribDivisorARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_instanced_arrays" << std::endl;
	#endif
		// GL_ARB_parallel_shader_compile
		total = loaded = 0;
		glMaxShaderCompilerThreadsARB = (PFNGLMAXSHADERCOMPILERTHREADSARBPROC)GetProc("glMaxShaderCompilerThreadsARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_parallel_shader_compile" << std::endl;
	#endif
		// GL_ARB_robustness
		total = loaded = 0;
		glGetGraphicsResetStatusARB = (PFNGLGETGRAPHICSRESETSTATUSARBPROC)GetProc("glGetGraphicsResetStatusARB", total, loaded);
		glGetnTexImageARB = (PFNGLGETNTEXIMAGEARBPROC)GetProc("glGetnTexImageARB", total, loaded);
		glReadnPixelsARB = (PFNGLREADNPIXELSARBPROC)GetProc("glReadnPixelsARB", total, loaded);
		glGetnCompressedTexImageARB = (PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC)GetProc("glGetnCompressedTexImageARB", total, loaded);
		glGetnUniformfvARB = (PFNGLGETNUNIFORMFVARBPROC)GetProc("glGetnUniformfvARB", total, loaded);
		glGetnUniformivARB = (PFNGLGETNUNIFORMIVARBPROC)GetProc("glGetnUniformivARB", total, loaded);
		glGetnUniformuivARB = (PFNGLGETNUNIFORMUIVARBPROC)GetProc("glGetnUniformuivARB", total, loaded);
		glGetnUniformdvARB = (PFNGLGETNUNIFORMDVARBPROC)GetProc("glGetnUniformdvARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_robustness" << std::endl;
	#endif
		// GL_ARB_sample_locations
		total = loaded = 0;
		glFramebufferSampleLocationsfvARB = (PFNGLFRAMEBUFFERSAMPLELOCATIONSFVARBPROC)GetProc("glFramebufferSampleLocationsfvARB", total, loaded);
		glNamedFramebufferSampleLocationsfvARB = (PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVARBPROC)GetProc("glNamedFramebufferSampleLocationsfvARB", total, loaded);
		glEvaluateDepthValuesARB = (PFNGLEVALUATEDEPTHVALUESARBPROC)GetProc("glEvaluateDepthValuesARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_sample_locations" << std::endl;
	#endif
		// GL_ARB_sample_shading
		total = loaded = 0;
		glMinSampleShadingARB = (PFNGLMINSAMPLESHADINGARBPROC)GetProc("glMinSampleShadingARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_sample_shading" << std::endl;
	#endif
		// GL_ARB_shading_language_include
		total = loaded = 0;
		glNamedStringARB = (PFNGLNAMEDSTRINGARBPROC)GetProc("glNamedStringARB", total, loaded);
		glDeleteNamedStringARB = (PFNGLDELETENAMEDSTRINGARBPROC)GetProc("glDeleteNamedStringARB", total, loaded);
		glCompileShaderIncludeARB = (PFNGLCOMPILESHADERINCLUDEARBPROC)GetProc("glCompileShaderIncludeARB", total, loaded);
		glIsNamedStringARB = (PFNGLISNAMEDSTRINGARBPROC)GetProc("glIsNamedStringARB", total, loaded);
		glGetNamedStringARB = (PFNGLGETNAMEDSTRINGARBPROC)GetProc("glGetNamedStringARB", total, loaded);
		glGetNamedStringivARB = (PFNGLGETNAMEDSTRINGIVARBPROC)GetProc("glGetNamedStringivARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_shading_language_include" << std::endl;
	#endif
		// GL_ARB_sparse_buffer
		total = loaded = 0;
		glBufferPageCommitmentARB = (PFNGLBUFFERPAGECOMMITMENTARBPROC)GetProc("glBufferPageCommitmentARB", total, loaded);
		glNamedBufferPageCommitmentEXT = (PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC)GetProc("glNamedBufferPageCommitmentEXT", total, loaded);
		glNamedBufferPageCommitmentARB = (PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC)GetProc("glNamedBufferPageCommitmentARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_sparse_buffer" << std::endl;
	#endif
		// GL_ARB_sparse_texture
		total = loaded = 0;
		glTexPageCommitmentARB = (PFNGLTEXPAGECOMMITMENTARBPROC)GetProc("glTexPageCommitmentARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_sparse_texture" << std::endl;
	#endif
		// GL_ARB_texture_buffer_object
		total = loaded = 0;
		glTexBufferARB = (PFNGLTEXBUFFERARBPROC)GetProc("glTexBufferARB", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_texture_buffer_object" << std::endl;
	#endif
		// GL_ARB_viewport_array
		total = loaded = 0;
		glDepthRangeArraydvNV = (PFNGLDEPTHRANGEARRAYDVNVPROC)GetProc("glDepthRangeArraydvNV", total, loaded);
		glDepthRangeIndexeddNV = (PFNGLDEPTHRANGEINDEXEDDNVPROC)GetProc("glDepthRangeIndexeddNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_ARB_viewport_array" << std::endl;
	#endif
		// GL_KHR_blend_equation_advanced
		total = loaded = 0;
		glBlendBarrierKHR = (PFNGLBLENDBARRIERKHRPROC)GetProc("glBlendBarrierKHR", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_KHR_blend_equation_advanced" << std::endl;
	#endif
		// GL_KHR_parallel_shader_compile
		total = loaded = 0;
		glMaxShaderCompilerThreadsKHR = (PFNGLMAXSHADERCOMPILERTHREADSKHRPROC)GetProc("glMaxShaderCompilerThreadsKHR", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_KHR_parallel_shader_compile" << std::endl;
	#endif
		// GL_AMD_framebuffer_multisample_advanced
		total = loaded = 0;
		glRenderbufferStorageMultisampleAdvancedAMD = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC)GetProc("glRenderbufferStorageMultisampleAdvancedAMD", total, loaded);
		glNamedRenderbufferStorageMultisampleAdvancedAMD = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC)GetProc("glNamedRenderbufferStorageMultisampleAdvancedAMD", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_AMD_framebuffer_multisample_advanced" << std::endl;
	#endif
		// GL_AMD_performance_monitor
		total = loaded = 0;
		glGetPerfMonitorGroupsAMD = (PFNGLGETPERFMONITORGROUPSAMDPROC)GetProc("glGetPerfMonitorGroupsAMD", total, loaded);
		glGetPerfMonitorCountersAMD = (PFNGLGETPERFMONITORCOUNTERSAMDPROC)GetProc("glGetPerfMonitorCountersAMD", total, loaded);
		glGetPerfMonitorGroupStringAMD = (PFNGLGETPERFMONITORGROUPSTRINGAMDPROC)GetProc("glGetPerfMonitorGroupStringAMD", total, loaded);
		glGetPerfMonitorCounterStringAMD = (PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC)GetProc("glGetPerfMonitorCounterStringAMD", total, loaded);
		glGetPerfMonitorCounterInfoAMD = (PFNGLGETPERFMONITORCOUNTERINFOAMDPROC)GetProc("glGetPerfMonitorCounterInfoAMD", total, loaded);
		glGenPerfMonitorsAMD = (PFNGLGENPERFMONITORSAMDPROC)GetProc("glGenPerfMonitorsAMD", total, loaded);
		glDeletePerfMonitorsAMD = (PFNGLDELETEPERFMONITORSAMDPROC)GetProc("glDeletePerfMonitorsAMD", total, loaded);
		glSelectPerfMonitorCountersAMD = (PFNGLSELECTPERFMONITORCOUNTERSAMDPROC)GetProc("glSelectPerfMonitorCountersAMD", total, loaded);
		glBeginPerfMonitorAMD = (PFNGLBEGINPERFMONITORAMDPROC)GetProc("glBeginPerfMonitorAMD", total, loaded);
		glEndPerfMonitorAMD = (PFNGLENDPERFMONITORAMDPROC)GetProc("glEndPerfMonitorAMD", total, loaded);
		glGetPerfMonitorCounterDataAMD = (PFNGLGETPERFMONITORCOUNTERDATAAMDPROC)GetProc("glGetPerfMonitorCounterDataAMD", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_AMD_performance_monitor" << std::endl;
	#endif
		// GL_EXT_EGL_image_storage
		total = loaded = 0;
		glEGLImageTargetTexStorageEXT = (PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC)GetProc("glEGLImageTargetTexStorageEXT", total, loaded);
		glEGLImageTargetTextureStorageEXT = (PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC)GetProc("glEGLImageTargetTextureStorageEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_EXT_EGL_image_storage" << std::endl;
	#endif
		// GL_EXT_debug_label
		total = loaded = 0;
		glLabelObjectEXT = (PFNGLLABELOBJECTEXTPROC)GetProc("glLabelObjectEXT", total, loaded);
		glGetObjectLabelEXT = (PFNGLGETOBJECTLABELEXTPROC)GetProc("glGetObjectLabelEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_EXT_debug_label" << std::endl;
	#endif
		// GL_EXT_debug_marker
		total = loaded = 0;
		glInsertEventMarkerEXT = (PFNGLINSERTEVENTMARKEREXTPROC)GetProc("glInsertEventMarkerEXT", total, loaded);
		glPushGroupMarkerEXT = (PFNGLPUSHGROUPMARKEREXTPROC)GetProc("glPushGroupMarkerEXT", total, loaded);
		glPopGroupMarkerEXT = (PFNGLPOPGROUPMARKEREXTPROC)GetProc("glPopGroupMarkerEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_EXT_debug_marker" << std::endl;
	#endif
		// GL_EXT_direct_state_access
		total = loaded = 0;
		glMatrixLoadfEXT = (PFNGLMATRIXLOADFEXTPROC)GetProc("glMatrixLoadfEXT", total, loaded);
		glMatrixLoaddEXT = (PFNGLMATRIXLOADDEXTPROC)GetProc("glMatrixLoaddEXT", total, loaded);
		glMatrixMultfEXT = (PFNGLMATRIXMULTFEXTPROC)GetProc("glMatrixMultfEXT", total, loaded);
		glMatrixMultdEXT = (PFNGLMATRIXMULTDEXTPROC)GetProc("glMatrixMultdEXT", total, loaded);
		glMatrixLoadIdentityEXT = (PFNGLMATRIXLOADIDENTITYEXTPROC)GetProc("glMatrixLoadIdentityEXT", total, loaded);
		glMatrixRotatefEXT = (PFNGLMATRIXROTATEFEXTPROC)GetProc("glMatrixRotatefEXT", total, loaded);
		glMatrixRotatedEXT = (PFNGLMATRIXROTATEDEXTPROC)GetProc("glMatrixRotatedEXT", total, loaded);
		glMatrixScalefEXT = (PFNGLMATRIXSCALEFEXTPROC)GetProc("glMatrixScalefEXT", total, loaded);
		glMatrixScaledEXT = (PFNGLMATRIXSCALEDEXTPROC)GetProc("glMatrixScaledEXT", total, loaded);
		glMatrixTranslatefEXT = (PFNGLMATRIXTRANSLATEFEXTPROC)GetProc("glMatrixTranslatefEXT", total, loaded);
		glMatrixTranslatedEXT = (PFNGLMATRIXTRANSLATEDEXTPROC)GetProc("glMatrixTranslatedEXT", total, loaded);
		glMatrixFrustumEXT = (PFNGLMATRIXFRUSTUMEXTPROC)GetProc("glMatrixFrustumEXT", total, loaded);
		glMatrixOrthoEXT = (PFNGLMATRIXORTHOEXTPROC)GetProc("glMatrixOrthoEXT", total, loaded);
		glMatrixPopEXT = (PFNGLMATRIXPOPEXTPROC)GetProc("glMatrixPopEXT", total, loaded);
		glMatrixPushEXT = (PFNGLMATRIXPUSHEXTPROC)GetProc("glMatrixPushEXT", total, loaded);
		glClientAttribDefaultEXT = (PFNGLCLIENTATTRIBDEFAULTEXTPROC)GetProc("glClientAttribDefaultEXT", total, loaded);
		glPushClientAttribDefaultEXT = (PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC)GetProc("glPushClientAttribDefaultEXT", total, loaded);
		glTextureParameterfEXT = (PFNGLTEXTUREPARAMETERFEXTPROC)GetProc("glTextureParameterfEXT", total, loaded);
		glTextureParameterfvEXT = (PFNGLTEXTUREPARAMETERFVEXTPROC)GetProc("glTextureParameterfvEXT", total, loaded);
		glTextureParameteriEXT = (PFNGLTEXTUREPARAMETERIEXTPROC)GetProc("glTextureParameteriEXT", total, loaded);
		glTextureParameterivEXT = (PFNGLTEXTUREPARAMETERIVEXTPROC)GetProc("glTextureParameterivEXT", total, loaded);
		glTextureImage1DEXT = (PFNGLTEXTUREIMAGE1DEXTPROC)GetProc("glTextureImage1DEXT", total, loaded);
		glTextureImage2DEXT = (PFNGLTEXTUREIMAGE2DEXTPROC)GetProc("glTextureImage2DEXT", total, loaded);
		glTextureSubImage1DEXT = (PFNGLTEXTURESUBIMAGE1DEXTPROC)GetProc("glTextureSubImage1DEXT", total, loaded);
		glTextureSubImage2DEXT = (PFNGLTEXTURESUBIMAGE2DEXTPROC)GetProc("glTextureSubImage2DEXT", total, loaded);
		glCopyTextureImage1DEXT = (PFNGLCOPYTEXTUREIMAGE1DEXTPROC)GetProc("glCopyTextureImage1DEXT", total, loaded);
		glCopyTextureImage2DEXT = (PFNGLCOPYTEXTUREIMAGE2DEXTPROC)GetProc("glCopyTextureImage2DEXT", total, loaded);
		glCopyTextureSubImage1DEXT = (PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC)GetProc("glCopyTextureSubImage1DEXT", total, loaded);
		glCopyTextureSubImage2DEXT = (PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC)GetProc("glCopyTextureSubImage2DEXT", total, loaded);
		glGetTextureImageEXT = (PFNGLGETTEXTUREIMAGEEXTPROC)GetProc("glGetTextureImageEXT", total, loaded);
		glGetTextureParameterfvEXT = (PFNGLGETTEXTUREPARAMETERFVEXTPROC)GetProc("glGetTextureParameterfvEXT", total, loaded);
		glGetTextureParameterivEXT = (PFNGLGETTEXTUREPARAMETERIVEXTPROC)GetProc("glGetTextureParameterivEXT", total, loaded);
		glGetTextureLevelParameterfvEXT = (PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC)GetProc("glGetTextureLevelParameterfvEXT", total, loaded);
		glGetTextureLevelParameterivEXT = (PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC)GetProc("glGetTextureLevelParameterivEXT", total, loaded);
		glTextureImage3DEXT = (PFNGLTEXTUREIMAGE3DEXTPROC)GetProc("glTextureImage3DEXT", total, loaded);
		glTextureSubImage3DEXT = (PFNGLTEXTURESUBIMAGE3DEXTPROC)GetProc("glTextureSubImage3DEXT", total, loaded);
		glCopyTextureSubImage3DEXT = (PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC)GetProc("glCopyTextureSubImage3DEXT", total, loaded);
		glBindMultiTextureEXT = (PFNGLBINDMULTITEXTUREEXTPROC)GetProc("glBindMultiTextureEXT", total, loaded);
		glMultiTexCoordPointerEXT = (PFNGLMULTITEXCOORDPOINTEREXTPROC)GetProc("glMultiTexCoordPointerEXT", total, loaded);
		glMultiTexEnvfEXT = (PFNGLMULTITEXENVFEXTPROC)GetProc("glMultiTexEnvfEXT", total, loaded);
		glMultiTexEnvfvEXT = (PFNGLMULTITEXENVFVEXTPROC)GetProc("glMultiTexEnvfvEXT", total, loaded);
		glMultiTexEnviEXT = (PFNGLMULTITEXENVIEXTPROC)GetProc("glMultiTexEnviEXT", total, loaded);
		glMultiTexEnvivEXT = (PFNGLMULTITEXENVIVEXTPROC)GetProc("glMultiTexEnvivEXT", total, loaded);
		glMultiTexGendEXT = (PFNGLMULTITEXGENDEXTPROC)GetProc("glMultiTexGendEXT", total, loaded);
		glMultiTexGendvEXT = (PFNGLMULTITEXGENDVEXTPROC)GetProc("glMultiTexGendvEXT", total, loaded);
		glMultiTexGenfEXT = (PFNGLMULTITEXGENFEXTPROC)GetProc("glMultiTexGenfEXT", total, loaded);
		glMultiTexGenfvEXT = (PFNGLMULTITEXGENFVEXTPROC)GetProc("glMultiTexGenfvEXT", total, loaded);
		glMultiTexGeniEXT = (PFNGLMULTITEXGENIEXTPROC)GetProc("glMultiTexGeniEXT", total, loaded);
		glMultiTexGenivEXT = (PFNGLMULTITEXGENIVEXTPROC)GetProc("glMultiTexGenivEXT", total, loaded);
		glGetMultiTexEnvfvEXT = (PFNGLGETMULTITEXENVFVEXTPROC)GetProc("glGetMultiTexEnvfvEXT", total, loaded);
		glGetMultiTexEnvivEXT = (PFNGLGETMULTITEXENVIVEXTPROC)GetProc("glGetMultiTexEnvivEXT", total, loaded);
		glGetMultiTexGendvEXT = (PFNGLGETMULTITEXGENDVEXTPROC)GetProc("glGetMultiTexGendvEXT", total, loaded);
		glGetMultiTexGenfvEXT = (PFNGLGETMULTITEXGENFVEXTPROC)GetProc("glGetMultiTexGenfvEXT", total, loaded);
		glGetMultiTexGenivEXT = (PFNGLGETMULTITEXGENIVEXTPROC)GetProc("glGetMultiTexGenivEXT", total, loaded);
		glMultiTexParameteriEXT = (PFNGLMULTITEXPARAMETERIEXTPROC)GetProc("glMultiTexParameteriEXT", total, loaded);
		glMultiTexParameterivEXT = (PFNGLMULTITEXPARAMETERIVEXTPROC)GetProc("glMultiTexParameterivEXT", total, loaded);
		glMultiTexParameterfEXT = (PFNGLMULTITEXPARAMETERFEXTPROC)GetProc("glMultiTexParameterfEXT", total, loaded);
		glMultiTexParameterfvEXT = (PFNGLMULTITEXPARAMETERFVEXTPROC)GetProc("glMultiTexParameterfvEXT", total, loaded);
		glMultiTexImage1DEXT = (PFNGLMULTITEXIMAGE1DEXTPROC)GetProc("glMultiTexImage1DEXT", total, loaded);
		glMultiTexImage2DEXT = (PFNGLMULTITEXIMAGE2DEXTPROC)GetProc("glMultiTexImage2DEXT", total, loaded);
		glMultiTexSubImage1DEXT = (PFNGLMULTITEXSUBIMAGE1DEXTPROC)GetProc("glMultiTexSubImage1DEXT", total, loaded);
		glMultiTexSubImage2DEXT = (PFNGLMULTITEXSUBIMAGE2DEXTPROC)GetProc("glMultiTexSubImage2DEXT", total, loaded);
		glCopyMultiTexImage1DEXT = (PFNGLCOPYMULTITEXIMAGE1DEXTPROC)GetProc("glCopyMultiTexImage1DEXT", total, loaded);
		glCopyMultiTexImage2DEXT = (PFNGLCOPYMULTITEXIMAGE2DEXTPROC)GetProc("glCopyMultiTexImage2DEXT", total, loaded);
		glCopyMultiTexSubImage1DEXT = (PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC)GetProc("glCopyMultiTexSubImage1DEXT", total, loaded);
		glCopyMultiTexSubImage2DEXT = (PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC)GetProc("glCopyMultiTexSubImage2DEXT", total, loaded);
		glGetMultiTexImageEXT = (PFNGLGETMULTITEXIMAGEEXTPROC)GetProc("glGetMultiTexImageEXT", total, loaded);
		glGetMultiTexParameterfvEXT = (PFNGLGETMULTITEXPARAMETERFVEXTPROC)GetProc("glGetMultiTexParameterfvEXT", total, loaded);
		glGetMultiTexParameterivEXT = (PFNGLGETMULTITEXPARAMETERIVEXTPROC)GetProc("glGetMultiTexParameterivEXT", total, loaded);
		glGetMultiTexLevelParameterfvEXT = (PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC)GetProc("glGetMultiTexLevelParameterfvEXT", total, loaded);
		glGetMultiTexLevelParameterivEXT = (PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC)GetProc("glGetMultiTexLevelParameterivEXT", total, loaded);
		glMultiTexImage3DEXT = (PFNGLMULTITEXIMAGE3DEXTPROC)GetProc("glMultiTexImage3DEXT", total, loaded);
		glMultiTexSubImage3DEXT = (PFNGLMULTITEXSUBIMAGE3DEXTPROC)GetProc("glMultiTexSubImage3DEXT", total, loaded);
		glCopyMultiTexSubImage3DEXT = (PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC)GetProc("glCopyMultiTexSubImage3DEXT", total, loaded);
		glEnableClientStateIndexedEXT = (PFNGLENABLECLIENTSTATEINDEXEDEXTPROC)GetProc("glEnableClientStateIndexedEXT", total, loaded);
		glDisableClientStateIndexedEXT = (PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC)GetProc("glDisableClientStateIndexedEXT", total, loaded);
		glGetFloatIndexedvEXT = (PFNGLGETFLOATINDEXEDVEXTPROC)GetProc("glGetFloatIndexedvEXT", total, loaded);
		glGetDoubleIndexedvEXT = (PFNGLGETDOUBLEINDEXEDVEXTPROC)GetProc("glGetDoubleIndexedvEXT", total, loaded);
		glGetPointerIndexedvEXT = (PFNGLGETPOINTERINDEXEDVEXTPROC)GetProc("glGetPointerIndexedvEXT", total, loaded);
		glEnableIndexedEXT = (PFNGLENABLEINDEXEDEXTPROC)GetProc("glEnableIndexedEXT", total, loaded);
		glDisableIndexedEXT = (PFNGLDISABLEINDEXEDEXTPROC)GetProc("glDisableIndexedEXT", total, loaded);
		glIsEnabledIndexedEXT = (PFNGLISENABLEDINDEXEDEXTPROC)GetProc("glIsEnabledIndexedEXT", total, loaded);
		glGetIntegerIndexedvEXT = (PFNGLGETINTEGERINDEXEDVEXTPROC)GetProc("glGetIntegerIndexedvEXT", total, loaded);
		glGetBooleanIndexedvEXT = (PFNGLGETBOOLEANINDEXEDVEXTPROC)GetProc("glGetBooleanIndexedvEXT", total, loaded);
		glCompressedTextureImage3DEXT = (PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC)GetProc("glCompressedTextureImage3DEXT", total, loaded);
		glCompressedTextureImage2DEXT = (PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC)GetProc("glCompressedTextureImage2DEXT", total, loaded);
		glCompressedTextureImage1DEXT = (PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC)GetProc("glCompressedTextureImage1DEXT", total, loaded);
		glCompressedTextureSubImage3DEXT = (PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC)GetProc("glCompressedTextureSubImage3DEXT", total, loaded);
		glCompressedTextureSubImage2DEXT = (PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC)GetProc("glCompressedTextureSubImage2DEXT", total, loaded);
		glCompressedTextureSubImage1DEXT = (PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC)GetProc("glCompressedTextureSubImage1DEXT", total, loaded);
		glGetCompressedTextureImageEXT = (PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC)GetProc("glGetCompressedTextureImageEXT", total, loaded);
		glCompressedMultiTexImage3DEXT = (PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC)GetProc("glCompressedMultiTexImage3DEXT", total, loaded);
		glCompressedMultiTexImage2DEXT = (PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC)GetProc("glCompressedMultiTexImage2DEXT", total, loaded);
		glCompressedMultiTexImage1DEXT = (PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC)GetProc("glCompressedMultiTexImage1DEXT", total, loaded);
		glCompressedMultiTexSubImage3DEXT = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC)GetProc("glCompressedMultiTexSubImage3DEXT", total, loaded);
		glCompressedMultiTexSubImage2DEXT = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC)GetProc("glCompressedMultiTexSubImage2DEXT", total, loaded);
		glCompressedMultiTexSubImage1DEXT = (PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC)GetProc("glCompressedMultiTexSubImage1DEXT", total, loaded);
		glGetCompressedMultiTexImageEXT = (PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC)GetProc("glGetCompressedMultiTexImageEXT", total, loaded);
		glMatrixLoadTransposefEXT = (PFNGLMATRIXLOADTRANSPOSEFEXTPROC)GetProc("glMatrixLoadTransposefEXT", total, loaded);
		glMatrixLoadTransposedEXT = (PFNGLMATRIXLOADTRANSPOSEDEXTPROC)GetProc("glMatrixLoadTransposedEXT", total, loaded);
		glMatrixMultTransposefEXT = (PFNGLMATRIXMULTTRANSPOSEFEXTPROC)GetProc("glMatrixMultTransposefEXT", total, loaded);
		glMatrixMultTransposedEXT = (PFNGLMATRIXMULTTRANSPOSEDEXTPROC)GetProc("glMatrixMultTransposedEXT", total, loaded);
		glNamedBufferDataEXT = (PFNGLNAMEDBUFFERDATAEXTPROC)GetProc("glNamedBufferDataEXT", total, loaded);
		glNamedBufferSubDataEXT = (PFNGLNAMEDBUFFERSUBDATAEXTPROC)GetProc("glNamedBufferSubDataEXT", total, loaded);
		glMapNamedBufferEXT = (PFNGLMAPNAMEDBUFFEREXTPROC)GetProc("glMapNamedBufferEXT", total, loaded);
		glUnmapNamedBufferEXT = (PFNGLUNMAPNAMEDBUFFEREXTPROC)GetProc("glUnmapNamedBufferEXT", total, loaded);
		glGetNamedBufferParameterivEXT = (PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC)GetProc("glGetNamedBufferParameterivEXT", total, loaded);
		glGetNamedBufferPointervEXT = (PFNGLGETNAMEDBUFFERPOINTERVEXTPROC)GetProc("glGetNamedBufferPointervEXT", total, loaded);
		glGetNamedBufferSubDataEXT = (PFNGLGETNAMEDBUFFERSUBDATAEXTPROC)GetProc("glGetNamedBufferSubDataEXT", total, loaded);
		glProgramUniform1fEXT = (PFNGLPROGRAMUNIFORM1FEXTPROC)GetProc("glProgramUniform1fEXT", total, loaded);
		glProgramUniform2fEXT = (PFNGLPROGRAMUNIFORM2FEXTPROC)GetProc("glProgramUniform2fEXT", total, loaded);
		glProgramUniform3fEXT = (PFNGLPROGRAMUNIFORM3FEXTPROC)GetProc("glProgramUniform3fEXT", total, loaded);
		glProgramUniform4fEXT = (PFNGLPROGRAMUNIFORM4FEXTPROC)GetProc("glProgramUniform4fEXT", total, loaded);
		glProgramUniform1iEXT = (PFNGLPROGRAMUNIFORM1IEXTPROC)GetProc("glProgramUniform1iEXT", total, loaded);
		glProgramUniform2iEXT = (PFNGLPROGRAMUNIFORM2IEXTPROC)GetProc("glProgramUniform2iEXT", total, loaded);
		glProgramUniform3iEXT = (PFNGLPROGRAMUNIFORM3IEXTPROC)GetProc("glProgramUniform3iEXT", total, loaded);
		glProgramUniform4iEXT = (PFNGLPROGRAMUNIFORM4IEXTPROC)GetProc("glProgramUniform4iEXT", total, loaded);
		glProgramUniform1fvEXT = (PFNGLPROGRAMUNIFORM1FVEXTPROC)GetProc("glProgramUniform1fvEXT", total, loaded);
		glProgramUniform2fvEXT = (PFNGLPROGRAMUNIFORM2FVEXTPROC)GetProc("glProgramUniform2fvEXT", total, loaded);
		glProgramUniform3fvEXT = (PFNGLPROGRAMUNIFORM3FVEXTPROC)GetProc("glProgramUniform3fvEXT", total, loaded);
		glProgramUniform4fvEXT = (PFNGLPROGRAMUNIFORM4FVEXTPROC)GetProc("glProgramUniform4fvEXT", total, loaded);
		glProgramUniform1ivEXT = (PFNGLPROGRAMUNIFORM1IVEXTPROC)GetProc("glProgramUniform1ivEXT", total, loaded);
		glProgramUniform2ivEXT = (PFNGLPROGRAMUNIFORM2IVEXTPROC)GetProc("glProgramUniform2ivEXT", total, loaded);
		glProgramUniform3ivEXT = (PFNGLPROGRAMUNIFORM3IVEXTPROC)GetProc("glProgramUniform3ivEXT", total, loaded);
		glProgramUniform4ivEXT = (PFNGLPROGRAMUNIFORM4IVEXTPROC)GetProc("glProgramUniform4ivEXT", total, loaded);
		glProgramUniformMatrix2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC)GetProc("glProgramUniformMatrix2fvEXT", total, loaded);
		glProgramUniformMatrix3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC)GetProc("glProgramUniformMatrix3fvEXT", total, loaded);
		glProgramUniformMatrix4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC)GetProc("glProgramUniformMatrix4fvEXT", total, loaded);
		glProgramUniformMatrix2x3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC)GetProc("glProgramUniformMatrix2x3fvEXT", total, loaded);
		glProgramUniformMatrix3x2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC)GetProc("glProgramUniformMatrix3x2fvEXT", total, loaded);
		glProgramUniformMatrix2x4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC)GetProc("glProgramUniformMatrix2x4fvEXT", total, loaded);
		glProgramUniformMatrix4x2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC)GetProc("glProgramUniformMatrix4x2fvEXT", total, loaded);
		glProgramUniformMatrix3x4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC)GetProc("glProgramUniformMatrix3x4fvEXT", total, loaded);
		glProgramUniformMatrix4x3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC)GetProc("glProgramUniformMatrix4x3fvEXT", total, loaded);
		glTextureBufferEXT = (PFNGLTEXTUREBUFFEREXTPROC)GetProc("glTextureBufferEXT", total, loaded);
		glMultiTexBufferEXT = (PFNGLMULTITEXBUFFEREXTPROC)GetProc("glMultiTexBufferEXT", total, loaded);
		glTextureParameterIivEXT = (PFNGLTEXTUREPARAMETERIIVEXTPROC)GetProc("glTextureParameterIivEXT", total, loaded);
		glTextureParameterIuivEXT = (PFNGLTEXTUREPARAMETERIUIVEXTPROC)GetProc("glTextureParameterIuivEXT", total, loaded);
		glGetTextureParameterIivEXT = (PFNGLGETTEXTUREPARAMETERIIVEXTPROC)GetProc("glGetTextureParameterIivEXT", total, loaded);
		glGetTextureParameterIuivEXT = (PFNGLGETTEXTUREPARAMETERIUIVEXTPROC)GetProc("glGetTextureParameterIuivEXT", total, loaded);
		glMultiTexParameterIivEXT = (PFNGLMULTITEXPARAMETERIIVEXTPROC)GetProc("glMultiTexParameterIivEXT", total, loaded);
		glMultiTexParameterIuivEXT = (PFNGLMULTITEXPARAMETERIUIVEXTPROC)GetProc("glMultiTexParameterIuivEXT", total, loaded);
		glGetMultiTexParameterIivEXT = (PFNGLGETMULTITEXPARAMETERIIVEXTPROC)GetProc("glGetMultiTexParameterIivEXT", total, loaded);
		glGetMultiTexParameterIuivEXT = (PFNGLGETMULTITEXPARAMETERIUIVEXTPROC)GetProc("glGetMultiTexParameterIuivEXT", total, loaded);
		glProgramUniform1uiEXT = (PFNGLPROGRAMUNIFORM1UIEXTPROC)GetProc("glProgramUniform1uiEXT", total, loaded);
		glProgramUniform2uiEXT = (PFNGLPROGRAMUNIFORM2UIEXTPROC)GetProc("glProgramUniform2uiEXT", total, loaded);
		glProgramUniform3uiEXT = (PFNGLPROGRAMUNIFORM3UIEXTPROC)GetProc("glProgramUniform3uiEXT", total, loaded);
		glProgramUniform4uiEXT = (PFNGLPROGRAMUNIFORM4UIEXTPROC)GetProc("glProgramUniform4uiEXT", total, loaded);
		glProgramUniform1uivEXT = (PFNGLPROGRAMUNIFORM1UIVEXTPROC)GetProc("glProgramUniform1uivEXT", total, loaded);
		glProgramUniform2uivEXT = (PFNGLPROGRAMUNIFORM2UIVEXTPROC)GetProc("glProgramUniform2uivEXT", total, loaded);
		glProgramUniform3uivEXT = (PFNGLPROGRAMUNIFORM3UIVEXTPROC)GetProc("glProgramUniform3uivEXT", total, loaded);
		glProgramUniform4uivEXT = (PFNGLPROGRAMUNIFORM4UIVEXTPROC)GetProc("glProgramUniform4uivEXT", total, loaded);
		glNamedProgramLocalParameters4fvEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC)GetProc("glNamedProgramLocalParameters4fvEXT", total, loaded);
		glNamedProgramLocalParameterI4iEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC)GetProc("glNamedProgramLocalParameterI4iEXT", total, loaded);
		glNamedProgramLocalParameterI4ivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC)GetProc("glNamedProgramLocalParameterI4ivEXT", total, loaded);
		glNamedProgramLocalParametersI4ivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC)GetProc("glNamedProgramLocalParametersI4ivEXT", total, loaded);
		glNamedProgramLocalParameterI4uiEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC)GetProc("glNamedProgramLocalParameterI4uiEXT", total, loaded);
		glNamedProgramLocalParameterI4uivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC)GetProc("glNamedProgramLocalParameterI4uivEXT", total, loaded);
		glNamedProgramLocalParametersI4uivEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC)GetProc("glNamedProgramLocalParametersI4uivEXT", total, loaded);
		glGetNamedProgramLocalParameterIivEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC)GetProc("glGetNamedProgramLocalParameterIivEXT", total, loaded);
		glGetNamedProgramLocalParameterIuivEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC)GetProc("glGetNamedProgramLocalParameterIuivEXT", total, loaded);
		glEnableClientStateiEXT = (PFNGLENABLECLIENTSTATEIEXTPROC)GetProc("glEnableClientStateiEXT", total, loaded);
		glDisableClientStateiEXT = (PFNGLDISABLECLIENTSTATEIEXTPROC)GetProc("glDisableClientStateiEXT", total, loaded);
		glGetFloati_vEXT = (PFNGLGETFLOATI_VEXTPROC)GetProc("glGetFloati_vEXT", total, loaded);
		glGetDoublei_vEXT = (PFNGLGETDOUBLEI_VEXTPROC)GetProc("glGetDoublei_vEXT", total, loaded);
		glGetPointeri_vEXT = (PFNGLGETPOINTERI_VEXTPROC)GetProc("glGetPointeri_vEXT", total, loaded);
		glNamedProgramStringEXT = (PFNGLNAMEDPROGRAMSTRINGEXTPROC)GetProc("glNamedProgramStringEXT", total, loaded);
		glNamedProgramLocalParameter4dEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC)GetProc("glNamedProgramLocalParameter4dEXT", total, loaded);
		glNamedProgramLocalParameter4dvEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC)GetProc("glNamedProgramLocalParameter4dvEXT", total, loaded);
		glNamedProgramLocalParameter4fEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC)GetProc("glNamedProgramLocalParameter4fEXT", total, loaded);
		glNamedProgramLocalParameter4fvEXT = (PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC)GetProc("glNamedProgramLocalParameter4fvEXT", total, loaded);
		glGetNamedProgramLocalParameterdvEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC)GetProc("glGetNamedProgramLocalParameterdvEXT", total, loaded);
		glGetNamedProgramLocalParameterfvEXT = (PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC)GetProc("glGetNamedProgramLocalParameterfvEXT", total, loaded);
		glGetNamedProgramivEXT = (PFNGLGETNAMEDPROGRAMIVEXTPROC)GetProc("glGetNamedProgramivEXT", total, loaded);
		glGetNamedProgramStringEXT = (PFNGLGETNAMEDPROGRAMSTRINGEXTPROC)GetProc("glGetNamedProgramStringEXT", total, loaded);
		glNamedRenderbufferStorageEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC)GetProc("glNamedRenderbufferStorageEXT", total, loaded);
		glGetNamedRenderbufferParameterivEXT = (PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC)GetProc("glGetNamedRenderbufferParameterivEXT", total, loaded);
		glNamedRenderbufferStorageMultisampleEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)GetProc("glNamedRenderbufferStorageMultisampleEXT", total, loaded);
		glNamedRenderbufferStorageMultisampleCoverageEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC)GetProc("glNamedRenderbufferStorageMultisampleCoverageEXT", total, loaded);
		glCheckNamedFramebufferStatusEXT = (PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC)GetProc("glCheckNamedFramebufferStatusEXT", total, loaded);
		glNamedFramebufferTexture1DEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC)GetProc("glNamedFramebufferTexture1DEXT", total, loaded);
		glNamedFramebufferTexture2DEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC)GetProc("glNamedFramebufferTexture2DEXT", total, loaded);
		glNamedFramebufferTexture3DEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC)GetProc("glNamedFramebufferTexture3DEXT", total, loaded);
		glNamedFramebufferRenderbufferEXT = (PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC)GetProc("glNamedFramebufferRenderbufferEXT", total, loaded);
		glGetNamedFramebufferAttachmentParameterivEXT = (PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)GetProc("glGetNamedFramebufferAttachmentParameterivEXT", total, loaded);
		glGenerateTextureMipmapEXT = (PFNGLGENERATETEXTUREMIPMAPEXTPROC)GetProc("glGenerateTextureMipmapEXT", total, loaded);
		glGenerateMultiTexMipmapEXT = (PFNGLGENERATEMULTITEXMIPMAPEXTPROC)GetProc("glGenerateMultiTexMipmapEXT", total, loaded);
		glFramebufferDrawBufferEXT = (PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC)GetProc("glFramebufferDrawBufferEXT", total, loaded);
		glFramebufferDrawBuffersEXT = (PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC)GetProc("glFramebufferDrawBuffersEXT", total, loaded);
		glFramebufferReadBufferEXT = (PFNGLFRAMEBUFFERREADBUFFEREXTPROC)GetProc("glFramebufferReadBufferEXT", total, loaded);
		glGetFramebufferParameterivEXT = (PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC)GetProc("glGetFramebufferParameterivEXT", total, loaded);
		glNamedCopyBufferSubDataEXT = (PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC)GetProc("glNamedCopyBufferSubDataEXT", total, loaded);
		glNamedFramebufferTextureEXT = (PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC)GetProc("glNamedFramebufferTextureEXT", total, loaded);
		glNamedFramebufferTextureLayerEXT = (PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC)GetProc("glNamedFramebufferTextureLayerEXT", total, loaded);
		glNamedFramebufferTextureFaceEXT = (PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC)GetProc("glNamedFramebufferTextureFaceEXT", total, loaded);
		glTextureRenderbufferEXT = (PFNGLTEXTURERENDERBUFFEREXTPROC)GetProc("glTextureRenderbufferEXT", total, loaded);
		glMultiTexRenderbufferEXT = (PFNGLMULTITEXRENDERBUFFEREXTPROC)GetProc("glMultiTexRenderbufferEXT", total, loaded);
		glVertexArrayVertexOffsetEXT = (PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC)GetProc("glVertexArrayVertexOffsetEXT", total, loaded);
		glVertexArrayColorOffsetEXT = (PFNGLVERTEXARRAYCOLOROFFSETEXTPROC)GetProc("glVertexArrayColorOffsetEXT", total, loaded);
		glVertexArrayEdgeFlagOffsetEXT = (PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC)GetProc("glVertexArrayEdgeFlagOffsetEXT", total, loaded);
		glVertexArrayIndexOffsetEXT = (PFNGLVERTEXARRAYINDEXOFFSETEXTPROC)GetProc("glVertexArrayIndexOffsetEXT", total, loaded);
		glVertexArrayNormalOffsetEXT = (PFNGLVERTEXARRAYNORMALOFFSETEXTPROC)GetProc("glVertexArrayNormalOffsetEXT", total, loaded);
		glVertexArrayTexCoordOffsetEXT = (PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC)GetProc("glVertexArrayTexCoordOffsetEXT", total, loaded);
		glVertexArrayMultiTexCoordOffsetEXT = (PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC)GetProc("glVertexArrayMultiTexCoordOffsetEXT", total, loaded);
		glVertexArrayFogCoordOffsetEXT = (PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC)GetProc("glVertexArrayFogCoordOffsetEXT", total, loaded);
		glVertexArraySecondaryColorOffsetEXT = (PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC)GetProc("glVertexArraySecondaryColorOffsetEXT", total, loaded);
		glVertexArrayVertexAttribOffsetEXT = (PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC)GetProc("glVertexArrayVertexAttribOffsetEXT", total, loaded);
		glVertexArrayVertexAttribIOffsetEXT = (PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC)GetProc("glVertexArrayVertexAttribIOffsetEXT", total, loaded);
		glEnableVertexArrayEXT = (PFNGLENABLEVERTEXARRAYEXTPROC)GetProc("glEnableVertexArrayEXT", total, loaded);
		glDisableVertexArrayEXT = (PFNGLDISABLEVERTEXARRAYEXTPROC)GetProc("glDisableVertexArrayEXT", total, loaded);
		glEnableVertexArrayAttribEXT = (PFNGLENABLEVERTEXARRAYATTRIBEXTPROC)GetProc("glEnableVertexArrayAttribEXT", total, loaded);
		glDisableVertexArrayAttribEXT = (PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC)GetProc("glDisableVertexArrayAttribEXT", total, loaded);
		glGetVertexArrayIntegervEXT = (PFNGLGETVERTEXARRAYINTEGERVEXTPROC)GetProc("glGetVertexArrayIntegervEXT", total, loaded);
		glGetVertexArrayPointervEXT = (PFNGLGETVERTEXARRAYPOINTERVEXTPROC)GetProc("glGetVertexArrayPointervEXT", total, loaded);
		glGetVertexArrayIntegeri_vEXT = (PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC)GetProc("glGetVertexArrayIntegeri_vEXT", total, loaded);
		glGetVertexArrayPointeri_vEXT = (PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC)GetProc("glGetVertexArrayPointeri_vEXT", total, loaded);
		glMapNamedBufferRangeEXT = (PFNGLMAPNAMEDBUFFERRANGEEXTPROC)GetProc("glMapNamedBufferRangeEXT", total, loaded);
		glFlushMappedNamedBufferRangeEXT = (PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC)GetProc("glFlushMappedNamedBufferRangeEXT", total, loaded);
		glNamedBufferStorageEXT = (PFNGLNAMEDBUFFERSTORAGEEXTPROC)GetProc("glNamedBufferStorageEXT", total, loaded);
		glClearNamedBufferDataEXT = (PFNGLCLEARNAMEDBUFFERDATAEXTPROC)GetProc("glClearNamedBufferDataEXT", total, loaded);
		glClearNamedBufferSubDataEXT = (PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC)GetProc("glClearNamedBufferSubDataEXT", total, loaded);
		glNamedFramebufferParameteriEXT = (PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC)GetProc("glNamedFramebufferParameteriEXT", total, loaded);
		glGetNamedFramebufferParameterivEXT = (PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC)GetProc("glGetNamedFramebufferParameterivEXT", total, loaded);
		glProgramUniform1dEXT = (PFNGLPROGRAMUNIFORM1DEXTPROC)GetProc("glProgramUniform1dEXT", total, loaded);
		glProgramUniform2dEXT = (PFNGLPROGRAMUNIFORM2DEXTPROC)GetProc("glProgramUniform2dEXT", total, loaded);
		glProgramUniform3dEXT = (PFNGLPROGRAMUNIFORM3DEXTPROC)GetProc("glProgramUniform3dEXT", total, loaded);
		glProgramUniform4dEXT = (PFNGLPROGRAMUNIFORM4DEXTPROC)GetProc("glProgramUniform4dEXT", total, loaded);
		glProgramUniform1dvEXT = (PFNGLPROGRAMUNIFORM1DVEXTPROC)GetProc("glProgramUniform1dvEXT", total, loaded);
		glProgramUniform2dvEXT = (PFNGLPROGRAMUNIFORM2DVEXTPROC)GetProc("glProgramUniform2dvEXT", total, loaded);
		glProgramUniform3dvEXT = (PFNGLPROGRAMUNIFORM3DVEXTPROC)GetProc("glProgramUniform3dvEXT", total, loaded);
		glProgramUniform4dvEXT = (PFNGLPROGRAMUNIFORM4DVEXTPROC)GetProc("glProgramUniform4dvEXT", total, loaded);
		glProgramUniformMatrix2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC)GetProc("glProgramUniformMatrix2dvEXT", total, loaded);
		glProgramUniformMatrix3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC)GetProc("glProgramUniformMatrix3dvEXT", total, loaded);
		glProgramUniformMatrix4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC)GetProc("glProgramUniformMatrix4dvEXT", total, loaded);
		glProgramUniformMatrix2x3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC)GetProc("glProgramUniformMatrix2x3dvEXT", total, loaded);
		glProgramUniformMatrix2x4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC)GetProc("glProgramUniformMatrix2x4dvEXT", total, loaded);
		glProgramUniformMatrix3x2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC)GetProc("glProgramUniformMatrix3x2dvEXT", total, loaded);
		glProgramUniformMatrix3x4dvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC)GetProc("glProgramUniformMatrix3x4dvEXT", total, loaded);
		glProgramUniformMatrix4x2dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC)GetProc("glProgramUniformMatrix4x2dvEXT", total, loaded);
		glProgramUniformMatrix4x3dvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC)GetProc("glProgramUniformMatrix4x3dvEXT", total, loaded);
		glTextureBufferRangeEXT = (PFNGLTEXTUREBUFFERRANGEEXTPROC)GetProc("glTextureBufferRangeEXT", total, loaded);
		glTextureStorage1DEXT = (PFNGLTEXTURESTORAGE1DEXTPROC)GetProc("glTextureStorage1DEXT", total, loaded);
		glTextureStorage2DEXT = (PFNGLTEXTURESTORAGE2DEXTPROC)GetProc("glTextureStorage2DEXT", total, loaded);
		glTextureStorage3DEXT = (PFNGLTEXTURESTORAGE3DEXTPROC)GetProc("glTextureStorage3DEXT", total, loaded);
		glTextureStorage2DMultisampleEXT = (PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC)GetProc("glTextureStorage2DMultisampleEXT", total, loaded);
		glTextureStorage3DMultisampleEXT = (PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC)GetProc("glTextureStorage3DMultisampleEXT", total, loaded);
		glVertexArrayBindVertexBufferEXT = (PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC)GetProc("glVertexArrayBindVertexBufferEXT", total, loaded);
		glVertexArrayVertexAttribFormatEXT = (PFNGLVERTEXARRAYVERTEXATTRIBFORMATEXTPROC)GetProc("glVertexArrayVertexAttribFormatEXT", total, loaded);
		glVertexArrayVertexAttribIFormatEXT = (PFNGLVERTEXARRAYVERTEXATTRIBIFORMATEXTPROC)GetProc("glVertexArrayVertexAttribIFormatEXT", total, loaded);
		glVertexArrayVertexAttribLFormatEXT = (PFNGLVERTEXARRAYVERTEXATTRIBLFORMATEXTPROC)GetProc("glVertexArrayVertexAttribLFormatEXT", total, loaded);
		glVertexArrayVertexAttribBindingEXT = (PFNGLVERTEXARRAYVERTEXATTRIBBINDINGEXTPROC)GetProc("glVertexArrayVertexAttribBindingEXT", total, loaded);
		glVertexArrayVertexBindingDivisorEXT = (PFNGLVERTEXARRAYVERTEXBINDINGDIVISOREXTPROC)GetProc("glVertexArrayVertexBindingDivisorEXT", total, loaded);
		glVertexArrayVertexAttribLOffsetEXT = (PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC)GetProc("glVertexArrayVertexAttribLOffsetEXT", total, loaded);
		glTexturePageCommitmentEXT = (PFNGLTEXTUREPAGECOMMITMENTEXTPROC)GetProc("glTexturePageCommitmentEXT", total, loaded);
		glVertexArrayVertexAttribDivisorEXT = (PFNGLVERTEXARRAYVERTEXATTRIBDIVISOREXTPROC)GetProc("glVertexArrayVertexAttribDivisorEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_EXT_direct_state_access" << std::endl;
	#endif
		// GL_EXT_draw_instanced
		total = loaded = 0;
		glDrawArraysInstancedEXT = (PFNGLDRAWARRAYSINSTANCEDEXTPROC)GetProc("glDrawArraysInstancedEXT", total, loaded);
		glDrawElementsInstancedEXT = (PFNGLDRAWELEMENTSINSTANCEDEXTPROC)GetProc("glDrawElementsInstancedEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_EXT_draw_instanced" << std::endl;
	#endif
		// GL_EXT_polygon_offset_clamp
		total = loaded = 0;
		glPolygonOffsetClampEXT = (PFNGLPOLYGONOFFSETCLAMPEXTPROC)GetProc("glPolygonOffsetClampEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_EXT_polygon_offset_clamp" << std::endl;
	#endif
		// GL_EXT_raster_multisample
		total = loaded = 0;
		glRasterSamplesEXT = (PFNGLRASTERSAMPLESEXTPROC)GetProc("glRasterSamplesEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_EXT_raster_multisample" << std::endl;
	#endif
		// GL_EXT_separate_shader_objects
		total = loaded = 0;
		glUseShaderProgramEXT = (PFNGLUSESHADERPROGRAMEXTPROC)GetProc("glUseShaderProgramEXT", total, loaded);
		glActiveProgramEXT = (PFNGLACTIVEPROGRAMEXTPROC)GetProc("glActiveProgramEXT", total, loaded);
		glCreateShaderProgramEXT = (PFNGLCREATESHADERPROGRAMEXTPROC)GetProc("glCreateShaderProgramEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_EXT_separate_shader_objects" << std::endl;
	#endif
		// GL_EXT_shader_framebuffer_fetch_non_coherent
		total = loaded = 0;
		glFramebufferFetchBarrierEXT = (PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC)GetProc("glFramebufferFetchBarrierEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_EXT_shader_framebuffer_fetch_non_coherent" << std::endl;
	#endif
		// GL_EXT_window_rectangles
		total = loaded = 0;
		glWindowRectanglesEXT = (PFNGLWINDOWRECTANGLESEXTPROC)GetProc("glWindowRectanglesEXT", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_EXT_window_rectangles" << std::endl;
	#endif
		// GL_INTEL_framebuffer_CMAA
		total = loaded = 0;
		glApplyFramebufferAttachmentCMAAINTEL = (PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC)GetProc("glApplyFramebufferAttachmentCMAAINTEL", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_INTEL_framebuffer_CMAA" << std::endl;
	#endif
		// GL_INTEL_performance_query
		total = loaded = 0;
		glBeginPerfQueryINTEL = (PFNGLBEGINPERFQUERYINTELPROC)GetProc("glBeginPerfQueryINTEL", total, loaded);
		glCreatePerfQueryINTEL = (PFNGLCREATEPERFQUERYINTELPROC)GetProc("glCreatePerfQueryINTEL", total, loaded);
		glDeletePerfQueryINTEL = (PFNGLDELETEPERFQUERYINTELPROC)GetProc("glDeletePerfQueryINTEL", total, loaded);
		glEndPerfQueryINTEL = (PFNGLENDPERFQUERYINTELPROC)GetProc("glEndPerfQueryINTEL", total, loaded);
		glGetFirstPerfQueryIdINTEL = (PFNGLGETFIRSTPERFQUERYIDINTELPROC)GetProc("glGetFirstPerfQueryIdINTEL", total, loaded);
		glGetNextPerfQueryIdINTEL = (PFNGLGETNEXTPERFQUERYIDINTELPROC)GetProc("glGetNextPerfQueryIdINTEL", total, loaded);
		glGetPerfCounterInfoINTEL = (PFNGLGETPERFCOUNTERINFOINTELPROC)GetProc("glGetPerfCounterInfoINTEL", total, loaded);
		glGetPerfQueryDataINTEL = (PFNGLGETPERFQUERYDATAINTELPROC)GetProc("glGetPerfQueryDataINTEL", total, loaded);
		glGetPerfQueryIdByNameINTEL = (PFNGLGETPERFQUERYIDBYNAMEINTELPROC)GetProc("glGetPerfQueryIdByNameINTEL", total, loaded);
		glGetPerfQueryInfoINTEL = (PFNGLGETPERFQUERYINFOINTELPROC)GetProc("glGetPerfQueryInfoINTEL", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_INTEL_performance_query" << std::endl;
	#endif
		// GL_MESA_framebuffer_flip_y
		total = loaded = 0;
		glFramebufferParameteriMESA = (PFNGLFRAMEBUFFERPARAMETERIMESAPROC)GetProc("glFramebufferParameteriMESA", total, loaded);
		glGetFramebufferParameterivMESA = (PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC)GetProc("glGetFramebufferParameterivMESA", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_MESA_framebuffer_flip_y" << std::endl;
	#endif
		// GL_NV_bindless_multi_draw_indirect
		total = loaded = 0;
		glMultiDrawArraysIndirectBindlessNV = (PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSNVPROC)GetProc("glMultiDrawArraysIndirectBindlessNV", total, loaded);
		glMultiDrawElementsIndirectBindlessNV = (PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSNVPROC)GetProc("glMultiDrawElementsIndirectBindlessNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_bindless_multi_draw_indirect" << std::endl;
	#endif
		// GL_NV_bindless_multi_draw_indirect_count
		total = loaded = 0;
		glMultiDrawArraysIndirectBindlessCountNV = (PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSCOUNTNVPROC)GetProc("glMultiDrawArraysIndirectBindlessCountNV", total, loaded);
		glMultiDrawElementsIndirectBindlessCountNV = (PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSCOUNTNVPROC)GetProc("glMultiDrawElementsIndirectBindlessCountNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_bindless_multi_draw_indirect_count" << std::endl;
	#endif
		// GL_NV_bindless_texture
		total = loaded = 0;
		glGetTextureHandleNV = (PFNGLGETTEXTUREHANDLENVPROC)GetProc("glGetTextureHandleNV", total, loaded);
		glGetTextureSamplerHandleNV = (PFNGLGETTEXTURESAMPLERHANDLENVPROC)GetProc("glGetTextureSamplerHandleNV", total, loaded);
		glMakeTextureHandleResidentNV = (PFNGLMAKETEXTUREHANDLERESIDENTNVPROC)GetProc("glMakeTextureHandleResidentNV", total, loaded);
		glMakeTextureHandleNonResidentNV = (PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC)GetProc("glMakeTextureHandleNonResidentNV", total, loaded);
		glGetImageHandleNV = (PFNGLGETIMAGEHANDLENVPROC)GetProc("glGetImageHandleNV", total, loaded);
		glMakeImageHandleResidentNV = (PFNGLMAKEIMAGEHANDLERESIDENTNVPROC)GetProc("glMakeImageHandleResidentNV", total, loaded);
		glMakeImageHandleNonResidentNV = (PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC)GetProc("glMakeImageHandleNonResidentNV", total, loaded);
		glUniformHandleui64NV = (PFNGLUNIFORMHANDLEUI64NVPROC)GetProc("glUniformHandleui64NV", total, loaded);
		glUniformHandleui64vNV = (PFNGLUNIFORMHANDLEUI64VNVPROC)GetProc("glUniformHandleui64vNV", total, loaded);
		glProgramUniformHandleui64NV = (PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC)GetProc("glProgramUniformHandleui64NV", total, loaded);
		glProgramUniformHandleui64vNV = (PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC)GetProc("glProgramUniformHandleui64vNV", total, loaded);
		glIsTextureHandleResidentNV = (PFNGLISTEXTUREHANDLERESIDENTNVPROC)GetProc("glIsTextureHandleResidentNV", total, loaded);
		glIsImageHandleResidentNV = (PFNGLISIMAGEHANDLERESIDENTNVPROC)GetProc("glIsImageHandleResidentNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_bindless_texture" << std::endl;
	#endif
		// GL_NV_blend_equation_advanced
		total = loaded = 0;
		glBlendParameteriNV = (PFNGLBLENDPARAMETERINVPROC)GetProc("glBlendParameteriNV", total, loaded);
		glBlendBarrierNV = (PFNGLBLENDBARRIERNVPROC)GetProc("glBlendBarrierNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_blend_equation_advanced" << std::endl;
	#endif
		// GL_NV_clip_space_w_scaling
		total = loaded = 0;
		glViewportPositionWScaleNV = (PFNGLVIEWPORTPOSITIONWSCALENVPROC)GetProc("glViewportPositionWScaleNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_clip_space_w_scaling" << std::endl;
	#endif
		// GL_NV_command_list
		total = loaded = 0;
		glCreateStatesNV = (PFNGLCREATESTATESNVPROC)GetProc("glCreateStatesNV", total, loaded);
		glDeleteStatesNV = (PFNGLDELETESTATESNVPROC)GetProc("glDeleteStatesNV", total, loaded);
		glIsStateNV = (PFNGLISSTATENVPROC)GetProc("glIsStateNV", total, loaded);
		glStateCaptureNV = (PFNGLSTATECAPTURENVPROC)GetProc("glStateCaptureNV", total, loaded);
		glGetCommandHeaderNV = (PFNGLGETCOMMANDHEADERNVPROC)GetProc("glGetCommandHeaderNV", total, loaded);
		glGetStageIndexNV = (PFNGLGETSTAGEINDEXNVPROC)GetProc("glGetStageIndexNV", total, loaded);
		glDrawCommandsNV = (PFNGLDRAWCOMMANDSNVPROC)GetProc("glDrawCommandsNV", total, loaded);
		glDrawCommandsAddressNV = (PFNGLDRAWCOMMANDSADDRESSNVPROC)GetProc("glDrawCommandsAddressNV", total, loaded);
		glDrawCommandsStatesNV = (PFNGLDRAWCOMMANDSSTATESNVPROC)GetProc("glDrawCommandsStatesNV", total, loaded);
		glDrawCommandsStatesAddressNV = (PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC)GetProc("glDrawCommandsStatesAddressNV", total, loaded);
		glCreateCommandListsNV = (PFNGLCREATECOMMANDLISTSNVPROC)GetProc("glCreateCommandListsNV", total, loaded);
		glDeleteCommandListsNV = (PFNGLDELETECOMMANDLISTSNVPROC)GetProc("glDeleteCommandListsNV", total, loaded);
		glIsCommandListNV = (PFNGLISCOMMANDLISTNVPROC)GetProc("glIsCommandListNV", total, loaded);
		glListDrawCommandsStatesClientNV = (PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC)GetProc("glListDrawCommandsStatesClientNV", total, loaded);
		glCommandListSegmentsNV = (PFNGLCOMMANDLISTSEGMENTSNVPROC)GetProc("glCommandListSegmentsNV", total, loaded);
		glCompileCommandListNV = (PFNGLCOMPILECOMMANDLISTNVPROC)GetProc("glCompileCommandListNV", total, loaded);
		glCallCommandListNV = (PFNGLCALLCOMMANDLISTNVPROC)GetProc("glCallCommandListNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_command_list" << std::endl;
	#endif
		// GL_NV_conditional_render
		total = loaded = 0;
		glBeginConditionalRenderNV = (PFNGLBEGINCONDITIONALRENDERNVPROC)GetProc("glBeginConditionalRenderNV", total, loaded);
		glEndConditionalRenderNV = (PFNGLENDCONDITIONALRENDERNVPROC)GetProc("glEndConditionalRenderNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_conditional_render" << std::endl;
	#endif
		// GL_NV_conservative_raster
		total = loaded = 0;
		glSubpixelPrecisionBiasNV = (PFNGLSUBPIXELPRECISIONBIASNVPROC)GetProc("glSubpixelPrecisionBiasNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_conservative_raster" << std::endl;
	#endif
		// GL_NV_conservative_raster_dilate
		total = loaded = 0;
		glConservativeRasterParameterfNV = (PFNGLCONSERVATIVERASTERPARAMETERFNVPROC)GetProc("glConservativeRasterParameterfNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_conservative_raster_dilate" << std::endl;
	#endif
		// GL_NV_conservative_raster_pre_snap_triangles
		total = loaded = 0;
		glConservativeRasterParameteriNV = (PFNGLCONSERVATIVERASTERPARAMETERINVPROC)GetProc("glConservativeRasterParameteriNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_conservative_raster_pre_snap_triangles" << std::endl;
	#endif
		// GL_NV_depth_buffer_float
		total = loaded = 0;
		glDepthRangedNV = (PFNGLDEPTHRANGEDNVPROC)GetProc("glDepthRangedNV", total, loaded);
		glClearDepthdNV = (PFNGLCLEARDEPTHDNVPROC)GetProc("glClearDepthdNV", total, loaded);
		glDepthBoundsdNV = (PFNGLDEPTHBOUNDSDNVPROC)GetProc("glDepthBoundsdNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_depth_buffer_float" << std::endl;
	#endif
		// GL_NV_draw_vulkan_image
		total = loaded = 0;
		glDrawVkImageNV = (PFNGLDRAWVKIMAGENVPROC)GetProc("glDrawVkImageNV", total, loaded);
		glGetVkProcAddrNV = (PFNGLGETVKPROCADDRNVPROC)GetProc("glGetVkProcAddrNV", total, loaded);
		glWaitVkSemaphoreNV = (PFNGLWAITVKSEMAPHORENVPROC)GetProc("glWaitVkSemaphoreNV", total, loaded);
		glSignalVkSemaphoreNV = (PFNGLSIGNALVKSEMAPHORENVPROC)GetProc("glSignalVkSemaphoreNV", total, loaded);
		glSignalVkFenceNV = (PFNGLSIGNALVKFENCENVPROC)GetProc("glSignalVkFenceNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_draw_vulkan_image" << std::endl;
	#endif
		// GL_NV_fragment_coverage_to_color
		total = loaded = 0;
		glFragmentCoverageColorNV = (PFNGLFRAGMENTCOVERAGECOLORNVPROC)GetProc("glFragmentCoverageColorNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_fragment_coverage_to_color" << std::endl;
	#endif
		// GL_NV_framebuffer_mixed_samples
		total = loaded = 0;
		glCoverageModulationTableNV = (PFNGLCOVERAGEMODULATIONTABLENVPROC)GetProc("glCoverageModulationTableNV", total, loaded);
		glGetCoverageModulationTableNV = (PFNGLGETCOVERAGEMODULATIONTABLENVPROC)GetProc("glGetCoverageModulationTableNV", total, loaded);
		glCoverageModulationNV = (PFNGLCOVERAGEMODULATIONNVPROC)GetProc("glCoverageModulationNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_framebuffer_mixed_samples" << std::endl;
	#endif
		// GL_NV_framebuffer_multisample_coverage
		total = loaded = 0;
		glRenderbufferStorageMultisampleCoverageNV = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC)GetProc("glRenderbufferStorageMultisampleCoverageNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_framebuffer_multisample_coverage" << std::endl;
	#endif
		// GL_NV_gpu_shader5
		total = loaded = 0;
		glUniform1i64NV = (PFNGLUNIFORM1I64NVPROC)GetProc("glUniform1i64NV", total, loaded);
		glUniform2i64NV = (PFNGLUNIFORM2I64NVPROC)GetProc("glUniform2i64NV", total, loaded);
		glUniform3i64NV = (PFNGLUNIFORM3I64NVPROC)GetProc("glUniform3i64NV", total, loaded);
		glUniform4i64NV = (PFNGLUNIFORM4I64NVPROC)GetProc("glUniform4i64NV", total, loaded);
		glUniform1i64vNV = (PFNGLUNIFORM1I64VNVPROC)GetProc("glUniform1i64vNV", total, loaded);
		glUniform2i64vNV = (PFNGLUNIFORM2I64VNVPROC)GetProc("glUniform2i64vNV", total, loaded);
		glUniform3i64vNV = (PFNGLUNIFORM3I64VNVPROC)GetProc("glUniform3i64vNV", total, loaded);
		glUniform4i64vNV = (PFNGLUNIFORM4I64VNVPROC)GetProc("glUniform4i64vNV", total, loaded);
		glUniform1ui64NV = (PFNGLUNIFORM1UI64NVPROC)GetProc("glUniform1ui64NV", total, loaded);
		glUniform2ui64NV = (PFNGLUNIFORM2UI64NVPROC)GetProc("glUniform2ui64NV", total, loaded);
		glUniform3ui64NV = (PFNGLUNIFORM3UI64NVPROC)GetProc("glUniform3ui64NV", total, loaded);
		glUniform4ui64NV = (PFNGLUNIFORM4UI64NVPROC)GetProc("glUniform4ui64NV", total, loaded);
		glUniform1ui64vNV = (PFNGLUNIFORM1UI64VNVPROC)GetProc("glUniform1ui64vNV", total, loaded);
		glUniform2ui64vNV = (PFNGLUNIFORM2UI64VNVPROC)GetProc("glUniform2ui64vNV", total, loaded);
		glUniform3ui64vNV = (PFNGLUNIFORM3UI64VNVPROC)GetProc("glUniform3ui64vNV", total, loaded);
		glUniform4ui64vNV = (PFNGLUNIFORM4UI64VNVPROC)GetProc("glUniform4ui64vNV", total, loaded);
		glGetUniformi64vNV = (PFNGLGETUNIFORMI64VNVPROC)GetProc("glGetUniformi64vNV", total, loaded);
		glProgramUniform1i64NV = (PFNGLPROGRAMUNIFORM1I64NVPROC)GetProc("glProgramUniform1i64NV", total, loaded);
		glProgramUniform2i64NV = (PFNGLPROGRAMUNIFORM2I64NVPROC)GetProc("glProgramUniform2i64NV", total, loaded);
		glProgramUniform3i64NV = (PFNGLPROGRAMUNIFORM3I64NVPROC)GetProc("glProgramUniform3i64NV", total, loaded);
		glProgramUniform4i64NV = (PFNGLPROGRAMUNIFORM4I64NVPROC)GetProc("glProgramUniform4i64NV", total, loaded);
		glProgramUniform1i64vNV = (PFNGLPROGRAMUNIFORM1I64VNVPROC)GetProc("glProgramUniform1i64vNV", total, loaded);
		glProgramUniform2i64vNV = (PFNGLPROGRAMUNIFORM2I64VNVPROC)GetProc("glProgramUniform2i64vNV", total, loaded);
		glProgramUniform3i64vNV = (PFNGLPROGRAMUNIFORM3I64VNVPROC)GetProc("glProgramUniform3i64vNV", total, loaded);
		glProgramUniform4i64vNV = (PFNGLPROGRAMUNIFORM4I64VNVPROC)GetProc("glProgramUniform4i64vNV", total, loaded);
		glProgramUniform1ui64NV = (PFNGLPROGRAMUNIFORM1UI64NVPROC)GetProc("glProgramUniform1ui64NV", total, loaded);
		glProgramUniform2ui64NV = (PFNGLPROGRAMUNIFORM2UI64NVPROC)GetProc("glProgramUniform2ui64NV", total, loaded);
		glProgramUniform3ui64NV = (PFNGLPROGRAMUNIFORM3UI64NVPROC)GetProc("glProgramUniform3ui64NV", total, loaded);
		glProgramUniform4ui64NV = (PFNGLPROGRAMUNIFORM4UI64NVPROC)GetProc("glProgramUniform4ui64NV", total, loaded);
		glProgramUniform1ui64vNV = (PFNGLPROGRAMUNIFORM1UI64VNVPROC)GetProc("glProgramUniform1ui64vNV", total, loaded);
		glProgramUniform2ui64vNV = (PFNGLPROGRAMUNIFORM2UI64VNVPROC)GetProc("glProgramUniform2ui64vNV", total, loaded);
		glProgramUniform3ui64vNV = (PFNGLPROGRAMUNIFORM3UI64VNVPROC)GetProc("glProgramUniform3ui64vNV", total, loaded);
		glProgramUniform4ui64vNV = (PFNGLPROGRAMUNIFORM4UI64VNVPROC)GetProc("glProgramUniform4ui64vNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_gpu_shader5" << std::endl;
	#endif
		// GL_NV_internalformat_sample_query
		total = loaded = 0;
		glGetInternalformatSampleivNV = (PFNGLGETINTERNALFORMATSAMPLEIVNVPROC)GetProc("glGetInternalformatSampleivNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_internalformat_sample_query" << std::endl;
	#endif
		// GL_NV_memory_attachment
		total = loaded = 0;
		glGetMemoryObjectDetachedResourcesuivNV = (PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC)GetProc("glGetMemoryObjectDetachedResourcesuivNV", total, loaded);
		glResetMemoryObjectParameterNV = (PFNGLRESETMEMORYOBJECTPARAMETERNVPROC)GetProc("glResetMemoryObjectParameterNV", total, loaded);
		glTexAttachMemoryNV = (PFNGLTEXATTACHMEMORYNVPROC)GetProc("glTexAttachMemoryNV", total, loaded);
		glBufferAttachMemoryNV = (PFNGLBUFFERATTACHMEMORYNVPROC)GetProc("glBufferAttachMemoryNV", total, loaded);
		glTextureAttachMemoryNV = (PFNGLTEXTUREATTACHMEMORYNVPROC)GetProc("glTextureAttachMemoryNV", total, loaded);
		glNamedBufferAttachMemoryNV = (PFNGLNAMEDBUFFERATTACHMEMORYNVPROC)GetProc("glNamedBufferAttachMemoryNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_memory_attachment" << std::endl;
	#endif
		// GL_NV_memory_object_sparse
		total = loaded = 0;
		glBufferPageCommitmentMemNV = (PFNGLBUFFERPAGECOMMITMENTMEMNVPROC)GetProc("glBufferPageCommitmentMemNV", total, loaded);
		glTexPageCommitmentMemNV = (PFNGLTEXPAGECOMMITMENTMEMNVPROC)GetProc("glTexPageCommitmentMemNV", total, loaded);
		glNamedBufferPageCommitmentMemNV = (PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC)GetProc("glNamedBufferPageCommitmentMemNV", total, loaded);
		glTexturePageCommitmentMemNV = (PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC)GetProc("glTexturePageCommitmentMemNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_memory_object_sparse" << std::endl;
	#endif
		// GL_NV_mesh_shader
		total = loaded = 0;
		glDrawMeshTasksNV = (PFNGLDRAWMESHTASKSNVPROC)GetProc("glDrawMeshTasksNV", total, loaded);
		glDrawMeshTasksIndirectNV = (PFNGLDRAWMESHTASKSINDIRECTNVPROC)GetProc("glDrawMeshTasksIndirectNV", total, loaded);
		glMultiDrawMeshTasksIndirectNV = (PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC)GetProc("glMultiDrawMeshTasksIndirectNV", total, loaded);
		glMultiDrawMeshTasksIndirectCountNV = (PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC)GetProc("glMultiDrawMeshTasksIndirectCountNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_mesh_shader" << std::endl;
	#endif
		// GL_NV_path_rendering
		total = loaded = 0;
		glGenPathsNV = (PFNGLGENPATHSNVPROC)GetProc("glGenPathsNV", total, loaded);
		glDeletePathsNV = (PFNGLDELETEPATHSNVPROC)GetProc("glDeletePathsNV", total, loaded);
		glIsPathNV = (PFNGLISPATHNVPROC)GetProc("glIsPathNV", total, loaded);
		glPathCommandsNV = (PFNGLPATHCOMMANDSNVPROC)GetProc("glPathCommandsNV", total, loaded);
		glPathCoordsNV = (PFNGLPATHCOORDSNVPROC)GetProc("glPathCoordsNV", total, loaded);
		glPathSubCommandsNV = (PFNGLPATHSUBCOMMANDSNVPROC)GetProc("glPathSubCommandsNV", total, loaded);
		glPathSubCoordsNV = (PFNGLPATHSUBCOORDSNVPROC)GetProc("glPathSubCoordsNV", total, loaded);
		glPathStringNV = (PFNGLPATHSTRINGNVPROC)GetProc("glPathStringNV", total, loaded);
		glPathGlyphsNV = (PFNGLPATHGLYPHSNVPROC)GetProc("glPathGlyphsNV", total, loaded);
		glPathGlyphRangeNV = (PFNGLPATHGLYPHRANGENVPROC)GetProc("glPathGlyphRangeNV", total, loaded);
		glWeightPathsNV = (PFNGLWEIGHTPATHSNVPROC)GetProc("glWeightPathsNV", total, loaded);
		glCopyPathNV = (PFNGLCOPYPATHNVPROC)GetProc("glCopyPathNV", total, loaded);
		glInterpolatePathsNV = (PFNGLINTERPOLATEPATHSNVPROC)GetProc("glInterpolatePathsNV", total, loaded);
		glTransformPathNV = (PFNGLTRANSFORMPATHNVPROC)GetProc("glTransformPathNV", total, loaded);
		glPathParameterivNV = (PFNGLPATHPARAMETERIVNVPROC)GetProc("glPathParameterivNV", total, loaded);
		glPathParameteriNV = (PFNGLPATHPARAMETERINVPROC)GetProc("glPathParameteriNV", total, loaded);
		glPathParameterfvNV = (PFNGLPATHPARAMETERFVNVPROC)GetProc("glPathParameterfvNV", total, loaded);
		glPathParameterfNV = (PFNGLPATHPARAMETERFNVPROC)GetProc("glPathParameterfNV", total, loaded);
		glPathDashArrayNV = (PFNGLPATHDASHARRAYNVPROC)GetProc("glPathDashArrayNV", total, loaded);
		glPathStencilFuncNV = (PFNGLPATHSTENCILFUNCNVPROC)GetProc("glPathStencilFuncNV", total, loaded);
		glPathStencilDepthOffsetNV = (PFNGLPATHSTENCILDEPTHOFFSETNVPROC)GetProc("glPathStencilDepthOffsetNV", total, loaded);
		glStencilFillPathNV = (PFNGLSTENCILFILLPATHNVPROC)GetProc("glStencilFillPathNV", total, loaded);
		glStencilStrokePathNV = (PFNGLSTENCILSTROKEPATHNVPROC)GetProc("glStencilStrokePathNV", total, loaded);
		glStencilFillPathInstancedNV = (PFNGLSTENCILFILLPATHINSTANCEDNVPROC)GetProc("glStencilFillPathInstancedNV", total, loaded);
		glStencilStrokePathInstancedNV = (PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC)GetProc("glStencilStrokePathInstancedNV", total, loaded);
		glPathCoverDepthFuncNV = (PFNGLPATHCOVERDEPTHFUNCNVPROC)GetProc("glPathCoverDepthFuncNV", total, loaded);
		glCoverFillPathNV = (PFNGLCOVERFILLPATHNVPROC)GetProc("glCoverFillPathNV", total, loaded);
		glCoverStrokePathNV = (PFNGLCOVERSTROKEPATHNVPROC)GetProc("glCoverStrokePathNV", total, loaded);
		glCoverFillPathInstancedNV = (PFNGLCOVERFILLPATHINSTANCEDNVPROC)GetProc("glCoverFillPathInstancedNV", total, loaded);
		glCoverStrokePathInstancedNV = (PFNGLCOVERSTROKEPATHINSTANCEDNVPROC)GetProc("glCoverStrokePathInstancedNV", total, loaded);
		glGetPathParameterivNV = (PFNGLGETPATHPARAMETERIVNVPROC)GetProc("glGetPathParameterivNV", total, loaded);
		glGetPathParameterfvNV = (PFNGLGETPATHPARAMETERFVNVPROC)GetProc("glGetPathParameterfvNV", total, loaded);
		glGetPathCommandsNV = (PFNGLGETPATHCOMMANDSNVPROC)GetProc("glGetPathCommandsNV", total, loaded);
		glGetPathCoordsNV = (PFNGLGETPATHCOORDSNVPROC)GetProc("glGetPathCoordsNV", total, loaded);
		glGetPathDashArrayNV = (PFNGLGETPATHDASHARRAYNVPROC)GetProc("glGetPathDashArrayNV", total, loaded);
		glGetPathMetricsNV = (PFNGLGETPATHMETRICSNVPROC)GetProc("glGetPathMetricsNV", total, loaded);
		glGetPathMetricRangeNV = (PFNGLGETPATHMETRICRANGENVPROC)GetProc("glGetPathMetricRangeNV", total, loaded);
		glGetPathSpacingNV = (PFNGLGETPATHSPACINGNVPROC)GetProc("glGetPathSpacingNV", total, loaded);
		glIsPointInFillPathNV = (PFNGLISPOINTINFILLPATHNVPROC)GetProc("glIsPointInFillPathNV", total, loaded);
		glIsPointInStrokePathNV = (PFNGLISPOINTINSTROKEPATHNVPROC)GetProc("glIsPointInStrokePathNV", total, loaded);
		glGetPathLengthNV = (PFNGLGETPATHLENGTHNVPROC)GetProc("glGetPathLengthNV", total, loaded);
		glPointAlongPathNV = (PFNGLPOINTALONGPATHNVPROC)GetProc("glPointAlongPathNV", total, loaded);
		glMatrixLoad3x2fNV = (PFNGLMATRIXLOAD3X2FNVPROC)GetProc("glMatrixLoad3x2fNV", total, loaded);
		glMatrixLoad3x3fNV = (PFNGLMATRIXLOAD3X3FNVPROC)GetProc("glMatrixLoad3x3fNV", total, loaded);
		glMatrixLoadTranspose3x3fNV = (PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC)GetProc("glMatrixLoadTranspose3x3fNV", total, loaded);
		glMatrixMult3x2fNV = (PFNGLMATRIXMULT3X2FNVPROC)GetProc("glMatrixMult3x2fNV", total, loaded);
		glMatrixMult3x3fNV = (PFNGLMATRIXMULT3X3FNVPROC)GetProc("glMatrixMult3x3fNV", total, loaded);
		glMatrixMultTranspose3x3fNV = (PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC)GetProc("glMatrixMultTranspose3x3fNV", total, loaded);
		glStencilThenCoverFillPathNV = (PFNGLSTENCILTHENCOVERFILLPATHNVPROC)GetProc("glStencilThenCoverFillPathNV", total, loaded);
		glStencilThenCoverStrokePathNV = (PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC)GetProc("glStencilThenCoverStrokePathNV", total, loaded);
		glStencilThenCoverFillPathInstancedNV = (PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC)GetProc("glStencilThenCoverFillPathInstancedNV", total, loaded);
		glStencilThenCoverStrokePathInstancedNV = (PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC)GetProc("glStencilThenCoverStrokePathInstancedNV", total, loaded);
		glPathGlyphIndexRangeNV = (PFNGLPATHGLYPHINDEXRANGENVPROC)GetProc("glPathGlyphIndexRangeNV", total, loaded);
		glPathGlyphIndexArrayNV = (PFNGLPATHGLYPHINDEXARRAYNVPROC)GetProc("glPathGlyphIndexArrayNV", total, loaded);
		glPathMemoryGlyphIndexArrayNV = (PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC)GetProc("glPathMemoryGlyphIndexArrayNV", total, loaded);
		glProgramPathFragmentInputGenNV = (PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC)GetProc("glProgramPathFragmentInputGenNV", total, loaded);
		glGetProgramResourcefvNV = (PFNGLGETPROGRAMRESOURCEFVNVPROC)GetProc("glGetProgramResourcefvNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_path_rendering" << std::endl;
	#endif
		// GL_NV_sample_locations
		total = loaded = 0;
		glFramebufferSampleLocationsfvNV = (PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC)GetProc("glFramebufferSampleLocationsfvNV", total, loaded);
		glNamedFramebufferSampleLocationsfvNV = (PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC)GetProc("glNamedFramebufferSampleLocationsfvNV", total, loaded);
		glResolveDepthValuesNV = (PFNGLRESOLVEDEPTHVALUESNVPROC)GetProc("glResolveDepthValuesNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_sample_locations" << std::endl;
	#endif
		// GL_NV_scissor_exclusive
		total = loaded = 0;
		glScissorExclusiveNV = (PFNGLSCISSOREXCLUSIVENVPROC)GetProc("glScissorExclusiveNV", total, loaded);
		glScissorExclusiveArrayvNV = (PFNGLSCISSOREXCLUSIVEARRAYVNVPROC)GetProc("glScissorExclusiveArrayvNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_scissor_exclusive" << std::endl;
	#endif
		// GL_NV_shader_buffer_load
		total = loaded = 0;
		glMakeBufferResidentNV = (PFNGLMAKEBUFFERRESIDENTNVPROC)GetProc("glMakeBufferResidentNV", total, loaded);
		glMakeBufferNonResidentNV = (PFNGLMAKEBUFFERNONRESIDENTNVPROC)GetProc("glMakeBufferNonResidentNV", total, loaded);
		glIsBufferResidentNV = (PFNGLISBUFFERRESIDENTNVPROC)GetProc("glIsBufferResidentNV", total, loaded);
		glMakeNamedBufferResidentNV = (PFNGLMAKENAMEDBUFFERRESIDENTNVPROC)GetProc("glMakeNamedBufferResidentNV", total, loaded);
		glMakeNamedBufferNonResidentNV = (PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC)GetProc("glMakeNamedBufferNonResidentNV", total, loaded);
		glIsNamedBufferResidentNV = (PFNGLISNAMEDBUFFERRESIDENTNVPROC)GetProc("glIsNamedBufferResidentNV", total, loaded);
		glGetBufferParameterui64vNV = (PFNGLGETBUFFERPARAMETERUI64VNVPROC)GetProc("glGetBufferParameterui64vNV", total, loaded);
		glGetNamedBufferParameterui64vNV = (PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC)GetProc("glGetNamedBufferParameterui64vNV", total, loaded);
		glGetIntegerui64vNV = (PFNGLGETINTEGERUI64VNVPROC)GetProc("glGetIntegerui64vNV", total, loaded);
		glUniformui64NV = (PFNGLUNIFORMUI64NVPROC)GetProc("glUniformui64NV", total, loaded);
		glUniformui64vNV = (PFNGLUNIFORMUI64VNVPROC)GetProc("glUniformui64vNV", total, loaded);
		glGetUniformui64vNV = (PFNGLGETUNIFORMUI64VNVPROC)GetProc("glGetUniformui64vNV", total, loaded);
		glProgramUniformui64NV = (PFNGLPROGRAMUNIFORMUI64NVPROC)GetProc("glProgramUniformui64NV", total, loaded);
		glProgramUniformui64vNV = (PFNGLPROGRAMUNIFORMUI64VNVPROC)GetProc("glProgramUniformui64vNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_shader_buffer_load" << std::endl;
	#endif
		// GL_NV_shading_rate_image
		total = loaded = 0;
		glBindShadingRateImageNV = (PFNGLBINDSHADINGRATEIMAGENVPROC)GetProc("glBindShadingRateImageNV", total, loaded);
		glGetShadingRateImagePaletteNV = (PFNGLGETSHADINGRATEIMAGEPALETTENVPROC)GetProc("glGetShadingRateImagePaletteNV", total, loaded);
		glGetShadingRateSampleLocationivNV = (PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC)GetProc("glGetShadingRateSampleLocationivNV", total, loaded);
		glShadingRateImageBarrierNV = (PFNGLSHADINGRATEIMAGEBARRIERNVPROC)GetProc("glShadingRateImageBarrierNV", total, loaded);
		glShadingRateImagePaletteNV = (PFNGLSHADINGRATEIMAGEPALETTENVPROC)GetProc("glShadingRateImagePaletteNV", total, loaded);
		glShadingRateSampleOrderNV = (PFNGLSHADINGRATESAMPLEORDERNVPROC)GetProc("glShadingRateSampleOrderNV", total, loaded);
		glShadingRateSampleOrderCustomNV = (PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC)GetProc("glShadingRateSampleOrderCustomNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_shading_rate_image" << std::endl;
	#endif
		// GL_NV_texture_barrier
		total = loaded = 0;
		glTextureBarrierNV = (PFNGLTEXTUREBARRIERNVPROC)GetProc("glTextureBarrierNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_texture_barrier" << std::endl;
	#endif
		// GL_NV_vertex_attrib_integer_64bit
		total = loaded = 0;
		glVertexAttribL1i64NV = (PFNGLVERTEXATTRIBL1I64NVPROC)GetProc("glVertexAttribL1i64NV", total, loaded);
		glVertexAttribL2i64NV = (PFNGLVERTEXATTRIBL2I64NVPROC)GetProc("glVertexAttribL2i64NV", total, loaded);
		glVertexAttribL3i64NV = (PFNGLVERTEXATTRIBL3I64NVPROC)GetProc("glVertexAttribL3i64NV", total, loaded);
		glVertexAttribL4i64NV = (PFNGLVERTEXATTRIBL4I64NVPROC)GetProc("glVertexAttribL4i64NV", total, loaded);
		glVertexAttribL1i64vNV = (PFNGLVERTEXATTRIBL1I64VNVPROC)GetProc("glVertexAttribL1i64vNV", total, loaded);
		glVertexAttribL2i64vNV = (PFNGLVERTEXATTRIBL2I64VNVPROC)GetProc("glVertexAttribL2i64vNV", total, loaded);
		glVertexAttribL3i64vNV = (PFNGLVERTEXATTRIBL3I64VNVPROC)GetProc("glVertexAttribL3i64vNV", total, loaded);
		glVertexAttribL4i64vNV = (PFNGLVERTEXATTRIBL4I64VNVPROC)GetProc("glVertexAttribL4i64vNV", total, loaded);
		glVertexAttribL1ui64NV = (PFNGLVERTEXATTRIBL1UI64NVPROC)GetProc("glVertexAttribL1ui64NV", total, loaded);
		glVertexAttribL2ui64NV = (PFNGLVERTEXATTRIBL2UI64NVPROC)GetProc("glVertexAttribL2ui64NV", total, loaded);
		glVertexAttribL3ui64NV = (PFNGLVERTEXATTRIBL3UI64NVPROC)GetProc("glVertexAttribL3ui64NV", total, loaded);
		glVertexAttribL4ui64NV = (PFNGLVERTEXATTRIBL4UI64NVPROC)GetProc("glVertexAttribL4ui64NV", total, loaded);
		glVertexAttribL1ui64vNV = (PFNGLVERTEXATTRIBL1UI64VNVPROC)GetProc("glVertexAttribL1ui64vNV", total, loaded);
		glVertexAttribL2ui64vNV = (PFNGLVERTEXATTRIBL2UI64VNVPROC)GetProc("glVertexAttribL2ui64vNV", total, loaded);
		glVertexAttribL3ui64vNV = (PFNGLVERTEXATTRIBL3UI64VNVPROC)GetProc("glVertexAttribL3ui64vNV", total, loaded);
		glVertexAttribL4ui64vNV = (PFNGLVERTEXATTRIBL4UI64VNVPROC)GetProc("glVertexAttribL4ui64vNV", total, loaded);
		glGetVertexAttribLi64vNV = (PFNGLGETVERTEXATTRIBLI64VNVPROC)GetProc("glGetVertexAttribLi64vNV", total, loaded);
		glGetVertexAttribLui64vNV = (PFNGLGETVERTEXATTRIBLUI64VNVPROC)GetProc("glGetVertexAttribLui64vNV", total, loaded);
		glVertexAttribLFormatNV = (PFNGLVERTEXATTRIBLFORMATNVPROC)GetProc("glVertexAttribLFormatNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_vertex_attrib_integer_64bit" << std::endl;
	#endif
		// GL_NV_vertex_buffer_unified_memory
		total = loaded = 0;
		glBufferAddressRangeNV = (PFNGLBUFFERADDRESSRANGENVPROC)GetProc("glBufferAddressRangeNV", total, loaded);
		glVertexFormatNV = (PFNGLVERTEXFORMATNVPROC)GetProc("glVertexFormatNV", total, loaded);
		glNormalFormatNV = (PFNGLNORMALFORMATNVPROC)GetProc("glNormalFormatNV", total, loaded);
		glColorFormatNV = (PFNGLCOLORFORMATNVPROC)GetProc("glColorFormatNV", total, loaded);
		glIndexFormatNV = (PFNGLINDEXFORMATNVPROC)GetProc("glIndexFormatNV", total, loaded);
		glTexCoordFormatNV = (PFNGLTEXCOORDFORMATNVPROC)GetProc("glTexCoordFormatNV", total, loaded);
		glEdgeFlagFormatNV = (PFNGLEDGEFLAGFORMATNVPROC)GetProc("glEdgeFlagFormatNV", total, loaded);
		glSecondaryColorFormatNV = (PFNGLSECONDARYCOLORFORMATNVPROC)GetProc("glSecondaryColorFormatNV", total, loaded);
		glFogCoordFormatNV = (PFNGLFOGCOORDFORMATNVPROC)GetProc("glFogCoordFormatNV", total, loaded);
		glVertexAttribFormatNV = (PFNGLVERTEXATTRIBFORMATNVPROC)GetProc("glVertexAttribFormatNV", total, loaded);
		glVertexAttribIFormatNV = (PFNGLVERTEXATTRIBIFORMATNVPROC)GetProc("glVertexAttribIFormatNV", total, loaded);
		glGetIntegerui64i_vNV = (PFNGLGETINTEGERUI64I_VNVPROC)GetProc("glGetIntegerui64i_vNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_vertex_buffer_unified_memory" << std::endl;
	#endif
		// GL_NV_viewport_swizzle
		total = loaded = 0;
		glViewportSwizzleNV = (PFNGLVIEWPORTSWIZZLENVPROC)GetProc("glViewportSwizzleNV", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_NV_viewport_swizzle" << std::endl;
	#endif
		// GL_OVR_multiview
		total = loaded = 0;
		glFramebufferTextureMultiviewOVR = (PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC)GetProc("glFramebufferTextureMultiviewOVR", total, loaded);
	#ifdef _DEBUG
		if (loaded != total)
			std::cerr << "!!! Only " << loaded << " of " << total << " functions has been loaded for GL_OVR_multiview" << std::endl;
	#endif
	}
#endif

#if defined(GL_VERSION_4_3) || defined(GL_ES_VERSION_3_2)
	void
	#ifdef GL_VERSION_4_3
		APIENTRY
	#else
		GL_APIENTRY
	#endif
		DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
	{
		std::cout << "ID: " << id;
		switch (source)
		{
		case GL_DEBUG_SOURCE_API:
			std::cout << ", Source: API";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			std::cout << ", Source: WINDOW_SYSTEM";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			std::cout << ", Source: SHADER_COMPILER";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			std::cout << ", Source: THIRD_PARTY";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			std::cout << ", Source: APPLICATION";
			break;
		case GL_DEBUG_SOURCE_OTHER:
			std::cout << ", Source: OTHER";
			break;
		default:
			std::cout << ", Source: " << source;
		}
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:
			std::cout << ", Type: ERROR";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			std::cout << ", Type: DEPRECATED_BEHAVIOR";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			std::cout << ", Type: UNDEFINED_BEHAVIOR";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			std::cout << ", Type: PORTABILITY";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			std::cout << ", Type: PERFORMANCE";
			break;
		case GL_DEBUG_TYPE_MARKER:
			std::cout << ", Type: MARKER";
			break;
		case GL_DEBUG_TYPE_PUSH_GROUP:
			std::cout << ", Type: PUSH_GROUP";
			break;
		case GL_DEBUG_TYPE_POP_GROUP:
			std::cout << ", Type: POP_GROUP";
			break;
		case GL_DEBUG_TYPE_OTHER:
			std::cout << ", Type: OTHER";
			break;
		default:
			std::cout << ", Type: " << type;
		}
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			std::cout << ", Severity: HIGH";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			std::cout << ", Severity: MEDIUM";
			break;
		case GL_DEBUG_SEVERITY_LOW:
			std::cout << ", Severity: LOW";
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			std::cout << ", Severity: NOTIFICATION";
			break;
		default:
			std::cout << ", Severity: " << severity;
		}
		std::cout << ", Message: " << message << std::endl;
	}
#endif
}