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
		CListItemMenuLabel::CGradientListener::CGradientListener(CListItemMenuLabel *control) :
			m_pControl{ control }
		{

		}

		void CListItemMenuLabel::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient && m_pControl->isActive() && m_pControl->isVisible() && m_pControl->QueryService()->getOwner())
				m_pControl->QueryService()->getOwner()->NotifyOnRepaintRequired(m_pControl);
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CListItemMenuLabel::CListItemMenuLabel() :
			CListItemMenu(L"ListItemMenuLabel", true),
			m_cGradientListener{ this },
			m_sIconPadding{ 2, 2, 4, 2 },
			m_sCaptionPadding{ 2, 5, 8, 5 },
			m_sHotkeyPadding{ 2, 2, 8, 2 },
			m_sArrowSize{ 0.2f, 0.3f },
			m_aIconIndex{ -1, -1, -1 },
			m_aColor{
				Color{ 0, 0, 0, 0 },
				Color{ 255, 255, 255, 255 },
				Color{ 133, 135, 139, 255 } },
			m_aShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aShadowRadius{ 1, 1, 1 },
			m_aShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 0, 0 } },
			m_aBorderWidth{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aBorderColor{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aArrowColor{
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 133, 135, 139, 255 } },
			m_aIconBackgroundColor{
				Color{ 200, 200, 200, 32 },
				Color{ 200, 200, 200, 32 },
				Color{ 200, 200, 200, 32 } },
			m_pService{ nullptr },
			m_fHotkeyWidth{ 0 },
			m_bIgnoreGradient{ false },
			OnClick{ nullptr }
		{

		}

		CListItemMenuLabel::CListItemMenuLabel(const String &caption) :CListItemMenuLabel()
		{
			m_sCaption = caption;
		}

		CListItemMenuLabel::~CListItemMenuLabel()
		{
			if (m_pService)
				m_pService->Release();
		}
	#pragma endregion

	#pragma region Helpers
		void CListItemMenuLabel::UpdateFromStyle(IStyle *style)
		{
			bool changed{ false };
			m_bIgnoreGradient = true;
			changed = style->getOption(m_sClassName + L".IconPadding", m_sIconPadding) || changed;
			changed = style->getOption(m_sClassName + L".CaptionPadding", m_sCaptionPadding) || changed;
			changed = style->getOption(m_sClassName + L".HotkeyPadding", m_sHotkeyPadding) || changed;
			changed = style->getOption(m_sClassName + L".ArrowSize", m_sArrowSize) || changed;
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String state;
				switch ((State)i)
				{
				case State::Active:
					state = L"Active";
					break;
				case State::Disabled:
					state = L"Disabled";
					break;
				default:
					state = L"Normal";
				}
				changed = style->getOption(m_sClassName + L".Color[" + state + L"]", m_aColor[i]) || changed;
				changed = style->getOption(m_sClassName + L".ShadowColor[" + state + L"]", m_aShadowColor[i]) || changed;
				changed = style->getOption(m_sClassName + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]) || changed;
				changed = style->getOption(m_sClassName + L".ShadowShift[" + state + L"]", m_aShadowShift[i]) || changed;
				changed = style->getOption(m_sClassName + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]) || changed;
				changed = style->getOption(m_sClassName + L".BorderWidth[" + state + L"]", m_aBorderWidth[i]) || changed;
				changed = style->getOption(m_sClassName + L".BorderRadius[" + state + L"]", m_aBorderRadius[i]) || changed;
				changed = style->getOption(m_sClassName + L".BorderColor[" + state + L"]", m_aBorderColor[i]) || changed;
				changed = style->getOption(m_sClassName + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]) || changed;
				changed = style->getOption(m_sClassName + L".ArrowColor[" + state + L"]", m_aArrowColor[i]) || changed;
			}
			m_bIgnoreGradient = false;
			if (changed && QueryService()->getOwner())
				QueryService()->getOwner()->NotifyOnSizeChange(this);
		}

		IListItem *CListItemMenuLabel::Clone()
		{
			CListItemMenuLabel *result{ new CListItemMenuLabel() };
			Copy(result);
			return result;
		}

		bool CListItemMenuLabel::Copy(IListItem *dest)
		{
			CListItemMenuLabel *d{ cast<CListItemMenuLabel*>(dest) };
			if (d)
			{
				d->m_sIconPadding = m_sIconPadding;
				d->m_sCaptionPadding = m_sCaptionPadding;
				d->m_sHotkeyPadding = m_sHotkeyPadding;
				d->m_sArrowSize = m_sArrowSize;
				d->m_sCaption = m_sCaption;
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					d->m_aIconIndex[i] = m_aIconIndex[i];
					d->m_aColor[i] = m_aColor[i];
					d->m_aShadowColor[i] = m_aShadowColor[i];
					d->m_aShadowRadius[i] = m_aShadowRadius[i];
					d->m_aShadowShift[i] = m_aShadowShift[i];
					d->m_aBackgroundColor[i] = m_aBackgroundColor[i];
					d->m_aBorderWidth[i] = m_aBorderWidth[i];
					d->m_aBorderRadius[i] = m_aBorderRadius[i];
					d->m_aBorderColor[i] = m_aBorderColor[i];
					d->m_aBackgroundGradient[i] = m_aBackgroundGradient[i];
					d->m_aArrowColor[i] = m_aArrowColor[i];
					d->m_aIconBackgroundColor[i] = m_aIconBackgroundColor[i];
				}
				d->m_fHotkeyWidth = m_fHotkeyWidth;
				return CListItemMenu::Copy(dest);
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface getters
		bool CListItemMenuLabel::isAcceptItem(IListItem *item)
		{
			return cast<IListItemMenu*>(item) != nullptr;
		}
	#pragma endregion

	#pragma region Getters
		IListItemService *CListItemMenuLabel::QueryService()
		{
			if (!m_pService)
				m_pService = new CListItemMenuLabelService(this);
			return m_pService;
		}

		CListItemMenuLabel::State CListItemMenuLabel::getState()
		{
			if (!isEnabled())
				return State::Disabled;
			if (isActive())
				return State::Active;
			return State::Normal;
		}

		int CListItemMenuLabel::getIconIndex(const State state) const
		{
			return m_aIconIndex[(int)state];
		}

		RectF CListItemMenuLabel::getIconPadding() const
		{
			return m_sIconPadding;
		}

		RectF CListItemMenuLabel::getCaptionPadding() const
		{
			return m_sCaptionPadding;
		}

		RectF CListItemMenuLabel::getHotkeyPadding() const
		{
			return m_sHotkeyPadding;
		}

		PointF CListItemMenuLabel::getArrowSize() const
		{
			return m_sArrowSize;
		}

		String CListItemMenuLabel::getCaption()
		{
			return m_sCaption;
		}

		Color CListItemMenuLabel::getColor(const State state) const
		{
			return m_aColor[(int)state];
		}

		Color CListItemMenuLabel::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		int CListItemMenuLabel::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CListItemMenuLabel::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		Color CListItemMenuLabel::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		RectF CListItemMenuLabel::getBorderWidth(const State state) const
		{
			return m_aBorderWidth[(int)state];
		}

		RectF CListItemMenuLabel::getBorderRadius(const State state) const
		{
			return m_aBorderRadius[(int)state];
		}

		BorderColor CListItemMenuLabel::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CListItemMenuLabel::getLeftBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Left;
		}

		Color CListItemMenuLabel::getTopBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Top;
		}

		Color CListItemMenuLabel::getRightBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Right;
		}

		Color CListItemMenuLabel::getBottomBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Bottom;
		}

		Gradient *CListItemMenuLabel::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		Color CListItemMenuLabel::getArrowColor(const State state) const
		{
			return m_aArrowColor[(int)state];
		}

		Color CListItemMenuLabel::getIconBackgroundColor(const State state) const
		{
			return m_aIconBackgroundColor[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemMenuLabel::setSelected(const bool value)
		{
			return false;
		}

		bool CListItemMenuLabel::setIconIndex(const State state, int value)
		{
			if (value < 0)
				value = -1;
			if (value != m_aIconIndex[(int)state])
			{
				m_aIconIndex[(int)state] = value;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnSizeChange(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuLabel::setIconPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sIconPadding))
			{
				m_sIconPadding = value;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnSizeChange(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuLabel::setCaptionPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sCaptionPadding))
			{
				m_sCaptionPadding = value;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnSizeChange(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuLabel::setHotkeyPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sHotkeyPadding))
			{
				m_sHotkeyPadding = value;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnSizeChange(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuLabel::setArrowSize(const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsLessOrEqual<float>(value.X, 1) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && ntl::IsLessOrEqual<float>(value.Y, 1) && IsNotEqual(value, m_sArrowSize))
			{
				m_sArrowSize = value;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuLabel::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnSizeChange(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuLabel::setColor(const State state, const Color &value)
		{
			if (value != m_aColor[(int)state])
			{
				m_aColor[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuLabel::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
				m_aShadowColor[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuLabel::setShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aShadowRadius[(int)state])
			{
				m_aShadowRadius[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuLabel::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				m_aShadowShift[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuLabel::setBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuLabel::setBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBorderWidth[(int)state]))
			{
				m_aBorderWidth[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuLabel::setBorderRadius(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBorderRadius[(int)state]))
			{
				m_aBorderRadius[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuLabel::setBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuLabel::setLeftBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ value, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CListItemMenuLabel::setTopBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, value, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CListItemMenuLabel::setRightBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, value, m_aBorderColor[(int)state].Bottom });
		}

		bool CListItemMenuLabel::setBottomBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, value });
		}

		bool CListItemMenuLabel::setArrowColor(const State state, const Color &value)
		{
			if (value != m_aArrowColor[(int)state])
			{
				m_aArrowColor[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuLabel::setIconBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aIconBackgroundColor[(int)state])
			{
				m_aIconBackgroundColor[(int)state] = value;
				if (isVisible() && getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CListItemMenuLabel::Render(const Mat4f &matrix, const Block *block, ITexture **clip)
		{
			IRenderer *renderer{ QueryService()->getOwner()->getRenderer() };
			IFont *font{ QueryService()->getOwner()->getFont(this) };
			IPlatformFont *pf{ font->getPlatformFont(renderer) };
			IListItemMenuOwner *owner{ cast<IListItemMenuOwner*>(QueryService()->getOwner()) };
			ITexture *clip_internal;
			if (clip)
			{
				if (*clip)
					(*clip)->setSize(ntl::Round<int>(getSize().X), ntl::Round<int>(getSize().Y));
				else
					*clip = renderer->CreateTexture(ntl::Round<int>(getSize().X), ntl::Round<int>(getSize().Y), 1, TextureFormat::RGBA, true);
				clip_internal = *clip;
			}
			else
				clip_internal = renderer->CreateTexture(ntl::Round<int>(getSize().X), ntl::Round<int>(getSize().Y), 1, TextureFormat::RGBA, true);
			if (clip_internal)
			{
				State state{ getState() };
				RectF rect_clip{ clip_internal->Rectf };
				String hotkeys{ getHotkeys() };
				Color text_color{ m_aColor[(int)state].A > 0 ? m_aColor[(int)state] : font->Color };
				Color shadow_color{ m_aShadowColor[(int)state] };
				int shadow_radius{ m_aShadowRadius[(int)state] };
				PointF shadow_shift{ m_aShadowShift[(int)state] };
				IBaseTexture *old{ renderer->ActiveTarget };
				renderer
					->ActivateTarget(clip_internal)
					->Clear(Color{ 0, 0, 0, 0 });
				DrawSimpleBackground(renderer, rect_clip, m_aBorderWidth[(int)state], m_aBorderRadius[(int)state], m_aBorderColor[(int)state], m_aBackgroundColor[(int)state], m_aBackgroundGradient[(int)state]);
				RenderParts(state, rect_clip, renderer, font, pf, hotkeys, owner, text_color, shadow_color, shadow_radius, shadow_shift);
				CStoreBlock s_block{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateTarget(old)
					->ActivateBlock(block)
					->ActivatePrimitiveMatrix(matrix)
					->DrawImage(clip_internal, 1);
				if (!clip)
					clip_internal->Release();
			}
		}

		void CListItemMenuLabel::RenderParts(const State state, const RectF &rect_clip, IRenderer *renderer, IFont *font, IPlatformFont *pf, const String &hotkeys,
			IListItemMenuOwner *owner, const Color &text_color, const Color &shadow_color, const int shadow_radius, const PointF &shadow_shift)
		{
			PointF caption_size{ pf->getStringSize(m_sCaption, font->Distance) };
			PointF caption_position{ cast<CListItemMenuLabelService*>(QueryService())->getIconWidth() + m_sCaptionPadding.Left, std::round((rect_clip.height() - caption_size.Y) * 0.5f) };
			DrawTextShadow(renderer, pf, font->Distance, Identity, rect_clip, caption_position, m_sCaption, shadow_color, shadow_shift, shadow_radius);

			PointF hotkeys_size{ pf->getStringSize(hotkeys, font->Distance) };
			PointF hotkeys_position{
				getSize().X - cast<CListItemMenuLabelService*>(QueryService())->getArrowWidth() - m_fHotkeyWidth + m_sHotkeyPadding.Left,
				std::round((rect_clip.height() - hotkeys_size.Y) * 0.5f) };
			DrawTextShadow(renderer, pf, font->Distance, Identity, rect_clip, hotkeys_position, hotkeys, shadow_color, shadow_shift, shadow_radius);

			// Render icon background
			if (m_aIconBackgroundColor[(int)state].A > 0)
			{
				if (m_aBorderWidth[(int)state].has_positive() || m_aBorderRadius[(int)state].has_positive())
				{
					CStoreBlock s_block{ renderer };
					Block b{ RectF{ 0, 0, getSize().X, getSize().Y }, m_aBorderWidth[(int)state], m_aBorderRadius[(int)state], PointLocation::Inside };
					renderer
						->ActivateBlock(&b)
						->DrawRectangle(RectF{ 0, 0, cast<CListItemMenuLabelService*>(QueryService())->getIconWidth(), getSize().Y }, m_aIconBackgroundColor[(int)state]);
				}
				else
					renderer->DrawRectangle(RectF{ 0, 0, cast<CListItemMenuLabelService*>(QueryService())->getIconWidth(), getSize().Y }, m_aIconBackgroundColor[(int)state]);
			}
			// Render caption
			CStorePrimitiveMatrix s_matrix{ renderer };
			if (!m_sCaption.empty())
			{
				renderer
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(caption_position.X, caption_position.Y, 0))
					->DrawText(m_sCaption, pf, font->Distance, text_color);
			}
			// Render hotkey
			if (!hotkeys.empty())
			{
				renderer
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(hotkeys_position.X, hotkeys_position.Y, 0))
					->DrawText(hotkeys, pf, font->Distance, text_color);
			}
			// Render arrow
			if (getItemCount() > 0 && m_aArrowColor[(int)state].A > 0)
			{
				RectF rect_arrow{
					getSize().X - cast<CListItemMenuLabelService*>(QueryService())->getArrowWidth() * 0.5f - cast<CListItemMenuLabelService*>(QueryService())->getArrowWidth() * m_sArrowSize.X * 0.5f,
					getSize().Y * 0.5f - getSize().Y * m_sArrowSize.Y * 0.5f,
					getSize().X - cast<CListItemMenuLabelService*>(QueryService())->getArrowWidth() * 0.5f + cast<CListItemMenuLabelService*>(QueryService())->getArrowWidth() * m_sArrowSize.X * 0.5f,
					getSize().Y * 0.5f + getSize().Y * m_sArrowSize.Y * 0.5f };
				if (rect_arrow.is_valid() && !rect_arrow.is_zero())
				{
					renderer
						->ActivatePrimitiveMatrix(nullptr)
						->DrawTriangle(
							PointF{ rect_arrow.Left, rect_arrow.Top },
							PointF{ rect_arrow.Right, (rect_arrow.Bottom + rect_arrow.Top) * 0.5f },
							PointF{ rect_arrow.Left, rect_arrow.Bottom },
							m_aArrowColor[(int)state]);
				}
			}
			// Render icon
			if (owner)
			{
				RectF part;
				ITexture *icon{ owner->getImage(isEnabled(), isActive(), isHovered(), m_aIconIndex[(int)state], part) };
				if (icon)
				{
					RectF rect_icon{ m_sIconPadding.Left, m_sIconPadding.Top, cast<CListItemMenuLabelService*>(QueryService())->getIconWidth() - m_sIconPadding.Right, getSize().Y - m_sIconPadding.Bottom };
					if (rect_icon.is_valid() && !rect_icon.is_zero())
					{
						renderer
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(rect_icon.Left, rect_icon.Top, 0) * ntl::Mat4Scale<float>(rect_icon.width() / part.width(), rect_icon.height() / part.height(), 1))
							->DrawImage(icon, 1, part);
					}
				}
			}
		}
	#pragma endregion
	}
}