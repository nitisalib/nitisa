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
		class CPrimitiveTorus :public virtual IPrimitive, public nitisa::CModel
		{
		private:
			float m_fRadius1;
			float m_fRadius2;
			int m_iSides1;
			int m_iSides2;
			IControl *m_pControl;
			IVertexArray *m_pVertexArray;
			bool m_bValid;

			void UpdateGeometry();
		public:
			bool Render() override;

			CPrimitiveTorus(IControl *control);

			float const &Radius1{ m_fRadius1 };
			float const &Radius2{ m_fRadius2 };
			int const &Sides1{ m_iSides1 };
			int const &Sides2{ m_iSides2 };

			bool setRadius1(const float value);
			bool setRadius2(const float value);
			bool setSides1(const int value);
			bool setSides2(const int value);
			bool setSize(const float radius1, const float radius2, const int sides1, const int sides2);

			void FreeResources();
		};
	}
}