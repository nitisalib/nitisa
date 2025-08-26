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
	class IComponent;
	class IEventList;
	class IPackageComponent;
	class IPropertyList;

	namespace fb
	{
		class CComponentList
		{
		private:
			std::vector<COMPONENT_INFO*> m_aComponents;
			std::vector<COMPONENT_INFO*> m_aSortedComponents;
			bool m_bSorted;
			COMPONENT_INFO m_sSearch;

			void Sort();
		public:
			CComponentList();
			~CComponentList();

			int getCount() const;
			COMPONENT_INFO *getInfo(const int index);
			COMPONENT_INFO *getInfo(IComponent *component);

			bool Add(IComponent *component, IEventList *events, IPropertyList *properties, IPackageComponent *package_component, const int index);
			bool Delete(const int index);
			bool Delete(IComponent *component);
			bool Clear();
		};
	}
}