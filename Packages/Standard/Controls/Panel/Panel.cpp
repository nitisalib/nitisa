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
		CPanel::CGradientListener::CGradientListener(CPanel *control) :
			m_pControl{ control }
		{

		}

		void CPanel::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(true);
			}
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CPanel::CPanel() :
			CControl(L"Panel", true, true, true, false, false, false),
			m_cGradientListener{ this },
			m_eCaptionHorizontalAlign{ TextAlign::Center },
			m_eCaptionVerticalAlign{ VerticalAlign::Middle },
			m_eOuterBevel{ Bevel::Raised },
			m_eInnerBevel{ Bevel::Raised },
			m_sBevelRaisedColor{ 255, 255, 255, 255 },
			m_sBevelLoweredColor{ 160, 160, 160, 255 },
			m_sOuterBevelWidth{ 1, 1, 1, 1 },
			m_sInnerBevelWidth{ 1, 1, 1, 1 },
			m_sBorderWidth{ 0, 0, 0, 0 },
			m_sBorderRadius{ 0, 0, 0, 0 },
			m_sBorderColor{ Color{ 240, 240, 240, 255 }, Color{ 240, 240, 240, 255 }, Color{ 240, 240, 240, 255 }, Color{ 240, 240, 240, 255 } },
			m_sPadding{ 0, 0, 0, 0 },
			m_sBackgroundColor{ 240, 240, 240, 255 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_sShadowColor{ 0, 0, 0, 0 },
			m_sShadowShift{ 0, 0 },
			m_iShadowRadius{ 1 },
			m_bUseMask{ true },
			m_bIgnoreGradient{ false },
			m_pCanvas{ nullptr },
			m_pMask{ nullptr },
			m_bCaptionChanged{ false }
		{
			setService(new CPanelService(this), true);
			setSize(PointF{ 185, 105 });
		}

		CPanel::CPanel(IControl *parent) : CPanel()
		{
			setParent(parent);
		}

		CPanel::CPanel(IForm *parent) : CPanel()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region CControl getters
		IControl *CPanel::getControl(const int index)
		{
			return CControl::getControl(index);
		}

		IControl *CPanel::getControl(const String &name)
		{
			return CControl::getControl(name);
		}

		IControl *CPanel::getControl(const PointF &position)
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

		RectF CPanel::getClientRect()
		{
			RectF result{ 0, 0, getWidth(), getHeight() };
			result.Left += m_sOuterBevelWidth.Left + m_sBorderWidth.Left + m_sInnerBevelWidth.Left + m_sPadding.Left;
			result.Top += m_sOuterBevelWidth.Top + m_sBorderWidth.Top + m_sInnerBevelWidth.Top + m_sPadding.Top;
			result.Right -= m_sOuterBevelWidth.Right + m_sBorderWidth.Right + m_sInnerBevelWidth.Right + m_sPadding.Right;
			result.Bottom -= m_sOuterBevelWidth.Bottom + m_sBorderWidth.Bottom + m_sInnerBevelWidth.Bottom + m_sPadding.Bottom;
			result.validate();
			return result;
		}

		RectF CPanel::getRenderRect()
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_sShadowColor, m_sShadowShift, m_iShadowRadius);
		}
	#pragma endregion

	#pragma region Getters
		String CPanel::getCaption()
		{
			return m_sCaption;
		}

		TextAlign CPanel::getCaptionHorizontalAlign() const
		{
			return m_eCaptionHorizontalAlign;
		}

		VerticalAlign CPanel::getCaptionVerticalAlign() const
		{
			return m_eCaptionVerticalAlign;
		}

		CPanel::Bevel CPanel::getOuterBevel() const
		{
			return m_eOuterBevel;
		}

		CPanel::Bevel CPanel::getInnerBevel() const
		{
			return m_eInnerBevel;
		}

		Color CPanel::getBevelRaisedColor() const
		{
			return m_sBevelRaisedColor;
		}

		Color CPanel::getBevelLoweredColor() const
		{
			return m_sBevelLoweredColor;
		}

		RectF CPanel::getOuterBevelWidth() const
		{
			return m_sOuterBevelWidth;
		}

		RectF CPanel::getInnerBevelWidth() const
		{
			return m_sInnerBevelWidth;
		}

		RectF CPanel::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		RectF CPanel::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		BorderColor CPanel::getBorderColor() const
		{
			return m_sBorderColor;
		}

		Color CPanel::getLeftBorderColor() const
		{
			return m_sBorderColor.Left;
		}

		Color CPanel::getTopBorderColor() const
		{
			return m_sBorderColor.Top;
		}

		Color CPanel::getRightBorderColor() const
		{
			return m_sBorderColor.Right;
		}

		Color CPanel::getBottomBorderColor() const
		{
			return m_sBorderColor.Bottom;
		}

		RectF CPanel::getPadding() const
		{
			return m_sPadding;
		}

		Color CPanel::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CPanel::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		Color CPanel::getShadowColor() const
		{
			return m_sShadowColor;
		}

		PointF CPanel::getShadowShift() const
		{
			return m_sShadowShift;
		}

		int CPanel::getShadowRadius() const
		{
			return m_iShadowRadius;
		}

		bool CPanel::isUseMask() const
		{
			return m_bUseMask;
		}
	#pragma endregion

	#pragma region Setters
		bool CPanel::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sOuterBevelWidth *= s;
				m_sInnerBevelWidth *= s;
				m_sBorderWidth *= s;
				m_sBorderRadius *= avg;
				m_sPadding *= s;
				m_sShadowShift *= s;
				m_iShadowRadius = ntl::Round<int>((float)m_iShadowRadius * avg);
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

		bool CPanel::setCaption(const String &value)
		{
			m_bCaptionChanged = true;
			if (value != m_sCaption)
			{
				m_sCaption = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPanel::setCaptionHorizontalAlign(const TextAlign value)
		{
			if (value != m_eCaptionHorizontalAlign)
			{
				m_eCaptionHorizontalAlign = value;
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

		bool CPanel::setCaptionVerticalAlign(const VerticalAlign value)
		{
			if (value != m_eCaptionVerticalAlign)
			{
				m_eCaptionVerticalAlign = value;
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

		bool CPanel::setOuterBevel(const Bevel value)
		{
			if (value != m_eOuterBevel)
			{
				m_eOuterBevel = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPanel::setInnerBevel(const Bevel value)
		{
			if (value != m_eInnerBevel)
			{
				m_eInnerBevel = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPanel::setBevelRaisedColor(const Color &value)
		{
			if (value != m_sBevelRaisedColor)
			{
				m_sBevelRaisedColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPanel::setBevelLoweredColor(const Color &value)
		{
			if (value != m_sBevelLoweredColor)
			{
				m_sBevelLoweredColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPanel::setOuterBevelWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sOuterBevelWidth))
			{
				CLockRepaint lock{ this };
				m_sOuterBevelWidth = value;
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

		bool CPanel::setInnerBevelWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sInnerBevelWidth))
			{
				CLockRepaint lock{ this };
				m_sInnerBevelWidth = value;
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

		bool CPanel::setBorderWidth(const RectF &value)
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

		bool CPanel::setBorderRadius(const RectF &value)
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

		bool CPanel::setBorderColor(const BorderColor &value)
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

		bool CPanel::setLeftBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ value, m_sBorderColor.Top, m_sBorderColor.Right, m_sBorderColor.Bottom });
		}

		bool CPanel::setTopBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, value, m_sBorderColor.Right, m_sBorderColor.Bottom });
		}

		bool CPanel::setRightBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, m_sBorderColor.Top, value, m_sBorderColor.Bottom });
		}

		bool CPanel::setBottomBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, m_sBorderColor.Top, m_sBorderColor.Right, value });
		}

		bool CPanel::setPadding(const RectF &value)
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

		bool CPanel::setBackgroundColor(const Color &value)
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

		bool CPanel::setShadowColor(const Color &value)
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

		bool CPanel::setShadowShift(const PointF &value)
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

		bool CPanel::setShadowRadius(const int value)
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

		bool CPanel::setUseMask(const bool value)
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
		void CPanel::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			CControl::Refresh(refresh_children);
		}

		void CPanel::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BevelRaisedColor", m_sBevelRaisedColor);
			style->getOption(m_sClassName + L".BevelLoweredColor", m_sBevelLoweredColor);
			style->getOption(m_sClassName + L".OuterBevelWidth", m_sOuterBevelWidth);
			style->getOption(m_sClassName + L".InnerBevelWidth", m_sInnerBevelWidth);
			style->getOption(m_sClassName + L".BorderWidth", m_sBorderWidth);
			style->getOption(m_sClassName + L".BorderRadius", m_sBorderRadius);
			style->getOption(m_sClassName + L".BorderColor", m_sBorderColor);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L".ShadowColor", m_sShadowColor);
			style->getOption(m_sClassName + L".ShadowShift", m_sShadowShift);
			style->getOption(m_sClassName + L".ShadowRadius", m_iShadowRadius);
			m_bIgnoreGradient = false;
			QueryService()->AlignControls();
		}
	#pragma endregion

	#pragma region Paint
		void CPanel::Render(IRenderer *renderer, const Mat4f &matrix)
		{
			PointF disp{ DispOnCanvas(m_sShadowColor, m_sShadowShift, m_iShadowRadius) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_sShadowColor, m_sShadowShift, m_iShadowRadius) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				IPlatformFont *pf{ getFont()->getPlatformFont(renderer) };
				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
				DrawBlockShadow(renderer, rect, m_sBorderRadius, m_sShadowColor, m_sShadowShift, m_iShadowRadius);
				RenderBackground(renderer, rect);
				RenderCaption(renderer, pf, rect, disp);

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, matrix, m_pCanvas, disp);
		}

		void CPanel::RenderBackground(IRenderer *renderer, const RectF &rect)
		{
			BorderColor outer_color{
				(m_eOuterBevel == Bevel::Raised) ? m_sBevelRaisedColor : m_sBevelLoweredColor,
				(m_eOuterBevel == Bevel::Raised) ? m_sBevelRaisedColor : m_sBevelLoweredColor,
				(m_eOuterBevel == Bevel::Raised) ? m_sBevelLoweredColor : m_sBevelRaisedColor,
				(m_eOuterBevel == Bevel::Raised) ? m_sBevelLoweredColor : m_sBevelRaisedColor
			};
			BorderColor inner_color{
				(m_eInnerBevel == Bevel::Raised) ? m_sBevelRaisedColor : m_sBevelLoweredColor,
				(m_eInnerBevel == Bevel::Raised) ? m_sBevelRaisedColor : m_sBevelLoweredColor,
				(m_eInnerBevel == Bevel::Raised) ? m_sBevelLoweredColor : m_sBevelRaisedColor,
				(m_eInnerBevel == Bevel::Raised) ? m_sBevelLoweredColor : m_sBevelRaisedColor
			};
			DrawTripleBackground(
				renderer,
				rect,
				m_sOuterBevelWidth,
				m_sBorderWidth,
				m_sInnerBevelWidth,
				m_sBorderRadius,
				outer_color,
				m_sBorderColor,
				inner_color,
				m_sBackgroundColor,
				m_cBackgroundGradient);
		}

		void CPanel::RenderCaption(IRenderer *renderer, IPlatformFont *pf, const RectF &rect, const PointF &disp)
		{
			if (m_sCaption.empty())
				return;
			RectF client{ getClientRect() };
			if (client.is_zero())
				return;
			client += disp;

			PointF caption_size{ pf->getStringSize(m_sCaption, getFont()->Distance) };
			PointF pos{ client.LeftTop }; // In clip coordinates
			switch (m_eCaptionHorizontalAlign)
			{
			case TextAlign::Center:
				pos.X = (client.Left + client.Right - caption_size.X) * 0.5f;
				break;
			case TextAlign::Right:
				pos.X = client.Right - caption_size.X;
				break;
			default:
				break;
			}
			switch (m_eCaptionVerticalAlign)
			{
			case VerticalAlign::Middle:
				pos.Y = (client.Top + client.Bottom - caption_size.Y) * 0.5f;
				break;
			case VerticalAlign::Bottom:
				pos.Y = client.Bottom - caption_size.Y;
				break;
			default:
				break;
			}
			pos.X = std::round(pos.X);
			pos.Y = std::round(pos.Y);
			DrawTextShadow(renderer, pf, getFont()->Distance, Identity, client, pos, m_sCaption, getFont()->ShadowColor, getFont()->ShadowShift, getFont()->ShadowRadius);
			if (getFont()->Color.A > 0)
			{
				Block b{ rect, AddElements(m_sOuterBevelWidth, m_sBorderWidth, m_sInnerBevelWidth, m_sPadding), m_sBorderRadius, PointLocation::Inside };
				CStoreBlock s_block{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBlock(&b)
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(pos.X, pos.Y, 0))
					->DrawText(m_sCaption, pf, getFont()->Distance, getFont()->Color);
			}
		}

		void CPanel::RenderMask(IRenderer *renderer)
		{
			if (PrepareCanvas(renderer, &m_pMask, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pMask)
					->Clear(Color{ 0, 0, 0, 0 });
				Block b{ RectF{ 0, 0, getWidth(), getHeight() }, AddElements(m_sOuterBevelWidth, m_sBorderWidth, m_sInnerBevelWidth, m_sPadding), m_sBorderRadius, PointLocation::Inside };
				if (m_sBorderRadius.has_positive())
				{
					CStoreBlock s_block{ renderer };
					renderer
						->ActivateBlock(&b)
						->DrawRectangle(b.Rect, Color{ 0, 0, 0, 255 });
				}
				else
					renderer->DrawRectangle(RectF{ b.Border.Left, b.Border.Top, b.Rect.Right - b.Border.Right, b.Rect.Bottom - b.Border.Bottom } * b.Rect, Color{ 0, 0, 0, 255 });
				m_pMask->setValid(true);
			}
		}
	#pragma endregion
	}
}