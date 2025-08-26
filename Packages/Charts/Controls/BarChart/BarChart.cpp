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
	namespace charts
	{
	#pragma region Constructor & destructor
		CBarChart::CBarChart() :
			CCustomCartesianChart(L"BarChart", true, true, false, false, false, false),
			m_pRenderer{ new CBarChartRenderer() }
		{
			setSize(PointF{ 370, 210 });
		}

		CBarChart::CBarChart(IForm *parent) : CBarChart()
		{
			setForm(parent);
		}

		CBarChart::CBarChart(IControl *parent) : CBarChart()
		{
			setParent(parent);
		}

		CBarChart::~CBarChart()
		{
			m_pRenderer->Release();
		}
	#pragma endregion

	#pragma region IControl setters
		bool CBarChart::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CCustomCartesianChart::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_pRenderer->setBorderWidth(CBarChartRenderer::PointState::Normal, m_pRenderer->getBorderWidth(CBarChartRenderer::PointState::Normal) * avg);
				m_pRenderer->setBorderWidth(CBarChartRenderer::PointState::Active, m_pRenderer->getBorderWidth(CBarChartRenderer::PointState::Active) * avg);
				m_pRenderer->setBarWidth(m_pRenderer->getBarWidth() * avg);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		bool CBarChart::isDrawBorder(const CBarChartRenderer::PointState state) const
		{
			return m_pRenderer->isDrawBorder(state);
		}

		bool CBarChart::isDrawBackground(const CBarChartRenderer::PointState state) const
		{
			return m_pRenderer->isDrawBackground(state);
		}

		float CBarChart::getBorderWidth(const CBarChartRenderer::PointState state) const
		{
			return m_pRenderer->getBorderWidth(state);
		}

		Color CBarChart::getBorderColor(const CBarChartRenderer::PointState state) const
		{
			return m_pRenderer->getBorderColor(state);
		}

		Color CBarChart::getBackgroundColor(const CBarChartRenderer::PointState state) const
		{
			return m_pRenderer->getBackgroundColor(state);
		}

		bool CBarChart::isVertical() const
		{
			return m_pRenderer->isVertical();
		}

		float CBarChart::getBarWidth() const
		{
			return m_pRenderer->getBarWidth();
		}
	#pragma endregion

	#pragma region Setters
		bool CBarChart::setDrawBorder(const CBarChartRenderer::PointState state, const bool value)
		{
			if (m_pRenderer->setDrawBorder(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CBarChart::setDrawBackground(const CBarChartRenderer::PointState state, const bool value)
		{
			if (m_pRenderer->setDrawBackground(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CBarChart::setBorderWidth(const CBarChartRenderer::PointState state, const float value)
		{
			if (m_pRenderer->setBorderWidth(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CBarChart::setBorderColor(const CBarChartRenderer::PointState state, const Color &value)
		{
			if (m_pRenderer->setBorderColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CBarChart::setBackgroundColor(const CBarChartRenderer::PointState state, const Color &value)
		{
			if (m_pRenderer->setBackgroundColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CBarChart::setVertical(const bool value)
		{
			if (m_pRenderer->setVertical(value))
			{
				CCustomCartesianChart::UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CBarChart::setBarWidth(const float value)
		{
			if (m_pRenderer->setBarWidth(value))
			{
				CCustomCartesianChart::UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CBarChart::UpdateFromStyle(IStyle *style)
		{
			CCustomCartesianChart::UpdateFromStyle(style);
			float vf;
			if (style->getOption(m_sClassName + L".BorderWidth[PointState::Normal]", vf))
				m_pRenderer->setBorderWidth(CBarChartRenderer::PointState::Normal, vf);
			if (style->getOption(m_sClassName + L".BorderWidth[PointState::Active]", vf))
				m_pRenderer->setBorderWidth(CBarChartRenderer::PointState::Active, vf);
			Color vc;
			if (style->getOption(m_sClassName + L".BorderColor[PointState::Normal]", vc))
				m_pRenderer->setBorderColor(CBarChartRenderer::PointState::Normal, vc);
			if (style->getOption(m_sClassName + L".BorderColor[PointState::Active]", vc))
				m_pRenderer->setBorderColor(CBarChartRenderer::PointState::Active, vc);
			if (style->getOption(m_sClassName + L".BackgroundColor[PointState::Normal]", vc))
				m_pRenderer->setBackgroundColor(CBarChartRenderer::PointState::Normal, vc);
			if (style->getOption(m_sClassName + L".BackgroundColor[PointState::Active]", vc))
				m_pRenderer->setBackgroundColor(CBarChartRenderer::PointState::Active, vc);
			if (style->getOption(m_sClassName + L".BarWidth", vf))
				m_pRenderer->setBarWidth(vf);
		}

		bool CBarChart::UpdateHoveredPoint(const PointF &position)
		{
			IChartData *hovered_data{ nullptr };
			int hovered_point{ -1 };
			if (m_pDataSet && isEnabled(true))
			{
				RectF client{ getClientRect() };
				if (!client.is_zero())
				{
					PointF p{ FormToLocal(position) };
					if (p.X >= client.Left && p.X < client.Right && p.Y >= client.Top && p.Y < client.Bottom)
					{
						p.X -= client.Left;
						p.Y -= client.Top;
						PointF view_size{ client.width(), client.height() }, dp;
						PointF xrange{ m_sAutoRange.X ? m_sAutoXRange : m_sXRange }, yrange{ m_sAutoRange.Y ? m_sAutoYRange : m_sYRange };
						PointF zero{ DataToView(PointF{ 0, 0 }, xrange, yrange, view_size) };
						RectF r;
						for (int i = 0; i < m_pDataSet->getDataCount(); i++)
						{
							for (int j = 0; j < m_pDataSet->getData(i)->getCount(); j++)
							{
								dp = DataToView(PointF{ m_pDataSet->getData(i)->getX(j), m_pDataSet->getData(i)->getY(j) }, xrange, yrange, view_size);
								if (m_pRenderer->isVertical())
								{
									r.Left = ntl::Min<float>(dp.X, zero.X);
									r.Right = ntl::Max<float>(dp.X, zero.X);
									r.Top = dp.Y - m_pRenderer->getBarWidth() * 0.5f;
									r.Bottom = r.Top + m_pRenderer->getBarWidth();
								}
								else
								{
									r.Left = dp.X - m_pRenderer->getBarWidth() * 0.5f;
									r.Right = r.Left + m_pRenderer->getBarWidth();
									r.Top = ntl::Min<float>(dp.Y, zero.Y);
									r.Bottom = ntl::Max<float>(dp.Y, zero.Y);
								}
								if (p.X >= r.Left && p.X < r.Right && p.Y >= r.Top && p.Y < r.Bottom)
								{
									hovered_data = m_pDataSet->getData(i);
									hovered_point = j;
									break;
								}
							}
							if (hovered_data)
								break;
						}
					}
				}
			}
			if (hovered_data != m_pHoveredData || hovered_point != m_iHoveredPoint)
			{
				m_pHoveredData = hovered_data;
				m_iHoveredPoint = hovered_point;
				if (m_pHoveredData)
				{
					if (OnHoverPoint)
						OnHoverPoint(this, m_pHoveredData, m_iHoveredPoint);
				}
				else
				{
					if (OnLeavePoint)
						OnLeavePoint(this);
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CBarChart::RenderData(IRenderer *renderer, const RectF &client, IChartData *data, const int index, ITexture *target, const PointF &xrange, const PointF &yrange)
		{
			if (data && data->getCount() > 0)
			{
				m_pRenderer->setActivePoint((data == m_pHoveredData) ? m_iHoveredPoint : -1);
				m_pRenderer->Render(renderer, target, data, xrange, yrange);
			}
		}
	#pragma endregion
	}
}