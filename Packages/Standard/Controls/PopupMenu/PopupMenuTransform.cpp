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
	namespace standard
	{
	#pragma region Constructor & destructor
		CPopupMenuTransform::CPopupMenuTransform(IFeedbackExListener *listener) :
			CTransform(listener)
		{

		}
	#pragma endregion

		bool CPopupMenuTransform::setTz(const float value)
		{
			return false;
		}

		bool CPopupMenuTransform::setSx(const float value)
		{
			return false;
		}

		bool CPopupMenuTransform::setSy(const float value)
		{
			return false;
		}

		bool CPopupMenuTransform::setSz(const float value)
		{
			return false;
		}

		bool CPopupMenuTransform::setRx(const float value)
		{
			return false;
		}

		bool CPopupMenuTransform::setRy(const float value)
		{
			return false;
		}

		bool CPopupMenuTransform::setRz(const float value)
		{
			return false;
		}

		bool CPopupMenuTransform::setTransformOrder(const TransformOrder value)
		{
			return false;
		}

		bool CPopupMenuTransform::setRotateOrder(const RotateOrder value)
		{
			return false;
		}

		bool CPopupMenuTransform::setTransform(const nitisa::Transform &value)
		{
			return CTransform::Translate(value.Tx, value.Ty, 0);
		}
	#pragma endregion

	#pragma region Transformations
		bool CPopupMenuTransform::Translate(const float tx, const float ty, const float tz)
		{
			return CTransform::Translate(tx, ty, 0);
		}

		bool CPopupMenuTransform::Scale(const float sx, const float sy, const float sz)
		{
			return false;
		}

		bool CPopupMenuTransform::Rotate(const float rx, const float ry, const float rz)
		{
			return false;
		}

		bool CPopupMenuTransform::Transform(const float tx, const float ty, const float tz, const float sx, const float sy, const float sz, const float rx, const float ry, const float rz)
		{
			return CTransform::Translate(tx, ty, 0);
		}
	#pragma endregion

	#pragma region Matrices
		const Mat4f &CPopupMenuTransform::getMatrix()
		{
			return getMatrixTranslate();
		}

		const Mat4f &CPopupMenuTransform::getMatrixScale()
		{
			return Identity;
		}

		const Mat4f &CPopupMenuTransform::getMatrixRotate()
		{
			return Identity;
		}

		bool CPopupMenuTransform::isTranslateIdentity() const
		{
			return ntl::IsEqual<float>(getTx(), 0) && ntl::IsEqual<float>(getTy(), 0);
		}

		bool CPopupMenuTransform::isScaleIdentity() const
		{
			return true;
		}

		bool CPopupMenuTransform::isRotateIdentity() const
		{
			return true;
		}

		bool CPopupMenuTransform::isIdentity() const
		{
			return ntl::IsEqual<float>(getTx(), 0) && ntl::IsEqual<float>(getTy(), 0);
		}
	#pragma endregion
	}
}