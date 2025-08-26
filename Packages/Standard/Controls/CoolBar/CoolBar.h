// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/Scroll/BuiltInScroll.h"
#include "Nitisa/BuiltInControls/IBuiltInScrollListener.h"
#include "Nitisa/Core/Align.h"
#include "Nitisa/Core/DialogBox.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "NTL/Core/Consts.h"
#include "../ICoolBar.h"

namespace nitisa
{
	class IBuiltInScroll;
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CCoolBarService;

		class CCoolBar :public virtual ICoolBar, public CDialogBox
		{
			friend CCoolBarService;
		public:
			enum class State // Possible states of widget parts
			{
				Normal, // Normal state
				Hovered, // Part is under mouse pointer
				Down, // Mouse button was pressed and not yet released when mouse pointer was over a part
				Disabled // Part is disabled
			};

			enum class MoverKind // Supported mover kind
			{
				Flat,
				Line,
				DoubleLine,
				Dots,
				TripleDots
			};
		private:
			enum class Element
			{
				None,
				Mover,
				Extra,
				ExtraList,
				ExtraListScroll,
				ExtraListButton,
				ToggleList,
				ToggleListScroll,
				ToggleListElement
			};

			class CScroll :public CBuiltInScroll
			{
			private:
				CCoolBar *m_pControl;
			public:
				IControl *getControl() override;

				CScroll(CCoolBar *control);
			};

			class CExtraListScrollListener :public virtual IBuiltInScrollListener
			{
			private:
				CCoolBar *m_pControl;
			public:
				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnScroll(IBuiltInControl *sender) override;

				CExtraListScrollListener(CCoolBar *control);
			};

			class CToggleListScrollListener :public virtual IBuiltInScrollListener
			{
			private:
				CCoolBar *m_pControl;
			public:
				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnScroll(IBuiltInControl *sender) override;

				CToggleListScrollListener(CCoolBar *control);
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CCoolBar *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CCoolBar *control);
			};
		private:
			CGradientListener m_cGradientListener;
			Orientation m_eOrientation;
			float m_fStickDistance;
			bool m_bAutoAlign;
			bool m_bLocked;
			bool m_bResizable;
			IVisibilityManager *m_pVisibilityManager;
			bool m_bMoverAlwaysVisible;
			bool m_bExtraAlwaysVisible;
			MoverKind m_eMoverKind;
			// Background
			RectF m_sOuterBorderWidth;
			BorderColor m_sOuterBorderColor;
			RectF m_sInnerBorderWidth;
			BorderColor m_sInnerBorderColor;
			RectF m_sPadding; // Doesn't affect mover and extra. Applies only to client area
			Color m_sBackgroundColor;
			Gradient m_cBackgroundGradient;
			// Mover
			RectF m_sMoverMargin; // From inner border
			RectF m_sMoverBorderWidth;
			RectF m_sMoverPadding;
			BorderColor m_aMoverBorderColor[(int)State::Disabled + 1];
			Color m_aMoverBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aMoverBackgroundGradient[(int)State::Disabled + 1];
			Color m_aMoverForeground1Color[(int)State::Disabled + 1];
			Color m_aMoverForeground2Color[(int)State::Disabled + 1]; // For lines only
			// Extra button
			RectF m_sExtraMargin; // From inner border
			RectF m_sExtraBorderWidth;
			RectF m_sExtraPadding;
			float m_fExtraSize;
			BorderColor m_aExtraBorderColor[(int)State::Disabled + 1];
			Color m_aExtraBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aExtraBackgroundGradient[(int)State::Disabled + 1];
			Color m_aExtraColor[(int)State::Disabled + 1];
			// ExtraList
			PointF m_sExtraListConstraints;
			RectF m_sExtraListOuterBorderWidth;
			BorderColor m_sExtraListOuterBorderColor;
			RectF m_sExtraListInnerBorderWidth;
			BorderColor m_sExtraListInnerBorderColor;
			RectF m_sExtraListPadding;
			Color m_sExtraListBackgroundColor;
			Gradient m_cExtraListBackgroundGradient;
			int m_iExtraListShadowRadius;
			PointF m_sExtraListShadowShift;
			Color m_sExtraListShadowColor;
			RectF m_sExtraListButtonPadding;
			RectF m_sExtraListButtonBorderWidth;
			BorderColor m_aExtraListButtonBorderColor[(int)State::Disabled + 1];
			Color m_aExtraListButtonBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aExtraListButtonBackgroundGradient[(int)State::Disabled + 1];
			Color m_aExtraListButtonColor[(int)State::Disabled + 1];
			// ToggleList
			PointF m_sToggleListConstraints;
			RectF m_sToggleListOuterBorderWidth;
			BorderColor m_sToggleListOuterBorderColor;
			RectF m_sToggleListInnerBorderWidth;
			BorderColor m_sToggleListInnerBorderColor;
			RectF m_sToggleListPadding;
			Color m_sToggleListBackgroundColor;
			Gradient m_cToggleListBackgroundGradient;
			int m_iToggleListShadowRadius;
			PointF m_sToggleListShadowShift;
			Color m_sToggleListShadowColor;
			float m_fToggleListIconPadding;
			RectF m_sToggleListElementPadding;
			RectF m_sToggleListElementBorderWidth;
			BorderColor m_aToggleListElementBorderColor[(int)State::Disabled + 1];
			Color m_aToggleListElementBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aToggleListElementBackgroundGradient[(int)State::Disabled + 1];
			Color m_aToggleListElementColor[(int)State::Disabled + 1];

