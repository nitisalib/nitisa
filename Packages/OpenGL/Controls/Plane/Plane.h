// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/3DControl.h"
#include "../../Primitives/2D/Plane/PrimitivePlane.h"
#include "../IPlane.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IRenderer;

	class COpenGL;

	namespace opengl
	{
		class CPlane :public virtual IPlane, public C3DControl
		{
		private:
			CPrimitivePlane m_cPrimitive;
		protected:
			void FreeResources(COpenGL *graphics) override;
			void Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera) override;
		public:
			// IPlane getters
			float getPlaneWidth() override;
			float getPlaneDepth() override;
			int getWidthSegments() override;
			int getDepthSegments() override;

			// IPlane setters
			bool setPlaneWidth(const float value) override;
			bool setPlaneDepth(const float value) override;
			bool setPlaneSize(const float width, const float depth) override;
			bool setWidthSegments(const int value) override;
			bool setDepthSegments(const int value) override;
			bool setSegments(const int width, const int depth) override;

			CPlane();
			CPlane(IControl *parent);
		};
	}
}