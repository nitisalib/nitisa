// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/RotateOrder.h"
#include "../Core/TransformOrder.h"
#include "../Math/Mat4f.h"
#include "../Math/Transform.h"
#include "IFeedbackEx.h"
#include "ITransformService.h"

namespace nitisa
{
	class ITransform :public virtual IFeedbackEx
	{
	protected:
		ITransform() = default;
		~ITransform() = default;
		ITransform(const ITransform &other) = delete;
		ITransform(ITransform &&other) = delete;
		ITransform &operator=(const ITransform &other) = delete;
		ITransform &operator=(ITransform &&other) = delete;
	public:
		virtual float getTx() const = 0; // Return X coordinate
		virtual float getTy() const = 0; // Return Y coordinate
		virtual float getTz() const = 0; // Return Z coordinate
		virtual float getSx() const = 0; // Return scaling factor for X axis
		virtual float getSy() const = 0; // Return scaling factor for Y axis
		virtual float getSz() const = 0; // Return scaling factor for Z axis
		virtual float getRx() const = 0; // Return rotation angle around X axis(in radians)
		virtual float getRy() const = 0; // Return rotation angle around Y axis(in radians)
		virtual float getRz() const = 0; // Return rotation angle around Z axis(in radians)
		virtual TransformOrder getTransformOrder() const = 0; // Return transformation order
		virtual RotateOrder getRotateOrder() const = 0; // Return rotation order
		virtual const Mat4f &getMatrix() = 0; // Return final matrix
		virtual const Mat4f &getMatrixInversed() = 0; // Return final inversed matrix
		virtual const Mat4f &getMatrixTranslate() = 0; // Return translation matrix
		virtual const Mat4f &getMatrixScale() = 0; // Return scaling matrix
		virtual const Mat4f &getMatrixRotate() = 0; // Return rotation matrix
		virtual const nitisa::Transform &getTransform() = 0; // Return transformation data
		virtual bool isTranslateIdentity() const = 0; // Check whether there is no translation
		virtual bool isScaleIdentity() const = 0; // Check whether there is no scaling
		virtual bool isRotateIdentity() const = 0; // Check whether there is no rotation
		virtual bool isIdentity() const = 0; // Check whether there is no any transformation at all

		virtual bool setTx(const float value) = 0; // Set X coordinate
		virtual bool setTy(const float value) = 0; // Set Y coordinate
		virtual bool setTz(const float value) = 0; // Set Z coordinate
		virtual bool setSx(const float value) = 0; // Set scaling factor for X axis
		virtual bool setSy(const float value) = 0; // Set scaling factor for Y axis
		virtual bool setSz(const float value) = 0; // Set scaling factor for Z axis
		virtual bool setRx(const float value) = 0; // Set rotation angle around X axis(in radians)
		virtual bool setRy(const float value) = 0; // Set rotation angle around Y axis(in radians)
		virtual bool setRz(const float value) = 0; // Set rotation angle around Z axis(in radians)
		virtual bool setTransformOrder(const TransformOrder value) = 0; // Set transformation order
		virtual bool setRotateOrder(const RotateOrder value) = 0; // Set rotation order
		virtual bool setTransform(const Transform &value) = 0; // Set all transformation data

		virtual ITransformService *QueryService() = 0; // Return service
		virtual bool Translate(const float tx, const float ty, const float tz) = 0; // Translate
		virtual bool Scale(const float sx, const float sy, const float sz) = 0; // Scale
		virtual bool Rotate(const float rx, const float ry, const float rz) = 0; // Rotate(in radians)
		virtual bool Transform(const float tx, const float ty, const float tz, const float sx, const float sy, const float sz, const float rx, const float ry, const float rz) = 0; // Translate, scale, and rotate

		virtual void Release() = 0; // Destroy instance
	};
}