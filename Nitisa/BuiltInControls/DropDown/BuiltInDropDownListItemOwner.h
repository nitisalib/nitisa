// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/ListItemOwner.h"

namespace nitisa
{
	class IControl;
	class IFont;
	class IListItem;
	class IRenderer;
	class IStyle;

	class CBuiltInDropDown;

	class CBuiltInDropDownListItemOwner :public CListItemOwner
	{
	private:
		CBuiltInDropDown * m_pDropDown;
	public:
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

		CBuiltInDropDownListItemOwner(CBuiltInDropDown *dropdown); // Constructor
	};
}