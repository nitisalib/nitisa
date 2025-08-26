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
	CBuiltInSelect::CGradientListener::CGradientListener(CBuiltInSelect *control) :
		m_pControl{ control }
	{

	}

	void CBuiltInSelect::CGradientListener::NotifyOnChange()
	{
		if (m_pControl->m_pCanvasControl)
			m_pControl->m_pCanvasControl->setValid(false);
		if (m_pControl->m_pCanvasList)
			m_pControl->m_pCanvasList->setValid(false);
		if (!m_pControl->m_bIgnoreGradient && m_pControl->m_pListener)
			m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getRenderRect());
	}
#pragma endregion

#pragma region CTextInput
	CBuiltInSelect::CTextInput::CTextInput(CBuiltInSelect *control) :
		CBuiltInTextInput(),
		m_pControl{ control }
	{

	}

	IControl *CBuiltInSelect::CTextInput::getControl()
	{
		return m_pControl->getControl();
	}

	CBuiltInTextInput::State CBuiltInSelect::CTextInput::getState()
	{
		switch (m_pControl->getState())
		{
		case CBuiltInSelect::State::Normal:			return CBuiltInTextInput::State::Normal;
		case CBuiltInSelect::State::Hovered:		return CBuiltInTextInput::State::Hovered;
		case CBuiltInSelect::State::Focused:		return CBuiltInTextInput::State::Focused;
		case CBuiltInSelect::State::FocusedHovered:	return CBuiltInTextInput::State::FocusedHovered;
		default:									return CBuiltInTextInput::State::Disabled;
		}
	}
#pragma endregion

#pragma region CTextInputListener
	CBuiltInSelect::CTextInputListener::CTextInputListener(CBuiltInSelect *control) :
		m_pControl{ control }
	{

	}

	void CBuiltInSelect::CTextInputListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
	{
		if (m_pControl->m_pListener)
		{
			if (m_pControl->m_pCanvasControl)
				m_pControl->m_pCanvasControl->setValid(false);
			m_pControl->m_pListener->NotifyOnRepaint(m_pControl, rect);
		}
	}

	void CBuiltInSelect::CTextInputListener::NotifyOnTextChanged(IBuiltInControl *sender)
	{
		m_pControl->UpdateList();
		m_pControl->UpdateHoveredItem();
		if (m_pControl->m_pSelectListener)
			m_pControl->m_pSelectListener->NotifyOnFilterChange(m_pControl);
	}
#pragma endregion

#pragma region CScroll
	CBuiltInSelect::CScroll::CScroll(CBuiltInSelect *control) :
		CBuiltInScrollLite(),
		m_pControl{ control }
	{

	}

	IControl *CBuiltInSelect::CScroll::getControl()
	{
		return m_pControl->getControl();
	}
#pragma endregion

#pragma region CScrollListener
	CBuiltInSelect::CScrollListener::CScrollListener(CBuiltInSelect *control) :
		m_pControl{ control }
	{

	}

	void CBuiltInSelect::CScrollListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
	{
		if (m_pControl->m_pListener)
		{
			if (m_pControl->m_pCanvasList)
				m_pControl->m_pCanvasList->setValid(false);
			m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getListRenderRect());
		}
	}

	void CBuiltInSelect::CScrollListener::NotifyOnScroll(IBuiltInControl *sender)
	{
		if (m_pControl->m_pListener)
		{
			m_pControl->m_fListScroll = m_pControl->getScroll()->getScroll();
			m_pControl->UpdateHoveredItem();
			if (m_pControl->m_pCanvasList)
				m_pControl->m_pCanvasList->setValid(false);
			m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getListRenderRect());
		}
	}
#pragma endregion

