#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Variant.h"
#include "Nitisa/Package/Core/PropertyState.h"
#include "../../Controls/IRegistration.h"
#include "../Interfaces/IPropertyRegistrationDataState.h"
#include <iostream>
#include <map>

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	namespace coolwidgets
	{
		class CPropertyRegistrationDataState :public virtual IPropertyRegistrationDataState, public CPropertyState
		{
		public:
			using FGetter = IRegistration::RegistrationData(*)(IClass *parent, const String &state);
			using FSetter = bool(*)(IClass *parent, const String &state, IRegistration::RegistrationData value);
		private:
			std::map<String, IRegistration::RegistrationData> m_aOld;
			std::map<String, IRegistration::RegistrationData> m_aValue;
			FGetter m_fGetter;
			FSetter m_fSetter;
			bool m_bChanged;
		public:
			// IProperty getters
			String getPreview() override;
			String getPreview(const String &state) override;
			bool isChanged() override;

			// IProperty setters
			IProperty *setChanged(const bool value) override;

			// IProperty methods
			bool Copy(IProperty *dest) override;
			void Save(Variant &dest) override;
			void Load(const Variant &src) override;
			void Export(std::wofstream &f, const String &shift, const String &control) override;

			// IPropertyRegistrationDataState getters
			IRegistration::RegistrationData getValue(const String &state) override;

			// IPropertyRegistrationDataState setters
			bool setValue(const String &state, const IRegistration::RegistrationData value) override;

			CPropertyRegistrationDataState(
				IPropertyList *list,
				IClass *parent,
				const String &name,
				const bool read_only,
				const StringArray &states,
				const ExportPrefixType state_prefix_type,
				const String &state_prefix,
				FSkip skip,
				FGetter getter,
				FSetter setter);
		};
	}
}