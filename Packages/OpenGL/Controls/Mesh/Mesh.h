// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/3DControl.h"
#include "../IMesh.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IRenderer;
	class IVertexArray;

	class COpenGL;

	namespace opengl
	{
		class CMesh :public virtual IMesh, public C3DControl
		{
		private:
			IVertexArray *m_pVertexArray;
		protected:
			void FreeResources(COpenGL *graphics) override;
			void Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera) override;
		public:
			// IMesh getters
			IVertexArray *getVertexArray() override;

			CMesh();
			CMesh(IControl *parent);
		};
	}
}