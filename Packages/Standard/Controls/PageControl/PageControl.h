// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IPageControl.h"
#include <vector>

namespace nitisa
{
	class IPlatformFont;
	class Renderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class IImageList;

		class CPageControlService;
		class CTabSheet;

		class CPageControl :public virtual IPageControl, public CControl
		{
			friend CPageControlService;
		public:
			enum class HeaderPosition // Tabs header position
			{
				Left,
				Top,
				Right,
				Bottom
			};

			enum class ScrollState // Scrolling states
			{
				Normal,
				Hovered,
				Active,
				ActiveHovered,
				Disabled
			};

			enum class TabState // Tab header states
			{
				Normal,
				Hovered,
				Active,
				ActiveFocused,
				Disabled
			};
		private:
			struct INFO
			{
				ITabSheet *Tab;
				PointF CaptionSize;
				float Width;
				ITexture *Icon;
				RectF IconPart;
			};

			enum class Element
			{
				None,
				Tab,
				ScrollStart,
				ScrollEnd
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CPageControl *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CPageControl *control);
			};
		private:
			CGradientListener m_cGradientListener;
			PointF m_sHeaderSize; // <= 0 - calculate automatically
			HeaderPosition m_eHeaderPosition;
			bool m_bMultiline;
			RectF m_sBorderWidth;
			BorderColor m_sBorderColor;
			Color m_sBackgroundColor;
			Gradient m_cBackgroundGradient;
			PointF m_sHeaderShift; // How bigger becomes active tab sheet header
			RectF m_sHeaderPadding;
			float m_fHeaderBorderWidth;
			Color m_aHeaderBorderColor[(int)TabState::Disabled + 1];
			Color m_aHeaderBackgroundColor[(int)TabState::Disabled + 1];
			Gradient m_aHeaderBackgroundGradient[(int)TabState::Disabled + 1];
			Color m_aCaptionColor[(int)TabState::Disabled + 1];
			Color m_aCaptionShadowColor[(int)TabState::Disabled + 1];
			PointF m_aCaptionShadowShift[(int)TabState::Disabled + 1];
			int m_aCaptionShadowRadius[(int)TabState::Disabled + 1];
			IImageList *m_pImageList;
			float m_fScrollArrowSize;
			RectF m_sScrollBorderWidth;
			RectF m_sScrollBorderRadius;
			BorderColor m_aScrollBorderColor[(int)ScrollState::Disabled + 1];
			Color m_aScrollBackgroundColor[(int)ScrollState::Disabled + 1];
			Gradient m_aScrollBackgroundGradient[(int)ScrollState::Disabled + 1];
			Color m_aScrollArrowColor[(int)ScrollState::Disabled + 1];
			int m_iActiveIndex;
			RectF m_sIconPadding; // Left has no matter. Icon rect has height same to width and calculated using top and bottom padding and header height, Right padding is distance to caption
			bool m_bUseMask;
			float m_fScrollInterval;
			float m_fDeltaScrollTimer;
			float m_fDeltaScrollWheel;

			bool m_bIgnoreGradient;
			float m_fScroll;
			float m_fScrollMax;
			ITexture *m_pCanvas;
			ITexture *m_pMask;
			int m_iHoveredTab;
			Element m_eHoveredElement;
			Element m_eDownElement;

			std::vector<std::vector<INFO>> m_aLines;
			float m_fHeaderSize;
			int m_iActiveLine;
			float m_fLineHeight;
			float m_fControlSize;

			void UpdateFromStyle(IStyle *style);
			void Update();
			bool UpdateHoveredElement(const PointF &position);
			RectF getTabSheetRect();
			RectF getHeaderRect();
			TabState getTabState(ITabSheet *tab);
			ScrollState getScrollStartState();
			ScrollState getScrollEndState();
			void Render(IRenderer *renderer, const Mat4f &matrix);
			void RenderTabHeaders(IRenderer *renderer, IPlatformFont *pf);
			void RenderTabHeader(IRenderer *renderer, const RectF &borders, const float x, const float y, IPlatformFont *pf, INFO &info, const bool active);
			void RenderScrolls(IRenderer *renderer);
			void RenderMask(IRenderer *renderer);
		public:
			void(*OnActivateTabSheet)(IControl *sender, const int index); // Event called when tab has been activated

			// IControl methods
			void Refresh(const bool refresh_children) override;

			RectF getClientRect() override;
			bool isFocusByMouse() override;
			
			int getTabSheetCount() override;
			ITabSheet *getTabSheet(const int index) override;
			ITabSheet *getActiveTabSheet() override;
			int getActiveIndex() override;

			bool setDPI(const Point &value) override;
			bool setActiveIndex(const int value) override;
			bool setActiveTabSheet(ITabSheet *value) override;

