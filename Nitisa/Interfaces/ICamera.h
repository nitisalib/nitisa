// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Consts.h"
#include "../Core/ProjectionMode.h"
#include "../Core/RotateOrder.h"
#include "../Math/Mat4f.h"
#include "../Math/Quaternion.h"
#include "../Math/RectF.h"
#include "../Math/Vec2f.h"
#include "../Math/Vec3f.h"
#include "IReleasable.h"

namespace nitisa
{
	class ICamera : public virtual IReleasable
	{
	protected:
		ICamera() = default;
		~ICamera() = default;
		ICamera(const ICamera &other) = delete;
		ICamera(ICamera &&other) = delete;
		ICamera &operator=(const ICamera &other) = delete;
		ICamera &operator=(ICamera &&other) = delete;
	protected:
		bool m_bPositionChanged;
		bool m_bMatrixChanged;
		nitisa::ProjectionMode m_eProjectionMode;
		nitisa::RotateOrder m_eRotateOrder;
		Vec3f m_sPosition;
		Vec3f m_sRotation;
		RectF m_sViewport;
		float m_fFOV;
		float m_fAspect;
		Vec2f m_sPlanes;
		Quaternion m_sTargetDirection;
		Quaternion m_sUpDirection;
		Quaternion m_sRightDirection;
		Vec2f m_sPitchLimits;
		Vec2f m_sYawLimits;
		Vec2f m_sRollLimits;
	public:
		bool const &PositionChanged{ m_bPositionChanged };
		bool const &MatrixChanged{ m_bMatrixChanged };
		nitisa::ProjectionMode const &ProjectionMode{ m_eProjectionMode };
		nitisa::RotateOrder const &RotateOrder{ m_eRotateOrder };
		Vec3f const &Position{ m_sPosition };
		float const &X{ m_sPosition.X };
		float const &Y{ m_sPosition.Y };
		float const &Z{ m_sPosition.Z };
		Vec3f const &Rotation{ m_sRotation };
		float const &Pitch{ m_sRotation.X };
		float const &Yaw{ m_sRotation.Y };
		float const &Roll{ m_sRotation.Z };
		RectF const &Viewport{ m_sViewport };
		float const &FOV{ m_fFOV };
		float const &Aspect{ m_fAspect };
		Vec2f const &Planes{ m_sPlanes };
		float const &NearPlane{ m_sPlanes.X };
		float const &FarPlane{ m_sPlanes.Y };
		Vec3f const &TargetDirection{ m_sTargetDirection.V3 };
		Vec3f const &UpDirection{ m_sUpDirection.V3 };
		Vec3f const &RightDirection{ m_sRightDirection.V3 };
		Vec2f const &PitchLimits{ m_sPitchLimits };
		Vec2f const &YawLimits{ m_sYawLimits };
		Vec2f const &RollLimits{ m_sRollLimits };

		virtual const Mat4f &getProjectionMatrix() = 0;
		virtual const Mat4f &getViewMatrix() = 0;
		virtual const Mat4f &getMatrix() = 0;
		virtual bool hasPitchLimits() const = 0;
		virtual bool hasYawLimits() const = 0;
		virtual bool hasRollLimits() const = 0;

		virtual bool setProjectionMode(const nitisa::ProjectionMode value) = 0;
		virtual bool setRotateOrder(const nitisa::RotateOrder value) = 0;
		virtual bool setPosition(const Vec3f &value, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setX(const float value, const bool add = false, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setY(const float value, const bool add = false, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setZ(const float value, const bool add = false, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setRotation(const Vec3f &value, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setPitch(const float value, const bool add = false, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setYaw(const float value, const bool add = false, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setRoll(const float value, const bool add = false, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setViewport(const RectF &value, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setFOV(const float value, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setAspect(const float value, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setPlanes(const Vec2f &value, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setNearPlane(const float value, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setFarPlane(const float value, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setPitchLimits(const Vec2f &value, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0; // X >= Y(usually 1, -1) means no limit
		virtual bool setYawLimits(const Vec2f &value, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setRollLimits(const Vec2f &value, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;

		virtual void MoveForward(const float delta) = 0;
		virtual void MoveBackward(const float delta) = 0;
		virtual void MoveLeft(const float delta) = 0;
		virtual void MoveRight(const float delta) = 0;
		virtual void MoveUp(const float delta) = 0;
		virtual void MoveDown(const float delta) = 0;

		virtual void TurnUp(const float delta) = 0;
		virtual void TurnDown(const float delta) = 0;
		virtual void TurnLeft(const float delta) = 0;
		virtual void TurnRight(const float delta) = 0;
		virtual void TiltLeft(const float delta) = 0;
		virtual void TiltRight(const float delta) = 0;
	};
}