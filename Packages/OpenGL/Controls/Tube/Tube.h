// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/3DControl.h"
#include "../../Primitives/3D/Tube/PrimitiveTube.h"
#include "../ITube.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IRenderer;

	class COpenGL;

	namespace opengl
	{
		class CTube :public virtual ITube, public C3DControl
		{
		private:
			CPrimitiveTube m_cPrimitive;
		protected:
			void FreeResources(COpenGL *graphics) override;
			void Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera) override;
		public:
			// ITube getters
			float getTubeOuterRadius() override;
			float getTubeInnerRadius() override;
			float getTubeHeight() override;
			int getTubeSides() override;
			int getCapSegments() override;
			int getHeightSegments() override;

			// ITube setters
			bool setTubeOuterRadius(const float value) override;
			bool setTubeInnerRadius(const float value) override;
			bool setTubeHeight(const float value) override;
			bool setTubeSides(const int value) override;
			bool setTubeSize(const float outer_radius, const float inner_radius, const float height, const int sides) override;
			bool setCapSegments(const int value) override;
			bool setHeightSegments(const int value) override;
			bool setSegments(const int cap, const int height) override;

			CTube();
			CTube(IControl *parent);
		};
	}
}