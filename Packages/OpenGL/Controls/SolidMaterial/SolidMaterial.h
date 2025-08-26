// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Image/Color.h"
#include "../ISolidMaterial.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IModel;
	class IProgram;
	class ITexture;

	class COpenGL;
	
	namespace opengl
	{
		class CSolidMaterialService;

		class CSolidMaterial :public virtual ISolidMaterial, public CControl
		{
			friend CSolidMaterialService;
		private:
			ITexture *m_pTexture;
			Color m_sColor;
			IProgram *m_pProgram;
			bool m_bProgramValid;

			PlatformHandle m_hUniformMatrix;
			PlatformHandle m_hUniformHasTexture;
			PlatformHandle m_hUniformColor;
		public:
			// IControl getters
			bool isAcceptControl() override;
			bool isAcceptControl(IControl *control) override;

			// IMaterialControl methods
			bool Activate(COpenGL *graphics, IModel *model, ICamera *camera) override;

			// ISolidMaterial getters
			ITexture *getTexture() override;
			Color getColor() override;

			// ISolidMaterial setters
			bool setTexture(ITexture *value) override;
			bool setColor(const Color &value) override;

			CSolidMaterial();
			CSolidMaterial(IControl *parent);
		};
	}
}