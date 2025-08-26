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
#include "ProgramBase.h"

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
			namespace opengl45
			{
			#pragma region Constructor & destructor
				CProgramBase::CProgramBase(COpenGL *graphics, COpenGLProgram *program) :
					CReleasable(),
					m_pGraphics{ graphics },
					m_pProgram{ program },
					m_bValid{ true }
				{
					*reinterpret_cast<GLuint*>(&m_hHandle) = program->Id;
					// Block
					if ((m_sBlock.SubroutineTest = m_pGraphics->GetSubroutineUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), GL_FRAGMENT_SHADER, "TestBlock")) < 0)
						m_bValid = false;
					if ((m_sBlock.SubroutineTest_None = m_pGraphics->GetProgramResourceIndex(*reinterpret_cast<GLuint*>(&m_hHandle), GL_FRAGMENT_SUBROUTINE, "TestBlockNone")) == GL_INVALID_INDEX)
						m_bValid = false;
					if ((m_sBlock.SubroutineTest_Exists = m_pGraphics->GetProgramResourceIndex(*reinterpret_cast<GLuint*>(&m_hHandle), GL_FRAGMENT_SUBROUTINE, "TestBlockExists")) == GL_INVALID_INDEX)
						m_bValid = false;
					if ((m_sBlock.PointLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_BlockPointLocation")) < 0)
						m_bValid = false;
					if ((m_sBlock.Colors = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_BlockColors")) < 0)
						m_bValid = false;

					if ((m_sBlock.Rect[0] = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blocks[0].Rect")) < 0)
						m_bValid = false;
					if ((m_sBlock.Border[0] = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blocks[0].Border")) < 0)
						m_bValid = false;
					if ((m_sBlock.Radius[0] = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blocks[0].Radius")) < 0)
						m_bValid = false;
					if ((m_sBlock.InnerScale[0] = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blocks[0].InnerScale")) < 0)
						m_bValid = false;
					if ((m_sBlock.CornerCenter[0] = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blocks[0].CornerCenter")) < 0)
						m_bValid = false;
					if ((m_sBlock.OuterRCenter[0] = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blocks[0].OuterRCenter")) < 0)
						m_bValid = false;
					if ((m_sBlock.HasInner[0] = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blocks[0].HasInner")) < 0)
						m_bValid = false;
					if ((m_sBlock.InnerRadius[0] = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blocks[0].InnerRadius")) < 0)
						m_bValid = false;

					if ((m_sBlock.Rect[1] = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blocks[1].Rect")) < 0)
						m_bValid = false;
					if ((m_sBlock.Border[1] = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blocks[1].Border")) < 0)
						m_bValid = false;
					if ((m_sBlock.Radius[1] = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blocks[1].Radius")) < 0)
						m_bValid = false;
					if ((m_sBlock.InnerScale[1] = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blocks[1].InnerScale")) < 0)
						m_bValid = false;
					if ((m_sBlock.CornerCenter[1] = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blocks[1].CornerCenter")) < 0)
						m_bValid = false;
					if ((m_sBlock.OuterRCenter[1] = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blocks[1].OuterRCenter")) < 0)
						m_bValid = false;
					if ((m_sBlock.HasInner[1] = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blocks[1].HasInner")) < 0)
						m_bValid = false;
					if ((m_sBlock.InnerRadius[1] = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Blocks[1].InnerRadius")) < 0)
						m_bValid = false;

					// Mask
					if ((m_sMask.SubroutineTest = m_pGraphics->GetSubroutineUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), GL_FRAGMENT_SHADER, "TestMask")) < 0)
						m_bValid = false;
					if ((m_sMask.SubroutineTest_None = m_pGraphics->GetProgramResourceIndex(*reinterpret_cast<GLuint*>(&m_hHandle), GL_FRAGMENT_SUBROUTINE, "TestMaskNone")) == GL_INVALID_INDEX)
						m_bValid = false;
					if ((m_sMask.SubroutineTest_Exists = m_pGraphics->GetProgramResourceIndex(*reinterpret_cast<GLuint*>(&m_hHandle), GL_FRAGMENT_SUBROUTINE, "TestMaskExists")) == GL_INVALID_INDEX)
						m_bValid = false;
					if ((m_sMask.Matrix = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Matrices.MaskInv")) < 0)
						m_bValid = false;
					if ((m_sMask.Texture = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Mask.Sampler")) < 0)
						m_bValid = false;
					if ((m_sMask.Size = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Mask.Size")) < 0)
						m_bValid = false;
					// Bitmask
					if ((m_sBitmask.SubroutineBitmask = m_pGraphics->GetSubroutineUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), GL_FRAGMENT_SHADER, "BitMask")) < 0)
						m_bValid = false;
					if ((m_sBitmask.SubroutineBitmask_None = m_pGraphics->GetProgramResourceIndex(*reinterpret_cast<GLuint*>(&m_hHandle), GL_FRAGMENT_SUBROUTINE, "BitMaskNone")) == GL_INVALID_INDEX)
						m_bValid = false;
					if ((m_sBitmask.SubroutineBitmask_1D = m_pGraphics->GetProgramResourceIndex(*reinterpret_cast<GLuint*>(&m_hHandle), GL_FRAGMENT_SUBROUTINE, "BitMask1D")) == GL_INVALID_INDEX)
						m_bValid = false;
					if ((m_sBitmask.SubroutineBitmask_2D = m_pGraphics->GetProgramResourceIndex(*reinterpret_cast<GLuint*>(&m_hHandle), GL_FRAGMENT_SUBROUTINE, "BitMask2D")) == GL_INVALID_INDEX)
						m_bValid = false;
					if ((m_sBitmask.SubroutineBitmask_Form = m_pGraphics->GetProgramResourceIndex(*reinterpret_cast<GLuint*>(&m_hHandle), GL_FRAGMENT_SUBROUTINE, "BitMaskForm")) == GL_INVALID_INDEX)
						m_bValid = false;
					if ((m_sBitmask.X = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Bitmask.X")) < 0)
						m_bValid = false;
					if ((m_sBitmask.Y = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Bitmask.Y")) < 0)
						m_bValid = false;
					// Spline
					if ((m_sSpline.SubroutineSplineLimit = m_pGraphics->GetSubroutineUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), GL_FRAGMENT_SHADER, "SplineLimit")) < 0)
						m_bValid = false;
					if ((m_sSpline.SubroutineSplineLimit_None = m_pGraphics->GetProgramResourceIndex(*reinterpret_cast<GLuint*>(&m_hHandle), GL_FRAGMENT_SUBROUTINE, "SplineLimitNone")) == GL_INVALID_INDEX)
						m_bValid = false;
					if ((m_sSpline.SubroutineSplineLimit_Y = m_pGraphics->GetProgramResourceIndex(*reinterpret_cast<GLuint*>(&m_hHandle), GL_FRAGMENT_SUBROUTINE, "SplineLimitY")) == GL_INVALID_INDEX)
						m_bValid = false;
					if ((m_sSpline.SubroutineSplineLimit_X = m_pGraphics->GetProgramResourceIndex(*reinterpret_cast<GLuint*>(&m_hHandle), GL_FRAGMENT_SUBROUTINE, "SplineLimitX")) == GL_INVALID_INDEX)
						m_bValid = false;
					if ((m_sSpline.A = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Spline.A")) < 0)
						m_bValid = false;
					if ((m_sSpline.B = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Spline.B")) < 0)
						m_bValid = false;
					if ((m_sSpline.AConsts = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Spline.AConsts")) < 0)
						m_bValid = false;
					if ((m_sSpline.BConsts = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Spline.BConsts")) < 0)
						m_bValid = false;
					// Matrices
					if ((m_sMatrices.FormToGL = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Matrices.FormToGL")) < 0)
						m_bValid = false;
					if ((m_sMatrices.Primitive = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Matrices.Primitive")) < 0)
						m_bValid = false;
					// Checker
					if ((m_sChecker.Color1 = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Checker.Color1")) < 0)
						m_bValid = false;
					if ((m_sChecker.Color2 = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_Checker.Color2")) < 0)
						m_bValid = false;
					// HSV plane
					if ((m_sHSVPlane.Hue = m_pGraphics->GetUniformLocation(*reinterpret_cast<GLuint*>(&m_hHandle), "app_HSVPlane.Hue")) < 0)
						m_bValid = false;
				}

				void CProgramBase::BeforeRelease()
				{
					delete m_pProgram;
				}
			#pragma endregion
			}
		}
	}
}
#endif