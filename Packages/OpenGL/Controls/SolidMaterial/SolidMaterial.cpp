// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#include "Platform/OpenGL/OpenGL.h"

namespace nitisa
{
	namespace opengl
	{
	#pragma region Constructor & destructor
		CSolidMaterial::CSolidMaterial():
			CControl(L"SolidMaterial", false, true, false, false, false, false),
			m_pTexture{ nullptr },
			m_sColor{ 255, 255, 255, 255 },
			m_pProgram{ nullptr },
			m_bProgramValid{ false }
		{
			setService(new CSolidMaterialService(this), true);
		}

		CSolidMaterial::CSolidMaterial(IControl *parent) :CSolidMaterial()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IControl getters
		bool CSolidMaterial::isAcceptControl()
		{
			return CControl::isAcceptControl();
		}

		bool CSolidMaterial::isAcceptControl(IControl *control)
		{
			return CControl::isAcceptControl() && cast<IView*>(control) != nullptr;
		}
	#pragma endregion

	#pragma region IMaterialControl methods
		bool CSolidMaterial::Activate(COpenGL *graphics, IModel *model, ICamera *camera)
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			if (!m_pProgram)
			{
				if (!(m_pProgram = renderer->CreateProgram(shaders::solid::Vertex, shaders::solid::Fragment)))
					return false;
				renderer->ActivateProgram(m_pProgram);
				m_bProgramValid = true;
				if ((*reinterpret_cast<GLint*>(&m_hUniformMatrix) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_Matrix")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformHasTexture) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_HasTexture")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformColor) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_Color")) < 0)
					m_bProgramValid = false;
				graphics->Uniform1i(graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_Texture"), 0);
			}
			bool result{ false };
			if (m_bProgramValid)
			{
				renderer->ActivateProgram(m_pProgram);
				graphics->UniformMatrix4fv(*reinterpret_cast<GLint*>(&m_hUniformMatrix), 1, GL_TRUE, (camera->getMatrix() * model->getMatrix()).Data);
				if (m_pTexture)
				{
					graphics->Uniform1i(*reinterpret_cast<GLint*>(&m_hUniformHasTexture), 1);
					graphics->ActiveTexture(GL_TEXTURE0);
					graphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_pTexture->Handle));
				}
				else
					graphics->Uniform1i(*reinterpret_cast<GLint*>(&m_hUniformHasTexture), 0);
				graphics->Uniform4f(*reinterpret_cast<GLint*>(&m_hUniformColor), m_sColor.R / 255.0f, m_sColor.G / 255.0f, m_sColor.B / 255.0f, m_sColor.A / 255.0f);
				result = true;
			}
			return result;
		}
	#pragma endregion

	#pragma region ISolidMaterial getters
		ITexture *CSolidMaterial::getTexture()
		{
			return m_pTexture;
		}

		Color CSolidMaterial::getColor()
		{
			return m_sColor;
		}
	#pragma endregion

	#pragma region ISolidMaterial setters
		bool CSolidMaterial::setTexture(ITexture *value)
		{
			m_pTexture = value;
			QueryService()->SendChangeNotification();
			return true;
		}

		bool CSolidMaterial::setColor(const Color &value)
		{
			if (value != m_sColor)
			{
				m_sColor = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}