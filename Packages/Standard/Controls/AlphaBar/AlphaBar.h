// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Math/Point.h"
#include "../IAlphaBar.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CAlphaBarService;

		class CAlphaBar :public virtual IAlphaBar, public CControl
		{
			friend CAlphaBarService;
		private:
			int m_iAlpha;
			float m_fPickerSize;
			Color m_sPickerColor;
			Color m_sPickerBorderColor;
			Color m_sCheckerColor1;
			Color m_sCheckerColor2;
			Color m_sBackgroundColor;
			Color m_sForegroundColor1;
			Color m_sForegroundColor2;
			float m_fCheckerSize;

			ITexture *m_pCanvas;

			void UpdateFromStyle(IStyle *style);
			void Render();
		public:
			void(*OnChange)(IControl *sender); // Event called when color changed by user

			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			int getAlpha() override;

			bool setAlpha(const int value) override;

			CAlphaBar();
			CAlphaBar(IControl *parent);
			CAlphaBar(IForm *parent);

			// Return layout properties
			float getPickerSize() const;
			Color getPickerColor() const;
			Color getPickerBorderColor() const;
			Color getCheckerColor1() const;
			Color getCheckerColor2() const;
			Color getBackgroundColor() const; // If alpha channel of background color is 0, then checker background will be drawn
			Color getForegroundColor1() const;
			Color getForegroundColor2() const;
			float getCheckerSize() const;

			// Set layout properties
			bool setPickerSize(const float value);
			bool setPickerColor(const Color &value);
			bool setPickerBorderColor(const Color &value);
			bool setCheckerColor1(const Color &value);
			bool setCheckerColor2(const Color &value);
			bool setBackgroundColor(const Color &value);
			bool setForegroundColor1(const Color &value);
			bool setForegroundColor2(const Color &value);
			bool setCheckerSize(const float value);
		};
	}
}