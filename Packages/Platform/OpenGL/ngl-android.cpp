// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef __ANDROID__
#include "ngl.h"

namespace ngl
{
	bool Loaded{ false };
	bool LoadResult{ false };
	nitisa::Version2 Version;

	void LoadProcedures()
	{
		// 2.0
		glActiveTexture = ::glActiveTexture;
		glAttachShader = ::glAttachShader;
		glBindAttribLocation = ::glBindAttribLocation;
		glBindBuffer = ::glBindBuffer;
		glBindFramebuffer = ::glBindFramebuffer;
		glBindRenderbuffer = ::glBindRenderbuffer;
		glBindTexture = ::glBindTexture;
		glBlendColor = ::glBlendColor;
		glBlendEquation = ::glBlendEquation;
		glBlendEquationSeparate = ::glBlendEquationSeparate;
		glBlendFunc = ::glBlendFunc;
		glBlendFuncSeparate = ::glBlendFuncSeparate;
		glBufferData = ::glBufferData;
		glBufferSubData = ::glBufferSubData;
		glCheckFramebufferStatus = ::glCheckFramebufferStatus;
		glClear = ::glClear;
		glClearColor = ::glClearColor;
		glClearDepthf = ::glClearDepthf;
		glClearStencil = ::glClearStencil;
		glColorMask = ::glColorMask;
		glCompileShader = ::glCompileShader;
		glCompressedTexImage2D = ::glCompressedTexImage2D;
		glCompressedTexSubImage2D = ::glCompressedTexSubImage2D;
		glCopyTexImage2D = ::glCopyTexImage2D;
		glCopyTexSubImage2D = ::glCopyTexSubImage2D;
		glCreateProgram = ::glCreateProgram;
		glCreateShader = ::glCreateShader;
		glCullFace = ::glCullFace;
		glDeleteBuffers = ::glDeleteBuffers;
		glDeleteFramebuffers = ::glDeleteFramebuffers;
		glDeleteProgram = ::glDeleteProgram;
		glDeleteRenderbuffers = ::glDeleteRenderbuffers;
		glDeleteShader = ::glDeleteShader;
		glDeleteTextures = ::glDeleteTextures;
		glDepthFunc = ::glDepthFunc;
		glDepthMask = ::glDepthMask;
		glDepthRangef = ::glDepthRangef;
		glDetachShader = ::glDetachShader;
		glDisable = ::glDisable;
		glDisableVertexAttribArray = ::glDisableVertexAttribArray;
		glDrawArrays = ::glDrawArrays;
		glDrawElements = ::glDrawElements;
		glEnable = ::glEnable;
		glEnableVertexAttribArray = ::glEnableVertexAttribArray;
		glFinish = ::glFinish;
		glFlush = ::glFlush;
		glFramebufferRenderbuffer = ::glFramebufferRenderbuffer;
		glFramebufferTexture2D = ::glFramebufferTexture2D;
		glFrontFace = ::glFrontFace;
		glGenBuffers = ::glGenBuffers;
		glGenerateMipmap = ::glGenerateMipmap;
		glGenFramebuffers = ::glGenFramebuffers;
		glGenRenderbuffers = ::glGenRenderbuffers;
		glGenTextures = ::glGenTextures;
		glGetActiveAttrib = ::glGetActiveAttrib;
		glGetActiveUniform = ::glGetActiveUniform;
		glGetAttachedShaders = ::glGetAttachedShaders;
		glGetAttribLocation = ::glGetAttribLocation;
		glGetBooleanv = ::glGetBooleanv;
		glGetBufferParameteriv = ::glGetBufferParameteriv;
		glGetError = ::glGetError;
		glGetFloatv = ::glGetFloatv;
		glGetFramebufferAttachmentParameteriv = ::glGetFramebufferAttachmentParameteriv;
		glGetIntegerv = ::glGetIntegerv;
		glGetProgramiv = ::glGetProgramiv;
		glGetProgramInfoLog = ::glGetProgramInfoLog;
		glGetRenderbufferParameteriv = ::glGetRenderbufferParameteriv;
		glGetShaderiv = ::glGetShaderiv;
		glGetShaderInfoLog = ::glGetShaderInfoLog;
		glGetShaderPrecisionFormat = ::glGetShaderPrecisionFormat;
		glGetShaderSource = ::glGetShaderSource;
		glGetString = ::glGetString;
		glGetTexParameterfv = ::glGetTexParameterfv;
		glGetTexParameteriv = ::glGetTexParameteriv;
		glGetUniformfv = ::glGetUniformfv;
		glGetUniformiv = ::glGetUniformiv;
		glGetUniformLocation = ::glGetUniformLocation;
		glGetVertexAttribfv = ::glGetVertexAttribfv;
		glGetVertexAttribiv = ::glGetVertexAttribiv;
		glGetVertexAttribPointerv = ::glGetVertexAttribPointerv;
		glHint = ::glHint;
		glIsBuffer = ::glIsBuffer;
		glIsEnabled = ::glIsEnabled;
		glIsFramebuffer = ::glIsFramebuffer;
		glIsProgram = ::glIsProgram;
		glIsRenderbuffer = ::glIsRenderbuffer;
		glIsShader = ::glIsShader;
		glIsTexture = ::glIsTexture;
		glLineWidth = ::glLineWidth;
		glLinkProgram = ::glLinkProgram;
		glPixelStorei = ::glPixelStorei;
		glPolygonOffset = ::glPolygonOffset;
		glReadPixels = ::glReadPixels;
		glReleaseShaderCompiler = ::glReleaseShaderCompiler;
		glRenderbufferStorage = ::glRenderbufferStorage;
		glSampleCoverage = ::glSampleCoverage;
		glScissor = ::glScissor;
		glShaderBinary = ::glShaderBinary;
		glShaderSource = ::glShaderSource;
		glStencilFunc = ::glStencilFunc;
		glStencilFuncSeparate = ::glStencilFuncSeparate;
		glStencilMask = ::glStencilMask;
		glStencilMaskSeparate = ::glStencilMaskSeparate;
		glStencilOp = ::glStencilOp;
		glStencilOpSeparate = ::glStencilOpSeparate;
		glTexImage2D = ::glTexImage2D;
		glTexParameterf = ::glTexParameterf;
		glTexParameterfv = ::glTexParameterfv;
		glTexParameteri = ::glTexParameteri;
		glTexParameteriv = ::glTexParameteriv;
		glTexSubImage2D = ::glTexSubImage2D;
		glUniform1f = ::glUniform1f;
		glUniform1fv = ::glUniform1fv;
		glUniform1i = ::glUniform1i;
		glUniform1iv = ::glUniform1iv;
		glUniform2f = ::glUniform2f;
		glUniform2fv = ::glUniform2fv;
		glUniform2i = ::glUniform2i;
		glUniform2iv = ::glUniform2iv;
		glUniform3f = ::glUniform3f;
		glUniform3fv = ::glUniform3fv;
		glUniform3i = ::glUniform3i;
		glUniform3iv = ::glUniform3iv;
		glUniform4f = ::glUniform4f;
		glUniform4fv = ::glUniform4fv;
		glUniform4i = ::glUniform4i;
		glUniform4iv = ::glUniform4iv;
		glUniformMatrix2fv = ::glUniformMatrix2fv;
		glUniformMatrix3fv = ::glUniformMatrix3fv;
		glUniformMatrix4fv = ::glUniformMatrix4fv;
		glUseProgram = ::glUseProgram;
		glValidateProgram = ::glValidateProgram;
		glVertexAttrib1f = ::glVertexAttrib1f;
		glVertexAttrib1fv = ::glVertexAttrib1fv;
		glVertexAttrib2f = ::glVertexAttrib2f;
		glVertexAttrib2fv = ::glVertexAttrib2fv;
		glVertexAttrib3f = ::glVertexAttrib3f;
		glVertexAttrib3fv = ::glVertexAttrib3fv;
		glVertexAttrib4f = ::glVertexAttrib4f;
		glVertexAttrib4fv = ::glVertexAttrib4fv;
		glVertexAttribPointer = ::glVertexAttribPointer;
		glViewport = ::glViewport;
	
		// 3.0
		glReadBuffer = ::glReadBuffer;
		glDrawRangeElements = ::glDrawRangeElements;
		glTexImage3D = ::glTexImage3D;
		glTexSubImage3D = ::glTexSubImage3D;
		glCopyTexSubImage3D = ::glCopyTexSubImage3D;
		glCompressedTexImage3D = ::glCompressedTexImage3D;
		glCompressedTexSubImage3D = ::glCompressedTexSubImage3D;
		glGenQueries = ::glGenQueries;
		glDeleteQueries = ::glDeleteQueries;
		glIsQuery = ::glIsQuery;
		glBeginQuery = ::glBeginQuery;
		glEndQuery = ::glEndQuery;
		glGetQueryiv = ::glGetQueryiv;
		glGetQueryObjectuiv = ::glGetQueryObjectuiv;
		glUnmapBuffer = ::glUnmapBuffer;
		glGetBufferPointerv = ::glGetBufferPointerv;
		glDrawBuffers = ::glDrawBuffers;
		glUniformMatrix2x3fv = ::glUniformMatrix2x3fv;
		glUniformMatrix3x2fv = ::glUniformMatrix3x2fv;
		glUniformMatrix2x4fv = ::glUniformMatrix2x4fv;
		glUniformMatrix4x2fv = ::glUniformMatrix4x2fv;
		glUniformMatrix3x4fv = ::glUniformMatrix3x4fv;
		glUniformMatrix4x3fv = ::glUniformMatrix4x3fv;
		glBlitFramebuffer = ::glBlitFramebuffer;
		glRenderbufferStorageMultisample = ::glRenderbufferStorageMultisample;
		glFramebufferTextureLayer = ::glFramebufferTextureLayer;
		glMapBufferRange = ::glMapBufferRange;
		glFlushMappedBufferRange = ::glFlushMappedBufferRange;
		glBindVertexArray = ::glBindVertexArray;
		glDeleteVertexArrays = ::glDeleteVertexArrays;
		glGenVertexArrays = ::glGenVertexArrays;
		glIsVertexArray = ::glIsVertexArray;
		glGetIntegeri_v = ::glGetIntegeri_v;
		glBeginTransformFeedback = ::glBeginTransformFeedback;
		glEndTransformFeedback = ::glEndTransformFeedback;
		glBindBufferRange = ::glBindBufferRange;
		glBindBufferBase = ::glBindBufferBase;
		glTransformFeedbackVaryings = ::glTransformFeedbackVaryings;
		glGetTransformFeedbackVarying = ::glGetTransformFeedbackVarying;
		glVertexAttribIPointer = ::glVertexAttribIPointer;
		glGetVertexAttribIiv = ::glGetVertexAttribIiv;
		glGetVertexAttribIuiv = ::glGetVertexAttribIuiv;
		glVertexAttribI4i = ::glVertexAttribI4i;
		glVertexAttribI4ui = ::glVertexAttribI4ui;
		glVertexAttribI4iv = ::glVertexAttribI4iv;
		glVertexAttribI4uiv = ::glVertexAttribI4uiv;
		glGetUniformuiv = ::glGetUniformuiv;
		glGetFragDataLocation = ::glGetFragDataLocation;
		glUniform1ui = ::glUniform1ui;
		glUniform2ui = ::glUniform2ui;
		glUniform3ui = ::glUniform3ui;
		glUniform4ui = ::glUniform4ui;
		glUniform1uiv = ::glUniform1uiv;
		glUniform2uiv = ::glUniform2uiv;
		glUniform3uiv = ::glUniform3uiv;
		glUniform4uiv = ::glUniform4uiv;
		glClearBufferiv = ::glClearBufferiv;
		glClearBufferuiv = ::glClearBufferuiv;
		glClearBufferfv = ::glClearBufferfv;
		glClearBufferfi = ::glClearBufferfi;
		glGetStringi = ::glGetStringi;
		glCopyBufferSubData = ::glCopyBufferSubData;
		glGetUniformIndices = ::glGetUniformIndices;
		glGetActiveUniformsiv = ::glGetActiveUniformsiv;
		glGetUniformBlockIndex = ::glGetUniformBlockIndex;
		glGetActiveUniformBlockiv = ::glGetActiveUniformBlockiv;
		glGetActiveUniformBlockName = ::glGetActiveUniformBlockName;
		glUniformBlockBinding = ::glUniformBlockBinding;
		glDrawArraysInstanced = ::glDrawArraysInstanced;
		glDrawElementsInstanced = ::glDrawElementsInstanced;
		glFenceSync = ::glFenceSync;
		glIsSync = ::glIsSync;
		glDeleteSync = ::glDeleteSync;
		glClientWaitSync = ::glClientWaitSync;
		glWaitSync = ::glWaitSync;
		glGetInteger64v = ::glGetInteger64v;
		glGetSynciv = ::glGetSynciv;
		glGetInteger64i_v = ::glGetInteger64i_v;
		glGetBufferParameteri64v = ::glGetBufferParameteri64v;
		glGenSamplers = ::glGenSamplers;
		glDeleteSamplers = ::glDeleteSamplers;
		glIsSampler = ::glIsSampler;
		glBindSampler = ::glBindSampler;
		glSamplerParameteri = ::glSamplerParameteri;
		glSamplerParameteriv = ::glSamplerParameteriv;
		glSamplerParameterf = ::glSamplerParameterf;
		glSamplerParameterfv = ::glSamplerParameterfv;
		glGetSamplerParameteriv = ::glGetSamplerParameteriv;
		glGetSamplerParameterfv = ::glGetSamplerParameterfv;
		glVertexAttribDivisor = ::glVertexAttribDivisor;
		glBindTransformFeedback = ::glBindTransformFeedback;
		glDeleteTransformFeedbacks = ::glDeleteTransformFeedbacks;
		glGenTransformFeedbacks = ::glGenTransformFeedbacks;
		glIsTransformFeedback = ::glIsTransformFeedback;
		glPauseTransformFeedback = ::glPauseTransformFeedback;
		glResumeTransformFeedback = ::glResumeTransformFeedback;
		glGetProgramBinary = ::glGetProgramBinary;
		glProgramBinary = ::glProgramBinary;
		glProgramParameteri = ::glProgramParameteri;
		glInvalidateFramebuffer = ::glInvalidateFramebuffer;
		glInvalidateSubFramebuffer = ::glInvalidateSubFramebuffer;
		glTexStorage2D = ::glTexStorage2D;
		glTexStorage3D = ::glTexStorage3D;
		glGetInternalformativ = ::glGetInternalformativ;

		// 3.1
		glDispatchCompute = ::glDispatchCompute;
		glDispatchComputeIndirect = ::glDispatchComputeIndirect;
		glDrawArraysIndirect = ::glDrawArraysIndirect;
		glDrawElementsIndirect = ::glDrawElementsIndirect;
		glFramebufferParameteri = ::glFramebufferParameteri;
		glGetFramebufferParameteriv = ::glGetFramebufferParameteriv;
		glGetProgramInterfaceiv = ::glGetProgramInterfaceiv;
		glGetProgramResourceIndex = ::glGetProgramResourceIndex;
		glGetProgramResourceName = ::glGetProgramResourceName;
		glGetProgramResourceiv = ::glGetProgramResourceiv;
		glGetProgramResourceLocation = ::glGetProgramResourceLocation;
		glUseProgramStages = ::glUseProgramStages;
		glActiveShaderProgram = ::glActiveShaderProgram;
		glCreateShaderProgramv = ::glCreateShaderProgramv;
		glBindProgramPipeline = ::glBindProgramPipeline;
		glDeleteProgramPipelines = ::glDeleteProgramPipelines;
		glGenProgramPipelines = ::glGenProgramPipelines;
		glIsProgramPipeline = ::glIsProgramPipeline;
		glGetProgramPipelineiv = ::glGetProgramPipelineiv;
		glProgramUniform1i = ::glProgramUniform1i;
		glProgramUniform2i = ::glProgramUniform2i;
		glProgramUniform3i = ::glProgramUniform3i;
		glProgramUniform4i = ::glProgramUniform4i;
		glProgramUniform1ui = ::glProgramUniform1ui;
		glProgramUniform2ui = ::glProgramUniform2ui;
		glProgramUniform3ui = ::glProgramUniform3ui;
		glProgramUniform4ui = ::glProgramUniform4ui;
		glProgramUniform1f = ::glProgramUniform1f;
		glProgramUniform2f = ::glProgramUniform2f;
		glProgramUniform3f = ::glProgramUniform3f;
		glProgramUniform4f = ::glProgramUniform4f;
		glProgramUniform1iv = ::glProgramUniform1iv;
		glProgramUniform2iv = ::glProgramUniform2iv;
		glProgramUniform3iv = ::glProgramUniform3iv;
		glProgramUniform4iv = ::glProgramUniform4iv;
		glProgramUniform1uiv = ::glProgramUniform1uiv;
		glProgramUniform2uiv = ::glProgramUniform2uiv;
		glProgramUniform3uiv = ::glProgramUniform3uiv;
		glProgramUniform4uiv = ::glProgramUniform4uiv;
		glProgramUniform1fv = ::glProgramUniform1fv;
		glProgramUniform2fv = ::glProgramUniform2fv;
		glProgramUniform3fv = ::glProgramUniform3fv;
		glProgramUniform4fv = ::glProgramUniform4fv;
		glProgramUniformMatrix2fv = ::glProgramUniformMatrix2fv;
		glProgramUniformMatrix3fv = ::glProgramUniformMatrix3fv;
		glProgramUniformMatrix4fv = ::glProgramUniformMatrix4fv;
		glProgramUniformMatrix2x3fv = ::glProgramUniformMatrix2x3fv;
		glProgramUniformMatrix3x2fv = ::glProgramUniformMatrix3x2fv;
		glProgramUniformMatrix2x4fv = ::glProgramUniformMatrix2x4fv;
		glProgramUniformMatrix4x2fv = ::glProgramUniformMatrix4x2fv;
		glProgramUniformMatrix3x4fv = ::glProgramUniformMatrix3x4fv;
		glProgramUniformMatrix4x3fv = ::glProgramUniformMatrix4x3fv;
		glValidateProgramPipeline = ::glValidateProgramPipeline;
		glGetProgramPipelineInfoLog = ::glGetProgramPipelineInfoLog;
		glBindImageTexture = ::glBindImageTexture;
		glGetBooleani_v = ::glGetBooleani_v;
		glMemoryBarrier = ::glMemoryBarrier;
		glMemoryBarrierByRegion = ::glMemoryBarrierByRegion;
		glTexStorage2DMultisample = ::glTexStorage2DMultisample;
		glGetMultisamplefv = ::glGetMultisamplefv;
		glSampleMaski = ::glSampleMaski;
		glGetTexLevelParameteriv = ::glGetTexLevelParameteriv;
		glGetTexLevelParameterfv = ::glGetTexLevelParameterfv;
		glBindVertexBuffer = ::glBindVertexBuffer;
		glVertexAttribFormat = ::glVertexAttribFormat;
		glVertexAttribIFormat = ::glVertexAttribIFormat;
		glVertexAttribBinding = ::glVertexAttribBinding;
		glVertexBindingDivisor = ::glVertexBindingDivisor;

		// 3.2
		glBlendBarrier = ::glBlendBarrier;
		glCopyImageSubData = ::glCopyImageSubData;
		glDebugMessageControl = ::glDebugMessageControl;
		glDebugMessageInsert = ::glDebugMessageInsert;
		glDebugMessageCallback = ::glDebugMessageCallback;
		glGetDebugMessageLog = ::glGetDebugMessageLog;
		glPushDebugGroup = ::glPushDebugGroup;
		glPopDebugGroup = ::glPopDebugGroup;
		glObjectLabel = ::glObjectLabel;
		glGetObjectLabel = ::glGetObjectLabel;
		glObjectPtrLabel = ::glObjectPtrLabel;
		glGetObjectPtrLabel = ::glGetObjectPtrLabel;
		glGetPointerv = ::glGetPointerv;
		glEnablei = ::glEnablei;
		glDisablei = ::glDisablei;
		glBlendEquationi = ::glBlendEquationi;
		glBlendEquationSeparatei = ::glBlendEquationSeparatei;
		glBlendFunci = ::glBlendFunci;
		glBlendFuncSeparatei = ::glBlendFuncSeparatei;
		glColorMaski = ::glColorMaski;
		glIsEnabledi = ::glIsEnabledi;
		glDrawElementsBaseVertex = ::glDrawElementsBaseVertex;
		glDrawRangeElementsBaseVertex = ::glDrawRangeElementsBaseVertex;
		glDrawElementsInstancedBaseVertex = ::glDrawElementsInstancedBaseVertex;
		glFramebufferTexture = ::glFramebufferTexture;
		glPrimitiveBoundingBox = ::glPrimitiveBoundingBox;
		glGetGraphicsResetStatus = ::glGetGraphicsResetStatus;
		glReadnPixels = ::glReadnPixels;
		glGetnUniformfv = ::glGetnUniformfv;
		glGetnUniformiv = ::glGetnUniformiv;
		glGetnUniformuiv = ::glGetnUniformuiv;
		glMinSampleShading = ::glMinSampleShading;
		glPatchParameteri = ::glPatchParameteri;
		glTexParameterIiv = ::glTexParameterIiv;
		glTexParameterIuiv = ::glTexParameterIuiv;
		glGetTexParameterIiv = ::glGetTexParameterIiv;
		glGetTexParameterIuiv = ::glGetTexParameterIuiv;
		glSamplerParameterIiv = ::glSamplerParameterIiv;
		glSamplerParameterIuiv = ::glSamplerParameterIuiv;
		glGetSamplerParameterIiv = ::glGetSamplerParameterIiv;
		glGetSamplerParameterIuiv = ::glGetSamplerParameterIuiv;
		glTexBuffer = ::glTexBuffer;
		glTexBufferRange = ::glTexBufferRange;
		glTexStorage3DMultisample = ::glTexStorage3DMultisample;
	}

