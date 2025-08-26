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
#include "../IHSVPlane.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CHSVPlaneService;

		class CHSVPlane :public virtual IHSVPlane, public CControl
		{
			friend CHSVPlaneService;
		private:
			int m_iHue;
			float m_fSaturation;
			float m_fValue;
			float m_fPickerRadius;
			float m_fPickerBorderWidth;
			float m_fPickerBorderRadius;
			Color m_sPickerBorderColor;
			Color m_sPickerBorderColorInv;
			Color m_sPickerBackgroundColor;
			Color m_sPickerBackgroundColorInv;

			ITexture *m_pCanvas;

			void UpdateFromStyle(IStyle *style);
			void Render();
		public:
			void(*OnChange)(IControl *sender); // Event called when color changed by user

			// IControl methods
			void Refresh(const bool refresh_children) override;

			int getHue() override;
			float getSaturation() override;
			float getValue() override;

			bool setDPI(const Point &value) override;
			bool setHue(const int value) override;
			bool setSaturation(const float value) override;
			bool setValue(const float value) override;

			CHSVPlane();
			CHSVPlane(IControl *parent);
			CHSVPlane(IForm *parent);

			// Return layout properties
			float getPickerRadius() const;
			float getPickerBorderWidth() const;
			float getPickerBorderRadius() const;
			Color getPickerBorderColor() const;
			Color getPickerBorderColorInv() const;
			Color getPickerBackgroundColor() const;
			Color getPickerBackgroundColorInv() const;

			// Set layout properties
			bool setPickerRadius(const float value);
			bool setPickerBorderWidth(const float value);
			bool setPickerBorderRadius(const float value);
			bool setPickerBorderColor(const Color &value);
			bool setPickerBorderColorInv(const Color &value);
			bool setPickerBackgroundColor(const Color &value);
			bool setPickerBackgroundColorInv(const Color &value);
		};
	}
}