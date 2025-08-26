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

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
			namespace opengl
			{
			#pragma region CSearchPlatformFont
				bool CBaseRenderer::CSearchPlatformFont::RegisterReleaseListener(IReleasableListener *value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchPlatformFont::UnregisterReleaseListener(IReleasableListener *value)
				{
					return false;
				}

				int CBaseRenderer::CSearchPlatformFont::AddRef()
				{
					return 0;
				}

				bool CBaseRenderer::CSearchPlatformFont::Release(const bool force)
				{
					return false;
				}

				IPlatformFont::Char *CBaseRenderer::CSearchPlatformFont::getChar(const wchar_t chr)
				{
					return nullptr;
				}

				PointF CBaseRenderer::CSearchPlatformFont::getStringSize(const String &str, const float distance)
				{
					return PointF{ 0, 0 };
				}

				ITexture *CBaseRenderer::CSearchPlatformFont::getTexture()
				{
					return nullptr;
				}
			#pragma endregion

			#pragma region CSearchTexture
				bool CBaseRenderer::CSearchTexture::RegisterReleaseListener(IReleasableListener *value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::UnregisterReleaseListener(IReleasableListener *value)
				{
					return false;
				}

				int CBaseRenderer::CSearchTexture::AddRef()
				{
					return 0;
				}

				bool CBaseRenderer::CSearchTexture::Release(const bool force)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::isValid() const
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setFormat(const TextureFormat value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setRequiredLevelCount(const int value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setSize(const int width, const int height)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setValid(const bool value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setInvalidRect(const nitisa::Rect &value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setDepthStencilMode(const TextureDepthStencilMode value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setBaseLevel(const int value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setMinFilter(const TextureMinFilter value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setMagFilter(const TextureMagFilter value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setMinLOD(const float value, const float relative_tolerance)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setMaxLOD(const float value, const float relative_tolerance)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setWrapS(const TextureWrap value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setWrapT(const TextureWrap value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setWrapR(const TextureWrap value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setBorderColor(const Color &value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setCompareMode(const TextureCompareMode value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setCompareFunction(const TextureCompareFunction value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setLODBias(const float value, const float relative_tolerance)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setMaxLevel(const int value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setSwizzleR(const TextureSwizzle value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setSwizzleG(const TextureSwizzle value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setSwizzleB(const TextureSwizzle value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setSwizzleA(const TextureSwizzle value)
				{
					return false;
				}

				bool CBaseRenderer::CSearchTexture::setSwizzleRGBA(const TextureSwizzle value)
				{
					return false;
				}

				ITexture::IData *CBaseRenderer::CSearchTexture::Lock(const TextureFormat format, const int level, const bool read_only)
				{
					return nullptr;
				}
			#pragma endregion

			#pragma region Constructor & destructor
				CBaseRenderer::CBaseRenderer(const bool double_buffered, const int multisample, const Version2 &max_version) :
					CReleasable(),
					m_pDefaultFramebuffer{ nullptr },
					m_pFramebuffer{ nullptr },
					m_pGradientPositions{ nullptr },
					m_pGradientColors{ nullptr },
					m_bDoubleBuffered{ double_buffered },
					m_iMultisample{ ntl::Max<int>(0, multisample) },
					m_sRequestedVersion{ max_version },
					m_bFontsSorted{ true },
					m_bFileTexturesSorted{ true },
					m_bImageTexturesSorted{ true },
					m_bDrawing{ false },
					m_sSearchImageTexture{ nullptr, &m_cSearchTexture },
					m_hContext{ 0 },
					m_pGraphics{ nullptr },
					m_pApplication{ cast<CApplication*>(Application) }
				{
					m_pWindow = nullptr;
					m_pNativeGraphics = nullptr;
					m_pActiveProgram = nullptr;
					m_pActiveFramebuffer = nullptr;
					m_pActiveVertexArray = nullptr;
					m_pActiveTarget = nullptr;
					m_pActiveMask = nullptr;
					m_pActiveBlock = nullptr;
					m_pActiveBitmask = nullptr;
					m_pActiveSplineLimits = nullptr;
					m_pActivePrimitiveMatrix = nullptr;
					m_sViewport = Rect{ 0, 0, -1, -1 };
					m_eTechnology = RendererTechnology::OpenGL;
					m_eInitializationStatus = InitializationStatus::NotInitialized;
				}

				void CBaseRenderer::BeforeRelease()
				{
					CleanUp();
				}
			#pragma endregion

			#pragma region IRenderer getters
				int CBaseRenderer::getPlatformFontCount()
				{
					return (int)m_aFonts.size();
				}

				IPlatformFont *CBaseRenderer::getPlatformFont(const int index)
				{
					if (index >= 0 && index < (int)m_aFonts.size())
					{
						SortFonts();
						return m_aFonts[index];
					}
					return nullptr;
				}

				int CBaseRenderer::getProgramCount()
				{
					return (int)m_aPrograms.size();
				}

				IProgram *CBaseRenderer::getProgram(const int index)
				{
					if (index >= 0 && index < (int)m_aPrograms.size())
						return m_aPrograms[index];
					return nullptr;
				}

				int CBaseRenderer::getFramebufferCount()
				{
					return (int)m_aFramebuffers.size();
				}

				IFramebuffer *CBaseRenderer::getFramebuffer(const int index)
				{
					if (index >= 0 && index < (int)m_aFramebuffers.size())
						return m_aFramebuffers[index];
					return nullptr;
				}

				int CBaseRenderer::getVertexArrayCount()
				{
					return (int)m_aVertexArrays.size();
				}

				IVertexArray *CBaseRenderer::getVertexArray(const int index)
				{
					if (index >= 0 && index < (int)m_aVertexArrays.size())
						return m_aVertexArrays[index];
					return nullptr;
				}

				int CBaseRenderer::getTextureCount()
				{
					return (int)m_aTextures.size();
				}

				ITexture *CBaseRenderer::getTexture(const int index)
				{
					if (index >= 0 && index < (int)m_aTextures.size())
						return m_aTextures[index];
					return nullptr;
				}

				int CBaseRenderer::getImageTextureCount()
				{
					return (int)m_aImageTextures.size();
				}

				ITexture *CBaseRenderer::getImageTexture(const int index)
				{
					if (index >= 0 && index < (int)m_aImageTextures.size())
					{
						SortImageTextures();
						return m_aImageTextures[index].Texture;
					}
					return nullptr;
				}

				const Image *CBaseRenderer::getImageTextureData(const int index)
				{
					if (index >= 0 && index < (int)m_aImageTextures.size())
					{
						SortImageTextures();
						return m_aImageTextures[index].Data;
					}
					return nullptr;
				}

				int CBaseRenderer::getMaskCount()
				{
					return (int)m_aMasks.size();
				}

				ITexture *CBaseRenderer::getMask(const int index)
				{
					if (index >= 0 && index < (int)m_aMasks.size())
						return m_aMasks[index].Texture;
					return nullptr;
				}

				const Mat4f *CBaseRenderer::getMaskMatrix(const int index)
				{
					if (index >= 0 && index < (int)m_aMasks.size())
						return &m_aMasks[index].M;
					return nullptr;
				}

				bool CBaseRenderer::isWindowSupported(IWindow *window)
				{
					bool result{ false };
					CWindow *w{ cast<CWindow*>(window) };
					if (w && !w->isCreated())
					{
						COpenGL *graphics{ COpenGL::Create(nullptr) };
						if (graphics)
						{
							GLXFBConfig config;
							if (FindPixelFormat(*reinterpret_cast<PlatformHandle*>(&config), m_bDoubleBuffered, m_iMultisample))
							{
								*reinterpret_cast<XVisualInfo**>(&w->m_hVisualInfo) = ngl::glXGetVisualFromFBConfig(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), config);
								if (*reinterpret_cast<XVisualInfo**>(&w->m_hVisualInfo))
									result = true;
							}
							graphics->Release();
						}
					}
					if (!result)
						m_eInitializationStatus = InitializationStatus::Window;
					return result;
				}

				int CBaseRenderer::getTextureMultisampleCount()
				{
					return (int)m_aTextureMultisamples.size();
				}

				ITextureMultisample *CBaseRenderer::getTextureMultisample(const int index)
				{
					if (index >= 0 && index < (int)m_aTextureMultisamples.size())
						return m_aTextureMultisamples[index];
					return nullptr;
				}
			#pragma endregion

			#pragma region IRenderer helpers
				IRenderer *CBaseRenderer::Activate()
				{
					if (*reinterpret_cast<GLXContext*>(&m_hContext) && glXGetCurrentContext() != *reinterpret_cast<GLXContext*>(&m_hContext))
						glXMakeCurrent(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<const ::Window*>(&m_pWindow->Handle), *reinterpret_cast<GLXContext*>(&m_hContext));
					return this;
				}
			#pragma endregion

			#pragma region Helpers
				bool CBaseRenderer::CompareFonts(IPlatformFont *a, IPlatformFont *b)
				{
					if (a->FontName < b->FontName)
						return true;
					if (a->FontName > b->FontName)
						return false;
					if (a->Height < b->Height)
						return true;
					if (a->Height > b->Height)
						return false;
					if (a->Weight < b->Weight)
						return true;
					if (a->Weight > b->Weight)
						return false;
					if (a->Italic < b->Italic)
						return true;
					if (a->Italic > b->Italic)
						return false;
					if (a->Underline < b->Underline)
						return true;
					if (a->Underline > b->Underline)
						return false;
					if (a->StrikeOut < b->StrikeOut)
						return true;
					if (a->StrikeOut > b->StrikeOut)
						return false;
					return a->Monospace < b->Monospace;
				}

				bool CBaseRenderer::CompareTextures(ITexture *a, ITexture *b)
				{
					if (a->Filename < b->Filename)
						return true;
					if (a->Filename > b->Filename)
						return false;
					if (a->RequiredLevelCount < b->RequiredLevelCount)
						return true;
					if (a->RequiredLevelCount > b->RequiredLevelCount)
						return false;
					if (a->Format < b->Format)
						return true;
					if (a->Format > b->Format)
						return false;
					return a->Precomputed < b->Precomputed;
				}

				bool CBaseRenderer::CompareImageTextures(const IMAGE_TEXTURE &a, const IMAGE_TEXTURE &b)
				{
					if (a.Data < b.Data)
						return true;
					if (a.Data > b.Data)
						return false;
					if (a.Texture->RequiredLevelCount < b.Texture->RequiredLevelCount)
						return true;
					if (a.Texture->RequiredLevelCount > b.Texture->RequiredLevelCount)
						return false;
					if (a.Texture->Format < b.Texture->Format)
						return true;
					if (a.Texture->Format > b.Texture->Format)
						return false;
					return a.Texture->Precomputed < b.Texture->Precomputed;
				}

				void CBaseRenderer::SortFonts()
				{
					if (!m_bFontsSorted)
					{
						std::sort(m_aFonts.begin(), m_aFonts.end(), CompareFonts);
						m_bFontsSorted = true;
					}
				}

				void CBaseRenderer::SortFileTextures()
				{
					if (!m_bFileTexturesSorted)
					{
						std::sort(m_aFileTextures.begin(), m_aFileTextures.end(), CompareTextures);
						m_bFileTexturesSorted = true;
					}
				}

				void CBaseRenderer::SortImageTextures()
				{
					if (!m_bImageTexturesSorted)
					{
						std::sort(m_aImageTextures.begin(), m_aImageTextures.end(), CompareImageTextures);
						m_bImageTexturesSorted = true;
					}
				}

				bool CBaseRenderer::FindPixelFormat(PlatformHandle &config, const bool double_buffered, int &multisample)
				{
					*reinterpret_cast<GLXFBConfig*>(&config) = nullptr;
					while (multisample > 0)
					{
						int visual_attributes[]{
							GLX_X_RENDERABLE, True,
							GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
							GLX_RENDER_TYPE, GLX_RGBA_BIT,
							GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
							GLX_RED_SIZE, 8,
							GLX_GREEN_SIZE, 8,
							GLX_BLUE_SIZE, 8,
							GLX_ALPHA_SIZE, 8,
							GLX_DEPTH_SIZE, 24,
							GLX_STENCIL_SIZE, 8,
							GLX_DOUBLEBUFFER, double_buffered ? True : False,
							GLX_SAMPLE_BUFFERS, 1,
							GLX_SAMPLES, multisample,
							None
						};
						int fb_config_count;
						GLXFBConfig *fb_configs{ ngl::glXChooseFBConfig(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), DefaultScreen(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle)), visual_attributes, &fb_config_count) };
						if (fb_configs)
						{
							if (fb_config_count > 0)
								*reinterpret_cast<GLXFBConfig*>(&config) = fb_configs[0];
							XFree(fb_configs);
							if (fb_config_count > 0)
								return true;
						}
						multisample--;
					}
					int visual_attributes[]{
							GLX_X_RENDERABLE, True,
							GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
							GLX_RENDER_TYPE, GLX_RGBA_BIT,
							GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
							GLX_RED_SIZE, 8,
							GLX_GREEN_SIZE, 8,
							GLX_BLUE_SIZE, 8,
							GLX_ALPHA_SIZE, 8,
							GLX_DEPTH_SIZE, 24,
							GLX_STENCIL_SIZE, 8,
							GLX_DOUBLEBUFFER, double_buffered ? True : False,
							None
					};
					int fb_config_count;
					GLXFBConfig *fb_configs{ ngl::glXChooseFBConfig(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), DefaultScreen(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle)), visual_attributes, &fb_config_count) };
					if (fb_configs)
					{
						if (fb_config_count > 0)
							*reinterpret_cast<GLXFBConfig*>(&config) = fb_configs[0];
						XFree(fb_configs);
						if (fb_config_count > 0)
							return true;
					}
					return false;
				}
			#pragma endregion
			}
		}
	}
}
#endif