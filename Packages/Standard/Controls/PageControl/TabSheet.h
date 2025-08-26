// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Align.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IPageControl.h"

namespace nitisa
{
	class IControl;

	namespace standard
	{
		class CTabSheetService;

		class CTabSheet :public virtual ITabSheet, public CControl
		{
			friend CTabSheetService;
		private:
			String m_sCaption;
			int m_iIconIndex;
			bool m_bCaptionChanged;
		public:
			IControl *getControl(const int index) override;
			IControl *getControl(const String &name) override;
			IControl *getControl(const PointF &position) override;

			IPageControl *getPageControl() override;
			int getIndex() override;
			bool isActive() override;
			bool isAcceptControl(IControl *control = nullptr) override;
			String getCaption() override;

			bool setParent(IControl *value) override;
			bool setAlign(const Align value) override;
			bool setConstraints(const RectF &value) override;
			bool setSize(const PointF &value) override;
			bool setZIndex(const int value) override;
			bool setCaption(const String &value) override;

			bool BringToFront() override;
			bool BringUp() override;
			bool BringDown() override;
			bool BringBefore(IControl *control) override;
			bool BringBefore(const int index) override;
			bool BringAfter(IControl *control) override;
			bool BringAfter(const int index) override;

			CTabSheet();
			CTabSheet(IPageControl *parent);

			int getIconIndex() const; // Return icon index

			bool setIconIndex(const int value); // Set icon index
		};
	}
}