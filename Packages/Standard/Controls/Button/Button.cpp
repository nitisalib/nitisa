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
		CButton::CGradientListener::CGradientListener(CButton *control) :
			m_pControl{ control }
		{

		}

		void CButton::CGradientListener::NotifyOnChange()
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
		CButton::CButton() :
			CControl(L"Button", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_bDown{ false },
			m_aOuterBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aInnerBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aBorderRadius{
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 },
				RectF{ 2, 2, 2, 2 } },
			m_aOuterBorderColor{
				BorderColor{ Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 }, Color{ 112, 112, 112, 255 } },
				BorderColor{ Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 173, 178, 181, 255 }, Color{ 173, 178, 181, 255 }, Color{ 173, 178, 181, 255 }, Color{ 173, 178, 181, 255 } } },
			m_aInnerBorderColor{
				BorderColor{ Color{ 243, 243, 243, 255 }, Color{ 243, 243, 243, 255 }, Color{ 243, 243, 243, 255 }, Color{ 243, 243, 243, 255 } },
				BorderColor{ Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 } },
				BorderColor{ Color{ 59, 214, 253, 255 }, Color{ 59, 214, 253, 255 }, Color{ 59, 214, 253, 255 }, Color{ 59, 214, 253, 255 } },
				BorderColor{ Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 }, Color{ 250, 253, 254, 255 } },
				BorderColor{ Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 } },
				BorderColor{ Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 } },
				BorderColor{ Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 } },
				BorderColor{ Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 } },
				BorderColor{ Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 } },
				BorderColor{ Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 } },
				BorderColor{ Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 } },
				BorderColor{ Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 }, Color{ 158, 176, 186, 255 } },
				BorderColor{ Color{ 252, 252, 252, 255 }, Color{ 252, 252, 252, 255 }, Color{ 252, 252, 252, 255 }, Color{ 252, 252, 252, 255 } } },
			m_aBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 244, 244, 244, 255 } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aShadowRadius{
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1 },
			m_aPadding{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aContentHorizontalAlign{
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center,
				TextAlign::Center },
			m_aContentVerticalAlign{
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle,
				VerticalAlign::Middle },
			m_aCaptionColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 133, 135, 139, 255 } },
			m_aCaptionShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aCaptionShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aCaptionShadowRadius{
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1,
				1 },
			m_aImageList{
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr },
			m_aIconIndex{
				-1,
				-1,
				-1,
				-1,
				-1,
				-1,
				-1,
				-1,
				-1,
				-1,
				-1,
				-1,
				-1 },
			m_aIconPadding{
				8,
				8,
				8,
				8,
				8,
				8,
				8,
				8,
				8,
				8,
				8,
				8,
				8 },
			m_aIconOnRight{
				true,
				true,
				true,
				true,
				true,
				true,
				true,
				true,
				true,
				true,
				true,
				true,
				true },
			m_pCanvas{ nullptr },
			m_bKeyDown{ false },
			m_bMouseDown{ false },
			m_bIgnoreGradient{ true },
			m_bCaptionChanged{ false },
			OnClick{ nullptr }
		{
			setService(new CButtonService(this), true);
			setSize(PointF{ 104, 23 });
			m_aBackgroundGradient[(int)State::Normal].setPointCount(4);
			m_aBackgroundGradient[(int)State::Normal].setPoint(0, Color1D{ 0.000f, Color{ 242, 242, 242, 255 } });
			m_aBackgroundGradient[(int)State::Normal].setPoint(1, Color1D{ 0.499f, Color{ 235, 235, 235, 255 } });
			m_aBackgroundGradient[(int)State::Normal].setPoint(2, Color1D{ 0.500f, Color{ 221, 221, 221, 255 } });
			m_aBackgroundGradient[(int)State::Normal].setPoint(3, Color1D{ 1.000f, Color{ 207, 207, 207, 255 } });
			m_aBackgroundGradient[(int)State::Hovered].setPointCount(4);
			m_aBackgroundGradient[(int)State::Hovered].setPoint(0, Color1D{ 0.000f, Color{ 234, 246, 253, 255 } });
			m_aBackgroundGradient[(int)State::Hovered].setPoint(1, Color1D{ 0.499f, Color{ 217, 240, 252, 255 } });
			m_aBackgroundGradient[(int)State::Hovered].setPoint(2, Color1D{ 0.500f, Color{ 190, 230, 253, 255 } });
			m_aBackgroundGradient[(int)State::Hovered].setPoint(3, Color1D{ 1.000f, Color{ 167, 217, 245, 255 } });
			m_aBackgroundGradient[(int)State::Focused].setPointCount(4);
			m_aBackgroundGradient[(int)State::Focused].setPoint(0, Color1D{ 0.000f, Color{ 238, 244, 247, 255 } });
			m_aBackgroundGradient[(int)State::Focused].setPoint(1, Color1D{ 0.499f, Color{ 232, 239, 244, 255 } });
			m_aBackgroundGradient[(int)State::Focused].setPoint(2, Color1D{ 0.500f, Color{ 211, 227, 236, 255 } });
			m_aBackgroundGradient[(int)State::Focused].setPoint(3, Color1D{ 1.000f, Color{ 195, 216, 228, 255 } });
			m_aBackgroundGradient[(int)State::FocusedHovered].setPointCount(4);
			m_aBackgroundGradient[(int)State::FocusedHovered].setPoint(0, Color1D{ 0.000f, Color{ 234, 246, 253, 255 } });
			m_aBackgroundGradient[(int)State::FocusedHovered].setPoint(1, Color1D{ 0.499f, Color{ 217, 240, 252, 255 } });
			m_aBackgroundGradient[(int)State::FocusedHovered].setPoint(2, Color1D{ 0.500f, Color{ 190, 230, 253, 255 } });
			m_aBackgroundGradient[(int)State::FocusedHovered].setPoint(3, Color1D{ 1.000f, Color{ 167, 217, 245, 255 } });
			m_aBackgroundGradient[(int)State::Active].setPointCount(4);
			m_aBackgroundGradient[(int)State::Active].setPoint(0, Color1D{ 0.000f, Color{ 229, 244, 252, 255 } });
			m_aBackgroundGradient[(int)State::Active].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 246, 255 } });
			m_aBackgroundGradient[(int)State::Active].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 239, 255 } });
			m_aBackgroundGradient[(int)State::Active].setPoint(3, Color1D{ 1.000f, Color{ 109, 182, 221, 255 } });
			m_aBackgroundGradient[(int)State::ActiveHovered].setPointCount(4);
			m_aBackgroundGradient[(int)State::ActiveHovered].setPoint(0, Color1D{ 0.000f, Color{ 229, 244, 252, 255 } });
			m_aBackgroundGradient[(int)State::ActiveHovered].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 246, 255 } });
			m_aBackgroundGradient[(int)State::ActiveHovered].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 239, 255 } });
			m_aBackgroundGradient[(int)State::ActiveHovered].setPoint(3, Color1D{ 1.000f, Color{ 109, 182, 221, 255 } });
			m_aBackgroundGradient[(int)State::Down].setPointCount(4);
			m_aBackgroundGradient[(int)State::Down].setPoint(0, Color1D{ 0.000f, Color{ 229, 244, 255, 255 } });
			m_aBackgroundGradient[(int)State::Down].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 255, 255 } });
			m_aBackgroundGradient[(int)State::Down].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 255, 255 } });
			m_aBackgroundGradient[(int)State::Down].setPoint(3, Color1D{ 1.000f, Color{ 109, 182, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownHovered].setPointCount(4);
			m_aBackgroundGradient[(int)State::DownHovered].setPoint(0, Color1D{ 0.000f, Color{ 229, 244, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownHovered].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownHovered].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownHovered].setPoint(3, Color1D{ 1.000f, Color{ 109, 182, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownFocused].setPointCount(4);
			m_aBackgroundGradient[(int)State::DownFocused].setPoint(0, Color1D{ 0.000f, Color{ 229, 244, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownFocused].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownFocused].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownFocused].setPoint(3, Color1D{ 1.000f, Color{ 109, 182, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownFocusedHovered].setPointCount(4);
			m_aBackgroundGradient[(int)State::DownFocusedHovered].setPoint(0, Color1D{ 0.000f, Color{ 229, 244, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownFocusedHovered].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownFocusedHovered].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownFocusedHovered].setPoint(3, Color1D{ 1.000f, Color{ 109, 182, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownActive].setPointCount(4);
			m_aBackgroundGradient[(int)State::DownActive].setPoint(0, Color1D{ 0.000f, Color{ 229, 244, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownActive].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownActive].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownActive].setPoint(3, Color1D{ 1.000f, Color{ 109, 182, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownActiveHovered].setPointCount(4);
			m_aBackgroundGradient[(int)State::DownActiveHovered].setPoint(0, Color1D{ 0.000f, Color{ 229, 244, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownActiveHovered].setPoint(1, Color1D{ 0.499f, Color{ 196, 229, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownActiveHovered].setPoint(2, Color1D{ 0.500f, Color{ 152, 209, 255, 255 } });
			m_aBackgroundGradient[(int)State::DownActiveHovered].setPoint(3, Color1D{ 1.000f, Color{ 109, 182, 255, 255 } });
			m_bIgnoreGradient = false;
		}

		CButton::CButton(IControl *parent) :CButton()
		{
			setParent(parent);
		}

		CButton::CButton(IForm *parent) : CButton()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region IControl methods
		void CButton::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region CControl getters
		RectF CButton::getClientRect()
		{
			RectF result{ 0, 0, getWidth(), getHeight() };
			State state{ getState() };
			result.Left += m_aOuterBorderWidth[(int)state].Left + m_aInnerBorderWidth[(int)state].Left + m_aPadding[(int)state].Left;
			result.Top += m_aOuterBorderWidth[(int)state].Top + m_aInnerBorderWidth[(int)state].Top + m_aPadding[(int)state].Top;
			result.Right -= m_aOuterBorderWidth[(int)state].Right + m_aInnerBorderWidth[(int)state].Right + m_aPadding[(int)state].Right;
			result.Bottom -= m_aOuterBorderWidth[(int)state].Bottom + m_aInnerBorderWidth[(int)state].Bottom + m_aPadding[(int)state].Bottom;
			result.validate();
			return result;
		}

		RectF CButton::getRenderRect()
		{
			RectF result{ getRenderRect(State::Normal) };
			for (int i = (int)State::Normal + 1; i <= (int)State::Disabled; i++)
				result += getRenderRect((State)i);
			return result;
		}
	#pragma endregion

	#pragma region Getters
		CButton::State CButton::getState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (m_bDown)
			{
				if (m_bKeyDown || m_bMouseDown)
				{
					if (isHovered())
						return State::DownActiveHovered;
					return State::DownActive;
				}
				if (isFocused())
				{
					if (isHovered())
						return State::DownFocusedHovered;
					return State::DownFocused;
				}
				if (isHovered())
					return State::DownHovered;
				return State::Down;
			}
			if (m_bKeyDown || m_bMouseDown)
			{
				if (isHovered())
					return State::ActiveHovered;
				return State::Active;
			}
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

		RectF CButton::getOuterBorderWidth(const State state) const
		{
			return m_aOuterBorderWidth[(int)state];
		}

		RectF CButton::getInnerBorderWidth(const State state) const
		{
			return m_aInnerBorderWidth[(int)state];
		}

		RectF CButton::getBorderRadius(const State state) const
		{
			return m_aBorderRadius[(int)state];
		}

		BorderColor CButton::getOuterBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state];
		}

		Color CButton::getLeftOuterBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state].Left;
		}

		Color CButton::getTopOuterBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state].Top;
		}

		Color CButton::getRightOuterBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state].Right;
		}

		Color CButton::getBottomOuterBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state].Bottom;
		}

		BorderColor CButton::getInnerBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state];
		}

		Color CButton::getLeftInnerBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state].Left;
		}

		Color CButton::getTopInnerBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state].Top;
		}

		Color CButton::getRightInnerBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state].Right;
		}

		Color CButton::getBottomInnerBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state].Bottom;
		}

		Color CButton::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CButton::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		Color CButton::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		PointF CButton::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		int CButton::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		RectF CButton::getPadding(const State state) const
		{
			return m_aPadding[(int)state];
		}

		TextAlign CButton::getContentHorizontalAlign(const State state) const
		{
			return m_aContentHorizontalAlign[(int)state];
		}

		VerticalAlign CButton::getContentVerticalAlign(const State state) const
		{
			return m_aContentVerticalAlign[(int)state];
		}

		String CButton::getCaption()
		{
			return m_sCaption;
		}

		bool CButton::isDown()
		{
			return m_bDown;
		}

		Color CButton::getCaptionColor(const State state) const
		{
			return m_aCaptionColor[(int)state];
		}

		Color CButton::getCaptionShadowColor(const State state) const
		{
			return m_aCaptionShadowColor[(int)state];
		}

		PointF CButton::getCaptionShadowShift(const State state) const
		{
			return m_aCaptionShadowShift[(int)state];
		}

		int CButton::getCaptionShadowRadius(const State state) const
		{
			return m_aCaptionShadowRadius[(int)state];
		}

		IImageList *CButton::getImageList(const State state) const
		{
			return m_aImageList[(int)state];
		}

		int CButton::getIconIndex(const State state) const
		{
			return m_aIconIndex[(int)state];
		}

		float CButton::getIconPadding(const State state) const
		{
			return m_aIconPadding[(int)state];
		}

		bool CButton::isIconOnRight(const State state) const
		{
			return m_aIconOnRight[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CButton::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aOuterBorderWidth[i] *= s;
					m_aInnerBorderWidth[i] *= s;
					m_aBorderRadius[i] *= avg;
					m_aShadowShift[i] *= s;
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
					m_aPadding[i] *= s;
					m_aCaptionShadowShift[i] *= s;
					m_aCaptionShadowRadius[i] = ntl::Round<int>((float)m_aCaptionShadowRadius[i] * avg);
					m_aIconPadding[i] *= s.X;
				}
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CButton::setOuterBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aOuterBorderWidth[(int)state]))
			{
				m_aOuterBorderWidth[(int)state] = value;
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

		bool CButton::setInnerBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aInnerBorderWidth[(int)state]))
			{
				m_aInnerBorderWidth[(int)state] = value;
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

		bool CButton::setBorderRadius(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBorderRadius[(int)state]))
			{
				m_aBorderRadius[(int)state] = value;
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

		bool CButton::setOuterBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aOuterBorderColor[(int)state])
			{
				m_aOuterBorderColor[(int)state] = value;
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

		bool CButton::setLeftOuterBorderColor(const State state, const Color &value)
		{
			return setOuterBorderColor(state, BorderColor{ value, m_aOuterBorderColor[(int)state].Top, m_aOuterBorderColor[(int)state].Right, m_aOuterBorderColor[(int)state].Bottom });
		}

		bool CButton::setTopOuterBorderColor(const State state, const Color &value)
		{
			return setOuterBorderColor(state, BorderColor{ m_aOuterBorderColor[(int)state].Left, value, m_aOuterBorderColor[(int)state].Right, m_aOuterBorderColor[(int)state].Bottom });
		}

		bool CButton::setRightOuterBorderColor(const State state, const Color &value)
		{
			return setOuterBorderColor(state, BorderColor{ m_aOuterBorderColor[(int)state].Left, m_aOuterBorderColor[(int)state].Top, value, m_aOuterBorderColor[(int)state].Bottom });
		}

		bool CButton::setBottomOuterBorderColor(const State state, const Color &value)
		{
			return setOuterBorderColor(state, BorderColor{ m_aOuterBorderColor[(int)state].Left, m_aOuterBorderColor[(int)state].Top, m_aOuterBorderColor[(int)state].Right, value });
		}

		bool CButton::setInnerBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aInnerBorderColor[(int)state])
			{
				m_aInnerBorderColor[(int)state] = value;
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

		bool CButton::setLeftInnerBorderColor(const State state, const Color &value)
		{
			return setInnerBorderColor(state, BorderColor{ value, m_aInnerBorderColor[(int)state].Top, m_aInnerBorderColor[(int)state].Right, m_aInnerBorderColor[(int)state].Bottom });
		}

		bool CButton::setTopInnerBorderColor(const State state, const Color &value)
		{
			return setInnerBorderColor(state, BorderColor{ m_aInnerBorderColor[(int)state].Left, value, m_aInnerBorderColor[(int)state].Right, m_aInnerBorderColor[(int)state].Bottom });
		}

		bool CButton::setRightInnerBorderColor(const State state, const Color &value)
		{
			return setInnerBorderColor(state, BorderColor{ m_aInnerBorderColor[(int)state].Left, m_aInnerBorderColor[(int)state].Top, value, m_aInnerBorderColor[(int)state].Bottom });
		}

		bool CButton::setBottomInnerBorderColor(const State state, const Color &value)
		{
			return setInnerBorderColor(state, BorderColor{ m_aInnerBorderColor[(int)state].Left, m_aInnerBorderColor[(int)state].Top, m_aInnerBorderColor[(int)state].Right, value });
		}

		bool CButton::setBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
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

		bool CButton::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
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

		bool CButton::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
					Repaint(false);
				m_aShadowShift[(int)state] = value;
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CButton::setShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
					Repaint(false);
				m_aShadowRadius[(int)state] = value;
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CButton::setPadding(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aPadding[(int)state]))
			{
				m_aPadding[(int)state] = value;
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

		bool CButton::setContentHorizontalAlign(const State state, const TextAlign value)
		{
			if (value != m_aContentHorizontalAlign[(int)state])
			{
				m_aContentHorizontalAlign[(int)state] = value;
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

		bool CButton::setContentVerticalAlign(const State state, const VerticalAlign value)
		{
			if (value != m_aContentVerticalAlign[(int)state])
			{
				m_aContentVerticalAlign[(int)state] = value;
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

		bool CButton::setCaption(const String &value)
		{
			m_bCaptionChanged = true;
			if (value != m_sCaption)
			{
				m_sCaption = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CButton::setDown(const bool value)
		{
			if (value != m_bDown)
			{
				m_bDown = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CButton::setCaptionColor(const State state, const Color &value)
		{
			if (value != m_aCaptionColor[(int)state])
			{
				m_aCaptionColor[(int)state] = value;
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

		bool CButton::setCaptionShadowColor(const State state, const Color &value)
		{
			if (value != m_aCaptionShadowColor[(int)state])
			{
				m_aCaptionShadowColor[(int)state] = value;
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

		bool CButton::setCaptionShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aCaptionShadowShift[(int)state]))
			{
				m_aCaptionShadowShift[(int)state] = value;
				if (m_aCaptionShadowColor[(int)state].A > 0 && getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CButton::setCaptionShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aCaptionShadowRadius[(int)state])
			{
				m_aCaptionShadowRadius[(int)state] = value;
				if (m_aCaptionShadowColor[(int)state].A > 0 && getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CButton::setImageList(const State state, IImageList *value)
		{
			if (value != m_aImageList[(int)state])
			{
				m_aImageList[(int)state] = value;
				if (getState() == state && m_aIconIndex[(int)state] >= 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CButton::setIconIndex(const State state, const int value)
		{
			if (value != m_aIconIndex[(int)state])
			{
				m_aIconIndex[(int)state] = value;
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

		bool CButton::setIconPadding(const State state, const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_aIconPadding[(int)state]))
			{
				m_aIconPadding[(int)state] = value;
				if (m_aImageList[(int)state] && m_aIconIndex[(int)state] >= 0 && getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CButton::setIconOnRight(const State state, const bool value)
		{
			if (value != m_aIconOnRight[(int)state])
			{
				m_aIconOnRight[(int)state] = value;
				if (m_aImageList[(int)state] && m_aIconIndex[(int)state] >= 0 && getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CButton::setOuterBorderWidth(const RectF &value)
		{
			bool result{ false };
			if (!value.has_negative())
				for (int i = 0; i <= (int)State::Disabled; i++)
					if (IsNotEqual(value, m_aOuterBorderWidth[i]))
					{
						m_aOuterBorderWidth[i] = value;
						result = true;
					}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setInnerBorderWidth(const RectF &value)
		{
			bool result{ false };
			if (!value.has_negative())
				for (int i = 0; i <= (int)State::Disabled; i++)
					if (IsNotEqual(value, m_aInnerBorderWidth[i]))
					{
						m_aInnerBorderWidth[i] = value;
						result = true;
					}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setBorderRadius(const RectF &value)
		{
			bool result{ false };
			if (!value.has_negative())
				for (int i = 0; i <= (int)State::Disabled; i++)
					if (IsNotEqual(value, m_aBorderRadius[i]))
					{
						m_aBorderRadius[i] = value;
						result = true;
					}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setOuterBorderColor(const BorderColor &value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aOuterBorderColor[i])
				{
					m_aOuterBorderColor[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setInnerBorderColor(const BorderColor &value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aInnerBorderColor[i])
				{
					m_aInnerBorderColor[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setBackgroundColor(const Color &value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aBackgroundColor[i])
				{
					m_aBackgroundColor[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setShadowColor(const Color &value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aShadowColor[i])
				{
					m_aShadowColor[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setShadowShift(const PointF &value)
		{
			CLockRepaint lock{ this };
			Repaint(false);
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (IsNotEqual(value, m_aShadowShift[i]))
				{
					m_aShadowShift[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setShadowRadius(const int value)
		{
			CLockRepaint lock{ this };
			Repaint(false);
			bool result{ false };
			if (value >= 1)
				for (int i = 0; i <= (int)State::Disabled; i++)
					if (value != m_aShadowRadius[i])
					{
						m_aShadowRadius[i] = value;
						result = true;
					}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setPadding(const RectF &value)
		{
			bool result{ false };
			if (!value.has_negative())
				for (int i = 0; i <= (int)State::Disabled; i++)
					if (IsNotEqual(value, m_aPadding[i]))
					{
						m_aPadding[i] = value;
						result = true;
					}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setContentHorizontalAlign(const TextAlign value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aContentHorizontalAlign[i])
				{
					m_aContentHorizontalAlign[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setContentVerticalAlign(const VerticalAlign value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aContentVerticalAlign[i])
				{
					m_aContentVerticalAlign[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setCaptionColor(const Color &value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aCaptionColor[i])
				{
					m_aCaptionColor[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setCaptionShadowColor(const Color &value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aCaptionShadowColor[i])
				{
					m_aCaptionShadowColor[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setCaptionShadowShift(const PointF &value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (IsNotEqual(value, m_aCaptionShadowShift[i]))
				{
					m_aCaptionShadowShift[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setCaptionShadowRadius(const int value)
		{
			bool result{ false };
			if (value >= 1)
				for (int i = 0; i <= (int)State::Disabled; i++)
					if (value != m_aCaptionShadowRadius[i])
					{
						m_aCaptionShadowRadius[i] = value;
						result = true;
					}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setImageList(IImageList *value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aImageList[i])
				{
					m_aImageList[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setIconIndex(const int value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aIconIndex[i])
				{
					m_aIconIndex[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setIconPadding(const float value)
		{
			bool result{ false };
			if (ntl::IsGreaterOrEqual<float>(value, 0))
				for (int i = 0; i <= (int)State::Disabled; i++)
					if (ntl::IsNotEqual<float>(value, m_aIconPadding[i]))
					{
						m_aIconPadding[i] = value;
						result = true;
					}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CButton::setIconOnRight(const bool value)
		{
			bool result{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (value != m_aIconOnRight[i])
				{
					m_aIconOnRight[i] = value;
					result = true;
				}
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}
	#pragma endregion

	#pragma region Helpers
		void CButton::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
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
				case State::Active:
					state = L"Active";
					break;
				case State::ActiveHovered:
					state = L"ActiveHovered";
					break;
				case State::Down:
					state = L"Down";
					break;
				case State::DownHovered:
					state = L"DownHovered";
					break;
				case State::DownFocused:
					state = L"DownFocused";
					break;
				case State::DownFocusedHovered:
					state = L"DownFocusedHovered";
					break;
				case State::DownActive:
					state = L"DownActive";
					break;
				case State::DownActiveHovered:
					state = L"DownActiveHovered";
					break;
				case State::Disabled:
					state = L"Disabled";
					break;
				default:
					state = L"Normal";
				}
				style->getOption(m_sClassName + L".OuterBorderWidth[" + state + L"]", m_aOuterBorderWidth[i]);
				style->getOption(m_sClassName + L".InnerBorderWidth[" + state + L"]", m_aInnerBorderWidth[i]);
				style->getOption(m_sClassName + L".BorderRadius[" + state + L"]", m_aBorderRadius[i]);
				style->getOption(m_sClassName + L".OuterBorderColor[" + state + L"]", m_aOuterBorderColor[i]);
				style->getOption(m_sClassName + L".InnerBorderColor[" + state + L"]", m_aInnerBorderColor[i]);
				style->getOption(m_sClassName + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]);
				style->getOption(m_sClassName + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
				style->getOption(m_sClassName + L".Padding[" + state + L"]", m_aPadding[i]);
				style->getOption(m_sClassName + L".CaptionColor[" + state + L"]", m_aCaptionColor[i]);
				style->getOption(m_sClassName + L".CaptionShadowColor[" + state + L"]", m_aCaptionShadowColor[i]);
				style->getOption(m_sClassName + L".CaptionShadowShift[" + state + L"]", m_aCaptionShadowShift[i]);
				style->getOption(m_sClassName + L".CaptionShadowRadius[" + state + L"]", m_aCaptionShadowRadius[i]);
				style->getOption(m_sClassName + L".IconPadding[" + state + L"]", m_aIconPadding[i]);
				style->getOption(m_sClassName + L".IconOnRight[" + state + L"]", m_aIconOnRight[i]);
			}
			m_bIgnoreGradient = false;
		}

		RectF CButton::getRenderRect(const State state)
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
		}

		void CButton::Click()
		{
			if (OnClick)
				OnClick(this);
		}
	#pragma endregion

	#pragma region Render
		void CButton::Render()
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

				DrawBlockShadow(
					renderer,
					rect,
					m_aBorderRadius[(int)state],
					m_aShadowColor[(int)state],
					m_aShadowShift[(int)state],
					m_aShadowRadius[(int)state]);
				DrawDoubleBackground(
					renderer,
					rect,
					m_aOuterBorderWidth[(int)state],
					m_aInnerBorderWidth[(int)state],
					m_aBorderRadius[(int)state],
					m_aOuterBorderColor[(int)state],
					m_aInnerBorderColor[(int)state],
					m_aBackgroundColor[(int)state],
					m_aBackgroundGradient[(int)state]);

				RenderContent(state, renderer, pf, rect);

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}

		void CButton::RenderContent(const State state, IRenderer *renderer, IPlatformFont *pf, const RectF &rect)
		{
			ITexture *icon{ (m_aImageList[(int)state] && m_aIconIndex[(int)state] >= 0) ? m_aImageList[(int)state]->getTexture(m_aIconIndex[(int)state]) : nullptr };
			if (!icon && m_sCaption.empty())
				return;
			RectF client_rect{ rect };
			client_rect.Left += m_aOuterBorderWidth[(int)state].Left + m_aInnerBorderWidth[(int)state].Left + m_aPadding[(int)state].Left;
			client_rect.Top += m_aOuterBorderWidth[(int)state].Top + m_aInnerBorderWidth[(int)state].Top + m_aPadding[(int)state].Top;
			client_rect.Right -= m_aOuterBorderWidth[(int)state].Right + m_aInnerBorderWidth[(int)state].Right + m_aPadding[(int)state].Right;
			client_rect.Bottom -= m_aOuterBorderWidth[(int)state].Bottom + m_aInnerBorderWidth[(int)state].Bottom + m_aPadding[(int)state].Bottom;
			client_rect.validate();
			if (client_rect.is_zero())
				return;
			PointF caption_size{ m_sCaption.empty() ? PointF{ 0, 0 } : pf->getStringSize(m_sCaption, getFont()->Distance) };
			float width{ caption_size.X + ((m_sCaption.empty() || !icon) ? 0 : m_aIconPadding[(int)state]) + (icon ? icon->Widthf : 0) };
			RectF borders{ AddElements(m_aOuterBorderWidth[(int)state], m_aInnerBorderWidth[(int)state], m_aPadding[(int)state]) };
			Block b{ rect, borders, m_aBorderRadius[(int)state], PointLocation::Inside };
			if (!m_sCaption.empty())
			{
				PointF pos{ borders.Left, borders.Top }; // In clip coordinates
				switch (m_aContentHorizontalAlign[(int)state])
				{
				case TextAlign::Center:
					pos.X = (borders.Left + rect.width() - borders.Right - width) * 0.5f;
					break;
				case TextAlign::Right:
					pos.X = rect.width() - borders.Right - width;
					break;
				default:
					break;
				}
				if (icon && !m_aIconOnRight[(int)state])
					pos.X += icon->Widthf + m_aIconPadding[(int)state];
				switch (m_aContentVerticalAlign[(int)state])
				{
				case VerticalAlign::Middle:
					pos.Y = (borders.Top + rect.height() - borders.Bottom - caption_size.Y) * 0.5f;
					break;
				case VerticalAlign::Bottom:
					pos.Y = rect.height() - borders.Bottom - caption_size.Y;
					break;
				default:
					break;
				}
				pos.X += rect.Left;
				pos.Y += rect.Top;
				pos.X = std::round(pos.X);
				pos.Y = std::round(pos.Y);
				DrawTextShadow(
					renderer,
					pf,
					getFont()->Distance,
					Identity,
					client_rect,
					pos,
					m_sCaption,
					m_aCaptionShadowColor[(int)state],
					m_aCaptionShadowShift[(int)state],
					m_aCaptionShadowRadius[(int)state]);
				Color color{ m_aCaptionColor[(int)state].A > 0 ? m_aCaptionColor[(int)state] : getFont()->Color };
				if (color.A > 0)
				{
					CStoreBlock s_block{ renderer };
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivateBlock(&b)
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(pos.X, pos.Y, 0))
						->DrawText(m_sCaption, pf, getFont()->Distance, color);
				}
			}
			if (icon)
			{
				PointF pos{ 0, borders.Top };
				switch (m_aContentHorizontalAlign[(int)state])
				{
				case TextAlign::Center:
					pos.X = (borders.Left + rect.width() - borders.Right - width) * 0.5f;
					break;
				case TextAlign::Right:
					pos.X = rect.width() - borders.Right - width;
					break;
				default:
					break;
				}
				if (m_aIconOnRight[(int)state])
					pos.X = pos.X + width - icon->Widthf;
				switch (m_aContentVerticalAlign[(int)state])
				{
				case VerticalAlign::Middle:
					pos.Y = (borders.Top + rect.height() - borders.Bottom - icon->Heightf) * 0.5f;
					break;
				case VerticalAlign::Bottom:
					pos.Y = rect.height() - borders.Bottom - icon->Heightf;
					break;
				default:
					break;
				}
				pos.X += rect.Left;
				pos.Y += rect.Top;
				CStoreBlock s_block{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBlock(&b)
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(pos.X), std::round(pos.Y), 0))
					->DrawImage(icon, 1);
			}
		}
	#pragma endregion
	}
}