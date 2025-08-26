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
	CCamera::CCamera() :
		CReleasable(),
		m_bProjectionMatrixValid{ false },
		m_bViewMatrixValid{ false },
		m_bMatrixValid{ false },
		m_bRotationValid{ true }
	{
		m_bPositionChanged = true;
		m_bMatrixChanged = true;
		m_eProjectionMode = ProjectionMode::Perspective;
		m_eRotateOrder = RotateOrder::YXZ;
		m_sPosition = Vec3f{ -50, 25, 50 };
		m_sRotation = Vec3f{ 0, 0, 0 };
		m_sViewport = RectF{ -1, 1, 1, -1 };
		m_fFOV = ntl::DegToRad<float>(45);
		m_fAspect = 16.0f / 9;
		m_sPlanes = Vec2f{ 0.001f, 1000 };
		m_sTargetDirection = Quaternion{ 0, 0, -1, 1 };
		m_sUpDirection = Quaternion{ 0, 1, 0, 1 };
		m_sRightDirection = Quaternion{ 1, 0, 0, 1 };
		m_sPitchLimits = Vec2f{ 1, -1 };
		m_sYawLimits = Vec2f{ 1, -1 };
		m_sRollLimits = Vec2f{ 1, -1 };

		setRotation(Vec3f{ -ntl::DegToRad<float>(15), -ntl::DegToRad<float>(45), 0 });
	}
#pragma endregion

#pragma region ICamera getters
	const Mat4f &CCamera::getProjectionMatrix()
	{
		UpdateProjectionMatrix();
		return m_sProjectionMatrix;
	}

	const Mat4f &CCamera::getViewMatrix()
	{
		UpdateViewMatrix();
		return m_sViewMatrix;
	}

	const Mat4f &CCamera::getMatrix()
	{
		UpdateMatrix();
		return m_sMatrix;
	}

	bool CCamera::hasPitchLimits() const
	{
		return m_sPitchLimits.X > m_sPitchLimits.X;
	}

	bool CCamera::hasYawLimits() const
	{
		return m_sYawLimits.X > m_sYawLimits.X;
	}

	bool CCamera::hasRollLimits() const
	{
		return m_sRollLimits.X > m_sRollLimits.X;
	}
#pragma endregion

