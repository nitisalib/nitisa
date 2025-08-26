// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	class IControl;
	class IFont;
	class IListItem;
	class IRenderer;
	class IStyle;

	// Interface for communication with parent control
	class IListItemOwner
	{
	protected:
		IListItemOwner() = default;
		~IListItemOwner() = default;
		IListItemOwner(const IListItemOwner &other) = delete;
		IListItemOwner(IListItemOwner &&other) = delete;
		IListItemOwner &operator=(const IListItemOwner &other) = delete;
		IListItemOwner &operator=(IListItemOwner &&other) = delete;
	public:
		virtual IControl *getControl() = 0; // Return associated control
		virtual IRenderer *getRenderer() = 0; // Return renderer
		virtual IFont *getFont(IListItem *item) = 0; // Return font of associated control. It is allowed to return different font for different item
		virtual IStyle *getStyle(IListItem *item) = 0; // Return associated control style. It is allowed to return different style for different item
		virtual bool isIgnoreSizeChange() = 0; // Return whether size change notification should be ignored. By default false
		virtual bool isIgnoreRepaintRequired() = 0; // Return whether repaint notification should be ignored. By default false
		virtual bool isIgnoreShow() = 0; // Return whether show notification should be ignored. By default false
		virtual bool isIgnoreHide() = 0; // Return whether hide notification should be ignored. By default false
		virtual bool isIgnoreEnable() = 0; // Return whether enable notification should be ignored. By default false
		virtual bool isIgnoreDisable() = 0; // Return whether disable notification should be ignored. By default false
		virtual bool isIgnoreSelect() = 0; // Return whether select notification should be ignored. By default false
		virtual bool isIgnoreDeselect() = 0; // Return whether unselect notification should be ignored. By default false
		virtual bool isIgnoreActivate() = 0; // Return whether activate notification should be ignored. By default false
		virtual bool isIgnoreDeactivate() = 0; // Return whether deactivate notification should be ignored. By default false

		virtual void setIgnoreSizeChange(const bool value) = 0; // Set whether size change notification should be ignored
		virtual void setIgnoreRepaintRequired(const bool value) = 0; // Set whether repaint notification should be ignored
		virtual void setIgnoreShow(const bool value) = 0; // Set whether show notification should be ignored
		virtual void setIgnoreHide(const bool value) = 0; // Set whether hide notification should be ignored
		virtual void setIgnoreEnable(const bool value) = 0; // Set whether enable notification should be ignored
		virtual void setIgnoreDisable(const bool value) = 0; // Set whether disable notification should be ignored
		virtual void setIgnoreSelect(const bool value) = 0; // Set whether select notification should be ignored
		virtual void setIgnoreDeselect(const bool value) = 0; // Set whether unselect notification should be ignored
		virtual void setIgnoreActivate(const bool value) = 0; // Set whether activate notification should be ignored
		virtual void setIgnoreDeactivate(const bool value) = 0; // Set whether deactivate notification should be ignored

		virtual void Release() = 0; // Destroy instance

		virtual void NotifyOnSizeChange(IListItem *item) = 0; // Called by list item when any property required size change where changed
		virtual void NotifyOnRepaintRequired(IListItem *item) = 0; // Called by list item when it should be repainted due to properties change
		virtual void NotifyOnBeforeAddItem(IListItem *item, IListItem *parent) = 0; // Called before item added(owner may lock repaint and repaint old own area on form)
		virtual void NotifyOnAddItem(IListItem *item) = 0; // Called by list item after child list item added to it. Called only for "item", not called for item's children
		virtual void NotifyOnBeforeDeleteItem(IListItem *item) = 0; // Called before item removing(owner may lock repaint and repaint old own area on form). Don't called for subitems
		virtual void NotifyOnDeleteItem(IListItem *item, IListItem *parent) = 0; // Called by list item after child list item removal. May be called after NotifyOnBeforeDeleteItem(). Don't called for subitems
		virtual void NotifyOnBeforeDeleteItems(IListItem *parent) = 0; // Called by list item before all child list items removal. Don't called for subitems
		virtual void NotifyOnDeleteItems(IListItem *parent) = 0; // Called by list item after all child list items removal. Don't called for subitems
		virtual void NotifyOnShow(IListItem *item) = 0; // Called when item become visible
		virtual void NotifyOnHide(IListItem *item) = 0; // Called when item become invisible
		virtual void NotifyOnEnable(IListItem *item) = 0; // Called when item become enabled
		virtual void NotifyOnDisable(IListItem *item) = 0; // Called when item become disabled
		virtual void NotifyOnSelect(IListItem *item) = 0; // Called when item become selected
		virtual void NotifyOnDeselect(IListItem *item) = 0; // Called when item become unselected
		virtual void NotifyOnActivate(IListItem *item) = 0; // Called when item become active
		virtual void NotifyOnDeactivate(IListItem *item) = 0; // Called when item become inactive
	};
}