			ITexture *m_pCanvas;
			ITexture *m_pCanvasExtraList;
			ITexture *m_pCanvasToggleList;
			ITexture *m_pMaskExtraList;
			Element m_eDownElement;
			Element m_eHoveredElement;
			int m_iDownElementIndex;
			int m_iHoveredElementIndex;
			int m_iLastVisibleControl;
			bool m_bShowExtra;
			bool m_bHasExtraControls;
			bool m_bIgnoreGradient;
			bool m_bExtraListVisible;
			bool m_bToggleListVisible;
			RectF m_sExtraListRect;
			RectF m_sExtraListClientRect;
			RectF m_sExtraListButtonRect;
			RectF m_sToggleListRect;
			RectF m_sToggleListClientRect;
			float m_fToggleListElementHeight;
			IBuiltInScroll *m_pExtraListScroll;
			IBuiltInScroll *m_pToggleListScroll;
			bool m_bExtraListScrollVisible;
			bool m_bToggleListScrollVisible;
			CExtraListScrollListener m_cExtraListScrollListener;
			CToggleListScrollListener m_cToggleListScrollListener;
			bool m_bAligning;

			float CalculateMoverSize() const;
			float CalculateRequiredSize();
			RectF CalculateClientRect(bool &show_extra, bool &has_extra_controls);
			RectF CalculateMoverRect();
			RectF CalculateMoverInnerRect(const RectF &total);
			RectF CalculateExtraRect();
			RectF CalculateToggleListClientRect(const RectF &rect) const;
			Gradient CalculateGradient(const Gradient &gradient) const;
			Element getElement(const PointF &pos, int &index);
			IBuiltInScroll *getExtraListScroll();
			IBuiltInScroll *getToggleListScroll();
			State CalculateMoverState();
			State CalculateExtraState();
			State CalculateExtraListButtonState();
			State CalculateToggleListElementState(IControl *control, const int index);
			ITexture *FindDefaultIcon(RectF &part);
			ITexture *FindCheckboxIcon(const bool checked, const State state, RectF &part);
			bool UpdateHoveredElement();
			bool UpdateHoveredElement(const PointF &pos);
			void UpdateFromStyle(IStyle *style);
			bool OpenExtraList();
			bool CloseExtraList();
			bool OpenToggleList();
			bool CloseToggleList();
			void UpdateExtraList();
			void UpdateToggleList();
			void AlignControls(const bool hide_controls);
			void AlignExtraControls();
			void PostClientAreaChange();
			void PostExtraListChange();
			void PostToggleListChange();
			void Render(IRenderer *renderer, const Mat4f &matrix);
			void RenderBackground(IRenderer *renderer, const RectF &rect);
			void RenderMover(IRenderer *renderer);
			void RenderExtra(IRenderer *renderer);
			void RenderExtraList(IRenderer *renderer, const Mat4f &matrix);
			void RenderExtraListMask(IRenderer *renderer);
			void RenderToggleList(IRenderer *renderer, const Mat4f &matrix);
		protected:
			void BeforeRelease() override;
		public:
			static const String TranslateCategory; // Category used for internationalization. Defined as L"standard::CoolBar"
			static const String TextAddOrRemoveButtons; // Text displayed on button responsible for display list of child controls visibility management. Defined as L"Add or Remove Buttons"
			static const String TextWidgetI; // Widget caption displayed when the widget is not supported by assigned visibility manager. Defined as L"Widget #{i}"

