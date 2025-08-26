// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "CustomTreeViewService.h"

namespace nitisa
{
	class IComponent;

	namespace standard
	{
		class CTreeView;

		class CTreeViewService :public CCustomTreeViewService
		{
		private:
			CTreeView *m_pTreeView;
		public:
			// Component notifications
			void NotifyOnComponentDetach(IComponent *component) override;
			void NotifyOnComponentChange(IComponent *component) override;

			CTreeViewService(CTreeView *treeview);
		};
	}
}