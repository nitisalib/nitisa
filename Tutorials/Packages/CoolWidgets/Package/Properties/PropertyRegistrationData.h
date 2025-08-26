#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Variant.h"
#include "Nitisa/Package/Core/Property.h"
#include "../../Controls/IRegistration.h"
#include "../Interfaces/IPropertyRegistrationData.h"
#include <iostream>

//#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	namespace coolwidgets
	{
		class CPropertyRegistrationData :public virtual IPropertyRegistrationData, public CProperty
		{
		public:
			using FGetter = IRegistration::RegistrationData(*)(IClass *parent);
			using FSetter = bool(*)(IClass *parent, IRegistration::RegistrationData value);
		private:
			IRegistration::RegistrationData m_tOld;
			IRegistration::RegistrationData m_tValue;
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

			// IPropertyRegistrationData getters
			IRegistration::RegistrationData getValue() override;

			// IPropertyRegistrationData setters
			bool setValue(const IRegistration::RegistrationData value) override;

			CPropertyRegistrationData(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter);
		};
	}
}