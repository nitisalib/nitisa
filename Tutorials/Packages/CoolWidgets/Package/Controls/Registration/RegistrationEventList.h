#pragma once

#include "Nitisa/Package/EventLists/ControlEventList.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace coolwidgets
	{
		class CRegistrationEventList :public CControlEventList
		{
		public:
			CRegistrationEventList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}