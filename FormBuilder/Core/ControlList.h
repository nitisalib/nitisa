// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Types.h"
#include <vector>

namespace nitisa
{
	class IControl;
	class IEventList;
	class IPackageControl;
	class IPropertyList;

	namespace fb
	{
		class CControlList
		{
		private:
			std::vector<CONTROL_INFO*> m_aControls;
			std::vector<CONTROL_INFO*> m_aSortedControls;
			bool m_bSorted;
			CONTROL_INFO m_sSearch;

			void Sort();
		public:
			CControlList();
			~CControlList();

			int getCount() const;
			CONTROL_INFO *getInfo(const int index);
			CONTROL_INFO *getInfo(IControl *control);

			bool Add(IControl *control, IEventList *events, IPropertyList *properties, IPackageControl *package_control, const int index);
			bool Delete(const int index);
			bool Delete(IControl *control);
			bool Clear();
		};
	}
}