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
		CCustomMaterial::CCustomMaterial() :
			CControl(L"CustomMaterial", false, true, false, false, false, false),
			m_pTexture{ nullptr },
			m_bUseMatrixModel{ true },
			m_bUseMatrixCamera{ true },
			m_bUseHasTexture{ true },
			m_iLockCount{ 0 },
			m_bUpdateRequired{ false },
			m_pProgram{ nullptr },
			m_pGraphics{ nullptr }
		{
			OnActivateMaterial = nullptr;
			setService(new CCustomMaterialService(this), true);
		}

		CCustomMaterial::CCustomMaterial(IControl *parent) :CCustomMaterial()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IControl getters
		bool CCustomMaterial::isAcceptControl()
		{
			return CControl::isAcceptControl();
		}

		bool CCustomMaterial::isAcceptControl(IControl *control)
		{
			return CControl::isAcceptControl() && cast<IView*>(control) != nullptr;
		}
	#pragma endregion

	#pragma region IMaterialControl methods
		bool CCustomMaterial::Activate(COpenGL *graphics, IModel *model, ICamera *camera)
		{
			if (!m_pProgram)
				return false;
			if (m_pProgram)
			{
				getForm()->getRenderer()->ActivateProgram(m_pProgram);
				for (auto &option : m_aOptions)
					if (option.Type == OptionType::Mat4 && option.Name == L"app_MatrixModel" && option.UniformLocation >= 0)
						graphics->UniformMatrix4fv(option.UniformLocation, 1, GL_FALSE, model->getMatrix().Data);
					else if (option.Type == OptionType::Mat4 && option.Name == L"app_MatrixCamera" && option.UniformLocation >= 0)
						graphics->UniformMatrix4fv(option.UniformLocation, 1, GL_FALSE, camera->getMatrix().Data);
					else if (option.Type == OptionType::Integer && option.Name == L"app_HasTexture" && option.UniformLocation >= 0)
					{
						if (m_pTexture)
						{
							graphics->Uniform1i(option.UniformLocation, 1);
							graphics->ActiveTexture(GL_TEXTURE0);
							graphics->BindTexture(GL_TEXTURE_2D, *reinterpret_cast<const GLuint*>(&m_pTexture->Handle));
						}
						else
							graphics->Uniform1i(option.UniformLocation, 0);
					}
				if (OnActivateMaterial)
					OnActivateMaterial(this);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region ICustomMaterial getters
		ITexture *CCustomMaterial::getTexture()
		{
			return m_pTexture;
		}

		AnsiString CCustomMaterial::getVertexShader()
		{
			return m_sVertexShader;
		}

		AnsiString CCustomMaterial::getFragmentShader()
		{
			return m_sFragmentShader;
		}

		int CCustomMaterial::getOptionCount()
		{
			return (int)m_aOptions.size();
		}

		String CCustomMaterial::getOptionName(const int index)
		{
			if (index >= 0 && index < (int)m_aOptions.size())
				return m_aOptions[index].Name;
			return L"";
		}

		ICustomMaterial::OptionType CCustomMaterial::getOptionType(const int index)
		{
			if (index >= 0 && index < (int)m_aOptions.size())
				return m_aOptions[index].Type;
			return OptionType::None;
		}

		int CCustomMaterial::getIntegerOptionValue(const int index)
		{
			if (index >= 0 && index < (int)m_aOptions.size() && m_aOptions[index].Type == OptionType::Integer)
				return m_aOptions[index].ValueInteger;
			return 0;
		}

		float CCustomMaterial::getFloatOptionValue(const int index)
		{
			if (index >= 0 && index < (int)m_aOptions.size() && m_aOptions[index].Type == OptionType::Float)
				return m_aOptions[index].ValueFloat;
			return 0;
		}

		Vec2f CCustomMaterial::getVec2OptionValue(const int index)
		{
			if (index >= 0 && index < (int)m_aOptions.size() && m_aOptions[index].Type == OptionType::Vec2)
				return m_aOptions[index].ValueVec2;
			return Vec2f{ 0, 0 };
		}

		Vec3f CCustomMaterial::getVec3OptionValue(const int index)
		{
			if (index >= 0 && index < (int)m_aOptions.size() && m_aOptions[index].Type == OptionType::Vec3)
				return m_aOptions[index].ValueVec3;
			return Vec3f{ 0, 0, 0 };
		}

		Vec4f CCustomMaterial::getVec4OptionValue(const int index)
		{
			if (index >= 0 && index < (int)m_aOptions.size() && m_aOptions[index].Type == OptionType::Vec4)
				return m_aOptions[index].ValueVec4;
			return Vec4f{ 0, 0, 0, 0 };
		}

		Vec2i CCustomMaterial::getVec2iOptionValue(const int index)
		{
			if (index >= 0 && index < (int)m_aOptions.size() && m_aOptions[index].Type == OptionType::Vec2i)
				return m_aOptions[index].ValueVec2i;
			return Vec2i{ 0, 0 };
		}

		Vec3i CCustomMaterial::getVec3iOptionValue(const int index)
		{
			if (index >= 0 && index < (int)m_aOptions.size() && m_aOptions[index].Type == OptionType::Vec3i)
				return m_aOptions[index].ValueVec3i;
			return Vec3i{ 0, 0, 0 };
		}

		Vec4i CCustomMaterial::getVec4iOptionValue(const int index)
		{
			if (index >= 0 && index < (int)m_aOptions.size() && m_aOptions[index].Type == OptionType::Vec4i)
				return m_aOptions[index].ValueVec4i;
			return Vec4i{ 0, 0, 0, 0 };
		}

		Mat4f CCustomMaterial::getMat4OptionValue(const int index)
		{
			if (index >= 0 && index < (int)m_aOptions.size() && m_aOptions[index].Type == OptionType::Mat4)
				return m_aOptions[index].ValueMat4;
			return Identity;
		}
	#pragma endregion

	#pragma region ICustomMaterial setters
		bool CCustomMaterial::setTexture(ITexture *value)
		{
			LockUpdate();
			m_pTexture = value;
			m_bUpdateRequired = true;
			UnlockUpdate();
			return true;
		}

		bool CCustomMaterial::setVertexShader(const AnsiString &value)
		{
			if (value != m_sVertexShader)
			{
				m_sVertexShader = value;
				if (!BuildProgram())
					return false;
				LockUpdate();
				m_bUpdateRequired = true;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomMaterial::setFragmentShader(const AnsiString &value)
		{
			if (value != m_sFragmentShader)
			{
				m_sFragmentShader = value;
				if (!BuildProgram())
					return false;
				LockUpdate();
				m_bUpdateRequired = true;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomMaterial::setShaders(const AnsiString &vertex, const AnsiString &fragment)
		{
			if (vertex != m_sVertexShader || fragment != m_sFragmentShader)
			{
				m_sVertexShader = vertex;
				m_sFragmentShader = fragment;
				if (!BuildProgram())
					return false;
				LockUpdate();
				m_bUpdateRequired = true;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomMaterial::setOption(const String &name, const int value)
		{
			if (m_pProgram && !name.empty())
			{
				CProgramLock lock{ this };
				for (auto &option : m_aOptions)
					if (option.Name == name)
					{
						if (option.Type != OptionType::Integer || value == option.ValueInteger)
							return false;
						option.ValueInteger = value;
						m_pGraphics->Uniform1i(option.UniformLocation, value);
						return true;
					}
				OPTION option;
				option.UniformLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), StringToAnsi(name).c_str());
				if (option.UniformLocation < 0)
					return false;
				option.Name = name;
				option.Type = OptionType::Integer;
				option.ValueInteger = value;
				m_aOptions.push_back(option);
				m_pGraphics->Uniform1i(option.UniformLocation, value);
				LockUpdate();
				m_bUpdateRequired = true;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomMaterial::setOption(const String &name, const float value)
		{
			if (m_pProgram && !name.empty())
			{
				CProgramLock lock{ this };
				for (auto &option : m_aOptions)
					if (option.Name == name)
					{
						if (option.Type != OptionType::Float || ntl::IsEqual<float>(value, option.ValueFloat))
							return false;
						option.ValueFloat = value;
						m_pGraphics->Uniform1f(option.UniformLocation, value);
						return true;
					}
				OPTION option;
				option.UniformLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), StringToAnsi(name).c_str());
				if (option.UniformLocation < 0)
					return false;
				option.Name = name;
				option.Type = OptionType::Float;
				option.ValueFloat = value;
				m_aOptions.push_back(option);
				m_pGraphics->Uniform1f(option.UniformLocation, value);
				LockUpdate();
				m_bUpdateRequired = true;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomMaterial::setOption(const String &name, const Vec2f &value)
		{
			if (m_pProgram && !name.empty())
			{
				CProgramLock lock{ this };
				for (auto &option : m_aOptions)
					if (option.Name == name)
					{
						if (option.Type != OptionType::Vec2 || ntl::IsEqual<float>(value, option.ValueVec2, ntl::Tolerance<float>))
							return false;
						option.ValueVec2 = value;
						m_pGraphics->Uniform2f(option.UniformLocation, value.X, value.Y);
						return true;
					}
				OPTION option;
				option.UniformLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), StringToAnsi(name).c_str());
				if (option.UniformLocation < 0)
					return false;
				option.Name = name;
				option.Type = OptionType::Vec2;
				option.ValueVec2 = value;
				m_aOptions.push_back(option);
				m_pGraphics->Uniform2f(option.UniformLocation, value.X, value.Y);
				LockUpdate();
				m_bUpdateRequired = true;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomMaterial::setOption(const String &name, const Vec3f &value)
		{
			if (m_pProgram && !name.empty())
			{
				CProgramLock lock{ this };
				for (auto &option : m_aOptions)
					if (option.Name == name)
					{
						if (option.Type != OptionType::Vec3 || ntl::IsEqual<float>(value, option.ValueVec3, ntl::Tolerance<float>))
							return false;
						option.ValueVec3 = value;
						m_pGraphics->Uniform3f(option.UniformLocation, value.X, value.Y, value.Z);
						return true;
					}
				OPTION option;
				option.UniformLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), StringToAnsi(name).c_str());
				if (option.UniformLocation < 0)
					return false;
				option.Name = name;
				option.Type = OptionType::Vec3;
				option.ValueVec3 = value;
				m_aOptions.push_back(option);
				m_pGraphics->Uniform3f(option.UniformLocation, value.X, value.Y, value.Z);
				LockUpdate();
				m_bUpdateRequired = true;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomMaterial::setOption(const String &name, const Vec4f &value)
		{
			if (m_pProgram && !name.empty())
			{
				CProgramLock lock{ this };
				for (auto &option : m_aOptions)
					if (option.Name == name)
					{
						if (option.Type != OptionType::Vec4 || ntl::IsEqual<float>(value, option.ValueVec4, ntl::Tolerance<float>))
							return false;
						option.ValueVec4 = value;
						m_pGraphics->Uniform4f(option.UniformLocation, value.X, value.Y, value.Z, value.W);
						return true;
					}
				OPTION option;
				option.UniformLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), StringToAnsi(name).c_str());
				if (option.UniformLocation < 0)
					return false;
				option.Name = name;
				option.Type = OptionType::Vec4;
				option.ValueVec4 = value;
				m_aOptions.push_back(option);
				m_pGraphics->Uniform4f(option.UniformLocation, value.X, value.Y, value.Z, value.W);
				LockUpdate();
				m_bUpdateRequired = true;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomMaterial::setOption(const String &name, const Vec2i &value)
		{
			if (m_pProgram && !name.empty())
			{
				CProgramLock lock{ this };
				for (auto &option : m_aOptions)
					if (option.Name == name)
					{
						if (option.Type != OptionType::Vec2i || value == option.ValueVec2i)
							return false;
						option.ValueVec2i = value;
						m_pGraphics->Uniform2i(option.UniformLocation, value.X, value.Y);
						return true;
					}
				OPTION option;
				option.UniformLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), StringToAnsi(name).c_str());
				if (option.UniformLocation < 0)
					return false;
				option.Name = name;
				option.Type = OptionType::Vec2i;
				option.ValueVec2i = value;
				m_aOptions.push_back(option);
				m_pGraphics->Uniform2i(option.UniformLocation, value.X, value.Y);
				LockUpdate();
				m_bUpdateRequired = true;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomMaterial::setOption(const String &name, const Vec3i &value)
		{
			if (m_pProgram && !name.empty())
			{
				CProgramLock lock{ this };
				for (auto &option : m_aOptions)
					if (option.Name == name)
					{
						if (option.Type != OptionType::Vec3i || value == option.ValueVec3i)
							return false;
						option.ValueVec3i = value;
						m_pGraphics->Uniform3i(option.UniformLocation, value.X, value.Y, value.Z);
						return true;
					}
				OPTION option;
				option.UniformLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), StringToAnsi(name).c_str());
				if (option.UniformLocation < 0)
					return false;
				option.Name = name;
				option.Type = OptionType::Vec3i;
				option.ValueVec3i = value;
				m_aOptions.push_back(option);
				m_pGraphics->Uniform3i(option.UniformLocation, value.X, value.Y, value.Z);
				LockUpdate();
				m_bUpdateRequired = true;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomMaterial::setOption(const String &name, const Vec4i &value)
		{
			if (m_pProgram && !name.empty())
			{
				CProgramLock lock{ this };
				for (auto &option : m_aOptions)
					if (option.Name == name)
					{
						if (option.Type != OptionType::Vec4i || value == option.ValueVec4i)
							return false;
						option.ValueVec4i = value;
						m_pGraphics->Uniform4i(option.UniformLocation, value.X, value.Y, value.Z, value.W);
						return true;
					}
				OPTION option;
				option.UniformLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), StringToAnsi(name).c_str());
				if (option.UniformLocation < 0)
					return false;
				option.Name = name;
				option.Type = OptionType::Vec4i;
				option.ValueVec4i = value;
				m_aOptions.push_back(option);
				m_pGraphics->Uniform4i(option.UniformLocation, value.X, value.Y, value.Z, value.W);
				LockUpdate();
				m_bUpdateRequired = true;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomMaterial::setOption(const String &name, const Mat4f &value)
		{
			if (m_pProgram && !name.empty())
			{
				CProgramLock lock{ this };
				for (auto &option : m_aOptions)
					if (option.Name == name)
					{
						if (option.Type != OptionType::Mat4 || ntl::IsEqual<float>(value, option.ValueMat4, ntl::Tolerance<float>))
							return false;
						option.ValueMat4 = value;
						m_pGraphics->UniformMatrix4fv(option.UniformLocation, 1, GL_TRUE, value.Data);
						return true;
					}
				OPTION option;
				option.UniformLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), StringToAnsi(name).c_str());
				if (option.UniformLocation < 0)
					return false;
				option.Name = name;
				option.Type = OptionType::Mat4;
				option.ValueMat4 = value;
				m_aOptions.push_back(option);
				m_pGraphics->UniformMatrix4fv(option.UniformLocation, 1, GL_TRUE, value.Data);
				LockUpdate();
				m_bUpdateRequired = true;
				UnlockUpdate();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Load shaders
		bool CCustomMaterial::LoadVertexShader(const String &filename)
		{
			m_sVertexShader = GetAnsiFileContent(filename);
			if (BuildProgram())
			{
				LockUpdate();
				m_bUpdateRequired = true;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomMaterial::LoadFragmentShader(const String &filename)
		{
			m_sFragmentShader = GetAnsiFileContent(filename);
			if (BuildProgram())
			{
				LockUpdate();
				m_bUpdateRequired = true;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CCustomMaterial::LoadShaders(const String &vertex_filename, const String &fragment_filename)
		{
			m_sVertexShader = GetAnsiFileContent(vertex_filename);
			m_sFragmentShader = GetAnsiFileContent(fragment_filename);
			if (BuildProgram())
			{
				LockUpdate();
				m_bUpdateRequired = true;
				UnlockUpdate();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Lock/Unlock update
		void CCustomMaterial::LockUpdate()
		{
			if (m_iLockCount == 0)
				m_bUpdateRequired = false;
			m_iLockCount++;
		}

		void CCustomMaterial::UnlockUpdate()
		{
			if (m_iLockCount == 0)
				return;
			if (--m_iLockCount == 0 && m_bUpdateRequired)
				QueryService()->SendChangeNotification();
		}
	#pragma endregion

	#pragma region Helpers
		bool CCustomMaterial::BuildProgram()
		{
			// Check there is proper native graphics
			if (!getForm() || !getForm()->getRenderer())
				return false;
			IRenderer *renderer{ getForm()->getRenderer() };
			m_pGraphics = cast<COpenGL*>(renderer->NativeGraphics);
			if (!m_pGraphics)
				return false;
			// Delete program if exists
			if (m_pProgram)
			{
				m_pProgram->Release();
				m_pProgram = nullptr;
			}
			// Try to create a program
			if (!(m_pProgram = renderer->CreateProgram(m_sVertexShader, m_sFragmentShader)))
				return false;
			CProgramLock lock{ this };
			// Check existing options are exists in the new program and get their locations
			std::vector<OPTION> options;
			bool has_matrix_model{ false }, has_matrix_camera{ false }, has_has_texture{ false };
			for (auto &option : m_aOptions)
			{
				if (option.Name == L"app_MatrixModel")
				{
					has_matrix_model = true;
					if (!m_bUseMatrixModel)
						continue;
				}
				if (option.Name == L"app_MatrixCamera")
				{
					has_matrix_camera = true;
					if (!m_bUseMatrixCamera)
						continue;
				}
				if (option.Name == L"app_HasTexture")
				{
					has_has_texture = true;
					if (!m_bUseHasTexture)
						continue;
				}
				option.UniformLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), StringToAnsi(option.Name).c_str());
				if (option.UniformLocation >= 0)
					options.push_back(option);
			}
			// Add missing predefined options if needed
			if (m_bUseMatrixModel && !has_matrix_model)
			{
				OPTION option;
				option.UniformLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_MatrixModel");
				if (option.UniformLocation >= 0)
				{
					option.Name = L"app_MatrixModel";
					option.Type = OptionType::Mat4;
					ntl::Identity<float>(option.ValueMat4);
					options.push_back(option);
				}
			}
			if (m_bUseMatrixCamera && !has_matrix_camera)
			{
				OPTION option;
				option.UniformLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_MatrixCamera");
				if (option.UniformLocation >= 0)
				{
					option.Name = L"app_MatrixCamera";
					option.Type = OptionType::Mat4;
					ntl::Identity<float>(option.ValueMat4);
					options.push_back(option);
				}
			}
			if (m_bUseHasTexture && !has_has_texture)
			{
				OPTION option;
				option.UniformLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_HasTexture");
				if (option.UniformLocation >= 0)
				{
					option.Name = L"app_HasTexture";
					option.Type = OptionType::Integer;
					option.ValueInteger = 0;
					options.push_back(option);
				}
			}
			// Send option values into a new program
			m_aOptions = options;
			for (auto &option : m_aOptions)
				switch (option.Type)
				{
				case OptionType::Integer:
					m_pGraphics->Uniform1i(option.UniformLocation, option.ValueInteger);
					break;
				case OptionType::Float:
					m_pGraphics->Uniform1f(option.UniformLocation, option.ValueFloat);
					break;
				case OptionType::Vec2:
					m_pGraphics->Uniform2f(option.UniformLocation, option.ValueVec2.X, option.ValueVec2.Y);
					break;
				case OptionType::Vec3:
					m_pGraphics->Uniform3f(option.UniformLocation, option.ValueVec3.X, option.ValueVec3.Y, option.ValueVec3.Z);
					break;
				case OptionType::Vec4:
					m_pGraphics->Uniform4f(option.UniformLocation, option.ValueVec4.X, option.ValueVec4.Y, option.ValueVec4.Z, option.ValueVec4.W);
					break;
				case OptionType::Vec2i:
					m_pGraphics->Uniform2i(option.UniformLocation, option.ValueVec2i.X, option.ValueVec2i.Y);
					break;
				case OptionType::Vec3i:
					m_pGraphics->Uniform3i(option.UniformLocation, option.ValueVec3i.X, option.ValueVec3i.Y, option.ValueVec3i.Z);
					break;
				case OptionType::Vec4i:
					m_pGraphics->Uniform4i(option.UniformLocation, option.ValueVec4i.X, option.ValueVec4i.Y, option.ValueVec4i.Z, option.ValueVec4i.W);
					break;
				case OptionType::Mat4:
					m_pGraphics->UniformMatrix4fv(option.UniformLocation, 1, GL_TRUE, option.ValueMat4.Data);
					break;
				}
			return true;
		}
	#pragma endregion

	#pragma region Getters
		bool CCustomMaterial::isUseMatrixModel() const
		{
			return m_bUseMatrixModel;
		}

		bool CCustomMaterial::isUseMatrixCamera() const
		{
			return m_bUseMatrixCamera;
		}

		bool CCustomMaterial::isUseHasTexture() const
		{
			return m_bUseHasTexture;
		}
	#pragma endregion

	#pragma region Setters
		bool CCustomMaterial::setUseMatrixModel(const bool value)
		{
			if (value != m_bUseMatrixModel)
			{
				m_bUseMatrixModel = value;
				bool found{ false };
				for (auto pos = m_aOptions.begin(); pos != m_aOptions.end(); pos++)
					if (pos->Name == L"app_MatrixModel")
					{
						if (!m_bUseMatrixModel)
						{
							m_aOptions.erase(pos);
							return true;
						}
						found = true;
						break;
					}
				if (m_bUseMatrixModel && !found && m_pProgram)
				{
					OPTION option;
					option.UniformLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_MatrixModel");
					if (option.UniformLocation < 0)
						return false;
					CProgramLock lock{ this };
					option.Name = L"app_MatrixModel";
					option.Type = OptionType::Mat4;
					ntl::Identity<float>(option.ValueMat4);
					m_pGraphics->UniformMatrix4fv(option.UniformLocation, 1, GL_TRUE, option.ValueMat4.Data);
					m_aOptions.push_back(option);
				}
				return true;
			}
			return false;
		}

		bool CCustomMaterial::setUseMatrixCamera(const bool value)
		{
			if (value != m_bUseMatrixCamera)
			{
				m_bUseMatrixModel = value;
				bool found{ false };
				for (auto pos = m_aOptions.begin(); pos != m_aOptions.end(); pos++)
					if (pos->Name == L"app_MatrixCamera")
					{
						if (!m_bUseMatrixCamera)
						{
							m_aOptions.erase(pos);
							return true;
						}
						found = true;
						break;
					}
				if (m_bUseMatrixCamera && !found && m_pProgram)
				{
					OPTION option;
					option.UniformLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_MatrixCamera");
					if (option.UniformLocation < 0)
						return false;
					CProgramLock lock{ this };
					option.Name = L"app_MatrixCamera";
					option.Type = OptionType::Mat4;
					ntl::Identity<float>(option.ValueMat4);
					m_pGraphics->UniformMatrix4fv(option.UniformLocation, 1, GL_TRUE, option.ValueMat4.Data);
					m_aOptions.push_back(option);
				}
				return true;
			}
			return false;
		}

		bool CCustomMaterial::setUseHasTexture(const bool value)
		{
			if (value != m_bUseHasTexture)
			{
				m_bUseHasTexture = value;
				bool found{ false };
				for (auto pos = m_aOptions.begin(); pos != m_aOptions.end(); pos++)
					if (pos->Name == L"app_HasTexture")
					{
						if (!m_bUseHasTexture)
						{
							m_aOptions.erase(pos);
							return true;
						}
						found = true;
						break;
					}
				if (m_bUseHasTexture && !found && m_pProgram)
				{
					OPTION option;
					option.UniformLocation = m_pGraphics->GetUniformLocation(*reinterpret_cast<const GLuint*>(&m_pProgram->Handle), "app_HasTexture");
					if (option.UniformLocation < 0)
						return false;
					CProgramLock lock{ this };
					option.Name = L"app_HasTexture";
					option.Type = OptionType::Integer;
					option.ValueInteger = 0;
					m_pGraphics->Uniform1i(option.UniformLocation, option.ValueInteger);
					m_aOptions.push_back(option);
				}
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}