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
		const String CCoolBar::TranslateCategory{ L"standard::CoolBar" };
		const String CCoolBar::TextAddOrRemoveButtons{ L"Add or Remove Buttons" };
		const String CCoolBar::TextWidgetI{ L"Widget #{i}" };

		const int DEFAULT_ICON_WIDTH{ 16 };
		const int DEFAULT_ICON_HEIGHT{ 16 };
		const Color DEFAULT_ICON_DATA[DEFAULT_ICON_WIDTH * DEFAULT_ICON_HEIGHT]{
			{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },
			{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },
			{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 0, 0, 0, 255 },{ 0, 0, 0, 255 },{ 0, 0, 0, 255 },{ 0, 0, 0, 255 },{ 0, 0, 0, 255 },{ 0, 0, 0, 255 },{ 0, 0, 0, 255 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },
			{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 0, 0, 0, 255 },{ 232, 123, 97, 255 },{ 228, 97, 67, 255 },{ 228, 97, 67, 255 },{ 228, 97, 67, 255 },{ 228, 97, 67, 255 },{ 0, 0, 0, 255 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },
			{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 0, 0, 0, 255 },{ 228, 97, 67, 255 },{ 223, 66, 30, 255 },{ 223, 66, 30, 255 },{ 223, 66, 30, 255 },{ 223, 66, 30, 255 },{ 0, 0, 0, 255 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },
			{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 0, 0, 0, 255 },{ 228, 97, 67, 255 },{ 223, 66, 30, 255 },{ 223, 66, 30, 255 },{ 223, 66, 30, 255 },{ 223, 66, 30, 255 },{ 0, 0, 0, 255 },{ 0, 0, 0, 255 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },
			{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 150, 150, 150, 255 },{ 40, 40, 40, 255 },{ 0, 0, 0, 255 },{ 228, 97, 67, 255 },{ 223, 66, 30, 255 },{ 223, 66, 30, 255 },{ 126, 36, 15, 255 },{ 106, 106, 106, 255 },{ 199, 208, 216, 255 },{ 0, 0, 0, 255 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },
			{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 152, 152, 152, 255 },{ 73, 66, 39, 255 },{ 239, 227, 188, 255 },{ 0, 0, 0, 255 },{ 0, 0, 0, 255 },{ 0, 0, 0, 255 },{ 130, 130, 130, 255 },{ 199, 208, 216, 255 },{ 158, 177, 198, 255 },{ 117, 144, 174, 255 },{ 0, 0, 0, 255 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },
			{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 41, 41, 41, 255 },{ 239, 227, 188, 255 },{ 242, 225, 165, 255 },{ 238, 214, 128, 255 },{ 0, 0, 0, 255 },{ 194, 200, 208, 255 },{ 139, 162, 187, 255 },{ 117, 144, 174, 255 },{ 117, 144, 174, 255 },{ 117, 144, 174, 255 },{ 0, 0, 0, 255 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },
			{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 0, 0, 0, 255 },{ 245, 233, 191, 255 },{ 238, 214, 128, 255 },{ 238, 214, 128, 255 },{ 165, 148, 88, 255 },{ 0, 0, 0, 255 },{ 0, 0, 0, 255 },{ 97, 120, 145, 255 },{ 117, 144, 174, 255 },{ 117, 144, 174, 255 },{ 0, 0, 0, 255 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },
			{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 41, 41, 40, 255 },{ 236, 222, 175, 255 },{ 238, 214, 128, 255 },{ 238, 214, 128, 255 },{ 238, 214, 128, 255 },{ 187, 167, 100, 255 },{ 38, 38, 38, 255 },{ 67, 67, 66, 255 },{ 0, 0, 0, 255 },{ 97, 120, 145, 255 },{ 0, 0, 0, 255 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },
			{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 148, 148, 148, 255 },{ 73, 66, 39, 255 },{ 224, 201, 120, 255 },{ 238, 214, 128, 255 },{ 224, 201, 120, 255 },{ 73, 66, 39, 255 },{ 141, 140, 139, 255 },{ 255, 255, 255, 0 },{ 161, 160, 158, 255 },{ 0, 0, 0, 255 },{ 0, 0, 0, 255 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },
			{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 136, 136, 135, 255 },{ 39, 39, 39, 255 },{ 0, 0, 0, 255 },{ 39, 39, 38, 255 },{ 140, 139, 137, 255 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },
			{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },
			{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },
			{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },{ 255, 255, 255, 0 },
		};
		const Image DEFAULT_ICON{ DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT, DEFAULT_ICON_DATA };

	#pragma region CGradientListener
		CCoolBar::CGradientListener::CGradientListener(CCoolBar *control) :
			m_pControl{ control }
		{

		}

		void CCoolBar::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_bExtraListVisible && m_pControl->m_pCanvasExtraList)
					m_pControl->m_pCanvasExtraList->setValid(false);
				if (m_pControl->m_bToggleListVisible && m_pControl->m_pCanvasToggleList)
					m_pControl->m_pCanvasToggleList->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CCoolBar::CCoolBar():
			CDialogBox(L"CoolBar", true, true, false, false, DesignDPI, new CCoolBarService(this)),
			m_cGradientListener{ this },
			m_eOrientation{ Orientation::LeftToRight },
			m_fStickDistance{ 10 },
			m_bAutoAlign{ true },
			m_bLocked{ false },
			m_bResizable{ true },
			m_pVisibilityManager{ nullptr },
			m_bMoverAlwaysVisible{ true },
			m_bExtraAlwaysVisible{ true },
			m_eMoverKind{ MoverKind::DoubleLine },
			m_sOuterBorderWidth{ 0, 1, 1, 0 },
			m_sOuterBorderColor{ Color{ 220, 224, 236, 255 }, Color{ 220, 224, 236, 255 }, Color{ 220, 224, 236, 255 }, Color{ 220, 224, 236, 255 } },
			m_sInnerBorderWidth{ 0, 0, 0, 0 },
			m_sInnerBorderColor{ Color{ 240, 240, 240, 255 }, Color{ 240, 240, 240, 255 }, Color{ 240, 240, 240, 255 }, Color{ 240, 240, 240, 255 } },
			m_sPadding{ 2, 2, 2, 2 },
			m_sBackgroundColor{ 207, 214, 229, 255 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_sMoverMargin{ 0, 0, 0, 0 },
			m_sMoverBorderWidth{ 0, 0, 0, 0 },
			m_sMoverPadding{ 2, 2, 2, 2 },
			m_aMoverBorderColor{
				BorderColor{ Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 } },
				BorderColor{ Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 } },
				BorderColor{ Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 } },
				BorderColor{ Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 } }
			},
			m_aMoverBackgroundColor{
				Color{ 207, 214, 229, 255 },
				Color{ 207, 214, 229, 255 },
				Color{ 207, 214, 229, 255 },
				Color{ 207, 214, 229, 255 }
			},
			m_aMoverBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener }
			},
			m_aMoverForeground1Color{
				Color{ 160, 160, 160, 255 },
				Color{ 160, 160, 160, 255 },
				Color{ 160, 160, 160, 255 },
				Color{ 160, 160, 160, 255 }
			},
			m_aMoverForeground2Color{
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 }
			},
			m_sExtraMargin{ 0, 0, 0, 0 },
			m_sExtraBorderWidth{ 0, 0, 0, 0 },
			m_sExtraPadding{ 2, 2, 2, 2 },
			m_fExtraSize{ 7 },
			m_aExtraBorderColor{
				BorderColor{ Color{ 253, 244, 191, 255 }, Color{ 253, 244, 191, 255 }, Color{ 253, 244, 191, 255 }, Color{ 253, 244, 191, 255 } },
				BorderColor{ Color{ 253, 244, 191, 255 }, Color{ 253, 244, 191, 255 }, Color{ 253, 244, 191, 255 }, Color{ 253, 244, 191, 255 } },
				BorderColor{ Color{ 253, 244, 191, 255 }, Color{ 253, 244, 191, 255 }, Color{ 253, 244, 191, 255 }, Color{ 253, 244, 191, 255 } },
				BorderColor{ Color{ 253, 244, 191, 255 }, Color{ 253, 244, 191, 255 }, Color{ 253, 244, 191, 255 }, Color{ 253, 244, 191, 255 } }
			},
			m_aExtraBackgroundColor{
				Color{ 220, 224, 236, 255 },
				Color{ 253, 244, 191, 255 },
				Color{ 253, 244, 191, 255 },
				Color{ 220, 224, 236, 255 }
			},
			m_aExtraBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener }
			},
			m_aExtraColor{
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 127, 127, 127, 255 }
			},
			m_sExtraListConstraints{ 0, 0 },
			m_sExtraListOuterBorderWidth{ 1, 1, 1, 1 },
			m_sExtraListOuterBorderColor{ Color{ 155, 167, 183, 255 }, Color{ 155, 167, 183, 255 }, Color{ 155, 167, 183, 255 }, Color{ 155, 167, 183, 255 } },
			m_sExtraListInnerBorderWidth{ 0, 0, 0, 0 },
			m_sExtraListInnerBorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			m_sExtraListPadding{ 2, 2, 2, 2 },
			m_sExtraListBackgroundColor{ 207, 214, 229, 255 },
			m_cExtraListBackgroundGradient{ &m_cGradientListener },
			m_iExtraListShadowRadius{ 3 },
			m_sExtraListShadowShift{ 2, 2 },
			m_sExtraListShadowColor{ 152, 152, 152, 200 },
			m_sExtraListButtonPadding{ 4, 4, 4, 4 },
			m_sExtraListButtonBorderWidth{ 1, 1, 1, 1 },
			m_aExtraListButtonBorderColor{
				BorderColor{ Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 } },
				BorderColor{ Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 } },
				BorderColor{ Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 } },
				BorderColor{ Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 } }
			},
			m_aExtraListButtonBackgroundColor{
				Color{ 207, 214, 229, 255 },
				Color{ 253, 244, 191, 255 },
				Color{ 253, 244, 191, 255 },
				Color{ 207, 214, 229, 255 }
			},
			m_aExtraListButtonBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener }
			},
			m_aExtraListButtonColor{
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 }
			},
			m_sToggleListConstraints{ 0, 0 },
			m_sToggleListOuterBorderWidth{ 1, 1, 1, 1 },
			m_sToggleListOuterBorderColor{ Color{ 155, 167, 183, 255 }, Color{ 155, 167, 183, 255 }, Color{ 155, 167, 183, 255 }, Color{ 155, 167, 183, 255 } },
			m_sToggleListInnerBorderWidth{ 0, 0, 0, 0 },
			m_sToggleListInnerBorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			m_sToggleListPadding{ 2, 2, 2, 2 },
			m_sToggleListBackgroundColor{ 207, 214, 229, 255 },
			m_cToggleListBackgroundGradient{ &m_cGradientListener },
			m_iToggleListShadowRadius{ 3 },
			m_sToggleListShadowShift{ 2, 2 },
			m_sToggleListShadowColor{ 152, 152, 152, 200 },
			m_fToggleListIconPadding{ 2 },
			m_sToggleListElementPadding{ 4, 4, 4, 4 },
			m_sToggleListElementBorderWidth{ 0, 0, 0, 0 },
			m_aToggleListElementBorderColor{
				BorderColor{ Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 } },
				BorderColor{ Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 } },
				BorderColor{ Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 } },
				BorderColor{ Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 }, Color{ 207, 214, 229, 255 } }
			},
			m_aToggleListElementBackgroundColor{
				Color{ 207, 214, 229, 255 },
				Color{ 253, 244, 191, 255 },
				Color{ 253, 244, 191, 255 },
				Color{ 207, 214, 229, 255 }
			},
			m_aToggleListElementBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener }
			},
			m_aToggleListElementColor{
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 127, 127, 127, 255 }
			},
			m_pCanvas{ nullptr },
			m_pCanvasExtraList{ nullptr },
			m_pCanvasToggleList{ nullptr },
			m_pMaskExtraList{ nullptr },
			m_eDownElement{ Element::None },
			m_eHoveredElement{ Element::None },
			m_iLastVisibleControl{ 0 },
			m_bShowExtra{ false },
			m_bHasExtraControls{ false },
			m_bIgnoreGradient{ false },
			m_bExtraListVisible{ false },
			m_bToggleListVisible{ false },
			m_pExtraListScroll{ nullptr },
			m_pToggleListScroll{ nullptr },
			m_bExtraListScrollVisible{ false },
			m_bToggleListScrollVisible{ false },
			m_cExtraListScrollListener{ this },
			m_cToggleListScrollListener{ this },
			m_bAligning{ false }
		{
			setSize(PointF{ 185, 40 });
		}

		CCoolBar::CCoolBar(IForm *parent) : CCoolBar()
		{
			setForm(parent);
		}

		CCoolBar::CCoolBar(IControl *parent) : CCoolBar()
		{
			setParent(parent);
		}

		CCoolBar::~CCoolBar()
		{
			if (m_pExtraListScroll)
				m_pExtraListScroll->Release();
			if (m_pToggleListScroll)
				m_pToggleListScroll->Release();
		}

		void CCoolBar::BeforeRelease()
		{
			m_pVisibilityManager = nullptr;
			m_bAligning = true;
			CDialogBox::BeforeRelease();
		}
	#pragma endregion

	#pragma region IControl getters
		IControl *CCoolBar::getControl(const int index)
		{
			return CControl::getControl(index);
		}

		IControl *CCoolBar::getControl(const String &name)
		{
			return CControl::getControl(name);
		}

		IControl *CCoolBar::getControl(const PointF &position)
		{
			if (isVisible(false))
			{
				Mat4f m{ ntl::Inversed<float>(getTransformMatrix()) };
				Vec4f v{ m * Vec4f{ position.X, position.Y, 0, 1 } };
				PointF p{ v.X, v.Y };
				IControl *result{ nullptr };
				std::vector<IControl*> controls;
				if (m_bExtraListVisible)
				{
					for (int i = m_iLastVisibleControl + 1; i < getControlCount(); i++)
						if (CControl::getControl(i)->isVisible(false))
							controls.push_back(CControl::getControl(i));
					std::sort(controls.begin(), controls.end(), [](IControl *a, IControl *b) { return a->getZIndex() < b->getZIndex(); });
					for (auto pos = controls.rbegin(); pos != controls.rend(); pos++)
						if ((result = (*pos)->getControl(position)))
							break;
					if (result)
					{
						if (result->hasExtra())
							return result;
						RectF client{ m_sExtraListClientRect };
						if (m_pVisibilityManager)
							client.Bottom = m_sExtraListButtonRect.Top;
						if (client.is_inside(p))
							return result;
					}
				}
				if (m_bToggleListVisible && m_sToggleListRect.is_inside(p))
					return this;
				controls.clear();
				for (int i = 0; i <= m_iLastVisibleControl && i < getControlCount(); i++)
					if (CControl::getControl(i)->isVisible(false))
						controls.push_back(CControl::getControl(i));
				std::sort(controls.begin(), controls.end(), [](IControl *a, IControl *b) { return a->getZIndex() < b->getZIndex(); });
				for (auto pos = controls.rbegin(); pos != controls.rend(); pos++)
					if ((result = (*pos)->getControl(position)))
						return result;
				if (m_bExtraListVisible && m_sExtraListRect.is_inside(p))
					return this;
				if (getRect().is_inside(p))
					return this;
			}
			return nullptr;
		}

		RectF CCoolBar::getClientRect()
		{
			bool t1, t2;
			return CalculateClientRect(t1, t2);
		}

		RectF CCoolBar::getRenderRect()
		{
			RectF result{ getRect() };
			if (m_bExtraListVisible)
				result += AddShadow(m_sExtraListRect, m_sExtraListShadowColor, m_sExtraListShadowShift, m_iExtraListShadowRadius);
			if (m_bToggleListVisible)
				result += AddShadow(m_sToggleListRect, m_sToggleListShadowColor, m_sToggleListShadowShift, m_iToggleListShadowRadius);
			return result;
		}

		CursorType CCoolBar::getCursor()
		{
			if (!m_bLocked && (m_eDownElement == Element::Mover || m_eHoveredElement == Element::Mover))
				return CursorType::SizeAll;
			return CControl::getCursor();
		}

		bool CCoolBar::isAcceptControl()
		{
			return true;
		}

		bool CCoolBar::isAcceptControl(IControl *control)
		{
			return cast<ICoolBar*>(control) != nullptr;
		}

		bool CCoolBar::isAcceptBubbledEvents()
		{
			return true;
		}

		bool CCoolBar::hasExtra()
		{
			return m_bExtraListVisible || m_bToggleListVisible;
		}
	#pragma endregion

	#pragma region IControl setters
		bool CCoolBar::setAlign(const Align value)
		{
			if (value != Align::Client)
				return CControl::setAlign(value);
			return false;
		}

		bool CCoolBar::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sOuterBorderWidth *= s;
				m_sInnerBorderWidth *= s;
				m_sPadding *= s;
				m_sMoverMargin *= s;
				m_sMoverBorderWidth *= s;
				m_sMoverPadding *= s;
				m_sExtraMargin *= s;
				m_sExtraBorderWidth *= s;
				m_sExtraPadding *= s;
				m_fExtraSize *= avg;
				m_sExtraListConstraints *= s;
				m_sExtraListOuterBorderWidth *= s;
				m_sExtraListInnerBorderWidth *= s;
				m_sExtraListPadding *= s;
				m_iExtraListShadowRadius = ntl::Max<int>(1, ntl::Round<int>((float)m_iExtraListShadowRadius * avg));
				m_sExtraListShadowShift *= s;
				m_sExtraListButtonPadding *= s;
				m_sExtraListButtonBorderWidth *= s;
				m_sToggleListConstraints *= s;
				m_sToggleListOuterBorderWidth *= s;
				m_sToggleListInnerBorderWidth *= s;
				m_sToggleListPadding *= s;
				m_iToggleListShadowRadius = ntl::Max<int>(1, ntl::Round<int>((float)m_iToggleListShadowRadius * avg));
				m_sToggleListShadowShift *= s;
				m_fToggleListIconPadding *= avg;
				m_sToggleListElementPadding *= s;
				m_sToggleListElementBorderWidth *= s;
				PostClientAreaChange();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region ICoolBar getters
		ICoolBar::Orientation CCoolBar::getOrientation()
		{
			return m_eOrientation;
		}

		float CCoolBar::getStickDistance()
		{
			return m_fStickDistance;
		}

		bool CCoolBar::isAutoAlign()
		{
			return m_bAutoAlign;
		}

		bool CCoolBar::isLocked()
		{
			return m_bLocked;
		}

		bool CCoolBar::isResizable()
		{
			return m_bResizable;
		}

		ICoolBar::IVisibilityManager *CCoolBar::getVisibilityManager()
		{
			return m_pVisibilityManager;
		}

		PointF CCoolBar::getResizeLimits()
		{
			PointF result{ 0, 0 };
			switch (m_eOrientation)
			{
			case Orientation::LeftToRight:
			case Orientation::RightToLeft:
				result.X = m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left + m_sPadding.Left + m_sPadding.Right + m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Right;
				if (m_bMoverAlwaysVisible || !m_bLocked)
					result.X += m_sMoverMargin.Left + m_sMoverBorderWidth.Left + m_sMoverPadding.Left + CalculateMoverSize() + m_sMoverPadding.Right + m_sMoverBorderWidth.Right + m_sMoverMargin.Right;
				if (m_bExtraAlwaysVisible)
					result.X += m_sExtraMargin.Left + m_sExtraBorderWidth.Left + m_sExtraPadding.Left + m_fExtraSize + m_sExtraPadding.Right + m_sExtraBorderWidth.Right + m_sExtraMargin.Right;
				result.Y = result.X + CalculateRequiredSize();
				break;
			case Orientation::TopToBottom:
			case Orientation::BottomToTop:
				result.X = m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left + m_sPadding.Left + m_sPadding.Right + m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Right;
				if (m_bMoverAlwaysVisible || !m_bLocked)
					result.X += m_sMoverMargin.Left + m_sMoverBorderWidth.Left + m_sMoverPadding.Left + CalculateMoverSize() + m_sMoverPadding.Right + m_sMoverBorderWidth.Right + m_sMoverMargin.Right;
				if (m_bExtraAlwaysVisible)
					result.X += m_sExtraMargin.Left + m_sExtraBorderWidth.Left + m_sExtraPadding.Left + m_fExtraSize + m_sExtraPadding.Right + m_sExtraBorderWidth.Right + m_sExtraMargin.Right;
				result.Y = result.X + CalculateRequiredSize();
				break;
			}
			return result;
		}
	#pragma endregion

	#pragma region ICoolBar setters
		bool CCoolBar::setOrientation(const Orientation value)
		{
			if (value != m_eOrientation)
			{
				CLockRepaint lock{ this };
				m_eOrientation = value;
				PostClientAreaChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setStickDistance(const float value, const float tolerance)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0, tolerance) && ntl::IsNotEqual<float>(value, m_fStickDistance, tolerance))
			{
				m_fStickDistance = value;
				return true;
			}
			return false;
		}

		bool CCoolBar::setAutoAlign(const bool value)
		{
			if (value != m_bAutoAlign)
			{
				m_bAutoAlign = value;
				return true;
			}
			return false;
		}

		bool CCoolBar::setLocked(const bool value)
		{
			if (m_eDownElement != Element::Mover && value != m_bLocked)
			{
				m_bLocked = value;
				return true;
			}
			return false;
		}

		bool CCoolBar::setResizable(const bool value)
		{
			if (value != m_bResizable)
			{
				CLockRepaint lock{ this };
				m_bResizable = value;
				PostClientAreaChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setVisibilityManager(IVisibilityManager *value)
		{
			if (m_eDownElement == Element::None && !m_bExtraListVisible && value != m_pVisibilityManager)
			{
				m_pVisibilityManager = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IDialogBox getters
		Color CCoolBar::getBackgroundColor()
		{
			return m_sBackgroundColor;
		}

		String CCoolBar::getCaption()
		{
			return L"";
		}

		WindowState CCoolBar::getState()
		{
			return WindowState::Normal;
		}

		RectF CCoolBar::getBorderWidth()
		{
			return RectF{ 0, 0, 0, 0 };
		}

		bool CCoolBar::hasCloseBox()
		{
			return false;
		}

		bool CCoolBar::hasMaximizeBox()
		{
			return false;
		}

		bool CCoolBar::hasMinimizeBox()
		{
			return false;
		}

		bool CCoolBar::hasSizeBox()
		{
			return false;
		}

		bool CCoolBar::hasSystemMenu()
		{
			return false;
		}

		bool CCoolBar::hasBorder()
		{
			return false;
		}

		bool CCoolBar::hasCaption()
		{
			return false;
		}

		bool CCoolBar::isPopup()
		{
			return false;
		}
	#pragma endregion

	#pragma region IDialogBox setters
		bool CCoolBar::setBackgroundColor(const Color &value)
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

		bool CCoolBar::setCaption(const String &value)
		{
			return false;
		}

		bool CCoolBar::setClientSize(const Point &value)
		{
			return false;
		}

		bool CCoolBar::setState(const WindowState value)
		{
			return false;
		}

		bool CCoolBar::setBorderWidth(const RectF &value)
		{
			return false;
		}

		bool CCoolBar::setHasCloseBox(const bool value)
		{
			return false;
		}

		bool CCoolBar::setHasMaximizeBox(const bool value)
		{
			return false;
		}

		bool CCoolBar::setHasMinimizeBox(const bool value)
		{
			return false;
		}

		bool CCoolBar::setHasSizeBox(const bool value)
		{
			return false;
		}

		bool CCoolBar::setHasSystemMenu(const bool value)
		{
			return false;
		}

		bool CCoolBar::setHasBorder(const bool value)
		{
			return false;
		}

		bool CCoolBar::setHasCaption(const bool value)
		{
			return false;
		}

		bool CCoolBar::setIsPopup(const bool value)
		{
			return false;
		}
	#pragma endregion

	#pragma region IDialogBox methods
		bool CCoolBar::Hide()
		{
			return false;
		}

		bool CCoolBar::Maximize()
		{
			return false;
		}

		bool CCoolBar::Minimize()
		{
			return false;
		}

		bool CCoolBar::Restore()
		{
			return false;
		}
	#pragma endregion

	#pragma region Getters
		bool CCoolBar::isMoverAlwaysVisible() const
		{
			return m_bMoverAlwaysVisible;
		}

		bool CCoolBar::isExtraAlwaysVisible() const
		{
			return m_bExtraAlwaysVisible;
		}

		CCoolBar::MoverKind CCoolBar::getMoverKind() const
		{
			return m_eMoverKind;
		}

		RectF CCoolBar::getOuterBorderWidth() const
		{
			return m_sOuterBorderWidth;
		}

		BorderColor CCoolBar::getOuterBorderColor() const
		{
			return m_sOuterBorderColor;
		}

		RectF CCoolBar::getInnerBorderWidth() const
		{
			return m_sInnerBorderWidth;
		}

		BorderColor CCoolBar::getInnerBorderColor() const
		{
			return m_sInnerBorderColor;
		}

		RectF CCoolBar::getPadding() const
		{
			return m_sPadding;
		}

		Gradient *CCoolBar::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		RectF CCoolBar::getMoverMargin() const
		{
			return m_sMoverMargin;
		}

		RectF CCoolBar::getMoverBorderWidth() const
		{
			return m_sMoverBorderWidth;
		}

		RectF CCoolBar::getMoverPadding() const
		{
			return m_sMoverPadding;
		}

		BorderColor CCoolBar::getMoverBorderColor(const State state) const
		{
			return m_aMoverBorderColor[(int)state];
		}

		Color CCoolBar::getMoverBackgroundColor(const State state) const
		{
			return m_aMoverBackgroundColor[(int)state];
		}

		Gradient *CCoolBar::getMoverBackgroundGradient(const State state)
		{
			return &m_aMoverBackgroundGradient[(int)state];
		}

		Color CCoolBar::getMoverForeground1Color(const State state) const
		{
			return m_aMoverForeground1Color[(int)state];
		}

		Color CCoolBar::getMoverForeground2Color(const State state) const
		{
			return m_aMoverForeground2Color[(int)state];
		}

		RectF CCoolBar::getExtraMargin() const
		{
			return m_sExtraMargin;
		}

		RectF CCoolBar::getExtraBorderWidth() const
		{
			return m_sExtraBorderWidth;
		}

		RectF CCoolBar::getExtraPadding() const
		{
			return m_sExtraPadding;
		}

		float CCoolBar::getExtraSize() const
		{
			return m_fExtraSize;
		}

		BorderColor CCoolBar::getExtraBorderColor(const State state) const
		{
			return m_aExtraBorderColor[(int)state];
		}

		Color CCoolBar::getExtraBackgroundColor(const State state) const
		{
			return m_aExtraBackgroundColor[(int)state];
		}

		Gradient *CCoolBar::getExtraBackgroundGradient(const State state)
		{
			return &m_aExtraBackgroundGradient[(int)state];
		}

		Color CCoolBar::getExtraColor(const State state) const
		{
			return m_aExtraColor[(int)state];
		}

		PointF CCoolBar::getExtraListConstraints() const
		{
			return m_sExtraListConstraints;
		}

		RectF CCoolBar::getExtraListOuterBorderWidth() const
		{
			return m_sExtraListOuterBorderWidth;
		}

		BorderColor CCoolBar::getExtraListOuterBorderColor() const
		{
			return m_sExtraListOuterBorderColor;
		}

		RectF CCoolBar::getExtraListInnerBorderWidth() const
		{
			return m_sExtraListInnerBorderWidth;
		}

		BorderColor CCoolBar::getExtraListInnerBorderColor() const
		{
			return m_sExtraListInnerBorderColor;
		}

		RectF CCoolBar::getExtraListPadding() const
		{
			return m_sExtraListPadding;
		}

		Color CCoolBar::getExtraListBackgroundColor() const
		{
			return m_sExtraListBackgroundColor;
		}

		Gradient *CCoolBar::getExtraListBackgroundGradient()
		{
			return &m_cExtraListBackgroundGradient;
		}

		int CCoolBar::getExtraListShadowRadius() const
		{
			return m_iExtraListShadowRadius;
		}

		PointF CCoolBar::getExtraListShadowShift() const
		{
			return m_sExtraListShadowShift;
		}

		Color CCoolBar::getExtraListShadowColor() const
		{
			return m_sExtraListShadowColor;
		}

		RectF CCoolBar::getExtraListButtonPadding() const
		{
			return m_sExtraListButtonPadding;
		}

		RectF CCoolBar::getExtraListButtonBorderWidth() const
		{
			return m_sExtraListButtonBorderWidth;
		}

		BorderColor CCoolBar::getExtraListButtonBorderColor(const State state) const
		{
			return m_aExtraListButtonBorderColor[(int)state];
		}

		Color CCoolBar::getExtraListButtonBackgroundColor(const State state) const
		{
			return m_aExtraListButtonBackgroundColor[(int)state];
		}

		Gradient *CCoolBar::getExtraListButtonBackgroundGradient(const State state)
		{
			return &m_aExtraListButtonBackgroundGradient[(int)state];
		}

		Color CCoolBar::getExtraListButtonColor(const State state) const
		{
			return m_aExtraListButtonColor[(int)state];
		}

		PointF CCoolBar::getToggleListConstraints() const
		{
			return m_sToggleListConstraints;
		}

		RectF CCoolBar::getToggleListOuterBorderWidth() const
		{
			return m_sToggleListOuterBorderWidth;
		}

		BorderColor CCoolBar::getToggleListOuterBorderColor() const
		{
			return m_sToggleListOuterBorderColor;
		}

		RectF CCoolBar::getToggleListInnerBorderWidth() const
		{
			return m_sToggleListInnerBorderWidth;
		}

		BorderColor CCoolBar::getToggleListInnerBorderColor() const
		{
			return m_sToggleListInnerBorderColor;
		}

		RectF CCoolBar::getToggleListPadding() const
		{
			return m_sToggleListPadding;
		}

		Color CCoolBar::getToggleListBackgroundColor() const
		{
			return m_sToggleListBackgroundColor;
		}

		Gradient *CCoolBar::getToggleListBackgroundGradient()
		{
			return &m_cToggleListBackgroundGradient;
		}

		int CCoolBar::getToggleListShadowRadius() const
		{
			return m_iToggleListShadowRadius;
		}

		PointF CCoolBar::getToggleListShadowShift() const
		{
			return m_sToggleListShadowShift;
		}

		Color CCoolBar::getToggleListShadowColor() const
		{
			return m_sToggleListShadowColor;
		}

		float CCoolBar::getToggleListIconPadding() const
		{
			return m_fToggleListIconPadding;
		}

		RectF CCoolBar::getToggleListElementPadding() const
		{
			return m_sToggleListElementPadding;
		}

		RectF CCoolBar::getToggleListElementBorderWidth() const
		{
			return m_sToggleListElementBorderWidth;
		}

		BorderColor CCoolBar::getToggleListElementBorderColor(const State state) const
		{
			return m_aToggleListElementBorderColor[(int)state];
		}

		Color CCoolBar::getToggleListElementBackgroundColor(const State state) const
		{
			return m_aToggleListElementBackgroundColor[(int)state];
		}

		Gradient *CCoolBar::getToggleListElementBackgroundGradient(const State state)
		{
			return &m_aToggleListElementBackgroundGradient[(int)state];
		}

		Color CCoolBar::getToggleListElementColor(const State state) const
		{
			return m_aToggleListElementColor[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CCoolBar::setExtraListScroll(IBuiltInScroll *value)
		{
			if (!value || (value && value != m_pExtraListScroll && value != m_pToggleListScroll))
			{
				if (m_pExtraListScroll)
					m_pExtraListScroll->Release();
				m_pExtraListScroll = value;
				if (m_pExtraListScroll)
				{
					if (!m_pExtraListScroll->isVertical())
					{
						CBuiltInScroll *scroll{ cast<CBuiltInScroll*>(m_pExtraListScroll) };
						if (scroll)
							scroll->SwitchDirection(true);
						else
						{
							m_pExtraListScroll->setVertical(true);
							m_pExtraListScroll->setSize(PointF{ m_pExtraListScroll->getHeight(), m_pExtraListScroll->getWidth() });
						}
					}
				}
				if (m_bExtraListVisible)
				{
					CLockRepaint lock{ this };
					Repaint(false);
					PostExtraListChange();
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListScroll(IBuiltInScroll *value)
		{
			if (!value || (value && value != m_pToggleListScroll && value != m_pExtraListScroll))
			{
				if (m_pToggleListScroll)
					m_pToggleListScroll->Release();
				m_pToggleListScroll = value;
				if (m_pToggleListScroll)
				{
					if (!m_pToggleListScroll->isVertical())
					{
						CBuiltInScroll *scroll{ cast<CBuiltInScroll*>(m_pToggleListScroll) };
						if (scroll)
							scroll->SwitchDirection(true);
						else
						{
							m_pToggleListScroll->setVertical(true);
							m_pToggleListScroll->setSize(PointF{ m_pToggleListScroll->getHeight(), m_pToggleListScroll->getWidth() });
						}
					}
				}
				if (m_bToggleListVisible)
				{
					CLockRepaint lock{ this };
					Repaint(false);
					PostToggleListChange();
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setMoverAlwaysVisible(const bool value)
		{
			if (value != m_bMoverAlwaysVisible)
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_bMoverAlwaysVisible = value;
				PostClientAreaChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraAlwaysVisible(const bool value)
		{
			if (value != m_bExtraAlwaysVisible)
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_bExtraAlwaysVisible = value;
				PostClientAreaChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setMoverKind(const MoverKind value)
		{
			if (value != m_eMoverKind)
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_eMoverKind = value;
				PostClientAreaChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setOuterBorderWidth(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sOuterBorderWidth, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_sOuterBorderWidth = value;
				PostClientAreaChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setOuterBorderColor(const BorderColor &value)
		{
			if (value != m_sOuterBorderColor)
			{
				m_sOuterBorderColor = value;
				if (m_sOuterBorderWidth.has_positive())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setInnerBorderWidth(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sInnerBorderWidth, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_sInnerBorderWidth = value;
				PostClientAreaChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setInnerBorderColor(const BorderColor &value)
		{
			if (value != m_sInnerBorderColor)
			{
				m_sInnerBorderColor = value;
				if (m_sInnerBorderWidth.has_positive())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setPadding(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sPadding, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_sPadding = value;
				PostClientAreaChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setMoverMargin(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sMoverMargin, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_sMoverMargin = value;
				PostClientAreaChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setMoverBorderWidth(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sMoverBorderWidth, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_sMoverBorderWidth = value;
				PostClientAreaChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setMoverPadding(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sMoverPadding, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_sMoverPadding = value;
				PostClientAreaChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setMoverBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aMoverBorderColor[(int)state])
			{
				m_aMoverBorderColor[(int)state] = value;
				if (CalculateMoverState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setMoverBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aMoverBackgroundColor[(int)state])
			{
				m_aMoverBackgroundColor[(int)state] = value;
				if (CalculateMoverState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setMoverForeground1Color(const State state, const Color &value)
		{
			if (value != m_aMoverForeground1Color[(int)state])
			{
				m_aMoverForeground1Color[(int)state] = value;
				if (CalculateMoverState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setMoverForeground2Color(const State state, const Color &value)
		{
			if (value != m_aMoverForeground2Color[(int)state])
			{
				m_aMoverForeground2Color[(int)state] = value;
				if (CalculateMoverState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraMargin(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sExtraMargin, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_sExtraMargin = value;
				PostClientAreaChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraBorderWidth(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sExtraBorderWidth, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_sExtraBorderWidth = value;
				PostClientAreaChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraPadding(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sExtraPadding, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_sExtraPadding = value;
				PostClientAreaChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraSize(const float value, const float tolerance)
		{
			if (ntl::IsNotNegative<float>(value, tolerance) && ntl::IsNotEqual<float>(value, m_fExtraSize, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_fExtraSize = value;
				PostClientAreaChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aExtraBorderColor[(int)state])
			{
				m_aExtraBorderColor[(int)state] = value;
				if (CalculateExtraState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aExtraBackgroundColor[(int)state])
			{
				m_aExtraBackgroundColor[(int)state] = value;
				if (CalculateExtraState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraColor(const State state, const Color &value)
		{
			if (value != m_aExtraColor[(int)state])
			{
				m_aExtraColor[(int)state] = value;
				if (CalculateExtraState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraListConstraints(const PointF &value, const float tolerance)
		{
			if (ntl::IsNotNegative<float>(value.X, tolerance) && ntl::IsNotNegative<float>(value.Y, tolerance) && IsNotEqual(value, m_sExtraListConstraints, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_sExtraListConstraints = value;
				PostExtraListChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraListOuterBorderWidth(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sExtraListOuterBorderWidth, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_sExtraListOuterBorderWidth = value;
				PostExtraListChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraListOuterBorderColor(const BorderColor &value)
		{
			if (value != m_sExtraListOuterBorderColor)
			{
				m_sExtraListOuterBorderColor = value;
				if (m_bExtraListVisible)
				{
					if (m_pCanvasExtraList)
						m_pCanvasExtraList->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraListInnerBorderWidth(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sExtraListInnerBorderWidth, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_sExtraListInnerBorderWidth = value;
				PostExtraListChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraListInnerBorderColor(const BorderColor &value)
		{
			if (value != m_sExtraListInnerBorderColor)
			{
				m_sExtraListInnerBorderColor = value;
				if (m_bExtraListVisible)
				{
					if (m_pCanvasExtraList)
						m_pCanvasExtraList->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraListPadding(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sExtraListPadding, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_sExtraListPadding = value;
				PostExtraListChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraListBackgroundColor(const Color &value)
		{
			if (value != m_sExtraListBackgroundColor)
			{
				m_sExtraListBackgroundColor = value;
				if (m_bExtraListVisible)
				{
					if (m_pCanvasExtraList)
						m_pCanvasExtraList->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraListShadowRadius(const int value)
		{
			if (value > 0 && value != m_iExtraListShadowRadius)
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
				{
					if (m_pCanvasExtraList)
						m_pCanvasExtraList->setValid(false);
					if (m_sExtraListShadowColor.A > 0)
						Repaint(false);
					m_iExtraListShadowRadius = value;
					if (m_sExtraListShadowColor.A > 0)
						Repaint(false);
				}
				else
					m_iExtraListShadowRadius = value;
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraListShadowShift(const PointF &value, const float tolerance)
		{
			if (IsNotEqual(value, m_sExtraListShadowShift, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
				{
					if (m_pCanvasExtraList)
						m_pCanvasExtraList->setValid(false);
					if (m_sExtraListShadowColor.A > 0)
						Repaint(false);
					m_sExtraListShadowShift = value;
					if (m_sExtraListShadowColor.A > 0)
						Repaint(false);
				}
				else
					m_sExtraListShadowShift = value;
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraListShadowColor(const Color &value)
		{
			if (value != m_sExtraListShadowColor)
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
				{
					if (m_pCanvasExtraList)
						m_pCanvasExtraList->setValid(false);
					if (m_sExtraListShadowColor.A > 0)
						Repaint(false);
					m_sExtraListShadowColor = value;
					if (m_sExtraListShadowColor.A > 0)
						Repaint(false);
				}
				else
					m_sExtraListShadowColor = value;
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraListButtonPadding(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sExtraListButtonPadding, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_sExtraListButtonPadding = value;
				PostExtraListChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraListButtonBorderWidth(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sExtraListButtonBorderWidth, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bExtraListVisible)
					Repaint(false);
				m_sExtraListButtonBorderWidth = value;
				PostExtraListChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraListButtonBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aExtraListButtonBorderColor[(int)state])
			{
				m_aExtraListButtonBorderColor[(int)state] = value;
				if (m_bExtraListVisible && m_pVisibilityManager && m_sExtraListButtonBorderWidth.has_positive() && state == CalculateExtraListButtonState())
				{
					if (m_pCanvasExtraList)
						m_pCanvasExtraList->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraListButtonBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aExtraListButtonBackgroundColor[(int)state])
			{
				m_aExtraListButtonBackgroundColor[(int)state] = value;
				if (m_bExtraListVisible && m_pVisibilityManager)
				{
					if (m_pCanvasExtraList)
						m_pCanvasExtraList->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setExtraListButtonColor(const State state, const Color &value)
		{
			if (value != m_aExtraListButtonColor[(int)state])
			{
				m_aExtraListButtonColor[(int)state] = value;
				if (m_bExtraListVisible && m_pVisibilityManager)
				{
					if (m_pCanvasExtraList)
						m_pCanvasExtraList->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListConstraints(const PointF &value, const float tolerance)
		{
			if (ntl::IsNotNegative<float>(value.X, tolerance) && ntl::IsNotNegative<float>(value.Y, tolerance) && IsNotEqual(value, m_sToggleListConstraints, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bToggleListVisible)
					Repaint(false);
				m_sToggleListConstraints = value;
				PostToggleListChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListOuterBorderWidth(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sToggleListOuterBorderWidth, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bToggleListVisible)
					Repaint(false);
				m_sToggleListOuterBorderWidth = value;
				PostToggleListChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListOuterBorderColor(const BorderColor &value)
		{
			if (value != m_sToggleListOuterBorderColor)
			{
				m_sToggleListOuterBorderColor = value;
				if (m_bToggleListVisible)
				{
					if (m_pCanvasToggleList)
						m_pCanvasToggleList->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListInnerBorderWidth(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sToggleListInnerBorderWidth, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bToggleListVisible)
					Repaint(false);
				m_sToggleListInnerBorderWidth = value;
				PostToggleListChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListInnerBorderColor(const BorderColor &value)
		{
			if (value != m_sToggleListInnerBorderColor)
			{
				m_sToggleListInnerBorderColor = value;
				if (m_bToggleListVisible)
				{
					if (m_pCanvasToggleList)
						m_pCanvasToggleList->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListPadding(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sToggleListPadding, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bToggleListVisible)
					Repaint(false);
				m_sToggleListPadding = value;
				PostToggleListChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListBackgroundColor(const Color &value)
		{
			if (value != m_sToggleListBackgroundColor)
			{
				m_sToggleListBackgroundColor = value;
				if (m_bToggleListVisible)
				{
					if (m_pCanvasToggleList)
						m_pCanvasToggleList->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListShadowRadius(const int value)
		{
			if (value > 0 && value != m_iToggleListShadowRadius)
			{
				CLockRepaint lock{ this };
				if (m_bToggleListVisible)
				{
					if (m_pCanvasToggleList)
						m_pCanvasToggleList->setValid(false);
					if (m_sToggleListShadowColor.A > 0)
						Repaint(false);
					m_iToggleListShadowRadius = value;
					if (m_sToggleListShadowColor.A > 0)
						Repaint(false);
				}
				else
					m_iToggleListShadowRadius = value;
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListShadowShift(const PointF &value, const float tolerance)
		{
			if (IsNotEqual(value, m_sToggleListShadowShift, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bToggleListVisible)
				{
					if (m_pCanvasToggleList)
						m_pCanvasToggleList->setValid(false);
					if (m_sToggleListShadowColor.A > 0)
						Repaint(false);
					m_sToggleListShadowShift = value;
					if (m_sToggleListShadowColor.A > 0)
						Repaint(false);
				}
				else
					m_sToggleListShadowShift = value;
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListShadowColor(const Color &value)
		{
			if (value != m_sToggleListShadowColor)
			{
				CLockRepaint lock{ this };
				if (m_bToggleListVisible)
				{
					if (m_pCanvasToggleList)
						m_pCanvasToggleList->setValid(false);
					if (m_sToggleListShadowColor.A > 0)
						Repaint(false);
					m_sToggleListShadowColor = value;
					if (m_sToggleListShadowColor.A > 0)
						Repaint(false);
				}
				else
					m_sToggleListShadowColor = value;
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListIconPadding(const float value, const float tolerance)
		{
			if (ntl::IsGreaterOrEqual<float>(value, tolerance) && ntl::IsNotEqual<float>(value, m_fToggleListIconPadding, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bToggleListVisible)
					Repaint(false);
				m_fToggleListIconPadding = value;
				PostToggleListChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListElementPadding(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sToggleListElementPadding, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bToggleListVisible)
					Repaint(false);
				m_sToggleListElementPadding = value;
				PostToggleListChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListElementBorderWidth(const RectF &value, const float tolerance)
		{
			if (!value.has_negative(tolerance) && IsNotEqual(value, m_sToggleListElementBorderWidth, tolerance))
			{
				CLockRepaint lock{ this };
				if (m_bToggleListVisible)
					Repaint(false);
				m_sToggleListElementBorderWidth = value;
				PostToggleListChange();
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListElementBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aToggleListElementBorderColor[(int)state])
			{
				m_aToggleListElementBorderColor[(int)state] = value;
				if (m_bToggleListVisible)
				{
					if (m_pCanvasToggleList)
						m_pCanvasToggleList->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListElementBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aToggleListElementBackgroundColor[(int)state])
			{
				m_aToggleListElementBackgroundColor[(int)state] = value;
				if (m_bToggleListVisible)
				{
					if (m_pCanvasToggleList)
						m_pCanvasToggleList->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::setToggleListElementColor(const State state, const Color &value)
		{
			if (value != m_aToggleListElementColor[(int)state])
			{
				m_aToggleListElementColor[(int)state] = value;
				if (m_bToggleListVisible)
				{
					if (m_pCanvasToggleList)
						m_pCanvasToggleList->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		float CCoolBar::CalculateMoverSize() const
		{
			switch (m_eMoverKind)
			{
			case MoverKind::Line: // line - 2
				return 2;
			case MoverKind::DoubleLine: // line - 2, space - 1, line - 2
				return 5;
			case MoverKind::Dots: // dots - 2
				return 2;
			case MoverKind::TripleDots: // dots - 1, space - 1, dots - 1, space - 1, dots - 1
				return 5;
			default: // space - 2
				return 2;
			}
		}

		float CCoolBar::CalculateRequiredSize()
		{
			float result{ 0 };
			int count{ getControlCount() };
			IControl *control;
			switch (m_eOrientation)
			{
			case Orientation::LeftToRight:
			case Orientation::RightToLeft:
				for (int i = 0; i < count; i++)
				{
					control = getControl(i);
					if (m_pVisibilityManager && !m_pVisibilityManager->isVisible(control, i))
						continue;
					result += AdjustByConstraints(control->QueryService()->getSizeRequested(), control->getConstraints()).X;
				}
				break;
			case Orientation::TopToBottom:
			case Orientation::BottomToTop:
				for (int i = 0; i < count; i++)
				{
					control = getControl(i);
					if (m_pVisibilityManager && !m_pVisibilityManager->isVisible(control, i))
						continue;
					result += AdjustByConstraints(control->QueryService()->getSizeRequested(), control->getConstraints()).Y;
				}
				break;
			}
			return result;
		}

		RectF CCoolBar::CalculateClientRect(bool &show_extra, bool &has_extra_controls)
		{
			RectF result{ getRect() };
			float required_size{ CalculateRequiredSize() };
			switch (m_eOrientation)
			{
			case Orientation::LeftToRight:
				result.Left += m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left + m_sPadding.Left;
				result.Top += m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top + m_sPadding.Top;
				result.Right -= m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Right + m_sPadding.Right;
				result.Bottom -= m_sOuterBorderWidth.Bottom + m_sInnerBorderWidth.Bottom + m_sPadding.Bottom;
				if (m_bMoverAlwaysVisible || !m_bLocked)
					result.Left += m_sMoverMargin.Left + m_sMoverMargin.Right + m_sMoverBorderWidth.Left + m_sMoverBorderWidth.Right + m_sMoverPadding.Left + m_sMoverPadding.Right + CalculateMoverSize();
				if (m_bExtraAlwaysVisible || result.width() < required_size)
				{
					result.Right -= m_sExtraMargin.Left + m_sExtraMargin.Right + m_sExtraBorderWidth.Left + m_sExtraBorderWidth.Right + m_sExtraPadding.Left + m_sExtraPadding.Right + m_fExtraSize;
					show_extra = true;
				}
				else
					show_extra = m_pVisibilityManager != nullptr;
				has_extra_controls = show_extra && (result.width() < required_size);
				break;
			case Orientation::TopToBottom:
				result.Top += m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left + m_sPadding.Left;
				result.Right -= m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top + m_sPadding.Top;
				result.Bottom -= m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Right + m_sPadding.Right;
				result.Left += m_sOuterBorderWidth.Bottom + m_sInnerBorderWidth.Bottom + m_sPadding.Bottom;
				if (m_bMoverAlwaysVisible || !m_bLocked)
					result.Top += m_sMoverMargin.Left + m_sMoverMargin.Right + m_sMoverBorderWidth.Left + m_sMoverBorderWidth.Right + m_sMoverPadding.Left + m_sMoverPadding.Right + CalculateMoverSize();
				if (m_bExtraAlwaysVisible || result.height() < required_size)
				{
					result.Bottom -= m_sExtraMargin.Left + m_sExtraMargin.Right + m_sExtraBorderWidth.Left + m_sExtraBorderWidth.Right + m_sExtraPadding.Left + m_sExtraPadding.Right + m_fExtraSize;
					show_extra = true;
				}
				else
					show_extra = m_pVisibilityManager != nullptr;
				has_extra_controls = show_extra && (result.height() < required_size);
				break;
			case Orientation::RightToLeft:
				result.Right -= m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left + m_sPadding.Left;
				result.Top += m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top + m_sPadding.Top;
				result.Left += m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Right + m_sPadding.Right;
				result.Bottom -= m_sOuterBorderWidth.Bottom + m_sInnerBorderWidth.Bottom + m_sPadding.Bottom;
				if (m_bMoverAlwaysVisible || !m_bLocked)
					result.Right -= m_sMoverMargin.Left + m_sMoverMargin.Right + m_sMoverBorderWidth.Left + m_sMoverBorderWidth.Right + m_sMoverPadding.Left + m_sMoverPadding.Right + CalculateMoverSize();
				if (m_bExtraAlwaysVisible || result.width() < required_size)
				{
					result.Left += m_sExtraMargin.Left + m_sExtraMargin.Right + m_sExtraBorderWidth.Left + m_sExtraBorderWidth.Right + m_sExtraPadding.Left + m_sExtraPadding.Right + m_fExtraSize;
					show_extra = true;
				}
				else
					show_extra = m_pVisibilityManager != nullptr;
				has_extra_controls = show_extra && (result.width() < required_size);
				break;
			case Orientation::BottomToTop:
				result.Bottom -= m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left + m_sPadding.Left;
				result.Left += m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top + m_sPadding.Top;
				result.Top += m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Right + m_sPadding.Right;
				result.Right -= m_sOuterBorderWidth.Bottom + m_sInnerBorderWidth.Bottom + m_sPadding.Bottom;
				if (m_bMoverAlwaysVisible || !m_bLocked)
					result.Bottom -= m_sMoverMargin.Left + m_sMoverMargin.Right + m_sMoverBorderWidth.Left + m_sMoverBorderWidth.Right + m_sMoverPadding.Left + m_sMoverPadding.Right + CalculateMoverSize();
				if (m_bExtraAlwaysVisible || result.height() < required_size)
				{
					result.Top += m_sExtraMargin.Left + m_sExtraMargin.Right + m_sExtraBorderWidth.Left + m_sExtraBorderWidth.Right + m_sExtraPadding.Left + m_sExtraPadding.Right + m_fExtraSize;
					show_extra = true;
				}
				else
					show_extra = m_pVisibilityManager != nullptr;
				has_extra_controls = show_extra && (result.height() < required_size);
				break;
			}
			result.validate();
			return result;
		}

		RectF CCoolBar::CalculateMoverRect()
		{
			RectF rect{ getRect() }, client{ rect }, result{ 0, 0, 0, 0 };
			switch (m_eOrientation)
			{
			case Orientation::LeftToRight:
				client.Left += m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left;
				client.Top += m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top;
				client.Right -= m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Right;
				client.Bottom -= m_sOuterBorderWidth.Bottom + m_sInnerBorderWidth.Bottom;
				if (client.has_area())
				{
					result = client;
					result.Left += m_sMoverMargin.Left;
					result.Top += m_sMoverMargin.Top;
					result.Right = result.Left + m_sMoverBorderWidth.Left + m_sMoverPadding.Left + CalculateMoverSize() + m_sMoverPadding.Right + m_sMoverBorderWidth.Right;
					result.Bottom -= m_sMoverMargin.Bottom;
					result *= client;
				}
				break;
			case Orientation::TopToBottom:
				client.Top += m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left;
				client.Right -= m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top;
				client.Bottom -= m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Right;
				client.Left += m_sOuterBorderWidth.Bottom + m_sInnerBorderWidth.Bottom;
				if (client.has_area())
				{
					result = client;
					result.Top += m_sMoverMargin.Left;
					result.Right -= m_sMoverMargin.Top;
					result.Bottom = result.Top + m_sMoverBorderWidth.Left + m_sMoverPadding.Left + CalculateMoverSize() + m_sMoverPadding.Right + m_sMoverBorderWidth.Right;
					result.Left += m_sMoverMargin.Bottom;
					result *= client;
				}
				break;
			case Orientation::RightToLeft:
				client.Right -= m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left;
				client.Top += m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top;
				client.Left += m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Right;
				client.Bottom -= m_sOuterBorderWidth.Bottom + m_sInnerBorderWidth.Bottom;
				if (client.has_area())
				{
					result = client;
					result.Right -= m_sMoverMargin.Left;
					result.Top += m_sMoverMargin.Top;
					result.Left = result.Right - m_sMoverBorderWidth.Left - m_sMoverPadding.Left - CalculateMoverSize() - m_sMoverPadding.Right - m_sMoverBorderWidth.Right;
					result.Bottom -= m_sMoverMargin.Bottom;
					result *= client;
				}
				break;
			case Orientation::BottomToTop:
				client.Bottom -= m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left;
				client.Left += m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top;
				client.Top += m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Right;
				client.Right -= m_sOuterBorderWidth.Bottom + m_sInnerBorderWidth.Bottom;
				if (client.has_area())
				{
					result = client;
					result.Bottom -= m_sMoverMargin.Left;
					result.Left += m_sMoverMargin.Top;
					result.Top = result.Bottom - m_sMoverBorderWidth.Left - m_sMoverPadding.Left - CalculateMoverSize() - m_sMoverPadding.Right - m_sMoverBorderWidth.Right;
					result.Right -= m_sMoverMargin.Bottom;
					result *= client;
				}
				break;
			}
			result.validate();
			return result;
		}

		RectF CCoolBar::CalculateMoverInnerRect(const RectF &total) // inner is total - border
		{
			RectF result{ total };
			switch (m_eOrientation)
			{
			case Orientation::LeftToRight:
				result.Left += m_sMoverBorderWidth.Left + m_sMoverPadding.Left;
				result.Top += m_sMoverBorderWidth.Top + m_sMoverPadding.Top;
				result.Right -= m_sMoverBorderWidth.Right + m_sMoverPadding.Right;
				result.Bottom -= m_sMoverBorderWidth.Bottom + m_sMoverPadding.Bottom;
				break;
			case Orientation::TopToBottom:
				result.Top += m_sMoverBorderWidth.Left + m_sMoverPadding.Left;
				result.Right -= m_sMoverBorderWidth.Top + m_sMoverPadding.Top;
				result.Bottom -= m_sMoverBorderWidth.Right + m_sMoverPadding.Right;
				result.Left += m_sMoverBorderWidth.Bottom + m_sMoverPadding.Bottom;
				break;
			case Orientation::RightToLeft:
				result.Right -= m_sMoverBorderWidth.Left + m_sMoverPadding.Left;
				result.Top += m_sMoverBorderWidth.Top + m_sMoverPadding.Top;
				result.Left += m_sMoverBorderWidth.Right + m_sMoverPadding.Right;
				result.Bottom -= m_sMoverBorderWidth.Bottom + m_sMoverPadding.Bottom;
				break;
			case Orientation::BottomToTop:
				result.Bottom -= m_sMoverBorderWidth.Left + m_sMoverPadding.Left;
				result.Left += m_sMoverBorderWidth.Top + m_sMoverPadding.Top;
				result.Top += m_sMoverBorderWidth.Right + m_sMoverPadding.Right;
				result.Right -= m_sMoverBorderWidth.Bottom + m_sMoverPadding.Bottom;
				break;
			}
			return result;
		}

		RectF CCoolBar::CalculateExtraRect()
		{
			RectF rect{ getRect() }, client{ rect }, result{ 0, 0, 0, 0 };
			switch (m_eOrientation)
			{
			case Orientation::LeftToRight:
				client.Left += m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left;
				client.Top += m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top;
				client.Right -= m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Right;
				client.Bottom -= m_sOuterBorderWidth.Bottom + m_sInnerBorderWidth.Bottom;
				if (client.has_area())
				{
					result.Left = client.Right - m_sExtraMargin.Right - m_sExtraBorderWidth.Right - m_sExtraPadding.Right - m_fExtraSize - m_sExtraPadding.Left - m_sExtraBorderWidth.Left;
					result.Top = client.Top + m_sExtraMargin.Top;
					result.Right = client.Right - m_sExtraMargin.Right;
					result.Bottom = client.Bottom - m_sExtraMargin.Bottom;
					result *= client;
				}
				break;
			case Orientation::TopToBottom:
				client.Top += m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left;
				client.Right -= m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top;
				client.Bottom -= m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Right;
				client.Left += m_sOuterBorderWidth.Bottom + m_sInnerBorderWidth.Bottom;
				if (client.has_area())
				{
					result.Top = client.Bottom - m_sExtraMargin.Right - m_sExtraBorderWidth.Right - m_sExtraPadding.Right - m_fExtraSize - m_sExtraPadding.Left - m_sExtraBorderWidth.Left;
					result.Right = client.Right - m_sExtraMargin.Top;
					result.Bottom = client.Bottom - m_sExtraMargin.Right;
					result.Left = client.Left + m_sExtraMargin.Bottom;
					result *= client;
				}
				break;
			case Orientation::RightToLeft:
				client.Right -= m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left;
				client.Top += m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top;
				client.Left += m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Right;
				client.Bottom -= m_sOuterBorderWidth.Bottom + m_sInnerBorderWidth.Bottom;
				if (client.has_area())
				{
					result.Right = client.Left + m_sExtraMargin.Right + m_sExtraBorderWidth.Right + m_sExtraPadding.Right + m_fExtraSize + m_sExtraPadding.Left + m_sExtraBorderWidth.Left;
					result.Top = client.Top + m_sExtraMargin.Top;
					result.Left = client.Left + m_sExtraMargin.Right;
					result.Bottom = client.Bottom - m_sExtraMargin.Bottom;
					result *= client;
				}
				break;
			case Orientation::BottomToTop:
				client.Bottom -= m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left;
				client.Left += m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top;
				client.Top += m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Right;
				client.Right -= m_sOuterBorderWidth.Bottom + m_sInnerBorderWidth.Bottom;
				if (client.has_area())
				{
					result.Bottom = client.Top + m_sExtraMargin.Right + m_sExtraBorderWidth.Right + m_sExtraPadding.Right + m_fExtraSize + m_sExtraPadding.Left + m_sExtraBorderWidth.Left;
					result.Left = client.Left + m_sExtraMargin.Top;
					result.Top = client.Top + m_sExtraMargin.Right;
					result.Right = client.Right - m_sExtraMargin.Bottom;
					result *= client;
				}
				break;
			}
			result.validate();
			return result;
		}

		RectF CCoolBar::CalculateToggleListClientRect(const RectF &rect) const
		{
			RectF result{
				rect.Left + m_sToggleListOuterBorderWidth.Left + m_sToggleListInnerBorderWidth.Left + m_sToggleListPadding.Left,
				rect.Top + m_sToggleListOuterBorderWidth.Top + m_sToggleListInnerBorderWidth.Top + m_sToggleListPadding.Top,
				rect.Right - m_sToggleListOuterBorderWidth.Right - m_sToggleListInnerBorderWidth.Right - m_sToggleListPadding.Right,
				rect.Bottom - m_sToggleListOuterBorderWidth.Bottom - m_sToggleListInnerBorderWidth.Bottom - m_sToggleListPadding.Bottom
			};
			result.validate();
			return result;
		}

		CCoolBar::Element CCoolBar::getElement(const PointF &pos, int &index)
		{
			if (m_bToggleListVisible && m_sToggleListRect.is_inside(pos))
			{
				if (m_bToggleListScrollVisible && m_pToggleListScroll->isInside(pos))
					return Element::ToggleListScroll;
				if (m_sToggleListClientRect.is_inside(pos))
				{
					float y{ pos.Y - m_sToggleListClientRect.Top + (m_bToggleListScrollVisible ? m_pToggleListScroll->getScroll() : 0) };
					if (y >= 0 && y < m_fToggleListElementHeight * (float)getControlCount())
					{
						index = int(y / m_fToggleListElementHeight);
						return Element::ToggleListElement;
					}
				}
				return Element::ToggleList;
			}
			if (m_bExtraListVisible && m_sExtraListRect.is_inside(pos))
			{
				if (m_bExtraListScrollVisible && m_pExtraListScroll->isInside(pos))
					return Element::ExtraListScroll;
				if (m_pVisibilityManager && m_sExtraListButtonRect.is_inside(pos))
					return Element::ExtraListButton;
				return Element::ExtraList;
			}
			if (m_bMoverAlwaysVisible || !m_bLocked)
			{
				if (CalculateMoverRect().is_inside(pos))
					return Element::Mover;
			}
			bool show_extra, has_extra_controls;
			CalculateClientRect(show_extra, has_extra_controls);
			if (show_extra)
			{
				if (CalculateExtraRect().is_inside(pos))
					return Element::Extra;
			}
			return Element::None;
		}

		IBuiltInScroll *CCoolBar::getExtraListScroll()
		{
			if (!m_pExtraListScroll)
			{
				CScroll *scroll{ new CScroll(this) };
				m_pExtraListScroll = scroll;
				if (!scroll->isVertical())
					scroll->SwitchDirection(true);
				scroll->setListener(&m_cExtraListScrollListener);
			}
			return m_pExtraListScroll;
		}

		IBuiltInScroll *CCoolBar::getToggleListScroll()
		{
			if (!m_pToggleListScroll)
			{
				CScroll *scroll{ new CScroll(this) };
				m_pToggleListScroll = scroll;
				if (!scroll->isVertical())
					scroll->SwitchDirection(true);
				scroll->setListener(&m_cToggleListScrollListener);
			}
			return m_pToggleListScroll;
		}

		Gradient CCoolBar::CalculateGradient(const Gradient &gradient) const
		{
			Gradient result{ gradient };
			switch (m_eOrientation)
			{
			case Orientation::TopToBottom:
				switch (result.Type)
				{
				case GradientType::DiagonalUp:
					result.setType(GradientType::DiagonalDown);
					break;
				case GradientType::DiagonalDown:
					result.setType(GradientType::DiagonalUp);
					result.Reverse();
					break;
				case GradientType::Horizontal:
					result.setType(GradientType::Vertical);
					break;
				case GradientType::Vertical:
					result.setType(GradientType::Horizontal);
					result.Reverse();
					break;
				default:
					break;
				}
				break;
			case Orientation::RightToLeft:
				switch (result.Type)
				{
				case GradientType::DiagonalUp:
					result.setType(GradientType::DiagonalDown);
					result.Reverse();
					break;
				case GradientType::DiagonalDown:
					result.setType(GradientType::DiagonalUp);
					result.Reverse();
					break;
				case GradientType::Horizontal:
					result.Reverse();
					break;
				case GradientType::Vertical:
					result.Reverse();
					break;
				default:
					break;
				}
				break;
			case Orientation::BottomToTop:
				switch (result.Type)
				{
				case GradientType::DiagonalUp:
					result.setType(GradientType::DiagonalDown);
					result.Reverse();
					break;
				case GradientType::DiagonalDown:
					result.setType(GradientType::DiagonalUp);
					break;
				case GradientType::Horizontal:
					result.setType(GradientType::Vertical);
					result.Reverse();
					break;
				case GradientType::Vertical:
					result.setType(GradientType::Horizontal);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			return result;
		}

		CCoolBar::State CCoolBar::CalculateMoverState()
		{
			if (m_bLocked || !isEnabled(false))
				return State::Disabled;
			if (m_eDownElement == Element::Mover)
				return State::Down;
			if (m_eHoveredElement == Element::Mover)
				return State::Hovered;
			return State::Normal;
		}

		CCoolBar::State CCoolBar::CalculateExtraState()
		{
			if ((!m_pVisibilityManager && !m_bHasExtraControls) || !isEnabled(false))
				return State::Disabled;
			if (m_eDownElement == Element::Extra || m_bExtraListVisible)
				return State::Down;
			if (m_eHoveredElement == Element::Extra)
				return State::Hovered;
			return State::Normal;
		}

		CCoolBar::State CCoolBar::CalculateExtraListButtonState()
		{
			if (m_eDownElement == Element::ExtraListButton || m_bToggleListVisible)
				return State::Down;
			if (m_eHoveredElement == Element::ExtraListButton)
				return State::Hovered;
			return State::Normal;
		}

		CCoolBar::State CCoolBar::CalculateToggleListElementState(IControl *control, const int index)
		{
			if (!m_pVisibilityManager->isTogglable(control, index))
				return State::Disabled;
			if (m_eDownElement == Element::ToggleListElement && m_iDownElementIndex == index)
				return State::Down;
			if (m_eHoveredElement == Element::ToggleListElement && m_iHoveredElementIndex == index)
				return State::Hovered;
			return State::Normal;
		}

		ITexture *CCoolBar::FindDefaultIcon(RectF &part)
		{
			String name{ m_sClassName };
			IStyle *style{ getStyle() };
			if (style)
			{
				IStyleSkin *skin{ style->getSkin(name) };
				if (skin)
				{
					part = skin->Rect;
					return getForm()->getRenderer()->CreateTextureFromImage(skin->getImage()->Image, 1, TextureFormat::RGBA, true);
				}
			}
			if (style != Application->Styles->getStyle(0) && (style = Application->Styles->getStyle(0)))
			{
				IStyleSkin *skin{ style->getSkin(name) };
				if (skin)
				{
					part = skin->Rect;
					return getForm()->getRenderer()->CreateTextureFromImage(skin->getImage()->Image, 1, TextureFormat::RGBA, true);
				}
			}
			part = RectF{ 0, 0, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT };
			return getForm()->getRenderer()->CreateTextureFromImage(DEFAULT_ICON, 1, TextureFormat::RGBA, true);
		}

		ITexture *CCoolBar::FindCheckboxIcon(const bool checked, const State state, RectF &part)
		{
			String name{ m_sClassName };
			name += checked ? L".Checked" : L".Unchecked";
			switch (state)
			{
			case State::Down:
				name += L".Down";
				break;
			case State::Hovered:
				name += L".Hovered";
				break;
			case State::Disabled:
				name += L".Disabled";
				break;
			default:
				break;
			}
			IStyle *style{ getStyle() };
			if (style)
			{
				IStyleSkin *skin{ style->getSkin(name) };
				if (skin)
				{
					part = skin->Rect;
					return getForm()->getRenderer()->CreateTextureFromImage(skin->getImage()->Image, 1, TextureFormat::RGBA, true);
				}
			}
			if (style != Application->Styles->getStyle(0) && (style = Application->Styles->getStyle(0)))
			{
				IStyleSkin *skin{ style->getSkin(name) };
				if (skin)
				{
					part = skin->Rect;
					return getForm()->getRenderer()->CreateTextureFromImage(skin->getImage()->Image, 1, TextureFormat::RGBA, true);
				}
			}
			return nullptr;
		}

		bool CCoolBar::UpdateHoveredElement()
		{
			if (getForm())
				return UpdateHoveredElement(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())));
			return false;
		}

		bool CCoolBar::UpdateHoveredElement(const PointF &pos)
		{
			int index{ -1 };
			Element e{ getElement(pos, index) };
			if (e != m_eHoveredElement || (e == Element::ToggleListElement && index != m_iHoveredElementIndex))
			{
				if (e != m_eHoveredElement)
				{
					switch (m_eHoveredElement)
					{
					case Element::ExtraListScroll:
						m_pExtraListScroll->NotifyOnMouseLeave();
						break;
					case Element::ToggleListScroll:
						m_pToggleListScroll->NotifyOnMouseLeave();
						break;
					default:
						break;
					}
					m_eHoveredElement = e;
					switch (m_eHoveredElement)
					{
					case Element::ExtraListScroll:
						m_pExtraListScroll->NotifyOnMouseHover(pos - m_pExtraListScroll->getPosition());
						break;
					case Element::ExtraListButton:
						if (m_eDownElement == Element::None && !m_bToggleListVisible)
							OpenToggleList();
						break;
					case Element::ToggleListScroll:
						m_pToggleListScroll->NotifyOnMouseHover(pos - m_pToggleListScroll->getPosition());
						break;
					default:
						break;
					}
				}
				m_iHoveredElementIndex = index;
				return true;
			}
			return false;
		}

		void CCoolBar::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".OuterBorderWidth", m_sOuterBorderWidth);
			style->getOption(m_sClassName + L".OuterBorderColor", m_sOuterBorderColor);
			style->getOption(m_sClassName + L".InnerBorderWidth", m_sInnerBorderWidth);
			style->getOption(m_sClassName + L".InnerBorderColor", m_sInnerBorderColor);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L".MoverMargin", m_sMoverMargin);
			style->getOption(m_sClassName + L".MoverBorderWidth", m_sMoverBorderWidth);
			style->getOption(m_sClassName + L".MoverPadding", m_sMoverPadding);
			style->getOption(m_sClassName + L".ExtraMargin", m_sExtraMargin);
			style->getOption(m_sClassName + L".ExtraBorderWidth", m_sExtraBorderWidth);
			style->getOption(m_sClassName + L".ExtraPadding", m_sExtraPadding);
			style->getOption(m_sClassName + L".ExtraSize", m_fExtraSize);
			style->getOption(m_sClassName + L".ExtraListOuterBorderWidth", m_sExtraListOuterBorderWidth);
			style->getOption(m_sClassName + L".ExtraListOuterBorderColor", m_sExtraListOuterBorderColor);
			style->getOption(m_sClassName + L".ExtraListInnerBorderWidth", m_sExtraListInnerBorderWidth);
			style->getOption(m_sClassName + L".ExtraListInnerBorderColor", m_sExtraListInnerBorderColor);
			style->getOption(m_sClassName + L".ExtraListPadding", m_sExtraListPadding);
			style->getOption(m_sClassName + L".ExtraListBackgroundColor", m_sExtraListBackgroundColor);
			style->getOption(m_sClassName + L".ExtraListBackgroundGradient", m_cExtraListBackgroundGradient);
			style->getOption(m_sClassName + L".ExtraListShadowRadius", m_iExtraListShadowRadius);
			style->getOption(m_sClassName + L".ExtraListShadowShift", m_sExtraListShadowShift);
			style->getOption(m_sClassName + L".ExtraListShadowColor", m_sExtraListShadowColor);
			style->getOption(m_sClassName + L".ExtraListButtonPadding", m_sExtraListButtonPadding);
			style->getOption(m_sClassName + L".ExtraListButtonBorderWidth", m_sExtraListButtonBorderWidth);
			style->getOption(m_sClassName + L".ToggleListOuterBorderWidth", m_sToggleListOuterBorderWidth);
			style->getOption(m_sClassName + L".ToggleListOuterBorderColor", m_sToggleListOuterBorderColor);
			style->getOption(m_sClassName + L".ToggleListInnerBorderWidth", m_sToggleListInnerBorderWidth);
			style->getOption(m_sClassName + L".ToggleListInnerBorderColor", m_sToggleListInnerBorderColor);
			style->getOption(m_sClassName + L".ToggleListPadding", m_sToggleListPadding);
			style->getOption(m_sClassName + L".ToggleListBackgroundColor", m_sToggleListBackgroundColor);
			style->getOption(m_sClassName + L".ToggleListBackgroundGradient", m_cToggleListBackgroundGradient);
			style->getOption(m_sClassName + L".ToggleListShadowRadius", m_iToggleListShadowRadius);
			style->getOption(m_sClassName + L".ToggleListShadowShift", m_sToggleListShadowShift);
			style->getOption(m_sClassName + L".ToggleListShadowColor", m_sToggleListShadowColor);
			style->getOption(m_sClassName + L".ToggleListIconPadding", m_fToggleListIconPadding);
			style->getOption(m_sClassName + L".ToggleListElementPadding", m_sToggleListElementPadding);
			style->getOption(m_sClassName + L".ToggleListElementBorderWidth", m_sToggleListElementBorderWidth);
			String name;
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				switch ((State)i)
				{
				case State::Hovered:
					name = L"Hovered";
					break;
				case State::Down:
					name = L"Down";
					break;
				case State::Disabled:
					name = L"Disabled";
					break;
				default:
					name = L"Normal";
				}
				style->getOption(m_sClassName + L".MoverBorderColor[" + name + L"]", m_aMoverBorderColor[i]);
				style->getOption(m_sClassName + L".MoverBackgroundColor[" + name + L"]", m_aMoverBackgroundColor[i]);
				style->getOption(m_sClassName + L".MoverBackgroundGradient[" + name + L"]", m_aMoverBackgroundGradient[i]);
				style->getOption(m_sClassName + L".MoverForeground1Color[" + name + L"]", m_aMoverForeground1Color[i]);
				style->getOption(m_sClassName + L".MoverForeground2Color[" + name + L"]", m_aMoverForeground2Color[i]);
				style->getOption(m_sClassName + L".ExtraBorderColor[" + name + L"]", m_aExtraBorderColor[i]);
				style->getOption(m_sClassName + L".ExtraBackgroundColor[" + name + L"]", m_aExtraBackgroundColor[i]);
				style->getOption(m_sClassName + L".ExtraBackgroundGradient[" + name + L"]", m_aExtraBackgroundGradient[i]);
				style->getOption(m_sClassName + L".ExtraColor[" + name + L"]", m_aExtraColor[i]);
				style->getOption(m_sClassName + L".ExtraListButtonBorderColor[" + name + L"]", m_aExtraListButtonBorderColor[i]);
				style->getOption(m_sClassName + L".ExtraListButtonBackgroundColor[" + name + L"]", m_aExtraListButtonBackgroundColor[i]);
				style->getOption(m_sClassName + L".ExtraListButtonBackgroundGradient[" + name + L"]", m_aExtraListButtonBackgroundGradient[i]);
				style->getOption(m_sClassName + L".ExtraListButtonColor[" + name + L"]", m_aExtraListButtonColor[i]);
				style->getOption(m_sClassName + L".ToggleListElementBorderColor[" + name + L"]", m_aToggleListElementBorderColor[i]);
				style->getOption(m_sClassName + L".ToggleListElementBackgroundColor[" + name + L"]", m_aToggleListElementBackgroundColor[i]);
				style->getOption(m_sClassName + L".ToggleListElementBackgroundGradient[" + name + L"]", m_aToggleListElementBackgroundGradient[i]);
				style->getOption(m_sClassName + L".ToggleListElementColor[" + name + L"]", m_aToggleListElementColor[i]);
			}
			m_bIgnoreGradient = false;
		}

		bool CCoolBar::OpenExtraList()
		{
			if (!m_bExtraListVisible && (m_pVisibilityManager || m_bHasExtraControls))
			{
				Repaint(false);
				m_bExtraListVisible = true;
				UpdateExtraList();
				AlignExtraControls();
				if (m_pCanvasExtraList)
					m_pCanvasExtraList->setValid(false);
				if (m_pMaskExtraList)
					m_pMaskExtraList->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCoolBar::CloseExtraList()
		{
			if (m_bExtraListVisible)
			{
				Repaint(false);
				m_bExtraListVisible = false;
				AlignControls(true);
				if (m_pCanvasExtraList)
				{
					m_pCanvasExtraList->Release();
					m_pCanvasExtraList = nullptr;
				}
				if (m_pMaskExtraList)
				{
					m_pMaskExtraList->Release();
					m_pMaskExtraList = nullptr;
				}
				return true;
			}
			return false;
		}

		bool CCoolBar::OpenToggleList()
		{
			if (!m_bToggleListVisible && m_pVisibilityManager)
			{
				Repaint(false);
				m_bToggleListVisible = true;
				UpdateToggleList();
				if (m_pCanvasToggleList)
					m_pCanvasToggleList->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCoolBar::CloseToggleList()
		{
			if (m_bToggleListVisible)
			{
				Repaint(false);
				m_bToggleListVisible = false;
				if (m_pCanvasToggleList)
				{
					m_pCanvasToggleList->Release();
					m_pCanvasToggleList = nullptr;
				}
				return true;
			}
			return false;
		}

		void CCoolBar::UpdateExtraList()
		{
			if (!m_bAligning)
			{
				m_bAligning = true;
				// Calculate minimum size: borders and padding + visibility manager button
				PointF minimum_size{
					m_sExtraListOuterBorderWidth.Left +
					m_sExtraListOuterBorderWidth.Right +
					m_sExtraListInnerBorderWidth.Left +
					m_sExtraListInnerBorderWidth.Right +
					m_sExtraListPadding.Left +
					m_sExtraListPadding.Right,

					m_sExtraListOuterBorderWidth.Top +
					m_sExtraListOuterBorderWidth.Bottom +
					m_sExtraListInnerBorderWidth.Top +
					m_sExtraListInnerBorderWidth.Bottom +
					m_sExtraListPadding.Top +
					m_sExtraListPadding.Bottom

				};
				// Calculate required client width
				PointF button_size{ 0, 0 }, required_client_size{ 0, 0 };
				if (m_pVisibilityManager)
				{
					IFont *f{ getFont() };
					IPlatformFont *pf{ f->getPlatformFont(getForm()->getRenderer()) };
					button_size = pf->getStringSize(Application->Translate->t(TranslateCategory, TextAddOrRemoveButtons), f->Distance);
					button_size.X += m_sExtraListButtonBorderWidth.Left + m_sExtraListButtonPadding.Left + m_sExtraListButtonPadding.Right + m_sExtraListButtonBorderWidth.Right;
					button_size.Y += m_sExtraListButtonBorderWidth.Top + m_sExtraListButtonPadding.Top + m_sExtraListButtonPadding.Bottom + m_sExtraListButtonBorderWidth.Bottom;
					required_client_size.X = ntl::Max<float>(required_client_size.X, button_size.X + button_size.Y);
					required_client_size.Y = ntl::Max<float>(required_client_size.Y, button_size.Y);
				}
				PointF avg_control_size{ 0, 0 };
				int control_count{ 0 };
				for (int i = m_iLastVisibleControl + 1; i < getControlCount(); i++)
				{
					IControl *control{ getControl(i) };
					if (m_pVisibilityManager && (!m_pVisibilityManager->isVisible(control, i) || !m_pVisibilityManager->isExtraVisible(control, i)))
						continue;
					PointF size{ AdjustByConstraints(control->QueryService()->getSizeRequested(), control->getConstraints()) };
					required_client_size.X = ntl::Max<float>(required_client_size.X, size.X);
					avg_control_size += size;
					control_count++;
				}
				if (control_count > 0)
				{
					avg_control_size /= (float)control_count;
					required_client_size.X = ntl::Max<float>(required_client_size.X, std::sqrt((float)control_count / 1.5f) * (avg_control_size.X + avg_control_size.Y) * 0.5f);
				}
				// Adjust required client width to constraints and form width
				PointF actual_client_size{ required_client_size };
				if (m_sExtraListConstraints.X > minimum_size.X + button_size.X)
					actual_client_size.X = ntl::Min<float>(actual_client_size.X, m_sExtraListConstraints.X - minimum_size.X);
				if ((float)getForm()->getClientWidth() > minimum_size.X + button_size.X)
					actual_client_size.X = ntl::Min<float>(actual_client_size.X, (float)getForm()->getClientWidth() - minimum_size.X);
				// Calculate required client height
				int index{ m_iLastVisibleControl + 1 };
				while (index < getControlCount())
				{
					float used_width{ 0 }, max_height{ 0 };
					bool first{ true };
					while (index < getControlCount())
					{
						IControl *control{ getControl(index) };
						if (m_pVisibilityManager && (!m_pVisibilityManager->isVisible(control, index) || !m_pVisibilityManager->isExtraVisible(control, index)))
						{
							index++;
							continue;
						}
						PointF size{ AdjustByConstraints(control->QueryService()->getSizeRequested(), control->getConstraints()) };
						if (size.X + used_width < actual_client_size.X) // If control can be placed on current line
						{
							used_width += size.X;
							max_height = ntl::Max<float>(max_height, size.Y);
							index++;
							first = false;
							continue;
						}
						// Control cannot be placed on current line or it takes entire line
						if (first)
						{
							max_height = size.Y;
							index++;
						}
						break;
					}
					required_client_size.Y += max_height;
				}
				// Adjust required client height to constraints and form height
				actual_client_size.Y = required_client_size.Y;
				if (m_sExtraListConstraints.Y > minimum_size.Y + button_size.Y)
					actual_client_size.Y = ntl::Min<float>(actual_client_size.Y, m_sExtraListConstraints.Y - minimum_size.Y);
				if ((float)getForm()->getClientHeight() > minimum_size.Y + button_size.Y)
					actual_client_size.Y = ntl::Min<float>(actual_client_size.Y, (float)getForm()->getClientHeight() - minimum_size.Y);
				// Adjust actual client size if scroll is required
				if (ntl::IsGreater<float>(required_client_size.Y, actual_client_size.Y))
				{
					m_bExtraListScrollVisible = true;
					IBuiltInScroll *scroll{ getExtraListScroll() };
					required_client_size.X = ntl::Max<float>(scroll->getWidth(), button_size.X + button_size.Y);
					avg_control_size = PointF{ 0, 0 };
					control_count = 0;
					for (int i = m_iLastVisibleControl + 1; i < getControlCount(); i++)
					{
						IControl *control{ getControl(i) };
						if (m_pVisibilityManager && (!m_pVisibilityManager->isVisible(control, i) || !m_pVisibilityManager->isExtraVisible(control, i)))
							continue;
						PointF size{ AdjustByConstraints(control->QueryService()->getSizeRequested(), control->getConstraints()) };
						required_client_size.X = ntl::Max<float>(required_client_size.X, size.X + scroll->getWidth());
						avg_control_size += size;
						control_count++;
					}
					if (control_count > 0)
					{
						avg_control_size /= (float)control_count;
						required_client_size.X = ntl::Max<float>(required_client_size.X, std::sqrt((float)control_count / 1.5f) * (avg_control_size.X + avg_control_size.Y) * 0.5f);
					}
					actual_client_size.X = required_client_size.X;
					if (m_sExtraListConstraints.X > minimum_size.X + ntl::Max<float>(scroll->getWidth(), button_size.X))
						actual_client_size.X = ntl::Min<float>(actual_client_size.X, m_sExtraListConstraints.X - minimum_size.X);
					if ((float)getForm()->getClientWidth() > minimum_size.X + ntl::Max<float>(scroll->getWidth(), button_size.X))
						actual_client_size.X = ntl::Min<float>(actual_client_size.X, (float)getForm()->getClientWidth() - minimum_size.X);

					required_client_size.Y = m_pVisibilityManager ? button_size.Y : 0;
					index = m_iLastVisibleControl + 1;
					while (index < getControlCount())
					{
						float used_width{ 0 }, max_height{ 0 };
						bool first{ true };
						while (index < getControlCount())
						{
							IControl *control{ getControl(index) };
							if (m_pVisibilityManager && (!m_pVisibilityManager->isVisible(control, index) || !m_pVisibilityManager->isExtraVisible(control, index)))
							{
								index++;
								continue;
							}
							PointF size{ AdjustByConstraints(control->QueryService()->getSizeRequested(), control->getConstraints()) };
							if (size.X + used_width < actual_client_size.X) // If control can be placed on current line
							{
								used_width += size.X;
								max_height = ntl::Max<float>(max_height, size.Y);
								index++;
								first = false;
								continue;
							}
							if (first)
							{
								max_height = size.Y;
								index++;
							}
							break;
						}
						required_client_size.Y += max_height;
					}
					actual_client_size.Y = required_client_size.Y;
					if (m_sExtraListConstraints.Y > minimum_size.Y + button_size.Y)
						actual_client_size.Y = ntl::Min<float>(actual_client_size.Y, m_sExtraListConstraints.Y - minimum_size.Y);
					if ((float)getForm()->getClientHeight() > minimum_size.Y + button_size.Y)
						actual_client_size.Y = ntl::Min<float>(actual_client_size.Y, (float)getForm()->getClientHeight() - minimum_size.Y);
					scroll->setMax(required_client_size.Y - actual_client_size.Y);
				}
				else
					m_bExtraListScrollVisible = false;
				// Calculate position
				PointF position{ 0, 0 };
				Mat4f local_to_form{ getTransformMatrix() }, form_to_local{ ntl::Inversed(local_to_form) };
				RectF r1{ 0, 0, minimum_size.X + actual_client_size.X, minimum_size.Y + actual_client_size.Y }, r2{ TransformRect(r1, local_to_form) };
				bool has_only_translate{ ntl::IsEqual<float>(r1.width(), r2.width()) && ntl::IsEqual<float>(r1.height(), r2.height()) };
				Vec4f v;
				switch (m_eOrientation)
				{
				case Orientation::LeftToRight:
					if (has_only_translate)
					{
						v = local_to_form * Vec4f{ getWidth() - minimum_size.X - actual_client_size.X, 0, 0, 1 };
						if (v.X < 0)
						{
							v = form_to_local * Vec4f{ 0, 0, 0, 1 };
							position.X = v.X;
						}
						else
							position.X = getWidth() - minimum_size.X - actual_client_size.X;
						v = local_to_form * Vec4f{ 0, getHeight() + minimum_size.Y + actual_client_size.Y, 0, 1 };
						if (v.Y >= (float)getForm()->getClientHeight())
						{
							v = local_to_form * Vec4f{ 0, -minimum_size.Y - actual_client_size.Y, 0, 1 };
							if (v.Y < 0)
							{
								v = form_to_local * Vec4f{ 0, 0, 0, 1 };
								position.Y = v.Y;
							}
							else
								position.Y = -minimum_size.Y - actual_client_size.Y;
						}
						else
							position.Y = getHeight();
					}
					else
					{
						position.X = getWidth() - minimum_size.X - actual_client_size.X;
						position.Y = getHeight();
					}
					break;
				case Orientation::TopToBottom:
					if (has_only_translate)
					{
						v = local_to_form * Vec4f{ -minimum_size.X - actual_client_size.X, 0, 0, 1 };
						if (v.X < 0)
						{
							v = local_to_form * Vec4f{ getWidth() + minimum_size.X + actual_client_size.X, 0, 0, 1 };
							if (v.X >= (float)getForm()->getClientWidth())
							{
								v = form_to_local * Vec4f{ 0, 0, 0, 1 };
								position.X = v.X;
							}
							else
								position.X = getWidth();
						}
						else
							position.X = -minimum_size.X - actual_client_size.X;
						v = local_to_form * Vec4f{ 0, getHeight() - minimum_size.Y - actual_client_size.Y, 0, 1 };
						if (v.Y < 0)
						{
							v = local_to_form * Vec4f{ 0, 0, 0, 1 };
							position.Y = v.Y;
						}
						else
							position.Y = getHeight() - minimum_size.Y - actual_client_size.Y;
					}
					else
					{
						position.X = -minimum_size.X - actual_client_size.X;
						position.Y = getHeight() - minimum_size.Y - actual_client_size.Y;
					}
					break;
				case Orientation::RightToLeft:
					if (has_only_translate)
					{
						v = local_to_form * Vec4f{ minimum_size.X + actual_client_size.X, 0, 0, 1 };
						if (v.X >= (float)getForm()->getClientWidth())
						{
							v = form_to_local * Vec4f{ 0, 0, 0, 1 };
							position.X = v.X;
						}
						else
							position.X = 0;
						v = local_to_form * Vec4f{ 0, getHeight() + minimum_size.Y + actual_client_size.Y, 0, 1 };
						if (v.Y >= (float)getForm()->getClientHeight())
						{
							v = local_to_form * Vec4f{ 0, -minimum_size.Y - actual_client_size.Y, 0, 1 };
							if (v.Y < 0)
							{
								v = form_to_local * Vec4f{ 0, 0, 0, 1 };
								position.Y = v.Y;
							}
							else
								position.Y = -minimum_size.Y - actual_client_size.Y;
						}
						else
							position.Y = getHeight();
					}
					else
					{
						position.X = 0;
						position.Y = getHeight();
					}
					break;
				case Orientation::BottomToTop:
					if (has_only_translate)
					{
						v = local_to_form * Vec4f{ getWidth() + minimum_size.X + actual_client_size.X, 0, 0, 1 };
						if (v.X >= (float)getForm()->getClientWidth())
						{
							v = local_to_form * Vec4f{ -minimum_size.X - actual_client_size.X, 0, 0, 1 };
							if (v.X < 0)
							{
								v = form_to_local * Vec4f{ 0, 0, 0, 1 };
								position.X = v.X;
							}
							else
								position.X = -minimum_size.X - actual_client_size.X;
						}
						else
							position.X = getWidth();
						v = local_to_form * Vec4f{ 0, minimum_size.Y + actual_client_size.Y, 0, 1 };
						if (v.Y >= (float)getForm()->getClientHeight())
						{
							v = local_to_form * Vec4f{ 0, 0, 0, 1 };
							position.Y = v.Y;
						}
						else
							position.Y = 0;
					}
					else
					{
						position.X = getWidth();
						position.Y = 0;
					}
					break;
				}
				// Fill rectangles
				m_sExtraListRect.LeftTop = position;
				m_sExtraListRect.RightBottom = position + minimum_size + actual_client_size;
				m_sExtraListClientRect.Left = m_sExtraListRect.Left + m_sExtraListOuterBorderWidth.Left + m_sExtraListInnerBorderWidth.Left + m_sExtraListPadding.Left;
				m_sExtraListClientRect.Top = m_sExtraListRect.Top + m_sExtraListOuterBorderWidth.Top + m_sExtraListInnerBorderWidth.Top + m_sExtraListPadding.Top;
				m_sExtraListClientRect.Right = m_sExtraListRect.Right - m_sExtraListOuterBorderWidth.Right - m_sExtraListInnerBorderWidth.Right - m_sExtraListPadding.Right;
				m_sExtraListClientRect.Bottom = m_sExtraListRect.Bottom - m_sExtraListOuterBorderWidth.Bottom - m_sExtraListInnerBorderWidth.Bottom - m_sExtraListPadding.Bottom;
				if (m_pVisibilityManager)
				{
					m_sExtraListButtonRect.Left = m_sExtraListClientRect.Left;
					m_sExtraListButtonRect.Top = m_sExtraListClientRect.Bottom - button_size.Y;
					m_sExtraListButtonRect.Right = m_sExtraListClientRect.Right;
					m_sExtraListButtonRect.Bottom = m_sExtraListClientRect.Bottom;
				}
				// Update scroll
				if (m_bExtraListScrollVisible)
				{
					m_pExtraListScroll->setPosition(PointF{
						m_sExtraListClientRect.Right - m_pExtraListScroll->getWidth() + m_sExtraListPadding.Right,
						m_sExtraListClientRect.Top - m_sExtraListPadding.Top });
					m_pExtraListScroll->setSize(PointF{
						m_pExtraListScroll->getWidth(),
						m_sExtraListClientRect.height() + m_sExtraListPadding.Top + (m_pVisibilityManager ? 0 : m_sExtraListPadding.Bottom) - button_size.Y });
					m_sExtraListClientRect.Right -= m_pExtraListScroll->getWidth();
				}
				m_bAligning = false;
			}
		}

		void CCoolBar::UpdateToggleList()
		{
			if (!m_bAligning)
			{
				m_bAligning = true;
				// Calculate element height
				IFont *f{ getFont() };
				IPlatformFont *pf{ f->getPlatformFont(getForm()->getRenderer()) };
				PointF dummy_text_size{ pf->getStringSize(L"Why", f->Distance) };
				m_fToggleListElementHeight = m_sToggleListElementBorderWidth.Top + m_sToggleListElementPadding.Top + dummy_text_size.Y + m_sToggleListElementPadding.Bottom + m_sToggleListElementBorderWidth.Bottom;
				// Calculate minimum size: borders and padding
				PointF minimum_size{
					m_sToggleListOuterBorderWidth.Left +
					m_sToggleListOuterBorderWidth.Right +
					m_sToggleListInnerBorderWidth.Left +
					m_sToggleListInnerBorderWidth.Right +
					m_sToggleListPadding.Left +
					m_sToggleListPadding.Right,

					m_sToggleListOuterBorderWidth.Top +
					m_sToggleListOuterBorderWidth.Bottom +
					m_sToggleListInnerBorderWidth.Top +
					m_sToggleListInnerBorderWidth.Bottom +
					m_sToggleListPadding.Top +
					m_sToggleListPadding.Bottom

				};
				// Calculate required client width
				PointF required_client_size{ 0, m_fToggleListElementHeight * (float)getControlCount() };
				float min_element_size{ m_sToggleListElementBorderWidth.Left + m_sToggleListElementPadding.Left + m_sToggleListElementPadding.Right + m_sToggleListElementBorderWidth.Right + 2 * (dummy_text_size.Y + m_fToggleListIconPadding) };
				for (int i = 0; i < getControlCount(); i++)
				{
					String text{ m_pVisibilityManager->getTitle(getControl(i), i) };
					if (text.empty())
						text = Application->Translate->t(TranslateCategory, TextWidgetI, StringKeyValueArray{ { L"{i}", ToString(i + 1) } });
					required_client_size.X = ntl::Max<float>(required_client_size.X, pf->getStringSize(text, f->Distance).X + min_element_size);
				}
				// Adjust required client height
				PointF actual_client_size{ required_client_size };
				if (m_sToggleListConstraints.Y > minimum_size.Y)
					actual_client_size.Y = ntl::Min<float>(actual_client_size.Y, m_sToggleListConstraints.Y - minimum_size.Y);
				if ((float)getForm()->getClientHeight() > minimum_size.Y)
					actual_client_size.Y = ntl::Min<float>(actual_client_size.Y, (float)getForm()->getClientHeight() - minimum_size.Y);
				// Adjust actual client size if scroll is required
				if (ntl::IsGreater<float>(required_client_size.Y, actual_client_size.Y))
				{
					m_bToggleListScrollVisible = true;
					IBuiltInScroll *scroll{ getToggleListScroll() };
					scroll->setMax(required_client_size.Y - actual_client_size.Y);
					actual_client_size.X += scroll->getWidth();
				}
				else
					m_bToggleListScrollVisible = false;
				// Adjust required client width to constraints
				if (m_sToggleListConstraints.X > minimum_size.X)
					actual_client_size.X = ntl::Min<float>(actual_client_size.X, m_sToggleListConstraints.X - minimum_size.X);
				if ((float)getForm()->getClientWidth() > minimum_size.X)
					actual_client_size.X = ntl::Min<float>(actual_client_size.X, (float)getForm()->getClientWidth() - minimum_size.X);
				// Calculate position
				PointF position{ 0, 0 };
				Mat4f local_to_form{ getTransformMatrix() }, form_to_local{ ntl::Inversed(local_to_form) };
				RectF r1{ 0, 0, minimum_size.X + actual_client_size.X, minimum_size.Y + actual_client_size.Y }, r2{ TransformRect(r1, local_to_form) };
				bool has_only_translate{ ntl::IsEqual<float>(r1.width(), r2.width()) && ntl::IsEqual<float>(r1.height(), r2.height()) };
				Vec4f v;
				if (has_only_translate)
				{
					v = local_to_form * Vec4f{ m_sExtraListRect.Right + minimum_size.X + actual_client_size.X, 0, 0, 1 };
					if (v.X >= (float)getForm()->getClientWidth())
					{
						v = local_to_form * Vec4f{ m_sExtraListRect.Left - minimum_size.X - actual_client_size.X, 0, 0, 1 };
						if (v.X < 0)
						{
							v = form_to_local * Vec4f{ 0, 0, 0, 1 };
							position.X = v.X;
						}
						else
							position.X = m_sExtraListRect.Left - minimum_size.X - actual_client_size.X;
					}
					else
						position.X = m_sExtraListRect.Right;
					v = local_to_form * Vec4f{ 0, m_sExtraListRect.Bottom - minimum_size.Y - actual_client_size.Y, 0, 1 };
					if (v.Y < 0)
					{
						v = form_to_local * Vec4f{ 0, 0, 0, 1 };
						position.Y = v.Y;
					}
					else
						position.Y = m_sExtraListRect.Bottom - minimum_size.Y - actual_client_size.Y;
				}
				else
				{
					position.X = m_sExtraListRect.Right;
					position.Y = m_sExtraListRect.Bottom - minimum_size.Y - actual_client_size.Y;
				}
				// Fill rectangles
				m_sToggleListRect.LeftTop = position;
				m_sToggleListRect.RightBottom = position + minimum_size + actual_client_size;
				m_sToggleListClientRect.Left = m_sToggleListRect.Left + m_sToggleListOuterBorderWidth.Left + m_sToggleListInnerBorderWidth.Left + m_sToggleListPadding.Left;
				m_sToggleListClientRect.Top = m_sToggleListRect.Top + m_sToggleListOuterBorderWidth.Top + m_sToggleListInnerBorderWidth.Top + m_sToggleListPadding.Top;
				m_sToggleListClientRect.Right = m_sToggleListRect.Right - m_sToggleListOuterBorderWidth.Right - m_sToggleListInnerBorderWidth.Right - m_sToggleListPadding.Right;
				m_sToggleListClientRect.Bottom = m_sToggleListRect.Bottom - m_sToggleListOuterBorderWidth.Bottom - m_sToggleListInnerBorderWidth.Bottom - m_sToggleListPadding.Bottom;
				// Update scroll
				if (m_bToggleListScrollVisible)
				{
					m_pToggleListScroll->setPosition(PointF{ m_sToggleListClientRect.Right - m_pToggleListScroll->getWidth() + m_sToggleListPadding.Right, m_sToggleListClientRect.Top - m_sToggleListPadding.Top });
					m_pToggleListScroll->setSize(PointF{ m_pToggleListScroll->getWidth(), m_sToggleListClientRect.height() + m_sToggleListPadding.Top + m_sToggleListPadding.Bottom });
					m_sToggleListClientRect.Right -= m_pToggleListScroll->getWidth();
				}
				m_bAligning = false;
			}
		}

		void CCoolBar::AlignControls(const bool hide_controls)
		{
			if (!m_bAligning)
			{
				m_bAligning = true;
				RectF client{ CalculateClientRect(m_bShowExtra, m_bHasExtraControls) };
				float client_size, control_second_size;
				IControl *control;
				PointF control_size, new_size;
				switch (m_eOrientation)
				{
				case Orientation::LeftToRight:
					client_size = client.width();
					control_second_size = client.height();
					for (m_iLastVisibleControl = 0; m_iLastVisibleControl < getControlCount(); m_iLastVisibleControl++)
					{
						control = getControl(m_iLastVisibleControl);
						if (m_pVisibilityManager && !m_pVisibilityManager->isVisible(control, m_iLastVisibleControl))
						{
							control->setVisible(false);
							continue;
						}
						control_size = AdjustByConstraints(control->QueryService()->getSizeRequested(), control->getConstraints());
						if (ntl::IsGreater<float>(control_size.X, client_size))
						{
							m_iLastVisibleControl--;
							control->setVisible(false);
							break;
						}
						new_size = PointF{ control_size.X, control_second_size };
						control->getTransform()->QueryService()->Transform(client.Left, client.Top, 0, 1, 1, 1, 0, 0, 0);
						control->setVisible(true);
						if (IsNotEqual(new_size, control->getSize()))
						{
							control->QueryService()->setSize(new_size);
							control->QueryService()->AlignControls();
							CNotifier::Resize(control);
						}
						client_size -= new_size.X;
						client.Left += new_size.X;
					}
					break;
				case Orientation::TopToBottom:
					client_size = client.height();
					control_second_size = client.width();
					for (m_iLastVisibleControl = 0; m_iLastVisibleControl < getControlCount(); m_iLastVisibleControl++)
					{
						control = getControl(m_iLastVisibleControl);
						if (m_pVisibilityManager && !m_pVisibilityManager->isVisible(control, m_iLastVisibleControl))
						{
							control->setVisible(false);
							continue;
						}
						control_size = AdjustByConstraints(control->QueryService()->getSizeRequested(), control->getConstraints());
						if (ntl::IsGreater<float>(control_size.Y, client_size))
						{
							m_iLastVisibleControl--;
							control->setVisible(false);
							break;
						}
						new_size = PointF{ control_second_size, control_size.Y };
						control->getTransform()->QueryService()->Transform(client.Left, client.Top, 0, 1, 1, 1, 0, 0, 0);
						control->setVisible(true);
						if (IsNotEqual(new_size, control->getSize()))
						{
							control->QueryService()->setSize(new_size);
							control->QueryService()->AlignControls();
							CNotifier::Resize(control);
						}
						client_size -= new_size.Y;
						client.Top += new_size.Y;
					}
					break;
				case Orientation::RightToLeft:
					client_size = client.width();
					control_second_size = client.height();
					for (m_iLastVisibleControl = 0; m_iLastVisibleControl < getControlCount(); m_iLastVisibleControl++)
					{
						control = getControl(m_iLastVisibleControl);
						if (m_pVisibilityManager && !m_pVisibilityManager->isVisible(control, m_iLastVisibleControl))
						{
							control->setVisible(false);
							continue;
						}
						control_size = AdjustByConstraints(control->QueryService()->getSizeRequested(), control->getConstraints());
						if (ntl::IsGreater<float>(control_size.X, client_size))
						{
							m_iLastVisibleControl--;
							control->setVisible(false);
							break;
						}
						new_size = PointF{ control_size.X, control_second_size };
						control->getTransform()->QueryService()->Transform(client.Right - new_size.X, client.Top, 0, 1, 1, 1, 0, 0, 0);
						control->setVisible(true);
						if (IsNotEqual(new_size, control->getSize()))
						{
							control->QueryService()->setSize(new_size);
							control->QueryService()->AlignControls();
							CNotifier::Resize(control);
						}
						client_size -= new_size.X;
						client.Right -= new_size.X;
					}
					break;
				case Orientation::BottomToTop:
					client_size = client.height();
					control_second_size = client.width();
					for (m_iLastVisibleControl = 0; m_iLastVisibleControl < getControlCount(); m_iLastVisibleControl++)
					{
						control = getControl(m_iLastVisibleControl);
						if (m_pVisibilityManager && !m_pVisibilityManager->isVisible(control, m_iLastVisibleControl))
						{
							control->setVisible(false);
							continue;
						}
						control_size = AdjustByConstraints(control->QueryService()->getSizeRequested(), control->getConstraints());
						if (ntl::IsGreater<float>(control_size.Y, client_size))
						{
							m_iLastVisibleControl--;
							control->setVisible(false);
							break;
						}
						new_size = PointF{ control_second_size, control_size.Y };
						control->getTransform()->QueryService()->Transform(client.Left, client.Bottom - new_size.Y, 0, 1, 1, 1, 0, 0, 0);
						control->setVisible(true);
						if (IsNotEqual(new_size, control->getSize()))
						{
							control->QueryService()->setSize(new_size);
							control->QueryService()->AlignControls();
							CNotifier::Resize(control);
						}
						client_size -= new_size.Y;
						client.Bottom -= new_size.Y;
					}
					break;
				}
				if (hide_controls)
					for (int i = m_iLastVisibleControl + 1; i < getControlCount(); i++)
						getControl(i)->setVisible(false);
				m_bAligning = false;
			}
		}

		void CCoolBar::AlignExtraControls()
		{
			if (!m_bAligning)
			{
				m_bAligning = true;
				RectF client{ m_sExtraListClientRect };
				float y{ client.Top + (m_bExtraListScrollVisible ? -m_pExtraListScroll->getScroll() : 0) };
				int index{ m_iLastVisibleControl + 1 };
				while (index < getControlCount())
				{
					float used_width{ 0 }, max_height{ 0 };
					bool first{ true };
					while (index < getControlCount())
					{
						IControl *control{ getControl(index) };
						if (m_pVisibilityManager && (!m_pVisibilityManager->isVisible(control, index) || !m_pVisibilityManager->isExtraVisible(control, index)))
						{
							control->setVisible(false);
							index++;
							continue;
						}
						PointF size{ AdjustByConstraints(control->QueryService()->getSizeRequested(), control->getConstraints()) };
						if (size.X + used_width < client.width()) // If control can be placed on current line
						{
							control->getTransform()->Transform(client.Left + used_width, y, 0, 1, 1, 1, 0, 0, 0);
							used_width += size.X;
							max_height = ntl::Max<float>(max_height, size.Y);
							index++;
							if (IsNotEqual(size, control->getSize()))
							{
								control->QueryService()->setSize(size);
								control->QueryService()->AlignControls();
								CNotifier::Resize(control);
							}
							control->setVisible(true);
							first = false;
							continue;
						}
						if (first)
						{
							max_height = size.Y;
							index++;
							control->getTransform()->Transform(client.Left, y, 0, 1, 1, 1, 0, 0, 0);
							size.X = client.width();
							if (IsNotEqual(size, control->getSize()))
							{
								control->QueryService()->setSize(size);
								control->QueryService()->AlignControls();
								CNotifier::Resize(control);
							}
							control->setVisible(true);
						}
						break;
					}
					y += max_height;
				}
				m_bAligning = false;
			}
		}

		void CCoolBar::PostClientAreaChange()
		{
			AlignControls(!m_bExtraListVisible);
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			if (m_bExtraListVisible)
			{
				UpdateExtraList();
				AlignExtraControls();
				if (m_pCanvasExtraList)
					m_pCanvasExtraList->setValid(false);
				if (m_pMaskExtraList)
					m_pMaskExtraList->setValid(false);
				if (m_bToggleListVisible)
				{
					UpdateToggleList();
					if (m_pCanvasToggleList)
						m_pCanvasToggleList->setValid(false);
				}
			}
			UpdateHoveredElement();
			Repaint(false);
		}

		void CCoolBar::PostExtraListChange()
		{
			if (m_bExtraListVisible)
			{
				UpdateExtraList();
				AlignExtraControls();
				if (m_pCanvasExtraList)
					m_pCanvasExtraList->setValid(false);
				if (m_pMaskExtraList)
					m_pMaskExtraList->setValid(false);
				if (m_bToggleListVisible)
				{
					UpdateToggleList();
					if (m_pCanvasToggleList)
						m_pCanvasToggleList->setValid(false);
				}
				UpdateHoveredElement();
				Repaint(false);
			}
		}

		void CCoolBar::PostToggleListChange()
		{
			if (m_bToggleListVisible)
			{
				UpdateToggleList();
				if (m_pCanvasToggleList)
					m_pCanvasToggleList->setValid(false);
				UpdateHoveredElement();
				Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Render
		void CCoolBar::Render(IRenderer *renderer, const Mat4f &matrix)
		{
			RectF rect{ getRect() };
			if (PrepareCanvas(renderer, &m_pCanvas, rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });
				RenderBackground(renderer, rect);
				RenderMover(renderer);
				RenderExtra(renderer);
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, matrix, m_pCanvas, PointF{ 0, 0 });
		}

		void CCoolBar::RenderBackground(IRenderer *renderer, const RectF &rect)
		{
			switch (m_eOrientation)
			{
			case Orientation::LeftToRight:
				DrawDoubleBackground(
					renderer,
					rect,
					m_sOuterBorderWidth,
					m_sInnerBorderWidth,
					RectF{ 0, 0, 0, 0 },
					m_sOuterBorderColor,
					m_sInnerBorderColor,
					m_sBackgroundColor,
					m_cBackgroundGradient);
				break;
			case Orientation::TopToBottom:
				{
					Gradient g{ CalculateGradient(m_cBackgroundGradient) };
					DrawDoubleBackground(
						renderer,
						rect,
						RectF{ m_sOuterBorderWidth.Bottom, m_sOuterBorderWidth.Left, m_sOuterBorderWidth.Top, m_sOuterBorderWidth.Right },
						RectF{ m_sInnerBorderWidth.Bottom, m_sInnerBorderWidth.Left, m_sInnerBorderWidth.Top, m_sInnerBorderWidth.Right },
						RectF{ 0, 0, 0, 0 },
						BorderColor{ m_sOuterBorderColor.Bottom, m_sOuterBorderColor.Left, m_sOuterBorderColor.Top, m_sOuterBorderColor.Right },
						BorderColor{ m_sInnerBorderColor.Bottom, m_sInnerBorderColor.Left, m_sInnerBorderColor.Top, m_sInnerBorderColor.Right },
						m_sBackgroundColor,
						g);
				}
				break;
			case Orientation::RightToLeft:
				{
					Gradient g{ CalculateGradient(m_cBackgroundGradient) };
					DrawDoubleBackground(
						renderer,
						rect,
						RectF{ m_sOuterBorderWidth.Right, m_sOuterBorderWidth.Top, m_sOuterBorderWidth.Left, m_sOuterBorderWidth.Bottom },
						RectF{ m_sInnerBorderWidth.Right, m_sInnerBorderWidth.Top, m_sInnerBorderWidth.Left, m_sInnerBorderWidth.Bottom },
						RectF{ 0, 0, 0, 0 },
						BorderColor{ m_sOuterBorderColor.Right, m_sOuterBorderColor.Top, m_sOuterBorderColor.Left, m_sOuterBorderColor.Bottom },
						BorderColor{ m_sInnerBorderColor.Right, m_sInnerBorderColor.Top, m_sInnerBorderColor.Left, m_sInnerBorderColor.Bottom },
						m_sBackgroundColor,
						g);
				}
				break;
			case Orientation::BottomToTop:
				{
					Gradient g{ CalculateGradient(m_cBackgroundGradient) };
					DrawDoubleBackground(
						renderer,
						rect,
						RectF{ m_sOuterBorderWidth.Top, m_sOuterBorderWidth.Right, m_sOuterBorderWidth.Bottom, m_sOuterBorderWidth.Left },
						RectF{ m_sInnerBorderWidth.Top, m_sInnerBorderWidth.Right, m_sInnerBorderWidth.Bottom, m_sInnerBorderWidth.Left },
						RectF{ 0, 0, 0, 0 },
						BorderColor{ m_sOuterBorderColor.Top, m_sOuterBorderColor.Right, m_sOuterBorderColor.Bottom, m_sOuterBorderColor.Left },
						BorderColor{ m_sInnerBorderColor.Top, m_sInnerBorderColor.Right, m_sInnerBorderColor.Bottom, m_sInnerBorderColor.Left },
						m_sBackgroundColor,
						g);
				}
				break;
			}
		}

		void CCoolBar::RenderMover(IRenderer *renderer)
		{
			if (m_bMoverAlwaysVisible || !m_bLocked)
			{
				RectF total{ CalculateMoverRect() };
				if (!total.is_zero())
				{
					RectF inner{ CalculateMoverInnerRect(total) };
					State st{ CalculateMoverState() };
					switch (m_eOrientation)
					{
					case Orientation::LeftToRight:
						DrawSimpleBackground(
							renderer,
							total,
							m_sMoverBorderWidth,
							RectF{ 0, 0, 0, 0 },
							m_aMoverBorderColor[(int)st],
							m_aMoverBackgroundColor[(int)st],
							m_aMoverBackgroundGradient[(int)st]);
						switch (m_eMoverKind)
						{
						case MoverKind::Line:
						{
							BlockColors colors{ m_aMoverForeground1Color[(int)st], Color{ 0, 0, 0, 0 }, m_aMoverForeground2Color[(int)st], Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
							renderer->DrawBlock(RectF{ inner.Left, inner.Top, inner.Right, inner.Bottom }, RectF{ 1, 0, 1, 0 }, RectF{ 0, 0, 0, 0 }, colors);
							break;
						}
						case MoverKind::DoubleLine:
						{
							BlockColors colors{ m_aMoverForeground1Color[(int)st], Color{ 0, 0, 0, 0 }, m_aMoverForeground2Color[(int)st], Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
							renderer
								->DrawBlock(RectF{ inner.Left, inner.Top, inner.Left + 2, inner.Bottom }, RectF{ 1, 0, 1, 0 }, RectF{ 0, 0, 0, 0 }, colors)
								->DrawBlock(RectF{ inner.Left + 3, inner.Top, inner.Right, inner.Bottom }, RectF{ 1, 0, 1, 0 }, RectF{ 0, 0, 0, 0 }, colors);
							break;
						}
						case MoverKind::Dots:
						{
							float y{ std::round((inner.Top + inner.Bottom) * 0.5f) };
							renderer
								->DrawRectangle(RectF{ inner.Left, y - 1, inner.Right, y + 1 }, m_aMoverForeground1Color[(int)st])
								->DrawRectangle(RectF{ inner.Left, y - 5, inner.Right, y - 3 }, m_aMoverForeground1Color[(int)st])
								->DrawRectangle(RectF{ inner.Left, y + 3, inner.Right, y + 5 }, m_aMoverForeground1Color[(int)st]);
							break;
						}
						case MoverKind::TripleDots:
						{
							CStoreBitmask store_bitmask{ renderer };
							renderer
								->ActivateBitmask(Bitmask{ 0b00010001000100010001000100010001, 0, true, false })
								->DrawLine(PointF{ inner.Left + 1, inner.Top }, PointF{ inner.Left + 1, inner.Bottom }, m_aMoverForeground1Color[(int)st])
								->DrawLine(PointF{ inner.Right, inner.Top }, PointF{ inner.Right, inner.Bottom }, m_aMoverForeground1Color[(int)st])
								->ActivateBitmask(Bitmask{ 0b01000100010001000100010001000100, 0, true, false })
								->DrawLine(PointF{ inner.Left + 3, inner.Top }, PointF{ inner.Left + 3, inner.Bottom }, m_aMoverForeground1Color[(int)st]);
							break;
						}
						default:
							break;
						}
						break;
					case Orientation::TopToBottom:
					{
						Gradient g{ CalculateGradient(m_aMoverBackgroundGradient[(int)st]) };
						DrawSimpleBackground(
							renderer,
							total,
							RectF{ m_sMoverBorderWidth.Bottom, m_sMoverBorderWidth.Left, m_sMoverBorderWidth.Top, m_sMoverBorderWidth.Right },
							RectF{ 0, 0, 0, 0 },
							m_aMoverBorderColor[(int)st],
							m_aMoverBackgroundColor[(int)st],
							g);
					}
					switch (m_eMoverKind)
					{
					case MoverKind::Line:
					{
						BlockColors colors{ Color{ 0, 0, 0, 0 }, m_aMoverForeground1Color[(int)st], Color{ 0, 0, 0, 0 }, m_aMoverForeground2Color[(int)st], Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
						renderer->DrawBlock(RectF{ inner.Left, inner.Top, inner.Right, inner.Bottom }, RectF{ 0, 1, 0, 1 }, RectF{ 0, 0, 0, 0 }, colors);
						break;
					}
					case MoverKind::DoubleLine:
					{
						BlockColors colors{ Color{ 0, 0, 0, 0 }, m_aMoverForeground1Color[(int)st], Color{ 0, 0, 0, 0 }, m_aMoverForeground2Color[(int)st], Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
						renderer
							->DrawBlock(RectF{ inner.Left, inner.Top, inner.Right, inner.Top + 2 }, RectF{ 0, 1, 0, 1 }, RectF{ 0, 0, 0, 0 }, colors)
							->DrawBlock(RectF{ inner.Left, inner.Top + 3, inner.Right, inner.Bottom }, RectF{ 0, 1, 0, 1 }, RectF{ 0, 0, 0, 0 }, colors);
						break;
					}
					case MoverKind::Dots:
					{
						float x{ std::round((inner.Left + inner.Right) * 0.5f) };
						renderer
							->DrawRectangle(RectF{ x - 1, inner.Top, x + 1, inner.Bottom }, m_aMoverForeground1Color[(int)st])
							->DrawRectangle(RectF{ x - 5, inner.Top, x - 3, inner.Bottom }, m_aMoverForeground1Color[(int)st])
							->DrawRectangle(RectF{ x + 3, inner.Top, x + 5, inner.Bottom }, m_aMoverForeground1Color[(int)st]);
						break;
					}
					case MoverKind::TripleDots:
					{
						CStoreBitmask store_bitmask{ renderer };
						renderer
							->ActivateBitmask(Bitmask{ 0b00010001000100010001000100010001, 0, true, false })
							->DrawLine(PointF{ inner.Left, inner.Top }, PointF{ inner.Right, inner.Top }, m_aMoverForeground1Color[(int)st])
							->DrawLine(PointF{ inner.Left, inner.Bottom - 1 }, PointF{ inner.Right, inner.Bottom - 1 }, m_aMoverForeground1Color[(int)st])
							->ActivateBitmask(Bitmask{ 0b01000100010001000100010001000100, 0, true, false })
							->DrawLine(PointF{ inner.Left, inner.Top + 2 }, PointF{ inner.Right, inner.Top + 2 }, m_aMoverForeground1Color[(int)st]);
						break;
					}
					default:
						break;
					}
					break;
					case Orientation::RightToLeft:
					{
						Gradient g{ CalculateGradient(m_aMoverBackgroundGradient[(int)st]) };
						DrawSimpleBackground(
							renderer,
							total,
							RectF{ m_sMoverBorderWidth.Right, m_sMoverBorderWidth.Top, m_sMoverBorderWidth.Left, m_sMoverBorderWidth.Bottom },
							RectF{ 0, 0, 0, 0 },
							m_aMoverBorderColor[(int)st],
							m_aMoverBackgroundColor[(int)st],
							g);
					}
					switch (m_eMoverKind)
					{
					case MoverKind::Line:
					{
						BlockColors colors{ m_aMoverForeground1Color[(int)st], Color{ 0, 0, 0, 0 }, m_aMoverForeground2Color[(int)st], Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
						renderer->DrawBlock(RectF{ inner.Left, inner.Top, inner.Right, inner.Bottom }, RectF{ 1, 0, 1, 0 }, RectF{ 0, 0, 0, 0 }, colors);
						break;
					}
					case MoverKind::DoubleLine:
					{
						BlockColors colors{ m_aMoverForeground1Color[(int)st], Color{ 0, 0, 0, 0 }, m_aMoverForeground2Color[(int)st], Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
						renderer
							->DrawBlock(RectF{ inner.Left, inner.Top, inner.Left + 2, inner.Bottom }, RectF{ 1, 0, 1, 0 }, RectF{ 0, 0, 0, 0 }, colors)
							->DrawBlock(RectF{ inner.Left + 3, inner.Top, inner.Right, inner.Bottom }, RectF{ 1, 0, 1, 0 }, RectF{ 0, 0, 0, 0 }, colors);
						break;
					}
					case MoverKind::Dots:
					{
						float y{ std::round((inner.Top + inner.Bottom) * 0.5f) };
						renderer
							->DrawRectangle(RectF{ inner.Left, y - 1, inner.Right, y + 1 }, m_aMoverForeground1Color[(int)st])
							->DrawRectangle(RectF{ inner.Left, y - 5, inner.Right, y - 3 }, m_aMoverForeground1Color[(int)st])
							->DrawRectangle(RectF{ inner.Left, y + 3, inner.Right, y + 5 }, m_aMoverForeground1Color[(int)st]);
						break;
					}
					case MoverKind::TripleDots:
					{
						CStoreBitmask store_bitmask{ renderer };
						renderer
							->ActivateBitmask(Bitmask{ 0b00010001000100010001000100010001, 0, true, false })
							->DrawLine(PointF{ inner.Left + 1, inner.Top }, PointF{ inner.Left + 1, inner.Bottom }, m_aMoverForeground1Color[(int)st])
							->DrawLine(PointF{ inner.Right, inner.Top }, PointF{ inner.Right, inner.Bottom }, m_aMoverForeground1Color[(int)st])
							->ActivateBitmask(Bitmask{ 0b01000100010001000100010001000100, 0, true, false })
							->DrawLine(PointF{ inner.Left + 3, inner.Top }, PointF{ inner.Left + 3, inner.Bottom }, m_aMoverForeground1Color[(int)st]);
						break;
					}
					default:
						break;
					}
					break;
					case Orientation::BottomToTop:
					{
						Gradient g{ CalculateGradient(m_aMoverBackgroundGradient[(int)st]) };
						DrawSimpleBackground(
							renderer,
							total,
							RectF{ m_sMoverBorderWidth.Top, m_sMoverBorderWidth.Right, m_sMoverBorderWidth.Bottom, m_sMoverBorderWidth.Left },
							RectF{ 0, 0, 0, 0 },
							m_aMoverBorderColor[(int)st],
							m_aMoverBackgroundColor[(int)st],
							g);
					}
					switch (m_eMoverKind)
					{
					case MoverKind::Line:
					{
						BlockColors colors{ Color{ 0, 0, 0, 0 }, m_aMoverForeground1Color[(int)st], Color{ 0, 0, 0, 0 }, m_aMoverForeground2Color[(int)st], Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
						renderer->DrawBlock(RectF{ inner.Left, inner.Top, inner.Right, inner.Bottom }, RectF{ 0, 1, 0, 1 }, RectF{ 0, 0, 0, 0 }, colors);
						break;
					}
					case MoverKind::DoubleLine:
					{
						BlockColors colors{ Color{ 0, 0, 0, 0 }, m_aMoverForeground1Color[(int)st], Color{ 0, 0, 0, 0 }, m_aMoverForeground2Color[(int)st], Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
						renderer
							->DrawBlock(RectF{ inner.Left, inner.Top, inner.Right, inner.Top + 2 }, RectF{ 0, 1, 0, 1 }, RectF{ 0, 0, 0, 0 }, colors)
							->DrawBlock(RectF{ inner.Left, inner.Top + 3, inner.Right, inner.Bottom }, RectF{ 0, 1, 0, 1 }, RectF{ 0, 0, 0, 0 }, colors);
						break;
					}
					case MoverKind::Dots:
					{
						float x{ std::round((inner.Left + inner.Right) * 0.5f) };
						renderer
							->DrawRectangle(RectF{ x - 1, inner.Top, x + 1, inner.Bottom }, m_aMoverForeground1Color[(int)st])
							->DrawRectangle(RectF{ x - 5, inner.Top, x - 3, inner.Bottom }, m_aMoverForeground1Color[(int)st])
							->DrawRectangle(RectF{ x + 3, inner.Top, x + 5, inner.Bottom }, m_aMoverForeground1Color[(int)st]);
						break;
					}
					case MoverKind::TripleDots:
					{
						CStoreBitmask store_bitmask{ renderer };
						renderer
							->ActivateBitmask(Bitmask{ 0b00010001000100010001000100010001, 0, true, false })
							->DrawLine(PointF{ inner.Left, inner.Top }, PointF{ inner.Right, inner.Top }, m_aMoverForeground1Color[(int)st])
							->DrawLine(PointF{ inner.Left, inner.Bottom - 1 }, PointF{ inner.Right, inner.Bottom - 1 }, m_aMoverForeground1Color[(int)st])
							->ActivateBitmask(Bitmask{ 0b01000100010001000100010001000100, 0, true, false })
							->DrawLine(PointF{ inner.Left, inner.Top + 2 }, PointF{ inner.Right, inner.Top + 2 }, m_aMoverForeground1Color[(int)st]);
						break;
					}
					default:
						break;
					}
					break;
					}
				}
			}
		}

		void CCoolBar::RenderExtra(IRenderer *renderer)
		{
			bool show_extra, has_extra_controls;
			CalculateClientRect(show_extra, has_extra_controls);
			if (show_extra)
			{
				RectF rect{ CalculateExtraRect() };
				if (rect.has_area())
				{
					State st{ CalculateExtraState() };
					switch (m_eOrientation)
					{
					case Orientation::LeftToRight:
						DrawSimpleBackground(
							renderer,
							rect,
							m_sMoverBorderWidth,
							RectF{ 0, 0, 0, 0 },
							m_aExtraBorderColor[(int)st],
							m_aExtraBackgroundColor[(int)st],
							m_aExtraBackgroundGradient[(int)st]);
						if (m_fExtraSize >= 3)
						{
							RectF inner{
								rect.Left + m_sExtraBorderWidth.Left + m_sExtraPadding.Left,
								rect.Top + m_sExtraBorderWidth.Top + m_sExtraPadding.Top,
								rect.Right - m_sExtraBorderWidth.Right - m_sExtraPadding.Right,
								rect.Bottom - m_sExtraBorderWidth.Bottom - m_sExtraPadding.Bottom };
							if (inner.height() >= m_fExtraSize)
							{
								renderer
									->DrawTriangle(
										PointF{ inner.Left, inner.Bottom - m_fExtraSize * 0.5f },
										PointF{ inner.Right, inner.Bottom - m_fExtraSize * 0.5f },
										PointF{ (inner.Left + inner.Right) * 0.5f, inner.Bottom },
										m_aExtraColor[(int)st])
									->DrawLine(
										PointF{ inner.Left, inner.Bottom - m_fExtraSize },
										PointF{ inner.Right, inner.Bottom - m_fExtraSize },
										m_aExtraColor[(int)st]);
							}
							if (m_bHasExtraControls && inner.height() >= 2 * m_fExtraSize)
							{
								float s{ std::roundf(m_fExtraSize * 0.5f - ntl::Max<float>(1, std::roundf(m_fExtraSize * 0.1f))) };
								renderer
									->DrawTriangle(
										PointF{ inner.Left, inner.Top },
										PointF{ inner.Left + s, inner.Top + m_fExtraSize * 0.5f },
										PointF{ inner.Left, inner.Top + m_fExtraSize },
										m_aExtraColor[(int)st])
									->DrawTriangle(
										PointF{ inner.Right - s, inner.Top },
										PointF{ inner.Right, inner.Top + m_fExtraSize * 0.5f },
										PointF{ inner.Right - s, inner.Top + m_fExtraSize },
										m_aExtraColor[(int)st]);
							}
						}
						break;
					case Orientation::TopToBottom:
						{
							Gradient g{ CalculateGradient(m_aExtraBackgroundGradient[(int)st]) };
							DrawSimpleBackground(
								renderer,
								rect,
								RectF{ m_sExtraBorderWidth.Bottom, m_sExtraBorderWidth.Left, m_sExtraBorderWidth.Top, m_sExtraBorderWidth.Right },
								RectF{ 0, 0, 0, 0 },
								m_aExtraBorderColor[(int)st],
								m_aExtraBackgroundColor[(int)st],
								g);
						}
						if (m_fExtraSize >= 3)
						{
							RectF inner{
								rect.Left + m_sExtraBorderWidth.Left + m_sExtraPadding.Left,
								rect.Top + m_sExtraBorderWidth.Top + m_sExtraPadding.Top,
								rect.Right - m_sExtraBorderWidth.Right - m_sExtraPadding.Right,
								rect.Bottom - m_sExtraBorderWidth.Bottom - m_sExtraPadding.Bottom };
							if (inner.height() >= m_fExtraSize)
							{
								renderer
									->DrawTriangle(
										PointF{ inner.Left, (inner.Top + inner.Bottom) * 0.5f },
										PointF{ inner.Left + m_fExtraSize * 0.5f, inner.Top },
										PointF{ inner.Left + m_fExtraSize * 0.5f, inner.Bottom },
										m_aExtraColor[(int)st])
									->DrawLine(
										PointF{ inner.Left + m_fExtraSize, inner.Top },
										PointF{ inner.Left + m_fExtraSize, inner.Bottom },
										m_aExtraColor[(int)st]);
							}
							if (m_bHasExtraControls && inner.width() >= 2 * m_fExtraSize)
							{
								float s{ std::roundf(m_fExtraSize * 0.5f - ntl::Max<float>(1, std::roundf(m_fExtraSize * 0.1f))) };
								renderer
									->DrawTriangle(
										PointF{ inner.Right - m_fExtraSize, inner.Top },
										PointF{ inner.Right, inner.Top },
										PointF{ inner.Right - m_fExtraSize * 0.5f, inner.Top + s },
										m_aExtraColor[(int)st])
									->DrawTriangle(
										PointF{ inner.Right - m_fExtraSize, inner.Bottom - s },
										PointF{ inner.Right, inner.Bottom - s },
										PointF{ inner.Right - m_fExtraSize * 0.5f, inner.Bottom },
										m_aExtraColor[(int)st]);
							}
						}
						break;
					case Orientation::RightToLeft:
						{
							Gradient g{ CalculateGradient(m_aExtraBackgroundGradient[(int)st]) };
							DrawSimpleBackground(
								renderer,
								rect,
								RectF{ m_sExtraBorderWidth.Right, m_sExtraBorderWidth.Top, m_sExtraBorderWidth.Left, m_sExtraBorderWidth.Bottom },
								RectF{ 0, 0, 0, 0 },
								m_aExtraBorderColor[(int)st],
								m_aExtraBackgroundColor[(int)st],
								g);
						}
						if (m_fExtraSize >= 3)
						{
							RectF inner{
								rect.Left + m_sExtraBorderWidth.Left + m_sExtraPadding.Left,
								rect.Top + m_sExtraBorderWidth.Top + m_sExtraPadding.Top,
								rect.Right - m_sExtraBorderWidth.Right - m_sExtraPadding.Right,
								rect.Bottom - m_sExtraBorderWidth.Bottom - m_sExtraPadding.Bottom };
							if (inner.height() >= m_fExtraSize)
							{
								renderer
									->DrawTriangle(
										PointF{ inner.Left, inner.Bottom - m_fExtraSize * 0.5f },
										PointF{ inner.Right, inner.Bottom - m_fExtraSize * 0.5f },
										PointF{ (inner.Left + inner.Right) * 0.5f, inner.Bottom },
										m_aExtraColor[(int)st])
									->DrawLine(
										PointF{ inner.Left, inner.Bottom - m_fExtraSize },
										PointF{ inner.Right, inner.Bottom - m_fExtraSize },
										m_aExtraColor[(int)st]);
							}
							if (m_bHasExtraControls && inner.height() >= 2 * m_fExtraSize)
							{
								float s{ std::roundf(m_fExtraSize * 0.5f - ntl::Max<float>(1, std::roundf(m_fExtraSize * 0.1f))) };
								renderer
									->DrawTriangle(
										PointF{ inner.Right, inner.Top },
										PointF{ inner.Right, inner.Top + m_fExtraSize },
										PointF{ inner.Right - s, inner.Top + m_fExtraSize * 0.5f },
										m_aExtraColor[(int)st])
									->DrawTriangle(
										PointF{ inner.Left + s, inner.Top },
										PointF{ inner.Left + s, inner.Top + m_fExtraSize },
										PointF{ inner.Left, inner.Top + m_fExtraSize * 0.5f },
										m_aExtraColor[(int)st]);
							}
						}
						break;
					case Orientation::BottomToTop:
						{
							Gradient g{ CalculateGradient(m_aExtraBackgroundGradient[(int)st]) };
							DrawSimpleBackground(
								renderer,
								rect,
								RectF{ m_sExtraBorderWidth.Top, m_sExtraBorderWidth.Right, m_sExtraBorderWidth.Bottom, m_sExtraBorderWidth.Left },
								RectF{ 0, 0, 0, 0 },
								m_aExtraBorderColor[(int)st],
								m_aExtraBackgroundColor[(int)st],
								g);
						}
						if (m_fExtraSize >= 3)
						{
							RectF inner{
								rect.Left + m_sExtraBorderWidth.Top + m_sExtraPadding.Top,
								rect.Top + m_sExtraBorderWidth.Right + m_sExtraPadding.Right,
								rect.Right - m_sExtraBorderWidth.Bottom - m_sExtraPadding.Bottom,
								rect.Bottom - m_sExtraBorderWidth.Left - m_sExtraPadding.Left };
							if (inner.height() >= m_fExtraSize)
							{
								renderer
									->DrawTriangle(
										PointF{ inner.Right - m_fExtraSize * 0.5f, inner.Top },
										PointF{ inner.Right, inner.Top + m_fExtraSize * 0.5f },
										PointF{ inner.Right - m_fExtraSize * 0.5f, inner.Bottom },
										m_aExtraColor[(int)st])
									->DrawLine(
										PointF{ inner.Right - m_fExtraSize, inner.Top },
										PointF{ inner.Right - m_fExtraSize, inner.Bottom },
										m_aExtraColor[(int)st]);
							}
							if (m_bHasExtraControls && inner.width() >= 2 * m_fExtraSize)
							{
								float s{ std::roundf(m_fExtraSize * 0.5f - ntl::Max<float>(1, std::roundf(m_fExtraSize * 0.1f))) };
								renderer
									->DrawTriangle(
										PointF{ inner.Left, inner.Bottom },
										PointF{ inner.Left + m_fExtraSize * 0.5f, inner.Bottom - s },
										PointF{ inner.Left + m_fExtraSize, inner.Bottom },
										m_aExtraColor[(int)st])
									->DrawTriangle(
										PointF{ inner.Left, inner.Top + s },
										PointF{ inner.Left + m_fExtraSize * 0.5f, inner.Top },
										PointF{ inner.Left + m_fExtraSize, inner.Top + s },
										m_aExtraColor[(int)st]);
							}
						}
						break;
					}
				}
			}
		}

		void CCoolBar::RenderExtraList(IRenderer *renderer, const Mat4f &matrix)
		{
			PointF disp{ DispOnCanvas(m_sExtraListShadowColor, m_sExtraListShadowShift, m_iExtraListShadowRadius) };
			RectF all_rect{ AddShadow(m_sExtraListRect, m_sExtraListShadowColor, m_sExtraListShadowShift, m_iExtraListShadowRadius) };
			if (PrepareCanvas(renderer, &m_pCanvasExtraList, all_rect))
			{
				RectF rect{ disp.X, disp.Y, disp.X + m_sExtraListRect.width(), disp.Y + m_sExtraListRect.height() };
				RectF client{
					disp.X + m_sExtraListClientRect.Left - m_sExtraListRect.Left,
					disp.Y + m_sExtraListClientRect.Top - m_sExtraListRect.Top,
					disp.X + m_sExtraListClientRect.Right - m_sExtraListRect.Left,
					disp.Y + m_sExtraListClientRect.Bottom - m_sExtraListRect.Top,
				};
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvasExtraList)
					->Clear(Color{ 0, 0, 0, 0 });
				DrawBlockShadow(
					renderer,
					rect,
					RectF{ 0, 0, 0, 0 },
					m_sExtraListShadowColor,
					m_sExtraListShadowShift,
					m_iExtraListShadowRadius);
				DrawDoubleBackground(
					renderer,
					rect,
					m_sExtraListOuterBorderWidth,
					m_sExtraListInnerBorderWidth,
					RectF{ 0, 0, 0, 0 },
					m_sExtraListOuterBorderColor,
					m_sExtraListInnerBorderColor,
					m_sExtraListBackgroundColor,
					m_cExtraListBackgroundGradient);
				if (!client.is_zero())
				{
					PointF button_size{ 0, 0 };
					if (m_pVisibilityManager)
					{
						IFont *f{ getFont() };
						IPlatformFont *pf{ f->getPlatformFont(renderer) };
						String text{ Application->Translate->t(TranslateCategory, TextAddOrRemoveButtons) };
						PointF size{ pf->getStringSize(text, f->Distance) };
						button_size = PointF{ m_sExtraListButtonRect.width(), m_sExtraListButtonRect.height() };
						if (ntl::IsLessOrEqual<float>(size.X, client.width() - m_sExtraListButtonBorderWidth.Left - m_sExtraListButtonPadding.Left - m_sExtraListButtonPadding.Right - m_sExtraListButtonBorderWidth.Right) &&
							ntl::IsLessOrEqual<float>(size.Y, client.height() - m_sExtraListButtonBorderWidth.Top - m_sExtraListButtonPadding.Top - m_sExtraListButtonPadding.Bottom - m_sExtraListButtonBorderWidth.Bottom))
						{
							RectF button_rect{ client.Left, client.Bottom - button_size.Y, client.Right, client.Bottom };
							if (m_bExtraListScrollVisible)
								button_rect.Right += m_pExtraListScroll->getWidth();
							State st{ CalculateExtraListButtonState() };
							DrawSimpleBackground(
								renderer,
								button_rect,
								m_sExtraListButtonBorderWidth,
								RectF{ 0, 0, 0, 0 },
								m_aExtraListButtonBorderColor[(int)st],
								m_aExtraListButtonBackgroundColor[(int)st],
								m_aExtraListButtonBackgroundGradient[(int)st]);
							if (button_rect.width() >= m_sExtraListButtonBorderWidth.Left + m_sExtraListButtonPadding.Left + size.X + m_sExtraListButtonPadding.Right + m_sExtraListButtonBorderWidth.Right + size.Y * 0.5f)
							{
								// Arrow
								float hs{ std::roundf(size.Y * 0.25f) }, y{ button_rect.Bottom - m_sExtraListButtonBorderWidth.Bottom - m_sExtraListButtonPadding.Bottom - 3 * hs };
								renderer->DrawTriangle(
									PointF{ button_rect.Right - m_sExtraListButtonBorderWidth.Right - m_sExtraListButtonPadding.Right - 2 * hs, y },
									PointF{ button_rect.Right - m_sExtraListButtonBorderWidth.Right - m_sExtraListButtonPadding.Right, y + hs },
									PointF{ button_rect.Right - m_sExtraListButtonBorderWidth.Right - m_sExtraListButtonPadding.Right - 2 * hs, y + 2 * hs },
									m_aExtraListButtonColor[(int)st]
								);
							}
							CStorePrimitiveMatrix s_matrix{ renderer };
							renderer
								->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(
									button_rect.Left + m_sExtraListButtonBorderWidth.Left + m_sExtraListButtonPadding.Left,
									button_rect.Bottom - m_sExtraListButtonBorderWidth.Bottom - m_sExtraListButtonPadding.Bottom - size.Y,
									0))
								->DrawText(text, pf, f->Distance, m_aExtraListButtonColor[(int)st]);
						}
					}
					if (m_bExtraListScrollVisible && client.width() > m_pExtraListScroll->getWidth() && client.height() > button_size.Y)
					{
						m_pExtraListScroll
							->Render(
								false,
								ntl::Mat4Translate<float>(
									disp.X + m_pExtraListScroll->getPosition().X - m_sExtraListRect.Left,
									disp.Y + m_pExtraListScroll->getPosition().Y - m_sExtraListRect.Top,
									0),
								nullptr);
					}
				}
				m_pCanvasExtraList->setValid(true);
			}
			DrawCanvas(renderer, matrix * ntl::Mat4Translate<float>(m_sExtraListRect.Left, m_sExtraListRect.Top, 0), m_pCanvasExtraList, disp);
		}

		void CCoolBar::RenderExtraListMask(IRenderer *renderer)
		{
			RectF rect{ 0, 0, m_sExtraListClientRect.width(), m_sExtraListClientRect.height() };
			if (m_pVisibilityManager)
				rect.Bottom = m_sExtraListButtonRect.Top - m_sExtraListClientRect.Top;
			if (PrepareCanvas(renderer, &m_pMaskExtraList, rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pMaskExtraList)
					->Clear(Color{ 0, 0, 0, 255 });
				m_pMaskExtraList->setValid(true);
			}
		}

		void CCoolBar::RenderToggleList(IRenderer *renderer, const Mat4f &matrix)
		{
			PointF disp{ DispOnCanvas(m_sToggleListShadowColor, m_sToggleListShadowShift, m_iToggleListShadowRadius) };
			RectF all_rect{ AddShadow(m_sToggleListRect, m_sToggleListShadowColor, m_sToggleListShadowShift, m_iToggleListShadowRadius) };
			if (PrepareCanvas(renderer, &m_pCanvasToggleList, all_rect))
			{
				RectF rect{ disp.X, disp.Y, disp.X + m_sToggleListRect.width(), disp.Y + m_sToggleListRect.height() }, client{ CalculateToggleListClientRect(rect) };
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvasToggleList)
					->Clear(Color{ 0, 0, 0, 0 });
				DrawBlockShadow(
					renderer,
					rect,
					RectF{ 0, 0, 0, 0 },
					m_sToggleListShadowColor,
					m_sToggleListShadowShift,
					m_iToggleListShadowRadius);
				DrawDoubleBackground(
					renderer,
					rect,
					m_sToggleListOuterBorderWidth,
					m_sToggleListInnerBorderWidth,
					RectF{ 0, 0, 0, 0 },
					m_sToggleListOuterBorderColor,
					m_sToggleListInnerBorderColor,
					m_sToggleListBackgroundColor,
					m_cToggleListBackgroundGradient);
				if (!client.is_zero())
				{
					if (m_bToggleListScrollVisible && client.width() > m_pToggleListScroll->getWidth())
					{
						m_pToggleListScroll
							->Render(
								false,
								ntl::Mat4Translate<float>(
									disp.X + m_pToggleListScroll->getPosition().X - m_sToggleListRect.Left,
									disp.Y + m_pToggleListScroll->getPosition().Y - m_sToggleListRect.Top,
									0),
								nullptr);
						client.Right -= m_pToggleListScroll->getWidth();
					}
					if (client.has_area())
					{
						IFont *f{ getFont() };
						IPlatformFont *pf{ f->getPlatformFont(renderer) };
						ITexture *icon, *checkbox;
						RectF icon_part, checkbox_part;
						String title;
						IControl *control;
						State st;
						float line_height{ m_fToggleListElementHeight - m_sToggleListElementBorderWidth.Top - m_sToggleListElementPadding.Top - m_sToggleListElementPadding.Bottom - m_sToggleListElementBorderWidth.Bottom };
						CStoreBlock s_block{ renderer };
						renderer->ActivateBlock(Block{ client, RectF{ 0, 0, 0, 0 }, RectF{ 0, 0, 0, 0 }, PointLocation::Inside });
						float y{ client.Top - (m_bToggleListScrollVisible ? m_pToggleListScroll->getScroll() : 0) }, s;
						for (int i = 0; i < getControlCount(); i++)
						{
							if (y >= client.Top - m_fToggleListElementHeight && y < client.Bottom)
							{
								control = getControl(i);
								if (!(icon = m_pVisibilityManager->getIcon(control, i, icon_part)))
									icon = FindDefaultIcon(icon_part);
								title = m_pVisibilityManager->getTitle(control, i);
								if (title.empty())
									title = Application->Translate->t(TranslateCategory, TextWidgetI, StringKeyValueArray{ {L"{i}", ToString(i + 1)} });
								st = CalculateToggleListElementState(control, i);
								checkbox = FindCheckboxIcon(m_pVisibilityManager->isVisible(control, i), st, checkbox_part);
								DrawSimpleBackground(
									renderer,
									RectF{ client.Left, y, client.Right, y + m_fToggleListElementHeight },
									m_sToggleListElementBorderWidth,
									RectF{ 0, 0, 0, 0 },
									m_aToggleListElementBorderColor[(int)st],
									m_aToggleListElementBackgroundColor[(int)st],
									m_aToggleListElementBackgroundGradient[(int)st]);
								CStorePrimitiveMatrix s_matrix{ renderer };
								if (checkbox)
								{
									s = ntl::Min<float>(1, line_height / ntl::Max<float>(checkbox_part.width(), checkbox_part.height()));
									Mat4f t1, t2;
									ntl::Translate<float>(t1, -checkbox_part.width() * 0.5f, -checkbox_part.height() * 0.5f, 0);
									ntl::Translate<float>(
										t2,
										checkbox_part.width() * 0.5f + client.Left + m_sToggleListElementBorderWidth.Left + m_sToggleListElementPadding.Left,
										checkbox_part.height() * 0.5f + y + m_sToggleListElementBorderWidth.Top + m_sToggleListElementPadding.Top, 0);
									renderer
										->ActivatePrimitiveMatrix(t2 * ntl::Mat4Scale<float>(s, s, 1) * t1)
										->DrawImage(checkbox, 1, checkbox_part);
								}
								if (icon)
								{
									s = ntl::Min<float>(1, line_height / ntl::Max<float>(icon_part.width(), icon_part.height()));
									Mat4f t1, t2;
									ntl::Translate<float>(t1, -icon_part.width() * 0.5f, -icon_part.height() * 0.5f, 0);
									ntl::Translate<float>(
										t2,
										icon_part.width() * 0.5f + client.Left + m_sToggleListElementBorderWidth.Left + m_sToggleListElementPadding.Left + line_height + m_fToggleListIconPadding,
										icon_part.height() * 0.5f + y + m_sToggleListElementBorderWidth.Top + m_sToggleListElementPadding.Top, 0);
									renderer
										->ActivatePrimitiveMatrix(t2 * ntl::Mat4Scale<float>(s, s, 1) * t1)
										->DrawImage(icon, 1, icon_part);
								}
								renderer
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(
										client.Left + m_sToggleListElementBorderWidth.Left + m_sToggleListElementPadding.Left + 2 * (line_height + m_fToggleListIconPadding),
										y + m_sToggleListElementBorderWidth.Top + m_sToggleListElementPadding.Top, 0))
									->DrawText(title, pf, f->Distance, m_aToggleListElementColor[(int)st]);
							}
							y += m_fToggleListElementHeight;
						}
					}
				}
				m_pCanvasToggleList->setValid(true);
			}
			DrawCanvas(renderer, matrix * ntl::Mat4Translate<float>(m_sToggleListRect.Left, m_sToggleListRect.Top, 0), m_pCanvasToggleList, disp);
		}
	#pragma endregion
	}
}