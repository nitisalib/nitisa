// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace standard
	{
	#pragma region CGradientListener
		CContainer::CGradientListener::CGradientListener(CContainer *control) :
			m_pControl{ control }
		{

		}

		void CContainer::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient)
				m_pControl->Repaint(false);
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CContainer::CContainer() :
			CControl(L"Container", true, true, true, false, false, false),
			m_cGradientListener{ this },
			m_sBackgroundColor{ 0, 0, 0, 0 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_bUseMask{ true },
			m_pMask{ nullptr },
			m_sPadding{ 0, 0, 0, 0 },
			m_bOutlineInEditor{ true },
			m_bIgnoreGradient{ false }
		{
			setService(new CContainerService(this), true);
			setSize(PointF{ 185, 105 });
		}

		CContainer::CContainer(IForm *parent) :CContainer()
		{
			setForm(parent);
		}

		CContainer::CContainer(IControl *parent) : CContainer()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		IControl *CContainer::getControl(const int index)
		{
			return CControl::getControl(index);
		}

		IControl *CContainer::getControl(const String &name)
		{
			return CControl::getControl(name);
		}

		IControl *CContainer::getControl(const PointF &position)
		{
			IControl *result{ CControl::getControl(position) };
			if (m_bUseMask && result && result != this)
			{
				Vec4f v{  ntl::Inversed<float>(getTransformMatrix()) * Vec4f{ position.X, position.Y, 0, 1 } };
				RectF client{ getClientRect() };
				if (v.X < 0 || v.X >= getWidth() || v.Y < 0 || v.Y >= getHeight())
					result = nullptr;
				else if (v.X < client.Left || v.X >= client.Right || v.Y < client.Top || v.Y >= client.Bottom)
					result = this;
			}
			return result;
		}

		RectF CContainer::getClientRect()
		{
			RectF result{ m_sPadding.Left, m_sPadding.Top, getWidth() - m_sPadding.Right, getHeight() - m_sPadding.Bottom };
			result.validate();
			return result;
		}

		RectF CContainer::getPadding()
		{
			return m_sPadding;
		}
	#pragma endregion

	#pragma region Getters
		Color CContainer::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CContainer::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		bool CContainer::isUseMask() const
		{
			return m_bUseMask;
		}

		bool CContainer::isOutlineInEditor() const
		{
			return m_bOutlineInEditor;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CContainer::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				m_sPadding *= s;
				QueryService()->AlignControls();
				return true;
			}
			return false;
		}

		bool CContainer::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				CLockRepaint lock{ this };
				m_sPadding = value;
				QueryService()->AlignControls();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CContainer::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				if (m_cBackgroundGradient.getPointCount() < 2)
					Repaint(false);
				return true;
			}
			return false;
		}

		bool CContainer::setUseMask(const bool value)
		{
			if (value != m_bUseMask)
			{
				m_bUseMask = value;
				Repaint(true);
				return true;
			}
			return false;
		}

		bool CContainer::setOutlineInEditor(const bool value)
		{
			if (value != m_bOutlineInEditor)
			{
				m_bOutlineInEditor = value;
				if (Application->Editor)
					Repaint(true);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CContainer::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			m_bIgnoreGradient = false;
		}
	#pragma endregion

	#pragma region Paint
		void CContainer::Render(IRenderer *renderer, const Mat4f &matrix)
		{
			if (m_cBackgroundGradient.getPointCount() >= 2)
			{
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(matrix)
					->DrawGradient(RectF{ 0, 0, getWidth(), getHeight() }, m_cBackgroundGradient);
			}
			else if (m_sBackgroundColor.A > 0)
			{
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(matrix)
					->DrawRectangle(RectF{ 0, 0, getWidth(), getHeight() }, m_sBackgroundColor);
			}
			else if (m_bOutlineInEditor && Application->Editor)
			{
				CStoreBitmask s_bitmask{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ OutlineMask, 0, true, false })
					->ActivatePrimitiveMatrix(matrix)
					->DrawLines({ PointF{ 0, 0 }, PointF{ getWidth() - 1, 0 }, PointF{ getWidth() - 1, getHeight() - 1 }, PointF{ 1, getHeight() - 1 }, PointF{ 1, 0 } }, Color{ 0, 0, 0, 255 }, false);
			}
		}

		void CContainer::RenderMask(IRenderer *renderer, const Mat4f &matrix)
		{
			if (PrepareCanvas(renderer, &m_pMask, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pMask)
					->Clear(Color{ 0, 0, 0, 255 });
				m_pMask->setValid(true);
			}
		}
	#pragma endregion
	}
}