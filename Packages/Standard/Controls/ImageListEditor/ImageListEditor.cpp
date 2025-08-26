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
		CImageListEditor::CGradientListener::CGradientListener(CImageListEditor *control) :
			m_pControl{ control }
		{

		}

		void CImageListEditor::CGradientListener::NotifyOnChange()
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
		CImageListEditor::CImageListEditor() :
			CControl(L"ImageListEditor", true, true, false, false, false, false),
			m_cGradientListener{ this },
			m_pImageList{ nullptr },
			m_sBorderWidth{ 1, 1, 1, 1 },
			m_sBorderRadius{ 0, 0, 0, 0 },
			m_sPadding{ 4, 4, 4, 4 },
			m_fItemDistance{ 4 },
			m_aBorderColor{
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
				BorderColor{ Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 } },
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } } },
			m_aBackgroundColor{
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aShadowRadius{ 1, 1, 1 },
			m_aItemBorderWidth{ 0, 0, 0, 0, 0, 0 },
			m_aItemBorderColor{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 255, 255 }, Color{ 0, 0, 255, 255 }, Color{ 0, 0, 255, 255 }, Color{ 0, 0, 255, 255 } },
				BorderColor{ Color{ 0, 0, 255, 255 }, Color{ 0, 0, 255, 255 }, Color{ 0, 0, 255, 255 }, Color{ 0, 0, 255, 255 } },
				BorderColor{ Color{ 0, 0, 255, 255 }, Color{ 0, 0, 255, 255 }, Color{ 0, 0, 255, 255 }, Color{ 0, 0, 255, 255 } },
				BorderColor{ Color{ 0, 0, 255, 127 }, Color{ 0, 0, 255, 127 }, Color{ 0, 0, 255, 127 }, Color{ 0, 0, 255, 127 } }},
			m_aItemBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 16 },
				Color{ 0, 0, 255, 127 },
				Color{ 0, 0, 255, 127 },
				Color{ 0, 0, 255, 240 },
				Color{ 0, 0, 0, 0 } },
			m_aItemBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aItemTextColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 133, 135, 139, 255 },
				Color{ 133, 135, 139, 255 } },
			m_aItemTextShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aItemTextShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aItemTextShadowRadius{ 0, 0, 0, 0, 0, 0 },
			m_pCanvas{ nullptr },
			m_pScroll{ nullptr },
			m_cScrollListener{ this },
			m_bIgnoreGradient{ false },
			m_eHoveredElement{ Element::None },
			m_iHoveredItemIndex{ -1 }
		{
			setService(new CImageListEditorService(this), true);
			setSize(PointF{ 320, 80 });
		}

		CImageListEditor::CImageListEditor(IControl *parent) :CImageListEditor()
		{
			setParent(parent);
		}

		CImageListEditor::CImageListEditor(IForm *parent) : CImageListEditor()
		{
			setForm(parent);
		}

		CImageListEditor::~CImageListEditor()
		{
			if (m_pScroll)
				m_pScroll->Release();
		}
	#pragma endregion

	#pragma region Interface getters
		RectF CImageListEditor::getClientRect()
		{
			RectF result{
				m_sBorderWidth.Left + m_sPadding.Left,
				m_sBorderWidth.Top + m_sPadding.Top,
				getWidth() - m_sBorderWidth.Right - m_sPadding.Right,
				getHeight() - m_sBorderWidth.Bottom - m_sPadding.Bottom - getScroll()->getHeight()
			};
			result.validate();
			return result;
		}

		RectF CImageListEditor::getRenderRect()
		{
			RectF result{ getRenderRect(State::Normal) };
			for (int i = 1; i <= (int)State::Disabled; i++)
				result += getRenderRect((State)i);
			return result;
		}

		IImageList *CImageListEditor::getImageList()
		{
			return m_pImageList;
		}

		int CImageListEditor::getImageCount()
		{
			if (m_pImageList)
				return m_pImageList->getImageCount();
			return 0;
		}

		Image *CImageListEditor::getImage(const int index)
		{
			if (m_pImageList)
				return m_pImageList->getImage(index);
			return nullptr;
		}

		bool CImageListEditor::isImageSelected(const int index)
		{
			if (index >= 0 && index < (int)m_aItems.size())
				return m_aItems[index].Selected;
			return false;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CImageListEditor::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				getScroll()->setDPI(value);
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sBorderWidth *= s;
				m_sBorderRadius *= avg;
				m_sPadding *= s;
				m_fItemDistance *= s.X;
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aShadowShift[i] *= s;
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
					m_aItemBorderWidth[i] *= s;
					m_aItemTextShadowShift[i] *= s;
					m_aItemTextShadowRadius[i] = ntl::Round<int>((float)m_aItemTextShadowRadius[i] * avg);
				}
				Update();
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImageListEditor::setImageList(IImageList *value)
		{
			if (value != m_pImageList)
			{
				m_pImageList = value;
				m_aItems.clear();
				if (m_eHoveredElement == Element::Item)
				{
					m_eHoveredElement = Element::None;
					m_iHoveredItemIndex = -1;
				}
				ImageListChange(m_pImageList);
				return true;
			}
			return false;
		}

		bool CImageListEditor::setImageSelected(const int index, const bool value)
		{
			if (index >= 0 && index < (int)m_aItems.size() && m_aItems[index].Selected != value)
			{
				m_aItems[index].Selected = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface helpers
		void CImageListEditor::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			getScroll()->Refresh();
		}

		bool CImageListEditor::DeleteSelectedImages()
		{
			CLockRepaint lock{ this };
			bool found, result{ false };
			do
			{
				found = false;
				for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
					if (pos->Selected)
					{
						found = result = true;
						m_pImageList->DeleteImage(int(pos - m_aItems.begin()));
						break;
					}
			} while (found);
			return result;
		}
	#pragma endregion

	#pragma region Getters
		CImageListEditor::State CImageListEditor::getState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (isHovered())
				return State::Hovered;
			return State::Normal;
		}

		CImageListEditor::ItemState CImageListEditor::getItemState(const int index)
		{
			// THIS IS WRONG!!!
			if (index >= 0 && index < (int)m_aItems.size())
			{
				if (!isEnabled(false))
					return m_aItems[index].Selected ? ItemState::SelectedDisabled : ItemState::Disabled;
				if (m_eHoveredElement == Element::Item && m_iHoveredItemIndex == index)
					return m_aItems[index].Selected ? ItemState::SelectedHovered : ItemState::Hovered;
				return m_aItems[index].Selected ? ItemState::Selected : ItemState::Normal;
			}
			return ItemState::Normal;
		}

		RectF CImageListEditor::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		RectF CImageListEditor::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		RectF CImageListEditor::getPadding() const
		{
			return m_sPadding;
		}

		float CImageListEditor::getItemDistance() const
		{
			return m_fItemDistance;
		}

		BorderColor CImageListEditor::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CImageListEditor::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CImageListEditor::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		Color CImageListEditor::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		PointF CImageListEditor::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		int CImageListEditor::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		RectF CImageListEditor::getItemBorderWidth(const ItemState state) const
		{
			return m_aItemBorderWidth[(int)state];
		}

		BorderColor CImageListEditor::getItemBorderColor(const ItemState state) const
		{
			return m_aItemBorderColor[(int)state];
		}

		Color CImageListEditor::getItemBackgroundColor(const ItemState state) const
		{
			return m_aItemBackgroundColor[(int)state];
		}

		Gradient *CImageListEditor::getItemBackgroundGradient(const ItemState state)
		{
			return &m_aItemBackgroundGradient[(int)state];
		}

		Color CImageListEditor::getItemTextColor(const ItemState state) const
		{
			return m_aItemTextColor[(int)state];
		}

		Color CImageListEditor::getItemTextShadowColor(const ItemState state) const
		{
			return m_aItemTextShadowColor[(int)state];
		}

		PointF CImageListEditor::getItemTextShadowShift(const ItemState state) const
		{
			return m_aItemTextShadowShift[(int)state];
		}

		int CImageListEditor::getItemTextShadowRadius(const ItemState state) const
		{
			return m_aItemTextShadowRadius[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CImageListEditor::setScroll(IBuiltInScroll *value)
		{
			if (value && value != m_pScroll)
			{
				if (value->isVertical())
				{
					value->setVertical(false);
					value->setSize({ value->getHeight(), value->getWidth() });
				}
				value->setListener(&m_cScrollListener);
				if (m_pScroll)
					m_pScroll->Release();
				m_pScroll = value;
				Update();
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImageListEditor::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				m_sBorderWidth = value;
				Update();
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImageListEditor::setBorderRadius(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderRadius))
			{
				m_sBorderRadius = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImageListEditor::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				m_sPadding = value;
				Update();
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImageListEditor::setItemDistance(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fItemDistance))
			{
				m_fItemDistance = value;
				Update();
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImageListEditor::setBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
				if (getState() == state && m_sBorderWidth.has_positive())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CImageListEditor::setBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
				if (getState() == state && m_aBackgroundGradient[(int)state].getPointCount() < 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CImageListEditor::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
				CLockRepaint lock{ this };
				if (getState() == state)
					Repaint(false);
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

		bool CImageListEditor::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				if (getState() == state && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowShift[(int)state] = value;
				if (getState() == state && m_aShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CImageListEditor::setShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				if (getState() == state && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowRadius[(int)state] = value;
				if (getState() == state && m_aShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CImageListEditor::setItemBorderWidth(const ItemState state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aItemBorderWidth[(int)state]))
			{
				m_aItemBorderWidth[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImageListEditor::setItemBorderColor(const ItemState state, const BorderColor &value)
		{
			if (value != m_aItemBorderColor[(int)state])
			{
				m_aItemBorderColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImageListEditor::setItemBackgroundColor(const ItemState state, const Color &value)
		{
			if (value != m_aItemBackgroundColor[(int)state])
			{
				m_aItemBackgroundColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImageListEditor::setItemTextColor(const ItemState state, const Color &value)
		{
			if (value != m_aItemTextColor[(int)state])
			{
				m_aItemTextColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImageListEditor::setItemTextShadowColor(const ItemState state, const Color &value)
		{
			if (value != m_aItemTextShadowColor[(int)state])
			{
				m_aItemTextShadowColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImageListEditor::setItemTextShadowShift(const ItemState state, const PointF &value)
		{
			if (IsNotEqual(value, m_aItemTextShadowShift[(int)state]))
			{
				m_aItemTextShadowShift[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImageListEditor::setItemTextShadowRadius(const ItemState state, const int value)
		{
			if (value >= 1 && value != m_aItemTextShadowRadius[(int)state])
			{
				m_aItemTextShadowRadius[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CImageListEditor::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BorderWidth", m_sBorderWidth);
			style->getOption(m_sClassName + L".BorderRadius", m_sBorderRadius);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			style->getOption(m_sClassName + L".ItemDistance", m_fItemDistance);
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String name;
				switch ((State)i)
				{
				case State::Normal:
					name = L"Normal";
					break;
				case State::Hovered:
					name = L"Hovered";
					break;
				default:
					name = L"Disabled";
				}
				style->getOption(m_sClassName + L".BorderColor[" + name + L"]", m_aBorderColor[i]);
				style->getOption(m_sClassName + L".BackgroundColor[" + name + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackgroundGradient[" + name + L"]", m_aBackgroundGradient[i]);
				style->getOption(m_sClassName + L".ShadowColor[" + name + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + name + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L".ShadowRadius[" + name + L"]", m_aShadowRadius[i]);
			}
			for (int i = 0; i <= (int)ItemState::Disabled; i++)
			{
				String name;
				switch ((ItemState)i)
				{
				case ItemState::Normal:
					name = L"Normal";
					break;
				case ItemState::Hovered:
					name = L"Hovered";
					break;
				case ItemState::Selected:
					name = L"Selected";
					break;
				case ItemState::SelectedHovered:
					name = L"SelectedHovered";
					break;
				case ItemState::SelectedDisabled:
					name = L"SelectedDisabled";
					break;
				default:
					name = L"Disabled";
				}
				style->getOption(m_sClassName + L".ItemBorderWidth[" + name + L"]", m_aItemBorderWidth[i]);
				style->getOption(m_sClassName + L".ItemBorderColor[" + name + L"]", m_aItemBorderColor[i]);
				style->getOption(m_sClassName + L".ItemBackgroundColor[" + name + L"]", m_aItemBackgroundColor[i]);
				style->getOption(m_sClassName + L".ItemBackgroundGradient[" + name + L"]", m_aItemBackgroundGradient[i]);
				style->getOption(m_sClassName + L".ItemTextColor[" + name + L"]", m_aItemTextColor[i]);
				style->getOption(m_sClassName + L".ItemTextShadowColor[" + name + L"]", m_aItemTextShadowColor[i]);
				style->getOption(m_sClassName + L".ItemTextShadowShift[" + name + L"]", m_aItemTextShadowShift[i]);
				style->getOption(m_sClassName + L".ItemTextShadowRadius[" + name + L"]", m_aItemTextShadowRadius[i]);
			}
			Update();
			UpdateHoveredElement();
			m_bIgnoreGradient = false;
		}

		RectF CImageListEditor::getRenderRect(const State state)
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
		}

		IBuiltInScroll *CImageListEditor::getScroll()
		{
			if (!m_pScroll)
			{
				CScroll *scroll{ new CScroll(this) };
				if (scroll->isVertical())
					scroll->SwitchDirection(true);
				scroll->setListener(&m_cScrollListener);
				m_pScroll = scroll;
			}
			return m_pScroll;
		}

		bool CImageListEditor::UpdateHoveredElement()
		{
			if (getForm())
				return UpdateHoveredElement(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())));
			return false;
		}

		bool CImageListEditor::UpdateHoveredElement(const PointF &position)
		{
			Element elem{ Element::None };
			int elem_index{ -1 };
			if (isEnabled(true) && position.X >= 0 && position.X < getWidth() && position.Y >= 0 && position.Y < getHeight())
			{
				RectF client{ m_sBorderWidth.Left, getHeight() - m_sBorderWidth.Bottom - getScroll()->getHeight(), getWidth() - m_sBorderWidth.Right, getHeight() - m_sBorderWidth.Bottom };
				if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
					elem = Element::Scroll;
				if (elem == Element::None)
				{
					client = getClientRect();
					if (getScroll()->isEnabled())
						client.Left += getScroll()->getScroll();
					client.Right = client.Left + client.height();
					if (client.is_valid() && !client.is_zero())
						for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
						{
							if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
							{
								elem = Element::Item;
								elem_index = int(pos - m_aItems.begin());
								break;
							}
							client.Left += client.height() + m_fItemDistance;
							client.Right += client.height() + m_fItemDistance;
						}
				}
			}
			if (elem != m_eHoveredElement || elem_index != m_iHoveredItemIndex)
			{
				switch (m_eHoveredElement)
				{
				case Element::Scroll:
					getScroll()->NotifyOnMouseLeave();
					break;
				default:
					break;
				}
				m_eHoveredElement = elem;
				m_iHoveredItemIndex = elem_index;
				switch (m_eHoveredElement)
				{
				case Element::Scroll:
					getScroll()->NotifyOnMouseHover(PointF{ position.X - m_sBorderWidth.Left, position.Y - (getHeight() - m_sBorderWidth.Bottom - getScroll()->getHeight()) });
					break;
				default:
					break;
				}
				return true;
			}
			return false;
		}

		void CImageListEditor::Update()
		{
			float item_height{ ntl::Max<float>(0, getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom - m_sPadding.Top - m_sPadding.Bottom - getScroll()->getHeight()) };
			float required_width{ item_height * (float)m_aItems.size() }, client_width{ ntl::Max<float>(0, getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - m_sPadding.Left - m_sPadding.Right) };
			if (m_aItems.size() > 1)
				required_width += m_fItemDistance * float(m_aItems.size() - 1);
			getScroll()->setPosition(PointF{ m_sBorderWidth.Left, getHeight() - m_sBorderWidth.Bottom - getScroll()->getHeight() });
			getScroll()->setSize(PointF{ getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right, getScroll()->getHeight() });
			getScroll()->setEnabled(ntl::IsGreater<float>(required_width, client_width));
			if (ntl::IsGreater<float>(required_width, client_width))
				getScroll()->setMax(required_width - client_width);
			if (!isEnabled(false))
				getScroll()->setEnabled(false);
		}

		void CImageListEditor::ImageListDetach(IImageList *imagelist)
		{
			if (m_pImageList && imagelist == m_pImageList)
			{
				m_pImageList = nullptr;
				m_aItems.clear();
				if (m_eHoveredElement == Element::Item)
				{
					m_eHoveredElement = Element::None;
					m_iHoveredItemIndex = -1;
				}
				Update();
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
		}

		void CImageListEditor::ImageListChange(IImageList *imagelist)
		{
			if (m_pImageList && imagelist == m_pImageList)
			{
				std::vector<ITEM> items;
				for (int i = 0; i < m_pImageList->getImageCount(); i++)
				{
					bool found{ false };
					for (auto pos : m_aItems)
						if (pos.Bmp == m_pImageList->getImage(i))
						{
							items.push_back({ pos.Bmp, pos.Selected });
							found = true;
							break;
						}
					if (!found)
						items.push_back({ m_pImageList->getImage(i), false });
				}
				m_aItems = items;
				if (m_eHoveredElement == Element::Item)
				{
					m_eHoveredElement = Element::None;
					m_iHoveredItemIndex = -1;
				}
				Update();
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Paint
		void CImageListEditor::Render()
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

				IPlatformFont *pf{ getFont()->getPlatformFont(renderer) };
				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
				Block b{ rect, AddElements(m_sBorderWidth, m_sPadding), m_sBorderRadius, PointLocation::Inside };
				b.Border.Bottom += getScroll()->getHeight();
				DrawBlockShadow(renderer, rect, m_sBorderRadius, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
				DrawSimpleBackground(renderer, rect, m_sBorderWidth, m_sBorderRadius, m_aBorderColor[(int)state], m_aBackgroundColor[(int)state], m_aBackgroundGradient[(int)state]);
				RenderItems(renderer, pf, &b);
				b.Border = m_sBorderWidth;
				RenderScroll(renderer, &b);
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}

		void CImageListEditor::RenderItems(IRenderer *renderer, IPlatformFont *pf, const Block *block)
		{
			if (m_aItems.size() > 0)
			{
				float item_width{ getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom - m_sPadding.Top - m_sPadding.Bottom - getScroll()->getHeight() };
				if (ntl::IsGreater<float>(item_width, 0) && ntl::IsGreater<float>(getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - m_sPadding.Left - m_sPadding.Right, 0))
				{
					ITexture *item{ renderer->CreateTexture(ntl::Round<int>(item_width), ntl::Round<int>(item_width), 1, TextureFormat::RGBA, true) };
					if (item)
					{
						float x{ m_sBorderWidth.Left + m_sPadding.Left }, y{ m_sBorderWidth.Top + m_sPadding.Top };
						if (getScroll()->isEnabled())
							x -= getScroll()->getScroll();
						RectF client{ getClientRect() };
						float line_height{ pf->getStringSize(L"Wy", 0).Y };
						Mat4f s, t;
						IFont *font{ getFont() };
						for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
						{
							if (x < client.Right && x + item_width >= client.Left)
							{
								int index{ int(pos - m_aItems.begin()) };
								PointF image_size{ 0, 0 };
								ItemState istate{ getItemState(index) };
								renderer
									->ActivateTarget(item)
									->Clear(Color{ 0, 0, 0, 0 });
								DrawSimpleBackground(
									renderer,
									RectF{ 0, 0, item_width, item_width },
									m_aItemBorderWidth[(int)istate],
									RectF{ 0, 0, 0, 0 },
									m_aItemBorderColor[(int)istate],
									m_aItemBackgroundColor[(int)istate],
									m_aItemBackgroundGradient[(int)istate]);
								if (item_width > line_height)
								{
									ITexture *image{ m_pImageList->getTexture(index) };
									if (image)
									{
										image_size.X = image->Widthf;
										image_size.Y = image->Heightf;
										float scale{ ntl::Min<float>((item_width - line_height) / image_size.X, (item_width - line_height) / image_size.Y) };
										ntl::Scale<float>(s, scale, scale, 1);
										ntl::Translate<float>(t, (item_width - scale * image_size.X) * 0.5f, 0, 0);
										CStorePrimitiveMatrix s_matrix{ renderer };
										renderer
											->ActivatePrimitiveMatrix(t * s)
											->DrawImage(image, 1);
									}
								}
								Color caption_shadow_color{ m_aItemTextShadowColor[(int)istate].A > 0 ? m_aItemTextShadowColor[(int)istate] : font->ShadowColor };
								String caption{ ToString(index) + L" - " + ToString(ntl::Round<int>(image_size.X)) + L"x" + ToString(ntl::Round<int>(image_size.Y)) };
								float caption_width{ pf->getStringSize(caption, font->Distance).X };
								PointF pos{ std::round((item_width - caption_width) / 2), std::round(item_width - line_height) };
								if (caption_shadow_color.A > 0)
								{
									DrawTextShadow(
										renderer,
										pf,
										font->Distance,
										t,
										RectF{ 0, 0, item_width, item_width },
										pos,
										caption,
										m_aItemTextShadowColor[(int)istate],
										m_aItemTextShadowShift[(int)istate],
										m_aItemTextShadowRadius[(int)istate]);
								}
								Color caption_color{ m_aItemTextColor[(int)istate].A > 0 ? m_aItemTextColor[(int)istate] : font->Color };
								CStoreBlock s_block{ renderer };
								CStorePrimitiveMatrix s_matrix{ renderer };
								if (caption_color.A > 0)
								{
									renderer
										->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(pos.X, pos.Y, 0))
										->DrawText(caption, pf, font->Distance, caption_color);
								}
								renderer
									->ActivateTarget(m_pCanvas)
									->ActivateBlock(block)
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(x + block->Rect.Left, y + block->Rect.Top, 1))
									->DrawImage(item, 1);
							}
							x += item_width + m_fItemDistance;
						}
						item->Release();
					}
				}
			}
		}

		void CImageListEditor::RenderScroll(IRenderer *renderer, const Block *block)
		{
			getScroll()->Render(false, ntl::Mat4Translate<float>(block->Rect.Left + getScroll()->getLeft(), block->Rect.Top + getScroll()->getTop(), 0), block);
		}
	#pragma endregion
	}
}