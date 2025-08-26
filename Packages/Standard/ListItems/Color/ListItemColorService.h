// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ListItemService.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"

namespace nitisa
{
	class ITexture;

	struct Block;

	namespace standard
	{
		class CListItemColor;

		class CListItemColorService :public CListItemService
		{
		private:
			CListItemColor *m_pListItem;
			bool m_bDown;
			Point m_sDPI;
		public:
			CListItemColorService(CListItemColor *listitem);

			PointF getRequiredSize() override;

			bool setDPI(const Point &value) override;

			void UpdateFromStyle() override;
			void Render(const Mat4f &matrix, const Block *block, const bool last_pass, ITexture **clip) override;

			bool NotifyOnMouseDown(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			bool NotifyOnMouseUp(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			void NotifyOnMouseDownCancel() override;
		};
	}
}