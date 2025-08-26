#pragma once

#include "Nitisa/Package/Interfaces/IProperty.h"
#include "../../Controls/IRegistration.h"

namespace nitisa
{
	namespace coolwidgets
	{
		class IPropertyRegistrationData :public virtual IProperty
		{
		public:
			virtual IRegistration::RegistrationData getValue() = 0;

			virtual bool setValue(const IRegistration::RegistrationData value) = 0;
		};
	}
}