// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Standard/Controls/TreeView/CustomTreeViewService.h"

namespace nitisa
{
	class IComponent;

	namespace ide
	{
		class CHierarchyEditor;

		class CHierarchyEditorService :public nitisa::standard::CCustomTreeViewService
		{
		private:
			CHierarchyEditor *m_pEditor;
		public:
			// Component notifications
			void NotifyOnComponentDetach(IComponent *component) override;
			void NotifyOnComponentChange(IComponent *component) override;

			CHierarchyEditorService(CHierarchyEditor *editor);
		};
	}
}