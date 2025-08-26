// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "Nitisa/Core/Releasable.h"
#include "Nitisa/Interfaces/IProgram.h"

namespace nitisa
{
	class COpenGL;
	class COpenGLProgram;

	namespace platform
	{
		namespace android
		{
			namespace gles31d
			{
				class CRenderer;
			}

			namespace gles31r
			{
				class CRenderer;
			}

			namespace gles
			{
				class CProgram :public virtual IProgram, public CReleasable
				{
					friend gles31d::CRenderer;
					friend gles31r::CRenderer;
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