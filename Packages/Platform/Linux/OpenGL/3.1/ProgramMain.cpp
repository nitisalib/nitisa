// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#if defined(__linux__) && !defined(__ANDROID__)
#include "../../../OpenGL/OpenGL.h"
#include "ProgramMain.h"

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
			namespace opengl31
			{
			#pragma region Constructor & destructor
				CProgramMain::CProgramMain(COpenGL *graphics, COpenGLProgram *program) :
					CProgramBase(graphics, program)
				{
					if ((m_sPattern.SubroutinePattern = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_SubroutinePattern")) < 0)
						m_bValid = false;
					// Texture
					if ((m_sPattern.Texture = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Texture.Sampler")) < 0)
						m_bValid = false;
					if ((m_sPattern.TextureMultisample = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Texture.Multisampler")) < 0)
						m_bValid = false;
					if ((m_sPattern.Transparency = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Texture.Transparency")) < 0)
						m_bValid = false;
					if ((m_sPattern.SampleCount = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Texture.SampleCount")) < 0)
						m_bValid = false;
					// Gradient
					if ((m_sPattern.TextureGradientPosition = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Gradient.PositionSampler")) < 0)
						m_bValid = false;
					if ((m_sPattern.TextureGradientColor = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Gradient.ColorSampler")) < 0)
						m_bValid = false;
					if ((m_sPattern.GradientSize = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Gradient.Size")) < 0)
						m_bValid = false;
					if ((m_sPattern.GradientType = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Gradient.Type")) < 0)
						m_bValid = false;
					// Blur
					if ((m_sPattern.BlurRadius = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blur.Radius")) < 0)
						m_bValid = false;
					if ((m_sPattern.BlurK = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blur.K")) < 0)
						m_bValid = false;
					if ((m_sPattern.BlurKExp = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blur.KExp")) < 0)
						m_bValid = false;
					if ((m_sPattern.BlurDisp = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blur.Disp")) < 0)
						m_bValid = false;

					if (m_bValid)
					{
						m_pGraphics->Uniform1i(m_sPattern.SubroutinePattern, m_sPattern.Pattern_Color);
						m_pGraphics->Uniform1i(m_sPattern.Texture, 0);
						m_pGraphics->Uniform1i(m_sPattern.TextureGradientPosition, 1);
						m_pGraphics->Uniform1i(m_sPattern.TextureGradientColor, 2);
						m_pGraphics->Uniform1i(m_sMask.Texture, 3);
						m_pGraphics->Uniform1i(m_sPattern.TextureMultisample, 4);
					}
				}

				CProgramMain *CProgramMain::Create(COpenGL *graphics, COpenGLProgram *program)
				{
					CProgramMain *result{ new CProgramMain(graphics, program) };
					if (result->m_bValid)
						return result;
					delete result->m_pProgram;
					delete result;
					return nullptr;
				}
			#pragma endregion

			#pragma region Notifications
				void CProgramMain::NotifyOnActivate()
				{

				}
			#pragma endregion
			}
		}
	}
}
#endif