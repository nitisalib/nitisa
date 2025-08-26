// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Version2.h"

// Windows
#ifdef _WIN32
	#include "4.6/glcorearb.h"
	#include "4.6/wglext.h"
#endif

// Linux
#if defined(__linux__) && !defined(__ANDROID__)
	#include "4.6/glcorearb.h"
	#include <GL/glx.h>
#endif

// Android
#if defined(__ANDROID__)
	#include <Android/native_activity.h>
	#include <EGL/egl.h>
	#include <EGL/eglext.h>
	#include <GLES3/gl32.h>
	#include <GLES3/gl3ext.h>
#endif

namespace ngl
{
	struct PlatformData
	{
	#ifdef _WIN32
		HINSTANCE instance;
	#endif
	#if defined(__linux__) && !defined(__ANDROID__)
		Display *display;
		Window window;
	#endif
	#ifdef __ANDROID__
		EGLDisplay display;
		ANativeWindow *window;
	#endif
	};

	// Windows, Linux
#if defined(_WIN32) || (defined(__linux__) && !defined(__ANDROID__))
	// 1.0
	extern PFNGLCULLFACEPROC										glCullFace;
	extern PFNGLFRONTFACEPROC										glFrontFace;
	extern PFNGLHINTPROC											glHint;
	extern PFNGLLINEWIDTHPROC										glLineWidth;
	extern PFNGLPOINTSIZEPROC										glPointSize;
	extern PFNGLPOLYGONMODEPROC										glPolygonMode;
	extern PFNGLSCISSORPROC											glScissor;
	extern PFNGLTEXPARAMETERFPROC									glTexParameterf;
	extern PFNGLTEXPARAMETERFVPROC									glTexParameterfv;
	extern PFNGLTEXPARAMETERIPROC									glTexParameteri;
	extern PFNGLTEXPARAMETERIVPROC									glTexParameteriv;
	extern PFNGLTEXIMAGE1DPROC										glTexImage1D;
	extern PFNGLTEXIMAGE2DPROC										glTexImage2D;
	extern PFNGLDRAWBUFFERPROC										glDrawBuffer;
	extern PFNGLCLEARPROC											glClear;
	extern PFNGLCLEARCOLORPROC										glClearColor;
	extern PFNGLCLEARSTENCILPROC									glClearStencil;
	extern PFNGLCLEARDEPTHPROC										glClearDepth;
	extern PFNGLSTENCILMASKPROC										glStencilMask;
	extern PFNGLCOLORMASKPROC										glColorMask;
	extern PFNGLDEPTHMASKPROC										glDepthMask;
	extern PFNGLDISABLEPROC											glDisable;
	extern PFNGLENABLEPROC											glEnable;
	extern PFNGLFINISHPROC											glFinish;
	extern PFNGLFLUSHPROC											glFlush;
	extern PFNGLBLENDFUNCPROC										glBlendFunc;
	extern PFNGLLOGICOPPROC											glLogicOp;
	extern PFNGLSTENCILFUNCPROC										glStencilFunc;
	extern PFNGLSTENCILOPPROC										glStencilOp;
	extern PFNGLDEPTHFUNCPROC										glDepthFunc;
	extern PFNGLPIXELSTOREFPROC										glPixelStoref;
	extern PFNGLPIXELSTOREIPROC										glPixelStorei;
	extern PFNGLREADBUFFERPROC										glReadBuffer;
	extern PFNGLREADPIXELSPROC										glReadPixels;
	extern PFNGLGETBOOLEANVPROC										glGetBooleanv;
	extern PFNGLGETDOUBLEVPROC										glGetDoublev;
	extern PFNGLGETERRORPROC										glGetError;
	extern PFNGLGETFLOATVPROC										glGetFloatv;
	extern PFNGLGETINTEGERVPROC										glGetIntegerv;
	extern PFNGLGETSTRINGPROC										glGetString;
	extern PFNGLGETTEXIMAGEPROC										glGetTexImage;
	extern PFNGLGETTEXPARAMETERFVPROC								glGetTexParameterfv;
	extern PFNGLGETTEXPARAMETERIVPROC								glGetTexParameteriv;
	extern PFNGLGETTEXLEVELPARAMETERFVPROC							glGetTexLevelParameterfv;
	extern PFNGLGETTEXLEVELPARAMETERIVPROC							glGetTexLevelParameteriv;
	extern PFNGLISENABLEDPROC										glIsEnabled;
	extern PFNGLDEPTHRANGEPROC										glDepthRange;
	extern PFNGLVIEWPORTPROC										glViewport;
	// 1.1
	extern PFNGLDRAWARRAYSPROC										glDrawArrays;
	extern PFNGLDRAWELEMENTSPROC									glDrawElements;
	extern PFNGLGETPOINTERVPROC										glGetPointerv;
	extern PFNGLPOLYGONOFFSETPROC									glPolygonOffset;
	extern PFNGLCOPYTEXIMAGE1DPROC									glCopyTexImage1D;
	extern PFNGLCOPYTEXIMAGE2DPROC									glCopyTexImage2D;
	extern PFNGLCOPYTEXSUBIMAGE1DPROC								glCopyTexSubImage1D;
	extern PFNGLCOPYTEXSUBIMAGE2DPROC								glCopyTexSubImage2D;
	extern PFNGLTEXSUBIMAGE1DPROC									glTexSubImage1D;
	extern PFNGLTEXSUBIMAGE2DPROC									glTexSubImage2D;
	extern PFNGLBINDTEXTUREPROC										glBindTexture;
	extern PFNGLDELETETEXTURESPROC									glDeleteTextures;
	extern PFNGLGENTEXTURESPROC										glGenTextures;
	extern PFNGLISTEXTUREPROC										glIsTexture;
	// 1.2
	extern PFNGLDRAWRANGEELEMENTSPROC								glDrawRangeElements;
	extern PFNGLTEXIMAGE3DPROC										glTexImage3D;
	extern PFNGLTEXSUBIMAGE3DPROC									glTexSubImage3D;
	extern PFNGLCOPYTEXSUBIMAGE3DPROC								glCopyTexSubImage3D;
	// 1.3
	extern PFNGLACTIVETEXTUREPROC									glActiveTexture;
	extern PFNGLSAMPLECOVERAGEPROC									glSampleCoverage;
	extern PFNGLCOMPRESSEDTEXIMAGE3DPROC							glCompressedTexImage3D;
	extern PFNGLCOMPRESSEDTEXIMAGE2DPROC							glCompressedTexImage2D;
	extern PFNGLCOMPRESSEDTEXIMAGE1DPROC							glCompressedTexImage1D;
	extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC							glCompressedTexSubImage3D;
	extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC							glCompressedTexSubImage2D;
	extern PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC							glCompressedTexSubImage1D;
	extern PFNGLGETCOMPRESSEDTEXIMAGEPROC							glGetCompressedTexImage;
	// 1.4
	extern PFNGLBLENDFUNCSEPARATEPROC								glBlendFuncSeparate;
	extern PFNGLMULTIDRAWARRAYSPROC									glMultiDrawArrays;
	extern PFNGLMULTIDRAWELEMENTSPROC								glMultiDrawElements;
	extern PFNGLPOINTPARAMETERFPROC									glPointParameterf;
	extern PFNGLPOINTPARAMETERFVPROC								glPointParameterfv;
	extern PFNGLPOINTPARAMETERIPROC									glPointParameteri;
	extern PFNGLPOINTPARAMETERIVPROC								glPointParameteriv;
	extern PFNGLBLENDCOLORPROC										glBlendColor;
	extern PFNGLBLENDEQUATIONPROC									glBlendEquation;
	// 1.5
	extern PFNGLGENQUERIESPROC										glGenQueries;
	extern PFNGLDELETEQUERIESPROC									glDeleteQueries;
	extern PFNGLISQUERYPROC											glIsQuery;
	extern PFNGLBEGINQUERYPROC										glBeginQuery;
	extern PFNGLENDQUERYPROC										glEndQuery;
	extern PFNGLGETQUERYIVPROC										glGetQueryiv;
	extern PFNGLGETQUERYOBJECTIVPROC								glGetQueryObjectiv;
	extern PFNGLGETQUERYOBJECTUIVPROC								glGetQueryObjectuiv;
	extern PFNGLBINDBUFFERPROC										glBindBuffer;
	extern PFNGLDELETEBUFFERSPROC									glDeleteBuffers;
	extern PFNGLGENBUFFERSPROC										glGenBuffers;
	extern PFNGLISBUFFERPROC										glIsBuffer;
	extern PFNGLBUFFERDATAPROC										glBufferData;
	extern PFNGLBUFFERSUBDATAPROC									glBufferSubData;
	extern PFNGLGETBUFFERSUBDATAPROC								glGetBufferSubData;
	extern PFNGLMAPBUFFERPROC										glMapBuffer;
	extern PFNGLUNMAPBUFFERPROC										glUnmapBuffer;
	extern PFNGLGETBUFFERPARAMETERIVPROC							glGetBufferParameteriv;
	extern PFNGLGETBUFFERPOINTERVPROC								glGetBufferPointerv;
	// 2.0
	extern PFNGLBLENDEQUATIONSEPARATEPROC							glBlendEquationSeparate;
	extern PFNGLDRAWBUFFERSPROC										glDrawBuffers;
	extern PFNGLSTENCILOPSEPARATEPROC								glStencilOpSeparate;
	extern PFNGLSTENCILFUNCSEPARATEPROC								glStencilFuncSeparate;
	extern PFNGLSTENCILMASKSEPARATEPROC								glStencilMaskSeparate;
	extern PFNGLATTACHSHADERPROC									glAttachShader;
	extern PFNGLBINDATTRIBLOCATIONPROC								glBindAttribLocation;
	extern PFNGLCOMPILESHADERPROC									glCompileShader;
	extern PFNGLCREATEPROGRAMPROC									glCreateProgram;
	extern PFNGLCREATESHADERPROC									glCreateShader;
	extern PFNGLDELETEPROGRAMPROC									glDeleteProgram;
	extern PFNGLDELETESHADERPROC									glDeleteShader;
	extern PFNGLDETACHSHADERPROC									glDetachShader;
	extern PFNGLDISABLEVERTEXATTRIBARRAYPROC						glDisableVertexAttribArray;
	extern PFNGLENABLEVERTEXATTRIBARRAYPROC							glEnableVertexAttribArray;
	extern PFNGLGETACTIVEATTRIBPROC									glGetActiveAttrib;
	extern PFNGLGETACTIVEUNIFORMPROC								glGetActiveUniform;
	extern PFNGLGETATTACHEDSHADERSPROC								glGetAttachedShaders;
	extern PFNGLGETATTRIBLOCATIONPROC								glGetAttribLocation;
	extern PFNGLGETPROGRAMIVPROC									glGetProgramiv;
	extern PFNGLGETPROGRAMINFOLOGPROC								glGetProgramInfoLog;
	extern PFNGLGETSHADERIVPROC										glGetShaderiv;
	extern PFNGLGETSHADERINFOLOGPROC								glGetShaderInfoLog;
	extern PFNGLGETSHADERSOURCEPROC									glGetShaderSource;
	extern PFNGLGETUNIFORMLOCATIONPROC								glGetUniformLocation;
	extern PFNGLGETUNIFORMFVPROC									glGetUniformfv;
	extern PFNGLGETUNIFORMIVPROC									glGetUniformiv;
	extern PFNGLGETVERTEXATTRIBDVPROC								glGetVertexAttribdv;
	extern PFNGLGETVERTEXATTRIBFVPROC								glGetVertexAttribfv;
	extern PFNGLGETVERTEXATTRIBIVPROC								glGetVertexAttribiv;
	extern PFNGLGETVERTEXATTRIBPOINTERVPROC							glGetVertexAttribPointerv;
	extern PFNGLISPROGRAMPROC										glIsProgram;
	extern PFNGLISSHADERPROC										glIsShader;
	extern PFNGLLINKPROGRAMPROC										glLinkProgram;
	extern PFNGLSHADERSOURCEPROC									glShaderSource;
	extern PFNGLUSEPROGRAMPROC										glUseProgram;
	extern PFNGLUNIFORM1FPROC										glUniform1f;
	extern PFNGLUNIFORM2FPROC										glUniform2f;
	extern PFNGLUNIFORM3FPROC										glUniform3f;
	extern PFNGLUNIFORM4FPROC										glUniform4f;
	extern PFNGLUNIFORM1IPROC										glUniform1i;
	extern PFNGLUNIFORM2IPROC										glUniform2i;
	extern PFNGLUNIFORM3IPROC										glUniform3i;
	extern PFNGLUNIFORM4IPROC										glUniform4i;
	extern PFNGLUNIFORM1FVPROC										glUniform1fv;
	extern PFNGLUNIFORM2FVPROC										glUniform2fv;
	extern PFNGLUNIFORM3FVPROC										glUniform3fv;
	extern PFNGLUNIFORM4FVPROC										glUniform4fv;
	extern PFNGLUNIFORM1IVPROC										glUniform1iv;
	extern PFNGLUNIFORM2IVPROC										glUniform2iv;
	extern PFNGLUNIFORM3IVPROC										glUniform3iv;
	extern PFNGLUNIFORM4IVPROC										glUniform4iv;
	extern PFNGLUNIFORMMATRIX2FVPROC								glUniformMatrix2fv;
	extern PFNGLUNIFORMMATRIX3FVPROC								glUniformMatrix3fv;
	extern PFNGLUNIFORMMATRIX4FVPROC								glUniformMatrix4fv;
	extern PFNGLVALIDATEPROGRAMPROC									glValidateProgram;
	extern PFNGLVERTEXATTRIB1DPROC									glVertexAttrib1d;
	extern PFNGLVERTEXATTRIB1DVPROC									glVertexAttrib1dv;
	extern PFNGLVERTEXATTRIB1FPROC									glVertexAttrib1f;
	extern PFNGLVERTEXATTRIB1FVPROC									glVertexAttrib1fv;
	extern PFNGLVERTEXATTRIB1SPROC									glVertexAttrib1s;
	extern PFNGLVERTEXATTRIB1SVPROC									glVertexAttrib1sv;
	extern PFNGLVERTEXATTRIB2DPROC									glVertexAttrib2d;
	extern PFNGLVERTEXATTRIB2DVPROC									glVertexAttrib2dv;
	extern PFNGLVERTEXATTRIB2FPROC									glVertexAttrib2f;
	extern PFNGLVERTEXATTRIB2FVPROC									glVertexAttrib2fv;
	extern PFNGLVERTEXATTRIB2SPROC									glVertexAttrib2s;
	extern PFNGLVERTEXATTRIB2SVPROC									glVertexAttrib2sv;
	extern PFNGLVERTEXATTRIB3DPROC									glVertexAttrib3d;
	extern PFNGLVERTEXATTRIB3DVPROC									glVertexAttrib3dv;
	extern PFNGLVERTEXATTRIB3FPROC									glVertexAttrib3f;
	extern PFNGLVERTEXATTRIB3FVPROC									glVertexAttrib3fv;
	extern PFNGLVERTEXATTRIB3SPROC									glVertexAttrib3s;
	extern PFNGLVERTEXATTRIB3SVPROC									glVertexAttrib3sv;
	extern PFNGLVERTEXATTRIB4NBVPROC								glVertexAttrib4Nbv;
	extern PFNGLVERTEXATTRIB4NIVPROC								glVertexAttrib4Niv;
	extern PFNGLVERTEXATTRIB4NSVPROC								glVertexAttrib4Nsv;
	extern PFNGLVERTEXATTRIB4NUBPROC								glVertexAttrib4Nub;
	extern PFNGLVERTEXATTRIB4NUBVPROC								glVertexAttrib4Nubv;
	extern PFNGLVERTEXATTRIB4NUIVPROC								glVertexAttrib4Nuiv;
	extern PFNGLVERTEXATTRIB4NUSVPROC								glVertexAttrib4Nusv;
	extern PFNGLVERTEXATTRIB4BVPROC									glVertexAttrib4bv;
	extern PFNGLVERTEXATTRIB4DPROC									glVertexAttrib4d;
	extern PFNGLVERTEXATTRIB4DVPROC									glVertexAttrib4dv;
	extern PFNGLVERTEXATTRIB4FPROC									glVertexAttrib4f;
	extern PFNGLVERTEXATTRIB4FVPROC									glVertexAttrib4fv;
	extern PFNGLVERTEXATTRIB4IVPROC									glVertexAttrib4iv;
	extern PFNGLVERTEXATTRIB4SPROC									glVertexAttrib4s;
	extern PFNGLVERTEXATTRIB4SVPROC									glVertexAttrib4sv;
	extern PFNGLVERTEXATTRIB4UBVPROC								glVertexAttrib4ubv;
	extern PFNGLVERTEXATTRIB4UIVPROC								glVertexAttrib4uiv;
	extern PFNGLVERTEXATTRIB4USVPROC								glVertexAttrib4usv;
	extern PFNGLVERTEXATTRIBPOINTERPROC								glVertexAttribPointer;
	// 2.1
	extern PFNGLUNIFORMMATRIX2X3FVPROC								glUniformMatrix2x3fv;
	extern PFNGLUNIFORMMATRIX3X2FVPROC								glUniformMatrix3x2fv;
	extern PFNGLUNIFORMMATRIX2X4FVPROC								glUniformMatrix2x4fv;
	extern PFNGLUNIFORMMATRIX4X2FVPROC								glUniformMatrix4x2fv;
	extern PFNGLUNIFORMMATRIX3X4FVPROC								glUniformMatrix3x4fv;
	extern PFNGLUNIFORMMATRIX4X3FVPROC								glUniformMatrix4x3fv;
	// 3.0
	extern PFNGLCOLORMASKIPROC										glColorMaski;
	extern PFNGLGETBOOLEANI_VPROC									glGetBooleani_v;
	extern PFNGLGETINTEGERI_VPROC									glGetIntegeri_v;
	extern PFNGLENABLEIPROC											glEnablei;
	extern PFNGLDISABLEIPROC										glDisablei;
	extern PFNGLISENABLEDIPROC										glIsEnabledi;
	extern PFNGLBEGINTRANSFORMFEEDBACKPROC							glBeginTransformFeedback;
	extern PFNGLENDTRANSFORMFEEDBACKPROC							glEndTransformFeedback;
	extern PFNGLBINDBUFFERRANGEPROC									glBindBufferRange;
	extern PFNGLBINDBUFFERBASEPROC									glBindBufferBase;
	extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC						glTransformFeedbackVaryings;
	extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC						glGetTransformFeedbackVarying;
	extern PFNGLCLAMPCOLORPROC										glClampColor;
	extern PFNGLBEGINCONDITIONALRENDERPROC							glBeginConditionalRender;
	extern PFNGLENDCONDITIONALRENDERPROC							glEndConditionalRender;
	extern PFNGLVERTEXATTRIBIPOINTERPROC							glVertexAttribIPointer;
	extern PFNGLGETVERTEXATTRIBIIVPROC								glGetVertexAttribIiv;
	extern PFNGLGETVERTEXATTRIBIUIVPROC								glGetVertexAttribIuiv;
	extern PFNGLVERTEXATTRIBI1IPROC									glVertexAttribI1i;
	extern PFNGLVERTEXATTRIBI2IPROC									glVertexAttribI2i;
	extern PFNGLVERTEXATTRIBI3IPROC									glVertexAttribI3i;
	extern PFNGLVERTEXATTRIBI4IPROC									glVertexAttribI4i;
	extern PFNGLVERTEXATTRIBI1UIPROC								glVertexAttribI1ui;
	extern PFNGLVERTEXATTRIBI2UIPROC								glVertexAttribI2ui;
	extern PFNGLVERTEXATTRIBI3UIPROC								glVertexAttribI3ui;
	extern PFNGLVERTEXATTRIBI4UIPROC								glVertexAttribI4ui;
	extern PFNGLVERTEXATTRIBI1IVPROC								glVertexAttribI1iv;
	extern PFNGLVERTEXATTRIBI2IVPROC								glVertexAttribI2iv;
	extern PFNGLVERTEXATTRIBI3IVPROC								glVertexAttribI3iv;
	extern PFNGLVERTEXATTRIBI4IVPROC								glVertexAttribI4iv;
	extern PFNGLVERTEXATTRIBI1UIVPROC								glVertexAttribI1uiv;
	extern PFNGLVERTEXATTRIBI2UIVPROC								glVertexAttribI2uiv;
	extern PFNGLVERTEXATTRIBI3UIVPROC								glVertexAttribI3uiv;
	extern PFNGLVERTEXATTRIBI4UIVPROC								glVertexAttribI4uiv;
	extern PFNGLVERTEXATTRIBI4BVPROC								glVertexAttribI4bv;
	extern PFNGLVERTEXATTRIBI4SVPROC								glVertexAttribI4sv;
	extern PFNGLVERTEXATTRIBI4UBVPROC								glVertexAttribI4ubv;
	extern PFNGLVERTEXATTRIBI4USVPROC								glVertexAttribI4usv;
	extern PFNGLGETUNIFORMUIVPROC									glGetUniformuiv;
	extern PFNGLBINDFRAGDATALOCATIONPROC							glBindFragDataLocation;
	extern PFNGLGETFRAGDATALOCATIONPROC								glGetFragDataLocation;
	extern PFNGLUNIFORM1UIPROC										glUniform1ui;
	extern PFNGLUNIFORM2UIPROC										glUniform2ui;
	extern PFNGLUNIFORM3UIPROC										glUniform3ui;
	extern PFNGLUNIFORM4UIPROC										glUniform4ui;
	extern PFNGLUNIFORM1UIVPROC										glUniform1uiv;
	extern PFNGLUNIFORM2UIVPROC										glUniform2uiv;
	extern PFNGLUNIFORM3UIVPROC										glUniform3uiv;
	extern PFNGLUNIFORM4UIVPROC										glUniform4uiv;
	extern PFNGLTEXPARAMETERIIVPROC									glTexParameterIiv;
	extern PFNGLTEXPARAMETERIUIVPROC								glTexParameterIuiv;
	extern PFNGLGETTEXPARAMETERIIVPROC								glGetTexParameterIiv;
	extern PFNGLGETTEXPARAMETERIUIVPROC								glGetTexParameterIuiv;
	extern PFNGLCLEARBUFFERIVPROC									glClearBufferiv;
	extern PFNGLCLEARBUFFERUIVPROC									glClearBufferuiv;
	extern PFNGLCLEARBUFFERFVPROC									glClearBufferfv;
	extern PFNGLCLEARBUFFERFIPROC									glClearBufferfi;
	extern PFNGLGETSTRINGIPROC										glGetStringi;
	extern PFNGLISRENDERBUFFERPROC									glIsRenderbuffer;
	extern PFNGLBINDRENDERBUFFERPROC								glBindRenderbuffer;
	extern PFNGLDELETERENDERBUFFERSPROC								glDeleteRenderbuffers;
	extern PFNGLGENRENDERBUFFERSPROC								glGenRenderbuffers;
	extern PFNGLRENDERBUFFERSTORAGEPROC								glRenderbufferStorage;
	extern PFNGLGETRENDERBUFFERPARAMETERIVPROC						glGetRenderbufferParameteriv;
	extern PFNGLISFRAMEBUFFERPROC									glIsFramebuffer;
	extern PFNGLBINDFRAMEBUFFERPROC									glBindFramebuffer;
	extern PFNGLDELETEFRAMEBUFFERSPROC								glDeleteFramebuffers;
	extern PFNGLGENFRAMEBUFFERSPROC									glGenFramebuffers;
	extern PFNGLCHECKFRAMEBUFFERSTATUSPROC							glCheckFramebufferStatus;
	extern PFNGLFRAMEBUFFERTEXTURE1DPROC							glFramebufferTexture1D;
	extern PFNGLFRAMEBUFFERTEXTURE2DPROC							glFramebufferTexture2D;
	extern PFNGLFRAMEBUFFERTEXTURE3DPROC							glFramebufferTexture3D;
	extern PFNGLFRAMEBUFFERRENDERBUFFERPROC							glFramebufferRenderbuffer;
	extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC				glGetFramebufferAttachmentParameteriv;
	extern PFNGLGENERATEMIPMAPPROC									glGenerateMipmap;
	extern PFNGLBLITFRAMEBUFFERPROC									glBlitFramebuffer;
	extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC					glRenderbufferStorageMultisample;
	extern PFNGLFRAMEBUFFERTEXTURELAYERPROC							glFramebufferTextureLayer;
	extern PFNGLMAPBUFFERRANGEPROC									glMapBufferRange;
	extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC							glFlushMappedBufferRange;
	extern PFNGLBINDVERTEXARRAYPROC									glBindVertexArray;
	extern PFNGLDELETEVERTEXARRAYSPROC								glDeleteVertexArrays;
	extern PFNGLGENVERTEXARRAYSPROC									glGenVertexArrays;
	extern PFNGLISVERTEXARRAYPROC									glIsVertexArray;
	// 3.1
	extern PFNGLDRAWARRAYSINSTANCEDPROC								glDrawArraysInstanced;
	extern PFNGLDRAWELEMENTSINSTANCEDPROC							glDrawElementsInstanced;
	extern PFNGLTEXBUFFERPROC										glTexBuffer;
	extern PFNGLPRIMITIVERESTARTINDEXPROC							glPrimitiveRestartIndex;
	extern PFNGLCOPYBUFFERSUBDATAPROC								glCopyBufferSubData;
	extern PFNGLGETUNIFORMINDICESPROC								glGetUniformIndices;
	extern PFNGLGETACTIVEUNIFORMSIVPROC								glGetActiveUniformsiv;
	extern PFNGLGETACTIVEUNIFORMNAMEPROC							glGetActiveUniformName;
	extern PFNGLGETUNIFORMBLOCKINDEXPROC							glGetUniformBlockIndex;
	extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC							glGetActiveUniformBlockiv;
	extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC						glGetActiveUniformBlockName;
	extern PFNGLUNIFORMBLOCKBINDINGPROC								glUniformBlockBinding;
	// 3.2
	extern PFNGLDRAWELEMENTSBASEVERTEXPROC							glDrawElementsBaseVertex;
	extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC						glDrawRangeElementsBaseVertex;
	extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC					glDrawElementsInstancedBaseVertex;
	extern PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC						glMultiDrawElementsBaseVertex;
	extern PFNGLPROVOKINGVERTEXPROC									glProvokingVertex;
	extern PFNGLFENCESYNCPROC										glFenceSync;
	extern PFNGLISSYNCPROC											glIsSync;
	extern PFNGLDELETESYNCPROC										glDeleteSync;
	extern PFNGLCLIENTWAITSYNCPROC									glClientWaitSync;
	extern PFNGLWAITSYNCPROC										glWaitSync;
	extern PFNGLGETINTEGER64VPROC									glGetInteger64v;
	extern PFNGLGETSYNCIVPROC										glGetSynciv;
	extern PFNGLGETINTEGER64I_VPROC									glGetInteger64i_v;
	extern PFNGLGETBUFFERPARAMETERI64VPROC							glGetBufferParameteri64v;
	extern PFNGLFRAMEBUFFERTEXTUREPROC								glFramebufferTexture;
	extern PFNGLTEXIMAGE2DMULTISAMPLEPROC							glTexImage2DMultisample;
	extern PFNGLTEXIMAGE3DMULTISAMPLEPROC							glTexImage3DMultisample;
	extern PFNGLGETMULTISAMPLEFVPROC								glGetMultisamplefv;
	extern PFNGLSAMPLEMASKIPROC										glSampleMaski;
	// 3.3
	extern PFNGLBINDFRAGDATALOCATIONINDEXEDPROC						glBindFragDataLocationIndexed;
	extern PFNGLGETFRAGDATAINDEXPROC								glGetFragDataIndex;
	extern PFNGLGENSAMPLERSPROC										glGenSamplers;
	extern PFNGLDELETESAMPLERSPROC									glDeleteSamplers;
	extern PFNGLISSAMPLERPROC										glIsSampler;
	extern PFNGLBINDSAMPLERPROC										glBindSampler;
	extern PFNGLSAMPLERPARAMETERIPROC								glSamplerParameteri;
	extern PFNGLSAMPLERPARAMETERIVPROC								glSamplerParameteriv;
	extern PFNGLSAMPLERPARAMETERFPROC								glSamplerParameterf;
	extern PFNGLSAMPLERPARAMETERFVPROC								glSamplerParameterfv;
	extern PFNGLSAMPLERPARAMETERIIVPROC								glSamplerParameterIiv;
	extern PFNGLSAMPLERPARAMETERIUIVPROC							glSamplerParameterIuiv;
	extern PFNGLGETSAMPLERPARAMETERIVPROC							glGetSamplerParameteriv;
	extern PFNGLGETSAMPLERPARAMETERIIVPROC							glGetSamplerParameterIiv;
	extern PFNGLGETSAMPLERPARAMETERFVPROC							glGetSamplerParameterfv;
	extern PFNGLGETSAMPLERPARAMETERIUIVPROC							glGetSamplerParameterIuiv;
	extern PFNGLQUERYCOUNTERPROC									glQueryCounter;
	extern PFNGLGETQUERYOBJECTI64VPROC								glGetQueryObjecti64v;
	extern PFNGLGETQUERYOBJECTUI64VPROC								glGetQueryObjectui64v;
	extern PFNGLVERTEXATTRIBDIVISORPROC								glVertexAttribDivisor;
	extern PFNGLVERTEXATTRIBP1UIPROC								glVertexAttribP1ui;
	extern PFNGLVERTEXATTRIBP1UIVPROC								glVertexAttribP1uiv;
	extern PFNGLVERTEXATTRIBP2UIPROC								glVertexAttribP2ui;
	extern PFNGLVERTEXATTRIBP2UIVPROC								glVertexAttribP2uiv;
	extern PFNGLVERTEXATTRIBP3UIPROC								glVertexAttribP3ui;
	extern PFNGLVERTEXATTRIBP3UIVPROC								glVertexAttribP3uiv;
	extern PFNGLVERTEXATTRIBP4UIPROC								glVertexAttribP4ui;
	extern PFNGLVERTEXATTRIBP4UIVPROC								glVertexAttribP4uiv;
	// 4.0
	extern PFNGLMINSAMPLESHADINGPROC								glMinSampleShading;
	extern PFNGLBLENDEQUATIONIPROC									glBlendEquationi;
	extern PFNGLBLENDEQUATIONSEPARATEIPROC							glBlendEquationSeparatei;
	extern PFNGLBLENDFUNCIPROC										glBlendFunci;
	extern PFNGLBLENDFUNCSEPARATEIPROC								glBlendFuncSeparatei;
	extern PFNGLDRAWARRAYSINDIRECTPROC								glDrawArraysIndirect;
	extern PFNGLDRAWELEMENTSINDIRECTPROC							glDrawElementsIndirect;
	extern PFNGLUNIFORM1DPROC										glUniform1d;
	extern PFNGLUNIFORM2DPROC										glUniform2d;
	extern PFNGLUNIFORM3DPROC										glUniform3d;
	extern PFNGLUNIFORM4DPROC										glUniform4d;
	extern PFNGLUNIFORM1DVPROC										glUniform1dv;
	extern PFNGLUNIFORM2DVPROC										glUniform2dv;
	extern PFNGLUNIFORM3DVPROC										glUniform3dv;
	extern PFNGLUNIFORM4DVPROC										glUniform4dv;
	extern PFNGLUNIFORMMATRIX2DVPROC								glUniformMatrix2dv;
	extern PFNGLUNIFORMMATRIX3DVPROC								glUniformMatrix3dv;
	extern PFNGLUNIFORMMATRIX4DVPROC								glUniformMatrix4dv;
	extern PFNGLUNIFORMMATRIX2X3DVPROC								glUniformMatrix2x3dv;
	extern PFNGLUNIFORMMATRIX2X4DVPROC								glUniformMatrix2x4dv;
	extern PFNGLUNIFORMMATRIX3X2DVPROC								glUniformMatrix3x2dv;
	extern PFNGLUNIFORMMATRIX3X4DVPROC								glUniformMatrix3x4dv;
	extern PFNGLUNIFORMMATRIX4X2DVPROC								glUniformMatrix4x2dv;
	extern PFNGLUNIFORMMATRIX4X3DVPROC								glUniformMatrix4x3dv;
	extern PFNGLGETUNIFORMDVPROC									glGetUniformdv;
	extern PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC					glGetSubroutineUniformLocation;
	extern PFNGLGETSUBROUTINEINDEXPROC								glGetSubroutineIndex;
	extern PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC					glGetActiveSubroutineUniformiv;
	extern PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC					glGetActiveSubroutineUniformName;
	extern PFNGLGETACTIVESUBROUTINENAMEPROC							glGetActiveSubroutineName;
	extern PFNGLUNIFORMSUBROUTINESUIVPROC							glUniformSubroutinesuiv;
	extern PFNGLGETUNIFORMSUBROUTINEUIVPROC							glGetUniformSubroutineuiv;
	extern PFNGLGETPROGRAMSTAGEIVPROC								glGetProgramStageiv;
	extern PFNGLPATCHPARAMETERIPROC									glPatchParameteri;
	extern PFNGLPATCHPARAMETERFVPROC								glPatchParameterfv;
	extern PFNGLBINDTRANSFORMFEEDBACKPROC							glBindTransformFeedback;
	extern PFNGLDELETETRANSFORMFEEDBACKSPROC						glDeleteTransformFeedbacks;
	extern PFNGLGENTRANSFORMFEEDBACKSPROC							glGenTransformFeedbacks;
	extern PFNGLISTRANSFORMFEEDBACKPROC								glIsTransformFeedback;
	extern PFNGLPAUSETRANSFORMFEEDBACKPROC							glPauseTransformFeedback;
	extern PFNGLRESUMETRANSFORMFEEDBACKPROC							glResumeTransformFeedback;
	extern PFNGLDRAWTRANSFORMFEEDBACKPROC							glDrawTransformFeedback;
	extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC						glDrawTransformFeedbackStream;
	extern PFNGLBEGINQUERYINDEXEDPROC								glBeginQueryIndexed;
	extern PFNGLENDQUERYINDEXEDPROC									glEndQueryIndexed;
	extern PFNGLGETQUERYINDEXEDIVPROC								glGetQueryIndexediv;
	// 4.1
	extern PFNGLRELEASESHADERCOMPILERPROC							glReleaseShaderCompiler;
	extern PFNGLSHADERBINARYPROC									glShaderBinary;
	extern PFNGLGETSHADERPRECISIONFORMATPROC						glGetShaderPrecisionFormat;
	extern PFNGLDEPTHRANGEFPROC										glDepthRangef;
	extern PFNGLCLEARDEPTHFPROC										glClearDepthf;
	extern PFNGLGETPROGRAMBINARYPROC								glGetProgramBinary;
	extern PFNGLPROGRAMBINARYPROC									glProgramBinary;
	extern PFNGLPROGRAMPARAMETERIPROC								glProgramParameteri;
	extern PFNGLUSEPROGRAMSTAGESPROC								glUseProgramStages;
	extern PFNGLACTIVESHADERPROGRAMPROC								glActiveShaderProgram;
	extern PFNGLCREATESHADERPROGRAMVPROC							glCreateShaderProgramv;
	extern PFNGLBINDPROGRAMPIPELINEPROC								glBindProgramPipeline;
	extern PFNGLDELETEPROGRAMPIPELINESPROC							glDeleteProgramPipelines;
	extern PFNGLGENPROGRAMPIPELINESPROC								glGenProgramPipelines;
	extern PFNGLISPROGRAMPIPELINEPROC								glIsProgramPipeline;
	extern PFNGLGETPROGRAMPIPELINEIVPROC							glGetProgramPipelineiv;
	extern PFNGLPROGRAMUNIFORM1IPROC								glProgramUniform1i;
	extern PFNGLPROGRAMUNIFORM1IVPROC								glProgramUniform1iv;
	extern PFNGLPROGRAMUNIFORM1FPROC								glProgramUniform1f;
	extern PFNGLPROGRAMUNIFORM1FVPROC								glProgramUniform1fv;
	extern PFNGLPROGRAMUNIFORM1DPROC								glProgramUniform1d;
	extern PFNGLPROGRAMUNIFORM1DVPROC								glProgramUniform1dv;
	extern PFNGLPROGRAMUNIFORM1UIPROC								glProgramUniform1ui;
	extern PFNGLPROGRAMUNIFORM1UIVPROC								glProgramUniform1uiv;
	extern PFNGLPROGRAMUNIFORM2IPROC								glProgramUniform2i;
	extern PFNGLPROGRAMUNIFORM2IVPROC								glProgramUniform2iv;
	extern PFNGLPROGRAMUNIFORM2FPROC								glProgramUniform2f;
	extern PFNGLPROGRAMUNIFORM2FVPROC								glProgramUniform2fv;
	extern PFNGLPROGRAMUNIFORM2DPROC								glProgramUniform2d;
	extern PFNGLPROGRAMUNIFORM2DVPROC								glProgramUniform2dv;
	extern PFNGLPROGRAMUNIFORM2UIPROC								glProgramUniform2ui;
	extern PFNGLPROGRAMUNIFORM2UIVPROC								glProgramUniform2uiv;
	extern PFNGLPROGRAMUNIFORM3IPROC								glProgramUniform3i;
	extern PFNGLPROGRAMUNIFORM3IVPROC								glProgramUniform3iv;
	extern PFNGLPROGRAMUNIFORM3FPROC								glProgramUniform3f;
	extern PFNGLPROGRAMUNIFORM3FVPROC								glProgramUniform3fv;
	extern PFNGLPROGRAMUNIFORM3DPROC								glProgramUniform3d;
	extern PFNGLPROGRAMUNIFORM3DVPROC								glProgramUniform3dv;
	extern PFNGLPROGRAMUNIFORM3UIPROC								glProgramUniform3ui;
	extern PFNGLPROGRAMUNIFORM3UIVPROC								glProgramUniform3uiv;
	extern PFNGLPROGRAMUNIFORM4IPROC								glProgramUniform4i;
	extern PFNGLPROGRAMUNIFORM4IVPROC								glProgramUniform4iv;
	extern PFNGLPROGRAMUNIFORM4FPROC								glProgramUniform4f;
	extern PFNGLPROGRAMUNIFORM4FVPROC								glProgramUniform4fv;
	extern PFNGLPROGRAMUNIFORM4DPROC								glProgramUniform4d;
	extern PFNGLPROGRAMUNIFORM4DVPROC								glProgramUniform4dv;
	extern PFNGLPROGRAMUNIFORM4UIPROC								glProgramUniform4ui;
	extern PFNGLPROGRAMUNIFORM4UIVPROC								glProgramUniform4uiv;
	extern PFNGLPROGRAMUNIFORMMATRIX2FVPROC							glProgramUniformMatrix2fv;
	extern PFNGLPROGRAMUNIFORMMATRIX3FVPROC							glProgramUniformMatrix3fv;
	extern PFNGLPROGRAMUNIFORMMATRIX4FVPROC							glProgramUniformMatrix4fv;
	extern PFNGLPROGRAMUNIFORMMATRIX2DVPROC							glProgramUniformMatrix2dv;
	extern PFNGLPROGRAMUNIFORMMATRIX3DVPROC							glProgramUniformMatrix3dv;
	extern PFNGLPROGRAMUNIFORMMATRIX4DVPROC							glProgramUniformMatrix4dv;
	extern PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC						glProgramUniformMatrix2x3fv;
	extern PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC						glProgramUniformMatrix3x2fv;
	extern PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC						glProgramUniformMatrix2x4fv;
	extern PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC						glProgramUniformMatrix4x2fv;
	extern PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC						glProgramUniformMatrix3x4fv;
	extern PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC						glProgramUniformMatrix4x3fv;
	extern PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC						glProgramUniformMatrix2x3dv;
	extern PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC						glProgramUniformMatrix3x2dv;
	extern PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC						glProgramUniformMatrix2x4dv;
	extern PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC						glProgramUniformMatrix4x2dv;
	extern PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC						glProgramUniformMatrix3x4dv;
	extern PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC						glProgramUniformMatrix4x3dv;
	extern PFNGLVALIDATEPROGRAMPIPELINEPROC							glValidateProgramPipeline;
	extern PFNGLGETPROGRAMPIPELINEINFOLOGPROC						glGetProgramPipelineInfoLog;
	extern PFNGLVERTEXATTRIBL1DPROC									glVertexAttribL1d;
	extern PFNGLVERTEXATTRIBL2DPROC									glVertexAttribL2d;
	extern PFNGLVERTEXATTRIBL3DPROC									glVertexAttribL3d;
	extern PFNGLVERTEXATTRIBL4DPROC									glVertexAttribL4d;
	extern PFNGLVERTEXATTRIBL1DVPROC								glVertexAttribL1dv;
	extern PFNGLVERTEXATTRIBL2DVPROC								glVertexAttribL2dv;
	extern PFNGLVERTEXATTRIBL3DVPROC								glVertexAttribL3dv;
	extern PFNGLVERTEXATTRIBL4DVPROC								glVertexAttribL4dv;
	extern PFNGLVERTEXATTRIBLPOINTERPROC							glVertexAttribLPointer;
	extern PFNGLGETVERTEXATTRIBLDVPROC								glGetVertexAttribLdv;
	extern PFNGLVIEWPORTARRAYVPROC									glViewportArrayv;
	extern PFNGLVIEWPORTINDEXEDFPROC								glViewportIndexedf;
	extern PFNGLVIEWPORTINDEXEDFVPROC								glViewportIndexedfv;
	extern PFNGLSCISSORARRAYVPROC									glScissorArrayv;
	extern PFNGLSCISSORINDEXEDPROC									glScissorIndexed;
	extern PFNGLSCISSORINDEXEDVPROC									glScissorIndexedv;
	extern PFNGLDEPTHRANGEARRAYVPROC								glDepthRangeArrayv;
	extern PFNGLDEPTHRANGEINDEXEDPROC								glDepthRangeIndexed;
	extern PFNGLGETFLOATI_VPROC										glGetFloati_v;
	extern PFNGLGETDOUBLEI_VPROC									glGetDoublei_v;
	// 4.2
	extern PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC					glDrawArraysInstancedBaseInstance;
	extern PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC				glDrawElementsInstancedBaseInstance;
	extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC		glDrawElementsInstancedBaseVertexBaseInstance;
	extern PFNGLGETINTERNALFORMATIVPROC								glGetInternalformativ;
	extern PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC					glGetActiveAtomicCounterBufferiv;
	extern PFNGLBINDIMAGETEXTUREPROC								glBindImageTexture;
	extern PFNGLMEMORYBARRIERPROC									glMemoryBarrier;
	extern PFNGLTEXSTORAGE1DPROC									glTexStorage1D;
	extern PFNGLTEXSTORAGE2DPROC									glTexStorage2D;
	extern PFNGLTEXSTORAGE3DPROC									glTexStorage3D;
	extern PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC					glDrawTransformFeedbackInstanced;
	extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC			glDrawTransformFeedbackStreamInstanced;
	// 4.3
	extern PFNGLCLEARBUFFERDATAPROC									glClearBufferData;
	extern PFNGLCLEARBUFFERSUBDATAPROC								glClearBufferSubData;
	extern PFNGLDISPATCHCOMPUTEPROC									glDispatchCompute;
	extern PFNGLDISPATCHCOMPUTEINDIRECTPROC							glDispatchComputeIndirect;
	extern PFNGLCOPYIMAGESUBDATAPROC								glCopyImageSubData;
	extern PFNGLFRAMEBUFFERPARAMETERIPROC							glFramebufferParameteri;
	extern PFNGLGETFRAMEBUFFERPARAMETERIVPROC						glGetFramebufferParameteriv;
	extern PFNGLGETINTERNALFORMATI64VPROC							glGetInternalformati64v;
	extern PFNGLINVALIDATETEXSUBIMAGEPROC							glInvalidateTexSubImage;
	extern PFNGLINVALIDATETEXIMAGEPROC								glInvalidateTexImage;
	extern PFNGLINVALIDATEBUFFERSUBDATAPROC							glInvalidateBufferSubData;
	extern PFNGLINVALIDATEBUFFERDATAPROC							glInvalidateBufferData;
	extern PFNGLINVALIDATEFRAMEBUFFERPROC							glInvalidateFramebuffer;
	extern PFNGLINVALIDATESUBFRAMEBUFFERPROC						glInvalidateSubFramebuffer;
	extern PFNGLMULTIDRAWARRAYSINDIRECTPROC							glMultiDrawArraysIndirect;
	extern PFNGLMULTIDRAWELEMENTSINDIRECTPROC						glMultiDrawElementsIndirect;
	extern PFNGLGETPROGRAMINTERFACEIVPROC							glGetProgramInterfaceiv;
	extern PFNGLGETPROGRAMRESOURCEINDEXPROC							glGetProgramResourceIndex;
	extern PFNGLGETPROGRAMRESOURCENAMEPROC							glGetProgramResourceName;
	extern PFNGLGETPROGRAMRESOURCEIVPROC							glGetProgramResourceiv;
	extern PFNGLGETPROGRAMRESOURCELOCATIONPROC						glGetProgramResourceLocation;
	extern PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC					glGetProgramResourceLocationIndex;
	extern PFNGLSHADERSTORAGEBLOCKBINDINGPROC						glShaderStorageBlockBinding;
	extern PFNGLTEXBUFFERRANGEPROC									glTexBufferRange;
	extern PFNGLTEXSTORAGE2DMULTISAMPLEPROC							glTexStorage2DMultisample;
	extern PFNGLTEXSTORAGE3DMULTISAMPLEPROC							glTexStorage3DMultisample;
	extern PFNGLTEXTUREVIEWPROC										glTextureView;
	extern PFNGLBINDVERTEXBUFFERPROC								glBindVertexBuffer;
	extern PFNGLVERTEXATTRIBFORMATPROC								glVertexAttribFormat;
	extern PFNGLVERTEXATTRIBIFORMATPROC								glVertexAttribIFormat;
	extern PFNGLVERTEXATTRIBLFORMATPROC								glVertexAttribLFormat;
	extern PFNGLVERTEXATTRIBBINDINGPROC								glVertexAttribBinding;
	extern PFNGLVERTEXBINDINGDIVISORPROC							glVertexBindingDivisor;
	extern PFNGLDEBUGMESSAGECONTROLPROC								glDebugMessageControl;
	extern PFNGLDEBUGMESSAGEINSERTPROC								glDebugMessageInsert;
	extern PFNGLDEBUGMESSAGECALLBACKPROC							glDebugMessageCallback;
	extern PFNGLGETDEBUGMESSAGELOGPROC								glGetDebugMessageLog;
	extern PFNGLPUSHDEBUGGROUPPROC									glPushDebugGroup;
	extern PFNGLPOPDEBUGGROUPPROC									glPopDebugGroup;
	extern PFNGLOBJECTLABELPROC										glObjectLabel;
	extern PFNGLGETOBJECTLABELPROC									glGetObjectLabel;
	extern PFNGLOBJECTPTRLABELPROC									glObjectPtrLabel;
	extern PFNGLGETOBJECTPTRLABELPROC								glGetObjectPtrLabel;
	// 4.4
	extern PFNGLBUFFERSTORAGEPROC									glBufferStorage;
	extern PFNGLCLEARTEXIMAGEPROC									glClearTexImage;
	extern PFNGLCLEARTEXSUBIMAGEPROC								glClearTexSubImage;
	extern PFNGLBINDBUFFERSBASEPROC									glBindBuffersBase;
	extern PFNGLBINDBUFFERSRANGEPROC								glBindBuffersRange;
	extern PFNGLBINDTEXTURESPROC									glBindTextures;
	extern PFNGLBINDSAMPLERSPROC									glBindSamplers;
	extern PFNGLBINDIMAGETEXTURESPROC								glBindImageTextures;
	extern PFNGLBINDVERTEXBUFFERSPROC								glBindVertexBuffers;
	// 4.5
	extern PFNGLCLIPCONTROLPROC										glClipControl;
	extern PFNGLCREATETRANSFORMFEEDBACKSPROC						glCreateTransformFeedbacks;
	extern PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC						glTransformFeedbackBufferBase;
	extern PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC					glTransformFeedbackBufferRange;
	extern PFNGLGETTRANSFORMFEEDBACKIVPROC							glGetTransformFeedbackiv;
	extern PFNGLGETTRANSFORMFEEDBACKI_VPROC							glGetTransformFeedbacki_v;
	extern PFNGLGETTRANSFORMFEEDBACKI64_VPROC						glGetTransformFeedbacki64_v;
	extern PFNGLCREATEBUFFERSPROC									glCreateBuffers;
	extern PFNGLNAMEDBUFFERSTORAGEPROC								glNamedBufferStorage;
	extern PFNGLNAMEDBUFFERDATAPROC									glNamedBufferData;
	extern PFNGLNAMEDBUFFERSUBDATAPROC								glNamedBufferSubData;
	extern PFNGLCOPYNAMEDBUFFERSUBDATAPROC							glCopyNamedBufferSubData;
	extern PFNGLCLEARNAMEDBUFFERDATAPROC							glClearNamedBufferData;
	extern PFNGLCLEARNAMEDBUFFERSUBDATAPROC							glClearNamedBufferSubData;
	extern PFNGLMAPNAMEDBUFFERPROC									glMapNamedBuffer;
	extern PFNGLMAPNAMEDBUFFERRANGEPROC								glMapNamedBufferRange;
	extern PFNGLUNMAPNAMEDBUFFERPROC								glUnmapNamedBuffer;
	extern PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC						glFlushMappedNamedBufferRange;
	extern PFNGLGETNAMEDBUFFERPARAMETERIVPROC						glGetNamedBufferParameteriv;
	extern PFNGLGETNAMEDBUFFERPARAMETERI64VPROC						glGetNamedBufferParameteri64v;
	extern PFNGLGETNAMEDBUFFERPOINTERVPROC							glGetNamedBufferPointerv;
	extern PFNGLGETNAMEDBUFFERSUBDATAPROC							glGetNamedBufferSubData;
	extern PFNGLCREATEFRAMEBUFFERSPROC								glCreateFramebuffers;
	extern PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC					glNamedFramebufferRenderbuffer;
	extern PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC						glNamedFramebufferParameteri;
	extern PFNGLNAMEDFRAMEBUFFERTEXTUREPROC							glNamedFramebufferTexture;
	extern PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC					glNamedFramebufferTextureLayer;
	extern PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC						glNamedFramebufferDrawBuffer;
	extern PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC						glNamedFramebufferDrawBuffers;
	extern PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC						glNamedFramebufferReadBuffer;
	extern PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC					glInvalidateNamedFramebufferData;
	extern PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC				glInvalidateNamedFramebufferSubData;
	extern PFNGLCLEARNAMEDFRAMEBUFFERIVPROC							glClearNamedFramebufferiv;
	extern PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC						glClearNamedFramebufferuiv;
	extern PFNGLCLEARNAMEDFRAMEBUFFERFVPROC							glClearNamedFramebufferfv;
	extern PFNGLCLEARNAMEDFRAMEBUFFERFIPROC							glClearNamedFramebufferfi;
	extern PFNGLBLITNAMEDFRAMEBUFFERPROC							glBlitNamedFramebuffer;
	extern PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC						glCheckNamedFramebufferStatus;
	extern PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC					glGetNamedFramebufferParameteriv;
	extern PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC		glGetNamedFramebufferAttachmentParameteriv;
	extern PFNGLCREATERENDERBUFFERSPROC								glCreateRenderbuffers;
	extern PFNGLNAMEDRENDERBUFFERSTORAGEPROC						glNamedRenderbufferStorage;
	extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC				glNamedRenderbufferStorageMultisample;
	extern PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC					glGetNamedRenderbufferParameteriv;
	extern PFNGLCREATETEXTURESPROC									glCreateTextures;
	extern PFNGLTEXTUREBUFFERPROC									glTextureBuffer;
	extern PFNGLTEXTUREBUFFERRANGEPROC								glTextureBufferRange;
	extern PFNGLTEXTURESTORAGE1DPROC								glTextureStorage1D;
	extern PFNGLTEXTURESTORAGE2DPROC								glTextureStorage2D;
	extern PFNGLTEXTURESTORAGE3DPROC								glTextureStorage3D;
	extern PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC						glTextureStorage2DMultisample;
	extern PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC						glTextureStorage3DMultisample;
	extern PFNGLTEXTURESUBIMAGE1DPROC								glTextureSubImage1D;
	extern PFNGLTEXTURESUBIMAGE2DPROC								glTextureSubImage2D;
	extern PFNGLTEXTURESUBIMAGE3DPROC								glTextureSubImage3D;
	extern PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC						glCompressedTextureSubImage1D;
	extern PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC						glCompressedTextureSubImage2D;
	extern PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC						glCompressedTextureSubImage3D;
	extern PFNGLCOPYTEXTURESUBIMAGE1DPROC							glCopyTextureSubImage1D;
	extern PFNGLCOPYTEXTURESUBIMAGE2DPROC							glCopyTextureSubImage2D;
	extern PFNGLCOPYTEXTURESUBIMAGE3DPROC							glCopyTextureSubImage3D;
	extern PFNGLTEXTUREPARAMETERFPROC								glTextureParameterf;
	extern PFNGLTEXTUREPARAMETERFVPROC								glTextureParameterfv;
	extern PFNGLTEXTUREPARAMETERIPROC								glTextureParameteri;
	extern PFNGLTEXTUREPARAMETERIIVPROC								glTextureParameterIiv;
	extern PFNGLTEXTUREPARAMETERIUIVPROC							glTextureParameterIuiv;
	extern PFNGLTEXTUREPARAMETERIVPROC								glTextureParameteriv;
	extern PFNGLGENERATETEXTUREMIPMAPPROC							glGenerateTextureMipmap;
	extern PFNGLBINDTEXTUREUNITPROC									glBindTextureUnit;
	extern PFNGLGETTEXTUREIMAGEPROC									glGetTextureImage;
	extern PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC						glGetCompressedTextureImage;
	extern PFNGLGETTEXTURELEVELPARAMETERFVPROC						glGetTextureLevelParameterfv;
	extern PFNGLGETTEXTURELEVELPARAMETERIVPROC						glGetTextureLevelParameteriv;
	extern PFNGLGETTEXTUREPARAMETERFVPROC							glGetTextureParameterfv;
	extern PFNGLGETTEXTUREPARAMETERIIVPROC							glGetTextureParameterIiv;
	extern PFNGLGETTEXTUREPARAMETERIUIVPROC							glGetTextureParameterIuiv;
	extern PFNGLGETTEXTUREPARAMETERIVPROC							glGetTextureParameteriv;
	extern PFNGLCREATEVERTEXARRAYSPROC								glCreateVertexArrays;
	extern PFNGLDISABLEVERTEXARRAYATTRIBPROC						glDisableVertexArrayAttrib;
	extern PFNGLENABLEVERTEXARRAYATTRIBPROC							glEnableVertexArrayAttrib;
	extern PFNGLVERTEXARRAYELEMENTBUFFERPROC						glVertexArrayElementBuffer;
	extern PFNGLVERTEXARRAYVERTEXBUFFERPROC							glVertexArrayVertexBuffer;
	extern PFNGLVERTEXARRAYVERTEXBUFFERSPROC						glVertexArrayVertexBuffers;
	extern PFNGLVERTEXARRAYATTRIBBINDINGPROC						glVertexArrayAttribBinding;
	extern PFNGLVERTEXARRAYATTRIBFORMATPROC							glVertexArrayAttribFormat;
	extern PFNGLVERTEXARRAYATTRIBIFORMATPROC						glVertexArrayAttribIFormat;
	extern PFNGLVERTEXARRAYATTRIBLFORMATPROC						glVertexArrayAttribLFormat;
	extern PFNGLVERTEXARRAYBINDINGDIVISORPROC						glVertexArrayBindingDivisor;
	extern PFNGLGETVERTEXARRAYIVPROC								glGetVertexArrayiv;
	extern PFNGLGETVERTEXARRAYINDEXEDIVPROC							glGetVertexArrayIndexediv;
	extern PFNGLGETVERTEXARRAYINDEXED64IVPROC						glGetVertexArrayIndexed64iv;
	extern PFNGLCREATESAMPLERSPROC									glCreateSamplers;
	extern PFNGLCREATEPROGRAMPIPELINESPROC							glCreateProgramPipelines;
	extern PFNGLCREATEQUERIESPROC									glCreateQueries;
	extern PFNGLGETQUERYBUFFEROBJECTI64VPROC						glGetQueryBufferObjecti64v;
	extern PFNGLGETQUERYBUFFEROBJECTIVPROC							glGetQueryBufferObjectiv;
	extern PFNGLGETQUERYBUFFEROBJECTUI64VPROC						glGetQueryBufferObjectui64v;
	extern PFNGLGETQUERYBUFFEROBJECTUIVPROC							glGetQueryBufferObjectuiv;
	extern PFNGLMEMORYBARRIERBYREGIONPROC							glMemoryBarrierByRegion;
	extern PFNGLGETTEXTURESUBIMAGEPROC								glGetTextureSubImage;
	extern PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC					glGetCompressedTextureSubImage;
	extern PFNGLGETGRAPHICSRESETSTATUSPROC							glGetGraphicsResetStatus;
	extern PFNGLGETNCOMPRESSEDTEXIMAGEPROC							glGetnCompressedTexImage;
	extern PFNGLGETNTEXIMAGEPROC									glGetnTexImage;
	extern PFNGLGETNUNIFORMDVPROC									glGetnUniformdv;
	extern PFNGLGETNUNIFORMFVPROC									glGetnUniformfv;
	extern PFNGLGETNUNIFORMIVPROC									glGetnUniformiv;
	extern PFNGLGETNUNIFORMUIVPROC									glGetnUniformuiv;
	extern PFNGLREADNPIXELSPROC										glReadnPixels;
	extern PFNGLTEXTUREBARRIERPROC									glTextureBarrier;
	// 4.6
	extern PFNGLSPECIALIZESHADERPROC								glSpecializeShader;
	extern PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC					glMultiDrawArraysIndirectCount;
	extern PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC					glMultiDrawElementsIndirectCount;
	extern PFNGLPOLYGONOFFSETCLAMPPROC								glPolygonOffsetClamp;

