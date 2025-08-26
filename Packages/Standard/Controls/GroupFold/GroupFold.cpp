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
		CGroupFold::CGradientListener::CGradientListener(CGroupFold *control) :
			m_pControl{ control }
		{

		}

		void CGroupFold::CGradientListener::NotifyOnChange()
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
		CGroupFold::CGroupFold():
			CControl(L"GroupFold", true, true, true, false, false, false),
			m_cGradientListener{ this },
			m_bFolded{ false },
			m_aShadowRadius{
				1,
				1,
				1,
				1,
				1,
				1 },
			m_aShadowColor{
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
				PointF{ 0, 0 } },
			m_aBorderWidth{
				RectF{ 0, 1, 0, 0 },
				RectF{ 0, 1, 0, 0 },
				RectF{ 0, 1, 0, 0 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aBorderColor{
				BorderColor{ Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 } },
				BorderColor{ Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 } },
				BorderColor{ Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 } },
				BorderColor{ Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 } },
				BorderColor{ Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 } },
				BorderColor{ Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 } } },
			m_aBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 } },
			m_aBackgroundGradient{
				&m_cGradientListener,
				&m_cGradientListener,
				&m_cGradientListener,
				&m_cGradientListener,
				&m_cGradientListener,
				&m_cGradientListener },
			m_eCaptionAlign{ TextAlign::Center },
			m_bCaptionPlusLeft{ true },
			m_aCaptionColor{
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 133, 135, 139, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 133, 135, 139, 255 } },
			m_aCaptionMargin{
				3,
				3,
				3,
				2,
				2,
				2 },
			m_aCaptionPadding{
				PointF{ 2, 1 },
				PointF{ 2, 1 },
				PointF{ 2, 1 },
				PointF{ 2, 1 },
				PointF{ 2, 1 },
				PointF{ 2, 1 } },
			m_aCaptionBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aCaptionBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aCaptionBorderColor{
				BorderColor{ Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 } },
				BorderColor{ Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 } },
				BorderColor{ Color{ 133, 135, 139, 255 }, Color{ 133, 135, 139, 255 }, Color{ 133, 135, 139, 255 }, Color{ 133, 135, 139, 255 } },
				BorderColor{ Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 } },
				BorderColor{ Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 } },
				BorderColor{ Color{ 133, 135, 139, 255 }, Color{ 133, 135, 139, 255 }, Color{ 133, 135, 139, 255 }, Color{ 133, 135, 139, 255 } } },
			m_aCaptionBackgroundColor{
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 } },
			m_aCaptionBackgroundGradient{
				&m_cGradientListener,
				&m_cGradientListener,
				&m_cGradientListener,
				&m_cGradientListener,
				&m_cGradientListener,
				&m_cGradientListener },
			m_aPlusSize{
				1,
				1,
				1,
				1,
				1,
				1 },
			m_aPlusPadding{
				4,
				4,
				4,
				4,
				4,
				4 },
			m_aPadding{
				RectF{ 4, 4, 4, 4 },
				RectF{ 4, 4, 4, 4 },
				RectF{ 4, 4, 4, 4 },
				RectF{ 4, 4, 4, 4 },
				RectF{ 4, 4, 4, 4 },
				RectF{ 4, 4, 4, 4 } },
			m_bUseMask{ true },
			m_bIgnoreGradient{ false },
			m_bCaptionChanged{ false },
			m_pCanvas{ nullptr },
			m_pMask{ nullptr },
			m_fUnfoldedHeight{ 0 },
			m_bHovered{ false },
			OnToggle{ nullptr }
		{
			setService(new CGroupFoldService(this), true);
			setSize(PointF{ 185, 105 });
		}

		CGroupFold::CGroupFold(IControl *parent) :
			CGroupFold()
		{
			setParent(parent);
		}

		CGroupFold::CGroupFold(IForm *parent) :
			CGroupFold()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region IControl getters
		IControl *CGroupFold::getControl(const int index)
		{
			return CControl::getControl(index);
		}

		IControl *CGroupFold::getControl(const String &name)
		{
			return CControl::getControl(name);
		}

		IControl *CGroupFold::getControl(const PointF &position)
		{
			IControl *result{ CControl::getControl(position) };
			if (m_bUseMask && result && result != this)
			{
				Vec4f v{ ntl::Inversed<float>(getTransformMatrix()) * Vec4f { position.X, position.Y, 0, 1 } };
				if (getClientRect().is_outside(PointF{ v.X, v.Y }))
					result = this;
			}
			return result;
		}

		RectF CGroupFold::getClientRect()
		{
			if (m_bFolded)
				return RectF{ 0, 0, 0, 0 };
			int state{ (int)getState() };
			RectF caption{ CalculateCaptionRect() };
			RectF result{
				m_aBorderWidth[state].Left + m_aPadding[state].Left,
				(caption.is_zero() ? m_aBorderWidth[state].Top : caption.Bottom) + m_aPadding[state].Top,
				getWidth() - m_aBorderWidth[state].Right - m_aPadding[state].Right,
				getHeight() - m_aBorderWidth[state].Bottom - m_aPadding[state].Bottom
			};
			result.validate();
			return result;
		}

		RectF CGroupFold::getRenderRect()
		{
			RectF result{ AddShadow(getRect(), m_aShadowColor[0], m_aShadowShift[0], m_aShadowRadius[0]) };
			for (int i = 1; i <= (int)State::Disabled; i++)
				result += AddShadow(getRect(), m_aShadowColor[i], m_aShadowShift[i], m_aShadowRadius[i]);
			return result;
		}

		CursorType CGroupFold::getCursor()
		{
			if (m_bHovered)
				return CursorType::Hand;
			return CControl::getCursor();
		}
	#pragma endregion

	#pragma region IControl setters
		bool CGroupFold::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
					m_aShadowShift[i] *= s;
					m_aBorderWidth[i] *= s;
					m_aBorderRadius[i] *= avg;
					m_aCaptionMargin[i] *= s.X;
					m_aCaptionPadding[i] *= s;
					m_aCaptionBorderWidth[i] *= s;
					m_aCaptionBorderRadius[i] *= avg;
					m_aPadding[i] *= s;
				}
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
	#pragma endregion

	#pragma region IControl methods
		void CGroupFold::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			if (m_pMask)
				m_pMask->setValid(false);
			CControl::Refresh(refresh_children);
		}
	#pragma endregion

	#pragma region IGroupFold getters
		bool CGroupFold::isFolded()
		{
			return m_bFolded;
		}

		String CGroupFold::getCaption()
		{
			return m_sCaption;
		}
	#pragma endregion

	#pragma region IGroupFold setters
		bool CGroupFold::setFolded(const bool value)
		{
			if (value != m_bFolded)
			{
				CLockRepaint lock{ this };
				m_bFolded = value;
				if (m_bFolded)
				{
					RectF caption{ CalculateCaptionRect() };
					int state{ (int)getState() };
					if (caption.is_zero())
						setHeight(m_aBorderWidth[state].Top + m_aBorderWidth[state].Bottom);
					else
						setHeight(caption.height() + m_aBorderWidth[state].Bottom);
					if (getForm())
					{
						IForm *form{ getForm() };
						IControl *control;
						if ((control = form->getFocusedControl()) && control->hasParent(this))
							form->setFocusedControl(nullptr);
						if ((control = form->getActiveControl()) && control->hasParent(this))
							form->setActiveControl(nullptr);
					}
				}
				else
					setHeight(m_fUnfoldedHeight);
				return true;
			}
			return false;
		}

		bool CGroupFold::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_bCaptionChanged = true;
				m_sCaption = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IGroupFold methods
		void CGroupFold::Toggle()
		{
			setFolded(!m_bFolded);
		}
	#pragma endregion

	#pragma region Layout getters
		int CGroupFold::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		Color CGroupFold::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		PointF CGroupFold::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		RectF CGroupFold::getBorderWidth(const State state) const
		{
			return m_aBorderWidth[(int)state];
		}

		RectF CGroupFold::getBorderRadius(const State state) const
		{
			return m_aBorderRadius[(int)state];
		}

		BorderColor CGroupFold::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CGroupFold::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CGroupFold::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		TextAlign CGroupFold::getCaptionAlign() const
		{
			return m_eCaptionAlign;
		}

		bool CGroupFold::isCaptionPlusLeft() const
		{
			return m_bCaptionPlusLeft;
		}

		Color CGroupFold::getCaptionColor(const State state) const
		{
			return m_aCaptionColor[(int)state];
		}

		float CGroupFold::getCaptionMargin(const State state) const
		{
			return m_aCaptionMargin[(int)state];
		}

		PointF CGroupFold::getCaptionPadding(const State state) const
		{
			return m_aCaptionPadding[(int)state];
		}

		RectF CGroupFold::getCaptionBorderWidth(const State state) const
		{
			return m_aCaptionBorderWidth[(int)state];
		}

		RectF CGroupFold::getCaptionBorderRadius(const State state) const
		{
			return m_aCaptionBorderRadius[(int)state];
		}

		BorderColor CGroupFold::getCaptionBorderColor(const State state) const
		{
			return m_aCaptionBorderColor[(int)state];
		}

		Color CGroupFold::getCaptionBackgroundColor(const State state) const
		{
			return m_aCaptionBackgroundColor[(int)state];
		}

		Gradient *CGroupFold::getCaptionBackgroundGradient(const State state)
		{
			return &m_aCaptionBackgroundGradient[(int)state];
		}

		float CGroupFold::getPlusSize(const State state) const
		{
			return m_aPlusSize[(int)state];
		}

		float CGroupFold::getPlusPadding(const State state) const
		{
			return m_aPlusPadding[(int)state];
		}

		RectF CGroupFold::getPadding(const State state) const
		{
			return m_aPadding[(int)state];
		}

		bool CGroupFold::isUseMask() const
		{
			return m_bUseMask;
		}
	#pragma endregion

	#pragma region Layout setters
		bool CGroupFold::setShadowRadius(const State state, const int value)
		{
			if (value > 0 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				State current{ getState() };
				if (state == current && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowRadius[(int)state] = value;
				if (state == current && m_aShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGroupFold::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
				m_aShadowColor[(int)state] = value;
				if (state == getState() && m_aShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGroupFold::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				State current{ getState() };
				if (state == current && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowShift[(int)state] = value;
				if (state == current && m_aShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGroupFold::setBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBorderWidth[(int)state]))
			{
				m_aBorderWidth[(int)state] = value;
				if (state == getState())
				{
					QueryService()->AlignControls();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					if (m_pMask)
						m_pMask->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGroupFold::setBorderRadius(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBorderRadius[(int)state]))
			{
				m_aBorderRadius[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					if (m_pMask)
						m_pMask->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGroupFold::setBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
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

		bool CGroupFold::setBackgroundColor(const State state, const Color &value)
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

		bool CGroupFold::setCaptionAlign(const TextAlign value)
		{
			if (value != m_eCaptionAlign)
			{
				m_eCaptionAlign = value;
				if (!m_sCaption.empty())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGroupFold::setCaptionPlusLeft(const bool value)
		{
			if (value != m_bCaptionPlusLeft)
			{
				m_bCaptionPlusLeft = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CGroupFold::setCaptionColor(const State state, const Color &value)
		{
			if (value != m_aCaptionColor[(int)state])
			{
				m_aCaptionColor[(int)state] = value;
				if (!m_sCaption.empty() && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGroupFold::setCaptionMargin(const State state, const float value)
		{
			if (ntl::IsPositive<float>(value) && ntl::IsNotEqual<float>(value, m_aCaptionMargin[(int)state]))
			{
				m_aCaptionMargin[(int)state] = value;
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

		bool CGroupFold::setCaptionPadding(const State state, const PointF &value)
		{
			if (ntl::IsPositive<float>(value.X) && ntl::IsPositive<float>(value.Y) && IsNotEqual(value, m_aCaptionPadding[(int)state]))
			{
				m_aCaptionPadding[(int)state] = value;
				if (state == getState())
				{
					QueryService()->AlignControls();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					if (m_pMask)
						m_pMask->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGroupFold::setCaptionBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aCaptionBorderWidth[(int)state]))
			{
				m_aCaptionBorderWidth[(int)state] = value;
				if (state == getState())
				{
					QueryService()->AlignControls();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					if (m_pMask)
						m_pMask->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGroupFold::setCaptionBorderRadius(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aCaptionBorderRadius[(int)state]))
			{
				m_aCaptionBorderRadius[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					if (m_pMask)
						m_pMask->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGroupFold::setCaptionBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aCaptionBorderColor[(int)state])
			{
				m_aCaptionBorderColor[(int)state] = value;
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

		bool CGroupFold::setCaptionBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aCaptionBackgroundColor[(int)state])
			{
				m_aCaptionBackgroundColor[(int)state] = value;
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

		bool CGroupFold::setPlusSize(const State state, const float value)
		{
			if (ntl::IsPositive<float>(value) && ntl::IsNotEqual<float>(value, m_aPlusSize[(int)state]))
			{
				m_aPlusSize[(int)state] = value;
				if (state == getState() && m_aCaptionColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGroupFold::setPlusPadding(const State state, const float value)
		{
			if (ntl::IsPositive<float>(value) && ntl::IsNotEqual<float>(value, m_aPlusPadding[(int)state]))
			{
				m_aPlusPadding[(int)state] = value;
				if (state == getState() && m_aCaptionColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGroupFold::setPadding(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aPadding[(int)state]))
			{
				m_aPadding[(int)state] = value;
				QueryService()->AlignControls();
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					if (m_pMask)
						m_pMask->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGroupFold::setUseMask(const bool value)
		{
			if (value != m_bUseMask)
			{
				m_bUseMask = value;
				Repaint(true);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CGroupFold::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String state;
				switch ((State)i)
				{
				case State::FoldedNormal:
					state = L"FoldedNormal";
					break;
				case State::FoldedHovered:
					state = L"FoldedHovered";
					break;
				case State::FoldedDisabled:
					state = L"FoldedDisabled";
					break;
				case State::Normal:
					state = L"Normal";
					break;
				case State::Hovered:
					state = L"Hovered";
					break;
				default:
					state = L"Disabled";
				}
				style->getOption(m_sClassName + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
				style->getOption(m_sClassName + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L".BorderWidth[" + state + L"]", m_aBorderWidth[i]);
				style->getOption(m_sClassName + L".BorderRadius[" + state + L"]", m_aBorderRadius[i]);
				style->getOption(m_sClassName + L".BorderColor[" + state + L"]", m_aBorderColor[i]);
				style->getOption(m_sClassName + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]);
				style->getOption(m_sClassName + L".CaptionColor[" + state + L"]", m_aCaptionColor[i]);
				style->getOption(m_sClassName + L".CaptionMargin[" + state + L"]", m_aCaptionMargin[i]);
				style->getOption(m_sClassName + L".CaptionPadding[" + state + L"]", m_aCaptionPadding[i]);
				style->getOption(m_sClassName + L".CaptionBorderWidth[" + state + L"]", m_aCaptionBorderWidth[i]);
				style->getOption(m_sClassName + L".CaptionBorderRadius[" + state + L"]", m_aCaptionBorderRadius[i]);
				style->getOption(m_sClassName + L".CaptionBorderColor[" + state + L"]", m_aCaptionBorderColor[i]);
				style->getOption(m_sClassName + L".CaptionBackgroundColor[" + state + L"]", m_aCaptionBackgroundColor[i]);
				style->getOption(m_sClassName + L".CaptionBackgroundGradient[" + state + L"]", m_aCaptionBackgroundGradient[i]);
				style->getOption(m_sClassName + L".Padding[" + state + L"]", m_aPadding[i]);
			}
			m_bIgnoreGradient = false;
			QueryService()->AlignControls();
		}

		CGroupFold::State CGroupFold::getState()
		{
			if (m_bFolded)
			{
				if (!isEnabled(false))
					return State::FoldedDisabled;
				if (m_bHovered)
					return State::FoldedHovered;
				return State::FoldedNormal;
			}
			if (!isEnabled(false))
				return State::Disabled;
			if (m_bHovered)
				return State::Hovered;
			return State::Normal;
		}

		RectF CGroupFold::CalculateCaptionRect()
		{
			if (!getForm())
				return RectF{ 0, 0, 0, 0 };
			IRenderer *renderer{ getForm()->getRenderer() };
			if (!renderer)
				return RectF{ 0, 0, 0, 0 };
			IFont *f{ getFont() };
			if (!f)
				return RectF{ 0, 0, 0, 0 };
			IPlatformFont *pf{ f->getPlatformFont(renderer) };
			if (!pf)
				return RectF{ 0, 0, 0, 0 };
			PointF size{ pf->getStringSize(L"Wy", f->Distance) };
			int state{ (int)getState() };
			RectF result{
				m_aBorderWidth[state].Left + m_aCaptionMargin[state],
				0,
				getWidth() - m_aBorderWidth[state].Right - m_aCaptionMargin[state],
				m_aCaptionBorderWidth[state].Top + m_aCaptionPadding[state].Y * 2 + size.Y + m_aCaptionBorderWidth[state].Bottom
			};
			if (result.width() > getWidth() || result.height() > getHeight() + m_aBorderWidth[state].Bottom)
				return RectF{ 0, 0, 0, 0 };
			result.validate();
			return result;
		}

		bool CGroupFold::UpdateHovered(const PointF &position)
		{
			RectF caption{ CalculateCaptionRect() };
			bool hovered{ caption.is_inside(position) };
			if (hovered != m_bHovered)
			{
				m_bHovered = hovered;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Render
		void CGroupFold::Render(IRenderer *renderer, const Mat4f &matrix)
		{
			int state{ (int)getState() };
			PointF disp{ DispOnCanvas(m_aShadowColor[state], m_aShadowShift[state], m_aShadowRadius[state]) };
			RectF all_rect{ AddShadow(getRect(), m_aShadowColor[state], m_aShadowShift[state], m_aShadowRadius[state]) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				RectF rect{ getRect() }, caption{ CalculateCaptionRect() };
				if (!caption.is_zero())
				{
					rect.Top = std::round(caption.Bottom * 0.5f);
					caption += disp;
				}
				rect += disp;

				if (m_aShadowColor[state].A > 0)
				{
					if (caption.is_zero())
					{
						renderer
							->DrawBlock(
								rect + m_aShadowShift[state],
								RectF{ 0, 0, 0, 0 },
								m_aBorderRadius[state],
								BlockColors{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, m_aShadowColor[state], Color{ 0, 0, 0, 0 } })
							->BlurImage(m_pCanvas, m_aShadowRadius[state], BlurType::Gaussian);
					}
					else
					{
						renderer
							->DrawBlock(
								rect + m_aShadowShift[state],
								RectF{ 0, 0, 0, 0 },
								m_aBorderRadius[state],
								BlockColors{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, m_aShadowColor[state], Color{ 0, 0, 0, 0 } })
							->DrawBlock(
								caption + m_aShadowShift[state],
								RectF{ 0, 0, 0, 0 },
								m_aCaptionBorderRadius[state],
								BlockColors{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, m_aShadowColor[state], Color{ 0, 0, 0, 0 } })
							->BlurImage(m_pCanvas, m_aShadowRadius[state], BlurType::Gaussian);
					}
				}
				if (caption.is_zero())
				{
					DrawSimpleBackground(
						renderer,
						rect,
						m_aBorderWidth[state],
						m_aBorderRadius[state],
						m_aBorderColor[state],
						m_aBackgroundColor[state],
						m_aBackgroundGradient[state]);
				}
				else
				{
					// Background
					DrawSimpleBackground(
						renderer,
						rect,
						m_aBorderWidth[state],
						m_aBorderRadius[state],
						m_aBorderColor[state],
						m_aBackgroundColor[state],
						m_aBackgroundGradient[state]);
					DrawSimpleBackground(
						renderer,
						caption,
						m_aCaptionBorderWidth[state],
						m_aCaptionBorderRadius[state],
						m_aCaptionBorderColor[state],
						m_aCaptionBackgroundColor[state],
						m_aCaptionBackgroundGradient[state]);
					if (m_aCaptionColor[state].A > 0)
					{
						PointF p;
						p.Y = caption.Top + m_aCaptionBorderWidth[state].Top + m_aCaptionPadding[state].Y;
						// Caption
						if (!m_sCaption.empty())
						{
							IFont *font{ getFont() };
							if (font)
							{
								IPlatformFont *pf{ font->getPlatformFont(renderer) };
								if (pf)
								{
									PointF size{ pf->getStringSize(m_sCaption, font->Distance) };
									switch (m_eCaptionAlign)
									{
									case TextAlign::Center:
										p.X = (caption.Left + m_aCaptionBorderWidth[state].Left + caption.Right - m_aCaptionBorderWidth[state].Right - size.X) * 0.5f;
										break;
									case TextAlign::Right:
										p.X = caption.Right - m_aCaptionBorderWidth[state].Right - m_aCaptionPadding[state].X - size.X;
										break;
									default:
										p.X = caption.Left + m_aCaptionBorderWidth[state].Left + m_aCaptionPadding[state].X;
										break;
									}
									CStorePrimitiveMatrix s_matrix{ renderer };
									renderer
										->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(p.X, p.Y, 0))
										->DrawText(m_sCaption, pf, font->Distance, m_aCaptionColor[state]);
								}
							}
						}
						// Plus
						float w{ caption.height() - m_aCaptionBorderWidth[state].Top - m_aCaptionBorderWidth[state].Bottom - m_aCaptionPadding[state].Y * 2 - m_aPlusPadding[state] * 2 };
						if (w >= 3)
						{
							switch (m_eCaptionAlign)
							{
							case TextAlign::Center:
								if (m_bCaptionPlusLeft)
									p.X = caption.Left + m_aCaptionBorderWidth[state].Left + m_aCaptionPadding[state].X;
								else
									p.X = caption.Right - m_aCaptionBorderWidth[state].Right - m_aCaptionPadding[state].X - w;
								break;
							case TextAlign::Right:
								p.X = caption.Right - m_aCaptionBorderWidth[state].Right - m_aCaptionPadding[state].X - w;
								break;
							default:
								p.X = caption.Left + m_aCaptionBorderWidth[state].Left + m_aCaptionPadding[state].X;
								break;
							}
							p.Y += m_aPlusPadding[state];
							p.X += m_aPlusPadding[state];
							renderer->DrawRectangle(RectF{ p.X, std::round(p.Y + (w - m_aPlusSize[state]) * 0.5f), p.X + w, std::round(p.Y + (w + m_aPlusSize[state]) * 0.5f) }, m_aCaptionColor[state]);
							if (m_bFolded)
								renderer->DrawRectangle(RectF{ std::round(p.X + (w - m_aPlusSize[state]) * 0.5f), p.Y, std::round(p.X + (w + m_aPlusSize[state]) * 0.5f), p.Y + w }, m_aCaptionColor[state]);
						}
					}
				}

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, matrix, m_pCanvas, disp);
		}

		void CGroupFold::RenderMask(IRenderer *renderer)
		{
			if (PrepareCanvas(renderer, &m_pMask, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pMask)
					->Clear(Color{ 0, 0, 0, 0 });

				int state{ (int)getState() };
				Block b{
					getRect(),
					RectF{
						m_aBorderWidth[state].Left + m_aPadding[state].Left,
						m_aBorderWidth[state].Top + m_aPadding[state].Top,
						m_aBorderWidth[state].Right + m_aPadding[state].Right,
						m_aBorderWidth[state].Bottom + m_aPadding[state].Bottom
					},
					m_aBorderRadius[state],
					PointLocation::Inside
				};
				RectF caption{ CalculateCaptionRect() };
				if (!caption.is_zero())
					b.Rect.Top = std::round(caption.Bottom * 0.5f);
				if (m_aBorderRadius[state].has_positive())
				{
					CStoreBlock s_block{ renderer };
					renderer
						->ActivateBlock(&b)
						->DrawRectangle(b.Rect, Color{ 0, 0, 0, 255 });
				}
				else
					renderer->DrawRectangle(RectF{ b.Border.Left, b.Border.Top, b.Rect.Right - b.Border.Right, b.Rect.Bottom - b.Border.Bottom }, Color{ 0, 0, 0, 255 });
				m_pMask->setValid(true);
			}
		}
	#pragma endregion
	}
}