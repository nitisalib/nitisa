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
		CPropertyComponentImageList::CPropertyComponentImageList(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetter getter, FSetter setter) :
			CProperty(list, parent, name, PropertyHandlerComponentImageList, skip, false),
			m_fGetter{ getter },
			m_fSetter{ setter },
			m_bChanged{ false }
		{
			AddForwardDeclaration(L"class IImageList;", L"Standard/Components/IImageList.h", L"standard");
		}
	#pragma endregion

	#pragma region IProperty getters
		String CPropertyComponentImageList::getPreview()
		{
			if (getValue())
				return getValue()->Name;
			return L"";
		}

		String CPropertyComponentImageList::getPreview(const String &state)
		{
			return L"";
		}

		bool CPropertyComponentImageList::isChanged()
		{
			return m_bChanged || getValue();
		}
	#pragma endregion

	#pragma region IProperty setters
		IProperty *CPropertyComponentImageList::setChanged(const bool value)
		{
			m_bChanged = value;
			return this;
		}
	#pragma endregion

	#pragma region IProperty methods
		bool CPropertyComponentImageList::Copy(IProperty *dest)
		{
			IPropertyComponentImageList *d{ cast<IPropertyComponentImageList*>(dest) };
			if (d)
			{
				d->setValue(getValue());
				return true;
			}
			return false;
		}

		void CPropertyComponentImageList::Save(Variant &dest)
		{
			if (getValue())
				dest = getValue()->Name;
		}

		void CPropertyComponentImageList::Load(const Variant &src)
		{
			IEditor *editor{ Application->Editor };
			if (editor)
			{
				IImageList *obj{ nullptr };
				for (int i = 0; i < editor->getPackageCount(); i++)
				{
					for (int j = 0; j < editor->getPackage(i)->getCreatedComponentCount(); j++)
						if (editor->getPackage(i)->getCreatedComponent(j)->Name == (String)src && (obj = cast<IImageList*>(editor->getPackage(i)->getCreatedComponent(j))))
							break;
					if (obj)
						break;
				}
				setValue(obj);
			}
		}

		void CPropertyComponentImageList::Export(std::wofstream &f, const String &shift, const String &control)
		{
			if (getValue())
			{
				IPackageComponent *pc{ Application->Editor ? Application->Editor->getComponent(getValue()) : nullptr };
				String ns{ pc ? pc->getNamespace() : L"" };
				if (!ns.empty())
					ns += L"::";
				if (control.empty())
					f << shift << L"set" << m_sName << L"(cast<" << ns << L"IImageList*>(getComponent(L\"" << getValue()->Name << L"\")));" << std::endl;
				else
					f << shift << control << L"->set" << m_sName << L"(cast<" << ns << L"IImageList*>(getComponent(L\"" << getValue()->Name << L"\")));" << std::endl;
			}
		}
	#pragma endregion

	#pragma region IPropertyComponentImageList getters
		IImageList *CPropertyComponentImageList::getValue()
		{
			return m_fGetter(m_pParent);
		}
	#pragma endregion

	#pragma region IPropertyComponentImageList setters
		bool CPropertyComponentImageList::setValue(IImageList *value)
		{
			return m_fSetter(m_pParent, value);
		}
	#pragma endregion
	}
}