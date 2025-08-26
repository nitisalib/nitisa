// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Align.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/TextAlign.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IFormStyleSolid.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CFormStyleSolidService;

		class CFormStyleSolid :public virtual IFormStyleSolid, public CControl
		{
			friend CFormStyleSolidService;
		public:
			enum class ButtonState // Possible button states
			{
				Normal, // Normal
				Hovered, // Mouse pointer is over a button
				Active, // Mouse button was down and not release yet over a button
				Disabled // Button is disabled
			};
		private:
			enum class Element
			{
				None,
				LeftBorder,
				TopBorder,
				RightBorder,
				BottomBorder,
				LeftTopCorner,
				RightTopCorner,
				LeftBottomCorner,
				RightBottomCorner,
				Header,
				BtnMinimize,
				BtnRestore,
				BtnClose
			};

			struct BUTTON
			{
				bool Visible;
				bool Enabled;
				RectF BorderWidth[(int)ButtonState::Disabled + 1];
				RectF BorderRadius[(int)ButtonState::Disabled + 1];
				nitisa::BorderColor BorderColor[(int)ButtonState::Disabled + 1];
				Color BackgroundColor[(int)ButtonState::Disabled + 1];
			};
		private:
			bool m_bShowCaption;
			float m_fCaptionHeight; // Additional to top border
			PointF m_sCaptionPadding;
			RectF m_sBorderWidth;
			BorderColor m_sBorderColor;
			Color m_sCaptionBackgroundColor;
			TextAlign m_eCaptionAlign;
			BUTTON m_sBtnMinimize;
			BUTTON m_sBtnRestore;
			BUTTON m_sBtnClose;

			ITexture *m_pCanvasHeader;
			Element m_eHovered;
			Element m_eDown;

			ButtonState getBtnMinimizeState();
			ButtonState getBtnRestoreState();
			ButtonState getBtnCloseState();
			Element getElement(const PointF &pos);
			bool UpdateHoveredElement(const PointF &position);
			bool DownAllowed();
			ITexture *FindIcon(IRenderer *renderer, const String &name, RectF &part);
			void UpdateFromStyle(IStyle *style);
			void Render();
			void RenderCaption(IRenderer *renderer);
			void RenderBtn(IRenderer *renderer, const BUTTON &btn, const ButtonState state, const String &name, float &x);
		public:
			IControl *getControl(const int index) override;
			IControl *getControl(const String &name) override;
			IControl *getControl(const PointF &position) override;
			RectF getRect() override;
			RectF getClientRect() override;
			RectF getRenderRect() override;
			CursorType getCursor() override;

			bool setAlign(const Align value) override; // Not supported
			bool setConstraints(const RectF &value) override; // Not supported
			bool setSize(const PointF &value) override; // Not supported
			bool setHintText(const String &value) override; // Not supported
			bool setVisible(const bool value) override; // Not supported
			bool setEnabled(const bool value) override; // Not supported
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			CFormStyleSolid(); // Constructor
			CFormStyleSolid(IForm *parent); // Construct and place onto a form

			bool isShowCaption() const; // Return whether caption should be shown or not
			RectF getBorderWidth() const; // Return border widths
			float getCaptionHeight() const; // Return caption height
			PointF getCaptionPadding() const;
			BorderColor getBorderColor() const; // Return border colors
			Color getCaptionBackgroundColor() const; // Return caption background color
			TextAlign getCaptionAlign() const;
			// Return minimize button settings
			bool isBtnMinimizeVisible() const;
			bool isBtnMinimizeEnabled() const;
			RectF getBtnMinimizeBorderWidth(const ButtonState state) const;
			RectF getBtnMinimizeBorderRadius(const ButtonState state) const;
			BorderColor getBtnMinimizeBorderColor(const ButtonState state) const;
			Color getBtnMinimizeBackgroundColor(const ButtonState state) const;
			// Return restore/maximize button settings
			bool isBtnRestoreVisible() const;
			bool isBtnRestoreEnabled() const;
			RectF getBtnRestoreBorderWidth(const ButtonState state) const;
			RectF getBtnRestoreBorderRadius(const ButtonState state) const;
			BorderColor getBtnRestoreBorderColor(const ButtonState state) const;
			Color getBtnRestoreBackgroundColor(const ButtonState state) const;
			// Return close button settings
			bool isBtnCloseVisible() const;
			bool isBtnCloseEnabled() const;
			RectF getBtnCloseBorderWidth(const ButtonState state) const;
			RectF getBtnCloseBorderRadius(const ButtonState state) const;
			BorderColor getBtnCloseBorderColor(const ButtonState state) const;
			Color getBtnCloseBackgroundColor(const ButtonState state) const;

			bool setShowCaption(const bool value); // Set whether caption should be shown or not
			bool setBorderWidth(const RectF &value); // Set border widths
			bool setCaptionHeight(const float value); // Set caption height
			bool setCaptionPadding(const PointF &value);
			bool setBorderColor(const BorderColor &value); // Set border colors
			bool setCaptionBackgroundColor(const Color &value); // Set caption background color
			bool setCaptionAlign(const TextAlign value);
			// Set minimize button settings
			bool setBtnMinimizeVisible(const bool value);
			bool setBtnMinimizeEnabled(const bool value);
			bool setBtnMinimizeBorderWidth(const ButtonState state, const RectF &value);
			bool setBtnMinimizeBorderRadius(const ButtonState state, const RectF &value);
			bool setBtnMinimizeBorderColor(const ButtonState state, const BorderColor &value);
			bool setBtnMinimizeBackgroundColor(const ButtonState state, const Color &value);
			// Set restore/maximize button settings
			bool setBtnRestoreVisible(const bool value);
			bool setBtnRestoreEnabled(const bool value);
			bool setBtnRestoreBorderWidth(const ButtonState state, const RectF &value);
			bool setBtnRestoreBorderRadius(const ButtonState state, const RectF &value);
			bool setBtnRestoreBorderColor(const ButtonState state, const BorderColor &value);
			bool setBtnRestoreBackgroundColor(const ButtonState state, const Color &value);
			// Set close button settings
			bool setBtnCloseVisible(const bool value);
			bool setBtnCloseEnabled(const bool value);
			bool setBtnCloseBorderWidth(const ButtonState state, const RectF &value);
			bool setBtnCloseBorderRadius(const ButtonState state, const RectF &value);
			bool setBtnCloseBorderColor(const ButtonState state, const BorderColor &value);
			bool setBtnCloseBackgroundColor(const ButtonState state, const Color &value);
		};
	}
}