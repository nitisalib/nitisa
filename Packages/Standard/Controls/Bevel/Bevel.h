// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Image/Color.h"
#include "../IBevel.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class ITexture;

	namespace standard
	{
		class CBevelService;

		class CBevel :public virtual IBevel, public CControl
		{
			friend CBevelService;
		private:
			BevelKind m_eBevelKind;
			BevelStyle m_eBevelStyle;
			Color m_sColorLowered;
			Color m_sColorRaised;
			float m_fBevelWidth;

			ITexture *m_pCanvas;

			void UpdateFromStyle(IStyle *style);
			void Render();
			void RenderBox(IRenderer *renderer, const Color &c1, const Color &c2);
			void RenderFrame(IRenderer *renderer, const Color &c1, const Color &c2);
			void RenderLeftEdge(IRenderer *renderer, const Color &c1, const Color &c2);
			void RenderTopEdge(IRenderer *renderer, const Color &c1, const Color &c2);
			void RenderRightEdge(IRenderer *renderer, const Color &c1, const Color &c2);
			void RenderBottomEdge(IRenderer *renderer, const Color &c1, const Color &c2);
		public:
			// IControl methods
			void Refresh(const bool refresh_children) override;

			BevelKind getBevelKind() override;
			BevelStyle getBevelStyle() override;

			bool setDPI(const Point &value) override;
			bool setBevelKind(const BevelKind value) override;
			bool setBevelStyle(const BevelStyle value) override;

			CBevel();
			CBevel(IForm *parent);
			CBevel(IControl *parent);

			Color getColorLowered(); // Return first bevel color
			Color getColorRaised(); // Return second bevel color
			float getBevelWidth(); // Return bevel width

			bool setColorLowered(const Color &value); // Set first bevel color
			bool setColorRaised(const Color &value); // Set second bevel color
			bool setBevelWidth(const float value); // Set bevel width
		};
	}
}