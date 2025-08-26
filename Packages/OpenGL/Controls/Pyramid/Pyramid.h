// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/3DControl.h"
#include "../../Primitives/3D/Pyramid/PrimitivePyramid.h"
#include "../IPyramid.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IRenderer;

	class COpenGL;

	namespace opengl
	{
		class CPyramid :public virtual IPyramid, public C3DControl
		{
		private:
			CPrimitivePyramid m_cPrimitive;
		protected:
			void FreeResources(COpenGL *graphics) override;
			void Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera) override;
		public:
			// IPyramid getters
			float getPyramidWidth() override;
			float getPyramidDepth() override;
			float getPyramidHeight() override;
			int getHeightSegments() override;

			// IPyramid setters
			bool setPyramidWidth(const float value) override;
			bool setPyramidDepth(const float value) override;
			bool setPyramidHeight(const float value) override;
			bool setPyramidSize(const float width, const float depth, const float height) override;
			bool setHeightSegments(const int value) override;

			CPyramid();
			CPyramid(IControl *parent);
		};
	}
}