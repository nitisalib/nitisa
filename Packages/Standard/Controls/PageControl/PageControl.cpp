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
		CPageControl::CGradientListener::CGradientListener(CPageControl *control) :
			m_pControl{ control }
		{

		}

		void CPageControl::CGradientListener::NotifyOnChange()
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
		CPageControl::CPageControl() :
			CControl(L"PageControl", true, true, true, true, false, true),
			m_cGradientListener{ this },
			m_sHeaderSize{ -1, -1 },
			m_eHeaderPosition{ HeaderPosition::Top },
			m_bMultiline{ false },
			m_sBorderWidth{ 1, 1, 1, 1 },
			m_sBorderColor{ Color{ 137, 140, 149, 255 }, Color{ 137, 140, 149, 255 }, Color{ 137, 140, 149, 255 }, Color{ 137, 140, 149, 255 } },
			m_sBackgroundColor{ 255, 255, 255, 255 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_sHeaderShift{ 2, 2 },
			m_sHeaderPadding{ 4, 2, 4, 2 },
			m_fHeaderBorderWidth{ 1 },
			m_aHeaderBorderColor{
				Color{ 137, 140, 149, 255 },
				Color{ 60, 127, 177, 255 },
				Color{ 137, 140, 149, 255 },
				Color{ 137, 140, 255, 255 },
				Color{ 137, 140, 149, 255 } },
			m_aHeaderBackgroundColor{
				Color{ 235, 235, 235, 255 },
				Color{ 235, 235, 235, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 235, 235, 255, 255 },
				Color{ 255, 255, 255, 255 } },
			m_aHeaderBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aCaptionColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aCaptionShadowColor{
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
				PointF{ 0, 0 } },
			m_aCaptionShadowRadius{ 1, 1, 1, 1, 1 },
			m_pImageList{ nullptr },
			m_fScrollArrowSize{ 0.333f },
			m_sScrollBorderWidth{ 1, 1, 1, 1 },
			m_sScrollBorderRadius{ 0, 0, 0, 0 },
			m_aScrollBorderColor{
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
				BorderColor{ Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } } },
			m_aScrollBackgroundColor{
				Color{ 232, 232, 232, 255 },
				Color{ 232, 232, 232, 255 },
				Color{ 232, 232, 232, 255 },
				Color{ 232, 232, 232, 255 },
				Color{ 232, 232, 232, 255 } },
			m_aScrollBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aScrollArrowColor{
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 } },
			m_iActiveIndex{ -1 },
			m_sIconPadding{ 0, 1, 4, 1 },
			m_bUseMask{ true },
			m_fScrollInterval{ ScrollInterval },
			m_fDeltaScrollTimer{ 10 },
			m_fDeltaScrollWheel{ 10 },
			m_bIgnoreGradient{ true },
			m_fScroll{ 0 },
			m_fScrollMax{ 0 },
			m_pCanvas{ nullptr },
			m_pMask{ nullptr },
			m_iHoveredTab{ -1 },
			m_eHoveredElement{ Element::None },
			m_eDownElement{ Element::None },
			m_fHeaderSize{ 0 },
			OnActivateTabSheet{ nullptr }
		{
			setService(new CPageControlService(this), true);
			m_aHeaderBackgroundGradient[(int)TabState::Normal].setPointCount(4);
			m_aHeaderBackgroundGradient[(int)TabState::Normal].setPoint(0, Color1D{ 0.000f, Color{ 242, 242, 242, 255 } });
			m_aHeaderBackgroundGradient[(int)TabState::Normal].setPoint(1, Color1D{ 0.500f, Color{ 235, 235, 235, 255 } });
			m_aHeaderBackgroundGradient[(int)TabState::Normal].setPoint(2, Color1D{ 0.501f, Color{ 221, 221, 221, 255 } });
			m_aHeaderBackgroundGradient[(int)TabState::Normal].setPoint(3, Color1D{ 1.000f, Color{ 207, 207, 207, 255 } });

			m_aHeaderBackgroundGradient[(int)TabState::Hovered].setPointCount(4);
			m_aHeaderBackgroundGradient[(int)TabState::Hovered].setPoint(0, Color1D{ 0.000f, Color{ 234, 246, 253, 255 } });
			m_aHeaderBackgroundGradient[(int)TabState::Hovered].setPoint(1, Color1D{ 0.500f, Color{ 217, 240, 252, 255 } });
			m_aHeaderBackgroundGradient[(int)TabState::Hovered].setPoint(2, Color1D{ 0.501f, Color{ 190, 230, 253, 255 } });
			m_aHeaderBackgroundGradient[(int)TabState::Hovered].setPoint(3, Color1D{ 1.000f, Color{ 167, 217, 245, 255 } });

			m_aScrollBackgroundGradient[(int)ScrollState::Normal].setPointCount(4);
			m_aScrollBackgroundGradient[(int)ScrollState::Normal].setPoint(0, Color1D{ 0.000f, Color{ 242, 242, 242, 255 } });
			m_aScrollBackgroundGradient[(int)ScrollState::Normal].setPoint(1, Color1D{ 0.500f, Color{ 232, 232, 232, 255 } });
			m_aScrollBackgroundGradient[(int)ScrollState::Normal].setPoint(2, Color1D{ 0.501f, Color{ 219, 219, 219, 255 } });
			m_aScrollBackgroundGradient[(int)ScrollState::Normal].setPoint(3, Color1D{ 1.000f, Color{ 209, 209, 209, 255 } });

			m_aScrollBackgroundGradient[(int)ScrollState::Disabled].setPointCount(4);
			m_aScrollBackgroundGradient[(int)ScrollState::Disabled].setPoint(0, Color1D{ 0.000f, Color{ 242, 242, 242, 255 } });
			m_aScrollBackgroundGradient[(int)ScrollState::Disabled].setPoint(1, Color1D{ 0.500f, Color{ 232, 232, 232, 255 } });
			m_aScrollBackgroundGradient[(int)ScrollState::Disabled].setPoint(2, Color1D{ 0.501f, Color{ 219, 219, 219, 255 } });
			m_aScrollBackgroundGradient[(int)ScrollState::Disabled].setPoint(3, Color1D{ 1.000f, Color{ 209, 209, 209, 255 } });

			m_aScrollBackgroundGradient[(int)ScrollState::Hovered].setPointCount(4);
			m_aScrollBackgroundGradient[(int)ScrollState::Hovered].setPoint(0, Color1D{ 0.000f, Color{ 233, 246, 253, 255 } });
			m_aScrollBackgroundGradient[(int)ScrollState::Hovered].setPoint(1, Color1D{ 0.500f, Color{ 210, 237, 252, 255 } });
			m_aScrollBackgroundGradient[(int)ScrollState::Hovered].setPoint(2, Color1D{ 0.501f, Color{ 187, 229, 252, 255 } });
			m_aScrollBackgroundGradient[(int)ScrollState::Hovered].setPoint(3, Color1D{ 1.000f, Color{ 169, 219, 245, 255 } });

			m_aScrollBackgroundGradient[(int)ScrollState::Active].setPointCount(4);
			m_aScrollBackgroundGradient[(int)ScrollState::Active].setPoint(0, Color1D{ 0.000f, Color{ 233, 246, 253, 255 } });
			m_aScrollBackgroundGradient[(int)ScrollState::Active].setPoint(1, Color1D{ 0.500f, Color{ 210, 237, 252, 255 } });
			m_aScrollBackgroundGradient[(int)ScrollState::Active].setPoint(2, Color1D{ 0.501f, Color{ 187, 229, 252, 255 } });
			m_aScrollBackgroundGradient[(int)ScrollState::Active].setPoint(3, Color1D{ 1.000f, Color{ 169, 219, 245, 255 } });

			m_aScrollBackgroundGradient[(int)ScrollState::ActiveHovered].setPointCount(4);
			m_aScrollBackgroundGradient[(int)ScrollState::ActiveHovered].setPoint(0, Color1D{ 0.000f, Color{ 194, 228, 246, 255 } });
			m_aScrollBackgroundGradient[(int)ScrollState::ActiveHovered].setPoint(1, Color1D{ 0.500f, Color{ 194, 228, 246, 255 } });
			m_aScrollBackgroundGradient[(int)ScrollState::ActiveHovered].setPoint(2, Color1D{ 0.501f, Color{ 170, 217, 243, 255 } });
			m_aScrollBackgroundGradient[(int)ScrollState::ActiveHovered].setPoint(3, Color1D{ 1.000f, Color{ 145, 204, 235, 255 } });

			m_bIgnoreGradient = false;

			setSize(PointF{ 288, 78 });
		}

		CPageControl::CPageControl(IForm *parent) : CPageControl()
		{
			setForm(parent);
		}

		CPageControl::CPageControl(IControl *parent) : CPageControl()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		RectF CPageControl::getClientRect()
		{
			RectF result{ m_sBorderWidth.Left, m_sBorderWidth.Top, getWidth() - m_sBorderWidth.Right, getHeight() - m_sBorderWidth.Bottom };
			switch (m_eHeaderPosition)
			{
			case HeaderPosition::Left:
				result.Left += m_fHeaderSize;
				break;
			case HeaderPosition::Top:
				result.Top += m_fHeaderSize;
				break;
			case HeaderPosition::Right:
				result.Right -= m_fHeaderSize;
				break;
			case HeaderPosition::Bottom:
				result.Bottom -= m_fHeaderSize;
				break;
			}
			result.validate();
			return result;
		}

		bool CPageControl::isFocusByMouse()
		{
			return false;
		}

		int CPageControl::getTabSheetCount()
		{
			return getControlCount();
		}

		ITabSheet *CPageControl::getTabSheet(const int index)
		{
			return cast<ITabSheet*>(getControl(index));
		}

		ITabSheet *CPageControl::getActiveTabSheet()
		{
			return cast<ITabSheet*>(getControl(m_iActiveIndex));
		}

		int CPageControl::getActiveIndex()
		{
			return m_iActiveIndex;
		}
	#pragma endregion

	#pragma region Geters
		PointF CPageControl::getHeaderSize() const
		{
			return m_sHeaderSize;
		}

		CPageControl::HeaderPosition CPageControl::getHeaderPosition() const
		{
			return m_eHeaderPosition;
		}

		bool CPageControl::isMultiline() const
		{
			return m_bMultiline;
		}

		RectF CPageControl::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		BorderColor CPageControl::getBorderColor() const
		{
			return m_sBorderColor;
		}

		Color CPageControl::getLeftBorderColor() const
		{
			return m_sBorderColor.Left;
		}

		Color CPageControl::getTopBorderColor() const
		{
			return m_sBorderColor.Top;
		}

		Color CPageControl::getRightBorderColor() const
		{
			return m_sBorderColor.Right;
		}

		Color CPageControl::getBottomBorderColor() const
		{
			return m_sBorderColor.Bottom;
		}

		Color CPageControl::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CPageControl::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		PointF CPageControl::getHeaderShift() const
		{
			return m_sHeaderShift;
		}

		RectF CPageControl::getHeaderPadding() const
		{
			return m_sHeaderPadding;
		}

		float CPageControl::getHeaderBorderWidth() const
		{
			return m_fHeaderBorderWidth;
		}

		Color CPageControl::getHeaderBorderColor(const TabState state) const
		{
			return m_aHeaderBorderColor[(int)state];
		}

		Color CPageControl::getHeaderBackgroundColor(const TabState state) const
		{
			return m_aHeaderBackgroundColor[(int)state];
		}

		Gradient *CPageControl::getHeaderBackgroundGradient(const TabState state)
		{
			return &m_aHeaderBackgroundGradient[(int)state];
		}

		Color CPageControl::getCaptionColor(const TabState state) const
		{
			return m_aCaptionColor[(int)state];
		}

		Color CPageControl::getCaptionShadowColor(const TabState state) const
		{
			return m_aCaptionShadowColor[(int)state];
		}

		PointF CPageControl::getCaptionShadowShift(const TabState state) const
		{
			return m_aCaptionShadowShift[(int)state];
		}

		int CPageControl::getCaptionShadowRadius(const TabState state) const
		{
			return m_aCaptionShadowRadius[(int)state];
		}

		IImageList *CPageControl::getImageList()
		{
			return m_pImageList;
		}

		float CPageControl::getScrollArrowSize() const
		{
			return m_fScrollArrowSize;
		}

		RectF CPageControl::getScrollBorderWidth() const
		{
			return m_sScrollBorderWidth;
		}

		RectF CPageControl::getScrollBorderRadius() const
		{
			return m_sScrollBorderRadius;
		}

		BorderColor CPageControl::getScrollBorderColor(const ScrollState state) const
		{
			return m_aScrollBorderColor[(int)state];
		}

		Color CPageControl::getScrollLeftBorderColor(const ScrollState state) const
		{
			return m_aScrollBorderColor[(int)state].Left;
		}

		Color CPageControl::getScrollTopBorderColor(const ScrollState state) const
		{
			return m_aScrollBorderColor[(int)state].Top;
		}

		Color CPageControl::getScrollRightBorderColor(const ScrollState state) const
		{
			return m_aScrollBorderColor[(int)state].Right;
		}

		Color CPageControl::getScrollBottomBorderColor(const ScrollState state) const
		{
			return m_aScrollBorderColor[(int)state].Bottom;
		}

		Color CPageControl::getScrollBackgroundColor(const ScrollState state) const
		{
			return m_aScrollBackgroundColor[(int)state];
		}

		Gradient *CPageControl::getScrollBackgroundGradient(const ScrollState state)
		{
			return &m_aScrollBackgroundGradient[(int)state];
		}

		Color CPageControl::getScrollArrowColor(const ScrollState state) const
		{
			return m_aScrollArrowColor[(int)state];
		}

		RectF CPageControl::getIconPadding() const
		{
			return m_sIconPadding;
		}

		bool CPageControl::isUseMask() const
		{
			return m_bUseMask;
		}

		float CPageControl::getScrollInterval() const
		{
			return m_fScrollInterval;
		}

		float CPageControl::getDeltaScrollTimer() const
		{
			return m_fDeltaScrollTimer;
		}

		float CPageControl::getDeltaScrollWheel() const
		{
			return m_fDeltaScrollWheel;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CPageControl::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				if (m_eHeaderPosition == HeaderPosition::Top || m_eHeaderPosition == HeaderPosition::Bottom)
				{
					m_sHeaderSize *= s;
					m_sHeaderShift *= s;
				}
				else
				{
					m_sHeaderSize.X *= s.Y;
					m_sHeaderSize.Y *= s.X;
					m_sHeaderShift.X *= s.Y;
					m_sHeaderShift.Y *= s.X;
				}
				m_sBorderWidth *= s;
				m_sHeaderPadding *= s;
				m_fHeaderBorderWidth *= avg;
				for (int i = 0; i <= (int)TabState::Disabled; i++)
				{
					m_aCaptionShadowShift[i] *= s;
					m_aCaptionShadowRadius[i] = ntl::Round<int>((float)m_aCaptionShadowRadius[i] * avg);
				}
				m_sScrollBorderWidth *= s;
				m_sScrollBorderRadius *= avg;
				m_sIconPadding *= s;
				m_fDeltaScrollTimer *= avg;
				m_fDeltaScrollWheel *= avg;
				Update();
				QueryService()->AlignControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPageControl::setActiveIndex(const int value)
		{
			int v{ ntl::Clamp<int>(value, 0, getControlCount() - 1) };
			if (v != m_iActiveIndex && getTabSheet(v))
				return getTabSheet(v)->setVisible(true);
			return false;
		}

		bool CPageControl::setActiveTabSheet(ITabSheet *value)
		{
			if (value && value->getParent() == this && value != getActiveTabSheet())
				return value->setVisible(true);
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CPageControl::setHeaderSize(const PointF &value)
		{
			if (ntl::IsLessOrEqual<float>(value.X, 0) && ntl::IsLessOrEqual<float>(value.Y, 0) && ntl::IsLessOrEqual<float>(m_sHeaderSize.X, 0) && ntl::IsLessOrEqual<float>(m_sHeaderSize.Y, 0))
				return false;
			if (IsNotEqual(value, m_sHeaderSize))
			{
				CLockRepaint lock{ this };
				m_sHeaderSize.X = ntl::IsLessOrEqual<float>(value.X, 0) ? -1 : value.X;
				m_sHeaderSize.Y = ntl::IsLessOrEqual<float>(value.Y, 0) ? -1 : value.Y;
				Update();
				QueryService()->AlignControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPageControl::setHeaderPosition(const HeaderPosition value)
		{
			if (value != m_eHeaderPosition)
			{
				CLockRepaint lock{ this };
				m_eHeaderPosition = value;
				Update();
				QueryService()->AlignControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPageControl::setMultiline(const bool value)
		{
			if (value != m_bMultiline)
			{
				CLockRepaint lock{ this };
				m_bMultiline = value;
				Update();
				QueryService()->AlignControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPageControl::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				CLockRepaint lock{ this };
				m_sBorderWidth = value;
				Update();
				QueryService()->AlignControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPageControl::setBorderColor(const BorderColor &value)
		{
			if (value != m_sBorderColor)
			{
				m_sBorderColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPageControl::setLeftBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ value, m_sBorderColor.Top, m_sBorderColor.Right, m_sBorderColor.Bottom });
		}

		bool CPageControl::setTopBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, value, m_sBorderColor.Right, m_sBorderColor.Bottom });
		}

		bool CPageControl::setRightBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, m_sBorderColor.Top, value, m_sBorderColor.Bottom });
		}

		bool CPageControl::setBottomBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, m_sBorderColor.Top, m_sBorderColor.Right, value });
		}

		bool CPageControl::setBackgroundColor(const Color &value)
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

		bool CPageControl::setHeaderShift(const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_sHeaderShift))
			{
				CLockRepaint lock{ this };
				m_sHeaderShift = value;
				Update();
				QueryService()->AlignControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPageControl::setHeaderPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sHeaderPadding))
			{
				CLockRepaint lock{ this };
				m_sHeaderPadding = value;
				if (ntl::IsLessOrEqual<float>(m_sHeaderSize.X, 0) || ntl::IsLessOrEqual<float>(m_sHeaderSize.Y, 0))
				{
					Update();
					QueryService()->AlignControls();
				}
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPageControl::setHeaderBorderWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fHeaderBorderWidth))
			{
				CLockRepaint lock{ this };
				m_fHeaderBorderWidth = value;
				if (ntl::IsLessOrEqual<float>(m_sHeaderSize.X, 0) || ntl::IsLessOrEqual<float>(m_sHeaderSize.Y, 0))
				{
					Update();
					QueryService()->AlignControls();
				}
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPageControl::setHeaderBorderColor(const TabState state, const Color &value)
		{
			if (value != m_aHeaderBorderColor[(int)state])
			{
				m_aHeaderBorderColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPageControl::setHeaderBackgroundColor(const TabState state, const Color &value)
		{
			if (value != m_aHeaderBackgroundColor[(int)state])
			{
				m_aHeaderBackgroundColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPageControl::setCaptionColor(const TabState state, const Color &value)
		{
			if (value != m_aCaptionColor[(int)state])
			{
				m_aCaptionColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPageControl::setCaptionShadowColor(const TabState state, const Color &value)
		{
			if (value != m_aCaptionShadowColor[(int)state])
			{
				m_aCaptionShadowColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPageControl::setCaptionShadowShift(const TabState state, const PointF &value)
		{
			if (IsNotEqual(value, m_aCaptionShadowShift[(int)state]))
			{
				m_aCaptionShadowShift[(int)state] = value;
				if (m_aCaptionShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPageControl::setCaptionShadowRadius(const TabState state, const int value)
		{
			if (value >= 1 && value != m_aCaptionShadowRadius[(int)state])
			{
				m_aCaptionShadowRadius[(int)state] = value;
				if (m_aCaptionShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPageControl::setImageList(IImageList *value)
		{
			if (value != m_pImageList)
			{
				CLockRepaint lock{ this };
				m_pImageList = value;
				if (ntl::IsLessOrEqual<float>(m_sHeaderSize.X, 0))
				{
					Update();
					QueryService()->AlignControls();
				}
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPageControl::setScrollArrowSize(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollArrowSize))
			{
				m_fScrollArrowSize = value;
				if (ntl::IsGreater<float>(m_fScrollMax, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPageControl::setScrollBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sScrollBorderWidth))
			{
				m_sScrollBorderWidth = value;
				if (ntl::IsGreater<float>(m_fScrollMax, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPageControl::setScrollBorderRadius(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sScrollBorderRadius))
			{
				m_sScrollBorderRadius = value;
				if (ntl::IsGreater<float>(m_fScrollMax, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPageControl::setScrollBackgroundColor(const ScrollState state, const Color &value)
		{
			if (value != m_aScrollBackgroundColor[(int)state])
			{
				m_aScrollBackgroundColor[(int)state] = value;
				if (ntl::IsGreater<float>(m_fScrollMax, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPageControl::setScrollBorderColor(const ScrollState state, const BorderColor &value)
		{
			if (value != m_aScrollBorderColor[(int)state])
			{
				m_aScrollBorderColor[(int)state] = value;
				if (ntl::IsGreater<float>(m_fScrollMax, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPageControl::setScrollLeftBorderColor(const ScrollState state, const Color &value)
		{
			return setScrollBorderColor(state, BorderColor{ value, m_aScrollBorderColor[(int)state].Top, m_aScrollBorderColor[(int)state].Right, m_aScrollBorderColor[(int)state].Bottom });
		}

		bool CPageControl::setScrollTopBorderColor(const ScrollState state, const Color &value)
		{
			return setScrollBorderColor(state, BorderColor{ m_aScrollBorderColor[(int)state].Left, value, m_aScrollBorderColor[(int)state].Right, m_aScrollBorderColor[(int)state].Bottom });
		}

		bool CPageControl::setScrollRightBorderColor(const ScrollState state, const Color &value)
		{
			return setScrollBorderColor(state, BorderColor{ m_aScrollBorderColor[(int)state].Left, m_aScrollBorderColor[(int)state].Top, value, m_aScrollBorderColor[(int)state].Bottom });
		}

		bool CPageControl::setScrollBottomBorderColor(const ScrollState state, const Color &value)
		{
			return setScrollBorderColor(state, BorderColor{ m_aScrollBorderColor[(int)state].Left, m_aScrollBorderColor[(int)state].Top, m_aScrollBorderColor[(int)state].Right, value });
		}

		bool CPageControl::setScrollArrowColor(const ScrollState state, const Color &value)
		{
			if (value != m_aScrollArrowColor[(int)state])
			{
				m_aScrollArrowColor[(int)state] = value;
				if (ntl::IsGreater<float>(m_fScrollMax, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPageControl::setIconPadding(const RectF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.Top, 0) && ntl::IsGreaterOrEqual<float>(value.Right, 0) && ntl::IsGreaterOrEqual<float>(value.Bottom, 0) &&
				(ntl::IsNotEqual<float>(value.Top, m_sIconPadding.Top) || ntl::IsNotEqual<float>(value.Right, m_sIconPadding.Right) || ntl::IsNotEqual<float>(value.Bottom, m_sIconPadding.Bottom)))
			{
				m_sIconPadding = value;
				if (m_pImageList)
				{
					Update();
					QueryService()->AlignControls();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPageControl::setUseMask(const bool value)
		{
			if (value != m_bUseMask)
			{
				m_bUseMask = value;
				Repaint(true);
				return true;
			}
			return false;
		}

		bool CPageControl::setScrollInterval(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollInterval))
			{
				m_fScrollInterval = value;
				return true;
			}
			return false;
		}

		bool CPageControl::setDeltaScrollTimer(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fDeltaScrollTimer))
			{
				m_fDeltaScrollTimer = value;
				return true;
			}
			return false;
		}

		bool CPageControl::setDeltaScrollWheel(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fDeltaScrollWheel))
			{
				m_fDeltaScrollWheel = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface methods
		void CPageControl::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			CControl::Refresh(refresh_children);
		}

		bool CPageControl::AttachControl(IControl *control)
		{
			if (!cast<ITabSheet*>(control))
				return false;
			return CControl::AttachControl(control);
		}

		bool CPageControl::InsertControl(IControl *control, const int before)
		{
			if (!cast<ITabSheet*>(control))
				return false;
			return CControl::InsertControl(control, before);
		}

		IControl *CPageControl::CreateChild()
		{
			return new CTabSheet(this);
		}

		ITabSheet *CPageControl::CreateTabSheet()
		{
			return new CTabSheet(this);
		}

		ITabSheet *CPageControl::CreateTabSheet(const int before)
		{
			CTabSheet *tab{ new CTabSheet() };
			CControl::InsertControl(tab, before);
			return tab;
		}

		bool CPageControl::AddTabSheet(ITabSheet *tab)
		{
			return CControl::AttachControl(tab);
		}

		bool CPageControl::InsertTabSheet(ITabSheet *tab, const int before)
		{
			return CControl::InsertControl(tab, before);
		}

		bool CPageControl::DeleteTabSheet(const int index)
		{
			return CControl::DeleteControl(index);
		}

		bool CPageControl::DeleteTabSheet(ITabSheet *tab)
		{
			return CControl::DeleteControl(tab);
		}

		bool CPageControl::DeleteTabSheets()
		{
			return CControl::DeleteControls();
		}
	#pragma endregion

	#pragma region Helpers
		void CPageControl::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BorderWidth", m_sBorderWidth);
			style->getOption(m_sClassName + L".BorderColor", m_sBorderColor);
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L".HeaderShift", m_sHeaderShift);
			style->getOption(m_sClassName + L".HeaderPadding", m_sHeaderPadding);
			style->getOption(m_sClassName + L".HeaderBorderWidth", m_fHeaderBorderWidth);
			for (int i = 0; i <= (int)TabState::Disabled; i++)
			{
				String state;
				switch ((TabState)i)
				{
				case TabState::Normal:
					state = L"Normal";
					break;
				case TabState::Hovered:
					state = L"Hovered";
					break;
				case TabState::Active:
					state = L"Active";
					break;
				case TabState::ActiveFocused:
					state = L"ActiveFocused";
					break;
				default:
					state = L"Disabled";
				}
				style->getOption(m_sClassName + L".HeaderBorderColor[" + state + L"]", m_aHeaderBorderColor[i]);
				style->getOption(m_sClassName + L".HeaderBackgroundColor[" + state + L"]", m_aHeaderBackgroundColor[i]);
				style->getOption(m_sClassName + L".HeaderBackgroundGradient[" + state + L"]", m_aHeaderBackgroundGradient[i]);
				style->getOption(m_sClassName + L".CaptionColor[" + state + L"]", m_aCaptionColor[i]);
				style->getOption(m_sClassName + L".CaptionShadowColor[" + state + L"]", m_aCaptionShadowColor[i]);
				style->getOption(m_sClassName + L".CaptionShadowShift[" + state + L"]", m_aCaptionShadowShift[i]);
				style->getOption(m_sClassName + L".CaptionShadowRadius[" + state + L"]", m_aCaptionShadowRadius[i]);
			}
			style->getOption(m_sClassName + L".ScrollArrowSize", m_fScrollArrowSize);
			style->getOption(m_sClassName + L".ScrollBorderWidth", m_sScrollBorderWidth);
			style->getOption(m_sClassName + L".ScrollBorderRadius", m_sScrollBorderRadius);
			for (int i = 0; i <= (int)ScrollState::Disabled; i++)
			{
				String state;
				switch ((ScrollState)i)
				{
				case ScrollState::Normal:
					state = L"Normal";
					break;
				case ScrollState::Hovered:
					state = L"Hovered";
					break;
				case ScrollState::Active:
					state = L"Active";
					break;
				case ScrollState::ActiveHovered:
					state = L"ActiveHovered";
					break;
				default:
					state = L"Disabled";
				}
				style->getOption(m_sClassName + L"ScrollBorderColor[" + state + L"]", m_aScrollBorderColor[i]);
				style->getOption(m_sClassName + L"ScrollBackgroundColor[" + state + L"]", m_aScrollBackgroundColor[i]);
				style->getOption(m_sClassName + L"ScrollBackgroundGradient[" + state + L"]", m_aScrollBackgroundGradient[i]);
				style->getOption(m_sClassName + L"ScrollArrowColor[" + state + L"]", m_aScrollArrowColor[i]);
			}
			style->getOption(m_sClassName + L".IconPadding", m_sIconPadding);
			m_bIgnoreGradient = false;
			Update();
			QueryService()->AlignControls();
		}

		void CPageControl::Update()
		{
			IPlatformFont *pf{ getForm() ? getFont()->getPlatformFont(getForm()->getRenderer()) : nullptr };
			if (pf)
			{
				m_fControlSize = (m_eHeaderPosition == HeaderPosition::Top || m_eHeaderPosition == HeaderPosition::Bottom) ? getWidth() : getHeight();
				m_iActiveLine = -1;
				m_aLines.clear();
				m_fLineHeight = ntl::IsGreater<float>(m_sHeaderSize.Y, 0) ? m_sHeaderSize.Y : (pf->getStringSize(L"Wy", 0).Y + m_fHeaderBorderWidth + m_sHeaderPadding.Top + m_sHeaderPadding.Bottom);
				// Split on lines
				std::vector<INFO> infos;
				float all_width{ 2 * m_sHeaderShift.X };
				bool line_processed{ false };
				for (int i = 0; i < getControlCount(); i++)
				{
					INFO info;
					info.Tab = getTabSheet(i);
					info.CaptionSize = pf->getStringSize(info.Tab->getCaption(), getFont()->Distance);
					CTabSheet *tab_sheet{ cast<CTabSheet*>(info.Tab) };
					if (tab_sheet && tab_sheet->getIconIndex() >= 0 && m_pImageList)
					{
						info.Icon = m_pImageList->getTexture(tab_sheet->getIconIndex());
						if (info.Icon)
							info.IconPart = RectF{ 0, 0, info.Icon->Widthf, info.Icon->Heightf };
					}
					else
						info.Icon = nullptr;
					if (ntl::IsGreater<float>(m_sHeaderSize.X, 0))
						info.Width = m_sHeaderSize.X;
					else
					{
						info.Width = info.CaptionSize.X + 2 * m_fHeaderBorderWidth + m_sHeaderPadding.Left + m_sHeaderPadding.Right;
						if (info.Icon)
							info.Width += m_fLineHeight + m_sIconPadding.Right;
					}

					if (m_bMultiline && line_processed && ntl::IsGreater<float>(all_width + info.Width, m_fControlSize))
					{
						all_width = 2 * m_sHeaderShift.X + info.Width;
						m_aLines.push_back(infos);
						infos.clear();
						infos.push_back(info);
					}
					else
					{
						all_width += info.Width;
						line_processed = true;
						infos.push_back(info);
					}
				}
				if (infos.size() > 0)
					m_aLines.push_back(infos);
				// Header size
				m_fHeaderSize = m_sHeaderShift.Y + (float)m_aLines.size() * m_fLineHeight;
				// Find active line
				int index{ 0 };
				for (int i = 0; i < (int)m_aLines.size(); i++)
				{
					bool found{ false };
					for (auto pos = m_aLines[i].begin(); pos != m_aLines[i].end(); pos++, index++)
						if (index == m_iActiveIndex)
						{
							m_iActiveLine = i;
							found = true;
							break;
						}
					if (found)
						break;
				}
				// Adjust size
				float total_size{ ntl::Max<float>(0, m_fControlSize - 2 * m_sHeaderShift.X) };
				for (int i = 0; i < (int)m_aLines.size(); i++)
				{
					float line_width{ 0 };
					for (auto pos = m_aLines[i].begin(); pos != m_aLines[i].end(); pos++)
						line_width += pos->Width;
					if (m_aLines.size() > 1 || (m_bMultiline && ntl::IsGreater<float>(line_width, total_size)) || (getControlCount() == 1 && ntl::IsGreater<float>(line_width, total_size)))
						for (auto pos = m_aLines[i].begin(); pos != m_aLines[i].end(); pos++)
							pos->Width *= total_size / line_width;
				}
				// Scroll
				m_fScrollMax = 0;
				if (!m_bMultiline)
				{
					float w{ 2 * m_sHeaderShift.X };
					if (ntl::IsGreater<float>(m_sHeaderSize.X, 0))
						w += (float)getControlCount() * m_sHeaderSize.X;
					else
						for (int i = 0; i < getControlCount(); i++)
						{
							ITabSheet *tab{ getTabSheet(i) };
							w += pf->getStringSize(tab->getCaption(), getFont()->Distance).X + 2 * m_fHeaderBorderWidth + m_sHeaderPadding.Left + m_sHeaderPadding.Right;
							CTabSheet *tab_sheet{ cast<CTabSheet*>(tab) };
							if (tab_sheet && tab_sheet->getIconIndex() >= 0 && m_pImageList && m_pImageList->getImage(tab_sheet->getIconIndex()))
								w += m_fLineHeight + m_sIconPadding.Right;
						}
					float control_size{ (m_eHeaderPosition == HeaderPosition::Top || m_eHeaderPosition == HeaderPosition::Bottom) ? getWidth() : getHeight() };
					if (ntl::IsGreater<float>(w, control_size))
						m_fScrollMax = w - control_size + 2 * m_fLineHeight + 3 * m_sHeaderShift.Y;
				}
				m_fScroll = ntl::Min<float>(m_fScrollMax, m_fScroll);
				// Scroll to active tab
				if (m_iActiveIndex >= 0 && !m_bMultiline && ntl::IsGreater<float>(m_fScrollMax, 0))
				{
					float x{ m_sHeaderShift.X - m_fScroll };
					ITabSheet *active{ getActiveTabSheet() };
					float control_size{ (m_eHeaderPosition == HeaderPosition::Top || m_eHeaderPosition == HeaderPosition::Bottom) ? getWidth() : getHeight() };
					CPageControl::INFO info{ nullptr, PointF{ 0, 0 }, 0, nullptr, RectF{ 0, 0, 0, 0 } };
					for (auto pos = m_aLines[0].begin(); pos != m_aLines[0].end(); pos++)
					{
						if (pos->Tab == active)
						{
							info = *pos;
							break;
						}
						x += pos->Width;
					}
					if (ntl::IsGreater<float>(x + info.Width, control_size - 2 * m_fLineHeight - 3 * m_sHeaderShift.Y))
					{
						float s{ ntl::Max<float>(0, m_fScroll + x + info.Width - control_size + 2 * m_fLineHeight + 3 * m_sHeaderShift.Y) };
						if (ntl::IsNotEqual<float>(m_fScroll, s))
							m_fScroll = s;
					}
					else if (ntl::IsLess<float>(x, m_sHeaderShift.X))
						m_fScroll += x - m_sHeaderShift.X;
				}
			}
		}

		bool CPageControl::UpdateHoveredElement(const PointF &position)
		{
			RectF header{ getHeaderRect() };
			if (position.X >= header.Left && position.X < header.Right && position.Y >= header.Top && position.Y < header.Bottom)
			{
				// Calculate coordinates to be like tabs position is always HeaderPosition::Top
				PointF p{ position };
				switch (m_eHeaderPosition)
				{
				case HeaderPosition::Left:
					p = PointF{ getHeight() - p.Y, p.X };
					break;
				case HeaderPosition::Right:
					p = PointF{ p.Y, getWidth() - p.X };
					break;
				case HeaderPosition::Bottom:
					p.Y = getHeight() - p.Y;
					break;
				default:
					break;
				}
				// Scrolls
				if (!m_bMultiline && ntl::IsGreater<float>(m_fScrollMax, 0))
				{
					float scroll_size{ m_fLineHeight + m_sHeaderShift.Y };
					if (p.X >= m_fControlSize - 2 * scroll_size && p.X < m_fControlSize - scroll_size && p.Y >= 0 && p.Y < scroll_size)
					{
						if (m_eHoveredElement != Element::ScrollStart)
						{
							m_eHoveredElement = Element::ScrollStart;
							return true;
						}
						return false;
					}
					if (p.X >= m_fControlSize - scroll_size && p.X < m_fControlSize && p.Y >= 0 && p.Y < scroll_size)
					{
						if (m_eHoveredElement != Element::ScrollEnd)
						{
							m_eHoveredElement = Element::ScrollEnd;
							return true;
						}
						return false;
					}
				}
				// Active tab
				if (m_iActiveLine >= 0)
				{
					float y{ m_sHeaderShift.Y + float((int)m_aLines.size() - 1) * m_fLineHeight };
					float x{ m_sHeaderShift.X - m_fScroll };
					ITabSheet *active_tab{ getActiveTabSheet() };
					for (auto pos = m_aLines[m_iActiveLine].begin(); pos != m_aLines[m_iActiveLine].end(); pos++)
					{
						if (pos->Tab == active_tab && p.X >= x && p.X < x + pos->Width && p.Y >= y - m_sHeaderShift.Y && p.Y < y + m_fLineHeight)
						{
							if (m_eHoveredElement != Element::Tab || m_iHoveredTab != m_iActiveIndex)
							{
								m_eHoveredElement = Element::Tab;
								m_iHoveredTab = m_iActiveIndex;
								return true;
							}
							return false;
						}
						x += pos->Width;
					}
				}
				// Tabs
				float y{ m_sHeaderShift.Y };
				for (int step = 0; step <= 1; step++)
					for (int i = 0; i < (int)m_aLines.size(); i++)
						if ((step == 0 && i != m_iActiveLine) || (step == 1 && i == m_iActiveLine))
						{
							float x{ m_sHeaderShift.X - m_fScroll };
							for (auto pos = m_aLines[i].begin(); pos != m_aLines[i].end(); pos++)
							{
								if (p.X >= x && p.X < x + pos->Width && p.Y >= y && p.Y < y + m_fLineHeight)
								{
									int index{ pos->Tab->getIndex() };
									if (m_eHoveredElement != Element::Tab || m_iHoveredTab != index)
									{
										m_eHoveredElement = Element::Tab;
										m_iHoveredTab = index;
										return true;
									}
									return false;
								}
								x += pos->Width;
							}
							y += m_fLineHeight;
						}
			}
			if (m_eHoveredElement != Element::None)
			{
				m_eHoveredElement = Element::None;
				return true;
			}
			return false;
		}

		RectF CPageControl::getTabSheetRect()
		{
			RectF result{ 0, 0, getWidth(), getHeight() };
			switch (m_eHeaderPosition)
			{
			case HeaderPosition::Left:
				result.Left += m_fHeaderSize;
				break;
			case HeaderPosition::Top:
				result.Top += m_fHeaderSize;
				break;
			case HeaderPosition::Right:
				result.Right -= m_fHeaderSize;
				break;
			case HeaderPosition::Bottom:
				result.Bottom -= m_fHeaderSize;
				break;
			}
			result.validate();
			return result;
		}

		RectF CPageControl::getHeaderRect()
		{
			RectF result{ 0, 0, getWidth(), getHeight() };
			switch (m_eHeaderPosition)
			{
			case HeaderPosition::Left:
				result.Right = ntl::Min<float>(result.Right, m_fHeaderSize);
				break;
			case HeaderPosition::Top:
				result.Bottom = ntl::Min<float>(result.Bottom, m_fHeaderSize);
				break;
			case HeaderPosition::Right:
				result.Left = ntl::Max<float>(result.Left, result.Right - m_fHeaderSize);
				break;
			case HeaderPosition::Bottom:
				result.Top = ntl::Max<float>(result.Top, result.Bottom - m_fHeaderSize);
				break;
			}
			return result;
		}

		CPageControl::TabState CPageControl::getTabState(ITabSheet *tab)
		{
			if (!tab->isEnabled(false))
				return TabState::Disabled;
			int index{ tab->getIndex() };
			if (index == m_iActiveIndex)
			{
				if (isFocused())
					return TabState::ActiveFocused;
				return TabState::Active;
			}
			if (m_eHoveredElement == Element::Tab && index == m_iHoveredTab)
				return TabState::Hovered;
			return TabState::Normal;
		}

		CPageControl::ScrollState CPageControl::getScrollStartState()
		{
			if (ntl::IsEqual<float>(m_fScrollMax, 0) || ntl::IsEqual<float>(m_fScroll, 0))
				return ScrollState::Disabled;
			if (m_eDownElement == Element::ScrollStart)
			{
				if (m_eHoveredElement == Element::ScrollStart)
					return ScrollState::ActiveHovered;
				return ScrollState::Active;
			}
			if (m_eHoveredElement == Element::ScrollStart)
				return ScrollState::Hovered;
			return ScrollState::Normal;
		}

		CPageControl::ScrollState CPageControl::getScrollEndState()
		{
			if (ntl::IsEqual<float>(m_fScrollMax, 0) || ntl::IsEqual<float>(m_fScroll, m_fScrollMax))
				return ScrollState::Disabled;
			if (m_eDownElement == Element::ScrollEnd)
			{
				if (m_eHoveredElement == Element::ScrollEnd)
					return ScrollState::ActiveHovered;
				return ScrollState::Active;
			}
			if (m_eHoveredElement == Element::ScrollEnd)
				return ScrollState::Hovered;
			return ScrollState::Normal;
		}
	#pragma endregion

	#pragma region Paint
		void CPageControl::Render(IRenderer *renderer, const Mat4f &matrix)
		{
			if (PrepareCanvas(renderer, &m_pCanvas, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				DrawSimpleBackground(renderer, getTabSheetRect(), m_sBorderWidth, RectF{ 0, 0, 0, 0 }, m_sBorderColor, m_sBackgroundColor, m_cBackgroundGradient);
				IPlatformFont *pf{ getFont()->getPlatformFont(renderer) };
				RenderTabHeaders(renderer, pf);
				RenderScrolls(renderer);

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, matrix, m_pCanvas, PointF{ 0, 0 });
		}

		void CPageControl::RenderTabHeaders(IRenderer *renderer, IPlatformFont *pf)
		{
			float y{ m_sHeaderShift.Y };
			RectF borders{ m_fHeaderBorderWidth, m_eHeaderPosition != HeaderPosition::Bottom ? m_fHeaderBorderWidth : 0, m_fHeaderBorderWidth, m_eHeaderPosition == HeaderPosition::Bottom ? m_fHeaderBorderWidth : 0 };
			ITabSheet *active_tab{ getActiveTabSheet() };
			INFO active_info;
			float active_x{ 0 };
			for (int step = 0; step <= 1; step++)
				for (int i = 0; i < (int)m_aLines.size(); i++)
					if ((step == 0 && i != m_iActiveLine) || (step == 1 && i == m_iActiveLine))
					{
						float x{ m_sHeaderShift.X - m_fScroll };
						for (auto pos : m_aLines[i])
						{
							if (pos.Tab != active_tab)
							{
								if (x + pos.Width >= 0 && x < m_fControlSize)
									RenderTabHeader(renderer, borders, x, y, pf, pos, false);
							}
							else
							{
								active_x = x;
								active_info = pos;
							}
							x += pos.Width;
						}
						if (active_tab && step == 1 && active_x + active_info.Width >= 0 && active_x < m_fControlSize)
							RenderTabHeader(renderer, borders, active_x, y, pf, active_info, true);
						y += m_fLineHeight;
					}
		}

		void CPageControl::RenderTabHeader(IRenderer *renderer, const RectF &borders, const float x, const float y, IPlatformFont *pf, INFO &info, const bool active)
		{
			PointF tab_size{ info.Width + (active ? (2 * m_sHeaderShift.X) : 0), m_fLineHeight + (active ? m_sHeaderShift.Y : 0) };
			float bottom_border{ 0 };
			if (active)
			{
				switch (m_eHeaderPosition)
				{
				case HeaderPosition::Left:
					bottom_border = m_sBorderWidth.Left;
					break;
				case HeaderPosition::Top:
					bottom_border = m_sBorderWidth.Top;
					break;
				case HeaderPosition::Right:
					bottom_border = m_sBorderWidth.Top;
					break;
				case HeaderPosition::Bottom:
					bottom_border = m_sBorderWidth.Top;
					break;
				}
				tab_size.Y += bottom_border;
			}
			ITexture *tab_header{ renderer->CreateTexture(ntl::Round<int>(tab_size.X), ntl::Round<int>(tab_size.Y), 1, TextureFormat::RGBA, true) };
			if (tab_header)
			{
				TabState state{ getTabState(info.Tab) };
				RectF tab_header_rect{ 0, 0, tab_header->Widthf, tab_header->Heightf };
				renderer
					->ActivateTarget(tab_header)
					->Clear(Color{ 0, 0, 0, 0 });
				DrawSimpleBackground(
					renderer,
					tab_header_rect,
					borders,
					RectF{ 0, 0, 0, 0 },
					BorderColor{ m_aHeaderBorderColor[(int)state], m_aHeaderBorderColor[(int)state], m_aHeaderBorderColor[(int)state], m_aHeaderBorderColor[(int)state] }, m_aHeaderBackgroundColor[(int)state], m_aHeaderBackgroundGradient[(int)state]);
				if (!info.Tab->getCaption().empty())
				{
					PointF position{
						(tab_header_rect.width() - info.CaptionSize.X - (info.Icon ? (m_fLineHeight + m_sIconPadding.Right) : 0)) * 0.5f,
						(tab_header_rect.height() - m_fHeaderBorderWidth - bottom_border - info.CaptionSize.Y) * 0.5f };
					if (m_eHeaderPosition == HeaderPosition::Bottom)
						position.Y += bottom_border;
					RectF client{ tab_header_rect.Left + borders.Left, tab_header_rect.Top + borders.Top, tab_header_rect.Right - borders.Right, tab_header_rect.Bottom - borders.Bottom };
					switch (m_eHeaderPosition)
					{
					case HeaderPosition::Top:
						client.Bottom -= bottom_border;
						break;
					case HeaderPosition::Bottom:
						client.Top += bottom_border;
						break;
					default:
						break;
					}
					position.X = std::round(position.X);
					position.Y = std::round(position.Y);
					DrawTextShadow(
						renderer,
						pf,
						getFont()->Distance,
						Identity,
						client,
						position,
						info.Tab->getCaption(),
						m_aCaptionShadowColor[(int)state],
						m_aCaptionShadowShift[(int)state],
						m_aCaptionShadowRadius[(int)state]);

					Color color{ m_aCaptionColor[(int)state].A > 0 ? m_aCaptionColor[(int)state] : getFont()->Color };
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(position.X, position.Y, 0));
					if (ntl::IsGreater<float>(m_fHeaderBorderWidth, 0))
					{
						Block b{ tab_header_rect, borders, RectF{ 0, 0, 0, 0 }, PointLocation::Inside };
						CStoreBlock s_block{ renderer };
						renderer
							->ActivateBlock(&b)
							->DrawText(info.Tab->getCaption(), pf, getFont()->Distance, color);
					}
					else
						renderer->DrawText(info.Tab->getCaption(), pf, getFont()->Distance, color);
				}
				if (info.Icon)
				{
					float icon_height{ tab_size.Y - 2 * m_fHeaderBorderWidth - m_sHeaderPadding.Top - m_sHeaderPadding.Bottom - m_sIconPadding.Top - m_sIconPadding.Bottom };
					RectF icon_rect;
					icon_rect.Right = tab_size.X - m_fHeaderBorderWidth - m_sHeaderPadding.Right - m_sIconPadding.Right;
					icon_rect.Left = icon_rect.Right - icon_height;
					icon_rect.Top = m_fHeaderBorderWidth + m_sHeaderPadding.Top + m_sIconPadding.Top;
					icon_rect.Bottom = tab_size.Y - m_fHeaderBorderWidth - m_sHeaderPadding.Bottom - m_sIconPadding.Bottom;
					if (icon_rect.is_valid() && !icon_rect.is_zero())
					{
						float icon_size{ ntl::Min<float>(icon_rect.width(), icon_rect.height()) };
						float scale{ icon_size / ntl::Max<float>(info.IconPart.width(), info.IconPart.height()) };
						PointF position{ (icon_rect.Left + icon_rect.Right - icon_size) * 0.5f, (icon_rect.Top + icon_rect.Bottom - icon_size) * 0.5f };

						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(position.X, position.Y, 0) * ntl::Mat4Scale<float>(scale, scale, 1))
							->DrawImage(info.Icon, 1, info.IconPart);
					}
				}

				Mat4f t1, r{ 1, 0 };
				switch (m_eHeaderPosition)
				{
				case HeaderPosition::Left:
					ntl::RotateZ<float>(r, -ntl::HalfPi<float>);
					ntl::Translate<float>(t1, y - (active ? m_sHeaderShift.Y : 0), getHeight() - x + (active ? m_sHeaderShift.X : 0), 0);
					break;
				case HeaderPosition::Top:
					ntl::Translate<float>(t1, x - (active ? m_sHeaderShift.X : 0), y - (active ? m_sHeaderShift.Y : 0), 0);
					break;
				case HeaderPosition::Right:
					ntl::RotateZ<float>(r, ntl::HalfPi<float>);
					ntl::Translate<float>(t1, getWidth() - y + (active ? m_sHeaderShift.X : 0), x - (active ? m_sHeaderShift.Y : 0), 0);
					break;
				case HeaderPosition::Bottom:
				default: // Need to silence warning about may be uninitialized t1 member on Linux
					ntl::Translate<float>(t1, x - (active ? m_sHeaderShift.X : 0), getHeight() - y - tab_size.Y + (active ? m_sHeaderShift.Y : 0), 0);
					break;
				}
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->ActivatePrimitiveMatrix(t1 * r)
					->DrawImage(tab_header, 1);
				tab_header->Release();
			}
		}

		void CPageControl::RenderScrolls(IRenderer *renderer)
		{
			if (!m_bMultiline && ntl::IsGreater<float>(m_fScrollMax, 0))
			{
				ITexture *scroller{ renderer->CreateTexture(ntl::Round<int>(m_fLineHeight + m_sHeaderShift.Y), ntl::Round<int>(m_fLineHeight + m_sHeaderShift.Y), 1, TextureFormat::RGBA, true) };
				if (scroller)
				{
					RectF scroller_rect{ 0, 0, scroller->Widthf, scroller->Heightf };
					renderer
						->ActivateTarget(scroller)
						->Clear(Color{ 0, 0, 0, 0 });
					// ScrollDown
					ScrollState state{ getScrollStartState() };
					DrawSimpleBackground(
						renderer,
						scroller_rect,
						m_sScrollBorderWidth,
						m_sScrollBorderRadius,
						m_aScrollBorderColor[(int)state],
						m_aScrollBackgroundColor[(int)state],
						m_aScrollBackgroundGradient[(int)state]);
					Block b{ scroller_rect, m_sScrollBorderWidth, m_sScrollBorderRadius, PointLocation::Inside };
					PointF mid{ scroller_rect.width() * 0.5f, scroller_rect.height() * 0.5f };
					float w{ ntl::Min<float>(scroller_rect.width(), scroller_rect.height()) * m_fScrollArrowSize * 0.5f };
					{
						CStoreBlock s_block{ renderer };
						renderer
							->ActivateBlock(&b)
							->DrawTriangle(PointF{ mid.X - w, mid.Y }, PointF{ mid.X + w, mid.Y - w }, PointF{ mid.X + w, mid.Y + w }, m_aScrollArrowColor[(int)state]);
					}
					Mat4f t1, r{ 1, 0 };
					switch (m_eHeaderPosition)
					{
					case HeaderPosition::Left:
						ntl::RotateZ<float>(r, -ntl::HalfPi<float>);
						ntl::Translate<float>(t1, 0, 2.0f * scroller->Widthf, 0);
						break;
					case HeaderPosition::Top:
						ntl::Translate<float>(t1, getWidth() - 2 * scroller->Widthf, 0, 0);
						break;
					case HeaderPosition::Right:
						ntl::RotateZ<float>(r, ntl::HalfPi<float>);
						ntl::Translate<float>(t1, getWidth(), getHeight() - 2 * scroller->Widthf, 0);
						break;
					case HeaderPosition::Bottom:
					default: // Need to silence warning about may be uninitialized t1 member on Linux
						ntl::Translate<float>(t1, getWidth() - 2 * scroller->Widthf, getHeight() - scroller->Widthf, 0);
						break;
					}
					{
						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer
							->ActivateTarget(m_pCanvas)
							->ActivatePrimitiveMatrix(t1 * r)
							->DrawImage(scroller, 1);
					}

					// ScrollUp
					renderer
						->ActivateTarget(scroller)
						->Clear(Color{ 0, 0, 0, 0 });
					state = getScrollEndState();
					DrawSimpleBackground(
						renderer,
						scroller_rect,
						m_sScrollBorderWidth,
						m_sScrollBorderRadius,
						m_aScrollBorderColor[(int)state],
						m_aScrollBackgroundColor[(int)state],
						m_aScrollBackgroundGradient[(int)state]);
					{
						CStoreBlock s_block{ renderer };
						renderer
							->ActivateBlock(&b)
							->DrawTriangle(PointF{ mid.X + w, mid.Y }, PointF{ mid.X - w, mid.Y + w }, PointF{ mid.X - w, mid.Y - w }, m_aScrollArrowColor[(int)state]);
					}
					switch (m_eHeaderPosition)
					{
					case HeaderPosition::Left:
						ntl::RotateZ<float>(r, -ntl::HalfPi<float>);
						ntl::Translate<float>(t1, 0, scroller->Widthf, 0);
						break;
					case HeaderPosition::Top:
						ntl::Identity<float>(r);
						ntl::Translate<float>(t1, getWidth() - scroller->Widthf, 0, 0);
						break;
					case HeaderPosition::Right:
						ntl::RotateZ<float>(r, ntl::HalfPi<float>);
						ntl::Translate<float>(t1, getWidth(), getHeight() - scroller->Widthf, 0);
						break;
					case HeaderPosition::Bottom:
						ntl::Identity<float>(r);
						ntl::Translate<float>(t1, getWidth() - scroller->Widthf, getHeight() - scroller->Widthf, 0);
						break;
					}
					{
						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer
							->ActivateTarget(m_pCanvas)
							->ActivatePrimitiveMatrix(t1 * r)
							->DrawImage(scroller, 1);
					}

					scroller->Release();
				}
			}
		}

		void CPageControl::RenderMask(IRenderer *renderer)
		{
			if (PrepareCanvas(renderer, &m_pMask, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pMask)
					->Clear(Color{ 0, 0, 0, 0 })
					->DrawRectangle(getClientRect(), Color{ 0, 0, 0, 255 });
				m_pMask->setValid(true);
			}
		}
	#pragma endregion
	}
}