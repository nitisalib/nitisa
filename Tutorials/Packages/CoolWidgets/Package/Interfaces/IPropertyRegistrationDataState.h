#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/Interfaces/IPropertyState.h"
#include "../../Controls/IRegistration.h"

namespace nitisa
{
	namespace coolwidgets
	{
		class IPropertyRegistrationDataState :public virtual IPropertyState
		{
		public:
			virtual IRegistration::RegistrationData getValue(const String &state) = 0;

			virtual bool setValue(const String &state, const IRegistration::RegistrationData value) = 0;
		};
	}
}