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
#pragma region CGradientListener
	CBuiltInDropDown::CGradientListener::CGradientListener(CBuiltInDropDown *control) :
		m_pControl{ control }
	{

	}

	void CBuiltInDropDown::CGradientListener::NotifyOnChange()
	{
		if (m_pControl->m_pCanvasControl)
			m_pControl->m_pCanvasControl->setValid(false);
		if (m_pControl->m_pCanvasList)
			m_pControl->m_pCanvasList->setValid(false);
		if (!m_pControl->m_bIgnoreGradient && m_pControl->m_pListener)
			m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getRenderRect());
	}
#pragma endregion

#pragma region Constructor & destructor
	CBuiltInDropDown::CBuiltInDropDown(const bool editable, FCompare compare, FGetItemText get_item_text, FSearch search) :
		CBuiltInControl(L"DropDown", { 145, 21 }),
		m_cGradientListener{ this },
		m_bEditable{ editable },
		m_bOpened{ false },
		m_bArrowAtRight{ true },
		m_bSortable{ false },
		m_eOpenDirection{ OpenDirection::Down },
		m_eArrowArea{ ArrowArea::Height },
		m_fListWidth{ -1 },
		m_fListMaxHeight{ 150 },
		m_iActiveIndex{ -1 },
		m_fArrowAreaSize{ 0.1f },
		m_fArrowSize{ 0.4f },
		m_sBorderWidth{ 1, 1, 1, 1 },
		m_sBorderRadius{ 0, 0, 0, 0 },
		m_sPadding{ 2, 2, 2, 2 },
		m_sArrowBorderWidth{ 1, 1, 1, 1 },
		m_sArrowBorderRadius{ 0, 0, 0, 0 },
		m_sListBorderWidth{ 1, 1, 1, 1 },
		m_sListBorderRadius{ 0, 0, 0, 0 },
		m_sListPadding{ 2, 2, 2, 2 },
		m_fSearchResetInterval{ 2 },
		m_fCompare{ compare },
		m_fGetItemText{ get_item_text },
		m_fSearch{ search },
		m_bLoopActiveItemOnDoubleClick{ false },
		m_aShadowColor{
			{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
		m_aShadowShift{
			{ PointF{ 0, 0 }, PointF{ 0, 0 } },
			{ PointF{ 0, 0 }, PointF{ 0, 0 } },
			{ PointF{ 0, 0 }, PointF{ 0, 0 } },
			{ PointF{ 0, 0 }, PointF{ 0, 0 } },
			{ PointF{ 0, 0 }, PointF{ 0, 0 } } },
		m_aShadowRadius{
			{ 1, 1 },
			{ 1, 1 },
			{ 1, 1 },
			{ 1, 1 },
			{ 1, 1 } },
		m_aBorderColor{
			{
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } } 
			},
			{
				BorderColor{ Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 } },
				BorderColor{ Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 } }
			},
			{
				BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
				BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } }
			},
			{
				BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
				BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } }
			},
			{
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } }
			}
		},
		m_aBackgroundColor{
			{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
			{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
			{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
			{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
			{ Color{ 244, 244, 244, 255 }, Color{ 244, 244, 244, 255 } } },
		m_aBackgroundGradient{
			{ Gradient{ &m_cGradientListener }, Gradient{ &m_cGradientListener } },
			{ Gradient{ &m_cGradientListener }, Gradient{ &m_cGradientListener } },
			{ Gradient{ &m_cGradientListener }, Gradient{ &m_cGradientListener } },
			{ Gradient{ &m_cGradientListener }, Gradient{ &m_cGradientListener } },
			{ Gradient{ &m_cGradientListener }, Gradient{ &m_cGradientListener } } },
		m_aArrowBorderColor{
			{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } }
			},
			{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 } }
			},
			{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 } }
			},
			{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 } }
			},
			{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } }
			}
		},
		m_aArrowBackgroundColor{
			{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
		m_aArrowBackgroundGradient{
			{ Gradient{ &m_cGradientListener }, Gradient{ &m_cGradientListener } },
			{ Gradient{ &m_cGradientListener }, Gradient{ &m_cGradientListener } },
			{ Gradient{ &m_cGradientListener }, Gradient{ &m_cGradientListener } },
			{ Gradient{ &m_cGradientListener }, Gradient{ &m_cGradientListener } },
			{ Gradient{ &m_cGradientListener }, Gradient{ &m_cGradientListener } } },
		m_aArrowColor{
			{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } },
			{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } },
			{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } },
			{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } },
			{ Color{ 109, 109, 109, 255 }, Color{ 109, 109, 109, 255 } } },
		m_aListBorderColor{
			BorderColor{ Color{ 227, 227, 227, 255 }, Color{ 227, 227, 227, 255 }, Color{ 227, 227, 227, 255 }, Color{ 227, 227, 227, 255 } },
			BorderColor{ Color{ 227, 227, 227, 255 }, Color{ 227, 227, 227, 255 }, Color{ 227, 227, 227, 255 }, Color{ 227, 227, 227, 255 } } },
		m_aListBackgroundColor{
			Color{ 255, 255, 255, 255 },
			Color{ 255, 255, 255, 255 } },
		m_aListBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener } },
		m_aListShadowColor{
			Color{ 152, 152, 152, 200 },
			Color{ 152, 152, 152, 200 } },
		m_aListShadowShift{
			PointF{ 2, 2 },
			PointF{ 2, 2 } },
		m_aListShadowRadius{ 3, 3 },
		m_pTextInput{ nullptr },
		m_pScroll{ nullptr },
		m_bIgnoreGradient{ true },
		m_pListItemOwner{ nullptr },
		m_sListRect{ 0, 0, 0, 0 },
		m_fListScroll{ 0 },
		m_fListScrollMax{ 0 },
		m_eHoveredElement{ ElementType::None },
		m_eDownElement{ ElementType::None },
		m_bSorted{ false },
		m_sLastSearch{ std::chrono::steady_clock::now() },
		m_pListener{ nullptr },
		m_cTextInputListener{ this },
		m_cScrollListener{ this },
		m_pCanvasControl{ nullptr },
		m_pCanvasList{ nullptr }		
	{
		// Non-editable
		m_aBackgroundGradient[(int)State::Normal][0].setPointCount(4);
		m_aBackgroundGradient[(int)State::Normal][0].setPoint(0, Color1D{ 0.000f, Color{ 242, 242, 242, 255 } });
		m_aBackgroundGradient[(int)State::Normal][0].setPoint(1, Color1D{ 0.499f, Color{ 235, 235, 235, 255 } });
		m_aBackgroundGradient[(int)State::Normal][0].setPoint(2, Color1D{ 0.500f, Color{ 221, 221, 221, 255 } });
		m_aBackgroundGradient[(int)State::Normal][0].setPoint(3, Color1D{ 1.000f, Color{ 207, 207, 207, 255 } });
		m_aArrowBackgroundGradient[(int)State::Normal][0].setPointCount(4);
		m_aArrowBackgroundGradient[(int)State::Normal][0].setPoint(0, Color1D{ 0.000f, Color{ 242, 242, 242, 255 } });
		m_aArrowBackgroundGradient[(int)State::Normal][0].setPoint(1, Color1D{ 0.499f, Color{ 235, 235, 235, 255 } });
		m_aArrowBackgroundGradient[(int)State::Normal][0].setPoint(2, Color1D{ 0.500f, Color{ 221, 221, 221, 255 } });
		m_aArrowBackgroundGradient[(int)State::Normal][0].setPoint(3, Color1D{ 1.000f, Color{ 207, 207, 207, 255 } });

		m_aBackgroundGradient[(int)State::Hovered][0].setPointCount(4);
		m_aBackgroundGradient[(int)State::Hovered][0].setPoint(0, Color1D{ 0.000f, Color{ 234, 246, 253, 255 } });
		m_aBackgroundGradient[(int)State::Hovered][0].setPoint(1, Color1D{ 0.499f, Color{ 217, 240, 252, 255 } });
		m_aBackgroundGradient[(int)State::Hovered][0].setPoint(2, Color1D{ 0.500f, Color{ 190, 230, 253, 255 } });
		m_aBackgroundGradient[(int)State::Hovered][0].setPoint(3, Color1D{ 1.000f, Color{ 167, 217, 245, 255 } });
		m_aArrowBackgroundGradient[(int)State::Hovered][0].setPointCount(4);
		m_aArrowBackgroundGradient[(int)State::Hovered][0].setPoint(0, Color1D{ 0.000f, Color{ 234, 246, 253, 255 } });
		m_aArrowBackgroundGradient[(int)State::Hovered][0].setPoint(1, Color1D{ 0.499f, Color{ 217, 240, 252, 255 } });
		m_aArrowBackgroundGradient[(int)State::Hovered][0].setPoint(2, Color1D{ 0.500f, Color{ 190, 230, 253, 255 } });
		m_aArrowBackgroundGradient[(int)State::Hovered][0].setPoint(3, Color1D{ 1.000f, Color{ 167, 217, 245, 255 } });

		m_aBackgroundGradient[(int)State::Focused][0].setPointCount(4);
		m_aBackgroundGradient[(int)State::Focused][0].setPoint(0, Color1D{ 0.000f, Color{ 222, 237, 246, 255 } });
		m_aBackgroundGradient[(int)State::Focused][0].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 246, 255 } });
		m_aBackgroundGradient[(int)State::Focused][0].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 239, 255 } });
		m_aBackgroundGradient[(int)State::Focused][0].setPoint(3, Color1D{ 1.000f, Color{ 102, 175, 215, 255 } });
		m_aArrowBackgroundGradient[(int)State::Focused][0].setPointCount(4);
		m_aArrowBackgroundGradient[(int)State::Focused][0].setPoint(0, Color1D{ 0.000f, Color{ 222, 237, 246, 255 } });
		m_aArrowBackgroundGradient[(int)State::Focused][0].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 246, 255 } });
		m_aArrowBackgroundGradient[(int)State::Focused][0].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 239, 255 } });
		m_aArrowBackgroundGradient[(int)State::Focused][0].setPoint(3, Color1D{ 1.000f, Color{ 102, 175, 215, 255 } });

		m_aBackgroundGradient[(int)State::FocusedHovered][0].setPointCount(4);
		m_aBackgroundGradient[(int)State::FocusedHovered][0].setPoint(0, Color1D{ 0.000f, Color{ 222, 237, 246, 255 } });
		m_aBackgroundGradient[(int)State::FocusedHovered][0].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 246, 255 } });
		m_aBackgroundGradient[(int)State::FocusedHovered][0].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 239, 255 } });
		m_aBackgroundGradient[(int)State::FocusedHovered][0].setPoint(3, Color1D{ 1.000f, Color{ 102, 175, 215, 255 } });
		m_aArrowBackgroundGradient[(int)State::FocusedHovered][0].setPointCount(4);
		m_aArrowBackgroundGradient[(int)State::FocusedHovered][0].setPoint(0, Color1D{ 0.000f, Color{ 222, 237, 246, 255 } });
		m_aArrowBackgroundGradient[(int)State::FocusedHovered][0].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 246, 255 } });
		m_aArrowBackgroundGradient[(int)State::FocusedHovered][0].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 239, 255 } });
		m_aArrowBackgroundGradient[(int)State::FocusedHovered][0].setPoint(3, Color1D{ 1.000f, Color{ 102, 175, 215, 255 } });

		// Editable
		m_aArrowBackgroundGradient[(int)State::Hovered][1].setPointCount(4);
		m_aArrowBackgroundGradient[(int)State::Hovered][1].setPoint(0, Color1D{ 0.000f, Color{ 234, 246, 253, 255 } });
		m_aArrowBackgroundGradient[(int)State::Hovered][1].setPoint(1, Color1D{ 0.499f, Color{ 217, 240, 252, 255 } });
		m_aArrowBackgroundGradient[(int)State::Hovered][1].setPoint(2, Color1D{ 0.500f, Color{ 190, 230, 253, 255 } });
		m_aArrowBackgroundGradient[(int)State::Hovered][1].setPoint(3, Color1D{ 1.000f, Color{ 167, 217, 245, 255 } });

		m_aArrowBackgroundGradient[(int)State::Focused][1].setPointCount(4);
		m_aArrowBackgroundGradient[(int)State::Focused][1].setPoint(0, Color1D{ 0.000f, Color{ 222, 237, 246, 255 } });
		m_aArrowBackgroundGradient[(int)State::Focused][1].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 246, 255 } });
		m_aArrowBackgroundGradient[(int)State::Focused][1].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 239, 255 } });
		m_aArrowBackgroundGradient[(int)State::Focused][1].setPoint(3, Color1D{ 1.000f, Color{ 102, 175, 215, 255 } });

		m_aArrowBackgroundGradient[(int)State::FocusedHovered][1].setPointCount(4);
		m_aArrowBackgroundGradient[(int)State::FocusedHovered][1].setPoint(0, Color1D{ 0.000f, Color{ 222, 237, 246, 255 } });
		m_aArrowBackgroundGradient[(int)State::FocusedHovered][1].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 246, 255 } });
		m_aArrowBackgroundGradient[(int)State::FocusedHovered][1].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 239, 255 } });
		m_aArrowBackgroundGradient[(int)State::FocusedHovered][1].setPoint(3, Color1D{ 1.000f, Color{ 102, 175, 215, 255 } });

		m_bIgnoreGradient = false;
	}

	CBuiltInDropDown::~CBuiltInDropDown()
	{
		DeleteItems();
		if (m_pTextInput)
			m_pTextInput->Release();
		if (m_pScroll)
			m_pScroll->Release();
		if (m_pListItemOwner)
			m_pListItemOwner->Release();
	}
