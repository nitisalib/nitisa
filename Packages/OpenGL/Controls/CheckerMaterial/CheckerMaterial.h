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
#include "Nitisa/Math/PointF.h"
#include "../ICheckerMaterial.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IModel;
	class IProgram;

	class COpenGL;

	namespace opengl
	{
		class CCheckerMaterialService;

		class CCheckerMaterial :public virtual ICheckerMaterial, public CControl
		{
			friend CCheckerMaterialService;
		private:
			Color m_sColor1;
			Color m_sColor2;
			IProgram *m_pProgram;
			PointF m_sScale;
			bool m_bProgramValid;

			PlatformHandle m_hUniformMatrix;
			PlatformHandle m_hUniformColor1;
			PlatformHandle m_hUniformColor2;
			PlatformHandle m_hUniformScale;
		public:
			// IControl getters
			bool isAcceptControl() override;
			bool isAcceptControl(IControl *control) override;

			// IMaterialControl methods
			bool Activate(COpenGL *graphics, IModel *model, ICamera *camera) override;

			// ICheckerMaterial getters
			Color getColor1() override;
			Color getColor2() override;
			PointF getScale() override;

			// ICheckerMaterial setters
			bool setColor1(const Color &value) override;
			bool setColor2(const Color &value) override;
			bool setScale(const PointF &value) override;

			CCheckerMaterial();
			CCheckerMaterial(IControl *parent);
		};
	}
}