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
		class CPrimitiveDisk :public virtual IPrimitive, public nitisa::CModel
		{
		private:
			float m_fOuterRadius;
			float m_fInnerRadius;
			int m_iSides;
			int m_iSegments;
			IControl *m_pControl;
			IVertexArray *m_pVertexArray;
			bool m_bValid;

			void UpdateGeometry();
		public:
			bool Render() override;

			CPrimitiveDisk(IControl *control);

			float const &OuterRadius{ m_fOuterRadius };
			float const &InnerRadius{ m_fInnerRadius };
			int const &Sides{ m_iSides };
			int const &Segments{ m_iSegments };

			bool setOuterRadius(const float value);
			bool setInnerRadius(const float value);
			bool setSides(const int value);
			bool setSegments(const int value);
			bool setSize(const float outer_radius, const float inner_radius, const int sides);

			void FreeResources();
		};
	}
}