// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "Platform/Package/PackagePlatform.h"
#include <Windows.h>

#pragma comment(lib, "Nitisa.lib")
#pragma comment(lib, "Standard.lib")
#pragma comment(lib, "Platform.lib")

#pragma comment(lib, "opengl32.lib")

namespace nitisa
{
	class IApplication;
	class IPackage;
}

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
	return TRUE;
}

nitisa::IPackage* __stdcall GetPackage(nitisa::IApplication *application)
{
	return nitisa::platform::CPackagePlatform::Create(application);
}