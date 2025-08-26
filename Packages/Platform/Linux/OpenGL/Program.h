// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "Nitisa/Core/Releasable.h"
#include "Nitisa/Interfaces/IProgram.h"

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
			namespace opengl31d
			{
				class CRenderer;
			}

			namespace opengl31r
			{
				class CRenderer;
			}

			namespace opengl45d
			{
				class CRenderer;
			}

			namespace opengl45r
			{
				class CRenderer;
			}

			namespace opengl
			{
				class CProgram :public virtual IProgram, public CReleasable
				{
					friend opengl31d::CRenderer;
					friend opengl31r::CRenderer;
					friend opengl45d::CRenderer;
					friend opengl45r::CRenderer;
				private:
					COpenGLProgram *m_pProgram;
				protected:
					COpenGL *m_pGraphics;

					void BeforeRelease() override;

					CProgram(COpenGL *graphics, COpenGLProgram *program);
					CProgram(const CProgram&) = delete;
					CProgram(CProgram&&) = delete;
					CProgram &operator=(const CProgram&) = delete;
					CProgram &operator=(CProgram&&) = delete;
				public:
					void NotifyOnActivate() override;
				};
			}
		}
	}
}
#endif