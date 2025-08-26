// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace standard
	{
		CPackageFormRectD::CPackageFormRectD(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/RectD/FormRectD.h");
		}

		String CPackageFormRectD::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormRectD::getClassName()
		{
			return CFormRectD::ClassName;
		}

		String CPackageFormRectD::getTitle()
		{
			return L"FormRectD";
		}

		String CPackageFormRectD::getDescription()
		{
			return L"RectD";
		}

		String CPackageFormRectD::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormRectD::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormRectD::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormRectD::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormRectD(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormRectD::CreatePropertyList(IForm *form)
		{
			CFormRectD *f{ cast<CFormRectD*>(form) };
			if (f)
				return new CFormRectDPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormRectD::CreateEventList(IForm *form)
		{
			CFormRectD *f{ cast<CFormRectD*>(form) };
			if (f)
				return new CFormRectDEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}