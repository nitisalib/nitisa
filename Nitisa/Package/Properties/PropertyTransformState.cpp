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
#pragma region Constructor & destructor
	CPropertyTransformState::CPropertyTransformState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerTransform, skip, read_only, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },

		m_bTx{ true },
		m_bTy{ true },
		m_bTz{ true },
		m_bRx{ true },
		m_bRy{ true },
		m_bRz{ true },
		m_bSx{ true },
		m_bSy{ true },
		m_bSz{ true },
		m_bRotateOrder{ true },
		m_bTransformOrder{ true },

		m_bMinTx{ false },
		m_bMinTy{ false },
		m_bMinTz{ false },
		m_bMinRx{ false },
		m_bMinRy{ false },
		m_bMinRz{ false },
		m_bMinSx{ false },
		m_bMinSy{ false },
		m_bMinSz{ false },

		m_bMaxTx{ false },
		m_bMaxTy{ false },
		m_bMaxTz{ false },
		m_bMaxRx{ false },
		m_bMaxRy{ false },
		m_bMaxRz{ false },
		m_bMaxSx{ false },
		m_bMaxSy{ false },
		m_bMaxSz{ false },

		m_fMinTx{ 0 },
		m_fMinTy{ 0 },
		m_fMinTz{ 0 },
		m_fMinRx{ 0 },
		m_fMinRy{ 0 },
		m_fMinRz{ 0 },
		m_fMinSx{ 0 },
		m_fMinSy{ 0 },
		m_fMinSz{ 0 },

		m_fMaxTx{ 0 },
		m_fMaxTy{ 0 },
		m_fMaxTz{ 0 },
		m_fMaxRx{ 0 },
		m_fMaxRy{ 0 },
		m_fMaxRz{ 0 },
		m_fMaxSx{ 0 },
		m_fMaxSy{ 0 },
		m_fMaxSz{ 0 }
	{
		AddHeaderFile(L"Nitisa/Core/RotateOrder.h");
		AddHeaderFile(L"Nitisa/Core/TransformOrder.h");
		AddHeaderFile(L"Nitisa/Math/Transform.h");
		AddHeaderFile(L"Nitisa/Interfaces/ITransform.h");
		for (int i = 0; i < getStateCount(); i++)
		{
			m_aOld[getState(i)] = m_fGetter(m_pParent, getState(i));
			m_aValue[getState(i)] = m_fGetter(m_pParent, getState(i));
		}
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyTransformState::getPreview()
	{
		return L"";
	}

	String CPropertyTransformState::getPreview(const String &state)
	{
		return ToString(getValue(state));
	}

	bool CPropertyTransformState::isChanged()
	{
		if (m_bChanged)
			return true;
		for (int i = 0; i < getStateCount(); i++)
			if (IsNotEqual(getValue(getState(i)), m_aOld[getState(i)]))
				return true;
		return false;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyTransformState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyTransformState::Copy(IProperty *dest)
	{
		IPropertyTransformState *d{ cast<IPropertyTransformState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyTransformState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
	}

	void CPropertyTransformState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			Transform v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyTransformState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
		{
			Transform v{ getValue(getState(i)) };
			if (v.RotateOrder == RotateOrder::XYZ && v.TransformOrder == TransformOrder::TRS)
			{
				if (ntl::IsEqual<float>(v.Sx, 1) && ntl::IsEqual<float>(v.Sy, 1) && ntl::IsEqual<float>(v.Sz, 1) && ntl::IsZero<float>(v.Rx) && ntl::IsZero<float>(v.Ry) && ntl::IsZero<float>(v.Rz))
				{
					if (control.empty())
						f << shift << L"get" << m_sName << L"(" << state_prefix << getState(i) << L")->Translate(" << AsSourceCode(v.Tx) << L", " << AsSourceCode(v.Ty) << L", " << AsSourceCode(v.Tz) << L");" << std::endl;
					else
						f << shift << control << L"->get" << m_sName << L"(" << state_prefix << getState(i) << L")->Translate(" << AsSourceCode(v.Tx) << L", " << AsSourceCode(v.Ty) << L", " << AsSourceCode(v.Tz) << L");" << std::endl;
					continue;
				}
				if (ntl::IsEqual<float>(v.Sx, 1) && ntl::IsEqual<float>(v.Sy, 1) && ntl::IsEqual<float>(v.Sz, 1) && ntl::IsZero<float>(v.Tx) && ntl::IsZero<float>(v.Ty) && ntl::IsZero<float>(v.Tz))
				{
					if (control.empty())
						f << shift << L"get" << m_sName << L"(" << state_prefix << getState(i) << L")->Rotate(" << AsSourceCode(v.Rx) << L", " << AsSourceCode(v.Ry) << L", " << AsSourceCode(v.Rz) << L");" << std::endl;
					else
						f << shift << control << L"->get" << m_sName << L"(" << state_prefix << getState(i) << L")->Rotate(" << AsSourceCode(v.Rx) << L", " << AsSourceCode(v.Ry) << L", " << AsSourceCode(v.Rz) << L");" << std::endl;
					continue;
				}
				if (ntl::IsZero<float>(v.Tx) && ntl::IsZero<float>(v.Ty) && ntl::IsZero<float>(v.Tz) && ntl::IsZero<float>(v.Rx) && ntl::IsZero<float>(v.Ry) && ntl::IsZero<float>(v.Rz))
				{
					if (control.empty())
						f << shift << L"get" << m_sName << L"(" << state_prefix << getState(i) << L")->Scale(" << AsSourceCode(v.Sx) << L", " << AsSourceCode(v.Sy) << L", " << AsSourceCode(v.Sz) << L");" << std::endl;
					else
						f << shift << control << L"->get" << m_sName << L"(" << state_prefix << getState(i) << L")->Scale(" << AsSourceCode(v.Sx) << L", " << AsSourceCode(v.Sy) << L", " << AsSourceCode(v.Sz) << L");" << std::endl;
					continue;
				}
			}
			if (control.empty())
				f << shift << L"get" << m_sName << L"(" << state_prefix << getState(i) << L")->setTransform(" << AsSourceCode(v) << L");" << std::endl;
			else
				f << shift << control << L"->get" << m_sName << L"(" << state_prefix << getState(i) << L")->setTransform(" << AsSourceCode(v) << L");" << std::endl;
		}
	}
#pragma endregion

#pragma region IPropertyTransformState getters
	Transform CPropertyTransformState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_aValue[state];
	}

	bool CPropertyTransformState::isAllowedTx() const
	{
		return m_bTx;
	}

	bool CPropertyTransformState::isAllowedTy() const
	{
		return m_bTy;
	}

	bool CPropertyTransformState::isAllowedTz() const
	{
		return m_bTz;
	}

	bool CPropertyTransformState::isAllowedRx() const
	{
		return m_bRx;
	}

	bool CPropertyTransformState::isAllowedRy() const
	{
		return m_bRy;
	}

	bool CPropertyTransformState::isAllowedRz() const
	{
		return m_bRz;
	}

	bool CPropertyTransformState::isAllowedSx() const
	{
		return m_bSx;
	}

	bool CPropertyTransformState::isAllowedSy() const
	{
		return m_bSy;
	}

	bool CPropertyTransformState::isAllowedSz() const
	{
		return m_bSz;
	}

	bool CPropertyTransformState::isAllowedRotateOrder() const
	{
		return m_bRotateOrder;
	}

	bool CPropertyTransformState::isAllowedTransformOrder() const
	{
		return m_bTransformOrder;
	}

	bool CPropertyTransformState::hasMinTx() const
	{
		return m_bMinTx;
	}

	bool CPropertyTransformState::hasMinTy() const
	{
		return m_bMinTy;
	}

	bool CPropertyTransformState::hasMinTz() const
	{
		return m_bMinTz;
	}

	bool CPropertyTransformState::hasMinRx() const
	{
		return m_bMinRx;
	}

	bool CPropertyTransformState::hasMinRy() const
	{
		return m_bMinRy;
	}

	bool CPropertyTransformState::hasMinRz() const
	{
		return m_bMinRz;
	}

	bool CPropertyTransformState::hasMinSx() const
	{
		return m_bMinSx;
	}

	bool CPropertyTransformState::hasMinSy() const
	{
		return m_bMinSy;
	}

	bool CPropertyTransformState::hasMinSz() const
	{
		return m_bMinSz;
	}

	bool CPropertyTransformState::hasMaxTx() const
	{
		return m_bMaxTx;
	}

	bool CPropertyTransformState::hasMaxTy() const
	{
		return m_bMaxTy;
	}

	bool CPropertyTransformState::hasMaxTz() const
	{
		return m_bMaxTz;
	}

	bool CPropertyTransformState::hasMaxRx() const
	{
		return m_bMaxRx;
	}

	bool CPropertyTransformState::hasMaxRy() const
	{
		return m_bMaxRy;
	}

	bool CPropertyTransformState::hasMaxRz() const
	{
		return m_bMaxRz;
	}

	bool CPropertyTransformState::hasMaxSx() const
	{
		return m_bMaxSx;
	}

	bool CPropertyTransformState::hasMaxSy() const
	{
		return m_bMaxSy;
	}

	bool CPropertyTransformState::hasMaxSz() const
	{
		return m_bMaxSz;
	}

	float CPropertyTransformState::getMinTx() const
	{
		return m_fMinTx;
	}

	float CPropertyTransformState::getMinTy() const
	{
		return m_fMinTy;
	}

	float CPropertyTransformState::getMinTz() const
	{
		return m_fMinTz;
	}

	float CPropertyTransformState::getMinRx() const
	{
		return m_fMinRx;
	}

	float CPropertyTransformState::getMinRy() const
	{
		return m_fMinRy;
	}

	float CPropertyTransformState::getMinRz() const
	{
		return m_fMinRz;
	}

	float CPropertyTransformState::getMinSx() const
	{
		return m_fMinSx;
	}

	float CPropertyTransformState::getMinSy() const
	{
		return m_fMinSy;
	}

	float CPropertyTransformState::getMinSz() const
	{
		return m_fMinSz;
	}

	float CPropertyTransformState::getMaxTx() const
	{
		return m_fMaxTx;
	}

	float CPropertyTransformState::getMaxTy() const
	{
		return m_fMaxTy;
	}

	float CPropertyTransformState::getMaxTz() const
	{
		return m_fMaxTz;
	}

	float CPropertyTransformState::getMaxRx() const
	{
		return m_fMaxRx;
	}

	float CPropertyTransformState::getMaxRy() const
	{
		return m_fMaxRy;
	}

	float CPropertyTransformState::getMaxRz() const
	{
		return m_fMaxRz;
	}

	float CPropertyTransformState::getMaxSx() const
	{
		return m_fMaxSx;
	}

	float CPropertyTransformState::getMaxSy() const
	{
		return m_fMaxSy;
	}

	float CPropertyTransformState::getMaxSz() const
	{
		return m_fMaxSz;
	}
#pragma endregion

#pragma region IPropertyTransformState setters
	bool CPropertyTransformState::setValue(const String &state, const Transform value)
	{
		Transform v{ value };
		if (m_bMinTx)
			v.Tx = ntl::Max<float>(m_fMinTx, v.Tx);
		if (m_bMinTy)
			v.Ty = ntl::Max<float>(m_fMinTy, v.Ty);
		if (m_bMinTz)
			v.Tz = ntl::Max<float>(m_fMinTz, v.Tz);
		if (m_bMinSx)
			v.Sx = ntl::Max<float>(m_fMinSx, v.Sx);
		if (m_bMinSy)
			v.Sy = ntl::Max<float>(m_fMinSy, v.Sy);
		if (m_bMinSz)
			v.Sz = ntl::Max<float>(m_fMinSz, v.Sz);
		if (m_bMinRx)
			v.Rx = ntl::Max<float>(m_fMinRx, v.Rx);
		if (m_bMinRy)
			v.Ry = ntl::Max<float>(m_fMinRy, v.Ry);
		if (m_bMinRz)
			v.Rz = ntl::Max<float>(m_fMinRz, v.Rz);

		if (m_bMaxTx)
			v.Tx = ntl::Min<float>(m_fMaxTx, v.Tx);
		if (m_bMaxTy)
			v.Ty = ntl::Min<float>(m_fMaxTy, v.Ty);
		if (m_bMaxTz)
			v.Tz = ntl::Min<float>(m_fMaxTz, v.Tz);
		if (m_bMaxSx)
			v.Sx = ntl::Min<float>(m_fMaxSx, v.Sx);
		if (m_bMaxSy)
			v.Sy = ntl::Min<float>(m_fMaxSy, v.Sy);
		if (m_bMaxSz)
			v.Sz = ntl::Min<float>(m_fMaxSz, v.Sz);
		if (m_bMaxRx)
			v.Rx = ntl::Min<float>(m_fMaxRx, v.Rx);
		if (m_bMaxRy)
			v.Ry = ntl::Min<float>(m_fMaxRy, v.Ry);
		if (m_bMaxRz)
			v.Rz = ntl::Min<float>(m_fMaxRz, v.Rz);
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, state, v);
		if (IsNotEqual(v, m_aValue[state]))
		{
			m_aValue[state] = v;
			return true;
		}
		return false;
	}

	IPropertyTransformState *CPropertyTransformState::setAllowedTx(const bool value)
	{
		m_bTx = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setAllowedTy(const bool value)
	{
		m_bTy = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setAllowedTz(const bool value)
	{
		m_bTz = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setAllowedRx(const bool value)
	{
		m_bRx = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setAllowedRy(const bool value)
	{
		m_bRy = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setAllowedRz(const bool value)
	{
		m_bRz = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setAllowedSx(const bool value)
	{
		m_bSx = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setAllowedSy(const bool value)
	{
		m_bSy = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setAllowedSz(const bool value)
	{
		m_bSz = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setAllowedRotateOrder(const bool value)
	{
		m_bRotateOrder = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setAllowedTransformOrder(const bool value)
	{
		m_bTransformOrder = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMinTx(const bool value)
	{
		m_bMinTx = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMinTy(const bool value)
	{
		m_bMinTy = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMinTz(const bool value)
	{
		m_bMinTz = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMinRx(const bool value)
	{
		m_bMinRx = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMinRy(const bool value)
	{
		m_bMinRy = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMinRz(const bool value)
	{
		m_bMinRz = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMinSx(const bool value)
	{
		m_bMinSx = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMinSy(const bool value)
	{
		m_bMinSy = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMinSz(const bool value)
	{
		m_bMinSz = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMaxTx(const bool value)
	{
		m_bMaxTx = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMaxTy(const bool value)
	{
		m_bMaxTy = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMaxTz(const bool value)
	{
		m_bMaxTz = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMaxRx(const bool value)
	{
		m_bMaxRx = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMaxRy(const bool value)
	{
		m_bMaxRy = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMaxRz(const bool value)
	{
		m_bMaxRz = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMaxSx(const bool value)
	{
		m_bMaxSx = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMaxSy(const bool value)
	{
		m_bMaxSy = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setHasMaxSz(const bool value)
	{
		m_bMaxSz = value;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMinTx(const float value)
	{
		m_fMinTx = value;
		m_bMinTx = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMinTy(const float value)
	{
		m_fMinTy = value;
		m_bMinTy = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMinTz(const float value)
	{
		m_fMinTz = value;
		m_bMinTz = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMinRx(const float value)
	{
		m_fMinRx = value;
		m_bMinRx = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMinRy(const float value)
	{
		m_fMinRy = value;
		m_bMinRy = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMinRz(const float value)
	{
		m_fMinRz = value;
		m_bMinRz = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMinSx(const float value)
	{
		m_fMinSx = value;
		m_bMinSx = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMinSy(const float value)
	{
		m_fMinSy = value;
		m_bMinSy = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMinSz(const float value)
	{
		m_fMinSz = value;
		m_bMinSz = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMaxTx(const float value)
	{
		m_fMaxTx = value;
		m_bMaxTx = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMaxTy(const float value)
	{
		m_fMaxTy = value;
		m_bMaxTy = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMaxTz(const float value)
	{
		m_fMaxTz = value;
		m_bMaxTz = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMaxRx(const float value)
	{
		m_fMaxRx = value;
		m_bMaxRx = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMaxRy(const float value)
	{
		m_fMaxRy = value;
		m_bMaxRy = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMaxRz(const float value)
	{
		m_fMaxRz = value;
		m_bMaxRz = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMaxSx(const float value)
	{
		m_fMaxSx = value;
		m_bMaxSx = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMaxSy(const float value)
	{
		m_fMaxSy = value;
		m_bMaxSy = true;
		return this;
	}

	IPropertyTransformState *CPropertyTransformState::setMaxSz(const float value)
	{
		m_fMaxSz = value;
		m_bMaxSz = true;
		return this;
	}
#pragma endregion
}