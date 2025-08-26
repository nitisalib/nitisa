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
	#pragma region Constructor & destructor
		CHSVBar::CHSVBar() :
			CControl(L"HSVBar", true, true, false, false, false, false),
			m_iHue{ 225 },
			m_fPickerSize{ 8 },
			m_sPickerColor{ 255, 255, 255, 255 },
			m_sPickerBorderColor{ 0, 0, 0, 255 },
			m_pHSVPlane{ nullptr },
			m_pCanvas{ nullptr },
			OnChange{ nullptr }
		{
			setService(new CHSVBarService(this), true);
			setSize(PointF{ 40, 256 + m_fPickerSize });
		}

		CHSVBar::CHSVBar(IControl *parent) :CHSVBar()
		{
			setParent(parent);
		}

		CHSVBar::CHSVBar(IForm *parent) : CHSVBar()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		int CHSVBar::getHue()
		{
			return m_iHue;
		}

		IHSVPlane *CHSVBar::getHSVPlane()
		{
			return m_pHSVPlane;
		}
	#pragma endregion

	#pragma region Getters
		float CHSVBar::getPickerSize() const
		{
			return m_fPickerSize;
		}

		Color CHSVBar::getPickerColor() const
		{
			return m_sPickerColor;
		}

		Color CHSVBar::getPickerBorderColor() const
		{
			return m_sPickerBorderColor;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CHSVBar::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				m_fPickerSize *= (s.X + s.Y) * 0.5f;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CHSVBar::setHue(const int value)
		{
			if (value >= 0 && value <= 360 && value != m_iHue)
			{
				m_iHue = value;
				if (m_pHSVPlane)
					m_pHSVPlane->setHue(m_iHue);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CHSVBar::setHSVPlane(IHSVPlane *value)
		{
			if (value != m_pHSVPlane)
			{
				if (!value || (value && value->getForm() && value->getForm() == getForm()))
				{
					m_pHSVPlane = value;
					if (m_pHSVPlane)
						m_pHSVPlane->setHue(m_iHue);
					return true;
				}
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CHSVBar::setPickerSize(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fPickerSize))
			{
				m_fPickerSize = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CHSVBar::setPickerColor(const Color &value)
		{
			if (value != m_sPickerColor)
			{
				m_sPickerColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CHSVBar::setPickerBorderColor(const Color &value)
		{
			if (value != m_sPickerBorderColor)
			{
				m_sPickerBorderColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CHSVBar::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		void CHSVBar::UpdateFromStyle(IStyle *style)
		{
			style->getOption(L"PickerSize", m_fPickerSize);
			style->getOption(L"PickerColor", m_sPickerColor);
			style->getOption(L"PickerBorderColor", m_sPickerBorderColor);
		}
	#pragma endregion

	#pragma region Paint
		void CHSVBar::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			if (PrepareCanvas(renderer, &m_pCanvas, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });
				float h_size{ m_fPickerSize / 2 };
				Gradient g{ GradientType::Vertical, Color1DArray{ Color1D{0, Color{ 255, 255, 255, 255 } }, Color1D{ 1, Color{ 0, 255, 255, 255 } } } };
				renderer->DrawHSVGradient(RectF{ m_fPickerSize, h_size, getWidth() - m_fPickerSize, getHeight() - h_size }, g);
				if (ntl::IsGreater<float>(m_fPickerSize, 0))
				{
					ITexture *picker{ renderer->CreateTexture(ntl::Round<int>(m_fPickerSize), ntl::Round<int>(m_fPickerSize), 1, TextureFormat::RGBA, true) };
					if (picker)
					{
						renderer
							->ActivateTarget(picker)
							->Clear(Color{ 0, 0, 0, 0 })
							->DrawRectangle(RectF{ 0, 0, m_fPickerSize / 2, m_fPickerSize }, m_sPickerColor)
							->DrawTriangle(PointF{ m_fPickerSize / 2, 0 }, PointF{ m_fPickerSize, m_fPickerSize / 2 }, PointF{ m_fPickerSize / 2, m_fPickerSize }, m_sPickerColor)
							->DrawLines({
								PointF{ 1, 0 },
								PointF{ m_fPickerSize / 2, 0 },
								PointF{ m_fPickerSize, m_fPickerSize / 2 },
								PointF{ m_fPickerSize / 2, m_fPickerSize },
								PointF{ 0, m_fPickerSize - 1 } },
								m_sPickerBorderColor,
								true)
							->ActivateTarget(m_pCanvas);
						CStorePrimitiveMatrix s_matrix{ renderer };
						Mat4f m;
						ntl::Translate<float>(m, 0, std::round((1 - (float)m_iHue / 360.0f) * (getHeight() - m_fPickerSize)), 0);
						renderer
							->ActivatePrimitiveMatrix(&m)
							->DrawImage(picker, 1);
						Mat4f r;
						ntl::RotateZ<float>(r, ntl::Pi<float>);
						ntl::Translate<float>(m, std::round(getWidth()), std::round(m_fPickerSize + (1 - (float)m_iHue / 360.0f) * (getHeight() - m_fPickerSize)), 0);
						renderer
							->ActivatePrimitiveMatrix(m * r)
							->DrawImage(picker, 1);
						picker->Release();
					}
				}
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}
	#pragma endregion
	}
}