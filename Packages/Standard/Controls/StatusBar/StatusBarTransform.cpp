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
		CStatusBarTransform::CStatusBarTransform() :
			CTransform(nullptr)
		{

		}
	#pragma endregion

	#pragma region Setters
		bool CStatusBarTransform::setTx(const float value)
		{
			return false;
		}

		bool CStatusBarTransform::setTy(const float value)
		{
			return false;
		}

		bool CStatusBarTransform::setTz(const float value)
		{
			return false;
		}

		bool CStatusBarTransform::setSx(const float value)
		{
			return false;
		}

		bool CStatusBarTransform::setSy(const float value)
		{
			return false;
		}

		bool CStatusBarTransform::setSz(const float value)
		{
			return false;
		}

		bool CStatusBarTransform::setRx(const float value)
		{
			return false;
		}

		bool CStatusBarTransform::setRy(const float value)
		{
			return false;
		}

		bool CStatusBarTransform::setRz(const float value)
		{
			return false;
		}

		bool CStatusBarTransform::setTransformOrder(const TransformOrder value)
		{
			return false;
		}

		bool CStatusBarTransform::setRotateOrder(const RotateOrder value)
		{
			return false;
		}

		bool CStatusBarTransform::setTransform(const nitisa::Transform &value)
		{
			return false;
		}
	#pragma endregion

	#pragma region Transformations
		bool CStatusBarTransform::Translate(const float tx, const float ty, const float tz)
		{
			return false;
		}

		bool CStatusBarTransform::Scale(const float sx, const float sy, const float sz)
		{
			return false;
		}

		bool CStatusBarTransform::Rotate(const float rx, const float ry, const float rz)
		{
			return false;
		}

		bool CStatusBarTransform::Transform(const float tx, const float ty, const float tz, const float sx, const float sy, const float sz, const float rx, const float ry, const float rz)
		{
			return false;
		}
	#pragma endregion
	}
}