	bool load(nitisa::Version2 *version, PlatformData *pd)
	{
		if (!Loaded)
		{
			Loaded = true;
			if (!pd || !pd->display || !pd->window)
				return false;
			if (eglInitialize(pd->display, nullptr, nullptr) == EGL_FALSE)
				return false;
			LoadProcedures();
			// Try 3.0+ contents
			const char *extensions{ eglQueryString(pd->display, EGL_EXTENSIONS) };
			if (extensions || strstr(extensions, "EGL_KHR_create_context"))
			{
				const EGLint attribs[] = {
					EGL_SURFACE_TYPE, EGL_WINDOW_BIT | EGL_PBUFFER_BIT,
					EGL_BLUE_SIZE, 8,
					EGL_GREEN_SIZE, 8,
					EGL_RED_SIZE, 8,
					EGL_ALPHA_SIZE, 8,
					EGL_DEPTH_SIZE, 24,
					EGL_STENCIL_SIZE, 8,
					EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
					EGL_NONE
				};
				EGLint config_count, format;
				EGLConfig config;
				if (eglChooseConfig(pd->display, attribs, &config, 1, &config_count) == EGL_TRUE &&
					eglGetConfigAttrib(pd->display, config, EGL_NATIVE_VISUAL_ID, &format) == EGL_TRUE &&
					ANativeWindow_setBuffersGeometry(pd->window, 0, 0, format) == 0)
				{
					EGLSurface surface;
					if ((surface = eglCreateWindowSurface(pd->display, config, pd->window, nullptr)))
					{
						for (int i = 2; i >= 0; i--)
						{
							const EGLint context_attribs[] = {
								EGL_CONTEXT_MAJOR_VERSION_KHR, 3,
								EGL_CONTEXT_MINOR_VERSION_KHR, i,
								EGL_NONE
							};
							EGLContext context;
							if ((context = eglCreateContext(pd->display, config, nullptr, context_attribs)))
							{
								if (eglMakeCurrent(pd->display, surface, surface, context) == EGL_TRUE)
								{
									Version.Major = 3;
									Version.Minor = i;
									LoadResult = true;
									eglMakeCurrent(pd->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
								}
								eglDestroyContext(pd->display, context);
								if (LoadResult)
									break;
							}
						}
						eglDestroySurface(pd->display, surface);
					}
				}
			}
			// Try 2.0 content
			if (!LoadResult)
			{
				const EGLint attribs[] = {
					EGL_SURFACE_TYPE, EGL_WINDOW_BIT | EGL_PBUFFER_BIT,
					EGL_BLUE_SIZE, 8,
					EGL_GREEN_SIZE, 8,
					EGL_RED_SIZE, 8,
					EGL_ALPHA_SIZE, 8,
					EGL_DEPTH_SIZE, 24,
					EGL_STENCIL_SIZE, 8,
					EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
					EGL_NONE
				};
				EGLint config_count, format;
				EGLConfig config;
				if (eglChooseConfig(pd->display, attribs, &config, 1, &config_count) == EGL_TRUE &&
					eglGetConfigAttrib(pd->display, config, EGL_NATIVE_VISUAL_ID, &format) == EGL_TRUE &&
					ANativeWindow_setBuffersGeometry(pd->window, 0, 0, format) == 0)
				{
					EGLSurface surface;
					if ((surface = eglCreateWindowSurface(pd->display, config, pd->window, nullptr)))
					{
						const EGLint context_attribs[] = {
							EGL_CONTEXT_CLIENT_VERSION, 2,
							EGL_NONE
						};
						EGLContext context;
						if ((context = eglCreateContext(pd->display, config, nullptr, context_attribs)))
						{
							if (eglMakeCurrent(pd->display, surface, surface, context) == EGL_TRUE)
							{
								Version.Major = 2;
								Version.Minor = 0;
								LoadResult = true;
								eglMakeCurrent(pd->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
							}
							eglDestroyContext(pd->display, context);
						}
						eglDestroySurface(pd->display, surface);
					}
				}
			}
			eglTerminate(pd->display);
		}
		if (version)
			*version = Version;
		return LoadResult;
	}

	bool loaded(nitisa::Version2 *version)
	{
		if (version)
			*version = Version;
		return LoadResult;
	}

	void unload()
	{
		Loaded = LoadResult = false;
		Version = nitisa::Version2{ 0, 0 };
	}
}
#endif