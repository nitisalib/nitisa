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
#pragma region Constructor & destructor
	CTransformable::CTransformable():
		m_bMatrixValid{ true },
		m_bTranslateMatrixValid{ true },
		m_bRotateMatrixValid{ true },
		m_bScaleMatrixValid{ true },
		m_bRotateXMatrixValid{ true },
		m_bRotateYMatrixValid{ true },
		m_bRotateZMatrixValid{ true },
		m_bInverseMatrixValid{ true },
		m_sMatrix{ 1, 0 },
		m_sTranslateMatrix{ 1, 0 },
		m_sRotateMatrix{ 1, 0 },
		m_sScaleMatrix{ 1, 0 },
		m_sRotateXMatrix{ 1, 0 },
		m_sRotateYMatrix{ 1, 0 },
		m_sRotateZMatrix{ 1, 0 },
		m_sInverseMatrix{ 1, 0 },
		m_bTransformChanged{ true }
	{
		m_sTransform.Translation = Vec3f{ 0, 0, 0 };
		m_sTransform.Scaling = Vec3f{ 1, 1, 1 };
		m_sTransform.Rotation = Vec3f{ 0, 0, 0 };
		m_sTransform.TransformOrder = TransformOrder::TRS;
		m_sTransform.RotateOrder = RotateOrder::XYZ;
	}
#pragma endregion

#pragma region ITransformable getters
	bool CTransformable::hasTranslation(const float relative_tolerance) const
	{
		return ntl::NotEquals<float>(m_sTransform.Translation, Vec3f{ 0, 0, 0 }, relative_tolerance);
	}

	bool CTransformable::hasRotation(const float relative_tolerance) const
	{
		return ntl::NotEquals<float>(m_sTransform.Rotation, Vec3f{ 0, 0, 0 }, relative_tolerance);
	}

	bool CTransformable::hasScaling(const float relative_tolerance) const
	{
		return ntl::NotEquals<float>(m_sTransform.Scaling, Vec3f{ 1, 1, 1 }, relative_tolerance);
	}

	const Mat4f &CTransformable::getMatrix()
	{
		UpdateMatrix();
		return m_sMatrix;
	}

	const Mat4f &CTransformable::getTranslateMatrix()
	{
		UpdateTranslateMatrix();
		return m_sTranslateMatrix;
	}

	const Mat4f &CTransformable::getScaleMatrix()
	{
		UpdateScaleMatrix();
		return m_sScaleMatrix;
	}

	const Mat4f &CTransformable::getRotateMaterix()
	{
		UpdateRotateMatrix();
		return m_sRotateMatrix;
	}

	const Mat4f &CTransformable::getRotateXMatrix()
	{
		UpdateRotateXMatrix();
		return m_sRotateXMatrix;
	}

	const Mat4f &CTransformable::getRotateYMatrix()
	{
		UpdateRotateYMatrix();
		return m_sRotateYMatrix;
	}

	const Mat4f &CTransformable::getRotateZMatrix()
	{
		UpdateRotateZMatrix();
		return m_sRotateZMatrix;
	}

	const Mat4f &CTransformable::getInverseMatrix()
	{
		UpdateInverseMatrix();
		return m_sInverseMatrix;
	}
#pragma endregion

