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
	#pragma region CGradientListener
		CCustomCartesianChart::CGradientListener::CGradientListener(CCustomCartesianChart *control) :
			m_pControl{ control }
		{

		}

		void CCustomCartesianChart::CGradientListener::NotifyOnChange()
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
		CCustomCartesianChart::CCustomCartesianChart(
			const String &class_name,
			const bool accept_form,
			const bool accept_control,
			const bool accept_controls,
			const bool accept_focus,
			const bool accept_modal,
			const bool tab_stop,
			const Point &design_dpi) :
			CControl(class_name, accept_form, accept_control, accept_controls, accept_focus, accept_modal, tab_stop, design_dpi),
			m_cGradientListener{ this },
			m_pDataSet{ nullptr },
			m_sAutoGrid{ true, true },
			m_sDefaultGridStep{ 50, 25 },
			m_sShowAxes{ true, true },
			m_sShowGrid{ true, true },
			m_sBackgroundColor{ 255, 255, 255, 255 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_sXAxisColor{ 200, 200, 200, 255 },
			m_sYAxisColor{ 200, 200, 200, 255 },
			m_sXGridColor{ 232, 232, 232, 255 },
			m_sYGridColor{ 232, 232, 232, 255 },
			m_sGridStep{ 50, 25 },
			m_sLabelPadding{ 32, 16 },
			m_sShowLabels{ true, true },
			m_bXLabelsAtTop{ false },
			m_bYLabelsAtRight{ false },
			m_sLabelSigns{ 0, 0 },
			m_sXLabelsColor{ 0, 0, 0, 0 },
			m_sYLabelsColor{ 0, 0, 0, 0 },
			m_sAutoGridStep{ 10, 10 },
			m_sXRange{ -169, 169 },
			m_sYRange{ -97, 97 },
			m_sAutoRange{ true, true },
			m_sAutoXRange{ 0, 0 },
			m_sAutoYRange{ 0, 0 },
			m_fPointSize{ 4 },
			m_pCanvas{ nullptr },
			m_pHoveredData{ nullptr },
			m_iHoveredPoint{ -1 },
			m_bIgnoreGradient{ false }
		{
			OnHoverPoint = nullptr;
			OnLeavePoint = nullptr;

			setService(new CCustomCartesianChartService(this), true);
		}

		CCustomCartesianChart::~CCustomCartesianChart()
		{
			if (m_pDataSet)
				m_pDataSet->Release();
		}
	#pragma endregion

	#pragma region IControl getters
		RectF CCustomCartesianChart::getClientRect()
		{
			RectF result{
				(m_sShowLabels.Y && !m_bYLabelsAtRight) ? m_sLabelPadding.X : 0,
				(m_sShowLabels.X && m_bXLabelsAtTop) ? m_sLabelPadding.Y : 0,
				getWidth() - ((m_sShowLabels.Y && m_bYLabelsAtRight) ? m_sLabelPadding.X : 0),
				getHeight() - ((m_sShowLabels.X && !m_bXLabelsAtTop) ? m_sLabelPadding.Y : 0)
			};
			result.validate();
			return result;
		}
	#pragma endregion

	#pragma region IControl setters
		bool CCustomCartesianChart::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sLabelPadding *= s;
				m_fPointSize *= avg;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IControl methods
		void CCustomCartesianChart::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			CControl::Refresh(refresh_children);
		}
	#pragma endregion

	#pragma region ICartesianChart getters
		PointF CCustomCartesianChart::getXRange()
		{
			return m_sXRange;
		}

		PointF CCustomCartesianChart::getYRange()
		{
			return m_sYRange;
		}

		PointB CCustomCartesianChart::getAutoRange()
		{
			return m_sAutoRange;
		}

		IChartDataSet *CCustomCartesianChart::getDataSet()
		{
			if (!m_pDataSet)
				m_pDataSet = new CChartDataSet();
			return m_pDataSet;
		}
	#pragma endregion

	#pragma region ICartesianChart setters
		bool CCustomCartesianChart::setXRange(const PointF &value)
		{
			if (ntl::IsGreater<float>(value.Y, value.X) && IsNotEqual(value, m_sXRange))
			{
				m_sXRange = value;
				m_sAutoRange.X = false;
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setYRange(const PointF &value)
		{
			if (ntl::IsGreater<float>(value.Y, value.X) && IsNotEqual(value, m_sYRange))
			{
				m_sYRange = value;
				m_sAutoRange.Y = false;
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setAutoRange(const PointB &value)
		{
			if (value != m_sAutoRange)
			{
				m_sAutoRange = value;
				UpdateAutoRanges();
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setDataSet(IChartDataSet *value, const bool release_old)
		{
			if (value != m_pDataSet)
			{
				if (m_pDataSet && release_old)
					m_pDataSet->Release();
				m_pDataSet = value;
				UpdateAutoRanges();
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region ICartesianChart methods
		void CCustomCartesianChart::Update()
		{
			UpdateAutoRanges();
			UpdateHoveredPoint();
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
		}
	#pragma endregion

	#pragma region Getters
		PointB CCustomCartesianChart::getShowAxes() const
		{
			return m_sShowAxes;
		}

		PointB CCustomCartesianChart::getShowGrid() const
		{
			return m_sShowGrid;
		}

		Color CCustomCartesianChart::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CCustomCartesianChart::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		Color CCustomCartesianChart::getXAxisColor() const
		{
			return m_sXAxisColor;
		}

		Color CCustomCartesianChart::getYAxisColor() const
		{
			return m_sYAxisColor;
		}

		Color CCustomCartesianChart::getXGridColor() const
		{
			return m_sXGridColor;
		}

		Color CCustomCartesianChart::getYGridColor() const
		{
			return m_sYGridColor;
		}

		PointF CCustomCartesianChart::getGridStep() const
		{
			return m_sGridStep;
		}

		PointF CCustomCartesianChart::getLabelPadding() const
		{
			return m_sLabelPadding;
		}

		PointB CCustomCartesianChart::getShowLabels() const
		{
			return m_sShowLabels;
		}

		bool CCustomCartesianChart::isXLabelsAtTop() const
		{
			return m_bXLabelsAtTop;
		}

		bool CCustomCartesianChart::isYLabelsAtRight() const
		{
			return m_bYLabelsAtRight;
		}

		Point CCustomCartesianChart::getLabelSigns() const
		{
			return m_sLabelSigns;
		}

		float CCustomCartesianChart::getPointSize() const
		{
			return m_fPointSize;
		}

		PointB CCustomCartesianChart::getAutoGrid()
		{
			return m_sAutoGrid;
		}

		PointF CCustomCartesianChart::getDefaultGridStep()
		{
			return m_sDefaultGridStep;
		}
	#pragma endregion

	#pragma region Setters
		bool CCustomCartesianChart::setShowAxes(const PointB &value)
		{
			if (value != m_sShowAxes)
			{
				m_sShowAxes = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setShowGrid(const PointB &value)
		{
			if (value != m_sShowGrid)
			{
				m_sShowGrid = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setBackgroundColor(const Color &value)
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

		bool CCustomCartesianChart::setXAxisColor(const Color &value)
		{
			if (value != m_sXAxisColor)
			{
				m_sXAxisColor = value;
				if (m_sShowAxes.X)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setYAxisColor(const Color &value)
		{
			if (value != m_sYAxisColor)
			{
				m_sYAxisColor = value;
				if (m_sShowAxes.Y)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setXGridColor(const Color &value)
		{
			if (value != m_sXGridColor)
			{
				m_sXGridColor = value;
				if (m_sShowGrid.X)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setYGridColor(const Color &value)
		{
			if (value != m_sYGridColor)
			{
				m_sYGridColor = value;
				if (m_sShowGrid.Y)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setGridStep(const PointF &value)
		{
			if (ntl::IsGreater<float>(value.X, 0) && ntl::IsGreater<float>(value.Y, 0) && IsNotEqual(value, m_sGridStep))
			{
				m_sGridStep = value;
				m_sAutoGrid = PointB{ false, false };
				if (m_sShowGrid.X || m_sShowGrid.Y)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setLabelPadding(const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_sLabelPadding))
			{
				m_sLabelPadding = value;
				UpdateAutoRanges();
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setShowLabels(const PointB &value)
		{
			if (value != m_sShowLabels)
			{
				m_sShowLabels = value;
				UpdateAutoRanges();
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setXLabelsAtTop(const bool value)
		{
			if (value != m_bXLabelsAtTop)
			{
				m_bXLabelsAtTop = value;
				if (m_sShowLabels.X)
				{
					UpdateHoveredPoint();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setYLabelsAtRight(const bool value)
		{
			if (value != m_bYLabelsAtRight)
			{
				m_bYLabelsAtRight = value;
				if (m_sShowLabels.Y)
				{
					UpdateHoveredPoint();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setLabelSigns(const Point &value)
		{
			if (value.X >= 0 && value.X <= 9 && value.Y >= 0 && value.Y <= 9 && value != m_sLabelSigns)
			{
				m_sLabelSigns = value;
				if (m_sShowLabels.X || m_sShowLabels.Y)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setPointSize(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fPointSize))
			{
				m_fPointSize = value;
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setAutoGrid(const PointB &value)
		{
			if (value != m_sAutoGrid)
			{
				m_sAutoGrid = value;
				UpdateAutoRanges();
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::setDefaultGridStep(const PointF &value)
		{
			if (ntl::IsGreater<float>(value.X, 0) && ntl::IsGreater<float>(value.Y, 0) && IsNotEqual(value, m_sDefaultGridStep))
			{
				m_sDefaultGridStep = value;
				if (m_sAutoGrid.X || m_sAutoGrid.Y)
				{
					UpdateAutoRanges();
					UpdateHoveredPoint();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CCustomCartesianChart::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L".XAxisColor", m_sXAxisColor);
			style->getOption(m_sClassName + L".YAxisColor", m_sYAxisColor);
			style->getOption(m_sClassName + L".XGridColor", m_sXGridColor);
			style->getOption(m_sClassName + L".YGridColor", m_sYGridColor);
			style->getOption(m_sClassName + L".LabelPadding", m_sLabelPadding);
			style->getOption(m_sClassName + L".XLabelsColor", m_sXLabelsColor);
			style->getOption(m_sClassName + L".YLabelsColor", m_sYLabelsColor);
			m_bIgnoreGradient = false;
		}

		bool CCustomCartesianChart::UpdateHoveredPoint()
		{
			if (getForm())
				return UpdateHoveredPoint((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition()));
			if (m_iHoveredPoint >= 0)
			{
				m_pHoveredData = nullptr;
				m_iHoveredPoint = -1;
				if (OnLeavePoint)
					OnLeavePoint(this);
				return true;
			}
			return false;
		}

		bool CCustomCartesianChart::UpdateHoveredPoint(const PointF &position)
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
						float d;
						PointF xrange{ m_sAutoRange.X ? m_sAutoXRange : m_sXRange }, yrange{ m_sAutoRange.Y ? m_sAutoYRange : m_sYRange };
						for (int i = 0; i < m_pDataSet->getDataCount(); i++)
						{
							for (int j = 0; j < m_pDataSet->getData(i)->getCount(); j++)
							{
								dp = DataToView(PointF{ m_pDataSet->getData(i)->getX(j), m_pDataSet->getData(i)->getY(j) }, xrange, yrange, view_size);
								d = std::sqrt((p.X - dp.X) * (p.X - dp.X) + (p.Y - dp.Y) * (p.Y - dp.Y));
								if (d <= m_fPointSize)
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

		void CCustomCartesianChart::UpdateAutoRanges()
		{
			RectF client{ getClientRect() };
			if (m_sAutoRange.X || m_sAutoRange.Y)
			{
				float xmin, ymin, xmax, ymax;
				int count{ 0 };
				if (m_pDataSet)
				{
					for (int i = 0; i < m_pDataSet->getDataCount(); i++)
					{
						for (int j = 0; j < m_pDataSet->getData(i)->getCount(); j++)
						{
							if (count > 0)
							{
								xmin = ntl::Min<float>(xmin, m_pDataSet->getData(i)->getX(j));
								ymin = ntl::Min<float>(ymin, m_pDataSet->getData(i)->getY(j));
								xmax = ntl::Max<float>(xmax, m_pDataSet->getData(i)->getX(j));
								ymax = ntl::Max<float>(ymax, m_pDataSet->getData(i)->getY(j));
								count++;
							}
							else
							{
								xmin = xmax = m_pDataSet->getData(i)->getX(j);
								ymin = ymax = m_pDataSet->getData(i)->getY(j);
								count = 1;
							}
						}
					}
				}
				if (count == 0)
				{
					xmin = -client.width() * 0.5f;
					ymin = -client.height() * 0.5f;
					xmax = client.width() * 0.5f;
					ymax = client.height() * 0.5f;
				}
				else if (count == 1)
				{
					xmin -= client.width() * 0.5f;
					xmax += client.width() * 0.5f;
					ymin -= client.height() * 0.5f;
					ymax += client.height() * 0.5f;
				}
				// Ranges are extended by 5% to leave some space at the borders. It is applied only if there is data
				if (m_sAutoRange.X)
					m_sAutoXRange = PointF{ xmin - ((count > 1) ? ((xmax - xmin) * 0.05f) : 0), xmax + ((count > 1) ? ((xmax - xmin) * 0.05f) : 0) };
				if (m_sAutoRange.Y)
					m_sAutoYRange = PointF{ ymin - ((count > 1) ? ((ymax - ymin) * 0.05f) : 0), ymax + ((count > 1) ? ((ymax - ymin) * 0.05f) : 0) };
			}
			if (m_sAutoGrid.X)
			{
				PointF xrange{ m_sAutoRange.X ? m_sAutoXRange : m_sXRange };
				if (ntl::IsGreater<float>(xrange.Y, xrange.X))
				{
					float step{ m_sDefaultGridStep.X }, w{ client.width() }, zero{ DataXToView(0, xrange, w) }, p{ ntl::Abs<float>(DataXToView(step, xrange, w) - zero) };
					if (p < m_sDefaultGridStep.X)
					{
						while (p < m_sDefaultGridStep.X)
						{
							step *= 2;
							p = ntl::Abs<float>(DataXToView(step, xrange, w) - zero);
						}
					}
					else if (p > m_sDefaultGridStep.X)
					{
						while (p > m_sDefaultGridStep.X)
						{
							step *= 0.5f;
							p = ntl::Abs<float>(DataXToView(step, xrange, w) - zero);
						}
					}
					m_sAutoGridStep.X = step;
				}
			}
			if (m_sAutoGrid.Y)
			{
				PointF yrange{ m_sAutoRange.Y ? m_sAutoYRange : m_sYRange };
				if (ntl::IsGreater<float>(yrange.Y, yrange.X))
				{
					float step{ m_sDefaultGridStep.Y }, h{ client.height() }, zero{ DataYToView(0, yrange, h) }, p{ ntl::Abs<float>(DataYToView(step, yrange, h) - zero) };
					if (p < m_sDefaultGridStep.Y)
					{
						while (p < m_sDefaultGridStep.Y)
						{
							step *= 2;
							p = ntl::Abs<float>(DataYToView(step, yrange, h) - zero);
						}
					}
					else if (p > m_sDefaultGridStep.Y)
					{
						while (p > m_sDefaultGridStep.Y)
						{
							step *= 0.5f;
							p = ntl::Abs<float>(DataYToView(step, yrange, h) - zero);
						}
					}
					m_sAutoGridStep.Y = step;
				}
			}
		}
	#pragma endregion

	#pragma region Paint
		void CCustomCartesianChart::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			RectF rect{ 0, 0, getWidth(), getHeight() };
			if (PrepareCanvas(renderer, &m_pCanvas, rect))
			{
				CStoreTarget s_target{ renderer };
				renderer->ActivateTarget(m_pCanvas);
				renderer->Clear(Color{ 0, 0, 0, 0 });

				RectF client{ getClientRect() };
				IFont *font{ getFont() };
				IPlatformFont *pf{ font ? font->getPlatformFont(renderer) : nullptr };
				RenderBackground(renderer, rect);
				if (!client.is_zero())
				{
					PointF xrange{ m_sAutoRange.X ? m_sAutoXRange : m_sXRange }, yrange{ m_sAutoRange.Y ? m_sAutoYRange : m_sYRange };
					PointF grid_step{ m_sAutoGrid.X ? m_sAutoGridStep.X : m_sGridStep.X, m_sAutoGrid.Y ? m_sAutoGridStep.Y : m_sGridStep.Y };
					RenderAxesAndGrid(renderer, client, xrange, yrange, grid_step);
					if (font && pf)
						RenderLabels(renderer, client, font, pf, xrange, yrange, grid_step);
					RenderDataSet(renderer, client, xrange, yrange);
				}

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}

		void CCustomCartesianChart::RenderBackground(IRenderer *renderer, const RectF &rect)
		{
			if (m_cBackgroundGradient.getPointCount() >= 2)
				renderer->DrawGradient(rect, m_cBackgroundGradient);
			else if (m_sBackgroundColor.A > 0)
				renderer->DrawRectangle(rect, m_sBackgroundColor);
		}

		void CCustomCartesianChart::RenderAxesAndGrid(IRenderer *renderer, const RectF &client, const PointF &xrange, const PointF &yrange, const PointF &grid_step)
		{
			if (m_sShowGrid.X && m_sXGridColor.A > 0)
			{
				float x1{ float(int(xrange.X / grid_step.X)) * grid_step.X }, x2{ float(int(xrange.Y / grid_step.X)) * grid_step.X };
				while (x1 <= x2)
				{
					float x{ client.Left + (x1 - xrange.X) * client.width() / (xrange.Y - xrange.X) };
					if (x >= client.Left && x < client.Right && (ntl::IsNotEqual<float>(x1, 0) || !m_sShowAxes.X))
						renderer->DrawLine(PointF{ x, client.Top }, PointF{ x, client.Bottom }, m_sXGridColor);
					x1 += grid_step.X;
				}
			}
			if (m_sShowGrid.Y && m_sYGridColor.A > 0)
			{
				float y1{ float(int(yrange.X / grid_step.Y)) * grid_step.Y }, y2{ float(int(yrange.Y / grid_step.Y)) * grid_step.Y };
				while (y1 <= y2)
				{
					float y{ client.Bottom - (y1 - yrange.X) * client.height() / (yrange.Y - yrange.X) };
					if (y >= client.Top && y < client.Bottom && (ntl::IsNotEqual<float>(y1, 0) || !m_sShowAxes.Y))
						renderer->DrawLine(PointF{ client.Left, y }, PointF{ client.Right, y }, m_sYGridColor);
					y1 += grid_step.Y;
				}
			}
			if (m_sShowAxes.X && yrange.X <= 0 && yrange.Y >= 0 && m_sXAxisColor.A > 0)
			{
				float y{ client.Bottom + yrange.X * client.height() / (yrange.Y - yrange.X) };
				renderer->DrawLine(PointF{ client.Left, y }, PointF{ client.Right, y }, m_sXAxisColor);
			}
			if (m_sShowAxes.Y && xrange.X <= 0 && xrange.Y >= 0 && m_sYAxisColor.A > 0)
			{
				float x{ client.Left - xrange.X * client.width() / (xrange.Y - xrange.X) };
				renderer->DrawLine(PointF{ x, client.Top }, PointF{ x, client.Bottom }, m_sYAxisColor);
			}
		}

		void CCustomCartesianChart::RenderLabels(IRenderer *renderer, const RectF &client, IFont *font, IPlatformFont *pf, const PointF &xrange, const PointF &yrange, const PointF &grid_step)
		{
			CStorePrimitiveMatrix s_matrix{ renderer };
			String label;
			PointF size;
			Color color;
			if (m_sShowLabels.X)
			{
				color = m_sXLabelsColor.A > 0 ? m_sXLabelsColor : font->Color;
				if (color.A > 0)
				{
					float x1{ float(int(xrange.X / grid_step.X)) * grid_step.X }, x2{ float(int(xrange.Y / grid_step.X)) * grid_step.X };
					while (x1 <= x2)
					{
						float x{ client.Left + (x1 - xrange.X) * client.width() / (xrange.Y - xrange.X) };
						if (x >= client.Left)
						{
							label = ToFixed(x1, m_sLabelSigns.X);
							if (m_pDataSet)
								label = m_pDataSet->getXLabel(x1, label);
							if (!label.empty())
							{
								size = pf->getStringSize(label, font->Distance);
								renderer
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(x - size.X / 2), std::round(m_bXLabelsAtTop ? (m_sLabelPadding.Y - size.Y) : client.Bottom), 0))
									->DrawText(label, pf, font->Distance, color);
							}
						}
						x1 += grid_step.X;
					}
				}
			}
			if (m_sShowLabels.Y)
			{
				color = m_sYLabelsColor.A > 0 ? m_sYLabelsColor : font->Color;
				if (color.A > 0)
				{
					float y1{ float(int(yrange.X / grid_step.Y)) * grid_step.Y }, y2{ float(int(yrange.Y / grid_step.Y)) * grid_step.Y };
					while (y1 <= y2)
					{
						float y{ client.Bottom - (y1 - yrange.X) * client.height() / (yrange.Y - yrange.X) };
						if (y < client.Bottom)
						{
							label = ToFixed(y1, m_sLabelSigns.Y);
							if (m_pDataSet)
								label = m_pDataSet->getYLabel(y1, label);
							if (!label.empty())
							{
								size = pf->getStringSize(label, font->Distance);
								renderer
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(m_bYLabelsAtRight ? client.Right : (m_sLabelPadding.X - size.X)), std::round(y - size.Y / 2), 0))
									->DrawText(label, pf, font->Distance, color);
							}
						}
						y1 += grid_step.Y;
					}
				}
			}
		}

		void CCustomCartesianChart::RenderDataSet(IRenderer *renderer, const RectF &client, const PointF &xrange, const PointF &yrange)
		{
			if (m_pDataSet)
			{
				ITexture *target{ renderer->CreateTexture(ntl::Round<int>(client.width()), ntl::Round<int>(client.height()), 1, TextureFormat::RGBA, true) };
				if (target)
				{
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer->ActivateTarget(target);
					renderer->Clear(Color{ 0, 0, 0, 0 });
					for (int i = 0; i < m_pDataSet->getDataCount(); i++)
						RenderData(renderer, client, m_pDataSet->getData(i), i, target, xrange, yrange);
					renderer
						->ActivateTarget(m_pCanvas)
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(client.Left, client.Top, 0))
						->DrawImage(target, 1);
					target->Release();
				}
			}
		}
	#pragma endregion
	}
}