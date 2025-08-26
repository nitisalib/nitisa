// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Consts.h"
#include "../Interfaces/ICamera.h"
#include "../Math/Mat4f.h"
#include "../Math/Quaternion.h"
#include "../Math/RectF.h"
#include "../Math/Vec2f.h"
#include "../Math/Vec3f.h"
#include "ProjectionMode.h"
#include "Releasable.h"
#include "RotateOrder.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class CCamera : public virtual ICamera, public CReleasable
	{
	private:
		bool m_bProjectionMatrixValid;
		bool m_bViewMatrixValid;
		bool m_bMatrixValid;
		bool m_bRotationValid;
		Mat4f m_sProjectionMatrix;
		Mat4f m_sViewMatrix;
		Mat4f m_sMatrix;

		void UpdateProjectionMatrix();
		void UpdateViewMatrix();
		void UpdateMatrix();
		void RotateDirections(const Quaternion &axis, const float angle);
	public:
		// ICamera getters
		const Mat4f &getProjectionMatrix() override;
		const Mat4f &getViewMatrix() override;
		const Mat4f &getMatrix() override;
		bool hasPitchLimits() const override;
		bool hasYawLimits() const override;
		bool hasRollLimits() const override;

		// ICamera setters
		bool setProjectionMode(const nitisa::ProjectionMode value) override;
		bool setRotateOrder(const nitisa::RotateOrder value) override;
		bool setPosition(const Vec3f &value, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
		bool setX(const float value, const bool add = false, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
		bool setY(const float value, const bool add = false, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
		bool setZ(const float value, const bool add = false, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
		bool setRotation(const Vec3f &value, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
		bool setPitch(const float value, const bool add = false, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
		bool setYaw(const float value, const bool add = false, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
		bool setRoll(const float value, const bool add = false, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
		bool setViewport(const RectF &value, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
		bool setFOV(const float value, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
		bool setAspect(const float value, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
		bool setPlanes(const Vec2f &value, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
		bool setNearPlane(const float value, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
		bool setFarPlane(const float value, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
		bool setPitchLimits(const Vec2f &value, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
		bool setYawLimits(const Vec2f &value, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
		bool setRollLimits(const Vec2f &value, const float relative_tolerance = ntl::RelativeTolerance<float>) override;

		// ICamera moving
		void MoveForward(const float delta) override;
		void MoveBackward(const float delta) override;
		void MoveLeft(const float delta) override;
		void MoveRight(const float delta) override;
		void MoveUp(const float delta) override;
		void MoveDown(const float delta) override;

		// ICamera rotating
		void TurnUp(const float delta) override;
		void TurnDown(const float delta) override;
		void TurnLeft(const float delta) override;
		void TurnRight(const float delta) override;
		void TiltLeft(const float delta) override;
		void TiltRight(const float delta) override;

		CCamera();
	};
}