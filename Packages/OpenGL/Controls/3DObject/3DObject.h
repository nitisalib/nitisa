// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../I3DObject.h"
#include "../../Core/3DControl.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IRenderer;
	class IVertexArray;

	class COpenGL;

	namespace opengl
	{
		class C3DObject :public virtual I3DObject, public C3DControl
		{
		private:
			IVertexArray *m_pVertexArray;
			PrimitiveType m_ePrimitiveType;
		protected:
			void FreeResources(COpenGL *graphics) override;
			void Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera) override;
		public:
			// I3DObject getters
			IVertexArray *getVertexArray() override;
			PrimitiveType getPrimitiveType() const override;

			// I3DObject setters
			bool setPrimitiveType(const PrimitiveType &value) override;

			C3DObject();
			C3DObject(IControl *parent);
		};
	}
}