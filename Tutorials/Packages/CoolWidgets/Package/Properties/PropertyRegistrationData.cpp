#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
	#pragma region Constructor & destructor
		CPropertyRegistrationData::CPropertyRegistrationData(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
			CProperty(list, parent, name, PropertyHandlerRegistrationData, skip, read_only),
			m_tOld{ getter(parent) },
			m_tValue{ getter(parent) },
			m_fGetter{ getter },
			m_fSetter{ setter },
			m_bChanged{ false }
		{
			AddHeaderFile(L"CoolWidgets/Controls/IRegistration.h");
		}
	#pragma endregion

	#pragma region IProperty getters
		String CPropertyRegistrationData::getPreview()
		{
			return ToString(getValue());
		}

		String CPropertyRegistrationData::getPreview(const String &state)
		{
			return L"";
		}

		bool CPropertyRegistrationData::isChanged()
		{
			return m_bChanged || getValue() != m_tOld;
		}
	#pragma endregion

	#pragma region IProperty setters
		IProperty *CPropertyRegistrationData::setChanged(const bool value)
		{
			m_bChanged = value;
			return this;
		}
	#pragma endregion

	#pragma region IProperty methods
		bool CPropertyRegistrationData::Copy(IProperty *dest)
		{
			IPropertyRegistrationData *d{ cast<IPropertyRegistrationData*>(dest) };
			if (d)
			{
				d->setValue(getValue());
				return true;
			}
			return false;
		}

		void CPropertyRegistrationData::Save(Variant &dest)
		{
			dest.Reset();
			dest = ToVariant(getValue());
		}

		void CPropertyRegistrationData::Load(const Variant &src)
		{
			IRegistration::RegistrationData v;
			FromVariant(src, v);
			setValue(v);
		}

		void CPropertyRegistrationData::Export(std::wofstream &f, const String &shift, const String &control)
		{
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		}
	#pragma endregion

	#pragma region IPropertyRegistrationData getters
		IRegistration::RegistrationData CPropertyRegistrationData::getValue()
		{
			if (!isReadOnly() || !Application->Editor)
				return m_fGetter(m_pParent);
			return m_tValue;
		}
	#pragma endregion

	#pragma region IPropertyRegistrationData setters
		bool CPropertyRegistrationData::setValue(const IRegistration::RegistrationData value)
		{
			if (!isReadOnly() || !Application->Editor)
				return m_fSetter(m_pParent, value);
			if (value != m_tValue)
			{
				m_tValue = value;
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}