	// GL_ARB_ES3_2_compatibility
	extern PFNGLPRIMITIVEBOUNDINGBOXARBPROC							glPrimitiveBoundingBoxARB;
	// GL_ARB_bindless_texture
	extern PFNGLGETTEXTUREHANDLEARBPROC								glGetTextureHandleARB;
	extern PFNGLGETTEXTURESAMPLERHANDLEARBPROC						glGetTextureSamplerHandleARB;
	extern PFNGLMAKETEXTUREHANDLERESIDENTARBPROC					glMakeTextureHandleResidentARB;
	extern PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC					glMakeTextureHandleNonResidentARB;
	extern PFNGLGETIMAGEHANDLEARBPROC								glGetImageHandleARB;
	extern PFNGLMAKEIMAGEHANDLERESIDENTARBPROC						glMakeImageHandleResidentARB;
	extern PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC					glMakeImageHandleNonResidentARB;
	extern PFNGLUNIFORMHANDLEUI64ARBPROC							glUniformHandleui64ARB;
	extern PFNGLUNIFORMHANDLEUI64VARBPROC							glUniformHandleui64vARB;
	extern PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC						glProgramUniformHandleui64ARB;
	extern PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC					glProgramUniformHandleui64vARB;
	extern PFNGLISTEXTUREHANDLERESIDENTARBPROC						glIsTextureHandleResidentARB;
	extern PFNGLISIMAGEHANDLERESIDENTARBPROC						glIsImageHandleResidentARB;
	extern PFNGLVERTEXATTRIBL1UI64ARBPROC							glVertexAttribL1ui64ARB;
	extern PFNGLVERTEXATTRIBL1UI64VARBPROC							glVertexAttribL1ui64vARB;
	extern PFNGLGETVERTEXATTRIBLUI64VARBPROC						glGetVertexAttribLui64vARB;
	// GL_ARB_cl_event
	extern PFNGLCREATESYNCFROMCLEVENTARBPROC						glCreateSyncFromCLeventARB;
	// GL_ARB_compute_variable_group_size
	extern PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC						glDispatchComputeGroupSizeARB;
	// GL_ARB_debug_output
	extern PFNGLDEBUGMESSAGECONTROLARBPROC							glDebugMessageControlARB;
	extern PFNGLDEBUGMESSAGEINSERTARBPROC							glDebugMessageInsertARB;
	extern PFNGLDEBUGMESSAGECALLBACKARBPROC							glDebugMessageCallbackARB;
	extern PFNGLGETDEBUGMESSAGELOGARBPROC							glGetDebugMessageLogARB;
	// GL_ARB_draw_buffers_blend
	extern PFNGLBLENDEQUATIONIARBPROC								glBlendEquationiARB;
	extern PFNGLBLENDEQUATIONSEPARATEIARBPROC						glBlendEquationSeparateiARB;
	extern PFNGLBLENDFUNCIARBPROC									glBlendFunciARB;
	extern PFNGLBLENDFUNCSEPARATEIARBPROC							glBlendFuncSeparateiARB;
	// GL_ARB_draw_instanced
	extern PFNGLDRAWARRAYSINSTANCEDARBPROC							glDrawArraysInstancedARB;
	extern PFNGLDRAWELEMENTSINSTANCEDARBPROC						glDrawElementsInstancedARB;
	// GL_ARB_geometry_shader4
	extern PFNGLPROGRAMPARAMETERIARBPROC							glProgramParameteriARB;
	extern PFNGLFRAMEBUFFERTEXTUREARBPROC							glFramebufferTextureARB;
	extern PFNGLFRAMEBUFFERTEXTURELAYERARBPROC						glFramebufferTextureLayerARB;
	extern PFNGLFRAMEBUFFERTEXTUREFACEARBPROC						glFramebufferTextureFaceARB;
	// GL_ARB_gl_spirv
	extern PFNGLSPECIALIZESHADERARBPROC								glSpecializeShaderARB;
	// GL_ARB_gpu_shader_int64
	extern PFNGLUNIFORM1I64ARBPROC									glUniform1i64ARB;
	extern PFNGLUNIFORM2I64ARBPROC									glUniform2i64ARB;
	extern PFNGLUNIFORM3I64ARBPROC									glUniform3i64ARB;
	extern PFNGLUNIFORM4I64ARBPROC									glUniform4i64ARB;
	extern PFNGLUNIFORM1I64VARBPROC									glUniform1i64vARB;
	extern PFNGLUNIFORM2I64VARBPROC									glUniform2i64vARB;
	extern PFNGLUNIFORM3I64VARBPROC									glUniform3i64vARB;
	extern PFNGLUNIFORM4I64VARBPROC									glUniform4i64vARB;
	extern PFNGLUNIFORM1UI64ARBPROC									glUniform1ui64ARB;
	extern PFNGLUNIFORM2UI64ARBPROC									glUniform2ui64ARB;
	extern PFNGLUNIFORM3UI64ARBPROC									glUniform3ui64ARB;
	extern PFNGLUNIFORM4UI64ARBPROC									glUniform4ui64ARB;
	extern PFNGLUNIFORM1UI64VARBPROC								glUniform1ui64vARB;
	extern PFNGLUNIFORM2UI64VARBPROC								glUniform2ui64vARB;
	extern PFNGLUNIFORM3UI64VARBPROC								glUniform3ui64vARB;
	extern PFNGLUNIFORM4UI64VARBPROC								glUniform4ui64vARB;
	extern PFNGLGETUNIFORMI64VARBPROC								glGetUniformi64vARB;
	extern PFNGLGETUNIFORMUI64VARBPROC								glGetUniformui64vARB;
	extern PFNGLGETNUNIFORMI64VARBPROC								glGetnUniformi64vARB;
	extern PFNGLGETNUNIFORMUI64VARBPROC								glGetnUniformui64vARB;
	extern PFNGLPROGRAMUNIFORM1I64ARBPROC							glProgramUniform1i64ARB;
	extern PFNGLPROGRAMUNIFORM2I64ARBPROC							glProgramUniform2i64ARB;
	extern PFNGLPROGRAMUNIFORM3I64ARBPROC							glProgramUniform3i64ARB;
	extern PFNGLPROGRAMUNIFORM4I64ARBPROC							glProgramUniform4i64ARB;
	extern PFNGLPROGRAMUNIFORM1I64VARBPROC							glProgramUniform1i64vARB;
	extern PFNGLPROGRAMUNIFORM2I64VARBPROC							glProgramUniform2i64vARB;
	extern PFNGLPROGRAMUNIFORM3I64VARBPROC							glProgramUniform3i64vARB;
	extern PFNGLPROGRAMUNIFORM4I64VARBPROC							glProgramUniform4i64vARB;
	extern PFNGLPROGRAMUNIFORM1UI64ARBPROC							glProgramUniform1ui64ARB;
	extern PFNGLPROGRAMUNIFORM2UI64ARBPROC							glProgramUniform2ui64ARB;
	extern PFNGLPROGRAMUNIFORM3UI64ARBPROC							glProgramUniform3ui64ARB;
	extern PFNGLPROGRAMUNIFORM4UI64ARBPROC							glProgramUniform4ui64ARB;
	extern PFNGLPROGRAMUNIFORM1UI64VARBPROC							glProgramUniform1ui64vARB;
	extern PFNGLPROGRAMUNIFORM2UI64VARBPROC							glProgramUniform2ui64vARB;
	extern PFNGLPROGRAMUNIFORM3UI64VARBPROC							glProgramUniform3ui64vARB;
	extern PFNGLPROGRAMUNIFORM4UI64VARBPROC							glProgramUniform4ui64vARB;
	// GL_ARB_indirect_parameters
	extern PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC					glMultiDrawArraysIndirectCountARB;
	extern PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC				glMultiDrawElementsIndirectCountARB;
	// GL_ARB_instanced_arrays
	extern PFNGLVERTEXATTRIBDIVISORARBPROC							glVertexAttribDivisorARB;
	// GL_ARB_parallel_shader_compile
	extern PFNGLMAXSHADERCOMPILERTHREADSARBPROC						glMaxShaderCompilerThreadsARB;
	// GL_ARB_robustness
	extern PFNGLGETGRAPHICSRESETSTATUSARBPROC						glGetGraphicsResetStatusARB;
	extern PFNGLGETNTEXIMAGEARBPROC									glGetnTexImageARB;
	extern PFNGLREADNPIXELSARBPROC									glReadnPixelsARB;
	extern PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC						glGetnCompressedTexImageARB;
	extern PFNGLGETNUNIFORMFVARBPROC								glGetnUniformfvARB;
	extern PFNGLGETNUNIFORMIVARBPROC								glGetnUniformivARB;
	extern PFNGLGETNUNIFORMUIVARBPROC								glGetnUniformuivARB;
	extern PFNGLGETNUNIFORMDVARBPROC								glGetnUniformdvARB;
	// GL_ARB_sample_locations
	extern PFNGLFRAMEBUFFERSAMPLELOCATIONSFVARBPROC					glFramebufferSampleLocationsfvARB;
	extern PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVARBPROC			glNamedFramebufferSampleLocationsfvARB;
	extern PFNGLEVALUATEDEPTHVALUESARBPROC							glEvaluateDepthValuesARB;
	// GL_ARB_sample_shading
	extern PFNGLMINSAMPLESHADINGARBPROC								glMinSampleShadingARB;
	// GL_ARB_shading_language_include
	extern PFNGLNAMEDSTRINGARBPROC									glNamedStringARB;
	extern PFNGLDELETENAMEDSTRINGARBPROC							glDeleteNamedStringARB;
	extern PFNGLCOMPILESHADERINCLUDEARBPROC							glCompileShaderIncludeARB;
	extern PFNGLISNAMEDSTRINGARBPROC								glIsNamedStringARB;
	extern PFNGLGETNAMEDSTRINGARBPROC								glGetNamedStringARB;
	extern PFNGLGETNAMEDSTRINGIVARBPROC								glGetNamedStringivARB;
	// GL_ARB_sparse_buffer
	extern PFNGLBUFFERPAGECOMMITMENTARBPROC							glBufferPageCommitmentARB;
	extern PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC					glNamedBufferPageCommitmentEXT;
	extern PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC					glNamedBufferPageCommitmentARB;
	// GL_ARB_sparse_texture
	extern PFNGLTEXPAGECOMMITMENTARBPROC							glTexPageCommitmentARB;
	// GL_ARB_texture_buffer_object
	extern PFNGLTEXBUFFERARBPROC									glTexBufferARB;
	// GL_ARB_viewport_array
	extern PFNGLDEPTHRANGEARRAYDVNVPROC								glDepthRangeArraydvNV;
	extern PFNGLDEPTHRANGEINDEXEDDNVPROC							glDepthRangeIndexeddNV;
	// GL_KHR_blend_equation_advanced
	extern PFNGLBLENDBARRIERKHRPROC									glBlendBarrierKHR;
	// GL_KHR_parallel_shader_compile
	extern PFNGLMAXSHADERCOMPILERTHREADSKHRPROC						glMaxShaderCompilerThreadsKHR;
	// GL_AMD_framebuffer_multisample_advanced
	extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC		glRenderbufferStorageMultisampleAdvancedAMD;
	extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC	glNamedRenderbufferStorageMultisampleAdvancedAMD;
	// GL_AMD_performance_monitor
	extern PFNGLGETPERFMONITORGROUPSAMDPROC							glGetPerfMonitorGroupsAMD;
	extern PFNGLGETPERFMONITORCOUNTERSAMDPROC						glGetPerfMonitorCountersAMD;
	extern PFNGLGETPERFMONITORGROUPSTRINGAMDPROC					glGetPerfMonitorGroupStringAMD;
	extern PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC					glGetPerfMonitorCounterStringAMD;
	extern PFNGLGETPERFMONITORCOUNTERINFOAMDPROC					glGetPerfMonitorCounterInfoAMD;
	extern PFNGLGENPERFMONITORSAMDPROC								glGenPerfMonitorsAMD;
	extern PFNGLDELETEPERFMONITORSAMDPROC							glDeletePerfMonitorsAMD;
	extern PFNGLSELECTPERFMONITORCOUNTERSAMDPROC					glSelectPerfMonitorCountersAMD;
	extern PFNGLBEGINPERFMONITORAMDPROC								glBeginPerfMonitorAMD;
	extern PFNGLENDPERFMONITORAMDPROC								glEndPerfMonitorAMD;
	extern PFNGLGETPERFMONITORCOUNTERDATAAMDPROC					glGetPerfMonitorCounterDataAMD;
	// GL_EXT_EGL_image_storage
	extern PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC						glEGLImageTargetTexStorageEXT;
	extern PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC					glEGLImageTargetTextureStorageEXT;
	// GL_EXT_debug_label
	extern PFNGLLABELOBJECTEXTPROC									glLabelObjectEXT;
	extern PFNGLGETOBJECTLABELEXTPROC								glGetObjectLabelEXT;
	// GL_EXT_debug_marker
	extern PFNGLINSERTEVENTMARKEREXTPROC							glInsertEventMarkerEXT;
	extern PFNGLPUSHGROUPMARKEREXTPROC								glPushGroupMarkerEXT;
	extern PFNGLPOPGROUPMARKEREXTPROC								glPopGroupMarkerEXT;
	// GL_EXT_direct_state_access
	extern PFNGLMATRIXLOADFEXTPROC									glMatrixLoadfEXT;
	extern PFNGLMATRIXLOADDEXTPROC									glMatrixLoaddEXT;
	extern PFNGLMATRIXMULTFEXTPROC									glMatrixMultfEXT;
	extern PFNGLMATRIXMULTDEXTPROC									glMatrixMultdEXT;
	extern PFNGLMATRIXLOADIDENTITYEXTPROC							glMatrixLoadIdentityEXT;
	extern PFNGLMATRIXROTATEFEXTPROC								glMatrixRotatefEXT;
	extern PFNGLMATRIXROTATEDEXTPROC								glMatrixRotatedEXT;
	extern PFNGLMATRIXSCALEFEXTPROC									glMatrixScalefEXT;
	extern PFNGLMATRIXSCALEDEXTPROC									glMatrixScaledEXT;
	extern PFNGLMATRIXTRANSLATEFEXTPROC								glMatrixTranslatefEXT;
	extern PFNGLMATRIXTRANSLATEDEXTPROC								glMatrixTranslatedEXT;
	extern PFNGLMATRIXFRUSTUMEXTPROC								glMatrixFrustumEXT;
	extern PFNGLMATRIXORTHOEXTPROC									glMatrixOrthoEXT;
	extern PFNGLMATRIXPOPEXTPROC									glMatrixPopEXT;
	extern PFNGLMATRIXPUSHEXTPROC									glMatrixPushEXT;
	extern PFNGLCLIENTATTRIBDEFAULTEXTPROC							glClientAttribDefaultEXT;
	extern PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC						glPushClientAttribDefaultEXT;
	extern PFNGLTEXTUREPARAMETERFEXTPROC							glTextureParameterfEXT;
	extern PFNGLTEXTUREPARAMETERFVEXTPROC							glTextureParameterfvEXT;
	extern PFNGLTEXTUREPARAMETERIEXTPROC							glTextureParameteriEXT;
	extern PFNGLTEXTUREPARAMETERIVEXTPROC							glTextureParameterivEXT;
	extern PFNGLTEXTUREIMAGE1DEXTPROC								glTextureImage1DEXT;
	extern PFNGLTEXTUREIMAGE2DEXTPROC								glTextureImage2DEXT;
	extern PFNGLTEXTURESUBIMAGE1DEXTPROC							glTextureSubImage1DEXT;
	extern PFNGLTEXTURESUBIMAGE2DEXTPROC							glTextureSubImage2DEXT;
	extern PFNGLCOPYTEXTUREIMAGE1DEXTPROC							glCopyTextureImage1DEXT;
	extern PFNGLCOPYTEXTUREIMAGE2DEXTPROC							glCopyTextureImage2DEXT;
	extern PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC						glCopyTextureSubImage1DEXT;
	extern PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC						glCopyTextureSubImage2DEXT;
	extern PFNGLGETTEXTUREIMAGEEXTPROC								glGetTextureImageEXT;
	extern PFNGLGETTEXTUREPARAMETERFVEXTPROC						glGetTextureParameterfvEXT;
	extern PFNGLGETTEXTUREPARAMETERIVEXTPROC						glGetTextureParameterivEXT;
	extern PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC					glGetTextureLevelParameterfvEXT;
	extern PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC					glGetTextureLevelParameterivEXT;
	extern PFNGLTEXTUREIMAGE3DEXTPROC								glTextureImage3DEXT;
	extern PFNGLTEXTURESUBIMAGE3DEXTPROC							glTextureSubImage3DEXT;
	extern PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC						glCopyTextureSubImage3DEXT;
	extern PFNGLBINDMULTITEXTUREEXTPROC								glBindMultiTextureEXT;
	extern PFNGLMULTITEXCOORDPOINTEREXTPROC							glMultiTexCoordPointerEXT;
	extern PFNGLMULTITEXENVFEXTPROC									glMultiTexEnvfEXT;
	extern PFNGLMULTITEXENVFVEXTPROC								glMultiTexEnvfvEXT;
	extern PFNGLMULTITEXENVIEXTPROC									glMultiTexEnviEXT;
	extern PFNGLMULTITEXENVIVEXTPROC								glMultiTexEnvivEXT;
	extern PFNGLMULTITEXGENDEXTPROC									glMultiTexGendEXT;
	extern PFNGLMULTITEXGENDVEXTPROC								glMultiTexGendvEXT;
	extern PFNGLMULTITEXGENFEXTPROC									glMultiTexGenfEXT;
	extern PFNGLMULTITEXGENFVEXTPROC								glMultiTexGenfvEXT;
	extern PFNGLMULTITEXGENIEXTPROC									glMultiTexGeniEXT;
	extern PFNGLMULTITEXGENIVEXTPROC								glMultiTexGenivEXT;
	extern PFNGLGETMULTITEXENVFVEXTPROC								glGetMultiTexEnvfvEXT;
	extern PFNGLGETMULTITEXENVIVEXTPROC								glGetMultiTexEnvivEXT;
	extern PFNGLGETMULTITEXGENDVEXTPROC								glGetMultiTexGendvEXT;
	extern PFNGLGETMULTITEXGENFVEXTPROC								glGetMultiTexGenfvEXT;
	extern PFNGLGETMULTITEXGENIVEXTPROC								glGetMultiTexGenivEXT;
	extern PFNGLMULTITEXPARAMETERIEXTPROC							glMultiTexParameteriEXT;
	extern PFNGLMULTITEXPARAMETERIVEXTPROC							glMultiTexParameterivEXT;
	extern PFNGLMULTITEXPARAMETERFEXTPROC							glMultiTexParameterfEXT;
	extern PFNGLMULTITEXPARAMETERFVEXTPROC							glMultiTexParameterfvEXT;
	extern PFNGLMULTITEXIMAGE1DEXTPROC								glMultiTexImage1DEXT;
	extern PFNGLMULTITEXIMAGE2DEXTPROC								glMultiTexImage2DEXT;
	extern PFNGLMULTITEXSUBIMAGE1DEXTPROC							glMultiTexSubImage1DEXT;
	extern PFNGLMULTITEXSUBIMAGE2DEXTPROC							glMultiTexSubImage2DEXT;
	extern PFNGLCOPYMULTITEXIMAGE1DEXTPROC							glCopyMultiTexImage1DEXT;
	extern PFNGLCOPYMULTITEXIMAGE2DEXTPROC							glCopyMultiTexImage2DEXT;
	extern PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC						glCopyMultiTexSubImage1DEXT;
	extern PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC						glCopyMultiTexSubImage2DEXT;
	extern PFNGLGETMULTITEXIMAGEEXTPROC								glGetMultiTexImageEXT;
	extern PFNGLGETMULTITEXPARAMETERFVEXTPROC						glGetMultiTexParameterfvEXT;
	extern PFNGLGETMULTITEXPARAMETERIVEXTPROC						glGetMultiTexParameterivEXT;
	extern PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC					glGetMultiTexLevelParameterfvEXT;
	extern PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC					glGetMultiTexLevelParameterivEXT;
	extern PFNGLMULTITEXIMAGE3DEXTPROC								glMultiTexImage3DEXT;
	extern PFNGLMULTITEXSUBIMAGE3DEXTPROC							glMultiTexSubImage3DEXT;
	extern PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC						glCopyMultiTexSubImage3DEXT;
	extern PFNGLENABLECLIENTSTATEINDEXEDEXTPROC						glEnableClientStateIndexedEXT;
	extern PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC					glDisableClientStateIndexedEXT;
	extern PFNGLGETFLOATINDEXEDVEXTPROC								glGetFloatIndexedvEXT;
	extern PFNGLGETDOUBLEINDEXEDVEXTPROC							glGetDoubleIndexedvEXT;
	extern PFNGLGETPOINTERINDEXEDVEXTPROC							glGetPointerIndexedvEXT;
	extern PFNGLENABLEINDEXEDEXTPROC								glEnableIndexedEXT;
	extern PFNGLDISABLEINDEXEDEXTPROC								glDisableIndexedEXT;
	extern PFNGLISENABLEDINDEXEDEXTPROC								glIsEnabledIndexedEXT;
	extern PFNGLGETINTEGERINDEXEDVEXTPROC							glGetIntegerIndexedvEXT;
	extern PFNGLGETBOOLEANINDEXEDVEXTPROC							glGetBooleanIndexedvEXT;
	extern PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC						glCompressedTextureImage3DEXT;
	extern PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC						glCompressedTextureImage2DEXT;
	extern PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC						glCompressedTextureImage1DEXT;
	extern PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC					glCompressedTextureSubImage3DEXT;
	extern PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC					glCompressedTextureSubImage2DEXT;
	extern PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC					glCompressedTextureSubImage1DEXT;
	extern PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC					glGetCompressedTextureImageEXT;
	extern PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC					glCompressedMultiTexImage3DEXT;
	extern PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC					glCompressedMultiTexImage2DEXT;
	extern PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC					glCompressedMultiTexImage1DEXT;
	extern PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC					glCompressedMultiTexSubImage3DEXT;
	extern PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC					glCompressedMultiTexSubImage2DEXT;
	extern PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC					glCompressedMultiTexSubImage1DEXT;
	extern PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC					glGetCompressedMultiTexImageEXT;
	extern PFNGLMATRIXLOADTRANSPOSEFEXTPROC							glMatrixLoadTransposefEXT;
	extern PFNGLMATRIXLOADTRANSPOSEDEXTPROC							glMatrixLoadTransposedEXT;
	extern PFNGLMATRIXMULTTRANSPOSEFEXTPROC							glMatrixMultTransposefEXT;
	extern PFNGLMATRIXMULTTRANSPOSEDEXTPROC							glMatrixMultTransposedEXT;
	extern PFNGLNAMEDBUFFERDATAEXTPROC								glNamedBufferDataEXT;
	extern PFNGLNAMEDBUFFERSUBDATAEXTPROC							glNamedBufferSubDataEXT;
	extern PFNGLMAPNAMEDBUFFEREXTPROC								glMapNamedBufferEXT;
	extern PFNGLUNMAPNAMEDBUFFEREXTPROC								glUnmapNamedBufferEXT;
	extern PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC					glGetNamedBufferParameterivEXT;
	extern PFNGLGETNAMEDBUFFERPOINTERVEXTPROC						glGetNamedBufferPointervEXT;
	extern PFNGLGETNAMEDBUFFERSUBDATAEXTPROC						glGetNamedBufferSubDataEXT;
	extern PFNGLPROGRAMUNIFORM1FEXTPROC								glProgramUniform1fEXT;
	extern PFNGLPROGRAMUNIFORM2FEXTPROC								glProgramUniform2fEXT;
	extern PFNGLPROGRAMUNIFORM3FEXTPROC								glProgramUniform3fEXT;
	extern PFNGLPROGRAMUNIFORM4FEXTPROC								glProgramUniform4fEXT;
	extern PFNGLPROGRAMUNIFORM1IEXTPROC								glProgramUniform1iEXT;
	extern PFNGLPROGRAMUNIFORM2IEXTPROC								glProgramUniform2iEXT;
	extern PFNGLPROGRAMUNIFORM3IEXTPROC								glProgramUniform3iEXT;
	extern PFNGLPROGRAMUNIFORM4IEXTPROC								glProgramUniform4iEXT;
	extern PFNGLPROGRAMUNIFORM1FVEXTPROC							glProgramUniform1fvEXT;
	extern PFNGLPROGRAMUNIFORM2FVEXTPROC							glProgramUniform2fvEXT;
	extern PFNGLPROGRAMUNIFORM3FVEXTPROC							glProgramUniform3fvEXT;
	extern PFNGLPROGRAMUNIFORM4FVEXTPROC							glProgramUniform4fvEXT;
	extern PFNGLPROGRAMUNIFORM1IVEXTPROC							glProgramUniform1ivEXT;
	extern PFNGLPROGRAMUNIFORM2IVEXTPROC							glProgramUniform2ivEXT;
	extern PFNGLPROGRAMUNIFORM3IVEXTPROC							glProgramUniform3ivEXT;
	extern PFNGLPROGRAMUNIFORM4IVEXTPROC							glProgramUniform4ivEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC						glProgramUniformMatrix2fvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC						glProgramUniformMatrix3fvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC						glProgramUniformMatrix4fvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC					glProgramUniformMatrix2x3fvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC					glProgramUniformMatrix3x2fvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC					glProgramUniformMatrix2x4fvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC					glProgramUniformMatrix4x2fvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC					glProgramUniformMatrix3x4fvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC					glProgramUniformMatrix4x3fvEXT;
	extern PFNGLTEXTUREBUFFEREXTPROC								glTextureBufferEXT;
	extern PFNGLMULTITEXBUFFEREXTPROC								glMultiTexBufferEXT;
	extern PFNGLTEXTUREPARAMETERIIVEXTPROC							glTextureParameterIivEXT;
	extern PFNGLTEXTUREPARAMETERIUIVEXTPROC							glTextureParameterIuivEXT;
	extern PFNGLGETTEXTUREPARAMETERIIVEXTPROC						glGetTextureParameterIivEXT;
	extern PFNGLGETTEXTUREPARAMETERIUIVEXTPROC						glGetTextureParameterIuivEXT;
	extern PFNGLMULTITEXPARAMETERIIVEXTPROC							glMultiTexParameterIivEXT;
	extern PFNGLMULTITEXPARAMETERIUIVEXTPROC						glMultiTexParameterIuivEXT;
	extern PFNGLGETMULTITEXPARAMETERIIVEXTPROC						glGetMultiTexParameterIivEXT;
	extern PFNGLGETMULTITEXPARAMETERIUIVEXTPROC						glGetMultiTexParameterIuivEXT;
	extern PFNGLPROGRAMUNIFORM1UIEXTPROC							glProgramUniform1uiEXT;
	extern PFNGLPROGRAMUNIFORM2UIEXTPROC							glProgramUniform2uiEXT;
	extern PFNGLPROGRAMUNIFORM3UIEXTPROC							glProgramUniform3uiEXT;
	extern PFNGLPROGRAMUNIFORM4UIEXTPROC							glProgramUniform4uiEXT;
	extern PFNGLPROGRAMUNIFORM1UIVEXTPROC							glProgramUniform1uivEXT;
	extern PFNGLPROGRAMUNIFORM2UIVEXTPROC							glProgramUniform2uivEXT;
	extern PFNGLPROGRAMUNIFORM3UIVEXTPROC							glProgramUniform3uivEXT;
	extern PFNGLPROGRAMUNIFORM4UIVEXTPROC							glProgramUniform4uivEXT;
	extern PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC				glNamedProgramLocalParameters4fvEXT;
	extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC				glNamedProgramLocalParameterI4iEXT;
	extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC				glNamedProgramLocalParameterI4ivEXT;
	extern PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC				glNamedProgramLocalParametersI4ivEXT;
	extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC				glNamedProgramLocalParameterI4uiEXT;
	extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC				glNamedProgramLocalParameterI4uivEXT;
	extern PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC				glNamedProgramLocalParametersI4uivEXT;
	extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC				glGetNamedProgramLocalParameterIivEXT;
	extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC			glGetNamedProgramLocalParameterIuivEXT;
	extern PFNGLENABLECLIENTSTATEIEXTPROC							glEnableClientStateiEXT;
	extern PFNGLDISABLECLIENTSTATEIEXTPROC							glDisableClientStateiEXT;
	extern PFNGLGETFLOATI_VEXTPROC									glGetFloati_vEXT;
	extern PFNGLGETDOUBLEI_VEXTPROC									glGetDoublei_vEXT;
	extern PFNGLGETPOINTERI_VEXTPROC								glGetPointeri_vEXT;
	extern PFNGLNAMEDPROGRAMSTRINGEXTPROC							glNamedProgramStringEXT;
	extern PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC					glNamedProgramLocalParameter4dEXT;
	extern PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC				glNamedProgramLocalParameter4dvEXT;
	extern PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC					glNamedProgramLocalParameter4fEXT;
	extern PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC				glNamedProgramLocalParameter4fvEXT;
	extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC				glGetNamedProgramLocalParameterdvEXT;
	extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC				glGetNamedProgramLocalParameterfvEXT;
	extern PFNGLGETNAMEDPROGRAMIVEXTPROC							glGetNamedProgramivEXT;
	extern PFNGLGETNAMEDPROGRAMSTRINGEXTPROC						glGetNamedProgramStringEXT;
	extern PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC						glNamedRenderbufferStorageEXT;
	extern PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC				glGetNamedRenderbufferParameterivEXT;
	extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC			glNamedRenderbufferStorageMultisampleEXT;
	extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC	glNamedRenderbufferStorageMultisampleCoverageEXT;
	extern PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC					glCheckNamedFramebufferStatusEXT;
	extern PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC					glNamedFramebufferTexture1DEXT;
	extern PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC					glNamedFramebufferTexture2DEXT;
	extern PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC					glNamedFramebufferTexture3DEXT;
	extern PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC					glNamedFramebufferRenderbufferEXT;
	extern PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC		glGetNamedFramebufferAttachmentParameterivEXT;
	extern PFNGLGENERATETEXTUREMIPMAPEXTPROC						glGenerateTextureMipmapEXT;
	extern PFNGLGENERATEMULTITEXMIPMAPEXTPROC						glGenerateMultiTexMipmapEXT;
	extern PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC						glFramebufferDrawBufferEXT;
	extern PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC						glFramebufferDrawBuffersEXT;
	extern PFNGLFRAMEBUFFERREADBUFFEREXTPROC						glFramebufferReadBufferEXT;
	extern PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC					glGetFramebufferParameterivEXT;
	extern PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC						glNamedCopyBufferSubDataEXT;
	extern PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC						glNamedFramebufferTextureEXT;
	extern PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC					glNamedFramebufferTextureLayerEXT;
	extern PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC					glNamedFramebufferTextureFaceEXT;
	extern PFNGLTEXTURERENDERBUFFEREXTPROC							glTextureRenderbufferEXT;
	extern PFNGLMULTITEXRENDERBUFFEREXTPROC							glMultiTexRenderbufferEXT;
	extern PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC						glVertexArrayVertexOffsetEXT;
	extern PFNGLVERTEXARRAYCOLOROFFSETEXTPROC						glVertexArrayColorOffsetEXT;
	extern PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC					glVertexArrayEdgeFlagOffsetEXT;
	extern PFNGLVERTEXARRAYINDEXOFFSETEXTPROC						glVertexArrayIndexOffsetEXT;
	extern PFNGLVERTEXARRAYNORMALOFFSETEXTPROC						glVertexArrayNormalOffsetEXT;
	extern PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC					glVertexArrayTexCoordOffsetEXT;
	extern PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC				glVertexArrayMultiTexCoordOffsetEXT;
	extern PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC					glVertexArrayFogCoordOffsetEXT;
	extern PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC				glVertexArraySecondaryColorOffsetEXT;
	extern PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC				glVertexArrayVertexAttribOffsetEXT;
	extern PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC				glVertexArrayVertexAttribIOffsetEXT;
	extern PFNGLENABLEVERTEXARRAYEXTPROC							glEnableVertexArrayEXT;
	extern PFNGLDISABLEVERTEXARRAYEXTPROC							glDisableVertexArrayEXT;
	extern PFNGLENABLEVERTEXARRAYATTRIBEXTPROC						glEnableVertexArrayAttribEXT;
	extern PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC						glDisableVertexArrayAttribEXT;
	extern PFNGLGETVERTEXARRAYINTEGERVEXTPROC						glGetVertexArrayIntegervEXT;
	extern PFNGLGETVERTEXARRAYPOINTERVEXTPROC						glGetVertexArrayPointervEXT;
	extern PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC						glGetVertexArrayIntegeri_vEXT;
	extern PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC						glGetVertexArrayPointeri_vEXT;
	extern PFNGLMAPNAMEDBUFFERRANGEEXTPROC							glMapNamedBufferRangeEXT;
	extern PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC					glFlushMappedNamedBufferRangeEXT;
	extern PFNGLNAMEDBUFFERSTORAGEEXTPROC							glNamedBufferStorageEXT;
	extern PFNGLCLEARNAMEDBUFFERDATAEXTPROC							glClearNamedBufferDataEXT;
	extern PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC						glClearNamedBufferSubDataEXT;
	extern PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC					glNamedFramebufferParameteriEXT;
	extern PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC				glGetNamedFramebufferParameterivEXT;
	extern PFNGLPROGRAMUNIFORM1DEXTPROC								glProgramUniform1dEXT;
	extern PFNGLPROGRAMUNIFORM2DEXTPROC								glProgramUniform2dEXT;
	extern PFNGLPROGRAMUNIFORM3DEXTPROC								glProgramUniform3dEXT;
	extern PFNGLPROGRAMUNIFORM4DEXTPROC								glProgramUniform4dEXT;
	extern PFNGLPROGRAMUNIFORM1DVEXTPROC							glProgramUniform1dvEXT;
	extern PFNGLPROGRAMUNIFORM2DVEXTPROC							glProgramUniform2dvEXT;
	extern PFNGLPROGRAMUNIFORM3DVEXTPROC							glProgramUniform3dvEXT;
	extern PFNGLPROGRAMUNIFORM4DVEXTPROC							glProgramUniform4dvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC						glProgramUniformMatrix2dvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC						glProgramUniformMatrix3dvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC						glProgramUniformMatrix4dvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC					glProgramUniformMatrix2x3dvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC					glProgramUniformMatrix2x4dvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC					glProgramUniformMatrix3x2dvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC					glProgramUniformMatrix3x4dvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC					glProgramUniformMatrix4x2dvEXT;
	extern PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC					glProgramUniformMatrix4x3dvEXT;
	extern PFNGLTEXTUREBUFFERRANGEEXTPROC							glTextureBufferRangeEXT;
	extern PFNGLTEXTURESTORAGE1DEXTPROC								glTextureStorage1DEXT;
	extern PFNGLTEXTURESTORAGE2DEXTPROC								glTextureStorage2DEXT;
	extern PFNGLTEXTURESTORAGE3DEXTPROC								glTextureStorage3DEXT;
	extern PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC					glTextureStorage2DMultisampleEXT;
	extern PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC					glTextureStorage3DMultisampleEXT;
	extern PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC					glVertexArrayBindVertexBufferEXT;
	extern PFNGLVERTEXARRAYVERTEXATTRIBFORMATEXTPROC				glVertexArrayVertexAttribFormatEXT;
	extern PFNGLVERTEXARRAYVERTEXATTRIBIFORMATEXTPROC				glVertexArrayVertexAttribIFormatEXT;
	extern PFNGLVERTEXARRAYVERTEXATTRIBLFORMATEXTPROC				glVertexArrayVertexAttribLFormatEXT;
	extern PFNGLVERTEXARRAYVERTEXATTRIBBINDINGEXTPROC				glVertexArrayVertexAttribBindingEXT;
	extern PFNGLVERTEXARRAYVERTEXBINDINGDIVISOREXTPROC				glVertexArrayVertexBindingDivisorEXT;
	extern PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC				glVertexArrayVertexAttribLOffsetEXT;
	extern PFNGLTEXTUREPAGECOMMITMENTEXTPROC						glTexturePageCommitmentEXT;
	extern PFNGLVERTEXARRAYVERTEXATTRIBDIVISOREXTPROC				glVertexArrayVertexAttribDivisorEXT;
	// GL_EXT_draw_instanced
	extern PFNGLDRAWARRAYSINSTANCEDEXTPROC							glDrawArraysInstancedEXT;
	extern PFNGLDRAWELEMENTSINSTANCEDEXTPROC						glDrawElementsInstancedEXT;
	// GL_EXT_polygon_offset_clamp
	extern PFNGLPOLYGONOFFSETCLAMPEXTPROC							glPolygonOffsetClampEXT;
	// GL_EXT_raster_multisample
	extern PFNGLRASTERSAMPLESEXTPROC								glRasterSamplesEXT;
	// GL_EXT_separate_shader_objects
	extern PFNGLUSESHADERPROGRAMEXTPROC								glUseShaderProgramEXT;
	extern PFNGLACTIVEPROGRAMEXTPROC								glActiveProgramEXT;
	extern PFNGLCREATESHADERPROGRAMEXTPROC							glCreateShaderProgramEXT;
	// GL_EXT_shader_framebuffer_fetch_non_coherent
	extern PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC						glFramebufferFetchBarrierEXT;
	// GL_EXT_window_rectangles
	extern PFNGLWINDOWRECTANGLESEXTPROC								glWindowRectanglesEXT;
	// GL_INTEL_framebuffer_CMAA
	extern PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC				glApplyFramebufferAttachmentCMAAINTEL;
	// GL_INTEL_performance_query
	extern PFNGLBEGINPERFQUERYINTELPROC								glBeginPerfQueryINTEL;
	extern PFNGLCREATEPERFQUERYINTELPROC							glCreatePerfQueryINTEL;
	extern PFNGLDELETEPERFQUERYINTELPROC							glDeletePerfQueryINTEL;
	extern PFNGLENDPERFQUERYINTELPROC								glEndPerfQueryINTEL;
	extern PFNGLGETFIRSTPERFQUERYIDINTELPROC						glGetFirstPerfQueryIdINTEL;
	extern PFNGLGETNEXTPERFQUERYIDINTELPROC							glGetNextPerfQueryIdINTEL;
	extern PFNGLGETPERFCOUNTERINFOINTELPROC							glGetPerfCounterInfoINTEL;
	extern PFNGLGETPERFQUERYDATAINTELPROC							glGetPerfQueryDataINTEL;
	extern PFNGLGETPERFQUERYIDBYNAMEINTELPROC						glGetPerfQueryIdByNameINTEL;
	extern PFNGLGETPERFQUERYINFOINTELPROC							glGetPerfQueryInfoINTEL;
	// GL_MESA_framebuffer_flip_y
	extern PFNGLFRAMEBUFFERPARAMETERIMESAPROC						glFramebufferParameteriMESA;
	extern PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC					glGetFramebufferParameterivMESA;
	// GL_NV_bindless_multi_draw_indirect
	extern PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSNVPROC				glMultiDrawArraysIndirectBindlessNV;
	extern PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSNVPROC				glMultiDrawElementsIndirectBindlessNV;
	// GL_NV_bindless_multi_draw_indirect_count
	extern PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSCOUNTNVPROC			glMultiDrawArraysIndirectBindlessCountNV;
	extern PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSCOUNTNVPROC		glMultiDrawElementsIndirectBindlessCountNV;
	// GL_NV_bindless_texture
	extern PFNGLGETTEXTUREHANDLENVPROC								glGetTextureHandleNV;
	extern PFNGLGETTEXTURESAMPLERHANDLENVPROC						glGetTextureSamplerHandleNV;
	extern PFNGLMAKETEXTUREHANDLERESIDENTNVPROC						glMakeTextureHandleResidentNV;
	extern PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC					glMakeTextureHandleNonResidentNV;
	extern PFNGLGETIMAGEHANDLENVPROC								glGetImageHandleNV;
	extern PFNGLMAKEIMAGEHANDLERESIDENTNVPROC						glMakeImageHandleResidentNV;
	extern PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC					glMakeImageHandleNonResidentNV;
	extern PFNGLUNIFORMHANDLEUI64NVPROC								glUniformHandleui64NV;
	extern PFNGLUNIFORMHANDLEUI64VNVPROC							glUniformHandleui64vNV;
	extern PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC						glProgramUniformHandleui64NV;
	extern PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC						glProgramUniformHandleui64vNV;
	extern PFNGLISTEXTUREHANDLERESIDENTNVPROC						glIsTextureHandleResidentNV;
	extern PFNGLISIMAGEHANDLERESIDENTNVPROC							glIsImageHandleResidentNV;
	// GL_NV_blend_equation_advanced
	extern PFNGLBLENDPARAMETERINVPROC								glBlendParameteriNV;
	extern PFNGLBLENDBARRIERNVPROC									glBlendBarrierNV;
	// GL_NV_clip_space_w_scaling
	extern PFNGLVIEWPORTPOSITIONWSCALENVPROC						glViewportPositionWScaleNV;
	// GL_NV_command_list
	extern PFNGLCREATESTATESNVPROC									glCreateStatesNV;
	extern PFNGLDELETESTATESNVPROC									glDeleteStatesNV;
	extern PFNGLISSTATENVPROC										glIsStateNV;
	extern PFNGLSTATECAPTURENVPROC									glStateCaptureNV;
	extern PFNGLGETCOMMANDHEADERNVPROC								glGetCommandHeaderNV;
	extern PFNGLGETSTAGEINDEXNVPROC									glGetStageIndexNV;
	extern PFNGLDRAWCOMMANDSNVPROC									glDrawCommandsNV;
	extern PFNGLDRAWCOMMANDSADDRESSNVPROC							glDrawCommandsAddressNV;
	extern PFNGLDRAWCOMMANDSSTATESNVPROC							glDrawCommandsStatesNV;
	extern PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC						glDrawCommandsStatesAddressNV;
	extern PFNGLCREATECOMMANDLISTSNVPROC							glCreateCommandListsNV;
	extern PFNGLDELETECOMMANDLISTSNVPROC							glDeleteCommandListsNV;
	extern PFNGLISCOMMANDLISTNVPROC									glIsCommandListNV;
	extern PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC					glListDrawCommandsStatesClientNV;
	extern PFNGLCOMMANDLISTSEGMENTSNVPROC							glCommandListSegmentsNV;
	extern PFNGLCOMPILECOMMANDLISTNVPROC							glCompileCommandListNV;
	extern PFNGLCALLCOMMANDLISTNVPROC								glCallCommandListNV;
	// GL_NV_conditional_render
	extern PFNGLBEGINCONDITIONALRENDERNVPROC						glBeginConditionalRenderNV;
	extern PFNGLENDCONDITIONALRENDERNVPROC							glEndConditionalRenderNV;
	// GL_NV_conservative_raster
	extern PFNGLSUBPIXELPRECISIONBIASNVPROC							glSubpixelPrecisionBiasNV;
	// GL_NV_conservative_raster_dilate
	extern PFNGLCONSERVATIVERASTERPARAMETERFNVPROC					glConservativeRasterParameterfNV;
	// GL_NV_conservative_raster_pre_snap_triangles
	extern PFNGLCONSERVATIVERASTERPARAMETERINVPROC					glConservativeRasterParameteriNV;
	// GL_NV_depth_buffer_float
	extern PFNGLDEPTHRANGEDNVPROC									glDepthRangedNV;
	extern PFNGLCLEARDEPTHDNVPROC									glClearDepthdNV;
	extern PFNGLDEPTHBOUNDSDNVPROC									glDepthBoundsdNV;
	// GL_NV_draw_vulkan_image
	extern PFNGLDRAWVKIMAGENVPROC									glDrawVkImageNV;
	extern PFNGLGETVKPROCADDRNVPROC									glGetVkProcAddrNV;
	extern PFNGLWAITVKSEMAPHORENVPROC								glWaitVkSemaphoreNV;
	extern PFNGLSIGNALVKSEMAPHORENVPROC								glSignalVkSemaphoreNV;
	extern PFNGLSIGNALVKFENCENVPROC									glSignalVkFenceNV;
	// GL_NV_fragment_coverage_to_color
	extern PFNGLFRAGMENTCOVERAGECOLORNVPROC							glFragmentCoverageColorNV;
	// GL_NV_framebuffer_mixed_samples
	extern PFNGLCOVERAGEMODULATIONTABLENVPROC						glCoverageModulationTableNV;
	extern PFNGLGETCOVERAGEMODULATIONTABLENVPROC					glGetCoverageModulationTableNV;
	extern PFNGLCOVERAGEMODULATIONNVPROC							glCoverageModulationNV;
	// GL_NV_framebuffer_multisample_coverage
	extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC		glRenderbufferStorageMultisampleCoverageNV;
	// GL_NV_gpu_shader5
	extern PFNGLUNIFORM1I64NVPROC									glUniform1i64NV;
	extern PFNGLUNIFORM2I64NVPROC									glUniform2i64NV;
	extern PFNGLUNIFORM3I64NVPROC									glUniform3i64NV;
	extern PFNGLUNIFORM4I64NVPROC									glUniform4i64NV;
	extern PFNGLUNIFORM1I64VNVPROC									glUniform1i64vNV;
	extern PFNGLUNIFORM2I64VNVPROC									glUniform2i64vNV;
	extern PFNGLUNIFORM3I64VNVPROC									glUniform3i64vNV;
	extern PFNGLUNIFORM4I64VNVPROC									glUniform4i64vNV;
	extern PFNGLUNIFORM1UI64NVPROC									glUniform1ui64NV;
	extern PFNGLUNIFORM2UI64NVPROC									glUniform2ui64NV;
	extern PFNGLUNIFORM3UI64NVPROC									glUniform3ui64NV;
	extern PFNGLUNIFORM4UI64NVPROC									glUniform4ui64NV;
	extern PFNGLUNIFORM1UI64VNVPROC									glUniform1ui64vNV;
	extern PFNGLUNIFORM2UI64VNVPROC									glUniform2ui64vNV;
	extern PFNGLUNIFORM3UI64VNVPROC									glUniform3ui64vNV;
	extern PFNGLUNIFORM4UI64VNVPROC									glUniform4ui64vNV;
	extern PFNGLGETUNIFORMI64VNVPROC								glGetUniformi64vNV;
	extern PFNGLPROGRAMUNIFORM1I64NVPROC							glProgramUniform1i64NV;
	extern PFNGLPROGRAMUNIFORM2I64NVPROC							glProgramUniform2i64NV;
	extern PFNGLPROGRAMUNIFORM3I64NVPROC							glProgramUniform3i64NV;
	extern PFNGLPROGRAMUNIFORM4I64NVPROC							glProgramUniform4i64NV;
	extern PFNGLPROGRAMUNIFORM1I64VNVPROC							glProgramUniform1i64vNV;
	extern PFNGLPROGRAMUNIFORM2I64VNVPROC							glProgramUniform2i64vNV;
	extern PFNGLPROGRAMUNIFORM3I64VNVPROC							glProgramUniform3i64vNV;
	extern PFNGLPROGRAMUNIFORM4I64VNVPROC							glProgramUniform4i64vNV;
	extern PFNGLPROGRAMUNIFORM1UI64NVPROC							glProgramUniform1ui64NV;
	extern PFNGLPROGRAMUNIFORM2UI64NVPROC							glProgramUniform2ui64NV;
	extern PFNGLPROGRAMUNIFORM3UI64NVPROC							glProgramUniform3ui64NV;
	extern PFNGLPROGRAMUNIFORM4UI64NVPROC							glProgramUniform4ui64NV;
	extern PFNGLPROGRAMUNIFORM1UI64VNVPROC							glProgramUniform1ui64vNV;
	extern PFNGLPROGRAMUNIFORM2UI64VNVPROC							glProgramUniform2ui64vNV;
	extern PFNGLPROGRAMUNIFORM3UI64VNVPROC							glProgramUniform3ui64vNV;
	extern PFNGLPROGRAMUNIFORM4UI64VNVPROC							glProgramUniform4ui64vNV;
	// GL_NV_internalformat_sample_query
	extern PFNGLGETINTERNALFORMATSAMPLEIVNVPROC						glGetInternalformatSampleivNV;
	// GL_NV_memory_attachment
	extern PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC			glGetMemoryObjectDetachedResourcesuivNV;
	extern PFNGLRESETMEMORYOBJECTPARAMETERNVPROC					glResetMemoryObjectParameterNV;
	extern PFNGLTEXATTACHMEMORYNVPROC								glTexAttachMemoryNV;
	extern PFNGLBUFFERATTACHMEMORYNVPROC							glBufferAttachMemoryNV;
	extern PFNGLTEXTUREATTACHMEMORYNVPROC							glTextureAttachMemoryNV;
	extern PFNGLNAMEDBUFFERATTACHMEMORYNVPROC						glNamedBufferAttachMemoryNV;
	// GL_NV_memory_object_sparse
	extern PFNGLBUFFERPAGECOMMITMENTMEMNVPROC						glBufferPageCommitmentMemNV;
	extern PFNGLTEXPAGECOMMITMENTMEMNVPROC							glTexPageCommitmentMemNV;
	extern PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC					glNamedBufferPageCommitmentMemNV;
	extern PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC						glTexturePageCommitmentMemNV;
	// GL_NV_mesh_shader
	extern PFNGLDRAWMESHTASKSNVPROC									glDrawMeshTasksNV;
	extern PFNGLDRAWMESHTASKSINDIRECTNVPROC							glDrawMeshTasksIndirectNV;
	extern PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC					glMultiDrawMeshTasksIndirectNV;
	extern PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC				glMultiDrawMeshTasksIndirectCountNV;
	// GL_NV_path_rendering
	extern PFNGLGENPATHSNVPROC										glGenPathsNV;
	extern PFNGLDELETEPATHSNVPROC									glDeletePathsNV;
	extern PFNGLISPATHNVPROC										glIsPathNV;
	extern PFNGLPATHCOMMANDSNVPROC									glPathCommandsNV;
	extern PFNGLPATHCOORDSNVPROC									glPathCoordsNV;
	extern PFNGLPATHSUBCOMMANDSNVPROC								glPathSubCommandsNV;
	extern PFNGLPATHSUBCOORDSNVPROC									glPathSubCoordsNV;
	extern PFNGLPATHSTRINGNVPROC									glPathStringNV;
	extern PFNGLPATHGLYPHSNVPROC									glPathGlyphsNV;
	extern PFNGLPATHGLYPHRANGENVPROC								glPathGlyphRangeNV;
	extern PFNGLWEIGHTPATHSNVPROC									glWeightPathsNV;
	extern PFNGLCOPYPATHNVPROC										glCopyPathNV;
	extern PFNGLINTERPOLATEPATHSNVPROC								glInterpolatePathsNV;
	extern PFNGLTRANSFORMPATHNVPROC									glTransformPathNV;
	extern PFNGLPATHPARAMETERIVNVPROC								glPathParameterivNV;
	extern PFNGLPATHPARAMETERINVPROC								glPathParameteriNV;
	extern PFNGLPATHPARAMETERFVNVPROC								glPathParameterfvNV;
	extern PFNGLPATHPARAMETERFNVPROC								glPathParameterfNV;
	extern PFNGLPATHDASHARRAYNVPROC									glPathDashArrayNV;
	extern PFNGLPATHSTENCILFUNCNVPROC								glPathStencilFuncNV;
	extern PFNGLPATHSTENCILDEPTHOFFSETNVPROC						glPathStencilDepthOffsetNV;
	extern PFNGLSTENCILFILLPATHNVPROC								glStencilFillPathNV;
	extern PFNGLSTENCILSTROKEPATHNVPROC								glStencilStrokePathNV;
	extern PFNGLSTENCILFILLPATHINSTANCEDNVPROC						glStencilFillPathInstancedNV;
	extern PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC					glStencilStrokePathInstancedNV;
	extern PFNGLPATHCOVERDEPTHFUNCNVPROC							glPathCoverDepthFuncNV;
	extern PFNGLCOVERFILLPATHNVPROC									glCoverFillPathNV;
	extern PFNGLCOVERSTROKEPATHNVPROC								glCoverStrokePathNV;
	extern PFNGLCOVERFILLPATHINSTANCEDNVPROC						glCoverFillPathInstancedNV;
	extern PFNGLCOVERSTROKEPATHINSTANCEDNVPROC						glCoverStrokePathInstancedNV;
	extern PFNGLGETPATHPARAMETERIVNVPROC							glGetPathParameterivNV;
	extern PFNGLGETPATHPARAMETERFVNVPROC							glGetPathParameterfvNV;
	extern PFNGLGETPATHCOMMANDSNVPROC								glGetPathCommandsNV;
	extern PFNGLGETPATHCOORDSNVPROC									glGetPathCoordsNV;
	extern PFNGLGETPATHDASHARRAYNVPROC								glGetPathDashArrayNV;
	extern PFNGLGETPATHMETRICSNVPROC								glGetPathMetricsNV;
	extern PFNGLGETPATHMETRICRANGENVPROC							glGetPathMetricRangeNV;
	extern PFNGLGETPATHSPACINGNVPROC								glGetPathSpacingNV;
	extern PFNGLISPOINTINFILLPATHNVPROC								glIsPointInFillPathNV;
	extern PFNGLISPOINTINSTROKEPATHNVPROC							glIsPointInStrokePathNV;
	extern PFNGLGETPATHLENGTHNVPROC									glGetPathLengthNV;
	extern PFNGLPOINTALONGPATHNVPROC								glPointAlongPathNV;
	extern PFNGLMATRIXLOAD3X2FNVPROC								glMatrixLoad3x2fNV;
	extern PFNGLMATRIXLOAD3X3FNVPROC								glMatrixLoad3x3fNV;
	extern PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC						glMatrixLoadTranspose3x3fNV;
	extern PFNGLMATRIXMULT3X2FNVPROC								glMatrixMult3x2fNV;
	extern PFNGLMATRIXMULT3X3FNVPROC								glMatrixMult3x3fNV;
	extern PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC						glMatrixMultTranspose3x3fNV;
	extern PFNGLSTENCILTHENCOVERFILLPATHNVPROC						glStencilThenCoverFillPathNV;
	extern PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC					glStencilThenCoverStrokePathNV;
	extern PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC				glStencilThenCoverFillPathInstancedNV;
	extern PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC			glStencilThenCoverStrokePathInstancedNV;
	extern PFNGLPATHGLYPHINDEXRANGENVPROC							glPathGlyphIndexRangeNV;
	extern PFNGLPATHGLYPHINDEXARRAYNVPROC							glPathGlyphIndexArrayNV;
	extern PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC						glPathMemoryGlyphIndexArrayNV;
	extern PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC					glProgramPathFragmentInputGenNV;
	extern PFNGLGETPROGRAMRESOURCEFVNVPROC							glGetProgramResourcefvNV;
	// GL_NV_sample_locations
	extern PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC					glFramebufferSampleLocationsfvNV;
	extern PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC				glNamedFramebufferSampleLocationsfvNV;
	extern PFNGLRESOLVEDEPTHVALUESNVPROC							glResolveDepthValuesNV;
	// GL_NV_scissor_exclusive
	extern PFNGLSCISSOREXCLUSIVENVPROC								glScissorExclusiveNV;
	extern PFNGLSCISSOREXCLUSIVEARRAYVNVPROC						glScissorExclusiveArrayvNV;
	// GL_NV_shader_buffer_load
	extern PFNGLMAKEBUFFERRESIDENTNVPROC							glMakeBufferResidentNV;
	extern PFNGLMAKEBUFFERNONRESIDENTNVPROC							glMakeBufferNonResidentNV;
	extern PFNGLISBUFFERRESIDENTNVPROC								glIsBufferResidentNV;
	extern PFNGLMAKENAMEDBUFFERRESIDENTNVPROC						glMakeNamedBufferResidentNV;
	extern PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC					glMakeNamedBufferNonResidentNV;
	extern PFNGLISNAMEDBUFFERRESIDENTNVPROC							glIsNamedBufferResidentNV;
	extern PFNGLGETBUFFERPARAMETERUI64VNVPROC						glGetBufferParameterui64vNV;
	extern PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC					glGetNamedBufferParameterui64vNV;
	extern PFNGLGETINTEGERUI64VNVPROC								glGetIntegerui64vNV;
	extern PFNGLUNIFORMUI64NVPROC									glUniformui64NV;
	extern PFNGLUNIFORMUI64VNVPROC									glUniformui64vNV;
	extern PFNGLGETUNIFORMUI64VNVPROC								glGetUniformui64vNV;
	extern PFNGLPROGRAMUNIFORMUI64NVPROC							glProgramUniformui64NV;
	extern PFNGLPROGRAMUNIFORMUI64VNVPROC							glProgramUniformui64vNV;
	// GL_NV_shading_rate_image
	extern PFNGLBINDSHADINGRATEIMAGENVPROC							glBindShadingRateImageNV;
	extern PFNGLGETSHADINGRATEIMAGEPALETTENVPROC					glGetShadingRateImagePaletteNV;
	extern PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC				glGetShadingRateSampleLocationivNV;
	extern PFNGLSHADINGRATEIMAGEBARRIERNVPROC						glShadingRateImageBarrierNV;
	extern PFNGLSHADINGRATEIMAGEPALETTENVPROC						glShadingRateImagePaletteNV;
	extern PFNGLSHADINGRATESAMPLEORDERNVPROC						glShadingRateSampleOrderNV;
	extern PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC					glShadingRateSampleOrderCustomNV;
	// GL_NV_texture_barrier
	extern PFNGLTEXTUREBARRIERNVPROC								glTextureBarrierNV;
	// GL_NV_vertex_attrib_integer_64bit
	extern PFNGLVERTEXATTRIBL1I64NVPROC								glVertexAttribL1i64NV;
	extern PFNGLVERTEXATTRIBL2I64NVPROC								glVertexAttribL2i64NV;
	extern PFNGLVERTEXATTRIBL3I64NVPROC								glVertexAttribL3i64NV;
	extern PFNGLVERTEXATTRIBL4I64NVPROC								glVertexAttribL4i64NV;
	extern PFNGLVERTEXATTRIBL1I64VNVPROC							glVertexAttribL1i64vNV;
	extern PFNGLVERTEXATTRIBL2I64VNVPROC							glVertexAttribL2i64vNV;
	extern PFNGLVERTEXATTRIBL3I64VNVPROC							glVertexAttribL3i64vNV;
	extern PFNGLVERTEXATTRIBL4I64VNVPROC							glVertexAttribL4i64vNV;
	extern PFNGLVERTEXATTRIBL1UI64NVPROC							glVertexAttribL1ui64NV;
	extern PFNGLVERTEXATTRIBL2UI64NVPROC							glVertexAttribL2ui64NV;
	extern PFNGLVERTEXATTRIBL3UI64NVPROC							glVertexAttribL3ui64NV;
	extern PFNGLVERTEXATTRIBL4UI64NVPROC							glVertexAttribL4ui64NV;
	extern PFNGLVERTEXATTRIBL1UI64VNVPROC							glVertexAttribL1ui64vNV;
	extern PFNGLVERTEXATTRIBL2UI64VNVPROC							glVertexAttribL2ui64vNV;
	extern PFNGLVERTEXATTRIBL3UI64VNVPROC							glVertexAttribL3ui64vNV;
	extern PFNGLVERTEXATTRIBL4UI64VNVPROC							glVertexAttribL4ui64vNV;
	extern PFNGLGETVERTEXATTRIBLI64VNVPROC							glGetVertexAttribLi64vNV;
	extern PFNGLGETVERTEXATTRIBLUI64VNVPROC							glGetVertexAttribLui64vNV;
	extern PFNGLVERTEXATTRIBLFORMATNVPROC							glVertexAttribLFormatNV;
	// GL_NV_vertex_buffer_unified_memory
	extern PFNGLBUFFERADDRESSRANGENVPROC							glBufferAddressRangeNV;
	extern PFNGLVERTEXFORMATNVPROC									glVertexFormatNV;
	extern PFNGLNORMALFORMATNVPROC									glNormalFormatNV;
	extern PFNGLCOLORFORMATNVPROC									glColorFormatNV;
	extern PFNGLINDEXFORMATNVPROC									glIndexFormatNV;
	extern PFNGLTEXCOORDFORMATNVPROC								glTexCoordFormatNV;
	extern PFNGLEDGEFLAGFORMATNVPROC								glEdgeFlagFormatNV;
	extern PFNGLSECONDARYCOLORFORMATNVPROC							glSecondaryColorFormatNV;
	extern PFNGLFOGCOORDFORMATNVPROC								glFogCoordFormatNV;
	extern PFNGLVERTEXATTRIBFORMATNVPROC							glVertexAttribFormatNV;
	extern PFNGLVERTEXATTRIBIFORMATNVPROC							glVertexAttribIFormatNV;
	extern PFNGLGETINTEGERUI64I_VNVPROC								glGetIntegerui64i_vNV;
	// GL_NV_viewport_swizzle
	extern PFNGLVIEWPORTSWIZZLENVPROC								glViewportSwizzleNV;
	// GL_OVR_multiview
	extern PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC					glFramebufferTextureMultiviewOVR;

#ifdef _WIN32
	// WGL_ARB_buffer_region
	extern PFNWGLCREATEBUFFERREGIONARBPROC							wglCreateBufferRegionARB;
	extern PFNWGLDELETEBUFFERREGIONARBPROC							wglDeleteBufferRegionARB;
	extern PFNWGLSAVEBUFFERREGIONARBPROC							wglSaveBufferRegionARB;
	extern PFNWGLRESTOREBUFFERREGIONARBPROC							wglRestoreBufferRegionARB;
	// WGL_ARB_create_context
	extern PFNWGLCREATECONTEXTATTRIBSARBPROC						wglCreateContextAttribsARB;
	// WGL_ARB_extensions_string
	extern PFNWGLGETEXTENSIONSSTRINGARBPROC							wglGetExtensionsStringARB;
	// WGL_ARB_make_current_read
	extern PFNWGLMAKECONTEXTCURRENTARBPROC							wglMakeContextCurrentARB;
	extern PFNWGLGETCURRENTREADDCARBPROC							wglGetCurrentReadDCARB;
	// WGL_ARB_pbuffer
	extern PFNWGLCREATEPBUFFERARBPROC								wglCreatePbufferARB;
	extern PFNWGLGETPBUFFERDCARBPROC								wglGetPbufferDCARB;
	extern PFNWGLRELEASEPBUFFERDCARBPROC							wglReleasePbufferDCARB;
	extern PFNWGLDESTROYPBUFFERARBPROC								wglDestroyPbufferARB;
	extern PFNWGLQUERYPBUFFERARBPROC								wglQueryPbufferARB;
	// WGL_ARB_pixel_format
	extern PFNWGLGETPIXELFORMATATTRIBIVARBPROC						wglGetPixelFormatAttribivARB;
	extern PFNWGLGETPIXELFORMATATTRIBFVARBPROC						wglGetPixelFormatAttribfvARB;
	extern PFNWGLCHOOSEPIXELFORMATARBPROC							wglChoosePixelFormatARB;
	// WGL_ARB_render_texture
	extern PFNWGLBINDTEXIMAGEARBPROC								wglBindTexImageARB;
	extern PFNWGLRELEASETEXIMAGEARBPROC								wglReleaseTexImageARB;
	extern PFNWGLSETPBUFFERATTRIBARBPROC							wglSetPbufferAttribARB;
	// WGL_3DL_stereo_control
	extern PFNWGLSETSTEREOEMITTERSTATE3DLPROC						wglSetStereoEmitterState3DL;
	// WGL_AMD_gpu_association
	extern PFNWGLGETGPUIDSAMDPROC									wglGetGPUIDsAMD;
	extern PFNWGLGETGPUINFOAMDPROC									wglGetGPUInfoAMD;
	extern PFNWGLGETCONTEXTGPUIDAMDPROC								wglGetContextGPUIDAMD;
	extern PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC						wglCreateAssociatedContextAMD;
	extern PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC				wglCreateAssociatedContextAttribsAMD;
	extern PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC						wglDeleteAssociatedContextAMD;
	extern PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC				wglMakeAssociatedContextCurrentAMD;
	extern PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC					wglGetCurrentAssociatedContextAMD;
	extern PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC						wglBlitContextFramebufferAMD;
	// WGL_EXT_display_color_table
	extern PFNWGLCREATEDISPLAYCOLORTABLEEXTPROC						wglCreateDisplayColorTableEXT;
	extern PFNWGLLOADDISPLAYCOLORTABLEEXTPROC						wglLoadDisplayColorTableEXT;
	extern PFNWGLBINDDISPLAYCOLORTABLEEXTPROC						wglBindDisplayColorTableEXT;
	extern PFNWGLDESTROYDISPLAYCOLORTABLEEXTPROC					wglDestroyDisplayColorTableEXT;
	// WGL_EXT_extensions_string
	extern PFNWGLGETEXTENSIONSSTRINGEXTPROC							wglGetExtensionsStringEXT;
	// WGL_EXT_make_current_read
	extern PFNWGLMAKECONTEXTCURRENTEXTPROC							wglMakeContextCurrentEXT;
	extern PFNWGLGETCURRENTREADDCEXTPROC							wglGetCurrentReadDCEXT;
	// WGL_EXT_pbuffer
	extern PFNWGLCREATEPBUFFEREXTPROC								wglCreatePbufferEXT;
	extern PFNWGLGETPBUFFERDCEXTPROC								wglGetPbufferDCEXT;
	extern PFNWGLRELEASEPBUFFERDCEXTPROC							wglReleasePbufferDCEXT;
	extern PFNWGLDESTROYPBUFFEREXTPROC								wglDestroyPbufferEXT;
	extern PFNWGLQUERYPBUFFEREXTPROC								wglQueryPbufferEXT;
	// WGL_EXT_pixel_format
	extern PFNWGLGETPIXELFORMATATTRIBIVEXTPROC						wglGetPixelFormatAttribivEXT;
	extern PFNWGLGETPIXELFORMATATTRIBFVEXTPROC						wglGetPixelFormatAttribfvEXT;
	extern PFNWGLCHOOSEPIXELFORMATEXTPROC							wglChoosePixelFormatEXT;
	// WGL_EXT_swap_control
	extern PFNWGLSWAPINTERVALEXTPROC								wglSwapIntervalEXT;
	extern PFNWGLGETSWAPINTERVALEXTPROC								wglGetSwapIntervalEXT;
	// WGL_I3D_digital_video_control
	extern PFNWGLGETDIGITALVIDEOPARAMETERSI3DPROC					wglGetDigitalVideoParametersI3D;
	extern PFNWGLSETDIGITALVIDEOPARAMETERSI3DPROC					wglSetDigitalVideoParametersI3D;
	// WGL_I3D_gamma
	extern PFNWGLGETGAMMATABLEPARAMETERSI3DPROC						wglGetGammaTableParametersI3D;
	extern PFNWGLSETGAMMATABLEPARAMETERSI3DPROC						wglSetGammaTableParametersI3D;
	extern PFNWGLGETGAMMATABLEI3DPROC								wglGetGammaTableI3D;
	extern PFNWGLSETGAMMATABLEI3DPROC								wglSetGammaTableI3D;
	// WGL_I3D_genlock
	extern PFNWGLENABLEGENLOCKI3DPROC								wglEnableGenlockI3D;
	extern PFNWGLDISABLEGENLOCKI3DPROC								wglDisableGenlockI3D;
	extern PFNWGLISENABLEDGENLOCKI3DPROC							wglIsEnabledGenlockI3D;
	extern PFNWGLGENLOCKSOURCEI3DPROC								wglGenlockSourceI3D;
	extern PFNWGLGETGENLOCKSOURCEI3DPROC							wglGetGenlockSourceI3D;
	extern PFNWGLGENLOCKSOURCEEDGEI3DPROC							wglGenlockSourceEdgeI3D;
	extern PFNWGLGETGENLOCKSOURCEEDGEI3DPROC						wglGetGenlockSourceEdgeI3D;
	extern PFNWGLGENLOCKSAMPLERATEI3DPROC							wglGenlockSampleRateI3D;
	extern PFNWGLGETGENLOCKSAMPLERATEI3DPROC						wglGetGenlockSampleRateI3D;
	extern PFNWGLGENLOCKSOURCEDELAYI3DPROC							wglGenlockSourceDelayI3D;
	extern PFNWGLGETGENLOCKSOURCEDELAYI3DPROC						wglGetGenlockSourceDelayI3D;
	extern PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC					wglQueryGenlockMaxSourceDelayI3D;
	// WGL_I3D_image_buffer
	extern PFNWGLCREATEIMAGEBUFFERI3DPROC							wglCreateImageBufferI3D;
	extern PFNWGLDESTROYIMAGEBUFFERI3DPROC							wglDestroyImageBufferI3D;
	extern PFNWGLASSOCIATEIMAGEBUFFEREVENTSI3DPROC					wglAssociateImageBufferEventsI3D;
	extern PFNWGLRELEASEIMAGEBUFFEREVENTSI3DPROC					wglReleaseImageBufferEventsI3D;
	// WGL_I3D_swap_frame_lock
	extern PFNWGLENABLEFRAMELOCKI3DPROC								wglEnableFrameLockI3D;
	extern PFNWGLDISABLEFRAMELOCKI3DPROC							wglDisableFrameLockI3D;
	extern PFNWGLISENABLEDFRAMELOCKI3DPROC							wglIsEnabledFrameLockI3D;
	extern PFNWGLQUERYFRAMELOCKMASTERI3DPROC						wglQueryFrameLockMasterI3D;
	// WGL_I3D_swap_frame_usage
	extern PFNWGLGETFRAMEUSAGEI3DPROC								wglGetFrameUsageI3D;
	extern PFNWGLBEGINFRAMETRACKINGI3DPROC							wglBeginFrameTrackingI3D;
	extern PFNWGLENDFRAMETRACKINGI3DPROC							wglEndFrameTrackingI3D;
	extern PFNWGLQUERYFRAMETRACKINGI3DPROC							wglQueryFrameTrackingI3D;
	// WGL_NV_DX_interop
	extern PFNWGLDXSETRESOURCESHAREHANDLENVPROC						wglDXSetResourceShareHandleNV;
	extern PFNWGLDXOPENDEVICENVPROC									wglDXOpenDeviceNV;
	extern PFNWGLDXCLOSEDEVICENVPROC								wglDXCloseDeviceNV;
	extern PFNWGLDXREGISTEROBJECTNVPROC								wglDXRegisterObjectNV;
	extern PFNWGLDXUNREGISTEROBJECTNVPROC							wglDXUnregisterObjectNV;
	extern PFNWGLDXOBJECTACCESSNVPROC								wglDXObjectAccessNV;
	extern PFNWGLDXLOCKOBJECTSNVPROC								wglDXLockObjectsNV;
	extern PFNWGLDXUNLOCKOBJECTSNVPROC								wglDXUnlockObjectsNV;
	// WGL_NV_copy_image
	extern PFNWGLCOPYIMAGESUBDATANVPROC								wglCopyImageSubDataNV;
	// WGL_NV_delay_before_swap
	extern PFNWGLDELAYBEFORESWAPNVPROC								wglDelayBeforeSwapNV;
	// WGL_NV_gpu_affinity
	extern PFNWGLENUMGPUSNVPROC										wglEnumGpusNV;
	extern PFNWGLENUMGPUDEVICESNVPROC								wglEnumGpuDevicesNV;
	extern PFNWGLCREATEAFFINITYDCNVPROC								wglCreateAffinityDCNV;
	extern PFNWGLENUMGPUSFROMAFFINITYDCNVPROC						wglEnumGpusFromAffinityDCNV;
	extern PFNWGLDELETEDCNVPROC										wglDeleteDCNV;
	// WGL_NV_present_video
	extern PFNWGLENUMERATEVIDEODEVICESNVPROC						wglEnumerateVideoDevicesNV;
	extern PFNWGLBINDVIDEODEVICENVPROC								wglBindVideoDeviceNV;
	extern PFNWGLQUERYCURRENTCONTEXTNVPROC							wglQueryCurrentContextNV;
	// WGL_NV_swap_group
	extern PFNWGLJOINSWAPGROUPNVPROC								wglJoinSwapGroupNV;
	extern PFNWGLBINDSWAPBARRIERNVPROC								wglBindSwapBarrierNV;
	extern PFNWGLQUERYSWAPGROUPNVPROC								wglQuerySwapGroupNV;
	extern PFNWGLQUERYMAXSWAPGROUPSNVPROC							wglQueryMaxSwapGroupsNV;
	extern PFNWGLQUERYFRAMECOUNTNVPROC								wglQueryFrameCountNV;
	extern PFNWGLRESETFRAMECOUNTNVPROC								wglResetFrameCountNV;
	// WGL_NV_vertex_array_range
	extern PFNWGLALLOCATEMEMORYNVPROC								wglAllocateMemoryNV;
	extern PFNWGLFREEMEMORYNVPROC									wglFreeMemoryNV;
	// WGL_NV_video_capture
	extern PFNWGLBINDVIDEOCAPTUREDEVICENVPROC						wglBindVideoCaptureDeviceNV;
	extern PFNWGLENUMERATEVIDEOCAPTUREDEVICESNVPROC					wglEnumerateVideoCaptureDevicesNV;
	extern PFNWGLLOCKVIDEOCAPTUREDEVICENVPROC						wglLockVideoCaptureDeviceNV;
	extern PFNWGLQUERYVIDEOCAPTUREDEVICENVPROC						wglQueryVideoCaptureDeviceNV;
	extern PFNWGLRELEASEVIDEOCAPTUREDEVICENVPROC					wglReleaseVideoCaptureDeviceNV;
	// WGL_NV_video_output
	extern PFNWGLGETVIDEODEVICENVPROC								wglGetVideoDeviceNV;
	extern PFNWGLRELEASEVIDEODEVICENVPROC							wglReleaseVideoDeviceNV;
	extern PFNWGLBINDVIDEOIMAGENVPROC								wglBindVideoImageNV;
	extern PFNWGLRELEASEVIDEOIMAGENVPROC							wglReleaseVideoImageNV;
	extern PFNWGLSENDPBUFFERTOVIDEONVPROC							wglSendPbufferToVideoNV;
	extern PFNWGLGETVIDEOINFONVPROC									wglGetVideoInfoNV;
	// WGL_OML_sync_control
	extern PFNWGLGETSYNCVALUESOMLPROC								wglGetSyncValuesOML;
	extern PFNWGLGETMSCRATEOMLPROC									wglGetMscRateOML;
	extern PFNWGLSWAPBUFFERSMSCOMLPROC								wglSwapBuffersMscOML;
	extern PFNWGLSWAPLAYERBUFFERSMSCOMLPROC							wglSwapLayerBuffersMscOML;
	extern PFNWGLWAITFORMSCOMLPROC									wglWaitForMscOML;
	extern PFNWGLWAITFORSBCOMLPROC									wglWaitForSbcOML;
#endif

#if defined(__linux__) && !defined(__ANDROID__)
	// GLX_VERSION_1_3
	extern PFNGLXGETFBCONFIGSPROC									glXGetFBConfigs;
	extern PFNGLXCHOOSEFBCONFIGPROC									glXChooseFBConfig;
	extern PFNGLXGETFBCONFIGATTRIBPROC								glXGetFBConfigAttrib;
	extern PFNGLXGETVISUALFROMFBCONFIGPROC							glXGetVisualFromFBConfig;
	extern PFNGLXCREATEWINDOWPROC									glXCreateWindow;
	extern PFNGLXDESTROYWINDOWPROC									glXDestroyWindow;
	extern PFNGLXCREATEPIXMAPPROC									glXCreatePixmap;
	extern PFNGLXDESTROYPIXMAPPROC									glXDestroyPixmap;
	extern PFNGLXCREATEPBUFFERPROC									glXCreatePbuffer;
	extern PFNGLXDESTROYPBUFFERPROC									glXDestroyPbuffer;
	extern PFNGLXQUERYDRAWABLEPROC									glXQueryDrawable;
	extern PFNGLXCREATENEWCONTEXTPROC								glXCreateNewContext;
	extern PFNGLXMAKECONTEXTCURRENTPROC								glXMakeContextCurrent;
	extern PFNGLXGETCURRENTREADDRAWABLEPROC							glXGetCurrentReadDrawable;
	extern PFNGLXQUERYCONTEXTPROC									glXQueryContext;
	extern PFNGLXSELECTEVENTPROC									glXSelectEvent;
	extern PFNGLXGETSELECTEDEVENTPROC								glXGetSelectedEvent;
	// GLX_VERSION_1_4
	//extern PFNGLXGETPROCADDRESSPROC									glXGetProcAddress;
	// GLX_ARB_create_context
	extern PFNGLXCREATECONTEXTATTRIBSARBPROC						glXCreateContextAttribsARB;
	// GLX_ARB_get_proc_address
	//extern PFNGLXGETPROCADDRESSARBPROC								glXGetProcAddressARB;
	// GLX_AMD_gpu_association
	extern PFNGLXGETGPUIDSAMDPROC									glXGetGPUIDsAMD;
	extern PFNGLXGETGPUINFOAMDPROC									glXGetGPUInfoAMD;
	extern PFNGLXGETCONTEXTGPUIDAMDPROC								glXGetContextGPUIDAMD;
	extern PFNGLXCREATEASSOCIATEDCONTEXTAMDPROC						glXCreateAssociatedContextAMD;
	extern PFNGLXCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC				glXCreateAssociatedContextAttribsAMD;
	extern PFNGLXDELETEASSOCIATEDCONTEXTAMDPROC						glXDeleteAssociatedContextAMD;
	extern PFNGLXMAKEASSOCIATEDCONTEXTCURRENTAMDPROC				glXMakeAssociatedContextCurrentAMD;
	extern PFNGLXGETCURRENTASSOCIATEDCONTEXTAMDPROC					glXGetCurrentAssociatedContextAMD;
	extern PFNGLXBLITCONTEXTFRAMEBUFFERAMDPROC						glXBlitContextFramebufferAMD;
	// GLX_EXT_import_context
	extern PFNGLXGETCURRENTDISPLAYEXTPROC							glXGetCurrentDisplayEXT;
	extern PFNGLXQUERYCONTEXTINFOEXTPROC							glXQueryContextInfoEXT;
	extern PFNGLXGETCONTEXTIDEXTPROC								glXGetContextIDEXT;
	extern PFNGLXIMPORTCONTEXTEXTPROC								glXImportContextEXT;
	extern PFNGLXFREECONTEXTEXTPROC									glXFreeContextEXT;
	// GLX_EXT_swap_control
	extern PFNGLXSWAPINTERVALEXTPROC								glXSwapIntervalEXT;
	// GLX_EXT_texture_from_pixmap
	extern PFNGLXBINDTEXIMAGEEXTPROC								glXBindTexImageEXT;
	extern PFNGLXRELEASETEXIMAGEEXTPROC								glXReleaseTexImageEXT;
	// GLX_MESA_agp_offset
	extern PFNGLXGETAGPOFFSETMESAPROC								glXGetAGPOffsetMESA;
	// GLX_MESA_copy_sub_buffer
	extern PFNGLXCOPYSUBBUFFERMESAPROC								glXCopySubBufferMESA;
	// GLX_MESA_pixmap_colormap
	extern PFNGLXCREATEGLXPIXMAPMESAPROC							glXCreateGLXPixmapMESA;
	// GLX_MESA_query_renderer
	extern PFNGLXQUERYCURRENTRENDERERINTEGERMESAPROC				glXQueryCurrentRendererIntegerMESA;
	extern PFNGLXQUERYCURRENTRENDERERSTRINGMESAPROC					glXQueryCurrentRendererStringMESA;
	extern PFNGLXQUERYRENDERERINTEGERMESAPROC						glXQueryRendererIntegerMESA;
	extern PFNGLXQUERYRENDERERSTRINGMESAPROC						glXQueryRendererStringMESA;
	// GLX_MESA_release_buffers
	extern PFNGLXRELEASEBUFFERSMESAPROC								glXReleaseBuffersMESA;
	// GLX_MESA_set_3dfx_mode
	extern PFNGLXSET3DFXMODEMESAPROC								glXSet3DfxModeMESA;
	// GLX_MESA_swap_control
	extern PFNGLXGETSWAPINTERVALMESAPROC							glXGetSwapIntervalMESA;
	extern PFNGLXSWAPINTERVALMESAPROC								glXSwapIntervalMESA;
	// GLX_NV_copy_buffer
	extern PFNGLXCOPYBUFFERSUBDATANVPROC							glXCopyBufferSubDataNV;
	extern PFNGLXNAMEDCOPYBUFFERSUBDATANVPROC						glXNamedCopyBufferSubDataNV;
	// GLX_NV_copy_image
	extern PFNGLXCOPYIMAGESUBDATANVPROC								glXCopyImageSubDataNV;
	// GLX_NV_delay_before_swap
	extern PFNGLXDELAYBEFORESWAPNVPROC								glXDelayBeforeSwapNV;
	// GLX_NV_present_video
	extern PFNGLXENUMERATEVIDEODEVICESNVPROC						glXEnumerateVideoDevicesNV;
	extern PFNGLXBINDVIDEODEVICENVPROC								glXBindVideoDeviceNV;
	// GLX_NV_swap_group
	extern PFNGLXJOINSWAPGROUPNVPROC								glXJoinSwapGroupNV;
	extern PFNGLXBINDSWAPBARRIERNVPROC								glXBindSwapBarrierNV;
	extern PFNGLXQUERYSWAPGROUPNVPROC								glXQuerySwapGroupNV;
	extern PFNGLXQUERYMAXSWAPGROUPSNVPROC							glXQueryMaxSwapGroupsNV;
	extern PFNGLXQUERYFRAMECOUNTNVPROC								glXQueryFrameCountNV;
	extern PFNGLXRESETFRAMECOUNTNVPROC								glXResetFrameCountNV;
	// GLX_NV_video_capture
	extern PFNGLXBINDVIDEOCAPTUREDEVICENVPROC						glXBindVideoCaptureDeviceNV;
	extern PFNGLXENUMERATEVIDEOCAPTUREDEVICESNVPROC					glXEnumerateVideoCaptureDevicesNV;
	extern PFNGLXLOCKVIDEOCAPTUREDEVICENVPROC						glXLockVideoCaptureDeviceNV;
	extern PFNGLXQUERYVIDEOCAPTUREDEVICENVPROC						glXQueryVideoCaptureDeviceNV;
	extern PFNGLXRELEASEVIDEOCAPTUREDEVICENVPROC					glXReleaseVideoCaptureDeviceNV;
	// GLX_NV_video_out
	extern PFNGLXGETVIDEODEVICENVPROC								glXGetVideoDeviceNV;
	extern PFNGLXRELEASEVIDEODEVICENVPROC							glXReleaseVideoDeviceNV;
	extern PFNGLXBINDVIDEOIMAGENVPROC								glXBindVideoImageNV;
	extern PFNGLXRELEASEVIDEOIMAGENVPROC							glXReleaseVideoImageNV;
	extern PFNGLXSENDPBUFFERTOVIDEONVPROC							glXSendPbufferToVideoNV;
	extern PFNGLXGETVIDEOINFONVPROC									glXGetVideoInfoNV;
	// GLX_OML_sync_control
	extern PFNGLXGETSYNCVALUESOMLPROC								glXGetSyncValuesOML;
	extern PFNGLXGETMSCRATEOMLPROC									glXGetMscRateOML;
	extern PFNGLXSWAPBUFFERSMSCOMLPROC								glXSwapBuffersMscOML;
	extern PFNGLXWAITFORMSCOMLPROC									glXWaitForMscOML;
	extern PFNGLXWAITFORSBCOMLPROC									glXWaitForSbcOML;
	// GLX_SGIX_dmbuffer
	#ifdef _DM_BUFFER_H_
	extern PFNGLXASSOCIATEDMPBUFFERSGIXPROC							glXAssociateDMPbufferSGIX;
	#endif
	// GLX_SGIX_fbconfig
	extern PFNGLXGETFBCONFIGATTRIBSGIXPROC							glXGetFBConfigAttribSGIX;
	extern PFNGLXCHOOSEFBCONFIGSGIXPROC								glXChooseFBConfigSGIX;
	extern PFNGLXCREATEGLXPIXMAPWITHCONFIGSGIXPROC					glXCreateGLXPixmapWithConfigSGIX;
	extern PFNGLXCREATECONTEXTWITHCONFIGSGIXPROC					glXCreateContextWithConfigSGIX;
	extern PFNGLXGETVISUALFROMFBCONFIGSGIXPROC						glXGetVisualFromFBConfigSGIX;
	extern PFNGLXGETFBCONFIGFROMVISUALSGIXPROC						glXGetFBConfigFromVisualSGIX;
	// GLX_SGIX_hyperpipe
	extern PFNGLXQUERYHYPERPIPENETWORKSGIXPROC						glXQueryHyperpipeNetworkSGIX;
	extern PFNGLXHYPERPIPECONFIGSGIXPROC							glXHyperpipeConfigSGIX;
	extern PFNGLXQUERYHYPERPIPECONFIGSGIXPROC						glXQueryHyperpipeConfigSGIX;
	extern PFNGLXDESTROYHYPERPIPECONFIGSGIXPROC						glXDestroyHyperpipeConfigSGIX;
	extern PFNGLXBINDHYPERPIPESGIXPROC								glXBindHyperpipeSGIX;
	extern PFNGLXQUERYHYPERPIPEBESTATTRIBSGIXPROC					glXQueryHyperpipeBestAttribSGIX;
	extern PFNGLXHYPERPIPEATTRIBSGIXPROC							glXHyperpipeAttribSGIX;
	extern PFNGLXQUERYHYPERPIPEATTRIBSGIXPROC						glXQueryHyperpipeAttribSGIX;
	// GLX_SGIX_pbuffer
	extern PFNGLXCREATEGLXPBUFFERSGIXPROC							glXCreateGLXPbufferSGIX;
	extern PFNGLXDESTROYGLXPBUFFERSGIXPROC							glXDestroyGLXPbufferSGIX;
	extern PFNGLXQUERYGLXPBUFFERSGIXPROC							glXQueryGLXPbufferSGIX;
	extern PFNGLXSELECTEVENTSGIXPROC								glXSelectEventSGIX;
	extern PFNGLXGETSELECTEDEVENTSGIXPROC							glXGetSelectedEventSGIX;
	// GLX_SGIX_swap_barrier
	extern PFNGLXBINDSWAPBARRIERSGIXPROC							glXBindSwapBarrierSGIX;
	extern PFNGLXQUERYMAXSWAPBARRIERSSGIXPROC						glXQueryMaxSwapBarriersSGIX;
	// GLX_SGIX_swap_group
	extern PFNGLXJOINSWAPGROUPSGIXPROC								glXJoinSwapGroupSGIX;
	// GLX_SGIX_video_resize
	extern PFNGLXBINDCHANNELTOWINDOWSGIXPROC						glXBindChannelToWindowSGIX;
	extern PFNGLXCHANNELRECTSGIXPROC								glXChannelRectSGIX;
	extern PFNGLXQUERYCHANNELRECTSGIXPROC							glXQueryChannelRectSGIX;
	extern PFNGLXQUERYCHANNELDELTASSGIXPROC							glXQueryChannelDeltasSGIX;
	extern PFNGLXCHANNELRECTSYNCSGIXPROC							glXChannelRectSyncSGIX;
	// GLX_SGIX_video_source
	#ifdef _VL_H
	extern PFNGLXCREATEGLXVIDEOSOURCESGIXPROC						glXCreateGLXVideoSourceSGIX;
	extern PFNGLXDESTROYGLXVIDEOSOURCESGIXPROC						glXDestroyGLXVideoSourceSGIX;
	#endif
	// GLX_SGI_cushion
	extern PFNGLXCUSHIONSGIPROC										glXCushionSGI;
	// GLX_SGI_make_current_read
	extern PFNGLXMAKECURRENTREADSGIPROC								glXMakeCurrentReadSGI;
	extern PFNGLXGETCURRENTREADDRAWABLESGIPROC						glXGetCurrentReadDrawableSGI;
	// GLX_SGI_swap_control
	extern PFNGLXSWAPINTERVALSGIPROC								glXSwapIntervalSGI;
	// GLX_SGI_video_sync
	extern PFNGLXGETVIDEOSYNCSGIPROC								glXGetVideoSyncSGI;
	extern PFNGLXWAITVIDEOSYNCSGIPROC								glXWaitVideoSyncSGI;
	// GLX_SUN_get_transparent_index
	extern PFNGLXGETTRANSPARENTINDEXSUNPROC							glXGetTransparentIndexSUN;
#endif
#endif

