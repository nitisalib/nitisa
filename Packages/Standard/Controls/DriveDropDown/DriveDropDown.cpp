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
		CDriveDropDown::CDriveDropDown() :
			CControl(L"DriveDropDown", true, true, false, true, false, true),
			m_pDropDown{ nullptr },
			m_cListener{ this },
			m_pDirectoryTree{ nullptr },
			m_bIgnoreKillCaptureMouse{ false },
			OnSelect{ nullptr }
		{
			setService(new CDriveDropDownService(this), true);
			setSize(PointF{ 145, 21 });
			Rescan();
		}

		CDriveDropDown::CDriveDropDown(IForm *parent) :CDriveDropDown()
		{
			setForm(parent);
		}

		CDriveDropDown::CDriveDropDown(IControl *parent) : CDriveDropDown()
		{
			setParent(parent);
		}

		CDriveDropDown::~CDriveDropDown()
		{
			if (m_pDropDown)
				m_pDropDown->Release();
		}
	#pragma endregion

	#pragma region Interface getters
		IControl *CDriveDropDown::getControl(const PointF &position)
		{
			Vec4f v{ ntl::Inversed<float>(getTransformMatrix()) * Vec4f{ position.X, position.Y, 0, 1 } };
			if (getDropDown()->isInside(PointF{ v.X, v.Y }))
				return this;
			return nullptr;
		}

		RectF CDriveDropDown::getClientRect()
		{
			return getDropDown()->getClientRect();
		}

		RectF CDriveDropDown::getRenderRect()
		{
			return getDropDown()->getRenderRect();
		}

		CursorType CDriveDropDown::getCursor()
		{
			if (isEnabled(true) && getForm())
			{
				PointF pos{ FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())) };
				return getDropDown()->getCursor(pos, CControl::getCursor());
			}
			return CControl::getCursor();
		}

		int CDriveDropDown::getDriveCount()
		{
			return getDropDown()->getItemCount();
		}

		String CDriveDropDown::getDrive(const int index)
		{
			IListItemIcon *item{ cast<IListItemIcon*>(getDropDown()->getItem(index)) };
			if (item)
				return item->getCaption();
			return L"";
		}

		int CDriveDropDown::getSelectedDriveIndex()
		{
			return getDropDown()->getActiveIndex();
		}

		String CDriveDropDown::getSelectedDrive()
		{
			IListItemIcon *item{ cast<IListItemIcon*>(getDropDown()->getItem(getDropDown()->getActiveIndex())) };
			if (item)
				return item->getCaption();
			return L"";
		}

		IDirectoryTree *CDriveDropDown::getDirectoryTree()
		{
			return m_pDirectoryTree;
		}

		bool CDriveDropDown::hasExtra()
		{
			return getDropDown()->isOpened();
		}
	#pragma endregion

	#pragma region Getters
		CBuiltInDropDown::State CDriveDropDown::getState()
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

		bool CDriveDropDown::isOpened()
		{
			return getDropDown()->isOpened();
		}

		CBuiltInDropDown::OpenDirection CDriveDropDown::getOpenDirection()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getOpenDirection();
			return CBuiltInDropDown::OpenDirection::Down;
		}

		CBuiltInDropDown::ArrowArea CDriveDropDown::getArrowArea()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowArea();
			return CBuiltInDropDown::ArrowArea::Height;
		}

		float CDriveDropDown::getListWidth()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListWidth();
			return 0;
		}

		float CDriveDropDown::getListMaxHeight()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListMaxHeight();
			return 0;
		}

		float CDriveDropDown::getArrowAreaSize()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowAreaSize();
			return 0;
		}

		float CDriveDropDown::getArrowSize()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowSize();
			return 0;
		}

		RectF CDriveDropDown::getBorderWidth()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getBorderWidth();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CDriveDropDown::getBorderRadius()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getBorderRadius();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CDriveDropDown::getPadding()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getPadding();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CDriveDropDown::getArrowBorderWidth()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowBorderWidth();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CDriveDropDown::getArrowBorderRadius()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowBorderRadius();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CDriveDropDown::getListBorderWidth()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListBorderWidth();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CDriveDropDown::getListBorderRadius()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListBorderRadius();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CDriveDropDown::getListPadding()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListPadding();
			return RectF{ 0, 0, 0, 0 };
		}

		Color CDriveDropDown::getShadowColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getShadowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		PointF CDriveDropDown::getShadowShift(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getShadowShift(state);
			return PointF{ 0, 0 };
		}

		int CDriveDropDown::getShadowRadius(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getShadowRadius(state);
			return 0;
		}

		BorderColor CDriveDropDown::getBorderColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getBorderColor(state);
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CDriveDropDown::getBackgroundColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CDriveDropDown::getBackgroundGradient(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getBackgroundGradient(state);
			return nullptr;
		}

		BorderColor CDriveDropDown::getArrowBorderColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowBorderColor(state);
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CDriveDropDown::getArrowBackgroundColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CDriveDropDown::getArrowBackgroundGradient(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowBackgroundGradient(state);
			return nullptr;
		}

		Color CDriveDropDown::getArrowColor(const CBuiltInDropDown::State state)
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getArrowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		BorderColor CDriveDropDown::getListBorderColor()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListBorderColor();
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CDriveDropDown::getListBackgroundColor()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListBackgroundColor();
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CDriveDropDown::getListBackgroundGradient()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListBackgroundGradient();
			return nullptr;
		}

		Color CDriveDropDown::getListShadowColor()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListShadowColor();
			return Color{ 0, 0, 0, 0 };
		}

		PointF CDriveDropDown::getListShadowShift()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListShadowShift();
			return PointF{ 0, 0 };
		}

		int CDriveDropDown::getListShadowRadius()
		{
			CDropDown *dd{ cast<CDropDown*>(getDropDown()) };
			if (dd)
				return dd->getListShadowRadius();
			return 0;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDriveDropDown::setDPI(const Point &value)
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

		bool CDriveDropDown::setSelectedDriveIndex(const int value)
		{
			if (value >= 0 && value < getDropDown()->getItemCount() && value != m_pDropDown->getActiveIndex())
			{
				RectF r{ m_pDropDown->getRenderRect() };
				if (m_pDropDown->setActiveIndex(value))
				{
					if (m_pDirectoryTree)
						m_pDirectoryTree->setRootDirectory(getSelectedDrive());
					if (OnSelect)
						OnSelect(this, value);
					Repaint(r + m_pDropDown->getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CDriveDropDown::setSelectedDrive(const String &value)
		{
			for (int i = 0; i < getDropDown()->getItemCount(); i++)
			{
				IListItemIcon *item{ cast<IListItemIcon*>(m_pDropDown->getItem(i)) };
				if (item && item->getCaption() == value)
					return setSelectedDriveIndex(i);
			}
			return false;
		}

		bool CDriveDropDown::setDirectoryTree(IDirectoryTree *value)
		{
			if (value != m_pDirectoryTree)
			{
				if (!value || (value && value->getForm() && value->getForm() == getForm()))
				{
					m_pDirectoryTree = value;
					if (m_pDirectoryTree)
						m_pDirectoryTree->setRootDirectory(getSelectedDrive());
					return true;
				}
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CDriveDropDown::setDropDown(IBuiltInDropDown *value)
		{
			if (value && value != m_pDropDown)
			{
				CLockRepaint lock{ this };
				value->setListener(&m_cListener);
				value->NotifyOnFreeResources();
				int index{ -1 };
				if (m_pDropDown)
				{
					Repaint(m_pDropDown->getRenderRect(), true);
					index = m_pDropDown->getActiveIndex();
					m_pDropDown->Release();
				}
				m_pDropDown = value;
				m_pDropDown->setEditable(false);
				UpdateDropDown();
				Rescan();
				if (index >= 0)
					m_pDropDown->setActiveIndex(index);
				m_pDropDown->setFocused(isFocused());
				m_pDropDown->setEnabled(isEnabled(false));
				Repaint(m_pDropDown->getRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CDriveDropDown::setOpenDirection(const CBuiltInDropDown::OpenDirection value)
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

		bool CDriveDropDown::setListWidth(const float value)
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

		bool CDriveDropDown::setListMaxHeight(const float value)
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

		bool CDriveDropDown::setArrowArea(const CBuiltInDropDown::ArrowArea value)
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

		bool CDriveDropDown::setArrowAreaSize(const float value)
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

		bool CDriveDropDown::setArrowSize(const float value)
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

		bool CDriveDropDown::setBorderWidth(const RectF &value)
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

		bool CDriveDropDown::setBorderRadius(const RectF &value)
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

		bool CDriveDropDown::setPadding(const RectF &value)
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

		bool CDriveDropDown::setArrowBorderWidth(const RectF &value)
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

		bool CDriveDropDown::setArrowBorderRadius(const RectF &value)
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

		bool CDriveDropDown::setListBorderWidth(const RectF &value)
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

		bool CDriveDropDown::setListBorderRadius(const RectF &value)
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

		bool CDriveDropDown::setListPadding(const RectF &value)
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

		bool CDriveDropDown::setShadowColor(const CBuiltInDropDown::State state, const Color &value)
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

		bool CDriveDropDown::setShadowShift(const CBuiltInDropDown::State state, const PointF &value)
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

		bool CDriveDropDown::setShadowRadius(const CBuiltInDropDown::State state, const int value)
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

		bool CDriveDropDown::setBorderColor(const CBuiltInDropDown::State state, const BorderColor &value)
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

		bool CDriveDropDown::setLeftBorderColor(const CBuiltInDropDown::State state, const Color &value)
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

		bool CDriveDropDown::setTopBorderColor(const CBuiltInDropDown::State state, const Color &value)
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

		bool CDriveDropDown::setRightBorderColor(const CBuiltInDropDown::State state, const Color &value)
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

		bool CDriveDropDown::setBottomBorderColor(const CBuiltInDropDown::State state, const Color &value)
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

		bool CDriveDropDown::setBackgroundColor(const CBuiltInDropDown::State state, const Color &value)
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

		bool CDriveDropDown::setArrowBorderColor(const CBuiltInDropDown::State state, const BorderColor &value)
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

		bool CDriveDropDown::setArrowLeftBorderColor(const CBuiltInDropDown::State state, const Color &value)
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

		bool CDriveDropDown::setArrowTopBorderColor(const CBuiltInDropDown::State state, const Color &value)
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

		bool CDriveDropDown::setArrowRightBorderColor(const CBuiltInDropDown::State state, const Color &value)
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

		bool CDriveDropDown::setArrowBottomBorderColor(const CBuiltInDropDown::State state, const Color &value)
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

		bool CDriveDropDown::setArrowBackgroundColor(const CBuiltInDropDown::State state, const Color &value)
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

		bool CDriveDropDown::setArrowColor(const CBuiltInDropDown::State state, const Color &value)
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

		bool CDriveDropDown::setListBorderColor(const BorderColor &value)
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

		bool CDriveDropDown::setListLeftBorderColor(const Color &value)
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

		bool CDriveDropDown::setListTopBorderColor(const Color &value)
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

		bool CDriveDropDown::setListRightBorderColor(const Color &value)
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

		bool CDriveDropDown::setListBottomBorderColor(const Color &value)
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

		bool CDriveDropDown::setListBackgroundColor(const Color &value)
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

		bool CDriveDropDown::setListShadowColor(const Color &value)
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

		bool CDriveDropDown::setListShadowShift(const PointF &value)
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

		bool CDriveDropDown::setListShadowRadius(const int value)
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
	#pragma endregion

	#pragma region IControl methods
		void CDriveDropDown::Refresh(const bool refresh_children)
		{
			getDropDown()->Refresh();
		}
	#pragma endregion

	#pragma region Helpers
		IBuiltInDropDown *CDriveDropDown::getDropDown()
		{
			if (!m_pDropDown)
			{
				m_pDropDown = new CDropDown(this);
				m_pDropDown->setListener(&m_cListener);
				m_pDropDown->setEnabled(isEnabled(false));
				m_pDropDown->setFocused(isFocused());
				m_pDropDown->setEditable(false);
				if (getStyle())
					m_pDropDown->UpdateFromStyle(getStyle(), m_sClassName + L".DropDown");
				UpdateDropDown();
			}
			return m_pDropDown;
		}

		void CDriveDropDown::UpdateFromStyle(IStyle *style)
		{
			getDropDown()->UpdateFromStyle(style, m_sClassName + L".DropDown");
			UpdateDropDown();
		}

		void CDriveDropDown::UpdateDropDown()
		{
			getDropDown()->setSize(PointF{ getWidth(), getHeight() });
		}

		bool CDriveDropDown::Open()
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

		bool CDriveDropDown::Close()
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

		bool CDriveDropDown::Rescan()
		{
			StringArray drives{ Application->FileSystem->SearchDrives() };
			IBuiltInDropDown *dd{ getDropDown() };
			bool changed;
			if (dd->getItemCount() == (int)drives.size())
			{
				for (int i = 0; i < dd->getItemCount(); i++)
				{
					IListItemIcon *item{ cast<IListItemIcon*>(dd->getItem(i)) };
					if (!item || item->getCaption() != drives[i])
					{
						changed = true;
						break;
					}
				}
				changed = false;
			}
			else
				changed = true;
			if (changed)
			{
				int index{ dd->getActiveIndex() }, last_index{ index }, c_index{ -1 };
				dd->DeleteItems();
				for (int i = 0; i < (int)drives.size(); i++)
				{
					dd->AddItem(new CListItemIcon(drives[i]));
					if (drives[i] == L"C:\\")
						c_index = i;
				}
				if (index < 0 || index >= dd->getItemCount())
					index = c_index;
				if (index >= 0)
					dd->setActiveIndex(index);
				if (OnSelect && last_index != dd->getActiveIndex())
					OnSelect(this, dd->getActiveIndex());
				if (m_pDirectoryTree)
					m_pDirectoryTree->setRootDirectory(getSelectedDrive());
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CDriveDropDown::Render()
		{
			getDropDown()->Render(false, getTransformMatrix(), nullptr);
		}

		void CDriveDropDown::RenderList()
		{
			getDropDown()->Render(true, getTransformMatrix(), nullptr);
		}
	#pragma endregion
	}
}