#pragma region ITransformable setters
	bool CTransformable::setRotateOrder(const nitisa::RotateOrder value)
	{
		if (value != m_sTransform.RotateOrder)
		{
			m_sTransform.RotateOrder = value;
			m_bRotateMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
			m_bTransformChanged = true;
			return true;
		}
		return false;
	}

	bool CTransformable::setTransformOrder(const nitisa::TransformOrder value)
	{
		if (value != m_sTransform.TransformOrder)
		{
			m_sTransform.TransformOrder = value;
			m_bInverseMatrixValid = m_bMatrixValid = false;
			m_bTransformChanged = true;
			return true;
		}
		return false;
	}

	bool CTransformable::setTx(const float value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sTransform.Translation.X, relative_tolerance))
		{
			m_sTransform.Translation.X = value;
			m_bTranslateMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
			m_bTransformChanged = true;
			return true;
		}
		return false;
	}

	bool CTransformable::setTy(const float value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sTransform.Translation.Y, relative_tolerance))
		{
			m_sTransform.Translation.Y = value;
			m_bTranslateMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
			m_bTransformChanged = true;
			return true;
		}
		return false;
	}

	bool CTransformable::setTz(const float value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sTransform.Translation.Z, relative_tolerance))
		{
			m_sTransform.Translation.Z = value;
			m_bTranslateMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
			m_bTransformChanged = true;
			return true;
		}
		return false;
	}

	bool CTransformable::setRx(const float value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sTransform.Rotation.X, relative_tolerance))
		{
			m_sTransform.Rotation.X = value;
			m_bRotateXMatrixValid = m_bRotateMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
			m_bTransformChanged = true;
			return true;
		}
		return false;
	}

	bool CTransformable::setRy(const float value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sTransform.Rotation.Y, relative_tolerance))
		{
			m_sTransform.Rotation.Y = value;
			m_bRotateYMatrixValid = m_bRotateMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
			m_bTransformChanged = true;
			return true;
		}
		return false;
	}

	bool CTransformable::setRz(const float value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sTransform.Rotation.Z, relative_tolerance))
		{
			m_sTransform.Rotation.Z = value;
			m_bRotateZMatrixValid = m_bRotateMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
			m_bTransformChanged = true;
			return true;
		}
		return false;
	}

	bool CTransformable::setSx(const float value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sTransform.Scaling.X, relative_tolerance))
		{
			m_sTransform.Scaling.X = value;
			m_bScaleMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
			m_bTransformChanged = true;
			return true;
		}
		return false;
	}

	bool CTransformable::setSy(const float value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sTransform.Scaling.Y, relative_tolerance))
		{
			m_sTransform.Scaling.Y = value;
			m_bScaleMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
			m_bTransformChanged = true;
			return true;
		}
		return false;
	}

	bool CTransformable::setSz(const float value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sTransform.Scaling.Z, relative_tolerance))
		{
			m_sTransform.Scaling.Z = value;
			m_bScaleMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
			m_bTransformChanged = true;
			return true;
		}
		return false;
	}

	bool CTransformable::setTranslation(const Vec3f &value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sTransform.Translation, relative_tolerance))
		{
			m_sTransform.Translation = value;
			m_bTranslateMatrixValid = m_bMatrixValid = m_bInverseMatrixValid = false;
			m_bTransformChanged = true;
			return true;
		}
		return false;
	}

	bool CTransformable::setRotation(const Vec3f &value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sTransform.Rotation, relative_tolerance))
		{
			m_sTransform.Rotation = value;
			m_bRotateXMatrixValid = m_bRotateYMatrixValid = m_bRotateZMatrixValid = m_bRotateMatrixValid = m_bMatrixValid = m_bInverseMatrixValid = false;
			m_bTransformChanged = true;
			return true;
		}
		return false;
	}

	bool CTransformable::setScaling(const Vec3f &value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sTransform.Scaling, relative_tolerance))
		{
			m_sTransform.Scaling = value;
			m_bScaleMatrixValid = m_bMatrixValid = m_bInverseMatrixValid = false;
			m_bTransformChanged = true;
			return true;
		}
		return false;
	}

	bool CTransformable::setTransform(const nitisa::Transform &value, const float relative_tolerance)
	{
		if (NotEquals(value, m_sTransform))
		{
			m_sTransform = value;
			m_bMatrixValid = m_bInverseMatrixValid = m_bTranslateMatrixValid = m_bScaleMatrixValid = m_bRotateMatrixValid = m_bRotateXMatrixValid = m_bRotateYMatrixValid = m_bRotateZMatrixValid = false;
			m_bTransformChanged = true;
			return true;
		}
		return false;
	}

	ITransformable *CTransformable::setOrder(const nitisa::RotateOrder value)
	{
		m_sTransform.RotateOrder = value;
		m_bRotateMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
		m_bTransformChanged = true;
		return this;
	}

	ITransformable *CTransformable::setOrder(const nitisa::TransformOrder value)
	{
		m_sTransform.TransformOrder = value;
		m_bInverseMatrixValid = m_bMatrixValid = false;
		m_bTransformChanged = true;
		return this;
	}

	ITransformable *CTransformable::setTx(const float value)
	{
		m_sTransform.Translation.X = value;
		m_bTranslateMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
		m_bTransformChanged = true;
		return this;
	}

	ITransformable *CTransformable::setTy(const float value)
	{
		m_sTransform.Translation.Y = value;
		m_bTranslateMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
		m_bTransformChanged = true;
		return this;
	}

	ITransformable *CTransformable::setTz(const float value)
	{
		m_sTransform.Translation.Z = value;
		m_bTranslateMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
		m_bTransformChanged = true;
		return this;
	}

	ITransformable *CTransformable::setRx(const float value)
	{
		m_sTransform.Rotation.X = value;
		m_bRotateXMatrixValid = m_bRotateMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
		m_bTransformChanged = true;
		return this;
	}

	ITransformable *CTransformable::setRy(const float value)
	{
		m_sTransform.Rotation.Y = value;
		m_bRotateYMatrixValid = m_bRotateMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
		m_bTransformChanged = true;
		return this;
	}

	ITransformable *CTransformable::setRz(const float value)
	{
		m_sTransform.Rotation.Z = value;
		m_bRotateZMatrixValid = m_bRotateMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
		m_bTransformChanged = true;
		return this;
	}

	ITransformable *CTransformable::setSx(const float value)
	{
		m_sTransform.Scaling.X = value;
		m_bScaleMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
		m_bTransformChanged = true;
		return this;
	}

	ITransformable *CTransformable::setSy(const float value)
	{
		m_sTransform.Scaling.Y = value;
		m_bScaleMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
		m_bTransformChanged = true;
		return this;
	}

	ITransformable *CTransformable::setSz(const float value)
	{
		m_sTransform.Scaling.Z = value;
		m_bScaleMatrixValid = m_bInverseMatrixValid = m_bMatrixValid = false;
		m_bTransformChanged = true;
		return this;
	}

	ITransformable *CTransformable::setTranslation(const Vec3f &value)
	{
		m_sTransform.Translation = value;
		m_bTranslateMatrixValid = m_bMatrixValid = m_bInverseMatrixValid = false;
		m_bTransformChanged = true;
		return this;
	}

	ITransformable *CTransformable::setRotation(const Vec3f &value)
	{
		m_sTransform.Rotation = value;
		m_bRotateXMatrixValid = m_bRotateYMatrixValid = m_bRotateZMatrixValid = m_bRotateMatrixValid = m_bMatrixValid = m_bInverseMatrixValid = false;
		m_bTransformChanged = true;
		return this;
	}

	ITransformable *CTransformable::setScaling(const Vec3f &value)
	{
		m_sTransform.Scaling = value;
		m_bScaleMatrixValid = m_bMatrixValid = m_bInverseMatrixValid = false;
		m_bTransformChanged = true;
		return this;
	}

	ITransformable *CTransformable::setTransform(const nitisa::Transform &value)
	{
		m_sTransform = value;
		m_bMatrixValid = m_bInverseMatrixValid = m_bTranslateMatrixValid = m_bScaleMatrixValid = m_bRotateMatrixValid = m_bRotateXMatrixValid = m_bRotateYMatrixValid = m_bRotateZMatrixValid = false;
		m_bTransformChanged = true;
		return this;
	}
