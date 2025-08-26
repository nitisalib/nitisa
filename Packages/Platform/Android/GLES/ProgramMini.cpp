// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef __ANDROID__
#include "../../OpenGL/OpenGL.h"
#include "ProgramMini.h"

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
			namespace gles
			{
			#pragma region Constructor & destructor
				CProgramMini::CProgramMini(COpenGL *graphics, COpenGLProgram *program) :
					CProgramBase(graphics, program)
				{
					if (m_bValid)
						m_pGraphics->Uniform1i(m_sMask.Texture, 3);
				}

				CProgramMini *CProgramMini::Create(COpenGL *graphics, COpenGLProgram *program)
				{
					CProgramMini *result{ new CProgramMini(graphics, program) };
					if (result->m_bValid)
						return result;
					delete result->m_pProgram;
					delete result;
					return nullptr;
				}
			#pragma endregion

			#pragma region Notifications
				void CProgramMini::NotifyOnActivate()
				{

				}
			#pragma endregion
			}
		}
	}
}
#endif