// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/3DControl.h"
#include "../../Primitives/3D/Sphere/PrimitiveSphere.h"
#include "../ISphere.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IRenderer;

	class COpenGL;

	namespace opengl
	{
		class CSphere :public virtual ISphere, public C3DControl
		{
		private:
			CPrimitiveSphere m_cPrimitive;
		protected:
			void FreeResources(COpenGL *graphics) override;
			void Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera) override;
		public:
			// ISphere getters
			float getSphereRadius() override;
			int getSphereSides() override;
			int getSphereYSides() override;

			// ISphere setters
			bool setSphereRadius(const float value) override;
			bool setSphereSides(const int value) override;
			bool setSphereYSides(const int value) override;
			bool setSphereSize(const float radius, const int sides, const int y_sides) override;

			CSphere();
			CSphere(IControl *parent);
		};
	}
}