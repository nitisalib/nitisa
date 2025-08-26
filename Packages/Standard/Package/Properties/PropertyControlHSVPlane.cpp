// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
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
	#pragma region Constructor & destructor
		CPropertyControlHSVPlane::CPropertyControlHSVPlane(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetter getter, FSetter setter) :
			CProperty(list, parent, name, PropertyHandlerControlHSVPlane, skip, false),
			m_fGetter{ getter },
			m_fSetter{ setter },
			m_bChanged{ false }
		{
			AddForwardDeclaration(L"class IHSVPlane;", L"Standard/Controls/IHSVPlane.h", L"standard");
		}
	#pragma endregion

	#pragma region IProperty getters
		String CPropertyControlHSVPlane::getPreview()
		{
			if (getValue())
				return getValue()->Name;
			return L"";
		}

		String CPropertyControlHSVPlane::getPreview(const String &state)
		{
			return L"";
		}

		bool CPropertyControlHSVPlane::isChanged()
		{
			return m_bChanged || getValue();
		}
	#pragma endregion

	#pragma region IProperty setters
		IProperty *CPropertyControlHSVPlane::setChanged(const bool value)
		{
			m_bChanged = value;
			return this;
		}
	#pragma endregion

	#pragma region IProperty methods
		bool CPropertyControlHSVPlane::Copy(IProperty *dest)
		{
			IPropertyControlHSVPlane *d{ cast<IPropertyControlHSVPlane*>(dest) };
			if (d)
			{
				d->setValue(getValue());
				return true;
			}
			return false;
		}

		void CPropertyControlHSVPlane::Save(Variant &dest)
		{
			if (getValue())
				dest = getValue()->Name;
		}

		void CPropertyControlHSVPlane::Load(const Variant &src)
		{
			IEditor *editor{ Application->Editor };
			if (editor)
			{
				IHSVPlane *obj{ nullptr };
				for (int i = 0; i < editor->getPackageCount(); i++)
				{
					for (int j = 0; j < editor->getPackage(i)->getCreatedControlCount(); j++)
						if (editor->getPackage(i)->getCreatedControl(j)->Name == (String)src && (obj = cast<IHSVPlane*>(editor->getPackage(i)->getCreatedControl(j))))
							break;
					if (obj)
						break;
				}
				setValue(obj);
			}
		}

		void CPropertyControlHSVPlane::Export(std::wofstream &f, const String &shift, const String &control)
		{
			if (getValue())
			{
				IPackageControl *pc{ Application->Editor ? Application->Editor->getControl(getValue()) : nullptr };
				String ns{ pc ? pc->getNamespace() : L"" };
				if (!ns.empty())
					ns += L"::";
				if (control.empty())
					f << shift << L"set" << m_sName << L"(cast<" << ns << L"IHSVPlane*>(FindControl(L\"" << getValue()->Name << L"\")));" << std::endl;
				else
					f << shift << control << L"->set" << m_sName << L"(cast<" << ns << L"IHSVPlane*>(FindControl(L\"" << getValue()->Name << L"\")));" << std::endl;
			}
		}
	#pragma endregion

	#pragma region IPropertyControlHSVPlane getters
		IHSVPlane *CPropertyControlHSVPlane::getValue()
		{
			return m_fGetter(m_pParent);
		}
	#pragma endregion

	#pragma region IPropertyControlHSVPlane setters
		bool CPropertyControlHSVPlane::setValue(IHSVPlane *value)
		{
			return m_fSetter(m_pParent, value);
		}
	#pragma endregion
	}
}