// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Key.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/FormService.h"
#include "Nitisa/Math/IntegerArray.h"

namespace nitisa
{
	class IComponent;
	class IControl;
	class IWindowListenerOnMessage;

	namespace fb
	{
		class CFormMain;

		class CFormMainService :public CFormService
		{
			friend CFormMain;
		private:
			CFormMain *m_pForm;
			bool m_bIgnoreDetach;

			void EnumControls(StringArray &names, IControl *control, IControl *exclude);
			void EnumTabOrders(IntegerArray &orders, IControl *control);
		public:
			CFormMainService(CFormMain *form);

			void UpdateTabOrders(const int old_tab_order, const int new_tab_order) override;
			String GenerateComponentName(IComponent *component) override;
			String GenerateControlName(IControl *control) override;
			int GenerateTabOrder(IControl *control) override;
			bool RegisterHotkey(IComponent *component, const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down) override;
			bool RegisterHotkey(IControl *control, const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down) override;
			bool RegisterMessageListener(IComponent *component, IWindowListenerOnMessage *listener) override;

			// Component notifications
			void NotifyOnComponentAttach(IComponent *component) override;
			void NotifyOnComponentDetach(IComponent *component) override;

			// Control notifications
			void NotifyOnControlAttach(IControl *control) override;
			void NotifyOnControlDetach(IControl *control) override;
		};
	}
}