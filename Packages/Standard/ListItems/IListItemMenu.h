// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Hotkey.h"
#include "Nitisa/Core/Key.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IListItem.h"
#include "Nitisa/Interfaces/IListItemService.h"
#include "Nitisa/Math/RectF.h"

namespace nitisa
{
	class ITexture;

	namespace standard
	{
		class IListItemMenu;

		// Menu items have icon, caption, hotkey, and arrow areas
		class IListItemMenuService :public virtual IListItemService
		{
		protected:
			IListItemMenuService() = default;
			~IListItemMenuService() = default;
			IListItemMenuService(const IListItemMenuService &other) = delete;
			IListItemMenuService(IListItemMenuService &&other) = delete;
			IListItemMenuService &operator=(const IListItemMenuService &other) = delete;
			IListItemMenuService &operator=(IListItemMenuService &&other) = delete;
		public:
			virtual float getIconWidth() = 0; // Return max between current set icon area width and min required icon area width including spacings
			virtual float getHotkeyWidth() = 0; // Return max between current set hotkey area width and min required hotkey area width including spacings
			virtual float getArrowWidth() = 0; // Return max between current set arrow area width and min required arrow area width including spacings

			virtual bool setIconWidth(const float value) = 0; // With spacings. Should be set before getting real required size
			virtual bool setHotkeyWidth(const float value) = 0; // With spacings. Should be set before getting real required size
			virtual bool setArrowWidth(const float value) = 0; // With spacings. Should be set before getting real required size

			virtual bool NotifyOnHotkey() = 0; // Called by owner when hotkey corresponding to item found. Should return true if processed(it owner is menu it will be closed it this method return true)
		};

		class IListItemMenuOwner :public virtual IListItemOwner
		{
		protected:
			IListItemMenuOwner() = default;
			~IListItemMenuOwner() = default;
			IListItemMenuOwner(const IListItemMenuOwner &other) = delete;
			IListItemMenuOwner(IListItemMenuOwner &&other) = delete;
			IListItemMenuOwner &operator=(const IListItemMenuOwner &other) = delete;
			IListItemMenuOwner &operator=(IListItemMenuOwner &&other) = delete;
		public:
			virtual ITexture *getImage(const bool enabled, const bool active, const bool hovered, const int index, RectF &rect) = 0; // Return image. To handle icons

			virtual void NotifyOnAddHotkey(IListItemMenu *listitem, const Hotkey &hotkey) = 0; // Notify about hotkey added
			virtual void NotifyOnDeleteHotkey(IListItemMenu *listitem, const Hotkey &hotkey) = 0; // Notify about hotkey deleted
		};

		// Difference from IListItem in 3 mandatory parts: icon, hotkey, and arrow(for subitems)
		class IListItemMenu :public virtual IListItem
		{
		protected:
			IListItemMenu() = default;
			~IListItemMenu() = default;
			IListItemMenu(const IListItemMenu &other) = delete;
			IListItemMenu(IListItemMenu &&other) = delete;
			IListItemMenu &operator=(const IListItemMenu &other) = delete;
			IListItemMenu &operator=(IListItemMenu &&other) = delete;
		public:
			virtual int getHotkeyCount() = 0; // Return hotkey count
			virtual Hotkey getHotkey(const int index) = 0; // Return hotkey by index
			virtual String getHotkeys() = 0; // Return hotkeys string representation

			virtual bool AddHotkey(const Key key, const bool ctrl, const bool alt, const bool shift, const bool down) = 0; // Add hotkey
			virtual bool DeleteHotkey(const int index) = 0; // Delete hotkey by index
			virtual bool DeleteHotkeys() = 0; // Delete all hotkeys
		};
	}
}