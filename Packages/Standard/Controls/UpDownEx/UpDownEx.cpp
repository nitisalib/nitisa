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
		CUpDownEx::CGradientListener::CGradientListener(CUpDownEx *control) :
			m_pControl{ control }
		{

		}

		void CUpDownEx::CGradientListener::NotifyOnChange()
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
		CUpDownEx::CUpDownEx():
			CControl(L"UpDownEx", true, true, false, false, false, false),
			m_cGradientListener{ this },
			m_fMin{ 0 },
			m_fMax{ 100 },
			m_fValue{ 0 },
			m_fStep{ 1 },
			m_pAssignedTo{ nullptr },
			m_iSigns{ 4 },
			m_fTimerInterval{ ScrollInterval },
			m_aDistance{ 1, 1, 1, 1 },
			m_aUpArrowOuterBorderWidth{
				RectF{ 1, 1, 1, 0 },
				RectF{ 1, 1, 1, 0 },
				RectF{ 1, 1, 1, 0 },
				RectF{ 1, 1, 1, 0 } },
			m_aUpArrowOuterBorderColor{
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } } },
			m_aUpArrowMiddleBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aUpArrowMiddleBorderColor{
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
				BorderColor{ Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 191, 191, 191, 255 }, Color{ 191, 191, 191, 255 }, Color{ 191, 191, 191, 255 }, Color{ 191, 191, 191, 255 } } },
			m_aUpArrowInnerBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aUpArrowInnerBorderColor{
				BorderColor{ Color{ 251, 251, 251, 255 }, Color{ 251, 251, 251, 255 }, Color{ 251, 251, 251, 255 }, Color{ 251, 251, 251, 255 } },
				BorderColor{ Color{ 248, 252, 254, 255 }, Color{ 248, 252, 254, 255 }, Color{ 248, 252, 254, 255 }, Color{ 248, 252, 254, 255 } },
				BorderColor{ Color{ 110, 141, 159, 255 }, Color{ 110, 141, 159, 255 }, Color{ 110, 141, 159, 255 }, Color{ 110, 141, 159, 255 } },
				BorderColor{ Color{ 238, 238, 238, 255 }, Color{ 238, 238, 238, 255 }, Color{ 238, 238, 238, 255 }, Color{ 238, 238, 238, 255 } } },
			m_aUpArrowBackgroundColor{
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 238, 238, 238, 255 } },
			m_aUpArrowBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aUpArrowPadding{
				RectF{ 2, 1, 2, 1 },
				RectF{ 2, 1, 2, 1 },
				RectF{ 2, 1, 2, 1 },
				RectF{ 2, 1, 2, 1 } },
			m_aUpArrowArrowColor{
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 77, 86, 120, 255 },
				Color{ 159, 160, 165, 255 } },
			m_aDownArrowOuterBorderWidth{
				RectF{ 1, 0, 1, 1 },
				RectF{ 1, 0, 1, 1 },
				RectF{ 1, 0, 1, 1 },
				RectF{ 1, 0, 1, 1 } },
			m_aDownArrowOuterBorderColor{
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } } },
			m_aDownArrowMiddleBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aDownArrowMiddleBorderColor{
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
				BorderColor{ Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 191, 191, 191, 255 }, Color{ 191, 191, 191, 255 }, Color{ 191, 191, 191, 255 }, Color{ 191, 191, 191, 255 } } },
			m_aDownArrowInnerBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aDownArrowInnerBorderColor{
				BorderColor{ Color{ 251, 251, 251, 255 }, Color{ 251, 251, 251, 255 }, Color{ 251, 251, 251, 255 }, Color{ 251, 251, 251, 255 } },
				BorderColor{ Color{ 248, 252, 254, 255 }, Color{ 248, 252, 254, 255 }, Color{ 248, 252, 254, 255 }, Color{ 248, 252, 254, 255 } },
				BorderColor{ Color{ 110, 141, 159, 255 }, Color{ 110, 141, 159, 255 }, Color{ 110, 141, 159, 255 }, Color{ 110, 141, 159, 255 } },
				BorderColor{ Color{ 238, 238, 238, 255 }, Color{ 238, 238, 238, 255 }, Color{ 238, 238, 238, 255 }, Color{ 238, 238, 238, 255 } } },
			m_aDownArrowBackgroundColor{
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 238, 238, 238, 255 } },
			m_aDownArrowBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aDownArrowPadding{
				RectF{ 2, 1, 2, 1 },
				RectF{ 2, 1, 2, 1 },
				RectF{ 2, 1, 2, 1 },
				RectF{ 2, 1, 2, 1 } },
			m_aDownArrowArrowColor{
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 77, 86, 120, 255 },
				Color{ 159, 160, 165, 255 } },
			m_bChangeByDrag{ false },
			m_fDragShift{ 0 },
			m_fDragScale{ 0.01f },
			m_fDragBase{ 1.5f },
			m_fDragBaseShift{ 0 },
			m_fDragBaseScale{ 0.25f },
			m_pCanvas{ nullptr },
			m_hTimer{ nullptr },
			m_bIgnoreGradient{ true },
			m_eHoveredElement{ Element::None },
			m_eDownElement{ Element::None }
		{
			OnChange = nullptr;

			setService(new CUpDownExService(this), true);
			setSize(PointF{ 18, 25 });
			
			m_aUpArrowBackgroundGradient[(int)State::Normal].setPointCount(3);
			m_aUpArrowBackgroundGradient[(int)State::Normal].setPoint(0, Color1D{ 0.0f, Color{ 242, 242, 242, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Normal].setPoint(1, Color1D{ 0.7f, Color{ 232, 232, 232, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Normal].setPoint(2, Color1D{ 1.0f, Color{ 209, 209, 209, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Hovered].setPointCount(3);
			m_aUpArrowBackgroundGradient[(int)State::Hovered].setPoint(0, Color1D{ 0.0f, Color{ 233, 236, 253, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Hovered].setPoint(1, Color1D{ 0.7f, Color{ 210, 237, 252, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Hovered].setPoint(2, Color1D{ 1.0f, Color{ 169, 219, 245, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Active].setPointCount(4);
			m_aUpArrowBackgroundGradient[(int)State::Active].setPoint(0, Color1D{ 0.0f, Color{ 166, 199, 217, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Active].setPoint(1, Color1D{ 0.3f, Color{ 194, 228, 246, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Active].setPoint(2, Color1D{ 0.7f, Color{ 194, 228, 246, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Active].setPoint(3, Color1D{ 1.0f, Color{ 145, 204, 235, 255 } });

			m_aDownArrowBackgroundGradient[(int)State::Normal].setPointCount(3);
			m_aDownArrowBackgroundGradient[(int)State::Normal].setPoint(0, Color1D{ 0.0f, Color{ 242, 242, 242, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Normal].setPoint(1, Color1D{ 0.7f, Color{ 232, 232, 232, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Normal].setPoint(2, Color1D{ 1.0f, Color{ 209, 209, 209, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Hovered].setPointCount(3);
			m_aDownArrowBackgroundGradient[(int)State::Hovered].setPoint(0, Color1D{ 0.0f, Color{ 233, 236, 253, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Hovered].setPoint(1, Color1D{ 0.7f, Color{ 210, 237, 252, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Hovered].setPoint(2, Color1D{ 1.0f, Color{ 169, 219, 245, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Active].setPointCount(4);
			m_aDownArrowBackgroundGradient[(int)State::Active].setPoint(0, Color1D{ 0.0f, Color{ 166, 199, 217, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Active].setPoint(1, Color1D{ 0.3f, Color{ 194, 228, 246, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Active].setPoint(2, Color1D{ 0.7f, Color{ 194, 228, 246, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Active].setPoint(3, Color1D{ 1.0f, Color{ 145, 204, 235, 255 } });

			m_bIgnoreGradient = false;
		}

		CUpDownEx::CUpDownEx(IForm *parent) : CUpDownEx()
		{
			setForm(parent);
		}

		CUpDownEx::CUpDownEx(IControl *parent) : CUpDownEx()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		float CUpDownEx::getMin()
		{
			return m_fMin;
		}

		float CUpDownEx::getMax()
		{
			return m_fMax;
		}

		float CUpDownEx::getValue()
		{
			float v;
			if (m_pAssignedTo && TryStringToFloat(m_pAssignedTo->getText(), v))
			{
				v = ntl::Clamp<float>(v, m_fMin, m_fMax);
				if (ntl::IsNotEqual<float>(v, m_fValue))
				{
					m_fValue = v;
					m_pAssignedTo->setText(getValueAsString());
				}
			}
			return m_fValue;
		}

		float CUpDownEx::getStep()
		{
			return m_fStep;
		}

		IEdit *CUpDownEx::getAssignedTo()
		{
			return m_pAssignedTo;
		}
	#pragma endregion

	#pragma region Getters
		CUpDownEx::State CUpDownEx::getState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (m_eDownElement != Element::None)
				return State::Active;
			if (isHovered())
				return State::Hovered;
			return State::Normal;
		}

		int CUpDownEx::getSigns()
		{
			return m_iSigns;
		}

		float CUpDownEx::getTimerInterval()
		{
			return m_fTimerInterval;
		}

		float CUpDownEx::getDistance(const State state)
		{
			return m_aDistance[(int)state];
		}

		RectF CUpDownEx::getUpArrowOuterBorderWidth(const State state)
		{
			return m_aUpArrowOuterBorderWidth[(int)state];
		}

		BorderColor CUpDownEx::getUpArrowOuterBorderColor(const State state)
		{
			return m_aUpArrowOuterBorderColor[(int)state];
		}

		RectF CUpDownEx::getUpArrowMiddleBorderWidth(const State state)
		{
			return m_aUpArrowMiddleBorderWidth[(int)state];
		}

		BorderColor CUpDownEx::getUpArrowMiddleBorderColor(const State state)
		{
			return m_aUpArrowMiddleBorderColor[(int)state];
		}

		RectF CUpDownEx::getUpArrowInnerBorderWidth(const State state)
		{
			return m_aUpArrowInnerBorderWidth[(int)state];
		}

		BorderColor CUpDownEx::getUpArrowInnerBorderColor(const State state)
		{
			return m_aUpArrowInnerBorderColor[(int)state];
		}

		Color CUpDownEx::getUpArrowBackgroundColor(const State state)
		{
			return m_aUpArrowBackgroundColor[(int)state];
		}

		Gradient *CUpDownEx::getUpArrowBackgroundGradient(const State state)
		{
			return &m_aUpArrowBackgroundGradient[(int)state];
		}

		RectF CUpDownEx::getUpArrowPadding(const State state)
		{
			return m_aUpArrowPadding[(int)state];
		}

		Color CUpDownEx::getUpArrowArrowColor(const State state)
		{
			return m_aUpArrowArrowColor[(int)state];
		}

		RectF CUpDownEx::getDownArrowOuterBorderWidth(const State state)
		{
			return m_aDownArrowOuterBorderWidth[(int)state];
		}

		BorderColor CUpDownEx::getDownArrowOuterBorderColor(const State state)
		{
			return m_aDownArrowOuterBorderColor[(int)state];
		}

		RectF CUpDownEx::getDownArrowMiddleBorderWidth(const State state)
		{
			return m_aDownArrowMiddleBorderWidth[(int)state];
		}

		BorderColor CUpDownEx::getDownArrowMiddleBorderColor(const State state)
		{
			return m_aDownArrowMiddleBorderColor[(int)state];
		}

		RectF CUpDownEx::getDownArrowInnerBorderWidth(const State state)
		{
			return m_aDownArrowInnerBorderWidth[(int)state];
		}

		BorderColor CUpDownEx::getDownArrowInnerBorderColor(const State state)
		{
			return m_aDownArrowInnerBorderColor[(int)state];
		}

		Color CUpDownEx::getDownArrowBackgroundColor(const State state)
		{
			return m_aDownArrowBackgroundColor[(int)state];
		}

		Gradient *CUpDownEx::getDownArrowBackgroundGradient(const State state)
		{
			return &m_aDownArrowBackgroundGradient[(int)state];
		}

		RectF CUpDownEx::getDownArrowPadding(const State state)
		{
			return m_aDownArrowPadding[(int)state];
		}

		Color CUpDownEx::getDownArrowArrowColor(const State state)
		{
			return m_aDownArrowArrowColor[(int)state];
		}

		bool CUpDownEx::isChangeByDrag() const
		{
			return m_bChangeByDrag;
		}

		float CUpDownEx::getDragShift() const
		{
			return m_fDragShift;
		}


		float CUpDownEx::getDragScale() const
		{
			return m_fDragScale;
		}

		float CUpDownEx::getDragBase() const
		{
			return m_fDragBase;
		}

		float CUpDownEx::getDragBaseShift() const
		{
			return m_fDragBaseShift;
		}

		float CUpDownEx::getDragBaseScale() const
		{
			return m_fDragBaseScale;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CUpDownEx::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aDistance[i] *= s.Y;
					m_aUpArrowOuterBorderWidth[i] *= s;
					m_aUpArrowMiddleBorderWidth[i] *= s;
					m_aUpArrowInnerBorderWidth[i] *= s;
					m_aUpArrowPadding[i] *= s;
					m_aDownArrowOuterBorderWidth[i] *= s;
					m_aDownArrowMiddleBorderWidth[i] *= s;
					m_aDownArrowInnerBorderWidth[i] *= s;
					m_aDownArrowPadding[i] *= s;
				}
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CUpDownEx::setAlign(const Align value)
		{
			return false;
		}

		bool CUpDownEx::setMin(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMin))
			{
				CLockRepaint lock{ this };
				m_fMin = value;
				if (ntl::IsLess<float>(m_fMax, m_fMin))
					m_fMax = m_fMin;
				if (ntl::IsLess<float>(m_fValue, m_fMin))
				{
					m_fValue = m_fMin;
					if (m_pAssignedTo)
						m_pAssignedTo->setText(getValueAsString());
				}
				return true;
			}
			return false;
		}

		bool CUpDownEx::setMax(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMax))
			{
				CLockRepaint lock{ this };
				m_fMax = value;
				if (ntl::IsGreater<float>(m_fMin, m_fMax))
					m_fMin = m_fMax;
				if (ntl::IsGreater<float>(m_fValue, m_fMax))
				{
					m_fValue = m_fMax;
					if (m_pAssignedTo)
						m_pAssignedTo->setText(getValueAsString());
				}
				return true;
			}
			return false;
		}

		bool CUpDownEx::setValue(const float value)
		{
			float v{ ntl::Clamp<float>(value, m_fMin, m_fMax) };
			if (ntl::IsNotEqual<float>(v, m_fValue))
			{
				m_fValue = v;
				if (m_pAssignedTo)
					m_pAssignedTo->setText(getValueAsString());
				return true;
			}
			return false;
		}

		bool CUpDownEx::setStep(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fStep))
			{
				m_fStep = value;
				return true;
			}
			return false;
		}

		bool CUpDownEx::setAssignedTo(IEdit *value)
		{
			if (value != m_pAssignedTo)
			{
				if (value && (value->getForm() != getForm() || value->getParent() != getParent())) // Can assign only to Edit which is on the same parent
					return false;
				if (m_pAssignedTo)
				{
					m_pSpliceService->Release();
					m_pSpliceService = nullptr;
				}
				m_pAssignedTo = value;
				if (m_pAssignedTo)
				{
					CLockRepaint lock{ this };
					ITransform *t{ m_pAssignedTo->getTransform() };
					getTransform()->Transform(t->getTx() + m_pAssignedTo->getWidth(), t->getTy(), t->getTz(), t->getSx(), t->getSy(), t->getSz(), t->getRx(), t->getRy(), t->getRz());
					setHeight(m_pAssignedTo->getHeight());
					m_pSpliceService = new CEditSpliceService(m_pAssignedTo, this);
					m_pAssignedTo->setText(getValueAsString());
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CUpDownEx::setSigns(const int value)
		{
			if (value >= 0 && value < 10 && value != m_iSigns)
			{
				m_iSigns = value;
				if (m_pAssignedTo)
					m_pAssignedTo->setText(getValueAsString());
				return true;
			}
			return false;
		}

		bool CUpDownEx::setTimerInterval(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fTimerInterval))
			{
				m_fTimerInterval = value;
				if (m_hTimer)
					getForm()->ResetTimer(m_hTimer, m_fTimerInterval);
				return true;
			}
			return false;
		}

		bool CUpDownEx::setDistance(const State state, const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_aDistance[(int)state]))
			{
				m_aDistance[(int)state] = value;
				if (getState() == state && getForm())
				{
					UpdateHoveredElement();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CUpDownEx::setUpArrowOuterBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aUpArrowOuterBorderWidth[(int)state]))
			{
				m_aUpArrowOuterBorderWidth[(int)state] = value;
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

		bool CUpDownEx::setUpArrowOuterBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aUpArrowOuterBorderColor[(int)state])
			{
				m_aUpArrowOuterBorderColor[(int)state] = value;
				if (getState() == state && m_aUpArrowOuterBorderWidth[(int)state].has_positive())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CUpDownEx::setUpArrowMiddleBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aUpArrowMiddleBorderWidth[(int)state]))
			{
				m_aUpArrowMiddleBorderWidth[(int)state] = value;
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

		bool CUpDownEx::setUpArrowMiddleBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aUpArrowMiddleBorderColor[(int)state])
			{
				m_aUpArrowMiddleBorderColor[(int)state] = value;
				if (getState() == state && m_aUpArrowMiddleBorderWidth[(int)state].has_positive())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CUpDownEx::setUpArrowInnerBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aUpArrowInnerBorderWidth[(int)state]))
			{
				m_aUpArrowInnerBorderWidth[(int)state] = value;
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

		bool CUpDownEx::setUpArrowInnerBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aUpArrowInnerBorderColor[(int)state])
			{
				m_aUpArrowInnerBorderColor[(int)state] = value;
				if (getState() == state && m_aUpArrowInnerBorderWidth[(int)state].has_positive())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CUpDownEx::setUpArrowBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aUpArrowBackgroundColor[(int)state])
			{
				m_aUpArrowBackgroundColor[(int)state] = value;
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

		bool CUpDownEx::setUpArrowPadding(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aUpArrowPadding[(int)state]))
			{
				m_aUpArrowPadding[(int)state] = value;
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

		bool CUpDownEx::setUpArrowArrowColor(const State state, const Color &value)
		{
			if (value != m_aUpArrowArrowColor[(int)state])
			{
				m_aUpArrowArrowColor[(int)state] = value;
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

		bool CUpDownEx::setDownArrowOuterBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aDownArrowOuterBorderWidth[(int)state]))
			{
				m_aDownArrowOuterBorderWidth[(int)state] = value;
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

		bool CUpDownEx::setDownArrowOuterBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aDownArrowOuterBorderColor[(int)state])
			{
				m_aDownArrowOuterBorderColor[(int)state] = value;
				if (getState() == state && m_aDownArrowOuterBorderWidth[(int)state].has_positive())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CUpDownEx::setDownArrowMiddleBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aDownArrowMiddleBorderWidth[(int)state]))
			{
				m_aDownArrowMiddleBorderWidth[(int)state] = value;
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

		bool CUpDownEx::setDownArrowMiddleBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aDownArrowMiddleBorderColor[(int)state])
			{
				m_aDownArrowMiddleBorderColor[(int)state] = value;
				if (getState() == state && m_aDownArrowMiddleBorderWidth[(int)state].has_positive())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CUpDownEx::setDownArrowInnerBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aDownArrowInnerBorderWidth[(int)state]))
			{
				m_aDownArrowInnerBorderWidth[(int)state] = value;
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

		bool CUpDownEx::setDownArrowInnerBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aDownArrowInnerBorderColor[(int)state])
			{
				m_aDownArrowInnerBorderColor[(int)state] = value;
				if (getState() == state && m_aDownArrowInnerBorderWidth[(int)state].has_positive())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CUpDownEx::setDownArrowBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aDownArrowBackgroundColor[(int)state])
			{
				m_aDownArrowBackgroundColor[(int)state] = value;
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

		bool CUpDownEx::setDownArrowPadding(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aDownArrowPadding[(int)state]))
			{
				m_aDownArrowPadding[(int)state] = value;
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

		bool CUpDownEx::setDownArrowArrowColor(const State state, const Color &value)
		{
			if (value != m_aDownArrowArrowColor[(int)state])
			{
				m_aDownArrowArrowColor[(int)state] = value;
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

		bool CUpDownEx::setChangeByDrag(const bool value)
		{
			if (value != m_bChangeByDrag)
			{
				m_bChangeByDrag = value;
				return true;
			}
			return false;
		}

		bool CUpDownEx::setDragShift(const float value, const float tolerance)
		{
			if (ntl::IsNotEqual<float>(value, m_fDragShift, tolerance))
			{
				m_fDragShift = value;
				return true;
			}
			return false;
		}

		bool CUpDownEx::setDragScale(const float value, const float tolerance)
		{
			if (ntl::IsPositive<float>(value, tolerance) && ntl::IsNotEqual<float>(value, m_fDragScale, tolerance))
			{
				m_fDragScale = value;
				return true;
			}
			return false;
		}

		bool CUpDownEx::setDragBase(const float value, const float tolerance)
		{
			if (ntl::IsPositive<float>(value, tolerance) && ntl::IsNotEqual<float>(value, m_fDragBase, tolerance))
			{
				m_fDragBase = value;
				return true;
			}
			return false;
		}

		bool CUpDownEx::setDragBaseShift(const float value, const float tolerance)
		{
			if (ntl::IsPositive<float>(value, tolerance) && ntl::IsNotEqual<float>(value, m_fDragBaseShift, tolerance))
			{
				m_fDragBaseShift = value;
				return true;
			}
			return false;
		}

		bool CUpDownEx::setDragBaseScale(const float value, const float tolerance)
		{
			if (ntl::IsPositive<float>(value, tolerance) && ntl::IsNotEqual<float>(value, m_fDragBaseScale, tolerance))
			{
				m_fDragBaseScale = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CUpDownEx::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		bool CUpDownEx::Up()
		{
			return setValue(getValue() + m_fStep);
		}

		bool CUpDownEx::Down()
		{
			return setValue(getValue() - m_fStep);
		}

		bool CUpDownEx::UpdateHoveredElement()
		{
			if (getForm())
				return UpdateHoveredElement(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())));
			if (m_eHoveredElement != Element::None)
			{
				m_eHoveredElement = Element::None;
				return true;
			}
			return false;
		}

		bool CUpDownEx::UpdateHoveredElement(const PointF &position)
		{
			State state{ getState() };
			Element el{ Element::None };
			RectF r{ getUpArrowRect(state) };
			if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
				el = Element::UpArrow;
			else
			{
				r = getDownArrowRect(state);
				if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
					el = Element::DownArrow;
			}
			if (el != m_eHoveredElement)
			{
				m_eHoveredElement = el;
				return true;
			}
			return false;
		}

		CUpDownEx::State CUpDownEx::getUpArrowState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (m_eDownElement == Element::UpArrow)
				return State::Active;
			if (m_eDownElement == Element::DownArrow)
				return State::Normal;
			if (m_eHoveredElement == Element::UpArrow)
				return State::Hovered;
			return State::Normal;
		}

		CUpDownEx::State CUpDownEx::getDownArrowState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (m_eDownElement == Element::DownArrow)
				return State::Active;
			if (m_eDownElement == Element::UpArrow)
				return State::Normal;
			if (m_eHoveredElement == Element::DownArrow)
				return State::Hovered;
			return State::Normal;
		}

		RectF CUpDownEx::getUpArrowRect(const State state)
		{
			return RectF{ 0, 0, getWidth(), (getHeight() - m_aDistance[(int)state]) / 2 };
		}

		RectF CUpDownEx::getDownArrowRect(const State state)
		{
			return RectF{ 0, getHeight() - (getHeight() - m_aDistance[(int)state]) / 2, getWidth(), getHeight() };
		}

		String CUpDownEx::getValueAsString()
		{
			static wchar_t buffer[64];
			swprintf(buffer, 64, (L"%." + ToString(m_iSigns) + L"f").c_str(), m_fValue);
			return buffer;
		}

		void CUpDownEx::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
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
				style->getOption(m_sClassName + L".Distance[" + state + L"]", m_aDistance[i]);
				style->getOption(m_sClassName + L".UpArrowOuterBorderWidth[" + state + L"]", m_aUpArrowOuterBorderWidth[i]);
				style->getOption(m_sClassName + L".UpArrowOuterBorderColor[" + state + L"]", m_aUpArrowOuterBorderColor[i]);
				style->getOption(m_sClassName + L".UpArrowMiddleBorderWidth[" + state + L"]", m_aUpArrowMiddleBorderWidth[i]);
				style->getOption(m_sClassName + L".UpArrowMiddleBorderColor[" + state + L"]", m_aUpArrowMiddleBorderColor[i]);
				style->getOption(m_sClassName + L".UpArrowInnerBorderWidth[" + state + L"]", m_aUpArrowInnerBorderWidth[i]);
				style->getOption(m_sClassName + L".UpArrowInnerBorderColor[" + state + L"]", m_aUpArrowInnerBorderColor[i]);
				style->getOption(m_sClassName + L".UpArrowBackgroundColor[" + state + L"]", m_aUpArrowBackgroundColor[i]);
				style->getOption(m_sClassName + L".UpArrowBackgroundGradient[" + state + L"]", m_aUpArrowBackgroundGradient[i]);
				style->getOption(m_sClassName + L".UpArrowPadding[" + state + L"]", m_aUpArrowPadding[i]);
				style->getOption(m_sClassName + L".UpArrowArrowColor[" + state + L"]", m_aUpArrowArrowColor[i]);
				style->getOption(m_sClassName + L".DownArrowOuterBorderWidth[" + state + L"]", m_aDownArrowOuterBorderWidth[i]);
				style->getOption(m_sClassName + L".DownArrowOuterBorderColor[" + state + L"]", m_aDownArrowOuterBorderColor[i]);
				style->getOption(m_sClassName + L".DownArrowMiddleBorderWidth[" + state + L"]", m_aDownArrowMiddleBorderWidth[i]);
				style->getOption(m_sClassName + L".DownArrowMiddleBorderColor[" + state + L"]", m_aDownArrowMiddleBorderColor[i]);
				style->getOption(m_sClassName + L".DownArrowInnerBorderWidth[" + state + L"]", m_aDownArrowInnerBorderWidth[i]);
				style->getOption(m_sClassName + L".DownArrowInnerBorderColor[" + state + L"]", m_aDownArrowInnerBorderColor[i]);
				style->getOption(m_sClassName + L".DownArrowBackgroundColor[" + state + L"]", m_aDownArrowBackgroundColor[i]);
				style->getOption(m_sClassName + L".DownArrowBackgroundGradient[" + state + L"]", m_aDownArrowBackgroundGradient[i]);
				style->getOption(m_sClassName + L".DownArrowPadding[" + state + L"]", m_aDownArrowPadding[i]);
				style->getOption(m_sClassName + L".DownArrowArrowColor[" + state + L"]", m_aDownArrowArrowColor[i]);
			}
			UpdateHoveredElement();
			m_bIgnoreGradient = false;
		}
	#pragma endregion

	#pragma region Paint
		void CUpDownEx::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			State state{ getState() };
			if (PrepareCanvas(renderer, &m_pCanvas, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });
					
				// Upper
				RectF r1{ getUpArrowRect(state) };
				if (r1.is_valid() && !r1.is_empty())
				{
					State st{ getUpArrowState() };
					DrawTripleBackground(
						renderer,
						r1,
						m_aUpArrowOuterBorderWidth[(int)state],
						m_aUpArrowMiddleBorderWidth[(int)state],
						m_aUpArrowInnerBorderWidth[(int)state],
						RectF{ 0, 0, 0, 0 },
						m_aUpArrowOuterBorderColor[(int)st],
						m_aUpArrowMiddleBorderColor[(int)st],
						m_aUpArrowInnerBorderColor[(int)st],
						m_aUpArrowBackgroundColor[(int)st],
						m_aUpArrowBackgroundGradient[(int)st]);
					RectF r{
						r1.Left + m_aUpArrowOuterBorderWidth[(int)state].Left + m_aUpArrowMiddleBorderWidth[(int)state].Left + m_aUpArrowInnerBorderWidth[(int)state].Left + m_aUpArrowPadding[(int)state].Left,
						r1.Top + m_aUpArrowOuterBorderWidth[(int)state].Top + m_aUpArrowMiddleBorderWidth[(int)state].Top + m_aUpArrowInnerBorderWidth[(int)state].Top + m_aUpArrowPadding[(int)state].Top,
						r1.Right - m_aUpArrowOuterBorderWidth[(int)state].Right - m_aUpArrowMiddleBorderWidth[(int)state].Right - m_aUpArrowInnerBorderWidth[(int)state].Right - m_aUpArrowPadding[(int)state].Right,
						r1.Bottom - m_aUpArrowOuterBorderWidth[(int)state].Bottom - m_aUpArrowMiddleBorderWidth[(int)state].Bottom - m_aUpArrowInnerBorderWidth[(int)state].Bottom - m_aUpArrowPadding[(int)state].Bottom
					};
					if (r.is_valid() && !r.is_empty() && m_aUpArrowArrowColor[(int)st].A > 0)
						renderer->DrawTriangle(PointF{ (r.Left + r.Right) / 2, r.Top }, PointF{ r.Right, r.Bottom }, PointF{ r.Left, r.Bottom }, m_aUpArrowArrowColor[(int)st]);
				}

				// Lower
				RectF r2{ getDownArrowRect(state) };
				if (r2.is_valid() && !r2.is_empty())
				{
					State st{ getDownArrowState() };
					DrawTripleBackground(
						renderer,
						r2,
						m_aDownArrowOuterBorderWidth[(int)state],
						m_aDownArrowMiddleBorderWidth[(int)state],
						m_aDownArrowInnerBorderWidth[(int)state],
						RectF{ 0, 0, 0, 0 },
						m_aDownArrowOuterBorderColor[(int)st],
						m_aDownArrowMiddleBorderColor[(int)st],
						m_aDownArrowInnerBorderColor[(int)st],
						m_aDownArrowBackgroundColor[(int)st],
						m_aDownArrowBackgroundGradient[(int)st]);
					RectF r{
						r2.Left + m_aDownArrowOuterBorderWidth[(int)state].Left + m_aDownArrowMiddleBorderWidth[(int)state].Left + m_aDownArrowInnerBorderWidth[(int)state].Left + m_aDownArrowPadding[(int)state].Left,
						r2.Top + m_aDownArrowOuterBorderWidth[(int)state].Top + m_aDownArrowMiddleBorderWidth[(int)state].Top + m_aDownArrowInnerBorderWidth[(int)state].Top + m_aDownArrowPadding[(int)state].Top,
						r2.Right - m_aDownArrowOuterBorderWidth[(int)state].Right - m_aDownArrowMiddleBorderWidth[(int)state].Right - m_aDownArrowInnerBorderWidth[(int)state].Right - m_aDownArrowPadding[(int)state].Right,
						r2.Bottom - m_aDownArrowOuterBorderWidth[(int)state].Bottom - m_aDownArrowMiddleBorderWidth[(int)state].Bottom - m_aDownArrowInnerBorderWidth[(int)state].Bottom - m_aDownArrowPadding[(int)state].Bottom
					};
					if (r.is_valid() && !r.is_empty() && m_aDownArrowArrowColor[(int)st].A > 0)
						renderer->DrawTriangle(PointF{ (r.Left + r.Right) / 2, r.Bottom }, PointF{ r.Left, r.Top }, PointF{ r.Right, r.Top }, m_aDownArrowArrowColor[(int)st]);
				}

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}
	#pragma endregion
	}
}