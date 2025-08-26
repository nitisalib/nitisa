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
		class CPrimitiveSphere :public virtual IPrimitive, public nitisa::CModel
		{
		private:
			float m_fRadius;
			int m_iSides;
			int m_iYSides;
			IControl *m_pControl;
			IVertexArray *m_pVertexArray;
			bool m_bValid;

			void UpdateGeometry();
		public:
			bool Render() override;

			CPrimitiveSphere(IControl *control);

			float const &Radius{ m_fRadius };
			int const &Sides{ m_iSides };
			int const &YSides{ m_iYSides };

			bool setRadius(const float value);
			bool setSides(const int value);
			bool setYSides(const int value);
			bool setSize(const float radius, const int sides, const int y_sides);

			void FreeResources();
		};
	}
}