// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "CustomTreeView.h"
#include "../ITreeView.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IListItemOwner;

	namespace standard
	{
		class IImageList;
		class IListItemTreeViewLabel;

		class CTreeViewService;

		class CTreeView :public virtual ITreeView, public CCustomTreeView
		{
			friend CTreeViewService;
		private:
			IListItemOwner *m_pOwner;
			IImageList *m_pImageList;
		public:
			int getItemCount() override;
			IListItemTreeViewLabel *getItem(const int index) override;

			bool Add(IListItemTreeViewLabel *item) override;
			bool Add(const String &caption) override;
			bool Delete(const int index) override;
			bool Clear() override;

			IListItemOwner *QueryListItemOwner() override;

			CTreeView();
			CTreeView(IControl *parent);
			CTreeView(IForm *parent);
			~CTreeView() override;

			IImageList *getImageList(); // Return associated image list

			bool setImageList(IImageList *value); // Associate image list
		};
	}
}