// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/Color.h"
#include "Standard/ListItems/TreeViewLabel/ListItemTreeViewLabel.h"
#include "../IHierarchyEditor.h"

namespace nitisa
{
	class IComponent;
	class IControl;
	class IListItem;
	class IPropertyList;

	namespace ide
	{
		class CListItemHierarchyEditor :public virtual IListItemHierarchyEditor, public standard::CListItemTreeViewLabel
		{
		private:
			IComponent *m_pAssignedComponent;
			IControl *m_pAssignedControl;
			IListItem *m_pAssignedListItem;
			IPropertyList *m_pPropertyList;
			Color m_sInvisibleColor;
		protected:
			Color getCustomColor(const State state) override;
		public:
			IComponent *getAssignedComponent() override;
			IControl *getAssignedControl() override;
			IListItem *getAssignedListItem() override;
			IPropertyList *getPropertyList() override;

			void setPropertyList(IPropertyList *value) override;

			CListItemHierarchyEditor(IComponent *component, IControl *control, IListItem *item);
			CListItemHierarchyEditor(const String &caption, IComponent *component, IControl *control, IListItem *item);
			~CListItemHierarchyEditor() override;
		};
	}
}