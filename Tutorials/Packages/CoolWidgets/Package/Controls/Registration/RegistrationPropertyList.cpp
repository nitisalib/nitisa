#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
		CRegistrationPropertyList::CRegistrationPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			// Delete unused properties
			Delete(L"TransformControls");
			Delete(L"Constraints");
			Delete(L"Size");
			Delete(L"Align");
			Delete(L"Enabled");

			// Add simple property called "BackgroundColor"
			Add(new CPropertyColor(
				this,
				control,
				L"BackgroundColor",
				false,
				nullptr,
				[](IClass *parent) { return cast<CRegistration*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) { return cast<CRegistration*>(parent)->setBackgroundColor(value); }));

			// Add multi-state property called "InputBorderColor"
			Add(new CPropertyColorState(
				this,
				control,
				L"InputBorderColor",
				false,
				StateItems(),
				ExportPrefixType::NamespaceParent,
				L"",
				nullptr,
				[](IClass *parent, const String &state) { return cast<CRegistration*>(parent)->getInputBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CRegistration*>(parent)->setInputBorderColor(StringToState(state), value); }));

			// Add custom RegistrationData property
			Add(new CPropertyRegistrationData(
				this,
				control,
				L"RegistrationData",
				false,
				nullptr,
				[](IClass *parent) { return cast<CRegistration*>(parent)->getRegistrationData(); },
				[](IClass *parent, const IRegistration::RegistrationData value) { return cast<CRegistration*>(parent)->setRegistrationData(value); }));
		}

		StringArray CRegistrationPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active"
			};
		}

		CRegistration::State CRegistrationPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CRegistration::State::Active;
			return CRegistration::State::Normal;
		}
	}
}