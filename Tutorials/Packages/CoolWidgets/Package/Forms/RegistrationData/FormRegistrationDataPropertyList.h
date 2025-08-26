#pragma once

#include "Nitisa/Package/PropertyLists/FormPropertyList.h"

namespace nitisa
{
	class IForm;
	class IPackage;
	class IPackageEntity;

	namespace coolwidgets
	{
		class CFormRegistrationDataPropertyList :public CFormPropertyList
		{
		public:
			CFormRegistrationDataPropertyList(IPackage *package, IForm *form, IPackageEntity *entity);
		};
	}
}