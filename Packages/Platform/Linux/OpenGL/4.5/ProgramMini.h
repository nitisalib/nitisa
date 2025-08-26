// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "../../../OpenGL/ngl.h"
#include "ProgramBase.h"

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	class COpenGL;
	class COpenGLProgram;

	namespace platform
	{
		namespace linux
		{
			namespace opengl45d
			{
				class CRenderer;
			}

			namespace opengl45r
			{
				class CRenderer;
			}

			namespace opengl45
			{
				class CProgramMini :public CProgramBase
				{
					friend opengl45d::CRenderer;
					friend opengl45r::CRenderer;
				private:
					static const int SUBROUTINE_COUNT{ 4 };
					GLuint m_aSubroutines[SUBROUTINE_COUNT];
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