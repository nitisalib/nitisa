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
#include "VertexArrayDynamic.h"

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
			namespace opengl45
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
					m_pGraphics->CreateVertexArrays(1, reinterpret_cast<GLuint*>(&m_hHandle));
					if (!(*reinterpret_cast<GLuint*>(&m_hHandle)))
						return;
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
					m_pGraphics->CreateBuffers(1, &m_hIndices);
					if (!m_hIndices)
						return;
					GLuint buffer_index{ 0 };
					SetupBuffers(m_sFormat.Vec1fCount, m_aVec1fIDs, sizeof(Vec1f), GL_FLOAT, 1, buffer_index);
					SetupBuffers(m_sFormat.Vec2fCount, m_aVec2fIDs, sizeof(Vec2f), GL_FLOAT, 2, buffer_index);
					SetupBuffers(m_sFormat.Vec3fCount, m_aVec3fIDs, sizeof(Vec3f), GL_FLOAT, 3, buffer_index);
					SetupBuffers(m_sFormat.Vec4fCount, m_aVec4fIDs, sizeof(Vec4f), GL_FLOAT, 4, buffer_index);
					SetupBuffers(m_sFormat.Vec1iCount, m_aVec1iIDs, sizeof(Vec1i), GL_INT, 1, buffer_index);
					SetupBuffers(m_sFormat.Vec2iCount, m_aVec2iIDs, sizeof(Vec2i), GL_INT, 2, buffer_index);
					SetupBuffers(m_sFormat.Vec3iCount, m_aVec3iIDs, sizeof(Vec3i), GL_INT, 3, buffer_index);
					SetupBuffers(m_sFormat.Vec4iCount, m_aVec4iIDs, sizeof(Vec4i), GL_INT, 4, buffer_index);
					m_pGraphics->VertexArrayVertexBuffer(*reinterpret_cast<GLuint*>(&m_hHandle), buffer_index, m_hIndices, 0, sizeof(unsigned int));
					m_pGraphics->VertexArrayAttribFormat(*reinterpret_cast<GLuint*>(&m_hHandle), buffer_index, 1, GL_UNSIGNED_INT, GL_FALSE, 0);
					m_pGraphics->VertexArrayElementBuffer(*reinterpret_cast<GLuint*>(&m_hHandle), m_hIndices);
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
							m_pGraphics->NamedBufferData(m_hIndices, m_iIndexCount * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
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
							m_pGraphics->NamedBufferData(m_hIndices, m_iIndexCount * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
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
							m_pGraphics->NamedBufferData(m_hIndices, m_iIndexCount * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
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
							m_pGraphics->NamedBufferData(m_hIndices, m_iIndexCount * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
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
						m_pGraphics->CreateBuffers(count, ids);
						for (byte i = 0; i < count; i++)
							if (!ids[i])
								return false;
					}
					return true;
				}

				void CVertexArrayDynamic::SetupBuffers(const byte count, GLuint *ids, const size_t size, const unsigned int type, const int element_count, GLuint &buffer_index)
				{
					for (byte i = 0; i < count; i++, buffer_index++)
					{
						m_pGraphics->EnableVertexArrayAttrib(*reinterpret_cast<GLuint*>(&m_hHandle), buffer_index);
						m_pGraphics->VertexArrayAttribBinding(*reinterpret_cast<GLuint*>(&m_hHandle), buffer_index, buffer_index);
						m_pGraphics->VertexArrayVertexBuffer(*reinterpret_cast<GLuint*>(&m_hHandle), buffer_index, ids[i], 0, (unsigned int)size);
						m_pGraphics->VertexArrayAttribFormat(*reinterpret_cast<GLuint*>(&m_hHandle), buffer_index, element_count, type, GL_FALSE, 0);
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
						m_pGraphics->NamedBufferData(m_aVec1fIDs[i], sizeof(Vec1f) * m_aVertices.size(), m_aVec1f[i].data(), GL_DYNAMIC_DRAW);
					for (byte i = 0; i < m_sFormat.Vec2fCount; i++)
						m_pGraphics->NamedBufferData(m_aVec2fIDs[i], sizeof(Vec2f) * m_aVertices.size(), m_aVec2f[i].data(), GL_DYNAMIC_DRAW);
					for (byte i = 0; i < m_sFormat.Vec3fCount; i++)
						m_pGraphics->NamedBufferData(m_aVec3fIDs[i], sizeof(Vec3f) * m_aVertices.size(), m_aVec3f[i].data(), GL_DYNAMIC_DRAW);
					for (byte i = 0; i < m_sFormat.Vec4fCount; i++)
						m_pGraphics->NamedBufferData(m_aVec4fIDs[i], sizeof(Vec4f) * m_aVertices.size(), m_aVec4f[i].data(), GL_DYNAMIC_DRAW);
					for (byte i = 0; i < m_sFormat.Vec1iCount; i++)
						m_pGraphics->NamedBufferData(m_aVec1iIDs[i], sizeof(Vec1i) * m_aVertices.size(), m_aVec1i[i].data(), GL_DYNAMIC_DRAW);
					for (byte i = 0; i < m_sFormat.Vec2iCount; i++)
						m_pGraphics->NamedBufferData(m_aVec2iIDs[i], sizeof(Vec2i) * m_aVertices.size(), m_aVec2i[i].data(), GL_DYNAMIC_DRAW);
					for (byte i = 0; i < m_sFormat.Vec3iCount; i++)
						m_pGraphics->NamedBufferData(m_aVec3iIDs[i], sizeof(Vec3i) * m_aVertices.size(), m_aVec3i[i].data(), GL_DYNAMIC_DRAW);
					for (byte i = 0; i < m_sFormat.Vec4iCount; i++)
						m_pGraphics->NamedBufferData(m_aVec4iIDs[i], sizeof(Vec4i) * m_aVertices.size(), m_aVec4i[i].data(), GL_DYNAMIC_DRAW);
				}
			#pragma endregion
			}
		}
	}
}
#endif