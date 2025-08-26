#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
	#pragma region Constructor & destructor
		CPropertyRegistrationDataState::CPropertyRegistrationDataState(
			IPropertyList *list,
			IClass *parent,
			const String &name,
			const bool read_only,
			const StringArray &states,
			const ExportPrefixType state_prefix_type,
			const String &state_prefix,
			FSkip skip,
			FGetter getter,
			FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerRegistrationData, skip, read_only, states, state_prefix_type, state_prefix),
			m_fGetter{ getter },
			m_fSetter{ setter },
			m_bChanged{ false }
		{
			AddHeaderFile(L"CoolWidgets/Controls/IRegistration.h");
			for (int i = 0; i < getStateCount(); i++)
			{
				m_aOld[getState(i)] = m_fGetter(m_pParent, getState(i));
				m_aValue[getState(i)] = m_fGetter(m_pParent, getState(i));
			}
		}
	#pragma endregion

	#pragma region IProperty getters
		String CPropertyRegistrationDataState::getPreview()
		{
			return L"";
		}

		String CPropertyRegistrationDataState::getPreview(const String &state)
		{
			return ToString(getValue(state));
		}

		bool CPropertyRegistrationDataState::isChanged()
		{
			if (m_bChanged)
				return true;
			for (int i = 0; i < getStateCount(); i++)
				if (getValue(getState(i)) != m_aOld[getState(i)])
					return true;
			return false;
		}
	#pragma endregion

	#pragma region IProperty setters
		IProperty *CPropertyRegistrationDataState::setChanged(const bool value)
		{
			m_bChanged = value;
			return this;
		}
	#pragma endregion

	#pragma region IProperty methods
		bool CPropertyRegistrationDataState::Copy(IProperty *dest)
		{
			IPropertyRegistrationDataState *d{ cast<IPropertyRegistrationDataState*>(dest) };
			if (d && d->getStateCount() == getStateCount())
			{
				for (int i = 0; i < getStateCount(); i++)
					d->setValue(getState(i), getValue(getState(i)));
				return true;
			}
			return false;
		}

		void CPropertyRegistrationDataState::Save(Variant &dest)
		{
			dest.Reset();
			for (int i = 0; i < getStateCount(); i++)
				dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
		}

		void CPropertyRegistrationDataState::Load(const Variant &src)
		{
			for (int i = 0; i < getStateCount(); i++)
			{
				IRegistration::RegistrationData v;
				FromVariant(src.get(getState(i).c_str()), v);
				setValue(getState(i), v);
			}
		}

		void CPropertyRegistrationDataState::Export(std::wofstream &f, const String &shift, const String &control)
		{
			String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
			for (int i = 0; i < getStateCount(); i++)
				if (control.empty())
					f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
				else
					f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
		}
	#pragma endregion

	#pragma region IPropertyRegistrationDataState getters
		IRegistration::RegistrationData CPropertyRegistrationDataState::getValue(const String &state)
		{
			if (!isReadOnly() || !Application->Editor)
				return m_fGetter(m_pParent, state);
			return m_aValue[state];
		}
	#pragma endregion

	#pragma region IPropertyRegistrationDataState setters
		bool CPropertyRegistrationDataState::setValue(const String &state, const IRegistration::RegistrationData value)
		{
			if (!isReadOnly() || !Application->Editor)
				return m_fSetter(m_pParent, state, value);
			if (value != m_aValue[state])
			{
				m_aValue[state] = value;
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}