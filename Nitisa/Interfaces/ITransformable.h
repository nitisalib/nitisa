// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Consts.h"
#include "../Core/RotateOrder.h"
#include "../Core/TransformOrder.h"
#include "../Math/Mat4f.h"
#include "../Math/Transform.h"
#include "../Math/Vec3f.h"

namespace nitisa
{
	class ITransformable
	{
	protected:
		ITransformable() = default;
		~ITransformable() = default;
		ITransformable(const ITransformable &other) = delete;
		ITransformable(ITransformable &&other) = delete;
		ITransformable &operator=(const ITransformable &other) = delete;
		ITransformable &operator=(ITransformable &&other) = delete;
	protected:
		nitisa::Transform m_sTransform;
	public:
		// Properties
		float const &Tx{ m_sTransform.Tx };
		float const &Ty{ m_sTransform.Ty };
		float const &Tz{ m_sTransform.Tz };
		float const &Rx{ m_sTransform.Rx };
		float const &Ry{ m_sTransform.Ry };
		float const &Rz{ m_sTransform.Rz };
		float const &Sx{ m_sTransform.Sx };
		float const &Sy{ m_sTransform.Sy };
		float const &Sz{ m_sTransform.Sz };
		Vec3f const &Translation{ m_sTransform.Translation };
		Vec3f const &Rotation{ m_sTransform.Rotation };
		Vec3f const &Scaling{ m_sTransform.Scaling };
		nitisa::TransformOrder const &TransformOrder{ m_sTransform.TransformOrder };
		nitisa::RotateOrder const &RotateOrder{ m_sTransform.RotateOrder };
		nitisa::Transform const &Transform{ m_sTransform };

		// Getters
		virtual bool hasTranslation(const float relative_tolerance = ntl::RelativeTolerance<float>) const = 0;
		virtual bool hasRotation(const float relative_tolerance = ntl::RelativeTolerance<float>) const = 0;
		virtual bool hasScaling(const float relative_tolerance = ntl::RelativeTolerance<float>) const = 0;
		virtual const Mat4f &getMatrix() = 0;
		virtual const Mat4f &getTranslateMatrix() = 0;
		virtual const Mat4f &getScaleMatrix() = 0;
		virtual const Mat4f &getRotateMaterix() = 0;
		virtual const Mat4f &getRotateXMatrix() = 0;
		virtual const Mat4f &getRotateYMatrix() = 0;
		virtual const Mat4f &getRotateZMatrix() = 0;
		virtual const Mat4f &getInverseMatrix() = 0;

		// Setters
		virtual bool setRotateOrder(const nitisa::RotateOrder value) = 0;
		virtual bool setTransformOrder(const nitisa::TransformOrder value) = 0;
		virtual bool setTx(const float value, const float relative_tolerance) = 0;
		virtual bool setTy(const float value, const float relative_tolerance) = 0;
		virtual bool setTz(const float value, const float relative_tolerance) = 0;
		virtual bool setRx(const float value, const float relative_tolerance) = 0;
		virtual bool setRy(const float value, const float relative_tolerance) = 0;
		virtual bool setRz(const float value, const float relative_tolerance) = 0;
		virtual bool setSx(const float value, const float relative_tolerance) = 0;
		virtual bool setSy(const float value, const float relative_tolerance) = 0;
		virtual bool setSz(const float value, const float relative_tolerance) = 0;
		virtual bool setTranslation(const Vec3f &value, const float relative_tolerance) = 0;
		virtual bool setRotation(const Vec3f &value, const float relative_tolerance) = 0;
		virtual bool setScaling(const Vec3f &value, const float relative_tolerance) = 0;
		virtual bool setTransform(const nitisa::Transform &value, const float relative_tolerance) = 0;

		// Absolute setters
		virtual ITransformable *setOrder(const nitisa::RotateOrder value) = 0;
		virtual ITransformable *setOrder(const nitisa::TransformOrder value) = 0;
		virtual ITransformable *setTx(const float value) = 0;
		virtual ITransformable *setTy(const float value) = 0;
		virtual ITransformable *setTz(const float value) = 0;
		virtual ITransformable *setRx(const float value) = 0;
		virtual ITransformable *setRy(const float value) = 0;
		virtual ITransformable *setRz(const float value) = 0;
		virtual ITransformable *setSx(const float value) = 0;
		virtual ITransformable *setSy(const float value) = 0;
		virtual ITransformable *setSz(const float value) = 0;
		virtual ITransformable *setTranslation(const Vec3f &value) = 0;
		virtual ITransformable *setRotation(const Vec3f &value) = 0;
		virtual ITransformable *setScaling(const Vec3f &value) = 0;
		virtual ITransformable *setTransform(const nitisa::Transform &value) = 0;
	};
}