			// IControl getters
			IControl *getControl(const int index) override;
			IControl *getControl(const String &name) override;
			IControl *getControl(const PointF &position) override;
			RectF getClientRect() override;
			RectF getRenderRect() override;
			CursorType getCursor() override;
			bool isAcceptControl() override;
			bool isAcceptControl(IControl *control) override;
			bool isAcceptBubbledEvents() override;
			bool hasExtra() override;

			// IControl setters
			bool setAlign(const Align value) override; // Align::Client is not allowed
			bool setDPI(const Point &value) override;

			// ICoolBar getters
			Orientation getOrientation() override;
			float getStickDistance() override;
			bool isAutoAlign() override;
			bool isLocked() override;
			bool isResizable() override;
			IVisibilityManager *getVisibilityManager() override;
			PointF getResizeLimits() override;

			// ICoolBar setters
			bool setOrientation(const Orientation value) override;
			bool setStickDistance(const float value, const float tolerance = ntl::Tolerance<float>) override;
			bool setAutoAlign(const bool value) override;
			bool setLocked(const bool value) override;
			bool setResizable(const bool value) override;
			bool setVisibilityManager(IVisibilityManager *value) override;

			// IDialogBox getters
			Color getBackgroundColor() override;
			String getCaption() override;
			WindowState getState() override;
			RectF getBorderWidth() override;
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
			bool setClientSize(const Point &value) override;
			bool setState(const WindowState value) override;
			bool setBorderWidth(const RectF &value) override;
			bool setHasCloseBox(const bool value) override;
			bool setHasMaximizeBox(const bool value) override;
			bool setHasMinimizeBox(const bool value) override;
			bool setHasSizeBox(const bool value) override;
			bool setHasSystemMenu(const bool value) override;
			bool setHasBorder(const bool value) override;
			bool setHasCaption(const bool value) override;
			bool setIsPopup(const bool value) override;

			// IDialogBox methods
			bool Hide() override;
			bool Maximize() override;
			bool Minimize() override;
			bool Restore() override;

			CCoolBar();
			CCoolBar(IForm *parent);
			CCoolBar(IControl *parent);
			~CCoolBar() override;

			// Getters
			bool isMoverAlwaysVisible() const;
			bool isExtraAlwaysVisible() const;
			MoverKind getMoverKind() const;
			RectF getOuterBorderWidth() const;
			BorderColor getOuterBorderColor() const;
			RectF getInnerBorderWidth() const;
			BorderColor getInnerBorderColor() const;
			RectF getPadding() const;
			Gradient *getBackgroundGradient();
			RectF getMoverMargin() const;
			RectF getMoverBorderWidth() const;
			RectF getMoverPadding() const;
			BorderColor getMoverBorderColor(const State state) const;
			Color getMoverBackgroundColor(const State state) const;
			Gradient *getMoverBackgroundGradient(const State state);
			Color getMoverForeground1Color(const State state) const;
			Color getMoverForeground2Color(const State state) const;
			RectF getExtraMargin() const;
			RectF getExtraBorderWidth() const;
			RectF getExtraPadding() const;
			float getExtraSize() const;
			BorderColor getExtraBorderColor(const State state) const;
			Color getExtraBackgroundColor(const State state) const;
			Gradient *getExtraBackgroundGradient(const State state);
			Color getExtraColor(const State state) const;
			PointF getExtraListConstraints() const;
			RectF getExtraListOuterBorderWidth() const;
			BorderColor getExtraListOuterBorderColor() const;
			RectF getExtraListInnerBorderWidth() const;
			BorderColor getExtraListInnerBorderColor() const;
			RectF getExtraListPadding() const;
			Color getExtraListBackgroundColor() const;
			Gradient *getExtraListBackgroundGradient();
			int getExtraListShadowRadius() const;
			PointF getExtraListShadowShift() const;
			Color getExtraListShadowColor() const;
			RectF getExtraListButtonPadding() const;
			RectF getExtraListButtonBorderWidth() const;
			BorderColor getExtraListButtonBorderColor(const State state) const;
			Color getExtraListButtonBackgroundColor(const State state) const;
			Gradient *getExtraListButtonBackgroundGradient(const State state);
			Color getExtraListButtonColor(const State state) const;
			PointF getToggleListConstraints() const;
			RectF getToggleListOuterBorderWidth() const;
			BorderColor getToggleListOuterBorderColor() const;
			RectF getToggleListInnerBorderWidth() const;
			BorderColor getToggleListInnerBorderColor() const;
			RectF getToggleListPadding() const;
			Color getToggleListBackgroundColor() const;
			Gradient *getToggleListBackgroundGradient();
			int getToggleListShadowRadius() const;
			PointF getToggleListShadowShift() const;
			Color getToggleListShadowColor() const;
			float getToggleListIconPadding() const;
			RectF getToggleListElementPadding() const;
			RectF getToggleListElementBorderWidth() const;
			BorderColor getToggleListElementBorderColor(const State state) const;
			Color getToggleListElementBackgroundColor(const State state) const;
			Gradient *getToggleListElementBackgroundGradient(const State state);
			Color getToggleListElementColor(const State state) const;

