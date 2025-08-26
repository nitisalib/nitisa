// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Vec2f.h"
#include "Nitisa/Math/Vec2i.h"
#include "Nitisa/Math/Vec3f.h"
#include "Nitisa/Math/Vec3i.h"
#include "Nitisa/Math/Vec4f.h"
#include "Nitisa/Math/Vec4i.h"
#include "../Interfaces/IMaterialControl.h"

namespace nitisa
{
	class ITexture;

	namespace opengl
	{
		class ICustomMaterial :public virtual IMaterialControl
		{
		protected:
			ICustomMaterial() = default;
			~ICustomMaterial() = default;
			ICustomMaterial(const ICustomMaterial &other) = delete;
			ICustomMaterial(ICustomMaterial &&other) = delete;
			ICustomMaterial &operator=(const ICustomMaterial &other) = delete;
			ICustomMaterial &operator=(ICustomMaterial &&other) = delete;
		public:
			enum class OptionType // Shader option types
			{
				None, // Option is not found
				Integer,
				Float,
				Vec2,
				Vec3,
				Vec4,
				Vec2i,
				Vec3i,
				Vec4i,
				Mat4
			};
		public:
			void(*OnActivateMaterial)(ICustomMaterial *sender); // Event called at material activation after setting default shader uniform. In this event custom options could be set/updated

			virtual ITexture *getTexture() = 0; // Return associated texture
			virtual AnsiString getVertexShader() = 0; // Return vertex shader code
			virtual AnsiString getFragmentShader() = 0; // Return fragment shader code
			virtual int getOptionCount() = 0; // Return option count
			virtual String getOptionName(const int index) = 0; // Return specified option name. Return empty string if not found
			virtual OptionType getOptionType(const int index) = 0; // Return specified option type. Return otNone if not found
			virtual int getIntegerOptionValue(const int index) = 0; // Return specified option integer value. Return 0 if not found
			virtual float getFloatOptionValue(const int index) = 0; // Return specified option float value. Return 0 if not found
			virtual Vec2f getVec2OptionValue(const int index) = 0; // Return specified option Vec2 value. Return zero vector if not found
			virtual Vec3f getVec3OptionValue(const int index) = 0; // Return specified option Vec3 value. Return zero vector if not found
			virtual Vec4f getVec4OptionValue(const int index) = 0; // Return specified option Vec4 value. Return zero vector if not found
			virtual Vec2i getVec2iOptionValue(const int index) = 0; // Return specified option Vec2i value. Return zero vector if not found
			virtual Vec3i getVec3iOptionValue(const int index) = 0; // Return specified option Vec3i value. Return zero vector if not found
			virtual Vec4i getVec4iOptionValue(const int index) = 0; // Return specified option Vec4i value. Return zero vector if not found
			virtual Mat4f getMat4OptionValue(const int index) = 0; // Return specified option matrix value. Return identity matrix if not found

			virtual bool setTexture(ITexture *value) = 0; // Associate texture
			virtual bool setVertexShader(const AnsiString &value) = 0; // Set vertex shader code
			virtual bool setFragmentShader(const AnsiString &value) = 0; // Set fragment shader code
			virtual bool setShaders(const AnsiString &vertex, const AnsiString &fragment) = 0; // Set both vertex and fragment shader codes
			virtual bool setOption(const String &name, const int value) = 0; // Set integer option value
			virtual bool setOption(const String &name, const float value) = 0; // Set float option value
			virtual bool setOption(const String &name, const Vec2f &value) = 0; // Set Vec2 option value
			virtual bool setOption(const String &name, const Vec3f &value) = 0; // Set Vec3 option value
			virtual bool setOption(const String &name, const Vec4f &value) = 0; // Set Vec4 option value
			virtual bool setOption(const String &name, const Vec2i &value) = 0; // Set Vec2i option value
			virtual bool setOption(const String &name, const Vec3i &value) = 0; // Set Vec3i option value
			virtual bool setOption(const String &name, const Vec4i &value) = 0; // Set Vec4i option value
			virtual bool setOption(const String &name, const Mat4f &value) = 0; // Set matrix option value

			virtual bool LoadVertexShader(const String &filename) = 0; // Load vertex shader code from specified file
			virtual bool LoadFragmentShader(const String &filename) = 0; // Load fragment shader code from specified file
			virtual bool LoadShaders(const String &vertex_filename, const String &fragment_filename) = 0; // Load vertex and fragment shader code from specified files

			virtual void LockUpdate() = 0; // Prevent shaders recompilation until final unlock
			virtual void UnlockUpdate() = 0; // Allow shader recompilation on changes. Should be called the same time the previous method was called
		};
	}
}