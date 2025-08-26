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
		CPackageFormMatrix::CPackageFormMatrix(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/Matrix/FormMatrix.h");
		}

		String CPackageFormMatrix::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormMatrix::getClassName()
		{
			return CFormMatrix::ClassName;
		}

		String CPackageFormMatrix::getTitle()
		{
			return L"FormMatrix";
		}

		String CPackageFormMatrix::getDescription()
		{
			return L"Matrix";
		}

		String CPackageFormMatrix::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormMatrix::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormMatrix::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormMatrix::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormMatrix(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormMatrix::CreatePropertyList(IForm *form)
		{
			CFormMatrix *f{ cast<CFormMatrix*>(form) };
			if (f)
				return new CFormMatrixPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormMatrix::CreateEventList(IForm *form)
		{
			CFormMatrix *f{ cast<CFormMatrix*>(form) };
			if (f)
				return new CFormMatrixEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}