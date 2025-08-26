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
	#pragma region Constructor & destructor
		CBevel::CBevel() :
			CControl(L"Bevel", true, true, false, false, false, false),
			m_eBevelKind{ BevelKind::Box },
			m_eBevelStyle{ BevelStyle::Lowered },
			m_sColorLowered{ 160, 160, 160, 255 },
			m_sColorRaised{ 255, 255, 255, 255 },
			m_fBevelWidth{ 1 },
			m_pCanvas{ nullptr }
		{
			setService(new CBevelService(this), true);
			setSize(PointF{ 50, 50 });
		}

		CBevel::CBevel(IForm *parent) :CBevel()
		{
			setForm(parent);
		}

		CBevel::CBevel(IControl *parent) : CBevel()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IControl methods
		void CBevel::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region  Interface getters
		IBevel::BevelKind CBevel::getBevelKind()
		{
			return m_eBevelKind;
		}

		IBevel::BevelStyle CBevel::getBevelStyle()
		{
			return m_eBevelStyle;
		}
	#pragma endregion

	#pragma region Getters
		Color CBevel::getColorLowered()
		{
			return m_sColorLowered;
		}

		Color CBevel::getColorRaised()
		{
			return m_sColorRaised;
		}

		float CBevel::getBevelWidth()
		{
			return m_fBevelWidth;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CBevel::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				m_fBevelWidth *= (s.X + s.Y) * 0.5f;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CBevel::setBevelKind(const BevelKind value)
		{
			if (value != m_eBevelKind)
			{
				m_eBevelKind = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CBevel::setBevelStyle(const BevelStyle value)
		{
			if (value != m_eBevelStyle)
			{
				m_eBevelStyle = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CBevel::setColorLowered(const Color &value)
		{
			if (value != m_sColorLowered)
			{
				m_sColorLowered = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CBevel::setColorRaised(const Color &value)
		{
			if (value != m_sColorRaised)
			{
				m_sColorRaised = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CBevel::setBevelWidth(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fBevelWidth))
			{
				m_fBevelWidth = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CBevel::UpdateFromStyle(IStyle *style)
		{
			style->getOption(m_sClassName + L".ColorLowered", m_sColorLowered);
			style->getOption(m_sClassName + L".ColorRaised", m_sColorRaised);
		}
	#pragma endregion

	#pragma region Paint
		void CBevel::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			if (PrepareCanvas(renderer, &m_pCanvas, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				Color c1{ (m_eBevelStyle == BevelStyle::Lowered) ? m_sColorLowered : m_sColorRaised }, c2{ (m_eBevelStyle == BevelStyle::Lowered) ? m_sColorRaised : m_sColorLowered };
				switch (m_eBevelKind)
				{
				case BevelKind::Box:
					RenderBox(renderer, c1, c2);
					break;
				case BevelKind::Frame:
					RenderFrame(renderer, c1, c2);
					break;
				case BevelKind::LeftEdge:
					RenderLeftEdge(renderer, c1, c2);
					break;
				case BevelKind::TopEdge:
					RenderTopEdge(renderer, c1, c2);
					break;
				case BevelKind::RightEdge:
					RenderRightEdge(renderer, c1, c2);
					break;
				case BevelKind::BottomEdge:
					RenderBottomEdge(renderer, c1, c2);
				}

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}

		void CBevel::RenderBox(IRenderer *renderer, const Color &c1, const Color &c2)
		{
			if (getWidth() >= m_fBevelWidth * 2 && getHeight() >= m_fBevelWidth * 2)
			{
				BlockColors colors{ c1, c1, c2, c2, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
				renderer->DrawBlock(RectF{ 0, 0, getWidth(), getHeight() }, RectF{ m_fBevelWidth, m_fBevelWidth, m_fBevelWidth, m_fBevelWidth }, RectF{ 0, 0, 0, 0 }, colors);
			}
		}

		void CBevel::RenderFrame(IRenderer *renderer, const Color &c1, const Color &c2)
		{
			if (getWidth() >= m_fBevelWidth * 4 && getHeight() >= m_fBevelWidth * 4)
			{
				BlockColors colors{ c2, c2, c2, c2, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
				renderer->DrawBlock(RectF{ m_fBevelWidth, m_fBevelWidth, getWidth(), getHeight() }, RectF{ m_fBevelWidth, m_fBevelWidth, m_fBevelWidth, m_fBevelWidth }, RectF{ 0, 0, 0, 0 }, colors);
				colors[0] = c1;
				colors[1] = c1;
				colors[2] = c1;
				colors[3] = c1;
				renderer->DrawBlock(RectF{ 0, 0, getWidth() - m_fBevelWidth, getHeight() - m_fBevelWidth }, RectF{ m_fBevelWidth, m_fBevelWidth, m_fBevelWidth, m_fBevelWidth }, RectF{ 0, 0, 0, 0 }, colors);
			}
		}

		void CBevel::RenderLeftEdge(IRenderer *renderer, const Color &c1, const Color &c2)
		{
			if (getWidth() >= m_fBevelWidth * 2)
			{
				BlockColors colors{ c1, Color{ 0, 0, 0, 0 }, c2, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
				renderer->DrawBlock(RectF{ 0, 0, m_fBevelWidth * 2, getHeight() }, RectF{ m_fBevelWidth, 0, m_fBevelWidth, 0 }, RectF{ 0, 0, 0, 0 }, colors);
			}
		}

		void CBevel::RenderTopEdge(IRenderer *renderer, const Color &c1, const Color &c2)
		{
			if (getHeight() >= m_fBevelWidth * 2)
			{
				BlockColors colors{ Color{ 0, 0, 0, 0 }, c1, Color{ 0, 0, 0, 0 }, c2, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
				renderer->DrawBlock(RectF{ 0, 0, getWidth(), m_fBevelWidth * 2 }, RectF{ 0, m_fBevelWidth, 0, m_fBevelWidth }, RectF{ 0, 0, 0, 0 }, colors);
			}
		}

		void CBevel::RenderRightEdge(IRenderer *renderer, const Color &c1, const Color &c2)
		{
			if (getWidth() >= m_fBevelWidth * 2)
			{
				BlockColors colors{ c1, Color{ 0, 0, 0, 0 }, c2, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
				renderer->DrawBlock(RectF{ getWidth() - m_fBevelWidth * 2, 0, getWidth(), getHeight() }, RectF{ m_fBevelWidth, 0, m_fBevelWidth, 0 }, RectF{ 0, 0, 0, 0 }, colors);
			}
		}

		void CBevel::RenderBottomEdge(IRenderer *renderer, const Color &c1, const Color &c2)
		{
			if (getHeight() >= m_fBevelWidth * 2)
			{
				BlockColors colors{ Color{ 0, 0, 0, 0 }, c1, Color{ 0, 0, 0, 0 }, c2, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
				renderer->DrawBlock(RectF{ 0, getHeight() - m_fBevelWidth * 2, getWidth(), getHeight() }, RectF{ 0, m_fBevelWidth, 0, m_fBevelWidth }, RectF{ 0, 0, 0, 0 }, colors);
			}
		}
	#pragma endregion
	}
}