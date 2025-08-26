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
		CPackageFormRectB::CPackageFormRectB(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/RectB/FormRectB.h");
		}

		String CPackageFormRectB::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormRectB::getClassName()
		{
			return CFormRectB::ClassName;
		}

		String CPackageFormRectB::getTitle()
		{
			return L"FormRectB";
		}

		String CPackageFormRectB::getDescription()
		{
			return L"RectB";
		}

		String CPackageFormRectB::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormRectB::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormRectB::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormRectB::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormRectB(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormRectB::CreatePropertyList(IForm *form)
		{
			CFormRectB *f{ cast<CFormRectB*>(form) };
			if (f)
				return new CFormRectBPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormRectB::CreateEventList(IForm *form)
		{
			CFormRectB *f{ cast<CFormRectB*>(form) };
			if (f)
				return new CFormRectBEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}