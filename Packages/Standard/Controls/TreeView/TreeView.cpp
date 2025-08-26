// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		CTreeView::CTreeView() :
			CCustomTreeView(L"TreeView"),
			m_pOwner{ nullptr },
			m_pImageList{ nullptr }
		{
			setService(new CTreeViewService(this), true);
		}

		CTreeView::CTreeView(IControl *parent) :CTreeView()
		{
			setParent(parent);
		}

		CTreeView::CTreeView(IForm *parent) : CTreeView()
		{
			setForm(parent);
		}

		CTreeView::~CTreeView()
		{
			if (m_pOwner)
				m_pOwner->Release();
		}
	#pragma endregion

	#pragma region Interfaces getters
		int CTreeView::getItemCount()
		{
			return getRootItem()->getItemCount();
		}

		IListItemTreeViewLabel *CTreeView::getItem(const int index)
		{
			return cast<IListItemTreeViewLabel*>(getRootItem()->getItem(index));
		}
	#pragma endregion

	#pragma region Getters
		IImageList *CTreeView::getImageList()
		{
			return m_pImageList;
		}
	#pragma endregion

	#pragma region Setters
		bool CTreeView::setImageList(IImageList *value)
		{
			if (value != m_pImageList)
			{
				m_pImageList = value;
				LockUpdate();
				UnlockUpdate();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface helpers
		IListItemOwner *CTreeView::QueryListItemOwner()
		{
			if (!m_pOwner)
				m_pOwner = new CTreeViewListItemOwner(this);
			return m_pOwner;
		}
	#pragma endregion

	#pragma region Items
		bool CTreeView::Add(IListItemTreeViewLabel *item)
		{
			return getRootItem()->AddItem(item);
		}

		bool CTreeView::Add(const String &caption)
		{
			return getRootItem()->AddItem(new CListItemTreeViewLabel(caption));
		}

		bool CTreeView::Delete(const int index)
		{
			return getRootItem()->DeleteItem(index);
		}

		bool CTreeView::Clear()
		{
			return getRootItem()->DeleteItems();
		}
	#pragma endregion
	}
}