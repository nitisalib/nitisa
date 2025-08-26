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
		class CPrimitivePyramid :public virtual IPrimitive, public nitisa::CModel
		{
		private:
			float m_fWidth;
			float m_fDepth;
			float m_fHeight;
			int m_iSegments;
			IControl *m_pControl;
			IVertexArray *m_pVertexArray;
			bool m_bValid;

			void UpdateGeometry();
		public:
			bool Render() override;

			CPrimitivePyramid(IControl *control);

			float const &Width{ m_fWidth };
			float const &Depth{ m_fDepth };
			float const &Height{ m_fHeight };
			int const &Segments{ m_iSegments };

			bool setWidth(const float value);
			bool setDepth(const float value);
			bool setHeight(const float value);
			bool setSize(const float width, const float depth, const float height);
			bool setSegments(const int value);

			void FreeResources();
		};
	}
}