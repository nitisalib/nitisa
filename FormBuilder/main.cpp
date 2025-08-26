// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

#pragma comment(lib, "Nitisa.lib")
#pragma comment(lib, "Platform.lib")
#pragma comment(lib, "Standard.lib")
#pragma comment(lib, "Ide.lib")
#if defined(VS_INTEGRATION) || defined(USE_DIALOGBOXES)
#pragma comment(lib, "Extended.lib")
#pragma comment(lib, "OpenGL.lib")
#pragma comment(lib, "Charts.lib")
#endif

#pragma comment(lib, "opengl32.lib")

int main()
{
	nitisa::fb::CApplication app;
	app.CreateForm(&nitisa::fb::FormMain);
	app.setMainForm(nitisa::fb::FormMain);
#if !defined(VS_INTEGRATION) && !defined(USE_DIALOGBOXES)
	app.CreateForm(&nitisa::fb::FormConfiguration);
#endif
	app.Run();
	return 0;
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	nitisa::fb::CApplication app;
	app.CreateForm(&nitisa::fb::FormMain);
	app.setMainForm(nitisa::fb::FormMain);
#if !defined(VS_INTEGRATION) && !defined(USE_DIALOGBOXES)
	app.CreateForm(&nitisa::fb::FormConfiguration);
#endif
	return app.Run();
}