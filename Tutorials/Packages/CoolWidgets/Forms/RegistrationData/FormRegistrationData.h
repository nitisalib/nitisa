#pragma once

#include "Nitisa/Core/FormService.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "../../Controls/IRegistration.h"
#include "../IFormRegistrationData.h"
#include "IFormRegistrationDataProto.h"

namespace nitisa
{
	class IControl;
	class IRenderer;
	class IWindow;

	namespace coolwidgets
	{
		class CFormRegistrationData :public virtual IFormRegistrationData, public IFormRegistrationDataProto
		{
		private:
			class CFormRegistrationDataService :public CFormService
			{
			private:
				CFormRegistrationData *m_pForm;
			public:
				void NotifyOnTranslateChange() override;

				CFormRegistrationDataService(CFormRegistrationData *form);
			};

			void LoadTranslatableTexts();
		protected:
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName;

			IRegistration::RegistrationData getValue() override;

			bool setValue(const IRegistration::RegistrationData &value) override;

			void ActivateFirstEnabledInput() override;

			CFormRegistrationData(IWindow *window, IRenderer *renderer);
		};
	}
}