			// Setters
			bool setExtraListScroll(IBuiltInScroll *value); // Assign new scroll used in extra list. Set nullptr to use default one. Should not be the same as toggle list scroll. Old one will be destroyed automatically
			bool setToggleListScroll(IBuiltInScroll *value); // Assign new scroll used in toggle list. Set nullptr to use default one. Should not be the same as extra list scroll. Old one will be destroyed automatically
			bool setMoverAlwaysVisible(const bool value);
			bool setExtraAlwaysVisible(const bool value);
			bool setMoverKind(const MoverKind value);
			bool setOuterBorderWidth(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setOuterBorderColor(const BorderColor &value);
			bool setInnerBorderWidth(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setInnerBorderColor(const BorderColor &value);
			bool setPadding(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setMoverMargin(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setMoverBorderWidth(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setMoverPadding(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setMoverBorderColor(const State state, const BorderColor &value);
			bool setMoverBackgroundColor(const State state, const Color &value);
			bool setMoverForeground1Color(const State state, const Color &value);
			bool setMoverForeground2Color(const State state, const Color &value);
			bool setExtraMargin(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setExtraBorderWidth(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setExtraPadding(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setExtraSize(const float value, const float tolerance = ntl::Tolerance<float>);
			bool setExtraBorderColor(const State state, const BorderColor &value);
			bool setExtraBackgroundColor(const State state, const Color &value);
			bool setExtraColor(const State state, const Color &value);
			bool setExtraListConstraints(const PointF &value, const float tolerance = ntl::Tolerance<float>);
			bool setExtraListOuterBorderWidth(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setExtraListOuterBorderColor(const BorderColor &value);
			bool setExtraListInnerBorderWidth(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setExtraListInnerBorderColor(const BorderColor &value);
			bool setExtraListPadding(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setExtraListBackgroundColor(const Color &value);
			bool setExtraListShadowRadius(const int value);
			bool setExtraListShadowShift(const PointF &value, const float tolerance = ntl::Tolerance<float>);
			bool setExtraListShadowColor(const Color &value);
			bool setExtraListButtonPadding(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setExtraListButtonBorderWidth(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setExtraListButtonBorderColor(const State state, const BorderColor &value);
			bool setExtraListButtonBackgroundColor(const State state, const Color &value);
			bool setExtraListButtonColor(const State state, const Color &value);
			bool setToggleListConstraints(const PointF &value, const float tolerance = ntl::Tolerance<float>);
			bool setToggleListOuterBorderWidth(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setToggleListOuterBorderColor(const BorderColor &value);
			bool setToggleListInnerBorderWidth(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setToggleListInnerBorderColor(const BorderColor &value);
			bool setToggleListPadding(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setToggleListBackgroundColor(const Color &value);
			bool setToggleListShadowRadius(const int value);
			bool setToggleListShadowShift(const PointF &value, const float tolerance = ntl::Tolerance<float>);
			bool setToggleListShadowColor(const Color &value);
			bool setToggleListIconPadding(const float value, const float tolerance = ntl::Tolerance<float>);
			bool setToggleListElementPadding(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setToggleListElementBorderWidth(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setToggleListElementBorderColor(const State state, const BorderColor &value);
			bool setToggleListElementBackgroundColor(const State state, const Color &value);
			bool setToggleListElementColor(const State state, const Color &value);
		};
	}
}