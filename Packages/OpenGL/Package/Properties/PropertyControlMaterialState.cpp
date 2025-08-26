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
		CPropertyControlMaterialState::CPropertyControlMaterialState(
			IPropertyList *list,
			IClass *parent,
			const String &name,
			const StringArray &states,
			const ExportPrefixType state_prefix_type,
			const String &state_prefix,
			FSkip skip,
			FGetter getter,
			FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerControlMaterial, skip, false, states, state_prefix_type, state_prefix),
			m_fGetter{ getter },
			m_fSetter{ setter },
			m_bChanged{ false }
		{
			AddForwardDeclaration(L"class IMaterialControl;", L"OpenGL/Interfaces/IMaterialControl.h", L"opengl");
		}
	#pragma endregion

	#pragma region IProperty getters
		String CPropertyControlMaterialState::getPreview()
		{
			return L"";
		}

		String CPropertyControlMaterialState::getPreview(const String &state)
		{
			if (getValue(state))
				return getValue(state)->Name;
			return L"";
		}

		bool CPropertyControlMaterialState::isChanged()
		{
			if (m_bChanged)
				return true;
			for (int i = 0; i < getStateCount(); i++)
				if (getValue(getState(i)))
					return true;
			return false;
		}
	#pragma endregion

	#pragma region IProperty setters
		IProperty *CPropertyControlMaterialState::setChanged(const bool value)
		{
			m_bChanged = value;
			return this;
		}
	#pragma endregion

	#pragma region IProperty methods
		bool CPropertyControlMaterialState::Copy(IProperty *dest)
		{
			IPropertyControlMaterialState *d{ cast<IPropertyControlMaterialState*>(dest) };
			if (d && d->getStateCount() == getStateCount())
			{
				for (int i = 0; i < getStateCount(); i++)
					d->setValue(getState(i), getValue(getState(i)));
				return true;
			}
			return false;
		}

		void CPropertyControlMaterialState::Save(Variant &dest)
		{
			dest.Reset();
			for (int i = 0; i < getStateCount(); i++)
				if (getValue(getState(i)))
					dest[getState(i).c_str()] = getValue(getState(i))->Name;
		}

		void CPropertyControlMaterialState::Load(const Variant &src)
		{
			IEditor *editor{ Application->Editor };
			if (editor)
				for (int n = 0; n < getStateCount(); n++)
				{
					IMaterialControl *obj{ nullptr };
					for (int i = 0; i < editor->getPackageCount(); i++)
					{
						for (int j = 0; j < editor->getPackage(i)->getCreatedControlCount(); j++)
							if (editor->getPackage(i)->getCreatedControl(j)->Name == (String)src.get(getState(n).c_str()) && (obj = cast<IMaterialControl*>(editor->getPackage(i)->getCreatedControl(j))))
								break;
						if (obj)
							break;
					}
					setValue(getState(n), obj);
				}
		}

		void CPropertyControlMaterialState::Export(std::wofstream &f, const String &shift, const String &control)
		{
			String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
			for (int i = 0; i < getStateCount(); i++)
				if (getValue(getState(i)))
				{
					IPackageControl *pc{ Application->Editor ? Application->Editor->getControl(getValue(getState(i))) : nullptr };
					String ns{ pc ? pc->getNamespace() : L"" };
					if (!ns.empty())
						ns += L"::";
					if (control.empty())
						f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", cast<" << ns << L"IMaterialControl*>(FindControl(L\""
						<< getValue(getState(i))->Name << L"\")));" << std::endl;
					else
						f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", cast<" << ns << L"IMaterialControl*>(FindControl(L\""
						<< getValue(getState(i))->Name << L"\")));" << std::endl;
				}
		}
	#pragma endregion

	#pragma region IPropertyControlMaterialState getters
		IMaterialControl *CPropertyControlMaterialState::getValue(const String &state)
		{
			return m_fGetter(m_pParent, state);
		}
	#pragma endregion

	#pragma region IPropertyControlMaterialState setters
		bool CPropertyControlMaterialState::setValue(const String &state, IMaterialControl *value)
		{
			return m_fSetter(m_pParent, state, value);
		}
	#pragma endregion
	}
}