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
		CListItemMenuRadioButton::CGradientListener::CGradientListener(CListItemMenuRadioButton *control) :
			m_pControl{ control }
		{

		}

		void CListItemMenuRadioButton::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient && m_pControl->isActive() && m_pControl->isVisible() && m_pControl->QueryService()->getOwner())
				m_pControl->QueryService()->getOwner()->NotifyOnRepaintRequired(m_pControl);
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CListItemMenuRadioButton::CListItemMenuRadioButton() :
			CListItemMenu(L"ListItemMenuRadioButton", false),
			m_cGradientListener{ this },
			m_iGroupIndex{ 0 },
			m_bChecked{ false },
			m_sIconPadding{ 0, 0, 4, 0 },
			m_sCaptionPadding{ 2, 5, 8, 5 },
			m_sHotkeyPadding{ 2, 2, 8, 2 },
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
			m_aIconBackgroundColor{
				Color{ 200, 200, 200, 32 },
				Color{ 200, 200, 200, 32 },
				Color{ 200, 200, 200, 32 } },
			m_pService{ nullptr },
			m_fIconWidth{ 0 },
			m_fHotkeyWidth{ 0 },
			m_bIgnoreGradient{ false },
			OnChange{ nullptr }
		{

		}

		CListItemMenuRadioButton::CListItemMenuRadioButton(const String &caption) :CListItemMenuRadioButton()
		{
			m_sCaption = caption;
		}

		CListItemMenuRadioButton::~CListItemMenuRadioButton()
		{
			if (m_pService)
				m_pService->Release();
		}
	#pragma endregion

	#pragma region Helpers
		void CListItemMenuRadioButton::UpdateFromStyle(IStyle *style)
		{
			bool changed{ false };
			m_bIgnoreGradient = true;
			changed = style->getOption(m_sClassName + L".IconPadding", m_sIconPadding) || changed;
			changed = style->getOption(m_sClassName + L".CaptionPadding", m_sCaptionPadding) || changed;
			changed = style->getOption(m_sClassName + L".HotkeyPadding", m_sHotkeyPadding) || changed;
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
				changed = style->getOption(m_sClassName + L".IconBackgroundColor[" + state + L"]", m_aIconBackgroundColor[i]) || changed;
			}
			m_bIgnoreGradient = false;
			if (changed && QueryService()->getOwner())
				QueryService()->getOwner()->NotifyOnSizeChange(this);
		}

		bool CListItemMenuRadioButton::AddItem(IListItem *item)
		{
			return false;
		}

		bool CListItemMenuRadioButton::InsertItem(IListItem *item, const int before)
		{
			return false;
		}

		ITexture *CListItemMenuRadioButton::FindIcon(RectF &part)
		{
			if (!QueryService()->getOwner() || !QueryService()->getOwner()->getRenderer())
				return nullptr;
			String name{ m_sClassName + (m_bChecked ? L".Checked" : L".Unchecked") };
			if (!isEnabled())
				name += L".Disabled";
			IStyle *style{ QueryService()->getOwner()->getStyle(this) };
			if (style)
			{
				IStyleSkin *skin{ style->getSkin(name) };
				if (skin)
				{
					part = skin->Rect;
					return QueryService()->getOwner()->getRenderer()->CreateTextureFromImage(skin->getImage()->Image, 1, TextureFormat::RGBA, true);
				}
			}
			if (style != Application->Styles->getStyle(0) && (style = Application->Styles->getStyle(0)))
			{
				IStyleSkin *skin{ style->getSkin(name) };
				if (skin)
				{
					part = skin->Rect;
					return QueryService()->getOwner()->getRenderer()->CreateTextureFromImage(skin->getImage()->Image, 1, TextureFormat::RGBA, true);
				}
			}
			return nullptr;
		}

		bool CListItemMenuRadioButton::HaveCheckedOnParent()
		{
			if (m_iGroupIndex >= 0 && getParent())
				for (int i = 0; i < getParent()->getItemCount(); i++)
					if (getParent()->getItem(i) != this)
					{
						IListItemRadioButton *item{ cast<IListItemRadioButton*>(getParent()->getItem(i)) };
						if (item && item->getGroupIndex() == m_iGroupIndex)
							return true;
					}
			return false;
		}

		void CListItemMenuRadioButton::UncheckAllOnParent()
		{
			if (m_iGroupIndex >= 0 && getParent())
				for (int i = 0; i < getParent()->getItemCount(); i++)
					if (getParent()->getItem(i) != this)
					{
						IListItemRadioButton *item{ cast<IListItemRadioButton*>(getParent()->getItem(i)) };
						if (item && item->getGroupIndex() == m_iGroupIndex && item->isChecked())
						{
							IListItemRadioButtonService *service{ cast<IListItemRadioButtonService*>(item->QueryService()) };
							if (service)
								service->setChecked(false);
						}
					}
		}

		IListItem *CListItemMenuRadioButton::Clone()
		{
			CListItemMenuRadioButton *result{ new CListItemMenuRadioButton() };
			Copy(result);
			return result;
		}

		bool CListItemMenuRadioButton::Copy(IListItem *dest)
		{
			CListItemMenuRadioButton *d{ cast<CListItemMenuRadioButton*>(dest) };
			if (d)
			{
				d->m_iGroupIndex = m_iGroupIndex;
				d->m_bChecked = m_bChecked;
				d->m_sIconPadding = m_sIconPadding;
				d->m_sCaptionPadding = m_sCaptionPadding;
				d->m_sHotkeyPadding = m_sHotkeyPadding;
				d->m_sCaption = m_sCaption;
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					d->m_aColor[i] = m_aColor[i];
					d->m_aShadowColor[i] = m_aShadowColor[i];
					d->m_aShadowRadius[i] = m_aShadowRadius[i];
					d->m_aShadowShift[i] = m_aShadowShift[i];
					d->m_aBackgroundColor[i] = m_aBackgroundColor[i];
					d->m_aBorderWidth[i] = m_aBorderWidth[i];
					d->m_aBorderRadius[i] = m_aBorderRadius[i];
					d->m_aBorderColor[i] = m_aBorderColor[i];
					d->m_aBackgroundGradient[i] = m_aBackgroundGradient[i];
					d->m_aIconBackgroundColor[i] = m_aIconBackgroundColor[i];
				}
				d->m_fIconWidth = m_fIconWidth;
				d->m_fHotkeyWidth = m_fHotkeyWidth;
				return CListItemMenu::Copy(dest);
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		IListItemService *CListItemMenuRadioButton::QueryService()
		{
			if (!m_pService)
				m_pService = new CListItemMenuRadioButtonService(this);
			return m_pService;
		}

		int CListItemMenuRadioButton::getGroupIndex()
		{
			return m_iGroupIndex;
		}

		bool CListItemMenuRadioButton::isChecked()
		{
			return m_bChecked;
		}

		CListItemMenuRadioButton::State CListItemMenuRadioButton::getState()
		{
			if (!isEnabled())
				return State::Disabled;
			if (isActive())
				return State::Active;
			return State::Normal;
		}

		RectF CListItemMenuRadioButton::getIconPadding() const
		{
			return m_sIconPadding;
		}

		RectF CListItemMenuRadioButton::getCaptionPadding() const
		{
			return m_sCaptionPadding;
		}

		RectF CListItemMenuRadioButton::getHotkeyPadding() const
		{
			return m_sHotkeyPadding;
		}

		String CListItemMenuRadioButton::getCaption()
		{
			return m_sCaption;
		}

		Color CListItemMenuRadioButton::getColor(const State state) const
		{
			return m_aColor[(int)state];
		}

		Color CListItemMenuRadioButton::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		int CListItemMenuRadioButton::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CListItemMenuRadioButton::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		Color CListItemMenuRadioButton::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		RectF CListItemMenuRadioButton::getBorderWidth(const State state) const
		{
			return m_aBorderWidth[(int)state];
		}

		RectF CListItemMenuRadioButton::getBorderRadius(const State state) const
		{
			return m_aBorderRadius[(int)state];
		}

		BorderColor CListItemMenuRadioButton::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CListItemMenuRadioButton::getLeftBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Left;
		}

		Color CListItemMenuRadioButton::getTopBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Top;
		}

		Color CListItemMenuRadioButton::getRightBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Right;
		}

		Color CListItemMenuRadioButton::getBottomBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Bottom;
		}

		Gradient *CListItemMenuRadioButton::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		Color CListItemMenuRadioButton::getIconBackgroundColor(const State state) const
		{
			return m_aIconBackgroundColor[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemMenuRadioButton::setSelected(const bool value)
		{
			return false;
		}

		bool CListItemMenuRadioButton::setGroupIndex(const int value)
		{
			if (value != m_iGroupIndex)
			{
				m_iGroupIndex = value;
				if (m_bChecked && HaveCheckedOnParent())
				{
					m_bChecked = false;
					if (OnChange)
						OnChange(this);
				}
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuRadioButton::setChecked(const bool value)
		{
			if (value != m_bChecked)
			{
				m_bChecked = value;
				if (m_bChecked)
					UncheckAllOnParent();
				if (OnChange)
					OnChange(this);
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuRadioButton::setIconPadding(const RectF &value)
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

		bool CListItemMenuRadioButton::setCaptionPadding(const RectF &value)
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

		bool CListItemMenuRadioButton::setHotkeyPadding(const RectF &value)
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

		bool CListItemMenuRadioButton::setCaption(const String &value)
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

		bool CListItemMenuRadioButton::setColor(const State state, const Color &value)
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

		bool CListItemMenuRadioButton::setShadowColor(const State state, const Color &value)
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

		bool CListItemMenuRadioButton::setShadowRadius(const State state, const int value)
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

		bool CListItemMenuRadioButton::setShadowShift(const State state, const PointF &value)
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

		bool CListItemMenuRadioButton::setBackgroundColor(const State state, const Color &value)
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

		bool CListItemMenuRadioButton::setBorderWidth(const State state, const RectF &value)
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

		bool CListItemMenuRadioButton::setBorderRadius(const State state, const RectF &value)
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

		bool CListItemMenuRadioButton::setBorderColor(const State state, const BorderColor &value)
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

		bool CListItemMenuRadioButton::setLeftBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ value, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CListItemMenuRadioButton::setTopBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, value, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CListItemMenuRadioButton::setRightBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, value, m_aBorderColor[(int)state].Bottom });
		}

		bool CListItemMenuRadioButton::setBottomBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, value });
		}

		bool CListItemMenuRadioButton::setIconBackgroundColor(const State state, const Color &value)
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
		void CListItemMenuRadioButton::Render(const Mat4f &matrix, const Block *block, ITexture **clip)
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
				DrawSimpleBackground(
					renderer,
					rect_clip,
					m_aBorderWidth[(int)state],
					m_aBorderRadius[(int)state],
					m_aBorderColor[(int)state],
					m_aBackgroundColor[(int)state],
					m_aBackgroundGradient[(int)state]);
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

		void CListItemMenuRadioButton::RenderParts(const State state, const RectF &rect_clip, IRenderer *renderer, IFont *font, IPlatformFont *pf, const String &hotkeys,
			IListItemMenuOwner *owner, const Color &text_color, const Color &shadow_color, const int shadow_radius, const PointF &shadow_shift)
		{
			PointF caption_size{ pf->getStringSize(m_sCaption, font->Distance) };
			PointF caption_position{ m_fIconWidth + m_sCaptionPadding.Left, std::round((rect_clip.height() - caption_size.Y) * 0.5f) };
			DrawTextShadow(renderer, pf, font->Distance, Identity, rect_clip, caption_position, m_sCaption, shadow_color, shadow_shift, shadow_radius);

			PointF hotkeys_size{ pf->getStringSize(hotkeys, font->Distance) };
			PointF hotkeys_position{
				getSize().X - cast<CListItemMenuRadioButtonService*>(QueryService())->getArrowWidth() - m_fHotkeyWidth + m_sHotkeyPadding.Left,
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
						->DrawRectangle(RectF{ 0, 0, m_fIconWidth, getSize().Y }, m_aIconBackgroundColor[(int)state]);
				}
				else
					renderer->DrawRectangle(RectF{ 0, 0, m_fIconWidth, getSize().Y }, m_aIconBackgroundColor[(int)state]);
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
			// Render icon
			if (owner)
			{
				RectF part;
				ITexture *icon{ FindIcon(part) };
				if (icon)
				{
					RectF rect_icon{ m_sIconPadding.Left, m_sIconPadding.Top, m_fIconWidth - m_sIconPadding.Right, getSize().Y - m_sIconPadding.Bottom };
					if (rect_icon.is_valid() && !rect_icon.is_zero())
					{
						float scale{ ntl::Min<float>(rect_icon.width() / part.width(), rect_icon.height() / part.height()) };
						PointF pos{ (rect_icon.width() - part.width() * scale) * 0.5f, (rect_icon.height() - part.height() * scale) * 0.5f };
						renderer
							->ActivatePrimitiveMatrix(ntl::Mat4Scale<float>(scale, scale, 1) * ntl::Mat4Translate<float>(pos.X + rect_icon.Left, pos.Y + rect_icon.Top, 0))
							->DrawImage(icon, 1, part);
					}
				}
			}
		}
	#pragma endregion
	}
}