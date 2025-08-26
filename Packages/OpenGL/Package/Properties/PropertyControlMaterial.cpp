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
	namespace opengl
	{
	#pragma region Constructor & destructor
		CPropertyControlMaterial::CPropertyControlMaterial(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetter getter, FSetter setter) :
			CProperty(list, parent, name, PropertyHandlerControlMaterial, skip, false),
			m_fGetter{ getter },
			m_fSetter{ setter },
			m_bChanged{ false }
		{
			AddForwardDeclaration(L"class IMaterialControl;", L"OpenGL/Interfaces/IMaterialControl.h", L"opengl");
		}
	#pragma endregion

	#pragma region IProperty getters
		String CPropertyControlMaterial::getPreview()
		{
			if (getValue())
				return getValue()->Name;
			return L"";
		}

		String CPropertyControlMaterial::getPreview(const String &state)
		{
			return L"";
		}

		bool CPropertyControlMaterial::isChanged()
		{
			return m_bChanged || getValue();
		}
	#pragma endregion

	#pragma region IProperty setters
		IProperty *CPropertyControlMaterial::setChanged(const bool value)
		{
			m_bChanged = value;
			return this;
		}
	#pragma endregion

	#pragma region IProperty methods
		bool CPropertyControlMaterial::Copy(IProperty *dest)
		{
			IPropertyControlMaterial *d{ cast<IPropertyControlMaterial*>(dest) };
			if (d)
			{
				d->setValue(getValue());
				return true;
			}
			return false;
		}

		void CPropertyControlMaterial::Save(Variant &dest)
		{
			if (getValue())
				dest = getValue()->Name;
		}

		void CPropertyControlMaterial::Load(const Variant &src)
		{
			IEditor *editor{ Application->Editor };
			if (editor)
			{
				IMaterialControl *obj{ nullptr };
				for (int i = 0; i < editor->getPackageCount(); i++)
				{
					for (int j = 0; j < editor->getPackage(i)->getCreatedControlCount(); j++)
						if (editor->getPackage(i)->getCreatedControl(j)->Name == (String)src && (obj = cast<IMaterialControl*>(editor->getPackage(i)->getCreatedControl(j))))
							break;
					if (obj)
						break;
				}
				setValue(obj);
			}
		}

		void CPropertyControlMaterial::Export(std::wofstream &f, const String &shift, const String &control)
		{
			if (getValue())
			{
				IPackageControl *pc{ Application->Editor ? Application->Editor->getControl(getValue()) : nullptr };
				String ns{ pc ? pc->getNamespace() : L"" };
				if (!ns.empty())
					ns += L"::";
				if (control.empty())
					f << shift << L"set" << m_sName << L"(cast<" << ns << L"IMaterialControl*>(FindControl(L\"" << getValue()->Name << L"\")));" << std::endl;
				else
					f << shift << control << L"->set" << m_sName << L"(cast<" << ns << L"IMaterialControl*>(FindControl(L\"" << getValue()->Name << L"\")));" << std::endl;
			}
		}
	#pragma endregion

	#pragma region IPropertyControlMaterial getters
		IMaterialControl *CPropertyControlMaterial::getValue()
		{
			return m_fGetter(m_pParent);
		}
	#pragma endregion

	#pragma region IPropertyControlMaterial setters
		bool CPropertyControlMaterial::setValue(IMaterialControl *value)
		{
			return m_fSetter(m_pParent, value);
		}
	#pragma endregion
	}
}