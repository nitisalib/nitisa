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
		class CPrimitiveCone :public virtual IPrimitive, public nitisa::CModel
		{
		private:
			float m_fRadius1;
			float m_fRadius2;
			float m_fHeight;
			int m_iSides;
			int m_iCapSegments;
			int m_iHeightSegments;
			IControl *m_pControl;
			IVertexArray *m_pVertexArray;
			bool m_bValid;

			void UpdateGeometry();
		public:
			bool Render() override;

			CPrimitiveCone(IControl *control);

			float const &Radius1{ m_fRadius1 };
			float const &Radius2{ m_fRadius2 };
			float const &Height{ m_fHeight };
			int const &Sides{ m_iSides };
			int const &CapSegments{ m_iCapSegments };
			int const &HeightSegments{ m_iHeightSegments };

			bool setRadius1(const float value);
			bool setRadius2(const float value);
			bool setHeight(const float value);
			bool setSides(const int value);
			bool setSize(const float radius1, const float radius2, const float height, const int sides);
			bool setCapSegments(const int value);
			bool setHeightSegments(const int value);
			bool setSegments(const int cap, const int height);

			void FreeResources();
		};
	}
}