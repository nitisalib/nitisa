// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#include "../../../OpenGL/OpenGL.h"
#include "ProgramMini.h"

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
			namespace opengl45
			{
			#pragma region Constructor & destructor
				CProgramMini::CProgramMini(COpenGL *graphics, COpenGLProgram *program) :
					CProgramBase(graphics, program)
				{
					if (m_bValid)
					{
						m_aSubroutines[m_sBlock.SubroutineTest] = m_sBlock.SubroutineTest_None;
						m_aSubroutines[m_sMask.SubroutineTest] = m_sMask.SubroutineTest_None;
						m_aSubroutines[m_sBitmask.SubroutineBitmask] = m_sBitmask.SubroutineBitmask_None;
						m_aSubroutines[m_sSpline.SubroutineSplineLimit] = m_sSpline.SubroutineSplineLimit_None;
						m_pGraphics->UseProgram(*reinterpret_cast<GLuint*>(&m_hHandle));
						m_pGraphics->UniformSubroutinesuiv(GL_FRAGMENT_SHADER, SUBROUTINE_COUNT, m_aSubroutines);
						m_pGraphics->Uniform1i(m_sMask.Texture, 3);
					}
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
					m_pGraphics->UniformSubroutinesuiv(GL_FRAGMENT_SHADER, SUBROUTINE_COUNT, m_aSubroutines);
				}
			#pragma endregion
			}
		}
	}
}
#endif