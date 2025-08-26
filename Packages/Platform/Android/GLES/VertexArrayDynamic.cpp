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
#include "VertexArrayDynamic.h"

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
			namespace gles
			{
			#pragma region Constructor & destructor
				CVertexArrayDynamic::CVertexArrayDynamic(COpenGL *graphics, const VertexFormat &format) :
					CVertexArray(format),
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
					m_pGraphics->GenBuffers(1, &m_hIndices);
					if (!m_hIndices)
						return;
					GLuint buffer_index{ 0 };
					SetupBuffers(m_sFormat.Vec1fCount, m_aVec1fIDs, GL_FLOAT, 1, buffer_index);
					SetupBuffers(m_sFormat.Vec2fCount, m_aVec2fIDs, GL_FLOAT, 2, buffer_index);
					SetupBuffers(m_sFormat.Vec3fCount, m_aVec3fIDs, GL_FLOAT, 3, buffer_index);
					SetupBuffers(m_sFormat.Vec4fCount, m_aVec4fIDs, GL_FLOAT, 4, buffer_index);
					SetupBuffers(m_sFormat.Vec1iCount, m_aVec1iIDs, GL_INT, 1, buffer_index);
					SetupBuffers(m_sFormat.Vec2iCount, m_aVec2iIDs, GL_INT, 2, buffer_index);
					SetupBuffers(m_sFormat.Vec3iCount, m_aVec3iIDs, GL_INT, 3, buffer_index);
					SetupBuffers(m_sFormat.Vec4iCount, m_aVec4iIDs, GL_INT, 4, buffer_index);

					m_pGraphics->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_hIndices);
					m_pGraphics->VertexAttribPointer(buffer_index, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(unsigned int), nullptr);
					m_bValid = true;
				}

				CVertexArrayDynamic::CVertexArrayDynamic(COpenGL *graphics, const VertexFormat &format, const size_t vertex_count) :
					CVertexArrayDynamic(graphics, format)
				{
					if (m_bValid)
						setVertexCount(vertex_count);
				}

				CVertexArrayDynamic::CVertexArrayDynamic(COpenGL *graphics, const VertexFormat &format, const size_t polygon_count, const size_t polygon_size) :
					CVertexArrayDynamic(graphics, format)
				{
					if (m_bValid)
						setPolygonCount(polygon_count, polygon_size);
				}

				void CVertexArrayDynamic::BeforeRelease()
				{
					DeleteBuffers(m_sFormat.Vec1fCount, m_aVec1fIDs);
					DeleteBuffers(m_sFormat.Vec2fCount, m_aVec2fIDs);
					DeleteBuffers(m_sFormat.Vec3fCount, m_aVec3fIDs);
					DeleteBuffers(m_sFormat.Vec4fCount, m_aVec4fIDs);
					DeleteBuffers(m_sFormat.Vec1iCount, m_aVec1iIDs);
					DeleteBuffers(m_sFormat.Vec2iCount, m_aVec2iIDs);
					DeleteBuffers(m_sFormat.Vec3iCount, m_aVec3iIDs);
					DeleteBuffers(m_sFormat.Vec4iCount, m_aVec4iIDs);
					DeleteBuffers(1, &m_hIndices);
					if (*reinterpret_cast<GLuint*>(&m_hHandle))
					{
						m_pGraphics->DeleteVertexArrays(1, reinterpret_cast<GLuint*>(&m_hHandle));
						*reinterpret_cast<GLuint*>(&m_hHandle) = 0;
					}
					CVertexArray::BeforeRelease();
				}

				CVertexArrayDynamic *CVertexArrayDynamic::Create(COpenGL *graphics, const VertexFormat &format)
				{
					CVertexArrayDynamic *result{ new CVertexArrayDynamic(graphics, format) };
					if (result->m_bValid)
						return result;
					result->Release();
					return nullptr;
				}

				CVertexArrayDynamic *CVertexArrayDynamic::Create(COpenGL *graphics, const VertexFormat &format, const size_t vertex_count)
				{
					CVertexArrayDynamic *result{ new CVertexArrayDynamic(graphics, format, vertex_count) };
					if (result->m_bValid)
						return result;
					result->Release();
					return nullptr;
				}

				CVertexArrayDynamic *CVertexArrayDynamic::Create(COpenGL *graphics, const VertexFormat &format, const size_t polygon_count, const size_t polygon_size)
				{
					CVertexArrayDynamic *result{ new CVertexArrayDynamic(graphics, format, polygon_count, polygon_size) };
					if (result->m_bValid)
						return result;
					result->Release();
					return nullptr;
				}
			#pragma endregion

			#pragma region IVertexArray rendering
				bool CVertexArrayDynamic::RenderPoints()
				{
					if (m_bChanged)
					{
						UpdateBuffers();
						m_iLastRenderedPrimitives = PRIMITIVE_NONE;
						m_bChanged = false;
					}
					if (m_iLastRenderedPrimitives != PRIMITIVE_POINT)
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
							m_pGraphics->BufferData(GL_ELEMENT_ARRAY_BUFFER, m_iIndexCount * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
							delete[] indices;
						}
						m_iLastRenderedPrimitives = PRIMITIVE_POINT;
					}
					if (m_iIndexCount > 0)
					{
						m_pGraphics->DrawElements(GL_POINTS, m_iIndexCount, GL_UNSIGNED_INT, nullptr);
						return true;
					}
					return false;
				}

				bool CVertexArrayDynamic::RenderLines()
				{
					if (m_bChanged)
					{
						UpdateBuffers();
						m_iLastRenderedPrimitives = PRIMITIVE_NONE;
						m_bChanged = false;
					}
					if (m_iLastRenderedPrimitives != PRIMITIVE_LINE)
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
							m_pGraphics->BufferData(GL_ELEMENT_ARRAY_BUFFER, m_iIndexCount * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
							delete[] indices;
						}
						m_iLastRenderedPrimitives = PRIMITIVE_LINE;
					}
					if (m_iIndexCount > 0)
					{
						m_pGraphics->DrawElements(GL_LINE_STRIP, m_iIndexCount, GL_UNSIGNED_INT, nullptr);
						return true;
					}
					return false;
				}

				bool CVertexArrayDynamic::RenderWires()
				{
					if (m_bChanged)
					{
						UpdateBuffers();
						m_iLastRenderedPrimitives = PRIMITIVE_NONE;
						m_bChanged = false;
					}
					if (m_iLastRenderedPrimitives != PRIMITIVE_WIRE)
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
							m_pGraphics->BufferData(GL_ELEMENT_ARRAY_BUFFER, m_iIndexCount * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
							delete[] indices;
						}
						m_iLastRenderedPrimitives = PRIMITIVE_WIRE;
					}
					if (m_iIndexCount > 0)
					{
						m_pGraphics->DrawElements(GL_LINE_LOOP, m_iIndexCount, GL_UNSIGNED_INT, nullptr);
						return true;
					}
					return false;
				}

				bool CVertexArrayDynamic::RenderPolygons()
				{
					if (m_bChanged)
					{
						UpdateBuffers();
						m_iLastRenderedPrimitives = PRIMITIVE_NONE;
						m_bChanged = false;
					}
					if (m_iLastRenderedPrimitives != PRIMITIVE_POLYGON)
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
							m_pGraphics->BufferData(GL_ELEMENT_ARRAY_BUFFER, m_iIndexCount * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
							delete[] indices;
						}
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
				bool CVertexArrayDynamic::CreateBuffers(const byte count, GLuint *ids)
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

				void CVertexArrayDynamic::SetupBuffers(const byte count, GLuint *ids, const unsigned int type, const int element_count, GLuint &buffer_index)
				{
					for (byte i = 0; i < count; i++, buffer_index++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, ids[i]);
						m_pGraphics->EnableVertexAttribArray(buffer_index);
						m_pGraphics->VertexAttribPointer(buffer_index, element_count, type, GL_FALSE, 0, nullptr);
					}
				}

				void CVertexArrayDynamic::DeleteBuffers(const byte count, GLuint *ids)
				{
					if (count > 0)
					{
						m_pGraphics->DeleteBuffers(count, ids);
						for (byte i = 0; i < count; i++)
							ids[i] = 0;
					}
				}

				void CVertexArrayDynamic::UpdateBuffers()
				{
					for (byte i = 0; i < m_sFormat.Vec1fCount; i++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_aVec1fIDs[i]);
						m_pGraphics->BufferData(GL_ARRAY_BUFFER, sizeof(Vec1f) * m_aVertices.size(), m_aVec1f[i].data(), GL_DYNAMIC_DRAW);
					}
					for (byte i = 0; i < m_sFormat.Vec2fCount; i++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_aVec2fIDs[i]);
						m_pGraphics->BufferData(GL_ARRAY_BUFFER, sizeof(Vec2f) * m_aVertices.size(), m_aVec2f[i].data(), GL_DYNAMIC_DRAW);
					}
					for (byte i = 0; i < m_sFormat.Vec3fCount; i++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_aVec3fIDs[i]);
						m_pGraphics->BufferData(GL_ARRAY_BUFFER, sizeof(Vec3f) * m_aVertices.size(), m_aVec3f[i].data(), GL_DYNAMIC_DRAW);
					}
					for (byte i = 0; i < m_sFormat.Vec4fCount; i++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_aVec4fIDs[i]);
						m_pGraphics->BufferData(GL_ARRAY_BUFFER, sizeof(Vec4f) * m_aVertices.size(), m_aVec4f[i].data(), GL_DYNAMIC_DRAW);
					}
					for (byte i = 0; i < m_sFormat.Vec1iCount; i++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_aVec1iIDs[i]);
						m_pGraphics->BufferData(GL_ARRAY_BUFFER, sizeof(Vec1i) * m_aVertices.size(), m_aVec1i[i].data(), GL_DYNAMIC_DRAW);
					}
					for (byte i = 0; i < m_sFormat.Vec2iCount; i++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_aVec2iIDs[i]);
						m_pGraphics->BufferData(GL_ARRAY_BUFFER, sizeof(Vec2i) * m_aVertices.size(), m_aVec2i[i].data(), GL_DYNAMIC_DRAW);
					}
					for (byte i = 0; i < m_sFormat.Vec3iCount; i++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_aVec3iIDs[i]);
						m_pGraphics->BufferData(GL_ARRAY_BUFFER, sizeof(Vec3i) * m_aVertices.size(), m_aVec3i[i].data(), GL_DYNAMIC_DRAW);
					}
					for (byte i = 0; i < m_sFormat.Vec4iCount; i++)
					{
						m_pGraphics->BindBuffer(GL_ARRAY_BUFFER, m_aVec4iIDs[i]);
						m_pGraphics->BufferData(GL_ARRAY_BUFFER, sizeof(Vec4i) * m_aVertices.size(), m_aVec4i[i].data(), GL_DYNAMIC_DRAW);
					}
				}
			#pragma endregion
			}
		}
	}
}
#endif