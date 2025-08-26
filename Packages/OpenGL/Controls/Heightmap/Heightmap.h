// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Math/Point.h"
#include "../../Core/3DControl.h"
#include "../IHeightmap.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IRenderer;
	class IVertexArray;

	class COpenGL;


	namespace opengl
	{
		class CHeightmap :public virtual IHeightmap, public C3DControl
		{
		private:
			float m_fCellWidth;
			float m_fCellHeight;
			float m_fCellDepth;
			String m_sFilename;
			Point m_sHeightmapSize;
			IVertexArray *m_pVertexArray;
			bool m_bValid;
		protected:
			void FreeResources(COpenGL *graphics) override;
			void Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera) override;
		public:
			// IHeightmap getters
			float getCellWidth() override;
			float getCellHeight() override;
			float getCellDepth() override;
			String getFilename() override;
			Point getHeightmapSize() override;

			// IHeightmap setters
			bool setCellWidth(const float value) override;
			bool setCellHeight(const float value) override;
			bool setCellDepth(const float value) override;
			bool setCellSize(const float width, const float height, const float depth) override;
			bool setFilename(const String &value) override;

			CHeightmap();
			CHeightmap(IControl *parent);
		};
	}
}