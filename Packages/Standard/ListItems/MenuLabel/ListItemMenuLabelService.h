// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Key.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "../Menu/ListItemMenuService.h"

namespace nitisa
{
	class ITexture;

	struct Block;

	namespace standard
	{
		class CListItemMenuLabel;

		class CListItemMenuLabelService :public CListItemMenuService
		{
		private:
			CListItemMenuLabel *m_pItem;
			bool m_bMouseDown;
		public:
			CListItemMenuLabelService(CListItemMenuLabel *item);

			PointF getRequiredSize() override;
			float getHotkeyWidth() override;

			bool setDPI(const Point &value) override;
			bool setHotkeyWidth(const float value) override;

			void UpdateFromStyle() override;
			void Render(const Mat4f &matrix, const Block *block, const bool last_pass, ITexture **clip) override;

			bool NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift) override; // Only Enter accepted
			bool NotifyOnMouseDown(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			void NotifyOnMouseDownCancel() override;
			bool NotifyOnMouseUp(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override; // Only left button accepted if it was down before
			bool NotifyOnHotkey() override;
		};
	}
}