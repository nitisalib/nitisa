// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace ide
	{
	#pragma region Constructor & destructor
		CListItemHierarchyEditor::CListItemHierarchyEditor(IComponent *component, IControl *control, IListItem *item) :
			CListItemTreeViewLabel(),
			m_pAssignedComponent{ component },
			m_pAssignedControl{ control },
			m_pAssignedListItem{ item },
			m_pPropertyList{ nullptr },
			m_sInvisibleColor{ 127, 127, 127, 255 }
		{

		}

		CListItemHierarchyEditor::CListItemHierarchyEditor(const String &caption, IComponent *component, IControl *control, IListItem *item) :
			CListItemTreeViewLabel(caption),
			m_pAssignedComponent{ component },
			m_pAssignedControl{ control },
			m_pAssignedListItem{ item },
			m_pPropertyList{ nullptr },
			m_sInvisibleColor{ 127, 127, 127, 255 }
		{

		}

		CListItemHierarchyEditor::~CListItemHierarchyEditor()
		{
			if (m_pPropertyList)
				m_pPropertyList->Release();
		}
	#pragma endregion

	#pragma region Interface getters
		IComponent *CListItemHierarchyEditor::getAssignedComponent()
		{
			return m_pAssignedComponent;
		}

		IControl *CListItemHierarchyEditor::getAssignedControl()
		{
			return m_pAssignedControl;
		}

		IListItem *CListItemHierarchyEditor::getAssignedListItem()
		{
			return m_pAssignedListItem;
		}

		IPropertyList *CListItemHierarchyEditor::getPropertyList()
		{
			return m_pPropertyList;
		}

		Color CListItemHierarchyEditor::getCustomColor(const State state)
		{
			if (!m_pAssignedListItem && m_pAssignedControl && !m_pAssignedControl->isVisible(false))
				return m_sInvisibleColor;
			return CListItemTreeViewLabel::getCustomColor(state);
		}
	#pragma endregion

	#pragma region Interface setters
		void CListItemHierarchyEditor::setPropertyList(IPropertyList *value)
		{
			m_pPropertyList = value;
		}
	#pragma endregion
	}
}