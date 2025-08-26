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
	CPropertyTransform::CPropertyTransform(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerTransform, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
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
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyTransform::getPreview()
	{
		return ToString(getValue());
	}

	String CPropertyTransform::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyTransform::isChanged()
	{
		return m_bChanged || IsNotEqual(getValue(), m_tOld);
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyTransform::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyTransform::Copy(IProperty *dest)
	{
		IPropertyTransform *d{ cast<IPropertyTransform*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyTransform::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyTransform::Load(const Variant &src)
	{
		Transform v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyTransform::Export(std::wofstream &f, const String &shift, const String &control)
	{
		Transform v{ getValue() };
		if (v.RotateOrder == RotateOrder::XYZ && v.TransformOrder == TransformOrder::TRS)
		{
			if (ntl::IsEqual<float>(v.Sx, 1) && ntl::IsEqual<float>(v.Sy, 1) && ntl::IsEqual<float>(v.Sz, 1) && ntl::IsZero<float>(v.Rx) && ntl::IsZero<float>(v.Ry) && ntl::IsZero<float>(v.Rz))
			{
				if (control.empty())
					f << shift << L"get" << m_sName << L"()->Translate(" << AsSourceCode(v.Tx) << L", " << AsSourceCode(v.Ty) << L", " << AsSourceCode(v.Tz) << L");" << std::endl;
				else
					f << shift << control << L"->get" << m_sName << L"()->Translate(" << AsSourceCode(v.Tx) << L", " << AsSourceCode(v.Ty) << L", " << AsSourceCode(v.Tz) << L");" << std::endl;
				return;
			}
			if (ntl::IsEqual<float>(v.Sx, 1) && ntl::IsEqual<float>(v.Sy, 1) && ntl::IsEqual<float>(v.Sz, 1) && ntl::IsZero<float>(v.Tx) && ntl::IsZero<float>(v.Ty) && ntl::IsZero<float>(v.Tz))
			{
				if (control.empty())
					f << shift << L"get" << m_sName << L"()->Rotate(" << AsSourceCode(v.Rx) << L", " << AsSourceCode(v.Ry) << L", " << AsSourceCode(v.Rz) << L");" << std::endl;
				else
					f << shift << control << L"->get" << m_sName << L"()->Rotate(" << AsSourceCode(v.Rx) << L", " << AsSourceCode(v.Ry) << L", " << AsSourceCode(v.Rz) << L");" << std::endl;
				return;
			}
			if (ntl::IsZero<float>(v.Tx) && ntl::IsZero<float>(v.Ty) && ntl::IsZero<float>(v.Tz) && ntl::IsZero<float>(v.Rx) && ntl::IsZero<float>(v.Ry) && ntl::IsZero<float>(v.Rz))
			{
				if (control.empty())
					f << shift << L"get" << m_sName << L"()->Scale(" << AsSourceCode(v.Sx) << L", " << AsSourceCode(v.Sy) << L", " << AsSourceCode(v.Sz) << L");" << std::endl;
				else
					f << shift << control << L"->get" << m_sName << L"()->Scale(" << AsSourceCode(v.Sx) << L", " << AsSourceCode(v.Sy) << L", " << AsSourceCode(v.Sz) << L");" << std::endl;
				return;
			}
		}
		if (control.empty())
			f << shift << L"get" << m_sName << L"()->setTransform(" << AsSourceCode(v) << L");" << std::endl;
		else
			f << shift << control << L"->get" << m_sName << L"()->setTransform(" << AsSourceCode(v) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyTransform getters
	Transform CPropertyTransform::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	bool CPropertyTransform::isAllowedTx() const
	{
		return m_bTx;
	}

	bool CPropertyTransform::isAllowedTy() const
	{
		return m_bTy;
	}

	bool CPropertyTransform::isAllowedTz() const
	{
		return m_bTz;
	}

	bool CPropertyTransform::isAllowedRx() const
	{
		return m_bRx;
	}

	bool CPropertyTransform::isAllowedRy() const
	{
		return m_bRy;
	}

	bool CPropertyTransform::isAllowedRz() const
	{
		return m_bRz;
	}

	bool CPropertyTransform::isAllowedSx() const
	{
		return m_bSx;
	}

	bool CPropertyTransform::isAllowedSy() const
	{
		return m_bSy;
	}

	bool CPropertyTransform::isAllowedSz() const
	{
		return m_bSz;
	}

	bool CPropertyTransform::isAllowedRotateOrder() const
	{
		return m_bRotateOrder;
	}

	bool CPropertyTransform::isAllowedTransformOrder() const
	{
		return m_bTransformOrder;
	}

	bool CPropertyTransform::hasMinTx() const
	{
		return m_bMinTx;
	}

	bool CPropertyTransform::hasMinTy() const
	{
		return m_bMinTy;
	}

	bool CPropertyTransform::hasMinTz() const
	{
		return m_bMinTz;
	}

	bool CPropertyTransform::hasMinRx() const
	{
		return m_bMinRx;
	}

	bool CPropertyTransform::hasMinRy() const
	{
		return m_bMinRy;
	}

	bool CPropertyTransform::hasMinRz() const
	{
		return m_bMinRz;
	}

	bool CPropertyTransform::hasMinSx() const
	{
		return m_bMinSx;
	}

	bool CPropertyTransform::hasMinSy() const
	{
		return m_bMinSy;
	}

	bool CPropertyTransform::hasMinSz() const
	{
		return m_bMinSz;
	}

	bool CPropertyTransform::hasMaxTx() const
	{
		return m_bMaxTx;
	}

	bool CPropertyTransform::hasMaxTy() const
	{
		return m_bMaxTy;
	}

	bool CPropertyTransform::hasMaxTz() const
	{
		return m_bMaxTz;
	}

	bool CPropertyTransform::hasMaxRx() const
	{
		return m_bMaxRx;
	}

	bool CPropertyTransform::hasMaxRy() const
	{
		return m_bMaxRy;
	}

	bool CPropertyTransform::hasMaxRz() const
	{
		return m_bMaxRz;
	}

	bool CPropertyTransform::hasMaxSx() const
	{
		return m_bMaxSx;
	}

	bool CPropertyTransform::hasMaxSy() const
	{
		return m_bMaxSy;
	}

	bool CPropertyTransform::hasMaxSz() const
	{
		return m_bMaxSz;
	}

	float CPropertyTransform::getMinTx() const
	{
		return m_fMinTx;
	}

	float CPropertyTransform::getMinTy() const
	{
		return m_fMinTy;
	}

	float CPropertyTransform::getMinTz() const
	{
		return m_fMinTz;
	}

	float CPropertyTransform::getMinRx() const
	{
		return m_fMinRx;
	}

	float CPropertyTransform::getMinRy() const
	{
		return m_fMinRy;
	}

	float CPropertyTransform::getMinRz() const
	{
		return m_fMinRz;
	}

	float CPropertyTransform::getMinSx() const
	{
		return m_fMinSx;
	}

	float CPropertyTransform::getMinSy() const
	{
		return m_fMinSy;
	}

	float CPropertyTransform::getMinSz() const
	{
		return m_fMinSz;
	}

	float CPropertyTransform::getMaxTx() const
	{
		return m_fMaxTx;
	}

	float CPropertyTransform::getMaxTy() const
	{
		return m_fMaxTy;
	}

	float CPropertyTransform::getMaxTz() const
	{
		return m_fMaxTz;
	}

	float CPropertyTransform::getMaxRx() const
	{
		return m_fMaxRx;
	}

	float CPropertyTransform::getMaxRy() const
	{
		return m_fMaxRy;
	}

	float CPropertyTransform::getMaxRz() const
	{
		return m_fMaxRz;
	}

	float CPropertyTransform::getMaxSx() const
	{
		return m_fMaxSx;
	}

	float CPropertyTransform::getMaxSy() const
	{
		return m_fMaxSy;
	}

	float CPropertyTransform::getMaxSz() const
	{
		return m_fMaxSz;
	}
#pragma endregion

#pragma region IPropertyTransform setters
	bool CPropertyTransform::setValue(const Transform value)
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
			return m_fSetter(m_pParent, v);
		if (IsNotEqual(v, m_tValue))
		{
			m_tValue = v;
			return true;
		}
		return false;
	}

	IPropertyTransform *CPropertyTransform::setAllowedTx(const bool value)
	{
		m_bTx = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setAllowedTy(const bool value)
	{
		m_bTy = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setAllowedTz(const bool value)
	{
		m_bTz = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setAllowedRx(const bool value)
	{
		m_bRx = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setAllowedRy(const bool value)
	{
		m_bRy = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setAllowedRz(const bool value)
	{
		m_bRz = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setAllowedSx(const bool value)
	{
		m_bSx = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setAllowedSy(const bool value)
	{
		m_bSy = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setAllowedSz(const bool value)
	{
		m_bSz = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setAllowedRotateOrder(const bool value)
	{
		m_bRotateOrder = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setAllowedTransformOrder(const bool value)
	{
		m_bTransformOrder = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMinTx(const bool value)
	{
		m_bMinTx = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMinTy(const bool value)
	{
		m_bMinTy = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMinTz(const bool value)
	{
		m_bMinTz = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMinRx(const bool value)
	{
		m_bMinRx = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMinRy(const bool value)
	{
		m_bMinRy = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMinRz(const bool value)
	{
		m_bMinRz = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMinSx(const bool value)
	{
		m_bMinSx = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMinSy(const bool value)
	{
		m_bMinSy = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMinSz(const bool value)
	{
		m_bMinSz = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMaxTx(const bool value)
	{
		m_bMaxTx = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMaxTy(const bool value)
	{
		m_bMaxTy = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMaxTz(const bool value)
	{
		m_bMaxTz = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMaxRx(const bool value)
	{
		m_bMaxRx = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMaxRy(const bool value)
	{
		m_bMaxRy = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMaxRz(const bool value)
	{
		m_bMaxRz = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMaxSx(const bool value)
	{
		m_bMaxSx = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMaxSy(const bool value)
	{
		m_bMaxSy = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setHasMaxSz(const bool value)
	{
		m_bMaxSz = value;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMinTx(const float value)
	{
		m_fMinTx = value;
		m_bMinTx = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMinTy(const float value)
	{
		m_fMinTy = value;
		m_bMinTy = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMinTz(const float value)
	{
		m_fMinTz = value;
		m_bMinTz = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMinRx(const float value)
	{
		m_fMinRx = value;
		m_bMinRx = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMinRy(const float value)
	{
		m_fMinRy = value;
		m_bMinRy = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMinRz(const float value)
	{
		m_fMinRz = value;
		m_bMinRz = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMinSx(const float value)
	{
		m_fMinSx = value;
		m_bMinSx = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMinSy(const float value)
	{
		m_fMinSy = value;
		m_bMinSy = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMinSz(const float value)
	{
		m_fMinSz = value;
		m_bMinSz = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMaxTx(const float value)
	{
		m_fMaxTx = value;
		m_bMaxTx = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMaxTy(const float value)
	{
		m_fMaxTy = value;
		m_bMaxTy = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMaxTz(const float value)
	{
		m_fMaxTz = value;
		m_bMaxTz = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMaxRx(const float value)
	{
		m_fMaxRx = value;
		m_bMaxRx = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMaxRy(const float value)
	{
		m_fMaxRy = value;
		m_bMaxRy = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMaxRz(const float value)
	{
		m_fMaxRz = value;
		m_bMaxRz = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMaxSx(const float value)
	{
		m_fMaxSx = value;
		m_bMaxSx = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMaxSy(const float value)
	{
		m_fMaxSy = value;
		m_bMaxSy = true;
		return this;
	}

	IPropertyTransform *CPropertyTransform::setMaxSz(const float value)
	{
		m_fMaxSz = value;
		m_bMaxSz = true;
		return this;
	}
#pragma endregion
}