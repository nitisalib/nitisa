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
		CPackageFormImageList::CPackageFormImageList(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/ImageList/FormImageList.h");
		}

		String CPackageFormImageList::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormImageList::getClassName()
		{
			return CFormImageList::ClassName;
		}

		String CPackageFormImageList::getTitle()
		{
			return L"FormImageList";
		}

		String CPackageFormImageList::getDescription()
		{
			return L"ImageList";
		}

		String CPackageFormImageList::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormImageList::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormImageList::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormImageList::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormImageList(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormImageList::CreatePropertyList(IForm *form)
		{
			CFormImageList *f{ cast<CFormImageList*>(form) };
			if (f)
				return new CFormImageListPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormImageList::CreateEventList(IForm *form)
		{
			CFormImageList *f{ cast<CFormImageList*>(form) };
			if (f)
				return new CFormImageListEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}