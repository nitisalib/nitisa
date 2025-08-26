// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "../../OpenGL/ngl.h"
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
				class CProgramMain :public CProgramBase
				{
					friend gles31d::CRenderer;
					friend gles31r::CRenderer;
				private:
					struct PATTERN
					{
						const int Pattern_Color{ 0 };
						const int Pattern_Gradient{ 1 };
						const int Pattern_Texture{ 2 };
						const int Pattern_TextureMultisample{ 3 };
						const int Pattern_Block{ 4 };
						const int Pattern_Text{ 5 };
						const int Pattern_BlurHGaussian{ 6 };
						const int Pattern_BlurVGaussian{ 7 };
						const int Pattern_BlurHAverage{ 8 };
						const int Pattern_BlurVAverage{ 9 };
						const int Pattern_Mask{ 10 };
						const int Pattern_Checker{ 11 };
						const int Pattern_HSVGradient{ 12 };
						const int Pattern_HSVPlane{ 13 };

						GLint SubroutinePattern;

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