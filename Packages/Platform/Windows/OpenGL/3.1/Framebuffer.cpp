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
			namespace opengl31
			{
			#pragma region Constructor & destructor
				CFramebuffer::CFramebuffer(COpenGL *graphics, IRenderer *renderer) :
					CReleasable(),
					m_pGraphics{ graphics },
					m_pRenderer{ renderer }
				{
					m_pDepthAttachment = nullptr;
					m_iDepthAttachmentLevel = 0;
					m_pStencilAttachment = nullptr;
					m_iStencilAttachmentLevel = 0;
					m_pGraphics->GenFramebuffers(1, reinterpret_cast<GLuint*>(&m_hHandle));
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0)
					{
						m_pGraphics->BindFramebuffer(GL_FRAMEBUFFER, *reinterpret_cast<GLuint*>(&m_hHandle));
						m_pGraphics->DrawBuffer(GL_NONE);
					}
				}

				void CFramebuffer::BeforeRelease()
				{
					if (*reinterpret_cast<GLuint*>(&m_hHandle) > 0)
						m_pGraphics->DeleteFramebuffers(1, reinterpret_cast<GLuint*>(&m_hHandle));
				}

				CFramebuffer *CFramebuffer::Create(COpenGL *graphics, IRenderer *renderer)
				{
					CFramebuffer *result{ new CFramebuffer(graphics, renderer) };
					if (*reinterpret_cast<GLuint*>(&result->m_hHandle) > 0)
						return result;
					delete result;
					return nullptr;
				}
			#pragma endregion

			#pragma region IFramebuffer getters
				int CFramebuffer::getColorAttachmentCount() const
				{
					return (int)m_aColorAttachments.size();
				}

				IBaseTexture *CFramebuffer::getColorAttachment(const int index)
				{
					if (index >= 0 && index < (int)m_aColorAttachments.size())
						return m_aColorAttachments[index].Texture;
					return nullptr;
				}

				int CFramebuffer::getColorAttachmentLevel(const int index) const
				{
					if (index >= 0 && index < (int)m_aColorAttachments.size())
						return m_aColorAttachments[index].Level;
					return 0;
				}
			#pragma endregion

			#pragma region IFramebuffer setters
				bool CFramebuffer::setDepthAttachment(IBaseTexture *value, const int level, const bool force)
				{
					ITexture *t{ cast<ITexture*>(value) };
					ITextureMultisample *m{ t ? nullptr : cast<ITextureMultisample*>(value) };
					int l{ m ? 0 : level };
					if (t && (l < 0 || l >= t->ActualLevelCount))
						return false;
					if (m && m_pRenderer->Version < Version2{ 3, 2 })
						return false;
					if (value != m_pDepthAttachment || l != m_iDepthAttachmentLevel || force)
					{
						if (value != m_pDepthAttachment || force)
						{
							if (m_pDepthAttachment && !value)
							{
								m_pGraphics->BindFramebuffer(GL_FRAMEBUFFER, *reinterpret_cast<GLuint*>(&m_hHandle));
								m_pGraphics->FramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
							}
							m_pDepthAttachment = value;
							if (m_pDepthAttachment)
							{
								m_pGraphics->BindFramebuffer(GL_FRAMEBUFFER, *reinterpret_cast<GLuint*>(&m_hHandle));
								m_pGraphics->FramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_pDepthAttachment->Handle), l);
								m_iDepthAttachmentLevel = l;
							}
							else
								m_iDepthAttachmentLevel = 0;
						}
						else if (m_pDepthAttachment)
						{
							m_pGraphics->BindFramebuffer(GL_FRAMEBUFFER, *reinterpret_cast<GLuint*>(&m_hHandle));
							m_pGraphics->FramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_pDepthAttachment->Handle), l);
							m_iDepthAttachmentLevel = l;
						}
						return true;
					}
					return false;
				}

				bool CFramebuffer::setStencilAttachment(IBaseTexture *value, const int level, const bool force)
				{
					ITexture *t{ cast<ITexture*>(value) };
					ITextureMultisample *m{ t ? nullptr : cast<ITextureMultisample*>(value) };
					int l{ m ? 0 : level };
					if (t && (l < 0 || l >= t->ActualLevelCount))
						return false;
					if (m && m_pRenderer->Version < Version2{ 3, 2 })
						return false;
					if (value != m_pStencilAttachment || l != m_iStencilAttachmentLevel || force)
					{
						if (value != m_pStencilAttachment || force)
						{
							if (m_pStencilAttachment && !value)
							{
								m_pGraphics->BindFramebuffer(GL_FRAMEBUFFER, *reinterpret_cast<GLuint*>(&m_hHandle));
								m_pGraphics->FramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
							}
							m_pStencilAttachment = value;
							if (m_pStencilAttachment)
							{
								m_pGraphics->BindFramebuffer(GL_FRAMEBUFFER, *reinterpret_cast<GLuint*>(&m_hHandle));
								m_pGraphics->FramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, m ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_pStencilAttachment->Handle), l);
								m_iStencilAttachmentLevel = l;
							}
							else
								m_iStencilAttachmentLevel = 0;
						}
						else if (m_pStencilAttachment)
						{
							m_pGraphics->BindFramebuffer(GL_FRAMEBUFFER, *reinterpret_cast<GLuint*>(&m_hHandle));
							m_pGraphics->FramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_pStencilAttachment->Handle), l);
							m_iStencilAttachmentLevel = l;
						}
						return true;
					}
					return false;
				}

				bool CFramebuffer::setDepthStencilAttachment(IBaseTexture *value, const int level, const bool force)
				{
					ITexture *t{ cast<ITexture*>(value) };
					ITextureMultisample *m{ t ? nullptr : cast<ITextureMultisample*>(value) };
					int l{ m ? 0 : level };
					if (t && (l < 0 || l >= t->ActualLevelCount))
						return false;
					if (m && m_pRenderer->Version < Version2{ 3, 2 })
						return false;
					if (value != m_pDepthAttachment || value != m_pStencilAttachment || l != m_iDepthAttachmentLevel || l != m_iStencilAttachmentLevel || force)
					{
						if (value != m_pDepthAttachment || value != m_pStencilAttachment || force)
						{
							if ((m_pDepthAttachment || m_pStencilAttachment) && !value)
							{
								m_pGraphics->BindFramebuffer(GL_FRAMEBUFFER, *reinterpret_cast<GLuint*>(&m_hHandle));
								m_pGraphics->FramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
							}
							m_pDepthAttachment = value;
							m_pStencilAttachment = value;
							if (m_pDepthAttachment)
							{
								m_pGraphics->BindFramebuffer(GL_FRAMEBUFFER, *reinterpret_cast<GLuint*>(&m_hHandle));
								m_pGraphics->FramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, m ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_pDepthAttachment->Handle), l);
								m_iDepthAttachmentLevel = l;
								m_iStencilAttachmentLevel = l;
							}
							else
							{
								m_iDepthAttachmentLevel = 0;
								m_iStencilAttachmentLevel = 0;
							}
						}
						else if (m_pDepthAttachment)
						{
							m_pGraphics->BindFramebuffer(GL_FRAMEBUFFER, *reinterpret_cast<GLuint*>(&m_hHandle));
							m_pGraphics->FramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_pDepthAttachment->Handle), l);
							m_iDepthAttachmentLevel = l;
							m_iStencilAttachmentLevel = l;
						}
						return true;
					}
					return false;
				}

				bool CFramebuffer::setColorAttachment(IBaseTexture *value, const int index, const int level, const bool force)
				{
					if (index < 0 || index >= m_pRenderer->Capabilities.MaxColorAttachments)
						return false;
					ITexture *t{ cast<ITexture*>(value) };
					ITextureMultisample *m{ t ? nullptr : cast<ITextureMultisample*>(value) };
					int l{ m ? 0 : level };
					if (t && (l < 0 || l >= t->ActualLevelCount))
						return false;
					if (m && m_pRenderer->Version < Version2{ 3, 2 })
						return false;
					if (index <= (int)m_aColorAttachments.size() || value != m_aColorAttachments[index].Texture || l != m_aColorAttachments[index].Level || force)
					{
						if (index >= (int)m_aColorAttachments.size())
							m_aColorAttachments.resize(index + 1, ATTACHMENT{ nullptr, 0 });
						if (value != m_aColorAttachments[index].Texture || force)
						{
							m_pGraphics->BindFramebuffer(GL_FRAMEBUFFER, *reinterpret_cast<GLuint*>(&m_hHandle));
							if (m_aColorAttachments[index].Texture && !value)
								m_pGraphics->FramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, 0, 0);
							m_aColorAttachments[index].Texture = value;
							if (m_aColorAttachments[index].Texture)
							{
								m_pGraphics->FramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, m ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_aColorAttachments[index].Texture->Handle), l);
								m_aColorAttachments[index].Level = l;
							}
							else
								m_aColorAttachments[index].Level = 0;
							size_t count{ ntl::Min<size_t>(m_aColorAttachments.size(), m_pRenderer->Capabilities.MaxDrawBuffers) };
							if (count > 0)
							{
								GLenum *draw_buffers{ new GLenum[count] };
								for (size_t index = 0; index < count; index++)
									if (m_aColorAttachments[index].Texture)
										draw_buffers[index] = GLenum(GL_COLOR_ATTACHMENT0 + index);
									else
										draw_buffers[index] = GL_NONE;
								m_pGraphics->DrawBuffers((GLsizei)count, draw_buffers);
								delete[] draw_buffers;
							}
							else
								m_pGraphics->DrawBuffer(GL_NONE);
						}
						else if (m_aColorAttachments[index].Texture)
						{
							m_pGraphics->BindFramebuffer(GL_FRAMEBUFFER, *reinterpret_cast<GLuint*>(&m_hHandle));
							m_pGraphics->FramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_aColorAttachments[index].Texture->Handle), l);
							m_aColorAttachments[index].Level = l;
						}
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