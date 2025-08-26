// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/VertexArray.h"
#include "Nitisa/Core/VertexFormat.h"
#include "../../OpenGL/ngl.h"

namespace nitisa
{
	class COpenGL;

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
				class CVertexArrayImmutable :public CVertexArray
				{
					friend gles31d::CRenderer;
					friend gles31r::CRenderer;
				private:
					COpenGL *m_pGraphics;
					GLuint m_aVec1fIDs[8];
					GLuint m_aVec2fIDs[8];
					GLuint m_aVec3fIDs[8];
					GLuint m_aVec4fIDs[8];
					GLuint m_aVec1iIDs[8];
					GLuint m_aVec2iIDs[8];
					GLuint m_aVec3iIDs[8];
					GLuint m_aVec4iIDs[8];
					GLuint m_hIndices;
					bool m_bValid;
					GLsizei m_iIndexCount;

					bool CreateBuffers(const byte count, GLuint *ids);
					void SetupBuffers(const byte count, GLuint *ids, const size_t size, const unsigned int type, const int element_count, GLuint &buffer_index);
					void DeleteBuffers(const byte count, GLuint *ids);
					void UpdateBuffers();
					void Initialize(const bool has_polygons);
				protected:
					void BeforeRelease() override;

					CVertexArrayImmutable(COpenGL *graphics, const VertexFormat &format, const size_t vertex_count);
					CVertexArrayImmutable(COpenGL *graphics, const VertexFormat &format, const size_t polygon_count, const size_t polygon_size);

					CVertexArrayImmutable(const CVertexArrayImmutable&) = delete;
					CVertexArrayImmutable(CVertexArrayImmutable&&) = delete;
					CVertexArrayImmutable &operator=(const CVertexArrayImmutable&) = delete;
					CVertexArrayImmutable &operator=(CVertexArrayImmutable&&) = delete;

					static CVertexArrayImmutable *Create(COpenGL *graphics, const VertexFormat &format, const size_t vertex_count);
					static CVertexArrayImmutable *Create(COpenGL *graphics, const VertexFormat &format, const size_t polygon_count, const size_t polygon_size);
				public:
					// IVertexArray rendering
					bool RenderPoints() override;
					bool RenderLines() override;
					bool RenderWires() override;
					bool RenderPolygons() override;
				};
			}
		}
	}
}
#endif