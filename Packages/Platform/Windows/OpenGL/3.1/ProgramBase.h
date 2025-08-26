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
			namespace opengl31d
			{
				class CRenderer;
			}

			namespace opengl31r
			{
				class CRenderer;
			}

			namespace opengl31
			{
				class CProgramBase :public virtual IProgram, public CReleasable
				{
					friend opengl31d::CRenderer;
					friend opengl31r::CRenderer;
				protected:
					struct BLOCK
					{
						const int None{ 0 };
						const int Exists{ 1 };

						GLint SubroutineTest;
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
						const int None{ 0 };
						const int Exists{ 1 };

						GLint SubroutineTest;
						GLint Matrix;
						GLint Texture;
						GLint Size;
					};

					struct BITMASK
					{
						const int Bitmask_None{ 0 };
						const int Bitmask_1D{ 1 };
						const int Bitmask_2D{ 2 };
						const int Bitmask_Form{ 3 };

						GLint SubroutineBitmask;
						GLint X;
						GLint Y;
					};

					struct SPLINE
					{
						const int None{ 0 };
						const int Y{ 1 };
						const int X{ 2 };

						GLint SubroutineSplineLimit;
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