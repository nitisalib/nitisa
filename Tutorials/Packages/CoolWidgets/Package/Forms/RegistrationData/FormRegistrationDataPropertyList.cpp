#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
		CFormRegistrationDataPropertyList::CFormRegistrationDataPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyRegistrationData(
				this,
				form,
				L"Value",
				false,
				nullptr,
				[](IClass *parent) { return cast<CFormRegistrationData*>(parent)->getValue(); },
				[](IClass *parent, const IRegistration::RegistrationData value) { return cast<CFormRegistrationData*>(parent)->setValue(value); }));
		}
	}
}