#pragma endregion

#pragma region IBuiltInControl getters
	IBuiltInControlListener *CBuiltInDropDown::getListener()
	{
		return m_pListener;
	}

	bool CBuiltInDropDown::isHovered()
	{
		return m_eHoveredElement != ElementType::None;
	}

	RectF CBuiltInDropDown::getClientRect()
	{
		RectF result{
			m_sBorderWidth.Left + m_sPadding.Left,
			m_sBorderWidth.Top + m_sPadding.Top,
			getWidth() - m_sBorderWidth.Right - m_sPadding.Right,
			getHeight() - m_sBorderWidth.Bottom - m_sPadding.Bottom
		};
		if (m_bArrowAtRight)
			switch (m_eArrowArea)
			{
			case ArrowArea::Height:
				result.Right = getWidth() - getHeight();
				break;
			case ArrowArea::WidthPart:
				result.Right = getWidth() * (1 - m_fArrowAreaSize);
				break;
			default:
				result.Right = getWidth() - m_fArrowAreaSize;
			}
		else
			switch (m_eArrowArea)
			{
			case ArrowArea::Height:
				result.Left = getHeight();
				break;
			case ArrowArea::WidthPart:
				result.Left = getWidth() * m_fArrowAreaSize;
				break;
			default:
				result.Left = m_fArrowAreaSize;
			}
		result.validate();
		return result;
	}

	RectF CBuiltInDropDown::getRenderRect()
	{
		RectF result{ getRenderRect(State::Normal) };
		for (int i = 1; i <= (int)State::Disabled; i++)
			result += getRenderRect((State)i);
		return result;
	}

	CursorType CBuiltInDropDown::getCursor(const PointF &position, const CursorType def)
	{
		if (isEnabled() && m_bEditable)
		{
			RectF client{ getClientRect() };
			return getTextInput()->getCursor(PointF{ position.X - client.Left, position.Y - client.Top }, def);
		}
		return def;
	}

	bool CBuiltInDropDown::isInside(const PointF &position)
	{
		if (position.X >= 0 && position.X < getWidth() && position.Y >= 0 && position.Y < getHeight())
			return true;
		if (m_bOpened && position.X >= m_sListRect.Left && position.X < m_sListRect.Right && position.Y >= m_sListRect.Top && position.Y < m_sListRect.Bottom)
			return true;
		return false;
	}

	bool CBuiltInDropDown::isDown()
	{
		return m_eDownElement != ElementType::None;
	}
#pragma endregion

#pragma region IBuiltInDropDown getters
	int CBuiltInDropDown::getItemCount()
	{
		return (int)m_aItems.size();
	}

	IListItem *CBuiltInDropDown::getItem(const int index)
	{
		if (index >= 0 && index < (int)m_aItems.size())
		{
			SortItems();
			return m_aItems[index];
		}
		return nullptr;
	}

	int CBuiltInDropDown::getItemIndex(IListItem *item)
	{
		SortItems();
		for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			if (*pos == item)
				return int(pos - m_aItems.begin());
		return -1;
	}

	bool CBuiltInDropDown::isEditable()
	{
		return m_bEditable;
	}

	bool CBuiltInDropDown::isOpened()
	{
		return m_bOpened;
	}

	bool CBuiltInDropDown::isSortable()
	{
		return m_bSortable;
	}

	String CBuiltInDropDown::getText()
	{
		if (m_bEditable)
			return getTextInput()->getText();
		if (m_iActiveIndex >= 0 && m_fGetItemText)
			return m_fGetItemText(m_aItems[m_iActiveIndex]);
		return L"";
	}

	int CBuiltInDropDown::getActiveIndex()
	{
		SortItems();
		return m_iActiveIndex;
	}

	IBuiltInDropDown::FCompare CBuiltInDropDown::getCompareFunc()
	{
		return m_fCompare;
	}

	IBuiltInDropDown::FGetItemText CBuiltInDropDown::getItemTextFunc()
	{
		return m_fGetItemText;
	}

	IBuiltInDropDown::FSearch CBuiltInDropDown::getSearchFunc()
	{
		return m_fSearch;
	}

	PointF CBuiltInDropDown::getMousePosition()
	{
		if (getControl() && getControl()->getForm())
		{
			Point cl{ getControl()->getForm()->ScreenToClient(Application->Mouse->getPosition()) };
			PointF p{ getControl()->FormToLocal(PointF{ (float)cl.X, (float)cl.Y }) };
			return PointF{ p.X - getLeft(), p.Y - getTop() };
		}
		return PointF{ 0, 0 };
	}

	bool CBuiltInDropDown::isLoopActiveItemOnDoubleClick()
	{
		return m_bLoopActiveItemOnDoubleClick;
	}
#pragma endregion

