#pragma once

#include "Nitisa/Package/EventLists/FormEventList.h"

namespace nitisa
{
	class IForm;
	class IPackage;
	class IPackageEntity;

	namespace coolwidgets
	{
		class CFormRegistrationDataEventList :public CFormEventList
		{
		public:
			CFormRegistrationDataEventList(IPackage *package, IForm *form, IPackageEntity *entity);
		};
	}
}