	// Android
#ifdef __ANDROID__
	// 2.0
	extern PFNGLACTIVETEXTUREPROC									glActiveTexture;
	extern PFNGLATTACHSHADERPROC									glAttachShader;
	extern PFNGLBINDATTRIBLOCATIONPROC								glBindAttribLocation;
	extern PFNGLBINDBUFFERPROC										glBindBuffer;
	extern PFNGLBINDFRAMEBUFFERPROC									glBindFramebuffer;
	extern PFNGLBINDRENDERBUFFERPROC								glBindRenderbuffer;
	extern PFNGLBINDTEXTUREPROC										glBindTexture;
	extern PFNGLBLENDCOLORPROC										glBlendColor;
	extern PFNGLBLENDEQUATIONPROC									glBlendEquation;
	extern PFNGLBLENDEQUATIONSEPARATEPROC							glBlendEquationSeparate;
	extern PFNGLBLENDFUNCPROC										glBlendFunc;
	extern PFNGLBLENDFUNCSEPARATEPROC								glBlendFuncSeparate;
	extern PFNGLBUFFERDATAPROC										glBufferData;
	extern PFNGLBUFFERSUBDATAPROC									glBufferSubData;
	extern PFNGLCHECKFRAMEBUFFERSTATUSPROC							glCheckFramebufferStatus;
	extern PFNGLCLEARPROC											glClear;
	extern PFNGLCLEARCOLORPROC										glClearColor;
	extern PFNGLCLEARDEPTHFPROC										glClearDepthf;
	extern PFNGLCLEARSTENCILPROC									glClearStencil;
	extern PFNGLCOLORMASKPROC										glColorMask;
	extern PFNGLCOMPILESHADERPROC									glCompileShader;
	extern PFNGLCOMPRESSEDTEXIMAGE2DPROC							glCompressedTexImage2D;
	extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC							glCompressedTexSubImage2D;
	extern PFNGLCOPYTEXIMAGE2DPROC									glCopyTexImage2D;
	extern PFNGLCOPYTEXSUBIMAGE2DPROC								glCopyTexSubImage2D;
	extern PFNGLCREATEPROGRAMPROC									glCreateProgram;
	extern PFNGLCREATESHADERPROC									glCreateShader;
	extern PFNGLCULLFACEPROC										glCullFace;
	extern PFNGLDELETEBUFFERSPROC									glDeleteBuffers;
	extern PFNGLDELETEFRAMEBUFFERSPROC								glDeleteFramebuffers;
	extern PFNGLDELETEPROGRAMPROC									glDeleteProgram;
	extern PFNGLDELETERENDERBUFFERSPROC								glDeleteRenderbuffers;
	extern PFNGLDELETESHADERPROC									glDeleteShader;
	extern PFNGLDELETETEXTURESPROC									glDeleteTextures;
	extern PFNGLDEPTHFUNCPROC										glDepthFunc;
	extern PFNGLDEPTHMASKPROC										glDepthMask;
	extern PFNGLDEPTHRANGEFPROC										glDepthRangef;
	extern PFNGLDETACHSHADERPROC									glDetachShader;
	extern PFNGLDISABLEPROC											glDisable;
	extern PFNGLDISABLEVERTEXATTRIBARRAYPROC						glDisableVertexAttribArray;
	extern PFNGLDRAWARRAYSPROC										glDrawArrays;
	extern PFNGLDRAWELEMENTSPROC									glDrawElements;
	extern PFNGLENABLEPROC											glEnable;
	extern PFNGLENABLEVERTEXATTRIBARRAYPROC							glEnableVertexAttribArray;
	extern PFNGLFINISHPROC											glFinish;
	extern PFNGLFLUSHPROC											glFlush;
	extern PFNGLFRAMEBUFFERRENDERBUFFERPROC							glFramebufferRenderbuffer;
	extern PFNGLFRAMEBUFFERTEXTURE2DPROC							glFramebufferTexture2D;
	extern PFNGLFRONTFACEPROC										glFrontFace;
	extern PFNGLGENBUFFERSPROC										glGenBuffers;
	extern PFNGLGENERATEMIPMAPPROC									glGenerateMipmap;
	extern PFNGLGENFRAMEBUFFERSPROC									glGenFramebuffers;
	extern PFNGLGENRENDERBUFFERSPROC								glGenRenderbuffers;
	extern PFNGLGENTEXTURESPROC										glGenTextures;
	extern PFNGLGETACTIVEATTRIBPROC									glGetActiveAttrib;
	extern PFNGLGETACTIVEUNIFORMPROC								glGetActiveUniform;
	extern PFNGLGETATTACHEDSHADERSPROC								glGetAttachedShaders;
	extern PFNGLGETATTRIBLOCATIONPROC								glGetAttribLocation;
	extern PFNGLGETBOOLEANVPROC										glGetBooleanv;
	extern PFNGLGETBUFFERPARAMETERIVPROC							glGetBufferParameteriv;
	extern PFNGLGETERRORPROC										glGetError;
	extern PFNGLGETFLOATVPROC										glGetFloatv;
	extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC				glGetFramebufferAttachmentParameteriv;
	extern PFNGLGETINTEGERVPROC										glGetIntegerv;
	extern PFNGLGETPROGRAMIVPROC									glGetProgramiv;
	extern PFNGLGETPROGRAMINFOLOGPROC								glGetProgramInfoLog;
	extern PFNGLGETRENDERBUFFERPARAMETERIVPROC						glGetRenderbufferParameteriv;
	extern PFNGLGETSHADERIVPROC										glGetShaderiv;
	extern PFNGLGETSHADERINFOLOGPROC								glGetShaderInfoLog;
	extern PFNGLGETSHADERPRECISIONFORMATPROC						glGetShaderPrecisionFormat;
	extern PFNGLGETSHADERSOURCEPROC									glGetShaderSource;
	extern PFNGLGETSTRINGPROC										glGetString;
	extern PFNGLGETTEXPARAMETERFVPROC								glGetTexParameterfv;
	extern PFNGLGETTEXPARAMETERIVPROC								glGetTexParameteriv;
	extern PFNGLGETUNIFORMFVPROC									glGetUniformfv;
	extern PFNGLGETUNIFORMIVPROC									glGetUniformiv;
	extern PFNGLGETUNIFORMLOCATIONPROC								glGetUniformLocation;
	extern PFNGLGETVERTEXATTRIBFVPROC								glGetVertexAttribfv;
	extern PFNGLGETVERTEXATTRIBIVPROC								glGetVertexAttribiv;
	extern PFNGLGETVERTEXATTRIBPOINTERVPROC							glGetVertexAttribPointerv;
	extern PFNGLHINTPROC											glHint;
	extern PFNGLISBUFFERPROC										glIsBuffer;
	extern PFNGLISENABLEDPROC										glIsEnabled;
	extern PFNGLISFRAMEBUFFERPROC									glIsFramebuffer;
	extern PFNGLISPROGRAMPROC										glIsProgram;
	extern PFNGLISRENDERBUFFERPROC									glIsRenderbuffer;
	extern PFNGLISSHADERPROC										glIsShader;
	extern PFNGLISTEXTUREPROC										glIsTexture;
	extern PFNGLLINEWIDTHPROC										glLineWidth;
	extern PFNGLLINKPROGRAMPROC										glLinkProgram;
	extern PFNGLPIXELSTOREIPROC										glPixelStorei;
	extern PFNGLPOLYGONOFFSETPROC									glPolygonOffset;
	extern PFNGLREADPIXELSPROC										glReadPixels;
	extern PFNGLRELEASESHADERCOMPILERPROC							glReleaseShaderCompiler;
	extern PFNGLRENDERBUFFERSTORAGEPROC								glRenderbufferStorage;
	extern PFNGLSAMPLECOVERAGEPROC									glSampleCoverage;
	extern PFNGLSCISSORPROC											glScissor;
	extern PFNGLSHADERBINARYPROC									glShaderBinary;
	extern PFNGLSHADERSOURCEPROC									glShaderSource;
	extern PFNGLSTENCILFUNCPROC										glStencilFunc;
	extern PFNGLSTENCILFUNCSEPARATEPROC								glStencilFuncSeparate;
	extern PFNGLSTENCILMASKPROC										glStencilMask;
	extern PFNGLSTENCILMASKSEPARATEPROC								glStencilMaskSeparate;
	extern PFNGLSTENCILOPPROC										glStencilOp;
	extern PFNGLSTENCILOPSEPARATEPROC								glStencilOpSeparate;
	extern PFNGLTEXIMAGE2DPROC										glTexImage2D;
	extern PFNGLTEXPARAMETERFPROC									glTexParameterf;
	extern PFNGLTEXPARAMETERFVPROC									glTexParameterfv;
	extern PFNGLTEXPARAMETERIPROC									glTexParameteri;
	extern PFNGLTEXPARAMETERIVPROC									glTexParameteriv;
	extern PFNGLTEXSUBIMAGE2DPROC									glTexSubImage2D;
	extern PFNGLUNIFORM1FPROC										glUniform1f;
	extern PFNGLUNIFORM1FVPROC										glUniform1fv;
	extern PFNGLUNIFORM1IPROC										glUniform1i;
	extern PFNGLUNIFORM1IVPROC										glUniform1iv;
	extern PFNGLUNIFORM2FPROC										glUniform2f;
	extern PFNGLUNIFORM2FVPROC										glUniform2fv;
	extern PFNGLUNIFORM2IPROC										glUniform2i;
	extern PFNGLUNIFORM2IVPROC										glUniform2iv;
	extern PFNGLUNIFORM3FPROC										glUniform3f;
	extern PFNGLUNIFORM3FVPROC										glUniform3fv;
	extern PFNGLUNIFORM3IPROC										glUniform3i;
	extern PFNGLUNIFORM3IVPROC										glUniform3iv;
	extern PFNGLUNIFORM4FPROC										glUniform4f;
	extern PFNGLUNIFORM4FVPROC										glUniform4fv;
	extern PFNGLUNIFORM4IPROC										glUniform4i;
	extern PFNGLUNIFORM4IVPROC										glUniform4iv;
	extern PFNGLUNIFORMMATRIX2FVPROC								glUniformMatrix2fv;
	extern PFNGLUNIFORMMATRIX3FVPROC								glUniformMatrix3fv;
	extern PFNGLUNIFORMMATRIX4FVPROC								glUniformMatrix4fv;
	extern PFNGLUSEPROGRAMPROC										glUseProgram;
	extern PFNGLVALIDATEPROGRAMPROC									glValidateProgram;
	extern PFNGLVERTEXATTRIB1FPROC									glVertexAttrib1f;
	extern PFNGLVERTEXATTRIB1FVPROC									glVertexAttrib1fv;
	extern PFNGLVERTEXATTRIB2FPROC									glVertexAttrib2f;
	extern PFNGLVERTEXATTRIB2FVPROC									glVertexAttrib2fv;
	extern PFNGLVERTEXATTRIB3FPROC									glVertexAttrib3f;
	extern PFNGLVERTEXATTRIB3FVPROC									glVertexAttrib3fv;
	extern PFNGLVERTEXATTRIB4FPROC									glVertexAttrib4f;
	extern PFNGLVERTEXATTRIB4FVPROC									glVertexAttrib4fv;
	extern PFNGLVERTEXATTRIBPOINTERPROC								glVertexAttribPointer;
	extern PFNGLVIEWPORTPROC										glViewport;