#pragma region Getters
	CBuiltInDropDown::State CBuiltInDropDown::getState()
	{
		if (!isEnabled())
			return State::Disabled;
		if (isFocused())
		{
			if (isHovered())
				return State::FocusedHovered;
			return State::Focused;
		}
		if (isHovered())
			return State::Hovered;
		return State::Normal;
	}

	bool CBuiltInDropDown::isArrowAtRight() const
	{
		return m_bArrowAtRight;
	}

	CBuiltInDropDown::OpenDirection CBuiltInDropDown::getOpenDirection() const
	{
		return m_eOpenDirection;
	}

	CBuiltInDropDown::ArrowArea CBuiltInDropDown::getArrowArea() const
	{
		return m_eArrowArea;
	}

	float CBuiltInDropDown::getListWidth() const
	{
		return m_fListWidth;
	}

	float CBuiltInDropDown::getListMaxHeight() const
	{
		return m_fListMaxHeight;
	}

	float CBuiltInDropDown::getArrowAreaSize() const
	{
		return m_fArrowAreaSize;
	}

	float CBuiltInDropDown::getArrowSize() const
	{
		return m_fArrowSize;
	}

	RectF CBuiltInDropDown::getBorderWidth() const
	{
		return m_sBorderWidth;
	}

	RectF CBuiltInDropDown::getBorderRadius() const
	{
		return m_sBorderRadius;
	}

	RectF CBuiltInDropDown::getPadding() const
	{
		return m_sPadding;
	}

	RectF CBuiltInDropDown::getArrowBorderWidth() const
	{
		return m_sArrowBorderWidth;
	}

	RectF CBuiltInDropDown::getArrowBorderRadius() const
	{
		return m_sArrowBorderRadius;
	}

	RectF CBuiltInDropDown::getListBorderWidth() const
	{
		return m_sListBorderWidth;
	}

	RectF CBuiltInDropDown::getListBorderRadius() const
	{
		return m_sListBorderRadius;
	}

	RectF CBuiltInDropDown::getListPadding() const
	{
		return m_sListPadding;
	}

	Color CBuiltInDropDown::getShadowColor(const State state) const
	{
		return m_aShadowColor[(int)state][0];
	}

	Color CBuiltInDropDown::getShadowColorEditable(const State state) const
	{
		return m_aShadowColor[(int)state][1];
	}

	PointF CBuiltInDropDown::getShadowShift(const State state) const
	{
		return m_aShadowShift[(int)state][0];
	}

	PointF CBuiltInDropDown::getShadowShiftEditable(const State state) const
	{
		return m_aShadowShift[(int)state][1];
	}

	int CBuiltInDropDown::getShadowRadius(const State state) const
	{
		return m_aShadowRadius[(int)state][0];
	}

	int CBuiltInDropDown::getShadowRadiusEditable(const State state) const
	{
		return m_aShadowRadius[(int)state][1];
	}

	BorderColor CBuiltInDropDown::getBorderColor(const State state) const
	{
		return m_aBorderColor[(int)state][0];
	}

	BorderColor CBuiltInDropDown::getBorderColorEditable(const State state) const
	{
		return m_aBorderColor[(int)state][1];
	}

	Color CBuiltInDropDown::getLeftBorderColor(const State state) const
	{
		return m_aBorderColor[(int)state][0].Left;
	}

	Color CBuiltInDropDown::getLeftBorderColorEditable(const State state) const
	{
		return m_aBorderColor[(int)state][1].Left;
	}

	Color CBuiltInDropDown::getTopBorderColor(const State state) const
	{
		return m_aBorderColor[(int)state][0].Top;
	}

	Color CBuiltInDropDown::getTopBorderColorEditable(const State state) const
	{
		return m_aBorderColor[(int)state][1].Top;
	}

	Color CBuiltInDropDown::getRightBorderColor(const State state) const
	{
		return m_aBorderColor[(int)state][0].Right;
	}

	Color CBuiltInDropDown::getRightBorderColorEditable(const State state) const
	{
		return m_aBorderColor[(int)state][1].Right;
	}

	Color CBuiltInDropDown::getBottomBorderColor(const State state) const
	{
		return m_aBorderColor[(int)state][0].Bottom;
	}

	Color CBuiltInDropDown::getBottomBorderColorEditable(const State state) const
	{
		return m_aBorderColor[(int)state][1].Bottom;
	}

	Color CBuiltInDropDown::getBackgroundColor(const State state) const
	{
		return m_aBackgroundColor[(int)state][0];
	}

	Color CBuiltInDropDown::getBackgroundColorEditable(const State state) const
	{
		return m_aBackgroundColor[(int)state][1];
	}

	Gradient *CBuiltInDropDown::getBackgroundGradient(const State state)
	{
		return &m_aBackgroundGradient[(int)state][0];
	}

	Gradient *CBuiltInDropDown::getBackgroundGradientEditable(const State state)
	{
		return &m_aBackgroundGradient[(int)state][1];
	}

	BorderColor CBuiltInDropDown::getArrowBorderColor(const State state) const
	{
		return m_aArrowBorderColor[(int)state][0];
	}

	BorderColor CBuiltInDropDown::getArrowBorderColorEditable(const State state) const
	{
		return m_aArrowBorderColor[(int)state][1];
	}

	Color CBuiltInDropDown::getArrowLeftBorderColor(const State state) const
	{
		return m_aArrowBorderColor[(int)state][0].Left;
	}

	Color CBuiltInDropDown::getArrowLeftBorderColorEditable(const State state) const
	{
		return m_aArrowBorderColor[(int)state][1].Left;
	}

	Color CBuiltInDropDown::getArrowTopBorderColor(const State state) const
	{
		return m_aArrowBorderColor[(int)state][0].Top;
	}

	Color CBuiltInDropDown::getArrowTopBorderColorEditable(const State state) const
	{
		return m_aArrowBorderColor[(int)state][1].Top;
	}

	Color CBuiltInDropDown::getArrowRightBorderColor(const State state) const
	{
		return m_aArrowBorderColor[(int)state][0].Right;
	}

	Color CBuiltInDropDown::getArrowRightBorderColorEditable(const State state) const
	{
		return m_aArrowBorderColor[(int)state][1].Right;
	}

	Color CBuiltInDropDown::getArrowBottomBorderColor(const State state) const
	{
		return m_aArrowBorderColor[(int)state][0].Bottom;
	}

	Color CBuiltInDropDown::getArrowBottomBorderColorEditable(const State state) const
	{
		return m_aArrowBorderColor[(int)state][1].Bottom;
	}

	Color CBuiltInDropDown::getArrowBackgroundColor(const State state) const
	{
		return m_aArrowBackgroundColor[(int)state][0];
	}

	Color CBuiltInDropDown::getArrowBackgroundColorEditable(const State state) const
	{
		return m_aArrowBackgroundColor[(int)state][1];
	}

	Gradient *CBuiltInDropDown::getArrowBackgroundGradient(const State state)
	{
		return &m_aArrowBackgroundGradient[(int)state][0];
	}

	Gradient *CBuiltInDropDown::getArrowBackgroundGradientEditable(const State state)
	{
		return &m_aArrowBackgroundGradient[(int)state][1];
	}

	Color CBuiltInDropDown::getArrowColor(const State state) const
	{
		return m_aArrowColor[(int)state][0];
	}

	Color CBuiltInDropDown::getArrowColorEditable(const State state) const
	{
		return m_aArrowColor[(int)state][1];
	}

	BorderColor CBuiltInDropDown::getListBorderColor() const
	{
		return m_aListBorderColor[0];
	}

	BorderColor CBuiltInDropDown::getListBorderColorEditable() const
	{
		return m_aListBorderColor[1];
	}

	Color CBuiltInDropDown::getListLeftBorderColor() const
	{
		return m_aListBorderColor[0].Left;
	}

	Color CBuiltInDropDown::getListLeftBorderColorEditable() const
	{
		return m_aListBorderColor[1].Left;
	}

	Color CBuiltInDropDown::getListTopBorderColor() const
	{
		return m_aListBorderColor[0].Top;
	}

	Color CBuiltInDropDown::getListTopBorderColorEditable() const
	{
		return m_aListBorderColor[1].Top;
	}

	Color CBuiltInDropDown::getListRightBorderColor() const
	{
		return m_aListBorderColor[0].Right;
	}

	Color CBuiltInDropDown::getListRightBorderColorEditable() const
	{
		return m_aListBorderColor[1].Right;
	}

	Color CBuiltInDropDown::getListBottomBorderColor() const
	{
		return m_aListBorderColor[0].Bottom;
	}

	Color CBuiltInDropDown::getListBottomBorderColorEditable() const
	{
		return m_aListBorderColor[1].Bottom;
	}

	Color CBuiltInDropDown::getListBackgroundColor() const
	{
		return m_aListBackgroundColor[0];
	}

	Color CBuiltInDropDown::getListBackgroundColorEditable() const
	{
		return m_aListBackgroundColor[1];
	}

	Gradient *CBuiltInDropDown::getListBackgroundGradient()
	{
		return &m_aListBackgroundGradient[0];
	}

	Gradient *CBuiltInDropDown::getListBackgroundGradientEditable()
	{
		return &m_aListBackgroundGradient[1];
	}

	Color CBuiltInDropDown::getListShadowColor() const
	{
		return m_aListShadowColor[0];
	}

	Color CBuiltInDropDown::getListShadowColorEditable() const
	{
		return m_aListShadowColor[1];
	}

	PointF CBuiltInDropDown::getListShadowShift() const
	{
		return m_aListShadowShift[0];
	}

	PointF CBuiltInDropDown::getListShadowShiftEditable() const
	{
		return m_aListShadowShift[1];
	}

	int CBuiltInDropDown::getListShadowRadius() const
	{
		return m_aListShadowRadius[0];
	}

	int CBuiltInDropDown::getListShadowRadiusEditable() const
	{
		return m_aListShadowRadius[1];
	}

	float CBuiltInDropDown::getSearchResetInterval() const
	{
		return m_fSearchResetInterval;
	}