#pragma region COwner
	CBuiltInSelect::COwner::COwner(CBuiltInSelect *control) :
		CListItemOwner(),
		m_pControl{ control }
	{

	}

	IControl *CBuiltInSelect::COwner::getControl()
	{
		return m_pControl->getControl();
	}

	IRenderer *CBuiltInSelect::COwner::getRenderer()
	{
		if (m_pControl->getControl() && m_pControl->getControl()->getForm())
			return m_pControl->getControl()->getForm()->getRenderer();
		return nullptr;
	}

	IFont *CBuiltInSelect::COwner::getFont(IListItem *item)
	{
		IFont *result{ item->getFont() };
		if (!result && m_pControl->getControl())
			result = m_pControl->getControl()->getFont();
		return result;
	}

	IStyle *CBuiltInSelect::COwner::getStyle(IListItem *item)
	{
		if (m_pControl->getControl())
			return m_pControl->getControl()->getStyle();
		return nullptr;
	}

	void CBuiltInSelect::COwner::NotifyOnSizeChange(IListItem *item)
	{
		if (!isIgnoreSizeChange() && m_pControl->m_bOpened && !item->getParent())
		{
			RectF r{ m_pControl->getListRenderRect() };
			m_pControl->UpdateList();
			m_pControl->UpdateHoveredItem();
			if (m_pControl->m_pListener)
			{
				if (m_pControl->m_pCanvasList)
					m_pControl->m_pCanvasList->setValid(false);
				m_pControl->m_pListener->NotifyOnRepaint(m_pControl, r + m_pControl->getListRenderRect());
			}
		}
	}

	void CBuiltInSelect::COwner::NotifyOnRepaintRequired(IListItem *item)
	{
		if (m_pControl->m_bOpened && !item->getParent() && m_pControl->m_pListener)
		{
			if (m_pControl->m_pCanvasList)
				m_pControl->m_pCanvasList->setValid(false);
			m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getListRenderRect());
		}
	}

	void CBuiltInSelect::COwner::NotifyOnBeforeAddItem(IListItem *item, IListItem *parent)
	{
		// Nothing. Children are not supported
	}

	void CBuiltInSelect::COwner::NotifyOnAddItem(IListItem *item)
	{
		// Nothing. Children are not supported
	}

	void CBuiltInSelect::COwner::NotifyOnBeforeDeleteItem(IListItem *item)
	{
		// Nothing. Children are not supported
	}

	void CBuiltInSelect::COwner::NotifyOnDeleteItem(IListItem *item, IListItem *parent)
	{
		// Nothing. Children are not supported
	}

	void CBuiltInSelect::COwner::NotifyOnBeforeDeleteItems(IListItem *parent)
	{
		// Nothing. Children are not supported
	}

	void CBuiltInSelect::COwner::NotifyOnDeleteItems(IListItem *parent)
	{
		// Nothing. Children are not supported
	}

	void CBuiltInSelect::COwner::NotifyOnShow(IListItem *item)
	{
		if (!isIgnoreShow() && m_pControl->m_bOpened && !item->getParent())
		{
			RectF r{ m_pControl->getListRenderRect() };
			m_pControl->UpdateList();
			m_pControl->UpdateHoveredItem();
			if (m_pControl->m_pListener)
			{
				if (m_pControl->m_pCanvasList)
					m_pControl->m_pCanvasList->setValid(false);
				m_pControl->m_pListener->NotifyOnRepaint(m_pControl, r + m_pControl->getListRenderRect());
			}
		}
	}

	void CBuiltInSelect::COwner::NotifyOnHide(IListItem *item)
	{
		if (!isIgnoreHide() && m_pControl->m_bOpened && !item->getParent())
		{
			RectF r{ m_pControl->getListRenderRect() };
			m_pControl->UpdateList();
			m_pControl->UpdateHoveredItem();
			if (m_pControl->m_pListener)
			{
				if (m_pControl->m_pCanvasList)
					m_pControl->m_pCanvasList->setValid(false);
				m_pControl->m_pListener->NotifyOnRepaint(m_pControl, r + m_pControl->getListRenderRect());
			}
		}
	}

	void CBuiltInSelect::COwner::NotifyOnEnable(IListItem *item)
	{
		if (!isIgnoreEnable() && m_pControl->m_bOpened && !item->getParent() && m_pControl->m_pListener)
		{
			if (m_pControl->m_pCanvasList)
				m_pControl->m_pCanvasList->setValid(false);
			m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getListRenderRect());
		}
	}

	void CBuiltInSelect::COwner::NotifyOnDisable(IListItem *item)
	{
		if (!isIgnoreDisable() && m_pControl->m_bOpened && !item->getParent())
		{
			RectF r{ m_pControl->getListRenderRect() };
			if (m_pControl->m_iActiveIndex >= 0 && m_pControl->getItemIndex(item) == m_pControl->m_iActiveIndex)
			{
				setIgnoreDeactivate(true);
				m_pControl->m_iActiveIndex = -1;
				item->setActive(false);
				setIgnoreDeactivate(false);
				r += m_pControl->getControlRenderRect();
				if (m_pControl->m_pCanvasControl)
					m_pControl->m_pCanvasControl->setValid(false);
			}
			if (m_pControl->m_pCanvasList)
				m_pControl->m_pCanvasList->setValid(false);
			if (m_pControl->m_pListener)
				m_pControl->m_pListener->NotifyOnRepaint(m_pControl, r);
		}
	}

	void CBuiltInSelect::COwner::NotifyOnSelect(IListItem *item)
	{
		if (!isIgnoreSelect() && item->isVisible() && m_pControl->m_bOpened && m_pControl->m_pListener)
		{
			if (m_pControl->m_pCanvasList)
				m_pControl->m_pCanvasList->setValid(false);
			m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getListRenderRect());
		}
	}

	void CBuiltInSelect::COwner::NotifyOnDeselect(IListItem *item)
	{
		if (!isIgnoreDeselect() && item->isVisible() && m_pControl->m_bOpened && m_pControl->m_pListener)
		{
			if (m_pControl->m_pCanvasList)
				m_pControl->m_pCanvasList->setValid(false);
			m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getListRenderRect());
		}
	}

	void CBuiltInSelect::COwner::NotifyOnActivate(IListItem *item)
	{
		if (!isIgnoreActivate() && !item->getParent())
		{
			int index{ 0 };
			setIgnoreDeactivate(true);
			for (auto pos = m_pControl->m_aItems.begin(); pos != m_pControl->m_aItems.end(); pos++, index++)
				if (*pos != item && (*pos)->isActive())
					(*pos)->setActive(false);
				else if (*pos == item)
					m_pControl->m_iActiveIndex = index;
			setIgnoreDeactivate(false);
			if (m_pControl->m_pSelectListener)
				m_pControl->m_pSelectListener->NotifyOnSelect(m_pControl, m_pControl->m_iActiveIndex);
			if (m_pControl->m_pCanvasControl)
				m_pControl->m_pCanvasControl->setValid(false);
			if (m_pControl->m_pCanvasList)
				m_pControl->m_pCanvasList->setValid(false);
			if (m_pControl->m_bOpened && m_pControl->m_pListener)
				m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getListRenderRect());
		}
	}

	void CBuiltInSelect::COwner::NotifyOnDeactivate(IListItem *item)
	{
		if (!isIgnoreDeactivate() && !item->getParent())
		{
			if (m_pControl->m_iActiveIndex >= 0 && m_pControl->getItemIndex(item) == m_pControl->m_iActiveIndex)
			{
				m_pControl->m_iActiveIndex = -1;
				if (m_pControl->m_pCanvasControl)
					m_pControl->m_pCanvasControl->setValid(false);
			}
			if (m_pControl->m_pCanvasList)
				m_pControl->m_pCanvasList->setValid(false);
			if (m_pControl->m_pListener)
				m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getListRenderRect());
		}
	}
#pragma endregion

