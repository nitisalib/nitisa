// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace standard
	{
	#pragma region Constructor & destructor
		CCustomDrawGridService::CCustomDrawGridService(CCustomDrawGrid *control) :
			CCustomGridService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Cell status change notifications
		void CCustomDrawGridService::NotifyOnMouseDownCell(const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			m_pControl->m_sDownCell = Point{ column, row };
		}

		void CCustomDrawGridService::NotifyOnMouseUpCell(const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			NotifyOnMouseDownCancel();
		}

		void CCustomDrawGridService::NotifyOnMouseDownCancel()
		{
			if (m_pControl->m_sDownCell != Point{ -1, -1 })
			{
				m_pControl->m_sDownCell = Point{ -1, -1 };
				m_pControl->ForceRepaint();
			}
		}
	#pragma endregion
	}
}