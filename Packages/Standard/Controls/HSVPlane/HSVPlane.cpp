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
		CHSVPlane::CHSVPlane() :
			CControl(L"HSVPlane", true, true, false, false, false, false),
			m_iHue{ 225 },
			m_fSaturation{ 0 },
			m_fValue{ 0 },
			m_fPickerRadius{ 5 },
			m_fPickerBorderWidth{ 1 },
			m_fPickerBorderRadius{ 5 },
			m_sPickerBorderColor{ 255, 255, 255, 255 },
			m_sPickerBorderColorInv{ 0, 0, 0, 255 },
			m_sPickerBackgroundColor{ 0, 0, 0, 0 },
			m_sPickerBackgroundColorInv{ 0, 0, 0, 0 },
			m_pCanvas{ nullptr },
			OnChange{ nullptr }
		{
			setService(new CHSVPlaneService(this), true);
			setSize(PointF{ 256, 256 });
		}

		CHSVPlane::CHSVPlane(IControl *parent) :CHSVPlane()
		{
			setParent(parent);
		}

		CHSVPlane::CHSVPlane(IForm *parent) : CHSVPlane()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		int CHSVPlane::getHue()
		{
			return m_iHue;
		}

		float CHSVPlane::getSaturation()
		{
			return m_fSaturation;
		}

		float CHSVPlane::getValue()
		{
			return m_fValue;
		}
	#pragma endregion

	#pragma region Getters
		float CHSVPlane::getPickerRadius() const
		{
			return m_fPickerRadius;
		}

		float CHSVPlane::getPickerBorderWidth() const
		{
			return m_fPickerBorderWidth;
		}

		float CHSVPlane::getPickerBorderRadius() const
		{
			return m_fPickerBorderRadius;
		}

		Color CHSVPlane::getPickerBorderColor() const
		{
			return m_sPickerBorderColor;
		}

		Color CHSVPlane::getPickerBorderColorInv() const
		{
			return m_sPickerBorderColorInv;
		}

		Color CHSVPlane::getPickerBackgroundColor() const
		{
			return m_sPickerBackgroundColor;
		}

		Color CHSVPlane::getPickerBackgroundColorInv() const
		{
			return m_sPickerBackgroundColorInv;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CHSVPlane::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_fPickerRadius *= avg;
				m_fPickerBorderWidth *= avg;
				m_fPickerBorderRadius *= avg;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CHSVPlane::setHue(const int value)
		{
			if (value >= 0 && value <= 360 && value != m_iHue)
			{
				m_iHue = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CHSVPlane::setSaturation(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsLessOrEqual<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fSaturation))
			{
				m_fSaturation = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CHSVPlane::setValue(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsLessOrEqual<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fValue))
			{
				m_fValue = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CHSVPlane::setPickerRadius(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fPickerRadius))
			{
				m_fPickerRadius = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CHSVPlane::setPickerBorderWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fPickerBorderWidth))
			{
				m_fPickerBorderWidth = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CHSVPlane::setPickerBorderRadius(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fPickerBorderRadius))
			{
				m_fPickerBorderRadius = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CHSVPlane::setPickerBorderColor(const Color &value)
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

		bool CHSVPlane::setPickerBorderColorInv(const Color &value)
		{
			if (value != m_sPickerBorderColorInv)
			{
				m_sPickerBorderColorInv = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CHSVPlane::setPickerBackgroundColor(const Color &value)
		{
			if (value != m_sPickerBackgroundColor)
			{
				m_sPickerBackgroundColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CHSVPlane::setPickerBackgroundColorInv(const Color &value)
		{
			if (value != m_sPickerBackgroundColorInv)
			{
				m_sPickerBackgroundColorInv = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CHSVPlane::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		void CHSVPlane::UpdateFromStyle(IStyle *style)
		{
			style->getOption(L"PickerRadius", m_fPickerRadius);
			style->getOption(L"PickerBorderWidth", m_fPickerBorderWidth);
			style->getOption(L"PickerBorderRadius", m_fPickerBorderRadius);
			style->getOption(L"PickerBorderColor", m_sPickerBorderColor);
			style->getOption(L"PickerBorderColorInv", m_sPickerBorderColorInv);
			style->getOption(L"PickerBackgroundColor", m_sPickerBackgroundColor);
			style->getOption(L"PickerBackgroundColorInv", m_sPickerBackgroundColorInv);
		}
	#pragma endregion

	#pragma region Paint
		void CHSVPlane::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			if (PrepareCanvas(renderer, &m_pCanvas, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 })
					->DrawHSVPlane(RectF{ 0, 0, getWidth(), getHeight() }, (float)m_iHue / 360.0f);
				if (ntl::IsGreater<float>(m_fPickerRadius, 0))
				{
					PointF center{ m_fSaturation * getWidth(), (1 - m_fValue) * getHeight() };
					if (center.X < getHeight() - center.Y && center.Y / getHeight() < 0.75f)
					{
						renderer->DrawBlock(
							RectF{ center.X - m_fPickerRadius, center.Y - m_fPickerRadius, center.X + m_fPickerRadius, center.Y + m_fPickerRadius },
							RectF{ m_fPickerBorderWidth, m_fPickerBorderWidth, m_fPickerBorderWidth, m_fPickerBorderWidth },
							RectF{ m_fPickerBorderRadius, m_fPickerBorderRadius, m_fPickerBorderRadius, m_fPickerBorderRadius },
							BlockColors{ m_sPickerBorderColorInv, m_sPickerBorderColorInv, m_sPickerBorderColorInv, m_sPickerBorderColorInv, m_sPickerBackgroundColorInv, Color{ 0, 0, 0, 0 } });
					}
					else
					{
						renderer->DrawBlock(
							RectF{ center.X - m_fPickerRadius, center.Y - m_fPickerRadius, center.X + m_fPickerRadius, center.Y + m_fPickerRadius },
							RectF{ m_fPickerBorderWidth, m_fPickerBorderWidth, m_fPickerBorderWidth, m_fPickerBorderWidth },
							RectF{ m_fPickerBorderRadius, m_fPickerBorderRadius, m_fPickerBorderRadius, m_fPickerBorderRadius },
							BlockColors{ m_sPickerBorderColor, m_sPickerBorderColor, m_sPickerBorderColor, m_sPickerBorderColor, m_sPickerBackgroundColor, Color{ 0, 0, 0, 0 } });
					}
				}
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}
	#pragma endregion
	}
}