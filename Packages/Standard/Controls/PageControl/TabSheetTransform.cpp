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
		CTabSheetTransform::CTabSheetTransform() :
			CTransform(nullptr)
		{

		}
	#pragma endregion

	#pragma region Setters
		bool CTabSheetTransform::setTx(const float value)
		{
			return false;
		}

		bool CTabSheetTransform::setTy(const float value)
		{
			return false;
		}

		bool CTabSheetTransform::setTz(const float value)
		{
			return false;
		}

		bool CTabSheetTransform::setSx(const float value)
		{
			return false;
		}

		bool CTabSheetTransform::setSy(const float value)
		{
			return false;
		}

		bool CTabSheetTransform::setSz(const float value)
		{
			return false;
		}

		bool CTabSheetTransform::setRx(const float value)
		{
			return false;
		}

		bool CTabSheetTransform::setRy(const float value)
		{
			return false;
		}

		bool CTabSheetTransform::setRz(const float value)
		{
			return false;
		}

		bool CTabSheetTransform::setTransformOrder(const TransformOrder value)
		{
			return false;
		}

		bool CTabSheetTransform::setRotateOrder(const RotateOrder value)
		{
			return false;
		}

		bool CTabSheetTransform::setTransform(const nitisa::Transform &value)
		{
			return false;
		}
	#pragma endregion

	#pragma region Transformations
		bool CTabSheetTransform::Translate(const float tx, const float ty, const float tz)
		{
			return false;
		}

		bool CTabSheetTransform::Scale(const float sx, const float sy, const float sz)
		{
			return false;
		}

		bool CTabSheetTransform::Rotate(const float rx, const float ry, const float rz)
		{
			return false;
		}

		bool CTabSheetTransform::Transform(const float tx, const float ty, const float tz, const float sx, const float sy, const float sz, const float rx, const float ry, const float rz)
		{
			return false;
		}
	#pragma endregion
	}
}