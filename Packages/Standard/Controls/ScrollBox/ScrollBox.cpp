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
		CScrollBox::CGradientListener::CGradientListener(CScrollBox *control) :
			m_pControl{ control }
		{

		}

		void CScrollBox::CGradientListener::NotifyOnChange()
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
		CScrollBox::CScrollBox() :
			CControl(L"ScrollBox", true, true, true, false, false, false),
			m_cGradientListener{ this },
			m_eVScroll{ ScrollVisibility::Auto },
			m_eHScroll{ ScrollVisibility::Auto },
			m_sBackgroundColor{ 240, 240, 240, 255 },
			m_sCornerColor{ 234, 234, 234, 255 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_sPadding{ 0, 0 },
			m_cScrollListener{ this },
			m_pCanvas{ nullptr },
			m_pMask{ nullptr },
			m_pVScroll{ nullptr },
			m_pHScroll{ nullptr },
			m_bIgnoreGradient{ false },
			m_bVScroll{ false },
			m_bHScroll{ false },
			m_eHoveredElement{ Element::None },
			m_eDownElement{ Element::None }
		{
			setService(new CScrollBoxService(this), true);
			setSize(PointF{ 185, 105 });
		}

		CScrollBox::CScrollBox(IControl *parent) :CScrollBox()
		{
			setParent(parent);
		}

		CScrollBox::CScrollBox(IForm *parent) : CScrollBox()
		{
			setForm(parent);
		}

		CScrollBox::~CScrollBox()
		{
			if (m_pHScroll)
				m_pHScroll->Release();
			if (m_pVScroll)
				m_pVScroll->Release();
		}
	#pragma endregion

	#pragma region Interface getters
		RectF CScrollBox::getClientRect()
		{
			RectF result{ 0, 0, getWidth(), getHeight() };
			if (m_bVScroll)
				result.Right -= getVScroll()->getWidth();
			if (m_bHScroll)
				result.Bottom -= getHScroll()->getHeight();
			result.validate();
			return result;
		}

		IControl *CScrollBox::getControl(const int index)
		{
			return CControl::getControl(index);
		}

		IControl *CScrollBox::getControl(const String &name)
		{
			return CControl::getControl(name);
		}

		IControl *CScrollBox::getControl(const PointF &position)
		{
			IControl *result{ CControl::getControl(position) };
			if (result && result != this)
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

		bool CScrollBox::isAcceptBubbledEvents()
		{
			return true;
		}

		ScrollVisibility CScrollBox::getVerticalScrollVisibility()
		{
			return m_eVScroll;
		}

		bool CScrollBox::isVerticalScrollEnabled()
		{
			return getVScroll()->isEnabled();
		}

		float CScrollBox::getVerticalScrollMax()
		{
			return getVScroll()->getMax();
		}

		float CScrollBox::getVerticalScrollPosition()
		{
			return getVScroll()->getScroll();
		}

		ScrollVisibility CScrollBox::getHorizontalScrollVisibility()
		{
			return m_eHScroll;
		}

		bool CScrollBox::isHorizontalScrollEnabled()
		{
			return getHScroll()->isEnabled();
		}

		float CScrollBox::getHorizontalScrollMax()
		{
			return getHScroll()->getMax();
		}

		float CScrollBox::getHorizontalScrollPosition()
		{
			return getHScroll()->getScroll();
		}
	#pragma endregion

	#pragma region Interface setters
		bool CScrollBox::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				getHScroll()->setDPI(value);
				getVScroll()->setDPI(value);
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				m_sPadding *= s;
				Update();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBox::setTransformControls(ITransform *value)
		{
			return false;
		}

		bool CScrollBox::setVerticalScrollVisibility(const ScrollVisibility value)
		{
			if (value != m_eVScroll)
			{
				m_eVScroll = value;
				Update();
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBox::setVerticalScrollPosition(const float value)
		{
			if (getVScroll()->isEnabled() && getVScroll()->setScroll(value))
			{
				CLockRepaint lock{ this };
				UpdateTransformControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBox::setHorizontalScrollVisibility(const ScrollVisibility value)
		{
			if (value != m_eHScroll)
			{
				m_eHScroll = value;
				Update();
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBox::setHorizontalScrollPosition(const float value)
		{
			if (getHScroll()->isEnabled() && getHScroll()->setScroll(value))
			{
				CLockRepaint lock{ this };
				UpdateTransformControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		Color CScrollBox::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CScrollBox::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		PointF CScrollBox::getPadding() const
		{
			return m_sPadding;
		}
	#pragma endregion

	#pragma region Setters
		bool CScrollBox::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				if (m_cBackgroundGradient.getPointCount() < 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CScrollBox::setVerticalScroll(IBuiltInScroll *value)
		{
			if (value && value != m_pVScroll && value != m_pHScroll)
			{
				if (m_pVScroll)
					m_pVScroll->Release();
				m_pVScroll = value;
				m_pVScroll->NotifyOnFreeResources();
				m_pVScroll->setVertical(true);
				m_pVScroll->setListener(&m_cScrollListener);
				Update();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBox::setHorizontalScroll(IBuiltInScroll *value)
		{
			if (value && value != m_pVScroll && value != m_pHScroll)
			{
				if (m_pHScroll)
					m_pHScroll->Release();
				m_pHScroll = value;
				m_pHScroll->NotifyOnFreeResources();
				m_pHScroll->setVertical(false);
				m_pHScroll->setListener(&m_cScrollListener);
				Update();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBox::setPadding(const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_sPadding))
			{
				m_sPadding = value;
				Update();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CScrollBox::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			getVScroll()->Refresh();
			getHScroll()->Refresh();
			CControl::Refresh(refresh_children);
		}

		void CScrollBox::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".CornerColor", m_sCornerColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			getVScroll()->UpdateFromStyle(style, m_sClassName + L".Scroll");
			getHScroll()->UpdateFromStyle(style, m_sClassName + L".Scroll");
			m_bIgnoreGradient = false;
		}

		IBuiltInScroll *CScrollBox::getVScroll()
		{
			if (!m_pVScroll)
			{
				CScroll *scroll{ new CScroll(this) };
				if (!scroll->isVertical())
					scroll->SwitchDirection(true);
				scroll->setEnabled(false);
				scroll->setListener(&m_cScrollListener);
				m_pVScroll = scroll;
			}
			return m_pVScroll;
		}

		IBuiltInScroll *CScrollBox::getHScroll()
		{
			if (!m_pHScroll)
			{
				CScroll *scroll{ new CScroll(this) };
				if (scroll->isVertical())
					scroll->SwitchDirection(true);
				scroll->setEnabled(false);
				scroll->setListener(&m_cScrollListener);
				m_pHScroll = scroll;
			}
			return m_pHScroll;
		}

		bool CScrollBox::UpdateTransformControls()
		{
			bool result{ getTransformControls()->setTx(-getHScroll()->getScroll()) };
			result = getTransformControls()->setTy(-getVScroll()->getScroll()) || result;
			return result;
		}

		void CScrollBox::Update() // Update scroll visibility, position, scroll, enabled state
		{
			PointF required_size{ 0, 0 };
			for (int i = 0; i < getControlCount(); i++)
				if (getControl(i)->isVisible(false) && getControl(i)->getAlign() == Align::None)
				{
					Vec4f v;
					Mat4f m{ getControl(i)->getTransform()->getMatrix() };
					v = m * Vec4f{ 0, 0, 0, 1 };
					required_size.X = ntl::Max<float>(required_size.X, v.X);
					required_size.Y = ntl::Max<float>(required_size.Y, v.Y);
					v = m * Vec4f{ getControl(i)->getWidth(), 0, 0, 1 };
					required_size.X = ntl::Max<float>(required_size.X, v.X);
					required_size.Y = ntl::Max<float>(required_size.Y, v.Y);
					v = m * Vec4f{ getControl(i)->getWidth(), getControl(i)->getHeight(), 0, 1 };
					required_size.X = ntl::Max<float>(required_size.X, v.X);
					required_size.Y = ntl::Max<float>(required_size.Y, v.Y);
					v = m * Vec4f{ 0, getControl(i)->getHeight(), 0, 1 };
					required_size.X = ntl::Max<float>(required_size.X, v.X);
					required_size.Y = ntl::Max<float>(required_size.Y, v.Y);
				}
			if (getControlCount() > 0)
			{
				required_size.X += m_sPadding.X;
				required_size.Y += m_sPadding.Y;
			}
			RectF client{ 0, 0, getWidth(), getHeight() };
			if (m_eVScroll == ScrollVisibility::Visible)
				client.Right -= getVScroll()->getWidth();
			if (m_eHScroll == ScrollVisibility::Visible)
				client.Bottom -= getHScroll()->getHeight();
			switch (m_eVScroll)
			{
			case ScrollVisibility::Visible:
				m_bVScroll = true;
				break;
			case ScrollVisibility::None:
				m_bVScroll = false;
				break;
			default:
				m_bVScroll = ntl::IsGreater<float>(required_size.Y, client.height());
			}
			switch (m_eHScroll)
			{
			case ScrollVisibility::Visible:
				m_bHScroll = true;
				break;
			case ScrollVisibility::None:
				m_bHScroll = false;
				break;
			default:
				m_bHScroll = ntl::IsGreater<float>(required_size.X, client.width());
			}
			getVScroll()->setEnabled(ntl::IsGreater<float>(required_size.Y, client.height()));
			getHScroll()->setEnabled(ntl::IsGreater<float>(required_size.X, client.width()));
			if (getVScroll()->isEnabled())
				getVScroll()->setMax(required_size.Y - client.height() + (m_bHScroll ? getHScroll()->getHeight() : 0));
			else
				getVScroll()->setScroll(0);
			if (getHScroll()->isEnabled())
				getHScroll()->setMax(required_size.X - client.width() + (m_bVScroll ? getVScroll()->getWidth() : 0));
			else
				getHScroll()->setScroll(0);
			getVScroll()->setSize(PointF{ getVScroll()->getWidth(), getHeight() - (m_bHScroll ? getHScroll()->getHeight() : 0) });
			getVScroll()->setPosition(PointF{ getWidth() - getVScroll()->getWidth(), 0 });
			getHScroll()->setSize(PointF{ getWidth() - (m_bVScroll ? getVScroll()->getWidth() : 0), getHScroll()->getHeight() });
			getHScroll()->setPosition(PointF{ 0, getHeight() - getHScroll()->getHeight() });
			UpdateTransformControls();
			if (!isEnabled(false))
			{
				getVScroll()->setEnabled(false);
				getHScroll()->setEnabled(false);
			}
		}

		bool CScrollBox::UpdateHoveredElement()
		{
			if (getForm())
				return UpdateHoveredElement(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())));
			return false;
		}

		bool CScrollBox::UpdateHoveredElement(const PointF &position)
		{
			Element el{ Element::None };
			if (isEnabled(true) && position.X >= 0 && position.X < getWidth() && position.Y >= 0 && position.Y < getHeight())
			{
				if (m_bVScroll && position.X >= getWidth() - getVScroll()->getWidth() && position.Y < getHeight() - (m_bHScroll ? getHScroll()->getHeight() : 0))
					el = Element::VScroll;
				else if (m_bHScroll && position.X < getWidth() - (m_bVScroll ? getVScroll()->getWidth() : 0) && position.Y >= getHeight() - getHScroll()->getHeight())
					el = Element::HScroll;
			}
			if (el != m_eHoveredElement)
			{
				switch (m_eHoveredElement)
				{
				case Element::VScroll:
					getVScroll()->NotifyOnMouseLeave();
					break;
				case Element::HScroll:
					getHScroll()->NotifyOnMouseLeave();
					break;
				default:
					break;
				}
				m_eHoveredElement = el;
				switch (m_eHoveredElement)
				{
				case Element::VScroll:
					getVScroll()->NotifyOnMouseHover(PointF{ position.X - getVScroll()->getLeft(), position.Y - getVScroll()->getTop() });
					break;
				case Element::HScroll:
					getHScroll()->NotifyOnMouseHover(PointF{ position.X - getHScroll()->getLeft(), position.Y - getHScroll()->getTop() });
					break;
				default:
					break;
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CScrollBox::Render(IRenderer *renderer, const Mat4f &matrix)
		{
			if (PrepareCanvas(renderer, &m_pCanvas, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });
				if (m_cBackgroundGradient.getPointCount() > 1)
					renderer->DrawGradient(RectF{ 0, 0, getWidth(), getHeight() }, m_cBackgroundGradient);
				else if (m_sBackgroundColor.A > 0)
					renderer->DrawRectangle(RectF{ 0, 0, getWidth(), getHeight() }, m_sBackgroundColor);
				if (m_bVScroll)
					getVScroll()->Render(false, ntl::Mat4Translate<float>(getVScroll()->getLeft(), getVScroll()->getTop(), 0), nullptr);
				if (m_bHScroll)
					getHScroll()->Render(false, ntl::Mat4Translate<float>(getHScroll()->getLeft(), getHScroll()->getTop(), 0), nullptr);
				if (m_bVScroll && m_bHScroll)
					renderer->DrawRectangle(RectF{ getVScroll()->getLeft(), getHScroll()->getTop(), getWidth(), getHeight() }, m_sCornerColor);
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, matrix, m_pCanvas, PointF{ 0, 0 });
		}

		void CScrollBox::RenderMask(IRenderer *renderer)
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