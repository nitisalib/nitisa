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
	#pragma region Constructor & destructor
		CPropertyControlEdit::CPropertyControlEdit(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetter getter, FSetter setter) :
			CProperty(list, parent, name, PropertyHandlerControlEdit, skip, false),
			m_fGetter{ getter },
			m_fSetter{ setter },
			m_bChanged{ false }
		{
			AddForwardDeclaration(L"class IEdit;", L"Standard/Controls/IEdit.h", L"standard");
		}
	#pragma endregion

	#pragma region IProperty getters
		String CPropertyControlEdit::getPreview()
		{
			if (getValue())
				return getValue()->Name;
			return L"";
		}

		String CPropertyControlEdit::getPreview(const String &state)
		{
			return L"";
		}

		bool CPropertyControlEdit::isChanged()
		{
			return m_bChanged || getValue();
		}
	#pragma endregion

	#pragma region IProperty setters
		IProperty *CPropertyControlEdit::setChanged(const bool value)
		{
			m_bChanged = value;
			return this;
		}
	#pragma endregion

	#pragma region IProperty methods
		bool CPropertyControlEdit::Copy(IProperty *dest)
		{
			IPropertyControlEdit *d{ cast<IPropertyControlEdit*>(dest) };
			if (d)
			{
				d->setValue(getValue());
				return true;
			}
			return false;
		}

		void CPropertyControlEdit::Save(Variant &dest)
		{
			if (getValue())
				dest = getValue()->Name;
		}

		void CPropertyControlEdit::Load(const Variant &src)
		{
			IEditor *editor{ Application->Editor };
			if (editor)
			{
				IEdit *obj{ nullptr };
				for (int i = 0; i < editor->getPackageCount(); i++)
				{
					for (int j = 0; j < editor->getPackage(i)->getCreatedControlCount(); j++)
						if (editor->getPackage(i)->getCreatedControl(j)->Name == (String)src && (obj = cast<IEdit*>(editor->getPackage(i)->getCreatedControl(j))))
							break;
					if (obj)
						break;
				}
				setValue(obj);
			}
		}

		void CPropertyControlEdit::Export(std::wofstream &f, const String &shift, const String &control)
		{
			if (getValue())
			{
				IPackageControl *pc{ Application->Editor ? Application->Editor->getControl(getValue()) : nullptr };
				String ns{ pc ? pc->getNamespace() : L"" };
				if (!ns.empty())
					ns += L"::";
				if (control.empty())
					f << shift << L"set" << m_sName << L"(cast<" << ns << L"IEdit*>(FindControl(L\"" << getValue()->Name << L"\")));" << std::endl;
				else
					f << shift << control << L"->set" << m_sName << L"(cast<" << ns << L"IEdit*>(FindControl(L\"" << getValue()->Name << L"\")));" << std::endl;
			}
		}
	#pragma endregion

	#pragma region IPropertyControlEdit getters
		IEdit *CPropertyControlEdit::getValue()
		{
			return m_fGetter(m_pParent);
		}
	#pragma endregion

	#pragma region IPropertyControlEdit setters
		bool CPropertyControlEdit::setValue(IEdit *value)
		{
			return m_fSetter(m_pParent, value);
		}
	#pragma endregion
	}
}