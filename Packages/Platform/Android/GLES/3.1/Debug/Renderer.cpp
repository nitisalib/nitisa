// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef __ANDROID__
#include "../../../../OpenGL/OpenGL.h"
#include "../../../NativeApplication.h"
#include "../../ProgramMini.h"
#include "../../ProgramMain.h"
#include "../../VertexArrayDynamic.h"
#include "../../VertexArrayImmutable.h"

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
			namespace gles31d
			{
				const Version2 MIN_OPENGL_VERSION{ 3, 1 };
				const VertexFormat DEFAULT_VERTEX_FORMAT{ 0, 2, 1, 1, 0, 0, 0, 0, 0, 1, VertexFormat::npos, VertexFormat::npos, VertexFormat::npos, 0, VertexFormat::npos, VertexFormat::npos, 0 };
				const size_t IDX_T{ 0 };
				const size_t IDX_B{ 1 };
				const size_t IDX_P{ 0 };
				const size_t IDX_C{ 0 };
				const GLenum SHADER_TYPES[]{ GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER, GL_COMPUTE_SHADER };

				const AnsiString ShaderHeader{
					"#version 310 es\n"
					"precision mediump float;\n"
				};
				const AnsiString ShaderVertex{
					#include "../../../../OpenGL/Shaders/GL31-GLES30/vertex.glsl"
				};
				const AnsiString ShaderFragmentBlock{
					#include "../../../../OpenGL/Shaders/fragment-block.glsl"
				};
				const AnsiString ShaderFragmentSpline{
					#include "../../../../OpenGL/Shaders/fragment-spline.glsl"
				};
				const AnsiString ShaderFragmentMini{
					#include "../../../../OpenGL/Shaders/GL31-GLES30/fragment-mini.glsl"
				};
				const AnsiString ShaderFragmentMain{
					#include "../../../../OpenGL/Shaders/GL32-GLES31/fragment-main.glsl"
				};
				const AnsiString ShaderFragmentUtils{
					#include "../../../../OpenGL/Shaders/fragment-utils.glsl"
				};

			#pragma region CTextureReleaseListener
				CRenderer::CTextureReleaseListener::CTextureReleaseListener(CRenderer *renderer) :
					m_pRenderer{ renderer }
				{

				}

				void CRenderer::CTextureReleaseListener::NotifyOnRelease(IReleasable *sender)
				{
					ITexture *texture{ cast<ITexture*>(sender) };
					if (!texture)
					{
						m_pRenderer->m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RELEASE_NON_TEXTURE);
						return;
					}
					if (m_pRenderer->m_aMasks.size() > 0)
					{
						for (size_t i = 0; i < m_pRenderer->m_aMasks.size(); i++)
							if (m_pRenderer->m_aMasks[i].Texture == texture)
							{
								m_pRenderer->m_aMasks.erase(m_pRenderer->m_aMasks.begin() + i, m_pRenderer->m_aMasks.end() - 1);
								if (m_pRenderer->m_pActiveProgramBase && !m_pRenderer->m_pActiveMask)
								{
									if (m_pRenderer->m_aMasks.size() == 0)
									{
										m_pRenderer->m_pGraphics->Uniform1i(m_pRenderer->m_pActiveProgramBase->m_sMask.SubroutineTest, m_pRenderer->m_pActiveProgramBase->m_sMask.None);
									}
									else
									{
										m_pRenderer->m_pGraphics->ActiveTexture(GL_TEXTURE3);
										m_pRenderer->m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_pRenderer->m_aMasks[m_pRenderer->m_aMasks.size() - 1].Texture->Handle));
									}
								}
								m_pRenderer->m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RELEASE_USED_MASK);
								break;
							}
					}
					if (texture == m_pRenderer->m_pGradientPositions)
						m_pRenderer->m_pGradientPositions = nullptr;
					if (texture == m_pRenderer->m_pGradientColors)
						m_pRenderer->m_pGradientColors = nullptr;
					if (texture == m_pRenderer->m_pActiveMask)
						m_pRenderer->ActivateMask(nullptr);
					std::vector<ITexture*>::iterator p1{ std::find(m_pRenderer->m_aFileTextures.begin(), m_pRenderer->m_aFileTextures.end(), texture) };
					if (p1 != m_pRenderer->m_aFileTextures.end())
						m_pRenderer->m_aFileTextures.erase(p1);
					bool found{ false };
					std::vector<ITexture*>::iterator p2{ std::find(m_pRenderer->m_aTextures.begin(), m_pRenderer->m_aTextures.end(), texture) };
					if (p2 != m_pRenderer->m_aTextures.end())
					{
						m_pRenderer->m_aTextures.erase(p2);
						found = true;
					}
					for (auto p3 = m_pRenderer->m_aImageTextures.begin(); p3 != m_pRenderer->m_aImageTextures.end(); p3++)
						if (p3->Texture == texture)
						{
							m_pRenderer->m_aImageTextures.erase(p3);
							found = true;
							break;
						}
					if (!found)
						m_pRenderer->m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RELEASE_UNKNOWN_TEXTURE);
					if (m_pRenderer->m_pDefaultFramebuffer)
					{
						for (int i = 0; i < m_pRenderer->m_pDefaultFramebuffer->getColorAttachmentCount(); i++)
							if (m_pRenderer->m_pDefaultFramebuffer->getColorAttachment(i) == texture)
								m_pRenderer->m_pDefaultFramebuffer->setColorAttachment(nullptr, i, 0, false);
						if (m_pRenderer->m_pDefaultFramebuffer->DepthAttachment == texture)
							m_pRenderer->m_pDefaultFramebuffer->setDepthAttachment(nullptr, false);
						if (m_pRenderer->m_pDefaultFramebuffer->StencilAttachment == texture)
							m_pRenderer->m_pDefaultFramebuffer->setStencilAttachment(nullptr, false);
					}
				}
			#pragma endregion

			#pragma region CTextureMultisampleReleaseListener
				CRenderer::CTextureMultisampleReleaseListener::CTextureMultisampleReleaseListener(CRenderer *renderer) :
					m_pRenderer{ renderer }
				{

				}

				void CRenderer::CTextureMultisampleReleaseListener::NotifyOnRelease(IReleasable *sender)
				{
					ITextureMultisample *texture{ cast<ITextureMultisample*>(sender) };
					if (!texture)
					{
						m_pRenderer->m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RELEASE_NON_TEXTURE_MULTISAMPLE);
						return;
					}
					std::vector<ITextureMultisample*>::iterator p{ std::find(m_pRenderer->m_aTextureMultisamples.begin(), m_pRenderer->m_aTextureMultisamples.end(), texture) };
					if (p != m_pRenderer->m_aTextureMultisamples.end())
						m_pRenderer->m_aTextureMultisamples.erase(p);
					else
						m_pRenderer->m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RELEASE_UNKNOWN_TEXTURE_MULTISAMPLE);
					if (m_pRenderer->m_pDefaultFramebuffer)
					{
						for (int i = 0; i < m_pRenderer->m_pDefaultFramebuffer->getColorAttachmentCount(); i++)
							if (m_pRenderer->m_pDefaultFramebuffer->getColorAttachment(i) == texture)
								m_pRenderer->m_pDefaultFramebuffer->setColorAttachment(nullptr, i, 0, false);
						if (m_pRenderer->m_pDefaultFramebuffer->DepthAttachment == texture)
							m_pRenderer->m_pDefaultFramebuffer->setDepthAttachment(nullptr, 0, false);
						if (m_pRenderer->m_pDefaultFramebuffer->StencilAttachment == texture)
							m_pRenderer->m_pDefaultFramebuffer->setStencilAttachment(nullptr, 0, false);
					}
				}
			#pragma endregion

			#pragma region CPlatformFontReleaseListener
				CRenderer::CPlatformFontReleaseListener::CPlatformFontReleaseListener(CRenderer *renderer) :
					m_pRenderer{ renderer }
				{

				}

				void CRenderer::CPlatformFontReleaseListener::NotifyOnRelease(IReleasable *sender)
				{
					IPlatformFont *font{ cast<IPlatformFont*>(sender) };
					if (!font)
					{
						m_pRenderer->m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RELEASE_NON_PLATFORM_FONT);
						return;
					}
					std::vector<IPlatformFont*>::iterator p{ std::find(m_pRenderer->m_aFonts.begin(), m_pRenderer->m_aFonts.end(), font) };
					if (p != m_pRenderer->m_aFonts.end())
						m_pRenderer->m_aFonts.erase(p);
					else
						m_pRenderer->m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RELEASE_UNKNOWN_PLATFORM_FONT);
				}
			#pragma endregion

			#pragma region CProgramReleaseListener
				CRenderer::CProgramReleaseListener::CProgramReleaseListener(CRenderer *renderer) :
					m_pRenderer{ renderer }
				{

				}

				void CRenderer::CProgramReleaseListener::NotifyOnRelease(IReleasable *sender)
				{
					IProgram *program{ cast<IProgram*>(sender) };
					if (!program)
					{
						m_pRenderer->m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RELEASE_NON_PROGRAM);
						return;
					}
					if (m_pRenderer->m_pActiveProgram == program)
						m_pRenderer->ActivateProgram(nullptr);
					std::vector<IProgram*>::iterator pos{ std::find(m_pRenderer->m_aPrograms.begin(), m_pRenderer->m_aPrograms.end(), program) };
					if (pos != m_pRenderer->m_aPrograms.end())
						m_pRenderer->m_aPrograms.erase(pos);
					else if (program != m_pRenderer->m_pProgramMain)
						m_pRenderer->m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RELEASE_UNKNOWN_PROGRAM);
					if (program == m_pRenderer->m_pProgramMain)
						m_pRenderer->m_pProgramMain = nullptr;
				}
			#pragma endregion

			#pragma region CFramebufferReleaseListener
				CRenderer::CFramebufferReleaseListener::CFramebufferReleaseListener(CRenderer *renderer) :
					m_pRenderer{ renderer }
				{

				}

				void CRenderer::CFramebufferReleaseListener::NotifyOnRelease(IReleasable *sender)
				{
					IFramebuffer *framebuffer{ cast<IFramebuffer*>(sender) };
					if (!framebuffer)
					{
						m_pRenderer->m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RELEASE_NON_FRAMEBUFFER);
						return;
					}
					if (m_pRenderer->m_pActiveFramebuffer == framebuffer)
						m_pRenderer->ActivateFramebuffer(nullptr);
					std::vector<IFramebuffer*>::iterator pos{ std::find(m_pRenderer->m_aFramebuffers.begin(), m_pRenderer->m_aFramebuffers.end(), framebuffer) };
					if (pos != m_pRenderer->m_aFramebuffers.end())
						m_pRenderer->m_aFramebuffers.erase(pos);
					else if (framebuffer != m_pRenderer->m_pDefaultFramebuffer)
						m_pRenderer->m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RELEASE_UNKNOWN_FRAMEBUFFER);
					if (framebuffer == m_pRenderer->m_pDefaultFramebuffer)
						m_pRenderer->m_pDefaultFramebuffer = nullptr;
				}
			#pragma endregion

			#pragma region CVertexArrayReleaseListener
				CRenderer::CVertexArrayReleaseListener::CVertexArrayReleaseListener(CRenderer *renderer) :
					m_pRenderer{ renderer }
				{

				}

				void CRenderer::CVertexArrayReleaseListener::NotifyOnRelease(IReleasable *sender)
				{
					IVertexArray *va{ cast<IVertexArray*>(sender) };
					if (!va)
					{
						m_pRenderer->m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RELEASE_NON_VERTEX_ARRAY);
						return;
					}
					if (m_pRenderer->m_pActiveVertexArray == va)
						m_pRenderer->ActivateVertexArray(nullptr);
					std::vector<IVertexArray*>::iterator pos{ std::find(m_pRenderer->m_aVertexArrays.begin(), m_pRenderer->m_aVertexArrays.end(), va) };
					if (pos != m_pRenderer->m_aVertexArrays.end())
						m_pRenderer->m_aVertexArrays.erase(pos);
					else if (va != m_pRenderer->m_pDefaultVertexArray)
						m_pRenderer->m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RELEASE_UNKNOWN_VERTEX_ARRAY);
					if (va == m_pRenderer->m_pDefaultVertexArray)
						m_pRenderer->m_pDefaultVertexArray = nullptr;
				}
			#pragma endregion

			#pragma region Constructor & destructor
				CRenderer::CRenderer(
					IErrorListener *listener,
					const bool double_buffered,
					const int multisample,
					const Version2 &max_version,
					const bool use_debug_context
				) :
					gles::CBaseRenderer(double_buffered, multisample, max_version),
					m_pListener{ listener },
					m_cPlatformFontReleaseListener{ this },
					m_cProgramReleaseListener{ this },
					m_cFramebufferReleaseListener{ this },
					m_cVertexArrayReleaseListener{ this },
					m_cTextureReleaseListener{ this },
					m_cTextureMultisampleReleaseListener{ this },
					m_pDefaultVertexArray{ nullptr },
					m_pActiveProgramBase{ nullptr },
					m_pActiveProgramMini{ nullptr },
					m_pProgramMain{ nullptr },
					m_bUseDebugContext{ use_debug_context },
					m_bDebugEnabled{ use_debug_context },
					m_bDrawAllowed{ false }
				{
					m_sMinVersion = MIN_OPENGL_VERSION;
				}

				void CRenderer::CleanUp()
				{
					// Platform fonts
					while (m_aFonts.size() > 0)
						m_aFonts[m_aFonts.size() - 1]->Release(true);
					// Textures
					while (m_aTextures.size() > 0)
						m_aTextures[m_aTextures.size() - 1]->Release(true);
					// Image textures
					while (m_aImageTextures.size() > 0)
						m_aImageTextures[m_aImageTextures.size() - 1].Texture->Release(true);
					if (m_aMasks.size() > 0)
					{
						m_aMasks.clear();
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_MASKS_NOT_REMOVED);
					}
					// Multi-sample textures
					while (m_aTextureMultisamples.size() > 0)
						m_aTextureMultisamples[m_aTextureMultisamples.size() - 1]->Release(true);
					// Programs
					while (m_aPrograms.size() > 0)
						m_aPrograms[m_aPrograms.size() - 1]->Release(true);
					if (m_pProgramMain)
						m_pProgramMain->Release();
					// Vertex arrays
					while (m_aVertexArrays.size() > 0)
						m_aVertexArrays[m_aVertexArrays.size() - 1]->Release(true);
					if (m_pDefaultVertexArray)
						m_pDefaultVertexArray->Release();
					// Framebuffers
					while (m_aFramebuffers.size() > 0)
						m_aFramebuffers[m_aFramebuffers.size() - 1]->Release(true);
					if (m_pTextureFramebuffer)
						m_pTextureFramebuffer->Release();
					if (m_pDefaultFramebuffer)
						m_pDefaultFramebuffer->Release();
					// EGL context & surface
					if (*reinterpret_cast<EGLDisplay*>(&m_pApplication->m_hHandle))
					{
						if (*reinterpret_cast<EGLContext*>(&m_hContext))
						{
							eglMakeCurrent(*reinterpret_cast<EGLDisplay*>(&m_pApplication->m_hHandle), EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
							eglDestroyContext(*reinterpret_cast<EGLDisplay*>(&m_pApplication->m_hHandle), *reinterpret_cast<EGLContext*>(&m_hContext));
							*reinterpret_cast<EGLContext*>(&m_hContext) = nullptr;
						}
						if (*reinterpret_cast<EGLSurface*>(&m_hSurface))
						{
							eglDestroySurface(*reinterpret_cast<EGLDisplay*>(&m_pApplication->m_hHandle), *reinterpret_cast<EGLSurface*>(&m_hSurface));
							*reinterpret_cast<EGLSurface*>(&m_hSurface) = nullptr;
						}
						eglTerminate(*reinterpret_cast<EGLDisplay*>(&m_pApplication->m_hHandle));
					}
					// Graphics
					if (m_pGraphics)
					{
						m_pGraphics->Release();
						m_pGraphics = nullptr;
						m_pNativeGraphics = nullptr;
					}
					// Properties
					m_pWindow = nullptr;
					m_pActiveBlock = nullptr;
					m_pActiveBitmask = nullptr;
					m_pActiveTarget = nullptr;
					m_pActiveSplineLimits = nullptr;
					m_pActivePrimitiveMatrix = nullptr;
					m_bDrawAllowed = false;
					m_eInitializationStatus = InitializationStatus::NotInitialized;
				}

				bool CRenderer::Initialize()
				{
					// Check display assigned
					if (!(*reinterpret_cast<EGLDisplay*>(&m_pApplication->m_hHandle)))
					{
						m_eInitializationStatus = InitializationStatus::DeviceContext;
						m_pWindow = nullptr;
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_EGL_GET_DISPLAY);
						return false;
					}
					// Initialize NGL
					ngl::PlatformData pd{ *reinterpret_cast<EGLDisplay*>(&m_pApplication->m_hHandle), NativeApplication::getWindow() };
					if (!ngl::load(nullptr, &pd))
					{
						m_eInitializationStatus = InitializationStatus::LoadNativeGraphics;
						m_pWindow = nullptr;
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_NGL_INITIALIZE);
						return false;
					}
					// Initialize EGL
					if (eglInitialize(*reinterpret_cast<EGLDisplay*>(&m_pApplication->m_hHandle), nullptr, nullptr) == EGL_FALSE)
					{
						m_eInitializationStatus = InitializationStatus::InitNativeGraphics;
						m_pWindow = nullptr;
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_EGL_INITIALIZE);
						return false;
					}
					// Check OpenGL minimum requirements
					m_pGraphics = COpenGL::Create(m_pListener);
					if (!m_pGraphics)
					{
						m_eInitializationStatus = InitializationStatus::CreateNativeGraphics;
						m_pWindow = nullptr;
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_CREATE_OPENGL);
						return false;
					}
					m_sMaxVersion = m_pGraphics->Version;
					if (m_pGraphics->Version < MIN_OPENGL_VERSION)
					{
						m_eInitializationStatus = InitializationStatus::Version;
						m_pGraphics->Release();
						m_pGraphics = nullptr;
						m_pWindow = nullptr;
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_OPENGL_VERSION_TOO_LOW);
						return false;
					}
					// Choose pixel format
					EGLConfig config;
					if (!FindPixelFormat(*reinterpret_cast<PlatformHandle*>(&config), m_iMultisample))
					{
						m_eInitializationStatus = InitializationStatus::FindPixelFormat;
						m_pGraphics->Release();
						m_pGraphics = nullptr;
						m_pWindow = nullptr;
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_FIND_PIXEL_FORMAT);
						return false;
					}
					//  Get format
					EGLint format;
					if (eglGetConfigAttrib(*reinterpret_cast<EGLDisplay*>(&m_pApplication->m_hHandle), config, EGL_NATIVE_VISUAL_ID, &format) == EGL_FALSE)
					{
						m_eInitializationStatus = InitializationStatus::FindConfig;
						m_pGraphics->Release();
						m_pGraphics = nullptr;
						m_pWindow = nullptr;
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_EGL_GET_FORMAT);
						return false;
					}
					// Set format
					if (ANativeWindow_setBuffersGeometry(NativeApplication::getWindow(), 0, 0, format) != 0)
					{
						m_eInitializationStatus = InitializationStatus::SetPixelFormat;
						m_pGraphics->Release();
						m_pGraphics = nullptr;
						m_pWindow = nullptr;
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_EGL_SET_FORMAT);
						return false;
					}
					// Create surface
					const EGLint surface_attributes[]{
						EGL_RENDER_BUFFER, m_bDoubleBuffered ? EGL_BACK_BUFFER : EGL_SINGLE_BUFFER,
						EGL_NONE
					};
					if (!(*reinterpret_cast<EGLSurface*>(&m_hSurface) = eglCreateWindowSurface(*reinterpret_cast<EGLDisplay*>(&m_pApplication->m_hHandle), config, NativeApplication::getWindow(), surface_attributes)))
					{
						CleanUp();
						m_eInitializationStatus = InitializationStatus::CreateSurface;
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_EGL_CREATE_SURFACE);
						return false;
					}
					// Create context
					m_sVersion = Min(m_sRequestedVersion, m_sMaxVersion);
					const EGLint context_attribs[] = {
						EGL_CONTEXT_MAJOR_VERSION_KHR, m_sVersion.Major,
						EGL_CONTEXT_MINOR_VERSION_KHR, m_sVersion.Minor,
						EGL_CONTEXT_FLAGS_KHR, (m_sVersion >= Version2{ 3, 2 }) ? EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR : 0,
						EGL_NONE
					};
					if (!(*reinterpret_cast<EGLContext*>(&m_hContext) = eglCreateContext(*reinterpret_cast<EGLDisplay*>(&m_pApplication->m_hHandle), config, nullptr, context_attribs)))
					{
						CleanUp();
						m_eInitializationStatus = InitializationStatus::CreateContext;
						return false;
					}
					// Activate OpenGL context
					if (eglMakeCurrent(*reinterpret_cast<EGLDisplay*>(&m_pApplication->m_hHandle), *reinterpret_cast<EGLSurface*>(&m_hSurface), *reinterpret_cast<EGLSurface*>(&m_hSurface),
						*reinterpret_cast<EGLContext*>(&m_hContext)) == EGL_FALSE)
					{
						CleanUp();
						m_eInitializationStatus = InitializationStatus::ActivateContext;
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_ACTIVATE_CONTEXT);
						return false;
					}
					m_pNativeGraphics = m_pGraphics;

					m_pGraphics->GetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_sCapabilities.MaxActiveTextures);
					m_pGraphics->GetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &m_sCapabilities.MaxColorAttachments);
					m_pGraphics->GetIntegerv(GL_MAX_DRAW_BUFFERS, &m_sCapabilities.MaxDrawBuffers);
					m_pGraphics->GetIntegerv(GL_MAX_SAMPLES, &m_sCapabilities.MaxSamples);

				#ifdef GL_ES_VERSION_3_2
					if (m_sVersion >= Version2{ 3, 2 })
					{
						m_pGraphics->DebugMessageCallback(ngl::DebugCallback, nullptr);
						m_pGraphics->DebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
						if (m_bUseDebugContext)
						{
							m_pGraphics->Enable(GL_DEBUG_OUTPUT);
							m_pGraphics->Enable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
						}
					}
				#endif

					// Settings
					m_pGraphics->FrontFace(GL_CW);
					m_pGraphics->CullFace(GL_BACK);
					m_pGraphics->Enable(GL_CULL_FACE);
					m_pGraphics->Enable(GL_BLEND);
					m_pGraphics->Enable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
					m_pGraphics->Disable(GL_DEPTH_TEST);
					m_pGraphics->BlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);

					// Texture framebuffer
					if (!(m_pTextureFramebuffer = gles::CFramebuffer::Create(m_pGraphics, this)))
					{
						CleanUp();
						m_eInitializationStatus = InitializationStatus::DefaultTextureFramebuffer;
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_CREATE_TEXTURE_FRAMEBUFFER);
						return false;
					}

					// Vertex array
					if (!(m_pDefaultVertexArray = gles::CVertexArrayImmutable::Create(m_pGraphics, DEFAULT_VERTEX_FORMAT, MaxPolygonPoints)))
					{
						CleanUp();
						m_eInitializationStatus = InitializationStatus::DefaultVertexArray;
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_CREATE_DEFAULT_VERTEX_ARRAY);
						return false;
					}
					m_pDefaultVertexArray->RegisterReleaseListener(&m_cVertexArrayReleaseListener);

					// Gradient textures
					if (!(m_pGradientPositions = CreateTexture(0, 0, 1, TextureFormat::Depth, false)) || !(m_pGradientColors = CreateTexture(0, 0, 1, TextureFormat::RGBA, true)))
					{
						CleanUp();
						m_eInitializationStatus = InitializationStatus::DefaultTextures;
						return false;
					}

					// Shader program
					if (!CreateMainProgram())
					{
						CleanUp();
						m_eInitializationStatus = InitializationStatus::DefaultProgram;
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_CREATE_MAIN_PROGRAM);
						return false;
					}

					// Framebuffer
					if (!(m_pDefaultFramebuffer = gles::CFramebuffer::Create(m_pGraphics, this)))
					{
						CleanUp();
						m_eInitializationStatus = InitializationStatus::DefaultFramebuffer;
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_CREATE_DEFAULT_FRAMEBUFFER);
						return false;
					}
					m_pDefaultFramebuffer->RegisterReleaseListener(&m_cFramebufferReleaseListener);
					m_pFramebuffer = m_pDefaultFramebuffer;
					m_pGraphics->BindFramebuffer(GL_FRAMEBUFFER, 0);

					// Properties
					m_bDrawAllowed = true;
					m_eInitializationStatus = InitializationStatus::Initialized;

					return true;
				}

				bool CRenderer::CreateMainProgram()
				{
					COpenGLShader vs{ m_pGraphics, ShaderHeader + ShaderVertex, GL_VERTEX_SHADER };
					if (!vs.Compiled)
						return false;
					COpenGLShader fs{ m_pGraphics, ShaderHeader + ShaderFragmentMain + ShaderFragmentBlock + ShaderFragmentSpline + ShaderFragmentUtils, GL_FRAGMENT_SHADER };
					if (!fs.Compiled)
						return false;
					COpenGLProgram *program{ new COpenGLProgram(m_pGraphics) };
					program->AddShader(vs);
					program->AddShader(fs);
					if (program->Link())
					{
						if ((m_pProgramMain = gles::CProgramMain::Create(m_pGraphics, program)))
						{
							m_pProgramMain->RegisterReleaseListener(&m_cProgramReleaseListener);
							m_pActiveProgramBase = cast<gles::CProgramBase*>(m_pProgramMain);
							m_pGraphics->UniformMatrix4fv(m_pActiveProgramBase->m_sMatrices.Primitive, 1, GL_TRUE, Identity.Data);
							return true;
						}
					}
					else
						delete program;
					return false;
				}
			#pragma endregion

			#pragma region IRenderer helper getters
				IReleasableListener *CRenderer::getTextureReleaseListener()
				{
					return &m_cTextureReleaseListener;
				}

				IReleasableListener *CRenderer::getProgramReleaseListener()
				{
					return &m_cProgramReleaseListener;
				}

				IReleasableListener *CRenderer::getFramebufferReleaseListener()
				{
					return &m_cFramebufferReleaseListener;
				}

				IReleasableListener *CRenderer::getVertexArrayReleaseListener()
				{
					return &m_cVertexArrayReleaseListener;
				}

				IReleasableListener *CRenderer::getTextureMultisampleReleaseListener()
				{
					return &m_cTextureMultisampleReleaseListener;
				}
			#pragma endregion

			#pragma region IRenderer helper methods
				void CRenderer::AddTexture(ITexture *texture)
				{
					if (!texture)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_ADD_EMPTY_TEXTURE);
						return;
					}
					std::vector<ITexture*>::iterator p{ std::find(m_aTextures.begin(), m_aTextures.end(), texture) };
					if (p != m_aTextures.end())
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_ADD_TEXTURE_ALREADY_IN_LIST);
						return;
					}
					m_aTextures.push_back(texture);
					if (!texture->Filename.empty())
					{
						m_aFileTextures.push_back(texture);
						m_bFileTexturesSorted = false;
					}
				}

				void CRenderer::AddProgram(IProgram *program)
				{
					if (!program)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_ADD_EMPTY_PROGRAM);
						return;
					}
					std::vector<IProgram*>::iterator p{ std::find(m_aPrograms.begin(), m_aPrograms.end(), program) };
					if (p != m_aPrograms.end())
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_ADD_PROGRAM_ALREADY_IN_LIST);
						return;
					}
					m_aPrograms.push_back(program);
				}

				void CRenderer::AddFramebuffer(IFramebuffer *framebuffer)
				{
					if (!framebuffer)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_ADD_EMPTY_FRAMEBUFFER);
						return;
					}
					std::vector<IFramebuffer*>::iterator p{ std::find(m_aFramebuffers.begin(), m_aFramebuffers.end(), framebuffer) };
					if (p != m_aFramebuffers.end())
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_ADD_FRAMEBUFFER_ALREADY_IN_LIST);
						return;
					}
					m_aFramebuffers.push_back(framebuffer);
				}

				void CRenderer::AddVertexArray(IVertexArray *vertex_array)
				{
					if (!vertex_array)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_ADD_EMPTY_VERTEX_ARRAY);
						return;
					}
					std::vector<IVertexArray*>::iterator p{ std::find(m_aVertexArrays.begin(), m_aVertexArrays.end(), vertex_array) };
					if (p != m_aVertexArrays.end())
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_ADD_VERTEX_ARRAY_ALREADY_IN_LIST);
						return;
					}
					m_aVertexArrays.push_back(vertex_array);
				}

				void CRenderer::AddTextureMultisample(ITextureMultisample *texture)
				{
					if (!texture)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_ADD_EMPTY_TEXTURE_MULTISAMPLE);
						return;
					}
					std::vector<ITextureMultisample*>::iterator p{ std::find(m_aTextureMultisamples.begin(), m_aTextureMultisamples.end(), texture) };
					if (p != m_aTextureMultisamples.end())
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_ADD_TEXTURE_MULTISAMPLE_ALREADY_IN_LIST);
						return;
					}
					m_aTextureMultisamples.push_back(texture);
				}
			#pragma endregion

			#pragma region IRenderer setters
				bool CRenderer::setWindow(IWindow *value, const bool fast_switch, const bool force)
				{
					if (value == m_pWindow || (value && !value->isCreated()))
					{
						if (value && value != m_pWindow)
							m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_WINDOW_NOT_CREATED);
						return false;
					}
					CleanUp();
					m_pWindow = value;
					if (m_pWindow)
						return Initialize();
					return true;
				}

				void CRenderer::setDebugEnabled(const bool value)
				{
				#ifdef GL_ES_VERSION_3_2
					if (value != m_bDebugEnabled)
					{
						m_bDebugEnabled = value;
						if (m_bDebugEnabled)
						{
							m_pGraphics->Enable(GL_DEBUG_OUTPUT);
							m_pGraphics->Enable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
						}
						else
						{
							m_pGraphics->Disable(GL_DEBUG_OUTPUT);
							m_pGraphics->Disable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
						}
					}
				#endif
				}
			#pragma endregion

			#pragma region IRenderer active state setters
				IRenderer *CRenderer::ActivateProgram(IProgram *value)
				{
					if (value != m_pActiveProgram)
					{
						m_pActiveProgram = value;
						if (m_pActiveProgram)
						{
							m_pActiveProgramBase = cast<gles::CProgramBase*>(value);
							m_pActiveProgramMini = cast<gles::CProgramMini*>(value);
							m_pGraphics->UseProgram(*reinterpret_cast<const GLuint*>(&m_pActiveProgram->Handle));
							m_pActiveProgram->NotifyOnActivate();
						}
						else
						{
							m_pActiveProgramBase = cast<gles::CProgramBase*>(m_pProgramMain);
							m_pActiveProgramMini = nullptr;
							if (m_pProgramMain)
							{
								m_pGraphics->UseProgram(*reinterpret_cast<const GLuint*>(&m_pProgramMain->Handle));
								m_pProgramMain->NotifyOnActivate();
							}
						}
						if (m_pActiveProgramBase)
							m_pGraphics->UniformMatrix4fv(m_pActiveProgramBase->m_sMatrices.FormToGL, 1, GL_TRUE, m_sMatrixFormToGL.Data);
						m_bDrawAllowed = m_pActiveProgramBase && !m_pActiveVertexArray;
					}
					return this;
				}

				IRenderer *CRenderer::ActivateFramebuffer(IFramebuffer *value)
				{
					if (value != m_pActiveFramebuffer)
					{
						if (m_pActiveFramebuffer && m_pActiveTarget && m_pActiveFramebuffer->getColorAttachment(0) == m_pActiveTarget)
							m_pActiveFramebuffer->setColorAttachment(nullptr, 0, false);
						m_pActiveFramebuffer = value;
						m_pFramebuffer = m_pActiveFramebuffer ? m_pActiveFramebuffer : m_pDefaultFramebuffer;
						if (m_pActiveTarget && m_pFramebuffer)
						{
							if (!m_pFramebuffer->getColorAttachment(0))
								m_pFramebuffer->setColorAttachment(m_pActiveTarget, 0, false);
							m_pGraphics->BindFramebuffer(GL_FRAMEBUFFER, *reinterpret_cast<const GLuint*>(&m_pFramebuffer->Handle));
						}
					}
					return this;
				}

				IRenderer *CRenderer::ActivateVertexArray(IVertexArray *value)
				{
					if (value != m_pActiveVertexArray)
					{
						m_pActiveVertexArray = value;
						m_pGraphics->BindVertexArray(*reinterpret_cast<const GLuint*>(m_pActiveVertexArray ? (&m_pActiveVertexArray->Handle) : (&m_pDefaultVertexArray->m_hHandle)));
						m_bDrawAllowed = m_pActiveProgramBase && !m_pActiveVertexArray;
					}
					return this;
				}

				IRenderer *CRenderer::ActivateTarget(IBaseTexture *value)
				{
					if (value != m_pActiveTarget)
					{
						ITexture *t{ cast<ITexture*>(m_pActiveTarget) };
						if (t)
						{
							t->setMinFilter(m_eActiveTargetMinFilter);
							t->setMagFilter(m_eActiveTargetMagFilter);
						}
						m_pActiveTarget = value;
						if (m_pActiveTarget)
						{
							ITexture *t{ cast<ITexture*>(m_pActiveTarget) };
							if (t)
							{
								m_eActiveTargetMinFilter = t->MinFilter;
								m_eActiveTargetMagFilter = t->MagFilter;
								t->setMinFilter(TextureMinFilter::Nearest);
								t->setMagFilter(TextureMagFilter::Nearest);
							}
							m_pFramebuffer->setColorAttachment(m_pActiveTarget, 0, false);
							m_pGraphics->BindFramebuffer(GL_FRAMEBUFFER, *reinterpret_cast<const GLuint*>(&m_pFramebuffer->Handle));
							m_sViewport = m_pActiveTarget->Rect;
							m_pGraphics->Viewport(0, 0, m_sViewport.Right, m_sViewport.Bottom);
							ActivateTextureMatrix(m_pActiveTarget->Sizef);
							if (m_pActiveProgramBase && !m_pActiveMask)
								m_pGraphics->Uniform1i(m_pActiveProgramBase->m_sMask.SubroutineTest, m_pActiveProgramBase->m_sMask.None);
						}
						else
						{
							m_pFramebuffer->setColorAttachment(nullptr, 0, 0, false);
							m_pGraphics->BindFramebuffer(GL_FRAMEBUFFER, 0);
							m_sViewport = m_sViewportForm;
							int h{ m_sViewport.height() };
							m_pGraphics->Viewport(m_sViewport.Left, h - m_sViewport.Bottom, m_sViewport.width(), h);
							ActivateViewportMatrix();
							if (m_pActiveProgramBase && !m_pActiveMask && m_aMasks.size() > 0)
							{
								m_pGraphics->ActiveTexture(GL_TEXTURE3);
								m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_aMasks[m_aMasks.size() - 1].Texture->Handle));
								m_pGraphics->Uniform1i(m_pActiveProgramBase->m_sMask.SubroutineTest, m_pActiveProgramBase->m_sMask.Exists);
								m_pGraphics->Uniform2f(m_pActiveProgramBase->m_sMask.Size, m_aMasks[0].Texture->Widthf, m_aMasks[0].Texture->Heightf);
								m_pGraphics->UniformMatrix4fv(m_pActiveProgramBase->m_sMask.Matrix, 1, GL_TRUE, m_aMasks[0].MInv.Data);
							}
						}
					}
					return this;
				}

				IRenderer *CRenderer::ActivateMask(ITexture *value)
				{
					if (!m_pActiveProgramBase)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_MASK_WITH_CUSTOM_PROGRAM);
						return this;
					}
					if (value != m_pActiveMask)
					{
						m_pActiveMask = value;
						if (m_pActiveMask)
						{
							m_pGraphics->ActiveTexture(GL_TEXTURE3);
							m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_pActiveMask->Handle));
							m_pGraphics->Uniform1i(m_pActiveProgramBase->m_sMask.SubroutineTest, m_pActiveProgramBase->m_sMask.Exists);
							m_pGraphics->Uniform2f(m_pActiveProgramBase->m_sMask.Size, m_pActiveMask->Widthf, m_pActiveMask->Heightf);
							m_pGraphics->UniformMatrix4fv(m_pActiveProgramBase->m_sMask.Matrix, 1, GL_TRUE, Identity.Data);
						}
						else if (!m_pActiveTarget && m_aMasks.size() > 0)
						{
							m_pGraphics->ActiveTexture(GL_TEXTURE3);
							m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_aMasks[m_aMasks.size() - 1].Texture->Handle));
							m_pGraphics->Uniform1i(m_pActiveProgramBase->m_sMask.SubroutineTest, m_pActiveProgramBase->m_sMask.Exists);
							m_pGraphics->Uniform2f(m_pActiveProgramBase->m_sMask.Size, m_aMasks[0].Texture->Widthf, m_aMasks[0].Texture->Heightf);
							m_pGraphics->UniformMatrix4fv(m_pActiveProgramBase->m_sMask.Matrix, 1, GL_TRUE, m_aMasks[0].MInv.Data);
						}
						else
						{
							m_pGraphics->Uniform1i(m_pActiveProgramBase->m_sMask.SubroutineTest, m_pActiveProgramBase->m_sMask.None);
						}
					}
					return this;
				}

				IRenderer *CRenderer::ActivateBlock(const nitisa::Block *value)
				{
					if (!m_pActiveProgramBase)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_BLOCK_WITH_CUSTOM_PROGRAM);
						return this;
					}
					if (value || m_pActiveBlock)
					{
						if (value)
						{
							m_sActiveBlock = *value;
							m_pActiveBlock = &m_sActiveBlock;
							SetBlockData(m_sActiveBlock.Rect, m_sActiveBlock.Border, m_sActiveBlock.Radius, 0);
							m_pGraphics->Uniform1i(m_pActiveProgramBase->m_sBlock.SubroutineTest, m_pActiveProgramBase->m_sBlock.Exists);
							m_pGraphics->Uniform1i(m_pActiveProgramBase->m_sBlock.PointLocation, (int)m_sActiveBlock.Location);
						}
						else
						{
							m_pActiveBlock = nullptr;
							m_pGraphics->Uniform1i(m_pActiveProgramBase->m_sBlock.SubroutineTest, m_pActiveProgramBase->m_sBlock.None);
						}
					}
					return this;
				}

				IRenderer *CRenderer::ActivateBlock(const nitisa::Block &value)
				{
					return ActivateBlock(&value);
				}

				IRenderer *CRenderer::ActivateBitmask(const Bitmask *value)
				{
					if (!m_pActiveProgramBase)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_BITMASK_WITH_CUSTOM_PROGRAM);
						return this;
					}
					if (value || m_pActiveBitmask)
					{
						if (value)
						{
							m_sActiveBitmask = *value;
							m_pActiveBitmask = &m_sActiveBitmask;
							m_pGraphics->Uniform1ui(m_pProgramMain->m_sBitmask.X, m_sActiveBitmask.X);
							if (m_sActiveBitmask.is1D)
							{
								m_pGraphics->Uniform1i(m_pActiveProgramBase->m_sBitmask.SubroutineBitmask, m_pActiveProgramBase->m_sBitmask.Bitmask_1D);
							}
							else
							{
								if (m_sActiveBitmask.useFormCoords)
									m_pGraphics->Uniform1i(m_pActiveProgramBase->m_sBitmask.SubroutineBitmask, m_pActiveProgramBase->m_sBitmask.Bitmask_Form);
								else
									m_pGraphics->Uniform1i(m_pActiveProgramBase->m_sBitmask.SubroutineBitmask, m_pActiveProgramBase->m_sBitmask.Bitmask_2D);
								m_pGraphics->Uniform1ui(m_pProgramMain->m_sBitmask.Y, m_sActiveBitmask.Y);
							}
						}
						else
						{
							m_pActiveBitmask = nullptr;
							m_pGraphics->Uniform1i(m_pActiveProgramBase->m_sBitmask.SubroutineBitmask, m_pActiveProgramBase->m_sBitmask.Bitmask_None);
						}
					}
					return this;
				}

				IRenderer *CRenderer::ActivateBitmask(const Bitmask &value)
				{
					return ActivateBitmask(&value);
				}

				IRenderer *CRenderer::ActivateSplineLimits(const CubicBezierSplineLimits *value)
				{
					if (!m_pActiveProgramBase)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_SPLINE_LIMITS_WITH_CUSTOM_PROGRAM);
						return this;
					}
					if (value || m_pActiveSplineLimits)
					{
						if (value)
						{
							float a[4], b[4], spline_a[4], spline_b[4];
							if (value->isY)
							{
								a[0] = value->Spline1.P2.X - value->Spline1.P1.X + 3 * (value->Spline1.C1.X - value->Spline1.C2.X);
								a[1] = 3 * (value->Spline1.P1.X - 2 * value->Spline1.C1.X + value->Spline1.C2.X);
								a[2] = 3 * (value->Spline1.C1.X - value->Spline1.P1.X);
								a[3] = value->Spline1.P1.X;

								b[0] = value->Spline2.P2.X - value->Spline2.P1.X + 3 * (value->Spline2.C1.X - value->Spline2.C2.X);
								b[1] = 3 * (value->Spline2.P1.X - 2 * value->Spline2.C1.X + value->Spline2.C2.X);
								b[2] = 3 * (value->Spline2.C1.X - value->Spline2.P1.X);
								b[3] = value->Spline2.P1.X;

								spline_a[0] = value->Spline1.P1.Y;
								spline_a[1] = value->Spline1.C1.Y;
								spline_a[2] = value->Spline1.C2.Y;
								spline_a[3] = value->Spline1.P2.Y;

								spline_b[0] = value->Spline2.P1.Y;
								spline_b[1] = value->Spline2.C1.Y;
								spline_b[2] = value->Spline2.C2.Y;
								spline_b[3] = value->Spline2.P2.Y;
							}
							else
							{
								a[0] = value->Spline1.P2.Y - value->Spline1.P1.Y + 3 * (value->Spline1.C1.Y - value->Spline1.C2.Y);
								a[1] = 3 * (value->Spline1.P1.Y - 2 * value->Spline1.C1.Y + value->Spline1.C2.Y);
								a[2] = 3 * (value->Spline1.C1.Y - value->Spline1.P1.Y);
								a[3] = value->Spline1.P1.Y;

								b[0] = value->Spline2.P2.Y - value->Spline2.P1.Y + 3 * (value->Spline2.C1.Y - value->Spline2.C2.Y);
								b[1] = 3 * (value->Spline2.P1.Y - 2 * value->Spline2.C1.Y + value->Spline2.C2.Y);
								b[2] = 3 * (value->Spline2.C1.Y - value->Spline2.P1.Y);
								b[3] = value->Spline2.P1.Y;

								spline_a[0] = value->Spline1.P1.X;
								spline_a[1] = value->Spline1.C1.X;
								spline_a[2] = value->Spline1.C2.X;
								spline_a[3] = value->Spline1.P2.X;

								spline_b[0] = value->Spline2.P1.X;
								spline_b[1] = value->Spline2.C1.X;
								spline_b[2] = value->Spline2.C2.X;
								spline_b[3] = value->Spline2.P2.X;
							}
							if ((ntl::IsNotZero<float>(a[0], ntl::Tolerance<float>) || ntl::IsNotZero<float>(a[1], ntl::Tolerance<float>) || ntl::IsNotZero<float>(a[2], ntl::Tolerance<float>)) ||
								(ntl::IsNotZero<float>(b[0], ntl::Tolerance<float>) || ntl::IsNotZero<float>(b[1], ntl::Tolerance<float>) || ntl::IsNotZero<float>(b[2], ntl::Tolerance<float>)))
							{
								m_sActiveSplineLimits = *value;
								m_pActiveSplineLimits = &m_sActiveSplineLimits;

								m_pGraphics->Uniform1fv(m_pActiveProgramBase->m_sSpline.A, 4, spline_a);
								m_pGraphics->Uniform1fv(m_pActiveProgramBase->m_sSpline.B, 4, spline_b);
								m_pGraphics->Uniform1fv(m_pActiveProgramBase->m_sSpline.AConsts, 4, a);
								m_pGraphics->Uniform1fv(m_pActiveProgramBase->m_sSpline.BConsts, 4, b);
								m_pGraphics->Uniform1i(m_pActiveProgramBase->m_sSpline.SubroutineSplineLimit, m_sActiveSplineLimits.isY ? m_pActiveProgramBase->m_sSpline.Y : m_pActiveProgramBase->m_sSpline.X);
							}
						}
						else
						{
							m_pActiveSplineLimits = nullptr;
							m_pGraphics->Uniform1i(m_pActiveProgramBase->m_sSpline.SubroutineSplineLimit, m_pActiveProgramBase->m_sSpline.None);
						}
					}
					return this;
				}

				IRenderer *CRenderer::ActivateSplineLimits(const CubicBezierSplineLimits &value)
				{
					return ActivateSplineLimits(&value);
				}

				IRenderer *CRenderer::ActivatePrimitiveMatrix(const Mat4f *value)
				{
					if (!m_pActiveProgramBase)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_PRIMITIVE_MATRIX_WITH_CUSTOM_PROGRAM);
						return this;
					}
					if (value || m_pActivePrimitiveMatrix)
					{
						if (value)
						{
							m_sActivePrimitiveMatrix = *value;
							m_pActivePrimitiveMatrix = &m_sActivePrimitiveMatrix;
						}
						else
						{
							ntl::Identity<float>(m_sActivePrimitiveMatrix);
							m_pActivePrimitiveMatrix = nullptr;
						}
						m_pGraphics->UniformMatrix4fv(m_pActiveProgramBase->m_sMatrices.Primitive, 1, GL_TRUE, m_sActivePrimitiveMatrix.Data);
					}
					return this;
				}

				IRenderer *CRenderer::ActivatePrimitiveMatrix(const Mat4f &value)
				{
					if (!m_pActiveProgramBase)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_PRIMITIVE_MATRIX_WITH_CUSTOM_PROGRAM);
						return this;
					}
					m_sActivePrimitiveMatrix = value;
					m_pActivePrimitiveMatrix = &m_sActivePrimitiveMatrix;
					m_pGraphics->UniformMatrix4fv(m_pActiveProgramBase->m_sMatrices.Primitive, 1, GL_TRUE, m_sActivePrimitiveMatrix.Data);
					return this;
				}
			#pragma endregion

			#pragma region IRenderer platform fonts
				IPlatformFont *CRenderer::CreatePlatformFont(const String &fontname, const int height, const FontWeight weight, const bool italic, const bool underline, const bool strikeout, const bool monospace)
				{
					SortFonts();
					FontWeight w{ (weight >= FontWeight::Bold) ? FontWeight::Bold : FontWeight::Normal };
					*const_cast<String*>(&m_cSearchPlatformFont.FontName) = fontname;
					*const_cast<int*>(&m_cSearchPlatformFont.Height) = height;
					*const_cast<FontWeight*>(&m_cSearchPlatformFont.Weight) = w;
					*const_cast<bool*>(&m_cSearchPlatformFont.Italic) = italic;
					*const_cast<bool*>(&m_cSearchPlatformFont.Underline) = underline;
					*const_cast<bool*>(&m_cSearchPlatformFont.StrikeOut) = strikeout;
					*const_cast<bool*>(&m_cSearchPlatformFont.Monospace) = monospace;
					std::vector<IPlatformFont*>::iterator p{ std::lower_bound(m_aFonts.begin(), m_aFonts.end(), &m_cSearchPlatformFont, CompareFonts) };
					if (p != m_aFonts.end() &&
						(*p)->FontName == fontname &&
						(*p)->Height == height &&
						(*p)->Weight == weight &&
						(*p)->Italic == italic &&
						(*p)->Underline == underline &&
						(*p)->StrikeOut == strikeout &&
						(*p)->Monospace == monospace)
					{
						(*p)->AddRef();
						return *p;
					}
					String filename{ fontname };
					CApplication::FONT_FACE *font_face{ m_pApplication->LoadFontFace(filename) };
					if (!font_face)
					{
						if (w == FontWeight::Bold)
							if (italic)
								filename = L"BoldItalic";
							else
								filename = L"Bold";
						else
							if (italic)
								filename = L"Italic";
							else
								filename = L"Regular";
						font_face = m_pApplication->LoadDefaultFontFace(filename);
					}
					if (!font_face)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_CREATE_FONT);
						return nullptr;
					}
					CPlatformFont *f{ new CPlatformFont(this) };
					f->RegisterReleaseListener(&m_cPlatformFontReleaseListener);
					*reinterpret_cast<CApplication::FONT_FACE**>(&f->m_hHandle) = font_face;
					f->m_sFontName = fontname;
					f->m_iHeight = height;
					f->m_eWeight = w;
					f->m_bItalic = italic;
					f->m_bUnderline = underline;
					f->m_bStrikeOut = strikeout;
					f->m_bMonospace = monospace;
					if (monospace)
					{
						PointF s{ f->getStringSize(L"QWERTYO", 0) };
						f->m_sCharacterSize = PointF{ 1.1f * s.X / 7.0f, s.Y };
					}
					m_aFonts.push_back(f);
					m_bFontsSorted = false;
					return f;
				}
			#pragma endregion

			#pragma region IRenderer programs
				IProgram *CRenderer::CreateProgram(const AnsiString &vertex, const AnsiString &fragment, const Bindings &bindings)
				{
					COpenGLShader vs{ m_pGraphics, vertex, GL_VERTEX_SHADER };
					if (!vs.Compiled)
						return nullptr;
					COpenGLShader fs{ m_pGraphics, fragment, GL_FRAGMENT_SHADER };
					if (!fs.Compiled)
						return nullptr;
					COpenGLProgram *program{ new COpenGLProgram(m_pGraphics) };
					program->AddShader(vs);
					program->AddShader(fs);
					for (auto b : bindings)
						m_pGraphics->BindAttribLocation(program->Id, b.first, b.second.c_str());
					if (program->Link())
					{
						gles::CProgram *result{ new gles::CProgram(m_pGraphics, program) };
						result->RegisterReleaseListener(&m_cProgramReleaseListener);
						m_aPrograms.push_back(result);
						if (m_pActiveProgram)
						{
							m_pGraphics->UseProgram(*reinterpret_cast<const GLuint*>(&m_pActiveProgram->Handle));
							m_pActiveProgram->NotifyOnActivate();
						}
						else
						{
							m_pGraphics->UseProgram(*reinterpret_cast<const GLuint*>(&m_pProgramMain->Handle));
							m_pProgramMain->NotifyOnActivate();
						}
						return result;
					}
					delete program;
					m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_LINK_CUSTOM_PROGRAM);
					return nullptr;
				}

				IProgram *CRenderer::CreateProgram(const AnsiString &fragment)
				{
					COpenGLShader vs{ m_pGraphics, ShaderHeader + ShaderVertex, GL_VERTEX_SHADER };
					if (!vs.Compiled)
						return nullptr;
					COpenGLShader fs{ m_pGraphics, ShaderHeader + ShaderFragmentMini + ShaderFragmentBlock + ShaderFragmentUtils + fragment, GL_FRAGMENT_SHADER };
					if (!fs.Compiled)
						return nullptr;
					COpenGLProgram *program{ new COpenGLProgram(m_pGraphics) };
					program->AddShader(vs);
					program->AddShader(fs);
					if (program->Link())
					{
						IProgram *result{ gles::CProgramMini::Create(m_pGraphics, program) };
						if (result)
						{
							result->RegisterReleaseListener(&m_cProgramReleaseListener);
							m_aPrograms.push_back(result);
							if (m_pActiveProgram)
							{
								m_pGraphics->UseProgram(*reinterpret_cast<const GLuint*>(&m_pActiveProgram->Handle));
								m_pActiveProgram->NotifyOnActivate();
							}
							else
							{
								m_pGraphics->UseProgram(*reinterpret_cast<const GLuint*>(&m_pProgramMain->Handle));
								m_pProgramMain->NotifyOnActivate();
							}
							return result;
						}
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_MISSING_UNIFORMS_IN_MINI);
					}
					else
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_LINK_MINI_PROGRAM);
					}
					delete program;
					return nullptr;
				}

				IProgram *CRenderer::CreateProgram(const Shaders &shaders, const Bindings &bindings)
				{
					std::vector<COpenGLShader*> gl_shaders;
					for (auto &info : shaders)
					{
						gl_shaders.push_back(new COpenGLShader(m_pGraphics, info.second, SHADER_TYPES[(int)info.first]));
						if (!gl_shaders[gl_shaders.size() - 1]->Compiled)
						{
							for (auto gl_shader : gl_shaders)
								delete gl_shader;
							return nullptr;
						}
					}
					COpenGLProgram *program{ new COpenGLProgram(m_pGraphics) };
					for (auto gl_shader : gl_shaders)
						program->AddShader(*gl_shader);
					for (auto b : bindings)
						m_pGraphics->BindAttribLocation(program->Id, b.first, b.second.c_str());
					if (program->Link())
					{
						gles::CProgram *result{ new gles::CProgram(m_pGraphics, program) };
						result->RegisterReleaseListener(&m_cProgramReleaseListener);
						m_aPrograms.push_back(result);
						if (m_pActiveProgram)
						{
							m_pGraphics->UseProgram(*reinterpret_cast<const GLuint*>(&m_pActiveProgram->Handle));
							m_pActiveProgram->NotifyOnActivate();
						}
						else
						{
							m_pGraphics->UseProgram(*reinterpret_cast<const GLuint*>(&m_pProgramMain->Handle));
							m_pProgramMain->NotifyOnActivate();
						}
						return result;
					}
					for (auto gl_shader : gl_shaders)
						delete gl_shader;
					delete program;
					m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_LINK_CUSTOM_PROGRAM);
					return nullptr;
				}
			#pragma endregion

			#pragma region IRenderer framebuffers
				IFramebuffer *CRenderer::CreateFramebuffer()
				{
					gles::CFramebuffer *result{ gles::CFramebuffer::Create(m_pGraphics, this) };
					if (result)
					{
						result->RegisterReleaseListener(&m_cFramebufferReleaseListener);
						m_aFramebuffers.push_back(result);
						return result;
					}
					m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_CREATE_FRAMEBUFFER);
					return nullptr;
				}
			#pragma endregion

			#pragma region IRenderer vertex arrays
				IVertexArray *CRenderer::CreateVertexArray(const VertexFormat &format)
				{
					IVertexArray *result{ gles::CVertexArrayDynamic::Create(m_pGraphics, format) };
					if (result)
					{
						result->RegisterReleaseListener(&m_cVertexArrayReleaseListener);
						m_aVertexArrays.push_back(result);
						return result;
					}
					m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_CREATE_VERTEX_ARRAY);
					return nullptr;
				}

				IVertexArray *CRenderer::CreateVertexArray(const VertexFormat &format, const size_t vertex_count, const bool immutable)
				{
					IVertexArray *result;
					if (immutable)
						result = gles::CVertexArrayImmutable::Create(m_pGraphics, format, vertex_count);
					else
						result = gles::CVertexArrayDynamic::Create(m_pGraphics, format, vertex_count);
					if (result)
					{
						result->RegisterReleaseListener(&m_cVertexArrayReleaseListener);
						m_aVertexArrays.push_back(result);
						return result;
					}
					m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_CREATE_VERTEX_ARRAY);
					return nullptr;
				}

				IVertexArray *CRenderer::CreateVertexArray(const VertexFormat &format, const size_t polygon_count, const size_t polygon_size, const bool immutable)
				{
					IVertexArray *result;
					if (immutable)
						result = gles::CVertexArrayImmutable::Create(m_pGraphics, format, polygon_count, polygon_size);
					else
						result = gles::CVertexArrayDynamic::Create(m_pGraphics, format, polygon_count, polygon_size);
					if (result)
					{
						result->RegisterReleaseListener(&m_cVertexArrayReleaseListener);
						m_aVertexArrays.push_back(result);
						return result;
					}
					m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_CREATE_VERTEX_ARRAY);
					return nullptr;
				}
			#pragma endregion

			#pragma region IRenderer textures
				ITexture *CRenderer::CreateTexture(const int width, const int height, const int level_count, const TextureFormat format, const bool precomputed)
				{
					if (width < 0 || height < 0 || level_count < 0)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_INVALID_TEXTURE_PARAMS);
						return nullptr;
					}
					gles::CTexture *t{ new gles::CTexture(m_pGraphics, this, precomputed) };
					t->RegisterReleaseListener(&m_cTextureReleaseListener);
					t->m_pFramebuffer = m_pTextureFramebuffer;
					t->m_eFormat = format;
					t->m_eMinFilter = TextureMinFilter::Linear;
					t->m_eMagFilter = TextureMagFilter::Linear;
					t->m_eWrapS = TextureWrap::Repeat;
					t->m_eWrapT = TextureWrap::Repeat;
					t->m_eWrapR = TextureWrap::Repeat;
					t->m_iRequiredLevelCount = level_count;
					if (width > 0 && height > 0 && !t->setSize(width, height))
					{
						t->Release();
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RESIZE_TEXTURE);
						return nullptr;
					}
					m_aTextures.push_back(t);
					return t;
				}

				ITexture *CRenderer::CreateTextureFromImage(const nitisa::Image &data, const int level_count, const TextureFormat format, const bool precomputed)
				{
					if (data.Width == 0 || data.Height == 0 || level_count < 0)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_INVALID_TEXTURE_PARAMS);
						return nullptr;
					}
					SortImageTextures();
					m_sSearchImageTexture.Data = &data;
					*const_cast<int*>(&m_cSearchTexture.RequiredLevelCount) = level_count;
					*const_cast<TextureFormat*>(&m_cSearchTexture.Format) = format;
					*const_cast<bool*>(&m_cSearchTexture.Precomputed) = precomputed;
					std::vector<IMAGE_TEXTURE>::iterator p{ std::lower_bound(m_aImageTextures.begin(), m_aImageTextures.end(), m_sSearchImageTexture, CompareImageTextures) };
					if (p != m_aImageTextures.end() && p->Data == &data && p->Texture->RequiredLevelCount == level_count && p->Texture->Format == format && p->Texture->Precomputed == precomputed)
					{
						p->Texture->AddRef();
						return p->Texture;
					}
					gles::CTexture *result{ new gles::CTexture(m_pGraphics, this, precomputed) };
					result->RegisterReleaseListener(&m_cTextureReleaseListener);
					result->m_pFramebuffer = m_pTextureFramebuffer;
					result->m_eFormat = format;
					result->m_eMinFilter = TextureMinFilter::Linear;
					result->m_eMagFilter = TextureMagFilter::Linear;
					result->m_eWrapS = TextureWrap::Repeat;
					result->m_eWrapT = TextureWrap::Repeat;
					result->m_eWrapR = TextureWrap::Repeat;
					result->m_iRequiredLevelCount = level_count;
					if (!result->setSize(data.Width, data.Height))
					{
						result->Release();
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RESIZE_TEXTURE);
						return nullptr;
					}
					ITexture::IData *d{ result->Lock(TextureFormat::RGBA, 0, false) };
					if (!d)
					{
						result->Release();
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_LOCK_TEXTURE_DATA);
						return nullptr;
					}
					for (int y = 0; y < result->Height; y++)
						for (int x = 0; x < result->Width; x++)
							d->setColor(x, y, data[x][y]);
					d->Release();
					if (result->m_iActualLevelCount > 1)
						m_pGraphics->GenerateMipmap(GL_TEXTURE_2D);
					m_aImageTextures.push_back(IMAGE_TEXTURE{ &data, result });
					m_bImageTexturesSorted = false;
					return result;
				}

				ITexture *CRenderer::CreateTextureFromFile(const String &filename, const int level_count, const TextureFormat format, const bool precomputed)
				{
					if (level_count < 0)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_INVALID_TEXTURE_PARAMS);
						return nullptr;
					}
					SortFileTextures();
					String file_name{ ToLower(filename) };
					*const_cast<String*>(&m_cSearchTexture.Filename) = file_name;
					*const_cast<int*>(&m_cSearchTexture.RequiredLevelCount) = level_count;
					*const_cast<TextureFormat*>(&m_cSearchTexture.Format) = format;
					*const_cast<bool*>(&m_cSearchTexture.Precomputed) = precomputed;
					std::vector<ITexture*>::iterator p{ std::lower_bound(m_aFileTextures.begin(), m_aFileTextures.end(), &m_cSearchTexture, CompareTextures) };
					if (p != m_aFileTextures.end() && (*p)->Filename == file_name && (*p)->RequiredLevelCount == level_count && (*p)->Format == format && (*p)->Precomputed == precomputed)
					{
						(*p)->AddRef();
						return *p;
					}
					nitisa::Image bmp{ Application->Picture->Load(filename) };
					if (bmp.Width == 0 || bmp.Height == 0)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_LOADED_PICTURE_EMPTY);
						return nullptr;
					}
					gles::CTexture *result{ new gles::CTexture(m_pGraphics, this, precomputed) };
					result->RegisterReleaseListener(&m_cTextureReleaseListener);
					result->m_pFramebuffer = m_pTextureFramebuffer;
					result->m_eFormat = format;
					result->m_eMinFilter = TextureMinFilter::Linear;
					result->m_eMagFilter = TextureMagFilter::Linear;
					result->m_eWrapS = TextureWrap::Repeat;
					result->m_eWrapT = TextureWrap::Repeat;
					result->m_eWrapR = TextureWrap::Repeat;
					result->m_iRequiredLevelCount = level_count;
					if (!result->setSize(bmp.Width, bmp.Height))
					{
						result->Release();
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RESIZE_TEXTURE);
						return nullptr;
					}
					ITexture::IData *d{ result->Lock(TextureFormat::RGBA, 0, false) };
					if (!d)
					{
						result->Release();
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_LOCK_TEXTURE_DATA);
						return nullptr;
					}
					for (int y = 0; y < result->Height; y++)
						for (int x = 0; x < result->Width; x++)
							d->setColor(x, y, bmp[x][y]);
					d->Release();
					result->m_sFilename = file_name;
					if (result->m_iActualLevelCount > 1)
						m_pGraphics->GenerateMipmap(GL_TEXTURE_2D);
					m_aTextures.push_back(result);
					m_aFileTextures.push_back(result);
					m_bFileTexturesSorted = false;
					return result;
				}

				ITextureMultisample *CRenderer::CreateTextureMultisample(const int width, const int height, const TextureFormat format, const int samples, const bool fixed_sample_locations)
				{
					if (width < 0 || height < 0 || samples < 1 || samples > m_sCapabilities.MaxSamples)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_INVALID_TEXTURE_MULTISAMPLE_PARAMS);
						return nullptr;
					}
					gles::CTextureMultisample *t{ new gles::CTextureMultisample(m_pGraphics, this, samples, fixed_sample_locations) };
					t->RegisterReleaseListener(&m_cTextureMultisampleReleaseListener);
					t->m_eFormat = format;
					if (width > 0 && height > 0 && !t->setSize(width, height))
					{
						t->Release();
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RESIZE_TEXTURE_MULTISAMPLE);
						return nullptr;
					}
					m_aTextureMultisamples.push_back(t);
					return t;
				}
			#pragma endregion

			#pragma region IRenderer helpers
				IRenderer *CRenderer::CreateInstance()
				{
					return new CRenderer(m_pListener, m_bDoubleBuffered, m_iMultisample, m_sRequestedVersion, m_bUseDebugContext);
				}

				IRenderer *CRenderer::RestoreState()
				{
					if (m_pWindow)
					{
						// Settings
						m_pGraphics->FrontFace(GL_CW);
						m_pGraphics->CullFace(GL_BACK);
						m_pGraphics->Enable(GL_CULL_FACE);
						m_pGraphics->Enable(GL_BLEND);
						m_pGraphics->Disable(GL_DEPTH_TEST);
						m_pGraphics->BlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);

						// Vertex array
						ActivateVertexArray(nullptr);

						// Gradient textures
						if (m_pGradientPositions->Width > 0)
						{
							m_pGraphics->ActiveTexture(GL_TEXTURE1);
							m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_pGradientPositions->Handle));
							m_pGraphics->ActiveTexture(GL_TEXTURE2);
							m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_pGradientColors->Handle));
						}

						// Program
						ActivateProgram(nullptr);
					}
					return this;
				}
			#pragma endregion

			#pragma region Masks
				bool CRenderer::PushMask(ITexture *mask, const Mat4f &matrix)
				{
					if (m_pActiveProgram || m_pActiveVertexArray || m_pActiveTarget || m_pActiveMask)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_PUSH_MASK_WITH_CUSTOM_PARAMS);
						return false;
					}
					mask->setWrapS(TextureWrap::ClampToBorder);
					mask->setWrapT(TextureWrap::ClampToBorder);
					Mat4f m_inv{ ntl::Inversed<float>(matrix) };
					if (m_aMasks.size() > 0)
					{
						ITexture *first{ m_aMasks[0].Texture }, *texture{ CreateTexture(first->Width, first->Height, 1, TextureFormat::RGBA, true) };
						if (!texture)
							return false;
						texture->setWrapS(TextureWrap::ClampToBorder);
						texture->setWrapT(TextureWrap::ClampToBorder);
						Mat4f m{ m_inv * m_aMasks[0].M }; // Matrix which transform mask into prev mask coordinate space
						CStoreState save{ this };
						ActivateTarget(texture);
						ActivateBlock(nullptr);
						ActivateBitmask(nullptr);
						ActivateSplineLimits(nullptr);
						ActivatePrimitiveMatrix(nullptr);
						PolygonSetRectangle(first->Rectf);
						m_pGraphics->ClearColor(0, 0, 0, 0);
						m_pGraphics->Clear(GL_COLOR_BUFFER_BIT);
						m_pGraphics->ActiveTexture(GL_TEXTURE0);
						m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&first->Handle));
						m_pGraphics->ActiveTexture(GL_TEXTURE3);
						m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&mask->Handle));
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Mask);
						m_pGraphics->Uniform2f(m_pActiveProgramBase->m_sMask.Size, mask->Widthf, mask->Heightf);
						m_pGraphics->UniformMatrix4fv(m_pActiveProgramBase->m_sMask.Matrix, 1, GL_TRUE, m.Data);
						m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
						m_aMasks.push_back(MASK{ texture });
					}
					else
						m_aMasks.push_back(MASK{ mask, m_inv, matrix });
					m_pGraphics->ActiveTexture(GL_TEXTURE3);
					m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_aMasks[m_aMasks.size() - 1].Texture->Handle));
					m_pGraphics->Uniform1i(m_pActiveProgramBase->m_sMask.SubroutineTest, m_pActiveProgramBase->m_sMask.Exists);
					m_pGraphics->Uniform2f(m_pActiveProgramBase->m_sMask.Size, m_aMasks[0].Texture->Widthf, m_aMasks[0].Texture->Heightf);
					m_pGraphics->UniformMatrix4fv(m_pActiveProgramBase->m_sMask.Matrix, 1, GL_TRUE, m_aMasks[0].MInv.Data);
					return true;
				}

				void CRenderer::PopMask()
				{
					if (m_aMasks.size() > 1) // Release current mask and activate prev one
					{
						ITexture *texture{ m_aMasks[m_aMasks.size() - 1].Texture };
						m_aMasks.pop_back();
						texture->Release();
						if (m_pActiveProgramBase && !m_pActiveTarget && !m_pActiveMask)
						{
							m_pGraphics->ActiveTexture(GL_TEXTURE3);
							m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_aMasks[m_aMasks.size() - 1].Texture->Handle));
						}
					}
					else if (m_aMasks.size() == 1) // Clear masks(first mask is owned by caller). Next drawing will set proper test mask subroutine via ActivateMask() and SetSubroutine()
					{
						m_aMasks.clear();
						if (m_pActiveProgramBase && !m_pActiveMask)
							m_pGraphics->Uniform1i(m_pActiveProgramBase->m_sMask.SubroutineTest, m_pActiveProgramBase->m_sMask.None);
					}
					else
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_NO_MASK_TO_POP);
					}
				}
			#pragma endregion

			#pragma region Helpers
				void CRenderer::ActivateViewportMatrix()
				{
					m_sMatrixFormToGL =
						ntl::Mat4Scale<float>(1, -1, 1) * // Invert y direction
						ntl::Mat4Translate<float>(-1, -1, 0) * // Transform coordinates to range -1..1
						ntl::Mat4Scale<float>(2.0f / m_sViewport.width(), 2.0f / m_sViewport.height(), 1) * // Transform coordinates to range 0..2
						ntl::Mat4Translate<float>(float(-m_sViewport.Left), float(-m_sViewport.Top), 0); // Transform window coordinates to viewport ones
					if (m_pActiveProgramBase)
						m_pGraphics->UniformMatrix4fv(m_pActiveProgramBase->m_sMatrices.FormToGL, 1, GL_TRUE, m_sMatrixFormToGL.Data);
				}

				void CRenderer::ActivateTextureMatrix(const PointF &size)
				{
					m_sMatrixFormToGL =
						ntl::Mat4Scale<float>(1, -1, 1) * // Invert y direction
						ntl::Mat4Translate<float>(-1, -1, 0) * // Transform coordinates to range -1..1
						ntl::Mat4Scale<float>(2.0f / size.X, 2.0f / size.Y, 1); // Transform coordinates to range 0..2
					if (m_pActiveProgramBase)
						m_pGraphics->UniformMatrix4fv(m_pActiveProgramBase->m_sMatrices.FormToGL, 1, GL_TRUE, m_sMatrixFormToGL.Data);
				}

				void CRenderer::PolygonSetLine(const PointF &p1, const PointF &p2, const Color &c1, const Color &c2)
				{
					m_pDefaultVertexArray->m_aVec3f[IDX_P][0].X = p1.X;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][0].Y = p1.Y;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[3] = c1.A / 255.0f;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[0] = c1.R / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[1] = c1.G / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[2] = c1.B / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[3];

					m_pDefaultVertexArray->m_aVec3f[IDX_P][1].X = p2.X;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][1].Y = p2.Y;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[3] = c2.A / 255.0f;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[0] = c2.R / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[1] = c2.G / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[2] = c2.B / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[3];

					if (m_pActiveBitmask)
					{
						m_pDefaultVertexArray->m_aVec2f[IDX_B][0].X = 0;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][1].X = std::sqrt((p2.X - p1.X) * (p2.X - p1.X) + (p2.Y - p1.Y) * (p2.Y - p1.Y));
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_B]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * 2, m_pDefaultVertexArray->m_aVec2f[IDX_B].data());
					}

					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec3fIDs[IDX_P]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec3f) * 2, m_pDefaultVertexArray->m_aVec3f[IDX_P].data());
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec4fIDs[IDX_C]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec4f) * 2, m_pDefaultVertexArray->m_aVec4f[IDX_C].data());
				}

				void CRenderer::PolygonSetLines(const std::vector<PointF> &points, const Color &color, const size_t offset, const size_t count)
				{
					float d{ 0 };
					for (size_t i = 0; i < count; i++)
					{
						m_pDefaultVertexArray->m_aVec3f[IDX_P][i].X = points[offset + i].X;
						m_pDefaultVertexArray->m_aVec3f[IDX_P][i].Y = points[offset + i].Y;
						m_pDefaultVertexArray->m_aVec4f[IDX_C][i].Data[3] = color.A / 255.0f;
						m_pDefaultVertexArray->m_aVec4f[IDX_C][i].Data[0] = color.R / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][i].Data[3];
						m_pDefaultVertexArray->m_aVec4f[IDX_C][i].Data[1] = color.G / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][i].Data[3];
						m_pDefaultVertexArray->m_aVec4f[IDX_C][i].Data[2] = color.B / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][i].Data[3];
						if (m_pActiveBitmask)
						{
							if (i == 0)
								m_pDefaultVertexArray->m_aVec2f[IDX_B][i].X = 0;
							else
							{
								d += ntl::Distance<float>(m_pDefaultVertexArray->m_aVec3f[IDX_P][i], m_pDefaultVertexArray->m_aVec3f[IDX_P][i - 1]);
								m_pDefaultVertexArray->m_aVec2f[IDX_B][i].X = d;
							}
						}
					}
					if (m_pActiveBitmask)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_B]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * count, m_pDefaultVertexArray->m_aVec2f[IDX_B].data());
					}
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec3fIDs[IDX_P]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec3f) * count, m_pDefaultVertexArray->m_aVec3f[IDX_P].data());
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec4fIDs[IDX_C]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec4f) * count, m_pDefaultVertexArray->m_aVec4f[IDX_C].data());
				}

				void CRenderer::PolygonSetTriangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &c1, const Color &c2, const Color &c3)
				{
					m_pDefaultVertexArray->m_aVec3f[IDX_P][0].X = p1.X;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][0].Y = p1.Y;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[3] = c1.A / 255.0f;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[0] = c1.R / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[1] = c1.G / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[2] = c1.B / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[3];

					m_pDefaultVertexArray->m_aVec3f[IDX_P][1].X = p2.X;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][1].Y = p2.Y;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[3] = c2.A / 255.0f;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[0] = c2.R / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[1] = c2.G / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[2] = c2.B / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[3];

					m_pDefaultVertexArray->m_aVec3f[IDX_P][2].X = p3.X;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][2].Y = p3.Y;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][2].Data[3] = c3.A / 255.0f;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][2].Data[0] = c3.R / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][2].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][2].Data[1] = c3.G / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][2].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][2].Data[2] = c3.B / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][2].Data[3];

					if (m_pActiveBitmask)
					{
						float x{ ntl::Min<float>(p1.X, p2.X, p3.X) }, y{ ntl::Min<float>(p1.Y, p2.Y, p3.Y) };
						m_pDefaultVertexArray->m_aVec2f[IDX_B][0].X = p1.X - x;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][0].Y = p1.Y - y;

						m_pDefaultVertexArray->m_aVec2f[IDX_B][1].X = p2.X - x;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][1].Y = p2.Y - y;

						m_pDefaultVertexArray->m_aVec2f[IDX_B][2].X = p3.X - x;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][2].Y = p3.Y - y;

						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_B]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * 3, m_pDefaultVertexArray->m_aVec2f[IDX_B].data());
					}
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec3fIDs[IDX_P]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec3f) * 3, m_pDefaultVertexArray->m_aVec3f[IDX_P].data());
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec4fIDs[IDX_C]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec4f) * 3, m_pDefaultVertexArray->m_aVec4f[IDX_C].data());
				}

				void CRenderer::PolygonSetRectangle(const RectF &rect, const Color &c1, const Color &c2, const Color &c3, const Color &c4)
				{
					m_pDefaultVertexArray->m_aVec3f[IDX_P][0].X = rect.Left;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][0].Y = rect.Top;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[3] = c1.A / 255.0f;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[0] = c1.R / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[1] = c1.G / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[2] = c1.B / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][0].Data[3];
					m_pDefaultVertexArray->m_aVec2f[IDX_T][0].X = 0;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][0].Y = 1;

					m_pDefaultVertexArray->m_aVec3f[IDX_P][1].X = rect.Right;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][1].Y = rect.Top;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[3] = c2.A / 255.0f;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[0] = c2.R / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[1] = c2.G / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[2] = c2.B / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][1].Data[3];
					m_pDefaultVertexArray->m_aVec2f[IDX_T][1].X = 1;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][1].Y = 1;

					m_pDefaultVertexArray->m_aVec3f[IDX_P][2].X = rect.Right;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][2].Y = rect.Bottom;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][2].Data[3] = c3.A / 255.0f;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][2].Data[0] = c3.R / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][2].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][2].Data[1] = c3.G / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][2].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][2].Data[2] = c3.B / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][2].Data[3];
					m_pDefaultVertexArray->m_aVec2f[IDX_T][2].X = 1;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][2].Y = 0;

					m_pDefaultVertexArray->m_aVec3f[IDX_P][3].X = rect.Left;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][3].Y = rect.Bottom;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][3].Data[3] = c4.A / 255.0f;
					m_pDefaultVertexArray->m_aVec4f[IDX_C][3].Data[0] = c4.R / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][3].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][3].Data[1] = c4.G / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][3].Data[3];
					m_pDefaultVertexArray->m_aVec4f[IDX_C][3].Data[2] = c4.B / 255.0f * m_pDefaultVertexArray->m_aVec4f[IDX_C][3].Data[3];
					m_pDefaultVertexArray->m_aVec2f[IDX_T][3].X = 0;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][3].Y = 0;

					if (m_pActiveBitmask)
					{
						m_pDefaultVertexArray->m_aVec2f[IDX_B][0].X = 0;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][0].Y = 0;

						m_pDefaultVertexArray->m_aVec2f[IDX_B][1].X = rect.width();
						m_pDefaultVertexArray->m_aVec2f[IDX_B][1].Y = 0;

						m_pDefaultVertexArray->m_aVec2f[IDX_B][2].X = m_pDefaultVertexArray->m_aVec2f[IDX_B][1].X;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][2].Y = rect.height();

						m_pDefaultVertexArray->m_aVec2f[IDX_B][3].X = 0;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][3].Y = m_pDefaultVertexArray->m_aVec2f[IDX_B][2].Y;

						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_B]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * 4, m_pDefaultVertexArray->m_aVec2f[IDX_B].data());
					}
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_T]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * 4, m_pDefaultVertexArray->m_aVec2f[IDX_T].data());
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec3fIDs[IDX_P]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec3f) * 4, m_pDefaultVertexArray->m_aVec3f[IDX_P].data());
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec4fIDs[IDX_C]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec4f) * 4, m_pDefaultVertexArray->m_aVec4f[IDX_C].data());
				}

				void CRenderer::PolygonSetRectangle(const RectF &rect)
				{
					m_pDefaultVertexArray->m_aVec3f[IDX_P][0].X = rect.Left;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][0].Y = rect.Top;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][0].X = 0;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][0].Y = 1;

					m_pDefaultVertexArray->m_aVec3f[IDX_P][1].X = rect.Right;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][1].Y = rect.Top;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][1].X = 1;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][1].Y = 1;

					m_pDefaultVertexArray->m_aVec3f[IDX_P][2].X = rect.Right;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][2].Y = rect.Bottom;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][2].X = 1;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][2].Y = 0;

					m_pDefaultVertexArray->m_aVec3f[IDX_P][3].X = rect.Left;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][3].Y = rect.Bottom;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][3].X = 0;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][3].Y = 0;

					if (m_pActiveBitmask)
					{
						m_pDefaultVertexArray->m_aVec2f[IDX_B][0].X = 0;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][0].Y = 0;

						m_pDefaultVertexArray->m_aVec2f[IDX_B][1].X = rect.width();
						m_pDefaultVertexArray->m_aVec2f[IDX_B][1].Y = 0;

						m_pDefaultVertexArray->m_aVec2f[IDX_B][2].X = m_pDefaultVertexArray->m_aVec2f[IDX_B][1].X;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][2].Y = rect.height();

						m_pDefaultVertexArray->m_aVec2f[IDX_B][3].X = 0;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][3].Y = m_pDefaultVertexArray->m_aVec2f[IDX_B][2].Y;

						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_B]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * 4, m_pDefaultVertexArray->m_aVec2f[IDX_B].data());
					}
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_T]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * 4, m_pDefaultVertexArray->m_aVec2f[IDX_T].data());
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec3fIDs[IDX_P]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec3f) * 4, m_pDefaultVertexArray->m_aVec3f[IDX_P].data());
				}

				void CRenderer::PolygonSetGradientRectangle(const RectF &rect, const GradientType type)
				{
					m_pDefaultVertexArray->m_aVec3f[IDX_P][0].X = rect.Left;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][0].Y = rect.Top;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][1].X = rect.Right;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][1].Y = rect.Top;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][2].X = rect.Right;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][2].Y = rect.Bottom;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][3].X = rect.Left;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][3].Y = rect.Bottom;

					float rect_w{ rect.width() }, rect_h{ rect.height() };
					if (type == GradientType::Circle)
					{
						float w{ ntl::Max<float>(rect_w, rect_h) };
						float x{ rect_w / w }, y{ rect_h / w };
						m_pDefaultVertexArray->m_aVec2f[IDX_T][0].X = -x;
						m_pDefaultVertexArray->m_aVec2f[IDX_T][0].Y = -y;
						m_pDefaultVertexArray->m_aVec2f[IDX_T][1].X = x;
						m_pDefaultVertexArray->m_aVec2f[IDX_T][1].Y = -y;
						m_pDefaultVertexArray->m_aVec2f[IDX_T][2].X = x;
						m_pDefaultVertexArray->m_aVec2f[IDX_T][2].Y = y;
						m_pDefaultVertexArray->m_aVec2f[IDX_T][3].X = -x;
						m_pDefaultVertexArray->m_aVec2f[IDX_T][3].Y = y;
					}
					else
					{
						m_pDefaultVertexArray->m_aVec2f[IDX_T][0].X = 0;
						m_pDefaultVertexArray->m_aVec2f[IDX_T][0].Y = 1;
						m_pDefaultVertexArray->m_aVec2f[IDX_T][1].X = 1;
						m_pDefaultVertexArray->m_aVec2f[IDX_T][1].Y = 1;
						m_pDefaultVertexArray->m_aVec2f[IDX_T][2].X = 1;
						m_pDefaultVertexArray->m_aVec2f[IDX_T][2].Y = 0;
						m_pDefaultVertexArray->m_aVec2f[IDX_T][3].X = 0;
						m_pDefaultVertexArray->m_aVec2f[IDX_T][3].Y = 0;
					}

					if (m_pActiveBitmask)
					{
						m_pDefaultVertexArray->m_aVec2f[IDX_B][0].X = 0;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][0].Y = 0;

						m_pDefaultVertexArray->m_aVec2f[IDX_B][1].X = rect_w;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][1].Y = 0;

						m_pDefaultVertexArray->m_aVec2f[IDX_B][2].X = m_pDefaultVertexArray->m_aVec2f[IDX_B][1].X;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][2].Y = rect_h;

						m_pDefaultVertexArray->m_aVec2f[IDX_B][3].X = 0;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][3].Y = m_pDefaultVertexArray->m_aVec2f[IDX_B][2].Y;

						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_B]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * 4, m_pDefaultVertexArray->m_aVec2f[IDX_B].data());
					}
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_T]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * 4, m_pDefaultVertexArray->m_aVec2f[IDX_T].data());
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec3fIDs[IDX_P]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec3f) * 4, m_pDefaultVertexArray->m_aVec3f[IDX_P].data());
				}

				void CRenderer::PolygonSetRectangle(const RectF &rect, const PointF &size, const RectF &part)
				{
					m_pDefaultVertexArray->m_aVec3f[IDX_P][0].X = rect.Left;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][0].Y = rect.Top;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][0].X = part.Left / size.X;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][0].Y = 1.0f - part.Top / size.Y;

					m_pDefaultVertexArray->m_aVec3f[IDX_P][1].X = rect.Right;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][1].Y = rect.Top;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][1].X = part.Right / size.X;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][1].Y = 1.0f - part.Top / size.Y;

					m_pDefaultVertexArray->m_aVec3f[IDX_P][2].X = rect.Right;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][2].Y = rect.Bottom;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][2].X = part.Right / size.X;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][2].Y = 1.0f - part.Bottom / size.Y;

					m_pDefaultVertexArray->m_aVec3f[IDX_P][3].X = rect.Left;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][3].Y = rect.Bottom;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][3].X = part.Left / size.X;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][3].Y = 1.0f - part.Bottom / size.Y;

					if (m_pActiveBitmask)
					{
						m_pDefaultVertexArray->m_aVec2f[IDX_B][0].X = 0;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][0].Y = 0;

						m_pDefaultVertexArray->m_aVec2f[IDX_B][1].X = rect.width();
						m_pDefaultVertexArray->m_aVec2f[IDX_B][1].Y = 0;

						m_pDefaultVertexArray->m_aVec2f[IDX_B][2].X = m_pDefaultVertexArray->m_aVec2f[IDX_B][1].X;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][2].Y = rect.height();

						m_pDefaultVertexArray->m_aVec2f[IDX_B][3].X = 0;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][3].Y = m_pDefaultVertexArray->m_aVec2f[IDX_B][2].Y;

						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_B]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * 4, m_pDefaultVertexArray->m_aVec2f[IDX_B].data());
					}
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_T]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * 4, m_pDefaultVertexArray->m_aVec2f[IDX_T].data());
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec3fIDs[IDX_P]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec3f) * 4, m_pDefaultVertexArray->m_aVec3f[IDX_P].data());
				}

				void CRenderer::PolygonSetRectangle(const RectF &rect, const PointF &grid_size, const Color &c1, const Color &c2)
				{
					m_pDefaultVertexArray->m_aVec3f[IDX_P][0].X = rect.Left;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][0].Y = rect.Top;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][0].X = rect.Left / grid_size.X;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][0].Y = rect.Top / grid_size.Y;

					m_pDefaultVertexArray->m_aVec3f[IDX_P][1].X = rect.Right;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][1].Y = rect.Top;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][1].X = rect.Right / grid_size.X;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][1].Y = rect.Top / grid_size.Y;

					m_pDefaultVertexArray->m_aVec3f[IDX_P][2].X = rect.Right;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][2].Y = rect.Bottom;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][2].X = rect.Right / grid_size.X;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][2].Y = rect.Bottom / grid_size.Y;

					m_pDefaultVertexArray->m_aVec3f[IDX_P][3].X = rect.Left;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][3].Y = rect.Bottom;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][3].X = rect.Left / grid_size.X;
					m_pDefaultVertexArray->m_aVec2f[IDX_T][3].Y = rect.Bottom / grid_size.Y;

					if (m_pActiveBitmask)
					{
						m_pDefaultVertexArray->m_aVec2f[IDX_B][0].X = 0;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][0].Y = 0;

						m_pDefaultVertexArray->m_aVec2f[IDX_B][1].X = rect.width();
						m_pDefaultVertexArray->m_aVec2f[IDX_B][1].Y = 0;

						m_pDefaultVertexArray->m_aVec2f[IDX_B][2].X = m_pDefaultVertexArray->m_aVec2f[IDX_B][1].X;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][2].Y = rect.height();

						m_pDefaultVertexArray->m_aVec2f[IDX_B][3].X = 0;
						m_pDefaultVertexArray->m_aVec2f[IDX_B][3].Y = m_pDefaultVertexArray->m_aVec2f[IDX_B][2].Y;

						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_B]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * 4, m_pDefaultVertexArray->m_aVec2f[IDX_B].data());
					}
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_T]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * 4, m_pDefaultVertexArray->m_aVec2f[IDX_T].data());
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec3fIDs[IDX_P]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec3f) * 4, m_pDefaultVertexArray->m_aVec3f[IDX_P].data());

					m_pGraphics->Uniform4f(m_pActiveProgramBase->m_sChecker.Color1, c1.R / 255.0f, c1.G / 255.0f, c1.B / 255.0f, c1.A / 255.0f);
					m_pGraphics->Uniform4f(m_pActiveProgramBase->m_sChecker.Color2, c2.R / 255.0f, c2.G / 255.0f, c2.B / 255.0f, c2.A / 255.0f);
				}

				void CRenderer::SetGradient(nitisa::Gradient &g, const bool precomputed)
				{
					int point_count{ g.getPointCount() };
					if (point_count > m_pGradientPositions->Width)
					{
						if (!m_pGradientPositions->setSize(point_count, 1))
						{
							m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RESIZE_TEXTURE);
							return;
						}
						if (!m_pGradientColors->setSize(point_count, 1))
						{
							m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_RESIZE_TEXTURE);
							return;
						}
					}
					const Color1DArray &points{ g.getSortedPoints() };
					ITexture::IData *d1{ m_pGradientPositions->Lock(TextureFormat::Depth, 0, false) };
					if (!d1)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_LOCK_TEXTURE_DATA);
						return;
					}
					ITexture::IData *d2{ m_pGradientColors->Lock(TextureFormat::RGBA, 0, false) };
					if (!d2)
					{
						if (d1)
							d1->Release();
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_LOCK_TEXTURE_DATA);
						return;
					}
					if (precomputed)
					{
						float a;
						for (int i = 0; i < point_count; i++)
						{
							d1->setDepth(i, 0, points[i].Position);
							a = points[i].Color.A / 255.0f;
							d2->setColor(i, 0, Color{
								(unsigned char)std::round(points[i].Color.R * a),
								(unsigned char)std::round(points[i].Color.G * a),
								(unsigned char)std::round(points[i].Color.B * a),
								points[i].Color.A });
						}
					}
					else
					{
						for (int i = 0; i < point_count; i++)
						{
							d1->setDepth(i, 0, points[i].Position);
							d2->setColor(i, 0, points[i].Color);
						}
					}
					d2->Release();
					d1->Release();
					m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.GradientType, (int)g.Type);
					m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.GradientSize, point_count);
					m_pGraphics->ActiveTexture(GL_TEXTURE1);
					m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_pGradientPositions->Handle));
					m_pGraphics->ActiveTexture(GL_TEXTURE2);
					m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_pGradientColors->Handle));
				}

				void CRenderer::PolygonSetBlock(const RectF &rect, const RectF &block, const RectF &border, const RectF &radius, const BlockColors &colors)
				{
					m_pDefaultVertexArray->m_aVec3f[IDX_P][0].X = rect.Left;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][0].Y = rect.Top;

					m_pDefaultVertexArray->m_aVec3f[IDX_P][1].X = rect.Right;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][1].Y = rect.Top;

					m_pDefaultVertexArray->m_aVec3f[IDX_P][2].X = rect.Right;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][2].Y = rect.Bottom;

					m_pDefaultVertexArray->m_aVec3f[IDX_P][3].X = rect.Left;
					m_pDefaultVertexArray->m_aVec3f[IDX_P][3].Y = rect.Bottom;

					m_pDefaultVertexArray->m_aVec2f[IDX_B][0].X = rect.Left - block.Left;
					m_pDefaultVertexArray->m_aVec2f[IDX_B][0].Y = rect.Top - block.Top;

					m_pDefaultVertexArray->m_aVec2f[IDX_B][1].X = rect.width();
					m_pDefaultVertexArray->m_aVec2f[IDX_B][1].Y = rect.Top - block.Top;

					m_pDefaultVertexArray->m_aVec2f[IDX_B][2].X = m_pDefaultVertexArray->m_aVec2f[IDX_B][1].X;
					m_pDefaultVertexArray->m_aVec2f[IDX_B][2].Y = rect.height();

					m_pDefaultVertexArray->m_aVec2f[IDX_B][3].X = rect.Left - block.Left;
					m_pDefaultVertexArray->m_aVec2f[IDX_B][3].Y = m_pDefaultVertexArray->m_aVec2f[IDX_B][2].Y;

					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_B]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * 4, m_pDefaultVertexArray->m_aVec2f[IDX_B].data());
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec3fIDs[IDX_P]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec3f) * 4, m_pDefaultVertexArray->m_aVec3f[IDX_P].data());

					SetBlockData(block, border, radius, 1);

					if (m_pActiveProgramBase)
					{
						static float gl_colors[4 * ((int)PointLocation::Outside + 1)];
						for (int i = 0; i <= (int)PointLocation::Outside; i++)
						{
							gl_colors[i * 4 + 3] = colors[i].A / 255.0f;
							gl_colors[i * 4 + 0] = colors[i].R / 255.0f * gl_colors[i * 4 + 3];
							gl_colors[i * 4 + 1] = colors[i].G / 255.0f * gl_colors[i * 4 + 3];
							gl_colors[i * 4 + 2] = colors[i].B / 255.0f * gl_colors[i * 4 + 3];
						}
						m_pGraphics->Uniform4fv(m_pActiveProgramBase->m_sBlock.Colors, 6, gl_colors);
					}
				}

				void CRenderer::PolygonSetPolygon(const std::vector<PointF> &points, const Color &color)
				{
					int count{ ntl::Min<int>(3000, (int)points.size()) };
					RectF bound{ points[0].X, points[0].Y, points[0].X, points[0].Y };
					float ca{ color.A / 255.0f }, cr{ color.R / 255.0f * ca }, cg{ color.G / 255.0f * ca }, cb{ color.B / 255.0f * ca };
					for (int i = 0; i < count; i++)
					{
						m_pDefaultVertexArray->m_aVec3f[IDX_P][i].X = points[i].X;
						m_pDefaultVertexArray->m_aVec3f[IDX_P][i].Y = points[i].Y;
						m_pDefaultVertexArray->m_aVec4f[IDX_C][i].Data[0] = cr;
						m_pDefaultVertexArray->m_aVec4f[IDX_C][i].Data[1] = cg;
						m_pDefaultVertexArray->m_aVec4f[IDX_C][i].Data[2] = cb;
						m_pDefaultVertexArray->m_aVec4f[IDX_C][i].Data[3] = ca;
						bound.Left = ntl::Min<float>(bound.Left, points[i].X);
						bound.Top = ntl::Min<float>(bound.Top, points[i].Y);
						bound.Right = ntl::Max<float>(bound.Right, points[i].X);
						bound.Bottom = ntl::Max<float>(bound.Bottom, points[i].Y);
					}
					float bw{ bound.width() }, bh{ bound.height() };
					for (int i = 0; i < count; i++)
					{
						m_pDefaultVertexArray->m_aVec2f[IDX_T][i].X = (points[i].X - bound.Left) / bw;
						m_pDefaultVertexArray->m_aVec2f[IDX_T][i].Y = 1 - (points[i].Y - bound.Top) / bh;
						if (m_pActiveBitmask)
						{
							m_pDefaultVertexArray->m_aVec2f[IDX_B][i].X = points[i].X - bound.Left;
							m_pDefaultVertexArray->m_aVec2f[IDX_B][i].Y = points[i].Y - bound.Top;
						}
					}
					if (m_pActiveBitmask)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_B]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * count, m_pDefaultVertexArray->m_aVec2f[IDX_B].data());
					}
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_T]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * count, m_pDefaultVertexArray->m_aVec2f[IDX_T].data());
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec3fIDs[IDX_P]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec3f) * count, m_pDefaultVertexArray->m_aVec3f[IDX_P].data());
					m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec4fIDs[IDX_C]);
					m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec4f) * count, m_pDefaultVertexArray->m_aVec4f[IDX_C].data());
				}

				void CRenderer::SetBlockData(const RectF &block, const RectF &border, const RectF &radius, const int index)
				{
					m_pGraphics->Uniform4fv(m_pActiveProgramBase->m_sBlock.Rect[index], 1, block.Data);
					m_pGraphics->Uniform4fv(m_pActiveProgramBase->m_sBlock.Border[index], 1, border.Data);
					m_pGraphics->Uniform4fv(m_pActiveProgramBase->m_sBlock.Radius[index], 1, radius.Data);

					float vec2four[8], vec4[4], corner;
					int has_inner[4];

					corner = ntl::Max<float>(border.Left, border.Top, radius.Left);
					vec2four[0] = block.Left + corner;
					vec2four[1] = block.Top + corner;
					corner = ntl::Max<float>(border.Top, border.Right, radius.Top);
					vec2four[2] = block.Right - corner;
					vec2four[3] = block.Top + corner;
					corner = ntl::Max<float>(border.Right, border.Bottom, radius.Right);
					vec2four[4] = block.Right - corner;
					vec2four[5] = block.Bottom - corner;
					corner = ntl::Max<float>(border.Bottom, border.Left, radius.Bottom);
					vec2four[6] = block.Left + corner;
					vec2four[7] = block.Bottom - corner;
					m_pGraphics->Uniform2fv(m_pActiveProgramBase->m_sBlock.CornerCenter[index], 4, vec2four);

					has_inner[0] = (ntl::IsLess<float>(border.Left, radius.Left) && ntl::IsLess<float>(border.Top, radius.Left)) ? 1 : 0;
					has_inner[1] = (ntl::IsLess<float>(border.Right, radius.Top) && ntl::IsLess<float>(border.Top, radius.Top)) ? 1 : 0;
					has_inner[2] = (ntl::IsLess<float>(border.Right, radius.Right) && ntl::IsLess<float>(border.Bottom, radius.Right)) ? 1 : 0;
					has_inner[3] = (ntl::IsLess<float>(border.Left, radius.Bottom) && ntl::IsLess<float>(border.Bottom, radius.Bottom)) ? 1 : 0;
					m_pGraphics->Uniform4iv(m_pActiveProgramBase->m_sBlock.HasInner[index], 1, has_inner);

					vec4[0] = has_inner[0] ? ((radius.Left - border.Top) / (radius.Left - border.Left)) : 1;
					vec4[1] = has_inner[1] ? ((radius.Top - border.Top) / (radius.Top - border.Right)) : 1;
					vec4[2] = has_inner[2] ? ((radius.Right - border.Bottom) / (radius.Right - border.Right)) : 1;
					vec4[3] = has_inner[3] ? ((radius.Bottom - border.Bottom) / (radius.Bottom - border.Left)) : 1;
					m_pGraphics->Uniform1fv(m_pActiveProgramBase->m_sBlock.InnerScale[index], 4, vec4);

					vec4[0] = radius.Left - border.Left;
					vec4[1] = radius.Top - border.Right;
					vec4[2] = radius.Right - border.Right;
					vec4[3] = radius.Bottom - border.Left;
					m_pGraphics->Uniform1fv(m_pActiveProgramBase->m_sBlock.InnerRadius[index], 4, vec4);

					vec2four[0] = block.Left + radius.Left;
					vec2four[1] = block.Top + radius.Left;
					vec2four[2] = block.Right - radius.Top;
					vec2four[3] = block.Top + radius.Top;
					vec2four[4] = block.Right - radius.Right;
					vec2four[5] = block.Bottom - radius.Right;
					vec2four[6] = block.Left + radius.Bottom;
					vec2four[7] = block.Bottom - radius.Bottom;
					m_pGraphics->Uniform2fv(m_pActiveProgramBase->m_sBlock.OuterRCenter[index], 4, vec2four);
				}

				bool CRenderer::CheckDrawAllowed(const AnsiString &function, const int line)
				{
					if (!m_pActiveTarget && !m_bDrawing)
					{
						m_pListener->NotifyOnError(function, line, ERROR_RENDERER_NO_DRAWING);
						return false;
					}
					if (!m_bDrawAllowed)
					{
						m_pListener->NotifyOnError(function, line, ERROR_RENDERER_DRAWING_NOT_ALLOWED);
						return false;
					}
					return true;
				}
			#pragma endregion

			#pragma region Draw start/stop
				bool CRenderer::DrawBegin(Rect &viewport, IWindow *window)
				{
					if (!m_pWindow)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_NO_WINDOW);
						return false;
					}
					if (m_bDrawing)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_ALREADY_DRAWING);
						return false;
					}
					Activate();
					m_bDrawing = true;
					viewport = m_pWindow->getClientRect();
					if (viewport != m_sViewport)
					{
						m_sViewport = m_sViewportForm = viewport;
						int h{ m_sViewport.height() };
						m_pGraphics->Viewport(m_sViewport.Left, h - m_sViewport.Bottom, m_sViewport.width(), h);
						ActivateViewportMatrix();
					}
					return true;
				}

				bool CRenderer::DrawEnd()
				{
					if (!m_bDrawing)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_NO_DRAWING);
						return false;
					}
					m_bDrawing = false;
					return true;
				}

				bool CRenderer::Present()
				{
					if (!m_pWindow)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_NO_WINDOW);
						return false;
					}
					if (m_bDrawing)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_DRAWING);
						return false;
					}
					if (m_pActiveTarget)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_PRESENT_WITH_ACTIVE_TARGET);
						return false;
					}
					eglSwapBuffers(*reinterpret_cast<EGLDisplay*>(&m_pApplication->m_hHandle), *reinterpret_cast<EGLSurface*>(&m_hSurface));
					return true;
				}
			#pragma endregion

			#pragma region Clear
				IRenderer *CRenderer::Clear(const Color &color)
				{
					if (!m_pActiveTarget && !m_bDrawing)
					{
						m_pListener->NotifyOnError(__FUNCTION__, __LINE__, ERROR_RENDERER_NO_DRAWING);
						return this;
					}
					m_pGraphics->ClearColor(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f);
					m_pGraphics->Clear(GL_COLOR_BUFFER_BIT);
					return this;
				}
			#pragma endregion

			#pragma region IRenderer draw line
				IRenderer *CRenderer::DrawLine(const PointF &p1, const PointF &p2, const Color &color)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						PolygonSetLine(p1, p2, color, color);
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Color);
						m_pGraphics->DrawArrays(GL_LINES, 0, 2);
					}
					return this;
				}

				IRenderer *CRenderer::DrawLine(const PointF &p1, const PointF &p2, const Color &c1, const Color &c2)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						PolygonSetLine(p1, p2, c1, c2);
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Color);
						m_pGraphics->DrawArrays(GL_LINES, 0, 2);
					}
					return this;
				}
			#pragma endregion

			#pragma region IRenderer draw lines
				IRenderer *CRenderer::DrawLines(const std::vector<PointF> &points, const Color &color, const bool loop)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Color);
						size_t offset{ 0 }, count;
						while (offset < points.size())
						{
							count = ntl::Min<size_t>(500, points.size() - offset);
							PolygonSetLines(points, color, offset, count);
							m_pGraphics->DrawArrays(loop ? GL_LINE_LOOP : GL_LINE_STRIP, 0, (GLsizei)count);
							offset += 500;
						}
					}
					return this;
				}
			#pragma endregion

			#pragma region IRenderer draw triangle
				IRenderer *CRenderer::DrawTriangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &color)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						PolygonSetTriangle(p1, p2, p3, color, color, color);
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Color);
						m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 3);
					}
					return this;
				}

				IRenderer *CRenderer::DrawTriangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &c1, const Color &c2, const Color &c3)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						PolygonSetTriangle(p1, p2, p3, c1, c2, c3);
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Color);
						m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 3);
					}
					return this;
				}
			#pragma endregion

			#pragma region IRenderer draw rectangle
				IRenderer *CRenderer::DrawRectangle(const RectF &rect, const Color &color)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						PolygonSetRectangle(rect, color, color, color, color);
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Color);
						m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
					}
					return this;
				}

				IRenderer *CRenderer::DrawRectangle(const RectF &rect, const BorderColor &colors)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						PolygonSetRectangle(rect, colors.Left, colors.Top, colors.Right, colors.Bottom);
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Color);
						m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
					}
					return this;
				}
			#pragma endregion

			#pragma region IRenderer draw checker
				IRenderer *CRenderer::DrawChecker(const RectF &rect, const PointF &grid_size, const Color &c1, const Color &c2)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						PolygonSetRectangle(rect, grid_size, c1, c2);
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Checker);
						m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
					}
					return this;
				}
			#pragma endregion

			#pragma region IRenderer draw HSV plane
				IRenderer *CRenderer::DrawHSVPlane(const RectF &rect, const float hue)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						PolygonSetRectangle(rect);
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_HSVPlane);
						m_pGraphics->Uniform1f(m_pProgramMain->m_sHSVPlane.Hue, hue);
						m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
					}
					return this;
				}
			#pragma endregion

			#pragma region IRenderer draw polygon
				IRenderer *CRenderer::DrawPolygon(const std::vector<PointF> &points, const Color &color)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						PolygonSetPolygon(points, color);
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Color);
						m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)points.size());
					}
					return this;
				}
			#pragma endregion

			#pragma region IRenderer draw polygons
				IRenderer *CRenderer::DrawPolygons(const std::vector<std::vector<PointF>> &polygons, const Color &color)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Color);
						for (auto &points : polygons)
						{
							PolygonSetPolygon(points, color);
							m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)points.size());
						}
					}
					return this;
				}
			#pragma endregion

			#pragma region IRenderer draw gradient
				IRenderer *CRenderer::DrawGradient(const RectF &rect, nitisa::Gradient &g)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						PolygonSetGradientRectangle(rect, g.Type);
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Gradient);
						SetGradient(g, true);
						m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
					}
					return this;
				}
			#pragma endregion

			#pragma region IRenderer draw HSV gradient
				IRenderer *CRenderer::DrawHSVGradient(const RectF &rect, nitisa::Gradient &g)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						PolygonSetGradientRectangle(rect, g.Type);
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_HSVGradient);
						SetGradient(g, false);
						m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
					}
					return this;
				}
			#pragma endregion

			#pragma region IRenderer draw image
				IRenderer *CRenderer::DrawImage(IBaseTexture *image, const float transparency)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						ITexture *t{ cast<ITexture*>(image) };
						PolygonSetRectangle(image->Rectf);
						if (t)
						{
							m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Texture);
							m_pGraphics->Uniform1f(m_pProgramMain->m_sPattern.Transparency, transparency);
							m_pGraphics->ActiveTexture(GL_TEXTURE0);
							m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&image->Handle));
						}
						else
						{
							ITextureMultisample *m{ cast<ITextureMultisample*>(image) };
							m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_TextureMultisample);
							m_pGraphics->Uniform1f(m_pProgramMain->m_sPattern.Transparency, transparency);
							m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SampleCount, m->Samples);
							m_pGraphics->ActiveTexture(GL_TEXTURE4);
							m_pGraphics->BindTexture(GL_TEXTURE_2D_MULTISAMPLE, *reinterpret_cast<const GLuint*>(&image->Handle));
						}
						m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
					}
					return this;
				}

				IRenderer *CRenderer::DrawImage(IBaseTexture *image, const float transparency, const RectF &part)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						PointF size{ image->Sizef };
						RectF r{ part * RectF{ 0, 0, size.X, size.Y } };
						if (r.is_valid() && !r.is_zero())
						{
							ITexture *t{ cast<ITexture*>(image) };
							PolygonSetRectangle(RectF{ 0, 0, r.width(), r.height() }, size, r);
							if (t)
							{
								m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Texture);
								m_pGraphics->Uniform1f(m_pProgramMain->m_sPattern.Transparency, transparency);
								m_pGraphics->ActiveTexture(GL_TEXTURE0);
								m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&image->Handle));
							}
							else
							{
								ITextureMultisample *m{ cast<ITextureMultisample*>(image) };
								m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_TextureMultisample);
								m_pGraphics->Uniform1f(m_pProgramMain->m_sPattern.Transparency, transparency);
								m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SampleCount, m->Samples);
								m_pGraphics->ActiveTexture(GL_TEXTURE4);
								m_pGraphics->BindTexture(GL_TEXTURE_2D_MULTISAMPLE, *reinterpret_cast<const GLuint*>(&image->Handle));
							}
							m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
						}
					}
					return this;
				}
			#pragma endregion

			#pragma region IRenderer draw block
				IRenderer *CRenderer::DrawBlock(const RectF &block, const RectF &border, const RectF &radius, const BlockColors &colors)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						PolygonSetBlock(block, block, border, radius, colors);
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Block);
						m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
					}
					return this;
				}

				IRenderer *CRenderer::DrawBlock(const RectF &block, const RectF &border, const RectF &radius, const BlockColors &colors, const RectF &rect)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						PolygonSetBlock(rect * block, block, border, radius, colors);
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Block);
						m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
					}
					return this;
				}
			#pragma endregion

			#pragma region IRenderer draw text
				IRenderer *CRenderer::DrawText(const String &text, IPlatformFont *pf, const float distance, const Color &color)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						size_t length{ text.length() };
						if (length > 0 && pf->getTexture())
						{
							//ActivateRenderer();
							float height{ pf->getStringSize(text, distance).Y }; // Generate all glyphs required by text and text height
							m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Text);
							m_pGraphics->ActiveTexture(GL_TEXTURE0);
							m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&pf->getTexture()->Handle));
							IPlatformFont::Char *g;
							size_t index{ 0 };
							float x{ 0 }, image_w;
							float c[4]{ color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f };
							for (size_t i = 0; i < length; i++)
							{
								if (!(g = pf->getChar(text[i])))
									continue;
								if (g->Data.Width > 0) // Skip drawing characters without visual representation(like space)
								{
									image_w = (float)g->Data.Width;
									m_pDefaultVertexArray->m_aVec3f[IDX_P][index].X = x;
									m_pDefaultVertexArray->m_aVec3f[IDX_P][index].Y = 0;
									m_pDefaultVertexArray->m_aVec2f[IDX_T][index].X = g->Tx1;
									m_pDefaultVertexArray->m_aVec2f[IDX_T][index].Y = g->Ty1;
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[0] = c[0];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[1] = c[1];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[2] = c[2];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[3] = c[3];
									m_pDefaultVertexArray->m_aVec2f[IDX_B][index].X = m_pDefaultVertexArray->m_aVec3f[IDX_P][index].X;
									m_pDefaultVertexArray->m_aVec2f[IDX_B][index].Y = m_pDefaultVertexArray->m_aVec3f[IDX_P][index].Y;
									index++;

									m_pDefaultVertexArray->m_aVec3f[IDX_P][index].X = x + image_w;
									m_pDefaultVertexArray->m_aVec3f[IDX_P][index].Y = 0;
									m_pDefaultVertexArray->m_aVec2f[IDX_T][index].X = g->Tx2;
									m_pDefaultVertexArray->m_aVec2f[IDX_T][index].Y = g->Ty1;
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[0] = c[0];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[1] = c[1];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[2] = c[2];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[3] = c[3];
									m_pDefaultVertexArray->m_aVec2f[IDX_B][index].X = m_pDefaultVertexArray->m_aVec3f[IDX_P][index].X;
									m_pDefaultVertexArray->m_aVec2f[IDX_B][index].Y = m_pDefaultVertexArray->m_aVec3f[IDX_P][index].Y;
									index++;

									m_pDefaultVertexArray->m_aVec3f[IDX_P][index].X = x;
									m_pDefaultVertexArray->m_aVec3f[IDX_P][index].Y = height;
									m_pDefaultVertexArray->m_aVec2f[IDX_T][index].X = g->Tx1;
									m_pDefaultVertexArray->m_aVec2f[IDX_T][index].Y = g->Ty2;
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[0] = c[0];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[1] = c[1];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[2] = c[2];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[3] = c[3];
									m_pDefaultVertexArray->m_aVec2f[IDX_B][index].X = m_pDefaultVertexArray->m_aVec3f[IDX_P][index].X;
									m_pDefaultVertexArray->m_aVec2f[IDX_B][index].Y = m_pDefaultVertexArray->m_aVec3f[IDX_P][index].Y;
									index++;

									m_pDefaultVertexArray->m_aVec3f[IDX_P][index].X = x;
									m_pDefaultVertexArray->m_aVec3f[IDX_P][index].Y = height;
									m_pDefaultVertexArray->m_aVec2f[IDX_T][index].X = g->Tx1;
									m_pDefaultVertexArray->m_aVec2f[IDX_T][index].Y = g->Ty2;
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[0] = c[0];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[1] = c[1];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[2] = c[2];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[3] = c[3];
									m_pDefaultVertexArray->m_aVec2f[IDX_B][index].X = m_pDefaultVertexArray->m_aVec3f[IDX_P][index].X;
									m_pDefaultVertexArray->m_aVec2f[IDX_B][index].Y = m_pDefaultVertexArray->m_aVec3f[IDX_P][index].Y;
									index++;

									m_pDefaultVertexArray->m_aVec3f[IDX_P][index].X = x + image_w;
									m_pDefaultVertexArray->m_aVec3f[IDX_P][index].Y = 0;
									m_pDefaultVertexArray->m_aVec2f[IDX_T][index].X = g->Tx2;
									m_pDefaultVertexArray->m_aVec2f[IDX_T][index].Y = g->Ty1;
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[0] = c[0];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[1] = c[1];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[2] = c[2];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[3] = c[3];
									m_pDefaultVertexArray->m_aVec2f[IDX_B][index].X = m_pDefaultVertexArray->m_aVec3f[IDX_P][index].X;
									m_pDefaultVertexArray->m_aVec2f[IDX_B][index].Y = m_pDefaultVertexArray->m_aVec3f[IDX_P][index].Y;
									index++;

									m_pDefaultVertexArray->m_aVec3f[IDX_P][index].X = x + image_w;
									m_pDefaultVertexArray->m_aVec3f[IDX_P][index].Y = height;
									m_pDefaultVertexArray->m_aVec2f[IDX_T][index].X = g->Tx2;
									m_pDefaultVertexArray->m_aVec2f[IDX_T][index].Y = g->Ty2;
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[0] = c[0];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[1] = c[1];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[2] = c[2];
									m_pDefaultVertexArray->m_aVec4f[IDX_C][index].Data[3] = c[3];
									m_pDefaultVertexArray->m_aVec2f[IDX_B][index].X = m_pDefaultVertexArray->m_aVec3f[IDX_P][index].X;
									m_pDefaultVertexArray->m_aVec2f[IDX_B][index].Y = m_pDefaultVertexArray->m_aVec3f[IDX_P][index].Y;
									index++;
								}
								// Go to next character
								x += (pf->Monospace ? pf->CharacterSize.X : g->Width) + distance;
								// Check if we are at triangles buffer limit or current character is the last one. Draw if so and reset index to triangles buffer start
								if ((index == 3000 || i == length - 1) && index > 0)
								{
									m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_B]);
									m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * index, m_pDefaultVertexArray->m_aVec2f[IDX_B].data());
									m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec2fIDs[IDX_T]);
									m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * index, m_pDefaultVertexArray->m_aVec2f[IDX_T].data());
									m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec3fIDs[IDX_P]);
									m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec3f) * index, m_pDefaultVertexArray->m_aVec3f[IDX_P].data());
									m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_pDefaultVertexArray->m_aVec4fIDs[IDX_C]);
									m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec4f) * index, m_pDefaultVertexArray->m_aVec4f[IDX_C].data());
									m_pGraphics->DrawArrays(GL_TRIANGLES, 0, (GLsizei)index);
									index = 0;
								}
							}
						}
					}
					return this;
				}
			#pragma endregion

			#pragma region IRenderer blur image
				IRenderer *CRenderer::BlurImage(ITexture *image, const int radius, const BlurType type)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						IBaseTexture *old{ m_pActiveTarget };
						ITexture *temp{ CreateTexture(image->Width, image->Height, 1, TextureFormat::RGBA, true) };
						if (temp)
						{
							const Mat4f *old_matrix{ m_pActivePrimitiveMatrix };
							if (old_matrix)
							{
								m_sTempMatrix = *m_pActivePrimitiveMatrix;
								ActivatePrimitiveMatrix(nullptr);
							}
							int s1, s2;
							switch (type)
							{
							case BlurType::Gaussian:
								s1 = m_pProgramMain->m_sPattern.Pattern_BlurHGaussian;
								s2 = m_pProgramMain->m_sPattern.Pattern_BlurVGaussian;
								m_pGraphics->Uniform1f(m_pProgramMain->m_sPattern.BlurK, 1.19682684f / radius);
								m_pGraphics->Uniform1f(m_pProgramMain->m_sPattern.BlurKExp, -4.5f / (radius * radius));
								break;
							default:
								s1 = m_pProgramMain->m_sPattern.Pattern_BlurHAverage;
								s2 = m_pProgramMain->m_sPattern.Pattern_BlurVAverage;
							}
							m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.BlurRadius, radius);
							m_pGraphics->Uniform2f(m_pProgramMain->m_sPattern.BlurDisp, 1 / image->Rectf.Right, 1 / image->Rectf.Bottom);
							// First pass
							ActivateTarget(temp);
							m_pGraphics->ClearColor(0, 0, 0, 0);
							m_pGraphics->Clear(GL_COLOR_BUFFER_BIT);
							PolygonSetRectangle(image->Rectf);
							m_pGraphics->ActiveTexture(GL_TEXTURE0);
							m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&image->Handle));
							m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, s1);
							m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
							// Second pass
							ActivateTarget(image);
							m_pGraphics->Clear(GL_COLOR_BUFFER_BIT);
							m_pGraphics->ActiveTexture(GL_TEXTURE0);
							m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&temp->Handle));
							m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, s2);
							m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
							// Finish
							temp->Release();
							ActivateTarget(old);
							if (old_matrix)
								ActivatePrimitiveMatrix(m_sTempMatrix);
						}
					}
					return this;
				}

				IRenderer *CRenderer::BlurImage(ITexture *source, const int radius, const BlurType type, ITexture *target)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						IBaseTexture *old{ m_pActiveTarget };
						ITexture *temp{ CreateTexture(target->Width, target->Height, 1, TextureFormat::RGBA, true) };
						if (temp)
						{
							const Mat4f *old_matrix{ m_pActivePrimitiveMatrix };
							if (old_matrix)
							{
								m_sTempMatrix = *m_pActivePrimitiveMatrix;
								ActivatePrimitiveMatrix(nullptr);
							}
							int s1, s2;
							switch (type)
							{
							case BlurType::Gaussian:
								s1 = m_pProgramMain->m_sPattern.Pattern_BlurHGaussian;
								s2 = m_pProgramMain->m_sPattern.Pattern_BlurVGaussian;
								m_pGraphics->Uniform1f(m_pProgramMain->m_sPattern.BlurK, 1.19682684f / radius);
								m_pGraphics->Uniform1f(m_pProgramMain->m_sPattern.BlurKExp, -4.5f / (radius * radius));
								break;
							default:
								s1 = m_pProgramMain->m_sPattern.Pattern_BlurHAverage;
								s2 = m_pProgramMain->m_sPattern.Pattern_BlurVAverage;
							}
							m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.BlurRadius, radius);
							m_pGraphics->Uniform2f(m_pProgramMain->m_sPattern.BlurDisp, 1 / target->Rectf.Right, 1 / target->Rectf.Bottom);
							// First pass
							ActivateTarget(temp);
							m_pGraphics->ClearColor(0, 0, 0, 0);
							m_pGraphics->Clear(GL_COLOR_BUFFER_BIT);
							PolygonSetRectangle(target->Rectf);
							m_pGraphics->ActiveTexture(GL_TEXTURE0);
							m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&source->Handle));
							m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, s1);
							m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
							// Second pass
							ActivateTarget(target);
							m_pGraphics->Clear(GL_COLOR_BUFFER_BIT);
							m_pGraphics->ActiveTexture(GL_TEXTURE0);
							m_pGraphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&temp->Handle));
							m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, s2);
							m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
							// Finish
							temp->Release();
							ActivateTarget(old);
							if (old_matrix)
								ActivatePrimitiveMatrix(m_sTempMatrix);
						}
					}
					return this;
				}
			#pragma endregion

			#pragma region IRenderer inverse pixels
				IRenderer *CRenderer::InversePixels(const RectF &rect)
				{
					if (CheckDrawAllowed(__FUNCTION__, __LINE__))
					{
						m_pGraphics->BlendFuncSeparate(GL_ONE_MINUS_DST_COLOR, GL_ZERO, GL_DST_ALPHA, GL_ZERO);
						PolygonSetRectangle(rect, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 });
						m_pGraphics->Uniform1i(m_pProgramMain->m_sPattern.SubroutinePattern, m_pProgramMain->m_sPattern.Pattern_Color);
						m_pGraphics->DrawArrays(GL_TRIANGLE_FAN, 0, 4);
						m_pGraphics->BlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);
					}
					return this;
				}
			#pragma endregion
			}
		}
	}
}
#endif