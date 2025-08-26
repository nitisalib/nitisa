// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/3DControl.h"
#include "../../Primitives/2D/Disk/PrimitiveDisk.h"
#include "../IDisk.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IRenderer;

	class COpenGL;

	namespace opengl
	{
		class CDisk :public virtual IDisk, public C3DControl
		{
		private:
			CPrimitiveDisk m_cPrimitive;
		protected:
			void FreeResources(COpenGL *graphics) override;
			void Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera) override;
		public:
			// IDisk getters
			float getDiskOuterRadius() override;
			float getDiskInnerRadius() override;
			int getDiskSides() override;
			int getCapSegments() override;
			
			// IDisk setters
			bool setDiskOuterRadius(const float value) override;
			bool setDiskInnerRadius(const float value) override;
			bool setDiskSides(const int value) override;
			bool setDiskSize(const float outer_radius, const float inner_radius, const int sides) override;
			bool setCapSegments(const int value) override;
			
			CDisk();
			CDisk(IControl *parent);
		};
	}
}