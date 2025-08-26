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
		CPackageFormMask::CPackageFormMask(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/Mask/FormMask.h");
		}

		String CPackageFormMask::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormMask::getClassName()
		{
			return CFormMask::ClassName;
		}

		String CPackageFormMask::getTitle()
		{
			return L"FormMask";
		}

		String CPackageFormMask::getDescription()
		{
			return L"Mask";
		}

		String CPackageFormMask::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormMask::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormMask::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormMask::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormMask(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormMask::CreatePropertyList(IForm *form)
		{
			CFormMask *f{ cast<CFormMask*>(form) };
			if (f)
				return new CFormMaskPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormMask::CreateEventList(IForm *form)
		{
			CFormMask *f{ cast<CFormMask*>(form) };
			if (f)
				return new CFormMaskEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}