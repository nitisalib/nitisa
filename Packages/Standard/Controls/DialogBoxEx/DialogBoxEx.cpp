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
	#pragma region Default icons
		const Color CloseIconData[10 * 10] = {
			{ 255, 255, 255,   0}, { 107, 110, 117, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 107, 110, 117, 255}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, {   0,   0,   0, 255}, {  94,  96, 102, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 107, 110, 117, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 107, 110, 117, 255}, {   0,   0,   0, 255}, {  94,  96, 102, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 120, 123, 131, 255}, {   0,   0,   0, 255}, { 107, 110, 117, 255}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 120, 123, 131, 255}, {   0,   0,   0, 255}, {  94,  96, 102, 255}, { 107, 110, 117, 255}, {   0,   0,   0, 255}, { 107, 110, 117, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 120, 123, 131, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {  94,  96, 102, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 120, 123, 131, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {  94,  96, 102, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 120, 123, 131, 255}, {   0,   0,   0, 255}, {  94,  96, 102, 255}, { 107, 110, 117, 255}, {   0,   0,   0, 255}, { 107, 110, 117, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 107, 110, 117, 255}, {   0,   0,   0, 255}, {  94,  96, 102, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 120, 123, 131, 255}, {   0,   0,   0, 255}, { 107, 110, 117, 255}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, {   0,   0,   0, 255}, {  94,  96, 102, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 107, 110, 117, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 107, 110, 117, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 107, 110, 117, 255}, { 255, 255, 255,   0},
		};

		const Color MaximizeIconData[10 * 10] = {
			{   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0},
		};

		const Color MinimizeIconData[10 * 10] = {
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0},
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0},
		};

		const Color RestoreIconData[10 * 10] = {
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255},
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255},
			{ 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255},
			{   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255},
			{   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255},
			{   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255},
			{   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255},
			{   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0},
			{   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0},
			{   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, {   0,   0,   0, 255}, { 255, 255, 255,   0}, { 255, 255, 255,   0}, { 255, 255, 255,   0},
		};

		const Image DefaultCloseButtonIcon{ 10, 10, CloseIconData };
		const Image DefaultMaximizeButtonIcon{ 10, 10, MaximizeIconData };
		const Image DefaultMinimizeButtonIcon{ 10, 10, MinimizeIconData };
		const Image DefaultRestoreButtonIcon{ 10, 10, RestoreIconData };
	#pragma endregion

	#pragma region CTimerListener
		CDialogBoxEx::CTimerListener::CTimerListener(CDialogBoxEx *control) :
			m_pControl{ control }
		{

		}

		void CDialogBoxEx::CTimerListener::NotifyOnTimer(const PlatformHandle id)
		{
			m_pControl->m_iBlinkCounter++;
			if (m_pControl->m_iBlinkCounter >= m_pControl->m_iBlinkCount)
			{
				m_pControl->getForm()->DeleteTimer(m_pControl->m_hTimerBlink);
				m_pControl->m_hTimerBlink = nullptr;
			}
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}
	#pragma endregion

	#pragma region CGradientListener
		CDialogBoxEx::CGradientListener::CGradientListener(CDialogBoxEx *control) :
			m_pControl{ control }
		{

		}

		void CDialogBoxEx::CGradientListener::NotifyOnChange()
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
		CDialogBoxEx::CDialogBoxEx(const String &class_name, const bool accept_form, const bool accept_control, const bool accept_focus, const bool tab_stop, const Point &design_dpi, IDialogBoxService *service):
			CDialogBox(class_name, accept_form, accept_control, accept_focus, tab_stop, design_dpi, service),
			m_cGradientListener{ this },
			m_eState{ WindowState::Normal },
			m_bHasCloseBox{ true },
			m_bHasMinimizeBox{ true },
			m_bHasMaximizeBox{ true },
			m_bHasSizeBox{ true },
			m_bHasSystemMenu{ true },
			m_bHasBorder{ true },
			m_bHasCaption{ true },
			m_bIsPopup{ false },
			m_sBackgroundColor{ 41, 57, 85, 255 },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_fCaptionHeight{ 32 },
			m_sCaptionPadding{ 0, 0, 0, 0 },
			m_eCaptionHorizontalAlign{ TextAlign::Left },
			m_eCaptionVerticalAlign{ VerticalAlign::Middle },
			m_aCaptionColor{
				Color{ 214, 219, 233, 255 },
				Color{ 214, 219, 233, 255 },
				Color{ 214, 219, 233, 255 },
				Color{ 214, 219, 233, 255 },
				Color{ 240, 240, 240, 255 } },
			m_aCaptionGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aCaptionTextColor{
				Color{ 0, 0, 0, 127 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 127 } },
			m_aBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_sResizeBorderWidth{ 8, 8, 8, 8 },
			m_sMargin{ 7, 7, 7, 7 },
			m_aRimWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_sPadding{ 6, 6, 6, 6 },
			m_aBorderColor{
				BorderColor{ Color{ 13, 32, 44, 255 }, Color{ 13, 32, 44, 255 }, Color{ 13, 32, 44, 255 }, Color{ 13, 32, 44, 255 } },
				BorderColor{ Color{ 13, 32, 44, 255 }, Color{ 13, 32, 44, 255 }, Color{ 13, 32, 44, 255 }, Color{ 13, 32, 44, 255 } },
				BorderColor{ Color{ 13, 32, 44, 255 }, Color{ 13, 32, 44, 255 }, Color{ 13, 32, 44, 255 }, Color{ 13, 32, 44, 255 } },
				BorderColor{ Color{ 13, 32, 44, 127 }, Color{ 13, 32, 44, 127 }, Color{ 13, 32, 44, 127 }, Color{ 13, 32, 44, 127 } },
				BorderColor{ Color{ 240, 240, 240, 255 }, Color{ 240, 240, 240, 255 }, Color{ 240, 240, 240, 255 }, Color{ 240, 240, 240, 255 } } },
			m_sButtonSize{ 34, 26 },
			m_sButtonPadding{ 12, 8, 12, 7 },
			m_sButtonBorderWidth{ 1, 0, 1, 1 },
			m_sButtonBorderRadius{ 0, 0, 0, 0 },
			m_aButtonBorderColor{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 } },
				BorderColor{ Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 } },
				BorderColor{ Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 }, Color{ 229, 195, 101, 255 } },
				BorderColor{ Color{ 240, 240, 240, 255 }, Color{ 240, 240, 240, 255 }, Color{ 240, 240, 240, 255 }, Color{ 240, 240, 240, 255 } } },
			m_aButtonBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 255, 252, 244, 255 },
				Color{ 255, 252, 244, 255 },
				Color{ 255, 232, 166, 255 },
				Color{ 0, 0, 0, 0 } },
			m_aButtonBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_pButtonIcons{ nullptr },
			m_aCloseIconIndex{
				-1,
				-1,
				-1,
				-1,
				-1 },
			m_aMinimizeIconIndex{
				-1,
				-1,
				-1,
				-1,
				-1 },
			m_aMaximizeIconIndex{
				-1,
				-1,
				-1,
				-1,
				-1 },
			m_aRestoreIconIndex{
				-1,
				-1,
				-1,
				-1,
				-1 },
			m_bUseMask{ true },
			m_bUseDefaultCloseIcon{ true },
			m_bUseDefaultMinimizeIcon{ true },
			m_bUseDefaultMaximizeIcon{ true },
			m_bUseDefaultRestoreIcon{ true },
			m_aShadowColor{
				Color{ 0, 0, 0, 32 },
				Color{ 0, 0, 0, 32 },
				Color{ 0, 0, 0, 32 },
				Color{ 0, 0, 0, 64 },
				Color{ 0, 0, 0, 32 } },
			m_aShadowRadius{
				10,
				10,
				10,
				10,
				10 },
			m_aShadowShift{
				PointF{ 8, 8 },
				PointF{ 8, 8 },
				PointF{ 8, 8 },
				PointF{ 8, 8 },
				PointF{ 8, 8 } },
			m_fMinimizedWidth{ 200 },
			m_sIconPadding{ 4, 4, 4, 4 },
			m_pIcons{ nullptr },
			m_aIconIndex{
				-1,
				-1,
				-1,
				-1,
				-1 },
			m_fBlinkInterval{ 0.07f },
			m_iBlinkCount{ 10 },
			m_pCanvas{ nullptr },
			m_pMask{ nullptr },
			m_bIgnoreGradient{ false },
			m_hTimerBlink{ nullptr },
			m_eHoveredElement{ Element::None },
			m_eDownElement{ Element::None },
			m_sNormalSize{ 0, 0 },
			m_sNormalTransform{ getTransform()->getTransform() },
			m_cTimerListener{ this }
		{
			UpdateTransformControls();
			setSize(PointF{ 320, 240 });
		}

		CDialogBoxEx::CDialogBoxEx() : CDialogBoxEx(L"DialogBoxEx", true, true, false, false, DesignDPI, new CDialogBoxExService(this))
		{

		}

		CDialogBoxEx::CDialogBoxEx(IControl *parent) : CDialogBoxEx()
		{
			setParent(parent);
		}

		CDialogBoxEx::CDialogBoxEx(IForm *parent) : CDialogBoxEx()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region IControl getters
		RectF CDialogBoxEx::getClientRect()
		{
			RectF result{ getRect() }, margin{ CalculateMargin() }, rim{ CalculateRimWidth() };
			float caption_height{ CalculateCaptionHeight() };
			result.Left += margin.Left + rim.Left + m_sPadding.Left;
			result.Top += margin.Top + rim.Top + caption_height + m_sPadding.Top;
			result.Right -= margin.Right + rim.Right + m_sPadding.Right;
			result.Bottom -= margin.Bottom + rim.Bottom + m_sPadding.Bottom;
			return result;
		}

		RectF CDialogBoxEx::getRenderRect()
		{
			RectF result{ getRect() };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result += AddShadow(getRect(), m_aShadowColor[i], m_aShadowShift[i], m_aShadowRadius[i]);
			return result;
		}

		CursorType CDialogBoxEx::getCursor()
		{
			if (!m_bIsPopup && m_bHasSizeBox && m_eState == WindowState::Normal)
			{
				switch (getElement())
				{
				case Element::LeftTopCorner:
				case Element::RightBottomCorner:
					return CursorType::SizeNorthwestSoutheast;
				case Element::LeftBottomCorner:
				case Element::RightTopCorner:
					return CursorType::SizeNortheastSouthwest;
				case Element::LeftBorder:
				case Element::RightBorder:
					return CursorType::SizeWestEast;
				case Element::TopBorder:
				case Element::BottomBorder:
					return CursorType::SizeNorthSouth;
				case Element::ButtonClose:
				case Element::ButtonMaximize:
				case Element::ButtonMinimize:
				case Element::ButtonRestore:
					return CursorType::Arrow;
				default:
					break;
				}
			}
			return CDialogBox::getCursor();
		}
	#pragma endregion

	#pragma region IControl setters
		bool CDialogBoxEx::setAlign(const Align value)
		{
			return false;
		}

		bool CDialogBoxEx::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			if (CDialogBox::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_fCaptionHeight *= s.Y;
				m_sCaptionPadding *= s;
				m_sResizeBorderWidth *= s;
				m_sMargin *= s;
				m_sPadding *= s;
				m_sButtonSize *= s;
				m_sButtonPadding *= s;
				m_sButtonBorderWidth *= s;
				m_sButtonBorderRadius *= avg;
				m_sIconPadding *= s;
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aShadowRadius[i] = ntl::Max<int>(1, ntl::Round<int>((float)m_aShadowRadius[i] * avg));
					m_aShadowShift[i] *= s;
				}
				for (int i = 0; i <= (int)WindowState::Hidden; i++)
				{
					m_aBorderRadius[i] *= avg;
					m_aRimWidth[i] *= s;
				}
				UpdateTransformControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(true);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IControl methods
		void CDialogBoxEx::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			if (m_pMask)
				m_pMask->setValid(false);
			CControl::Refresh(refresh_children);
		}
	#pragma endregion

	#pragma region IDialogBox getters
		Color CDialogBoxEx::getBackgroundColor()
		{
			return m_sBackgroundColor;
		}

		String CDialogBoxEx::getCaption()
		{
			return m_sCaption;
		}

		WindowState CDialogBoxEx::getState()
		{
			return m_eState;
		}

		RectF CDialogBoxEx::getBorderWidth()
		{
			return m_sPadding;
		}

		bool CDialogBoxEx::hasCloseBox()
		{
			return m_bHasCloseBox;
		}

		bool CDialogBoxEx::hasMaximizeBox()
		{
			return m_bHasMaximizeBox;
		}

		bool CDialogBoxEx::hasMinimizeBox()
		{
			return m_bHasMinimizeBox;
		}

		bool CDialogBoxEx::hasSizeBox()
		{
			return m_bHasSizeBox;
		}

		bool CDialogBoxEx::hasSystemMenu()
		{
			return m_bHasSystemMenu;
		}

		bool CDialogBoxEx::hasBorder()
		{
			return m_bHasBorder;
		}

		bool CDialogBoxEx::hasCaption()
		{
			return m_bHasCaption;
		}

		bool CDialogBoxEx::isPopup()
		{
			return m_bIsPopup;
		}
	#pragma endregion

	#pragma region IDialogBox setters
		bool CDialogBoxEx::setBackgroundColor(const Color &value)
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

		bool CDialogBoxEx::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				if (m_bHasCaption && !m_bIsPopup)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setClientSize(const Point &value)
		{
			if (value.X >= 0 && value.Y >= 0)
			{
				RectF client{ getClientRect() };
				PointF size{ client.width(), client.height() };
				if (IsNotEqual((PointF)value, size) || m_eState != WindowState::Normal)
				{
					CLockRepaint lock{ this };
					if (m_eState != WindowState::Hidden)
						setState(WindowState::Normal);
					size = (PointF)value;
					RectF margin{ CalculateMargin() }, rim{ CalculateRimWidth() };
					float caption_height{ CalculateCaptionHeight() };
					size.X += margin.Left + margin.Right + rim.Left + rim.Right + m_sPadding.Left + m_sPadding.Right;
					size.Y += margin.Top + margin.Bottom + rim.Top + rim.Bottom + m_sPadding.Top + m_sPadding.Bottom + caption_height;
					UpdateTransformControls();
					return setSize(size);
				}
			}
			return false;
		}

		bool CDialogBoxEx::setState(const WindowState value)
		{
			if (value != m_eState)
			{
				switch (value)
				{
				case WindowState::Normal:
					return Restore();
				case WindowState::Maximized:
					return Maximize();
				case WindowState::Minimized:
					return Minimize();
				case WindowState::Hidden:
					return Hide();
				}
			}
			return false;
		}

		bool CDialogBoxEx::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				m_sPadding = value;
				UpdateTransformControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(true);
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setHasCloseBox(const bool value)
		{
			if (value != m_bHasCloseBox)
			{
				m_bHasCloseBox = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setHasMaximizeBox(const bool value)
		{
			if (value != m_bHasMaximizeBox)
			{
				m_bHasMaximizeBox = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setHasMinimizeBox(const bool value)
		{
			if (value != m_bHasMinimizeBox)
			{
				m_bHasMinimizeBox = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setHasSizeBox(const bool value)
		{
			if (value != m_bHasSizeBox)
			{
				m_bHasSizeBox = value;
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setHasSystemMenu(const bool value)
		{
			if (value != m_bHasSystemMenu)
			{
				m_bHasSystemMenu = value;
				if (m_bHasCaption && !m_bIsPopup)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setHasBorder(const bool value)
		{
			if (value != m_bHasBorder)
			{
				m_bHasBorder = value;
				if (!m_bIsPopup)
				{
					UpdateTransformControls();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setHasCaption(const bool value)
		{
			if (value != m_bHasCaption)
			{
				m_bHasCaption = value;
				if (!m_bIsPopup)
				{
					UpdateTransformControls();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setIsPopup(const bool value)
		{
			if (value != m_bIsPopup)
			{
				m_bIsPopup = value;
				UpdateTransformControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IDialogBox methods
		bool CDialogBoxEx::Maximize()
		{
			if (m_eState != WindowState::Maximized)
			{
				CLockRepaint lock{ this };
				m_eState = WindowState::Maximized;
				setVisible(true);
				FitInParent();
				UpdateTransformControls();
				if (OnMaximize)
					OnMaximize(this);
				if (getDialogBoxListener())
					getDialogBoxListener()->OnMaximize(this);
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::Minimize()
		{
			if (m_eState != WindowState::Minimized)
			{
				CLockRepaint lock{ this };
				m_eState = WindowState::Minimized;
				setVisible(true);
				setSize(PointF{ m_fMinimizedWidth, CalculateMinimizedHeight() });
				getTransform()->Translate(CalculateMinimizedXPosition(), CalculateMinimizedYPosition(), 0);
				UpdateTransformControls();
				if (OnMinimize)
					OnMinimize(this);
				if (getDialogBoxListener())
					getDialogBoxListener()->OnMinimize(this);
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::Restore()
		{
			if (m_eState != WindowState::Normal)
			{
				CLockRepaint lock{ this };
				m_eState = WindowState::Normal;
				setVisible(true);
				setSize(m_sNormalSize);
				getTransform()->setTransform(m_sNormalTransform);
				UpdateTransformControls();
				if (OnRestore)
					OnRestore(this);
				if (getDialogBoxListener())
					getDialogBoxListener()->OnRestore(this);
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::Hide()
		{
			if (m_eState != WindowState::Hidden)
			{
				CLockRepaint lock{ this };
				m_eState = WindowState::Hidden;
				setVisible(false);
				if (getDialogBoxListener())
					getDialogBoxListener()->OnClose(this);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IDialogBoxEx methods
		void CDialogBoxEx::AutoResize(const bool transform)
		{
			if (getControlCount() > 0)
			{
				bool first{ true };
				RectF bound, r;
				IControl *control;
				Mat4f m;
				for (int i = 0; i < getControlCount(); i++)
					if ((control = getControl(i)) && control->isVisible(false))
					{
						m = control->getTransform()->getMatrix();
						r = TransformRect(control->getRenderRect(), m);
						if (first)
						{
							bound = r;
							first = false;
						}
						else
						{
							bound.Left = ntl::Min<float>(bound.Left, r.Left);
							bound.Top = ntl::Min<float>(bound.Top, r.Top);
							bound.Right = ntl::Max<float>(bound.Right, r.Right);
							bound.Bottom = ntl::Max<float>(bound.Bottom, r.Bottom);
						}
						CalculateBound(control, bound, m * control->getTransformControls()->getMatrix());
					}
				if (!first)
				{
					CLockRepaint lock{ this };
					setPadding(RectF{ 0, 0, 0, 0 });
					setClientSize(Point{ ntl::Round<int>(bound.Right + bound.Left), ntl::Round<int>(bound.Bottom + bound.Top) });
					UpdateTransformControls();
					if (transform)
						Translate();
				}
			}
		}
	#pragma endregion

	#pragma region Getters
		CDialogBoxEx::State CDialogBoxEx::getControlState()
		{
			if (m_hTimerBlink)
				return State::Blinking;
			if (isModal())
				return State::Modal;
			if (!isEnabled(false))
				return State::Disabled;
			if (isActiveDialogBox())
				return State::Active;
			return State::Normal;
		}

		bool CDialogBoxEx::isUseMask() const
		{
			return m_bUseMask;
		}

		Gradient *CDialogBoxEx::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		float CDialogBoxEx::getCaptionHeight() const
		{
			return m_fCaptionHeight;
		}

		RectF CDialogBoxEx::getCaptionPadding() const
		{
			return m_sCaptionPadding;
		}

		TextAlign CDialogBoxEx::getCaptionHorizontalAlign() const
		{
			return m_eCaptionHorizontalAlign;
		}

		VerticalAlign CDialogBoxEx::getCaptionVerticalAlign() const
		{
			return m_eCaptionVerticalAlign;
		}

		Color CDialogBoxEx::getCaptionColor(const State state) const
		{
			return m_aCaptionColor[(int)state];
		}

		Gradient *CDialogBoxEx::getCaptionGradient(const State state)
		{
			return &m_aCaptionGradient[(int)state];
		}

		Color CDialogBoxEx::getCaptionTextColor(const State state) const
		{
			return m_aCaptionTextColor[(int)state];
		}

		RectF CDialogBoxEx::getBorderRadius(const WindowState state) const
		{
			return m_aBorderRadius[(int)state];
		}

		RectF CDialogBoxEx::getResizeBorderWidth() const
		{
			return m_sResizeBorderWidth;
		}

		RectF CDialogBoxEx::getMargin() const
		{
			return m_sMargin;
		}

		RectF CDialogBoxEx::getRimWidth(const WindowState state) const
		{
			return m_aRimWidth[(int)state];
		}

		RectF CDialogBoxEx::getPadding() const
		{
			return m_sPadding;
		}

		BorderColor CDialogBoxEx::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		PointF CDialogBoxEx::getButtonSize() const
		{
			return m_sButtonSize;
		}

		RectF CDialogBoxEx::getButtonPadding() const
		{
			return m_sButtonPadding;
		}

		RectF CDialogBoxEx::getButtonBorderWidth() const
		{
			return m_sButtonBorderWidth;
		}

		RectF CDialogBoxEx::getButtonBorderRadius() const
		{
			return m_sButtonBorderRadius;
		}

		BorderColor CDialogBoxEx::getButtonBorderColor(const ButtonState state) const
		{
			return m_aButtonBorderColor[(int)state];
		}

		Color CDialogBoxEx::getButtonBackgroundColor(const ButtonState state) const
		{
			return m_aButtonBackgroundColor[(int)state];
		}

		Gradient *CDialogBoxEx::getButtonBackgroundGradient(const ButtonState state)
		{
			return &m_aButtonBackgroundGradient[(int)state];
		}

		IImageList *CDialogBoxEx::getButtonIcons()
		{
			return m_pButtonIcons;
		}

		int CDialogBoxEx::getCloseIconIndex(const ButtonState state) const
		{
			return m_aCloseIconIndex[(int)state];
		}

		int CDialogBoxEx::getMinimizeIconIndex(const ButtonState state) const
		{
			return m_aMinimizeIconIndex[(int)state];
		}

		int CDialogBoxEx::getMaximizeIconIndex(const ButtonState state) const
		{
			return m_aMaximizeIconIndex[(int)state];
		}

		int CDialogBoxEx::getRestoreIconIndex(const ButtonState state) const
		{
			return m_aRestoreIconIndex[(int)state];
		}

		bool CDialogBoxEx::isUseDefaultCloseIcon() const
		{
			return m_bUseDefaultCloseIcon;
		}

		bool CDialogBoxEx::isUseDefaultMinimizeIcon() const
		{
			return m_bUseDefaultMinimizeIcon;
		}

		bool CDialogBoxEx::isUseDefaultMaximizeIcon() const
		{
			return m_bUseDefaultMaximizeIcon;
		}

		bool CDialogBoxEx::isUseDefaultRestoreIcon() const
		{
			return m_bUseDefaultRestoreIcon;
		}

		Color CDialogBoxEx::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		int CDialogBoxEx::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CDialogBoxEx::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		float CDialogBoxEx::getMinimizedWidth() const
		{
			return m_fMinimizedWidth;
		}

		RectF CDialogBoxEx::getIconPadding() const
		{
			return m_sIconPadding;
		}

		IImageList *CDialogBoxEx::getIcons()
		{
			return m_pIcons;
		}

		int CDialogBoxEx::getIconIndex(const State state) const
		{
			return m_aIconIndex[(int)state];
		}

		float CDialogBoxEx::getBlinkInterval() const
		{
			return m_fBlinkInterval;
		}

		int CDialogBoxEx::getBlinkCount() const
		{
			return m_iBlinkCount;
		}
	#pragma endregion

	#pragma region Setters
		bool CDialogBoxEx::setUseMask(const bool value)
		{
			if (value != m_bUseMask)
			{
				m_bUseMask = value;
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(true);
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setCaptionHeight(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fCaptionHeight))
			{
				m_fCaptionHeight = value;
				if (!m_bIsPopup && m_bHasCaption)
				{
					UpdateTransformControls();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					if (m_pMask)
						m_pMask->setValid(false);
					Repaint(true);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setCaptionPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sCaptionPadding))
			{
				m_sCaptionPadding = value;
				if (!m_bIsPopup && m_bHasCaption && ntl::IsGreater<float>(m_fCaptionHeight, 0) && !m_sCaption.empty())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setCaptionHorizontalAlign(const TextAlign value)
		{
			if (value != m_eCaptionHorizontalAlign)
			{
				m_eCaptionHorizontalAlign = value;
				if (!m_bIsPopup && m_bHasCaption && ntl::IsGreater<float>(m_fCaptionHeight, 0) && !m_sCaption.empty())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setCaptionVerticalAlign(const VerticalAlign value)
		{
			if (value != m_eCaptionVerticalAlign)
			{
				m_eCaptionVerticalAlign = value;
				if (!m_bIsPopup && m_bHasCaption && ntl::IsGreater<float>(m_fCaptionHeight, 0) && !m_sCaption.empty())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setCaptionColor(const State state, const Color &value)
		{
			if (value != m_aCaptionColor[(int)state])
			{
				m_aCaptionColor[(int)state] = value;
				if (!m_bIsPopup && m_bHasCaption && ntl::IsGreater<float>(m_fCaptionHeight, 0) && state == getControlState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setCaptionTextColor(const State state, const Color &value)
		{
			if (value != m_aCaptionTextColor[(int)state])
			{
				m_aCaptionTextColor[(int)state] = value;
				if (!m_bIsPopup && m_bHasCaption && ntl::IsGreater<float>(m_fCaptionHeight, 0) && !m_sCaption.empty() && state == getControlState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setBorderRadius(const WindowState state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBorderRadius[(int)state]))
			{
				m_aBorderRadius[(int)state] = value;
				if (state == m_eState)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					if (m_pMask)
						m_pMask->setValid(false);
					Repaint(true);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setResizeBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sResizeBorderWidth))
			{
				m_sResizeBorderWidth = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(true);
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setMargin(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sMargin))
			{
				m_sMargin = value;
				if (!m_bIsPopup && m_eState == WindowState::Normal)
				{
					UpdateTransformControls();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					if (m_pMask)
						m_pMask->setValid(false);
					Repaint(true);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setRimWidth(const WindowState state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aRimWidth[(int)state]))
			{
				m_aRimWidth[(int)state] = value;
				if (!m_bIsPopup && m_bHasBorder && state == m_eState)
				{
					UpdateTransformControls();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					if (m_pMask)
						m_pMask->setValid(false);
					Repaint(true);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				m_sPadding = value;
				UpdateTransformControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(true);
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
				if (!m_bIsPopup && m_bHasBorder && state == getControlState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setButtonSize(const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_sButtonSize))
			{
				m_sButtonSize = value;
				if (!m_bIsPopup)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setButtonPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sButtonPadding))
			{
				m_sButtonPadding = value;
				if (!m_bIsPopup && (m_bHasCloseBox || m_bHasMaximizeBox || m_bHasMinimizeBox))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setButtonBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sButtonBorderWidth))
			{
				m_sButtonBorderWidth = value;
				if (!m_bIsPopup && (m_bHasCloseBox || m_bHasMaximizeBox || m_bHasMinimizeBox))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setButtonBorderRadius(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sButtonBorderRadius))
			{
				m_sButtonBorderRadius = value;
				if (!m_bIsPopup && (m_bHasCloseBox || m_bHasMaximizeBox || m_bHasMinimizeBox))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setButtonBorderColor(const ButtonState state, const BorderColor &value)
		{
			if (value != m_aButtonBorderColor[(int)state])
			{
				m_aButtonBorderColor[(int)state] = value;
				if (!m_bIsPopup && (m_bHasCloseBox || m_bHasMaximizeBox || m_bHasMinimizeBox))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setButtonBackgroundColor(const ButtonState state, const Color &value)
		{
			if (value != m_aButtonBackgroundColor[(int)state])
			{
				m_aButtonBackgroundColor[(int)state] = value;
				if (!m_bIsPopup && (m_bHasCloseBox || m_bHasMaximizeBox || m_bHasMinimizeBox))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setButtonIcons(IImageList *value)
		{
			if (value != m_pButtonIcons)
			{
				m_pButtonIcons = value;
				if (!m_bIsPopup && (m_bHasCloseBox || m_bHasMaximizeBox || m_bHasMinimizeBox))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setCloseIconIndex(const ButtonState state, const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_aCloseIconIndex[(int)state])
			{
				m_aCloseIconIndex[(int)state] = v;
				if (!m_bIsPopup && m_pButtonIcons && m_bHasCloseBox)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setMinimizeIconIndex(const ButtonState state, const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_aMinimizeIconIndex[(int)state])
			{
				m_aMinimizeIconIndex[(int)state] = v;
				if (!m_bIsPopup && m_pButtonIcons && m_bHasMinimizeBox)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setMaximizeIconIndex(const ButtonState state, const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_aMaximizeIconIndex[(int)state])
			{
				m_aMaximizeIconIndex[(int)state] = v;
				if (!m_bIsPopup && m_pButtonIcons && m_bHasMaximizeBox)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setRestoreIconIndex(const ButtonState state, const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_aRestoreIconIndex[(int)state])
			{
				m_aRestoreIconIndex[(int)state] = v;
				if (!m_bIsPopup && m_pButtonIcons && (m_bHasMinimizeBox || m_bHasMaximizeBox))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setUseDefaultCloseIcon(const bool value)
		{
			if (value != m_bUseDefaultCloseIcon)
			{
				m_bUseDefaultCloseIcon = value;
				if (!m_bIsPopup && m_bHasCloseBox)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setUseDefaultMinimizeIcon(const bool value)
		{
			if (value != m_bUseDefaultMinimizeIcon)
			{
				m_bUseDefaultMinimizeIcon = value;
				if (!m_bIsPopup && m_bHasMinimizeBox)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setUseDefaultMaximizeIcon(const bool value)
		{
			if (value != m_bUseDefaultMaximizeIcon)
			{
				m_bUseDefaultMaximizeIcon = value;
				if (!m_bIsPopup && m_bHasMaximizeBox)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setUseDefaultRestoreIcon(const bool value)
		{
			if (value != m_bUseDefaultRestoreIcon)
			{
				m_bUseDefaultRestoreIcon = value;
				if (!m_bIsPopup && (m_bHasMinimizeBox || m_bHasMaximizeBox))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
				CLockRepaint lock{ this };
				State st{ getControlState() };
				if (st == state && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowColor[(int)state] = value;
				if (state == getControlState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				State st{ getControlState() };
				if (st == state && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowRadius[(int)state] = value;
				if (state == getControlState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				State st{ getControlState() };
				if (st == state && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowShift[(int)state] = value;
				if (state == getControlState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setMinimizedWidth(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fMinimizedWidth))
			{
				m_fMinimizedWidth = value;
				if (m_eState == WindowState::Minimized)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setIconPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sIconPadding))
			{
				m_sIconPadding = value;
				if (!m_bIsPopup && m_bHasCaption && m_bHasSystemMenu && m_pIcons && m_aIconIndex[(int)getControlState()] >= 0 && ntl::IsGreater<float>(m_fCaptionHeight, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setIcons(IImageList *value)
		{
			if (value != m_pIcons)
			{
				m_pIcons = value;
				if (!m_bIsPopup && m_bHasCaption && m_bHasSystemMenu && m_aIconIndex[(int)getControlState()] >= 0 && ntl::IsGreater<float>(m_fCaptionHeight, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setIconIndex(const State state, const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_aIconIndex[(int)state])
			{
				m_aIconIndex[(int)state] = v;
				if (!m_bIsPopup && m_bHasCaption && m_bHasSystemMenu && m_pIcons && ntl::IsGreater<float>(m_fCaptionHeight, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setBlinkInterval(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fBlinkInterval))
			{
				m_fBlinkInterval = value;
				return true;
			}
			return false;
		}

		bool CDialogBoxEx::setBlinkCount(const int value)
		{
			if (value > 0 && value != m_iBlinkCount)
			{
				m_iBlinkCount = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CDialogBoxEx::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".CaptionHeight", m_fCaptionHeight);
			style->getOption(m_sClassName + L".CaptionPadding", m_sCaptionPadding);
			style->getOption(m_sClassName + L".ResizeBorderWidth", m_sResizeBorderWidth);
			style->getOption(m_sClassName + L".Margin", m_sMargin);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			style->getOption(m_sClassName + L".ButtonSize", m_sButtonSize);
			style->getOption(m_sClassName + L".ButtonPadding", m_sButtonPadding);
			style->getOption(m_sClassName + L".ButtonBorderWidth", m_sButtonBorderWidth);
			style->getOption(m_sClassName + L".ButtonBorderRadius", m_sButtonBorderRadius);
			style->getOption(m_sClassName + L".MinimizeWidth", m_fMinimizedWidth);
			style->getOption(m_sClassName + L".IconPudding", m_sIconPadding);
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String state;
				switch ((State)i)
				{
				case State::Active:
					state = L"Active";
					break;
				case State::Modal:
					state = L"Modal";
					break;
				case State::Blinking:
					state = L"Blinking";
					break;
				case State::Disabled:
					state = L"Disabled";
					break;
				default:
					state = L"Normal";
				}
				style->getOption(m_sClassName + L".CaptionColor[" + state + L"]", m_aCaptionColor[i]);
				style->getOption(m_sClassName + L".CaptionGradient[" + state + L"]", m_aCaptionGradient[i]);
				style->getOption(m_sClassName + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]);
				style->getOption(m_sClassName + L".BorderColor[" + state + L"]", m_aBorderColor[i]);
				style->getOption(m_sClassName + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
			}
			for (int i = 0; i <= (int)ButtonState::Disabled; i++)
			{
				String state;
				switch ((ButtonState)i)
				{
				case ButtonState::Hovered:
					state = L"Hovered";
					break;
				case ButtonState::Down:
					state = L"Down";
					break;
				case ButtonState::DownHovered:
					state = L"DownHovered";
					break;
				case ButtonState::Disabled:
					state = L"Disabled";
					break;
				default:
					state = L"Normal";
				}
				style->getOption(m_sClassName + L".ButtonBorderColor[" + state + L"]", m_aButtonBorderColor[i]);
				style->getOption(m_sClassName + L".ButtonBackgroundColor[" + state + L"]", m_aButtonBackgroundColor[i]);
				style->getOption(m_sClassName + L".ButtonBackgroundGradient[" + state + L"]", m_aButtonBackgroundGradient[i]);
			}
			for (int i = 0; i <= (int)WindowState::Hidden; i++)
			{
				String state;
				switch ((WindowState)i)
				{
				case WindowState::Maximized:
					state = L"Maximized";
					break;
				case WindowState::Minimized:
					state = L"Minimized";
					break;
				case WindowState::Hidden:
					state = L"Hidden";
					break;
				default:
					state = L"Normal";
				}
				style->getOption(m_sClassName + L".BorderRadius[" + state + L"]", m_aBorderRadius[i]);
				style->getOption(m_sClassName + L".RimWidth[" + state + L"]", m_aRimWidth[i]);
			}
			UpdateTransformControls();
			m_bIgnoreGradient = false;
		}

		CDialogBoxEx::Element CDialogBoxEx::getElement()
		{
			if (getForm())
				return getElement(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())));
			return Element::None;
		}

		CDialogBoxEx::Element CDialogBoxEx::getElement(const PointF &p)
		{
			if (p.X >= 0 && p.X < getWidth() && p.Y >= 0 && p.Y < getHeight())
			{
				RectF close, maximize, minimize, restore;
				getButtonRects(close, maximize, minimize, restore);
				if (p.X >= close.Left && p.X < close.Right && p.Y >= close.Top && p.Y < close.Bottom)
					return Element::ButtonClose;
				if (p.X >= maximize.Left && p.X < maximize.Right && p.Y >= maximize.Top && p.Y < maximize.Bottom)
					return Element::ButtonMaximize;
				if (p.X >= minimize.Left && p.X < minimize.Right && p.Y >= minimize.Top && p.Y < minimize.Bottom)
					return Element::ButtonMinimize;
				if (p.X >= restore.Left && p.X < restore.Right && p.Y >= restore.Top && p.Y < restore.Bottom)
					return Element::ButtonRestore;
				RectF icon{ getIconRect() };
				if (p.X >= icon.Left && p.X < icon.Right && p.Y >= icon.Top && p.Y < icon.Bottom)
					return Element::Icon;
				RectF caption{ getCaptionRect(close, maximize, minimize, restore) };
				if (p.X >= caption.Left && p.X < caption.Right && p.Y >= caption.Top && p.Y < caption.Bottom)
					return Element::Caption;
				RectF resize{ CalculateResizeBorderWidth() }, margin{ CalculateMargin() }, rim{ CalculateRimWidth() };
				if (p.X < resize.Left)
				{
					if (p.Y < resize.Top)
						return Element::LeftTopCorner;
					if (p.Y >= getHeight() - resize.Bottom)
						return Element::LeftBottomCorner;
					return Element::LeftBorder;
				}
				if (p.X >= getWidth() - resize.Right)
				{
					if (p.Y < resize.Top)
						return Element::RightTopCorner;
					if (p.Y >= getHeight() - resize.Bottom)
						return Element::RightBottomCorner;
					return Element::RightBorder;
				}
				if (p.Y < resize.Top)
					return Element::TopBorder;
				if (p.Y < margin.Top + rim.Top + CalculateCaptionHeight())
					return Element::Caption;
				if (p.Y >= getHeight() - resize.Bottom)
					return Element::BottomBorder;
				return Element::Client;
			}
			return Element::None;
		}

		void CDialogBoxEx::getButtonRects(RectF &close, RectF &maximize, RectF &minimize, RectF &restore)
		{
			RectF margin{ CalculateMargin() }, rim{ CalculateRimWidth() };
			float x{ getWidth() }, y{ 0 };
			x -= margin.Right + rim.Right;
			y += margin.Top + rim.Top;
			close = maximize = minimize = restore = RectF{ x, y, x, y + m_sButtonSize.Y };
			if (!m_bIsPopup)
			{
				if (m_bHasCloseBox)
				{
					x -= m_sButtonSize.X;
					close.Left = x;
				}
				if (m_bHasMaximizeBox)
				{
					if (m_eState == WindowState::Maximized)
					{
						restore.Right = x;
						x -= m_sButtonSize.X;
						restore.Left = x;
					}
					else
					{
						maximize.Right = x;
						x -= m_sButtonSize.X;
						maximize.Left = x;
					}
				}
				if (m_bHasMinimizeBox)
				{
					if (m_eState == WindowState::Minimized)
					{
						restore.Right = x;
						x -= m_sButtonSize.X;
						restore.Left = x;
					}
					else
					{
						minimize.Right = x;
						x -= m_sButtonSize.X;
						minimize.Left = x;
					}
				}
			}
		}

		RectF CDialogBoxEx::getIconRect()
		{
			RectF margin{ CalculateMargin() }, rim{ CalculateRimWidth() };
			float caption_height{ CalculateCaptionHeight() };
			RectF result{ margin.Left + rim.Left, margin.Top + rim.Top, margin.Left + rim.Left, margin.Top + rim.Top };
			if (m_bHasCaption && m_bHasSystemMenu)
			{
				result.Right = result.Left + caption_height;
				result.Bottom = result.Top + caption_height;
			}
			return result;
		}

		RectF CDialogBoxEx::getCaptionRect(const RectF &close, const RectF &maximize, const RectF &minimize, const RectF &restore)
		{
			RectF margin{ CalculateMargin() }, rim{ CalculateRimWidth() };
			float caption_height{ CalculateCaptionHeight() };
			RectF result{ margin.Left + rim.Left, margin.Top + rim.Top, ntl::Min<float>(close.Left, maximize.Left, minimize.Left, restore.Left), margin.Top + rim.Top + caption_height };
			if (m_bHasSystemMenu)
				result.Left += caption_height;
			return result;
		}

		CDialogBoxEx::ButtonState CDialogBoxEx::getButtonState(const Element el)
		{
			if (!isEnabled(false))
				return ButtonState::Disabled;
			if (m_eDownElement == el)
			{
				if (m_eHoveredElement == el)
					return ButtonState::DownHovered;
				return ButtonState::Down;
			}
			if (m_eHoveredElement == el)
				return ButtonState::Hovered;
			return ButtonState::Normal;
		}

		ITexture *CDialogBoxEx::getButtonIcon(IRenderer *renderer, const bool use_default, const Image &default_icon, IImageList *icons, const int icon_index)
		{
			if (use_default)
				return renderer->CreateTextureFromImage(default_icon, 1, TextureFormat::RGBA, true);
			if (icons && icon_index >= 0)
				return icons->getTexture(icon_index);
			return nullptr;
		}

		bool CDialogBoxEx::UpdateHoveredElement()
		{
			if (getForm())
				return UpdateHoveredElement(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())));
			return false;
		}

		bool CDialogBoxEx::UpdateHoveredElement(const PointF &p)
		{
			Element e{ getElement(p) };
			if (e != m_eHoveredElement)
			{
				m_eHoveredElement = e;
				return true;
			}
			return false;
		}

		float CDialogBoxEx::CalculateMinimizedXPosition()
		{
			float x{ 0 };
			if (getParent())
			{
				x = getParent()->getClientRect().Left;
				IControl *control;
				IDialogBox *dlg;
				for (int i = 0; i < getParent()->getControlCount(); i++)
				{
					control = getParent()->getControl(i);
					if (control != this && control->isVisible(false) && control->getAlign() == Align::None && (dlg = cast<IDialogBox*>(control)) && dlg->getState() == WindowState::Minimized)
						x = ntl::Max<float>(x, control->getTransform()->getTx() + control->getRenderRect().Right);
				}
			}
			else if (getForm())
			{
				x = (float)getForm()->getClientRect().Left;
				IControl *control;
				IDialogBox *dlg;
				for (int i = 0; i < getForm()->getControlCount(); i++)
				{
					control = getForm()->getControl(i);
					if (control != this && control->isVisible(false) && control->getAlign() == Align::None && (dlg = cast<IDialogBox*>(control)) && dlg->getState() == WindowState::Minimized)
						x = ntl::Max<float>(x, control->getTransform()->getTx() + control->getRenderRect().Right);
				}
			}
			return x;
		}

		float CDialogBoxEx::CalculateMinimizedYPosition()
		{
			if (getParent())
				return ntl::Max<float>(0, getParent()->getClientRect().Bottom - CalculateMinimizedHeight());
			if (getForm())
				return ntl::Max<float>(0, (float)getForm()->getClientRect().Bottom - CalculateMinimizedHeight());
			return 0;
		}

		float CDialogBoxEx::CalculateMinimizedHeight()
		{
			RectF rim{ CalculateRimWidth() };
			float caption_height{ CalculateCaptionHeight() };
			return rim.Top + rim.Bottom + caption_height;
		}

		float CDialogBoxEx::CalculateCaptionHeight()
		{
			if (m_bIsPopup || !m_bHasCaption)
				return 0;
			return m_fCaptionHeight;
		}

		RectF CDialogBoxEx::CalculateResizeBorderWidth()
		{
			if (m_bIsPopup || !m_bHasSizeBox || m_eState != WindowState::Normal)
				return RectF{ 0, 0, 0, 0 };
			return m_sResizeBorderWidth;
		}

		RectF CDialogBoxEx::CalculateMargin()
		{
			if (m_bIsPopup || !m_bHasSizeBox || !m_bHasBorder || m_eState != WindowState::Normal)
				return RectF{ 0, 0, 0, 0 };
			return m_sMargin;
		}

		RectF CDialogBoxEx::CalculateRimWidth()
		{
			if (m_bIsPopup || !m_bHasBorder)
				return RectF{ 0, 0, 0, 0 };
			return m_aRimWidth[(int)m_eState];
		}

		void CDialogBoxEx::HandleAttach()
		{
			switch (m_eState)
			{
			case WindowState::Maximized:
				setVisible(true);
				FitInParent();
				break;
			case WindowState::Minimized:
				setVisible(true);
				setSize(PointF{ m_fMinimizedWidth, CalculateMinimizedHeight() });
				getTransform()->Translate(CalculateMinimizedXPosition(), CalculateMinimizedYPosition(), 0);
				break;
			case WindowState::Hidden:
				setVisible(false);
				break;
			default:
				setVisible(true);
				setSize(m_sNormalSize);
				getTransform()->setTransform(m_sNormalTransform);
			}
		}

		void CDialogBoxEx::UpdateTransformControls()
		{
			RectF client{ getClientRect() };
			getTransformControls()->Translate(client.Left, client.Top, 0);
		}

		void CDialogBoxEx::CalculateBound(IControl *parent, RectF &bound, const Mat4f &m)
		{
			RectF r;
			IControl *control;
			Mat4f t;
			for (int i = 0; i < parent->getControlCount(); i++)
				if ((control = parent->getControl(i)) && control->isVisible(false))
				{
					t = m * control->getTransform()->getMatrix();
					r = TransformRect(control->getRenderRect(), t);
					bound.Left = ntl::Min<float>(bound.Left, r.Left);
					bound.Top = ntl::Min<float>(bound.Top, r.Top);
					bound.Right = ntl::Max<float>(bound.Right, r.Right);
					bound.Bottom = ntl::Max<float>(bound.Bottom, r.Bottom);
					CalculateBound(control, bound, t * control->getTransformControls()->getMatrix());
				}
		}

		void CDialogBoxEx::FitInParent()
		{
			if (getParent())
			{
				RectF client{ getParent()->getClientRect() };
				getTransform()->Translate(client.Left, client.Top, 0);
				setSize(PointF{ client.width(), client.height() });
			}
			else if (getForm())
			{
				RectF client{ (RectF)getForm()->getClientRect() };
				getTransform()->Translate(client.Left, client.Top, 0);
				setSize(PointF{ client.width(), client.height() });
			}
		}
	#pragma endregion

	#pragma region Paint
		void CDialogBoxEx::Render(IRenderer *renderer, const Mat4f &matrix)
		{
			State state{ getControlState() };
			PointF disp{ DispOnCanvas(m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			RectF rect{ getRect() };
			RectF all_rect{ AddShadow(rect, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				if (state == State::Blinking)
					state = (m_iBlinkCounter % 2) ? State::Blinking : State::Normal;
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				rect += disp;
				Block block{ rect, RectF{ 0, 0, 0, 0 }, m_aBorderRadius[(int)m_eState], PointLocation::Inside };
				RectF margin{ CalculateMargin() }, rim{ CalculateRimWidth() };
				float caption_height{ CalculateCaptionHeight() };
				block.Rect.Left += margin.Left;
				block.Rect.Top += margin.Top;
				block.Rect.Right -= margin.Right;
				block.Rect.Bottom -= margin.Bottom;
				block.Border = rim;
				if (block.Rect.is_valid() && !block.Rect.is_zero())
				{
					if (m_eState == WindowState::Minimized)
						block.Radius.Right = block.Radius.Bottom = 0;
					DrawBlockShadow(renderer, block.Rect, block.Radius, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
					DrawSimpleBackground(renderer, block.Rect, block.Border, m_aBorderRadius[(int)m_eState], m_aBorderColor[(int)state], m_sBackgroundColor, m_aBackgroundGradient[(int)state]);
					if (!m_bIsPopup)
					{
						RectF close, maximize, minimize, restore;
						getButtonRects(close, maximize, minimize, restore);
						if (ntl::IsGreater<float>(caption_height, 0))
						{
							Block *b{ (block.Radius.has_positive() || block.Border.has_positive()) ? &block : nullptr };
							RenderCaptionBackground(renderer, block.Rect, rim, state, b);
							if (m_bHasSystemMenu)
								RenderIcon(renderer, state, disp, b);
							if (m_bHasCaption)
								RenderCaption(renderer, state, disp, close, maximize, minimize, restore, b);
						}
						block.Border = RectF{ 0, 0, 0, 0 };
						RenderButtons(renderer, disp, close, maximize, minimize, restore, (block.Radius.has_positive() || block.Border.has_positive()) ? &block : nullptr);
					}
				}
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, matrix, m_pCanvas, disp);
		}

		void CDialogBoxEx::RenderCaptionBackground(IRenderer *renderer, const RectF &rect, const RectF &rim, const State state, Block *block)
		{
			CStoreBlock s_block{ renderer };
			RectF r{ rect.Left, rect.Top, rect.Right, rect.Top + m_fCaptionHeight };
			r.Left += rim.Left;
			r.Top += rim.Top;
			r.Right -= rim.Right;
			r.Bottom += rim.Top;
			renderer->ActivateBlock(block);
			(m_aCaptionGradient[(int)state].getPointCount() < 2) ? renderer->DrawRectangle(r, m_aCaptionColor[(int)state]) : renderer->DrawGradient(r, m_aCaptionGradient[(int)state]);
		}

		void CDialogBoxEx::RenderIcon(IRenderer *renderer, const State state, const PointF &disp, const Block *block)
		{
			RectF icon_rect{ getIconRect() + disp };
			ITexture *icon;
			if (m_pIcons && m_aIconIndex[(int)state] >= 0 && (icon = m_pIcons->getTexture(m_aIconIndex[(int)state])))
			{
				icon_rect.Left += m_sIconPadding.Left;
				icon_rect.Top += m_sIconPadding.Top;
				icon_rect.Right -= m_sIconPadding.Right;
				icon_rect.Bottom -= m_sIconPadding.Bottom;
				if (icon_rect.is_valid() && !icon_rect.is_zero())
				{
					Mat4f t1, s, t2;
					ntl::Translate<float>(t1, -icon->Widthf / 2, -icon->Heightf / 2, 0);
					ntl::Scale<float>(s, icon_rect.width() / icon->Widthf, icon_rect.height() / icon->Heightf, 1);
					ntl::Translate<float>(t2, (icon_rect.Left + icon_rect.Right) / 2, (icon_rect.Top + icon_rect.Bottom) / 2, 0);
					CStoreBlock s_block{ renderer };
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivateBlock(block)
						->ActivatePrimitiveMatrix(t2 * s * t1)
						->DrawImage(icon, 1);
				}
			}
		}

		void CDialogBoxEx::RenderCaption(IRenderer *renderer, const State state, const PointF &disp, const RectF &close, const RectF &maximize, const RectF &minimize, const RectF &restore, Block *block)
		{
			if (!m_sCaption.empty())
			{
				RectF caption_rect{ getCaptionRect(close, maximize, minimize, restore) + disp };
				caption_rect.Left += m_sCaptionPadding.Left;
				caption_rect.Top += m_sCaptionPadding.Top;
				caption_rect.Right -= m_sCaptionPadding.Right;
				caption_rect.Bottom -= m_sCaptionPadding.Bottom;
				if (caption_rect.is_valid() && !caption_rect.is_zero())
				{
					IFont *font{ getFont() };
					Color color{ m_aCaptionTextColor[(int)state] };
					if (color.A == 0)
						color = font->Color;
					if (color.A > 0)
					{
						IPlatformFont *pf{ getFont()->getPlatformFont(renderer) };
						if (pf)
						{
							PointF size{ pf->getStringSize(m_sCaption, font->Distance) }, p;
							switch (m_eCaptionHorizontalAlign)
							{
							case TextAlign::Center:
								p.X = std::round(ntl::Max<float>(caption_rect.Left, (caption_rect.Left + caption_rect.Right - size.X) / 2));
								break;
							case TextAlign::Right:
								p.X = ntl::Max<float>(caption_rect.Left, caption_rect.Right - size.X);
								break;
							default:
								p.X = caption_rect.Left;
							}
							switch (m_eCaptionVerticalAlign)
							{
							case VerticalAlign::Middle:
								p.Y = std::round((caption_rect.Top + caption_rect.Bottom - size.Y) / 2);
								break;
							case VerticalAlign::Bottom:
								p.Y = caption_rect.Bottom - size.Y;
								break;
							default:
								p.Y = caption_rect.Top;
							}
							CStoreBlock s_block{ renderer };
							CStorePrimitiveMatrix s_matrix{ renderer };
							renderer
								->ActivateBlock(block)
								->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(p.X, p.Y, 0))
								->DrawText(m_sCaption, pf, font->Distance, color);
						}
					}
				}
			}
		}

		void CDialogBoxEx::RenderButtons(IRenderer *renderer, const PointF &disp, const RectF &close, const RectF &maximize, const RectF &minimize, const RectF &restore, Block *block)
		{
			ITexture *clip{ nullptr };
			if (m_bHasCloseBox && !close.is_zero())
			{
				ButtonState st{ getButtonState(Element::ButtonClose) };
				RenderButton(renderer, getButtonIcon(renderer, m_bUseDefaultCloseIcon, DefaultCloseButtonIcon, m_pButtonIcons, m_aCloseIconIndex[(int)st]), close + disp,
					m_aButtonBorderColor[(int)st], m_aButtonBackgroundColor[(int)st], m_aButtonBackgroundGradient[(int)st], &clip, block);
			}
			if (m_bHasMaximizeBox && !maximize.is_zero())
			{
				ButtonState st{ getButtonState(Element::ButtonMaximize) };
				RenderButton(renderer, getButtonIcon(renderer, m_bUseDefaultMaximizeIcon, DefaultMaximizeButtonIcon, m_pButtonIcons, m_aMaximizeIconIndex[(int)st]), maximize + disp,
					m_aButtonBorderColor[(int)st], m_aButtonBackgroundColor[(int)st], m_aButtonBackgroundGradient[(int)st], &clip, block);
			}
			if (m_bHasMinimizeBox && !minimize.is_zero())
			{
				ButtonState st{ getButtonState(Element::ButtonMinimize) };
				RenderButton(renderer, getButtonIcon(renderer, m_bUseDefaultMinimizeIcon, DefaultMinimizeButtonIcon, m_pButtonIcons, m_aMinimizeIconIndex[(int)st]), minimize + disp,
					m_aButtonBorderColor[(int)st], m_aButtonBackgroundColor[(int)st], m_aButtonBackgroundGradient[(int)st], &clip, block);
			}
			if ((m_bHasMaximizeBox || m_bHasMinimizeBox) && m_eState != WindowState::Normal && !restore.is_zero())
			{
				ButtonState st{ getButtonState(Element::ButtonRestore) };
				RenderButton(renderer, getButtonIcon(renderer, m_bUseDefaultRestoreIcon, DefaultRestoreButtonIcon, m_pButtonIcons, m_aRestoreIconIndex[(int)st]), restore + disp,
					m_aButtonBorderColor[(int)st], m_aButtonBackgroundColor[(int)st], m_aButtonBackgroundGradient[(int)st], &clip, block);
			}
			if (clip)
				clip->Release();
		}

		void CDialogBoxEx::RenderButton(IRenderer *renderer, ITexture *icon, const RectF &rect, const BorderColor &border_color, const Color &background_color, Gradient &background_gradient, ITexture **clip,
			const Block *block)
		{
			if (*clip == nullptr && !(*clip = renderer->CreateTexture(ntl::Round<int>(rect.width()), ntl::Round<int>(rect.height()), 1, TextureFormat::RGBA, true)))
				return;
			renderer
				->ActivateTarget(*clip)
				->Clear(Color{ 0, 0, 0, 0 });
			DrawSimpleBackground(renderer, (*clip)->Rectf, m_sButtonBorderWidth, m_sButtonBorderRadius, border_color, background_color, background_gradient);
			CStorePrimitiveMatrix s_matrix{ renderer };
			if (icon)
			{
				RectF icon_rect{ m_sButtonPadding.Left, m_sButtonPadding.Top, rect.width() - m_sButtonPadding.Right, rect.height() - m_sButtonPadding.Bottom };
				if (icon_rect.is_valid() && !icon_rect.is_zero())
				{
					float scale{ ntl::Min<float>(icon_rect.width(), icon_rect.height()) / ntl::Max<float>(icon->Widthf, icon->Heightf) };
					Mat4f t1, s, t2;
					ntl::Translate<float>(t1, -icon->Widthf / 2, -icon->Heightf / 2, 0);
					ntl::Scale<float>(s, scale, scale, 1);
					ntl::Translate<float>(t2, std::round((icon_rect.Left + icon_rect.Right) / 2), std::round((icon_rect.Top + icon_rect.Bottom) / 2), 0);
					renderer
						->ActivatePrimitiveMatrix(t2 * s * t1)
						->DrawImage(icon, 1);
				}
			}
			CStoreBlock s_block{ renderer };
			renderer
				->ActivateBlock(block)
				->ActivateTarget(m_pCanvas)
				->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(rect.Left, rect.Top, 0))
				->DrawImage(*clip, 1);
		}

		void CDialogBoxEx::RenderMask(IRenderer *renderer)
		{
			if (PrepareCanvas(renderer, &m_pMask, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pMask)
					->Clear(Color{ 0, 0, 0, 0 });
				Block b{ getRect(), RectF{ 0, 0, 0, 0 }, m_aBorderRadius[(int)m_eState], PointLocation::Inside };
				RectF margin{ CalculateMargin() }, rim{ CalculateRimWidth() };
				float caption_height{ CalculateCaptionHeight() };
				b.Rect.Left += margin.Left;
				b.Rect.Top += margin.Top + caption_height;
				b.Rect.Right -= margin.Right;
				b.Rect.Bottom -= margin.Bottom;
				b.Border = rim;
				b.Border.Left += m_sPadding.Left;
				b.Border.Top += m_sPadding.Top;
				b.Border.Right += m_sPadding.Right;
				b.Border.Bottom += m_sPadding.Bottom;
				if (m_eState == WindowState::Minimized)
					b.Radius.Right = b.Radius.Bottom = 0;
				if (ntl::IsLessOrEqual<float>(b.Radius.Left, b.Border.Top) && ntl::IsLessOrEqual<float>(b.Radius.Left, b.Border.Left))
					b.Radius.Left = 0;
				if (ntl::IsLessOrEqual<float>(b.Radius.Top, b.Border.Right) && ntl::IsLessOrEqual<float>(b.Radius.Top, b.Border.Top))
					b.Radius.Top = 0;
				if (b.Radius.has_positive())
				{
					CStoreBlock s_block{ renderer };
					renderer
						->ActivateBlock(&b)
						->DrawRectangle(b.Rect, Color{ 0, 0, 0, 255 });
				}
				else
				{
					b.Rect.Left += b.Border.Left;
					b.Rect.Top += b.Border.Top;
					b.Rect.Right -= b.Border.Right;
					b.Rect.Bottom -= b.Border.Bottom;
					if (b.Rect.is_valid() && !b.Rect.is_zero())
						renderer->DrawRectangle(b.Rect, Color{ 0, 0, 0, 255 });
				}
				m_pMask->setValid(true);
			}
		}
	#pragma endregion
	}
}