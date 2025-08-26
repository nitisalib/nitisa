#pragma once

#include "Nitisa/Core/Strings.h"
#include "Standard/Package/Core/PropertyHandlerModal.h"
#include "../../../Controls/IRegistration.h"

namespace nitisa
{
	class IPackage;
	class IProperty;

	namespace coolwidgets
	{
		class IFormRegistrationData;

		class CPropertyHandlerRegistrationData :public standard::CPropertyHandlerModal
		{
		private:
			IProperty *m_pProperty;
			String m_sState;

			IFormRegistrationData *getForm();
			void setFormData(const IRegistration::RegistrationData &value);
		protected:
			void NotifyOnActivateModal() override;
		public:
			String getPropertyState() override;
			IProperty *getProperty() override;
			bool isEditable(IProperty *property) override;

			bool setProperty(IProperty *value) override;
			bool setPropertyState(const String &value) override;

			CPropertyHandlerRegistrationData(IPackage *package);
		};
	}
}