	// 3.0
	extern PFNGLREADBUFFERPROC										glReadBuffer;
	extern PFNGLDRAWRANGEELEMENTSPROC								glDrawRangeElements;
	extern PFNGLTEXIMAGE3DPROC										glTexImage3D;
	extern PFNGLTEXSUBIMAGE3DPROC									glTexSubImage3D;
	extern PFNGLCOPYTEXSUBIMAGE3DPROC								glCopyTexSubImage3D;
	extern PFNGLCOMPRESSEDTEXIMAGE3DPROC							glCompressedTexImage3D;
	extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC							glCompressedTexSubImage3D;
	extern PFNGLGENQUERIESPROC										glGenQueries;
	extern PFNGLDELETEQUERIESPROC									glDeleteQueries;
	extern PFNGLISQUERYPROC											glIsQuery;
	extern PFNGLBEGINQUERYPROC										glBeginQuery;
	extern PFNGLENDQUERYPROC										glEndQuery;
	extern PFNGLGETQUERYIVPROC										glGetQueryiv;
	extern PFNGLGETQUERYOBJECTUIVPROC								glGetQueryObjectuiv;
	extern PFNGLUNMAPBUFFERPROC										glUnmapBuffer;
	extern PFNGLGETBUFFERPOINTERVPROC								glGetBufferPointerv;
	extern PFNGLDRAWBUFFERSPROC										glDrawBuffers;
	extern PFNGLUNIFORMMATRIX2X3FVPROC								glUniformMatrix2x3fv;
	extern PFNGLUNIFORMMATRIX3X2FVPROC								glUniformMatrix3x2fv;
	extern PFNGLUNIFORMMATRIX2X4FVPROC								glUniformMatrix2x4fv;
	extern PFNGLUNIFORMMATRIX4X2FVPROC								glUniformMatrix4x2fv;
	extern PFNGLUNIFORMMATRIX3X4FVPROC								glUniformMatrix3x4fv;
	extern PFNGLUNIFORMMATRIX4X3FVPROC								glUniformMatrix4x3fv;
	extern PFNGLBLITFRAMEBUFFERPROC									glBlitFramebuffer;
	extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC					glRenderbufferStorageMultisample;
	extern PFNGLFRAMEBUFFERTEXTURELAYERPROC							glFramebufferTextureLayer;
	extern PFNGLMAPBUFFERRANGEPROC									glMapBufferRange;
	extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC							glFlushMappedBufferRange;
	extern PFNGLBINDVERTEXARRAYPROC									glBindVertexArray;
	extern PFNGLDELETEVERTEXARRAYSPROC								glDeleteVertexArrays;
	extern PFNGLGENVERTEXARRAYSPROC									glGenVertexArrays;
	extern PFNGLISVERTEXARRAYPROC									glIsVertexArray;
	extern PFNGLGETINTEGERI_VPROC									glGetIntegeri_v;
	extern PFNGLBEGINTRANSFORMFEEDBACKPROC							glBeginTransformFeedback;
	extern PFNGLENDTRANSFORMFEEDBACKPROC							glEndTransformFeedback;
	extern PFNGLBINDBUFFERRANGEPROC									glBindBufferRange;
	extern PFNGLBINDBUFFERBASEPROC									glBindBufferBase;
	extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC						glTransformFeedbackVaryings;
	extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC						glGetTransformFeedbackVarying;
	extern PFNGLVERTEXATTRIBIPOINTERPROC							glVertexAttribIPointer;
	extern PFNGLGETVERTEXATTRIBIIVPROC								glGetVertexAttribIiv;
	extern PFNGLGETVERTEXATTRIBIUIVPROC								glGetVertexAttribIuiv;
	extern PFNGLVERTEXATTRIBI4IPROC									glVertexAttribI4i;
	extern PFNGLVERTEXATTRIBI4UIPROC								glVertexAttribI4ui;
	extern PFNGLVERTEXATTRIBI4IVPROC								glVertexAttribI4iv;
	extern PFNGLVERTEXATTRIBI4UIVPROC								glVertexAttribI4uiv;
	extern PFNGLGETUNIFORMUIVPROC									glGetUniformuiv;
	extern PFNGLGETFRAGDATALOCATIONPROC								glGetFragDataLocation;
	extern PFNGLUNIFORM1UIPROC										glUniform1ui;
	extern PFNGLUNIFORM2UIPROC										glUniform2ui;
	extern PFNGLUNIFORM3UIPROC										glUniform3ui;
	extern PFNGLUNIFORM4UIPROC										glUniform4ui;
	extern PFNGLUNIFORM1UIVPROC										glUniform1uiv;
	extern PFNGLUNIFORM2UIVPROC										glUniform2uiv;
	extern PFNGLUNIFORM3UIVPROC										glUniform3uiv;
	extern PFNGLUNIFORM4UIVPROC										glUniform4uiv;
	extern PFNGLCLEARBUFFERIVPROC									glClearBufferiv;
	extern PFNGLCLEARBUFFERUIVPROC									glClearBufferuiv;
	extern PFNGLCLEARBUFFERFVPROC									glClearBufferfv;
	extern PFNGLCLEARBUFFERFIPROC									glClearBufferfi;
	extern PFNGLGETSTRINGIPROC										glGetStringi;
	extern PFNGLCOPYBUFFERSUBDATAPROC								glCopyBufferSubData;
	extern PFNGLGETUNIFORMINDICESPROC								glGetUniformIndices;
	extern PFNGLGETACTIVEUNIFORMSIVPROC								glGetActiveUniformsiv;
	extern PFNGLGETUNIFORMBLOCKINDEXPROC							glGetUniformBlockIndex;
	extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC							glGetActiveUniformBlockiv;
	extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC						glGetActiveUniformBlockName;
	extern PFNGLUNIFORMBLOCKBINDINGPROC								glUniformBlockBinding;
	extern PFNGLDRAWARRAYSINSTANCEDPROC								glDrawArraysInstanced;
	extern PFNGLDRAWELEMENTSINSTANCEDPROC							glDrawElementsInstanced;
	extern PFNGLFENCESYNCPROC										glFenceSync;
	extern PFNGLISSYNCPROC											glIsSync;
	extern PFNGLDELETESYNCPROC										glDeleteSync;
	extern PFNGLCLIENTWAITSYNCPROC									glClientWaitSync;
	extern PFNGLWAITSYNCPROC										glWaitSync;
	extern PFNGLGETINTEGER64VPROC									glGetInteger64v;
	extern PFNGLGETSYNCIVPROC										glGetSynciv;
	extern PFNGLGETINTEGER64I_VPROC									glGetInteger64i_v;
	extern PFNGLGETBUFFERPARAMETERI64VPROC							glGetBufferParameteri64v;
	extern PFNGLGENSAMPLERSPROC										glGenSamplers;
	extern PFNGLDELETESAMPLERSPROC									glDeleteSamplers;
	extern PFNGLISSAMPLERPROC										glIsSampler;
	extern PFNGLBINDSAMPLERPROC										glBindSampler;
	extern PFNGLSAMPLERPARAMETERIPROC								glSamplerParameteri;
	extern PFNGLSAMPLERPARAMETERIVPROC								glSamplerParameteriv;
	extern PFNGLSAMPLERPARAMETERFPROC								glSamplerParameterf;
	extern PFNGLSAMPLERPARAMETERFVPROC								glSamplerParameterfv;
	extern PFNGLGETSAMPLERPARAMETERIVPROC							glGetSamplerParameteriv;
	extern PFNGLGETSAMPLERPARAMETERFVPROC							glGetSamplerParameterfv;
	extern PFNGLVERTEXATTRIBDIVISORPROC								glVertexAttribDivisor;
	extern PFNGLBINDTRANSFORMFEEDBACKPROC							glBindTransformFeedback;
	extern PFNGLDELETETRANSFORMFEEDBACKSPROC						glDeleteTransformFeedbacks;
	extern PFNGLGENTRANSFORMFEEDBACKSPROC							glGenTransformFeedbacks;
	extern PFNGLISTRANSFORMFEEDBACKPROC								glIsTransformFeedback;
	extern PFNGLPAUSETRANSFORMFEEDBACKPROC							glPauseTransformFeedback;
	extern PFNGLRESUMETRANSFORMFEEDBACKPROC							glResumeTransformFeedback;
	extern PFNGLGETPROGRAMBINARYPROC								glGetProgramBinary;
	extern PFNGLPROGRAMBINARYPROC									glProgramBinary;
	extern PFNGLPROGRAMPARAMETERIPROC								glProgramParameteri;
	extern PFNGLINVALIDATEFRAMEBUFFERPROC							glInvalidateFramebuffer;
	extern PFNGLINVALIDATESUBFRAMEBUFFERPROC						glInvalidateSubFramebuffer;
	extern PFNGLTEXSTORAGE2DPROC									glTexStorage2D;
	extern PFNGLTEXSTORAGE3DPROC									glTexStorage3D;
	extern PFNGLGETINTERNALFORMATIVPROC								glGetInternalformativ;

