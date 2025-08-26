#pragma once

#include "../Controls/IRegistration.h"

namespace nitisa
{
	namespace coolwidgets
	{
		class IFormRegistrationData
		{
		public:
			virtual IRegistration::RegistrationData getValue() = 0;

			virtual bool setValue(const IRegistration::RegistrationData &value) = 0;

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}