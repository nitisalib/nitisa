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
		CPackageFormPointB::CPackageFormPointB(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/PointB/FormPointB.h");
		}

		String CPackageFormPointB::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormPointB::getClassName()
		{
			return CFormPointB::ClassName;
		}

		String CPackageFormPointB::getTitle()
		{
			return L"FormPointB";
		}

		String CPackageFormPointB::getDescription()
		{
			return L"PointB";
		}

		String CPackageFormPointB::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormPointB::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormPointB::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormPointB::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormPointB(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormPointB::CreatePropertyList(IForm *form)
		{
			CFormPointB *f{ cast<CFormPointB*>(form) };
			if (f)
				return new CFormPointBPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormPointB::CreateEventList(IForm *form)
		{
			CFormPointB *f{ cast<CFormPointB*>(form) };
			if (f)
				return new CFormPointBEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}