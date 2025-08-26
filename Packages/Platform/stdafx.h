// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#ifndef H_STANDARD_STDAFX // Using include guard instead of "#pragma once" to avoid gcc bug https://stackoverflow.com/questions/56563679/gcc-precompiled-header-pragma-once-in-main-file
#define H_STANDARD_STDAFX

#include <codecvt>
#include <locale>

#include "NTL/NTL.h"
#include "Nitisa/Nitisa.h"
#include "Standard/Standard.h"

#include "Platform.h"

// Core
#include "Core/BasePlatformFont.h"
#include "Core/Db.h"
#include "Core/DbConnection.h"
#include "Core/DbStatement.h"

// Package renderers
#include "Package/Renderers/Android/GLES-3.1/PackageRendererAndroidGLES31d.h"
#include "Package/Renderers/Android/GLES-3.1/PackageRendererAndroidGLES31r.h"
#include "Package/Renderers/Linux/OpenGL-3.1/PackageRendererLinuxOpenGL31d.h"
#include "Package/Renderers/Linux/OpenGL-3.1/PackageRendererLinuxOpenGL31r.h"
#include "Package/Renderers/Linux/OpenGL-4.5/PackageRendererLinuxOpenGL45d.h"
#include "Package/Renderers/Linux/OpenGL-4.5/PackageRendererLinuxOpenGL45r.h"
#include "Package/Renderers/Windows/OpenGL-3.1/PackageRendererWindowsOpenGL31d.h"
#include "Package/Renderers/Windows/OpenGL-3.1/PackageRendererWindowsOpenGL31r.h"
#include "Package/Renderers/Windows/OpenGL-4.5/PackageRendererWindowsOpenGL45d.h"
#include "Package/Renderers/Windows/OpenGL-4.5/PackageRendererWindowsOpenGL45r.h"

#ifdef _WIN32
// Platform Windows OpenGL
#include "Windows/OpenGL/3.1/Debug/Renderer.h"
#include "Windows/OpenGL/3.1/Release/Renderer.h"
#include "Windows/OpenGL/3.1/Framebuffer.h"
#include "Windows/OpenGL/3.1/Texture.h"
#include "Windows/OpenGL/3.1/TextureMultisample.h"
#include "Windows/OpenGL/4.5/Debug/Renderer.h"
#include "Windows/OpenGL/4.5/Release/Renderer.h"
#include "Windows/OpenGL/4.5/Framebuffer.h"
#include "Windows/OpenGL/4.5/Texture.h"
#include "Windows/OpenGL/4.5/TextureMultisample.h"
#include "Windows/OpenGL/Core/BaseRenderer.h"
#include "Windows/OpenGL/Program.h"
// Platform Windows
#include "Windows/Application.h"
#include "Windows/ApplicationService.h"
#include "Windows/ClientSocket.h"
#include "Windows/Dialogs.h"
#include "Windows/File.h"
#include "Windows/FileSystem.h"
#include "Windows/Keyboard.h"
#include "Windows/Mouse.h"
#include "Windows/Network.h"
#include "Windows/Picture.h"
#include "Windows/PlatformFont.h"
#include "Windows/Screen.h"
#include "Windows/ServerSocket.h"
#include "Windows/Socket.h"
#include "Windows/System.h"
#include "Windows/Thread.h"
#include "Windows/Window.h"
#include "Windows/WindowService.h"
#endif

#if defined(__linux__) && !defined(__ANDROID__)
// Platform Linux OpenGL
#include "Linux/OpenGL/3.1/Debug/Renderer.h"
#include "Linux/OpenGL/3.1/Release/Renderer.h"
#include "Linux/OpenGL/3.1/Framebuffer.h"
#include "Linux/OpenGL/3.1/Texture.h"
#include "Linux/OpenGL/3.1/TextureMultisample.h"
#include "Linux/OpenGL/4.5/Debug/Renderer.h"
#include "Linux/OpenGL/4.5/Release/Renderer.h"
#include "Linux/OpenGL/4.5/Framebuffer.h"
#include "Linux/OpenGL/4.5/Texture.h"
#include "Linux/OpenGL/4.5/TextureMultisample.h"
#include "Linux/OpenGL/Core/BaseRenderer.h"
#include "Linux/OpenGL/Program.h"
// Platform Linux
#include "Linux/Application.h"
#include "Linux/ApplicationService.h"
#include "Linux/ClientSocket.h"
#include "Linux/Dialogs.h"
#include "Linux/File.h"
#include "Linux/FileSystem.h"
#include "Linux/Keyboard.h"
#include "Linux/Mouse.h"
#include "Linux/Network.h"
#include "Linux/Picture.h"
#include "Linux/PlatformFont.h"
#include "Linux/Screen.h"
#include "Linux/ServerSocket.h"
#include "Linux/Socket.h"
#include "Linux/System.h"
#include "Linux/Thread.h"
#include "Linux/Window.h"
#include "Linux/WindowService.h"
#endif

#ifdef __ANDROID__
// Platform Android GL ES
#include "Android/GLES/3.1/Debug/Renderer.h"
#include "Android/GLES/3.1/Release/Renderer.h"
#include "Android/GLES/Core/BaseRenderer.h"
#include "Android/GLES/Framebuffer.h"
#include "Android/GLES/Program.h"
#include "Android/GLES/Texture.h"
#include "Android/GLES/TextureMultisample.h"
// Platform Android
#include "Android/Application.h"
#include "Android/ApplicationService.h"
#include "Android/ClientSocket.h"
#include "Android/Dialogs.h"
#include "Android/File.h"
#include "Android/FileSystem.h"
#include "Android/Keyboard.h"
#include "Android/Mouse.h"
#include "Android/Network.h"
#include "Android/Picture.h"
#include "Android/PlatformFont.h"
#include "Android/Screen.h"
#include "Android/ServerSocket.h"
#include "Android/Socket.h"
#include "Android/System.h"
#include "Android/Thread.h"
#include "Android/Window.h"
#include "Android/WindowService.h"
#endif

#endif