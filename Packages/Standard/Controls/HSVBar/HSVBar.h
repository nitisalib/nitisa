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
#include "Nitisa/Math/Point.h"
#include "../IHSVBar.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class IHSVPlane;

		class CHSVBarService;

		class CHSVBar :public virtual IHSVBar, public CControl
		{
			friend CHSVBarService;
		private:
			int m_iHue;
			float m_fPickerSize;
			Color m_sPickerColor;
			Color m_sPickerBorderColor;
			IHSVPlane *m_pHSVPlane;

			ITexture *m_pCanvas;

			void UpdateFromStyle(IStyle *style);
			void Render();
		public:
			void(*OnChange)(IControl *sender); // Event called when color changed by user

			// IControl methods
			void Refresh(const bool refresh_children) override;

			int getHue() override;
			IHSVPlane *getHSVPlane() override;

			bool setDPI(const Point &value) override;
			bool setHue(const int value) override;
			bool setHSVPlane(IHSVPlane *value) override;

			CHSVBar();
			CHSVBar(IControl *parent);
			CHSVBar(IForm *parent);

			// Return layout properties
			float getPickerSize() const;
			Color getPickerColor() const;
			Color getPickerBorderColor() const;

			// Set layout properties
			bool setPickerSize(const float value);
			bool setPickerColor(const Color &value);
			bool setPickerBorderColor(const Color &value);
		};
	}
}