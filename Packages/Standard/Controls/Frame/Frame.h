// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/CloseAction.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IFrame.h"
#include "FrameService.h"

namespace nitisa
{
	class IControl;
	class IFrame;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CFrame :public virtual IFrame, public CControl
		{
			friend CFrameService;
		public:
			enum class State // Possible states
			{
				Normal,
				Hovered,
				Active, // Modal or focused control is on it
				Disabled
			};

			enum class FrameState // Frame states
			{
				Normal,
				Minimized,
				Maximized
			};

			enum class ButtonState // Frame caption button states
			{
				InactiveNormal, // Frame is not active
				InactiveHovered, // Frame is inactive and button is hovered
				InactiveDisabled, // Frame is inactive and button is disabled
				Normal, // Normal state
				Hovered, // Button is hovered
				Active, // Button is active(mouse button was down on it but not released yet)
				ActiveHovered, // Button is active and hovered
				Disabled // Button is disabled
			};
		private:
			struct BUTTON
			{
				bool DisplayDisabled;
				PointF Size;
				RectF BorderWidth;
				RectF BorderRadius;
				RectF IconPadding;
				nitisa::BorderColor BorderColor[(int)ButtonState::Disabled + 1];
				Color BackgroundColor[(int)ButtonState::Disabled + 1];
				Gradient BackgroundGradient[(int)ButtonState::Disabled + 1];
				Color ShadowColor[(int)ButtonState::Disabled + 1];
				PointF ShadowShift[(int)ButtonState::Disabled + 1];
				int ShadowRadius[(int)ButtonState::Disabled + 1];
				ButtonState State;
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CFrame *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CFrame *control);
			};
		private:
			CGradientListener m_cGradientListener;
			// Shadow
			Color m_aShadowColor[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];
			// Border
			RectF m_sOuterBorderWidth;
			RectF m_sBorderRadius;
			BorderColor m_aOuterBorderColor[(int)State::Disabled + 1];
			RectF m_sMiddleBorderWidth;
			BorderColor m_aMiddleBorderColor[(int)State::Disabled + 1];
			Gradient m_aMiddleBorderGradient[(int)State::Disabled + 1];
			RectF m_sInnerBorderWidth;
			BorderColor m_aInnerBorderColor[(int)State::Disabled + 1];
			// Background
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			// Caption
			float m_fCaptionPadding; // From left side of caption rect
			Color m_aCaptionColor[(int)State::Disabled + 1];
			Color m_aCaptionShadowColor[(int)State::Disabled + 1];
			PointF m_aCaptionShadowShift[(int)State::Disabled + 1];
			int m_aCaptionShadowRadius[(int)State::Disabled + 1];
			// Common
			String m_sCaption;
			bool m_bMinimizable;
			bool m_bMaximizable;
			bool m_bClosable;
			bool m_bResizable;
			bool m_bMovable;
			bool m_bUseMask;
			float m_fMinimizedWidth;
			// Buttons
			BUTTON m_sBtnMinimizeRestore;
			BUTTON m_sBtnMaximizeRestore;
			BUTTON m_sBtnClose;

			bool m_bIgnoreGradient;
			bool m_bModal;
			FrameState m_eFrameState;
			FrameState m_eLastFrameState;
			RectF m_sLastRect;
			ITexture *m_pCanvas;
			ITexture *m_pMask;
			bool m_bMaskActive;
			State m_eLastRenderState;
			bool m_bCaptionChanged;

			CFrameService::DownPart getPart(const PointF &position);
			RectF getCaptionRect();
			RectF getLeftTopCornerRect();
			RectF getRightTopCornerRect();
			RectF getRightBottomCornerRect();
			RectF getLeftBottomCornerRect();
			RectF getLeftBorderRect();
			RectF getTopBorderRect();
			RectF getRightBorderRect();
			RectF getBottomBorderRect();
			RectF getMinimizeRestoreButtonRect();
			RectF getMaximizeRestoreButtonRect();
			RectF getCloseButtonRect();
			RectF getCaptionRenderRect();
			RectF getMinimizeRestoreButtonRenderRect();
			RectF getMaximizeRestoreButtonRenderRect();
			RectF getCloseButtonRenderRect();
			ITexture *FindIcon(const String &name, RectF &part);
			String StateToString(const ButtonState state);
			PointF getMinSize();
			void AdjustConstraints();
			void UpdateFromStyle(IStyle *style);
			void Render(IRenderer *renderer, const Mat4f &matrix);
			void RenderButton(IRenderer *renderer, BUTTON &btn, const RectF &btn_rect, const bool allowed, const String &name, const bool first, const ButtonState bs);
			void RenderButtons(IRenderer *renderer, const State state, const PointF &disp);
			void RenderCaption(IRenderer *renderer, const State state, const RectF &rect, const PointF &disp);
			void RenderMask(IRenderer *renderer);
		public:
			void(*OnMinimize)(IFrame *sender); // Event called when frame has been minimized
			void(*OnMaximize)(IFrame *sender); // Event called when frame has been maximized
			void(*OnRestore)(IFrame *sender); // Event called when frame has been restored
			void(*OnClose)(IFrame *sender, CloseAction &action); // Event called when frame is about to be closed

