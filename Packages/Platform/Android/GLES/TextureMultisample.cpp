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

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
			namespace gles
			{
				const GLenum Formats[(int)TextureFormat::DepthStencil + 1]{ GL_R8, GL_R32F, GL_RGB8, GL_RGB32F, GL_RGBA8, GL_RGBA32F, GL_DEPTH_COMPONENT32F, GL_STENCIL_INDEX8, GL_DEPTH32F_STENCIL8 };
				const GLint DepthStencilModes[(int)TextureDepthStencilMode::StencilIndex + 1]{ GL_DEPTH_COMPONENT, GL_STENCIL_INDEX };
				const GLint Swizzles[(int)TextureSwizzle::One + 1]{ GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_ZERO, GL_ONE };

			#pragma region Constructor & destructor
				CTextureMultisample::CTextureMultisample(COpenGL *graphics, IRenderer *renderer, const int samples, const bool fixed_sample_locations) :
					CBaseTexture(),
					m_pGraphics{ graphics },
					m_pRenderer{ renderer }
				{
					m_eDepthStencilMode = TextureDepthStencilMode::DepthComponent;
					m_eSwizzleR = TextureSwizzle::Red;
					m_eSwizzleG = TextureSwizzle::Green;
					m_eSwizzleB = TextureSwizzle::Blue;
					m_eSwizzleA = TextureSwizzle::Alpha;
					m_iSamples = samples;
					m_bFixedSampleLocations = fixed_sample_locations;
				}

				void CTextureMultisample::BeforeRelease()
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0)
						m_pGraphics->DeleteTextures(1, reinterpret_cast<GLuint*>(&m_hHandle));
				}

				CTextureMultisample *CTextureMultisample::Create(COpenGL *graphics, IRenderer *renderer, const int samples, const bool fixed_sample_locations)
				{
					return new CTextureMultisample(graphics, renderer, samples, fixed_sample_locations);
				}
			#pragma endregion

			#pragma region ITextureMultisample setters
				bool CTextureMultisample::setFormat(const TextureFormat value)
				{
					if (value != m_eFormat)
					{
						m_eFormat = value;
						if (m_sRect.Right > 0 && m_sRect.Bottom > 0 && m_pGraphics)
							UpdateTexture();
						return true;
					}
					return false;
				}

				bool CTextureMultisample::setSize(const int width, const int height)
				{
					if (width >= 0 && height >= 0 && (width != m_sRect.Right || height != m_sRect.Bottom) && m_pGraphics)
					{
						if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && (width == 0 || height == 0))
						{
							m_pGraphics->DeleteTextures(1, reinterpret_cast<GLuint*>(&m_hHandle));
							*reinterpret_cast<GLuint*>(&m_hHandle) = 0;
							m_bCreated = false;
						}
						m_sRect.Right = width;
						m_sRect.Bottom = height;
						m_sRectf.Right = (float)width;
						m_sRectf.Bottom = (float)height;
						if (m_sRect.Right > 0 && m_sRect.Bottom > 0)
						{
							if (*reinterpret_cast<GLuint*>(&m_hHandle) == 0)
							{
								m_pGraphics->GenTextures(1, reinterpret_cast<GLuint*>(&m_hHandle));
								if (*reinterpret_cast<GLuint*>(&m_hHandle) == 0)
									return false;
							}
							UpdateTexture();
						}
						return true;
					}
					return false;
				}

				bool CTextureMultisample::setDepthStencilMode(const TextureDepthStencilMode value)
				{
				#ifdef GL_DEPTH_STENCIL_TEXTURE_MODE
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eDepthStencilMode)
					{
						m_eDepthStencilMode = value;
						m_pGraphics->ActiveTexture(GL_TEXTURE0);
						m_pGraphics->BindTexture(GL_TEXTURE_2D_MULTISAMPLE, *reinterpret_cast<GLuint*>(&m_hHandle));
						m_pGraphics->TexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_DEPTH_STENCIL_TEXTURE_MODE, DepthStencilModes[(int)m_eDepthStencilMode]);
						return true;
					}
				#endif
					return false;
				}

				bool CTextureMultisample::setSwizzleR(const TextureSwizzle value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eSwizzleR)
					{
						m_eSwizzleR = value;
						m_pGraphics->ActiveTexture(GL_TEXTURE0);
						m_pGraphics->BindTexture(GL_TEXTURE_2D_MULTISAMPLE, *reinterpret_cast<GLuint*>(&m_hHandle));
						m_pGraphics->TexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_R, Swizzles[(int)m_eSwizzleR]);
						return true;
					}
					return false;
				}

				bool CTextureMultisample::setSwizzleG(const TextureSwizzle value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eSwizzleG)
					{
						m_eSwizzleG = value;
						m_pGraphics->ActiveTexture(GL_TEXTURE0);
						m_pGraphics->BindTexture(GL_TEXTURE_2D_MULTISAMPLE, *reinterpret_cast<GLuint*>(&m_hHandle));
						m_pGraphics->TexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_G, Swizzles[(int)m_eSwizzleG]);
						return true;
					}
					return false;
				}

				bool CTextureMultisample::setSwizzleB(const TextureSwizzle value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eSwizzleB)
					{
						m_eSwizzleB = value;
						m_pGraphics->ActiveTexture(GL_TEXTURE0);
						m_pGraphics->BindTexture(GL_TEXTURE_2D_MULTISAMPLE, *reinterpret_cast<GLuint*>(&m_hHandle));
						m_pGraphics->TexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_B, Swizzles[(int)m_eSwizzleB]);
						return true;
					}
					return false;
				}

				bool CTextureMultisample::setSwizzleA(const TextureSwizzle value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eSwizzleA)
					{
						m_eSwizzleA = value;
						m_pGraphics->ActiveTexture(GL_TEXTURE0);
						m_pGraphics->BindTexture(GL_TEXTURE_2D_MULTISAMPLE, *reinterpret_cast<GLuint*>(&m_hHandle));
						m_pGraphics->TexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_A, Swizzles[(int)m_eSwizzleA]);
						return true;
					}
					return false;
				}

				bool CTextureMultisample::setSwizzleRGBA(const TextureSwizzle value)
				{
					return setSwizzleR(value) || setSwizzleG(value) || setSwizzleB(value) || setSwizzleA(value);
				}

				bool CTextureMultisample::setSamples(const int value)
				{
					if (value != m_iSamples && value >= 1 && value <= m_pRenderer->Capabilities.MaxSamples)
					{
						m_iSamples = value;
						if (m_sRect.Right > 0 && m_sRect.Bottom > 0 && m_pGraphics)
							UpdateTexture();
						return true;
					}
					return false;
				}

				bool CTextureMultisample::setFixedSampleLocations(const bool value)
				{
					if (value != m_bFixedSampleLocations)
					{
						m_bFixedSampleLocations = value;
						if (m_sRect.Right > 0 && m_sRect.Bottom > 0 && m_pGraphics)
							UpdateTexture();
						return true;
					}
					return false;
				}
			#pragma endregion

			#pragma region Helpers
				void CTextureMultisample::UpdateParameters()
				{
					if (m_eDepthStencilMode != TextureDepthStencilMode::DepthComponent)
						m_pGraphics->TexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_DEPTH_STENCIL_TEXTURE_MODE, DepthStencilModes[(int)m_eDepthStencilMode]);
					if (m_eSwizzleR != TextureSwizzle::Red)
						m_pGraphics->TexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_R, Swizzles[(int)m_eSwizzleR]);
					if (m_eSwizzleG != TextureSwizzle::Green)
						m_pGraphics->TexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_G, Swizzles[(int)m_eSwizzleG]);
					if (m_eSwizzleB != TextureSwizzle::Blue)
						m_pGraphics->TexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_B, Swizzles[(int)m_eSwizzleB]);
					if (m_eSwizzleA != TextureSwizzle::Alpha)
						m_pGraphics->TexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_SWIZZLE_A, Swizzles[(int)m_eSwizzleA]);
				}

				void CTextureMultisample::UpdateTexture()
				{
					m_pGraphics->ActiveTexture(GL_TEXTURE0);
					m_pGraphics->BindTexture(GL_TEXTURE_2D_MULTISAMPLE, *reinterpret_cast<GLuint*>(&m_hHandle));
					UpdateParameters();
					m_pGraphics->TexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_iSamples, Formats[(int)m_eFormat], m_sRect.Right, m_sRect.Bottom, m_bFixedSampleLocations);
					m_bCreated = true;
					m_sInvalidRect = m_sRect;
				}
			#pragma endregion
			}
		}
	}
}
#endif