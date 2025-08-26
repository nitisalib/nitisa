// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef _WIN32
#include "ProgramBase.h"

namespace nitisa
{
	class COpenGL;
	class COpenGLProgram;

	namespace platform
	{
		namespace windows
		{
			namespace opengl31d
			{
				class CRenderer;
			}

			namespace opengl31r
			{
				class CRenderer;
			}

			namespace opengl31
			{
				class CProgramMini :public CProgramBase
				{
					friend opengl31d::CRenderer;
					friend opengl31r::CRenderer;
				private:
					CProgramMini(COpenGL *graphics, COpenGLProgram *program);
					CProgramMini(const CProgramMini&) = delete;
					CProgramMini(CProgramMini&&) = delete;
					CProgramMini &operator=(const CProgramMini&) = delete;
					CProgramMini &operator=(CProgramMini&&) = delete;

					static CProgramMini *Create(COpenGL *graphics, COpenGLProgram *program);
				public:
					void NotifyOnActivate() override;
				};
			}
		}
	}
}
#endif