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
		CCheckerMaterial::CCheckerMaterial() :
			CControl(L"CheckerMaterial", false, true, false, false, false, false),
			m_sColor1{ 0, 0, 0, 255 },
			m_sColor2{ 255, 255, 255, 255 },
			m_sScale{ 1, 1 },
			m_pProgram{ nullptr },
			m_bProgramValid{ false }
		{
			setService(new CCheckerMaterialService(this), true);
		}

		CCheckerMaterial::CCheckerMaterial(IControl *parent) :CCheckerMaterial()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IControl getters
		bool CCheckerMaterial::isAcceptControl()
		{
			return CControl::isAcceptControl();
		}

		bool CCheckerMaterial::isAcceptControl(IControl *control)
		{
			return CControl::isAcceptControl() && cast<IView*>(control) != nullptr;
		}
	#pragma endregion

	#pragma region IMaterialControl methods
		bool CCheckerMaterial::Activate(COpenGL *graphics, IModel *model, ICamera *camera)
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			if (!m_pProgram)
			{
				if (!(m_pProgram = renderer->CreateProgram(shaders::checker::Vertex, shaders::checker::Fragment)))
					return false;
				renderer->ActivateProgram(m_pProgram);
				m_bProgramValid = true;
				if ((*reinterpret_cast<GLint*>(&m_hUniformMatrix) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_Matrix")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformColor1) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_Color1")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformColor2) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_Color2")) < 0)
					m_bProgramValid = false;
				if ((*reinterpret_cast<GLint*>(&m_hUniformScale) = graphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_Scale")) < 0)
					m_bProgramValid = false;
			}
			bool result{ false };
			if (m_bProgramValid)
			{
				renderer->ActivateProgram(m_pProgram);
				graphics->UniformMatrix4fv(*reinterpret_cast<GLint*>(&m_hUniformMatrix), 1, GL_TRUE, (camera->getMatrix() * model->getMatrix()).Data);
				graphics->Uniform4f(*reinterpret_cast<GLint*>(&m_hUniformColor1), m_sColor1.R / 255.0f, m_sColor1.G / 255.0f, m_sColor1.B / 255.0f, m_sColor1.A / 255.0f);
				graphics->Uniform4f(*reinterpret_cast<GLint*>(&m_hUniformColor2), m_sColor2.R / 255.0f, m_sColor2.G / 255.0f, m_sColor2.B / 255.0f, m_sColor2.A / 255.0f);
				graphics->Uniform2f(*reinterpret_cast<GLint*>(&m_hUniformScale), m_sScale.X, m_sScale.Y);
				result = true;
			}
			return result;
		}
	#pragma endregion

	#pragma region ICheckerMaterial getters
		Color CCheckerMaterial::getColor1()
		{
			return m_sColor1;
		}

		Color CCheckerMaterial::getColor2()
		{
			return m_sColor2;
		}

		PointF CCheckerMaterial::getScale()
		{
			return m_sScale;
		}
	#pragma endregion

	#pragma region ICheckerMaterial setters
		bool CCheckerMaterial::setColor1(const Color &value)
		{
			if (value != m_sColor1)
			{
				m_sColor1 = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCheckerMaterial::setColor2(const Color &value)
		{
			if (value != m_sColor2)
			{
				m_sColor2 = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CCheckerMaterial::setScale(const PointF &value)
		{
			if (ntl::IsNotZero<float>(ntl::Abs<float>(value.X)) && ntl::IsNotZero<float>(ntl::Abs<float>(value.Y)) && IsNotEqual(value, m_sScale))
			{
				m_sScale = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}