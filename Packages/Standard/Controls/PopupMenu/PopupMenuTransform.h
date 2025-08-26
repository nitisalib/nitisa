// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/RotateOrder.h"
#include "Nitisa/Core/Transform.h"
#include "Nitisa/Core/TransformOrder.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Transform.h"

namespace nitisa
{
	class IFeedbackExListener;

	namespace standard
	{
		class CPopupMenu;

		class CPopupMenuTransform :public CTransform
		{
		public:
			const Mat4f &getMatrix() override;
			const Mat4f &getMatrixScale() override;
			const Mat4f &getMatrixRotate() override;
			bool isTranslateIdentity() const override;
			bool isScaleIdentity() const override;
			bool isRotateIdentity() const override;
			bool isIdentity() const override;

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

			CPopupMenuTransform(IFeedbackExListener *listener);

			bool Translate(const float tx, const float ty, const float tz) override;
			bool Scale(const float sx, const float sy, const float sz) override;
			bool Rotate(const float rx, const float ry, const float rz) override;
			bool Transform(const float tx, const float ty, const float tz, const float sx, const float sy, const float sz, const float rx, const float ry, const float rz) override;
		};
	}
}