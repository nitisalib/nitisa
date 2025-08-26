// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/RotateOrder.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/TransformOrder.h"
#include "../Interfaces/I3DControl.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IModel;
	class IRenderer;

	class COpenGL;

	namespace opengl
	{
		class IMaterialControl;

		class C3DControlService;

		class C3DControl :public virtual I3DControl, public CControl
		{
			friend C3DControlService;
		private:
			IModel *m_pModel;
			IMaterialControl *m_pMaterial;
			RenderMode m_eRenderMode;
		protected:
			virtual void FreeResources(COpenGL *graphics) = 0; // Called when platform resources should be released
			virtual void Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera) = 0; // Called when rendering of the control is required
		public:
			// IControl getters
			bool isAcceptControl() override;
			bool isAcceptControl(IControl *control) override;

			// IControl setters
			bool setVisible(const bool value) override; // Not allowed

			// I3DControl getters
			IModel *getModel() override;
			IMaterialControl *getMaterial() override;
			RenderMode getRenderMode() override;
			RotateOrder getRotateOrder() override;
			TransformOrder getTransformOrder() override;
			float getX() override;
			float getY() override;
			float getZ() override;
			float getSx() override;
			float getSy() override;
			float getSz() override;
			float getPitch() override; // In degrees
			float getYaw() override; // In degrees
			float getRoll() override; // In degrees

			// I3DControl setters
			bool setMaterial(IMaterialControl *value) override;
			bool setRenderMode(const RenderMode value) override;
			bool setRotateOrder(const RotateOrder value) override;
			bool setTransformOrder(const TransformOrder value) override;
			bool setX(const float value) override;
			bool setY(const float value) override;
			bool setZ(const float value) override;
			bool setSx(const float value) override;
			bool setSy(const float value) override;
			bool setSz(const float value) override;
			bool setPitch(const float value) override; // In degrees
			bool setYaw(const float value) override; // In degrees
			bool setRoll(const float value) override; // In degrees

			C3DControl(const String &class_name);
			~C3DControl() override;
		};
	}
}