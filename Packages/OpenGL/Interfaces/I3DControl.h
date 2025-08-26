// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/RotateOrder.h"
#include "Nitisa/Core/TransformOrder.h"
#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	class ICamera;
	class IModel;

	class COpenGL;
	
	namespace opengl
	{
		class IMaterialControl;

		class I3DControl :public virtual IControl
		{
		protected:
			I3DControl() = default;
			~I3DControl() = default;
			I3DControl(const I3DControl &other) = delete;
			I3DControl(I3DControl &&other) = delete;
			I3DControl &operator=(const I3DControl &other) = delete;
			I3DControl &operator=(I3DControl &&other) = delete;
		public:
			enum class RenderMode // How 3D geometry should be rendered
			{
				Fill, // Common way, triangles are displayed in normal, filled, way
				Wireframe, // Render as wire-frames, only edges or triangles are rendered
				Vertices // Render only vertices as points
			};
		public:
			virtual IModel *getModel() = 0; // Return associated model
			virtual IMaterialControl *getMaterial() = 0; // Return associated material control
			virtual RenderMode getRenderMode() = 0; // Return rendering mode
			virtual RotateOrder getRotateOrder() = 0; // Return rotation order
			virtual TransformOrder getTransformOrder() = 0; // Return transformation order
			virtual float getX() = 0; // Return X position
			virtual float getY() = 0; // Return Y position
			virtual float getZ() = 0; // Return Z position
			virtual float getSx() = 0; // Return scaling in local X direction
			virtual float getSy() = 0; // Return scaling in local Y direction
			virtual float getSz() = 0; // Return scaling in local Z direction
			virtual float getPitch() = 0; // Return rotation around local X axis
			virtual float getYaw() = 0; // Return rotation around local Y axis
			virtual float getRoll() = 0; // Return rotation around local Z axis

			virtual bool setMaterial(IMaterialControl *value) = 0; // Assign material control
			virtual bool setRenderMode(const RenderMode value) = 0; // Set rendering mode
			virtual bool setRotateOrder(const RotateOrder value) = 0; // Set rotate order
			virtual bool setTransformOrder(const TransformOrder value) = 0; // Set transform order
			virtual bool setX(const float value) = 0; // Set X position
			virtual bool setY(const float value) = 0; // Set Y position
			virtual bool setZ(const float value) = 0; // Set Z position
			virtual bool setSx(const float value) = 0; // Set scaling in local X direction
			virtual bool setSy(const float value) = 0; // Set scaling in local Y direction
			virtual bool setSz(const float value) = 0; // Set scaling in local Z direction
			virtual bool setPitch(const float value) = 0; // Set rotation angle around local X axis
			virtual bool setYaw(const float value) = 0; // Set rotation angle around local Y axis
			virtual bool setRoll(const float value) = 0; // Set rotation angle around local Z axis
		};
	}
}