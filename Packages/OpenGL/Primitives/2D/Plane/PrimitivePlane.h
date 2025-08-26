// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Model.h"
#include "Nitisa/Interfaces/IPrimitive.h"

namespace nitisa
{
	class IControl;
	class IVertexArray;

	namespace opengl
	{
		class CPrimitivePlane :public virtual IPrimitive, public nitisa::CModel
		{
		private:
			float m_fWidth;
			float m_fDepth;
			int m_iWidthSegments;
			int m_iDepthSegments;
			IControl *m_pControl;
			IVertexArray *m_pVertexArray;
			bool m_bValid;

			void UpdateGeometry();
		public:
			bool Render() override;

			CPrimitivePlane(IControl *control);

			float const &Width{ m_fWidth };
			float const &Depth{ m_fDepth };
			int const &WidthSegments{ m_iWidthSegments };
			int const &DepthSegments{ m_iDepthSegments };

			bool setWidth(const float value);
			bool setDepth(const float value);
			bool setSize(const float width, const float depth);
			bool setWidthSegments(const int value);
			bool setDepthSegments(const int value);
			bool setSegments(const int width, const int depth);

			void FreeResources();
		};
	}
}