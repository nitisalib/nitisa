// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/3DControl.h"
#include "../../Primitives/3D/Cylinder/PrimitiveCylinder.h"
#include "../ICylinder.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IRenderer;

	class COpenGL;

	namespace opengl
	{
		class CCylinder :public virtual ICylinder, public C3DControl
		{
		private:
			CPrimitiveCylinder m_cPrimitive;
		protected:
			void FreeResources(COpenGL *graphics) override;
			void Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera) override;
		public:
			// ICylinder getters
			float getCylinderRadius() override;
			float getCylinderHeight() override;
			int getCylinderSides() override;
			int getCapSegments() override;
			int getHeightSegments() override;

			// ICylinder setters
			bool setCylinderRadius(const float value) override;
			bool setCylinderHeight(const float value) override;
			bool setCylinderSides(const int value) override;
			bool setCylinderSize(const float radius, const float height, const int sides) override;
			bool setCapSegments(const int value) override;
			bool setHeightSegments(const int value) override;
			bool setSegments(const int cap, const int height) override;

			CCylinder();
			CCylinder(IControl *parent);
		};
	}
}