			// IControl methods
			void Refresh(const bool refresh_children) override;

			IControl *getControl(const int index) override;
			IControl *getControl(const String &name) override;
			IControl *getControl(const PointF &position) override;
			RectF getClientRect() override;
			RectF getRenderRect() override;
			CursorType getCursor() override;
			
			bool setConstraints(const RectF &value) override;
			bool setDPI(const Point &value) override;

			String getCaption() override;
			bool isMinimizable() override;
			bool isMaximizable() override;
			bool isClosable() override;
			bool isResizable() override;
			bool isMovable() override;
			bool isMinimized() override;
			bool isMaximized() override;

			bool setCaption(const String &value) override;
			bool setMinimizable(const bool value) override;
			bool setMaximizable(const bool value) override;
			bool setClosable(const bool value) override;
			bool setResizable(const bool value) override;
			bool setMovable(const bool value) override;

			bool Show() override;
			bool ShowModal() override;
			bool Hide() override;
			bool Minimize() override;
			bool Maximize() override;
			bool Restore() override;

			CFrame();
			CFrame(IForm *parent);
			CFrame(IControl *parent);

			State getState(); // Return state
			FrameState getFrameState() const; // Return frame state
			// Return layout properties
			Color getShadowColor(const State state) const;
			PointF getShadowShift(const State state) const;
			int getShadowRadius(const State state) const;
			RectF getOuterBorderWidth() const;
			RectF getBorderRadius() const;
			BorderColor getOuterBorderColor(const State state) const;
			Color getOuterLeftBorderColor(const State state) const;
			Color getOuterTopBorderColor(const State state) const;
			Color getOuterRightBorderColor(const State state) const;
			Color getOuterBottomBorderColor(const State state) const;
			RectF getMiddleBorderWidth() const;
			BorderColor getMiddleBorderColor(const State state) const;
			Color getMiddleLeftBorderColor(const State state) const;
			Color getMiddleTopBorderColor(const State state) const;
			Color getMiddleRightBorderColor(const State state) const;
			Color getMiddleBottomBorderColor(const State state) const;
			Gradient *getMiddleBorderGradient(const State state);
			RectF getInnerBorderWidth() const;
			BorderColor getInnerBorderColor(const State state) const;
			Color getInnerLeftBorderColor(const State state) const;
			Color getInnerTopBorderColor(const State state) const;
			Color getInnerRightBorderColor(const State state) const;
			Color getInnerBottomBorderColor(const State state) const;
			Color getBackgroundColor(const State state) const;
			Gradient *getBackgroundGradient(const State state);
			float getCaptionPadding() const;
			Color getCaptionColor(const State state) const;
			Color getCaptionShadowColor(const State state) const;
			PointF getCaptionShadowShift(const State state) const;
			int getCaptionShadowRadius(const State state) const;
			float getMinimizedWidth() const;
			bool isUseMask() const; // Whether to use mask

