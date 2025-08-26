// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/3DControl.h"
#include "../../Primitives/3D/Torus/PrimitiveTorus.h"
#include "../ITorus.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IRenderer;

	class COpenGL;

	namespace opengl
	{
		class CTorus :public virtual ITorus, public C3DControl
		{
		private:
			CPrimitiveTorus m_cPrimitive;
		protected:
			void FreeResources(COpenGL *graphics) override;
			void Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera) override;
		public:
			// ITorus getters
			float getTorusRadius1() override;
			float getTorusRadius2() override;
			int getTorusSides1() override;
			int getTorusSides2() override;

			// ITorus setters
			bool setTorusRadius1(const float value) override;
			bool setTorusRadius2(const float value) override;
			bool setTorusSides1(const int value) override;
			bool setTorusSides2(const int value) override;
			bool setTorusSize(const float radius1, const float radius2, const int sides1, const int sides2) override;

			CTorus();
			CTorus(IControl *parent);
		};
	}
}