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
	CTransformService::CTransformService(CTransform *transform) :
		m_pTransform{ transform }
	{

	}

	void CTransformService::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Setters
	bool CTransformService::setTx(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_pTransform->m_sTransform.Tx))
		{
			m_pTransform->m_sTransform.Tx = value;
			m_pTransform->m_bMatrixTranslate = m_pTransform->m_bMatrix = m_pTransform->m_bMatrixInversed = false;
			return true;
		}
		return false;
	}

	bool CTransformService::setTy(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_pTransform->m_sTransform.Ty))
		{
			m_pTransform->m_sTransform.Ty = value;
			m_pTransform->m_bMatrixTranslate = m_pTransform->m_bMatrix = m_pTransform->m_bMatrixInversed = false;
			return true;
		}
		return false;
	}

	bool CTransformService::setTz(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_pTransform->m_sTransform.Tz))
		{
			m_pTransform->m_sTransform.Tz = value;
			m_pTransform->m_bMatrixTranslate = m_pTransform->m_bMatrix = m_pTransform->m_bMatrixInversed = false;
			return true;
		}
		return false;
	}

	bool CTransformService::setSx(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_pTransform->m_sTransform.Sx))
		{
			m_pTransform->m_sTransform.Sx = value;
			m_pTransform->m_bMatrixScale = m_pTransform->m_bMatrix = m_pTransform->m_bMatrixInversed = false;
			return true;
		}
		return false;
	}

	bool CTransformService::setSy(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_pTransform->m_sTransform.Sy))
		{
			m_pTransform->m_sTransform.Sy = value;
			m_pTransform->m_bMatrixScale = m_pTransform->m_bMatrix = m_pTransform->m_bMatrixInversed = false;
			return true;
		}
		return false;
	}

	bool CTransformService::setSz(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_pTransform->m_sTransform.Sz))
		{
			m_pTransform->m_sTransform.Sz = value;
			m_pTransform->m_bMatrixScale = m_pTransform->m_bMatrix = m_pTransform->m_bMatrixInversed = false;
			return true;
		}
		return false;
	}

	bool CTransformService::setRx(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_pTransform->m_sTransform.Rx))
		{
			m_pTransform->m_sTransform.Rx = value;
			m_pTransform->m_bMatrixRx = m_pTransform->m_bMatrixRotate = m_pTransform->m_bMatrix = m_pTransform->m_bMatrixInversed = false;
			return true;
		}
		return false;
	}

	bool CTransformService::setRy(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_pTransform->m_sTransform.Ry))
		{
			m_pTransform->m_sTransform.Ry = value;
			m_pTransform->m_bMatrixRy = m_pTransform->m_bMatrixRotate = m_pTransform->m_bMatrix = m_pTransform->m_bMatrixInversed = false;
			return true;
		}
		return false;
	}

	bool CTransformService::setRz(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_pTransform->m_sTransform.Rz))
		{
			m_pTransform->m_sTransform.Rz = value;
			m_pTransform->m_bMatrixRz = m_pTransform->m_bMatrixRotate = m_pTransform->m_bMatrix = m_pTransform->m_bMatrixInversed = false;
			return true;
		}
		return false;
	}

	bool CTransformService::setTransformOrder(const TransformOrder value)
	{
		if (value != m_pTransform->m_sTransform.TransformOrder)
		{
			m_pTransform->m_sTransform.TransformOrder = value;
			m_pTransform->m_bMatrix = m_pTransform->m_bMatrixInversed = false;
			return true;
		}
		return false;
	}

	bool CTransformService::setRotateOrder(const RotateOrder value)
	{
		if (value != m_pTransform->m_sTransform.RotateOrder)
		{
			m_pTransform->m_sTransform.RotateOrder = value;
			m_pTransform->m_bMatrixRotate = m_pTransform->m_bMatrix = m_pTransform->m_bMatrixInversed = false;
			return true;
		}
		return false;
	}

	bool CTransformService::setTransform(const nitisa::Transform &value)
	{
		if (IsNotEqual(value, m_pTransform->m_sTransform))
		{
			m_pTransform->m_sTransform = value;
			m_pTransform->m_bMatrixTranslate = m_pTransform->m_bMatrixScale = m_pTransform->m_bMatrixRx = m_pTransform->m_bMatrixRy = m_pTransform->m_bMatrixRz = m_pTransform->m_bMatrixRotate =
				m_pTransform->m_bMatrix = m_pTransform->m_bMatrixInversed = false;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Transformations
	bool CTransformService::Translate(const float tx, const float ty, const float tz)
	{
		if (ntl::IsNotEqual<float>(tx, m_pTransform->m_sTransform.Tx) || ntl::IsNotEqual<float>(ty, m_pTransform->m_sTransform.Ty) || ntl::IsNotEqual<float>(tz, m_pTransform->m_sTransform.Tz))
		{
			m_pTransform->m_sTransform.Tx = tx;
			m_pTransform->m_sTransform.Ty = ty;
			m_pTransform->m_sTransform.Tz = tz;
			m_pTransform->m_bMatrixTranslate = m_pTransform->m_bMatrix = m_pTransform->m_bMatrixInversed = false;
			return true;
		}
		return false;
	}

	bool CTransformService::Scale(const float sx, const float sy, const float sz)
	{
		if (ntl::IsNotEqual<float>(sx, m_pTransform->m_sTransform.Sx) || ntl::IsNotEqual<float>(sy, m_pTransform->m_sTransform.Sy) || ntl::IsNotEqual<float>(sz, m_pTransform->m_sTransform.Sz))
		{
			m_pTransform->m_sTransform.Sx = sx;
			m_pTransform->m_sTransform.Sy = sy;
			m_pTransform->m_sTransform.Sz = sz;
			m_pTransform->m_bMatrixScale = m_pTransform->m_bMatrix = m_pTransform->m_bMatrixInversed = false;
			return true;
		}
		return false;
	}

	bool CTransformService::Rotate(const float rx, const float ry, const float rz)
	{
		if (ntl::IsNotEqual<float>(rx, m_pTransform->m_sTransform.Rx) || ntl::IsNotEqual<float>(ry, m_pTransform->m_sTransform.Ry) || ntl::IsNotEqual<float>(rz, m_pTransform->m_sTransform.Rz))
		{
			m_pTransform->m_sTransform.Rx = rx;
			m_pTransform->m_sTransform.Ry = ry;
			m_pTransform->m_sTransform.Rz = rz;
			m_pTransform->m_bMatrixRx = m_pTransform->m_bMatrixRy = m_pTransform->m_bMatrixRz = m_pTransform->m_bMatrixRotate = m_pTransform->m_bMatrix = m_pTransform->m_bMatrixInversed = false;
			return true;
		}
		return false;
	}

	bool CTransformService::Transform(const float tx, const float ty, const float tz, const float sx, const float sy, const float sz, const float rx, const float ry, const float rz)
	{
		if (ntl::IsNotEqual<float>(tx, m_pTransform->m_sTransform.Tx) || ntl::IsNotEqual<float>(ty, m_pTransform->m_sTransform.Ty) || ntl::IsNotEqual<float>(tz, m_pTransform->m_sTransform.Tz) ||
			ntl::IsNotEqual<float>(sx, m_pTransform->m_sTransform.Sx) || ntl::IsNotEqual<float>(sy, m_pTransform->m_sTransform.Sy) || ntl::IsNotEqual<float>(sz, m_pTransform->m_sTransform.Sz) ||
			ntl::IsNotEqual<float>(rx, m_pTransform->m_sTransform.Rx) || ntl::IsNotEqual<float>(ry, m_pTransform->m_sTransform.Ry) || ntl::IsNotEqual<float>(rz, m_pTransform->m_sTransform.Rz))
		{
			m_pTransform->m_sTransform.Tx = tx;
			m_pTransform->m_sTransform.Ty = ty;
			m_pTransform->m_sTransform.Tz = tz;
			m_pTransform->m_sTransform.Sx = sx;
			m_pTransform->m_sTransform.Sy = sy;
			m_pTransform->m_sTransform.Sz = sz;
			m_pTransform->m_sTransform.Rx = rx;
			m_pTransform->m_sTransform.Ry = ry;
			m_pTransform->m_sTransform.Rz = rz;
			m_pTransform->m_bMatrixTranslate = m_pTransform->m_bMatrixScale = m_pTransform->m_bMatrixRx = m_pTransform->m_bMatrixRy = m_pTransform->m_bMatrixRz = m_pTransform->m_bMatrixRotate =
				m_pTransform->m_bMatrix = m_pTransform->m_bMatrixInversed = false;
			return true;
		}
		return false;
	}
#pragma endregion
}