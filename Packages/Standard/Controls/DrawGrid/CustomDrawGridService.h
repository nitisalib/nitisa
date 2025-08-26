// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Math/PointF.h"
#include "CustomGridService.h"

namespace nitisa
{
	class IListItem;

	namespace standard
	{
		class CCustomDrawGrid;

		class CCustomDrawGridService :public CCustomGridService
		{
		private:
			CCustomDrawGrid * m_pControl;
		public:
			// Cell status change notifications
			void NotifyOnMouseDownCell(const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			void NotifyOnMouseUpCell(const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			void NotifyOnMouseDownCancel() override;

			CCustomDrawGridService(CCustomDrawGrid *control);
		};
	}
}