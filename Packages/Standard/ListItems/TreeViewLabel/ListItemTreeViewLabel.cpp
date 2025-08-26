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
		CListItemTreeViewLabel::CGradientListener::CGradientListener(CListItemTreeViewLabel *control) :
			m_pControl{ control }
		{

		}

		void CListItemTreeViewLabel::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient && m_pControl->QueryService()->getOwner())
				m_pControl->QueryService()->getOwner()->NotifyOnRepaintRequired(m_pControl);
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CListItemTreeViewLabel::CListItemTreeViewLabel() :
			CListItem(L"ListItemTreeViewLabel", true),
			m_cGradientListener{ this },
			m_iIconIndex{ -1 },
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
			m_aPadding{
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 } },
			m_aIconPadding{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aBorderColor{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } },
				BorderColor{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } },
				BorderColor{ Color{ 255, 0, 0, 255 }, Color{ 255, 0, 0, 255 }, Color{ 255, 0, 0, 255 }, Color{ 255, 0, 0, 255 } },
				BorderColor{ Color{ 255, 0, 0, 255 }, Color{ 255, 0, 0, 255 }, Color{ 255, 0, 0, 255 }, Color{ 255, 0, 0, 255 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
			m_aBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 32 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 32 },
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
			m_aColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 133, 135, 139, 255 } },
			m_pService{ nullptr },
			m_bIgnoreGradient{ false }
		{

		}

		CListItemTreeViewLabel::CListItemTreeViewLabel(const String &caption) :CListItemTreeViewLabel()
		{
			m_sCaption = caption;
		}

		CListItemTreeViewLabel::~CListItemTreeViewLabel()
		{
			if (m_pService)
				m_pService->Release();
		}
	#pragma endregion

	#pragma region Interface getters
		IListItemTreeViewLabel *CListItemTreeViewLabel::getSpecificItem(const int index)
		{
			return cast<IListItemTreeViewLabel*>(CListItem::getItem(index));
		}

		String CListItemTreeViewLabel::getCaption()
		{
			return m_sCaption;
		}

		int CListItemTreeViewLabel::getIconIndex()
		{
			return m_iIconIndex;
		}
	#pragma endregion

	#pragma region Getters
		CListItemTreeViewLabel::State CListItemTreeViewLabel::getState()
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

		RectF CListItemTreeViewLabel::getBorderWidth(const State state) const
		{
			return m_aBorderWidth[(int)state];
		}

		RectF CListItemTreeViewLabel::getBorderRadius(const State state) const
		{
			return m_aBorderRadius[(int)state];
		}

		RectF CListItemTreeViewLabel::getPadding(const State state) const
		{
			return m_aPadding[(int)state];
		}

		RectF CListItemTreeViewLabel::getIconPadding(const State state) const
		{
			return m_aIconPadding[(int)state];
		}

		BorderColor CListItemTreeViewLabel::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CListItemTreeViewLabel::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CListItemTreeViewLabel::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		Color CListItemTreeViewLabel::getColor(const State state) const
		{
			return m_aColor[(int)state];
		}
	#pragma endregion

	#pragma region Interface setters
		bool CListItemTreeViewLabel::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				if (QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnSizeChange(this);
				return true;
			}
			return false;
		}

		bool CListItemTreeViewLabel::setIconIndex(const int value)
		{
			if (value < 0 && m_iIconIndex < 0)
				return false;
			if (value != m_iIconIndex)
			{
				m_iIconIndex = value < 0 ? -1 : value;
				if (QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemTreeViewLabel::setBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBorderWidth[(int)state]))
			{
				m_aBorderWidth[(int)state] = value;
				if (getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemTreeViewLabel::setBorderRadius(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBorderRadius[(int)state]))
			{
				m_aBorderRadius[(int)state] = value;
				if (getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemTreeViewLabel::setPadding(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aPadding[(int)state]))
			{
				m_aPadding[(int)state] = value;
				if (getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnSizeChange(this);
				return true;
			}
			return false;
		}

		bool CListItemTreeViewLabel::setIconPadding(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aIconPadding[(int)state]))
			{
				m_aIconPadding[(int)state] = value;
				if (getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemTreeViewLabel::setBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
				if (getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemTreeViewLabel::setBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
				if (getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemTreeViewLabel::setColor(const State state, const Color &value)
		{
			if (value != m_aColor[(int)state])
			{
				m_aColor[(int)state] = value;
				if (getState() == state && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Items
		bool CListItemTreeViewLabel::Add(const String &caption)
		{
			return CListItem::AddItem(new CListItemTreeViewLabel(caption));
		}

		bool CListItemTreeViewLabel::Add(IListItemTreeViewLabel *item)
		{
			return CListItem::AddItem(item);
		}

		bool CListItemTreeViewLabel::Insert(const String &caption, const int before)
		{
			return CListItem::InsertItem(new CListItemTreeViewLabel(caption), before);
		}

		bool CListItemTreeViewLabel::Insert(IListItemTreeViewLabel *item, const int before)
		{
			return CListItem::InsertItem(item, before);
		}
	#pragma endregion

	#pragma region Interface helpers
		IListItem *CListItemTreeViewLabel::Clone()
		{
			CListItemTreeViewLabel *result{ new CListItemTreeViewLabel() };
			Copy(result);
			return result;
		}

		bool CListItemTreeViewLabel::Copy(IListItem *dest)
		{
			CListItemTreeViewLabel *d{ cast<CListItemTreeViewLabel*>(dest) };
			if (d)
			{
				d->m_sCaption = m_sCaption;
				d->m_iIconIndex = m_iIconIndex;
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					d->m_aBorderWidth[i] = m_aBorderWidth[i];
					d->m_aBorderRadius[i] = m_aBorderRadius[i];
					d->m_aPadding[i] = m_aPadding[i];
					d->m_aIconPadding[i] = m_aIconPadding[i];
					d->m_aBorderColor[i] = m_aBorderColor[i];
					d->m_aBackgroundColor[i] = m_aBackgroundColor[i];
					d->m_aBackgroundGradient[i] = m_aBackgroundGradient[i];
					d->m_aColor[i] = m_aColor[i];
				}
				return CListItem::Copy(d);
			}
			return false;
		}

		IListItemService *CListItemTreeViewLabel::QueryService()
		{
			if (!m_pService)
				m_pService = new CListItemTreeViewLabelService(this);
			return m_pService;
		}
	#pragma endregion

	#pragma region Helpers
		void CListItemTreeViewLabel::UpdateFromStyle(IStyle *style)
		{
			bool changed{ false };
			m_bIgnoreGradient = true;
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
				changed = style->getOption(m_sClassName + L".BorderWidth[" + state + L"]", m_aBorderWidth[i]) || changed;
				changed = style->getOption(m_sClassName + L".BorderRadius[" + state + L"]", m_aBorderRadius[i]) || changed;
				changed = style->getOption(m_sClassName + L".Padding[" + state + L"]", m_aPadding[i]) || changed;
				changed = style->getOption(m_sClassName + L".IconPadding[" + state + L"]", m_aIconPadding[i]) || changed;
				changed = style->getOption(m_sClassName + L".BorderColor[" + state + L"]", m_aBorderColor[i]) || changed;
				changed = style->getOption(m_sClassName + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]) || changed;
				changed = style->getOption(m_sClassName + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]) || changed;
				changed = style->getOption(m_sClassName + L".Color[" + state + L"]", m_aColor[i]) || changed;
			}
			m_bIgnoreGradient = false;
			if (changed && QueryService()->getOwner())
				QueryService()->getOwner()->NotifyOnSizeChange(this);
		}

		Color CListItemTreeViewLabel::getCustomColor(const State state)
		{
			if (m_aColor[(int)state].A > 0)
				return m_aColor[(int)state];
			if (QueryService()->getOwner())
				return QueryService()->getOwner()->getFont(this)->Color;
			return m_aColor[(int)state];
		}
	#pragma endregion

	#pragma region Paint
		void CListItemTreeViewLabel::Render(const Mat4f &matrix, const Block *block, ITexture **clip)
		{
			IRenderer *renderer{ QueryService()->getOwner()->getRenderer() };
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
				IBaseTexture *old{ renderer->ActiveTarget };
				renderer
					->ActivateTarget(clip_internal)
					->Clear(Color{ 0, 0, 0, 0 });
				DrawSimpleBackground(
					renderer,
					RectF{ 0, 0, getSize().X, getSize().Y },
					m_aBorderWidth[(int)state],
					m_aBorderRadius[(int)state],
					m_aBorderColor[(int)state],
					m_aBackgroundColor[(int)state],
					m_aBackgroundGradient[(int)state]);
				CStoreBlock s_block{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				RenderIcon(renderer, state);
				RenderCaption(renderer, state);
				renderer
					->ActivateTarget(old)
					->ActivateBlock(block)
					->ActivatePrimitiveMatrix(matrix)
					->DrawImage(clip_internal, 1);
				if (!clip)
					clip_internal->Release();
			}
		}

		void CListItemTreeViewLabel::RenderIcon(IRenderer *renderer, const State state)
		{
			if (m_iIconIndex >= 0 && QueryService()->getOwner())
			{
				RectF r{ m_aIconPadding[(int)state].Left, m_aIconPadding[(int)state].Top, getSize().Y - m_aIconPadding[(int)state].Right, getSize().Y - m_aIconPadding[(int)state].Bottom };
				if (r.is_valid() && !r.is_zero())
				{
					IListItemOwnerTreeViewLabel *owner{ cast<IListItemOwnerTreeViewLabel*>(QueryService()->getOwner()) };
					if (owner && owner->getImageList())
					{
						ITexture *icon{ owner->getImageList()->getTexture(m_iIconIndex) };
						if (icon)
						{
							Block b{ RectF{ 0, 0, getSize().X, getSize().Y }, m_aBorderWidth[(int)state], m_aBorderRadius[(int)state], PointLocation::Inside };
							renderer
								->ActivateBlock(&b)
								->ActivatePrimitiveMatrix(ntl::Mat4Scale<float>(r.width() / icon->Widthf, r.height() / icon->Heightf, 1) * ntl::Mat4Translate<float>(r.Left, r.Top, 0))
								->DrawImage(icon, 1);
						}
					}
				}
			}
		}

		void CListItemTreeViewLabel::RenderCaption(IRenderer *renderer, const State state)
		{
			if (m_sCaption.length() > 0 && QueryService()->getOwner() && QueryService()->getOwner()->getFont(this))
			{
				IFont *font{ QueryService()->getOwner()->getFont(this) };
				IPlatformFont *pf{ font->getPlatformFont(renderer) };
				Color color{ getCustomColor(state) };
				if (pf && color.A > 0)
				{
					IListItemOwnerTreeViewLabel *owner{ cast<IListItemOwnerTreeViewLabel*>(QueryService()->getOwner()) };
					Block b{ RectF{ 0, 0, getSize().X, getSize().Y }, RectF{ m_aPadding[(int)state].Left, m_aPadding[(int)state].Top, m_aPadding[(int)state].Right, m_aPadding[(int)state].Bottom }, m_aBorderRadius[(int)state], PointLocation::Inside };
					PointF size{ pf->getStringSize(m_sCaption, font->Distance) };
					float y{ m_aPadding[(int)state].Top + (getSize().Y - m_aPadding[(int)state].Top - m_aPadding[(int)state].Bottom - size.Y) / 2 };
					PointF p{ m_aPadding[(int)state].Left, y };
					if (owner && owner->getImageList())
					{
						p.X += getSize().Y;
						b.Border.Left += getSize().Y;
					}
					renderer
						->ActivateBlock(&b)
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(p.X, p.Y, 0))
						->DrawText(m_sCaption, pf, font->Distance, color);
				}
			}
		}
	#pragma endregion
	}
}