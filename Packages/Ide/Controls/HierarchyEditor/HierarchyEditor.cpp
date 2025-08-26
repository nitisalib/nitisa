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
	namespace ide
	{
	#pragma region Constructor & destructor
		CHierarchyEditor::CHierarchyEditor() :
			CCustomTreeView(L"HierarchyEditor"),
			m_pOwner{ nullptr },
			m_pImageList{ nullptr }
		{
			setService(new CHierarchyEditorService(this), true);
		}

		CHierarchyEditor::CHierarchyEditor(IControl *parent) :CHierarchyEditor()
		{
			setParent(parent);
		}

		CHierarchyEditor::CHierarchyEditor(IForm *parent) : CHierarchyEditor()
		{
			setForm(parent);
		}

		CHierarchyEditor::~CHierarchyEditor()
		{
			if (m_pOwner)
				m_pOwner->Release();
		}

		void CHierarchyEditor::BeforeRelease()
		{
			getRootItem()->DeleteItems();
			CCustomTreeView::BeforeRelease();
		}
	#pragma endregion

	#pragma region Interfaces getters
		int CHierarchyEditor::getItemCount()
		{
			return getRootItem()->getItemCount();
		}

		IListItemHierarchyEditor *CHierarchyEditor::getItem(const int index)
		{
			return cast<IListItemHierarchyEditor*>(getRootItem()->getItem(index));
		}
	#pragma endregion

	#pragma region Getters
		standard::IImageList *CHierarchyEditor::getImageList()
		{
			return m_pImageList;
		}
	#pragma endregion

	#pragma region Setters
		bool CHierarchyEditor::setImageList(standard::IImageList *value)
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
		IListItemOwner *CHierarchyEditor::QueryListItemOwner()
		{
			if (!m_pOwner)
				m_pOwner = new CListItemOwner(this);
			return m_pOwner;
		}
	#pragma endregion

	#pragma region Helpers
		bool CHierarchyEditor::Add(IListItem *parent, IListItemHierarchyEditor *item, IControl *parent_control, const bool unfold)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				IListItemHierarchyEditor *t{ cast<IListItemHierarchyEditor*>(parent->getItem(i)) };
				if (t && t->getAssignedControl() == parent_control)
				{
					if (unfold)
						setFolded(t, false);
					return t->AddItem(item);
				}
				if (Add(t, item, parent_control, unfold))
				{
					if (unfold)
						setFolded(t, false);
					return true;
				}
			}
			return false;
		}

		IListItemHierarchyEditor *CHierarchyEditor::Find(IListItem *parent, IListItem *item)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				IListItemHierarchyEditor *t{ cast<IListItemHierarchyEditor*>(parent->getItem(i)) };
				if (t && t->getAssignedListItem() == item)
					return t;
				t = Find(t, item);
				if (t)
					return t;
			}
			return nullptr;
		}

		IListItemHierarchyEditor *CHierarchyEditor::Find(IListItem *parent, IComponent *component, IControl *control)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				IListItemHierarchyEditor *t{ cast<IListItemHierarchyEditor*>(parent->getItem(i)) };
				if (t && t->getAssignedComponent() == component && t->getAssignedControl() == control)
					return t;
				t = Find(t, component, control);
				if (t)
					return t;
			}
			return nullptr;
		}
	#pragma endregion

	#pragma region Items
		IListItemHierarchyEditor *CHierarchyEditor::Add(IListItemHierarchyEditor *item)
		{
			if (getRootItem()->AddItem(item))
				return item;
			if (item)
				item->Release();
			return nullptr;
		}

		IListItemHierarchyEditor *CHierarchyEditor::Add(const String &caption, IComponent *component, IControl *control, IListItem *item)
		{
			IListItemHierarchyEditor *result{ new CListItemHierarchyEditor(caption, component, control, item) };
			if (getRootItem()->AddItem(result))
				return result;
			result->Release();
			return nullptr;
		}

		IListItemHierarchyEditor *CHierarchyEditor::Add(const String &caption, IComponent *component, IControl *control, IListItem *item, IControl *parent, const bool unfold)
		{
			IListItemHierarchyEditor *result{ new CListItemHierarchyEditor(caption, component, control, item) };
			if (Add(getRootItem(), result, parent, unfold))
				return result;
			result->Release();
			return nullptr;
		}

		bool CHierarchyEditor::Delete(const int index)
		{
			return getRootItem()->DeleteItem(index);
		}

		bool CHierarchyEditor::Clear()
		{
			LockUpdate();
			bool result{ getRootItem()->DeleteItems() };
			UnlockUpdate();
			return result;
		}

		IListItemHierarchyEditor *CHierarchyEditor::Find(IComponent *component, IControl *control, IListItem *item)
		{
			if (item)
				return Find(getRootItem(), item);
			return Find(getRootItem(), component, control);
		}

		bool CHierarchyEditor::DeleteEx(IComponent *component, IControl *control, IListItem *item)
		{
			IListItemHierarchyEditor *i{ Find(component, control, item) };
			if (i)
				return i->getParent()->DeleteItem(i);
			return false;
		}

		bool CHierarchyEditor::SelectEx(IComponent *component, IControl *control, IListItem *item, const bool selected, const bool active)
		{
			IListItemHierarchyEditor *i{ Find(component, control, item) };
			if (i)
			{
				bool result{ i->setSelected(selected) };
				result = i->setActive(active) || result;
				return result;
			}
			return false;
		}

		void CHierarchyEditor::CollectSelected(IListItem *parent, std::vector<IListItemHierarchyEditor*> &items)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				IListItemHierarchyEditor *item{ cast<IListItemHierarchyEditor*>(parent->getItem(i)) };
				if (item->isSelected())
					items.push_back(item);
				CollectSelected(item, items);
			}
		}

		bool CHierarchyEditor::isMovable(IListItemHierarchyEditor *target)
		{
			std::vector<IListItemHierarchyEditor*> items;
			bool move_items;
			return isMovable(target, items, move_items);
		}

		bool CHierarchyEditor::isMovable(IListItemHierarchyEditor *target, std::vector<IListItemHierarchyEditor*> &items, bool &move_items)
		{
			if (target && !target->getAssignedControl() && !target->getAssignedListItem())
				return false;
			CollectSelected(getRootItem(), items);
			bool has_controls{ false }, has_items{ false };
			IListItemHierarchyEditor *control{ nullptr }, *item{ nullptr };
			for (auto pos : items)
				if (pos->getAssignedListItem())
				{
					if (has_items && pos->getParent() != item->getParent())
						return false;
					has_items = true;
					item = pos;
				}
				else if (pos->getAssignedControl())
				{
					if (has_controls && pos->getParent() != control->getParent())
						return false;
					has_controls = true;
					control = pos;
				}
				else
					return false;
			if (has_items && !has_controls) // Attempt to move items
			{
				if (target && target->getAssignedControl() == item->getAssignedControl() && target->getAssignedComponent() == item->getAssignedComponent()) // Items can be moved only inside component/control
				{
					IComponentItemTree *c{ cast<IComponentItemTree*>(target->getAssignedControl() ? target->getAssignedControl() : target->getAssignedComponent()) };
					if (c)
					{
						move_items = true;
						if (target->getAssignedListItem()) // Try move to another list item
						{
							if (!target->getAssignedListItem()->isSelected() && target->getAssignedListItem()->getParent() != item->getParent())
							{
								IListItem *parent{ target->getAssignedListItem()->getParent() };
								bool has_selected{ false };
								while (parent)
								{
									if (parent->isSelected())
									{
										has_selected = true;
										break;
									}
									parent = parent->getParent();
								}
								if (!has_selected)
									return true;
							}
						}
						else // Try move to root
						{
							if (c->getRootItem() != item->getParent())
								return true;
						}
					}
				}
			}
			else if (has_controls && !has_items) // Attempt to move controls
			{
				move_items = false;
				if (target)
				{
					if (target->getAssignedControl() == control->getAssignedControl()->getParent())
						return false;
					if (!target->getAssignedControl()->isAcceptControls())
						return false;
					IListItem *li{ target };
					bool has_selected{ false };
					while (li)
					{
						if (li->isSelected())
						{
							has_selected = true;
							break;
						}
						li = li->getParent();
					}
					if (!has_selected)
						return true;
				}
				else
				{
					if (control->getParent() != getRootItem())
						return true;
				}
			}
			return false;
		}

		bool CHierarchyEditor::DeselectAllListItems()
		{
			CLockRepaint lock{ this };
			return DeselectAllListItems(getRootItem());
		}

		bool CHierarchyEditor::DeselectAllListItems(IListItem *parent)
		{
			bool result{ false };
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				IListItemHierarchyEditor *h{ cast<IListItemHierarchyEditor*>(parent->getItem(i)) };
				if (h && h->getAssignedListItem() && h->isSelected())
					result = h->setSelected(false) || result;
				result = DeselectAllListItems(parent->getItem(i)) || result;
			}
			return result;
		}

		bool CHierarchyEditor::DeselectAll()
		{
			CLockRepaint lock{ this };
			return DeselectAll(getRootItem());
		}

		bool CHierarchyEditor::DeselectAll(IListItem *parent)
		{
			bool result{ false };
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				result = parent->getItem(i)->setSelected(false) || result;
				result = DeselectAll(parent->getItem(i)) || result;
			}
			return result;
		}

		bool CHierarchyEditor::DeleteSelected()
		{
			return DeleteSelected(getRootItem());
		}

		bool CHierarchyEditor::DeleteSelected(IListItem *parent)
		{
			bool result{ false };
			int i{ 0 };
			while (i < parent->getItemCount())
				if (parent->getItem(i)->isSelected())
				{
					IListItemHierarchyEditor *item{ cast<IListItemHierarchyEditor*>(parent->getItem(i)) };
					if (item)
					{
						if (item->getAssignedListItem())
						{
							if (item->getAssignedListItem()->getParent())
								item->getAssignedListItem()->getParent()->DeleteItem(item->getAssignedListItem());
							else
							{
								IComponentItemList *list{ cast<IComponentItemList*>(item->getAssignedComponent()) };
								if (list)
									list->DeleteItem(item->getAssignedListItem());
							}
							parent->DeleteItem(i);
						}
						else
						{
							if (item->getAssignedControl())
								item->getAssignedControl()->Release();
							else
								item->getAssignedComponent()->Release();
						}
					}
					result = true;
				}
				else
				{
					result = DeleteSelected(parent->getItem(i)) || result;
					i++;
				}
			return result;
		}
	#pragma endregion
	}
}