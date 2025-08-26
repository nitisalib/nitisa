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
	#pragma region Constructor & destructor
		CCustomDropDown::CCustomDropDown(const String &class_name, const bool accept_form, const bool accept_control, const bool tab_stop, const bool editable, const Point &design_dpi):
			CControlItemList(class_name, accept_form, accept_control, false, true, false, tab_stop, design_dpi),
			m_pDropDown{ nullptr },
			m_cListener{ this },
			m_bIgnoreKillCaptureMouse{ false },
			OnChange{ nullptr },
			OnSelect{ nullptr }
		{
			setService(new CCustomDropDownService(this), true);
			setSize(PointF{ 145, 21 });
		}

		CCustomDropDown::~CCustomDropDown()
		{
			if (m_pDropDown)
				m_pDropDown->Release();
		}
	#pragma endregion

	#pragma region CControl getters
		IControl *CCustomDropDown::getControl(const PointF &position)
		{
			Vec4f v{ ntl::Inversed<float>(getTransformMatrix()) * Vec4f{ position.X, position.Y, 0, 1 } };
			if (getDropDown()->isInside(PointF{ v.X, v.Y }))
				return this;
			return nullptr;
		}

		RectF CCustomDropDown::getClientRect()
		{
			return getDropDown()->getClientRect();
		}

		RectF CCustomDropDown::getRenderRect()
		{
			return getDropDown()->getRenderRect();
		}

		CursorType CCustomDropDown::getCursor()
		{
			if (isEnabled(true) && getForm())
			{
				PointF pos{ FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())) };
				return getDropDown()->getCursor(pos, CControl::getCursor());
			}
			return CControl::getCursor();
		}

		IListItemOwner *CCustomDropDown::QueryListItemOwner()
		{
			return getDropDown()->QueryListItemOwner();
		}
	#pragma endregion

	#pragma region Getters
		CBuiltInDropDown::State CCustomDropDown::getState()
		{
			if (!isEnabled(false))
				return CBuiltInDropDown::State::Disabled;
			if (isFocused())
			{
				if (isHovered())
					return CBuiltInDropDown::State::FocusedHovered;
				return CBuiltInDropDown::State::Focused;
			}
			if (isHovered())
				return CBuiltInDropDown::State::Hovered;
			return CBuiltInDropDown::State::Normal;
		}

		int CCustomDropDown::getItemCount()
		{
			return getDropDown()->getItemCount();
		}

		IListItem *CCustomDropDown::getItem(const int index)
		{
			return getDropDown()->getItem(index);
		}

		int CCustomDropDown::getItemIndex(IListItem *item)
		{
			return getDropDown()->getItemIndex(item);
		}

		bool CCustomDropDown::isEditable()
		{
			return getDropDown()->isEditable();
		}

		bool CCustomDropDown::isOpened()
		{
			return getDropDown()->isOpened();
		}

		bool CCustomDropDown::isArrowAtRight()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->isArrowAtRight();
			return false;
		}

		bool CCustomDropDown::isSortable()
		{
			return getDropDown()->isSortable();
		}

		CBuiltInDropDown::OpenDirection CCustomDropDown::getOpenDirection()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getOpenDirection();
			return CBuiltInDropDown::OpenDirection::Down;
		}

		CBuiltInDropDown::ArrowArea CCustomDropDown::getArrowArea()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowArea();
			return CBuiltInDropDown::ArrowArea::Height;
		}

		float CCustomDropDown::getListWidth()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListWidth();
			return 0;
		}

		float CCustomDropDown::getListMaxHeight()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListMaxHeight();
			return 0;
		}

		String CCustomDropDown::getText()
		{
			return getDropDown()->getText();
		}

		int CCustomDropDown::getActiveIndex()
		{
			return getDropDown()->getActiveIndex();
		}

		float CCustomDropDown::getArrowAreaSize()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowAreaSize();
			return 0;
		}

		float CCustomDropDown::getArrowSize()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowSize();
			return 0;
		}

		RectF CCustomDropDown::getBorderWidth()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getBorderWidth();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CCustomDropDown::getBorderRadius()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getBorderRadius();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CCustomDropDown::getPadding()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getPadding();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CCustomDropDown::getArrowBorderWidth()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowBorderWidth();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CCustomDropDown::getArrowBorderRadius()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowBorderRadius();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CCustomDropDown::getListBorderWidth()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListBorderWidth();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CCustomDropDown::getListBorderRadius()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListBorderRadius();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CCustomDropDown::getListPadding()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListPadding();
			return RectF{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getShadowColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getShadowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getShadowColorEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getShadowColorEditable(state);
			return Color{ 0, 0, 0, 0 };
		}

		PointF CCustomDropDown::getShadowShift(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getShadowShift(state);
			return PointF{ 0, 0 };
		}

		PointF CCustomDropDown::getShadowShiftEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getShadowShiftEditable(state);
			return PointF{ 0, 0 };
		}

		int CCustomDropDown::getShadowRadius(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getShadowRadius(state);
			return 0;
		}

		int CCustomDropDown::getShadowRadiusEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getShadowRadiusEditable(state);
			return 0;
		}

		BorderColor CCustomDropDown::getBorderColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getBorderColor(state);
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		BorderColor CCustomDropDown::getBorderColorEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getBorderColorEditable(state);
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CCustomDropDown::getLeftBorderColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getLeftBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getLeftBorderColorEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getLeftBorderColorEditable(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getTopBorderColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getTopBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getTopBorderColorEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getTopBorderColorEditable(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getRightBorderColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getRightBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getRightBorderColorEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getRightBorderColorEditable(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getBottomBorderColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getBottomBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getBottomBorderColorEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getBottomBorderColorEditable(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getBackgroundColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getBackgroundColorEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getBackgroundColorEditable(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CCustomDropDown::getBackgroundGradient(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getBackgroundGradient(state);
			return nullptr;
		}

		Gradient *CCustomDropDown::getBackgroundGradientEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getBackgroundGradientEditable(state);
			return nullptr;
		}

		BorderColor CCustomDropDown::getArrowBorderColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowBorderColor(state);
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		BorderColor CCustomDropDown::getArrowBorderColorEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowBorderColorEditable(state);
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CCustomDropDown::getArrowLeftBorderColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowLeftBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getArrowLeftBorderColorEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowLeftBorderColorEditable(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getArrowTopBorderColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowTopBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getArrowTopBorderColorEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowTopBorderColorEditable(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getArrowRightBorderColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowRightBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getArrowRightBorderColorEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowRightBorderColorEditable(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getArrowBottomBorderColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowBottomBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getArrowBottomBorderColorEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowBottomBorderColorEditable(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getArrowBackgroundColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getArrowBackgroundColorEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowBackgroundColorEditable(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CCustomDropDown::getArrowBackgroundGradient(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowBackgroundGradient(state);
			return nullptr;
		}

		Gradient *CCustomDropDown::getArrowBackgroundGradientEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowBackgroundGradientEditable(state);
			return nullptr;
		}

		Color CCustomDropDown::getArrowColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getArrowColorEditable(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowColorEditable(state);
			return Color{ 0, 0, 0, 0 };
		}

		BorderColor CCustomDropDown::getListBorderColor()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListBorderColor();
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		BorderColor CCustomDropDown::getListBorderColorEditable()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListBorderColorEditable();
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CCustomDropDown::getListLeftBorderColor()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListLeftBorderColor();
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getListLeftBorderColorEditable()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListLeftBorderColorEditable();
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getListTopBorderColor()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListTopBorderColor();
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getListTopBorderColorEditable()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListTopBorderColorEditable();
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getListRightBorderColor()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListRightBorderColor();
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getListRightBorderColorEditable()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListRightBorderColorEditable();
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getListBottomBorderColor()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListBottomBorderColor();
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getListBottomBorderColorEditable()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListBottomBorderColorEditable();
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getListBackgroundColor()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListBackgroundColor();
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getListBackgroundColorEditable()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListBackgroundColorEditable();
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CCustomDropDown::getListBackgroundGradient()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListBackgroundGradient();
			return nullptr;
		}

		Gradient *CCustomDropDown::getListBackgroundGradientEditable()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListBackgroundGradientEditable();
			return nullptr;
		}

		Color CCustomDropDown::getListShadowColor()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListShadowColor();
			return Color{ 0, 0, 0, 0 };
		}

		Color CCustomDropDown::getListShadowColorEditable()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListShadowColorEditable();
			return Color{ 0, 0, 0, 0 };
		}

		PointF CCustomDropDown::getListShadowShift()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListShadowShift();
			return PointF{ 0, 0 };
		}

		PointF CCustomDropDown::getListShadowShiftEditable()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListShadowShiftEditable();
			return PointF{ 0, 0 };
		}

		int CCustomDropDown::getListShadowRadius()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListShadowRadius();
			return 0;
		}

		int CCustomDropDown::getListShadowRadiusEditable()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListShadowRadiusEditable();
			return 0;
		}

		float CCustomDropDown::getSearchResetInterval()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getSearchResetInterval();
			return 0;
		}

		IBuiltInDropDown::FCompare CCustomDropDown::getCompareFunc()
		{
			return getDropDown()->getCompareFunc();
		}

		IBuiltInDropDown::FGetItemText CCustomDropDown::getItemTextFunc()
		{
			return getDropDown()->getItemTextFunc();
		}

		IBuiltInDropDown::FSearch CCustomDropDown::getSearchFunc()
		{
			return getDropDown()->getSearchFunc();
		}
	#pragma endregion

	#pragma region IControl getters
		bool CCustomDropDown::hasExtra()
		{
			return getDropDown()->isOpened();
		}
	#pragma endregion

	#pragma region Setters
		bool CCustomDropDown::setDPI(const Point &value)
		{
			RectF r{ getDropDown()->getRenderRect() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value) && m_pDropDown->setDPI(value))
			{
				Repaint(r + m_pDropDown->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CCustomDropDown::setDropDown(IBuiltInDropDown *value)
		{
			if (value && value != m_pDropDown)
			{
				CLockRepaint lock{ this };
				value->setListener(&m_cListener);
				value->NotifyOnFreeResources();
				if (m_pDropDown)
				{
					Repaint(m_pDropDown->getRenderRect(), true);
					value->setText(m_pDropDown->getText());
					m_pDropDown->Release();
				}
				m_pDropDown = value;
				UpdateDropDown();
				m_pDropDown->setFocused(isFocused());
				m_pDropDown->setEnabled(isEnabled(false));
				Repaint(m_pDropDown->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CCustomDropDown::setEditable(const bool value)
		{
			RectF r{ getDropDown()->getRenderRect() };
			if (m_pDropDown->setEditable(value))
			{
				Repaint(r + m_pDropDown->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CCustomDropDown::setArrowAtRight(const bool value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setSortable(const bool value)
		{
			RectF r{ getDropDown()->getRenderRect() };
			if (m_pDropDown->setSortable(value))
			{
				Repaint(r + m_pDropDown->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CCustomDropDown::setOpenDirection(const CBuiltInDropDown::OpenDirection value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setListWidth(const float value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setListMaxHeight(const float value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setText(const String &value)
		{
			RectF r{ getDropDown()->getRenderRect() };
			if (m_pDropDown->setText(value))
			{
				Repaint(r + m_pDropDown->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CCustomDropDown::setActiveIndex(const int value)
		{
			RectF r{ getDropDown()->getRenderRect() };
			if (m_pDropDown->setActiveIndex(value))
			{
				Repaint(r + m_pDropDown->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CCustomDropDown::setArrowArea(const CBuiltInDropDown::ArrowArea value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setArrowAreaSize(const float value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setArrowSize(const float value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setBorderWidth(const RectF &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setBorderRadius(const RectF &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setPadding(const RectF &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setArrowBorderWidth(const RectF &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setArrowBorderRadius(const RectF &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setListBorderWidth(const RectF &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setListBorderRadius(const RectF &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setListPadding(const RectF &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setShadowColor(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setShadowColorEditable(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setShadowColorEditable(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setShadowShift(const CBuiltInDropDown::State state, const PointF &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setShadowShiftEditable(const CBuiltInDropDown::State state, const PointF &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setShadowShiftEditable(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setShadowRadius(const CBuiltInDropDown::State state, const int value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setShadowRadiusEditable(const CBuiltInDropDown::State state, const int value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setShadowRadiusEditable(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setBorderColor(const CBuiltInDropDown::State state, const BorderColor &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setBorderColorEditable(const CBuiltInDropDown::State state, const BorderColor &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setBorderColorEditable(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setLeftBorderColor(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setLeftBorderColor(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setLeftBorderColorEditable(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setLeftBorderColorEditable(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setTopBorderColor(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setTopBorderColor(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setTopBorderColorEditable(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setTopBorderColorEditable(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setRightBorderColor(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setRightBorderColor(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setRightBorderColorEditable(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setRightBorderColorEditable(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setBottomBorderColor(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setBottomBorderColor(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setBottomBorderColorEditable(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setBottomBorderColorEditable(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setBackgroundColor(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setBackgroundColorEditable(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setBackgroundColorEditable(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setArrowBorderColor(const CBuiltInDropDown::State state, const BorderColor &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setArrowBorderColorEditable(const CBuiltInDropDown::State state, const BorderColor &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowBorderColorEditable(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setArrowLeftBorderColor(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowLeftBorderColor(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setArrowLeftBorderColorEditable(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowLeftBorderColorEditable(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setArrowTopBorderColor(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowTopBorderColor(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setArrowTopBorderColorEditable(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowTopBorderColorEditable(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setArrowRightBorderColor(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowRightBorderColor(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setArrowRightBorderColorEditable(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowRightBorderColorEditable(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setArrowBottomBorderColor(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowBottomBorderColor(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setArrowBottomBorderColorEditable(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowBottomBorderColorEditable(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setArrowBackgroundColor(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setArrowBackgroundColorEditable(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowBackgroundColorEditable(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setArrowColor(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setArrowColorEditable(const CBuiltInDropDown::State state, const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setArrowColorEditable(state, value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setListBorderColor(const BorderColor &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setListBorderColorEditable(const BorderColor &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListBorderColorEditable(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setListLeftBorderColor(const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListLeftBorderColor(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setListLeftBorderColorEditable(const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListLeftBorderColorEditable(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setListTopBorderColor(const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListTopBorderColor(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setListTopBorderColorEditable(const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListTopBorderColorEditable(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setListRightBorderColor(const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListRightBorderColor(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setListRightBorderColorEditable(const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListRightBorderColorEditable(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setListBottomBorderColor(const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListBottomBorderColor(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setListBottomBorderColorEditable(const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListBottomBorderColorEditable(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setListBackgroundColor(const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setListBackgroundColorEditable(const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListBackgroundColorEditable(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setListShadowColor(const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setListShadowColorEditable(const Color &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListShadowColorEditable(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setListShadowShift(const PointF &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setListShadowShiftEditable(const PointF &value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListShadowShiftEditable(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setListShadowRadius(const int value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
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

		bool CCustomDropDown::setListShadowRadiusEditable(const int value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setListShadowRadiusEditable(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setSearchResetInterval(const float value)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
			{
				RectF r{ dd->getRenderRect() };
				if (dd->setSearchResetInterval(value))
				{
					Repaint(r + dd->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CCustomDropDown::setCompareFunc(IBuiltInDropDown::FCompare value)
		{
			return getDropDown()->setCompareFunc(value);
		}

		bool CCustomDropDown::setGetItemTextFunc(IBuiltInDropDown::FGetItemText value)
		{
			return getDropDown()->setGetItemTextFunc(value);
		}

		bool CCustomDropDown::setSearchFunc(IBuiltInDropDown::FSearch value)
		{
			return getDropDown()->setSearchFunc(value);
		}
	#pragma endregion

	#pragma region IControl methods
		void CCustomDropDown::Refresh(const bool refresh_children)
		{
			getDropDown()->Refresh();
		}
	#pragma endregion

	#pragma region Items
		bool CCustomDropDown::AddItem(IListItem *item)
		{
			RectF r{ getDropDown()->getRenderRect() };
			if (m_pDropDown->AddItem(item))
			{
				Repaint(r + m_pDropDown->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CCustomDropDown::InsertItem(IListItem *item, const int before)
		{
			RectF r{ getDropDown()->getRenderRect() };
			if (m_pDropDown->InsertItem(item, before))
			{
				Repaint(r + m_pDropDown->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CCustomDropDown::DeleteItem(const int index)
		{
			RectF r{ getDropDown()->getRenderRect() };
			if (m_pDropDown->DeleteItem(index))
			{
				Repaint(r + m_pDropDown->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CCustomDropDown::DeleteItem(IListItem *item)
		{
			RectF r{ getDropDown()->getRenderRect() };
			if (m_pDropDown->DeleteItem(item))
			{
				Repaint(r + m_pDropDown->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CCustomDropDown::DeleteItems()
		{
			RectF r{ getDropDown()->getRenderRect() };
			if (m_pDropDown->DeleteItems())
			{
				Repaint(r + m_pDropDown->getRenderRect(), true);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		IBuiltInDropDown *CCustomDropDown::getDropDown()
		{
			if (!m_pDropDown)
			{
				m_pDropDown = new CDropDown(this);
				m_pDropDown->setListener(&m_cListener);
				m_pDropDown->setEnabled(isEnabled(false));
				m_pDropDown->setFocused(isFocused());
				if (getStyle())
					m_pDropDown->UpdateFromStyle(getStyle(), m_sClassName + L".DropDown");
				UpdateDropDown();
			}
			return m_pDropDown;
		}

		void CCustomDropDown::UpdateFromStyle(IStyle *style)
		{
			getDropDown()->UpdateFromStyle(style, m_sClassName + L".DropDown");
			UpdateDropDown();
		}

		void CCustomDropDown::UpdateDropDown()
		{
			getDropDown()->setSize(PointF{ getWidth(), getHeight() });
		}

		bool CCustomDropDown::Open()
		{
			RectF r{ getDropDown()->getRenderRect() };
			if (m_pDropDown->Open())
			{
				getForm()->CaptureMouse(this, false);
				Repaint(r + m_pDropDown->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CCustomDropDown::Close()
		{
			RectF r{ getDropDown()->getRenderRect() };
			if (m_pDropDown->Close())
			{
				if (isCaptureMouse())
					getForm()->ReleaseCaptureMouse();
				Repaint(r + m_pDropDown->getRenderRect(), true);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CCustomDropDown::Render()
		{
			getDropDown()->Render(false, getTransformMatrix(), nullptr);
		}

		void CCustomDropDown::RenderList()
		{
			getDropDown()->Render(true, getTransformMatrix(), nullptr);
		}
	#pragma endregion
	}
}