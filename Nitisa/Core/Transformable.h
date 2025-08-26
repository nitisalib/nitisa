// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Consts.h"
#include "../Interfaces/ITransformable.h"
#include "../Math/Mat4f.h"
#include "../Math/Transform.h"
#include "../Math/Vec3f.h"
#include "RotateOrder.h"
#include "TransformOrder.h"

namespace nitisa
{
	class CTransformable :public virtual ITransformable
	{
	private:
		bool m_bMatrixValid;
		bool m_bTranslateMatrixValid;
		bool m_bRotateMatrixValid;
		bool m_bScaleMatrixValid;
		bool m_bRotateXMatrixValid;
		bool m_bRotateYMatrixValid;
		bool m_bRotateZMatrixValid;
		bool m_bInverseMatrixValid;
		Mat4f m_sMatrix;
		Mat4f m_sTranslateMatrix;
		Mat4f m_sRotateMatrix;
		Mat4f m_sScaleMatrix;
		Mat4f m_sRotateXMatrix;
		Mat4f m_sRotateYMatrix;
		Mat4f m_sRotateZMatrix;
		Mat4f m_sInverseMatrix;

		void UpdateMatrix();
		void UpdateTranslateMatrix();
		void UpdateRotateMatrix();
		void UpdateScaleMatrix();
		void UpdateRotateXMatrix();
		void UpdateRotateYMatrix();
		void UpdateRotateZMatrix();
		void UpdateInverseMatrix();
	protected:
		bool m_bTransformChanged;
	public:
		// ITransformable getters
		bool hasTranslation(const float relative_tolerance = ntl::RelativeTolerance<float>) const override;
		bool hasRotation(const float relative_tolerance = ntl::RelativeTolerance<float>) const override;
		bool hasScaling(const float relative_tolerance = ntl::RelativeTolerance<float>) const override;
		const Mat4f &getMatrix() override;
		const Mat4f &getTranslateMatrix() override;
		const Mat4f &getScaleMatrix() override;
		const Mat4f &getRotateMaterix() override;
		const Mat4f &getRotateXMatrix() override;
		const Mat4f &getRotateYMatrix() override;
		const Mat4f &getRotateZMatrix() override;
		const Mat4f &getInverseMatrix() override;

		// ITransformable setters
		bool setRotateOrder(const nitisa::RotateOrder value) override;
		bool setTransformOrder(const nitisa::TransformOrder value) override;
		bool setTx(const float value, const float relative_tolerance) override;
		bool setTy(const float value, const float relative_tolerance) override;
		bool setTz(const float value, const float relative_tolerance) override;
		bool setRx(const float value, const float relative_tolerance) override;
		bool setRy(const float value, const float relative_tolerance) override;
		bool setRz(const float value, const float relative_tolerance) override;
		bool setSx(const float value, const float relative_tolerance) override;
		bool setSy(const float value, const float relative_tolerance) override;
		bool setSz(const float value, const float relative_tolerance) override;
		bool setTranslation(const Vec3f &value, const float relative_tolerance) override;
		bool setRotation(const Vec3f &value, const float relative_tolerance) override;
		bool setScaling(const Vec3f &value, const float relative_tolerance) override;
		bool setTransform(const nitisa::Transform &value, const float relative_tolerance) override;

		ITransformable *setOrder(const nitisa::RotateOrder value) override;
		ITransformable *setOrder(const nitisa::TransformOrder value) override;
		ITransformable *setTx(const float value) override;
		ITransformable *setTy(const float value) override;
		ITransformable *setTz(const float value) override;
		ITransformable *setRx(const float value) override;
		ITransformable *setRy(const float value) override;
		ITransformable *setRz(const float value) override;
		ITransformable *setSx(const float value) override;
		ITransformable *setSy(const float value) override;
		ITransformable *setSz(const float value) override;
		ITransformable *setTranslation(const Vec3f &value) override;
		ITransformable *setRotation(const Vec3f &value) override;
		ITransformable *setScaling(const Vec3f &value) override;
		ITransformable *setTransform(const nitisa::Transform &value) override;

		CTransformable();
	};
}