// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		CMainMenuTransform::CMainMenuTransform(IFeedbackExListener *listener) :
			CTransform(listener)
		{

		}
	#pragma endregion

	#pragma region Setters
		bool CMainMenuTransform::setTz(const float value)
		{
			return false;
		}

		bool CMainMenuTransform::setSx(const float value)
		{
			return false;
		}

		bool CMainMenuTransform::setSy(const float value)
		{
			return false;
		}

		bool CMainMenuTransform::setSz(const float value)
		{
			return false;
		}

		bool CMainMenuTransform::setRx(const float value)
		{
			return false;
		}

		bool CMainMenuTransform::setRy(const float value)
		{
			return false;
		}

		bool CMainMenuTransform::setRz(const float value)
		{
			return false;
		}

		bool CMainMenuTransform::setTransformOrder(const TransformOrder value)
		{
			return false;
		}

		bool CMainMenuTransform::setRotateOrder(const RotateOrder value)
		{
			return false;
		}

		bool CMainMenuTransform::setTransform(const nitisa::Transform &value)
		{
			return CTransform::setTransform(nitisa::Transform{ value.Tx, value.Ty, 0, 1, 1, 1, 0, 0, 0, m_sTransform.RotateOrder, m_sTransform.TransformOrder });
		}
	#pragma endregion

	#pragma region Transformations
		bool CMainMenuTransform::Translate(const float tx, const float ty, const float tz)
		{
			return CTransform::Translate(tx, ty, 0);
		}

		bool CMainMenuTransform::Scale(const float sx, const float sy, const float sz)
		{
			return false;
		}

		bool CMainMenuTransform::Rotate(const float rx, const float ry, const float rz)
		{
			return false;
		}

		bool CMainMenuTransform::Transform(const float tx, const float ty, const float tz, const float sx, const float sy, const float sz, const float rx, const float ry, const float rz)
		{
			return CTransform::Transform(tx, ty, 0, 1, 1, 1, 0, 0, 0);
		}
	#pragma endregion

	#pragma region Matrices
		bool CMainMenuTransform::isScaleIdentity() const
		{
			return true;
		}

		bool CMainMenuTransform::isRotateIdentity() const
		{
			return true;
		}

		bool CMainMenuTransform::isIdentity() const
		{
			return ntl::IsZero<float>(m_sTransform.Tx) && ntl::IsZero<float>(m_sTransform.Ty);
		}
	#pragma endregion
	}
}