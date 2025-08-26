#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
		const String CFormRegistrationData::ClassName{ L"FormRegistrationData" };

	#pragma region Service
		CFormRegistrationData::CFormRegistrationDataService::CFormRegistrationDataService(CFormRegistrationData *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormRegistrationData::CFormRegistrationDataService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CFormRegistrationData::CFormRegistrationData(IWindow *window, IRenderer *renderer) :
			IFormRegistrationDataProto(window, renderer, ClassName)
		{
			setService(new CFormRegistrationDataService(this), true);
			LoadTranslatableTexts();
		}

		void CFormRegistrationData::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Registration Data"));
			m_pLabel1->setCaption(Application->Translate->t(ClassName, L"First name:"));
			m_pLabel2->setCaption(Application->Translate->t(ClassName, L"Last name:"));
			m_pLabel3->setCaption(Application->Translate->t(ClassName, L"Date of birth:"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"Ok"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormRegistrationData::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormRegistrationData::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		IRegistration::RegistrationData CFormRegistrationData::getValue()
		{
			return IRegistration::RegistrationData{
				m_pEditFirstName->getText(),
				m_pEditLastName->getText(),
				m_pMonthCalendar->getYear(),
				m_pMonthCalendar->getMonth(),
				m_pMonthCalendar->getDay()
			};
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormRegistrationData::setValue(const IRegistration::RegistrationData &value)
		{
			return
				m_pEditFirstName->setText(value.FirstName) ||
				m_pEditLastName->setText(value.LastName) ||
				m_pMonthCalendar->setYear(value.Year) ||
				m_pMonthCalendar->setMonth(value.Month) ||
				m_pMonthCalendar->setDay(value.Day);
		}
	#pragma endregion

	#pragma region Interface methods
		void CFormRegistrationData::ActivateFirstEnabledInput()
		{
			m_pEditFirstName->setFocus();
		}
	#pragma endregion
	}
}