#pragma endregion

#pragma region IBuiltInControl setters
	void CBuiltInDropDown::setListener(IBuiltInControlListener *value)
	{
		m_pListener = value;
	}

	bool CBuiltInDropDown::setEnabled(const bool value)
	{
		if (CBuiltInControl::setEnabled(value))
		{
			if (!isEnabled())
			{
				NotifyOnMouseDownCancel();
				setFocused(false);
				Close();
			}
			getTextInput()->setEnabled(isEnabled());
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setFocused(const bool value)
	{
		if (CBuiltInControl::setFocused(value && isEnabled()))
		{
			getTextInput()->setFocused(m_bEditable && isFocused());
			if (!isFocused())
			{
				NotifyOnMouseDownCancel();
				Close();
			}
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setSize(const PointF &value)
	{
		if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, getSize()))
		{
			CBuiltInControl::setSize(value);
			UpdateInput();
			if (m_bOpened)
			{
				UpdateList();
				UpdateHoveredItem();
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setDPI(const Point &value)
	{
		Point old{ getDPI() };
		if (CBuiltInControl::setDPI(value))
		{
			if (m_bEditable)
				getTextInput()->setDPI(value);
			getScroll()->setDPI(value);
			PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
			float avg{ (s.X + s.Y) * 0.5f };
			if (ntl::IsGreater<float>(m_fListWidth, 0))
				m_fListWidth *= s.X;
			m_fListMaxHeight *= s.Y;
			m_sBorderWidth *= s;
			m_sBorderRadius *= avg;
			m_sPadding *= s;
			m_sArrowBorderWidth *= s;
			m_sArrowBorderRadius *= avg;
			m_sListBorderWidth *= s;
			m_sListBorderRadius *= avg;
			m_sListPadding *= s;
			for (int j = 0; j < 2; j++)
			{
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aShadowShift[i][j] *= s;
					m_aShadowRadius[i][j] = ntl::Round<int>((float)m_aShadowRadius[i][j] * avg);
				}
				m_aListShadowShift[j] *= s;
				m_aListShadowShift[j].Y = m_aListShadowShift[j].Y * s.Y;
				m_aListShadowRadius[j] = ntl::Round<int>((float)m_aListShadowRadius[j] * avg);
			}
			UpdateInput();
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			if (m_bOpened)
			{
				UpdateList();
				UpdateHoveredItem();
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region IBuiltInDropDown setters
	bool CBuiltInDropDown::setTextInput(IBuiltInTextInput *value)
	{
		if (value && value != m_pTextInput)
		{
			value->setListener(&m_cTextInputListener);
			value->NotifyOnFreeResources();
			if (m_pTextInput)
			{
				value->setText(m_pTextInput->getText());
				m_pTextInput->Release();
			}
			m_pTextInput = value;
			UpdateInput();
			m_pTextInput->setFocused(m_bEditable && isFocused());
			m_pTextInput->setEnabled(isEnabled());
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setScroll(IBuiltInScroll *value)
	{
		if (value && value != m_pScroll)
		{
			value->setListener(&m_cScrollListener);
			value->NotifyOnFreeResources();
			value->setMin(0);
			value->setMax(m_fListScrollMax);
			value->setVertical(true);
			if (m_pScroll)
			{
				value->setPosition(m_pScroll->getPosition());
				value->setSize(m_pScroll->getSize());
				m_pScroll->Release();
			}
			m_pScroll = value;
			if (m_bOpened)
			{
				UpdateList();
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setEditable(const bool value)
	{
		if (value != m_bEditable)
		{
			m_bEditable = value;
			if (m_bEditable)
			{
				getTextInput()->setEnabled(isEnabled());
				getTextInput()->setFocused(isFocused());
				UpdateInput();
			}
			else if (isEnabled() && isFocused())
				getTextInput()->setFocused(false);
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setSortable(const bool value)
	{
		if (value != m_bSortable)
		{
			m_bSortable = value;
			if (m_bSortable)
			{
				SortItems();
				if (m_pCanvasControl)
					m_pCanvasControl->setValid(false);
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setText(const String &value)
	{
		if (m_bEditable && value != getTextInput()->getText())
		{
			getTextInput()->setText(value);
			if (m_iActiveIndex >= 0)
			{
				QueryListItemOwner()->setIgnoreActivate(true);
				m_aItems[m_iActiveIndex]->setActive(false);
				QueryListItemOwner()->setIgnoreActivate(false);
				m_iActiveIndex = -1;
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setActiveIndex(const int value)
	{
		if (value < 0 && m_iActiveIndex < 0)
			return false;
		if (value != m_iActiveIndex && value < (int)m_aItems.size())
		{
			SortItems();
			if (m_iActiveIndex >= 0)
			{
				QueryListItemOwner()->setIgnoreActivate(true);
				m_aItems[m_iActiveIndex]->setActive(false);
				QueryListItemOwner()->setIgnoreActivate(false);
			}
			m_iActiveIndex = value >= 0 ? value : -1;
			if (m_iActiveIndex >= 0)
			{
				QueryListItemOwner()->setIgnoreActivate(true);
				m_aItems[m_iActiveIndex]->setActive(true);
				QueryListItemOwner()->setIgnoreActivate(false);
				if (m_bEditable && m_fGetItemText)
					getTextInput()->setText(m_fGetItemText(m_aItems[m_iActiveIndex]));
			}
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setCompareFunc(FCompare value)
	{
		if (value != m_fCompare)
		{
			m_fCompare = value;
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setGetItemTextFunc(FGetItemText value)
	{
		if (value != m_fGetItemText)
		{
			m_fGetItemText = value;
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setSearchFunc(FSearch value)
	{
		if (value != m_fSearch)
		{
			m_fSearch = value;
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setLoopActiveItemOnDoubleClick(const bool value)
	{
		if (value != m_bLoopActiveItemOnDoubleClick)
		{
			m_bLoopActiveItemOnDoubleClick = value;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Setters
	bool CBuiltInDropDown::setArrowAtRight(const bool value)
	{
		if (value != m_bArrowAtRight)
		{
			m_bArrowAtRight = value;
			UpdateInput();
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setOpenDirection(const OpenDirection value)
	{
		if (value != m_eOpenDirection)
		{
			m_eOpenDirection = value;
			if (m_bOpened)
			{
				UpdateList();
				UpdateHoveredItem();
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListWidth(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_fListWidth))
		{
			m_fListWidth = value;
			if (m_bOpened)
			{
				UpdateList();
				UpdateHoveredItem();
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListMaxHeight(const float value)
	{
		if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fListMaxHeight))
		{
			m_fListMaxHeight = value;
			if (m_bOpened)
			{
				UpdateList();
				UpdateHoveredItem();
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowArea(const ArrowArea value)
	{
		if (value != m_eArrowArea)
		{
			m_eArrowArea = value;
			UpdateInput();
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowAreaSize(const float value)
	{
		if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fArrowAreaSize))
		{
			m_fArrowAreaSize = value;
			UpdateInput();
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowSize(const float value)
	{
		if (value >= 0 && value <= 1 && ntl::IsNotEqual<float>(value, m_fArrowSize))
		{
			m_fArrowSize = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setBorderWidth(const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
		{
			m_sBorderWidth = value;
			UpdateInput();
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setBorderRadius(const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_sBorderRadius))
		{
			m_sBorderRadius = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setPadding(const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_sPadding))
		{
			m_sPadding = value;
			UpdateInput();
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowBorderWidth(const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_sArrowBorderWidth))
		{
			m_sArrowBorderWidth = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowBorderRadius(const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_sArrowBorderRadius))
		{
			m_sArrowBorderRadius = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListBorderWidth(const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_sListBorderWidth))
		{
			m_sListBorderWidth = value;
			if (m_bOpened)
			{
				UpdateList();
				UpdateHoveredItem();
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListBorderRadius(const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_sListBorderRadius))
		{
			m_sListBorderRadius = value;
			if (m_bOpened && m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListPadding(const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_sListPadding))
		{
			m_sListPadding = value;
			if (m_bOpened)
			{
				UpdateList();
				UpdateHoveredItem();
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setShadowColor(const State state, const Color &value)
	{
		if (value != m_aShadowColor[(int)state][0])
		{
			m_aShadowColor[(int)state][0] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setShadowColorEditable(const State state, const Color &value)
	{
		if (value != m_aShadowColor[(int)state][1])
		{
			m_aShadowColor[(int)state][1] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setShadowShift(const State state, const PointF &value)
	{
		if (IsNotEqual(value, m_aShadowShift[(int)state][0]))
		{
			m_aShadowShift[(int)state][0] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setShadowShiftEditable(const State state, const PointF &value)
	{
		if (IsNotEqual(value, m_aShadowShift[(int)state][1]))
		{
			m_aShadowShift[(int)state][1] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setShadowRadius(const State state, const int value)
	{
		if (value != m_aShadowRadius[(int)state][0])
		{
			m_aShadowRadius[(int)state][0] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setShadowRadiusEditable(const State state, const int value)
	{
		if (value != m_aShadowRadius[(int)state][1])
		{
			m_aShadowRadius[(int)state][1] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setBorderColor(const State state, const BorderColor &value)
	{
		if (value != m_aBorderColor[(int)state][0])
		{
			m_aBorderColor[(int)state][0] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setBorderColorEditable(const State state, const BorderColor &value)
	{
		if (value != m_aBorderColor[(int)state][1])
		{
			m_aBorderColor[(int)state][1] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setLeftBorderColor(const State state, const Color &value)
	{
		if (value != m_aBorderColor[(int)state][0].Left)
		{
			m_aBorderColor[(int)state][0].Left = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setLeftBorderColorEditable(const State state, const Color &value)
	{
		if (value != m_aBorderColor[(int)state][1].Left)
		{
			m_aBorderColor[(int)state][1].Left = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setTopBorderColor(const State state, const Color &value)
	{
		if (value != m_aBorderColor[(int)state][0].Top)
		{
			m_aBorderColor[(int)state][0].Top = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setTopBorderColorEditable(const State state, const Color &value)
	{
		if (value != m_aBorderColor[(int)state][1].Top)
		{
			m_aBorderColor[(int)state][1].Top = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setRightBorderColor(const State state, const Color &value)
	{
		if (value != m_aBorderColor[(int)state][0].Right)
		{
			m_aBorderColor[(int)state][0].Right = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setRightBorderColorEditable(const State state, const Color &value)
	{
		if (value != m_aBorderColor[(int)state][1].Right)
		{
			m_aBorderColor[(int)state][1].Right = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setBottomBorderColor(const State state, const Color &value)
	{
		if (value != m_aBorderColor[(int)state][0].Bottom)
		{
			m_aBorderColor[(int)state][0].Bottom = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setBottomBorderColorEditable(const State state, const Color &value)
	{
		if (value != m_aBorderColor[(int)state][1].Bottom)
		{
			m_aBorderColor[(int)state][1].Bottom = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setBackgroundColor(const State state, const Color &value)
	{
		if (value != m_aBackgroundColor[(int)state][0])
		{
			m_aBackgroundColor[(int)state][0] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setBackgroundColorEditable(const State state, const Color &value)
	{
		if (value != m_aBackgroundColor[(int)state][1])
		{
			m_aBackgroundColor[(int)state][1] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowBorderColor(const State state, const BorderColor &value)
	{
		if (value != m_aArrowBorderColor[(int)state][0])
		{
			m_aArrowBorderColor[(int)state][0] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowBorderColorEditable(const State state, const BorderColor &value)
	{
		if (value != m_aArrowBorderColor[(int)state][1])
		{
			m_aArrowBorderColor[(int)state][1] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowLeftBorderColor(const State state, const Color &value)
	{
		if (value != m_aArrowBorderColor[(int)state][0].Left)
		{
			m_aArrowBorderColor[(int)state][0].Left = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowLeftBorderColorEditable(const State state, const Color &value)
	{
		if (value != m_aArrowBorderColor[(int)state][1].Left)
		{
			m_aArrowBorderColor[(int)state][1].Left = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowTopBorderColor(const State state, const Color &value)
	{
		if (value != m_aArrowBorderColor[(int)state][0].Top)
		{
			m_aArrowBorderColor[(int)state][0].Top = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowTopBorderColorEditable(const State state, const Color &value)
	{
		if (value != m_aArrowBorderColor[(int)state][1].Top)
		{
			m_aArrowBorderColor[(int)state][1].Top = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowRightBorderColor(const State state, const Color &value)
	{
		if (value != m_aArrowBorderColor[(int)state][0].Right)
		{
			m_aArrowBorderColor[(int)state][0].Right = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowRightBorderColorEditable(const State state, const Color &value)
	{
		if (value != m_aArrowBorderColor[(int)state][1].Right)
		{
			m_aArrowBorderColor[(int)state][1].Right = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowBottomBorderColor(const State state, const Color &value)
	{
		if (value != m_aArrowBorderColor[(int)state][0].Bottom)
		{
			m_aArrowBorderColor[(int)state][0].Bottom = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowBottomBorderColorEditable(const State state, const Color &value)
	{
		if (value != m_aArrowBorderColor[(int)state][1].Bottom)
		{
			m_aArrowBorderColor[(int)state][1].Bottom = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowBackgroundColor(const State state, const Color &value)
	{
		if (value != m_aArrowBackgroundColor[(int)state][0])
		{
			m_aArrowBackgroundColor[(int)state][0] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowBackgroundColorEditable(const State state, const Color &value)
	{
		if (value != m_aArrowBackgroundColor[(int)state][1])
		{
			m_aArrowBackgroundColor[(int)state][1] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowColor(const State state, const Color &value)
	{
		if (value != m_aArrowColor[(int)state][0])
		{
			m_aArrowColor[(int)state][0] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setArrowColorEditable(const State state, const Color &value)
	{
		if (value != m_aArrowColor[(int)state][1])
		{
			m_aArrowColor[(int)state][1] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListBorderColor(const BorderColor &value)
	{
		if (value != m_aListBorderColor[0])
		{
			m_aListBorderColor[0] = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListBorderColorEditable(const BorderColor &value)
	{
		if (value != m_aListBorderColor[1])
		{
			m_aListBorderColor[1] = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListLeftBorderColor(const Color &value)
	{
		if (value != m_aListBorderColor[0].Left)
		{
			m_aListBorderColor[0].Left = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListLeftBorderColorEditable(const Color &value)
	{
		if (value != m_aListBorderColor[1].Left)
		{
			m_aListBorderColor[1].Left = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListTopBorderColor(const Color &value)
	{
		if (value != m_aListBorderColor[0].Top)
		{
			m_aListBorderColor[0].Top = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListTopBorderColorEditable(const Color &value)
	{
		if (value != m_aListBorderColor[1].Top)
		{
			m_aListBorderColor[1].Top = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListRightBorderColor(const Color &value)
	{
		if (value != m_aListBorderColor[0].Right)
		{
			m_aListBorderColor[0].Right = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListRightBorderColorEditable(const Color &value)
	{
		if (value != m_aListBorderColor[1].Right)
		{
			m_aListBorderColor[1].Right = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListBottomBorderColor(const Color &value)
	{
		if (value != m_aListBorderColor[0].Bottom)
		{
			m_aListBorderColor[0].Bottom = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListBottomBorderColorEditable(const Color &value)
	{
		if (value != m_aListBorderColor[1].Bottom)
		{
			m_aListBorderColor[1].Bottom = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListBackgroundColor(const Color &value)
	{
		if (value != m_aListBackgroundColor[0])
		{
			m_aListBackgroundColor[0] = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListBackgroundColorEditable(const Color &value)
	{
		if (value != m_aListBackgroundColor[1])
		{
			m_aListBackgroundColor[1] = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListShadowColor(const Color &value)
	{
		if (value != m_aListShadowColor[0])
		{
			m_aListShadowColor[0] = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListShadowColorEditable(const Color &value)
	{
		if (value != m_aListShadowColor[1])
		{
			m_aListShadowColor[1] = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListShadowShift(const PointF &value)
	{
		if (IsNotEqual(value, m_aListShadowShift[0]))
		{
			m_aListShadowShift[0] = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListShadowShiftEditable(const PointF &value)
	{
		if (IsNotEqual(value, m_aListShadowShift[1]))
		{
			m_aListShadowShift[1] = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListShadowRadius(const int value)
	{
		if (value != m_aListShadowRadius[0])
		{
			m_aListShadowRadius[0] = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setListShadowRadiusEditable(const int value)
	{
		if (value != m_aListShadowRadius[1])
		{
			m_aListShadowRadius[1] = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::setSearchResetInterval(const float value)
	{
		if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fSearchResetInterval))
		{
			m_fSearchResetInterval = value;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region IBuiltInControl methods
	void CBuiltInDropDown::Refresh()
	{
		if (m_pCanvasControl)
			m_pCanvasControl->setValid(false);
		if (m_pCanvasList)
			m_pCanvasList->setValid(false);
		if (getScroll())
			getScroll()->Refresh();
		if (getTextInput())
			getTextInput()->Refresh();
	}
#pragma endregion

#pragma region Items
	bool CBuiltInDropDown::AddItem(IListItem *item)
	{
		return InsertItem(item, (int)m_aItems.size());
	}

	bool CBuiltInDropDown::InsertItem(IListItem *item, const int before)
	{
		if (item && !item->getParent() && !item->QueryService()->getOwner())
		{
			SortItems();
			item->setActive(false);
			item->setSelected(false);
			item->QueryService()->setHovered(false);
			item->QueryService()->setOwner(QueryListItemOwner());
			if (before <= 0)
				m_aItems.insert(m_aItems.begin(), item);
			else if (before >= (int)m_aItems.size())
				m_aItems.push_back(item);
			else
				m_aItems.insert(m_aItems.begin() + before, item);
			m_bSorted = false;
			if (m_bOpened)
			{
				UpdateList();
				UpdateHoveredItem();
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::DeleteItem(const int index)
	{
		if (index >= 0 && index < (int)m_aItems.size())
		{
			SortItems();
			m_aItems[index]->Release();
			m_aItems.erase(m_aItems.begin() + index);
			if (index < m_iActiveIndex)
				m_iActiveIndex--;
			else if (index == m_iActiveIndex)
			{
				m_iActiveIndex = -1;
				if (m_pCanvasControl)
					m_pCanvasControl->setValid(false);
			}
			if (m_bOpened)
			{
				UpdateList();
				UpdateHoveredItem();
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::DeleteItem(IListItem *item)
	{
		if (item)
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				if ((*pos) == item)
					return DeleteItem(int(pos - m_aItems.begin()));
		return false;
	}

	bool CBuiltInDropDown::DeleteItems()
	{
		if (m_aItems.size() > 0)
		{
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				(*pos)->Release();
			m_aItems.clear();
			m_iActiveIndex = -1;
			if (m_bOpened)
			{
				UpdateList();
				UpdateHoveredItem();
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			m_bSorted = true;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::MoveItem(IListItem *item, const int before)
	{
		if (MoveListItem(m_aItems, cast<IComponentItemList*>(getControl()), item, before))
		{
			m_bSorted = false;
			m_bSortable = false;
			if (m_iActiveIndex >= 0)
			{
				if (m_pCanvasControl)
					m_pCanvasControl->setValid(false);
				if (m_bOpened && m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region IBuiltInControl helpers
	void CBuiltInDropDown::UpdateFromStyle(IStyle *style, const String &class_name)
	{
		m_bIgnoreGradient = true;
		style->getOption(class_name + L".ArrowAtRight", m_bArrowAtRight);
		style->getOption(class_name + L".ArrowSize", m_fArrowSize);
		style->getOption(class_name + L".BorderWidth", m_sBorderWidth);
		style->getOption(class_name + L".BorderRadius", m_sBorderRadius);
		style->getOption(class_name + L".Padding", m_sPadding);
		style->getOption(class_name + L".ArrowBorderWidth", m_sArrowBorderWidth);
		style->getOption(class_name + L".ArrowBorderRadius", m_sArrowBorderRadius);
		style->getOption(class_name + L".ListBorderWidth", m_sListBorderWidth);
		style->getOption(class_name + L".ListBorderRadius", m_sListBorderRadius);
		style->getOption(class_name + L".ListPadding", m_sListPadding);
		for (int i = 0; i <= (int)State::Disabled; i++)
		{
			String state;
			switch ((State)i)
			{
			case State::Hovered:
				state = L"Hovered";
				break;
			case State::Focused:
				state = L"Focused";
				break;
			case State::FocusedHovered:
				state = L"FocusedHovered";
				break;
			case State::Disabled:
				state = L"Disabled";
				break;
			default:
				state = L"Normal";
			}
			for (int k = 0; k <= 1; k++)
			{
				if (k == 1)
					state += L".Editable";
				style->getOption(class_name + L".ShadowColor[" + state + L"]", m_aShadowColor[i][k]);
				style->getOption(class_name + L".ShadowShift[" + state + L"]", m_aShadowShift[i][k]);
				style->getOption(class_name + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i][k]);
				style->getOption(class_name + L".BorderColor[" + state + L"]", m_aBorderColor[i][k]);
				style->getOption(class_name + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i][k]);
				style->getOption(class_name + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i][k]);

				style->getOption(class_name + L".ArrowBorderColor[" + state + L"]", m_aArrowBorderColor[i][k]);
				style->getOption(class_name + L".ArrowBackgroundColor[" + state + L"]", m_aArrowBackgroundColor[i][k]);
				style->getOption(class_name + L".ArrowBackgroundGradient[" + state + L"]", m_aArrowBackgroundGradient[i][k]);
				style->getOption(class_name + L".ArrowColor[" + state + L"]", m_aArrowColor[i][k]);
			}
		}
		for (int k = 0; k <= 1; k++)
		{
			String state = k == 1 ? L".Editable" : L"";
			style->getOption(class_name + L".ListBorderColor" + state, m_aListBorderColor[k]);
			style->getOption(class_name + L".ListBackgroundColor" + state, m_aListBackgroundColor[k]);
			style->getOption(class_name + L".ListBackgroundGradient" + state, m_aListBackgroundGradient[k]);
			style->getOption(class_name + L".ListShadowColor" + state, m_aListShadowColor[k]);
			style->getOption(class_name + L".ListShadowShift" + state, m_aListShadowShift[k]);
			style->getOption(class_name + L".ListShadowRadius" + state, m_aListShadowRadius[k]);
		}
		if (m_bEditable || m_pTextInput)
			getTextInput()->UpdateFromStyle(style, class_name + L".TextInput");
		getScroll()->UpdateFromStyle(style, class_name + L".Scroll");
		for (auto item : m_aItems)
			item->QueryService()->UpdateFromStyle();
		UpdateInput();
		if (m_bOpened)
		{
			UpdateList();
			UpdateHoveredItem();
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
		}
		if (m_pCanvasControl)
			m_pCanvasControl->setValid(false);
		m_bIgnoreGradient = false;
	}

	void CBuiltInDropDown::Update()
	{
		UpdateInput();
		if (m_bEditable)
			getTextInput()->Update();
		if (m_bOpened)
		{
			UpdateList();
			UpdateHoveredItem();
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
		}
		if (m_pCanvasControl)
			m_pCanvasControl->setValid(false);
	}
#pragma endregion

#pragma region IBuiltInDropDown helpers
	bool CBuiltInDropDown::Open()
	{
		if (!m_bOpened && isEnabled() && getControl() && getControl()->getForm())
		{
			m_bOpened = true;
			getControl()->getForm()->setActiveControl(getControl());
			UpdateList();
			UpdateHoveredItem();
			ScrollToActiveItem();
			if (m_pListener && cast<IBuiltInDropDownListener*>(m_pListener))
				cast<IBuiltInDropDownListener*>(m_pListener)->NotifyOnOpen(this);
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInDropDown::Close()
	{
		if (m_bOpened)
		{
			m_eDownElement = ElementType::None;
			m_bOpened = false;
			if (m_pTextInput)
				m_pTextInput->NotifyOnMouseDownCancel();
			if (m_pScroll)
				m_pScroll->NotifyOnMouseDownCancel();
			if (getControl() && getControl()->isActive())
				getControl()->getForm()->setActiveControl(nullptr);
			if (m_pListener && cast<IBuiltInDropDownListener*>(m_pListener))
				cast<IBuiltInDropDownListener*>(m_pListener)->NotifyOnClose(this);
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	IListItemOwner *CBuiltInDropDown::QueryListItemOwner()
	{
		if (!m_pListItemOwner)
			m_pListItemOwner = new CBuiltInDropDownListItemOwner(this);
		return m_pListItemOwner;
	}
#pragma endregion

#pragma region Helpers
	IBuiltInTextInput *CBuiltInDropDown::getTextInput()
	{
		if (!m_pTextInput)
		{
			m_pTextInput = new CTextInput(this);
			m_pTextInput->setListener(&m_cTextInputListener);
			m_pTextInput->setEnabled(isEnabled());
			m_pTextInput->setFocused(isFocused());
			UpdateInput();
		}
		return m_pTextInput;
	}

	IBuiltInScroll *CBuiltInDropDown::getScroll()
	{
		if (!m_pScroll)
		{
			CScroll *scroll{ new CScroll(this) };
			scroll->setListener(&m_cScrollListener);
			if (!scroll->isVertical())
				scroll->SwitchDirection(true);
			m_pScroll = scroll;
			if (m_bOpened)
				UpdateList();
		}
		return m_pScroll;
	}

	RectF CBuiltInDropDown::getRenderRect(const State state)
	{
		RectF result{ getControlRenderRect(state) };
		if (m_bOpened)
			result += getListRenderRect();
		return result;
	}

	RectF CBuiltInDropDown::getListRenderRect()
	{
		return AddShadow(m_sListRect, m_aListShadowColor[m_bEditable], m_aListShadowShift[m_bEditable], m_aListShadowRadius[m_bEditable]);
	}

	RectF CBuiltInDropDown::getControlRenderRect(const State state)
	{
		return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state][m_bEditable], m_aShadowShift[(int)state][m_bEditable], m_aShadowRadius[(int)state][m_bEditable]);
	}

	RectF CBuiltInDropDown::getControlRenderRect()
	{
		RectF result{ getControlRenderRect(State::Normal) };
		for (int i = 1; i <= (int)State::Disabled; i++)
			result += getControlRenderRect((State)i);
		return result;
	}

	RectF CBuiltInDropDown::getArrowAreaRect()
	{
		RectF result{ 0, 0, getWidth(), getHeight() };
		if (m_bArrowAtRight)
			switch (m_eArrowArea)
			{
			case ArrowArea::Height:
				result.Left = getWidth() - getHeight();
				break;
			case ArrowArea::WidthPart:
				result.Left = getWidth() * (1 - m_fArrowAreaSize);
				break;
			default:
				result.Left = getWidth() - m_fArrowAreaSize;
			}
		else
			switch (m_eArrowArea)
			{
			case ArrowArea::Height:
				result.Right = getHeight();
				break;
			case ArrowArea::WidthPart:
				result.Right = getWidth();
				break;
			default:
				result.Right = m_fArrowAreaSize;
			}
		result.validate();
		return result;
	}

	IListItem *CBuiltInDropDown::getItem(const PointF &position)
	{
		SortItems();
		RectF client{
			m_sListRect.Left + m_sListBorderWidth.Left + m_sListPadding.Left,
			m_sListRect.Top + m_sListBorderWidth.Top + m_sListPadding.Top,
			m_sListRect.Right - m_sListBorderWidth.Right - m_sListPadding.Right,
			m_sListRect.Bottom - m_sListBorderWidth.Bottom - m_sListPadding.Bottom
		};
		if (ntl::IsGreater<float>(m_fListScrollMax, 0))
			client.Right = m_sListRect.Right - getScroll()->getSize().X;
		if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
			for (auto item : m_aItems)
				if (position.X >= item->getPosition().X && position.X < item->getPosition().X + item->getSize().X &&
					position.Y >= item->getPosition().Y - m_fListScroll && position.Y < item->getPosition().Y - m_fListScroll + item->getSize().Y)
					return item;
		return nullptr;
	}

	bool CBuiltInDropDown::isListHovered(const PointF &position)
	{
		return position.X >= m_sListRect.Left && position.X < m_sListRect.Right && position.Y >= m_sListRect.Top && position.Y < m_sListRect.Bottom;
	}

	bool CBuiltInDropDown::ScrollToActiveItem()
	{
		if (m_bOpened && ntl::IsGreater<float>(m_fListScrollMax, 0) && m_iActiveIndex >= 0)
		{
			if (ntl::IsLess<float>(m_aItems[m_iActiveIndex]->getPosition().Y - m_fListScroll, m_sListRect.Top + m_sListBorderWidth.Top + m_sListPadding.Top))
			{
				m_fListScroll -= m_sListRect.Top + m_sListBorderWidth.Top + m_sListPadding.Top - m_aItems[m_iActiveIndex]->getPosition().Y + m_fListScroll;
				getScroll()->setScroll(m_fListScroll);
				return true;
			}
			if (ntl::IsGreater<float>(m_aItems[m_iActiveIndex]->getPosition().Y - m_fListScroll + m_aItems[m_iActiveIndex]->getSize().Y, m_sListRect.Bottom - m_sListBorderWidth.Bottom - m_sListPadding.Bottom))
			{
				m_fListScroll += m_aItems[m_iActiveIndex]->getPosition().Y - m_fListScroll + m_aItems[m_iActiveIndex]->getSize().Y - m_sListRect.Bottom + m_sListBorderWidth.Bottom + m_sListPadding.Bottom;
				getScroll()->setScroll(m_fListScroll);
				return true;
			}
		}
		return false;
	}

	void CBuiltInDropDown::UpdateList()
	{
		SortItems();
		float required_height{ 0 };
		for (auto item : m_aItems)
			required_height += item->QueryService()->getRequiredSize().Y;
		float inner_height{ required_height }, inner_width{ ntl::Max<float>(10.0f, ntl::IsGreater<float>(m_fListWidth, 0) ? m_fListWidth : getWidth() - m_sListBorderWidth.Left - m_sListPadding.Left - m_sListBorderWidth.Right - m_sListPadding.Right) };
		float outer_width{ inner_width + m_sBorderWidth.Left + m_sPadding.Left + m_sBorderWidth.Right + m_sPadding.Right };
		if (ntl::IsGreater<float>(m_fListMaxHeight, 0) && ntl::IsGreater<float>(required_height + m_sListBorderWidth.Top + m_sListPadding.Top + m_sListBorderWidth.Bottom + m_sListPadding.Bottom, m_fListMaxHeight))
		{
			// Scroll required(inner size cannot be less that 10x10 pixels)
			inner_height = ntl::Max<float>(10.0f, m_fListMaxHeight - m_sListBorderWidth.Top - m_sListPadding.Top - m_sListBorderWidth.Bottom - m_sListPadding.Bottom);
			m_fListScrollMax = required_height - inner_height;
			m_fListScroll = ntl::Min<float>(m_fListScroll, m_fListScrollMax);
			inner_width = ntl::Max<float>(10.0f, outer_width - m_sListBorderWidth.Left - m_sListPadding.Left - m_sListBorderWidth.Right - m_sListPadding.Right);
			outer_width = inner_width + m_sBorderWidth.Left + m_sPadding.Left + m_sBorderWidth.Right + m_sPadding.Right;
		}
		else
		{
			// Scroll is not required
			m_fListScrollMax = 0;
			m_fListScroll = 0;
		}
		float outer_height{ inner_height + m_sListBorderWidth.Top + m_sListPadding.Top + m_sListBorderWidth.Bottom + m_sListPadding.Bottom };
		switch (m_eOpenDirection)
		{
		case OpenDirection::Up:
			m_sListRect = RectF{ getWidth() - outer_width, -outer_height, getWidth(), 0 };
			break;
		case OpenDirection::Auto:
			m_sListRect = RectF{ getWidth() - outer_width, getHeight(), getWidth(), getHeight() + outer_height };
			if (getControl() && getControl()->getForm())
			{
				Vec4f v1{ getControl()->getTransformMatrix() * Vec4f{ m_sListRect.Left, m_sListRect.Top, 0, 1 } };
				Vec4f v2{ getControl()->getTransformMatrix() * Vec4f{ m_sListRect.Right, m_sListRect.Top, 0, 1 } };
				Vec4f v3{ getControl()->getTransformMatrix() * Vec4f{ m_sListRect.Right, m_sListRect.Bottom, 0, 1 } };
				Vec4f v4{ getControl()->getTransformMatrix() * Vec4f{ m_sListRect.Left, m_sListRect.Bottom, 0, 1 } };
				float y{ ntl::Max<float>(v1.Y, v2.Y, v3.Y, v4.Y) };
				if (y >= (float)getControl()->getForm()->getClientHeight())
					m_sListRect = RectF{ getWidth() - outer_width, -outer_height, getWidth(), 0 };
			}
			break;
		default:
			m_sListRect = RectF{ getWidth() - outer_width, getHeight(), getWidth(), getHeight() + outer_height };
		}
		if (ntl::IsGreater<float>(m_fListScrollMax, 0))
		{
			getScroll()->setSize(PointF{ getScroll()->getSize().X, inner_height + m_sListPadding.Top + m_sListPadding.Bottom });
			getScroll()->setMax(m_fListScrollMax);
			getScroll()->setPosition(PointF{ m_sListRect.Right - m_sListBorderWidth.Right - getScroll()->getWidth(), m_sListRect.Top + m_sListBorderWidth.Top });
		}
		float y{ m_sListRect.Top + m_sListBorderWidth.Top + m_sListPadding.Top };
		for (auto item : m_aItems)
		{
			float h{ item->QueryService()->getRequiredSize().Y };
			item->QueryService()->setSize(PointF{ inner_width - (ntl::IsGreater<float>(m_fListScrollMax, 0) ? (getScroll()->getSize().X - m_sListPadding.Right) : 0), h });
			item->QueryService()->setPosition(PointF{ m_sListRect.Left + m_sListBorderWidth.Left + m_sListPadding.Left, y });
			y += h;
		}
	}

	void CBuiltInDropDown::UpdateInput()
	{
		if (m_bEditable)
		{
			RectF client{ getClientRect() };
			getTextInput()->setSize(PointF{ client.width(), client.height() });
			getTextInput()->setPosition(client.LeftTop);
		}
	}

	void CBuiltInDropDown::SortItems()
	{
		if (m_bSortable && !m_bSorted && m_fCompare && m_aItems.size() > 1)
		{
			IListItem *active{ m_iActiveIndex >= 0 ? m_aItems[m_iActiveIndex] : nullptr };
			std::sort(m_aItems.begin(), m_aItems.end(), m_fCompare);
			if (active)
				m_iActiveIndex = int(std::find(m_aItems.begin(), m_aItems.end(), active) - m_aItems.begin());
			m_bSorted = true;
		}
	}
#pragma endregion

#pragma region Paint
	void CBuiltInDropDown::Render(const bool last_pass, const Mat4f &matrix, const Block *block)
	{
		if (getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
		{
			if (last_pass)
				RenderList(getControl()->getForm()->getRenderer(), matrix);
			else
				RenderControl(getControl()->getForm()->getRenderer(), matrix, block);
		}
	}

	void CBuiltInDropDown::RenderControl(IRenderer *renderer, const Mat4f &matrix, const Block *block)
	{
		State state{ getState() };
		PointF disp{ DispOnCanvas(m_aShadowColor[(int)state][m_bEditable], m_aShadowShift[(int)state][m_bEditable], m_aShadowRadius[(int)state][m_bEditable]) };
		RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state][m_bEditable], m_aShadowShift[(int)state][m_bEditable], m_aShadowRadius[(int)state][m_bEditable]) };
		if (PrepareCanvas(renderer, &m_pCanvasControl, all_rect))
		{
			CStoreTarget s_target{ renderer };
			renderer->ActivateTarget(m_pCanvasControl);
			renderer->Clear(Color{ 0, 0, 0, 0 });

			SortItems();
			RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
			DrawBlockShadow(renderer, rect, m_sBorderRadius, m_aShadowColor[(int)state][m_bEditable], m_aShadowShift[(int)state][m_bEditable], m_aShadowRadius[(int)state][m_bEditable]);
			DrawSimpleBackground(renderer, rect, m_sBorderWidth, m_sBorderRadius, m_aBorderColor[(int)state][m_bEditable], m_aBackgroundColor[(int)state][m_bEditable],
				m_aBackgroundGradient[(int)state][m_bEditable]);
			RenderControlArrowToCanvas(renderer, state, disp);
			RenderControlActiveItemToCanvas(renderer, state, rect);
			RenderControlInputToCanvas(renderer, state, rect);

			m_pCanvasControl->setValid(true);
		}
		if (m_pCanvasControl)
		{
			CStoreBlock s_block{ renderer };
			CStorePrimitiveMatrix s_matrix{ renderer };
			renderer
				->ActivateBlock(block)
				->ActivatePrimitiveMatrix(matrix * ntl::Mat4Translate<float>(-disp.X, -disp.Y, 0))
				->DrawImage(m_pCanvasControl, 1);
		}
	}

	void CBuiltInDropDown::RenderControlArrowToCanvas(IRenderer *renderer, const State state, const PointF &disp)
	{
		RectF area_rect{ getArrowAreaRect() };
		area_rect += disp;
		if (!area_rect.is_zero())
		{
			Block b{ area_rect, m_sArrowBorderWidth, m_sArrowBorderRadius, PointLocation::Inside };
			DrawSimpleBackground(renderer, area_rect, m_sArrowBorderWidth, m_sArrowBorderRadius, m_aArrowBorderColor[(int)state][m_bEditable], m_aArrowBackgroundColor[(int)state][m_bEditable],
				m_aArrowBackgroundGradient[(int)state][m_bEditable]);
			float w{ ntl::Min<float>(area_rect.width(), area_rect.height()) * m_fArrowSize };
			PointF center{ (area_rect.Left + area_rect.Right) * 0.5f, (area_rect.Top + area_rect.Bottom) * 0.5f };
			if (ntl::IsGreater<float>(w, 0))
			{
				if (m_sArrowBorderRadius.has_positive() || m_sArrowBorderWidth.has_positive())
				{
					CStoreBlock s_block{ renderer };
					renderer
						->ActivateBlock(&b)
						->DrawTriangle(PointF{ center.X, center.Y + w * 0.25f }, PointF{ center.X - w * 0.5f, center.Y - w * 0.25f }, PointF{ center.X + w * 0.5f, center.Y - w * 0.25f },
							m_aArrowColor[(int)state][m_bEditable]);
				}
				else
				{
					renderer->DrawTriangle(PointF{ center.X, center.Y + w * 0.25f }, PointF{ center.X - w * 0.5f, center.Y - w * 0.25f }, PointF{ center.X + w * 0.5f, center.Y - w * 0.25f },
						m_aArrowColor[(int)state][m_bEditable]);
				}
			}
		}
	}

	void CBuiltInDropDown::RenderControlActiveItemToCanvas(IRenderer *renderer, const State state, const RectF &rect)
	{
		if (!m_bEditable && m_iActiveIndex >= 0)
		{
			Block b{ rect, AddElements(m_sBorderWidth, m_sPadding), m_sBorderRadius, PointLocation::Inside };

			// Prepare
			RectF client{ rect };
			client.Left += m_sBorderWidth.Left + m_sPadding.Left;
			client.Top += m_sBorderWidth.Top + m_sPadding.Top;
			client.Right -= m_sBorderWidth.Right + m_sPadding.Right;
			client.Bottom -= m_sBorderWidth.Bottom + m_sPadding.Bottom;
			client.validate();

			bool hovered{ m_aItems[m_iActiveIndex]->isHovered() }, selected{ m_aItems[m_iActiveIndex]->isSelected() }, active{ m_aItems[m_iActiveIndex]->isActive() },
				enabled{ m_aItems[m_iActiveIndex]->isEnabled() };
			PointF size{ m_aItems[m_iActiveIndex]->getSize() };
			QueryListItemOwner()->setIgnoreActivate(true);
			QueryListItemOwner()->setIgnoreDeactivate(true);
			QueryListItemOwner()->setIgnoreEnable(true);
			QueryListItemOwner()->setIgnoreDisable(true);
			QueryListItemOwner()->setIgnoreSizeChange(true);
			m_aItems[m_iActiveIndex]->QueryService()->setHovered(false);
			m_aItems[m_iActiveIndex]->setSelected(false);
			m_aItems[m_iActiveIndex]->setActive(false);
			m_aItems[m_iActiveIndex]->setEnabled(isEnabled());
			m_aItems[m_iActiveIndex]->setVisible(true);
			m_aItems[m_iActiveIndex]->QueryService()->setSize(PointF{ client.width(), client.height() });

			// Draw
			m_aItems[m_iActiveIndex]->QueryService()->Render(ntl::Mat4Translate<float>(client.Left, client.Top, 0), &b, false, nullptr);
			// Rollback preparation
			m_aItems[m_iActiveIndex]->QueryService()->setHovered(hovered);
			m_aItems[m_iActiveIndex]->setSelected(selected);
			m_aItems[m_iActiveIndex]->setActive(active);
			m_aItems[m_iActiveIndex]->setEnabled(enabled);
			m_aItems[m_iActiveIndex]->QueryService()->setSize(size);
			QueryListItemOwner()->setIgnoreActivate(false);
			QueryListItemOwner()->setIgnoreDeactivate(false);
			QueryListItemOwner()->setIgnoreEnable(false);
			QueryListItemOwner()->setIgnoreDisable(false);
			QueryListItemOwner()->setIgnoreSizeChange(false);
		}
	}

	void CBuiltInDropDown::RenderControlInputToCanvas(IRenderer *renderer, const State state, const RectF &rect)
	{
		if (m_bEditable)
		{
			Block b{ rect, AddElements(m_sBorderWidth, m_sPadding), m_sBorderRadius, PointLocation::Inside };
			getTextInput()->Render(false, ntl::Mat4Translate<float>(rect.Left + m_sBorderWidth.Left + m_sPadding.Left, rect.Top + m_sBorderWidth.Top + m_sPadding.Top, 0), &b);
		}
	}

	void CBuiltInDropDown::RenderList(IRenderer *renderer, const Mat4f &matrix)
	{
		if (m_bOpened)
		{
			PointF disp{ DispOnCanvas(m_aListShadowColor[m_bEditable], m_aListShadowShift[m_bEditable], m_aListShadowRadius[m_bEditable]) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, m_sListRect.width(), m_sListRect.height() }, m_aListShadowColor[m_bEditable], m_aListShadowShift[m_bEditable], m_aListShadowRadius[m_bEditable]) };
			if (PrepareCanvas(renderer, &m_pCanvasList, all_rect))
			{
				SortItems();
				RectF rect{ disp.X, disp.Y, disp.X + m_sListRect.width(), disp.Y + m_sListRect.height() };
				CStoreTarget s_target{ renderer };
				renderer->ActivateTarget(m_pCanvasList);
				renderer->Clear(Color{ 0, 0, 0, 0 });

				DrawBlockShadow(renderer, rect, m_sListBorderRadius, m_aListShadowColor[m_bEditable], m_aListShadowShift[m_bEditable], m_aListShadowRadius[m_bEditable]);
				DrawSimpleBackground(renderer, rect, m_sListBorderWidth, m_sListBorderRadius, m_aListBorderColor[m_bEditable], m_aListBackgroundColor[m_bEditable],
					m_aListBackgroundGradient[m_bEditable]);
				RenderListItems(renderer, rect);
				RenderListScroll(renderer, rect);

				m_pCanvasList->setValid(true);
			}
			if (m_pCanvasList)
			{
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(matrix * ntl::Mat4Translate<float>(-disp.X, -disp.Y, 0) * ntl::Mat4Translate<float>(m_sListRect.Left, m_sListRect.Top, 0))
					->DrawImage(m_pCanvasList, 1);
			}
		}
	}

	void CBuiltInDropDown::RenderListItems(IRenderer *renderer, const RectF &rect)
	{
		Block b{ rect, AddElements(m_sListBorderWidth, m_sListPadding), m_sListBorderRadius, PointLocation::Inside };
		Block *pb{ (b.Radius.has_positive() || b.Border.has_positive()) ? &b : nullptr };
		float x{ rect.Left + m_sListBorderWidth.Left + m_sListPadding.Left }, y{ rect.Top - m_fListScroll + m_sListBorderWidth.Top + m_sListPadding.Top };
		ITexture *clip{ nullptr };
		for (auto pos : m_aItems)
		{
			if (y >= m_sListRect.height() - m_sListBorderWidth.Bottom - m_sListPadding.Bottom)
				break;
			if (y + pos->getSize().Y >= m_sListBorderWidth.Top + m_sListPadding.Top)
				pos->QueryService()->Render(ntl::Mat4Translate<float>(std::round(x), std::round(y), 0), pb, true, &clip);
			y += pos->getSize().Y;
		}
		if (clip)
			clip->Release();
	}

	void CBuiltInDropDown::RenderListScroll(IRenderer *renderer, const RectF &rect)
	{
		if (ntl::IsGreater<float>(m_fListScrollMax, 0))
		{
			Block b{ rect, m_sListBorderWidth, m_sListBorderRadius, PointLocation::Inside };
			Block *pb{ (b.Radius.has_positive() || b.Border.has_positive()) ? &b : nullptr };
			getScroll()->Render(true, ntl::Mat4Translate<float>(rect.Left + m_sListRect.width() - m_sListBorderWidth.Right - getScroll()->getSize().X, rect.Top + m_sListBorderWidth.Top, 0), pb);
		}
	}
#pragma endregion
}