// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		CGroupBox::CGradientListener::CGradientListener(CGroupBox *control) :
			m_pControl{ control }
		{

		}

		void CGroupBox::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CGroupBox::CGroupBox() :
			CControl(L"GroupBox", true, true, true, false, false, false),
			m_cGradientListener{ this },
			m_sBorderWidth{ 1, 1, 1, 1 },
			m_sBorderRadius{ 1, 1, 1, 1 },
			m_sBorderColor{ Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 } },
			m_sPadding{ 4, 14, 4, 4 },
			m_sBackgroundColor{ 240, 240, 240, 255 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_sShadowColor{ 0, 0, 0, 0 },
			m_sShadowShift{ 0, 0 },
			m_iShadowRadius{ 1 },
			m_eCaptionAlign{ TextAlign::Left },
			m_sCaptionPadding{ 5, 0 },
			m_bUseMask{ true },
			m_bIgnoreGradient{ false },
			m_pCanvas{ nullptr },
			m_pMask{ nullptr },
			m_bCaptionChanged{ false }
		{
			setService(new CGroupBoxService(this), true);
			setSize(PointF{ 185, 105 });
		}

		CGroupBox::CGroupBox(IControl *parent) : CGroupBox()
		{
			setParent(parent);
		}

		CGroupBox::CGroupBox(IForm *parent) : CGroupBox()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region CControl getters
		IControl *CGroupBox::getControl(const int index)
		{
			return CControl::getControl(index);
		}

		IControl *CGroupBox::getControl(const String &name)
		{
			return CControl::getControl(name);
		}

		IControl *CGroupBox::getControl(const PointF &position)
		{
			IControl *result{ CControl::getControl(position) };
			if (m_bUseMask && result && result != this)
			{
				Vec4f v{ ntl::Inversed<float>(getTransformMatrix()) * Vec4f{ position.X, position.Y, 0, 1 } };
				RectF client{ getClientRect() };
				if (v.X < 0 || v.X >= getWidth() || v.Y < 0 || v.Y >= getHeight())
					result = nullptr;
				else if (v.X < client.Left || v.X >= client.Right || v.Y < client.Top || v.Y >= client.Bottom)
					result = this;
			}
			return result;
		}

		RectF CGroupBox::getClientRect()
		{
			RectF result{
				m_sBorderWidth.Left + m_sPadding.Left,
				m_sBorderWidth.Top + m_sPadding.Top,
				getWidth() - m_sBorderWidth.Right - m_sPadding.Right,
				getHeight() - m_sBorderWidth.Bottom - m_sPadding.Bottom
			};
			result.validate();
			return result;
		}

		RectF CGroupBox::getRenderRect()
		{
			RectF caption_rect{ getCaptionRect() };
			return
				AddShadow(getBlockRect(caption_rect), m_sShadowColor, m_sShadowShift, m_iShadowRadius) +
				AddShadow(caption_rect, getFont()->ShadowColor, getFont()->ShadowShift, getFont()->ShadowRadius);
		}
	#pragma endregion

	#pragma region Getters
		RectF CGroupBox::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		RectF CGroupBox::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		BorderColor CGroupBox::getBorderColor() const
		{
			return m_sBorderColor;
		}

		Color CGroupBox::getLeftBorderColor() const
		{
			return m_sBorderColor.Left;
		}

		Color CGroupBox::getTopBorderColor() const
		{
			return m_sBorderColor.Top;
		}

		Color CGroupBox::getRightBorderColor() const
		{
			return m_sBorderColor.Right;
		}

		Color CGroupBox::getBottomBorderColor() const
		{
			return m_sBorderColor.Bottom;
		}

		RectF CGroupBox::getPadding() const
		{
			return m_sPadding;
		}

		Color CGroupBox::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CGroupBox::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		Color CGroupBox::getShadowColor() const
		{
			return m_sShadowColor;
		}

		PointF CGroupBox::getShadowShift() const
		{
			return m_sShadowShift;
		}

		int CGroupBox::getShadowRadius() const
		{
			return m_iShadowRadius;
		}

		String CGroupBox::getCaption()
		{
			return m_sCaption;
		}

		TextAlign CGroupBox::getCaptionAlign() const
		{
			return m_eCaptionAlign;
		}

		PointF CGroupBox::getCaptionPadding() const
		{
			return m_sCaptionPadding;
		}

		bool CGroupBox::isUseMask() const
		{
			return m_bUseMask;
		}
	#pragma endregion

	#pragma region Setters
		bool CGroupBox::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sBorderWidth *= s;
				m_sBorderRadius *= avg;
				m_sPadding *= s;
				m_sShadowShift *= s;
				m_iShadowRadius = ntl::Round<int>((float)m_iShadowRadius * avg);
				m_sCaptionPadding *= s;
				QueryService()->AlignControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CGroupBox::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				CLockRepaint lock{ this };
				m_sBorderWidth = value;
				QueryService()->AlignControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CGroupBox::setBorderRadius(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderRadius))
			{
				m_sBorderRadius = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CGroupBox::setBorderColor(const BorderColor &value)
		{
			if (value != m_sBorderColor)
			{
				m_sBorderColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CGroupBox::setLeftBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ value, m_sBorderColor.Top, m_sBorderColor.Right, m_sBorderColor.Bottom });
		}

		bool CGroupBox::setTopBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, value, m_sBorderColor.Right, m_sBorderColor.Bottom });
		}

		bool CGroupBox::setRightBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, m_sBorderColor.Top, value, m_sBorderColor.Bottom });
		}

		bool CGroupBox::setBottomBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, m_sBorderColor.Top, m_sBorderColor.Right, value });
		}

		bool CGroupBox::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				CLockRepaint lock{ this };
				m_sPadding = value;
				QueryService()->AlignControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CGroupBox::setBackgroundColor(const Color &value)
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

		bool CGroupBox::setShadowColor(const Color &value)
		{
			if (value != m_sShadowColor)
			{
				m_sShadowColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CGroupBox::setShadowShift(const PointF &value)
		{
			if (IsNotEqual(value, m_sShadowShift))
			{
				CLockRepaint lock{ this };
				if (m_sShadowColor.A > 0)
					Repaint(false);
				m_sShadowShift = value;
				if (m_sShadowColor.A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGroupBox::setShadowRadius(const int value)
		{
			if (value >= 1 && value != m_iShadowRadius)
			{
				CLockRepaint lock{ this };
				if (m_sShadowColor.A > 0)
					Repaint(false);
				m_iShadowRadius = value;
				if (m_sShadowColor.A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGroupBox::setCaption(const String &value)
		{
			m_bCaptionChanged = true;
			if (value != m_sCaption)
			{
				m_sCaption = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CGroupBox::setCaptionAlign(const TextAlign value)
		{
			if (value != m_eCaptionAlign)
			{
				m_eCaptionAlign = value;
				if (!m_sCaption.empty())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGroupBox::setCaptionPadding(const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_sCaptionPadding))
			{
				m_sCaptionPadding = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CGroupBox::setUseMask(const bool value)
		{
			if (value != m_bUseMask)
			{
				m_bUseMask = value;
				Repaint(true);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CGroupBox::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			if (m_pMask)
				m_pMask->setValid(false);
			CControl::Refresh(refresh_children);
		}

		void CGroupBox::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BorderWidth", m_sBorderWidth);
			style->getOption(m_sClassName + L".BorderRadius", m_sBorderRadius);
			style->getOption(m_sClassName + L".BorderColor", m_sBorderColor);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			style->getOption(m_sClassName + L".BackgrundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L".ShadowColor", m_sShadowColor);
			style->getOption(m_sClassName + L".ShadowShift", m_sShadowShift);
			style->getOption(m_sClassName + L".ShadowRadius", m_iShadowRadius);
			style->getOption(m_sClassName + L".CaptionPadding", m_sCaptionPadding);
			m_bIgnoreGradient = false;
			QueryService()->AlignControls();
		}

		RectF CGroupBox::getBlockRect(const RectF &caption_rect)
		{
			RectF result{ 0, std::round((caption_rect.Top + caption_rect.Bottom) * 0.5f), getWidth(), getHeight() };
			result.validate();
			return result;
		}

		RectF CGroupBox::getCaptionRect()
		{
			if (m_sCaption.empty() || !getForm() || !getForm()->getRenderer() || !getFont()->getPlatformFont(getForm()->getRenderer()))
				return RectF{ 0, m_sCaptionPadding.Y, 0, m_sCaptionPadding.Y };
			PointF size{ getFont()->getPlatformFont(getForm()->getRenderer())->getStringSize(m_sCaption, getFont()->Distance) };
			RectF result;
			switch (m_eCaptionAlign)
			{
			case TextAlign::Center:
				result.Left = (getWidth() - size.X) * 0.5f;
				break;
			case TextAlign::Right:
				result.Left = getWidth() - m_sCaptionPadding.X - size.X;
				break;
			default:
				result.Left = m_sCaptionPadding.X;
			}
			result.Top = m_sCaptionPadding.Y;
			result.Right = result.Left + size.X;
			result.Bottom = result.Top + size.Y;
			return result;
		}
	#pragma endregion

	#pragma region Paint
		void CGroupBox::Render(IRenderer *renderer, const Mat4f &matrix)
		{
			PointF disp{ DispOnCanvas(m_sShadowColor, m_sShadowShift, m_iShadowRadius) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_sShadowColor, m_sShadowShift, m_iShadowRadius) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				RectF caption_rect{ getCaptionRect() };
				caption_rect += disp;
				RectF block_rect{ getBlockRect(caption_rect) };

				DrawBlockShadow(renderer, block_rect, m_sBorderRadius, m_sShadowColor, m_sShadowShift, m_iShadowRadius);
				Block b{ block_rect, m_sBorderWidth, m_sBorderRadius, PointLocation::Inside };
				BlockColors colors{ m_sBorderColor.Left, m_sBorderColor.Top, m_sBorderColor.Right, m_sBorderColor.Bottom, m_sBackgroundColor, Color{ 0, 0, 0, 0 } };
				if (m_sCaption.empty())
				{
					renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
					if (m_cBackgroundGradient.getPointCount() >= 2)
					{
						CStoreBlock s_block{ renderer };
						renderer
							->ActivateBlock(&b)
							->DrawGradient(b.Rect, m_cBackgroundGradient);
					}
				}
				else
				{
					// Background
					IBaseTexture *old{ renderer->ActiveTarget };
					ITexture *background{ renderer->CreateTexture(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()), 1, TextureFormat::RGBA, true) };
					if (background)
					{
						CStorePrimitiveMatrix s_matrix{ renderer };
						b.Rect = getBlockRect(getCaptionRect());
						renderer
							->ActivateTarget(background)
							->Clear(Color{ 0, 0, 0, 0 })
							->DrawBlock(b.Rect, b.Border, b.Radius, colors)
							->DrawRectangle(RectF{ caption_rect.Left, b.Rect.Top, caption_rect.Right, caption_rect.Bottom }, m_sBackgroundColor)
							->ActivateTarget(old)
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(disp.X, disp.Y, 0))
							->DrawImage(background, 1);
						background->Release();
						b.Rect = block_rect;
					}
					if (m_cBackgroundGradient.getPointCount() >= 2)
					{
						CStoreBlock s_block{ renderer };
						renderer
							->ActivateBlock(&b)
							->DrawGradient(b.Rect, m_cBackgroundGradient);
					}
					// Caption
					IPlatformFont *pf{ getFont()->getPlatformFont(renderer) };
					PointF pos{ std::round(caption_rect.Left), std::round(caption_rect.Top) };
					DrawTextShadow(renderer, pf, getFont()->Distance, Identity, all_rect, pos, m_sCaption, getFont()->ShadowColor, getFont()->ShadowShift, getFont()->ShadowRadius);
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(pos.X, pos.Y, 0))
						->DrawText(m_sCaption, pf, getFont()->Distance, getFont()->Color);
				}

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, matrix, m_pCanvas, disp);
		}

		void CGroupBox::RenderMask(IRenderer *renderer)
		{
			if (PrepareCanvas(renderer, &m_pMask, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pMask)
					->Clear(Color{ 0, 0, 0, 0 });
				Block b{
					RectF{ 0, 0, getWidth(), getHeight() },
					RectF{
						m_sBorderWidth.Left + m_sPadding.Left,
						m_sBorderWidth.Top + m_sPadding.Top,
						m_sBorderWidth.Right + m_sPadding.Right,
						m_sBorderWidth.Bottom + m_sPadding.Bottom
					},
					m_sBorderRadius,
					PointLocation::Inside
				};
				if (m_sBorderRadius.has_positive())
				{
					CStoreBlock s_block{ renderer };
					renderer
						->ActivateBlock(&b)
						->DrawRectangle(b.Rect, Color{ 0, 0, 0, 255 });
				}
				else
					renderer->DrawRectangle(RectF{ b.Border.Left, b.Border.Top, b.Rect.Right - b.Border.Right, b.Rect.Bottom - b.Border.Bottom }, Color{ 0, 0, 0, 255 });
				m_pMask->setValid(true);
			}
		}
	#pragma endregion
	}
}