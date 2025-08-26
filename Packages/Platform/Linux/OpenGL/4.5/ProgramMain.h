// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "../../../OpenGL/ngl.h"
#include "ProgramBase.h"

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
				class CProgramMain :public CProgramBase
				{
					friend opengl45d::CRenderer;
					friend opengl45r::CRenderer;
				private:
					struct PATTERN
					{
						GLint SubroutinePattern;
						GLuint SubroutinePattern_Color;
						GLuint SubroutinePattern_Gradient;
						GLuint SubroutinePattern_Texture;
						GLuint SubroutinePattern_TextureMultisample;
						GLuint SubroutinePattern_Block;
						GLuint SubroutinePattern_Text;
						GLuint SubroutinePattern_BlurHGaussian;
						GLuint SubroutinePattern_BlurVGaussian;
						GLuint SubroutinePattern_BlurHAverage;
						GLuint SubroutinePattern_BlurVAverage;
						GLuint SubroutinePattern_Mask;
						GLuint SubroutinePattern_Checker;
						GLuint SubroutinePattern_HSVGradient;
						GLuint SubroutinePattern_HSVPlane;

						GLint Texture;
						GLint TextureMultisample;
						GLint Transparency;
						GLint SampleCount;

						GLint TextureGradientPosition;
						GLint TextureGradientColor;
						GLint GradientSize;
						GLint GradientType;

						GLint BlurRadius;
						GLint BlurK;
						GLint BlurKExp;
						GLint BlurDisp;
					};
				private:
					PATTERN m_sPattern;

					static const int SUBROUTINE_COUNT{ 5 };
					GLuint m_aSubroutines[SUBROUTINE_COUNT];
				private:
					CProgramMain(COpenGL *graphics, COpenGLProgram *program);
					CProgramMain(const CProgramMain&) = delete;
					CProgramMain(CProgramMain&&) = delete;
					CProgramMain &operator=(const CProgramMain&) = delete;
					CProgramMain &operator=(CProgramMain&&) = delete;

					static CProgramMain *Create(COpenGL *graphics, COpenGLProgram *program);
				public:
					void NotifyOnActivate() override;
				};
			}
		}
	}
}
#endif