#pragma region ICamera setters
	bool CCamera::setProjectionMode(const nitisa::ProjectionMode value)
	{
		if (value != m_eProjectionMode)
		{
			m_eProjectionMode = value;
			m_bProjectionMatrixValid = m_bMatrixValid = false;
			m_bMatrixChanged = true;
			return true;
		}
		return false;
	}

	bool CCamera::setRotateOrder(const nitisa::RotateOrder value)
	{
		if (value != m_eRotateOrder)
		{
			m_eRotateOrder = value;
			if (m_bRotationValid)
			{
				m_bViewMatrixValid = m_bMatrixValid = false;
				m_bMatrixChanged = true;
			}
			return true;
		}
		return false;
	}

	bool CCamera::setPosition(const Vec3f &value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sPosition, relative_tolerance))
		{
			m_sPosition = value;
			m_bViewMatrixValid = m_bMatrixValid = false;
			m_bPositionChanged = m_bMatrixChanged = true;
			return true;
		}
		return false;
	}

	bool CCamera::setX(const float value, const bool add, const float relative_tolerance)
	{
		float v{ add ? (m_sPosition.X + value) : value };
		if (ntl::NotEquals<float>(v, m_sPosition.X, relative_tolerance))
		{
			m_sPosition.X = v;
			m_bViewMatrixValid = m_bMatrixValid = false;
			m_bPositionChanged = m_bMatrixChanged = true;
			return true;
		}
		return false;
	}

	bool CCamera::setY(const float value, const bool add, const float relative_tolerance)
	{
		float v{ add ? (m_sPosition.Y + value) : value };
		if (ntl::NotEquals<float>(v, m_sPosition.Y, relative_tolerance))
		{
			m_sPosition.Y = v;
			m_bViewMatrixValid = m_bMatrixValid = false;
			m_bPositionChanged = m_bMatrixChanged = true;
			return true;
		}
		return false;
	}

	bool CCamera::setZ(const float value, const bool add, const float relative_tolerance)
	{
		float v{ add ? (m_sPosition.Z + value) : value };
		if (ntl::NotEquals<float>(v, m_sPosition.Z, relative_tolerance))
		{
			m_sPosition.Z = v;
			m_bViewMatrixValid = m_bMatrixValid = false;
			m_bPositionChanged = m_bMatrixChanged = true;
			return true;
		}
		return false;
	}

	bool CCamera::setRotation(const Vec3f &value, const float relative_tolerance)
	{
		Vec3f v{ value };
		if (m_sPitchLimits.Y > m_sPitchLimits.X)
			v.X = ntl::Clamp<float>(v.X, m_sPitchLimits.X, m_sPitchLimits.Y);
		if (m_sYawLimits.Y > m_sYawLimits.X)
			v.Y = ntl::Clamp<float>(v.Y, m_sYawLimits.X, m_sYawLimits.Y);
		if (m_sRollLimits.Y > m_sRollLimits.X)
			v.Z = ntl::Clamp<float>(v.Z, m_sRollLimits.X, m_sRollLimits.Y);
		if (!m_bRotationValid || ntl::NotEquals<float>(v, m_sRotation, relative_tolerance))
		{
			m_sRotation = v;
			m_sTargetDirection = Quaternion{ 0, 0, -1, 1 };
			m_sUpDirection = Quaternion{ 0, 1, 0, 1 };
			m_sRightDirection = Quaternion{ 1, 0, 0, 1 };
			switch (m_eRotateOrder)
			{
			case RotateOrder::XYZ:
				RotateDirections(m_sRightDirection, m_sRotation.X);
				RotateDirections(m_sUpDirection, m_sRotation.Y);
				RotateDirections(m_sTargetDirection, m_sRotation.Z);
				break;
			case RotateOrder::XZY:
				RotateDirections(m_sRightDirection, m_sRotation.X);
				RotateDirections(m_sTargetDirection, m_sRotation.Z);
				RotateDirections(m_sUpDirection, m_sRotation.Y);
				break;
			case RotateOrder::YXZ:
				RotateDirections(m_sUpDirection, m_sRotation.Y);
				RotateDirections(m_sRightDirection, m_sRotation.X);
				RotateDirections(m_sTargetDirection, m_sRotation.Z);
				break;
			case RotateOrder::YZX:
				RotateDirections(m_sUpDirection, m_sRotation.Y);
				RotateDirections(m_sTargetDirection, m_sRotation.Z);
				RotateDirections(m_sRightDirection, m_sRotation.X);
				break;
			case RotateOrder::ZXY:
				RotateDirections(m_sTargetDirection, m_sRotation.Z);
				RotateDirections(m_sRightDirection, m_sRotation.X);
				RotateDirections(m_sUpDirection, m_sRotation.Y);
				break;
			case RotateOrder::ZYX:
				RotateDirections(m_sTargetDirection, m_sRotation.Z);
				RotateDirections(m_sUpDirection, m_sRotation.Y);
				RotateDirections(m_sRightDirection, m_sRotation.X);
				break;
			}
			m_bRotationValid = true;
			m_bViewMatrixValid = m_bMatrixValid = false;
			m_bMatrixChanged = true;
			return true;
		}
		return false;
	}

	bool CCamera::setPitch(const float value, const bool add, const float relative_tolerance)
	{
		return setRotation(Vec3f{ add ? (m_sRotation.X + value) : value, m_sRotation.Y, m_sRotation.Z }, relative_tolerance);
	}

	bool CCamera::setYaw(const float value, const bool add, const float relative_tolerance)
	{
		return setRotation(Vec3f{ m_sRotation.X, add ? (m_sRotation.Y + value) : value, m_sRotation.Z }, relative_tolerance);
	}

	bool CCamera::setRoll(const float value, const bool add, const float relative_tolerance)
	{
		return setRotation(Vec3f{ m_sRotation.X, m_sRotation.Y, add ? (m_sRotation.Z + value) : value }, relative_tolerance);
	}

	bool CCamera::setViewport(const RectF &value, const float relative_tolerance)
	{
		if (NotEquals(value, m_sViewport, relative_tolerance) &&
			ntl::Less<float>(value.Left, value.Right, relative_tolerance) &&
			ntl::Less<float>(value.Bottom, value.Top, relative_tolerance))
		{
			m_sViewport = value;
			if (m_eProjectionMode != ProjectionMode::Perspective)
			{
				m_bProjectionMatrixValid = m_bMatrixValid = false;
				m_bMatrixChanged = true;
			}
			return true;
		}
		return false;
	}

	bool CCamera::setFOV(const float value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_fFOV, relative_tolerance) && ntl::Greater<float>(value, 0, relative_tolerance) && ntl::Less<float>(value, ntl::Pi<float>, relative_tolerance))
		{
			m_fFOV = value;
			if (m_eProjectionMode == ProjectionMode::Perspective)
			{
				m_bProjectionMatrixValid = m_bMatrixValid = false;
				m_bMatrixChanged = true;
			}
			return true;
		}
		return false;
	}

	bool CCamera::setAspect(const float value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_fAspect, relative_tolerance) && ntl::Greater<float>(value, 0, relative_tolerance))
		{
			m_fAspect = value;
			if (m_eProjectionMode == ProjectionMode::Perspective)
			{
				m_bProjectionMatrixValid = m_bMatrixValid = false;
				m_bMatrixChanged = true;
			}
			return true;
		}
		return false;
	}

	bool CCamera::setPlanes(const Vec2f &value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sPlanes, relative_tolerance) && ntl::Greater<float>(value.Y, value.X, relative_tolerance))
		{
			m_sPlanes = value;
			m_bProjectionMatrixValid = m_bMatrixValid = false;
			m_bMatrixChanged = true;
			return true;
		}
		return false;
	}

	bool CCamera::setNearPlane(const float value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sPlanes.X, relative_tolerance) && ntl::Less<float>(value, m_sPlanes.Y, relative_tolerance))
		{
			m_sPlanes.X = value;
			m_bProjectionMatrixValid = m_bMatrixValid = false;
			m_bMatrixChanged = true;
			return true;
		}
		return false;
	}

	bool CCamera::setFarPlane(const float value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sPlanes.Y, relative_tolerance) && ntl::Greater<float>(value, m_sPlanes.X, relative_tolerance))
		{
			m_sPlanes.Y = value;
			m_bProjectionMatrixValid = m_bMatrixValid = false;
			m_bMatrixChanged = true;
			return true;
		}
		return false;
	}

	bool CCamera::setPitchLimits(const Vec2f &value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sPitchLimits, relative_tolerance))
		{
			m_sPitchLimits = value;
			if (m_sPitchLimits.Y > m_sPitchLimits.X)
				setPitch(m_sRotation.X, false, relative_tolerance);
			return true;
		}
		return false;
	}

	bool CCamera::setYawLimits(const Vec2f &value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sYawLimits, relative_tolerance))
		{
			m_sYawLimits = value;
			if (m_sYawLimits.Y > m_sYawLimits.X)
				setYaw(m_sRotation.Y, false, relative_tolerance);
			return true;
		}
		return false;
	}

	bool CCamera::setRollLimits(const Vec2f &value, const float relative_tolerance)
	{
		if (ntl::NotEquals<float>(value, m_sRollLimits, relative_tolerance))
		{
			m_sRollLimits = value;
			if (m_sRollLimits.Y > m_sRollLimits.X)
				setRoll(m_sRotation.Z, false, relative_tolerance);
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region ICamera moving
	void CCamera::MoveForward(const float delta)
	{
		m_sPosition += delta * m_sTargetDirection.V3;
		m_bViewMatrixValid = m_bMatrixValid = false;
		m_bPositionChanged = m_bMatrixChanged = true;
	}

	void CCamera::MoveBackward(const float delta)
	{
		m_sPosition -= delta * m_sTargetDirection.V3;
		m_bViewMatrixValid = m_bMatrixValid = false;
		m_bPositionChanged = m_bMatrixChanged = true;
	}

	void CCamera::MoveLeft(const float delta)
	{
		m_sPosition -= delta * m_sRightDirection.V3;
		m_bViewMatrixValid = m_bMatrixValid = false;
		m_bPositionChanged = m_bMatrixChanged = true;
	}

	void CCamera::MoveRight(const float delta)
	{
		m_sPosition += delta * m_sRightDirection.V3;
		m_bViewMatrixValid = m_bMatrixValid = false;
		m_bPositionChanged = m_bMatrixChanged = true;
	}

	void CCamera::MoveUp(const float delta)
	{
		m_sPosition += delta * m_sUpDirection.V3;
		m_bViewMatrixValid = m_bMatrixValid = false;
		m_bPositionChanged = m_bMatrixChanged = true;
	}

	void CCamera::MoveDown(const float delta)
	{
		m_sPosition -= delta * m_sUpDirection.V3;
		m_bViewMatrixValid = m_bMatrixValid = false;
		m_bPositionChanged = m_bMatrixChanged = true;
	}
#pragma endregion

#pragma region ICamera rotation
	void CCamera::TurnUp(const float delta)
	{
		RotateDirections(m_sRightDirection, delta);
		m_bRotationValid = false;
		m_bViewMatrixValid = m_bMatrixValid = false;
		m_bMatrixChanged = true;
	}

	void CCamera::TurnDown(const float delta)
	{
		RotateDirections(m_sRightDirection, -delta);
		m_bRotationValid = false;
		m_bViewMatrixValid = m_bMatrixValid = false;
		m_bMatrixChanged = true;
	}

	void CCamera::TurnLeft(const float delta)
	{
		RotateDirections(m_sUpDirection, delta);
		m_bRotationValid = false;
		m_bViewMatrixValid = m_bMatrixValid = false;
		m_bMatrixChanged = true;
	}

	void CCamera::TurnRight(const float delta)
	{
		RotateDirections(m_sUpDirection, -delta);
		m_bRotationValid = false;
		m_bViewMatrixValid = m_bMatrixValid = false;
		m_bMatrixChanged = true;
	}

	void CCamera::TiltLeft(const float delta)
	{
		RotateDirections(m_sTargetDirection, delta);
		m_bRotationValid = false;
		m_bViewMatrixValid = m_bMatrixValid = false;
		m_bMatrixChanged = true;
	}

	void CCamera::TiltRight(const float delta)
	{
		RotateDirections(m_sTargetDirection, -delta);
		m_bRotationValid = false;
		m_bViewMatrixValid = m_bMatrixValid = false;
		m_bMatrixChanged = true;
	}
#pragma endregion

#pragma region Helpers
	void CCamera::UpdateProjectionMatrix()
	{
		if (!m_bProjectionMatrixValid)
		{
			switch (m_eProjectionMode)
			{
			case ProjectionMode::Orthographic:
				ntl::Ortho<float>(m_sProjectionMatrix, m_sViewport.Left, m_sViewport.Top, m_sViewport.Right, m_sViewport.Bottom, m_sPlanes.X, m_sPlanes.Y);
				break;
			case ProjectionMode::Perspective:
				ntl::Perspective<float>(m_sProjectionMatrix, m_fFOV, m_fAspect, m_sPlanes.X, m_sPlanes.Y);
				break;
			}
			m_bProjectionMatrixValid = true;
		}
	}

	void CCamera::UpdateViewMatrix()
	{
		if (!m_bViewMatrixValid)
		{
			ntl::LookAt<float>(m_sViewMatrix, m_sPosition, m_sTargetDirection.V3, m_sUpDirection.V3);
			m_bViewMatrixValid = true;
		}
	}

	void CCamera::UpdateMatrix()
	{
		if (!m_bMatrixValid)
		{
			UpdateProjectionMatrix();
			UpdateViewMatrix();
			m_sMatrix = m_sProjectionMatrix * m_sViewMatrix;
			m_bMatrixValid = true;
		}
	}

	void CCamera::RotateDirections(const Quaternion &axis, const float angle)
	{
		m_sTargetDirection = ntl::Rotate<float>(m_sTargetDirection, axis, angle);
		m_sUpDirection = ntl::Rotate<float>(m_sUpDirection, axis, angle);
		m_sRightDirection = ntl::Rotate<float>(m_sRightDirection, axis, angle);
		ntl::Normalize<float>(m_sTargetDirection.V3);
		ntl::Normalize<float>(m_sUpDirection.V3);
		ntl::Normalize<float>(m_sRightDirection.V3);
		m_sTargetDirection.W = 1;
		m_sUpDirection.W = 1;
		m_sRightDirection.W = 1;
	}
#pragma endregion
}