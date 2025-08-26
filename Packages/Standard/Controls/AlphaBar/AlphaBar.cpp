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
		CAlphaBar::CAlphaBar() :
			CControl(L"AlphaBar", true, true, false, false, false, false),
			m_iAlpha{ 127 },
			m_fPickerSize{ 8 },
			m_sPickerColor{ 255, 255, 255, 255 },
			m_sPickerBorderColor{ 0, 0, 0, 255 },
			m_sCheckerColor1{ 0, 0, 0, 0 },
			m_sCheckerColor2{ 0, 0, 0, 32 },
			m_sBackgroundColor{ 0, 0, 0, 0 },
			m_sForegroundColor1{ 255, 255, 255, 200 },
			m_sForegroundColor2{ 0, 0, 0, 255 },
			m_fCheckerSize{ 8 },
			m_pCanvas{ nullptr },
			OnChange{ nullptr }
		{
			setService(new CAlphaBarService(this), true);
			setSize(PointF{ 40, 256 + m_fPickerSize });
		}

		CAlphaBar::CAlphaBar(IControl *parent) :CAlphaBar()
		{
			setParent(parent);
		}

		CAlphaBar::CAlphaBar(IForm *parent) : CAlphaBar()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region IControl methods
		void CAlphaBar::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region Interface getters
		int CAlphaBar::getAlpha()
		{
			return m_iAlpha;
		}
	#pragma endregion

	#pragma region Getters
		float CAlphaBar::getPickerSize() const
		{
			return m_fPickerSize;
		}

		Color CAlphaBar::getPickerColor() const
		{
			return m_sPickerColor;
		}

		Color CAlphaBar::getPickerBorderColor() const
		{
			return m_sPickerBorderColor;
		}

		Color CAlphaBar::getCheckerColor1() const
		{
			return m_sCheckerColor1;
		}

		Color CAlphaBar::getCheckerColor2() const
		{
			return m_sCheckerColor2;
		}

		Color CAlphaBar::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Color CAlphaBar::getForegroundColor1() const
		{
			return m_sForegroundColor1;
		}

		Color CAlphaBar::getForegroundColor2() const
		{
			return m_sForegroundColor2;
		}

		float CAlphaBar::getCheckerSize() const
		{
			return m_fCheckerSize;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CAlphaBar::setDPI(const Point &value)
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

		bool CAlphaBar::setAlpha(const int value)
		{
			if (value >= 0 && value <= 255 && value != m_iAlpha)
			{
				m_iAlpha = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CAlphaBar::setPickerSize(const float value)
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

		bool CAlphaBar::setPickerColor(const Color &value)
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

		bool CAlphaBar::setPickerBorderColor(const Color &value)
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

		bool CAlphaBar::setCheckerColor1(const Color &value)
		{
			if (value != m_sCheckerColor1)
			{
				m_sCheckerColor1 = value;
				if (m_sBackgroundColor.A == 0 && m_pCanvas)
				{
					m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CAlphaBar::setCheckerColor2(const Color &value)
		{
			if (value != m_sCheckerColor2)
			{
				m_sCheckerColor2 = value;
				if (m_sBackgroundColor.A == 0 && m_pCanvas)
				{
					m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CAlphaBar::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CAlphaBar::setForegroundColor1(const Color &value)
		{
			if (value != m_sForegroundColor1)
			{
				m_sForegroundColor1 = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CAlphaBar::setForegroundColor2(const Color &value)
		{
			if (value != m_sForegroundColor2)
			{
				m_sForegroundColor2 = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CAlphaBar::setCheckerSize(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fCheckerSize))
			{
				m_fCheckerSize = value;
				if (m_sBackgroundColor.A == 0 && m_pCanvas)
				{
					m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CAlphaBar::UpdateFromStyle(IStyle *style)
		{
			style->getOption(L"PickerSize", m_fPickerSize);
			style->getOption(L"PickerColor", m_sPickerColor);
			style->getOption(L"PickerBorderColor", m_sPickerBorderColor);
			style->getOption(L"CheckerColor1", m_sCheckerColor1);
			style->getOption(L"CheckerColor2", m_sCheckerColor2);
			style->getOption(L"BackgroundColor", m_sBackgroundColor);
			style->getOption(L"ForegroundColor1", m_sForegroundColor1);
			style->getOption(L"ForegroundColor2", m_sForegroundColor2);
			style->getOption(L"CheckerSize", m_fCheckerSize);
		}
	#pragma endregion

	#pragma region Paint
		void CAlphaBar::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			if (PrepareCanvas(renderer, &m_pCanvas, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });
				RectF r{ m_fPickerSize, m_fPickerSize / 2, getWidth() - m_fPickerSize, getHeight() - m_fPickerSize / 2 };
				if (r.is_valid() && !r.is_zero())
				{
					if (m_sBackgroundColor.A > 0)
						renderer->DrawRectangle(r, m_sBackgroundColor);
					else if (m_sCheckerColor1.A > 0 || m_sCheckerColor2.A > 0)
					{
						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(r.Left, r.Top, 0))
							->DrawChecker(RectF{ 0, 0, r.width(), r.height() }, PointF{ m_fCheckerSize, m_fCheckerSize }, m_sCheckerColor1, m_sCheckerColor2);
					}
					if (m_sForegroundColor1.A > 0 || m_sForegroundColor2.A > 0)
					{
						Gradient g;
						g.setType(GradientType::Vertical);
						g.setPoints(Color1DArray{ Color1D{ 0, m_sForegroundColor1 }, Color1D{ 1, m_sForegroundColor2 } });
						renderer->DrawGradient(RectF{ r.Left, r.Top + (1 - (float)m_iAlpha / 255.0f) * r.height(), r.Right, r.Bottom }, g);
					}
				}
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
							->DrawLines({ PointF{ 1, 0 }, PointF{ m_fPickerSize / 2, 0 }, PointF{ m_fPickerSize, m_fPickerSize / 2 }, PointF{ m_fPickerSize / 2, m_fPickerSize },
								PointF{ 0, m_fPickerSize - 1 } }, m_sPickerBorderColor, true)
							->ActivateTarget(m_pCanvas);
						CStorePrimitiveMatrix s_matrix{ renderer };
						Mat4f m;
						ntl::Translate<float>(m, 0, std::round((1 - (float)m_iAlpha / 255.0f) * (getHeight() - m_fPickerSize)), 0);
						renderer
							->ActivatePrimitiveMatrix(m)
							->DrawImage(picker, 1);
						Mat4f r;
						ntl::RotateZ<float>(r, ntl::Pi<float>);
						ntl::Translate<float>(m, std::round(getWidth()), std::round(m_fPickerSize + (1 - (float)m_iAlpha / 255.0f) * (getHeight() - m_fPickerSize)), 0);
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