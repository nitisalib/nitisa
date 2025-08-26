// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef __ANDROID__
#include "../Android/NativeApplication.h"
#endif
#include "../OpenGL/ngl.h"

namespace nitisa
{
	IRenderer *CRenderer::Create(
		const RendererTechnology technology,
		const Version2 &max_version,
		const bool double_buffered,
		const int multisample_factor,
		IErrorListener *listener,
		const bool debug_context)
	{
		switch (technology)
		{
		case RendererTechnology::OpenGL:
		{
		#ifdef _WIN32
			if (max_version < Version2{ 3, 1 })
			{
				if (listener)
					listener->NotifyOnError(__FUNCTION__, __LINE__, platform::ERROR_RENDERER_REQUESTED_MAX_VERSION,
						StringKeyValueArray{ StringKeyValue{ L"{major}", ToString(max_version.Major) }, StringKeyValue{ L"{minor}", ToString(max_version.Minor) } });
				return nullptr;
			}
			Version2 ver;
			ngl::PlatformData pd{ *reinterpret_cast<const HINSTANCE*>(&Application->Handle) };
			if (!ngl::load(&ver, &pd))
			{
				if (listener)
					listener->NotifyOnError(__FUNCTION__, __LINE__, platform::ERROR_OPENGL_LOAD);
				return nullptr;
			}
			if (ver < Version2{ 3, 1 })
			{
				if (listener)
					listener->NotifyOnError(__FUNCTION__, __LINE__, platform::ERROR_RENDERER_OPENGL_VERSION,
						StringKeyValueArray{ StringKeyValue{ L"{major}", ToString(ver.Major) }, StringKeyValue{ L"{minor}", ToString(ver.Minor) } });
				return nullptr;
			}
			if (ver < Version2{ 4, 5 } || max_version < Version2{ 4, 5 })
			{
				if (listener)
					return new platform::windows::opengl31d::CRenderer(listener, double_buffered, multisample_factor, max_version, debug_context);
				return new platform::windows::opengl31r::CRenderer(double_buffered, multisample_factor, max_version);
			}
			if (listener)
				return new platform::windows::opengl45d::CRenderer(listener, double_buffered, multisample_factor, max_version, debug_context);
			return new platform::windows::opengl45r::CRenderer(double_buffered, multisample_factor, max_version);
		#endif
		#if defined(__linux__) && !defined(__ANDROID__)
			if (max_version < Version2{ 3, 1 })
			{
				if (listener)
					listener->NotifyOnError(__FUNCTION__, __LINE__, platform::ERROR_RENDERER_REQUESTED_MAX_VERSION,
						StringKeyValueArray{ StringKeyValue{ L"{major}", ToString(max_version.Major) }, StringKeyValue{ L"{minor}", ToString(max_version.Minor) } });
				return nullptr;
			}
			platform::linux::CApplication *app{ cast<platform::linux::CApplication*>(Application) };
			Version2 ver;
			ngl::PlatformData pd{ *reinterpret_cast<Display**>(&app->m_hHandle), *reinterpret_cast<Window*>(&app->m_hClipboardWindow) };
			if (!ngl::load(&ver, &pd))
			{
				if (listener)
					listener->NotifyOnError(__FUNCTION__, __LINE__, platform::ERROR_OPENGL_LOAD);
				return nullptr;
			}
			if (ver < Version2{ 3, 1 })
			{
				if (listener)
					listener->NotifyOnError(__FUNCTION__, __LINE__, platform::ERROR_RENDERER_OPENGL_VERSION,
						StringKeyValueArray{ StringKeyValue{ L"{major}", ToString(ver.Major) }, StringKeyValue{ L"{minor}", ToString(ver.Minor) } });
				return nullptr;
			}
			if (ver < Version2{ 4, 5 } || max_version < Version2{ 4, 5 })
			{
				if (listener)
					return new platform::linux::opengl31d::CRenderer(listener, double_buffered, multisample_factor, max_version, debug_context);
				return new platform::linux::opengl31r::CRenderer(double_buffered, multisample_factor, max_version);
			}
			if (listener)
				return new platform::linux::opengl45d::CRenderer(listener, double_buffered, multisample_factor, max_version, debug_context);
			return new platform::linux::opengl45r::CRenderer(double_buffered, multisample_factor, max_version);
		#endif
		#ifdef __ANDROID__
			if (max_version < Version2{ 3, 1 })
			{
				if (listener)
					listener->NotifyOnError(__FUNCTION__, __LINE__, platform::ERROR_RENDERER_REQUESTED_MAX_VERSION,
						StringKeyValueArray{ StringKeyValue{ L"{major}", ToString(max_version.Major) }, StringKeyValue{ L"{minor}", ToString(max_version.Minor) } });
				return nullptr;
			}
			platform::android::CApplication *app{ cast<platform::android::CApplication*>(Application) };
			if (app->m_pRenderer)
				return app->m_pRenderer;
			Version2 ver;
			ngl::PlatformData pd{ *reinterpret_cast<EGLDisplay*>(&app->m_hHandle), NativeApplication::getWindow() };
			if (!ngl::load(&ver, &pd))
			{
				if (listener)
					listener->NotifyOnError(__FUNCTION__, __LINE__, platform::ERROR_OPENGL_LOAD);
				return nullptr;
			}
			if (ver < Version2{ 3, 0 })
			{
				if (listener)
					listener->NotifyOnError(__FUNCTION__, __LINE__, platform::ERROR_RENDERER_OPENGL_VERSION,
						StringKeyValueArray{ StringKeyValue{ L"{major}", ToString(ver.Major) }, StringKeyValue{ L"{minor}", ToString(ver.Minor) } });
				return nullptr;
			}
			if (listener)
				return new platform::android::gles31d::CRenderer(listener, double_buffered, multisample_factor, max_version, debug_context);
			return new platform::android::gles31r::CRenderer(double_buffered, multisample_factor, max_version);
		#endif
		}
		default:
			return nullptr;
		}
	}
}