// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IListItemService.h"
#include "../Math/Mat4f.h"
#include "../Math/Point.h"
#include "../Math/PointF.h"
#include "Key.h"
#include "Strings.h"

namespace nitisa
{
	class IListItem;
	class IListItemOwner;
	class ITexture;

	class CListItem;

	struct Block;

	class CListItemService :public virtual IListItemService
	{
	private:
		CListItem *m_pListItem;
	public:
		IListItemOwner *getOwner() override;
		PointF getRequiredSize() override;

		bool setOwner(IListItemOwner *value) override;
		bool setParent(IListItem *value) override;
		bool setSize(const PointF &value) override;
		bool setPosition(const PointF &value) override;
		bool setHovered(const bool value) override;
		bool setDPI(const Point &value) override; // Do nothing. Return false. Should be implemented by child class

		void Release() override;
		void UpdateFromStyle() override;
		void Render(const Mat4f &matrix, const Block *block, const bool last_pass, ITexture **clip) override;
		bool MoveItem(IListItem *item, const int before) override;

		void NotifyOnFreeResources() override;
		bool NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseDown(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		void NotifyOnMouseDownCancel() override;
		bool NotifyOnMouseMove(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseUp(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseDoubleClick(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseVerticalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta) override;
		bool NotifyOnMouseHorizontalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta) override;
		bool NotifyOnDropFiles(const PointF &position, const StringArray &filenames) override;

		CListItemService(CListItem *listitem);
		virtual ~CListItemService() = default;
	};
}