	// 3.1
	extern PFNGLDISPATCHCOMPUTEPROC									glDispatchCompute;
	extern PFNGLDISPATCHCOMPUTEINDIRECTPROC							glDispatchComputeIndirect;
	extern PFNGLDRAWARRAYSINDIRECTPROC								glDrawArraysIndirect;
	extern PFNGLDRAWELEMENTSINDIRECTPROC							glDrawElementsIndirect;
	extern PFNGLFRAMEBUFFERPARAMETERIPROC							glFramebufferParameteri;
	extern PFNGLGETFRAMEBUFFERPARAMETERIVPROC						glGetFramebufferParameteriv;
	extern PFNGLGETPROGRAMINTERFACEIVPROC							glGetProgramInterfaceiv;
	extern PFNGLGETPROGRAMRESOURCEINDEXPROC							glGetProgramResourceIndex;
	extern PFNGLGETPROGRAMRESOURCENAMEPROC							glGetProgramResourceName;
	extern PFNGLGETPROGRAMRESOURCEIVPROC							glGetProgramResourceiv;
	extern PFNGLGETPROGRAMRESOURCELOCATIONPROC						glGetProgramResourceLocation;
	extern PFNGLUSEPROGRAMSTAGESPROC								glUseProgramStages;
	extern PFNGLACTIVESHADERPROGRAMPROC								glActiveShaderProgram;
	extern PFNGLCREATESHADERPROGRAMVPROC							glCreateShaderProgramv;
	extern PFNGLBINDPROGRAMPIPELINEPROC								glBindProgramPipeline;
	extern PFNGLDELETEPROGRAMPIPELINESPROC							glDeleteProgramPipelines;
	extern PFNGLGENPROGRAMPIPELINESPROC								glGenProgramPipelines;
	extern PFNGLISPROGRAMPIPELINEPROC								glIsProgramPipeline;
	extern PFNGLGETPROGRAMPIPELINEIVPROC							glGetProgramPipelineiv;
	extern PFNGLPROGRAMUNIFORM1IPROC								glProgramUniform1i;
	extern PFNGLPROGRAMUNIFORM2IPROC								glProgramUniform2i;
	extern PFNGLPROGRAMUNIFORM3IPROC								glProgramUniform3i;
	extern PFNGLPROGRAMUNIFORM4IPROC								glProgramUniform4i;
	extern PFNGLPROGRAMUNIFORM1UIPROC								glProgramUniform1ui;
	extern PFNGLPROGRAMUNIFORM2UIPROC								glProgramUniform2ui;
	extern PFNGLPROGRAMUNIFORM3UIPROC								glProgramUniform3ui;
	extern PFNGLPROGRAMUNIFORM4UIPROC								glProgramUniform4ui;
	extern PFNGLPROGRAMUNIFORM1FPROC								glProgramUniform1f;
	extern PFNGLPROGRAMUNIFORM2FPROC								glProgramUniform2f;
	extern PFNGLPROGRAMUNIFORM3FPROC								glProgramUniform3f;
	extern PFNGLPROGRAMUNIFORM4FPROC								glProgramUniform4f;
	extern PFNGLPROGRAMUNIFORM1IVPROC								glProgramUniform1iv;
	extern PFNGLPROGRAMUNIFORM2IVPROC								glProgramUniform2iv;
	extern PFNGLPROGRAMUNIFORM3IVPROC								glProgramUniform3iv;
	extern PFNGLPROGRAMUNIFORM4IVPROC								glProgramUniform4iv;
	extern PFNGLPROGRAMUNIFORM1UIVPROC								glProgramUniform1uiv;
	extern PFNGLPROGRAMUNIFORM2UIVPROC								glProgramUniform2uiv;
	extern PFNGLPROGRAMUNIFORM3UIVPROC								glProgramUniform3uiv;
	extern PFNGLPROGRAMUNIFORM4UIVPROC								glProgramUniform4uiv;
	extern PFNGLPROGRAMUNIFORM1FVPROC								glProgramUniform1fv;
	extern PFNGLPROGRAMUNIFORM2FVPROC								glProgramUniform2fv;
	extern PFNGLPROGRAMUNIFORM3FVPROC								glProgramUniform3fv;
	extern PFNGLPROGRAMUNIFORM4FVPROC								glProgramUniform4fv;
	extern PFNGLPROGRAMUNIFORMMATRIX2FVPROC							glProgramUniformMatrix2fv;
	extern PFNGLPROGRAMUNIFORMMATRIX3FVPROC							glProgramUniformMatrix3fv;
	extern PFNGLPROGRAMUNIFORMMATRIX4FVPROC							glProgramUniformMatrix4fv;
	extern PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC						glProgramUniformMatrix2x3fv;
	extern PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC						glProgramUniformMatrix3x2fv;
	extern PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC						glProgramUniformMatrix2x4fv;
	extern PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC						glProgramUniformMatrix4x2fv;
	extern PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC						glProgramUniformMatrix3x4fv;
	extern PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC						glProgramUniformMatrix4x3fv;
	extern PFNGLVALIDATEPROGRAMPIPELINEPROC							glValidateProgramPipeline;
	extern PFNGLGETPROGRAMPIPELINEINFOLOGPROC						glGetProgramPipelineInfoLog;
	extern PFNGLBINDIMAGETEXTUREPROC								glBindImageTexture;
	extern PFNGLGETBOOLEANI_VPROC									glGetBooleani_v;
	extern PFNGLMEMORYBARRIERPROC									glMemoryBarrier;
	extern PFNGLMEMORYBARRIERBYREGIONPROC							glMemoryBarrierByRegion;
	extern PFNGLTEXSTORAGE2DMULTISAMPLEPROC							glTexStorage2DMultisample;
	extern PFNGLGETMULTISAMPLEFVPROC								glGetMultisamplefv;
	extern PFNGLSAMPLEMASKIPROC										glSampleMaski;
	extern PFNGLGETTEXLEVELPARAMETERIVPROC							glGetTexLevelParameteriv;
	extern PFNGLGETTEXLEVELPARAMETERFVPROC							glGetTexLevelParameterfv;
	extern PFNGLBINDVERTEXBUFFERPROC								glBindVertexBuffer;
	extern PFNGLVERTEXATTRIBFORMATPROC								glVertexAttribFormat;
	extern PFNGLVERTEXATTRIBIFORMATPROC								glVertexAttribIFormat;
	extern PFNGLVERTEXATTRIBBINDINGPROC								glVertexAttribBinding;
	extern PFNGLVERTEXBINDINGDIVISORPROC							glVertexBindingDivisor;

