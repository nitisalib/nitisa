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
		CListItemCheckBox::CGradientListener::CGradientListener(CListItemCheckBox *control) :
			m_pControl{ control }
		{

		}

		void CListItemCheckBox::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient && m_pControl->QueryService()->getOwner())
				m_pControl->QueryService()->getOwner()->NotifyOnRepaintRequired(m_pControl);
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CListItemCheckBox::CListItemCheckBox() :
			CListItem(L"ListItemCheckBox", false),
			m_cGradientListener{ this },
			m_bChecked{ false },
			m_eAlign{ TextAlign::Left },
			m_sPadding{ 4, 2, 4, 2 },
			m_bTextAtRight{ true },
			m_aColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 109, 109, 109, 255 } },
			m_aShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aShadowRadius{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			m_aShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 0, 0 } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aBorderWidth{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 0, 0, 0, 0 } },
			m_aBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aBorderColor{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } },
				BorderColor{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } },
				BorderColor{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } },
				BorderColor{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
			m_aImagePadding{
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 } },
			m_pService{ nullptr },
			m_bIgnoreGradient{ false },
			OnChange{ nullptr }
		{

		}

		CListItemCheckBox::CListItemCheckBox(const String &caption) : CListItemCheckBox()
		{
			m_sCaption = caption;
		}

		CListItemCheckBox::~CListItemCheckBox()
		{
			if (m_pService)
				m_pService->Release();
		}
	#pragma endregion

	#pragma region Getters
		IListItemService *CListItemCheckBox::QueryService()
		{
			if (!m_pService)
				m_pService = new CListItemCheckBoxService(this);
			return m_pService;
		}

		String CListItemCheckBox::getCaption()
		{
			return m_sCaption;
		}

		bool CListItemCheckBox::isChecked()
		{
			return m_bChecked;
		}

		CListItemCheckBox::State CListItemCheckBox::getState()
		{
			if (!isEnabled())
				return State::Disabled;
			if (isActive())
			{
				if (isSelected())
				{
					if (isHovered())
						return State::ActiveSelectedHovered;
					return State::ActiveSelected;
				}
				if (isHovered())
					return State::ActiveHovered;
				return State::Active;
			}
			if (isSelected())
			{
				if (isHovered())
					return State::SelectedHovered;
				return State::Selected;
			}
			if (isHovered())
				return State::Hovered;
			return State::Normal;
		}

		TextAlign CListItemCheckBox::getAlign()
		{
			return m_eAlign;
		}

		RectF CListItemCheckBox::getPadding() const
		{
			return m_sPadding;
		}

		Color CListItemCheckBox::getColor(const State state) const
		{
			return m_aColor[(int)state];
		}

		Color CListItemCheckBox::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		int CListItemCheckBox::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CListItemCheckBox::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		Color CListItemCheckBox::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CListItemCheckBox::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		RectF CListItemCheckBox::getBorderWidth(const State state) const
		{
			return m_aBorderWidth[(int)state];
		}

		RectF CListItemCheckBox::getBorderRadius(const State state) const
		{
			return m_aBorderRadius[(int)state];
		}

		BorderColor CListItemCheckBox::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CListItemCheckBox::getLeftBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Left;
		}

		Color CListItemCheckBox::getTopBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Top;
		}

		Color CListItemCheckBox::getRightBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Right;
		}

		Color CListItemCheckBox::getBottomBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Bottom;
		}

		bool CListItemCheckBox::isTextAtRight() const
		{
			return m_bTextAtRight;
		}

		RectF CListItemCheckBox::getImagePadding(const State state) const
		{
			return m_aImagePadding[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemCheckBox::setCaption(const String &value)
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

		bool CListItemCheckBox::setChecked(const bool value)
		{
			if (value != m_bChecked)
			{
				m_bChecked = value;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemCheckBox::setAlign(const TextAlign value)
		{
			if (value != m_eAlign)
			{
				m_eAlign = value;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemCheckBox::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				m_sPadding = value;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnSizeChange(this);
				return true;
			}
			return false;
		}

		bool CListItemCheckBox::setColor(const State state, const Color &value)
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

		bool CListItemCheckBox::setShadowColor(const State state, const Color &value)
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

		bool CListItemCheckBox::setShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aShadowRadius[(int)state])
			{
				m_aShadowRadius[(int)state] = value;
				if (isVisible() && getState() == state && m_aShadowColor[(int)state].A > 0 && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemCheckBox::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				m_aShadowShift[(int)state] = value;
				if (isVisible() && getState() == state && m_aShadowColor[(int)state].A > 0 && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemCheckBox::setBackgroundColor(const State state, const Color &value)
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

		bool CListItemCheckBox::setBorderWidth(const State state, const RectF &value)
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

		bool CListItemCheckBox::setBorderRadius(const State state, const RectF &value)
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

		bool CListItemCheckBox::setBorderColor(const State state, const BorderColor &value)
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

		bool CListItemCheckBox::setLeftBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ value, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CListItemCheckBox::setTopBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, value, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CListItemCheckBox::setRightBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, value, m_aBorderColor[(int)state].Bottom });
		}

		bool CListItemCheckBox::setBottomBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, value });
		}

		bool CListItemCheckBox::setTextAtRight(const bool value)
		{
			if (value != m_bTextAtRight)
			{
				m_bTextAtRight = value;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemCheckBox::setImagePadding(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aImagePadding[(int)state]))
			{
				m_aImagePadding[(int)state] = value;
				if (isVisible() && QueryService()->getOwner() && getState() == state)
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Items
		bool CListItemCheckBox::AddItem(IListItem *item)
		{
			return false;
		}

		bool CListItemCheckBox::InsertItem(IListItem *item, const int before)
		{
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CListItemCheckBox::UpdateFromStyle(IStyle *style)
		{
			bool changed{ false };
			m_bIgnoreGradient = true;
			changed = style->getOption(m_sClassName + L".Padding", m_sPadding) || changed;
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String state;
				switch ((State)i)
				{
				case State::Hovered:
					state = L"Hovered";
					break;
				case State::Selected:
					state = L"Selected";
					break;
				case State::SelectedHovered:
					state = L"SelectedHovered";
					break;
				case State::Active:
					state = L"Active";
					break;
				case State::ActiveHovered:
					state = L"ActiveHovered";
					break;
				case State::ActiveSelected:
					state = L"ActiveSelected";
					break;
				case State::ActiveSelectedHovered:
					state = L"ActiveSelectedHovered";
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
				changed = style->getOption(m_sClassName + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]) || changed;
				changed = style->getOption(m_sClassName + L".BorderWidth[" + state + L"]", m_aBorderWidth[i]) || changed;
				changed = style->getOption(m_sClassName + L".BorderRadius[" + state + L"]", m_aBorderRadius[i]) || changed;
				changed = style->getOption(m_sClassName + L".BorderColor[" + state + L"]", m_aBorderColor[i]) || changed;
				changed = style->getOption(m_sClassName + L".ImagePadding[" + state + L"]", m_aImagePadding[i]) || changed;
			}
			m_bIgnoreGradient = false;
			if (changed && QueryService()->getOwner())
				QueryService()->getOwner()->NotifyOnSizeChange(this);
		}

		PointF CListItemCheckBox::CalculateTextPosition()
		{
			IListItemOwner *owner{ QueryService()->getOwner() };
			if (owner && owner->getRenderer() && owner->getFont(this) && owner->getFont(this)->getPlatformFont(owner->getRenderer()))
			{
				IPlatformFont *pf{ owner->getFont(this)->getPlatformFont(owner->getRenderer()) };
				PointF size{ pf->getStringSize(m_sCaption, owner->getFont(this)->Distance) };
				if (m_sCaption.empty())
					size.Y = pf->getStringSize(L"Wy", 0).Y;
				if (m_bTextAtRight)
					return PointF{ getSize().Y + m_sPadding.Left, std::round((getSize().Y + m_sPadding.Top - m_sPadding.Bottom - size.Y) * 0.5f) };
				return PointF{ getSize().X - getSize().Y - m_sPadding.Right - size.X, std::round((getSize().Y + m_sPadding.Top - m_sPadding.Bottom - size.Y) * 0.5f) };
			}
			return PointF{ 0, 0 };
		}

		ITexture *CListItemCheckBox::FindImage(RectF &part)
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

		IListItem *CListItemCheckBox::Clone()
		{
			CListItemCheckBox *result{ new CListItemCheckBox(m_sCaption) };
			Copy(result);
			return result;
		}

		bool CListItemCheckBox::Copy(IListItem *dest)
		{
			CListItemCheckBox *d{ cast<CListItemCheckBox*>(dest) };
			if (d)
			{
				d->m_bChecked = m_bChecked;
				d->m_eAlign = m_eAlign;
				d->m_sPadding = m_sPadding;
				d->m_bTextAtRight = m_bTextAtRight;
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					d->m_aColor[i] = m_aColor[i];
					d->m_aShadowColor[i] = m_aShadowColor[i];
					d->m_aShadowRadius[i] = m_aShadowRadius[i];
					d->m_aShadowShift[i] = m_aShadowShift[i];
					d->m_aBackgroundColor[i] = m_aBackgroundColor[i];
					d->m_aBackgroundGradient[i] = m_aBackgroundGradient[i];
					d->m_aBorderWidth[i] = m_aBorderWidth[i];
					d->m_aBorderRadius[i] = m_aBorderRadius[i];
					d->m_aBorderColor[i] = m_aBorderColor[i];
					d->m_aImagePadding[i] = m_aImagePadding[i];
				}
				return CListItem::Copy(dest);
			}
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CListItemCheckBox::Render(const Mat4f &matrix, const Block *block, ITexture **clip)
		{
			IRenderer *renderer{ QueryService()->getOwner()->getRenderer() };
			IFont *font{ QueryService()->getOwner()->getFont(this) };
			IPlatformFont *pf{ font->getPlatformFont(renderer) };
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
				Color text_color{ m_aColor[(int)state].A > 0 ? m_aColor[(int)state] : font->Color };
				Color shadow_color{ m_aShadowColor[(int)state] };
				int shadow_radius{ m_aShadowRadius[(int)state] };
				PointF shadow_shift{ m_aShadowShift[(int)state] };
				PointF text_position{ CalculateTextPosition() };
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
				RenderParts(state, rect_clip, renderer, font, pf, text_position, text_color, shadow_color, shadow_radius, shadow_shift);
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

		void CListItemCheckBox::RenderParts(const State state, const RectF &rect_clip, IRenderer *renderer, IFont *font, IPlatformFont *pf,
			const PointF &text_position, const Color &text_color, const Color &shadow_color, const int shadow_radius, const PointF &shadow_shift)
		{
			DrawTextShadow(renderer, pf, font->Distance, Identity, rect_clip, text_position, m_sCaption, shadow_color, shadow_shift, shadow_radius);
			// Render image
			RectF image_rect{ m_aImagePadding[(int)state].Left, m_aImagePadding[(int)state].Top, getSize().Y - m_aImagePadding[(int)state].Right, getSize().Y - m_aImagePadding[(int)state].Bottom };
			CStorePrimitiveMatrix s_matrix{ renderer };
			if (image_rect.is_valid() && !image_rect.is_zero())
			{
				RectF part;
				ITexture *image{ FindImage(part) };
				if (image)
				{
					float scale{ ntl::Min<float>(image_rect.width() / part.width(), image_rect.height() / part.height()) };
					PointF pos{ std::round((image_rect.width() - part.width() * scale) * 0.5f), std::round((image_rect.height() - part.height() * scale) * 0.5f) };
					renderer
						->ActivatePrimitiveMatrix(ntl::Mat4Scale<float>(scale, scale, 1) * ntl::Mat4Translate<float>(image_rect.Left + pos.X, image_rect.Top + pos.Y, 0))
						->DrawImage(image, 1, part);
				}
			}
			// Render caption
			if (!m_sCaption.empty())
			{
				renderer
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(text_position.X, text_position.Y, 0))
					->DrawText(m_sCaption, pf, font->Distance, text_color);
			}
		}
	#pragma endregion
	}
}