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
	namespace charts
	{
	#pragma region Constructor & destructor
		CPropertyLineInterpolationPositionArray::CPropertyLineInterpolationPositionArray(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
			CProperty(list, parent, name, PropertyHandlerLineInterpolationPositionArray, skip, read_only),
			m_tOld{ getter(parent) },
			m_tValue{ getter(parent) },
			m_fGetter{ getter },
			m_fSetter{ setter },
			m_bChanged{ false },
			m_iMinCount{ 0 }
		{
			AddHeaderFile(L"Charts/Core/Enums.h");
		}
	#pragma endregion

	#pragma region IProperty getters
		String CPropertyLineInterpolationPositionArray::getPreview()
		{
			if (getValue().size() > 1)
				return L"{ " + LineInterpolationPositionToString(getValue()[0]) + L", ... }";
			if (getValue().size() == 1)
				return L"{ " + LineInterpolationPositionToString(getValue()[0]) + L" }";
			return L"";
		}

		String CPropertyLineInterpolationPositionArray::getPreview(const String &state)
		{
			return L"";
		}

		bool CPropertyLineInterpolationPositionArray::isChanged()
		{
			return m_bChanged || getValue() != m_tOld;
		}
	#pragma endregion

	#pragma region IProperty setters
		IProperty *CPropertyLineInterpolationPositionArray::setChanged(const bool value)
		{
			m_bChanged = value;
			return this;
		}
	#pragma endregion

	#pragma region IProperty methods
		bool CPropertyLineInterpolationPositionArray::Copy(IProperty *dest)
		{
			IPropertyLineInterpolationPositionArray *d{ cast<IPropertyLineInterpolationPositionArray*>(dest) };
			if (d)
			{
				d->setValue(getValue());
				return true;
			}
			return false;
		}

		void CPropertyLineInterpolationPositionArray::Save(Variant &dest)
		{
			dest.Reset();
			dest = LineInterpolationPositionArrayToVariant(getValue());
		}

		void CPropertyLineInterpolationPositionArray::Load(const Variant &src)
		{
			std::vector<LineInterpolationPosition> v;
			LineInterpolationPositionArrayFromVariant(src, v);
			setValue(v);
		}

		void CPropertyLineInterpolationPositionArray::Export(std::wofstream &f, const String &shift, const String &control)
		{
			if (control.empty())
			{
				f << shift << L"set" << m_sName << L"({ ";
				for (auto v : getValue())
					f << L"charts::"<< LineInterpolationPositionToString(v) << L", ";
				f << L" });" << std::endl;
			}
			else
			{
				f << shift << control << L"->set" << m_sName << L"({ ";
				for (auto v : getValue())
					f << L"charts::" << LineInterpolationPositionToString(v) << L", ";
				f << L" });" << std::endl;
			}
		}
	#pragma endregion

	#pragma region IPropertyLineInterpolationPositionArray getters
		std::vector<LineInterpolationPosition> CPropertyLineInterpolationPositionArray::getValue()
		{
			if (!isReadOnly() || !Application->Editor)
				return m_fGetter(m_pParent);
			return m_tValue;
		}

		int CPropertyLineInterpolationPositionArray::getMinCount()
		{
			return m_iMinCount;
		}
	#pragma endregion

	#pragma region IPropertyLineInterpolationPositionArray setters
		bool CPropertyLineInterpolationPositionArray::setValue(const std::vector<LineInterpolationPosition> value)
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

		IPropertyLineInterpolationPositionArray *CPropertyLineInterpolationPositionArray::setMinCount(const int value)
		{
			m_iMinCount = ntl::Max<int>(0, value);
			return this;
		}
	#pragma endregion
	}
}