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
		CLabel::CLabel() :
			CControl(L"Label", true, true, false, false, false, false),
			m_eCaptionHorizontalAlign{ TextAlign::Left },
			m_eCaptionVerticalAlign{ VerticalAlign::Middle },
			m_bAutoSize{ true },
			m_bMultiline{ false },
			m_aColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 133, 135, 139, 255 } },
			m_aShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aShadowRadius{ 1, 1, 1 },
			m_pCanvas{ nullptr },
			m_bCaptionChanged{ false }
			
		{
			setService(new CLabelService(this), true);
		}

		CLabel::CLabel(IControl *parent) : CLabel()
		{
			setParent(parent);
		}

		CLabel::CLabel(IForm *parent) : CLabel()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region CControl getters
		RectF CLabel::getRenderRect()
		{
			RectF result{ getRenderRect(State::Normal) };
			for (int i = (int)State::Normal + 1; i <= (int)State::Disabled; i++)
				result += getRenderRect((State)i);
			return result;
		}
	#pragma endregion

	#pragma region Getters
		CLabel::State CLabel::getState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (isHovered())
				return State::Hovered;
			return State::Normal;
		}

		String CLabel::getCaption()
		{
			return m_sCaption;
		}

		TextAlign CLabel::getCaptionHorizontalAlign() const
		{
			return m_eCaptionHorizontalAlign;
		}

		VerticalAlign CLabel::getCaptionVerticalAlign() const
		{
			return m_eCaptionVerticalAlign;
		}

		bool CLabel::isAutoSize() const
		{
			return m_bAutoSize;
		}

		bool CLabel::isMultiline() const
		{
			return m_bMultiline;
		}

		Color CLabel::getColor(const State state) const
		{
			return m_aColor[(int)state];
		}

		Color CLabel::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		PointF CLabel::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		int CLabel::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}
	#pragma endregion

	#pragma region CControl setters
		bool CLabel::setAlign(const Align value)
		{
			m_bAutoSize = false;
			return CControl::setAlign(value);
		}

		bool CLabel::setConstraints(const RectF &value)
		{
			m_bAutoSize = false;
			return CControl::setConstraints(value);
		}

		bool CLabel::setSize(const PointF &value)
		{
			m_bAutoSize = false;
			return CControl::setSize(value);
		}

		bool CLabel::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aShadowShift[i] *= s;
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
				}
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CLabel::setCaption(const String &value)
		{
			m_bCaptionChanged = true;
			if (value != m_sCaption)
			{
				CLockRepaint lock{ this };
				m_sCaption = value;
				m_aLines.clear();
				UpdateAutoSize();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CLabel::setCaptionHorizontalAlign(const TextAlign value)
		{
			if (value != m_eCaptionHorizontalAlign)
			{
				m_eCaptionHorizontalAlign = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CLabel::setCaptionVerticalAlign(const VerticalAlign value)
		{
			if (value != m_eCaptionVerticalAlign)
			{
				m_eCaptionVerticalAlign = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CLabel::setAutoSize(const bool value)
		{
			if (value != m_bAutoSize)
			{
				m_bAutoSize = value;
				if (m_bAutoSize)
				{
					CLockRepaint lock{ this };
					CControl::setAlign(Align::None);
					UpdateAutoSize();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CLabel::setMultiline(const bool value)
		{
			if (value != m_bMultiline)
			{
				CLockRepaint lock{ this };
				m_bMultiline = value;
				m_aLines.clear();
				UpdateAutoSize();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CLabel::setColor(const State state, const Color &value)
		{
			if (value != m_aColor[(int)state])
			{
				m_aColor[(int)state] = value;
				if (getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CLabel::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
				m_aShadowColor[(int)state] = value;
				if (getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CLabel::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
					Repaint(false);
				m_aShadowShift[(int)state] = value;
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CLabel::setShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
					Repaint(false);
				m_aShadowRadius[(int)state] = value;
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CLabel::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		void CLabel::UpdateLines()
		{
			if (m_aLines.size() == 0 && !m_sCaption.empty())
			{
				String str{ m_sCaption };
				ReplaceAllDirect(str, L"\r\n", L"\n");
				ReplaceAllDirect(str, L"\r", L"\n");
				Explode(str, L"\n", m_aLines, false);
			}
		}

		void CLabel::UpdateAutoSize()
		{
			if (m_bAutoSize && getForm() && getForm()->getRenderer() && getFont()->getPlatformFont(getForm()->getRenderer()))
			{
				PointF required_size{ 0, 0 };
				if (!m_sCaption.empty())
				{
					IPlatformFont *pf{ getFont()->getPlatformFont(getForm()->getRenderer()) };
					if (m_bMultiline)
					{
						UpdateLines();
						float line_height{ pf->getStringSize(L"Wy", 0).Y };
						for (auto pos = m_aLines.begin(); pos != m_aLines.end(); pos++)
							required_size.X = ntl::Max<float>(required_size.X, pf->getStringSize(*pos, getFont()->Distance).X);
						required_size.Y = line_height * (float)m_aLines.size();
					}
					else
						required_size = pf->getStringSize(m_sCaption, getFont()->Distance);
				}
				CControl::setSize(required_size);
			}
		}

		void CLabel::UpdateFromStyle(IStyle *style)
		{
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String state;
				switch ((State)i)
				{
				case State::Hovered:
					state = L"Hovered";
					break;
				case State::Disabled:
					state = L"Disabled";
					break;
				default:
					state = L"Normal";
				}
				style->getOption(m_sClassName + L".Color[" + state + L"]", m_aColor[i]);
				style->getOption(m_sClassName + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
			}
		}

		RectF CLabel::getRenderRect(const State state)
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
		}
	#pragma endregion

	#pragma region Paint
		void CLabel::Render()
		{
			if (!m_sCaption.empty())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				State state{ getState() };
				PointF disp{ DispOnCanvas(m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
				RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
				if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
				{
					CStoreTarget s_target{ renderer };
					renderer
						->ActivateTarget(m_pCanvas)
						->Clear(Color{ 0, 0, 0, 0 });

					IFont *font{ getFont() };
					IPlatformFont *pf{ font->getPlatformFont(renderer) };
					if (m_aShadowColor[(int)state].A > 0)
					{
						ITexture *shadow{ renderer->CreateTexture(ntl::Round<int>(getWidth() + float(2 * m_aShadowRadius[(int)state])), ntl::Round<int>(getHeight() + float(2 * m_aShadowRadius[(int)state])), 1, TextureFormat::RGBA, true) };
						if (shadow)
						{
							renderer
								->ActivateTarget(shadow)
								->Clear(Color{ 0, 0, 0, 0 });
							if (m_bMultiline)
							{
								UpdateLines();
								float line_height{ pf->getStringSize(L"Wy", 0).Y }, text_height{ line_height * (float)m_aLines.size() }, y{ (float)m_aShadowRadius[(int)state] };
								switch (m_eCaptionVerticalAlign)
								{
								case VerticalAlign::Middle:
									y = (getHeight() - text_height) * 0.5f + (float)m_aShadowRadius[(int)state];
									break;
								case VerticalAlign::Bottom:
									y = getHeight() - text_height + (float)m_aShadowRadius[(int)state];
									break;
								default:
									break;
								}
								CStorePrimitiveMatrix s_matrix{ renderer };
								for (auto pos = m_aLines.begin(); pos != m_aLines.end(); pos++)
								{
									float text_width{ pf->getStringSize(*pos, font->Distance).X }, x{ (float)m_aShadowRadius[(int)state] };
									switch (m_eCaptionHorizontalAlign)
									{
									case TextAlign::Center:
										x = (getWidth() - text_width) * 0.5f + (float)m_aShadowRadius[(int)state];
										break;
									case TextAlign::Right:
										x = getWidth() - text_width + (float)m_aShadowRadius[(int)state];
										break;
									default:
										break;
									}
									renderer
										->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(x), std::round(y), 0))
										->DrawText(*pos, pf, font->Distance, m_aShadowColor[(int)state]);
									y += line_height;
								}
							}
							else
							{
								PointF pos{ (float)m_aShadowRadius[(int)state], (float)m_aShadowRadius[(int)state] }, text_size{ pf->getStringSize(m_sCaption, font->Distance) };
								switch (m_eCaptionHorizontalAlign)
								{
								case TextAlign::Center:
									pos.X = (getWidth() - text_size.X) * 0.5f + (float)m_aShadowRadius[(int)state];
									break;
								case TextAlign::Right:
									pos.X = getWidth() - text_size.X + (float)m_aShadowRadius[(int)state];
									break;
								default:
									break;
								}
								switch (m_eCaptionVerticalAlign)
								{
								case VerticalAlign::Middle:
									pos.Y = (getHeight() - text_size.Y) * 0.5f + (float)m_aShadowRadius[(int)state];
									break;
								case VerticalAlign::Bottom:
									pos.Y = getHeight() - text_size.Y + (float)m_aShadowRadius[(int)state];
									break;
								default:
									break;
								}
								CStorePrimitiveMatrix s_matrix{ renderer };
								renderer
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(pos.X),std::round(pos.Y), 0))
									->DrawText(m_sCaption, pf, font->Distance, m_aShadowColor[(int)state]);
							}
							CStorePrimitiveMatrix s_matrix{ renderer };
							renderer
								->BlurImage(shadow, m_aShadowRadius[(int)state], BlurType::Gaussian)
								->ActivateTarget(m_pCanvas)
								->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(m_aShadowShift[(int)state].X - (float)m_aShadowRadius[(int)state] + disp.X, m_aShadowShift[(int)state].Y - (float)m_aShadowRadius[(int)state] + disp.Y, 0))
								->DrawImage(shadow, 1);
							shadow->Release();
						}
					}
					Color color{ m_aColor[(int)state].A > 0 ? m_aColor[(int)state] : getFont()->Color };
					if (color.A > 0)
					{
						CStorePrimitiveMatrix s_matrix{ renderer };
						if (m_bMultiline)
						{
							UpdateLines();
							float line_height{ pf->getStringSize(L"Wy", 0).Y }, text_height{ line_height * (float)m_aLines.size() }, y{ 0 };
							switch (m_eCaptionVerticalAlign)
							{
							case VerticalAlign::Middle:
								y = (getHeight() - text_height) * 0.5f;
								break;
							case VerticalAlign::Bottom:
								y = getHeight() - text_height;
								break;
							default:
								break;
							}
							for (auto pos = m_aLines.begin(); pos != m_aLines.end(); pos++)
							{
								float text_width{ pf->getStringSize(*pos, font->Distance).X }, x{ 0 };
								switch (m_eCaptionHorizontalAlign)
								{
								case TextAlign::Center:
									x = (getWidth() - text_width) * 0.5f;
									break;
								case TextAlign::Right:
									x = getWidth() - text_width;
									break;
								default:
									break;
								}
								renderer
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(x + disp.X), std::round(y + disp.Y), 0))
									->DrawText(*pos, pf, font->Distance, color);
								y += line_height;
							}
						}
						else
						{
							PointF pos{ 0, 0 }, text_size{ pf->getStringSize(m_sCaption, font->Distance) };
							switch (m_eCaptionHorizontalAlign)
							{
							case TextAlign::Center:
								pos.X = (getWidth() - text_size.X) * 0.5f;
								break;
							case TextAlign::Right:
								pos.X = getWidth() - text_size.X;
								break;
							default:
								break;
							}
							switch (m_eCaptionVerticalAlign)
							{
							case VerticalAlign::Middle:
								pos.Y = (getHeight() - text_size.Y) * 0.5f;
								break;
							case VerticalAlign::Bottom:
								pos.Y = getHeight() - text_size.Y;
								break;
							default:
								break;
							}
							renderer
								->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(pos.X + disp.X), std::round(pos.Y + disp.Y), 0))
								->DrawText(m_sCaption, pf, font->Distance, color);
						}
					}

					m_pCanvas->setValid(true);
				}
				DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
			}
		}
	#pragma endregion
	}
}