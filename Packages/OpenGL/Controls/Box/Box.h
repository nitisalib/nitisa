// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/3DControl.h"
#include "../../Primitives/3D/Box/PrimitiveBox.h"
#include "../IBox.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IRenderer;

	class COpenGL;

	namespace opengl
	{
		class CBox :public virtual IBox, public C3DControl
		{
		private:
			CPrimitiveBox m_cPrimitive;
		protected:
			void FreeResources(COpenGL *graphics) override;
			void Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera) override;
		public:
			// IBox getters
			float getBoxWidth() override;
			float getBoxHeight() override;
			float getBoxDepth() override;
			int getWidthSegments() override;
			int getHeightSegments() override;
			int getDepthSegments() override;

			// IBox setters
			bool setBoxWidth(const float value) override;
			bool setBoxHeight(const float value) override;
			bool setBoxDepth(const float value) override;
			bool setBoxSize(const float width, const float height, const float depth) override;
			bool setWidthSegments(const int value) override;
			bool setHeightSegments(const int value) override;
			bool setDepthSegments(const int value) override;
			bool setSegments(const int width, const int height, const int depth) override;

			CBox();
			CBox(IControl *parent);
		};
	}
}