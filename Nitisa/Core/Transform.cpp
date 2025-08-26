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
	CTransform::CTransform(IFeedbackExListener *listener) :
		CFeedbackEx(listener),
		m_sMatrixTranslate{ Identity },
		m_sMatrixScale{ Identity },
		m_sMatrixRx{ Identity },
		m_sMatrixRy{ Identity },
		m_sMatrixRz{ Identity },
		m_sMatrixRotate{ Identity },
		m_sMatrix{ Identity },
		m_sMatrixInversed{ Identity },
		m_bMatrixTranslate{ true },
		m_bMatrixScale{ true },
		m_bMatrixRx{ true },
		m_bMatrixRy{ true },
		m_bMatrixRz{ true },
		m_bMatrixRotate{ true },
		m_bMatrix{ true },
		m_bMatrixInversed{ true },
		m_pService{ nullptr },
		m_sTransform{ 0, 0, 0, 1, 1, 1, 0, 0, 0, RotateOrder::XYZ, TransformOrder::TRS }
	{

	}

	CTransform::~CTransform()
	{
		if (m_pService)
			m_pService->Release();
	}

	void CTransform::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Getters
	float CTransform::getTx() const
	{
		return m_sTransform.Tx;
	}

	float CTransform::getTy() const
	{
		return m_sTransform.Ty;
	}

	float CTransform::getTz() const
	{
		return m_sTransform.Tz;
	}

	float CTransform::getSx() const
	{
		return m_sTransform.Sx;
	}

	float CTransform::getSy() const
	{
		return m_sTransform.Sy;
	}

	float CTransform::getSz() const
	{
		return m_sTransform.Sz;
	}

	float CTransform::getRx() const
	{
		return m_sTransform.Rx;
	}

	float CTransform::getRy() const
	{
		return m_sTransform.Ry;
	}

	float CTransform::getRz() const
	{
		return m_sTransform.Rz;
	}

	TransformOrder CTransform::getTransformOrder() const
	{
		return m_sTransform.TransformOrder;
	}

	RotateOrder CTransform::getRotateOrder() const
	{
		return m_sTransform.RotateOrder;
	}
#pragma endregion

