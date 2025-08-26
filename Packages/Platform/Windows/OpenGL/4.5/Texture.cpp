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

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
			namespace opengl45
			{
				const GLenum Formats[(int)TextureFormat::DepthStencil + 1]{ GL_R8, GL_R32F, GL_RGB8, GL_RGB32F, GL_RGBA8, GL_RGBA32F, GL_DEPTH_COMPONENT32F, GL_STENCIL_INDEX8, GL_DEPTH32F_STENCIL8 };
				const GLint DepthStencilModes[(int)TextureDepthStencilMode::StencilIndex + 1]{ GL_DEPTH_COMPONENT, GL_STENCIL_INDEX };
				const GLint MinFilters[(int)TextureMinFilter::LinearMipmapLinear + 1]{ GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR };
				const GLint MagFilters[(int)TextureMagFilter::Linear + 1]{ GL_NEAREST, GL_LINEAR };
				const GLint Wraps[(int)TextureWrap::RepeatMirrored + 1]{ GL_CLAMP_TO_BORDER, GL_CLAMP_TO_EDGE, GL_MIRROR_CLAMP_TO_EDGE, GL_REPEAT, GL_MIRRORED_REPEAT };
				const GLint CompareModes[(int)TextureCompareMode::RefToTexture + 1]{ GL_NONE, GL_COMPARE_REF_TO_TEXTURE };
				const GLint CompareFuncs[(int)TextureCompareFunction::Never + 1]{ GL_LEQUAL, GL_GEQUAL, GL_LESS, GL_GREATER, GL_EQUAL, GL_NOTEQUAL, GL_ALWAYS, GL_NEVER };
				const GLint Swizzles[(int)TextureSwizzle::One + 1]{ GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_ZERO, GL_ONE };

			#pragma region CDataAlpha
				CTexture::CDataAlpha::CDataAlpha(CTexture *texture, const int level, const bool read_only) :
					CReleasable(),
					m_pTexture{ texture },
					m_bReadOnly{ read_only },
					m_aData{ nullptr }
				{
					m_iLevel = 0;
					m_iWidth = 0;
					m_iHeight = 0;
					m_bPrecomputed = false;
					GLint w, h;
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_WIDTH, &w);
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_HEIGHT, &h);
					if (w > 0 && h > 0)
					{
						m_iWidth = w;
						m_iHeight = h;
						m_aData = new DATA[m_iWidth * m_iHeight];
						m_pTexture->m_pGraphics->PixelStorei(GL_PACK_ALIGNMENT, 1);
						m_pTexture->m_pGraphics->GetTextureImage(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_RED, GL_UNSIGNED_BYTE, (int)sizeof(DATA) * m_iWidth * m_iHeight, reinterpret_cast<void*>(m_aData));
						m_pTexture->m_pGraphics->PixelStorei(GL_PACK_ALIGNMENT, 4);
					}
				}

				void CTexture::CDataAlpha::BeforeRelease()
				{
					if (m_aData)
					{
						if (!m_bReadOnly)
						{
							m_pTexture->m_pGraphics->PixelStorei(GL_UNPACK_ALIGNMENT, 1);
							m_pTexture->m_pGraphics->TextureSubImage2D(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, 0, 0, m_iWidth, m_iHeight, GL_RED, GL_UNSIGNED_BYTE, reinterpret_cast<const void*>(m_aData));
							m_pTexture->m_pGraphics->PixelStorei(GL_UNPACK_ALIGNMENT, 4);
						}
						delete[] m_aData;
					}
				}

				Color CTexture::CDataAlpha::getColor(const int x, const int y) const
				{
					return Color{ 0, 0, 0, m_aData[m_iWidth * (m_iHeight - y - 1) + x].A };
				}

				void CTexture::CDataAlpha::getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha)
				{
					alpha = m_aData[m_iWidth * (m_iHeight - y - 1) + x].A;
				}

				void CTexture::CDataAlpha::getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha)
				{
					alpha = m_aData[m_iWidth * (m_iHeight - y - 1) + x].A / 255.0f;
				}

				float CTexture::CDataAlpha::getDepth(const int x, const int y) const
				{
					return 0;
				}

				unsigned char CTexture::CDataAlpha::getStencil(const int x, const int y) const
				{
					return 0;
				}

				unsigned char *CTexture::CDataAlpha::getData()
				{
					return reinterpret_cast<unsigned char*>(m_aData);
				}

				void CTexture::CDataAlpha::setColor(const int x, const int y, const Color &color)
				{
					m_aData[m_iWidth * (m_iHeight - y - 1) + x].A = color.A;
				}

				void CTexture::CDataAlpha::setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha)
				{
					m_aData[m_iWidth * (m_iHeight - y - 1) + x].A = ntl::Round<unsigned char>(alpha * 255);
				}

				void CTexture::CDataAlpha::setDepth(const int x, const int y, const float value)
				{

				}

				void CTexture::CDataAlpha::setStencil(const int x, const int y, const unsigned char value)
				{

				}
			#pragma endregion

			#pragma region CDataAlphaFloat
				CTexture::CDataAlphaFloat::CDataAlphaFloat(CTexture *texture, const int level, const bool read_only) :
					CReleasable(),
					m_pTexture{ texture },
					m_bReadOnly{ read_only },
					m_aData{ nullptr }
				{
					m_iLevel = 0;
					m_iWidth = 0;
					m_iHeight = 0;
					m_bPrecomputed = false;
					GLint w, h;
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_WIDTH, &w);
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_HEIGHT, &h);
					if (w > 0 && h > 0)
					{
						m_iWidth = w;
						m_iHeight = h;
						m_aData = new DATA[m_iWidth * m_iHeight];
						m_pTexture->m_pGraphics->GetTextureImage(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_RED, GL_FLOAT, (int)sizeof(DATA) * m_iWidth * m_iHeight, reinterpret_cast<void*>(m_aData));
					}
				}

				void CTexture::CDataAlphaFloat::BeforeRelease()
				{
					if (m_aData)
					{
						if (!m_bReadOnly)
							m_pTexture->m_pGraphics->TextureSubImage2D(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, 0, 0, m_iWidth, m_iHeight, GL_RED, GL_FLOAT, reinterpret_cast<const void*>(m_aData));
						delete[] m_aData;
					}
				}

				Color CTexture::CDataAlphaFloat::getColor(const int x, const int y) const
				{
					return Color{ 0, 0, 0, ntl::Round<unsigned char>(m_aData[m_iWidth * (m_iHeight - y - 1) + x].A * 255) };
				}

				void CTexture::CDataAlphaFloat::getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha)
				{
					alpha = ntl::Round<unsigned char>(m_aData[m_iWidth * (m_iHeight - y - 1) + x].A * 255);
				}

				void CTexture::CDataAlphaFloat::getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha)
				{
					alpha = m_aData[m_iWidth * (m_iHeight - y - 1) + x].A;
				}

				float CTexture::CDataAlphaFloat::getDepth(const int x, const int y) const
				{
					return 0;
				}

				unsigned char CTexture::CDataAlphaFloat::getStencil(const int x, const int y) const
				{
					return 0;
				}

				unsigned char *CTexture::CDataAlphaFloat::getData()
				{
					return reinterpret_cast<unsigned char*>(m_aData);
				}

				void CTexture::CDataAlphaFloat::setColor(const int x, const int y, const Color &color)
				{
					m_aData[m_iWidth * (m_iHeight - y - 1) + x].A = color.A / 255.0f;
				}

				void CTexture::CDataAlphaFloat::setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha)
				{
					m_aData[m_iWidth * (m_iHeight - y - 1) + x].A = alpha;
				}

				void CTexture::CDataAlphaFloat::setDepth(const int x, const int y, const float value)
				{

				}

				void CTexture::CDataAlphaFloat::setStencil(const int x, const int y, const unsigned char value)
				{

				}
			#pragma endregion

			#pragma region CDataRGB
				CTexture::CDataRGB::CDataRGB(CTexture *texture, const int level, const bool read_only) :
					CReleasable(),
					m_pTexture{ texture },
					m_bReadOnly{ read_only },
					m_aData{ nullptr }
				{
					m_iLevel = 0;
					m_iWidth = 0;
					m_iHeight = 0;
					m_bPrecomputed = false;
					GLint w, h;
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_WIDTH, &w);
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_HEIGHT, &h);
					if (w > 0 && h > 0)
					{
						m_iWidth = w;
						m_iHeight = h;
						m_aData = new DATA[m_iWidth * m_iHeight];
						m_pTexture->m_pGraphics->GetTextureImage(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_RGB, GL_UNSIGNED_BYTE, (int)sizeof(DATA) * m_iWidth * m_iHeight, reinterpret_cast<void*>(m_aData));
					}
				}

				void CTexture::CDataRGB::BeforeRelease()
				{
					if (m_aData)
					{
						if (!m_bReadOnly)
							m_pTexture->m_pGraphics->TextureSubImage2D(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, 0, 0, m_iWidth, m_iHeight, GL_RGB, GL_UNSIGNED_BYTE, reinterpret_cast<const void*>(m_aData));
						delete[] m_aData;
					}
				}

				Color CTexture::CDataRGB::getColor(const int x, const int y) const
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					return Color{ data.R, data.G, data.B, 1 };
				}

				void CTexture::CDataRGB::getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha)
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					red = data.R;
					green = data.G;
					blue = data.B;
				}

				void CTexture::CDataRGB::getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha)
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					red = data.R / 255.0f;
					green = data.G / 255.0f;
					blue = data.B / 255.0f;
				}

				float CTexture::CDataRGB::getDepth(const int x, const int y) const
				{
					return 0;
				}

				unsigned char CTexture::CDataRGB::getStencil(const int x, const int y) const
				{
					return 0;
				}

				unsigned char *CTexture::CDataRGB::getData()
				{
					return reinterpret_cast<unsigned char*>(m_aData);
				}

				void CTexture::CDataRGB::setColor(const int x, const int y, const Color &color)
				{
					DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					data.R = color.R;
					data.G = color.G;
					data.B = color.B;
				}

				void CTexture::CDataRGB::setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha)
				{
					m_aData[m_iWidth * (m_iHeight - y - 1) + x].R = ntl::Round<unsigned char>(red * 255);
					m_aData[m_iWidth * (m_iHeight - y - 1) + x].G = ntl::Round<unsigned char>(green * 255);
					m_aData[m_iWidth * (m_iHeight - y - 1) + x].B = ntl::Round<unsigned char>(blue * 255);
				}

				void CTexture::CDataRGB::setDepth(const int x, const int y, const float value)
				{

				}

				void CTexture::CDataRGB::setStencil(const int x, const int y, const unsigned char value)
				{

				}
			#pragma endregion

			#pragma region CDataRGBFloat
				CTexture::CDataRGBFloat::CDataRGBFloat(CTexture *texture, const int level, const bool read_only) :
					CReleasable(),
					m_pTexture{ texture },
					m_bReadOnly{ read_only },
					m_aData{ nullptr }
				{
					m_iLevel = 0;
					m_iWidth = 0;
					m_iHeight = 0;
					m_bPrecomputed = false;
					GLint w, h;
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_WIDTH, &w);
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_HEIGHT, &h);
					if (w > 0 && h > 0)
					{
						m_iWidth = w;
						m_iHeight = h;
						m_aData = new DATA[m_iWidth * m_iHeight];
						m_pTexture->m_pGraphics->GetTextureImage(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_RGB, GL_FLOAT, (int)sizeof(DATA) * m_iWidth * m_iHeight, reinterpret_cast<void*>(m_aData));
					}
				}

				void CTexture::CDataRGBFloat::BeforeRelease()
				{
					if (m_aData)
					{
						if (!m_bReadOnly)
							m_pTexture->m_pGraphics->TextureSubImage2D(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, 0, 0, m_iWidth, m_iHeight, GL_RGB, GL_FLOAT, reinterpret_cast<const void*>(m_aData));
						delete[] m_aData;
					}
				}

				Color CTexture::CDataRGBFloat::getColor(const int x, const int y) const
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					return Color{
						ntl::Round<unsigned char>(data.R * 255),
						ntl::Round<unsigned char>(data.G * 255),
						ntl::Round<unsigned char>(data.B * 255),
						1 };
				}

				void CTexture::CDataRGBFloat::getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha)
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					red = ntl::Round<unsigned char>(data.R * 255);
					green = ntl::Round<unsigned char>(data.G * 255);
					blue = ntl::Round<unsigned char>(data.B * 255);
				}

				void CTexture::CDataRGBFloat::getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha)
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					red = data.R;
					green = data.G;
					blue = data.B;
				}

				float CTexture::CDataRGBFloat::getDepth(const int x, const int y) const
				{
					return 0;
				}

				unsigned char CTexture::CDataRGBFloat::getStencil(const int x, const int y) const
				{
					return 0;
				}

				unsigned char *CTexture::CDataRGBFloat::getData()
				{
					return reinterpret_cast<unsigned char*>(m_aData);
				}

				void CTexture::CDataRGBFloat::setColor(const int x, const int y, const Color &color)
				{
					DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					data.R = color.R / 255.0f;
					data.G = color.G / 255.0f;
					data.B = color.B / 255.0f;
				}

				void CTexture::CDataRGBFloat::setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha)
				{
					DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					data.R = red;
					data.G = green;
					data.B = blue;
				}

				void CTexture::CDataRGBFloat::setDepth(const int x, const int y, const float value)
				{

				}

				void CTexture::CDataRGBFloat::setStencil(const int x, const int y, const unsigned char value)
				{

				}
			#pragma endregion

			#pragma region CDataRGBA
				CTexture::CDataRGBA::CDataRGBA(CTexture *texture, const int level, const bool read_only) :
					CReleasable(),
					m_pTexture{ texture },
					m_bReadOnly{ read_only },
					m_aData{ nullptr }
				{
					m_iLevel = 0;
					m_iWidth = 0;
					m_iHeight = 0;
					m_bPrecomputed = false;
					GLint w, h;
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_WIDTH, &w);
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_HEIGHT, &h);
					if (w > 0 && h > 0)
					{
						m_iWidth = w;
						m_iHeight = h;
						m_aData = new DATA[m_iWidth * m_iHeight];
						m_pTexture->m_pGraphics->GetTextureImage(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_RGBA, GL_UNSIGNED_BYTE, (int)sizeof(DATA) * m_iWidth * m_iHeight, reinterpret_cast<void*>(m_aData));
					}
				}

				void CTexture::CDataRGBA::BeforeRelease()
				{
					if (m_aData)
					{
						if (!m_bReadOnly)
							m_pTexture->m_pGraphics->TextureSubImage2D(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, 0, 0, m_iWidth, m_iHeight, GL_RGBA, GL_UNSIGNED_BYTE, reinterpret_cast<const void*>(m_aData));
						delete[] m_aData;
					}
				}

				Color CTexture::CDataRGBA::getColor(const int x, const int y) const
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					return Color{ data.R, data.G, data.B, data.A };
				}

				void CTexture::CDataRGBA::getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha)
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					red = data.R;
					green = data.G;
					blue = data.B;
					alpha = data.A;
				}

				void CTexture::CDataRGBA::getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha)
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					red = data.R / 255.0f;
					green = data.G / 255.0f;
					blue = data.B / 255.0f;
					alpha = data.A / 255.0f;
				}

				float CTexture::CDataRGBA::getDepth(const int x, const int y) const
				{
					return 0;
				}

				unsigned char CTexture::CDataRGBA::getStencil(const int x, const int y) const
				{
					return 0;
				}

				unsigned char *CTexture::CDataRGBA::getData()
				{
					return reinterpret_cast<unsigned char*>(m_aData);
				}

				void CTexture::CDataRGBA::setColor(const int x, const int y, const Color &color)
				{
					DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					data.R = color.R;
					data.G = color.G;
					data.B = color.B;
					data.A = color.A;
				}

				void CTexture::CDataRGBA::setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha)
				{
					DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					data.R = ntl::Round<unsigned char>(red * 255);
					data.G = ntl::Round<unsigned char>(green * 255);
					data.B = ntl::Round<unsigned char>(blue * 255);
					data.A = ntl::Round<unsigned char>(alpha * 255);
				}

				void CTexture::CDataRGBA::setDepth(const int x, const int y, const float value)
				{

				}

				void CTexture::CDataRGBA::setStencil(const int x, const int y, const unsigned char value)
				{

				}
			#pragma endregion

			#pragma region CDataRGBAPrecomputed
				CTexture::CDataRGBAPrecomputed::CDataRGBAPrecomputed(CTexture *texture, const int level, const bool read_only) :
					CReleasable(),
					m_pTexture{ texture },
					m_bReadOnly{ read_only },
					m_aData{ nullptr }
				{
					m_iLevel = 0;
					m_iWidth = 0;
					m_iHeight = 0;
					m_bPrecomputed = false;
					GLint w, h;
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_WIDTH, &w);
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_HEIGHT, &h);
					if (w > 0 && h > 0)
					{
						m_iWidth = w;
						m_iHeight = h;
						m_aData = new DATA[m_iWidth * m_iHeight];
						m_pTexture->m_pGraphics->GetTextureImage(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_RGBA, GL_UNSIGNED_BYTE, (int)sizeof(DATA) * m_iWidth * m_iHeight, reinterpret_cast<void*>(m_aData));
					}
				}

				void CTexture::CDataRGBAPrecomputed::BeforeRelease()
				{
					if (m_aData)
					{
						if (!m_bReadOnly)
							m_pTexture->m_pGraphics->TextureSubImage2D(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, 0, 0, m_iWidth, m_iHeight, GL_RGBA, GL_UNSIGNED_BYTE, reinterpret_cast<const void*>(m_aData));
						delete[] m_aData;
					}
				}

				Color CTexture::CDataRGBAPrecomputed::getColor(const int x, const int y) const
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					if (data.A > 0)
						return Color{
							(unsigned char)((255 * data.R) / data.A),
							(unsigned char)((255 * data.G) / data.A),
							(unsigned char)((255 * data.B) / data.A),
							data.A };
					return Color{ data.R, data.G, data.B, data.A };
				}

				void CTexture::CDataRGBAPrecomputed::getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha)
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					if (data.A > 0)
					{
						red = (unsigned char)((255 * data.R) / data.A);
						green = (unsigned char)((255 * data.G) / data.A);
						blue = (unsigned char)((255 * data.B) / data.A);
					}
					else
					{
						red = data.R;
						green = data.G;
						blue = data.B;
					}
					alpha = data.A;
				}

				void CTexture::CDataRGBAPrecomputed::getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha)
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					if (data.A > 0)
					{
						red = data.R / (float)data.A;
						green = data.G / (float)data.A;
						blue = data.B / (float)data.A;
					}
					else
					{
						red = data.R / 255.0f;
						green = data.G / 255.0f;
						blue = data.B / 255.0f;
					}
					alpha = data.A / 255.0f;
				}

				float CTexture::CDataRGBAPrecomputed::getDepth(const int x, const int y) const
				{
					return 0;
				}

				unsigned char CTexture::CDataRGBAPrecomputed::getStencil(const int x, const int y) const
				{
					return 0;
				}

				unsigned char *CTexture::CDataRGBAPrecomputed::getData()
				{
					return reinterpret_cast<unsigned char*>(m_aData);
				}

				void CTexture::CDataRGBAPrecomputed::setColor(const int x, const int y, const Color &color)
				{
					DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					data.R = (unsigned char)((color.R * color.A) >> 8);
					data.G = (unsigned char)((color.G * color.A) >> 8);
					data.B = (unsigned char)((color.B * color.A) >> 8);
					data.A = color.A;
				}

				void CTexture::CDataRGBAPrecomputed::setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha)
				{
					DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					data.R = ntl::Round<unsigned char>(red * alpha * 255);
					data.G = ntl::Round<unsigned char>(green * alpha * 255);
					data.B = ntl::Round<unsigned char>(blue * alpha * 255);
					data.A = ntl::Round<unsigned char>(alpha * 255);
				}

				void CTexture::CDataRGBAPrecomputed::setDepth(const int x, const int y, const float value)
				{

				}

				void CTexture::CDataRGBAPrecomputed::setStencil(const int x, const int y, const unsigned char value)
				{

				}
			#pragma endregion

			#pragma region CDataRGBAFloat
				CTexture::CDataRGBAFloat::CDataRGBAFloat(CTexture *texture, const int level, const bool read_only) :
					CReleasable(),
					m_pTexture{ texture },
					m_bReadOnly{ read_only },
					m_aData{ nullptr }
				{
					m_iLevel = 0;
					m_iWidth = 0;
					m_iHeight = 0;
					m_bPrecomputed = false;
					GLint w, h;
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_WIDTH, &w);
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_HEIGHT, &h);
					if (w > 0 && h > 0)
					{
						m_iWidth = w;
						m_iHeight = h;
						m_aData = new DATA[m_iWidth * m_iHeight];
						m_pTexture->m_pGraphics->GetTextureImage(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_RGBA, GL_FLOAT, (int)sizeof(DATA) * m_iWidth * m_iHeight, reinterpret_cast<void*>(m_aData));
					}
				}

				void CTexture::CDataRGBAFloat::BeforeRelease()
				{
					if (m_aData)
					{
						if (!m_bReadOnly)
							m_pTexture->m_pGraphics->TextureSubImage2D(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, 0, 0, m_iWidth, m_iHeight, GL_RGBA, GL_FLOAT, reinterpret_cast<const void*>(m_aData));
						delete[] m_aData;
					}
				}

				Color CTexture::CDataRGBAFloat::getColor(const int x, const int y) const
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					return Color{
						ntl::Round<unsigned char>(data.R * 255),
						ntl::Round<unsigned char>(data.G * 255),
						ntl::Round<unsigned char>(data.B * 255),
						ntl::Round<unsigned char>(data.A * 255) };
				}

				void CTexture::CDataRGBAFloat::getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha)
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					red = ntl::Round<unsigned char>(data.R * 255);
					green = ntl::Round<unsigned char>(data.G * 255);
					blue = ntl::Round<unsigned char>(data.B * 255);
					alpha = ntl::Round<unsigned char>(data.A * 255);
				}

				void CTexture::CDataRGBAFloat::getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha)
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					red = data.R;
					green = data.G;
					blue = data.B;
					alpha = data.A;
				}

				float CTexture::CDataRGBAFloat::getDepth(const int x, const int y) const
				{
					return 0;
				}

				unsigned char CTexture::CDataRGBAFloat::getStencil(const int x, const int y) const
				{
					return 0;
				}

				unsigned char *CTexture::CDataRGBAFloat::getData()
				{
					return reinterpret_cast<unsigned char*>(m_aData);
				}

				void CTexture::CDataRGBAFloat::setColor(const int x, const int y, const Color &color)
				{
					DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					data.R = color.R / 255.0f;
					data.G = color.G / 255.0f;
					data.B = color.B / 255.0f;
					data.A = color.A / 255.0f;
				}

				void CTexture::CDataRGBAFloat::setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha)
				{
					DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					data.R = red;
					data.G = green;
					data.B = blue;
					data.A = alpha;
				}

				void CTexture::CDataRGBAFloat::setDepth(const int x, const int y, const float value)
				{

				}

				void CTexture::CDataRGBAFloat::setStencil(const int x, const int y, const unsigned char value)
				{

				}
			#pragma endregion

			#pragma region CDataRGBAFloatPrecomputed
				CTexture::CDataRGBAFloatPrecomputed::CDataRGBAFloatPrecomputed(CTexture *texture, const int level, const bool read_only) :
					CReleasable(),
					m_pTexture{ texture },
					m_bReadOnly{ read_only },
					m_aData{ nullptr }
				{
					m_iLevel = 0;
					m_iWidth = 0;
					m_iHeight = 0;
					m_bPrecomputed = false;
					GLint w, h;
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_WIDTH, &w);
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_HEIGHT, &h);
					if (w > 0 && h > 0)
					{
						m_iWidth = w;
						m_iHeight = h;
						m_aData = new DATA[m_iWidth * m_iHeight];
						m_pTexture->m_pGraphics->GetTextureImage(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_RGBA, GL_FLOAT, (int)sizeof(DATA) * m_iWidth * m_iHeight, reinterpret_cast<void*>(m_aData));
					}
				}

				void CTexture::CDataRGBAFloatPrecomputed::BeforeRelease()
				{
					if (m_aData)
					{
						if (!m_bReadOnly)
							m_pTexture->m_pGraphics->TextureSubImage2D(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, 0, 0, m_iWidth, m_iHeight, GL_RGBA, GL_FLOAT, reinterpret_cast<const void*>(m_aData));
						delete[] m_aData;
					}
				}

				Color CTexture::CDataRGBAFloatPrecomputed::getColor(const int x, const int y) const
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					if (data.A > 0)
						return Color{
							ntl::Round<unsigned char>(255 * data.R / data.A),
							ntl::Round<unsigned char>(255 * data.G / data.A),
							ntl::Round<unsigned char>(255 * data.B / data.A),
							ntl::Round<unsigned char>(255 * data.A) };
					return Color{
						ntl::Round<unsigned char>(data.R * 255),
						ntl::Round<unsigned char>(data.G * 255),
						ntl::Round<unsigned char>(data.B * 255),
						ntl::Round<unsigned char>(data.A * 255) };
				}

				void CTexture::CDataRGBAFloatPrecomputed::getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha)
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					if (data.A > 0)
					{
						red = ntl::Round<unsigned char>(255 * data.R / data.A);
						green = ntl::Round<unsigned char>(255 * data.G / data.A);
						blue = ntl::Round<unsigned char>(255 * data.B / data.A);
					}
					else
					{
						red = ntl::Round<unsigned char>(data.R * 255);
						green = ntl::Round<unsigned char>(data.G * 255);
						blue = ntl::Round<unsigned char>(data.B * 255);
					}
					alpha = ntl::Round<unsigned char>(data.A * 255);
				}

				void CTexture::CDataRGBAFloatPrecomputed::getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha)
				{
					const DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					if (data.A > 0)
					{
						red = data.R / data.A;
						green = data.G / data.A;
						blue = data.B / data.A;
					}
					else
					{
						red = data.R;
						green = data.G;
						blue = data.B;
					}
					alpha = data.A;
				}

				float CTexture::CDataRGBAFloatPrecomputed::getDepth(const int x, const int y) const
				{
					return 0;
				}

				unsigned char CTexture::CDataRGBAFloatPrecomputed::getStencil(const int x, const int y) const
				{
					return 0;
				}

				unsigned char *CTexture::CDataRGBAFloatPrecomputed::getData()
				{
					return reinterpret_cast<unsigned char*>(m_aData);
				}

				void CTexture::CDataRGBAFloatPrecomputed::setColor(const int x, const int y, const Color &color)
				{
					DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					data.R = float(color.R * color.A) / 255.0f;
					data.G = float(color.G * color.A) / 255.0f;
					data.B = float(color.B * color.A) / 255.0f;
					data.A = color.A / 255.0f;
				}

				void CTexture::CDataRGBAFloatPrecomputed::setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha)
				{
					DATA &data{ m_aData[m_iWidth * (m_iHeight - y - 1) + x] };
					data.R = red * alpha;
					data.G = green * alpha;
					data.B = blue * alpha;
					data.A = alpha;
				}

				void CTexture::CDataRGBAFloatPrecomputed::setDepth(const int x, const int y, const float value)
				{

				}

				void CTexture::CDataRGBAFloatPrecomputed::setStencil(const int x, const int y, const unsigned char value)
				{

				}
			#pragma endregion

			#pragma region CDataDepth
				CTexture::CDataDepth::CDataDepth(CTexture *texture, const int level, const bool read_only) :
					CReleasable(),
					m_pTexture{ texture },
					m_bReadOnly{ read_only },
					m_aData{ nullptr }
				{
					m_iLevel = 0;
					m_iWidth = 0;
					m_iHeight = 0;
					m_bPrecomputed = false;
					GLint w, h;
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_WIDTH, &w);
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_HEIGHT, &h);
					if (w > 0 && h > 0)
					{
						m_iWidth = w;
						m_iHeight = h;
						m_aData = new DATA[m_iWidth * m_iHeight];
						m_pTexture->m_pGraphics->GetTextureImage(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_DEPTH_COMPONENT, GL_FLOAT, (int)sizeof(DATA) * m_iWidth * m_iHeight, reinterpret_cast<void*>(m_aData));
					}
				}

				void CTexture::CDataDepth::BeforeRelease()
				{
					if (m_aData)
					{
						if (!m_bReadOnly)
							m_pTexture->m_pGraphics->TextureSubImage2D(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, 0, 0, m_iWidth, m_iHeight, GL_DEPTH_COMPONENT, GL_FLOAT, reinterpret_cast<const void*>(m_aData));
						delete[] m_aData;
					}
				}

				Color CTexture::CDataDepth::getColor(const int x, const int y) const
				{
					return Color{ 0, 0, 0, 0 };
				}

				void CTexture::CDataDepth::getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha)
				{

				}

				void CTexture::CDataDepth::getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha)
				{

				}

				float CTexture::CDataDepth::getDepth(const int x, const int y) const
				{
					return m_aData[m_iWidth * (m_iHeight - y - 1) + x].D;
				}

				unsigned char CTexture::CDataDepth::getStencil(const int x, const int y) const
				{
					return 0;
				}

				unsigned char *CTexture::CDataDepth::getData()
				{
					return reinterpret_cast<unsigned char*>(m_aData);
				}

				void CTexture::CDataDepth::setColor(const int x, const int y, const Color &color)
				{

				}

				void CTexture::CDataDepth::setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha)
				{

				}

				void CTexture::CDataDepth::setDepth(const int x, const int y, const float value)
				{
					m_aData[m_iWidth * (m_iHeight - y - 1) + x].D = value;
				}

				void CTexture::CDataDepth::setStencil(const int x, const int y, const unsigned char value)
				{

				}
			#pragma endregion

			#pragma region CDataStencil
				CTexture::CDataStencil::CDataStencil(CTexture *texture, const int level, const bool read_only) :
					CReleasable(),
					m_pTexture{ texture },
					m_bReadOnly{ read_only },
					m_aData{ nullptr }
				{
					m_iLevel = 0;
					m_iWidth = 0;
					m_iHeight = 0;
					m_bPrecomputed = false;
					GLint w, h;
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_WIDTH, &w);
					m_pTexture->m_pGraphics->GetTextureLevelParameteriv(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_TEXTURE_HEIGHT, &h);
					if (w > 0 && h > 0)
					{
						m_iWidth = w;
						m_iHeight = h;
						m_aData = new DATA[m_iWidth * m_iHeight];
						m_pTexture->m_pGraphics->PixelStorei(GL_PACK_ALIGNMENT, 1);
						m_pTexture->m_pGraphics->GetTextureImage(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, (int)sizeof(DATA) * m_iWidth * m_iHeight, reinterpret_cast<void*>(m_aData));
						m_pTexture->m_pGraphics->PixelStorei(GL_PACK_ALIGNMENT, 4);
					}
				}

				void CTexture::CDataStencil::BeforeRelease()
				{
					if (m_aData)
					{
						if (!m_bReadOnly)
						{
							m_pTexture->m_pGraphics->PixelStorei(GL_UNPACK_ALIGNMENT, 1);
							m_pTexture->m_pGraphics->TextureSubImage2D(*reinterpret_cast<GLuint*>(&m_pTexture->m_hHandle), m_iLevel, 0, 0, m_iWidth, m_iHeight, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, reinterpret_cast<const void*>(m_aData));
							m_pTexture->m_pGraphics->PixelStorei(GL_UNPACK_ALIGNMENT, 4);
						}
						delete[] m_aData;
					}
				}

				Color CTexture::CDataStencil::getColor(const int x, const int y) const
				{
					return Color{ 0, 0, 0, 0 };
				}

				void CTexture::CDataStencil::getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha)
				{

				}

				void CTexture::CDataStencil::getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha)
				{

				}

				float CTexture::CDataStencil::getDepth(const int x, const int y) const
				{
					return 0;
				}

				unsigned char CTexture::CDataStencil::getStencil(const int x, const int y) const
				{
					return m_aData[m_iWidth * (m_iHeight - y - 1) + x].S;
				}

				unsigned char *CTexture::CDataStencil::getData()
				{
					return reinterpret_cast<unsigned char*>(m_aData);
				}

				void CTexture::CDataStencil::setColor(const int x, const int y, const Color &color)
				{

				}

				void CTexture::CDataStencil::setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha)
				{

				}

				void CTexture::CDataStencil::setDepth(const int x, const int y, const float value)
				{

				}

				void CTexture::CDataStencil::setStencil(const int x, const int y, const unsigned char value)
				{
					m_aData[m_iWidth * (m_iHeight - y - 1) + x].S = value;
				}
			#pragma endregion

			#pragma region CDataReleaseListener
				CTexture::CDataReleaseListener::CDataReleaseListener(CTexture *texture) :
					m_pTexture{ texture }
				{

				}

				void CTexture::CDataReleaseListener::NotifyOnRelease(IReleasable *sender)
				{
					m_pTexture->m_pData = nullptr;
				}
			#pragma endregion

			#pragma region Constructor & destructor
				CTexture::CTexture(COpenGL *graphics, IRenderer *renderer, const bool precomputed) :
					CBaseTexture(),
					m_cDataReleaseListener{ this },
					m_pGraphics{ graphics },
					m_pData{ nullptr }
				{
					m_iRequiredLevelCount = 0;
					m_iActualLevelCount = 1;
					m_bPrecomputed = precomputed;
					m_eMinFilter = TextureMinFilter::Nearest;
					m_eMagFilter = TextureMagFilter::Nearest;
					m_eDepthStencilMode = TextureDepthStencilMode::DepthComponent;
					m_iBaseLevel = 0;
					m_fMinLOD = -1000;
					m_fMaxLOD = 1000;
					m_eWrapS = TextureWrap::Repeat;
					m_eWrapT = TextureWrap::Repeat;
					m_eWrapR = TextureWrap::Repeat;
					m_sBorderColor = Color{ 0, 0, 0, 0 };
					m_eCompareMode = TextureCompareMode::None;
					m_eCompareFunction = TextureCompareFunction::Always;
					m_fLODBias = 0;
					m_iMaxLevel = 1000;
					m_eSwizzleR = TextureSwizzle::Red;
					m_eSwizzleG = TextureSwizzle::Green;
					m_eSwizzleB = TextureSwizzle::Blue;
					m_eSwizzleA = TextureSwizzle::Alpha;
				}

				void CTexture::BeforeRelease()
				{
					if (m_pData)
						m_pData->Release(true);
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0)
						m_pGraphics->DeleteTextures(1, reinterpret_cast<GLuint*>(&m_hHandle));
				}

				CTexture *CTexture::Create(COpenGL *graphics, IRenderer *renderer, const bool precomputed)
				{
					return new CTexture(graphics, renderer, precomputed);
				}
			#pragma endregion

			#pragma region ITexture setters
				bool CTexture::setFormat(const TextureFormat value)
				{
					if (value != m_eFormat)
					{
						m_eFormat = value;
						if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0)
						{
							m_pGraphics->DeleteTextures(1, reinterpret_cast<GLuint*>(&m_hHandle));
							*reinterpret_cast<GLuint*>(&m_hHandle) = 0;
							m_bCreated = false;
						}
						if (m_sRect.Right > 0 && m_sRect.Bottom > 0 && m_pGraphics)
						{
							m_pGraphics->CreateTextures(GL_TEXTURE_2D, 1, reinterpret_cast<GLuint*>(&m_hHandle));
							if (*reinterpret_cast<GLuint*>(&m_hHandle) == 0)
								return false;
							m_pGraphics->TextureStorage2D(*reinterpret_cast<GLuint*>(&m_hHandle), m_iActualLevelCount, Formats[(int)m_eFormat], m_sRect.Right, m_sRect.Bottom);
							UpdateParameters();
							m_bCreated = true;
							m_sInvalidRect = m_sRect;
						}
						return true;
					}
					return false;
				}

				bool CTexture::setRequiredLevelCount(const int value)
				{
					if (value >= 0 && value != m_iRequiredLevelCount)
					{
						m_iRequiredLevelCount = value;
						if (m_sRect.Right > 0 && m_sRect.Bottom > 0 && m_pGraphics)
						{
							int l{ CalculateLevelCount(m_sRect.Right, m_sRect.Bottom, m_iRequiredLevelCount) };
							if (l != m_iActualLevelCount)
							{
								m_iActualLevelCount = l;
								if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0)
								{
									m_pGraphics->DeleteTextures(1, reinterpret_cast<GLuint*>(&m_hHandle));
									*reinterpret_cast<GLuint*>(&m_hHandle) = 0;
									m_bCreated = false;
								}
								m_pGraphics->CreateTextures(GL_TEXTURE_2D, 1, reinterpret_cast<GLuint*>(&m_hHandle));
								if (*reinterpret_cast<GLuint*>(&m_hHandle) == 0)
									return false;
								m_pGraphics->TextureStorage2D(*reinterpret_cast<GLuint*>(&m_hHandle), m_iActualLevelCount, Formats[(int)m_eFormat], m_sRect.Right, m_sRect.Bottom);
								UpdateParameters();
								m_bCreated = true;
								m_sInvalidRect = m_sRect;
							}
						}
						return true;
					}
					return false;
				}

				bool CTexture::setSize(const int width, const int height)
				{
					if (width >= 0 && height >= 0 && (width != m_sRect.Right || height != m_sRect.Bottom) && m_pGraphics)
					{
						if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0)
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
							m_pGraphics->CreateTextures(GL_TEXTURE_2D, 1, reinterpret_cast<GLuint*>(&m_hHandle));
							if (*reinterpret_cast<GLuint*>(&m_hHandle) == 0)
								return false;
							m_iActualLevelCount = CalculateLevelCount(m_sRect.Right, m_sRect.Bottom, m_iRequiredLevelCount);
							m_pGraphics->TextureStorage2D(*reinterpret_cast<GLuint*>(&m_hHandle), m_iActualLevelCount, Formats[(int)m_eFormat], m_sRect.Right, m_sRect.Bottom);
							UpdateParameters();
							m_bCreated = true;
							m_sInvalidRect = m_sRect;
						}
						return true;
					}
					return false;
				}

				bool CTexture::setDepthStencilMode(const TextureDepthStencilMode value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eDepthStencilMode)
					{
						m_eDepthStencilMode = value;
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_DEPTH_STENCIL_TEXTURE_MODE, DepthStencilModes[(int)m_eDepthStencilMode]);
						return true;
					}
					return false;
				}

				bool CTexture::setBaseLevel(const int value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value >= 0 && value != m_iBaseLevel)
					{
						m_iBaseLevel = value;
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_BASE_LEVEL, (GLint)m_iBaseLevel);
						return true;
					}
					return false;
				}

				bool CTexture::setMinFilter(const TextureMinFilter value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eMinFilter)
					{
						m_eMinFilter = value;
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_MIN_FILTER, MinFilters[(int)m_eMinFilter]);
						return true;
					}
					return false;
				}

				bool CTexture::setMagFilter(const TextureMagFilter value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eMagFilter)
					{
						m_eMagFilter = value;
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_MAG_FILTER, MagFilters[(int)m_eMagFilter]);
						return true;
					}
					return false;
				}

				bool CTexture::setMinLOD(const float value, const float relative_tolerance)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && ntl::NotEquals<float>(value, m_fMinLOD, relative_tolerance))
					{
						m_fMinLOD = value;
						m_pGraphics->TextureParameterf(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_MIN_LOD, m_fMinLOD);
						if (m_fMinLOD >= m_fMaxLOD)
						{
							m_fMaxLOD = m_fMinLOD + 1;
							m_pGraphics->TextureParameterf(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_MAX_LOD, m_fMaxLOD);
						}
						return true;
					}
					return false;
				}

				bool CTexture::setMaxLOD(const float value, const float relative_tolerance)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && ntl::NotEquals<float>(value, m_fMaxLOD, relative_tolerance))
					{
						m_fMaxLOD = value;
						m_pGraphics->TextureParameterf(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_MAX_LOD, m_fMaxLOD);
						if (m_fMinLOD >= m_fMaxLOD)
						{
							m_fMinLOD = m_fMaxLOD - 1;
							m_pGraphics->TextureParameterf(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_MIN_LOD, m_fMinLOD);
						}
						return true;
					}
					return false;
				}

				bool CTexture::setWrapS(const TextureWrap value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eWrapS)
					{
						m_eWrapS = value;
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_WRAP_S, Wraps[(int)m_eWrapS]);
						return true;
					}
					return false;
				}

				bool CTexture::setWrapT(const TextureWrap value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eWrapT)
					{
						m_eWrapT = value;
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_WRAP_T, Wraps[(int)m_eWrapT]);
						return true;
					}
					return false;
				}

				bool CTexture::setWrapR(const TextureWrap value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eWrapR)
					{
						m_eWrapR = value;
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_WRAP_R, Wraps[(int)m_eWrapR]);
						return true;
					}
					return false;
				}

				bool CTexture::setBorderColor(const Color &value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_sBorderColor)
					{
						m_sBorderColor = value;
						GLfloat data[4]{ m_sBorderColor.R * 255.0f, m_sBorderColor.G * 255.0f, m_sBorderColor.B * 255.0f, m_sBorderColor.A * 255.0f };
						m_pGraphics->TextureParameterfv(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_BORDER_COLOR, data);
						return true;
					}
					return false;
				}

				bool CTexture::setCompareMode(const TextureCompareMode value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eCompareMode)
					{
						m_eCompareMode = value;
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_COMPARE_MODE, CompareModes[(int)m_eCompareMode]);
						return true;
					}
					return false;
				}

				bool CTexture::setCompareFunction(const TextureCompareFunction value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eCompareFunction)
					{
						m_eCompareFunction = value;
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_COMPARE_FUNC, CompareFuncs[(int)m_eCompareFunction]);
						return true;
					}
					return false;
				}

				bool CTexture::setLODBias(const float value, const float relative_tolerance)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && ntl::NotEquals<float>(value, m_fLODBias, relative_tolerance))
					{
						m_fLODBias = value;
						m_pGraphics->TextureParameterf(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_LOD_BIAS, m_fLODBias);
						return true;
					}
					return false;
				}

				bool CTexture::setMaxLevel(const int value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value > 0 && value != m_iMaxLevel)
					{
						m_iMaxLevel = value;
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_MAX_LEVEL, (GLint)m_iMaxLevel);
						return true;
					}
					return false;
				}

				bool CTexture::setSwizzleR(const TextureSwizzle value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eSwizzleR)
					{
						m_eSwizzleR = value;
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_SWIZZLE_R, Swizzles[(int)m_eSwizzleR]);
						return true;
					}
					return false;
				}

				bool CTexture::setSwizzleG(const TextureSwizzle value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eSwizzleG)
					{
						m_eSwizzleG = value;
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_SWIZZLE_G, Swizzles[(int)m_eSwizzleG]);
						return true;
					}
					return false;
				}

				bool CTexture::setSwizzleB(const TextureSwizzle value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eSwizzleB)
					{
						m_eSwizzleB = value;
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_SWIZZLE_B, Swizzles[(int)m_eSwizzleB]);
						return true;
					}
					return false;
				}

				bool CTexture::setSwizzleA(const TextureSwizzle value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && value != m_eSwizzleA)
					{
						m_eSwizzleA = value;
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_SWIZZLE_A, Swizzles[(int)m_eSwizzleA]);
						return true;
					}
					return false;
				}

				bool CTexture::setSwizzleRGBA(const TextureSwizzle value)
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0 && (value != m_eSwizzleR || value != m_eSwizzleG || value != m_eSwizzleB || value != m_eSwizzleA))
					{
						m_eSwizzleR = value;
						m_eSwizzleG = value;
						m_eSwizzleB = value;
						m_eSwizzleA = value;
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_SWIZZLE_RGBA, Swizzles[(int)m_eSwizzleR]);
						return true;
					}
					return false;
				}
			#pragma endregion

			#pragma region ITexture methods
				ITexture::IData *CTexture::Lock(const TextureFormat format, const int level, const bool read_only)
				{
					if (!m_pData && level >= 0 && level < m_iActualLevelCount && *reinterpret_cast<GLuint*>(&m_hHandle) > 0)
					{
						switch (format)
						{
						case TextureFormat::Alpha:
							m_pData = new CDataAlpha(this, level, read_only);
							break;
						case TextureFormat::AlphaFloat:
							m_pData = new CDataAlphaFloat(this, level, read_only);
							break;
						case TextureFormat::RGB:
							m_pData = new CDataRGB(this, level, read_only);
							break;
						case TextureFormat::RGBFloat:
							m_pData = new CDataRGBFloat(this, level, read_only);
							break;
						case TextureFormat::RGBA:
							if (m_bPrecomputed)
								m_pData = new CDataRGBAPrecomputed(this, level, read_only);
							else
								m_pData = new CDataRGBA(this, level, read_only);
							break;
						case TextureFormat::RGBAFloat:
							if (m_bPrecomputed)
								m_pData = new CDataRGBAFloatPrecomputed(this, level, read_only);
							else
								m_pData = new CDataRGBAFloat(this, level, read_only);
							break;
						case TextureFormat::Depth:
							m_pData = new CDataDepth(this, level, read_only);
							break;
						case TextureFormat::Stencil:
							m_pData = new CDataStencil(this, level, read_only);
							break;
						}
						m_pData->RegisterReleaseListener(&m_cDataReleaseListener);
						return m_pData;
					}
					return nullptr;
				}
			#pragma endregion

			#pragma region Helpers
				int CTexture::CalculateLevelCount(const int width, const int height, const int max_level_count)
				{
					if (max_level_count > 0)
						return ntl::Max<int>(1, ntl::Min<int>(max_level_count, ntl::Round<int, float>(std::log2((float)ntl::Min<int>(width, height)))));
					return ntl::Max<int>(1, ntl::Round<int, float>(std::log2((float)ntl::Min<int>(width, height))));
				}

				void CTexture::UpdateParameters()
				{
					if (m_eDepthStencilMode != TextureDepthStencilMode::DepthComponent)
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_DEPTH_STENCIL_TEXTURE_MODE, DepthStencilModes[(int)m_eDepthStencilMode]);
					if (m_iBaseLevel != 0)
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_BASE_LEVEL, (GLint)m_iBaseLevel);
					if (m_eMinFilter != TextureMinFilter::Nearest)
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_MIN_FILTER, MinFilters[(int)m_eMinFilter]);
					if (m_eMagFilter != TextureMagFilter::Nearest)
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_MAG_FILTER, MagFilters[(int)m_eMagFilter]);
					if (ntl::NotEquals<float>(m_fMinLOD, -1000.0f, ntl::RelativeTolerance<float>))
						m_pGraphics->TextureParameterf(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_MIN_LOD, m_fMinLOD);
					if (ntl::NotEquals<float>(m_fMaxLOD, 1000.0f, ntl::RelativeTolerance<float>))
						m_pGraphics->TextureParameterf(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_MAX_LOD, m_fMaxLOD);
					if (m_eWrapS != TextureWrap::Repeat)
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_WRAP_S, Wraps[(int)m_eWrapS]);
					if (m_eWrapT != TextureWrap::Repeat)
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_WRAP_T, Wraps[(int)m_eWrapT]);
					if (m_eWrapR != TextureWrap::Repeat)
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_WRAP_R, Wraps[(int)m_eWrapR]);
					if (m_sBorderColor != Color{ 0, 0, 0, 0 })
					{
						GLfloat data[4]{ m_sBorderColor.R * 255.0f, m_sBorderColor.G * 255.0f, m_sBorderColor.B * 255.0f, m_sBorderColor.A * 255.0f };
						m_pGraphics->TextureParameterfv(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_BORDER_COLOR, data);
					}
					if (m_eCompareMode != TextureCompareMode::None)
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_COMPARE_MODE, CompareModes[(int)m_eCompareMode]);
					if (m_eCompareFunction != TextureCompareFunction::Always)
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_COMPARE_FUNC, CompareFuncs[(int)m_eCompareFunction]);
					if (ntl::NotEquals<float>(m_fLODBias, 0.0f, ntl::RelativeTolerance<float>))
						m_pGraphics->TextureParameterf(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_LOD_BIAS, m_fLODBias);
					if (m_iMaxLevel != 1000)
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_MAX_LEVEL, (GLint)m_iMaxLevel);
					if (m_eSwizzleR != TextureSwizzle::Red)
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_SWIZZLE_R, Swizzles[(int)m_eSwizzleR]);
					if (m_eSwizzleG != TextureSwizzle::Green)
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_SWIZZLE_G, Swizzles[(int)m_eSwizzleG]);
					if (m_eSwizzleB != TextureSwizzle::Blue)
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_SWIZZLE_B, Swizzles[(int)m_eSwizzleB]);
					if (m_eSwizzleA != TextureSwizzle::Alpha)
						m_pGraphics->TextureParameteri(*reinterpret_cast<GLuint*>(&m_hHandle), GL_TEXTURE_SWIZZLE_A, Swizzles[(int)m_eSwizzleA]);
				}
			#pragma endregion
			}
		}
	}
}
#endif