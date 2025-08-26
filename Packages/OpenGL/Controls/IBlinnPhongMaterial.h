// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Image/Color.h"
#include "Nitisa/Math/Vec3f.h"
#include "../Interfaces/IMaterialControl.h"

namespace nitisa
{
	class ITexture;

	namespace opengl
	{
		class IBlinnPhongMaterial :public virtual IMaterialControl
		{
		protected:
			IBlinnPhongMaterial() = default;
			~IBlinnPhongMaterial() = default;
			IBlinnPhongMaterial(const IBlinnPhongMaterial &other) = delete;
			IBlinnPhongMaterial(IBlinnPhongMaterial &&other) = delete;
			IBlinnPhongMaterial &operator=(const IBlinnPhongMaterial &other) = delete;
			IBlinnPhongMaterial &operator=(IBlinnPhongMaterial &&other) = delete;
		public:
			virtual ITexture *getTexture() = 0; // Return associated texture
			virtual Color getAmbientColor() = 0; // Return ambient color
			virtual Color getDiffuseColor() = 0; // Return diffuse color
			virtual Color getSpecularColor() = 0; // Return specular color
			virtual Color getLightDiffuseColor() = 0; // Return light diffuse color
			virtual Color getLightSpecularColor() = 0; // Return light specular color
			virtual Vec3f getLightPosition() = 0; // Return light position
			virtual float getLightX() = 0; // Return light X position
			virtual float getLightY() = 0; // Return light Y position
			virtual float getLightZ() = 0; // Return light Z position
			virtual float getShininess() = 0; // Return shininess power

			virtual bool setTexture(ITexture *value) = 0; // Assign texture
			virtual bool setAmbientColor(const Color &value) = 0; // Set ambient color
			virtual bool setDiffuseColor(const Color &value) = 0; // Set diffuse color
			virtual bool setSpecularColor(const Color &value) = 0; // Set specular color
			virtual bool setLightDiffuseColor(const Color &value) = 0; // Set light diffuse color
			virtual bool setLightSpecularColor(const Color &value) = 0; // Set light specular color
			virtual bool setLightPosition(const Vec3f &value) = 0; // Set light position
			virtual bool setLightX(const float value) = 0; // Set light X position
			virtual bool setLightY(const float value) = 0; // Set light Y position
			virtual bool setLightZ(const float value) = 0; // Set light Z position
			virtual bool setShininess(const float value) = 0; // Set shininess power
		};
	}
}