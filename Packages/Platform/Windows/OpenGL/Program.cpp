// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#include "../../OpenGL/OpenGL.h"

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
			namespace opengl
			{
			#pragma region Constructor & destructor
				CProgram::CProgram(COpenGL *graphics, COpenGLProgram *program) :
					CReleasable(),
					m_pProgram{ program },
					m_pGraphics{ graphics }
				{
					*reinterpret_cast<GLuint*>(&m_hHandle) = m_pProgram->Id;
				}

				void CProgram::BeforeRelease()
				{
					delete m_pProgram;
				}
			#pragma endregion

			#pragma region Notifications
				void CProgram::NotifyOnActivate()
				{

				}
			#pragma endregion
			}
		}
	}
}
#endif