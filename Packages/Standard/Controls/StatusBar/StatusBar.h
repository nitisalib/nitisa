// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Align.h"
#include "Nitisa/Core/ControlItemList.h"
#include "Nitisa/Core/ListItemOwner.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IStatusBar.h"

namespace nitisa
{
	class IFont;
	class IForm;
	class IListItem;
	class IListItemOwner;
	class IControl;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class IListItemStatusPanelLabel;

		class CStatusBarService;

		class CStatusBar :public virtual IStatusBar, public CControlItemList
		{
			friend CStatusBarService;
		private:
			class CStatusBarListItemOwner :public virtual CListItemOwner
			{
			private:
				CStatusBar *m_pStatusBar;
			public:
				CStatusBarListItemOwner(CStatusBar *statusbar);

				IControl *getControl() override;
				IRenderer *getRenderer() override;
				IFont *getFont(IListItem *item) override;
				IStyle *getStyle(IListItem *item) override;

				void NotifyOnSizeChange(IListItem *item) override;
				void NotifyOnRepaintRequired(IListItem *item) override;
				void NotifyOnBeforeAddItem(IListItem *item, IListItem *parent) override;
				void NotifyOnAddItem(IListItem *item) override;
				void NotifyOnBeforeDeleteItem(IListItem *item) override;
				void NotifyOnDeleteItem(IListItem *item, IListItem *parent) override;
				void NotifyOnBeforeDeleteItems(IListItem *parent) override;
				void NotifyOnDeleteItems(IListItem *parent) override;
				void NotifyOnShow(IListItem *item) override;
				void NotifyOnHide(IListItem *item) override;
				void NotifyOnEnable(IListItem *item) override;
				void NotifyOnDisable(IListItem *item) override;
				void NotifyOnSelect(IListItem *item) override;
				void NotifyOnDeselect(IListItem *item) override;
				void NotifyOnActivate(IListItem *item) override;
				void NotifyOnDeactivate(IListItem *item) override;
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CStatusBar *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CStatusBar *control);
			};
		private:
			CGradientListener m_cGradientListener;
			RectF m_sOuterBorderWidth;
			RectF m_sInnerBorderWidth;
			RectF m_sBorderRadius;
			BorderColor m_sOuterBorderColor;
			BorderColor m_sInnerBorderColor;
			Color m_sBackgroundColor;
			Gradient m_cBackgroundGradient;
			Color m_sShadowColor;
			PointF m_sShadowShift;
			int m_iShadowRadius;
			float m_fSeparatorWidth;
			Color m_sSeparatorColor;
			Gradient m_cSeparatorGradient;

			bool m_bIgnoreGradient;
			IListItemOwner *m_pListItemOwner;
			ITexture *m_pCanvas;

			void UpdateFromStyle(IStyle *style);
			bool Update(); // Also update hovered item
			bool UpdateHoveredItem();
			bool UpdateHoveredItem(const PointF &position);
			IListItem *getItemAtPoint(const PointF &position);
			void Render();
			void RenderItems(IRenderer *renderer, const RectF &rect, const PointF &disp);
		public:
			RectF getClientRect() override;
			RectF getRenderRect() override;

			bool setAlign(const Align value) override;
			bool setConstraints(const RectF &value) override;
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			IListItemOwner *QueryListItemOwner() override;

			bool InsertItem(IListItem *item, const int before) override;
			bool DeleteItem(const int index) override;
			bool DeleteItem(IListItem *item) override;
			bool DeleteItems() override;

			IListItemStatusPanelLabel *getPanel(const int index) override;
			IListItemStatusPanelLabel *getPanel(const String &name) override;

			CStatusBar();
			CStatusBar(IForm *parent);
			~CStatusBar() override;

			// Return layout properties
			RectF getOuterBorderWidth() const;
			RectF getInnerBorderWidth() const;
			RectF getBorderRadius() const;
			BorderColor getOuterBorderColor() const;
			Color getLeftOuterBorderColor() const;
			Color getTopOuterBorderColor() const;
			Color getRightOuterBorderColor() const;
			Color getBottomOuterBorderColor() const;
			BorderColor getInnerBorderColor() const;
			Color getLeftInnerBorderColor() const;
			Color getTopInnerBorderColor() const;
			Color getRightInnerBorderColor() const;
			Color getBottomInnerBorderColor() const;
			Color getBackgroundColor() const;
			Gradient *getBackgroundGradient();
			Color getShadowColor() const;
			PointF getShadowShift() const;
			int getShadowRadius() const;
			float getSeparatorWidth() const;
			Color getSeparatorColor() const;
			Gradient *getSeparatorGradient();

			// Set layout properties
			bool setOuterBorderWidth(const RectF &value);
			bool setInnerBorderWidth(const RectF &value);
			bool setBorderRadius(const RectF &value);
			bool setOuterBorderColor(const BorderColor &value);
			bool setLeftOuterBorderColor(const Color &value);
			bool setTopOuterBorderColor(const Color &value);
			bool setRightOuterBorderColor(const Color &value);
			bool setBottomOuterBorderColor(const Color &value);
			bool setInnerBorderColor(const BorderColor &value);
			bool setLeftInnerBorderColor(const Color &value);
			bool setTopInnerBorderColor(const Color &value);
			bool setRightInnerBorderColor(const Color &value);
			bool setBottomInnerBorderColor(const Color &value);
			bool setBackgroundColor(const Color &value);
			bool setShadowColor(const Color &value);
			bool setShadowShift(const PointF &value);
			bool setShadowRadius(const int value);
			bool setSeparatorWidth(const float value);
			bool setSeparatorColor(const Color &value);

			bool Add(const String &caption, const float width = 50); // Add new panel
			bool Insert(const String &caption, const int before, const float width = 50); // Insert new panel before specified one
		};
	}
}