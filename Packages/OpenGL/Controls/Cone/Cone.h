// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/3DControl.h"
#include "../../Primitives/3D/Cone/PrimitiveCone.h"
#include "../ICone.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IRenderer;

	class COpenGL;

	namespace opengl
	{
		class CCone :public virtual ICone, public C3DControl
		{
		private:
			CPrimitiveCone m_cPrimitive;
		protected:
			void FreeResources(COpenGL *graphics) override;
			void Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera) override;
		public:
			// ICone getters
			float getConeRadius1() override;
			float getConeRadius2() override;
			float getConeHeight() override;
			int getConeSides() override;
			int getCapSegments() override;
			int getHeightSegments() override;

			// ICone setters
			bool setConeRadius1(const float value) override;
			bool setConeRadius2(const float value) override;
			bool setConeHeight(const float value) override;
			bool setConeSides(const int value) override;
			bool setConeSize(const float radius1, const float radius2, const float height, const int sides) override;
			bool setCapSegments(const int value) override;
			bool setHeightSegments(const int value) override;
			bool setSegments(const int cap, const int height) override;

			CCone();
			CCone(IControl *parent);
		};
	}
}