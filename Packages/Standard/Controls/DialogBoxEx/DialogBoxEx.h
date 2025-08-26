// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Align.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Core/DialogBox.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/TextAlign.h"
#include "Nitisa/Core/VerticalAlign.h"
#include "Nitisa/Core/WindowState.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Image/Image.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Interfaces/ITimerListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "Nitisa/Math/Transform.h"
#include "../IDialogBoxEx.h"

namespace nitisa
{
	class IControl;
	class IDialogBoxService;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;

	struct Block;

	namespace standard
	{
		class IImageList;

		class CDialogBoxExService;

		class CDialogBoxEx :public virtual IDialogBoxEx, public CDialogBox
		{
			friend CDialogBoxExService;
		public:
			enum class State // States of elements
			{
				Normal, // Normal state
				Active, // Dialog box is active
				Modal, // Dialog box is modal(and most probably active as well)
				Blinking, // Blinking
				Disabled, // Disabled
			};

			enum class ButtonState // Button states
			{
				Normal, // Normal
				Hovered, // Mouse over button
				Down, // Mouse was down over button
				DownHovered,  // Mouse was down over button and is currently over it
				Disabled // Disabled
			};
		private:
			enum class Element
			{
				None,
				LeftTopCorner,
				RightTopCorner,
				RightBottomCorner,
				LeftBottomCorner,
				LeftBorder,
				TopBorder,
				RightBorder,
				BottomBorder,
				Caption,
				ButtonMinimize,
				ButtonMaximize,
				ButtonRestore,
				ButtonClose,
				Icon,
				Client
			};

			class CTimerListener :public virtual ITimerListener
			{
			private:
				CDialogBoxEx *m_pControl;
			public:
				void NotifyOnTimer(const PlatformHandle id) override;

				CTimerListener(CDialogBoxEx *control);
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CDialogBoxEx *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CDialogBoxEx *control);
			};
		private:
			CGradientListener m_cGradientListener;
			WindowState m_eState;
			bool m_bHasCloseBox;
			bool m_bHasMinimizeBox;
			bool m_bHasMaximizeBox;
			bool m_bHasSizeBox;
			bool m_bHasSystemMenu;
			bool m_bHasBorder;
			bool m_bHasCaption;
			bool m_bIsPopup;

			Color m_sBackgroundColor;
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];

			String m_sCaption;
			float m_fCaptionHeight;
			RectF m_sCaptionPadding;
			TextAlign m_eCaptionHorizontalAlign;
			VerticalAlign m_eCaptionVerticalAlign;
			Color m_aCaptionColor[(int)State::Disabled + 1];
			Gradient m_aCaptionGradient[(int)State::Disabled + 1];
			Color m_aCaptionTextColor[(int)State::Disabled + 1];

			RectF m_aBorderRadius[(int)WindowState::Hidden + 1];
			RectF m_sResizeBorderWidth;
			RectF m_sMargin;
			RectF m_aRimWidth[(int)WindowState::Hidden + 1];
			RectF m_sPadding;
			BorderColor m_aBorderColor[(int)State::Disabled + 1];

			PointF m_sButtonSize;
			RectF m_sButtonPadding;
			RectF m_sButtonBorderWidth;
			RectF m_sButtonBorderRadius;
			BorderColor m_aButtonBorderColor[(int)ButtonState::Disabled + 1];
			Color m_aButtonBackgroundColor[(int)ButtonState::Disabled + 1];
			Gradient m_aButtonBackgroundGradient[(int)ButtonState::Disabled + 1];

			IImageList *m_pButtonIcons;
			int m_aCloseIconIndex[(int)ButtonState::Disabled + 1];
			int m_aMinimizeIconIndex[(int)ButtonState::Disabled + 1];
			int m_aMaximizeIconIndex[(int)ButtonState::Disabled + 1];
			int m_aRestoreIconIndex[(int)ButtonState::Disabled + 1];

			bool m_bUseMask;
			bool m_bUseDefaultCloseIcon;
			bool m_bUseDefaultMinimizeIcon;
			bool m_bUseDefaultMaximizeIcon;
			bool m_bUseDefaultRestoreIcon;

			Color m_aShadowColor[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];

			float m_fMinimizedWidth;

			RectF m_sIconPadding;
			IImageList *m_pIcons;
			int m_aIconIndex[(int)State::Disabled + 1];

			float m_fBlinkInterval;
			int m_iBlinkCount;

			ITexture *m_pCanvas;
			ITexture *m_pMask;
			bool m_bIgnoreGradient;
			PlatformHandle m_hTimerBlink;
			Element m_eHoveredElement;
			Element m_eDownElement;
			int m_iBlinkCounter;
			PointF m_sNormalSize;
			Transform m_sNormalTransform;
			WindowState m_eHideState;
			CTimerListener m_cTimerListener;

