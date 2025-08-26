// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IRenderer.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Vec2f.h"
#include "Nitisa/Math/Vec2i.h"
#include "Nitisa/Math/Vec3f.h"
#include "Nitisa/Math/Vec3i.h"
#include "Nitisa/Math/Vec4f.h"
#include "Nitisa/Math/Vec4i.h"
#include "../ICustomMaterial.h"
#include <vector>

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
		class CCustomMaterialService;

		class CCustomMaterial :public virtual ICustomMaterial, public CControl
		{
			friend CCustomMaterialService;
		private:
			class CProgramLock
			{
			private:
				IRenderer *m_pRenderer;
				IProgram *m_pOldProgram;
			public:
				CProgramLock(CCustomMaterial *control) :
					m_pRenderer{ control->getForm()->getRenderer() }
				{
					m_pOldProgram = m_pRenderer->ActiveProgram;
					m_pRenderer->ActivateProgram(control->m_pProgram);
				}

				~CProgramLock()
				{
					m_pRenderer->ActivateProgram(m_pOldProgram);
				}
			};
			struct OPTION
			{
				String Name;
				OptionType Type;
				int ValueInteger;
				float ValueFloat;
				Vec2f ValueVec2;
				Vec3f ValueVec3;
				Vec4f ValueVec4;
				Vec2i ValueVec2i;
				Vec3i ValueVec3i;
				Vec4i ValueVec4i;
				Mat4f ValueMat4;
				int UniformLocation;
			};
		private:
			ITexture *m_pTexture;
			AnsiString m_sVertexShader;
			AnsiString m_sFragmentShader;
			std::vector<OPTION> m_aOptions;
			bool m_bUseMatrixModel;
			bool m_bUseMatrixCamera;
			bool m_bUseHasTexture;

			int m_iLockCount;
			bool m_bUpdateRequired;
			IProgram *m_pProgram;
			COpenGL *m_pGraphics;

			bool BuildProgram();
		public:
			// IControl getters
			bool isAcceptControl() override;
			bool isAcceptControl(IControl *control) override;

			// IMaterialControl methods
			bool Activate(COpenGL *graphics, IModel *model, ICamera *camera) override;

			// ICustomMaterial getters
			ITexture *getTexture() override;
			AnsiString getVertexShader() override;
			AnsiString getFragmentShader() override;
			int getOptionCount() override;
			String getOptionName(const int index) override;
			OptionType getOptionType(const int index) override;
			int getIntegerOptionValue(const int index) override;
			float getFloatOptionValue(const int index) override;
			Vec2f getVec2OptionValue(const int index) override;
			Vec3f getVec3OptionValue(const int index) override;
			Vec4f getVec4OptionValue(const int index) override;
			Vec2i getVec2iOptionValue(const int index) override;
			Vec3i getVec3iOptionValue(const int index) override;
			Vec4i getVec4iOptionValue(const int index) override;
			Mat4f getMat4OptionValue(const int index) override;

			// ICustomMaterial setters
			bool setTexture(ITexture *value) override;
			bool setVertexShader(const AnsiString &value) override;
			bool setFragmentShader(const AnsiString &value) override;
			bool setShaders(const AnsiString &vertex, const AnsiString &fragment) override;
			bool setOption(const String &name, const int value) override;
			bool setOption(const String &name, const float value) override;
			bool setOption(const String &name, const Vec2f &value) override;
			bool setOption(const String &name, const Vec3f &value) override;
			bool setOption(const String &name, const Vec4f &value) override;
			bool setOption(const String &name, const Vec2i &value) override;
			bool setOption(const String &name, const Vec3i &value) override;
			bool setOption(const String &name, const Vec4i &value) override;
			bool setOption(const String &name, const Mat4f &value) override;

			bool LoadVertexShader(const String &filename) override;
			bool LoadFragmentShader(const String &filename) override;
			bool LoadShaders(const String &vertex_filename, const String &fragment_filename) override;

			void LockUpdate() override;
			void UnlockUpdate() override;

			CCustomMaterial();
			CCustomMaterial(IControl *parent);

			bool isUseMatrixModel() const; // Return whether app_MatrixModel uniform should be looked up and used
			bool isUseMatrixCamera() const; // Return whether app_MatrixCamera uniform should be looked up and used
			bool isUseHasTexture() const; // Return whether app_HasTexture uniform should be looked up and used

			bool setUseMatrixModel(const bool value); // Set whether app_MatrixModel uniform should be looked up and used
			bool setUseMatrixCamera(const bool value); // Set whether app_MatrixCamera uniform should be looked up and used
			bool setUseHasTexture(const bool value); // Set whether app_HasTexture uniform should be looked up and used
		};
	}
}