	// 3.2
	extern PFNGLBLENDBARRIERPROC									glBlendBarrier;
	extern PFNGLCOPYIMAGESUBDATAPROC								glCopyImageSubData;
	extern PFNGLDEBUGMESSAGECONTROLPROC								glDebugMessageControl;
	extern PFNGLDEBUGMESSAGEINSERTPROC								glDebugMessageInsert;
	extern PFNGLDEBUGMESSAGECALLBACKPROC							glDebugMessageCallback;
	extern PFNGLGETDEBUGMESSAGELOGPROC								glGetDebugMessageLog;
	extern PFNGLPUSHDEBUGGROUPPROC									glPushDebugGroup;
	extern PFNGLPOPDEBUGGROUPPROC									glPopDebugGroup;
	extern PFNGLOBJECTLABELPROC										glObjectLabel;
	extern PFNGLGETOBJECTLABELPROC									glGetObjectLabel;
	extern PFNGLOBJECTPTRLABELPROC									glObjectPtrLabel;
	extern PFNGLGETOBJECTPTRLABELPROC								glGetObjectPtrLabel;
	extern PFNGLGETPOINTERVPROC										glGetPointerv;
	extern PFNGLENABLEIPROC											glEnablei;
	extern PFNGLDISABLEIPROC										glDisablei;
	extern PFNGLBLENDEQUATIONIPROC									glBlendEquationi;
	extern PFNGLBLENDEQUATIONSEPARATEIPROC							glBlendEquationSeparatei;
	extern PFNGLBLENDFUNCIPROC										glBlendFunci;
	extern PFNGLBLENDFUNCSEPARATEIPROC								glBlendFuncSeparatei;
	extern PFNGLCOLORMASKIPROC										glColorMaski;
	extern PFNGLISENABLEDIPROC										glIsEnabledi;
	extern PFNGLDRAWELEMENTSBASEVERTEXPROC							glDrawElementsBaseVertex;
	extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC						glDrawRangeElementsBaseVertex;
	extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC					glDrawElementsInstancedBaseVertex;
	extern PFNGLFRAMEBUFFERTEXTUREPROC								glFramebufferTexture;
	extern PFNGLPRIMITIVEBOUNDINGBOXPROC							glPrimitiveBoundingBox;
	extern PFNGLGETGRAPHICSRESETSTATUSPROC							glGetGraphicsResetStatus;
	extern PFNGLREADNPIXELSPROC										glReadnPixels;
	extern PFNGLGETNUNIFORMFVPROC									glGetnUniformfv;
	extern PFNGLGETNUNIFORMIVPROC									glGetnUniformiv;
	extern PFNGLGETNUNIFORMUIVPROC									glGetnUniformuiv;
	extern PFNGLMINSAMPLESHADINGPROC								glMinSampleShading;
	extern PFNGLPATCHPARAMETERIPROC									glPatchParameteri;
	extern PFNGLTEXPARAMETERIIVPROC									glTexParameterIiv;
	extern PFNGLTEXPARAMETERIUIVPROC								glTexParameterIuiv;
	extern PFNGLGETTEXPARAMETERIIVPROC								glGetTexParameterIiv;
	extern PFNGLGETTEXPARAMETERIUIVPROC								glGetTexParameterIuiv;
	extern PFNGLSAMPLERPARAMETERIIVPROC								glSamplerParameterIiv;
	extern PFNGLSAMPLERPARAMETERIUIVPROC							glSamplerParameterIuiv;
	extern PFNGLGETSAMPLERPARAMETERIIVPROC							glGetSamplerParameterIiv;
	extern PFNGLGETSAMPLERPARAMETERIUIVPROC							glGetSamplerParameterIuiv;
	extern PFNGLTEXBUFFERPROC										glTexBuffer;
	extern PFNGLTEXBUFFERRANGEPROC									glTexBufferRange;
	extern PFNGLTEXSTORAGE3DMULTISAMPLEPROC							glTexStorage3DMultisample;
#endif

	bool load(nitisa::Version2 *version = nullptr, PlatformData *pd = nullptr);
	bool loaded(nitisa::Version2 *version = nullptr);
	void unload();

#ifdef GL_VERSION_4_3
	void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
#elif defined(GL_ES_VERSION_3_2)
	void GL_APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
#endif
#if defined(_WIN32) || (defined(__linux__) && !defined(__ANDROID__))
	void PrintProgramUniforms(GLuint program);
#endif
}