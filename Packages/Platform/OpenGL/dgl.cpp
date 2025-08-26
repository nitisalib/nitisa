// This file is a part of Nitisa framework
// Copyright © 2024 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#include "dgl.h"

namespace dgl
{
	nitisa::CErrorListenerCout DefaultErrorListener;
	nitisa::IErrorListener *ErrorListener = &DefaultErrorListener;
	GLint Error;
}

using namespace dgl;

void dglListener(nitisa::IErrorListener *listener)
{
	ErrorListener = listener ? listener : &DefaultErrorListener;
}

extern "C"
{
#if defined(_WIN32) || (defined(__linux__) && !defined(__ANDROID__))
	// 1.0
	void APIENTRY dglCullFace(GLenum mode)
	{
		ngl::glCullFace(mode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglFrontFace(GLenum mode)
	{
		ngl::glFrontFace(mode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglHint(GLenum target, GLenum mode)
	{
		ngl::glHint(target, mode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglLineWidth(GLfloat width)
	{
		ngl::glLineWidth(width);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglPointSize(GLfloat size)
	{
		ngl::glPointSize(size);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglPolygonMode(GLenum face, GLenum mode)
	{
		ngl::glPolygonMode(face, mode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglScissor(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		ngl::glScissor(x, y, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexParameterf(GLenum target, GLenum pname, GLfloat param)
	{
		ngl::glTexParameterf(target, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexParameterfv(GLenum target, GLenum pname, const GLfloat *params)
	{
		ngl::glTexParameterfv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexParameteri(GLenum target, GLenum pname, GLint param)
	{
		ngl::glTexParameteri(target, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexParameteriv(GLenum target, GLenum pname, const GLint *params)
	{
		ngl::glTexParameteriv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels)
	{
		ngl::glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)
	{
		ngl::glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDrawBuffer(GLenum buf)
	{
		ngl::glDrawBuffer(buf);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClear(GLbitfield mask)
	{
		ngl::glClear(mask);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
	{
		ngl::glClearColor(red, green, blue, alpha);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearStencil(GLint s)
	{
		ngl::glClearStencil(s);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearDepth(GLdouble depth)
	{
		ngl::glClearDepth(depth);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglStencilMask(GLuint mask)
	{
		ngl::glStencilMask(mask);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
	{
		ngl::glColorMask(red, green, blue, alpha);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDepthMask(GLboolean flag)
	{
		ngl::glDepthMask(flag);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDisable(GLenum cap)
	{
		ngl::glDisable(cap);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglEnable(GLenum cap)
	{
		ngl::glEnable(cap);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglFinish()
	{
		ngl::glFinish();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglFlush()
	{
		ngl::glFlush();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBlendFunc(GLenum sfactor, GLenum dfactor)
	{
		ngl::glBlendFunc(sfactor, dfactor);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglLogicOp(GLenum opcode)
	{
		ngl::glLogicOp(opcode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglStencilFunc(GLenum func, GLint ref, GLuint mask)
	{
		ngl::glStencilFunc(func, ref, mask);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
	{
		ngl::glStencilOp(fail, zfail, zpass);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDepthFunc(GLenum func)
	{
		ngl::glDepthFunc(func);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglPixelStoref(GLenum pname, GLfloat param)
	{
		ngl::glPixelStoref(pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglPixelStorei(GLenum pname, GLint param)
	{
		ngl::glPixelStorei(pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglReadBuffer(GLenum src)
	{
		ngl::glReadBuffer(src);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels)
	{
		ngl::glReadPixels(x, y, width, height, format, type, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetBooleanv(GLenum pname, GLboolean *data)
	{
		ngl::glGetBooleanv(pname, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetDoublev(GLenum pname, GLdouble *data)
	{
		ngl::glGetDoublev(pname, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetFloatv(GLenum pname, GLfloat *data)
	{
		ngl::glGetFloatv(pname, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetIntegerv(GLenum pname, GLint *data)
	{
		ngl::glGetIntegerv(pname, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	const GLubyte *APIENTRY dglGetString(GLenum name)
	{
		auto result{ ngl::glGetString(name) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void *pixels)
	{
		ngl::glGetTexImage(target, level, format, type, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTexParameterfv(GLenum target, GLenum pname, GLfloat *params)
	{
		ngl::glGetTexParameterfv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTexParameteriv(GLenum target, GLenum pname, GLint *params)
	{
		ngl::glGetTexParameteriv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat *params)
	{
		ngl::glGetTexLevelParameterfv(target, level, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint *params)
	{
		ngl::glGetTexLevelParameteriv(target, level, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean APIENTRY dglIsEnabled(GLenum cap)
	{
		auto result{ ngl::glIsEnabled(cap) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglDepthRange(GLdouble n, GLdouble f)
	{
		ngl::glDepthRange(n, f);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglViewport(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		ngl::glViewport(x, y, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 1.1
	void APIENTRY dglDrawArrays(GLenum mode, GLint first, GLsizei count)
	{
		ngl::glDrawArrays(mode, first, count);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices)
	{
		ngl::glDrawElements(mode, count, type, indices);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetPointerv(GLenum pname, void **params)
	{
		ngl::glGetPointerv(pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglPolygonOffset(GLfloat factor, GLfloat units)
	{
		ngl::glPolygonOffset(factor, units);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
	{
		ngl::glCopyTexImage1D(target, level, internalformat, x, y, width, border);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
	{
		ngl::glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
	{
		ngl::glCopyTexSubImage1D(target, level, xoffset, x, y, width);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		ngl::glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels)
	{
		ngl::glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels)
	{
		ngl::glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindTexture(GLenum target, GLuint texture)
	{
		ngl::glBindTexture(target, texture);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDeleteTextures(GLsizei n, const GLuint *textures)
	{
		ngl::glDeleteTextures(n, textures);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGenTextures(GLsizei n, GLuint *textures)
	{
		ngl::glGenTextures(n, textures);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean APIENTRY dglIsTexture(GLuint texture)
	{
		auto result{ ngl::glIsTexture(texture) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	// 1.2
	void APIENTRY dglDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices)
	{
		ngl::glDrawRangeElements(mode, start, end, count, type, indices);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels)
	{
		ngl::glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels)
	{
		ngl::glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		ngl::glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 1.3
	void APIENTRY dglActiveTexture(GLenum texture)
	{
		ngl::glActiveTexture(texture);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglSampleCoverage(GLfloat value, GLboolean invert)
	{
		ngl::glSampleCoverage(value, invert);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data)
	{
		ngl::glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data)
	{
		ngl::glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data)
	{
		ngl::glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data)
	{
		ngl::glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data)
	{
		ngl::glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data)
	{
		ngl::glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetCompressedTexImage(GLenum target, GLint level, void *img)
	{
		ngl::glGetCompressedTexImage(target, level, img);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 1.4
	void APIENTRY dglBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
	{
		ngl::glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglMultiDrawArrays(GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount)
	{
		ngl::glMultiDrawArrays(mode, first, count, drawcount);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglMultiDrawElements(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount)
	{
		ngl::glMultiDrawElements(mode, count, type, indices, drawcount);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglPointParameterf(GLenum pname, GLfloat param)
	{
		ngl::glPointParameterf(pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglPointParameterfv(GLenum pname, const GLfloat *params)
	{
		ngl::glPointParameterfv(pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglPointParameteri(GLenum pname, GLint param)
	{
		ngl::glPointParameteri(pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglPointParameteriv(GLenum pname, const GLint *params)
	{
		ngl::glPointParameteriv(pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
	{
		ngl::glBlendColor(red, green, blue, alpha);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBlendEquation(GLenum mode)
	{
		ngl::glBlendEquation(mode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 1.5
	void APIENTRY dglGenQueries(GLsizei n, GLuint *ids)
	{
		ngl::glGenQueries(n, ids);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDeleteQueries(GLsizei n, const GLuint *ids)
	{
		ngl::glDeleteQueries(n, ids);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean APIENTRY dglIsQuery(GLuint id)
	{
		auto result{ ngl::glIsQuery(id) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglBeginQuery(GLenum target, GLuint id)
	{
		ngl::glBeginQuery(target, id);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglEndQuery(GLenum target)
	{
		ngl::glEndQuery(target);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetQueryiv(GLenum target, GLenum pname, GLint *params)
	{
		ngl::glGetQueryiv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetQueryObjectiv(GLuint id, GLenum pname, GLint *params)
	{
		ngl::glGetQueryObjectiv(id, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetQueryObjectuiv(GLuint id, GLenum pname, GLuint *params)
	{
		ngl::glGetQueryObjectuiv(id, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindBuffer(GLenum target, GLuint buffer)
	{
		ngl::glBindBuffer(target, buffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDeleteBuffers(GLsizei n, const GLuint *buffers)
	{
		ngl::glDeleteBuffers(n, buffers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGenBuffers(GLsizei n, GLuint *buffers)
	{
		ngl::glGenBuffers(n, buffers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean APIENTRY dglIsBuffer(GLuint buffer)
	{
		auto result{ ngl::glIsBuffer(buffer) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage)
	{
		ngl::glBufferData(target, size, data, usage);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data)
	{
		ngl::glBufferSubData(target, offset, size, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void *data)
	{
		ngl::glGetBufferSubData(target, offset, size, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void *APIENTRY dglMapBuffer(GLenum target, GLenum access)
	{
		auto result{ ngl::glMapBuffer(target, access) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	GLboolean APIENTRY dglUnmapBuffer(GLenum target)
	{
		auto result{ ngl::glUnmapBuffer(target) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglGetBufferParameteriv(GLenum target, GLenum pname, GLint *params)
	{
		ngl::glGetBufferParameteriv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetBufferPointerv(GLenum target, GLenum pname, void **params)
	{
		ngl::glGetBufferPointerv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 2.0
	void APIENTRY dglBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
	{
		ngl::glBlendEquationSeparate(modeRGB, modeAlpha);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDrawBuffers(GLsizei n, const GLenum *bufs)
	{
		ngl::glDrawBuffers(n, bufs);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
	{
		ngl::glStencilOpSeparate(face, sfail, dpfail, dppass);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
	{
		ngl::glStencilFuncSeparate(face, func, ref, mask);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglStencilMaskSeparate(GLenum face, GLuint mask)
	{
		ngl::glStencilMaskSeparate(face, mask);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglAttachShader(GLuint program, GLuint shader)
	{
		ngl::glAttachShader(program, shader);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindAttribLocation(GLuint program, GLuint index, const GLchar *name)
	{
		ngl::glBindAttribLocation(program, index, name);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCompileShader(GLuint shader)
	{
		ngl::glCompileShader(shader);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLuint APIENTRY dglCreateProgram()
	{
		auto result{ ngl::glCreateProgram() };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	GLuint APIENTRY dglCreateShader(GLenum type)
	{
		auto result{ ngl::glCreateShader(type) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglDeleteProgram(GLuint program)
	{
		ngl::glDeleteProgram(program);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDeleteShader(GLuint shader)
	{
		ngl::glDeleteShader(shader);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDetachShader(GLuint program, GLuint shader)
	{
		ngl::glDetachShader(program, shader);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDisableVertexAttribArray(GLuint index)
	{
		ngl::glDisableVertexAttribArray(index);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglEnableVertexAttribArray(GLuint index)
	{
		ngl::glEnableVertexAttribArray(index);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name)
	{
		ngl::glGetActiveAttrib(program, index, bufSize, length, size, type, name);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name)
	{
		ngl::glGetActiveUniform(program, index, bufSize, length, size, type, name);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders)
	{
		ngl::glGetAttachedShaders(program, maxCount, count, shaders);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLint APIENTRY dglGetAttribLocation(GLuint program, const GLchar *name)
	{
		auto result{ ngl::glGetAttribLocation(program, name) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglGetProgramiv(GLuint program, GLenum pname, GLint *params)
	{
		ngl::glGetProgramiv(program, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
	{
		ngl::glGetProgramInfoLog(program, bufSize, length, infoLog);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetShaderiv(GLuint shader, GLenum pname, GLint *params)
	{
		ngl::glGetShaderiv(shader, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
	{
		ngl::glGetShaderInfoLog(shader, bufSize, length, infoLog);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source)
	{
		ngl::glGetShaderSource(shader, bufSize, length, source);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLint APIENTRY dglGetUniformLocation(GLuint program, const GLchar *name)
	{
		auto result{ ngl::glGetUniformLocation(program, name) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglGetUniformfv(GLuint program, GLint location, GLfloat *params)
	{
		ngl::glGetUniformfv(program, location, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetUniformiv(GLuint program, GLint location, GLint *params)
	{
		ngl::glGetUniformiv(program, location, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetVertexAttribdv(GLuint index, GLenum pname, GLdouble *params)
	{
		ngl::glGetVertexAttribdv(index, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetVertexAttribfv(GLuint index, GLenum pname, GLfloat *params)
	{
		ngl::glGetVertexAttribfv(index, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetVertexAttribiv(GLuint index, GLenum pname, GLint *params)
	{
		ngl::glGetVertexAttribiv(index, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetVertexAttribPointerv(GLuint index, GLenum pname, void **pointer)
	{
		ngl::glGetVertexAttribPointerv(index, pname, pointer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean APIENTRY dglIsProgram(GLuint program)
	{
		auto result{ ngl::glIsProgram(program) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	GLboolean APIENTRY dglIsShader(GLuint shader)
	{
		auto result{ ngl::glIsShader(shader) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglLinkProgram(GLuint program)
	{
		ngl::glLinkProgram(program);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length)
	{
		ngl::glShaderSource(shader, count, string, length);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUseProgram(GLuint program)
	{
		ngl::glUseProgram(program);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform1f(GLint location, GLfloat v0)
	{
		ngl::glUniform1f(location, v0);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform2f(GLint location, GLfloat v0, GLfloat v1)
	{
		ngl::glUniform2f(location, v0, v1);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
	{
		ngl::glUniform3f(location, v0, v1, v2);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
	{
		ngl::glUniform4f(location, v0, v1, v2, v3);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform1i(GLint location, GLint v0)
	{
		ngl::glUniform1i(location, v0);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform2i(GLint location, GLint v0, GLint v1)
	{
		ngl::glUniform2i(location, v0, v1);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform3i(GLint location, GLint v0, GLint v1, GLint v2)
	{
		ngl::glUniform3i(location, v0, v1, v2);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
	{
		ngl::glUniform4i(location, v0, v1, v2, v3);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform1fv(GLint location, GLsizei count, const GLfloat *value)
	{
		ngl::glUniform1fv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform2fv(GLint location, GLsizei count, const GLfloat *value)
	{
		ngl::glUniform2fv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform3fv(GLint location, GLsizei count, const GLfloat *value)
	{
		ngl::glUniform3fv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform4fv(GLint location, GLsizei count, const GLfloat *value)
	{
		ngl::glUniform4fv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform1iv(GLint location, GLsizei count, const GLint *value)
	{
		ngl::glUniform1iv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform2iv(GLint location, GLsizei count, const GLint *value)
	{
		ngl::glUniform2iv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform3iv(GLint location, GLsizei count, const GLint *value)
	{
		ngl::glUniform3iv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform4iv(GLint location, GLsizei count, const GLint *value)
	{
		ngl::glUniform4iv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix2fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix3fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix4fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglValidateProgram(GLuint program)
	{
		ngl::glValidateProgram(program);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib1d(GLuint index, GLdouble x)
	{
		ngl::glVertexAttrib1d(index, x);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib1dv(GLuint index, const GLdouble *v)
	{
		ngl::glVertexAttrib1dv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib1f(GLuint index, GLfloat x)
	{
		ngl::glVertexAttrib1f(index, x);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib1fv(GLuint index, const GLfloat *v)
	{
		ngl::glVertexAttrib1fv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib1s(GLuint index, GLshort x)
	{
		ngl::glVertexAttrib1s(index, x);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib1sv(GLuint index, const GLshort *v)
	{
		ngl::glVertexAttrib1sv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib2d(GLuint index, GLdouble x, GLdouble y)
	{
		ngl::glVertexAttrib2d(index, x, y);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib2dv(GLuint index, const GLdouble *v)
	{
		ngl::glVertexAttrib2dv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
	{
		ngl::glVertexAttrib2f(index, x, y);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib2fv(GLuint index, const GLfloat *v)
	{
		ngl::glVertexAttrib2fv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib2s(GLuint index, GLshort x, GLshort y)
	{
		ngl::glVertexAttrib2s(index, x, y);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib2sv(GLuint index, const GLshort *v)
	{
		ngl::glVertexAttrib2sv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
	{
		ngl::glVertexAttrib3d(index, x, y, z);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib3dv(GLuint index, const GLdouble *v)
	{
		ngl::glVertexAttrib3dv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
	{
		ngl::glVertexAttrib3f(index, x, y, z);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib3fv(GLuint index, const GLfloat *v)
	{
		ngl::glVertexAttrib3fv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z)
	{
		ngl::glVertexAttrib3s(index, x, y, z);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib3sv(GLuint index, const GLshort *v)
	{
		ngl::glVertexAttrib3sv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4Nbv(GLuint index, const GLbyte *v)
	{
		ngl::glVertexAttrib4Nbv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4Niv(GLuint index, const GLint *v)
	{
		ngl::glVertexAttrib4Niv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4Nsv(GLuint index, const GLshort *v)
	{
		ngl::glVertexAttrib4Nsv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
	{
		ngl::glVertexAttrib4Nub(index, x, y, z, w);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4Nubv(GLuint index, const GLubyte *v)
	{
		ngl::glVertexAttrib4Nubv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4Nuiv(GLuint index, const GLuint *v)
	{
		ngl::glVertexAttrib4Nuiv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4Nusv(GLuint index, const GLushort *v)
	{
		ngl::glVertexAttrib4Nusv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4bv(GLuint index, const GLbyte *v)
	{
		ngl::glVertexAttrib4bv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
	{
		ngl::glVertexAttrib4d(index, x, y, z, w);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4dv(GLuint index, const GLdouble *v)
	{
		ngl::glVertexAttrib4dv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
	{
		ngl::glVertexAttrib4f(index, x, y, z, w);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4fv(GLuint index, const GLfloat *v)
	{
		ngl::glVertexAttrib4fv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4iv(GLuint index, const GLint *v)
	{
		ngl::glVertexAttrib4iv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
	{
		ngl::glVertexAttrib4s(index, x, y, z, w);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4sv(GLuint index, const GLshort *v)
	{
		ngl::glVertexAttrib4sv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4ubv(GLuint index, const GLubyte *v)
	{
		ngl::glVertexAttrib4ubv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4uiv(GLuint index, const GLuint *v)
	{
		ngl::glVertexAttrib4uiv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttrib4usv(GLuint index, const GLushort *v)
	{
		ngl::glVertexAttrib4usv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
	{
		ngl::glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 2.1
	void APIENTRY dglUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix2x3fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix3x2fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix2x4fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix4x2fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix3x4fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix4x3fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 3.0
	void APIENTRY dglColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
	{
		ngl::glColorMaski(index, r, g, b, a);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetBooleani_v(GLenum target, GLuint index, GLboolean *data)
	{
		ngl::glGetBooleani_v(target, index, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetIntegeri_v(GLenum target, GLuint index, GLint *data)
	{
		ngl::glGetIntegeri_v(target, index, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglEnablei(GLenum target, GLuint index)
	{
		ngl::glEnablei(target, index);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDisablei(GLenum target, GLuint index)
	{
		ngl::glDisablei(target, index);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean APIENTRY dglIsEnabledi(GLenum target, GLuint index)
	{
		auto result{ ngl::glIsEnabledi(target, index) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglBeginTransformFeedback(GLenum primitiveMode)
	{
		ngl::glBeginTransformFeedback(primitiveMode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglEndTransformFeedback()
	{
		ngl::glEndTransformFeedback();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
	{
		ngl::glBindBufferRange(target, index, buffer, offset, size);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindBufferBase(GLenum target, GLuint index, GLuint buffer)
	{
		ngl::glBindBufferBase(target, index, buffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode)
	{
		ngl::glTransformFeedbackVaryings(program, count, varyings, bufferMode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name)
	{
		ngl::glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClampColor(GLenum target, GLenum clamp)
	{
		ngl::glClampColor(target, clamp);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBeginConditionalRender(GLuint id, GLenum mode)
	{
		ngl::glBeginConditionalRender(id, mode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglEndConditionalRender()
	{
		ngl::glEndConditionalRender();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer)
	{
		ngl::glVertexAttribIPointer(index, size, type, stride, pointer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetVertexAttribIiv(GLuint index, GLenum pname, GLint *params)
	{
		ngl::glGetVertexAttribIiv(index, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint *params)
	{
		ngl::glGetVertexAttribIuiv(index, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI1i(GLuint index, GLint x)
	{
		ngl::glVertexAttribI1i(index, x);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI2i(GLuint index, GLint x, GLint y)
	{
		ngl::glVertexAttribI2i(index, x, y);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z)
	{
		ngl::glVertexAttribI3i(index, x, y, z);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
	{
		ngl::glVertexAttribI4i(index, x, y, z, w);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI1ui(GLuint index, GLuint x)
	{
		ngl::glVertexAttribI1ui(index, x);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI2ui(GLuint index, GLuint x, GLuint y)
	{
		ngl::glVertexAttribI2ui(index, x, y);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z)
	{
		ngl::glVertexAttribI3ui(index, x, y, z);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
	{
		ngl::glVertexAttribI4ui(index, x, y, z, w);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI1iv(GLuint index, const GLint *v)
	{
		ngl::glVertexAttribI1iv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI2iv(GLuint index, const GLint *v)
	{
		ngl::glVertexAttribI2iv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI3iv(GLuint index, const GLint *v)
	{
		ngl::glVertexAttribI3iv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI4iv(GLuint index, const GLint *v)
	{
		ngl::glVertexAttribI4iv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI1uiv(GLuint index, const GLuint *v)
	{
		ngl::glVertexAttribI1uiv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI2uiv(GLuint index, const GLuint *v)
	{
		ngl::glVertexAttribI2uiv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI3uiv(GLuint index, const GLuint *v)
	{
		ngl::glVertexAttribI3uiv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI4uiv(GLuint index, const GLuint *v)
	{
		ngl::glVertexAttribI4uiv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI4bv(GLuint index, const GLbyte *v)
	{
		ngl::glVertexAttribI4bv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI4sv(GLuint index, const GLshort *v)
	{
		ngl::glVertexAttribI4sv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI4ubv(GLuint index, const GLubyte *v)
	{
		ngl::glVertexAttribI4ubv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribI4usv(GLuint index, const GLushort *v)
	{
		ngl::glVertexAttribI4usv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetUniformuiv(GLuint program, GLint location, GLuint *params)
	{
		ngl::glGetUniformuiv(program, location, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindFragDataLocation(GLuint program, GLuint color, const GLchar *name)
	{
		ngl::glBindFragDataLocation(program, color, name);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLint APIENTRY dglGetFragDataLocation(GLuint program, const GLchar *name)
	{
		auto result{ ngl::glGetFragDataLocation(program, name) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglUniform1ui(GLint location, GLuint v0)
	{
		ngl::glUniform1ui(location, v0);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform2ui(GLint location, GLuint v0, GLuint v1)
	{
		ngl::glUniform2ui(location, v0, v1);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
	{
		ngl::glUniform3ui(location, v0, v1, v2);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
	{
		ngl::glUniform4ui(location, v0, v1, v2, v3);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform1uiv(GLint location, GLsizei count, const GLuint *value)
	{
		ngl::glUniform1uiv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform2uiv(GLint location, GLsizei count, const GLuint *value)
	{
		ngl::glUniform2uiv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform3uiv(GLint location, GLsizei count, const GLuint *value)
	{
		ngl::glUniform3uiv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform4uiv(GLint location, GLsizei count, const GLuint *value)
	{
		ngl::glUniform4uiv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexParameterIiv(GLenum target, GLenum pname, const GLint *params)
	{
		ngl::glTexParameterIiv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexParameterIuiv(GLenum target, GLenum pname, const GLuint *params)
	{
		ngl::glTexParameterIuiv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTexParameterIiv(GLenum target, GLenum pname, GLint *params)
	{
		ngl::glGetTexParameterIiv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTexParameterIuiv(GLenum target, GLenum pname, GLuint *params)
	{
		ngl::glGetTexParameterIuiv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint *value)
	{
		ngl::glClearBufferiv(buffer, drawbuffer, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint *value)
	{
		ngl::glClearBufferuiv(buffer, drawbuffer, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat *value)
	{
		ngl::glClearBufferfv(buffer, drawbuffer, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
	{
		ngl::glClearBufferfi(buffer, drawbuffer, depth, stencil);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	const GLubyte *APIENTRY dglGetStringi(GLenum name, GLuint index)
	{
		auto result{ ngl::glGetStringi(name, index) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	GLboolean APIENTRY dglIsRenderbuffer(GLuint renderbuffer)
	{
		auto result{ ngl::glIsRenderbuffer(renderbuffer) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglBindRenderbuffer(GLenum target, GLuint renderbuffer)
	{
		ngl::glBindRenderbuffer(target, renderbuffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers)
	{
		ngl::glDeleteRenderbuffers(n, renderbuffers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGenRenderbuffers(GLsizei n, GLuint *renderbuffers)
	{
		ngl::glGenRenderbuffers(n, renderbuffers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
	{
		ngl::glRenderbufferStorage(target, internalformat, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params)
	{
		ngl::glGetRenderbufferParameteriv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean APIENTRY dglIsFramebuffer(GLuint framebuffer)
	{
		auto result{ ngl::glIsFramebuffer(framebuffer) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglBindFramebuffer(GLenum target, GLuint framebuffer)
	{
		ngl::glBindFramebuffer(target, framebuffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDeleteFramebuffers(GLsizei n, const GLuint *framebuffers)
	{
		ngl::glDeleteFramebuffers(n, framebuffers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGenFramebuffers(GLsizei n, GLuint *framebuffers)
	{
		ngl::glGenFramebuffers(n, framebuffers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLenum APIENTRY dglCheckFramebufferStatus(GLenum target)
	{
		auto result{ ngl::glCheckFramebufferStatus(target) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
	{
		ngl::glFramebufferTexture1D(target, attachment, textarget, texture, level);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
	{
		ngl::glFramebufferTexture2D(target, attachment, textarget, texture, level);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
	{
		ngl::glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
	{
		ngl::glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint *params)
	{
		ngl::glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGenerateMipmap(GLenum target)
	{
		ngl::glGenerateMipmap(target);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
	{
		ngl::glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
	{
		ngl::glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
	{
		ngl::glFramebufferTextureLayer(target, attachment, texture, level, layer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void *APIENTRY dglMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
	{
		auto result{ ngl::glMapBufferRange(target, offset, length, access) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
	{
		ngl::glFlushMappedBufferRange(target, offset, length);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindVertexArray(GLuint array)
	{
		ngl::glBindVertexArray(array);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDeleteVertexArrays(GLsizei n, const GLuint *arrays)
	{
		ngl::glDeleteVertexArrays(n, arrays);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGenVertexArrays(GLsizei n, GLuint *arrays)
	{
		ngl::glGenVertexArrays(n, arrays);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean APIENTRY dglIsVertexArray(GLuint array)
	{
		auto result{ ngl::glIsVertexArray(array) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	// 3.1
	void APIENTRY dglDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
	{
		ngl::glDrawArraysInstanced(mode, first, count, instancecount);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount)
	{
		ngl::glDrawElementsInstanced(mode, count, type, indices, instancecount);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexBuffer(GLenum target, GLenum internalformat, GLuint buffer)
	{
		ngl::glTexBuffer(target, internalformat, buffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglPrimitiveRestartIndex(GLuint index)
	{
		ngl::glPrimitiveRestartIndex(index);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		ngl::glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices)
	{
		ngl::glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params)
	{
		ngl::glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName)
	{
		ngl::glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLuint APIENTRY dglGetUniformBlockIndex(GLuint program, const GLchar *uniformBlockName)
	{
		auto result{ ngl::glGetUniformBlockIndex(program, uniformBlockName) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params)
	{
		ngl::glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName)
	{
		ngl::glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
	{
		ngl::glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 3.2
	void APIENTRY dglDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex)
	{
		ngl::glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex)
	{
		ngl::glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex)
	{
		ngl::glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglMultiDrawElementsBaseVertex(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex)
	{
		ngl::glMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProvokingVertex(GLenum mode)
	{
		ngl::glProvokingVertex(mode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLsync APIENTRY dglFenceSync(GLenum condition, GLbitfield flags)
	{
		auto result{ ngl::glFenceSync(condition, flags) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	GLboolean APIENTRY dglIsSync(GLsync sync)
	{
		auto result{ ngl::glIsSync(sync) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglDeleteSync(GLsync sync)
	{
		ngl::glDeleteSync(sync);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLenum APIENTRY dglClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
	{
		auto result{ ngl::glClientWaitSync(sync, flags, timeout) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
	{
		ngl::glWaitSync(sync, flags, timeout);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetInteger64v(GLenum pname, GLint64 *data)
	{
		ngl::glGetInteger64v(pname, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetSynciv(GLsync sync, GLenum pname, GLsizei count, GLsizei *length, GLint *values)
	{
		ngl::glGetSynciv(sync, pname, count, length, values);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetInteger64i_v(GLenum target, GLuint index, GLint64 *data)
	{
		ngl::glGetInteger64i_v(target, index, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 *params)
	{
		ngl::glGetBufferParameteri64v(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
	{
		ngl::glFramebufferTexture(target, attachment, texture, level);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
	{
		ngl::glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
	{
		ngl::glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetMultisamplefv(GLenum pname, GLuint index, GLfloat *val)
	{
		ngl::glGetMultisamplefv(pname, index, val);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglSampleMaski(GLuint maskNumber, GLbitfield mask)
	{
		ngl::glSampleMaski(maskNumber, mask);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 3.3
	void APIENTRY dglBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar *name)
	{
		ngl::glBindFragDataLocationIndexed(program, colorNumber, index, name);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLint APIENTRY dglGetFragDataIndex(GLuint program, const GLchar *name)
	{
		auto result{ ngl::glGetFragDataIndex(program, name) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglGenSamplers(GLsizei count, GLuint *samplers)
	{
		ngl::glGenSamplers(count, samplers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDeleteSamplers(GLsizei count, const GLuint *samplers)
	{
		ngl::glDeleteSamplers(count, samplers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean APIENTRY dglIsSampler(GLuint sampler)
	{
		auto result{ ngl::glIsSampler(sampler) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglBindSampler(GLuint unit, GLuint sampler)
	{
		ngl::glBindSampler(unit, sampler);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglSamplerParameteri(GLuint sampler, GLenum pname, GLint param)
	{
		ngl::glSamplerParameteri(sampler, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglSamplerParameteriv(GLuint sampler, GLenum pname, const GLint *param)
	{
		ngl::glSamplerParameteriv(sampler, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
	{
		ngl::glSamplerParameterf(sampler, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat *param)
	{
		ngl::glSamplerParameterfv(sampler, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglSamplerParameterIiv(GLuint sampler, GLenum pname, const GLint *param)
	{
		ngl::glSamplerParameterIiv(sampler, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglSamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint *param)
	{
		ngl::glSamplerParameterIuiv(sampler, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint *params)
	{
		ngl::glGetSamplerParameteriv(sampler, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint *params)
	{
		ngl::glGetSamplerParameterIiv(sampler, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat *params)
	{
		ngl::glGetSamplerParameterfv(sampler, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint *params)
	{
		ngl::glGetSamplerParameterIuiv(sampler, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglQueryCounter(GLuint id, GLenum target)
	{
		ngl::glQueryCounter(id, target);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetQueryObjecti64v(GLuint id, GLenum pname, GLint64 *params)
	{
		ngl::glGetQueryObjecti64v(id, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 *params)
	{
		ngl::glGetQueryObjectui64v(id, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribDivisor(GLuint index, GLuint divisor)
	{
		ngl::glVertexAttribDivisor(index, divisor);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
	{
		ngl::glVertexAttribP1ui(index, type, normalized, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value)
	{
		ngl::glVertexAttribP1uiv(index, type, normalized, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
	{
		ngl::glVertexAttribP2ui(index, type, normalized, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value)
	{
		ngl::glVertexAttribP2uiv(index, type, normalized, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
	{
		ngl::glVertexAttribP3ui(index, type, normalized, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value)
	{
		ngl::glVertexAttribP3uiv(index, type, normalized, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
	{
		ngl::glVertexAttribP4ui(index, type, normalized, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value)
	{
		ngl::glVertexAttribP4uiv(index, type, normalized, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 4.0
	void APIENTRY dglMinSampleShading(GLfloat value)
	{
		ngl::glMinSampleShading(value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBlendEquationi(GLuint buf, GLenum mode)
	{
		ngl::glBlendEquationi(buf, mode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
	{
		ngl::glBlendEquationSeparatei(buf, modeRGB, modeAlpha);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBlendFunci(GLuint buf, GLenum src, GLenum dst)
	{
		ngl::glBlendFunci(buf, src, dst);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
	{
		ngl::glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDrawArraysIndirect(GLenum mode, const void *indirect)
	{
		ngl::glDrawArraysIndirect(mode, indirect);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect)
	{
		ngl::glDrawElementsIndirect(mode, type, indirect);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform1d(GLint location, GLdouble x)
	{
		ngl::glUniform1d(location, x);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform2d(GLint location, GLdouble x, GLdouble y)
	{
		ngl::glUniform2d(location, x, y);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z)
	{
		ngl::glUniform3d(location, x, y, z);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
	{
		ngl::glUniform4d(location, x, y, z, w);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform1dv(GLint location, GLsizei count, const GLdouble *value)
	{
		ngl::glUniform1dv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform2dv(GLint location, GLsizei count, const GLdouble *value)
	{
		ngl::glUniform2dv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform3dv(GLint location, GLsizei count, const GLdouble *value)
	{
		ngl::glUniform3dv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniform4dv(GLint location, GLsizei count, const GLdouble *value)
	{
		ngl::glUniform4dv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glUniformMatrix2dv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glUniformMatrix3dv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glUniformMatrix4dv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glUniformMatrix2x3dv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glUniformMatrix2x4dv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glUniformMatrix3x2dv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glUniformMatrix3x4dv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glUniformMatrix4x2dv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glUniformMatrix4x3dv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetUniformdv(GLuint program, GLint location, GLdouble *params)
	{
		ngl::glGetUniformdv(program, location, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLint APIENTRY dglGetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar *name)
	{
		auto result{ ngl::glGetSubroutineUniformLocation(program, shadertype, name) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	GLuint APIENTRY dglGetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar *name)
	{
		auto result{ ngl::glGetSubroutineIndex(program, shadertype, name) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values)
	{
		ngl::glGetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name)
	{
		ngl::glGetActiveSubroutineUniformName(program, shadertype, index, bufSize, length, name);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name)
	{
		ngl::glGetActiveSubroutineName(program, shadertype, index, bufSize, length, name);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint *indices)
	{
		ngl::glUniformSubroutinesuiv(shadertype, count, indices);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint *params)
	{
		ngl::glGetUniformSubroutineuiv(shadertype, location, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint *values)
	{
		ngl::glGetProgramStageiv(program, shadertype, pname, values);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglPatchParameteri(GLenum pname, GLint value)
	{
		ngl::glPatchParameteri(pname, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglPatchParameterfv(GLenum pname, const GLfloat *values)
	{
		ngl::glPatchParameterfv(pname, values);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindTransformFeedback(GLenum target, GLuint id)
	{
		ngl::glBindTransformFeedback(target, id);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDeleteTransformFeedbacks(GLsizei n, const GLuint *ids)
	{
		ngl::glDeleteTransformFeedbacks(n, ids);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGenTransformFeedbacks(GLsizei n, GLuint *ids)
	{
		ngl::glGenTransformFeedbacks(n, ids);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean APIENTRY dglIsTransformFeedback(GLuint id)
	{
		auto result{ ngl::glIsTransformFeedback(id) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglPauseTransformFeedback()
	{
		ngl::glPauseTransformFeedback();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglResumeTransformFeedback()
	{
		ngl::glResumeTransformFeedback();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDrawTransformFeedback(GLenum mode, GLuint id)
	{
		ngl::glDrawTransformFeedback(mode, id);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream)
	{
		ngl::glDrawTransformFeedbackStream(mode, id, stream);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBeginQueryIndexed(GLenum target, GLuint index, GLuint id)
	{
		ngl::glBeginQueryIndexed(target, index, id);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglEndQueryIndexed(GLenum target, GLuint index)
	{
		ngl::glEndQueryIndexed(target, index);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint *params)
	{
		ngl::glGetQueryIndexediv(target, index, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 4.1
	void APIENTRY dglReleaseShaderCompiler()
	{
		ngl::glReleaseShaderCompiler();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglShaderBinary(GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length)
	{
		ngl::glShaderBinary(count, shaders, binaryformat, binary, length);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision)
	{
		ngl::glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDepthRangef(GLfloat n, GLfloat f)
	{
		ngl::glDepthRangef(n, f);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearDepthf(GLfloat d)
	{
		ngl::glClearDepthf(d);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary)
	{
		ngl::glGetProgramBinary(program, bufSize, length, binaryFormat, binary);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramBinary(GLuint program, GLenum binaryFormat, const void *binary, GLsizei length)
	{
		ngl::glProgramBinary(program, binaryFormat, binary, length);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramParameteri(GLuint program, GLenum pname, GLint value)
	{
		ngl::glProgramParameteri(program, pname, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program)
	{
		ngl::glUseProgramStages(pipeline, stages, program);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglActiveShaderProgram(GLuint pipeline, GLuint program)
	{
		ngl::glActiveShaderProgram(pipeline, program);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLuint APIENTRY dglCreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const*strings)
	{
		auto result{ ngl::glCreateShaderProgramv(type, count, strings) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglBindProgramPipeline(GLuint pipeline)
	{
		ngl::glBindProgramPipeline(pipeline);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDeleteProgramPipelines(GLsizei n, const GLuint *pipelines)
	{
		ngl::glDeleteProgramPipelines(n, pipelines);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGenProgramPipelines(GLsizei n, GLuint *pipelines)
	{
		ngl::glGenProgramPipelines(n, pipelines);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean APIENTRY dglIsProgramPipeline(GLuint pipeline)
	{
		auto result{ ngl::glIsProgramPipeline(pipeline) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint *params)
	{
		ngl::glGetProgramPipelineiv(pipeline, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform1i(GLuint program, GLint location, GLint v0)
	{
		ngl::glProgramUniform1i(program, location, v0);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint *value)
	{
		ngl::glProgramUniform1iv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform1f(GLuint program, GLint location, GLfloat v0)
	{
		ngl::glProgramUniform1f(program, location, v0);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat *value)
	{
		ngl::glProgramUniform1fv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform1d(GLuint program, GLint location, GLdouble v0)
	{
		ngl::glProgramUniform1d(program, location, v0);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble *value)
	{
		ngl::glProgramUniform1dv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform1ui(GLuint program, GLint location, GLuint v0)
	{
		ngl::glProgramUniform1ui(program, location, v0);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint *value)
	{
		ngl::glProgramUniform1uiv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1)
	{
		ngl::glProgramUniform2i(program, location, v0, v1);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint *value)
	{
		ngl::glProgramUniform2iv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1)
	{
		ngl::glProgramUniform2f(program, location, v0, v1);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat *value)
	{
		ngl::glProgramUniform2fv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1)
	{
		ngl::glProgramUniform2d(program, location, v0, v1);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble *value)
	{
		ngl::glProgramUniform2dv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1)
	{
		ngl::glProgramUniform2ui(program, location, v0, v1);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint *value)
	{
		ngl::glProgramUniform2uiv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2)
	{
		ngl::glProgramUniform3i(program, location, v0, v1, v2);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint *value)
	{
		ngl::glProgramUniform3iv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
	{
		ngl::glProgramUniform3f(program, location, v0, v1, v2);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat *value)
	{
		ngl::glProgramUniform3fv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2)
	{
		ngl::glProgramUniform3d(program, location, v0, v1, v2);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble *value)
	{
		ngl::glProgramUniform3dv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)
	{
		ngl::glProgramUniform3ui(program, location, v0, v1, v2);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint *value)
	{
		ngl::glProgramUniform3uiv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
	{
		ngl::glProgramUniform4i(program, location, v0, v1, v2, v3);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint *value)
	{
		ngl::glProgramUniform4iv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
	{
		ngl::glProgramUniform4f(program, location, v0, v1, v2, v3);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat *value)
	{
		ngl::glProgramUniform4fv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
	{
		ngl::glProgramUniform4d(program, location, v0, v1, v2, v3);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble *value)
	{
		ngl::glProgramUniform4dv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
	{
		ngl::glProgramUniform4ui(program, location, v0, v1, v2, v3);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint *value)
	{
		ngl::glProgramUniform4uiv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix2fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix3fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix4fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glProgramUniformMatrix2dv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glProgramUniformMatrix3dv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glProgramUniformMatrix4dv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix2x3fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix3x2fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix2x4fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix4x2fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix3x4fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix4x3fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glProgramUniformMatrix2x3dv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glProgramUniformMatrix3x2dv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glProgramUniformMatrix2x4dv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glProgramUniformMatrix4x2dv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glProgramUniformMatrix3x4dv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
	{
		ngl::glProgramUniformMatrix4x3dv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglValidateProgramPipeline(GLuint pipeline)
	{
		ngl::glValidateProgramPipeline(pipeline);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
	{
		ngl::glGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribL1d(GLuint index, GLdouble x)
	{
		ngl::glVertexAttribL1d(index, x);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribL2d(GLuint index, GLdouble x, GLdouble y)
	{
		ngl::glVertexAttribL2d(index, x, y);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
	{
		ngl::glVertexAttribL3d(index, x, y, z);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
	{
		ngl::glVertexAttribL4d(index, x, y, z, w);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribL1dv(GLuint index, const GLdouble *v)
	{
		ngl::glVertexAttribL1dv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribL2dv(GLuint index, const GLdouble *v)
	{
		ngl::glVertexAttribL2dv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribL3dv(GLuint index, const GLdouble *v)
	{
		ngl::glVertexAttribL3dv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribL4dv(GLuint index, const GLdouble *v)
	{
		ngl::glVertexAttribL4dv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer)
	{
		ngl::glVertexAttribLPointer(index, size, type, stride, pointer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble *params)
	{
		ngl::glGetVertexAttribLdv(index, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglViewportArrayv(GLuint first, GLsizei count, const GLfloat *v)
	{
		ngl::glViewportArrayv(first, count, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
	{
		ngl::glViewportIndexedf(index, x, y, w, h);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglViewportIndexedfv(GLuint index, const GLfloat *v)
	{
		ngl::glViewportIndexedfv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglScissorArrayv(GLuint first, GLsizei count, const GLint *v)
	{
		ngl::glScissorArrayv(first, count, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height)
	{
		ngl::glScissorIndexed(index, left, bottom, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglScissorIndexedv(GLuint index, const GLint *v)
	{
		ngl::glScissorIndexedv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDepthRangeArrayv(GLuint first, GLsizei count, const GLdouble *v)
	{
		ngl::glDepthRangeArrayv(first, count, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f)
	{
		ngl::glDepthRangeIndexed(index, n, f);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetFloati_v(GLenum target, GLuint index, GLfloat *data)
	{
		ngl::glGetFloati_v(target, index, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetDoublei_v(GLenum target, GLuint index, GLdouble *data)
	{
		ngl::glGetDoublei_v(target, index, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 4.2
	void APIENTRY dglDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance)
	{
		ngl::glDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance)
	{
		ngl::glDrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance)
	{
		ngl::glDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint *params)
	{
		ngl::glGetInternalformativ(target, internalformat, pname, count, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint *params)
	{
		ngl::glGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)
	{
		ngl::glBindImageTexture(unit, texture, level, layered, layer, access, format);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglMemoryBarrier(GLbitfield barriers)
	{
		ngl::glMemoryBarrier(barriers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
	{
		ngl::glTexStorage1D(target, levels, internalformat, width);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
	{
		ngl::glTexStorage2D(target, levels, internalformat, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
	{
		ngl::glTexStorage3D(target, levels, internalformat, width, height, depth);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount)
	{
		ngl::glDrawTransformFeedbackInstanced(mode, id, instancecount);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount)
	{
		ngl::glDrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 4.3
	void APIENTRY dglClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data)
	{
		ngl::glClearBufferData(target, internalformat, format, type, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data)
	{
		ngl::glClearBufferSubData(target, internalformat, offset, size, format, type, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z)
	{
		ngl::glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDispatchComputeIndirect(GLintptr indirect)
	{
		ngl::glDispatchComputeIndirect(indirect);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)
	{
		ngl::glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglFramebufferParameteri(GLenum target, GLenum pname, GLint param)
	{
		ngl::glFramebufferParameteri(target, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetFramebufferParameteriv(GLenum target, GLenum pname, GLint *params)
	{
		ngl::glGetFramebufferParameteriv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint64 *params)
	{
		ngl::glGetInternalformati64v(target, internalformat, pname, count, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth)
	{
		ngl::glInvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglInvalidateTexImage(GLuint texture, GLint level)
	{
		ngl::glInvalidateTexImage(texture, level);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length)
	{
		ngl::glInvalidateBufferSubData(buffer, offset, length);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglInvalidateBufferData(GLuint buffer)
	{
		ngl::glInvalidateBufferData(buffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments)
	{
		ngl::glInvalidateFramebuffer(target, numAttachments, attachments);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		ngl::glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglMultiDrawArraysIndirect(GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride)
	{
		ngl::glMultiDrawArraysIndirect(mode, indirect, drawcount, stride);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglMultiDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride)
	{
		ngl::glMultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint *params)
	{
		ngl::glGetProgramInterfaceiv(program, programInterface, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLuint APIENTRY dglGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar *name)
	{
		auto result{ ngl::glGetProgramResourceIndex(program, programInterface, name) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name)
	{
		ngl::glGetProgramResourceName(program, programInterface, index, bufSize, length, name);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei count, GLsizei *length, GLint *params)
	{
		ngl::glGetProgramResourceiv(program, programInterface, index, propCount, props, count, length, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLint APIENTRY dglGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar *name)
	{
		auto result{ ngl::glGetProgramResourceLocation(program, programInterface, name) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	GLint APIENTRY dglGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar *name)
	{
		auto result{ ngl::glGetProgramResourceLocationIndex(program, programInterface, name) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding)
	{
		ngl::glShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
	{
		ngl::glTexBufferRange(target, internalformat, buffer, offset, size);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
	{
		ngl::glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
	{
		ngl::glTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers)
	{
		ngl::glTextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
	{
		ngl::glBindVertexBuffer(bindingindex, buffer, offset, stride);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
	{
		ngl::glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
	{
		ngl::glVertexAttribIFormat(attribindex, size, type, relativeoffset);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
	{
		ngl::glVertexAttribLFormat(attribindex, size, type, relativeoffset);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexAttribBinding(GLuint attribindex, GLuint bindingindex)
	{
		ngl::glVertexAttribBinding(attribindex, bindingindex);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexBindingDivisor(GLuint bindingindex, GLuint divisor)
	{
		ngl::glVertexBindingDivisor(bindingindex, divisor);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled)
	{
		ngl::glDebugMessageControl(source, type, severity, count, ids, enabled);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf)
	{
		ngl::glDebugMessageInsert(source, type, id, severity, length, buf);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDebugMessageCallback(GLDEBUGPROC callback, const void *userParam)
	{
		ngl::glDebugMessageCallback(callback, userParam);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLuint APIENTRY dglGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog)
	{
		auto result{ ngl::glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar *message)
	{
		ngl::glPushDebugGroup(source, id, length, message);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglPopDebugGroup()
	{
		ngl::glPopDebugGroup();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar *label)
	{
		ngl::glObjectLabel(identifier, name, length, label);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label)
	{
		ngl::glGetObjectLabel(identifier, name, bufSize, length, label);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglObjectPtrLabel(const void *ptr, GLsizei length, const GLchar *label)
	{
		ngl::glObjectPtrLabel(ptr, length, label);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetObjectPtrLabel(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label)
	{
		ngl::glGetObjectPtrLabel(ptr, bufSize, length, label);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 4.4
	void APIENTRY dglBufferStorage(GLenum target, GLsizeiptr size, const void *data, GLbitfield flags)
	{
		ngl::glBufferStorage(target, size, data, flags);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void *data)
	{
		ngl::glClearTexImage(texture, level, format, type, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data)
	{
		ngl::glClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint *buffers)
	{
		ngl::glBindBuffersBase(target, first, count, buffers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes)
	{
		ngl::glBindBuffersRange(target, first, count, buffers, offsets, sizes);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindTextures(GLuint first, GLsizei count, const GLuint *textures)
	{
		ngl::glBindTextures(first, count, textures);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindSamplers(GLuint first, GLsizei count, const GLuint *samplers)
	{
		ngl::glBindSamplers(first, count, samplers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindImageTextures(GLuint first, GLsizei count, const GLuint *textures)
	{
		ngl::glBindImageTextures(first, count, textures);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindVertexBuffers(GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides)
	{
		ngl::glBindVertexBuffers(first, count, buffers, offsets, strides);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 4.5
	void APIENTRY dglClipControl(GLenum origin, GLenum depth)
	{
		ngl::glClipControl(origin, depth);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCreateTransformFeedbacks(GLsizei n, GLuint *ids)
	{
		ngl::glCreateTransformFeedbacks(n, ids);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer)
	{
		ngl::glTransformFeedbackBufferBase(xfb, index, buffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
	{
		ngl::glTransformFeedbackBufferRange(xfb, index, buffer, offset, size);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint *param)
	{
		ngl::glGetTransformFeedbackiv(xfb, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint *param)
	{
		ngl::glGetTransformFeedbacki_v(xfb, pname, index, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64 *param)
	{
		ngl::glGetTransformFeedbacki64_v(xfb, pname, index, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCreateBuffers(GLsizei n, GLuint *buffers)
	{
		ngl::glCreateBuffers(n, buffers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags)
	{
		ngl::glNamedBufferStorage(buffer, size, data, flags);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglNamedBufferData(GLuint buffer, GLsizeiptr size, const void *data, GLenum usage)
	{
		ngl::glNamedBufferData(buffer, size, data, usage);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data)
	{
		ngl::glNamedBufferSubData(buffer, offset, size, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		ngl::glCopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data)
	{
		ngl::glClearNamedBufferData(buffer, internalformat, format, type, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data)
	{
		ngl::glClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void *APIENTRY dglMapNamedBuffer(GLuint buffer, GLenum access)
	{
		auto result{ ngl::glMapNamedBuffer(buffer, access) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void *APIENTRY dglMapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access)
	{
		auto result{ ngl::glMapNamedBufferRange(buffer, offset, length, access) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	GLboolean APIENTRY dglUnmapNamedBuffer(GLuint buffer)
	{
		auto result{ ngl::glUnmapNamedBuffer(buffer) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglFlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length)
	{
		ngl::glFlushMappedNamedBufferRange(buffer, offset, length);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint *params)
	{
		ngl::glGetNamedBufferParameteriv(buffer, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64 *params)
	{
		ngl::glGetNamedBufferParameteri64v(buffer, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetNamedBufferPointerv(GLuint buffer, GLenum pname, void **params)
	{
		ngl::glGetNamedBufferPointerv(buffer, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void *data)
	{
		ngl::glGetNamedBufferSubData(buffer, offset, size, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCreateFramebuffers(GLsizei n, GLuint *framebuffers)
	{
		ngl::glCreateFramebuffers(n, framebuffers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglNamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
	{
		ngl::glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglNamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param)
	{
		ngl::glNamedFramebufferParameteri(framebuffer, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level)
	{
		ngl::glNamedFramebufferTexture(framebuffer, attachment, texture, level);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer)
	{
		ngl::glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf)
	{
		ngl::glNamedFramebufferDrawBuffer(framebuffer, buf);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum *bufs)
	{
		ngl::glNamedFramebufferDrawBuffers(framebuffer, n, bufs);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src)
	{
		ngl::glNamedFramebufferReadBuffer(framebuffer, src);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglInvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments)
	{
		ngl::glInvalidateNamedFramebufferData(framebuffer, numAttachments, attachments);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglInvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		ngl::glInvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint *value)
	{
		ngl::glClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint *value)
	{
		ngl::glClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat *value)
	{
		ngl::glClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
	{
		ngl::glClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
	{
		ngl::glBlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLenum APIENTRY dglCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target)
	{
		auto result{ ngl::glCheckNamedFramebufferStatus(framebuffer, target) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglGetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint *param)
	{
		ngl::glGetNamedFramebufferParameteriv(framebuffer, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params)
	{
		ngl::glGetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCreateRenderbuffers(GLsizei n, GLuint *renderbuffers)
	{
		ngl::glCreateRenderbuffers(n, renderbuffers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglNamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height)
	{
		ngl::glNamedRenderbufferStorage(renderbuffer, internalformat, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
	{
		ngl::glNamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint *params)
	{
		ngl::glGetNamedRenderbufferParameteriv(renderbuffer, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCreateTextures(GLenum target, GLsizei n, GLuint *textures)
	{
		ngl::glCreateTextures(target, n, textures);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer)
	{
		ngl::glTextureBuffer(texture, internalformat, buffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
	{
		ngl::glTextureBufferRange(texture, internalformat, buffer, offset, size);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width)
	{
		ngl::glTextureStorage1D(texture, levels, internalformat, width);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
	{
		ngl::glTextureStorage2D(texture, levels, internalformat, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
	{
		ngl::glTextureStorage3D(texture, levels, internalformat, width, height, depth);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
	{
		ngl::glTextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
	{
		ngl::glTextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels)
	{
		ngl::glTextureSubImage1D(texture, level, xoffset, width, format, type, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels)
	{
		ngl::glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels)
	{
		ngl::glTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data)
	{
		ngl::glCompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data)
	{
		ngl::glCompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data)
	{
		ngl::glCompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
	{
		ngl::glCopyTextureSubImage1D(texture, level, xoffset, x, y, width);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		ngl::glCopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		ngl::glCopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureParameterf(GLuint texture, GLenum pname, GLfloat param)
	{
		ngl::glTextureParameterf(texture, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureParameterfv(GLuint texture, GLenum pname, const GLfloat *param)
	{
		ngl::glTextureParameterfv(texture, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureParameteri(GLuint texture, GLenum pname, GLint param)
	{
		ngl::glTextureParameteri(texture, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureParameterIiv(GLuint texture, GLenum pname, const GLint *params)
	{
		ngl::glTextureParameterIiv(texture, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureParameterIuiv(GLuint texture, GLenum pname, const GLuint *params)
	{
		ngl::glTextureParameterIuiv(texture, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureParameteriv(GLuint texture, GLenum pname, const GLint *param)
	{
		ngl::glTextureParameteriv(texture, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGenerateTextureMipmap(GLuint texture)
	{
		ngl::glGenerateTextureMipmap(texture);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglBindTextureUnit(GLuint unit, GLuint texture)
	{
		ngl::glBindTextureUnit(unit, texture);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels)
	{
		ngl::glGetTextureImage(texture, level, format, type, bufSize, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void *pixels)
	{
		ngl::glGetCompressedTextureImage(texture, level, bufSize, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat *params)
	{
		ngl::glGetTextureLevelParameterfv(texture, level, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint *params)
	{
		ngl::glGetTextureLevelParameteriv(texture, level, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTextureParameterfv(GLuint texture, GLenum pname, GLfloat *params)
	{
		ngl::glGetTextureParameterfv(texture, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTextureParameterIiv(GLuint texture, GLenum pname, GLint *params)
	{
		ngl::glGetTextureParameterIiv(texture, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint *params)
	{
		ngl::glGetTextureParameterIuiv(texture, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTextureParameteriv(GLuint texture, GLenum pname, GLint *params)
	{
		ngl::glGetTextureParameteriv(texture, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCreateVertexArrays(GLsizei n, GLuint *arrays)
	{
		ngl::glCreateVertexArrays(n, arrays);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglDisableVertexArrayAttrib(GLuint vaobj, GLuint index)
	{
		ngl::glDisableVertexArrayAttrib(vaobj, index);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglEnableVertexArrayAttrib(GLuint vaobj, GLuint index)
	{
		ngl::glEnableVertexArrayAttrib(vaobj, index);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexArrayElementBuffer(GLuint vaobj, GLuint buffer)
	{
		ngl::glVertexArrayElementBuffer(vaobj, buffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
	{
		ngl::glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides)
	{
		ngl::glVertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex)
	{
		ngl::glVertexArrayAttribBinding(vaobj, attribindex, bindingindex);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
	{
		ngl::glVertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
	{
		ngl::glVertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
	{
		ngl::glVertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglVertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor)
	{
		ngl::glVertexArrayBindingDivisor(vaobj, bindingindex, divisor);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetVertexArrayiv(GLuint vaobj, GLenum pname, GLint *param)
	{
		ngl::glGetVertexArrayiv(vaobj, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint *param)
	{
		ngl::glGetVertexArrayIndexediv(vaobj, index, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64 *param)
	{
		ngl::glGetVertexArrayIndexed64iv(vaobj, index, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCreateSamplers(GLsizei n, GLuint *samplers)
	{
		ngl::glCreateSamplers(n, samplers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCreateProgramPipelines(GLsizei n, GLuint *pipelines)
	{
		ngl::glCreateProgramPipelines(n, pipelines);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglCreateQueries(GLenum target, GLsizei n, GLuint *ids)
	{
		ngl::glCreateQueries(target, n, ids);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
	{
		ngl::glGetQueryBufferObjecti64v(id, buffer, pname, offset);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
	{
		ngl::glGetQueryBufferObjectiv(id, buffer, pname, offset);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
	{
		ngl::glGetQueryBufferObjectui64v(id, buffer, pname, offset);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
	{
		ngl::glGetQueryBufferObjectuiv(id, buffer, pname, offset);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglMemoryBarrierByRegion(GLbitfield barriers)
	{
		ngl::glMemoryBarrierByRegion(barriers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void *pixels)
	{
		ngl::glGetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void *pixels)
	{
		ngl::glGetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLenum APIENTRY dglGetGraphicsResetStatus()
	{
		auto result{ ngl::glGetGraphicsResetStatus() };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void APIENTRY dglGetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void *pixels)
	{
		ngl::glGetnCompressedTexImage(target, lod, bufSize, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels)
	{
		ngl::glGetnTexImage(target, level, format, type, bufSize, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble *params)
	{
		ngl::glGetnUniformdv(program, location, bufSize, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat *params)
	{
		ngl::glGetnUniformfv(program, location, bufSize, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint *params)
	{
		ngl::glGetnUniformiv(program, location, bufSize, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint *params)
	{
		ngl::glGetnUniformuiv(program, location, bufSize, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data)
	{
		ngl::glReadnPixels(x, y, width, height, format, type, bufSize, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglTextureBarrier()
	{
		ngl::glTextureBarrier();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 4.6
	void APIENTRY dglSpecializeShader(GLuint shader, const GLchar *pEntryPoint, GLuint numSpecializationConstants, const GLuint *pConstantIndex, const GLuint *pConstantValue)
	{
		ngl::glSpecializeShader(shader, pEntryPoint, numSpecializationConstants, pConstantIndex, pConstantValue);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglMultiDrawArraysIndirectCount(GLenum mode, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride)
	{
		ngl::glMultiDrawArraysIndirectCount(mode, indirect, drawcount, maxdrawcount, stride);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglMultiDrawElementsIndirectCount(GLenum mode, GLenum type, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride)
	{
		ngl::glMultiDrawElementsIndirectCount(mode, type, indirect, drawcount, maxdrawcount, stride);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void APIENTRY dglPolygonOffsetClamp(GLfloat factor, GLfloat units, GLfloat clamp)
	{
		ngl::glPolygonOffsetClamp(factor, units, clamp);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}
#elif defined(__ANDROID__)
	// 2.0
	void GL_APIENTRY dglActiveTexture(GLenum texture)
	{
		ngl::glActiveTexture(texture);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglAttachShader(GLuint program, GLuint shader)
	{
		ngl::glAttachShader(program, shader);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBindAttribLocation(GLuint program, GLuint index, const GLchar *name)
	{
		ngl::glBindAttribLocation(program, index, name);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBindBuffer(GLenum target, GLuint buffer)
	{
		ngl::glBindBuffer(target, buffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBindFramebuffer(GLenum target, GLuint framebuffer)
	{
		ngl::glBindFramebuffer(target, framebuffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBindRenderbuffer(GLenum target, GLuint renderbuffer)
	{
		ngl::glBindRenderbuffer(target, renderbuffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBindTexture(GLenum target, GLuint texture)
	{
		ngl::glBindTexture(target, texture);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
	{
		ngl::glBlendColor(red, green, blue, alpha);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBlendEquation(GLenum mode)
	{
		ngl::glBlendEquation(mode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
	{
		ngl::glBlendEquationSeparate(modeRGB, modeAlpha);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBlendFunc(GLenum sfactor, GLenum dfactor)
	{
		ngl::glBlendFunc(sfactor, dfactor);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
	{
		ngl::glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage)
	{
		ngl::glBufferData(target, size, data, usage);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data)
	{
		ngl::glBufferSubData(target, offset, size, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLenum GL_APIENTRY dglCheckFramebufferStatus(GLenum target)
	{
		GLenum result{ ngl::glCheckFramebufferStatus(target) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglClear(GLbitfield mask)
	{
		ngl::glClear(mask);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
	{
		ngl::glClearColor(red, green, blue, alpha);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglClearDepthf(GLfloat d)
	{
		ngl::glClearDepthf(d);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglClearStencil(GLint s)
	{
		ngl::glClearStencil(s);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
	{
		ngl::glColorMask(red, green, blue, alpha);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglCompileShader(GLuint shader)
	{
		ngl::glCompileShader(shader);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data)
	{
		ngl::glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data)
	{
		ngl::glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
	{
		ngl::glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		ngl::glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLuint GL_APIENTRY dglCreateProgram()
	{
		GLuint result{ ngl::glCreateProgram() };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	GLuint GL_APIENTRY dglCreateShader(GLenum type)
	{
		GLuint result{ ngl::glCreateShader(type) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglCullFace(GLenum mode)
	{
		ngl::glCullFace(mode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDeleteBuffers(GLsizei n, const GLuint *buffers)
	{
		ngl::glDeleteBuffers(n, buffers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDeleteFramebuffers(GLsizei n, const GLuint *framebuffers)
	{
		ngl::glDeleteFramebuffers(n, framebuffers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDeleteProgram(GLuint program)
	{
		ngl::glDeleteProgram(program);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers)
	{
		ngl::glDeleteRenderbuffers(n, renderbuffers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDeleteShader(GLuint shader)
	{
		ngl::glDeleteShader(shader);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDeleteTextures(GLsizei n, const GLuint *textures)
	{
		ngl::glDeleteTextures(n, textures);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDepthFunc(GLenum func)
	{
		ngl::glDepthFunc(func);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDepthMask(GLboolean flag)
	{
		ngl::glDepthMask(flag);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDepthRangef(GLfloat n, GLfloat f)
	{
		ngl::glDepthRangef(n, f);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDetachShader(GLuint program, GLuint shader)
	{
		ngl::glDetachShader(program, shader);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDisable(GLenum cap)
	{
		ngl::glDisable(cap);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDisableVertexAttribArray(GLuint index)
	{
		ngl::glDisableVertexAttribArray(index);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDrawArrays(GLenum mode, GLint first, GLsizei count)
	{
		ngl::glDrawArrays(mode, first, count);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices)
	{
		ngl::glDrawElements(mode, count, type, indices);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglEnable(GLenum cap)
	{
		ngl::glEnable(cap);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglEnableVertexAttribArray(GLuint index)
	{
		ngl::glEnableVertexAttribArray(index);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglFinish()
	{
		ngl::glFinish();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglFlush()
	{
		ngl::glFlush();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
	{
		ngl::glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
	{
		ngl::glFramebufferTexture2D(target, attachment, textarget, texture, level);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglFrontFace(GLenum mode)
	{
		ngl::glFrontFace(mode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGenBuffers(GLsizei n, GLuint *buffers)
	{
		ngl::glGenBuffers(n, buffers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGenerateMipmap(GLenum target)
	{
		ngl::glGenerateMipmap(target);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGenFramebuffers(GLsizei n, GLuint *framebuffers)
	{
		ngl::glGenFramebuffers(n, framebuffers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGenRenderbuffers(GLsizei n, GLuint *renderbuffers)
	{
		ngl::glGenRenderbuffers(n, renderbuffers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGenTextures(GLsizei n, GLuint *textures)
	{
		ngl::glGenTextures(n, textures);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name)
	{
		ngl::glGetActiveAttrib(program, index, bufSize, length, size, type, name);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name)
	{
		ngl::glGetActiveUniform(program, index, bufSize, length, size, type, name);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders)
	{
		ngl::glGetAttachedShaders(program, maxCount, count, shaders);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLint GL_APIENTRY dglGetAttribLocation(GLuint program, const GLchar *name)
	{
		GLint result{ ngl::glGetAttribLocation(program, name) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglGetBooleanv(GLenum pname, GLboolean *data)
	{
		ngl::glGetBooleanv(pname, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetBufferParameteriv(GLenum target, GLenum pname, GLint *params)
	{
		ngl::glGetBufferParameteriv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLenum GL_APIENTRY dglGetError()
	{
		GLenum result{ ngl::glGetError() };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglGetFloatv(GLenum pname, GLfloat *data)
	{
		ngl::glGetFloatv(pname, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint *params)
	{
		ngl::glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetIntegerv(GLenum pname, GLint *data)
	{
		ngl::glGetIntegerv(pname, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetProgramiv(GLuint program, GLenum pname, GLint *params)
	{
		ngl::glGetProgramiv(program, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
	{
		ngl::glGetProgramInfoLog(program, bufSize, length, infoLog);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params)
	{
		ngl::glGetRenderbufferParameteriv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetShaderiv(GLuint shader, GLenum pname, GLint *params)
	{
		ngl::glGetShaderiv(shader, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
	{
		ngl::glGetShaderInfoLog(shader, bufSize, length, infoLog);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision)
	{
		ngl::glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source)
	{
		ngl::glGetShaderSource(shader, bufSize, length, source);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	const GLubyte * GL_APIENTRY dglGetString(GLenum name)
	{
		const GLubyte *result{ ngl::glGetString(name) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglGetTexParameterfv(GLenum target, GLenum pname, GLfloat *params)
	{
		ngl::glGetTexParameterfv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetTexParameteriv(GLenum target, GLenum pname, GLint *params)
	{
		ngl::glGetTexParameteriv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetUniformfv(GLuint program, GLint location, GLfloat *params)
	{
		ngl::glGetUniformfv(program, location, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetUniformiv(GLuint program, GLint location, GLint *params)
	{
		ngl::glGetUniformiv(program, location, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLint GL_APIENTRY dglGetUniformLocation(GLuint program, const GLchar *name)
	{
		GLint result{ ngl::glGetUniformLocation(program, name) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglGetVertexAttribfv(GLuint index, GLenum pname, GLfloat *params)
	{
		ngl::glGetVertexAttribfv(index, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetVertexAttribiv(GLuint index, GLenum pname, GLint *params)
	{
		ngl::glGetVertexAttribiv(index, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetVertexAttribPointerv(GLuint index, GLenum pname, void **pointer)
	{
		ngl::glGetVertexAttribPointerv(index, pname, pointer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglHint(GLenum target, GLenum mode)
	{
		ngl::glHint(target, mode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean GL_APIENTRY dglIsBuffer(GLuint buffer)
	{
		GLboolean result{ ngl::glIsBuffer(buffer) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	GLboolean GL_APIENTRY dglIsEnabled(GLenum cap)
	{
		GLboolean result{ ngl::glIsEnabled(cap) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	GLboolean GL_APIENTRY dglIsFramebuffer(GLuint framebuffer)
	{
		GLboolean result{ ngl::glIsFramebuffer(framebuffer) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	GLboolean GL_APIENTRY dglIsProgram(GLuint program)
	{
		GLboolean result{ ngl::glIsProgram(program) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	GLboolean GL_APIENTRY dglIsRenderbuffer(GLuint renderbuffer)
	{
		GLboolean result{ ngl::glIsRenderbuffer(renderbuffer) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	GLboolean GL_APIENTRY dglIsShader(GLuint shader)
	{
		GLboolean result{ ngl::glIsShader(shader) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	GLboolean GL_APIENTRY dglIsTexture(GLuint texture)
	{
		GLboolean result{ ngl::glIsTexture(texture) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglLineWidth(GLfloat width)
	{
		ngl::glLineWidth(width);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglLinkProgram(GLuint program)
	{
		ngl::glLinkProgram(program);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglPixelStorei(GLenum pname, GLint param)
	{
		ngl::glPixelStorei(pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglPolygonOffset(GLfloat factor, GLfloat units)
	{
		ngl::glPolygonOffset(factor, units);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels)
	{
		ngl::glReadPixels(x, y, width, height, format, type, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglReleaseShaderCompiler()
	{
		ngl::glReleaseShaderCompiler();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
	{
		ngl::glRenderbufferStorage(target, internalformat, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglSampleCoverage(GLfloat value, GLboolean invert)
	{
		ngl::glSampleCoverage(value, invert);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglScissor(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		ngl::glScissor(x, y, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglShaderBinary(GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length)
	{
		ngl::glShaderBinary(count, shaders, binaryformat, binary, length);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length)
	{
		ngl::glShaderSource(shader, count, string, length);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglStencilFunc(GLenum func, GLint ref, GLuint mask)
	{
		ngl::glStencilFunc(func, ref, mask);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
	{
		ngl::glStencilFuncSeparate(face, func, ref, mask);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglStencilMask(GLuint mask)
	{
		ngl::glStencilMask(mask);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglStencilMaskSeparate(GLenum face, GLuint mask)
	{
		ngl::glStencilMaskSeparate(face, mask);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
	{
		ngl::glStencilOp(fail, zfail, zpass);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
	{
		ngl::glStencilOpSeparate(face, sfail, dpfail, dppass);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)
	{
		ngl::glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTexParameterf(GLenum target, GLenum pname, GLfloat param)
	{
		ngl::glTexParameterf(target, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTexParameterfv(GLenum target, GLenum pname, const GLfloat *params)
	{
		ngl::glTexParameterfv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTexParameteri(GLenum target, GLenum pname, GLint param)
	{
		ngl::glTexParameteri(target, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTexParameteriv(GLenum target, GLenum pname, const GLint *params)
	{
		ngl::glTexParameteriv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels)
	{
		ngl::glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform1f(GLint location, GLfloat v0)
	{
		ngl::glUniform1f(location, v0);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform1fv(GLint location, GLsizei count, const GLfloat *value)
	{
		ngl::glUniform1fv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform1i(GLint location, GLint v0)
	{
		ngl::glUniform1i(location, v0);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform1iv(GLint location, GLsizei count, const GLint *value)
	{
		ngl::glUniform1iv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform2f(GLint location, GLfloat v0, GLfloat v1)
	{
		ngl::glUniform2f(location, v0, v1);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform2fv(GLint location, GLsizei count, const GLfloat *value)
	{
		ngl::glUniform2fv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform2i(GLint location, GLint v0, GLint v1)
	{
		ngl::glUniform2i(location, v0, v1);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform2iv(GLint location, GLsizei count, const GLint *value)
	{
		ngl::glUniform2iv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
	{
		ngl::glUniform3f(location, v0, v1, v2);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform3fv(GLint location, GLsizei count, const GLfloat *value)
	{
		ngl::glUniform3fv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform3i(GLint location, GLint v0, GLint v1, GLint v2)
	{
		ngl::glUniform3i(location, v0, v1, v2);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform3iv(GLint location, GLsizei count, const GLint *value)
	{
		ngl::glUniform3iv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
	{
		ngl::glUniform4f(location, v0, v1, v2, v3);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform4fv(GLint location, GLsizei count, const GLfloat *value)
	{
		ngl::glUniform4fv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
	{
		ngl::glUniform4i(location, v0, v1, v2, v3);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform4iv(GLint location, GLsizei count, const GLint *value)
	{
		ngl::glUniform4iv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix2fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix3fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix4fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUseProgram(GLuint program)
	{
		ngl::glUseProgram(program);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglValidateProgram(GLuint program)
	{
		ngl::glValidateProgram(program);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttrib1f(GLuint index, GLfloat x)
	{
		ngl::glVertexAttrib1f(index, x);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttrib1fv(GLuint index, const GLfloat *v)
	{
		ngl::glVertexAttrib1fv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
	{
		ngl::glVertexAttrib2f(index, x, y);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttrib2fv(GLuint index, const GLfloat *v)
	{
		ngl::glVertexAttrib2fv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
	{
		ngl::glVertexAttrib3f(index, x, y, z);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttrib3fv(GLuint index, const GLfloat *v)
	{
		ngl::glVertexAttrib3fv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
	{
		ngl::glVertexAttrib4f(index, x, y, z, w);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttrib4fv(GLuint index, const GLfloat *v)
	{
		ngl::glVertexAttrib4fv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
	{
		ngl::glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglViewport(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		ngl::glViewport(x, y, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 3.0
	void GL_APIENTRY dglReadBuffer(GLenum src)
	{
		ngl::glReadBuffer(src);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices)
	{
		ngl::glDrawRangeElements(mode, start, end, count, type, indices);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels)
	{
		ngl::glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels)
	{
		ngl::glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		ngl::glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data)
	{
		ngl::glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data)
	{
		ngl::glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGenQueries(GLsizei n, GLuint *ids)
	{
		ngl::glGenQueries(n, ids);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDeleteQueries(GLsizei n, const GLuint *ids)
	{
		ngl::glDeleteQueries(n, ids);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean GL_APIENTRY dglIsQuery(GLuint id)
	{
		GLboolean result{ ngl::glIsQuery(id) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglBeginQuery(GLenum target, GLuint id)
	{
		ngl::glBeginQuery(target, id);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglEndQuery(GLenum target)
	{
		ngl::glEndQuery(target);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetQueryiv(GLenum target, GLenum pname, GLint *params)
	{
		ngl::glGetQueryiv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetQueryObjectuiv(GLuint id, GLenum pname, GLuint *params)
	{
		ngl::glGetQueryObjectuiv(id, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean GL_APIENTRY dglUnmapBuffer(GLenum target)
	{
		GLboolean result{ ngl::glUnmapBuffer(target) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglGetBufferPointerv(GLenum target, GLenum pname, void **params)
	{
		ngl::glGetBufferPointerv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDrawBuffers(GLsizei n, const GLenum *bufs)
	{
		ngl::glDrawBuffers(n, bufs);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix2x3fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix3x2fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix2x4fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix4x2fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix3x4fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glUniformMatrix4x3fv(location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
	{
		ngl::glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
	{
		ngl::glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
	{
		ngl::glFramebufferTextureLayer(target, attachment, texture, level, layer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void *GL_APIENTRY dglMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
	{
		void *result{ ngl::glMapBufferRange(target, offset, length, access) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
	{
		ngl::glFlushMappedBufferRange(target, offset, length);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBindVertexArray(GLuint array)
	{
		ngl::glBindVertexArray(array);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDeleteVertexArrays(GLsizei n, const GLuint *arrays)
	{
		ngl::glDeleteVertexArrays(n, arrays);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGenVertexArrays(GLsizei n, GLuint *arrays)
	{
		ngl::glGenVertexArrays(n, arrays);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean GL_APIENTRY dglIsVertexArray(GLuint array)
	{
		GLboolean result{ ngl::glIsVertexArray(array) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglGetIntegeri_v(GLenum target, GLuint index, GLint *data)
	{
		ngl::glGetIntegeri_v(target, index, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBeginTransformFeedback(GLenum primitiveMode)
	{
		ngl::glBeginTransformFeedback(primitiveMode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglEndTransformFeedback()
	{
		ngl::glEndTransformFeedback();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
	{
		ngl::glBindBufferRange(target, index, buffer, offset, size);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBindBufferBase(GLenum target, GLuint index, GLuint buffer)
	{
		ngl::glBindBufferBase(target, index, buffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode)
	{
		ngl::glTransformFeedbackVaryings(program, count, varyings, bufferMode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name)
	{
		ngl::glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer)
	{
		ngl::glVertexAttribIPointer(index, size, type, stride, pointer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetVertexAttribIiv(GLuint index, GLenum pname, GLint *params)
	{
		ngl::glGetVertexAttribIiv(index, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint *params)
	{
		ngl::glGetVertexAttribIuiv(index, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
	{
		ngl::glVertexAttribI4i(index, x, y, z, w);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
	{
		ngl::glVertexAttribI4ui(index, x, y, z, w);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttribI4iv(GLuint index, const GLint *v)
	{
		ngl::glVertexAttribI4iv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttribI4uiv(GLuint index, const GLuint *v)
	{
		ngl::glVertexAttribI4uiv(index, v);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetUniformuiv(GLuint program, GLint location, GLuint *params)
	{
		ngl::glGetUniformuiv(program, location, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLint GL_APIENTRY dglGetFragDataLocation(GLuint program, const GLchar *name)
	{
		GLint result{ ngl::glGetFragDataLocation(program, name) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglUniform1ui(GLint location, GLuint v0)
	{
		ngl::glUniform1ui(location, v0);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform2ui(GLint location, GLuint v0, GLuint v1)
	{
		ngl::glUniform2ui(location, v0, v1);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
	{
		ngl::glUniform3ui(location, v0, v1, v2);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
	{
		ngl::glUniform4ui(location, v0, v1, v2, v3);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform1uiv(GLint location, GLsizei count, const GLuint *value)
	{
		ngl::glUniform1uiv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform2uiv(GLint location, GLsizei count, const GLuint *value)
	{
		ngl::glUniform2uiv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform3uiv(GLint location, GLsizei count, const GLuint *value)
	{
		ngl::glUniform3uiv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniform4uiv(GLint location, GLsizei count, const GLuint *value)
	{
		ngl::glUniform4uiv(location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint *value)
	{
		ngl::glClearBufferiv(buffer, drawbuffer, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint *value)
	{
		ngl::glClearBufferuiv(buffer, drawbuffer, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat *value)
	{
		ngl::glClearBufferfv(buffer, drawbuffer, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
	{
		ngl::glClearBufferfi(buffer, drawbuffer, depth, stencil);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	const GLubyte * GL_APIENTRY dglGetStringi(GLenum name, GLuint index)
	{
		const GLubyte *result{ ngl::glGetStringi(name, index) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		ngl::glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices)
	{
		ngl::glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params)
	{
		ngl::glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLuint GL_APIENTRY dglGetUniformBlockIndex(GLuint program, const GLchar *uniformBlockName)
	{
		GLuint result{ ngl::glGetUniformBlockIndex(program, uniformBlockName) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params)
	{
		ngl::glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName)
	{
		ngl::glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
	{
		ngl::glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
	{
		ngl::glDrawArraysInstanced(mode, first, count, instancecount);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount)
	{
		ngl::glDrawElementsInstanced(mode, count, type, indices, instancecount);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLsync GL_APIENTRY dglFenceSync(GLenum condition, GLbitfield flags)
	{
		GLsync result{ ngl::glFenceSync(condition, flags) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	GLboolean GL_APIENTRY dglIsSync(GLsync sync)
	{
		GLboolean result{ ngl::glIsSync(sync) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglDeleteSync(GLsync sync)
	{
		ngl::glDeleteSync(sync);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLenum GL_APIENTRY dglClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
	{
		GLenum result{ ngl::glClientWaitSync(sync, flags, timeout) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
	{
		ngl::glWaitSync(sync, flags, timeout);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetInteger64v(GLenum pname, GLint64 *data)
	{
		ngl::glGetInteger64v(pname, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values)
	{
		ngl::glGetSynciv(sync, pname, bufSize, length, values);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetInteger64i_v(GLenum target, GLuint index, GLint64 *data)
	{
		ngl::glGetInteger64i_v(target, index, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 *params)
	{
		ngl::glGetBufferParameteri64v(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGenSamplers(GLsizei count, GLuint *samplers)
	{
		ngl::glGenSamplers(count, samplers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDeleteSamplers(GLsizei count, const GLuint *samplers)
	{
		ngl::glDeleteSamplers(count, samplers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean GL_APIENTRY dglIsSampler(GLuint sampler)
	{
		GLboolean result{ ngl::glIsSampler(sampler) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglBindSampler(GLuint unit, GLuint sampler)
	{
		ngl::glBindSampler(unit, sampler);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglSamplerParameteri(GLuint sampler, GLenum pname, GLint param)
	{
		ngl::glSamplerParameteri(sampler, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglSamplerParameteriv(GLuint sampler, GLenum pname, const GLint *param)
	{
		ngl::glSamplerParameteriv(sampler, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
	{
		ngl::glSamplerParameterf(sampler, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat *param)
	{
		ngl::glSamplerParameterfv(sampler, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint *params)
	{
		ngl::glGetSamplerParameteriv(sampler, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat *params)
	{
		ngl::glGetSamplerParameterfv(sampler, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttribDivisor(GLuint index, GLuint divisor)
	{
		ngl::glVertexAttribDivisor(index, divisor);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBindTransformFeedback(GLenum target, GLuint id)
	{
		ngl::glBindTransformFeedback(target, id);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDeleteTransformFeedbacks(GLsizei n, const GLuint *ids)
	{
		ngl::glDeleteTransformFeedbacks(n, ids);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGenTransformFeedbacks(GLsizei n, GLuint *ids)
	{
		ngl::glGenTransformFeedbacks(n, ids);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean GL_APIENTRY dglIsTransformFeedback(GLuint id)
	{
		GLboolean result{ ngl::glIsTransformFeedback(id) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglPauseTransformFeedback()
	{
		ngl::glPauseTransformFeedback();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglResumeTransformFeedback()
	{
		ngl::glResumeTransformFeedback();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary)
	{
		ngl::glGetProgramBinary(program, bufSize, length, binaryFormat, binary);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramBinary(GLuint program, GLenum binaryFormat, const void *binary, GLsizei length)
	{
		ngl::glProgramBinary(program, binaryFormat, binary, length);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramParameteri(GLuint program, GLenum pname, GLint value)
	{
		ngl::glProgramParameteri(program, pname, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments)
	{
		ngl::glInvalidateFramebuffer(target, numAttachments, attachments);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		ngl::glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
	{
		ngl::glTexStorage2D(target, levels, internalformat, width, height);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
	{
		ngl::glTexStorage3D(target, levels, internalformat, width, height, depth);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params)
	{
		ngl::glGetInternalformativ(target, internalformat, pname, bufSize, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 3.1
	void GL_APIENTRY dglDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z)
	{
		ngl::glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDispatchComputeIndirect(GLintptr indirect)
	{
		ngl::glDispatchComputeIndirect(indirect);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDrawArraysIndirect(GLenum mode, const void *indirect)
	{
		ngl::glDrawArraysIndirect(mode, indirect);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect)
	{
		ngl::glDrawElementsIndirect(mode, type, indirect);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglFramebufferParameteri(GLenum target, GLenum pname, GLint param)
	{
		ngl::glFramebufferParameteri(target, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetFramebufferParameteriv(GLenum target, GLenum pname, GLint *params)
	{
		ngl::glGetFramebufferParameteriv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint *params)
	{
		ngl::glGetProgramInterfaceiv(program, programInterface, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLuint GL_APIENTRY dglGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar *name)
	{
		GLuint result{ ngl::glGetProgramResourceIndex(program, programInterface, name) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name)
	{
		ngl::glGetProgramResourceName(program, programInterface, index, bufSize, length, name);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params)
	{
		ngl::glGetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLint GL_APIENTRY dglGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar *name)
	{
		GLint result{ ngl::glGetProgramResourceLocation(program, programInterface, name) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program)
	{
		ngl::glUseProgramStages(pipeline, stages, program);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglActiveShaderProgram(GLuint pipeline, GLuint program)
	{
		ngl::glActiveShaderProgram(pipeline, program);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLuint GL_APIENTRY dglCreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const*strings)
	{
		GLuint result{ ngl::glCreateShaderProgramv(type, count, strings) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglBindProgramPipeline(GLuint pipeline)
	{
		ngl::glBindProgramPipeline(pipeline);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDeleteProgramPipelines(GLsizei n, const GLuint *pipelines)
	{
		ngl::glDeleteProgramPipelines(n, pipelines);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGenProgramPipelines(GLsizei n, GLuint *pipelines)
	{
		ngl::glGenProgramPipelines(n, pipelines);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean GL_APIENTRY dglIsProgramPipeline(GLuint pipeline)
	{
		GLboolean result{ ngl::glIsProgramPipeline(pipeline) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint *params)
	{
		ngl::glGetProgramPipelineiv(pipeline, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform1i(GLuint program, GLint location, GLint v0)
	{
		ngl::glProgramUniform1i(program, location, v0);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1)
	{
		ngl::glProgramUniform2i(program, location, v0, v1);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2)
	{
		ngl::glProgramUniform3i(program, location, v0, v1, v2);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
	{
		ngl::glProgramUniform4i(program, location, v0, v1, v2, v3);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform1ui(GLuint program, GLint location, GLuint v0)
	{
		ngl::glProgramUniform1ui(program, location, v0);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1)
	{
		ngl::glProgramUniform2ui(program, location, v0, v1);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)
	{
		ngl::glProgramUniform3ui(program, location, v0, v1, v2);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
	{
		ngl::glProgramUniform4ui(program, location, v0, v1, v2, v3);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform1f(GLuint program, GLint location, GLfloat v0)
	{
		ngl::glProgramUniform1f(program, location, v0);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1)
	{
		ngl::glProgramUniform2f(program, location, v0, v1);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
	{
		ngl::glProgramUniform3f(program, location, v0, v1, v2);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
	{
		ngl::glProgramUniform4f(program, location, v0, v1, v2, v3);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint *value)
	{
		ngl::glProgramUniform1iv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint *value)
	{
		ngl::glProgramUniform2iv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint *value)
	{
		ngl::glProgramUniform3iv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint *value)
	{
		ngl::glProgramUniform4iv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint *value)
	{
		ngl::glProgramUniform1uiv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint *value)
	{
		ngl::glProgramUniform2uiv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint *value)
	{
		ngl::glProgramUniform3uiv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint *value)
	{
		ngl::glProgramUniform4uiv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat *value)
	{
		ngl::glProgramUniform1fv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat *value)
	{
		ngl::glProgramUniform2fv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat *value)
	{
		ngl::glProgramUniform3fv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat *value)
	{
		ngl::glProgramUniform4fv(program, location, count, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix2fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix3fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix4fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix2x3fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix3x2fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix2x4fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix4x2fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix3x4fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		ngl::glProgramUniformMatrix4x3fv(program, location, count, transpose, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglValidateProgramPipeline(GLuint pipeline)
	{
		ngl::glValidateProgramPipeline(pipeline);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
	{
		ngl::glGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)
	{
		ngl::glBindImageTexture(unit, texture, level, layered, layer, access, format);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetBooleani_v(GLenum target, GLuint index, GLboolean *data)
	{
		ngl::glGetBooleani_v(target, index, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglMemoryBarrier(GLbitfield barriers)
	{
		ngl::glMemoryBarrier(barriers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglMemoryBarrierByRegion(GLbitfield barriers)
	{
		ngl::glMemoryBarrierByRegion(barriers);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
	{
		ngl::glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetMultisamplefv(GLenum pname, GLuint index, GLfloat *val)
	{
		ngl::glGetMultisamplefv(pname, index, val);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglSampleMaski(GLuint maskNumber, GLbitfield mask)
	{
		ngl::glSampleMaski(maskNumber, mask);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint *params)
	{
		ngl::glGetTexLevelParameteriv(target, level, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat *params)
	{
		ngl::glGetTexLevelParameterfv(target, level, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
	{
		ngl::glBindVertexBuffer(bindingindex, buffer, offset, stride);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
	{
		ngl::glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
	{
		ngl::glVertexAttribIFormat(attribindex, size, type, relativeoffset);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexAttribBinding(GLuint attribindex, GLuint bindingindex)
	{
		ngl::glVertexAttribBinding(attribindex, bindingindex);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglVertexBindingDivisor(GLuint bindingindex, GLuint divisor)
	{
		ngl::glVertexBindingDivisor(bindingindex, divisor);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	// 3.2
	void GL_APIENTRY dglBlendBarrier()
	{
		ngl::glBlendBarrier();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)
	{
		ngl::glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled)
	{
		ngl::glDebugMessageControl(source, type, severity, count, ids, enabled);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf)
	{
		ngl::glDebugMessageInsert(source, type, id, severity, length, buf);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDebugMessageCallback(GLDEBUGPROC callback, const void *userParam)
	{
		ngl::glDebugMessageCallback(callback, userParam);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLuint GL_APIENTRY dglGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog)
	{
		GLuint result{ ngl::glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar *message)
	{
		ngl::glPushDebugGroup(source, id, length, message);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglPopDebugGroup()
	{
		ngl::glPopDebugGroup();
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar *label)
	{
		ngl::glObjectLabel(identifier, name, length, label);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label)
	{
		ngl::glGetObjectLabel(identifier, name, bufSize, length, label);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglObjectPtrLabel(const void *ptr, GLsizei length, const GLchar *label)
	{
		ngl::glObjectPtrLabel(ptr, length, label);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetObjectPtrLabel(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label)
	{
		ngl::glGetObjectPtrLabel(ptr, bufSize, length, label);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetPointerv(GLenum pname, void **params)
	{
		ngl::glGetPointerv(pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglEnablei(GLenum target, GLuint index)
	{
		ngl::glEnablei(target, index);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDisablei(GLenum target, GLuint index)
	{
		ngl::glDisablei(target, index);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBlendEquationi(GLuint buf, GLenum mode)
	{
		ngl::glBlendEquationi(buf, mode);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
	{
		ngl::glBlendEquationSeparatei(buf, modeRGB, modeAlpha);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBlendFunci(GLuint buf, GLenum src, GLenum dst)
	{
		ngl::glBlendFunci(buf, src, dst);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
	{
		ngl::glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
	{
		ngl::glColorMaski(index, r, g, b, a);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLboolean GL_APIENTRY dglIsEnabledi(GLenum target, GLuint index)
	{
		GLboolean result{ ngl::glIsEnabledi(target, index) };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex)
	{
		ngl::glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex)
	{
		ngl::glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex)
	{
		ngl::glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
	{
		ngl::glFramebufferTexture(target, attachment, texture, level);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglPrimitiveBoundingBox(GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW)
	{
		ngl::glPrimitiveBoundingBox(minX, minY, minZ, minW, maxX, maxY, maxZ, maxW);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	GLenum GL_APIENTRY dglGetGraphicsResetStatus()
	{
		GLenum result{ ngl::glGetGraphicsResetStatus() };
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
		return result;
	}

	void GL_APIENTRY dglReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data)
	{
		ngl::glReadnPixels(x, y, width, height, format, type, bufSize, data);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat *params)
	{
		ngl::glGetnUniformfv(program, location, bufSize, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint *params)
	{
		ngl::glGetnUniformiv(program, location, bufSize, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint *params)
	{
		ngl::glGetnUniformuiv(program, location, bufSize, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglMinSampleShading(GLfloat value)
	{
		ngl::glMinSampleShading(value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglPatchParameteri(GLenum pname, GLint value)
	{
		ngl::glPatchParameteri(pname, value);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTexParameterIiv(GLenum target, GLenum pname, const GLint *params)
	{
		ngl::glTexParameterIiv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTexParameterIuiv(GLenum target, GLenum pname, const GLuint *params)
	{
		ngl::glTexParameterIuiv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetTexParameterIiv(GLenum target, GLenum pname, GLint *params)
	{
		ngl::glGetTexParameterIiv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetTexParameterIuiv(GLenum target, GLenum pname, GLuint *params)
	{
		ngl::glGetTexParameterIuiv(target, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglSamplerParameterIiv(GLuint sampler, GLenum pname, const GLint *param)
	{
		ngl::glSamplerParameterIiv(sampler, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglSamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint *param)
	{
		ngl::glSamplerParameterIuiv(sampler, pname, param);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint *params)
	{
		ngl::glGetSamplerParameterIiv(sampler, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint *params)
	{
		ngl::glGetSamplerParameterIuiv(sampler, pname, params);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTexBuffer(GLenum target, GLenum internalformat, GLuint buffer)
	{
		ngl::glTexBuffer(target, internalformat, buffer);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
	{
		ngl::glTexBufferRange(target, internalformat, buffer, offset, size);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}

	void GL_APIENTRY dglTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
	{
		ngl::glTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
		if ((Error = ngl::glGetError()) != GL_NO_ERROR)
			ErrorListener->NotifyOnError(__FUNCTION__, __LINE__, nitisa::platform::ERROR_OPENGL_CALL_FAILED,
				nitisa::StringKeyValueArray{ { L"{name}", nitisa::AnsiToString(__func__) }, { L"{code}", nitisa::Hex((unsigned int)Error) } });
	}
#endif
}