#pragma endregion

#pragma region Helpers
	void CTransformable::UpdateMatrix()
	{
		if (!m_bMatrixValid)
		{
			UpdateTranslateMatrix();
			UpdateRotateMatrix();
			UpdateScaleMatrix();
			switch (m_sTransform.TransformOrder)
			{
			case TransformOrder::TRS:
				m_sMatrix = m_sTranslateMatrix * m_sRotateMatrix * m_sScaleMatrix;
				break;
			case TransformOrder::TSR:
				m_sMatrix = m_sTranslateMatrix * m_sScaleMatrix * m_sRotateMatrix;
				break;
			case TransformOrder::RTS:
				m_sMatrix = m_sRotateMatrix * m_sTranslateMatrix * m_sScaleMatrix;
				break;
			case TransformOrder::RST:
				m_sMatrix = m_sRotateMatrix * m_sScaleMatrix * m_sTranslateMatrix;
				break;
			case TransformOrder::STR:
				m_sMatrix = m_sScaleMatrix * m_sTranslateMatrix * m_sRotateMatrix;
				break;
			case TransformOrder::SRT:
				m_sMatrix = m_sScaleMatrix * m_sRotateMatrix * m_sTranslateMatrix;
				break;
			}
			m_bMatrixValid = true;
		}
	}

	void CTransformable::UpdateTranslateMatrix()
	{
		if (!m_bTranslateMatrixValid)
		{
			ntl::Translate<float>(m_sTranslateMatrix, m_sTransform.Translation.X, m_sTransform.Translation.Y, m_sTransform.Translation.Z);
			m_bTranslateMatrixValid = true;
		}
	}

	void CTransformable::UpdateRotateMatrix()
	{
		if (!m_bRotateMatrixValid)
		{
			UpdateRotateXMatrix();
			UpdateRotateYMatrix();
			UpdateRotateZMatrix();
			switch (m_sTransform.RotateOrder)
			{
			case RotateOrder::XYZ:
				m_sRotateMatrix = m_sRotateXMatrix * m_sRotateYMatrix * m_sRotateZMatrix;
				break;
			case RotateOrder::XZY:
				m_sRotateMatrix = m_sRotateXMatrix * m_sRotateZMatrix * m_sRotateYMatrix;
				break;
			case RotateOrder::YXZ:
				m_sRotateMatrix = m_sRotateYMatrix * m_sRotateXMatrix * m_sRotateZMatrix;
				break;
			case RotateOrder::YZX:
				m_sRotateMatrix = m_sRotateYMatrix * m_sRotateZMatrix * m_sRotateXMatrix;
				break;
			case RotateOrder::ZXY:
				m_sRotateMatrix = m_sRotateZMatrix * m_sRotateXMatrix * m_sRotateYMatrix;
				break;
			case RotateOrder::ZYX:
				m_sRotateMatrix = m_sRotateZMatrix * m_sRotateYMatrix * m_sRotateXMatrix;
				break;
			}
			m_bRotateMatrixValid = true;
		}
	}

	void CTransformable::UpdateScaleMatrix()
	{
		if (!m_bScaleMatrixValid)
		{
			ntl::Scale<float>(m_sScaleMatrix, m_sTransform.Scaling.X, m_sTransform.Scaling.Y, m_sTransform.Scaling.Z);
			m_bScaleMatrixValid = true;
		}
	}

	void CTransformable::UpdateRotateXMatrix()
	{
		if (!m_bRotateXMatrixValid)
		{
			ntl::RotateX<float>(m_sRotateXMatrix, m_sTransform.Rotation.X);
			m_bRotateXMatrixValid = true;
		}
	}

	void CTransformable::UpdateRotateYMatrix()
	{
		if (!m_bRotateYMatrixValid)
		{
			ntl::RotateY<float>(m_sRotateYMatrix, m_sTransform.Rotation.Y);
			m_bRotateYMatrixValid = true;
		}
	}

	void CTransformable::UpdateRotateZMatrix()
	{
		if (!m_bRotateZMatrixValid)
		{
			ntl::RotateZ<float>(m_sRotateZMatrix, m_sTransform.Rotation.Z);
			m_bRotateZMatrixValid = true;
		}
	}

	void CTransformable::UpdateInverseMatrix()
	{
		if (!m_bInverseMatrixValid)
		{
			UpdateMatrix();
			m_sInverseMatrix = ntl::Inversed<float>(m_sMatrix);
			m_bInverseMatrixValid = true;
		}
	}
#pragma endregion
}