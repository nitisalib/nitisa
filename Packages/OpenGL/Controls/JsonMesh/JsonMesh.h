// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Variant.h"
#include "../../Core/3DControl.h"
#include "../IJsonMesh.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IRenderer;
	class IVertexArray;

	class COpenGL;


	namespace opengl
	{
		class CJsonMesh :public virtual IJsonMesh, public C3DControl
		{
		private:
			String m_sFilename;

			IVertexArray *m_pVertexArray;
			bool m_bValid;

			void VariantToVertexArray(IVertexArray *va, const Variant &content);
		protected:
			void FreeResources(COpenGL *graphics) override;
			void Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera) override;
		public:
			// IJsonMesh getters
			String getFilename() override;

			// IJsonMesh setters
			bool setFilename(const String &value) override;

			CJsonMesh();
			CJsonMesh(IControl *parent);
		};
	}
}