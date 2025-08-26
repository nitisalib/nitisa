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
#include "VertexArrayImmutable.h"

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
			namespace opengl31
			{
			#pragma region Constructor & destructor
				CVertexArrayImmutable::CVertexArrayImmutable(COpenGL *graphics, const VertexFormat &format, const size_t vertex_count) :
					CVertexArray(format, vertex_count),
					m_pGraphics{ graphics },
					m_aVec1fIDs{ 0, 0, 0, 0, 0, 0, 0, 0 },
					m_aVec2fIDs{ 0, 0, 0, 0, 0, 0, 0, 0 },
					m_aVec3fIDs{ 0, 0, 0, 0, 0, 0, 0, 0 },
					m_aVec4fIDs{ 0, 0, 0, 0, 0, 0, 0, 0 },
					m_aVec1iIDs{ 0, 0, 0, 0, 0, 0, 0, 0 },
					m_aVec2iIDs{ 0, 0, 0, 0, 0, 0, 0, 0 },
					m_aVec3iIDs{ 0, 0, 0, 0, 0, 0, 0, 0 },
					m_aVec4iIDs{ 0, 0, 0, 0, 0, 0, 0, 0 },
					m_hIndices{ 0 },
					m_bValid{ false },
					m_iIndexCount{ 0 }
				{
					Initialize(false);
				}

				CVertexArrayImmutable::CVertexArrayImmutable(COpenGL *graphics, const VertexFormat &format, const size_t polygon_count, const size_t polygon_size) :
					CVertexArray(format, polygon_count, polygon_size),
					m_pGraphics{ graphics },
					m_aVec1fIDs{ 0, 0, 0, 0, 0, 0, 0, 0 },
					m_aVec2fIDs{ 0, 0, 0, 0, 0, 0, 0, 0 },
					m_aVec3fIDs{ 0, 0, 0, 0, 0, 0, 0, 0 },
					m_aVec4fIDs{ 0, 0, 0, 0, 0, 0, 0, 0 },
					m_aVec1iIDs{ 0, 0, 0, 0, 0, 0, 0, 0 },
					m_aVec2iIDs{ 0, 0, 0, 0, 0, 0, 0, 0 },
					m_aVec3iIDs{ 0, 0, 0, 0, 0, 0, 0, 0 },
					m_aVec4iIDs{ 0, 0, 0, 0, 0, 0, 0, 0 },
					m_hIndices{ 0 },
					m_bValid{ false },
					m_iIndexCount{ 0 }
				{
					Initialize(true);
				}

				void CVertexArrayImmutable::BeforeRelease()
				{
					DeleteBuffers(m_sFormat.Vec1fCount, m_aVec1fIDs);
					DeleteBuffers(m_sFormat.Vec2fCount, m_aVec2fIDs);
					DeleteBuffers(m_sFormat.Vec3fCount, m_aVec3fIDs);
					DeleteBuffers(m_sFormat.Vec4fCount, m_aVec4fIDs);
					DeleteBuffers(m_sFormat.Vec1iCount, m_aVec1iIDs);
					DeleteBuffers(m_sFormat.Vec2iCount, m_aVec2iIDs);
					DeleteBuffers(m_sFormat.Vec3iCount, m_aVec3iIDs);
					DeleteBuffers(m_sFormat.Vec4iCount, m_aVec4iIDs);
					if (m_hIndices > 0)
						DeleteBuffers(1, &m_hIndices);
					if (*reinterpret_cast<GLuint*>(&m_hHandle))
					{
						m_pGraphics->DeleteVertexArrays(1, reinterpret_cast<GLuint*>(&m_hHandle));
						*reinterpret_cast<GLuint*>(&m_hHandle) = 0;
					}
					CVertexArray::BeforeRelease();
				}

				CVertexArrayImmutable *CVertexArrayImmutable::Create(COpenGL *graphics, const VertexFormat &format, const size_t vertex_count)
				{
					CVertexArrayImmutable *result{ new CVertexArrayImmutable(graphics, format, vertex_count) };
					if (result->m_bValid)
						return result;
					result->Release();
					return nullptr;
				}

				CVertexArrayImmutable *CVertexArrayImmutable::Create(COpenGL *graphics, const VertexFormat &format, const size_t polygon_count, const size_t polygon_size)
				{
					CVertexArrayImmutable *result{ new CVertexArrayImmutable(graphics, format, polygon_count, polygon_size) };
					if (result->m_bValid)
						return result;
					result->Release();
					return nullptr;
				}
			#pragma endregion

			#pragma region IVertexArray rendering
				bool CVertexArrayImmutable::RenderPoints()
				{
					if (m_iLastRenderedPrimitives == PRIMITIVE_NONE)
					{
						UpdateBuffers();
						if (m_hIndices > 0)
						{
							m_iIndexCount = 0;
							for (auto p : m_aPolygons)
								m_iIndexCount += (GLsizei)p->getVertexCount();
							if (m_iIndexCount > 0)
							{
								unsigned int *indices{ new unsigned int[m_iIndexCount] };
								m_iIndexCount = 0;
								for (auto p : m_aPolygons)
									for (size_t i = 0; i < p->getVertexCount(); i++)
										indices[m_iIndexCount++] = (unsigned int)p->getVertex(i)->VAIndex;
								m_pGraphics->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hIndices);
								m_pGraphics->BufferData(GL_ELEMENT_ARRAY_BUFFER, m_iIndexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
								delete[] indices;
							}
						}
						m_bChanged = false;
						m_iLastRenderedPrimitives = PRIMITIVE_POINT;
					}
					if (m_iIndexCount > 0)
					{
						m_pGraphics->DrawElements(GL_POINTS, m_iIndexCount, GL_UNSIGNED_INT, nullptr);
						return true;
					}
					return false;
				}

				bool CVertexArrayImmutable::RenderLines()
				{
					if (m_iLastRenderedPrimitives == PRIMITIVE_NONE)
					{
						UpdateBuffers();
						if (m_hIndices > 0)
						{
							m_iIndexCount = 0;
							int vc;
							for (auto p : m_aPolygons)
								if ((vc = (int)p->getVertexCount()) >= 2)
									m_iIndexCount += vc + 1;
							if (m_iIndexCount > 0)
							{
								unsigned int *indices{ new unsigned int[m_iIndexCount] };
								m_iIndexCount = 0;
								for (auto p : m_aPolygons)
									if ((vc = (int)p->getVertexCount()) >= 2)
									{
										for (int i = 0; i < vc; i++)
											indices[m_iIndexCount++] = (unsigned int)p->getVertex(i)->VAIndex;
										indices[m_iIndexCount++] = (unsigned int)-1;
									}
								m_pGraphics->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hIndices);
								m_pGraphics->BufferData(GL_ELEMENT_ARRAY_BUFFER, m_iIndexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
								delete[] indices;
							}
						}
						m_bChanged = false;
						m_iLastRenderedPrimitives = PRIMITIVE_LINE;
					}
					if (m_iIndexCount > 0)
					{
						m_pGraphics->DrawElements(GL_LINE_STRIP, m_iIndexCount, GL_UNSIGNED_INT, nullptr);
						return true;
					}
					return false;
				}

				bool CVertexArrayImmutable::RenderWires()
				{
					if (m_iLastRenderedPrimitives == PRIMITIVE_NONE)
					{
						UpdateBuffers();
						if (m_hIndices > 0)
						{
							m_iIndexCount = 0;
							int vc;
							for (auto p : m_aPolygons)
								if ((vc = (int)p->getVertexCount()) >= 3)
									m_iIndexCount += vc + 1;
							if (m_iIndexCount > 0)
							{
								unsigned int *indices{ new unsigned int[m_iIndexCount] };
								m_iIndexCount = 0;
								for (auto p : m_aPolygons)
									if ((vc = (int)p->getVertexCount()) >= 3)
									{
										for (int i = 0; i < vc; i++)
											indices[m_iIndexCount++] = (unsigned int)p->getVertex(i)->VAIndex;
										indices[m_iIndexCount++] = (unsigned int)-1;
									}
								m_pGraphics->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hIndices);
								m_pGraphics->BufferData(GL_ELEMENT_ARRAY_BUFFER, m_iIndexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
								delete[] indices;
							}
						}
						m_bChanged = false;
						m_iLastRenderedPrimitives = PRIMITIVE_WIRE;
					}
					if (m_iIndexCount > 0)
					{
						m_pGraphics->DrawElements(GL_LINE_LOOP, m_iIndexCount, GL_UNSIGNED_INT, nullptr);
						return true;
					}
					return false;
				}

				bool CVertexArrayImmutable::RenderPolygons()
				{
					if (m_iLastRenderedPrimitives == PRIMITIVE_NONE)
					{
						UpdateBuffers();
						if (m_hIndices > 0)
						{
							m_iIndexCount = 0;
							int vc;
							for (auto p : m_aPolygons)
								if ((vc = (int)p->getVertexCount()) >= 3)
									m_iIndexCount += vc + 1;
							if (m_iIndexCount > 0)
							{
								unsigned int *indices{ new unsigned int[m_iIndexCount] };
								m_iIndexCount = 0;
								for (auto p : m_aPolygons)
									if ((vc = (int)p->getVertexCount()) >= 3)
									{
										for (int i = 0; i < vc; i++)
											indices[m_iIndexCount++] = (unsigned int)p->getVertex(i)->VAIndex;
										indices[m_iIndexCount++] = (unsigned int)-1;
									}
								m_pGraphics->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hIndices);
								m_pGraphics->BufferData(GL_ELEMENT_ARRAY_BUFFER, m_iIndexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
								delete[] indices;
							}
						}
						m_bChanged = false;
						m_iLastRenderedPrimitives = PRIMITIVE_POLYGON;
					}
					if (m_iIndexCount > 0)
					{
						m_pGraphics->DrawElements(GL_TRIANGLE_FAN, m_iIndexCount, GL_UNSIGNED_INT, nullptr);
						return true;
					}
					return false;
				}
			#pragma endregion

			#pragma region Helpers
				void CVertexArrayImmutable::Initialize(const bool has_polygons)
				{
					m_pGraphics->GenVertexArrays(1, reinterpret_cast<GLuint*>(&m_hHandle));
					if (!(*reinterpret_cast<GLuint*>(&m_hHandle)))
						return;
					m_pGraphics->BindVertexArray(*reinterpret_cast<GLuint*>(&m_hHandle));
					if (!CreateBuffers(m_sFormat.Vec1fCount, m_aVec1fIDs))
						return;
					if (!CreateBuffers(m_sFormat.Vec2fCount, m_aVec2fIDs))
						return;
					if (!CreateBuffers(m_sFormat.Vec3fCount, m_aVec3fIDs))
						return;
					if (!CreateBuffers(m_sFormat.Vec4fCount, m_aVec4fIDs))
						return;
					if (!CreateBuffers(m_sFormat.Vec1iCount, m_aVec1iIDs))
						return;
					if (!CreateBuffers(m_sFormat.Vec2iCount, m_aVec2iIDs))
						return;
					if (!CreateBuffers(m_sFormat.Vec3iCount, m_aVec3iIDs))
						return;
					if (!CreateBuffers(m_sFormat.Vec4iCount, m_aVec4iIDs))
						return;
					if (has_polygons)
					{
						m_pGraphics->GenBuffers(1, &m_hIndices);
						if (!m_hIndices)
							return;
					}
					GLuint buffer_index{ 0 };
					SetupBuffers(m_sFormat.Vec1fCount, m_aVec1fIDs, sizeof(Vec1f), GL_FLOAT, 1, buffer_index);
					SetupBuffers(m_sFormat.Vec2fCount, m_aVec2fIDs, sizeof(Vec2f), GL_FLOAT, 2, buffer_index);
					SetupBuffers(m_sFormat.Vec3fCount, m_aVec3fIDs, sizeof(Vec3f), GL_FLOAT, 3, buffer_index);
					SetupBuffers(m_sFormat.Vec4fCount, m_aVec4fIDs, sizeof(Vec4f), GL_FLOAT, 4, buffer_index);
					SetupBuffers(m_sFormat.Vec1iCount, m_aVec1iIDs, sizeof(Vec1i), GL_INT, 1, buffer_index);
					SetupBuffers(m_sFormat.Vec2iCount, m_aVec2iIDs, sizeof(Vec2i), GL_INT, 2, buffer_index);
					SetupBuffers(m_sFormat.Vec3iCount, m_aVec3iIDs, sizeof(Vec3i), GL_INT, 3, buffer_index);
					SetupBuffers(m_sFormat.Vec4iCount, m_aVec4iIDs, sizeof(Vec4i), GL_INT, 4, buffer_index);

					if (has_polygons)
					{
						m_pGraphics->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hIndices);
						m_pGraphics->VertexAttribPointer(buffer_index, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(unsigned int), nullptr);
					}
					m_bValid = true;
				}

				bool CVertexArrayImmutable::CreateBuffers(const byte count, GLuint *ids)
				{
					if (count > 0)
					{
						m_pGraphics->GenBuffers(count, ids);
						for (byte i = 0; i < count; i++)
							if (!ids[i])
								return false;
					}
					return true;
				}

				void CVertexArrayImmutable::SetupBuffers(const byte count, GLuint *ids, const size_t size, const unsigned int type, const int element_count, GLuint &buffer_index)
				{
					for (byte i = 0; i < count; i++, buffer_index++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, ids[i]);
						m_pGraphics->BufferData(GL_ARRAY_BUFFER, size * m_aVertices.size(), nullptr, GL_DYNAMIC_DRAW);
						m_pGraphics->EnableVertexAttribArray(buffer_index);
						m_pGraphics->VertexAttribPointer(buffer_index, element_count, type, GL_FALSE, 0, nullptr);
					}
				}

				void CVertexArrayImmutable::DeleteBuffers(const byte count, GLuint *ids)
				{
					if (count > 0)
					{
						m_pGraphics->DeleteBuffers(count, ids);
						for (byte i = 0; i < count; i++)
							ids[i] = 0;
					}
				}

				void CVertexArrayImmutable::UpdateBuffers()
				{
					for (byte i = 0; i < m_sFormat.Vec1fCount; i++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_aVec1fIDs[i]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec1f) * m_aVertices.size(), m_aVec1f[i].data());
					}
					for (byte i = 0; i < m_sFormat.Vec2fCount; i++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_aVec2fIDs[i]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * m_aVertices.size(), m_aVec2f[i].data());
					}
					for (byte i = 0; i < m_sFormat.Vec3fCount; i++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_aVec3fIDs[i]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec3f) * m_aVertices.size(), m_aVec3f[i].data());
					}
					for (byte i = 0; i < m_sFormat.Vec4fCount; i++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_aVec4fIDs[i]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec4f) * m_aVertices.size(), m_aVec4f[i].data());
					}
					for (byte i = 0; i < m_sFormat.Vec1iCount; i++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_aVec1iIDs[i]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec1i) * m_aVertices.size(), m_aVec1i[i].data());
					}
					for (byte i = 0; i < m_sFormat.Vec2iCount; i++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_aVec2iIDs[i]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2i) * m_aVertices.size(), m_aVec2i[i].data());
					}
					for (byte i = 0; i < m_sFormat.Vec3iCount; i++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_aVec3iIDs[i]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec3i) * m_aVertices.size(), m_aVec3i[i].data());
					}
					for (byte i = 0; i < m_sFormat.Vec4iCount; i++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_aVec4iIDs[i]);
						m_pGraphics->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec4i) * m_aVertices.size(), m_aVec4i[i].data());
					}
				}
			#pragma endregion
			}
		}
	}
}
#endif