			// Return minimize-restore button layout properties
			bool isBtnMinimizeRestoreDisplayDisabled() const;
			PointF getBtnMinimizeRestoreSize() const;
			RectF getBtnMinimizeRestoreBorderWidth() const;
			RectF getBtnMinimizeRestoreBorderRadius() const;
			RectF getBtnMinimizeRestoreIconPadding() const;
			BorderColor getBtnMinimizeRestoreBorderColor(const ButtonState state) const;
			Color getBtnMinimizeRestoreLeftBorderColor(const ButtonState state) const;
			Color getBtnMinimizeRestoreTopBorderColor(const ButtonState state) const;
			Color getBtnMinimizeRestoreRightBorderColor(const ButtonState state) const;
			Color getBtnMinimizeRestoreBottomBorderColor(const ButtonState state) const;
			Color getBtnMinimizeRestoreBackgroundColor(const ButtonState state) const;
			Gradient *getBtnMinimizeRestoreBackgroundGradient(const ButtonState state);
			Color getBtnMinimizeRestoreShadowColor(const ButtonState state) const;
			PointF getBtnMinimizeRestoreShadowShift(const ButtonState state) const;
			int getBtnMinimizeRestoreShadowRadius(const ButtonState state) const;
			ButtonState getBtnMinimizeRestoreState();

			// Return maximize-restore button layout properties
			bool isBtnMaximizeRestoreDisplayDisabled() const;
			PointF getBtnMaximizeRestoreSize() const;
			RectF getBtnMaximizeRestoreBorderWidth() const;
			RectF getBtnMaximizeRestoreBorderRadius() const;
			RectF getBtnMaximizeRestoreIconPadding() const;
			BorderColor getBtnMaximizeRestoreBorderColor(const ButtonState state) const;
			Color getBtnMaximizeRestoreLeftBorderColor(const ButtonState state) const;
			Color getBtnMaximizeRestoreTopBorderColor(const ButtonState state) const;
			Color getBtnMaximizeRestoreRightBorderColor(const ButtonState state) const;
			Color getBtnMaximizeRestoreBottomBorderColor(const ButtonState state) const;
			Color getBtnMaximizeRestoreBackgroundColor(const ButtonState state) const;
			Gradient *getBtnMaximizeRestoreBackgroundGradient(const ButtonState state);
			Color getBtnMaximizeRestoreShadowColor(const ButtonState state) const;
			PointF getBtnMaximizeRestoreShadowShift(const ButtonState state) const;
			int getBtnMaximizeRestoreShadowRadius(const ButtonState state) const;
			ButtonState getBtnMaximizeRestoreState();

			// Return close button layout properties
			bool isBtnCloseDisplayDisabled() const;
			PointF getBtnCloseSize() const;
			RectF getBtnCloseBorderWidth() const;
			RectF getBtnCloseBorderRadius() const;
			RectF getBtnCloseIconPadding() const;
			BorderColor getBtnCloseBorderColor(const ButtonState state) const;
			Color getBtnCloseLeftBorderColor(const ButtonState state) const;
			Color getBtnCloseTopBorderColor(const ButtonState state) const;
			Color getBtnCloseRightBorderColor(const ButtonState state) const;
			Color getBtnCloseBottomBorderColor(const ButtonState state) const;
			Color getBtnCloseBackgroundColor(const ButtonState state) const;
			Gradient *getBtnCloseBackgroundGradient(const ButtonState state);
			Color getBtnCloseShadowColor(const ButtonState state) const;
			PointF getBtnCloseShadowShift(const ButtonState state) const;
			int getBtnCloseShadowRadius(const ButtonState state) const;
			ButtonState getBtnCloseState();

			// Set layout properties
			bool setShadowColor(const State state, const Color &value);
			bool setShadowShift(const State state, const PointF &value);
			bool setShadowRadius(const State state, const int value);
			bool setOuterBorderWidth(const RectF &value);
			bool setBorderRadius(const RectF &value);
			bool setOuterBorderColor(const State state, const BorderColor &value);
			bool setOuterLeftBorderColor(const State state, const Color &value);
			bool setOuterTopBorderColor(const State state, const Color &value);
			bool setOuterRightBorderColor(const State state, const Color &value);
			bool setOuterBottomBorderColor(const State state, const Color &value);
			bool setMiddleBorderWidth(const RectF &value);
			bool setMiddleBorderColor(const State state, const BorderColor &value);
			bool setMiddleLeftBorderColor(const State state, const Color &value);
			bool setMiddleTopBorderColor(const State state, const Color &value);
			bool setMiddleRightBorderColor(const State state, const Color &value);
			bool setMiddleBottomBorderColor(const State state, const Color &value);
			bool setInnerBorderWidth(const RectF &value);
			bool setInnerBorderColor(const State state, const BorderColor &value);
			bool setInnerLeftBorderColor(const State state, const Color &value);
			bool setInnerTopBorderColor(const State state, const Color &value);
			bool setInnerRightBorderColor(const State state, const Color &value);
			bool setInnerBottomBorderColor(const State state, const Color &value);
			bool setBackgroundColor(const State state, const Color &value);
			bool setCaptionPadding(const float value);
			bool setCaptionColor(const State state, const Color &value);
			bool setCaptionShadowColor(const State state, const Color &value);
			bool setCaptionShadowShift(const State state, const PointF &value);
			bool setCaptionShadowRadius(const State state, const int value);
			bool setUseMask(const bool value); // Set whether to use mask
			bool setMinimizedWidth(const float value);

