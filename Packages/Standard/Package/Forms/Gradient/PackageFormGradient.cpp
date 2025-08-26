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
		CPackageFormGradient::CPackageFormGradient(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/Gradient/FormGradient.h");
		}

		String CPackageFormGradient::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormGradient::getClassName()
		{
			return CFormGradient::ClassName;
		}

		String CPackageFormGradient::getTitle()
		{
			return L"FormGradient";
		}

		String CPackageFormGradient::getDescription()
		{
			return L"Gradient";
		}

		String CPackageFormGradient::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormGradient::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormGradient::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormGradient::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormGradient(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormGradient::CreatePropertyList(IForm *form)
		{
			CFormGradient *f{ cast<CFormGradient*>(form) };
			if (f)
				return new CFormGradientPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormGradient::CreateEventList(IForm *form)
		{
			CFormGradient *f{ cast<CFormGradient*>(form) };
			if (f)
				return new CFormGradientEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}