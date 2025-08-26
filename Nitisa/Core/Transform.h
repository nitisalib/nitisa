// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/ITransform.h"
#include "../Math/Mat4f.h"
#include "../Math/Transform.h"
#include "FeedbackEx.h"
#include "RotateOrder.h"
#include "TransformOrder.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class IFeedbackExListener;
	class ITransformService;

	class CTransformService;

	class CTransform :public virtual ITransform, public CFeedbackEx
	{
		friend CTransformService;
	private:
		Mat4f m_sMatrixTranslate;
		Mat4f m_sMatrixScale;
		Mat4f m_sMatrixRx;
		Mat4f m_sMatrixRy;
		Mat4f m_sMatrixRz;
		Mat4f m_sMatrixRotate;
		Mat4f m_sMatrix;
		Mat4f m_sMatrixInversed;

		bool m_bMatrixTranslate;
		bool m_bMatrixScale;
		bool m_bMatrixRx;
		bool m_bMatrixRy;
		bool m_bMatrixRz;
		bool m_bMatrixRotate;
		bool m_bMatrix;
		bool m_bMatrixInversed;

		ITransformService *m_pService;

		bool FeedbackBefore();
	protected:
		nitisa::Transform m_sTransform;
	public:
		float getTx() const override;
		float getTy() const override;
		float getTz() const override;
		float getSx() const override;
		float getSy() const override;
		float getSz() const override;
		float getRx() const override;
		float getRy() const override;
		float getRz() const override;
		TransformOrder getTransformOrder() const override;
		RotateOrder getRotateOrder() const override;
		const Mat4f &getMatrix() override;
		const Mat4f &getMatrixInversed() override;
		const Mat4f &getMatrixTranslate() override;
		const Mat4f &getMatrixScale() override;
		const Mat4f &getMatrixRotate() override;
		const nitisa::Transform &getTransform() override;
		bool isTranslateIdentity() const override;
		bool isScaleIdentity() const override;
		bool isRotateIdentity() const override;
		bool isIdentity() const override;

		bool setTx(const float value) override;
		bool setTy(const float value) override;
		bool setTz(const float value) override;
		bool setSx(const float value) override;
		bool setSy(const float value) override;
		bool setSz(const float value) override;
		bool setRx(const float value) override;
		bool setRy(const float value) override;
		bool setRz(const float value) override;
		bool setTransformOrder(const TransformOrder value) override;
		bool setRotateOrder(const RotateOrder value) override;
		bool setTransform(const nitisa::Transform &value) override;

		bool Translate(const float tx, const float ty, const float tz) override;
		bool Scale(const float sx, const float sy, const float sz) override;
		bool Rotate(const float rx, const float ry, const float rz) override;
		bool Transform(const float tx, const float ty, const float tz, const float sx, const float sy, const float sz, const float rx, const float ry, const float rz) override;

		ITransformService *QueryService() override;
		void Release() override;

		CTransform(IFeedbackExListener *listener);
		virtual ~CTransform();
	};
}