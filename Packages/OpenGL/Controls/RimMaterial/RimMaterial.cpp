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
		CRimMaterial::CRimMaterial() :
			CControl(L"RimMaterial", false, true, false, false, false, false),
			m_pTexture{ nullptr },
			m_sAmbientColor{ 32, 32, 32, 255 },
			m_sDiffuseColor{ 127, 127, 127, 255 },
			m_sSpecularColor{ 255, 255, 255, 255 },
			m_sRimColor{ 255, 255, 255, 255 },
			m_sLightDiffuseColor{ 127, 127, 127, 255 },
			m_sLightSpecularColor{ 220, 220, 220, 255 },
			m_sLightPosition{ 0, 100, 100 },
			m_fShininess{ 100 },
			m_fRimPower{ 5 },
			m_pProgram{ nullptr },
			m_bProgramValid{ false }
		{
			setService(new CRimMaterialService(this), true);
		}

		CRimMaterial::CRimMaterial(IControl *parent) :CRimMaterial()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IControl getters
		bool CRimMaterial::isAcceptControl()
		{
			return CControl::isAcceptControl();
		}

		bool CRimMaterial::isAcceptControl(IControl *control)
		{
			return CControl::isAcceptControl() && cast<IView*>(control) != nullptr;
		}
	#pragma endregion

	#pragma region IMaterialControl methods
		bool CRimMaterial::Activate(COpenGL *graphics, IModel *model, ICamera *camera)
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			if (!m_pProgram)
			{
				if (!(m_pProgram = renderer->CreateProgram(shaders::rim::Vertex, shaders::rim::Fragment)))
					return false;
				renderer->ActivateProgram(m_pProgram);
				m_bProgramValid = true;
				if ((*reinterpret_cast<GLint*>(&m_hUniformMatrixModel) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_MatrixModel")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformMatrixNormal) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_MatrixNormal")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformMatrixCamera) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_MatrixCamera")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformHasTexture) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_HasTexture")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformAmbientColor) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_AmbientColor")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformDiffuseAlbedo) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_DiffuseAlbedo")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformSpecularAlbedo) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_SpecularAlbedo")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformRimColor) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_RimColor")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformLightPosition) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_LightPosition")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformCameraPosition) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_CameraPosition")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformShininess) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_Shininess")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformRimPower) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_RimPower")) < 0)
					m_bProgramValid = false;
				graphics->Uniform1i(graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_Texture"), 0);
			}
			bool result{ false };
			if (m_bProgramValid)
			{
				renderer->ActivateProgram(m_pProgram);
				graphics->UniformMatrix4fv(*reinterpret_cast<GLint*>(&m_hUniformMatrixModel), 1, GL_TRUE, model->getMatrix().Data);
				graphics->UniformMatrix3fv(*reinterpret_cast<GLint*>(&m_hUniformMatrixNormal), 1, GL_TRUE, model->getNormalMatrix().Data);
				graphics->UniformMatrix4fv(*reinterpret_cast<GLint*>(&m_hUniformMatrixCamera), 1, GL_TRUE, camera->getMatrix().Data);
				if (m_pTexture)
				{
					graphics->Uniform1i(*reinterpret_cast<GLint*>(&m_hUniformHasTexture), 1);
					graphics->ActiveTexture(GL_TEXTURE0);
					graphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_pTexture->Handle));
				}
				else
					graphics->Uniform1i(*reinterpret_cast<GLint*>(&m_hUniformHasTexture), 0);
				graphics->Uniform4f(*reinterpret_cast<GLint*>(&m_hUniformAmbientColor), m_sAmbientColor.R / 255.0f, m_sAmbientColor.G / 255.0f, m_sAmbientColor.B / 255.0f, m_sAmbientColor.A / 255.0f);
				graphics->Uniform4f(*reinterpret_cast<GLint*>(&m_hUniformDiffuseAlbedo),
					m_sDiffuseColor.R / 255.0f * m_sLightDiffuseColor.R / 255.0f,
					m_sDiffuseColor.G / 255.0f * m_sLightDiffuseColor.G / 255.0f,
					m_sDiffuseColor.B / 255.0f * m_sLightDiffuseColor.B / 255.0f,
					m_sDiffuseColor.A / 255.0f * m_sLightDiffuseColor.A / 255.0f);
				graphics->Uniform4f(*reinterpret_cast<GLint*>(&m_hUniformSpecularAlbedo),
					m_sSpecularColor.R / 255.0f * m_sLightSpecularColor.R / 255.0f,
					m_sSpecularColor.G / 255.0f * m_sLightSpecularColor.G / 255.0f,
					m_sSpecularColor.B / 255.0f * m_sLightSpecularColor.B / 255.0f,
					m_sSpecularColor.A / 255.0f * m_sLightSpecularColor.A / 255.0f);
				graphics->Uniform4f(*reinterpret_cast<GLint*>(&m_hUniformRimColor), m_sRimColor.R / 255.0f, m_sRimColor.G / 255.0f, m_sRimColor.B / 255.0f, m_sRimColor.A / 255.0f);
				graphics->Uniform3f(*reinterpret_cast<GLint*>(&m_hUniformLightPosition), m_sLightPosition.X, m_sLightPosition.Y, m_sLightPosition.Z);
				graphics->Uniform3f(*reinterpret_cast<GLint*>(&m_hUniformCameraPosition), camera->Position.X, camera->Position.Y, camera->Position.Z);
				graphics->Uniform1f(*reinterpret_cast<GLint*>(&m_hUniformShininess), m_fShininess);
				graphics->Uniform1f(*reinterpret_cast<GLint*>(&m_hUniformRimPower), m_fRimPower);
				result = true;
			}
			return result;
		}
	#pragma endregion

	#pragma region IRimMaterial getters
		ITexture *CRimMaterial::getTexture()
		{
			return m_pTexture;
		}

		Color CRimMaterial::getAmbientColor()
		{
			return m_sAmbientColor;
		}

		Color CRimMaterial::getDiffuseColor()
		{
			return m_sDiffuseColor;
		}

		Color CRimMaterial::getSpecularColor()
		{
			return m_sSpecularColor;
		}

		Color CRimMaterial::getRimColor()
		{
			return m_sRimColor;
		}

		Color CRimMaterial::getLightDiffuseColor()
		{
			return m_sLightDiffuseColor;
		}

		Color CRimMaterial::getLightSpecularColor()
		{
			return m_sLightSpecularColor;
		}

		Vec3f CRimMaterial::getLightPosition()
		{
			return m_sLightPosition;
		}

		float CRimMaterial::getLightX()
		{
			return m_sLightPosition.X;
		}

		float CRimMaterial::getLightY()
		{
			return m_sLightPosition.Y;
		}

		float CRimMaterial::getLightZ()
		{
			return m_sLightPosition.Z;
		}

		float CRimMaterial::getShininess()
		{
			return m_fShininess;
		}

		float CRimMaterial::getRimPower()
		{
			return m_fRimPower;
		}
	#pragma endregion

	#pragma region IRimMaterial setters
		bool CRimMaterial::setTexture(ITexture *value)
		{
			m_pTexture = value;
			QueryService()->SendChangeNotification();
			return true;
		}

		bool CRimMaterial::setAmbientColor(const Color &value)
		{
			if (value != m_sAmbientColor)
			{
				m_sAmbientColor = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CRimMaterial::setDiffuseColor(const Color &value)
		{
			if (value != m_sDiffuseColor)
			{
				m_sDiffuseColor = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CRimMaterial::setSpecularColor(const Color &value)
		{
			if (value != m_sSpecularColor)
			{
				m_sSpecularColor = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CRimMaterial::setRimColor(const Color &value)
		{
			if (value != m_sRimColor)
			{
				m_sRimColor = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CRimMaterial::setLightDiffuseColor(const Color &value)
		{
			if (value != m_sLightDiffuseColor)
			{
				m_sLightDiffuseColor = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CRimMaterial::setLightSpecularColor(const Color &value)
		{
			if (value != m_sLightSpecularColor)
			{
				m_sLightSpecularColor = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CRimMaterial::setLightPosition(const Vec3f &value)
		{
			if (ntl::IsNotEqual<float>(value, m_sLightPosition))
			{
				m_sLightPosition = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CRimMaterial::setLightX(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_sLightPosition.X))
			{
				m_sLightPosition.X = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CRimMaterial::setLightY(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_sLightPosition.Y))
			{
				m_sLightPosition.Y = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CRimMaterial::setLightZ(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_sLightPosition.Z))
			{
				m_sLightPosition.Z = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CRimMaterial::setShininess(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fShininess))
			{
				m_fShininess = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CRimMaterial::setRimPower(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fRimPower))
			{
				m_fRimPower = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}