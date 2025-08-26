#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Variant.h"
#include "../../Controls/IRegistration.h"

namespace nitisa
{
	namespace coolwidgets
	{
		extern const String PropertyHandlerRegistrationData;

		bool operator!=(const IRegistration::RegistrationData &a, const IRegistration::RegistrationData &b);
		String ToString(const IRegistration::RegistrationData &value);
		String AsSourceCode(const IRegistration::RegistrationData &value);
		Variant ToVariant(const IRegistration::RegistrationData &value);
		void FromVariant(const Variant &src, IRegistration::RegistrationData &value);
	}
}