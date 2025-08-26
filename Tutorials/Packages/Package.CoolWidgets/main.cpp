#include "CoolWidgets/Package/PackageCoolWidgets.h"
#include <Windows.h>

#pragma comment(lib, "Nitisa.lib")
#pragma comment(lib, "Standard.lib")
#pragma comment(lib, "Platform.lib")
#pragma comment(lib, "CoolWidgets.lib")
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
	return nitisa::coolwidgets::CPackageCoolWidgets::Create(application);
}