			// Set minimize-restore button layout properties
			bool setBtnMinimizeRestoreDisplayDisabled(const bool value);
			bool setBtnMinimizeRestoreSize(const PointF &value);
			bool setBtnMinimizeRestoreBorderWidth(const RectF &value);
			bool setBtnMinimizeRestoreBorderRadius(const RectF &value);
			bool setBtnMinimizeRestoreIconPadding(const RectF &value);
			bool setBtnMinimizeRestoreBorderColor(const ButtonState state, const BorderColor &value);
			bool setBtnMinimizeRestoreLeftBorderColor(const ButtonState state, const Color &value);
			bool setBtnMinimizeRestoreTopBorderColor(const ButtonState state, const Color &value);
			bool setBtnMinimizeRestoreRightBorderColor(const ButtonState state, const Color &value);
			bool setBtnMinimizeRestoreBottomBorderColor(const ButtonState state, const Color &value);
			bool setBtnMinimizeRestoreBackgroundColor(const ButtonState state, const Color &value);
			bool setBtnMinimizeRestoreShadowColor(const ButtonState state, const Color &value);
			bool setBtnMinimizeRestoreShadowShift(const ButtonState state, const PointF &value);
			bool setBtnMinimizeRestoreShadowRadius(const ButtonState state, const int value);

			// Set maximize-restore button layout properties
			bool setBtnMaximizeRestoreDisplayDisabled(const bool value);
			bool setBtnMaximizeRestoreSize(const PointF &value);
			bool setBtnMaximizeRestoreBorderWidth(const RectF &value);
			bool setBtnMaximizeRestoreBorderRadius(const RectF &value);
			bool setBtnMaximizeRestoreIconPadding(const RectF &value);
			bool setBtnMaximizeRestoreBorderColor(const ButtonState state, const BorderColor &value);
			bool setBtnMaximizeRestoreLeftBorderColor(const ButtonState state, const Color &value);
			bool setBtnMaximizeRestoreTopBorderColor(const ButtonState state, const Color &value);
			bool setBtnMaximizeRestoreRightBorderColor(const ButtonState state, const Color &value);
			bool setBtnMaximizeRestoreBottomBorderColor(const ButtonState state, const Color &value);
			bool setBtnMaximizeRestoreBackgroundColor(const ButtonState state, const Color &value);
			bool setBtnMaximizeRestoreShadowColor(const ButtonState state, const Color &value);
			bool setBtnMaximizeRestoreShadowShift(const ButtonState state, const PointF &value);
			bool setBtnMaximizeRestoreShadowRadius(const ButtonState state, const int value);

			// Set close button layout properties
			bool setBtnCloseDisplayDisabled(const bool value);
			bool setBtnCloseSize(const PointF &value);
			bool setBtnCloseBorderWidth(const RectF &value);
			bool setBtnCloseBorderRadius(const RectF &value);
			bool setBtnCloseIconPadding(const RectF &value);
			bool setBtnCloseBorderColor(const ButtonState state, const BorderColor &value);
			bool setBtnCloseLeftBorderColor(const ButtonState state, const Color &value);
			bool setBtnCloseTopBorderColor(const ButtonState state, const Color &value);
			bool setBtnCloseRightBorderColor(const ButtonState state, const Color &value);
			bool setBtnCloseBottomBorderColor(const ButtonState state, const Color &value);
			bool setBtnCloseBackgroundColor(const ButtonState state, const Color &value);
			bool setBtnCloseShadowColor(const ButtonState state, const Color &value);
			bool setBtnCloseShadowShift(const ButtonState state, const PointF &value);
			bool setBtnCloseShadowRadius(const ButtonState state, const int value);
		};
	}
}