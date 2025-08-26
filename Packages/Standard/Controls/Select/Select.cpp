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
	#pragma region CBuiltIn
		CSelect::CBuiltIn::CBuiltIn(CSelect *control) :
			CBuiltInSelect(),
			m_pControl{ control }
		{

		}

		IControl *CSelect::CBuiltIn::getControl()
		{
			return m_pControl;
		}

		CBuiltInSelect::State CSelect::CBuiltIn::getState()
		{
			return m_pControl->getState();
		}
	#pragma endregion

	#pragma region CBuiltInListener
		CSelect::CBuiltInListener::CBuiltInListener(CSelect *control) :
			m_pControl{ control }
		{

		}

		void CSelect::CBuiltInListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			m_pControl->Repaint(rect, true);
		}

		void CSelect::CBuiltInListener::NotifyOnFilterChange(IBuiltInControl *sender)
		{
			
		}

		void CSelect::CBuiltInListener::NotifyOnSelect(IBuiltInControl *sender, const int index)
		{
			if (m_pControl->OnSelect)
				m_pControl->OnSelect(m_pControl, index);
		}

		void CSelect::CBuiltInListener::NotifyOnOpen(IBuiltInControl *sender)
		{
			if (!m_pControl->isCaptureMouse() && m_pControl->getForm())
				m_pControl->getForm()->CaptureMouse(m_pControl, true);
		}

		void CSelect::CBuiltInListener::NotifyOnClose(IBuiltInControl *sender)
		{
			if (m_pControl->isCaptureMouse())
			{
				m_pControl->m_bIgnoreKillCaptureMouse = true;
				m_pControl->getForm()->ReleaseCaptureMouse();
				m_pControl->m_bIgnoreKillCaptureMouse = false;
			}
		}
	#pragma endregion

	#pragma region CFontListener
		CSelect::CFontListener::CFontListener(CSelect *control) :
			m_pControl{ control }
		{

		}

		void CSelect::CFontListener::NotifyOnBeforeChange()
		{
			if (!m_pControl->m_bIgnoreFont)
			{
				if (m_pControl->getForm())
					m_pControl->getForm()->LockRepaint();
				m_pControl->Repaint(false);
			}
		}

		void CSelect::CFontListener::NotifyOnBeforeChange(bool &allowed)
		{
			if (!m_pControl->m_bIgnoreFont)
			{
				if (m_pControl->getForm())
					m_pControl->getForm()->LockRepaint();
				m_pControl->Repaint(false);
			}
		}

		void CSelect::CFontListener::NotifyOnAfterChange()
		{
			if (!m_pControl->m_bIgnoreFont)
			{
				m_pControl->getSelect()->Update();
				m_pControl->Repaint(false);
				if (m_pControl->getForm())
				{
					m_pControl->getForm()->UpdateHoveredControl();
					m_pControl->getForm()->UnlockRepaint();
				}
			}
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CSelect::CSelect() :
			CControlItemList(L"Select", true, true, false, true, false, true),
			m_pSelect{ nullptr },
			m_cListener{ this },
			m_cFontListener{ this },
			m_cCategoryFont{ &m_cFontListener },
			m_bIgnoreFont{ true },
			m_bIgnoreKillCaptureMouse{ false },
			OnSelect{ nullptr }
		{
			m_cCategoryFont.setWeight(FontWeight::Bold);
			m_bIgnoreFont = false;

			setService(new CSelectService(this), true);
			setSize(PointF{ 145, 21 });
		}

		CSelect::CSelect(IForm *parent) :
			CSelect()
		{
			setForm(parent);
		}

		CSelect::CSelect(IControl *parent) :
			CSelect()
		{
			setParent(parent);
		}

		CSelect::~CSelect()
		{
			if (m_pSelect)
				m_pSelect->Release();
		}
	#pragma endregion

	#pragma region IControl getters
		IControl *CSelect::getControl(const PointF &position)
		{
			Vec4f v{ ntl::Inversed<float>(getTransformMatrix()) * Vec4f { position.X, position.Y, 0, 1 } };
			if (getSelect()->isInside(PointF{ v.X, v.Y }))
				return this;
			return nullptr;
		}

		RectF CSelect::getClientRect()
		{
			return getSelect()->getClientRect();
		}

		RectF CSelect::getRenderRect()
		{
			return getSelect()->getRenderRect();
		}

		CursorType CSelect::getCursor()
		{
			if (isEnabled(true) && getForm())
			{
				PointF pos{ FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())) };
				return getSelect()->getCursor(pos, CControl::getCursor());
			}
			return CControl::getCursor();
		}

		bool CSelect::hasExtra()
		{
			return getSelect()->isOpened();
		}
	#pragma endregion

	#pragma region IControl setters
		bool CSelect::setDPI(const Point &value)
		{
			RectF r{ getSelect()->getRenderRect() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value) && m_pSelect->setDPI(value))
			{
				Repaint(r + m_pSelect->getRenderRect(), true);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IControl methods
		void CSelect::Refresh(const bool refresh_children)
		{
			if (m_pSelect)
				m_pSelect->Refresh();
		}
	#pragma endregion

	#pragma region IComponentItemList getters
		int CSelect::getItemCount()
		{
			return getSelect()->getItemCount();
		}

		IListItem *CSelect::getItem(const int index)
		{
			return getSelect()->getItem(index);
		}

		int CSelect::getItemIndex(IListItem *item)
		{
			return getSelect()->getItemIndex(item);
		}
	#pragma endregion

	#pragma region IComponentItemList items
		bool CSelect::AddItem(IListItem *item)
		{
			RectF r{ getSelect()->getRenderRect() };
			if (m_pSelect->AddItem(item))
			{
				Repaint(r + m_pSelect->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CSelect::InsertItem(IListItem *item, const int before)
		{
			RectF r{ getSelect()->getRenderRect() };
			if (m_pSelect->InsertItem(item, before))
			{
				Repaint(r + m_pSelect->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CSelect::DeleteItem(const int index)
		{
			RectF r{ getSelect()->getRenderRect() };
			if (m_pSelect->DeleteItem(index))
			{
				Repaint(r + m_pSelect->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CSelect::DeleteItem(IListItem *item)
		{
			RectF r{ getSelect()->getRenderRect() };
			if (m_pSelect->DeleteItem(item))
			{
				Repaint(r + m_pSelect->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CSelect::DeleteItems()
		{
			RectF r{ getSelect()->getRenderRect() };
			if (m_pSelect->DeleteItems())
			{
				Repaint(r + m_pSelect->getRenderRect(), true);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IComponentItemList methods
		IListItemOwner *CSelect::QueryListItemOwner()
		{
			return getSelect()->QueryListItemOwner();
		}
	#pragma endregion

	#pragma region ISelect getters
		String CSelect::getFilter()
		{
			return getSelect()->getFilter();
		}

		int CSelect::getActiveIndex()
		{
			return getSelect()->getActiveIndex();
		}

		IBuiltInSelect *CSelect::getSelect()
		{
			if (!m_pSelect)
			{
				m_pSelect = new CBuiltIn(this);
				m_pSelect->setListener(&m_cListener);
				m_pSelect->setEnabled(isEnabled(false));
				m_pSelect->setFocused(isFocused());
				if (getStyle())
					m_pSelect->UpdateFromStyle(getStyle(), m_sClassName + L".Select");
				UpdateSelect();
			}
			return m_pSelect;
		}

		IFont *CSelect::getCategoryFont()
		{
			return &m_cCategoryFont;
		}
	#pragma endregion

	#pragma region ISelect setters
		bool CSelect::setFilter(const String &value)
		{
			RectF r{ getSelect()->getRenderRect() };
			if (m_pSelect->setFilter(value))
			{
				Repaint(r + m_pSelect->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CSelect::setActiveIndex(const int value)
		{
			RectF r{ getSelect()->getRenderRect() };
			if (m_pSelect->setActiveIndex(value))
			{
				Repaint(r + m_pSelect->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CSelect::setSelect(IBuiltInSelect *value)
		{
			if (value && value != m_pSelect)
			{
				CLockRepaint lock{ this };
				value->setListener(&m_cListener);
				value->NotifyOnFreeResources();
				if (m_pSelect)
				{
					Repaint(m_pSelect->getRenderRect(), true);
					value->setFilter(m_pSelect->getFilter());
					m_pSelect->Release();
				}
				m_pSelect = value;
				UpdateSelect();
				m_pSelect->setFocused(isFocused());
				m_pSelect->setEnabled(isEnabled(false));
				Repaint(m_pSelect->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CSelect::setCategoryFont(IFont *value)
		{
			if (value)
			{
				CLockRepaint lock{ this };
				Repaint(false);
				m_bIgnoreFont = true;
				m_cCategoryFont.Copy(value);
				m_bIgnoreFont = false;
				getSelect()->Update();
				Repaint(false);
				if (getForm())
					getForm()->UpdateHoveredControl();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region ISelect methods
		bool CSelect::Open()
		{
			RectF r{ getSelect()->getRenderRect() };
			if (m_pSelect->Open())
			{
				getForm()->CaptureMouse(this, false);
				Repaint(r + m_pSelect->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CSelect::Close()
		{
			RectF r{ getSelect()->getRenderRect() };
			if (m_pSelect->Close())
			{
				if (isCaptureMouse())
					getForm()->ReleaseCaptureMouse();
				Repaint(r + m_pSelect->getRenderRect(), true);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Layout getters
		CBuiltInSelect::State CSelect::getState()
		{
			if (!isEnabled(false))
				return CBuiltInSelect::State::Disabled;
			if (isFocused())
			{
				if (isHovered())
					return CBuiltInSelect::State::FocusedHovered;
				return CBuiltInSelect::State::Focused;
			}
			if (isHovered())
				return CBuiltInSelect::State::Hovered;
			return CBuiltInSelect::State::Normal;
		}

		bool CSelect::isOpened()
		{
			return getSelect()->isOpened();
		}

		bool CSelect::isArrowAtRight()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->isArrowAtRight();
			return false;
		}

		CBuiltInSelect::OpenDirection CSelect::getOpenDirection()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getOpenDirection();
			return CBuiltInSelect::OpenDirection::Down;
		}

		CBuiltInSelect::ArrowArea CSelect::getArrowArea()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getArrowArea();
			return CBuiltInSelect::ArrowArea::Height;
		}

		float CSelect::getListWidth()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getListWidth();
			return 0;
		}

		float CSelect::getListMaxHeight()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getListMaxHeight();
			return 0;
		}

		float CSelect::getArrowAreaSize()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getArrowAreaSize();
			return 0;
		}

		float CSelect::getArrowSize()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getArrowSize();
			return 0;
		}

		RectF CSelect::getBorderWidth()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getBorderWidth();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CSelect::getBorderRadius()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getBorderRadius();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CSelect::getPadding()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getPadding();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CSelect::getArrowBorderWidth()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getArrowBorderWidth();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CSelect::getArrowBorderRadius()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getArrowBorderRadius();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CSelect::getListBorderWidth()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getListBorderWidth();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CSelect::getListBorderRadius()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getListBorderRadius();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CSelect::getListPadding()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getListPadding();
			return RectF{ 0, 0, 0, 0 };
		}

		Color CSelect::getShadowColor(const CBuiltInSelect::State state)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getShadowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		PointF CSelect::getShadowShift(const CBuiltInSelect::State state)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getShadowShift(state);
			return PointF{ 0, 0 };
		}

		int CSelect::getShadowRadius(const CBuiltInSelect::State state)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getShadowRadius(state);
			return 0;
		}

		BorderColor CSelect::getBorderColor(const CBuiltInSelect::State state)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getBorderColor(state);
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CSelect::getBackgroundColor(const CBuiltInSelect::State state)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CSelect::getBackgroundGradient(const CBuiltInSelect::State state)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getBackgroundGradient(state);
			return nullptr;
		}

		BorderColor CSelect::getInputBorderColor(const CBuiltInSelect::State state)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getInputBorderColor(state);
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CSelect::getInputBackgroundColor(const CBuiltInSelect::State state)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getInputBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CSelect::getInputBackgroundGradient(const CBuiltInSelect::State state)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getInputBackgroundGradient(state);
			return nullptr;
		}

		BorderColor CSelect::getArrowBorderColor(const CBuiltInSelect::State state)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getArrowBorderColor(state);
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CSelect::getArrowBackgroundColor(const CBuiltInSelect::State state)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getArrowBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CSelect::getArrowBackgroundGradient(const CBuiltInSelect::State state)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getArrowBackgroundGradient(state);
			return nullptr;
		}

		Color CSelect::getArrowColor(const CBuiltInSelect::State state)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getArrowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		BorderColor CSelect::getListBorderColor()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getListBorderColor();
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CSelect::getListBackgroundColor()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getListBackgroundColor();
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CSelect::getListBackgroundGradient()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getListBackgroundGradient();
			return nullptr;
		}

		Color CSelect::getListShadowColor()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getListShadowColor();
			return Color{ 0, 0, 0, 0 };
		}

		PointF CSelect::getListShadowShift()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getListShadowShift();
			return PointF{ 0, 0 };
		}

		int CSelect::getListShadowRadius()
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
				return dd->getListShadowRadius();
			return 0;
		}
	#pragma endregion

	#pragma region Layout setters
		bool CSelect::setArrowAtRight(const bool value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowAtRight(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setOpenDirection(const CBuiltInSelect::OpenDirection value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setOpenDirection(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setListWidth(const float value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListWidth(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setListMaxHeight(const float value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListMaxHeight(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setArrowArea(const CBuiltInSelect::ArrowArea value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowArea(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setArrowAreaSize(const float value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowAreaSize(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setArrowSize(const float value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowSize(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setBorderWidth(const RectF &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setBorderWidth(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setBorderRadius(const RectF &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setBorderRadius(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setPadding(const RectF &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setPadding(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setArrowBorderWidth(const RectF &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowBorderWidth(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setArrowBorderRadius(const RectF &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowBorderRadius(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setListBorderWidth(const RectF &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListBorderWidth(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setListBorderRadius(const RectF &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListBorderRadius(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setListPadding(const RectF &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListPadding(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setShadowColor(const CBuiltInSelect::State state, const Color &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setShadowColor(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setShadowShift(const CBuiltInSelect::State state, const PointF &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setShadowShift(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setShadowRadius(const CBuiltInSelect::State state, const int value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setShadowRadius(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setBorderColor(const CBuiltInSelect::State state, const BorderColor &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setBorderColor(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setBackgroundColor(const CBuiltInSelect::State state, const Color &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setBackgroundColor(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setInputBorderColor(const CBuiltInSelect::State state, const BorderColor &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setInputBorderColor(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setInputBackgroundColor(const CBuiltInSelect::State state, const Color &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setInputBackgroundColor(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setArrowBorderColor(const CBuiltInSelect::State state, const BorderColor &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowBorderColor(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setArrowBackgroundColor(const CBuiltInSelect::State state, const Color &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowBackgroundColor(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setArrowColor(const CBuiltInSelect::State state, const Color &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowColor(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setListBorderColor(const BorderColor &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListBorderColor(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setListBackgroundColor(const Color &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListBackgroundColor(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setListShadowColor(const Color &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListShadowColor(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setListShadowShift(const PointF &value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListShadowShift(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CSelect::setListShadowRadius(const int value)
		{
			CBuiltIn *dd{ cast<CBuiltIn*>(getSelect()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListShadowRadius(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}
	#pragma endregion

	#pragma region Methods
		bool CSelect::Add(const String &caption, const bool category)
		{
			if (!caption.empty())
			{
				RectF r{ getSelect()->getRenderRect() };
				if (category)
					m_pSelect->AddItem(new CListItemSelectCategory(caption));
				else
					m_pSelect->AddItem(new CListItemSelectLabel(caption));
				Repaint(r + m_pSelect->getRenderRect(), true);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CSelect::UpdateFromStyle(IStyle *style)
		{
			getSelect()->UpdateFromStyle(style, m_sClassName + L".Select");
			UpdateSelect();
		}

		void CSelect::UpdateSelect()
		{
			getSelect()->setSize(PointF{ getWidth(), getHeight() });
		}
	#pragma endregion

	#pragma region Paint
		void CSelect::Render()
		{
			getSelect()->Render(false, getTransformMatrix(), nullptr);
		}

		void CSelect::RenderList()
		{
			getSelect()->Render(true, getTransformMatrix(), nullptr);
		}
	#pragma endregion
	}
}