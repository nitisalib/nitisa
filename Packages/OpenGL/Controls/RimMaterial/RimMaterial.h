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
#include "Nitisa/Math/Vec3f.h"
#include "../IRimMaterial.h"

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
		class CRimMaterialService;

		class CRimMaterial :public virtual IRimMaterial, public CControl
		{
			friend CRimMaterialService;
		private:
			ITexture *m_pTexture;
			Color m_sAmbientColor;
			Color m_sDiffuseColor;
			Color m_sSpecularColor;
			Color m_sRimColor;
			Color m_sLightDiffuseColor;
			Color m_sLightSpecularColor;
			Vec3f m_sLightPosition;
			float m_fShininess;
			float m_fRimPower;

			IProgram *m_pProgram;
			bool m_bProgramValid;

			PlatformHandle m_hUniformMatrixModel;
			PlatformHandle m_hUniformMatrixNormal;
			PlatformHandle m_hUniformMatrixCamera;
			PlatformHandle m_hUniformHasTexture;
			PlatformHandle m_hUniformAmbientColor;
			PlatformHandle m_hUniformDiffuseAlbedo;
			PlatformHandle m_hUniformSpecularAlbedo;
			PlatformHandle m_hUniformRimColor;
			PlatformHandle m_hUniformLightPosition;
			PlatformHandle m_hUniformCameraPosition;
			PlatformHandle m_hUniformShininess;
			PlatformHandle m_hUniformRimPower;
		public:
			// IControl getters
			bool isAcceptControl() override;
			bool isAcceptControl(IControl *control) override;

			// IMaterialControl methods
			bool Activate(COpenGL *graphics, IModel *model, ICamera *camera) override;

			// IRimMaterial getters
			ITexture *getTexture() override;
			Color getAmbientColor() override;
			Color getDiffuseColor() override;
			Color getSpecularColor() override;
			Color getRimColor() override;
			Color getLightDiffuseColor() override;
			Color getLightSpecularColor() override;
			Vec3f getLightPosition() override;
			float getLightX() override;
			float getLightY() override;
			float getLightZ() override;
			float getShininess() override;
			float getRimPower() override;

			// IRimMaterial setters
			bool setTexture(ITexture *value) override;
			bool setAmbientColor(const Color &value) override;
			bool setDiffuseColor(const Color &value) override;
			bool setSpecularColor(const Color &value) override;
			bool setRimColor(const Color &value) override;
			bool setLightDiffuseColor(const Color &value) override;
			bool setLightSpecularColor(const Color &value) override;
			bool setLightPosition(const Vec3f &value) override;
			bool setLightX(const float value) override;
			bool setLightY(const float value) override;
			bool setLightZ(const float value) override;
			bool setShininess(const float value) override;
			bool setRimPower(const float value) override;

			CRimMaterial();
			CRimMaterial(IControl *parent);
		};
	}
}