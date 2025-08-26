#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
		const String PropertyHandlerRegistrationData{ L"RegistrationData" };

		bool operator!=(const IRegistration::RegistrationData &a, const IRegistration::RegistrationData &b)
		{
			return a.FirstName != b.FirstName || a.FirstName != b.LastName || a.Year != b.Year || a.Month != b.Month || a.Day != b.Day;
		}

		String ToString(const IRegistration::RegistrationData &value)
		{
			return value.FirstName + L" " + value.LastName + L", " + nitisa::ToString(value.Month) + L"/" + nitisa::ToString(value.Day) + L"/" + nitisa::ToString(value.Year);
		}

		String AsSourceCode(const IRegistration::RegistrationData &value)
		{
			return
				L"coolwidgets::IRegistration::RegistrationData{ L\"" +
				value.FirstName + L"\", L\"" +
				value.LastName + L"\", " +
				nitisa::ToString(value.Year) + L", " +
				nitisa::ToString(value.Month) + L"," +
				nitisa::ToString(value.Day) +
				L"}";
		}

		Variant ToVariant(const IRegistration::RegistrationData &value)
		{
			Variant result;
			result[L"FirstName"] = value.FirstName;
			result[L"LastName"] = value.LastName;
			result[L"Year"] = value.Year;
			result[L"Month"] = value.Month;
			result[L"Day"] = value.Day;
			return result;
		}

		void FromVariant(const Variant &src, IRegistration::RegistrationData &value)
		{
			if (src.isSet(L"FirstName"))
				value.FirstName = (String)src.get(L"FirstName");
			if (src.isSet(L"LastName"))
				value.LastName = (String)src.get(L"LastName");
			if (src.isSet(L"Year"))
				value.Year = (int)src.get(L"Year");
			if (src.isSet(L"Month"))
				value.Month = (int)src.get(L"Month");
			if (src.isSet(L"Day"))
				value.Day = (int)src.get(L"Day");
		}
	}
}