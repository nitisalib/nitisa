// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Key.h"
#include "../Core/Strings.h"
#include "../Math/Point.h"
#include "../Math/PointF.h"
#include "../Math/Mat4f.h"

namespace nitisa
{
	class IListItem;
	class IListItemOwner;
	class ITexture;

	struct Block;

	class IListItemService
	{
	protected:
		IListItemService() = default;
		~IListItemService() = default;
		IListItemService(const IListItemService &other) = delete;
		IListItemService(IListItemService &&other) = delete;
		IListItemService &operator=(const IListItemService &other) = delete;
		IListItemService &operator=(IListItemService &&other) = delete;
	public:
		virtual IListItemOwner *getOwner() = 0; // Return attached IListItemOwner interface for communication with owner control
		virtual PointF getRequiredSize() = 0; // Return total required size

		virtual bool setOwner(IListItemOwner *value) = 0; // Should store specified owner
		virtual bool setParent(IListItem *value) = 0; // Should store specified parent
		virtual bool setSize(const PointF &value) = 0; // Should set specified size
		virtual bool setPosition(const PointF &value) = 0; // Should set specified position(it is relative to parent)
		virtual bool setHovered(const bool value) = 0; // Should set flag indication the item is hovered or not
		virtual bool setDPI(const Point &value) = 0; // Adjust list item parameters to specified DPI. Default DPI is { 96, 96 }

		virtual void Release() = 0; // Destroy instance
		virtual void UpdateFromStyle() = 0; // Update list item from style returned by associated list item owner getStyle() method
		virtual void Render(const Mat4f &matrix, const Block *block, const bool last_pass, // Render independently on visibility state
			ITexture **clip) = 0; // If clip is not nullptr it should be used by list item during rendering and prevent creating/destroying new clip texture each time
		virtual bool MoveItem(IListItem *item, const int before) = 0; // Change item position in parent item list. Index should be in range 0..ItemCount, item should be child and it's index should not be equal to index

		// State change notifications
		virtual void NotifyOnFreeResources() = 0; // Should free all renderer and window resources

		// Input notifications(return true if input processed. If so it will be repainted by owner or any other, like menu close, action will be performed)
		virtual bool NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift) = 0; // Called by owner to notify on key down
		virtual bool NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift) = 0; // Called by owner to notify on key release
		virtual bool NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift) = 0; // Called by owner to notify about character received from keyboard input
		virtual bool NotifyOnMouseDown(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) = 0; // Called by owner to notify on mouse button down
		virtual void NotifyOnMouseDownCancel() = 0; // Called by owner to cancel previous mouse down event
		virtual bool NotifyOnMouseMove(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) = 0; // Called by owner to notify on mouse pointer moving
		virtual bool NotifyOnMouseUp(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) = 0; // Called by owner to notify on mouse button release
		virtual bool NotifyOnMouseDoubleClick(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) = 0; // Called by owner to notify on mouse button double click
		virtual bool NotifyOnMouseVerticalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta) = 0; // Called by owner to notify on mouse vertical wheel
		virtual bool NotifyOnMouseHorizontalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta) = 0; // Called by owner to notify on mouse horizontal wheel
		virtual bool NotifyOnDropFiles(const PointF &position, const StringArray &filenames) = 0; // Called by owner to notify about files dropping
	};
}