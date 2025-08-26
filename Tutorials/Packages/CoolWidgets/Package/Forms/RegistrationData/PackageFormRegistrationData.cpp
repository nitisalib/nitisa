#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
		CPackageFormRegistrationData::CPackageFormRegistrationData(IPackage *package) :
			CPackageForm(package, L"coolwidgets"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"CoolWidgets/Forms/RegistrationData/FormRegistrationData.h");
		}

		String CPackageFormRegistrationData::getCategory()
		{
			return L"CoolWidgets";
		}

		String CPackageFormRegistrationData::getClassName()
		{
			return CFormRegistrationData::ClassName;
		}

		String CPackageFormRegistrationData::getTitle()
		{
			return L"FormRegistrationData";
		}

		String CPackageFormRegistrationData::getDescription()
		{
			return L"RegistrationData";
		}

		String CPackageFormRegistrationData::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormRegistrationData::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormRegistrationData::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormRegistrationData::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormRegistrationData(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormRegistrationData::CreatePropertyList(IForm *form)
		{
			CFormRegistrationData *f{ cast<CFormRegistrationData*>(form) };
			if (f)
				return new CFormRegistrationDataPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormRegistrationData::CreateEventList(IForm *form)
		{
			CFormRegistrationData *f{ cast<CFormRegistrationData*>(form) };
			if (f)
				return new CFormRegistrationDataEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}