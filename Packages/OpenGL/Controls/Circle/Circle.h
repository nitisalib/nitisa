// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/3DControl.h"
#include "../../Primitives/2D/Circle/PrimitiveCircle.h"
#include "../ICircle.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IRenderer;

	class COpenGL;

	namespace opengl
	{
		class CCircle :public virtual ICircle, public C3DControl
		{
		private:
			CPrimitiveCircle m_cPrimitive;
		protected:
			void FreeResources(COpenGL *graphics) override;
			void Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera) override;
		public:
			// ICircle getters
			float getCircleRadius() override;
			int getCircleSides() override;
			int getCapSegments() override;
			
			// ICircle setters
			bool setCircleRadius(const float value) override;
			bool setCircleSides(const int value) override;
			bool setCircleSize(const float radius, const int sides) override;
			bool setCapSegments(const int value) override;
			
			CCircle();
			CCircle(IControl *parent);
		};
	}
}