#pragma region Setters
	bool CTransform::setTx(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_sTransform.Tx) && FeedbackBefore())
		{
			m_sTransform.Tx = value;
			m_bMatrixTranslate = m_bMatrix = m_bMatrixInversed = false;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CTransform::setTy(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_sTransform.Ty) && FeedbackBefore())
		{
			m_sTransform.Ty = value;
			m_bMatrixTranslate = m_bMatrix = m_bMatrixInversed = false;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CTransform::setTz(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_sTransform.Tz) && FeedbackBefore())
		{
			m_sTransform.Tz = value;
			m_bMatrixTranslate = m_bMatrix = m_bMatrixInversed = false;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CTransform::setSx(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_sTransform.Sx) && FeedbackBefore())
		{
			m_sTransform.Sx = value;
			m_bMatrixScale = m_bMatrix = m_bMatrixInversed = false;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CTransform::setSy(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_sTransform.Sy) && FeedbackBefore())
		{
			m_sTransform.Sy = value;
			m_bMatrixScale = m_bMatrix = m_bMatrixInversed = false;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CTransform::setSz(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_sTransform.Sz) && FeedbackBefore())
		{
			m_sTransform.Sz = value;
			m_bMatrixScale = m_bMatrix = m_bMatrixInversed = false;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CTransform::setRx(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_sTransform.Rx) && FeedbackBefore())
		{
			m_sTransform.Rx = value;
			m_bMatrixRx = m_bMatrixRotate = m_bMatrix = m_bMatrixInversed = false;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CTransform::setRy(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_sTransform.Ry) && FeedbackBefore())
		{
			m_sTransform.Ry = value;
			m_bMatrixRy = m_bMatrixRotate = m_bMatrix = m_bMatrixInversed = false;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CTransform::setRz(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_sTransform.Rz) && FeedbackBefore())
		{
			m_sTransform.Rz = value;
			m_bMatrixRz = m_bMatrixRotate = m_bMatrix = m_bMatrixInversed = false;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CTransform::setTransformOrder(const TransformOrder value)
	{
		if (value != m_sTransform.TransformOrder && FeedbackBefore())
		{
			m_sTransform.TransformOrder = value;
			m_bMatrix = m_bMatrixInversed = false;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CTransform::setRotateOrder(const RotateOrder value)
	{
		if (value != m_sTransform.RotateOrder && FeedbackBefore())
		{
			m_sTransform.RotateOrder = value;
			m_bMatrixRotate = m_bMatrix = m_bMatrixInversed = false;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CTransform::setTransform(const nitisa::Transform &value)
	{
		if (IsNotEqual(value, m_sTransform) && FeedbackBefore())
		{
			m_sTransform = value;
			m_bMatrixTranslate = m_bMatrixScale = m_bMatrixRx = m_bMatrixRy = m_bMatrixRz = m_bMatrixRotate = m_bMatrix = m_bMatrixInversed = false;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Transformations
	ITransformService *CTransform::QueryService()
	{
		if (!m_pService)
			m_pService = new CTransformService(this);
		return m_pService;
	}

	bool CTransform::Translate(const float tx, const float ty, const float tz)
	{
		if ((ntl::IsNotEqual<float>(tx, m_sTransform.Tx) || ntl::IsNotEqual<float>(ty, m_sTransform.Ty) || ntl::IsNotEqual<float>(tz, m_sTransform.Tz)) && FeedbackBefore())
		{
			m_sTransform.Tx = tx;
			m_sTransform.Ty = ty;
			m_sTransform.Tz = tz;
			m_bMatrixTranslate = m_bMatrix = m_bMatrixInversed = false;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CTransform::Scale(const float sx, const float sy, const float sz)
	{
		if ((ntl::IsNotEqual<float>(sx, m_sTransform.Sx) || ntl::IsNotEqual<float>(sy, m_sTransform.Sy) || ntl::IsNotEqual<float>(sz, m_sTransform.Sz)) && FeedbackBefore())
		{
			m_sTransform.Sx = sx;
			m_sTransform.Sy = sy;
			m_sTransform.Sz = sz;
			m_bMatrixScale = m_bMatrix = m_bMatrixInversed = false;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CTransform::Rotate(const float rx, const float ry, const float rz)
	{
		if ((ntl::IsNotEqual<float>(rx, m_sTransform.Rx) || ntl::IsNotEqual<float>(ry, m_sTransform.Ry) || ntl::IsNotEqual<float>(rz, m_sTransform.Rz)) && FeedbackBefore())
		{
			m_sTransform.Rx = rx;
			m_sTransform.Ry = ry;
			m_sTransform.Rz = rz;
			m_bMatrixRx = m_bMatrixRy = m_bMatrixRz = m_bMatrixRotate = m_bMatrix = m_bMatrixInversed = false;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CTransform::Transform(const float tx, const float ty, const float tz, const float sx, const float sy, const float sz, const float rx, const float ry, const float rz)
	{
		if ((ntl::IsNotEqual<float>(tx, m_sTransform.Tx) || ntl::IsNotEqual<float>(ty, m_sTransform.Ty) || ntl::IsNotEqual<float>(tz, m_sTransform.Tz) ||
			ntl::IsNotEqual<float>(sx, m_sTransform.Sx) || ntl::IsNotEqual<float>(sy, m_sTransform.Sy) || ntl::IsNotEqual<float>(sz, m_sTransform.Sz) ||
			ntl::IsNotEqual<float>(rx, m_sTransform.Rx) || ntl::IsNotEqual<float>(ry, m_sTransform.Ry) || ntl::IsNotEqual<float>(rz, m_sTransform.Rz)) &&
			FeedbackBefore())
		{
			m_sTransform.Tx = tx;
			m_sTransform.Ty = ty;
			m_sTransform.Tz = tz;
			m_sTransform.Sx = sx;
			m_sTransform.Sy = sy;
			m_sTransform.Sz = sz;
			m_sTransform.Rx = rx;
			m_sTransform.Ry = ry;
			m_sTransform.Rz = rz;
			m_bMatrixTranslate = m_bMatrixScale = m_bMatrixRx = m_bMatrixRy = m_bMatrixRz = m_bMatrixRotate = m_bMatrix = m_bMatrixInversed = false;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Matrices
	const Mat4f &CTransform::getMatrix()
	{
		if (!m_bMatrix)
		{
			switch (m_sTransform.TransformOrder)
			{
			case TransformOrder::SRT:
				m_sMatrix = getMatrixScale() * getMatrixRotate() * getMatrixTranslate();
				break;
			case TransformOrder::STR:
				m_sMatrix = getMatrixScale() * getMatrixTranslate() * getMatrixRotate();
				break;
			case TransformOrder::RST:
				m_sMatrix = getMatrixRotate() * getMatrixScale() * getMatrixTranslate();
				break;
			case TransformOrder::RTS:
				m_sMatrix = getMatrixRotate() * getMatrixTranslate() * getMatrixScale();
				break;
			case TransformOrder::TSR:
				m_sMatrix = getMatrixTranslate() * getMatrixScale() * getMatrixRotate();
				break;
			case TransformOrder::TRS:
				m_sMatrix = getMatrixTranslate() * getMatrixRotate() * getMatrixScale();
				break;
			}
			m_bMatrix = true;
		}
		return m_sMatrix;
	}

	const Mat4f &CTransform::getMatrixInversed()
	{
		if (!m_bMatrixInversed)
		{
			m_sMatrixInversed = ntl::Inversed<float>(getMatrix());
			m_bMatrixInversed = true;
		}
		return m_sMatrixInversed;
	}

	const Mat4f &CTransform::getMatrixTranslate()
	{
		if (!m_bMatrixTranslate)
		{
			ntl::Translate<float>(m_sMatrixTranslate, m_sTransform.Tx, m_sTransform.Ty, m_sTransform.Tz);
			m_bMatrixTranslate = true;
		}
		return m_sMatrixTranslate;
	}

	const Mat4f &CTransform::getMatrixScale()
	{
		if (!m_bMatrixScale)
		{
			ntl::Scale<float>(m_sMatrixScale, m_sTransform.Sx, m_sTransform.Sy, m_sTransform.Sz);
			m_bMatrixScale = true;
		}
		return m_sMatrixScale;
	}

	const Mat4f &CTransform::getMatrixRotate()
	{
		if (!m_bMatrixRotate)
		{
			if (!m_bMatrixRx)
			{
				ntl::RotateX<float>(m_sMatrixRx, m_sTransform.Rx);
				m_bMatrixRx = true;
			}
			if (!m_bMatrixRy)
			{
				ntl::RotateY<float>(m_sMatrixRy, m_sTransform.Ry);
				m_bMatrixRy = true;
			}
			if (!m_bMatrixRz)
			{
				ntl::RotateZ<float>(m_sMatrixRz, m_sTransform.Rz);
				m_bMatrixRz = true;
			}
			switch (m_sTransform.RotateOrder)
			{
			case RotateOrder::XYZ:
				m_sMatrixRotate = m_sMatrixRx * m_sMatrixRy * m_sMatrixRz;
				break;
			case RotateOrder::XZY:
				m_sMatrixRotate = m_sMatrixRx * m_sMatrixRz * m_sMatrixRy;
				break;
			case RotateOrder::YXZ:
				m_sMatrixRotate = m_sMatrixRy * m_sMatrixRx * m_sMatrixRz;
				break;
			case RotateOrder::YZX:
				m_sMatrixRotate = m_sMatrixRy * m_sMatrixRz * m_sMatrixRx;
				break;
			case RotateOrder::ZXY:
				m_sMatrixRotate = m_sMatrixRz * m_sMatrixRx * m_sMatrixRy;
				break;
			case RotateOrder::ZYX:
				m_sMatrixRotate = m_sMatrixRz * m_sMatrixRy * m_sMatrixRx;
				break;
			}
			m_bMatrixRotate = true;
		}
		return m_sMatrixRotate;
	}

	const nitisa::Transform &CTransform::getTransform()
	{
		return m_sTransform;
	}

	bool CTransform::isTranslateIdentity() const
	{
		return ntl::IsEqual<float>(m_sTransform.Tx, 0) && ntl::IsEqual<float>(m_sTransform.Ty, 0) && ntl::IsEqual<float>(m_sTransform.Tz, 0);
	}

	bool CTransform::isScaleIdentity() const
	{
		return ntl::IsEqual<float>(m_sTransform.Sx, 1) && ntl::IsEqual<float>(m_sTransform.Sy, 1) && ntl::IsEqual<float>(m_sTransform.Sz, 1);
	}

	bool CTransform::isRotateIdentity() const
	{
		return ntl::IsEqual<float>(m_sTransform.Rx, 0) && ntl::IsEqual<float>(m_sTransform.Ry, 0) && ntl::IsEqual<float>(m_sTransform.Rz, 0);
	}

	bool CTransform::isIdentity() const
	{
		return
			ntl::IsEqual<float>(m_sTransform.Tx, 0) && ntl::IsEqual<float>(m_sTransform.Ty, 0) && ntl::IsEqual<float>(m_sTransform.Tz, 0) &&
			ntl::IsEqual<float>(m_sTransform.Sx, 1) && ntl::IsEqual<float>(m_sTransform.Sy, 1) && ntl::IsEqual<float>(m_sTransform.Sz, 1) &&
			ntl::IsEqual<float>(m_sTransform.Rx, 0) && ntl::IsEqual<float>(m_sTransform.Ry, 0) && ntl::IsEqual<float>(m_sTransform.Rz, 0);
	}
#pragma endregion

#pragma region Helpers
	bool CTransform::FeedbackBefore()
	{
		if (m_pListener)
		{
			bool allowed{ true };
			m_pListener->NotifyOnBeforeChange(allowed);
			return allowed;
		}
		return true;
	}
#pragma endregion
}