			void UpdateFromStyle(IStyle *style);
			Element getElement();
			Element getElement(const PointF &p);
			void getButtonRects(RectF &close, RectF &maximize, RectF &minimize, RectF &restore);
			RectF getIconRect();
			RectF getCaptionRect(const RectF &close, const RectF &maximize, const RectF &minimize, const RectF &restore);
			ButtonState getButtonState(const Element el);
			ITexture *getButtonIcon(IRenderer *renderer, const bool use_default, const Image &default_icon, IImageList *icons, const int icon_index);
			bool UpdateHoveredElement();
			bool UpdateHoveredElement(const PointF &p);
			float CalculateMinimizedXPosition();
			float CalculateMinimizedYPosition();
			float CalculateMinimizedHeight();
			float CalculateCaptionHeight();
			RectF CalculateResizeBorderWidth();
			RectF CalculateMargin();
			RectF CalculateRimWidth();
			void CalculateBound(IControl *parent, RectF &bound, const Mat4f &m);
			void HandleAttach();
			void UpdateTransformControls();
			void FitInParent();
			void Render(IRenderer *renderer, const Mat4f &matrix);
			void RenderCaptionBackground(IRenderer *renderer, const RectF &rect, const RectF &rim, const State state, Block *block);
			void RenderIcon(IRenderer *renderer, const State state, const PointF &disp, const Block *block);
			void RenderCaption(IRenderer *renderer, const State state, const PointF &disp, const RectF &close, const RectF &maximize, const RectF &minimize, const RectF &restore, Block *block);
			void RenderButtons(IRenderer *renderer, const PointF &disp, const RectF &close, const RectF &maximize, const RectF &minimize, const RectF &restore, Block *block);
			void RenderButton(IRenderer *renderer, ITexture *icon, const RectF &rect, const BorderColor &border_color, const Color &background_color, Gradient &background_gradient, ITexture **clip,
				const Block *block);
			void RenderMask(IRenderer *renderer);
		public:
			// IControl getters
			RectF getClientRect() override;
			RectF getRenderRect() override;
			CursorType getCursor() override;

			// IControl setters
			bool setAlign(const Align value) override; // Not allowed
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// IDialogBox getters
			Color getBackgroundColor() override;
			String getCaption() override;
			WindowState getState() override;
			RectF getBorderWidth() override; // Return padding
			bool hasCloseBox() override;
			bool hasMaximizeBox() override;
			bool hasMinimizeBox() override;
			bool hasSizeBox() override;
			bool hasSystemMenu() override;
			bool hasBorder() override;
			bool hasCaption() override;
			bool isPopup() override;

			// IDialogBox setters
			bool setBackgroundColor(const Color &value) override;
			bool setCaption(const String &value) override;
			bool setClientSize(const Point &value) override; // Set notmal state and required size so that controls client size becomes equal to specified one
			bool setState(const WindowState value) override;
			bool setBorderWidth(const RectF &value) override; // Set padding
			bool setHasCloseBox(const bool value) override;
			bool setHasMaximizeBox(const bool value) override;
			bool setHasMinimizeBox(const bool value) override;
			bool setHasSizeBox(const bool value) override;
			bool setHasSystemMenu(const bool value) override;
			bool setHasBorder(const bool value) override;
			bool setHasCaption(const bool value) override;
			bool setIsPopup(const bool value) override;

			// IDialogBox actions
			bool Maximize() override;
			bool Minimize() override;
			bool Restore() override;
			bool Hide() override;

			// IDialogBoxEx actions
			void AutoResize(const bool transform) override;

			CDialogBoxEx(const String &class_name, const bool accept_form, const bool accept_control, const bool accept_focus, const bool tab_stop, const Point &design_dpi, IDialogBoxService *service);
			CDialogBoxEx();
			CDialogBoxEx(IControl *parent);
			CDialogBoxEx(IForm *parent);

