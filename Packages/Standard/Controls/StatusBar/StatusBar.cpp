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
		CStatusBar::CGradientListener::CGradientListener(CStatusBar *control) :
			m_pControl{ control }
		{

		}

		void CStatusBar::CGradientListener::NotifyOnChange()
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
		CStatusBar::CStatusBar() :
			CControlItemList(L"StatusBar", true, false, false, false, false, false),
			m_cGradientListener{ this },
			m_sOuterBorderWidth{ 0, 1, 0, 0 },
			m_sInnerBorderWidth{ 1, 1, 1, 1 },
			m_sBorderRadius{ 0, 0, 0, 0 },
			m_sOuterBorderColor{ Color{ 0, 0, 0, 0 }, Color{ 145, 145, 145, 255 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			m_sInnerBorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
			m_sBackgroundColor{ 240, 240, 240, 255 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_sShadowColor{ 0, 0, 0, 0 },
			m_sShadowShift{ 0, 0 },
			m_iShadowRadius{ 1 },
			m_fSeparatorWidth{ 1 },
			m_sSeparatorColor{ 215, 215, 215, 255 },
			m_cSeparatorGradient{ &m_cGradientListener },
			m_bIgnoreGradient{ false },
			m_pListItemOwner{ nullptr },
			m_pCanvas{ nullptr }
		{
			setService(new CStatusBarService(this), true);
			setTransform(new CStatusBarTransform());
			CControl::setAlign(Align::Bottom);
			setHeight(18);
		}

		CStatusBar::CStatusBar(IForm *parent) :CStatusBar()
		{
			setForm(parent);
		}

		CStatusBar::~CStatusBar()
		{
			if (m_pListItemOwner)
				m_pListItemOwner->Release();
		}
	#pragma endregion

	#pragma region Interfaces getters
		RectF CStatusBar::getClientRect()
		{
			RectF result{
				m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left, m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top,
				getWidth() - m_sOuterBorderWidth.Right - m_sInnerBorderWidth.Right, getHeight() - m_sOuterBorderWidth.Bottom - m_sInnerBorderWidth.Bottom };
			result.validate();
			return result;
		}

		RectF CStatusBar::getRenderRect()
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_sShadowColor, m_sShadowShift, m_iShadowRadius);
		}

		IListItemOwner *CStatusBar::QueryListItemOwner()
		{
			if (!m_pListItemOwner)
				m_pListItemOwner = new CStatusBarListItemOwner(this);
			return m_pListItemOwner;
		}

		IListItemStatusPanelLabel *CStatusBar::getPanel(const int index)
		{
			return cast<IListItemStatusPanelLabel*>(getItem(index));
		}

		IListItemStatusPanelLabel *CStatusBar::getPanel(const String &name)
		{
			IListItemStatusPanelLabel *result;
			for (int i = 0; i < getItemCount(); i++)
				if (getItem(i)->Name == name && (result = cast<IListItemStatusPanelLabel*>(getItem(i))))
					return result;
			return nullptr;
		}
	#pragma endregion

	#pragma region Getters
		RectF CStatusBar::getOuterBorderWidth() const
		{
			return m_sOuterBorderWidth;
		}

		RectF CStatusBar::getInnerBorderWidth() const
		{
			return m_sInnerBorderWidth;
		}

		RectF CStatusBar::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		BorderColor CStatusBar::getOuterBorderColor() const
		{
			return m_sOuterBorderColor;
		}

		Color CStatusBar::getLeftOuterBorderColor() const
		{
			return m_sOuterBorderColor.Left;
		}

		Color CStatusBar::getTopOuterBorderColor() const
		{
			return m_sOuterBorderColor.Top;
		}

		Color CStatusBar::getRightOuterBorderColor() const
		{
			return m_sOuterBorderColor.Right;
		}

		Color CStatusBar::getBottomOuterBorderColor() const
		{
			return m_sOuterBorderColor.Bottom;
		}

		BorderColor CStatusBar::getInnerBorderColor() const
		{
			return m_sInnerBorderColor;
		}

		Color CStatusBar::getLeftInnerBorderColor() const
		{
			return m_sInnerBorderColor.Left;
		}

		Color CStatusBar::getTopInnerBorderColor() const
		{
			return m_sInnerBorderColor.Top;
		}

		Color CStatusBar::getRightInnerBorderColor() const
		{
			return m_sInnerBorderColor.Right;
		}

		Color CStatusBar::getBottomInnerBorderColor() const
		{
			return m_sInnerBorderColor.Bottom;
		}

		Color CStatusBar::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CStatusBar::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		Color CStatusBar::getShadowColor() const
		{
			return m_sShadowColor;
		}

		PointF CStatusBar::getShadowShift() const
		{
			return m_sShadowShift;
		}

		int CStatusBar::getShadowRadius() const
		{
			return m_iShadowRadius;
		}

		float CStatusBar::getSeparatorWidth() const
		{
			return m_fSeparatorWidth;
		}

		Color CStatusBar::getSeparatorColor() const
		{
			return m_sSeparatorColor;
		}

		Gradient *CStatusBar::getSeparatorGradient()
		{
			return &m_cSeparatorGradient;
		}
	#pragma endregion

	#pragma region Interfaces setters
		bool CStatusBar::setAlign(const Align value)
		{
			return false;
		}

		bool CStatusBar::setConstraints(const RectF &value)
		{
			return false;
		}

		bool CStatusBar::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sOuterBorderWidth *= s;
				m_sInnerBorderWidth *= s;
				m_sBorderRadius *= avg;
				m_sShadowShift *= s;
				m_iShadowRadius = ntl::Round<int>((float)m_iShadowRadius * avg);
				m_fSeparatorWidth *= s.X;
				for (int i = 0; i < getItemCount(); i++)
					getItem(i)->QueryService()->setDPI(value);
				Update();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CStatusBar::setOuterBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sOuterBorderWidth))
			{
				CLockRepaint lock{ this };
				m_sOuterBorderWidth = value;
				if (Update())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CStatusBar::setInnerBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sInnerBorderWidth))
			{
				CLockRepaint lock{ this };
				m_sInnerBorderWidth = value;
				if (Update())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CStatusBar::setBorderRadius(const RectF &value)
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

		bool CStatusBar::setOuterBorderColor(const BorderColor &value)
		{
			if (value != m_sOuterBorderColor)
			{
				m_sOuterBorderColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CStatusBar::setLeftOuterBorderColor(const Color &value)
		{
			return setOuterBorderColor(BorderColor{ value, m_sOuterBorderColor.Top, m_sOuterBorderColor.Right, m_sOuterBorderColor.Bottom });
		}

		bool CStatusBar::setTopOuterBorderColor(const Color &value)
		{
			return setOuterBorderColor(BorderColor{ m_sOuterBorderColor.Left, value, m_sOuterBorderColor.Right, m_sOuterBorderColor.Bottom });
		}

		bool CStatusBar::setRightOuterBorderColor(const Color &value)
		{
			return setOuterBorderColor(BorderColor{ m_sOuterBorderColor.Left, m_sOuterBorderColor.Top, value, m_sOuterBorderColor.Bottom });
		}

		bool CStatusBar::setBottomOuterBorderColor(const Color &value)
		{
			return setOuterBorderColor(BorderColor{ m_sOuterBorderColor.Left, m_sOuterBorderColor.Top, m_sOuterBorderColor.Right, value });
		}

		bool CStatusBar::setInnerBorderColor(const BorderColor &value)
		{
			if (value != m_sInnerBorderColor)
			{
				m_sInnerBorderColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CStatusBar::setLeftInnerBorderColor(const Color &value)
		{
			return setInnerBorderColor(BorderColor{ value, m_sInnerBorderColor.Top, m_sInnerBorderColor.Right, m_sInnerBorderColor.Bottom });
		}

		bool CStatusBar::setTopInnerBorderColor(const Color &value)
		{
			return setInnerBorderColor(BorderColor{ m_sInnerBorderColor.Left, value, m_sInnerBorderColor.Right, m_sInnerBorderColor.Bottom });
		}

		bool CStatusBar::setRightInnerBorderColor(const Color &value)
		{
			return setInnerBorderColor(BorderColor{ m_sInnerBorderColor.Left, m_sInnerBorderColor.Top, value, m_sInnerBorderColor.Bottom });
		}

		bool CStatusBar::setBottomInnerBorderColor(const Color &value)
		{
			return setInnerBorderColor(BorderColor{ m_sInnerBorderColor.Left, m_sInnerBorderColor.Top, m_sInnerBorderColor.Right, value });
		}

		bool CStatusBar::setBackgroundColor(const Color &value)
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

		bool CStatusBar::setShadowColor(const Color &value)
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

		bool CStatusBar::setShadowShift(const PointF &value)
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

		bool CStatusBar::setShadowRadius(const int value)
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

		bool CStatusBar::setSeparatorWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fSeparatorWidth))
			{
				CLockRepaint lock{ this };
				m_fSeparatorWidth = value;
				if (Update())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CStatusBar::setSeparatorColor(const Color &value)
		{
			if (value != m_sSeparatorColor)
			{
				m_sSeparatorColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Items
		bool CStatusBar::InsertItem(IListItem *item, const int before)
		{
			CLockRepaint lock{ this };
			if (CControlItemList::InsertItem(item, before))
			{
				item->QueryService()->setOwner(QueryListItemOwner());
				if (Update())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CStatusBar::DeleteItem(const int index)
		{
			CLockRepaint lock{ this };
			if (CControlItemList::DeleteItem(index))
			{
				if (Update())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CStatusBar::DeleteItem(IListItem *item)
		{
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				if (*pos == item)
					return DeleteItem(int(pos - m_aItems.begin()));
			return false;
		}

		bool CStatusBar::DeleteItems()
		{
			if (CControlItemList::DeleteItems())
			{
				if (Update())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CStatusBar::Add(const String &caption, const float width)
		{
			CListItemStatusPanelLabel *item{ new CListItemStatusPanelLabel(caption) };
			item->setWidth(width);
			return AddItem(item);
		}

		bool CStatusBar::Insert(const String &caption, const int before, const float width)
		{
			CListItemStatusPanelLabel *item{ new CListItemStatusPanelLabel(caption) };
			item->setWidth(width);
			return InsertItem(item, before);
		}
	#pragma endregion

	#pragma region Helpers
		void CStatusBar::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		void CStatusBar::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".OuterBorderWidth", m_sOuterBorderWidth);
			style->getOption(m_sClassName + L".InnerBorderWidth", m_sInnerBorderWidth);
			style->getOption(m_sClassName + L".BorderRadius", m_sBorderRadius);
			style->getOption(m_sClassName + L".OuterBorderColor", m_sOuterBorderColor);
			style->getOption(m_sClassName + L".InnerBorderColor", m_sInnerBorderColor);
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L".ShadowColor", m_sShadowColor);
			style->getOption(m_sClassName + L".ShadowShift", m_sShadowShift);
			style->getOption(m_sClassName + L".ShadowRadius", m_iShadowRadius);
			style->getOption(m_sClassName + L".SeparatorWidth", m_fSeparatorWidth);
			style->getOption(m_sClassName + L".SeparatorColor", m_sSeparatorColor);
			style->getOption(m_sClassName + L".SeparatorGradient", m_cSeparatorGradient);
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				(*pos)->QueryService()->UpdateFromStyle();
			Update();
			m_bIgnoreGradient = false;
		}

		bool CStatusBar::Update()
		{
			bool result{ false };
			if (getForm() && getForm()->getRenderer() && getFont()->getPlatformFont(getForm()->getRenderer()))
			{
				// Update control min height
				float height{ m_sOuterBorderWidth.Top + m_sOuterBorderWidth.Bottom + m_sInnerBorderWidth.Top + m_sInnerBorderWidth.Bottom };
				result = CControl::setConstraints(RectF{ 0, height, 0, 0 }) || result;
				// Update items' size and position
				float x{ m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left };
				for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
					if ((*pos)->isVisible())
					{
						PointF size{ (*pos)->QueryService()->getRequiredSize() };
						result = (*pos)->QueryService()->setSize(PointF{ size.X, ntl::Max<float>(0, getHeight() - m_sOuterBorderWidth.Top - m_sOuterBorderWidth.Bottom - m_sInnerBorderWidth.Top - m_sInnerBorderWidth.Bottom) }) || result;
						result = (*pos)->QueryService()->setPosition(PointF{ x, m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top }) || result;
						x += size.X + m_fSeparatorWidth;
					}
				result = UpdateHoveredItem() || result;
			}
			return result;
		}

		bool CStatusBar::UpdateHoveredItem()
		{
			if (getForm())
				return UpdateHoveredItem(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())));
			return false;
		}

		bool CStatusBar::UpdateHoveredItem(const PointF &position)
		{
			IListItem *hovered{ getItemAtPoint(position) };
			bool result{ false };
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				if (*pos == hovered)
				{
					if (!hovered->isHovered())
					{
						hovered->QueryService()->setHovered(true);
						result = true;
					}
				}
				else if ((*pos)->isHovered())
				{
					(*pos)->QueryService()->setHovered(false);
					result = true;
				}
			return result;
		}

		IListItem *CStatusBar::getItemAtPoint(const PointF &position)
		{
			if (m_aItems.size() > 0)
			{
				RectF client{ getClientRect() };
				if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
					for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
					{
						if ((*pos)->isVisible() && (*pos)->getPosition().X >= client.Right)
							break;
						if ((*pos)->isVisible() && position.X >= (*pos)->getPosition().X && position.X < (*pos)->getPosition().X + (*pos)->getSize().X && position.Y >= (*pos)->getPosition().Y && position.Y < (*pos)->getPosition().Y + (*pos)->getSize().Y)
							return *pos;
					}
			}
			return nullptr;
		}
	#pragma endregion

	#pragma region Paint
		void CStatusBar::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			PointF disp{ DispOnCanvas(m_sShadowColor, m_sShadowShift, m_iShadowRadius) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_sShadowColor, m_sShadowShift, m_iShadowRadius) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
				DrawBlockShadow(renderer, rect, m_sBorderRadius, m_sShadowColor, m_sShadowShift, m_iShadowRadius);
				DrawDoubleBackground(renderer, rect, m_sOuterBorderWidth, m_sInnerBorderWidth, m_sBorderRadius, m_sOuterBorderColor, m_sInnerBorderColor, m_sBackgroundColor, m_cBackgroundGradient);
				RenderItems(renderer, rect, disp);

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}

		void CStatusBar::RenderItems(IRenderer *renderer, const RectF &rect, const PointF &disp)
		{
			Block b{ rect, AddElements(m_sOuterBorderWidth, m_sInnerBorderWidth), m_sBorderRadius, PointLocation::Inside };
			Mat4f m;
			RectF separator_rect{ 0, 0, m_fSeparatorWidth, getHeight() - m_sOuterBorderWidth.Top - m_sOuterBorderWidth.Bottom - m_sInnerBorderWidth.Top - m_sInnerBorderWidth.Bottom };
			ITexture *clip{ nullptr };
			CStoreBlock s_block{ renderer };
			CStorePrimitiveMatrix s_matrix{ renderer };
			renderer->ActivateBlock(&b);
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				if ((*pos)->isVisible())
				{
					if ((*pos)->getPosition().X >= getWidth())
						break;
					if (pos != m_aItems.begin() && ntl::IsGreater<float>(m_fSeparatorWidth, 0))
					{
						ntl::Translate<float>(m, (*pos)->getPosition().X - m_fSeparatorWidth + disp.X, m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top + disp.Y, 0);
						renderer->ActivatePrimitiveMatrix(&m);
						if (m_cSeparatorGradient.getPointCount() >= 2)
							renderer->DrawGradient(separator_rect, m_cSeparatorGradient);
						else
							renderer->DrawRectangle(separator_rect, m_sSeparatorColor);
					}
					ntl::Translate<float>(m, (*pos)->getPosition().X + disp.X, (*pos)->getPosition().Y + disp.Y, 0);
					(*pos)->QueryService()->Render(m, &b, false, &clip);
				}
			if (clip)
				clip->Release();
		}
	#pragma endregion
	}
}