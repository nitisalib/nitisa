// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "ProgramBase.h"

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
				class CProgramMini :public CProgramBase
				{
					friend gles31d::CRenderer;
					friend gles31r::CRenderer;
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