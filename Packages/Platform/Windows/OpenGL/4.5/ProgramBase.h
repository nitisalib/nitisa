// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef _WIN32
#include "Nitisa/Core/Releasable.h"
#include "Nitisa/Interfaces/IProgram.h"
#include "../../../OpenGL/ngl.h"

namespace nitisa
{
	class COpenGL;
	class COpenGLProgram;

	namespace platform
	{
		namespace windows
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
				class CProgramBase :public virtual IProgram, public CReleasable
				{
					friend opengl45d::CRenderer;
					friend opengl45r::CRenderer;
				protected:
					struct BLOCK
					{
						GLint SubroutineTest;
						GLuint SubroutineTest_None;
						GLuint SubroutineTest_Exists;
						GLint PointLocation;
						GLint Colors;
						GLint Rect[2];
						GLint Border[2];
						GLint Radius[2];
						GLint InnerScale[2];
						GLint CornerCenter[2];
						GLint OuterRCenter[2];
						GLint HasInner[2];
						GLint InnerRadius[2];
					};

					struct MASK
					{
						GLint SubroutineTest;
						GLuint SubroutineTest_None;
						GLuint SubroutineTest_Exists;
						GLint Matrix;
						GLint Texture;
						GLint Size;
					};

					struct BITMASK
					{
						GLint SubroutineBitmask;
						GLuint SubroutineBitmask_None;
						GLuint SubroutineBitmask_1D;
						GLuint SubroutineBitmask_2D;
						GLuint SubroutineBitmask_Form;
						GLint X;
						GLint Y;
					};

					struct SPLINE
					{
						GLint SubroutineSplineLimit;
						GLuint SubroutineSplineLimit_None;
						GLuint SubroutineSplineLimit_Y;
						GLuint SubroutineSplineLimit_X;
						GLint A;
						GLint B;
						GLint AConsts;
						GLint BConsts;
					};

					struct MATRICES
					{
						GLint FormToGL;
						GLint Primitive;
					};

					struct CHECKER
					{
						GLint Color1;
						GLint Color2;
					};

					struct HSV_PLANE
					{
						GLint Hue;
					};
				protected:
					COpenGL *m_pGraphics;
					COpenGLProgram *m_pProgram;
					bool m_bValid;
					BLOCK m_sBlock;
					MASK m_sMask;
					BITMASK m_sBitmask;
					SPLINE m_sSpline;
					MATRICES m_sMatrices;
					CHECKER m_sChecker;
					HSV_PLANE m_sHSVPlane;

					CProgramBase(COpenGL *graphics, COpenGLProgram *program);
					CProgramBase(const CProgramBase&) = delete;
					CProgramBase(CProgramBase&&) = delete;
					CProgramBase &operator=(const CProgramBase&) = delete;
					CProgramBase &operator=(CProgramBase&&) = delete;

					void BeforeRelease() override;
				public:

				};
			}
		}
	}
}
#endif