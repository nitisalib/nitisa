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
#include "../Math/Transform.h"

namespace nitisa
{
	class ITransformService
	{
	protected:
		ITransformService() = default;
		~ITransformService() = default;
		ITransformService(const ITransformService &other) = delete;
		ITransformService(ITransformService &&other) = delete;
		ITransformService &operator=(const ITransformService &other) = delete;
		ITransformService &operator=(ITransformService &&other) = delete;
	public:
		virtual bool setTx(const float value) = 0; // Set X coordinate without calling any callbacks
		virtual bool setTy(const float value) = 0; // Set Y coordinate without calling any callbacks
		virtual bool setTz(const float value) = 0; // Set Z coordinate without calling any callbacks
		virtual bool setSx(const float value) = 0; // Set scaling around X axis without calling any callbacks
		virtual bool setSy(const float value) = 0; // Set scaling around Y axis without calling any callbacks
		virtual bool setSz(const float value) = 0; // Set scaling around Z axis without calling any callbacks
		virtual bool setRx(const float value) = 0; // Set rotation around X axis without calling any callbacks
		virtual bool setRy(const float value) = 0; // Set rotation around Y axis without calling any callbacks
		virtual bool setRz(const float value) = 0; // Set rotation around Z axis without calling any callbacks
		virtual bool setTransformOrder(const TransformOrder value) = 0; // Set transformation order without calling any callbacks
		virtual bool setRotateOrder(const RotateOrder value) = 0; // Set rotation order without calling any callbacks
		virtual bool setTransform(const Transform &value) = 0; // Set all transformations without calling any callbacks

		virtual bool Translate(const float tx, const float ty, const float tz) = 0; // Translate without calling any callbacks
		virtual bool Scale(const float sx, const float sy, const float sz) = 0; // Scale without calling any callbacks
		virtual bool Rotate(const float rx, const float ry, const float rz) = 0; // Rotate without calling any callbacks
		virtual bool Transform(const float tx, const float ty, const float tz, const float sx, const float sy, const float sz, const float rx, const float ry, const float rz) = 0; // Translate, scale, and rotate without calling any callbacks

		virtual void Release() = 0; // Destroy service
	};
}