#pragma region Constructor & destructor
	CBuiltInSelect::CBuiltInSelect() :
		CBuiltInControl(L"DropDown", { 145, 21 }),
		m_cGradientListener{ this },
		m_cScrollListener{ this },
		m_cTextInputListener{ this },
		m_cOwner{ this },
		m_pListener{ nullptr },
		m_pSelectListener{ nullptr },
		m_bOpened{ false },
		m_iActiveIndex{ -1 },
		m_bArrowAtRight{ true },
		m_eOpenDirection{ OpenDirection::Down },
		m_eArrowArea{ ArrowArea::Height },
		m_fListWidth{ -1 },
		m_fListMaxHeight{ 150 },
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
		m_aShadowColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 }
		},
		m_aShadowShift{
			PointF{ 0, 0 },
			PointF{ 0, 0 },
			PointF{ 0, 0 },
			PointF{ 0, 0 },
			PointF{ 0, 0 }
		},
		m_aShadowRadius{
			1,
			1,
			1,
			1,
			1
		},
		m_aBorderColor{
			BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
			BorderColor{ Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 } },
			BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
			BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
			BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } }
		},
		m_aBackgroundColor{
			Color{ 255, 255, 255, 255 },
			Color{ 255, 255, 255, 255 },
			Color{ 255, 255, 255, 255 },
			Color{ 255, 255, 255, 255 },
			Color{ 244, 244, 244, 255 }
		},
		m_aBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener }
		},
		m_aInputBorderColor{
			BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
			BorderColor{ Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 } },
			BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
			BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
			BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } }
		},
		m_aInputBackgroundColor{
			Color{ 255, 255, 255, 255 },
			Color{ 255, 255, 255, 255 },
			Color{ 255, 255, 255, 255 },
			Color{ 255, 255, 255, 255 },
			Color{ 244, 244, 244, 255 }
		},
		m_aInputBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener }
		},
		m_aArrowBorderColor{
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 } },
			BorderColor{ Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 } },
			BorderColor{ Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
		},
		m_aArrowBackgroundColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 }
		},
		m_aArrowBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener }
		},
		m_aArrowColor{
			Color{ 0, 0, 0, 255 },
			Color{ 0, 0, 0, 255 },
			Color{ 0, 0, 0, 255 },
			Color{ 0, 0, 0, 255 },
			Color{ 109, 109, 109, 255 }
		},
		m_sListBorderColor{ Color{ 227, 227, 227, 255 }, Color{ 227, 227, 227, 255 }, Color{ 227, 227, 227, 255 }, Color{ 227, 227, 227, 255 } },
		m_sListBackgroundColor{ 255, 255, 255, 255 },
		m_cListBackgroundGradient{ &m_cGradientListener },
		m_sListShadowColor{ 152, 152, 152, 200 },
		m_sListShadowShift{ 2, 2 },
		m_iListShadowRadius{ 3 },
		m_pScroll{ nullptr },
		m_pTextInput{ nullptr },
		m_bIgnoreGradient{ true },
		m_sListRect{ 0, 0, 0, 0 },
		m_fListScroll{ 0 },
		m_fListScrollMax{ 0 },
		m_eHoveredElement{ ElementType::None },
		m_eDownElement{ ElementType::None },
		m_pCanvasControl{ nullptr },
		m_pCanvasList{ nullptr }
	{
		m_aBackgroundGradient[(int)State::Normal].setPointCount(4);
		m_aBackgroundGradient[(int)State::Normal].setPoint(0, Color1D{ 0.000f, Color{ 242, 242, 242, 255 } });
		m_aBackgroundGradient[(int)State::Normal].setPoint(1, Color1D{ 0.499f, Color{ 235, 235, 235, 255 } });
		m_aBackgroundGradient[(int)State::Normal].setPoint(2, Color1D{ 0.500f, Color{ 221, 221, 221, 255 } });
		m_aBackgroundGradient[(int)State::Normal].setPoint(3, Color1D{ 1.000f, Color{ 207, 207, 207, 255 } });
		m_aArrowBackgroundGradient[(int)State::Normal].setPointCount(4);
		m_aArrowBackgroundGradient[(int)State::Normal].setPoint(0, Color1D{ 0.000f, Color{ 242, 242, 242, 255 } });
		m_aArrowBackgroundGradient[(int)State::Normal].setPoint(1, Color1D{ 0.499f, Color{ 235, 235, 235, 255 } });
		m_aArrowBackgroundGradient[(int)State::Normal].setPoint(2, Color1D{ 0.500f, Color{ 221, 221, 221, 255 } });
		m_aArrowBackgroundGradient[(int)State::Normal].setPoint(3, Color1D{ 1.000f, Color{ 207, 207, 207, 255 } });

		m_aBackgroundGradient[(int)State::Hovered].setPointCount(4);
		m_aBackgroundGradient[(int)State::Hovered].setPoint(0, Color1D{ 0.000f, Color{ 234, 246, 253, 255 } });
		m_aBackgroundGradient[(int)State::Hovered].setPoint(1, Color1D{ 0.499f, Color{ 217, 240, 252, 255 } });
		m_aBackgroundGradient[(int)State::Hovered].setPoint(2, Color1D{ 0.500f, Color{ 190, 230, 253, 255 } });
		m_aBackgroundGradient[(int)State::Hovered].setPoint(3, Color1D{ 1.000f, Color{ 167, 217, 245, 255 } });
		m_aArrowBackgroundGradient[(int)State::Hovered].setPointCount(4);
		m_aArrowBackgroundGradient[(int)State::Hovered].setPoint(0, Color1D{ 0.000f, Color{ 234, 246, 253, 255 } });
		m_aArrowBackgroundGradient[(int)State::Hovered].setPoint(1, Color1D{ 0.499f, Color{ 217, 240, 252, 255 } });
		m_aArrowBackgroundGradient[(int)State::Hovered].setPoint(2, Color1D{ 0.500f, Color{ 190, 230, 253, 255 } });
		m_aArrowBackgroundGradient[(int)State::Hovered].setPoint(3, Color1D{ 1.000f, Color{ 167, 217, 245, 255 } });

		m_aBackgroundGradient[(int)State::Focused].setPointCount(4);
		m_aBackgroundGradient[(int)State::Focused].setPoint(0, Color1D{ 0.000f, Color{ 222, 237, 246, 255 } });
		m_aBackgroundGradient[(int)State::Focused].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 246, 255 } });
		m_aBackgroundGradient[(int)State::Focused].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 239, 255 } });
		m_aBackgroundGradient[(int)State::Focused].setPoint(3, Color1D{ 1.000f, Color{ 102, 175, 215, 255 } });
		m_aArrowBackgroundGradient[(int)State::Focused].setPointCount(4);
		m_aArrowBackgroundGradient[(int)State::Focused].setPoint(0, Color1D{ 0.000f, Color{ 222, 237, 246, 255 } });
		m_aArrowBackgroundGradient[(int)State::Focused].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 246, 255 } });
		m_aArrowBackgroundGradient[(int)State::Focused].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 239, 255 } });
		m_aArrowBackgroundGradient[(int)State::Focused].setPoint(3, Color1D{ 1.000f, Color{ 102, 175, 215, 255 } });

		m_aBackgroundGradient[(int)State::FocusedHovered].setPointCount(4);
		m_aBackgroundGradient[(int)State::FocusedHovered].setPoint(0, Color1D{ 0.000f, Color{ 222, 237, 246, 255 } });
		m_aBackgroundGradient[(int)State::FocusedHovered].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 246, 255 } });
		m_aBackgroundGradient[(int)State::FocusedHovered].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 239, 255 } });
		m_aBackgroundGradient[(int)State::FocusedHovered].setPoint(3, Color1D{ 1.000f, Color{ 102, 175, 215, 255 } });
		m_aArrowBackgroundGradient[(int)State::FocusedHovered].setPointCount(4);
		m_aArrowBackgroundGradient[(int)State::FocusedHovered].setPoint(0, Color1D{ 0.000f, Color{ 222, 237, 246, 255 } });
		m_aArrowBackgroundGradient[(int)State::FocusedHovered].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 246, 255 } });
		m_aArrowBackgroundGradient[(int)State::FocusedHovered].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 239, 255 } });
		m_aArrowBackgroundGradient[(int)State::FocusedHovered].setPoint(3, Color1D{ 1.000f, Color{ 102, 175, 215, 255 } });

		m_bIgnoreGradient = false;
	}

	CBuiltInSelect::~CBuiltInSelect()
	{
		DeleteItems();
		if (m_pScroll)
			m_pScroll->Release();
		if (m_pTextInput)
			m_pTextInput->Release();
	}
#pragma endregion

#pragma region IBuiltInControl getters
	IBuiltInControlListener *CBuiltInSelect::getListener()
	{
		return m_pListener;
	}

	bool CBuiltInSelect::isHovered()
	{
		return m_eHoveredElement != ElementType::None;
	}

	RectF CBuiltInSelect::getClientRect()
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

	RectF CBuiltInSelect::getRenderRect()
	{
		RectF result{ getRenderRect(State::Normal) };
		for (int i = 1; i <= (int)State::Disabled; i++)
			result += getRenderRect((State)i);
		return result;
	}

	CursorType CBuiltInSelect::getCursor(const PointF &position, const CursorType def)
	{
		if (isEnabled() && m_bOpened)
		{
			RectF client{ getClientRect() };
			return getTextInput()->getCursor(PointF{ position.X - client.Left, position.Y - client.Top }, def);
		}
		return def;
	}

	bool CBuiltInSelect::isInside(const PointF &position)
	{
		if (position.X >= 0 && position.X < getWidth() && position.Y >= 0 && position.Y < getHeight())
			return true;
		if (m_bOpened && m_sListRect.is_inside(position))
			return true;
		return false;
	}

	bool CBuiltInSelect::isDown()
	{
		return m_eDownElement != ElementType::None;
	}
#pragma endregion

