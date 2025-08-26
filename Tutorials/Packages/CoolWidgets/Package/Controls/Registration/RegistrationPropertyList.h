#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/ControlPropertyList.h"
#include "../../../Controls/Registration/Registration.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace coolwidgets
	{
		class CRegistrationPropertyList :public CControlPropertyList
		{
		private:
			static StringArray StateItems();
			static CRegistration::State StringToState(const String &state);
		public:
			CRegistrationPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}