			State getControlState(); // Return current control state
			bool isUseMask() const; // Return whether mask should be used to clip child controls
			Gradient *getBackgroundGradient(const State state); // Return background gradient depending on state
			float getCaptionHeight() const; // Return caption area height
			RectF getCaptionPadding() const; // Return caption padding on caption area
			TextAlign getCaptionHorizontalAlign() const; // Return caption horizontal alignment
			VerticalAlign getCaptionVerticalAlign() const; // Return caption vertical alignment
			Color getCaptionColor(const State state) const; // Return caption color area background depending on state
			Gradient *getCaptionGradient(const State state); // Return caption area background gradient depending on state
			Color getCaptionTextColor(const State state) const; // Return caption color depending on state
			RectF getBorderRadius(const WindowState state) const; // Return border radius depending on state
			RectF getResizeBorderWidth() const; // Return resize border width. Border widthes used to resize control. Used only in wsNormal state
			RectF getMargin() const; // Return margin which is blank space outside control
			RectF getRimWidth(const WindowState state) const; // Return border width depending on state
			RectF getPadding() const; // Return padding
			BorderColor getBorderColor(const State state) const; // Return border color depending on state
			PointF getButtonSize() const; // Return button size
			RectF getButtonPadding() const; // Return button padding
			RectF getButtonBorderWidth() const; // Return button border width
			RectF getButtonBorderRadius() const; // Return button border radius
			BorderColor getButtonBorderColor(const ButtonState state) const; // Return button border color depending on state
			Color getButtonBackgroundColor(const ButtonState state) const; // Return button background color depending on state
			Gradient *getButtonBackgroundGradient(const ButtonState state); // Return button background gradient depending on state
			IImageList *getButtonIcons(); // Return button icons image list
			int getCloseIconIndex(const ButtonState state) const; // Return index of close icon in button image list depending on state
			int getMinimizeIconIndex(const ButtonState state) const; // Return index of minimize icon in button image list depending on state
			int getMaximizeIconIndex(const ButtonState state) const; // Return index of maximize icon in button image list depending on state
			int getRestoreIconIndex(const ButtonState state) const; // Return index of restore icon in button image list depending on state
			bool isUseDefaultCloseIcon() const; // Return whether default close button icon should be drawn in case of there is no icon in attached button's icon list or no such list attached
			bool isUseDefaultMinimizeIcon() const; // Return whether default minimize button icon should be drawn in case of there is no icon in attached button's icon list or no such list attached
			bool isUseDefaultMaximizeIcon() const; // Return whether default maximize button icon should be drawn in case of there is no icon in attached button's icon list or no such list attached
			bool isUseDefaultRestoreIcon() const; // Return whether default restore button icon should be drawn in case of there is no icon in attached button's icon list or no such list attached
			Color getShadowColor(const State state) const; // Return shadow color depending on state
			int getShadowRadius(const State state) const; // Return shadow radius depending on state
			PointF getShadowShift(const State state) const; // Return shadow shift depending on state
			float getMinimizedWidth() const; // Return control width in minimized state
			RectF getIconPadding() const; // Return system icon padding
			IImageList *getIcons(); // Return image list where system icon is
			int getIconIndex(const State state) const; // Return index of system icon in system icon image list
			float getBlinkInterval() const; // Return blinking interval
			int getBlinkCount() const; // Return number of blinks. <=0 means no blinking

			bool setUseMask(const bool value); // Set whether mask should be used to clip child controls
			bool setCaptionHeight(const float value); // Set caption area height
			bool setCaptionPadding(const RectF &value); // Set caption padding on caption area
			bool setCaptionHorizontalAlign(const TextAlign value); // Set caption horizontal alignment
			bool setCaptionVerticalAlign(const VerticalAlign value); // Set caption vertical alignment
			bool setCaptionColor(const State state, const Color &value); // Set caption color area background depending on state
			bool setCaptionTextColor(const State state, const Color &value); // Set caption color depending on state
			bool setBorderRadius(const WindowState state, const RectF &value); // Set border radius depending on state
			bool setResizeBorderWidth(const RectF &value); // Set resize border width. Border widthes used to resize control. Used only in wsNormal state
			bool setMargin(const RectF &value); // Set margin which is blank space outside control
			bool setRimWidth(const WindowState state, const RectF &value); // Set border width depending on state
			bool setPadding(const RectF &value); // Set padding
			bool setBorderColor(const State state, const BorderColor &value); // Set border color depending on state
			bool setButtonSize(const PointF &value); // Set button size
			bool setButtonPadding(const RectF &value); // Set button padding
			bool setButtonBorderWidth(const RectF &value); // Set button border width
			bool setButtonBorderRadius(const RectF &value); // Set button border radius
			bool setButtonBorderColor(const ButtonState state, const BorderColor &value); // Set button border color depending on state
			bool setButtonBackgroundColor(const ButtonState state, const Color &value); // Set button background color depending on state
			bool setButtonIcons(IImageList *value); // Set button icons image list
			bool setCloseIconIndex(const ButtonState state, const int value); // Set index of close icon in button image list depending on state
			bool setMinimizeIconIndex(const ButtonState state, const int value); // Set index of minimize icon in button image list depending on state
			bool setMaximizeIconIndex(const ButtonState state, const int value); // Set index of maximize icon in button image list depending on state
			bool setRestoreIconIndex(const ButtonState state, const int value); // Set index of restore icon in button image list depending on state
			bool setUseDefaultCloseIcon(const bool value); // Set whether default close button icon should be drawn in case of there is no icon in attached button's icon list or no such list attached
			bool setUseDefaultMinimizeIcon(const bool value); // Set whether default minimize button icon should be drawn in case of there is no icon in attached button's icon list or no such list attached
			bool setUseDefaultMaximizeIcon(const bool value); // Set whether default maximize button icon should be drawn in case of there is no icon in attached button's icon list or no such list attached
			bool setUseDefaultRestoreIcon(const bool value); // Set whether default restore button icon should be drawn in case of there is no icon in attached button's icon list or no such list attached
			bool setShadowColor(const State state, const Color &value); // Set shadow color depending on state
			bool setShadowRadius(const State state, const int value); // Set shadow radius depending on state
			bool setShadowShift(const State state, const PointF &value); // Set shadow shift depending on state
			bool setMinimizedWidth(const float value); // Set control width in minimized state
			bool setIconPadding(const RectF &value); // Set system icon padding
			bool setIcons(IImageList *value); // Set image list where system icon is
			bool setIconIndex(const State state, const int value); // Set index of system icon in system icon image list
			bool setBlinkInterval(const float value); // Set blinking interval
			bool setBlinkCount(const int value); // Set number of blinks. <=0 means no blinking
		};
	}
}