#pragma region IBuiltInControl setters
	void CBuiltInSelect::setListener(IBuiltInControlListener *value)
	{
		m_pListener = value;
		m_pSelectListener = cast<IBuiltInSelectListener*>(value);
	}

	bool CBuiltInSelect::setEnabled(const bool value)
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

	bool CBuiltInSelect::setFocused(const bool value)
	{
		if (CBuiltInControl::setFocused(value && isEnabled()))
		{
			getTextInput()->setFocused(m_bOpened && isFocused());
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

	bool CBuiltInSelect::setSize(const PointF &value)
	{
		if (CBuiltInControl::setSize(value))
		{
			if (m_bOpened)
			{
				UpdateInput();
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

	bool CBuiltInSelect::setDPI(const Point &value)
	{
		Point old{ getDPI() };
		if (CBuiltInControl::setDPI(value))
		{
			getScroll()->setDPI(value);
			getTextInput()->setDPI(value);
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
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				m_aShadowShift[i] *= s;
				m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
			}
			m_sListShadowShift *= s;
			m_iListShadowRadius = ntl::Round<int>((float)m_iListShadowRadius * avg);
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			if (m_bOpened)
			{
				UpdateInput();
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

#pragma region IBuiltInControl methods
	void CBuiltInSelect::UpdateFromStyle(IStyle *style, const String &class_name)
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
			style->getOption(class_name + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);
			style->getOption(class_name + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
			style->getOption(class_name + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
			style->getOption(class_name + L".BorderColor[" + state + L"]", m_aBorderColor[i]);
			style->getOption(class_name + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]);
			style->getOption(class_name + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]);
			style->getOption(class_name + L".ArrowBorderColor[" + state + L"]", m_aArrowBorderColor[i]);
			style->getOption(class_name + L".ArrowBackgroundColor[" + state + L"]", m_aArrowBackgroundColor[i]);
			style->getOption(class_name + L".ArrowBackgroundGradient[" + state + L"]", m_aArrowBackgroundGradient[i]);
			style->getOption(class_name + L".ArrowColor[" + state + L"]", m_aArrowColor[i]);
		}
		style->getOption(class_name + L".ListBorderColor", m_sListBorderColor);
		style->getOption(class_name + L".ListBackgroundColor", m_sListBackgroundColor);
		style->getOption(class_name + L".ListBackgroundGradient", m_cListBackgroundGradient);
		style->getOption(class_name + L".ListShadowColor", m_sListShadowColor);
		style->getOption(class_name + L".ListShadowShift", m_sListShadowShift);
		style->getOption(class_name + L".ListShadowRadius", m_iListShadowRadius);
		getScroll()->UpdateFromStyle(style, class_name + L".Scroll");
		getTextInput()->UpdateFromStyle(style, class_name + L".TextInput");
		for (auto item : m_aItems)
			item->QueryService()->UpdateFromStyle();
		if (m_bOpened)
		{
			UpdateInput();
			UpdateList();
			UpdateHoveredItem();
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
		}
		if (m_pCanvasControl)
			m_pCanvasControl->setValid(false);
		m_bIgnoreGradient = false;
	}

	void CBuiltInSelect::Update()
	{
		if (m_bOpened)
		{
			getTextInput()->Update();
			getScroll()->Update();
			UpdateInput();
			UpdateList();
			UpdateHoveredItem();
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
		}
		if (m_pCanvasControl)
			m_pCanvasControl->setValid(false);
	}

	void CBuiltInSelect::Refresh()
	{
		if (m_pCanvasControl)
			m_pCanvasControl->setValid(false);
		if (m_pCanvasList)
			m_pCanvasList->setValid(false);
		getScroll()->Refresh();
		getTextInput()->Refresh();
	}
#pragma endregion

#pragma region IBuiltInSelect getters
	int CBuiltInSelect::getItemCount()
	{
		return (int)m_aItems.size();
	}

	IListItem *CBuiltInSelect::getItem(const int index)
	{
		if (index >= 0 && index < (int)m_aItems.size())
			return m_aItems[index];
		return nullptr;
	}

	int CBuiltInSelect::getItemIndex(IListItem *item)
	{
		for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			if (*pos == item)
				return int(pos - m_aItems.begin());
		return -1;
	}

	bool CBuiltInSelect::isOpened()
	{
		return m_bOpened;
	}

	String CBuiltInSelect::getFilter()
	{
		return getTextInput()->getText();
	}

	int CBuiltInSelect::getActiveIndex()
	{
		return m_iActiveIndex;
	}

	PointF CBuiltInSelect::getMousePosition()
	{
		if (getControl() && getControl()->getForm())
		{
			Point cl{ getControl()->getForm()->ScreenToClient(Application->Mouse->getPosition()) };
			PointF p{ getControl()->FormToLocal(PointF{ (float)cl.X, (float)cl.Y }) };
			return PointF{ p.X - getLeft(), p.Y - getTop() };
		}
		return PointF{ 0, 0 };
	}

	IBuiltInScroll *CBuiltInSelect::getScroll()
	{
		if (!m_pScroll)
		{
			CScroll *scroll{ new CScroll(this) };
			m_pScroll = scroll;
			if (!scroll->isVertical())
				scroll->SwitchDirection(true);
			scroll->setSize(PointF{ 8, scroll->getHeight() });
			scroll->setBorderRound(false);
			scroll->setScrollerRound(false);
			scroll->setBackgroundColor(Color{ 220, 220, 220, 255 });
			scroll->setScrollerBackgroundColor(CBuiltInScrollLite::State::Normal, Color{ 200, 200, 200, 255 });
			scroll->setListener(&m_cScrollListener);
		}
		return m_pScroll;
	}

	IBuiltInTextInput *CBuiltInSelect::getTextInput()
	{
		if (!m_pTextInput)
		{
			m_pTextInput = new CTextInput(this);
			m_pTextInput->setListener(&m_cTextInputListener);
			m_pTextInput->setEnabled(isEnabled());
			m_pTextInput->setFocused(m_bOpened && isFocused());
		}
		return m_pTextInput;
	}
#pragma endregion

#pragma region IBuiltInSelect setters
	bool CBuiltInSelect::setFilter(const String &value)
	{
		if (getTextInput()->setText(value))
		{
			if (m_bOpened)
			{
				UpdateList();
				UpdateHoveredItem();
				if (m_pCanvasControl)
					m_pCanvasControl->setValid(false);
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setActiveIndex(const int value)
	{
		if (value < 0 && m_iActiveIndex < 0)
			return false;
		if (value != m_iActiveIndex && value < (int)m_aItems.size() && m_aItems[value]->isEnabled())
		{
			if (m_iActiveIndex >= 0)
			{
				m_cOwner.setIgnoreDeactivate(true);
				m_aItems[m_iActiveIndex]->setActive(false);
				m_cOwner.setIgnoreDeactivate(false);
			}
			m_iActiveIndex = value >= 0 ? value : -1;
			if (m_iActiveIndex >= 0)
			{
				m_cOwner.setIgnoreActivate(true);
				m_aItems[m_iActiveIndex]->setActive(true);
				m_cOwner.setIgnoreActivate(false);
			}
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			if (m_bOpened)
			{
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setScroll(IBuiltInScroll *value)
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
				UpdateHoveredItem();
				if (m_pCanvasList)
					m_pCanvasList->setValid(false);
			}
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setTextInput(IBuiltInTextInput *value)
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
			m_pTextInput->setFocused(m_bOpened && isFocused());
			m_pTextInput->setEnabled(isEnabled());
			if (m_bOpened)
				UpdateInput();
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region IBuiltInSelect items
	bool CBuiltInSelect::AddItem(IListItem *item)
	{
		return InsertItem(item, (int)m_aItems.size());
	}

	bool CBuiltInSelect::InsertItem(IListItem *item, const int before)
	{
		if (item && !item->getParent() && !item->QueryService()->getOwner())
		{
			item->setActive(false);
			item->setSelected(false);
			item->QueryService()->setHovered(false);
			item->QueryService()->setOwner(&m_cOwner);
			item->QueryService()->setDPI(getDPI());
			if (before <= 0)
				m_aItems.insert(m_aItems.begin(), item);
			else if (before >= (int)m_aItems.size())
				m_aItems.push_back(item);
			else
				m_aItems.insert(m_aItems.begin() + before, item);
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

	bool CBuiltInSelect::DeleteItem(const int index)
	{
		if (index >= 0 && index < (int)m_aItems.size())
		{
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

	bool CBuiltInSelect::DeleteItem(IListItem *item)
	{
		if (item)
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				if ((*pos) == item)
					return DeleteItem(int(pos - m_aItems.begin()));
		return false;
	}

	bool CBuiltInSelect::DeleteItems()
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
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::MoveItem(IListItem *item, const int before)
	{
		if (MoveListItem(m_aItems, cast<IComponentItemList*>(getControl()), item, before))
		{
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

#pragma region IBuiltInSelect helpers
	bool CBuiltInSelect::Open()
	{
		if (!m_bOpened && isEnabled() && getControl() && getControl()->getForm())
		{
			m_bOpened = true;
			getControl()->getForm()->setActiveControl(getControl());
			UpdateInput();
			UpdateList();
			UpdateHoveredItem();
			ScrollToActiveItem();
			m_pTextInput->setFocused(true);
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::Close()
	{
		if (m_bOpened)
		{
			m_eDownElement = ElementType::None;
			m_bOpened = false;
			if (m_pTextInput)
			{
				m_pTextInput->setFocused(false);
				m_pTextInput->NotifyOnMouseDownCancel();
			}
			if (m_pScroll)
				m_pScroll->NotifyOnMouseDownCancel();
			if (getControl() && getControl()->isActive())
				getControl()->getForm()->setActiveControl(nullptr);
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	IListItemOwner *CBuiltInSelect::QueryListItemOwner()
	{
		return &m_cOwner;
	}
#pragma endregion

#pragma region Getters
	CBuiltInSelect::State CBuiltInSelect::getState()
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

	bool CBuiltInSelect::isArrowAtRight() const
	{
		return m_bArrowAtRight;
	}

	CBuiltInSelect::OpenDirection CBuiltInSelect::getOpenDirection() const
	{
		return m_eOpenDirection;
	}

	CBuiltInSelect::ArrowArea CBuiltInSelect::getArrowArea() const
	{
		return m_eArrowArea;
	}

	float CBuiltInSelect::getListWidth() const
	{
		return m_fListWidth;
	}

	float CBuiltInSelect::getListMaxHeight() const
	{
		return m_fListMaxHeight;
	}

	float CBuiltInSelect::getArrowAreaSize() const
	{
		return m_fArrowAreaSize;
	}

	float CBuiltInSelect::getArrowSize() const
	{
		return m_fArrowSize;
	}

	RectF CBuiltInSelect::getBorderWidth() const
	{
		return m_sBorderWidth;
	}

	RectF CBuiltInSelect::getBorderRadius() const
	{
		return m_sBorderRadius;
	}

	RectF CBuiltInSelect::getPadding() const
	{
		return m_sPadding;
	}

	RectF CBuiltInSelect::getArrowBorderWidth() const
	{
		return m_sArrowBorderWidth;
	}

	RectF CBuiltInSelect::getArrowBorderRadius() const
	{
		return m_sArrowBorderRadius;
	}

	RectF CBuiltInSelect::getListBorderWidth() const
	{
		return m_sListBorderWidth;
	}

	RectF CBuiltInSelect::getListBorderRadius() const
	{
		return m_sListBorderRadius;
	}

	RectF CBuiltInSelect::getListPadding() const
	{
		return m_sListPadding;
	}

	Color CBuiltInSelect::getShadowColor(const State state) const
	{
		return m_aShadowColor[(int)state];
	}

	PointF CBuiltInSelect::getShadowShift(const State state) const
	{
		return m_aShadowShift[(int)state];
	}

	int CBuiltInSelect::getShadowRadius(const State state) const
	{
		return m_aShadowRadius[(int)state];
	}

	BorderColor CBuiltInSelect::getBorderColor(const State state) const
	{
		return m_aBorderColor[(int)state];
	}

	Color CBuiltInSelect::getBackgroundColor(const State state) const
	{
		return m_aBackgroundColor[(int)state];
	}

	Gradient *CBuiltInSelect::getBackgroundGradient(const State state)
	{
		return &m_aBackgroundGradient[(int)state];
	}

	BorderColor CBuiltInSelect::getInputBorderColor(const State state) const
	{
		return m_aInputBorderColor[(int)state];
	}

	Color CBuiltInSelect::getInputBackgroundColor(const State state) const
	{
		return m_aInputBackgroundColor[(int)state];
	}

	Gradient *CBuiltInSelect::getInputBackgroundGradient(const State state)
	{
		return &m_aInputBackgroundGradient[(int)state];
	}

	BorderColor CBuiltInSelect::getArrowBorderColor(const State state) const
	{
		return m_aArrowBorderColor[(int)state];
	}

	Color CBuiltInSelect::getArrowBackgroundColor(const State state) const
	{
		return m_aArrowBackgroundColor[(int)state];
	}

	Gradient *CBuiltInSelect::getArrowBackgroundGradient(const State state)
	{
		return &m_aArrowBackgroundGradient[(int)state];
	}

	Color CBuiltInSelect::getArrowColor(const State state) const
	{
		return m_aArrowColor[(int)state];
	}

	BorderColor CBuiltInSelect::getListBorderColor() const
	{
		return m_sListBorderColor;
	}

	Color CBuiltInSelect::getListBackgroundColor() const
	{
		return m_sListBackgroundColor;
	}

	Gradient *CBuiltInSelect::getListBackgroundGradient()
	{
		return &m_cListBackgroundGradient;
	}

	Color CBuiltInSelect::getListShadowColor() const
	{
		return m_sListShadowColor;
	}

	PointF CBuiltInSelect::getListShadowShift() const
	{
		return m_sListShadowShift;
	}

	int CBuiltInSelect::getListShadowRadius() const
	{
		return m_iListShadowRadius;
	}
#pragma endregion

#pragma region Setters
	bool CBuiltInSelect::setArrowAtRight(const bool value)
	{
		if (value != m_bArrowAtRight)
		{
			m_bArrowAtRight = value;
			if (m_bOpened)
				UpdateInput();
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setOpenDirection(const OpenDirection value)
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

	bool CBuiltInSelect::setListWidth(const float value)
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

	bool CBuiltInSelect::setListMaxHeight(const float value)
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

	bool CBuiltInSelect::setArrowArea(const ArrowArea value)
	{
		if (value != m_eArrowArea)
		{
			m_eArrowArea = value;
			if (m_bOpened)
				UpdateInput();
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setArrowAreaSize(const float value)
	{
		if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fArrowAreaSize))
		{
			m_fArrowAreaSize = value;
			if (m_bOpened)
				UpdateInput();
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setArrowSize(const float value)
	{
		if (value >= 0 && value <= 1 && ntl::IsNotEqual<float>(value, m_fArrowSize))
		{
			m_fArrowSize = value;
			if (m_bOpened)
				UpdateInput();
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setBorderWidth(const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
		{
			m_sBorderWidth = value;
			if (m_bOpened)
				UpdateInput();
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setBorderRadius(const RectF &value)
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

	bool CBuiltInSelect::setPadding(const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_sPadding))
		{
			m_sPadding = value;
			if (m_bOpened)
				UpdateInput();
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setArrowBorderWidth(const RectF &value)
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

	bool CBuiltInSelect::setArrowBorderRadius(const RectF &value)
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

	bool CBuiltInSelect::setListBorderWidth(const RectF &value)
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

	bool CBuiltInSelect::setListBorderRadius(const RectF &value)
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

	bool CBuiltInSelect::setListPadding(const RectF &value)
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

	bool CBuiltInSelect::setShadowColor(const State state, const Color &value)
	{
		if (value != m_aShadowColor[(int)state])
		{
			m_aShadowColor[(int)state] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setShadowShift(const State state, const PointF &value)
	{
		if (IsNotEqual(value, m_aShadowShift[(int)state]))
		{
			m_aShadowShift[(int)state] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setShadowRadius(const State state, const int value)
	{
		if (value != m_aShadowRadius[(int)state])
		{
			m_aShadowRadius[(int)state] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setBorderColor(const State state, const BorderColor &value)
	{
		if (value != m_aBorderColor[(int)state])
		{
			m_aBorderColor[(int)state] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setBackgroundColor(const State state, const Color &value)
	{
		if (value != m_aBackgroundColor[(int)state])
		{
			m_aBackgroundColor[(int)state] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setInputBorderColor(const State state, const BorderColor &value)
	{
		if (value != m_aInputBorderColor[(int)state])
		{
			m_aInputBorderColor[(int)state] = value;
			if (m_bOpened)
			{
				if (m_pCanvasControl)
					m_pCanvasControl->setValid(false);
			}
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setInputBackgroundColor(const State state, const Color &value)
	{
		if (value != m_aInputBackgroundColor[(int)state])
		{
			m_aInputBackgroundColor[(int)state] = value;
			if (m_bOpened)
			{
				if (m_pCanvasControl)
					m_pCanvasControl->setValid(false);
			}
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setArrowBorderColor(const State state, const BorderColor &value)
	{
		if (value != m_aArrowBorderColor[(int)state])
		{
			m_aArrowBorderColor[(int)state] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setArrowBackgroundColor(const State state, const Color &value)
	{
		if (value != m_aArrowBackgroundColor[(int)state])
		{
			m_aArrowBackgroundColor[(int)state] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setArrowColor(const State state, const Color &value)
	{
		if (value != m_aArrowColor[(int)state])
		{
			m_aArrowColor[(int)state] = value;
			if (m_pCanvasControl)
				m_pCanvasControl->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setListBorderColor(const BorderColor &value)
	{
		if (value != m_sListBorderColor)
		{
			m_sListBorderColor = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setListBackgroundColor(const Color &value)
	{
		if (value != m_sListBackgroundColor)
		{
			m_sListBackgroundColor = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setListShadowColor(const Color &value)
	{
		if (value != m_sListShadowColor)
		{
			m_sListShadowColor = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setListShadowShift(const PointF &value)
	{
		if (IsNotEqual(value, m_sListShadowShift))
		{
			m_sListShadowShift = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInSelect::setListShadowRadius(const int value)
	{
		if (value != m_iListShadowRadius)
		{
			m_iListShadowRadius = value;
			if (m_pCanvasList)
				m_pCanvasList->setValid(false);
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Helpers
	RectF CBuiltInSelect::getRenderRect(const State state)
	{
		RectF result{ getControlRenderRect(state) };
		if (m_bOpened)
			result += getListRenderRect();
		return result;
	}

	RectF CBuiltInSelect::getListRenderRect()
	{
		return AddShadow(m_sListRect, m_sListShadowColor, m_sListShadowShift, m_iListShadowRadius);
	}

	RectF CBuiltInSelect::getControlRenderRect(const State state)
	{
		return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
	}

	RectF CBuiltInSelect::getControlRenderRect()
	{
		RectF result{ getControlRenderRect(State::Normal) };
		for (int i = 1; i <= (int)State::Disabled; i++)
			result += getControlRenderRect((State)i);
		return result;
	}

	RectF CBuiltInSelect::getArrowAreaRect()
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

	IListItem *CBuiltInSelect::getItem(const PointF &position)
	{
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
				if (item->isVisible() &&
					position.X >= item->getPosition().X && position.X < item->getPosition().X + item->getSize().X &&
					position.Y >= item->getPosition().Y - m_fListScroll && position.Y < item->getPosition().Y - m_fListScroll + item->getSize().Y)
					return item;
		return nullptr;
	}

	bool CBuiltInSelect::isListHovered(const PointF &position)
	{
		return m_sListRect.is_inside(position);
	}

	bool CBuiltInSelect::ScrollToActiveItem()
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

	void CBuiltInSelect::UpdateList()
	{
		// Update visibility
		String filter{ ToLower(m_pTextInput->getText()) };
		m_cOwner.setIgnoreShow(true);
		m_cOwner.setIgnoreHide(true);
		for (auto item : m_aItems)
			item->setVisible(filter.empty() || !cast<IListItemCaption*>(item) || ToLower(cast<IListItemCaption*>(item)->getCaption()).find(filter) != String::npos);
		m_cOwner.setIgnoreShow(false);
		m_cOwner.setIgnoreHide(false);
		// Update list and scroll
		float required_height{ 0 };
		for (auto item : m_aItems)
			if (item->isVisible())
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
				Vec4f v1{ getControl()->getTransformMatrix() * Vec4f { m_sListRect.Left, m_sListRect.Top, 0, 1 } };
				Vec4f v2{ getControl()->getTransformMatrix() * Vec4f { m_sListRect.Right, m_sListRect.Top, 0, 1 } };
				Vec4f v3{ getControl()->getTransformMatrix() * Vec4f { m_sListRect.Right, m_sListRect.Bottom, 0, 1 } };
				Vec4f v4{ getControl()->getTransformMatrix() * Vec4f { m_sListRect.Left, m_sListRect.Bottom, 0, 1 } };
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
			getScroll()->setScrollerSize(inner_height * inner_height / required_height);
			getScroll()->setPosition(PointF{ m_sListRect.Right - m_sListBorderWidth.Right - getScroll()->getWidth(), m_sListRect.Top + m_sListBorderWidth.Top });
		}
		float y{ m_sListRect.Top + m_sListBorderWidth.Top + m_sListPadding.Top };
		for (auto item : m_aItems)
			if (item->isVisible())
			{
				float h{ item->QueryService()->getRequiredSize().Y };
				item->QueryService()->setSize(PointF{ inner_width - (ntl::IsGreater<float>(m_fListScrollMax, 0) ? (getScroll()->getSize().X - m_sListPadding.Right) : 0), h });
				item->QueryService()->setPosition(PointF{ m_sListRect.Left + m_sListBorderWidth.Left + m_sListPadding.Left, y });
				y += h;
			}
	}

	bool CBuiltInSelect::UpdateHoveredItem()
	{
		return UpdateHoveredItem(getMousePosition());
	}

	bool CBuiltInSelect::UpdateHoveredItem(const PointF &position)
	{
		if (!m_bOpened)
			return false;
		// Find new hovered items
		IListItem *hovered{ nullptr };
		if (m_bOpened)
			hovered = getItem(position);
		// Change hovered item
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

	void CBuiltInSelect::UpdateInput()
	{
		RectF client{ getClientRect() };
		getTextInput()->setSize(PointF{ client.width(), client.height() });
		getTextInput()->setPosition(client.LeftTop);
	}

	CBuiltInSelect::ElementType CBuiltInSelect::getElement(const PointF &position)
	{
		if (getArrowAreaRect().is_inside(position))
			return ElementType::Arrow;
		if (m_bOpened)
		{
			if (getClientRect().is_inside(position))
				return ElementType::Input;
			if (m_sListRect.is_inside(position))
			{
				if (ntl::IsGreater<float>(m_fListScrollMax, 0))
				{
					RectF client{
						m_sListRect.Right - m_sListBorderWidth.Right - m_sListPadding.Right - getScroll()->getSize().X,
						m_sListRect.Top + m_sListBorderWidth.Top + m_sListPadding.Top,
						m_sListRect.Right - m_sListBorderWidth.Right - m_sListPadding.Right,
						m_sListRect.Bottom - m_sListBorderWidth.Bottom - m_sListPadding.Bottom
					};
					if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
						return ElementType::ListScroll;
				}
				return ElementType::List;
			}
		}
		return ElementType::None;
	}

	PointF CBuiltInSelect::LocalToInput(const PointF &position)
	{
		RectF client{ getClientRect() };
		return PointF{ position.X - client.Left, position.Y - client.Top };
	}

	PointF CBuiltInSelect::LocalToScroll(const PointF &position)
	{
		return PointF{
			position.X - (m_sListRect.Right - m_sListBorderWidth.Right - getScroll()->getSize().X),
			position.Y - (m_sListRect.Top + m_sListBorderWidth.Top) };
	}

	bool CBuiltInSelect::ProcessKeyUp()
	{
		if (m_aItems.size() > 0)
		{
			int new_index{ m_iActiveIndex > 0 ? (m_iActiveIndex - 1) : ((int)m_aItems.size() - 1) };
			if (m_bOpened)
			{
				while (new_index >= 0 && (!m_aItems[new_index]->isEnabled() || !m_aItems[new_index]->isVisible()))
					new_index--;
			}
			else
			{
				while (new_index >= 0 && !m_aItems[new_index]->isEnabled())
					new_index--;
			}
			if (new_index >= 0 && new_index != m_iActiveIndex)
			{
				if (setActiveIndex(new_index) && m_pSelectListener)
					m_pSelectListener->NotifyOnSelect(this, m_iActiveIndex);
				if (ScrollToActiveItem())
					UpdateHoveredItem();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInSelect::ProcessKeyDown()
	{
		if (m_aItems.size() > 0)
		{
			int new_index{ m_iActiveIndex < ((int)m_aItems.size() - 1) ? (m_iActiveIndex + 1) : 0 };
			if (m_bOpened)
			{
				while (new_index < (int)m_aItems.size() && (!m_aItems[new_index]->isEnabled() || !m_aItems[new_index]->isVisible()))
					new_index++;
			}
			else
			{
				while (new_index < (int)m_aItems.size() && !m_aItems[new_index]->isEnabled())
					new_index++;
			}
			if (new_index < (int)m_aItems.size() && new_index != m_iActiveIndex)
			{
				if (setActiveIndex(new_index) && m_pSelectListener)
					m_pSelectListener->NotifyOnSelect(this, m_iActiveIndex);
				if (ScrollToActiveItem())
					UpdateHoveredItem();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInSelect::ProcessKeyPageUp()
	{
		if (m_aItems.size() > 0 && m_bOpened)
		{
			float item_height{ m_aItems[0]->getSize().Y };
			int count{ ntl::Round<int>((m_sListRect.height() - m_sListBorderWidth.Top - m_sListBorderWidth.Bottom - m_sListPadding.Top - m_sListPadding.Bottom) / item_height) };
			if (count == 0)
				count++;
			int new_index{ m_iActiveIndex >= 0 ? ntl::Max<int>(0, m_iActiveIndex - count) : ((int)m_aItems.size() - 1) };
			while (new_index >= 0 && (!m_aItems[new_index]->isEnabled() || !m_aItems[new_index]->isVisible()))
				new_index--;
			if (new_index < 0)
			{
				new_index = 0;
				while (new_index < (int)m_aItems.size() && (m_iActiveIndex < 0 || new_index < m_iActiveIndex) && (!m_aItems[new_index]->isEnabled() || !m_aItems[new_index]->isVisible()))
					new_index++;
			}
			if (new_index >= 0 && new_index < (int)m_aItems.size() && new_index != m_iActiveIndex)
			{
				if (setActiveIndex(new_index) && m_pSelectListener)
					m_pSelectListener->NotifyOnSelect(this, m_iActiveIndex);
				if (ScrollToActiveItem())
					UpdateHoveredItem();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInSelect::ProcessKeyPageDown()
	{
		if (m_aItems.size() > 0 && m_bOpened)
		{
			float item_height{ m_aItems[0]->getSize().Y };
			int count{ ntl::Round<int>((m_sListRect.height() - m_sListBorderWidth.Top - m_sListBorderWidth.Bottom - m_sListPadding.Top - m_sListPadding.Bottom) / item_height) };
			if (count == 0)
				count++;
			int new_index{ m_iActiveIndex >= 0 ? ntl::Min<int>((int)m_aItems.size() - 1, m_iActiveIndex + count) : 0 };
			while (new_index < (int)m_aItems.size() && (!m_aItems[new_index]->isEnabled() || !m_aItems[new_index]->isVisible()))
				new_index++;
			if (new_index >= (int)m_aItems.size())
			{
				new_index = (int)m_aItems.size() - 1;
				while (new_index >= 0 && (m_iActiveIndex < 0 || new_index > m_iActiveIndex) && (!m_aItems[new_index]->isEnabled() || !m_aItems[new_index]->isVisible()))
					new_index--;
			}
			if (new_index >= 0 && new_index < (int)m_aItems.size() && new_index != m_iActiveIndex)
			{
				if (setActiveIndex(new_index) && m_pSelectListener)
					m_pSelectListener->NotifyOnSelect(this, m_iActiveIndex);
				if (ScrollToActiveItem())
					UpdateHoveredItem();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInSelect::ProcessKeyHome()
	{
		if (m_aItems.size() > 0 && m_bOpened)
		{
			int new_index{ 0 };
			while (new_index < (int)m_aItems.size() && (m_iActiveIndex < 0 || new_index < m_iActiveIndex) && (!m_aItems[new_index]->isEnabled() || !m_aItems[new_index]->isVisible()))
				new_index++;
			if (new_index < (int)m_aItems.size() && new_index != m_iActiveIndex)
			{
				if (setActiveIndex(new_index) && m_pSelectListener)
					m_pSelectListener->NotifyOnSelect(this, m_iActiveIndex);
				if (ScrollToActiveItem())
					UpdateHoveredItem();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInSelect::ProcessKeyEnd()
	{
		if (m_aItems.size() > 0 && m_bOpened)
		{
			int new_index{ (int)m_aItems.size() - 1 };
			while (new_index >= 0 && (m_iActiveIndex < 0 || new_index > m_iActiveIndex) && (!m_aItems[new_index]->isEnabled() || !m_aItems[new_index]->isVisible()))
				new_index--;
			if (new_index >= 0 && new_index != m_iActiveIndex)
			{
				if (setActiveIndex(new_index) && m_pSelectListener)
					m_pSelectListener->NotifyOnSelect(this, m_iActiveIndex);
				if (ScrollToActiveItem())
					UpdateHoveredItem();
				return true;
			}
		}
		return false;
	}
#pragma endregion

#pragma region Paint
	void CBuiltInSelect::Render(const bool last_pass, const Mat4f &matrix, const Block *block)
	{
		if (getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
		{
			if (last_pass)
				RenderList(getControl()->getForm()->getRenderer(), matrix);
			else
				RenderControl(getControl()->getForm()->getRenderer(), matrix, block);
		}
	}

	void CBuiltInSelect::RenderControl(IRenderer *renderer, const Mat4f &matrix, const Block *block)
	{
		State state{ getState() };
		PointF disp{ DispOnCanvas(m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
		RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
		if (PrepareCanvas(renderer, &m_pCanvasControl, all_rect))
		{
			CStoreTarget s_target{ renderer };
			renderer
				->ActivateTarget(m_pCanvasControl)
				->Clear(Color{ 0, 0, 0, 0 });

			RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
			DrawBlockShadow(renderer, rect, m_sBorderRadius, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
			if (m_bOpened)
				DrawSimpleBackground(renderer, rect, m_sBorderWidth, m_sBorderRadius, m_aInputBorderColor[(int)state], m_aInputBackgroundColor[(int)state], m_aInputBackgroundGradient[(int)state]);
			else
				DrawSimpleBackground(renderer, rect, m_sBorderWidth, m_sBorderRadius, m_aBorderColor[(int)state], m_aBackgroundColor[(int)state], m_aBackgroundGradient[(int)state]);
			RenderControlArrow(renderer, state, disp);
			RenderControlActiveItem(renderer, state, rect);
			RenderControlInput(renderer, state, rect);

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

	void CBuiltInSelect::RenderControlArrow(IRenderer *renderer, const State state, const PointF &disp)
	{
		RectF area_rect{ getArrowAreaRect() };
		area_rect += disp;
		if (!area_rect.is_zero())
		{
			Block b{ area_rect, m_sArrowBorderWidth, m_sArrowBorderRadius, PointLocation::Inside };
			DrawSimpleBackground(renderer, area_rect, m_sArrowBorderWidth, m_sArrowBorderRadius, m_aArrowBorderColor[(int)state], m_aArrowBackgroundColor[(int)state],
				m_aArrowBackgroundGradient[(int)state]);
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
							m_aArrowColor[(int)state]);
				}
				else
				{
					renderer->DrawTriangle(PointF{ center.X, center.Y + w * 0.25f }, PointF{ center.X - w * 0.5f, center.Y - w * 0.25f }, PointF{ center.X + w * 0.5f, center.Y - w * 0.25f },
						m_aArrowColor[(int)state]);
				}
			}
		}
	}

	void CBuiltInSelect::RenderControlActiveItem(IRenderer *renderer, const State state, const RectF &rect)
	{
		if (!m_bOpened && m_iActiveIndex >= 0)
		{
			Block b{ rect, AddElements(m_sBorderWidth, m_sPadding), m_sBorderRadius, PointLocation::Inside };

			// Prepare
			RectF client{ rect };
			client.Left += m_sBorderWidth.Left + m_sPadding.Left;
			client.Top += m_sBorderWidth.Top + m_sPadding.Top;
			client.Right -= m_sBorderWidth.Right + m_sPadding.Right;
			client.Bottom -= m_sBorderWidth.Bottom + m_sPadding.Bottom;
			client.validate();

			bool hovered{ m_aItems[m_iActiveIndex]->isHovered() }, selected{ m_aItems[m_iActiveIndex]->isSelected() }, active{ m_aItems[m_iActiveIndex]->isActive() };
			bool enabled{ m_aItems[m_iActiveIndex]->isEnabled() };
			PointF size{ m_aItems[m_iActiveIndex]->getSize() };
			QueryListItemOwner()->setIgnoreActivate(true);
			QueryListItemOwner()->setIgnoreDeactivate(true);
			QueryListItemOwner()->setIgnoreEnable(true);
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
			QueryListItemOwner()->setIgnoreSizeChange(false);
		}
	}

	void CBuiltInSelect::RenderControlInput(IRenderer *renderer, const State state, const RectF &rect)
	{
		if (m_bOpened)
		{
			Block b{ rect, AddElements(m_sBorderWidth, m_sPadding), m_sBorderRadius, PointLocation::Inside };
			getTextInput()->Render(false, ntl::Mat4Translate<float>(rect.Left + m_sBorderWidth.Left + m_sPadding.Left, rect.Top + m_sBorderWidth.Top + m_sPadding.Top, 0), &b);
		}
	}

	void CBuiltInSelect::RenderList(IRenderer *renderer, const Mat4f &matrix)
	{
		if (m_bOpened)
		{
			PointF disp{ DispOnCanvas(m_sListShadowColor, m_sListShadowShift, m_iListShadowRadius) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, m_sListRect.width(), m_sListRect.height() }, m_sListShadowColor, m_sListShadowShift, m_iListShadowRadius) };
			if (PrepareCanvas(renderer, &m_pCanvasList, all_rect))
			{
				RectF rect{ disp.X, disp.Y, disp.X + m_sListRect.width(), disp.Y + m_sListRect.height() };
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvasList)
					->Clear(Color{ 0, 0, 0, 0 });

				DrawBlockShadow(renderer, rect, m_sListBorderRadius, m_sListShadowColor, m_sListShadowShift, m_iListShadowRadius);
				DrawSimpleBackground(renderer, rect, m_sListBorderWidth, m_sListBorderRadius, m_sListBorderColor, m_sListBackgroundColor, m_cListBackgroundGradient);
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

	void CBuiltInSelect::RenderListItems(IRenderer *renderer, const RectF &rect)
	{
		Block b{ rect, AddElements(m_sListBorderWidth, m_sListPadding), m_sListBorderRadius, PointLocation::Inside };
		Block *pb{ (b.Radius.has_positive() || b.Border.has_positive()) ? &b : nullptr };
		float x{ rect.Left + m_sListBorderWidth.Left + m_sListPadding.Left }, y{ rect.Top - m_fListScroll + m_sListBorderWidth.Top + m_sListPadding.Top };
		ITexture *clip{ nullptr };
		for (auto pos : m_aItems)
			if (pos->isVisible())
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

	void CBuiltInSelect::RenderListScroll(IRenderer *renderer, const RectF &rect)
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