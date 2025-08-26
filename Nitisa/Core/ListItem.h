// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IListItem.h"
#include "../Math/PointF.h"
#include "Class.h"
#include "Strings.h"
#include <vector>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IFont;
	class IListItemOwner;
	class IListItemService;

	class CListItemService;

	class CListItem :public virtual IListItem, public CClass
	{
		friend CListItemService;
	private:
		PointF m_sSize;
		PointF m_sPosition;
		bool m_bVisible;
		bool m_bEnabled;
		bool m_bHovered;
		bool m_bSelected;
		bool m_bActive;
		IListItemService *m_pService;
		std::vector<IListItem*> m_aItems;
		IListItemOwner *m_pOwner;
		IListItem *m_pParent;
		bool m_bDestroying;
		bool m_bAcceptItems;
	public:
		IListItem *getParent() override;
		PointF getSize() override;
		PointF getPosition() override;
		int getItemCount(const bool total = false) override;
		IListItem *getItem(const int index) override;
		IListItem *getItem(const String &name) override;
		IListItem *getItem(const PointF &position) override;
		int getItemIndex(IListItem *item) override;
		IFont *getFont() override; // Return nullptr
		bool isVisible() override;
		bool isEnabled() override;
		bool isHovered() override;
		bool isSelected() override;
		bool isActive() override;
		bool hasItem(IListItem *item) override;
		bool isAcceptItems() override;
		bool isAcceptItem(IListItem *item) override;

		bool setName(const String &value) override;
		bool setVisible(const bool value) override;
		bool setEnabled(const bool value) override;
		bool setSelected(const bool value) override;
		bool setActive(const bool value) override;

		bool AddItem(IListItem *item) override;
		bool InsertItem(IListItem *item, const int before) override;
		bool DeleteItem(const int index) override;
		bool DeleteItem(IListItem *item) override;
		bool DeleteItems() override;
		bool DetachItem(IListItem *item) override;

		bool Copy(IListItem *dest) override;

		void Release() override;
		IListItemService *QueryService() override;

		bool BringToFront() override;
		bool BringUp() override;
		bool BringDown() override;
		bool BringBefore(IListItem *item) override;
		bool BringBefore(const int index) override;
		bool BringAfter(IListItem *item) override;
		bool BringAfter(const int index) override;

		/**
		Constructor
		@param class_name Class name of the list item
		@param accept_items Whether child items could be added
		*/
		CListItem(const String &class_name, const bool accept_items);
		virtual ~CListItem();
	};
}