			bool AttachControl(IControl *control) override;
			bool InsertControl(IControl *control, const int before) override;

			IControl *CreateChild() override;
			ITabSheet *CreateTabSheet() override;
			ITabSheet *CreateTabSheet(const int before) override;
			bool AddTabSheet(ITabSheet *tab) override;
			bool InsertTabSheet(ITabSheet *tab, const int before) override;
			bool DeleteTabSheet(const int index) override;
			bool DeleteTabSheet(ITabSheet *tab) override;
			bool DeleteTabSheets() override;

			CPageControl();
			CPageControl(IForm *parent);
			CPageControl(IControl *parent);

			// Return layout properties
			PointF getHeaderSize() const;
			HeaderPosition getHeaderPosition() const;
			bool isMultiline() const;
			RectF getBorderWidth() const;
			BorderColor getBorderColor() const;
			Color getLeftBorderColor() const;
			Color getTopBorderColor() const;
			Color getRightBorderColor() const;
			Color getBottomBorderColor() const;
			Color getBackgroundColor() const;
			Gradient *getBackgroundGradient();
			PointF getHeaderShift() const;
			RectF getHeaderPadding() const;
			float getHeaderBorderWidth() const;
			Color getHeaderBorderColor(const TabState state) const;
			Color getHeaderBackgroundColor(const TabState state) const;
			Gradient *getHeaderBackgroundGradient(const TabState state);
			Color getCaptionColor(const TabState state) const;
			Color getCaptionShadowColor(const TabState state) const;
			PointF getCaptionShadowShift(const TabState state) const;
			int getCaptionShadowRadius(const TabState state) const;
			IImageList *getImageList();
			float getScrollArrowSize() const;
			RectF getScrollBorderWidth() const;
			RectF getScrollBorderRadius() const;
			BorderColor getScrollBorderColor(const ScrollState state) const;
			Color getScrollLeftBorderColor(const ScrollState state) const;
			Color getScrollTopBorderColor(const ScrollState state) const;
			Color getScrollRightBorderColor(const ScrollState state) const;
			Color getScrollBottomBorderColor(const ScrollState state) const;
			Color getScrollBackgroundColor(const ScrollState state) const;
			Gradient *getScrollBackgroundGradient(const ScrollState state);
			Color getScrollArrowColor(const ScrollState state) const;
			RectF getIconPadding() const;
			bool isUseMask() const; // Whether to use mask
			float getScrollInterval() const; // Return scroll interval(in seconds)
			float getDeltaScrollTimer() const;
			float getDeltaScrollWheel() const;

			// Set layout properties
			bool setHeaderSize(const PointF &value);
			bool setHeaderPosition(const HeaderPosition value);
			bool setMultiline(const bool value);
			bool setBorderWidth(const RectF &value);
			bool setBorderColor(const BorderColor &value);
			bool setLeftBorderColor(const Color &value);
			bool setTopBorderColor(const Color &value);
			bool setRightBorderColor(const Color &value);
			bool setBottomBorderColor(const Color &value);
			bool setBackgroundColor(const Color &value);
			bool setHeaderShift(const PointF &value);
			bool setHeaderPadding(const RectF &value);
			bool setHeaderBorderWidth(const float value);
			bool setHeaderBorderColor(const TabState state, const Color &value);
			bool setHeaderBackgroundColor(const TabState state, const Color &value);
			bool setCaptionColor(const TabState state, const Color &value);
			bool setCaptionShadowColor(const TabState state, const Color &value);
			bool setCaptionShadowShift(const TabState state, const PointF &value);
			bool setCaptionShadowRadius(const TabState state, const int value);
			bool setImageList(IImageList *value);
			bool setScrollArrowSize(const float value);
			bool setScrollBorderWidth(const RectF &value);
			bool setScrollBorderRadius(const RectF &value);
			bool setScrollBackgroundColor(const ScrollState state, const Color &value);
			bool setScrollBorderColor(const ScrollState state, const BorderColor &value);
			bool setScrollLeftBorderColor(const ScrollState state, const Color &value);
			bool setScrollTopBorderColor(const ScrollState state, const Color &value);
			bool setScrollRightBorderColor(const ScrollState state, const Color &value);
			bool setScrollBottomBorderColor(const ScrollState state, const Color &value);
			bool setScrollArrowColor(const ScrollState state, const Color &value);
			bool setIconPadding(const RectF &value);
			bool setUseMask(const bool value); // Set whether to use mask
			bool setScrollInterval(const float value); // Set scroll interval(in seconds)
			bool setDeltaScrollTimer(const float value);
			bool setDeltaScrollWheel(const float value);
		};
	}
}