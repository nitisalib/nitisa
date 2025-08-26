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
		CFrame::CGradientListener::CGradientListener(CFrame *control) :
			m_pControl{ control }
		{

		}

		void CFrame::CGradientListener::NotifyOnChange()
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
		CFrame::CFrame():
			CControl(L"Frame", true, false, true, true, true, true),
			m_cGradientListener{ this },
			// Shadow
			m_aShadowColor{
				Color{ 0, 0, 0, 150 },
				Color{ 0, 0, 0, 150 },
				Color{ 0, 0, 0, 150 },
				Color{ 0, 0, 0, 150 } },
			m_aShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aShadowRadius{ 6, 6, 6, 6 },
			// Border
			m_sOuterBorderWidth{ 1, 1, 1, 1 },
			m_sBorderRadius{ 6, 6, 6, 6 },
			m_aOuterBorderColor{
				BorderColor{ Color{ 82, 86, 91, 255 }, Color{ 82, 86, 91, 255 }, Color{ 82, 86, 91, 255 }, Color{ 82, 86, 91, 255 } },
				BorderColor{ Color{ 82, 86, 91, 255 }, Color{ 82, 86, 91, 255 }, Color{ 82, 86, 91, 255 }, Color{ 82, 86, 91, 255 } },
				BorderColor{ Color{ 36, 41, 47, 255 }, Color{ 36, 41, 47, 255 }, Color{ 36, 41, 47, 255 }, Color{ 31, 41, 47, 255 } },
				BorderColor{ Color{ 82, 86, 91, 255 }, Color{ 82, 86, 91, 255 }, Color{ 82, 86, 91, 255 }, Color{ 82, 86, 91, 255 } } },
			m_sMiddleBorderWidth{ 6, 28, 6, 6 },
			m_aMiddleBorderColor{
				BorderColor{ Color{ 207, 218, 229, 255 }, Color{ 207, 218, 229, 255 }, Color{ 207, 218, 229, 255 }, Color{ 207, 218, 229, 255 } },
				BorderColor{ Color{ 207, 218, 229, 255 }, Color{ 207, 218, 229, 255 }, Color{ 207, 218, 229, 255 }, Color{ 207, 218, 229, 255 } },
				BorderColor{ Color{ 190, 215, 238, 255 }, Color{ 190, 215, 238, 255 }, Color{ 190, 215, 238, 255 }, Color{ 190, 215, 238, 255 } },
				BorderColor{ Color{ 207, 218, 229, 255 }, Color{ 207, 218, 229, 255 }, Color{ 207, 218, 229, 255 }, Color{ 207, 218, 229, 255 } } },
			m_aMiddleBorderGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_sInnerBorderWidth{ 1, 1, 1, 1 },
			m_aInnerBorderColor{
				BorderColor{ Color{ 102, 106, 111, 255 }, Color{ 102, 106, 111, 255 }, Color{ 102, 106, 111, 255 }, Color{ 102, 106, 111, 255 } },
				BorderColor{ Color{ 102, 106, 111, 255 }, Color{ 102, 106, 111, 255 }, Color{ 102, 106, 111, 255 }, Color{ 102, 106, 111, 255 } },
				BorderColor{ Color{ 90, 102, 114, 255 }, Color{ 90, 102, 114, 255 }, Color{ 90, 102, 114, 255 }, Color{ 90, 102, 114, 255 } },
				BorderColor{ Color{ 102, 106, 111, 255 }, Color{ 102, 106, 111, 255 }, Color{ 102, 106, 111, 255 }, Color{ 102, 106, 111, 255 } } },
			// Background
			m_aBackgroundColor{
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			// Caption
			m_fCaptionPadding{ 6 },
			m_aCaptionColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aCaptionShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aCaptionShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aCaptionShadowRadius{ 1, 1, 1, 1 },
			// Common
			m_bMinimizable{ true },
			m_bMaximizable{ true },
			m_bClosable{ true },
			m_bResizable{ true },
			m_bMovable{ true },
			m_bUseMask{ true },
			m_fMinimizedWidth{ 150 },
			// Buttons
			m_sBtnMinimizeRestore{
				true,
				PointF{ 28, 18 },
				RectF{ 1, 0, 1, 1 },
				RectF{ 0, 0, 0, 4 },
				RectF{ 7, 2, 7, 3 },
				{
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
				},
				{
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 }
				},
				{
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener }
				},
				{
					Color{ 0, 0, 0, 0 },
					Color{ 109, 207, 249, 255 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 109, 207, 249, 255 },
					Color{ 0, 0, 0, 0 },
					Color{ 106, 207, 250, 255 },
					Color{ 0, 0, 0, 0 }
				},
				{
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 }
				},
				{ 6, 6, 6, 6, 6, 6, 6, 6 },
				ButtonState::Normal
			},
			m_sBtnMaximizeRestore{
				true,
				PointF{ 26, 18 },
				RectF{ 0, 0, 0, 1 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 7, 2, 7, 3 },
				{
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
				},
				{
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 }
				},
				{
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener }
				},
				{
					Color{ 0, 0, 0, 0 },
					Color{ 109, 207, 249, 255 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 109, 207, 249, 255 },
					Color{ 0, 0, 0, 0 },
					Color{ 106, 207, 250, 255 },
					Color{ 0, 0, 0, 0 }
				},
				{
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 }
				},
				{ 6, 6, 6, 6, 6, 6, 6, 6 },
				ButtonState::Normal
			},
			m_sBtnClose{
				true,
				PointF{ 47, 18 },
				RectF{ 1, 0, 1, 1 },
				RectF{ 0, 0, 4, 0 },
				RectF{ 17, 2, 17, 3 },
				{
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
					BorderColor{ Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 }, Color{ 80, 88, 96, 255 } },
				},
				{
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 }
				},
				{
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener },
					Gradient{ &m_cGradientListener }
				},
				{
					Color{ 0, 0, 0, 0 },
					Color{ 237, 159, 146, 255 },
					Color{ 0, 0, 0, 0 },
					Color{ 0, 0, 0, 0 },
					Color{ 237, 159, 146, 255 },
					Color{ 0, 0, 0, 0 },
					Color{ 248, 158, 136, 255 },
					Color{ 0, 0, 0, 0 }
				},
				{
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 },
					PointF{ 0, 0 }
				},
				{ 6, 6, 6, 6, 6, 6, 6, 6 },
				ButtonState::Normal
			},
			m_bIgnoreGradient{ true },
			m_bModal{ false },
			m_eFrameState{ FrameState::Normal },
			m_pCanvas{ nullptr },
			m_pMask{ nullptr },
			m_eLastRenderState{ State::Normal },
			m_bCaptionChanged{ false },
			OnMinimize{ nullptr },
			OnMaximize{ nullptr },
			OnRestore{ nullptr },
			OnClose{ nullptr }
		{
			setService(new CFrameService(this), true);
			m_sBtnMinimizeRestore.BackgroundGradient[(int)ButtonState::InactiveHovered].setPointCount(4);
			m_sBtnMinimizeRestore.BackgroundGradient[(int)ButtonState::InactiveHovered].setPoint(0, Color1D{ 0.000f, Color{ 183, 219, 243, 255 } });
			m_sBtnMinimizeRestore.BackgroundGradient[(int)ButtonState::InactiveHovered].setPoint(1, Color1D{ 0.500f, Color{ 134, 184, 219, 255 } });
			m_sBtnMinimizeRestore.BackgroundGradient[(int)ButtonState::InactiveHovered].setPoint(2, Color1D{ 0.501f, Color{ 43, 127, 181, 255 } });
			m_sBtnMinimizeRestore.BackgroundGradient[(int)ButtonState::InactiveHovered].setPoint(3, Color1D{ 1.000f, Color{ 64, 160, 208, 255 } });
			m_sBtnMinimizeRestore.BackgroundGradient[(int)ButtonState::Hovered].setPointCount(4);
			m_sBtnMinimizeRestore.BackgroundGradient[(int)ButtonState::Hovered].setPoint(0, Color1D{ 0.000f, Color{ 183, 219, 243, 255 } });
			m_sBtnMinimizeRestore.BackgroundGradient[(int)ButtonState::Hovered].setPoint(1, Color1D{ 0.500f, Color{ 134, 184, 219, 255 } });
			m_sBtnMinimizeRestore.BackgroundGradient[(int)ButtonState::Hovered].setPoint(2, Color1D{ 0.501f, Color{ 43, 127, 181, 255 } });
			m_sBtnMinimizeRestore.BackgroundGradient[(int)ButtonState::Hovered].setPoint(3, Color1D{ 1.000f, Color{ 64, 160, 208, 255 } });
			m_sBtnMinimizeRestore.BackgroundGradient[(int)ButtonState::ActiveHovered].setPointCount(4);
			m_sBtnMinimizeRestore.BackgroundGradient[(int)ButtonState::ActiveHovered].setPoint(0, Color1D{ 0.000f, Color{ 156, 184, 201, 255 } });
			m_sBtnMinimizeRestore.BackgroundGradient[(int)ButtonState::ActiveHovered].setPoint(1, Color1D{ 0.500f, Color{ 88, 137, 164, 255 } });
			m_sBtnMinimizeRestore.BackgroundGradient[(int)ButtonState::ActiveHovered].setPoint(2, Color1D{ 0.501f, Color{ 20, 54, 86, 255 } });
			m_sBtnMinimizeRestore.BackgroundGradient[(int)ButtonState::ActiveHovered].setPoint(3, Color1D{ 1.000f, Color{ 30, 94, 135, 255 } });

			m_sBtnMaximizeRestore.BackgroundGradient[(int)ButtonState::InactiveHovered].setPointCount(4);
			m_sBtnMaximizeRestore.BackgroundGradient[(int)ButtonState::InactiveHovered].setPoint(0, Color1D{ 0.000f, Color{ 183, 219, 243, 255 } });
			m_sBtnMaximizeRestore.BackgroundGradient[(int)ButtonState::InactiveHovered].setPoint(1, Color1D{ 0.500f, Color{ 134, 184, 219, 255 } });
			m_sBtnMaximizeRestore.BackgroundGradient[(int)ButtonState::InactiveHovered].setPoint(2, Color1D{ 0.501f, Color{ 43, 127, 181, 255 } });
			m_sBtnMaximizeRestore.BackgroundGradient[(int)ButtonState::InactiveHovered].setPoint(3, Color1D{ 1.000f, Color{ 64, 160, 208, 255 } });
			m_sBtnMaximizeRestore.BackgroundGradient[(int)ButtonState::Hovered].setPointCount(4);
			m_sBtnMaximizeRestore.BackgroundGradient[(int)ButtonState::Hovered].setPoint(0, Color1D{ 0.000f, Color{ 183, 219, 243, 255 } });
			m_sBtnMaximizeRestore.BackgroundGradient[(int)ButtonState::Hovered].setPoint(1, Color1D{ 0.500f, Color{ 134, 184, 219, 255 } });
			m_sBtnMaximizeRestore.BackgroundGradient[(int)ButtonState::Hovered].setPoint(2, Color1D{ 0.501f, Color{ 43, 127, 181, 255 } });
			m_sBtnMaximizeRestore.BackgroundGradient[(int)ButtonState::Hovered].setPoint(3, Color1D{ 1.000f, Color{ 64, 160, 208, 255 } });
			m_sBtnMaximizeRestore.BackgroundGradient[(int)ButtonState::ActiveHovered].setPointCount(4);
			m_sBtnMaximizeRestore.BackgroundGradient[(int)ButtonState::ActiveHovered].setPoint(0, Color1D{ 0.000f, Color{ 156, 184, 201, 255 } });
			m_sBtnMaximizeRestore.BackgroundGradient[(int)ButtonState::ActiveHovered].setPoint(1, Color1D{ 0.500f, Color{ 88, 137, 164, 255 } });
			m_sBtnMaximizeRestore.BackgroundGradient[(int)ButtonState::ActiveHovered].setPoint(2, Color1D{ 0.501f, Color{ 20, 54, 86, 255 } });
			m_sBtnMaximizeRestore.BackgroundGradient[(int)ButtonState::ActiveHovered].setPoint(3, Color1D{ 1.000f, Color{ 30, 94, 135, 255 } });

			m_sBtnClose.BackgroundGradient[(int)ButtonState::InactiveHovered].setPointCount(4);
			m_sBtnClose.BackgroundGradient[(int)ButtonState::InactiveHovered].setPoint(0, Color1D{ 0.000f, Color{ 244, 155, 139, 255 } });
			m_sBtnClose.BackgroundGradient[(int)ButtonState::InactiveHovered].setPoint(1, Color1D{ 0.500f, Color{ 228, 108, 86, 255 } });
			m_sBtnClose.BackgroundGradient[(int)ButtonState::InactiveHovered].setPoint(2, Color1D{ 0.501f, Color{ 197, 38, 10, 255 } });
			m_sBtnClose.BackgroundGradient[(int)ButtonState::InactiveHovered].setPoint(3, Color1D{ 1.000f, Color{ 222, 132, 46, 255 } });
			m_sBtnClose.BackgroundGradient[(int)ButtonState::Hovered].setPointCount(4);
			m_sBtnClose.BackgroundGradient[(int)ButtonState::Hovered].setPoint(0, Color1D{ 0.000f, Color{ 244, 155, 139, 255 } });
			m_sBtnClose.BackgroundGradient[(int)ButtonState::Hovered].setPoint(1, Color1D{ 0.500f, Color{ 228, 108, 86, 255 } });
			m_sBtnClose.BackgroundGradient[(int)ButtonState::Hovered].setPoint(2, Color1D{ 0.501f, Color{ 197, 38, 10, 255 } });
			m_sBtnClose.BackgroundGradient[(int)ButtonState::Hovered].setPoint(3, Color1D{ 1.000f, Color{ 222, 132, 46, 255 } });
			m_sBtnClose.BackgroundGradient[(int)ButtonState::ActiveHovered].setPointCount(4);
			m_sBtnClose.BackgroundGradient[(int)ButtonState::ActiveHovered].setPoint(0, Color1D{ 0.000f, Color{ 196, 158, 136, 255 } });
			m_sBtnClose.BackgroundGradient[(int)ButtonState::ActiveHovered].setPoint(1, Color1D{ 0.500f, Color{ 173, 108, 84, 255 } });
			m_sBtnClose.BackgroundGradient[(int)ButtonState::ActiveHovered].setPoint(2, Color1D{ 0.501f, Color{ 123, 22, 8, 255 } });
			m_sBtnClose.BackgroundGradient[(int)ButtonState::ActiveHovered].setPoint(3, Color1D{ 1.000f, Color{ 129, 94, 21, 255 } });

			setSize(PointF{ 200, 200 });
			AdjustConstraints();

			float top{ m_sOuterBorderWidth.Top + m_sMiddleBorderWidth.Top + m_sInnerBorderWidth.Top };
			m_aMiddleBorderGradient[(int)State::Active].setPointCount(5);
			m_aMiddleBorderGradient[(int)State::Active].setPoint(0, Color1D{ 0.0f, Color{ 204, 223, 242, 255 } });
			float y1{ top / getHeight() }, y2{ (y1 + getHeight() - top) * 0.25f / (getHeight() - top) };
			m_aMiddleBorderGradient[(int)State::Active].setPoint(1, Color1D{ y1, Color{ 204, 223, 242, 255 } });
			m_aMiddleBorderGradient[(int)State::Active].setPoint(2, Color1D{ y2, Color{ 228, 238, 247, 255 } });
			m_aMiddleBorderGradient[(int)State::Active].setPoint(3, Color1D{ y2 + 0.001f, Color{ 178, 207, 235, 255 } });
			m_aMiddleBorderGradient[(int)State::Active].setPoint(4, Color1D{ 1.0f, Color{ 178, 207, 235, 255 } });
			
			m_bIgnoreGradient = false;
		}

		CFrame::CFrame(IForm *parent) :CFrame()
		{
			setForm(parent);
		}

		CFrame::CFrame(IControl *parent) : CFrame()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		IControl *CFrame::getControl(const int index)
		{
			return CControl::getControl(index);
		}

		IControl *CFrame::getControl(const String &name)
		{
			return CControl::getControl(name);
		}

		IControl *CFrame::getControl(const PointF &position)
		{
			IControl *result{ CControl::getControl(position) };
			if (m_bUseMask && result && result != this)
			{
				Vec4f v{ ntl::Inversed<float>(getTransformMatrix()) * Vec4f{ position.X, position.Y, 0, 1 } };
				RectF client{ getClientRect() };
				if (v.X < 0 || v.X >= getWidth() || v.Y < 0 || v.Y >= getHeight())
					result = nullptr;
				else if (v.X < client.Left || v.X >= client.Right || v.Y < client.Top || v.Y >= client.Bottom)
					result = this;
			}
			return result;
		}

		RectF CFrame::getClientRect()
		{
			RectF result{
				m_sOuterBorderWidth.Left + m_sMiddleBorderWidth.Left + m_sInnerBorderWidth.Left,
				m_sOuterBorderWidth.Top + m_sMiddleBorderWidth.Top + m_sInnerBorderWidth.Top,
				getWidth() - m_sOuterBorderWidth.Right - m_sMiddleBorderWidth.Right - m_sInnerBorderWidth.Right,
				getHeight() - m_sOuterBorderWidth.Bottom - m_sMiddleBorderWidth.Bottom - m_sInnerBorderWidth.Bottom
			};
			result.validate();
			return result;
		}

		RectF CFrame::getRenderRect()
		{
			RectF result{ 0, 0, getWidth(), getHeight() };
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				result += AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[i], m_aShadowShift[i], m_aShadowRadius[i]);
				result += getMinimizeRestoreButtonRenderRect();
				result += getMaximizeRestoreButtonRenderRect();
				result += getCloseButtonRenderRect();
			}
			return result;
		}

		CursorType CFrame::getCursor()
		{
			if (getForm())
				switch (getPart(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition()))))
				{
				case CFrameService::DownPart::Caption:
					return CursorType::Arrow;
				case CFrameService::DownPart::LeftBorder:
					if (m_bResizable && m_eFrameState == FrameState::Normal)
						return CursorType::SizeWestEast;
					return CursorType::Arrow;
				case CFrameService::DownPart::TopBorder:
					if (m_bResizable && m_eFrameState == FrameState::Normal)
						return CursorType::SizeNorthSouth;
					return CursorType::Arrow;
				case CFrameService::DownPart::RightBorder:
					if (m_bResizable && m_eFrameState == FrameState::Normal)
						return CursorType::SizeWestEast;
					return CursorType::Arrow;
				case CFrameService::DownPart::BottomBorder:
					if (m_bResizable && m_eFrameState == FrameState::Normal)
						return CursorType::SizeNorthSouth;
					return CursorType::Arrow;
				case CFrameService::DownPart::LeftTopCorner:
					if (m_bResizable && m_eFrameState == FrameState::Normal)
						return CursorType::SizeNorthwestSoutheast;
					return CursorType::Arrow;
				case CFrameService::DownPart::RightTopCorner:
					if (m_bResizable && m_eFrameState == FrameState::Normal)
						return CursorType::SizeNortheastSouthwest;
					return CursorType::Arrow;
				case CFrameService::DownPart::RightBottomCorner:
					if (m_bResizable && m_eFrameState == FrameState::Normal)
						return CursorType::SizeNorthwestSoutheast;
					return CursorType::Arrow;
				case CFrameService::DownPart::LeftBottomCorner:
					if (m_bResizable && m_eFrameState == FrameState::Normal)
						return CursorType::SizeNortheastSouthwest;
					return CursorType::Arrow;
				case CFrameService::DownPart::MinimizeRestoreButton:
					return CursorType::Arrow;
				case CFrameService::DownPart::MaximizeRestoreButton:
					return CursorType::Arrow;
				case CFrameService::DownPart::CloseButton:
					return CursorType::Arrow;
				default:
					break;
				}
			return CControl::getCursor();
		}

		String CFrame::getCaption()
		{
			return m_sCaption;
		}

		bool CFrame::isMinimizable()
		{
			return m_bMinimizable;
		}

		bool CFrame::isMaximizable()
		{
			return m_bMaximizable;
		}

		bool CFrame::isClosable()
		{
			return m_bClosable;
		}

		bool CFrame::isResizable()
		{
			return m_bResizable;
		}

		bool CFrame::isMovable()
		{
			return m_bMovable;
		}

		bool CFrame::isMinimized()
		{
			return m_eFrameState == FrameState::Minimized;
		}

		bool CFrame::isMaximized()
		{
			return m_eFrameState == FrameState::Maximized;
		}
	#pragma endregion

	#pragma region Getters
		CFrame::State CFrame::getState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (isModal() || isFocused() || (getForm() && getForm()->getFocusedControl() && hasChild(getForm()->getFocusedControl())))
				return State::Active;
			if (isHovered())
				return State::Hovered;
			return State::Normal;
		}

		CFrame::FrameState CFrame::getFrameState() const
		{
			return m_eFrameState;
		}

		Color CFrame::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		PointF CFrame::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		int CFrame::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		RectF CFrame::getOuterBorderWidth() const
		{
			return m_sOuterBorderWidth;
		}

		RectF CFrame::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		BorderColor CFrame::getOuterBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state];
		}

		Color CFrame::getOuterLeftBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state].Left;
		}

		Color CFrame::getOuterTopBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state].Top;
		}

		Color CFrame::getOuterRightBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state].Right;
		}

		Color CFrame::getOuterBottomBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state].Bottom;
		}

		RectF CFrame::getMiddleBorderWidth() const
		{
			return m_sMiddleBorderWidth;
		}

		BorderColor CFrame::getMiddleBorderColor(const State state) const
		{
			return m_aMiddleBorderColor[(int)state];
		}

		Color CFrame::getMiddleLeftBorderColor(const State state) const
		{
			return m_aMiddleBorderColor[(int)state].Left;
		}

		Color CFrame::getMiddleTopBorderColor(const State state) const
		{
			return m_aMiddleBorderColor[(int)state].Top;
		}

		Color CFrame::getMiddleRightBorderColor(const State state) const
		{
			return m_aMiddleBorderColor[(int)state].Right;
		}

		Color CFrame::getMiddleBottomBorderColor(const State state) const
		{
			return m_aMiddleBorderColor[(int)state].Bottom;
		}

		Gradient *CFrame::getMiddleBorderGradient(const State state)
		{
			return &m_aMiddleBorderGradient[(int)state];
		}

		RectF CFrame::getInnerBorderWidth() const
		{
			return m_sInnerBorderWidth;
		}

		BorderColor CFrame::getInnerBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state];
		}

		Color CFrame::getInnerLeftBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state].Left;
		}

		Color CFrame::getInnerTopBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state].Top;
		}

		Color CFrame::getInnerRightBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state].Right;
		}

		Color CFrame::getInnerBottomBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state].Bottom;
		}

		Color CFrame::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CFrame::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		float CFrame::getCaptionPadding() const
		{
			return m_fCaptionPadding;
		}

		Color CFrame::getCaptionColor(const State state) const
		{
			return m_aCaptionColor[(int)state];
		}

		Color CFrame::getCaptionShadowColor(const State state) const
		{
			return m_aCaptionShadowColor[(int)state];
		}

		PointF CFrame::getCaptionShadowShift(const State state) const
		{
			return m_aCaptionShadowShift[(int)state];
		}

		int CFrame::getCaptionShadowRadius(const State state) const
		{
			return m_aCaptionShadowRadius[(int)state];
		}

		bool CFrame::isUseMask() const
		{
			return m_bUseMask;
		}

		float CFrame::getMinimizedWidth() const
		{
			return m_fMinimizedWidth;
		}

		bool CFrame::isBtnMinimizeRestoreDisplayDisabled() const
		{
			return m_sBtnMinimizeRestore.DisplayDisabled;
		}

		PointF CFrame::getBtnMinimizeRestoreSize() const
		{
			return m_sBtnMinimizeRestore.Size;
		}

		RectF CFrame::getBtnMinimizeRestoreBorderWidth() const
		{
			return m_sBtnMinimizeRestore.BorderWidth;
		}

		RectF CFrame::getBtnMinimizeRestoreBorderRadius() const
		{
			return m_sBtnMinimizeRestore.BorderRadius;
		}

		RectF CFrame::getBtnMinimizeRestoreIconPadding() const
		{
			return m_sBtnMinimizeRestore.IconPadding;
		}

		BorderColor CFrame::getBtnMinimizeRestoreBorderColor(const ButtonState state) const
		{
			return m_sBtnMinimizeRestore.BorderColor[(int)state];
		}

		Color CFrame::getBtnMinimizeRestoreLeftBorderColor(const ButtonState state) const
		{
			return m_sBtnMinimizeRestore.BorderColor[(int)state].Left;
		}

		Color CFrame::getBtnMinimizeRestoreTopBorderColor(const ButtonState state) const
		{
			return m_sBtnMinimizeRestore.BorderColor[(int)state].Top;
		}

		Color CFrame::getBtnMinimizeRestoreRightBorderColor(const ButtonState state) const
		{
			return m_sBtnMinimizeRestore.BorderColor[(int)state].Right;
		}

		Color CFrame::getBtnMinimizeRestoreBottomBorderColor(const ButtonState state) const
		{
			return m_sBtnMinimizeRestore.BorderColor[(int)state].Bottom;
		}

		Color CFrame::getBtnMinimizeRestoreBackgroundColor(const ButtonState state) const
		{
			return m_sBtnMinimizeRestore.BackgroundColor[(int)state];
		}

		Gradient *CFrame::getBtnMinimizeRestoreBackgroundGradient(const ButtonState state)
		{
			return &m_sBtnMinimizeRestore.BackgroundGradient[(int)state];
		}

		Color CFrame::getBtnMinimizeRestoreShadowColor(const ButtonState state) const
		{
			return m_sBtnMinimizeRestore.ShadowColor[(int)state];
		}

		PointF CFrame::getBtnMinimizeRestoreShadowShift(const ButtonState state) const
		{
			return m_sBtnMinimizeRestore.ShadowShift[(int)state];
		}

		int CFrame::getBtnMinimizeRestoreShadowRadius(const ButtonState state) const
		{
			return m_sBtnMinimizeRestore.ShadowRadius[(int)state];
		}

		CFrame::ButtonState CFrame::getBtnMinimizeRestoreState()
		{
			if (getState() != State::Active)
				switch (m_sBtnMinimizeRestore.State)
				{
				case ButtonState::Normal:
					return ButtonState::InactiveNormal;
				case ButtonState::Hovered:
					return ButtonState::InactiveHovered;
				case ButtonState::Disabled:
					return ButtonState::InactiveDisabled;
				default:
					break;
				}
			return m_sBtnMinimizeRestore.State;
		}

		bool CFrame::isBtnMaximizeRestoreDisplayDisabled() const
		{
			return m_sBtnMaximizeRestore.DisplayDisabled;
		}

		PointF CFrame::getBtnMaximizeRestoreSize() const
		{
			return m_sBtnMaximizeRestore.Size;
		}

		RectF CFrame::getBtnMaximizeRestoreBorderWidth() const
		{
			return m_sBtnMaximizeRestore.BorderWidth;
		}

		RectF CFrame::getBtnMaximizeRestoreBorderRadius() const
		{
			return m_sBtnMaximizeRestore.BorderRadius;
		}

		RectF CFrame::getBtnMaximizeRestoreIconPadding() const
		{
			return m_sBtnMaximizeRestore.IconPadding;
		}

		BorderColor CFrame::getBtnMaximizeRestoreBorderColor(const ButtonState state) const
		{
			return m_sBtnMaximizeRestore.BorderColor[(int)state];
		}

		Color CFrame::getBtnMaximizeRestoreLeftBorderColor(const ButtonState state) const
		{
			return m_sBtnMaximizeRestore.BorderColor[(int)state].Left;
		}

		Color CFrame::getBtnMaximizeRestoreTopBorderColor(const ButtonState state) const
		{
			return m_sBtnMaximizeRestore.BorderColor[(int)state].Top;
		}

		Color CFrame::getBtnMaximizeRestoreRightBorderColor(const ButtonState state) const
		{
			return m_sBtnMaximizeRestore.BorderColor[(int)state].Right;
		}

		Color CFrame::getBtnMaximizeRestoreBottomBorderColor(const ButtonState state) const
		{
			return m_sBtnMaximizeRestore.BorderColor[(int)state].Bottom;
		}

		Color CFrame::getBtnMaximizeRestoreBackgroundColor(const ButtonState state) const
		{
			return m_sBtnMaximizeRestore.BackgroundColor[(int)state];
		}

		Gradient *CFrame::getBtnMaximizeRestoreBackgroundGradient(const ButtonState state)
		{
			return &m_sBtnMaximizeRestore.BackgroundGradient[(int)state];
		}

		Color CFrame::getBtnMaximizeRestoreShadowColor(const ButtonState state) const
		{
			return m_sBtnMaximizeRestore.ShadowColor[(int)state];
		}

		PointF CFrame::getBtnMaximizeRestoreShadowShift(const ButtonState state) const
		{
			return m_sBtnMaximizeRestore.ShadowShift[(int)state];
		}

		int CFrame::getBtnMaximizeRestoreShadowRadius(const ButtonState state) const
		{
			return m_sBtnMaximizeRestore.ShadowRadius[(int)state];
		}

		CFrame::ButtonState CFrame::getBtnMaximizeRestoreState()
		{
			if (getState() != State::Active)
				switch (m_sBtnMaximizeRestore.State)
				{
				case ButtonState::Normal:
					return ButtonState::InactiveNormal;
				case ButtonState::Hovered:
					return ButtonState::InactiveHovered;
				case ButtonState::Disabled:
					return ButtonState::InactiveDisabled;
				default:
					break;
				}
			return m_sBtnMaximizeRestore.State;
		}

		bool CFrame::isBtnCloseDisplayDisabled() const
		{
			return m_sBtnClose.DisplayDisabled;
		}

		PointF CFrame::getBtnCloseSize() const
		{
			return m_sBtnClose.Size;
		}

		RectF CFrame::getBtnCloseBorderWidth() const
		{
			return m_sBtnClose.BorderWidth;
		}

		RectF CFrame::getBtnCloseBorderRadius() const
		{
			return m_sBtnClose.BorderRadius;
		}

		RectF CFrame::getBtnCloseIconPadding() const
		{
			return m_sBtnClose.IconPadding;
		}

		BorderColor CFrame::getBtnCloseBorderColor(const ButtonState state) const
		{
			return m_sBtnClose.BorderColor[(int)state];
		}

		Color CFrame::getBtnCloseLeftBorderColor(const ButtonState state) const
		{
			return m_sBtnClose.BorderColor[(int)state].Left;
		}

		Color CFrame::getBtnCloseTopBorderColor(const ButtonState state) const
		{
			return m_sBtnClose.BorderColor[(int)state].Top;
		}

		Color CFrame::getBtnCloseRightBorderColor(const ButtonState state) const
		{
			return m_sBtnClose.BorderColor[(int)state].Right;
		}

		Color CFrame::getBtnCloseBottomBorderColor(const ButtonState state) const
		{
			return m_sBtnClose.BorderColor[(int)state].Bottom;
		}

		Color CFrame::getBtnCloseBackgroundColor(const ButtonState state) const
		{
			return m_sBtnClose.BackgroundColor[(int)state];
		}

		Gradient *CFrame::getBtnCloseBackgroundGradient(const ButtonState state)
		{
			return &m_sBtnClose.BackgroundGradient[(int)state];
		}

		Color CFrame::getBtnCloseShadowColor(const ButtonState state) const
		{
			return m_sBtnClose.ShadowColor[(int)state];
		}

		PointF CFrame::getBtnCloseShadowShift(const ButtonState state) const
		{
			return m_sBtnClose.ShadowShift[(int)state];
		}

		int CFrame::getBtnCloseShadowRadius(const ButtonState state) const
		{
			return m_sBtnClose.ShadowRadius[(int)state];
		}

		CFrame::ButtonState CFrame::getBtnCloseState()
		{
			if (getState() != State::Active)
				switch (m_sBtnClose.State)
				{
				case ButtonState::Normal:
					return ButtonState::InactiveNormal;
				case ButtonState::Hovered:
					return ButtonState::InactiveHovered;
				case ButtonState::Disabled:
					return ButtonState::InactiveDisabled;
				default:
					break;
				}
			return m_sBtnClose.State;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFrame::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aShadowShift[i] *= s;
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
					m_aCaptionShadowShift[i] *= s;
					m_aCaptionShadowRadius[i] = ntl::Round<int>((float)m_aCaptionShadowRadius[i] * avg);
				}
				m_sOuterBorderWidth *= s;
				m_sBorderRadius *= avg;
				m_sMiddleBorderWidth *= s;
				m_sInnerBorderWidth *= s;
				m_fCaptionPadding *= s.X;
				m_fMinimizedWidth *= s.X;

				m_sBtnMinimizeRestore.Size *= s;
				m_sBtnMinimizeRestore.BorderWidth *= s;
				m_sBtnMinimizeRestore.BorderRadius *= avg;
				m_sBtnMinimizeRestore.IconPadding *= s;
				for (int i = 0; i <= (int)ButtonState::Disabled; i++)
				{
					m_sBtnMinimizeRestore.ShadowShift[i] *= s;
					m_sBtnMinimizeRestore.ShadowRadius[i] = ntl::Round<int>((float)m_sBtnMinimizeRestore.ShadowRadius[i] * avg);
				}

				m_sBtnMaximizeRestore.Size *= s;
				m_sBtnMaximizeRestore.BorderWidth *= s;
				m_sBtnMaximizeRestore.BorderRadius *= avg;
				m_sBtnMaximizeRestore.IconPadding *= s;
				for (int i = 0; i <= (int)ButtonState::Disabled; i++)
				{
					m_sBtnMaximizeRestore.ShadowShift[i] *= s;
					m_sBtnMaximizeRestore.ShadowRadius[i] = ntl::Round<int>((float)m_sBtnMaximizeRestore.ShadowRadius[i] * avg);
				}

				m_sBtnClose.Size *= s;
				m_sBtnClose.BorderWidth *= s;
				m_sBtnClose.BorderRadius *= avg;
				m_sBtnClose.IconPadding *= s;
				for (int i = 0; i <= (int)ButtonState::Disabled; i++)
				{
					m_sBtnClose.ShadowShift[i] *= s;
					m_sBtnClose.ShadowRadius[i] = ntl::Round<int>((float)m_sBtnClose.ShadowRadius[i] * avg);
				}

				AdjustConstraints();
				QueryService()->AlignControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFrame::setConstraints(const RectF &value)
		{
			RectF v{ value };
			PointF min_size{ getMinSize() };
			v.Left = ntl::Max<float>(v.Left, min_size.X);
			v.Top = ntl::Max<float>(v.Top, min_size.Y);
			return CControl::setConstraints(v);
		}

		bool CFrame::setCaption(const String &value)
		{
			m_bCaptionChanged = true;
			if (value != m_sCaption)
			{
				m_sCaption = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getCaptionRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setMinimizable(const bool value)
		{
			if (value != m_bMinimizable)
			{
				CLockRepaint lock{ this };
				m_bMinimizable = value;
				m_sBtnMinimizeRestore.State = m_bMinimizable ? ButtonState::Normal : ButtonState::Disabled;
				AdjustConstraints();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getCaptionRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setMaximizable(const bool value)
		{
			if (value != m_bMaximizable)
			{
				CLockRepaint lock{ this };
				m_bMaximizable = value;
				m_sBtnMaximizeRestore.State = m_bMaximizable ? ButtonState::Normal : ButtonState::Disabled;
				AdjustConstraints();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getCaptionRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setClosable(const bool value)
		{
			if (value != m_bClosable)
			{
				CLockRepaint lock{ this };
				m_bClosable = value;
				m_sBtnClose.State = m_bClosable ? ButtonState::Normal : ButtonState::Disabled;
				AdjustConstraints();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getCaptionRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setResizable(const bool value)
		{
			if (value != m_bResizable)
			{
				m_bResizable = value;
				return true;
			}
			return false;
		}

		bool CFrame::setMovable(const bool value)
		{
			if (value != m_bMovable)
			{
				m_bMovable = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CFrame::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
				m_aShadowColor[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				if (m_aShadowColor[(int)state].A > 0 && state == getState())
					Repaint(false);
				m_aShadowShift[(int)state] = value;
				if (m_aShadowColor[(int)state].A > 0 && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				if (m_aShadowColor[(int)state].A > 0 && state == getState())
					Repaint(false);
				m_aShadowRadius[(int)state] = value;
				if (m_aShadowColor[(int)state].A > 0 && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setOuterBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sOuterBorderWidth))
			{
				CLockRepaint lock{ this };
				m_sOuterBorderWidth = value;
				AdjustConstraints();
				QueryService()->AlignControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFrame::setBorderRadius(const RectF &value)
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

		bool CFrame::setOuterBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aOuterBorderColor[(int)state])
			{
				m_aOuterBorderColor[(int)state] = value;
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

		bool CFrame::setOuterLeftBorderColor(const State state, const Color &value)
		{
			return setOuterBorderColor(state, BorderColor{ value, m_aOuterBorderColor[(int)state].Top, m_aOuterBorderColor[(int)state].Right, m_aOuterBorderColor[(int)state].Bottom });
		}

		bool CFrame::setOuterTopBorderColor(const State state, const Color &value)
		{
			return setOuterBorderColor(state, BorderColor{ m_aOuterBorderColor[(int)state].Left, value, m_aOuterBorderColor[(int)state].Right, m_aOuterBorderColor[(int)state].Bottom });
		}

		bool CFrame::setOuterRightBorderColor(const State state, const Color &value)
		{
			return setOuterBorderColor(state, BorderColor{ m_aOuterBorderColor[(int)state].Left, m_aOuterBorderColor[(int)state].Top, value, m_aOuterBorderColor[(int)state].Bottom });
		}

		bool CFrame::setOuterBottomBorderColor(const State state, const Color &value)
		{
			return setOuterBorderColor(state, BorderColor{ m_aOuterBorderColor[(int)state].Left, m_aOuterBorderColor[(int)state].Top, m_aOuterBorderColor[(int)state].Right, value });
		}

		bool CFrame::setMiddleBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sMiddleBorderWidth))
			{
				CLockRepaint lock{ this };
				m_sMiddleBorderWidth = value;
				AdjustConstraints();
				QueryService()->AlignControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFrame::setMiddleBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aMiddleBorderColor[(int)state])
			{
				m_aMiddleBorderColor[(int)state] = value;
				if (m_sMiddleBorderWidth.has_positive())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setMiddleLeftBorderColor(const State state, const Color &value)
		{
			return setMiddleBorderColor(state, BorderColor{ value, m_aMiddleBorderColor[(int)state].Top, m_aMiddleBorderColor[(int)state].Right, m_aMiddleBorderColor[(int)state].Bottom });
		}

		bool CFrame::setMiddleTopBorderColor(const State state, const Color &value)
		{
			return setMiddleBorderColor(state, BorderColor{ m_aMiddleBorderColor[(int)state].Left, value, m_aMiddleBorderColor[(int)state].Right, m_aMiddleBorderColor[(int)state].Bottom });
		}

		bool CFrame::setMiddleRightBorderColor(const State state, const Color &value)
		{
			return setMiddleBorderColor(state, BorderColor{ m_aMiddleBorderColor[(int)state].Left, m_aMiddleBorderColor[(int)state].Top, value, m_aMiddleBorderColor[(int)state].Bottom });
		}

		bool CFrame::setMiddleBottomBorderColor(const State state, const Color &value)
		{
			return setMiddleBorderColor(state, BorderColor{ m_aMiddleBorderColor[(int)state].Left, m_aMiddleBorderColor[(int)state].Top, m_aMiddleBorderColor[(int)state].Right, value });
		}

		bool CFrame::setInnerBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sInnerBorderWidth))
			{
				CLockRepaint lock{ this };
				m_sInnerBorderWidth = value;
				AdjustConstraints();
				QueryService()->AlignControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFrame::setInnerBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aInnerBorderColor[(int)state])
			{
				m_aInnerBorderColor[(int)state] = value;
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

		bool CFrame::setInnerLeftBorderColor(const State state, const Color &value)
		{
			return setInnerBorderColor(state, BorderColor{ value, m_aInnerBorderColor[(int)state].Top, m_aInnerBorderColor[(int)state].Right, m_aInnerBorderColor[(int)state].Bottom });
		}

		bool CFrame::setInnerTopBorderColor(const State state, const Color &value)
		{
			return setInnerBorderColor(state, BorderColor{ m_aInnerBorderColor[(int)state].Left, value, m_aInnerBorderColor[(int)state].Right, m_aInnerBorderColor[(int)state].Bottom });
		}

		bool CFrame::setInnerRightBorderColor(const State state, const Color &value)
		{
			return setInnerBorderColor(state, BorderColor{ m_aInnerBorderColor[(int)state].Left, m_aInnerBorderColor[(int)state].Top, value, m_aInnerBorderColor[(int)state].Bottom });
		}

		bool CFrame::setInnerBottomBorderColor(const State state, const Color &value)
		{
			return setInnerBorderColor(state, BorderColor{ m_aInnerBorderColor[(int)state].Left, m_aInnerBorderColor[(int)state].Top, m_aInnerBorderColor[(int)state].Right, value });
		}

		bool CFrame::setBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setCaptionPadding(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fCaptionPadding))
			{
				m_fCaptionPadding = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getCaptionRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setCaptionColor(const State state, const Color &value)
		{
			if (value != m_aCaptionColor[(int)state])
			{
				m_aCaptionColor[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getCaptionRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setCaptionShadowColor(const State state, const Color &value)
		{
			if (value != m_aCaptionShadowColor[(int)state])
			{
				m_aCaptionShadowColor[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getCaptionRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setCaptionShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aCaptionShadowShift[(int)state]))
			{
				m_aCaptionShadowShift[(int)state] = value;
				if (m_aCaptionShadowColor[(int)state].A > 0 && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getCaptionRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setCaptionShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aCaptionShadowRadius[(int)state])
			{
				m_aCaptionShadowRadius[(int)state] = value;
				if (m_aCaptionShadowColor[(int)state].A > 0 && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getCaptionRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setUseMask(const bool value)
		{
			if (value != m_bUseMask)
			{
				m_bUseMask = value;
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFrame::setMinimizedWidth(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fMinimizedWidth))
			{
				m_fMinimizedWidth = value;
				if (m_eFrameState == FrameState::Minimized)
					setWidth(m_fMinimizedWidth);
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMinimizeRestoreDisplayDisabled(const bool value)
		{
			if (value != m_sBtnMinimizeRestore.DisplayDisabled)
			{
				CLockRepaint lock{ this };
				m_sBtnMinimizeRestore.DisplayDisabled = value;
				AdjustConstraints();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getCaptionRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMinimizeRestoreSize(const PointF &value)
		{
			if (ntl::IsGreater<float>(value.X, 0) && ntl::IsGreater<float>(value.Y, 0) && IsNotEqual(value, m_sBtnMinimizeRestore.Size))
			{
				CLockRepaint lock{ this };
				m_sBtnMinimizeRestore.Size = value;
				AdjustConstraints();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getCaptionRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMinimizeRestoreBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBtnMinimizeRestore.BorderWidth))
			{
				m_sBtnMinimizeRestore.BorderWidth = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getMinimizeRestoreButtonRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMinimizeRestoreBorderRadius(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBtnMinimizeRestore.BorderRadius))
			{
				m_sBtnMinimizeRestore.BorderRadius = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getMinimizeRestoreButtonRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMinimizeRestoreIconPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBtnMinimizeRestore.IconPadding))
			{
				m_sBtnMinimizeRestore.IconPadding = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getMinimizeRestoreButtonRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMinimizeRestoreBorderColor(const ButtonState state, const BorderColor &value)
		{
			if (value != m_sBtnMinimizeRestore.BorderColor[(int)state])
			{
				m_sBtnMinimizeRestore.BorderColor[(int)state] = value;
				if (state == m_sBtnMinimizeRestore.State)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getMinimizeRestoreButtonRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMinimizeRestoreLeftBorderColor(const ButtonState state, const Color &value)
		{
			return setBtnMinimizeRestoreBorderColor(state,
				BorderColor{ value, m_sBtnMinimizeRestore.BorderColor[(int)state].Top, m_sBtnMinimizeRestore.BorderColor[(int)state].Right, m_sBtnMinimizeRestore.BorderColor[(int)state].Bottom });
		}

		bool CFrame::setBtnMinimizeRestoreTopBorderColor(const ButtonState state, const Color &value)
		{
			return setBtnMinimizeRestoreBorderColor(state,
				BorderColor{ m_sBtnMinimizeRestore.BorderColor[(int)state].Left, value, m_sBtnMinimizeRestore.BorderColor[(int)state].Right, m_sBtnMinimizeRestore.BorderColor[(int)state].Bottom });
		}

		bool CFrame::setBtnMinimizeRestoreRightBorderColor(const ButtonState state, const Color &value)
		{
			return setBtnMinimizeRestoreBorderColor(state,
				BorderColor{ m_sBtnMinimizeRestore.BorderColor[(int)state].Left, m_sBtnMinimizeRestore.BorderColor[(int)state].Top, value, m_sBtnMinimizeRestore.BorderColor[(int)state].Bottom });
		}

		bool CFrame::setBtnMinimizeRestoreBottomBorderColor(const ButtonState state, const Color &value)
		{
			return setBtnMinimizeRestoreBorderColor(state,
				BorderColor{ m_sBtnMinimizeRestore.BorderColor[(int)state].Left, m_sBtnMinimizeRestore.BorderColor[(int)state].Top, m_sBtnMinimizeRestore.BorderColor[(int)state].Right, value });
		}

		bool CFrame::setBtnMinimizeRestoreBackgroundColor(const ButtonState state, const Color &value)
		{
			if (value != m_sBtnMinimizeRestore.BackgroundColor[(int)state])
			{
				m_sBtnMinimizeRestore.BackgroundColor[(int)state] = value;
				if (state == m_sBtnMinimizeRestore.State)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getMinimizeRestoreButtonRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMinimizeRestoreShadowColor(const ButtonState state, const Color &value)
		{
			if (value != m_sBtnMinimizeRestore.ShadowColor[(int)state])
			{
				m_sBtnMinimizeRestore.ShadowColor[(int)state] = value;
				if (state == m_sBtnMinimizeRestore.State)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getMinimizeRestoreButtonRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMinimizeRestoreShadowShift(const ButtonState state, const PointF &value)
		{
			if (IsNotEqual(value, m_sBtnMinimizeRestore.ShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				if (state == m_sBtnMinimizeRestore.State && m_sBtnMinimizeRestore.ShadowColor[(int)state].A > 0)
					Repaint(getMinimizeRestoreButtonRenderRect(), true);
				m_sBtnMinimizeRestore.ShadowShift[(int)state] = value;
				if (state == m_sBtnMinimizeRestore.State && m_sBtnMinimizeRestore.ShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getMinimizeRestoreButtonRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMinimizeRestoreShadowRadius(const ButtonState state, const int value)
		{
			if (value >= 1 && value != m_sBtnMinimizeRestore.ShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				if (state == m_sBtnMinimizeRestore.State && m_sBtnMinimizeRestore.ShadowColor[(int)state].A > 0)
					Repaint(getMinimizeRestoreButtonRenderRect(), true);
				m_sBtnMinimizeRestore.ShadowRadius[(int)state] = value;
				if (state == m_sBtnMinimizeRestore.State && m_sBtnMinimizeRestore.ShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getMinimizeRestoreButtonRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMaximizeRestoreDisplayDisabled(const bool value)
		{
			if (value != m_sBtnMaximizeRestore.DisplayDisabled)
			{
				CLockRepaint lock{ this };
				m_sBtnMaximizeRestore.DisplayDisabled = value;
				AdjustConstraints();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getCaptionRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMaximizeRestoreSize(const PointF &value)
		{
			if (ntl::IsGreater<float>(value.X, 0) && ntl::IsGreater<float>(value.Y, 0) && IsNotEqual(value, m_sBtnMaximizeRestore.Size))
			{
				CLockRepaint lock{ this };
				m_sBtnMaximizeRestore.Size = value;
				AdjustConstraints();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getCaptionRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMaximizeRestoreBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBtnMaximizeRestore.BorderWidth))
			{
				m_sBtnMaximizeRestore.BorderWidth = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getMaximizeRestoreButtonRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMaximizeRestoreBorderRadius(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBtnMaximizeRestore.BorderRadius))
			{
				m_sBtnMaximizeRestore.BorderRadius = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getMaximizeRestoreButtonRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMaximizeRestoreIconPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBtnMaximizeRestore.IconPadding))
			{
				m_sBtnMaximizeRestore.IconPadding = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getMaximizeRestoreButtonRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMaximizeRestoreBorderColor(const ButtonState state, const BorderColor &value)
		{
			if (value != m_sBtnMaximizeRestore.BorderColor[(int)state])
			{
				m_sBtnMaximizeRestore.BorderColor[(int)state] = value;
				if (state == m_sBtnMaximizeRestore.State)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getMaximizeRestoreButtonRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMaximizeRestoreLeftBorderColor(const ButtonState state, const Color &value)
		{
			return setBtnMaximizeRestoreBorderColor(state,
				BorderColor{ value, m_sBtnMaximizeRestore.BorderColor[(int)state].Top, m_sBtnMaximizeRestore.BorderColor[(int)state].Right, m_sBtnMaximizeRestore.BorderColor[(int)state].Bottom });
		}

		bool CFrame::setBtnMaximizeRestoreTopBorderColor(const ButtonState state, const Color &value)
		{
			return setBtnMaximizeRestoreBorderColor(state,
				BorderColor{ m_sBtnMaximizeRestore.BorderColor[(int)state].Left, value, m_sBtnMaximizeRestore.BorderColor[(int)state].Right, m_sBtnMaximizeRestore.BorderColor[(int)state].Bottom });
		}

		bool CFrame::setBtnMaximizeRestoreRightBorderColor(const ButtonState state, const Color &value)
		{
			return setBtnMaximizeRestoreBorderColor(state,
				BorderColor{ m_sBtnMaximizeRestore.BorderColor[(int)state].Left, m_sBtnMaximizeRestore.BorderColor[(int)state].Top, value, m_sBtnMaximizeRestore.BorderColor[(int)state].Bottom });
		}

		bool CFrame::setBtnMaximizeRestoreBottomBorderColor(const ButtonState state, const Color &value)
		{
			return setBtnMaximizeRestoreBorderColor(state,
				BorderColor{ m_sBtnMaximizeRestore.BorderColor[(int)state].Left, m_sBtnMaximizeRestore.BorderColor[(int)state].Top, m_sBtnMaximizeRestore.BorderColor[(int)state].Right, value });
		}

		bool CFrame::setBtnMaximizeRestoreBackgroundColor(const ButtonState state, const Color &value)
		{
			if (value != m_sBtnMaximizeRestore.BackgroundColor[(int)state])
			{
				m_sBtnMaximizeRestore.BackgroundColor[(int)state] = value;
				if (state == m_sBtnMaximizeRestore.State)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getMaximizeRestoreButtonRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMaximizeRestoreShadowColor(const ButtonState state, const Color &value)
		{
			if (value != m_sBtnMaximizeRestore.ShadowColor[(int)state])
			{
				m_sBtnMaximizeRestore.ShadowColor[(int)state] = value;
				if (state == m_sBtnMaximizeRestore.State)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getMaximizeRestoreButtonRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMaximizeRestoreShadowShift(const ButtonState state, const PointF &value)
		{
			if (IsNotEqual(value, m_sBtnMaximizeRestore.ShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				if (state == m_sBtnMaximizeRestore.State && m_sBtnMaximizeRestore.ShadowColor[(int)state].A > 0)
					Repaint(getMaximizeRestoreButtonRenderRect(), true);
				m_sBtnMaximizeRestore.ShadowShift[(int)state] = value;
				if (state == m_sBtnMaximizeRestore.State && m_sBtnMaximizeRestore.ShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getMaximizeRestoreButtonRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setBtnMaximizeRestoreShadowRadius(const ButtonState state, const int value)
		{
			if (value >= 1 && value != m_sBtnMaximizeRestore.ShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				if (state == m_sBtnMaximizeRestore.State && m_sBtnMaximizeRestore.ShadowColor[(int)state].A > 0)
					Repaint(getMaximizeRestoreButtonRenderRect(), true);
				m_sBtnMaximizeRestore.ShadowRadius[(int)state] = value;
				if (state == m_sBtnMaximizeRestore.State && m_sBtnMaximizeRestore.ShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getMaximizeRestoreButtonRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setBtnCloseDisplayDisabled(const bool value)
		{
			if (value != m_sBtnClose.DisplayDisabled)
			{
				CLockRepaint lock{ this };
				m_sBtnClose.DisplayDisabled = value;
				AdjustConstraints();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getCaptionRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setBtnCloseSize(const PointF &value)
		{
			if (ntl::IsGreater<float>(value.X, 0) && ntl::IsGreater<float>(value.Y, 0) && IsNotEqual(value, m_sBtnClose.Size))
			{
				CLockRepaint lock{ this };
				m_sBtnClose.Size = value;
				AdjustConstraints();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getCaptionRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setBtnCloseBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBtnClose.BorderWidth))
			{
				m_sBtnClose.BorderWidth = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getCloseButtonRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setBtnCloseBorderRadius(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBtnClose.BorderRadius))
			{
				m_sBtnClose.BorderRadius = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getCloseButtonRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setBtnCloseIconPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBtnClose.IconPadding))
			{
				m_sBtnClose.IconPadding = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(getCloseButtonRenderRect(), true);
				return true;
			}
			return false;
		}

		bool CFrame::setBtnCloseBorderColor(const ButtonState state, const BorderColor &value)
		{
			if (value != m_sBtnClose.BorderColor[(int)state])
			{
				m_sBtnClose.BorderColor[(int)state] = value;
				if (state == m_sBtnClose.State)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getCloseButtonRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setBtnCloseLeftBorderColor(const ButtonState state, const Color &value)
		{
			return setBtnCloseBorderColor(state, BorderColor{ value, m_sBtnClose.BorderColor[(int)state].Top, m_sBtnClose.BorderColor[(int)state].Right, m_sBtnClose.BorderColor[(int)state].Bottom });
		}

		bool CFrame::setBtnCloseTopBorderColor(const ButtonState state, const Color &value)
		{
			return setBtnCloseBorderColor(state, BorderColor{ m_sBtnClose.BorderColor[(int)state].Left, value, m_sBtnClose.BorderColor[(int)state].Right, m_sBtnClose.BorderColor[(int)state].Bottom });
		}

		bool CFrame::setBtnCloseRightBorderColor(const ButtonState state, const Color &value)
		{
			return setBtnCloseBorderColor(state, BorderColor{ m_sBtnClose.BorderColor[(int)state].Left, m_sBtnClose.BorderColor[(int)state].Top, value, m_sBtnClose.BorderColor[(int)state].Bottom });
		}

		bool CFrame::setBtnCloseBottomBorderColor(const ButtonState state, const Color &value)
		{
			return setBtnCloseBorderColor(state, BorderColor{ m_sBtnClose.BorderColor[(int)state].Left, m_sBtnClose.BorderColor[(int)state].Top, m_sBtnClose.BorderColor[(int)state].Right, value });
		}

		bool CFrame::setBtnCloseBackgroundColor(const ButtonState state, const Color &value)
		{
			if (value != m_sBtnClose.BackgroundColor[(int)state])
			{
				m_sBtnClose.BackgroundColor[(int)state] = value;
				if (state == m_sBtnClose.State)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getCloseButtonRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setBtnCloseShadowColor(const ButtonState state, const Color &value)
		{
			if (value != m_sBtnClose.ShadowColor[(int)state])
			{
				m_sBtnClose.ShadowColor[(int)state] = value;
				if (state == m_sBtnClose.State)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getCloseButtonRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setBtnCloseShadowShift(const ButtonState state, const PointF &value)
		{
			if (IsNotEqual(value, m_sBtnClose.ShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				if (state == m_sBtnClose.State && m_sBtnClose.ShadowColor[(int)state].A > 0)
					Repaint(getCloseButtonRenderRect(), true);
				m_sBtnClose.ShadowShift[(int)state] = value;
				if (state == m_sBtnClose.State && m_sBtnClose.ShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getCloseButtonRenderRect(), true);
				}
				return true;
			}
			return false;
		}

		bool CFrame::setBtnCloseShadowRadius(const ButtonState state, const int value)
		{
			if (value >= 1 && value != m_sBtnClose.ShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				if (state == m_sBtnClose.State && m_sBtnClose.ShadowColor[(int)state].A > 0)
					Repaint(getCloseButtonRenderRect(), true);
				m_sBtnClose.ShadowRadius[(int)state] = value;
				if (state == m_sBtnClose.State && m_sBtnClose.ShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(getCloseButtonRenderRect(), true);
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CFrame::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			CControl::Refresh(refresh_children);
		}

		void CFrame::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L"OuterBorderWidth", m_sOuterBorderWidth);
			style->getOption(m_sClassName + L"BorderRadius", m_sBorderRadius);
			style->getOption(m_sClassName + L"MiddleBorderWidth", m_sMiddleBorderWidth);
			style->getOption(m_sClassName + L"InnerBorderWidth", m_sInnerBorderWidth);
			style->getOption(m_sClassName + L"CaptionPadding", m_fCaptionPadding);

			style->getOption(m_sClassName + L"BtnMinimizeRestore.Size", m_sBtnMinimizeRestore.Size);
			style->getOption(m_sClassName + L"BtnMinimizeRestore.BorderWidth", m_sBtnMinimizeRestore.BorderWidth);
			style->getOption(m_sClassName + L"BtnMinimizeRestore.BorderRadius", m_sBtnMinimizeRestore.BorderRadius);
			style->getOption(m_sClassName + L"BtnMinimizeRestore.IconPadding", m_sBtnMinimizeRestore.IconPadding);

			style->getOption(m_sClassName + L"BtnMaximizeRestore.Size", m_sBtnMaximizeRestore.Size);
			style->getOption(m_sClassName + L"BtnMaximizeRestore.BorderWidth", m_sBtnMaximizeRestore.BorderWidth);
			style->getOption(m_sClassName + L"BtnMaximizeRestore.BorderRadius", m_sBtnMaximizeRestore.BorderRadius);
			style->getOption(m_sClassName + L"BtnMaximizeRestore.IconPadding", m_sBtnMaximizeRestore.IconPadding);

			style->getOption(m_sClassName + L"BtnClose.Size", m_sBtnClose.Size);
			style->getOption(m_sClassName + L"BtnClose.BorderWidth", m_sBtnClose.BorderWidth);
			style->getOption(m_sClassName + L"BtnClose.BorderRadius", m_sBtnClose.BorderRadius);
			style->getOption(m_sClassName + L"BtnClose.IconPadding", m_sBtnClose.IconPadding);
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String state;
				switch ((State)i)
				{
				case State::Normal:
					state = L"Normal";
					break;
				case State::Hovered:
					state = L"Hovered";
					break;
				case State::Active:
					state = L"Active";
					break;
				default:
					state = L"Disabled";
				}
				style->getOption(m_sClassName + L"ShadowColor[" + state + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L"ShadowShift[" + state + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L"ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
				style->getOption(m_sClassName + L"OuterBorderColor[" + state + L"]", m_aOuterBorderColor[i]);
				style->getOption(m_sClassName + L"MiddleBorderColor[" + state + L"]", m_aMiddleBorderColor[i]);
				style->getOption(m_sClassName + L"MiddleBorderGradient[" + state + L"]", m_aMiddleBorderGradient[i]);
				style->getOption(m_sClassName + L"InnerBorderColor[" + state + L"]", m_aInnerBorderColor[i]);
				style->getOption(m_sClassName + L"BackgroundColor[" + state + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L"BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]);
				style->getOption(m_sClassName + L"CaptionColor[" + state + L"]", m_aCaptionColor[i]);
				style->getOption(m_sClassName + L"CaptionShadowColor[" + state + L"]", m_aCaptionShadowColor[i]);
				style->getOption(m_sClassName + L"CaptionShadowShift[" + state + L"]", m_aCaptionShadowShift[i]);
				style->getOption(m_sClassName + L"CaptionShadowRadius[" + state + L"]", m_aCaptionShadowRadius[i]);
			}
			for (int i = 0; i <= (int)ButtonState::Disabled; i++)
			{
				String state;
				switch ((ButtonState)i)
				{
				case ButtonState::InactiveNormal:
					state = L"InactiveNormal";
					break;
				case ButtonState::InactiveHovered:
					state = L"InactiveHovered";
					break;
				case ButtonState::InactiveDisabled:
					state = L"InactiveDisabled";
					break;
				case ButtonState::Normal:
					state = L"Normal";
					break;
				case ButtonState::Hovered:
					state = L"Hovered";
					break;
				case ButtonState::Active:
					state = L"Active";
					break;
				case ButtonState::ActiveHovered:
					state = L"ActiveHovered";
					break;
				default:
					state = L"Disabled";
				}
				style->getOption(m_sClassName + L"BtnMinimizeRestore.BorderColor[" + state + L"]", m_sBtnMinimizeRestore.BorderColor[i]);
				style->getOption(m_sClassName + L"BtnMinimizeRestore.BackgroundColor[" + state + L"]", m_sBtnMinimizeRestore.BackgroundColor[i]);
				style->getOption(m_sClassName + L"BtnMinimizeRestore.BackgroundGradient[" + state + L"]", m_sBtnMinimizeRestore.BackgroundGradient[i]);
				style->getOption(m_sClassName + L"BtnMinimizeRestore.ShadowColor[" + state + L"]", m_sBtnMinimizeRestore.ShadowColor[i]);
				style->getOption(m_sClassName + L"BtnMinimizeRestore.ShadowShift[" + state + L"]", m_sBtnMinimizeRestore.ShadowShift[i]);
				style->getOption(m_sClassName + L"BtnMinimizeRestore.ShadowRadius[" + state + L"]", m_sBtnMinimizeRestore.ShadowRadius[i]);

				style->getOption(m_sClassName + L"BtnMaximizeRestore.BorderColor[" + state + L"]", m_sBtnMaximizeRestore.BorderColor[i]);
				style->getOption(m_sClassName + L"BtnMaximizeRestore.BackgroundColor[" + state + L"]", m_sBtnMaximizeRestore.BackgroundColor[i]);
				style->getOption(m_sClassName + L"BtnMaximizeRestore.BackgroundGradient[" + state + L"]", m_sBtnMaximizeRestore.BackgroundGradient[i]);
				style->getOption(m_sClassName + L"BtnMaximizeRestore.ShadowColor[" + state + L"]", m_sBtnMaximizeRestore.ShadowColor[i]);
				style->getOption(m_sClassName + L"BtnMaximizeRestore.ShadowShift[" + state + L"]", m_sBtnMaximizeRestore.ShadowShift[i]);
				style->getOption(m_sClassName + L"BtnMaximizeRestore.ShadowRadius[" + state + L"]", m_sBtnMaximizeRestore.ShadowRadius[i]);

				style->getOption(m_sClassName + L"BtnClose.BorderColor[" + state + L"]", m_sBtnClose.BorderColor[i]);
				style->getOption(m_sClassName + L"BtnClose.BackgroundColor[" + state + L"]", m_sBtnClose.BackgroundColor[i]);
				style->getOption(m_sClassName + L"BtnClose.BackgroundGradient[" + state + L"]", m_sBtnClose.BackgroundGradient[i]);
				style->getOption(m_sClassName + L"BtnClose.ShadowColor[" + state + L"]", m_sBtnClose.ShadowColor[i]);
				style->getOption(m_sClassName + L"BtnClose.ShadowShift[" + state + L"]", m_sBtnClose.ShadowShift[i]);
				style->getOption(m_sClassName + L"BtnClose.ShadowRadius[" + state + L"]", m_sBtnClose.ShadowRadius[i]);
			}

			m_bIgnoreGradient = false;
			AdjustConstraints();
			QueryService()->AlignControls();
		}

		bool CFrame::Show()
		{
			return setVisible(true);
		}

		bool CFrame::ShowModal()
		{
			if (!isModal() && getForm())
			{
				CLockRepaint lock{ this };
				setVisible(true);
				CControl::setAlign(Align::None);
				if (m_eFrameState == FrameState::Maximized)
				{
					getTransform()->Translate(0, 0, 0);
					setSize((PointF)getForm()->getClientSize());
				}
				return getForm()->setModalControl(this);
			}
			return false;
		}

		bool CFrame::Hide()
		{
			if (setVisible(false))
			{
				m_eFrameState = FrameState::Normal;
				return true;
			}
			return false;
		}

		bool CFrame::Minimize()
		{
			if (m_eFrameState != FrameState::Minimized && getForm())
			{
				CLockRepaint lock{ this };
				if (m_eFrameState != FrameState::Maximized)
				{
					m_eLastFrameState = m_eFrameState;
					m_sLastRect = RectF{ getTransform()->getTx(), getTransform()->getTy(), getWidth(), getHeight() };
				}
				m_eFrameState = FrameState::Minimized;
				setSize(PointF{ m_fMinimizedWidth, getMinSize().Y });
				// Assume form has no control's transformation
				RectF rect{ 0, (float)getForm()->getClientHeight() - getHeight(), getWidth(), (float)getForm()->getClientHeight() };
				bool row_processed{ false };
				while (true)
				{
					// Check rect is free from another minimized frames
					bool free{ true };
					for (int i = 0; i < getForm()->getControlCount(); i++)
						if (getForm()->getControl(i)->isVisible(false))
						{
							IFrame *frame{ cast<IFrame*>(getForm()->getControl(i)) };
							if (frame && frame->isMinimized())
							{
								RectF r{
									frame->getTransform()->getTx(),
									frame->getTransform()->getTy(),
									frame->getTransform()->getTx() + frame->getWidth(),
									frame->getTransform()->getTy() + frame->getHeight()
								};
								if (Intersects(rect, r, Identity))
								{
									free = false;
									break;
								}
							}
						}
					if (free)
						break;
					// Calculate next position
					if (row_processed && rect.Right >= (float)getForm()->getClientWidth())
					{
						rect.Left = 0;
						rect.Right = getWidth();
						rect.Top -= getHeight();
						rect.Bottom -= getHeight();
						if (rect.Top < 0)
							break;
						row_processed = false;
					}
					row_processed = true;
				}
				getTransform()->Translate(rect.Left, rect.Top, 0);
				return true;
			}
			return false;
		}

		bool CFrame::Maximize()
		{
			if (m_eFrameState != FrameState::Maximized && getForm())
			{
				CLockRepaint lock{ this };
				if (m_eFrameState != FrameState::Minimized)
				{
					m_eLastFrameState = m_eFrameState;
					m_sLastRect = RectF{ getTransform()->getTx(), getTransform()->getTy(), getWidth(), getHeight() };
				}
				m_eFrameState = FrameState::Maximized;
				getTransform()->Translate(0, 0, 0);
				setSize((PointF)getForm()->getClientSize());
				return true;
			}
			return false;
		}

		bool CFrame::Restore()
		{
			if (m_eFrameState != FrameState::Normal)
			{
				CLockRepaint lock{ this };
				switch (m_eLastFrameState)
				{
				case FrameState::Minimized:
					return Minimize();
				case FrameState::Maximized:
					return Maximize();
				case FrameState::Normal:
					m_eFrameState = FrameState::Normal;
					getTransform()->Translate(m_sLastRect.Left, m_sLastRect.Top, 0);
					setSize(PointF{ m_sLastRect.Right, m_sLastRect.Bottom });
					return true;
				}
			}
			return false;
		}

		CFrameService::DownPart CFrame::getPart(const PointF &position)
		{
			if (isVisible(false))
			{
				RectF r;
				if (m_bMinimizable || m_sBtnMinimizeRestore.DisplayDisabled)
				{
					r = getMinimizeRestoreButtonRect();
					if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
						return CFrameService::DownPart::MinimizeRestoreButton;
				}
				if (m_bMaximizable || m_sBtnMaximizeRestore.DisplayDisabled)
				{
					r = getMaximizeRestoreButtonRect();
					if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
						return CFrameService::DownPart::MaximizeRestoreButton;
				}
				if (m_bClosable || m_sBtnClose.DisplayDisabled)
				{
					r = getCloseButtonRect();
					if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
						return CFrameService::DownPart::CloseButton;
				}

				r = getLeftTopCornerRect();
				if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
					return CFrameService::DownPart::LeftTopCorner;
				r = getRightTopCornerRect();
				if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
					return CFrameService::DownPart::RightTopCorner;
				r = getRightBottomCornerRect();
				if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
					return CFrameService::DownPart::RightBottomCorner;
				r = getLeftBottomCornerRect();
				if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
					return CFrameService::DownPart::LeftBottomCorner;
				r = getLeftBorderRect();
				if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
					return CFrameService::DownPart::LeftBorder;
				r = getTopBorderRect();
				if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
					return CFrameService::DownPart::TopBorder;
				r = getRightBorderRect();
				if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
					return CFrameService::DownPart::RightBorder;
				r = getBottomBorderRect();
				if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
					return CFrameService::DownPart::BottomBorder;
				r = getCaptionRect();
				if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
					return CFrameService::DownPart::Caption;
			}
			return CFrameService::DownPart::None;
		}

		RectF CFrame::getCaptionRect()
		{
			RectF result{
				m_sOuterBorderWidth.Left + m_sMiddleBorderWidth.Left + m_sOuterBorderWidth.Left,
				m_sOuterBorderWidth.Top,
				getWidth() - m_sOuterBorderWidth.Right - m_sMiddleBorderWidth.Right - m_sInnerBorderWidth.Right,
				m_sOuterBorderWidth.Top + m_sMiddleBorderWidth.Top
			};
			result.validate();
			return result;
		}

		RectF CFrame::getLeftTopCornerRect()
		{
			return RectF{
				0,
				0,
				m_sOuterBorderWidth.Left + m_sMiddleBorderWidth.Left + m_sInnerBorderWidth.Left,
				m_sOuterBorderWidth.Left + m_sMiddleBorderWidth.Left + m_sInnerBorderWidth.Left };
		}

		RectF CFrame::getRightTopCornerRect()
		{
			RectF result{
				getWidth() - m_sOuterBorderWidth.Right - m_sMiddleBorderWidth.Right - m_sInnerBorderWidth.Right,
				0,
				getWidth(),
				m_sOuterBorderWidth.Right + m_sMiddleBorderWidth.Right + m_sInnerBorderWidth.Right };
			result.validate();
			return result;
		}

		RectF CFrame::getRightBottomCornerRect()
		{
			RectF result{
				getWidth() - m_sOuterBorderWidth.Right - m_sMiddleBorderWidth.Right - m_sInnerBorderWidth.Right,
				getHeight() - m_sOuterBorderWidth.Right - m_sMiddleBorderWidth.Right - m_sInnerBorderWidth.Right,
				getWidth(),
				getHeight()
			};
			result.validate();
			return result;
		}

		RectF CFrame::getLeftBottomCornerRect()
		{
			RectF result{
				0,
				getHeight() - m_sOuterBorderWidth.Left - m_sMiddleBorderWidth.Left - m_sInnerBorderWidth.Left,
				m_sOuterBorderWidth.Left + m_sMiddleBorderWidth.Left + m_sInnerBorderWidth.Left,
				getHeight() };
			result.validate();
			return result;
		}

		RectF CFrame::getLeftBorderRect()
		{
			return RectF{ 0, 0, m_sOuterBorderWidth.Left + m_sMiddleBorderWidth.Left + m_sInnerBorderWidth.Left, getHeight() };
		}

		RectF CFrame::getTopBorderRect()
		{
			return RectF{ 0, 0, getWidth(), m_sOuterBorderWidth.Bottom + m_sMiddleBorderWidth.Bottom + m_sInnerBorderWidth.Bottom };
		}

		RectF CFrame::getRightBorderRect()
		{
			RectF result{ getWidth() - m_sOuterBorderWidth.Right - m_sMiddleBorderWidth.Right - m_sInnerBorderWidth.Right, 0, getWidth(), getHeight() };
			result.validate();
			return result;
		}

		RectF CFrame::getBottomBorderRect()
		{
			RectF result{ 0, getHeight() - m_sOuterBorderWidth.Bottom - m_sMiddleBorderWidth.Bottom - m_sInnerBorderWidth.Bottom, getWidth(), getHeight() };
			result.validate();
			return result;
		}

		RectF CFrame::getMinimizeRestoreButtonRect()
		{
			RectF result;
			result.Left = getWidth() - m_sOuterBorderWidth.Right - m_sMiddleBorderWidth.Right - m_sInnerBorderWidth.Right - m_sBtnMinimizeRestore.Size.X;
			result.Top = m_sOuterBorderWidth.Top;
			if (m_bMaximizable || m_sBtnMaximizeRestore.DisplayDisabled)
				result.Left -= m_sBtnMaximizeRestore.Size.X;
			if (m_bClosable || m_sBtnClose.DisplayDisabled)
				result.Left -= m_sBtnClose.Size.X;
			result.Right = result.Left + m_sBtnMinimizeRestore.Size.X;
			result.Bottom = result.Top + m_sBtnMinimizeRestore.Size.Y;
			return result;
		}

		RectF CFrame::getMaximizeRestoreButtonRect()
		{
			RectF result;
			result.Left = getWidth() - m_sOuterBorderWidth.Right - m_sMiddleBorderWidth.Right - m_sInnerBorderWidth.Right - m_sBtnMaximizeRestore.Size.X;
			result.Top = m_sOuterBorderWidth.Top;
			if (m_bClosable || m_sBtnClose.DisplayDisabled)
				result.Left -= m_sBtnClose.Size.X;
			result.Right = result.Left + m_sBtnMaximizeRestore.Size.X;
			result.Bottom = result.Top + m_sBtnMaximizeRestore.Size.Y;
			return result;
		}

		RectF CFrame::getCloseButtonRect()
		{
			RectF result;
			result.Left = getWidth() - m_sOuterBorderWidth.Right - m_sMiddleBorderWidth.Right - m_sInnerBorderWidth.Right - m_sBtnClose.Size.X;
			result.Top = m_sOuterBorderWidth.Top;
			result.Right = result.Left + m_sBtnClose.Size.X;
			result.Bottom = result.Top + m_sBtnClose.Size.Y;
			return result;
		}

		RectF CFrame::getCaptionRenderRect()
		{
			RectF result{ getCaptionRect() };
			result += getMinimizeRestoreButtonRenderRect();
			result += getMaximizeRestoreButtonRenderRect();
			result += getCloseButtonRenderRect();
			return result;
		}

		RectF CFrame::getMinimizeRestoreButtonRenderRect()
		{
			return AddShadow(getMinimizeRestoreButtonRect(), m_sBtnMinimizeRestore.ShadowColor[(int)m_sBtnMinimizeRestore.State],
				m_sBtnMinimizeRestore.ShadowShift[(int)m_sBtnMinimizeRestore.State], m_sBtnMinimizeRestore.ShadowRadius[(int)m_sBtnMinimizeRestore.State]);
		}

		RectF CFrame::getMaximizeRestoreButtonRenderRect()
		{
			return AddShadow(getMaximizeRestoreButtonRect(), m_sBtnMaximizeRestore.ShadowColor[(int)m_sBtnMaximizeRestore.State],
				m_sBtnMaximizeRestore.ShadowShift[(int)m_sBtnMaximizeRestore.State], m_sBtnMaximizeRestore.ShadowRadius[(int)m_sBtnMaximizeRestore.State]);
		}

		RectF CFrame::getCloseButtonRenderRect()
		{
			return AddShadow(getCloseButtonRect(), m_sBtnClose.ShadowColor[(int)m_sBtnClose.State], m_sBtnClose.ShadowShift[(int)m_sBtnClose.State],
				m_sBtnClose.ShadowRadius[(int)m_sBtnClose.State]);
		}

		ITexture *CFrame::FindIcon(const String &name, RectF &part)
		{
			IStyle *style{ getStyle() };
			if (style)
			{
				IStyleSkin *skin{ style->getSkin(m_sClassName + L"." + name) };
				if (skin)
				{
					part = skin->Rect;
					return getForm()->getRenderer()->CreateTextureFromImage(skin->getImage()->Image, 1, TextureFormat::RGBA, true);
				}
			}
			if (style != Application->Styles->getStyle(0) && (style = Application->Styles->getStyle(0)))
			{
				IStyleSkin *skin{ style->getSkin(m_sClassName + L"." + name) };
				if (skin)
				{
					part = skin->Rect;
					return getForm()->getRenderer()->CreateTextureFromImage(skin->getImage()->Image, 1, TextureFormat::RGBA, true);
				}
			}
			return nullptr;
		}

		String CFrame::StateToString(const ButtonState state)
		{
			switch (state)
			{
			case ButtonState::InactiveNormal: return L"InactiveNormal";
			case ButtonState::InactiveHovered: return L"InactiveHovered";
			case ButtonState::InactiveDisabled: return L"InactiveDisabled";
			case ButtonState::Hovered: return L"Hovered";
			case ButtonState::Active: return L"Active";
			case ButtonState::ActiveHovered: return L"ActiveHovered";
			case ButtonState::Disabled: return L"Disabled";
			default:
				return L"Normal";
			}
		}

		PointF CFrame::getMinSize()
		{
			PointF result{
				m_sOuterBorderWidth.Left + m_sMiddleBorderWidth.Left + m_sInnerBorderWidth.Left + m_sOuterBorderWidth.Right + m_sMiddleBorderWidth.Right + m_sInnerBorderWidth.Right,
				m_sOuterBorderWidth.Top + m_sMiddleBorderWidth.Top + m_sInnerBorderWidth.Top + m_sOuterBorderWidth.Bottom + m_sMiddleBorderWidth.Bottom + m_sInnerBorderWidth.Bottom
			};
			if (m_bMinimizable || m_sBtnMinimizeRestore.DisplayDisabled)
				result.X += m_sBtnMinimizeRestore.Size.X;
			if (m_bMaximizable || m_sBtnMaximizeRestore.DisplayDisabled)
				result.X += m_sBtnMaximizeRestore.Size.X;
			if (m_bClosable || m_sBtnClose.DisplayDisabled)
				result.X += m_sBtnClose.Size.X;
			return result;
		}

		void CFrame::AdjustConstraints()
		{
			PointF min_size{ getMinSize() };
			RectF c{ getConstraints() };
			c.Left = ntl::Max<float>(c.Left, min_size.X);
			c.Top = ntl::Max<float>(c.Top, min_size.Y);
			CControl::setConstraints(c);
		}
	#pragma endregion

	#pragma region Paint
		void CFrame::Render(IRenderer *renderer, const Mat4f &matrix)
		{
			State state{ getState() };
			PointF disp{ DispOnCanvas(m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
				DrawBlockShadow(renderer, rect, m_sBorderRadius, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
				DrawFrame(
					renderer,
					rect,
					m_sOuterBorderWidth,
					m_sMiddleBorderWidth,
					m_sInnerBorderWidth,
					m_sBorderRadius,
					m_aOuterBorderColor[(int)state],
					m_aMiddleBorderColor[(int)state],
					m_aInnerBorderColor[(int)state],
					m_aMiddleBorderGradient[(int)state],
					m_aBackgroundColor[(int)state],
					m_aBackgroundGradient[(int)state]);
				RenderCaption(renderer, state, rect, disp);
				RenderButtons(renderer, state, disp);

				m_pCanvas->setValid(true);
				m_eLastRenderState = state;
			}
			DrawCanvas(renderer, matrix, m_pCanvas, disp);
		}

		void CFrame::RenderButton(IRenderer *renderer, BUTTON &btn, const RectF &btn_rect, const bool allowed, const String &name, const bool first, const ButtonState bs)
		{
			BlockColors colors;
			colors[(int)PointLocation::Outside] = Color{ 0, 0, 0, 0 };
			Block b{ btn_rect, btn.BorderWidth, btn.BorderRadius, PointLocation::Inside };
			if ((allowed || btn.DisplayDisabled) && ((first && btn.ShadowColor[(int)btn.State].A == 0) || (!first && btn.ShadowColor[(int)btn.State].A > 0)))
			{
				if (!first)
					DrawBlockShadow(renderer, b.Rect, btn.BorderRadius, btn.ShadowColor[(int)btn.State], btn.ShadowShift[(int)btn.State], btn.ShadowRadius[(int)btn.State]);
				colors[0] = btn.BorderColor[(int)btn.State].Left;
				colors[1] = btn.BorderColor[(int)btn.State].Top;
				colors[2] = btn.BorderColor[(int)btn.State].Right;
				colors[3] = btn.BorderColor[(int)btn.State].Bottom;
				colors[4] = btn.BackgroundColor[(int)btn.State];
				renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
				if (btn.BackgroundGradient[(int)btn.State].getPointCount() >= 2)
				{
					CStoreBlock s_block{ renderer };
					renderer
						->ActivateBlock(&b)
						->DrawGradient(b.Rect, btn.BackgroundGradient[(int)btn.State]);
				}

				RectF icon_part, icon_rect{ b.Rect };
				icon_rect.Left += btn.BorderWidth.Left + btn.IconPadding.Left;
				icon_rect.Top += btn.BorderWidth.Top + btn.IconPadding.Top;
				icon_rect.Right -= btn.BorderWidth.Right + btn.IconPadding.Right;
				icon_rect.Bottom -= btn.BorderWidth.Bottom + btn.IconPadding.Bottom;
				if (icon_rect.is_valid() && !icon_rect.is_zero())
				{
					ITexture *icon{ FindIcon(name + L"[" + StateToString(btn.State) + L"]", icon_part) };
					if (!icon && btn.State != ButtonState::Normal)
						icon = FindIcon(name + L"[" + StateToString(ButtonState::Normal) + L"]", icon_part);
					if (icon)
					{
						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(icon_rect.Left, icon_rect.Top, 0) * ntl::Mat4Scale<float>(icon_rect.width() / icon_part.width(), icon_rect.height() / icon_part.height(), 1))
							->DrawImage(icon, 1, icon_part);
					}
				}
			}
		}

		void CFrame::RenderButtons(IRenderer *renderer, const State state, const PointF &disp)
		{
			ButtonState bs1{ getBtnMinimizeRestoreState() }, bs2{ getBtnMaximizeRestoreState() }, bs3{ getBtnCloseState() };
			RectF rects[3]{ getMinimizeRestoreButtonRect() + disp, getMaximizeRestoreButtonRect() + disp, getCloseButtonRect() + disp };
			RenderButton(renderer, m_sBtnMinimizeRestore, rects[0], m_bMinimizable, m_eFrameState == FrameState::Minimized ? L"IconRestore" : L"IconMinimize", true, bs1);
			RenderButton(renderer, m_sBtnMaximizeRestore, rects[1], m_bMaximizable, m_eFrameState == FrameState::Maximized ? L"IconRestore" : L"IconMaximize", true, bs2);
			RenderButton(renderer, m_sBtnClose, rects[2], m_bClosable, L"IconClose", true, bs3);

			RenderButton(renderer, m_sBtnMinimizeRestore, rects[0], m_bMinimizable, m_eFrameState == FrameState::Minimized ? L"IconRestore" : L"IconMinimize", false, bs1);
			RenderButton(renderer, m_sBtnMaximizeRestore, rects[1], m_bMaximizable, m_eFrameState == FrameState::Maximized ? L"IconRestore" : L"IconMaximize", false, bs2);
			RenderButton(renderer, m_sBtnClose, rects[2], m_bClosable, L"IconClose", false, bs3);
		}

		void CFrame::RenderCaption(IRenderer *renderer, const State state, const RectF &rect, const PointF &disp)
		{
			if (!m_sCaption.empty())
			{
				IPlatformFont *pf{ getFont()->getPlatformFont(renderer) };
				RectF caption_rect{ getCaptionRect() };
				caption_rect += disp;
				if (!caption_rect.is_zero())
				{
					PointF size{ pf->getStringSize(m_sCaption, getFont()->Distance) };
					PointF position{
						m_fCaptionPadding + m_sOuterBorderWidth.Left + m_sMiddleBorderWidth.Left + m_sInnerBorderWidth.Left + disp.X,
						caption_rect.Top + (caption_rect.height() - size.Y) * 0.5f
					};
					DrawTextShadow(
						renderer,
						pf,
						getFont()->Distance,
						Identity,
						caption_rect,
						PointF{ std::round(position.X),std::round(position.Y) },
						m_sCaption,
						m_aCaptionShadowColor[(int)state],
						m_aCaptionShadowShift[(int)state],
						m_aCaptionShadowRadius[(int)state]);
					Color color{ m_aCaptionColor[(int)state].A > 0 ? m_aCaptionColor[(int)state] : getFont()->Color };
					if (color.A > 0)
					{
						IBaseTexture *old{ renderer->ActiveTarget };
						ITexture *clip{ renderer->CreateTexture(ntl::Round<int>(caption_rect.width()), ntl::Round<int>(caption_rect.height()), 1, TextureFormat::RGBA, true) };
						if (clip)
						{
							CStorePrimitiveMatrix s_matrix{ renderer };
							Mat4f m;
							ntl::Translate<float>(m, std::round(position.X - caption_rect.Left), std::round(position.Y - caption_rect.Top), 0);
							renderer
								->ActivateTarget(clip)
								->Clear(Color{ 0, 0, 0, 0 })
								->ActivatePrimitiveMatrix(&m)
								->DrawText(m_sCaption, pf, getFont()->Distance, color)
								->ActivateTarget(old);
							ntl::Translate<float>(m, caption_rect.Left, caption_rect.Top, 0);
							renderer->ActivatePrimitiveMatrix(&m);
							if (ntl::IsGreater<float>(m_sBorderRadius.Left, 0) || ntl::IsGreater<float>(m_sBorderRadius.Top, 0))
							{
								Block b{ rect, m_sOuterBorderWidth, m_sBorderRadius, PointLocation::Inside };
								CStoreBlock s_block{ renderer };
								renderer
									->ActivateBlock(&b)
									->DrawImage(clip, 1);
							}
							else
								renderer->DrawImage(clip, 1);
							clip->Release();
						}
					}
				}
			}
		}

		void CFrame::RenderMask(IRenderer *renderer)
		{
			if (PrepareCanvas(renderer, &m_pMask, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pMask)
					->Clear(Color{ 0, 0, 0, 0 });
				Block b{ RectF{ 0, 0, getWidth(), getHeight() }, AddElements(m_sOuterBorderWidth, m_sMiddleBorderWidth, m_sOuterBorderWidth), m_sBorderRadius, PointLocation::Inside };
				if (m_sBorderRadius.has_positive())
				{
					CStoreBlock s_block{ renderer };
					renderer
						->ActivateBlock(&b)
						->DrawRectangle(b.Rect, Color{ 0, 0, 0, 255 });
				}
				else
					renderer->DrawRectangle(RectF{ b.Border.Left, b.Border.Top, b.Rect.Right - b.Border.Right, b.Rect.Bottom - b.Border.Bottom } * b.Rect, Color{ 0, 0, 0, 255 });
				m_pMask->setValid(true);
			}
		}
	#pragma endregion
	}
}