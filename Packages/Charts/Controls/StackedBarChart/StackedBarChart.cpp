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
	namespace charts
	{
	#pragma region Constructor & destructor
		CStackedBarChart::CStackedBarChart() :
			CCustomCartesianChart(L"StackedBarChart", true, true, false, false, false, false),
			m_aNormalBackgroundColors{
				Color{ 255, 123, 151, 128 },
				Color{ 73, 171, 236, 128 },
				Color{ 255, 208, 98, 128 },
				Color{ 88, 255, 196, 128 },
				Color{ 220, 20, 60, 128 },
				Color{ 160, 113, 255, 128 },
				Color{ 205, 206, 210, 128 },
				Color{ 255, 166, 77, 128 } },
			m_aActiveBackgroundColors{
				Color{ 255, 123, 151, 156 },
				Color{ 73, 171, 236, 156 },
				Color{ 255, 208, 98, 156 },
				Color{ 88, 255, 196, 156 },
				Color{ 220, 20, 60, 156 },
				Color{ 160, 113, 255, 156 },
				Color{ 205, 206, 210, 156 },
				Color{ 255, 166, 77, 156 } },
			m_bVertical{ false },
			m_fBarSize{ 0.8f }
		{
			setSize(PointF{ 370, 210 });
		}

		CStackedBarChart::CStackedBarChart(IForm *parent) : CStackedBarChart()
		{
			setForm(parent);
		}

		CStackedBarChart::CStackedBarChart(IControl *parent) : CStackedBarChart()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Getters
		bool CStackedBarChart::isVertical() const
		{
			return m_bVertical;
		}

		float CStackedBarChart::getBarSize() const
		{
			return m_fBarSize;
		}

		const ColorArray &CStackedBarChart::getNormalBackgroundColors() const
		{
			return m_aNormalBackgroundColors;
		}

		const ColorArray &CStackedBarChart::getActiveBackgroundColors() const
		{
			return m_aActiveBackgroundColors;
		}
	#pragma endregion

	#pragma region Setters
		bool CStackedBarChart::setVertical(const bool value)
		{
			if (value != m_bVertical)
			{
				m_bVertical = value;
				CCustomCartesianChart::UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CStackedBarChart::setBarSize(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsLessOrEqual<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fBarSize))
			{
				m_fBarSize = value;
				if (m_pDataSet)
				{
					CCustomCartesianChart::UpdateHoveredPoint();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CStackedBarChart::setNormalBackgroundColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aNormalBackgroundColors = values;
				if (m_pDataSet)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CStackedBarChart::setActiveBackgroundColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aActiveBackgroundColors = values;
				if (m_pDataSet)
				{
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
		void CStackedBarChart::UpdateFromStyle(IStyle *style)
		{
			CCustomCartesianChart::UpdateFromStyle(style);
			int index;
			Color vc;
			index = 0;
			while (style->getOption(m_sClassName + L".NormalBackgroundColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aNormalBackgroundColors.clear();
				m_aNormalBackgroundColors.push_back(vc);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".ActiveBackgroundColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aActiveBackgroundColors.clear();
				m_aActiveBackgroundColors.push_back(vc);
				index++;
			}
		}

		IChartData *CStackedBarChart::FindBestData() const
		{
			IChartData *result{ nullptr };
			if (m_pDataSet)
				for (int i = 0; i < m_pDataSet->getDataCount(); i++)
					if (m_pDataSet->getData(i)->getCount() > 0 && (!result || m_pDataSet->getData(i)->getCount() > result->getCount()))
						result = m_pDataSet->getData(i);
			return result;
		}

		void CStackedBarChart::UpdateAutoRanges()
		{
			RectF client{ getClientRect() };
			if (m_sAutoRange.X || m_sAutoRange.Y)
			{
				float xmin{ 0 }, ymin{ 0 }, xmax{ 0 }, ymax{ 0 }, t_pos, t_neg;
				IChartData *best{ FindBestData() };
				if (best)
					for (int index = 0; index < best->getCount(); index++)
					{
						if (!m_bVertical)
						{
							if (index == 0)
								xmin = xmax = best->getX(index);
							else
							{
								xmin = ntl::Min<float>(xmin, best->getX(index));
								xmax = ntl::Max<float>(xmax, best->getX(index));
							}
						}
						t_pos = t_neg = 0;
						for (int i = 0; i < m_pDataSet->getDataCount(); i++)
							if (m_pDataSet->getData(i)->getCount() >= index - 1)
							{
								if (m_bVertical)
								{
									if (index == 0)
										ymin = ymax = m_pDataSet->getData(i)->getY(index);
									else
									{
										ymin = ntl::Min<float>(ymin, m_pDataSet->getData(i)->getY(index));
										ymax = ntl::Max<float>(ymax, m_pDataSet->getData(i)->getY(index));
									}
									if (m_pDataSet->getData(i)->getX(index) >= 0)
										t_pos += m_pDataSet->getData(i)->getX(index);
									else
										t_neg += m_pDataSet->getData(i)->getX(index);
								}
								else
								{
									if (m_pDataSet->getData(i)->getY(index) >= 0)
										t_pos += m_pDataSet->getData(i)->getY(index);
									else
										t_neg += m_pDataSet->getData(i)->getY(index);
								}
							}
						if (m_bVertical)
						{
							xmin = ntl::Min<float>(xmin, t_neg);
							xmax = ntl::Max<float>(xmax, t_pos);
						}
						else
						{
							ymin = ntl::Min<float>(ymin, t_neg);
							ymax = ntl::Max<float>(ymax, t_pos);
						}
					}
				if (!best)
				{
					xmin = -client.width() * 0.5f;
					ymin = -client.height() * 0.5f;
					xmax = client.width() * 0.5f;
					ymax = client.height() * 0.5f;
				}
				else if (best->getCount() == 1)
				{
					if (m_bVertical)
					{
						ymin -= client.height() * 0.5f;
						ymax += client.height() * 0.5f;
					}
					else
					{
						xmin -= client.width() * 0.5f;
						xmax += client.width() * 0.5f;
					}
				}
				// Ranges are extended by 5% to leave some space at the borders. It is applied only if there is data
				if (m_sAutoRange.X)
					m_sAutoXRange = PointF{ xmin - (xmax - xmin) * 0.05f, xmax + (xmax - xmin) * 0.05f };
				if (m_sAutoRange.Y)
					m_sAutoYRange = PointF{ ymin - (ymax - ymin) * 0.05f, ymax + (ymax - ymin) * 0.05f };
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

		bool CStackedBarChart::UpdateHoveredPoint(const PointF &position)
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
						IChartData *best{ FindBestData() };
						if (best)
						{
							p.X -= client.Left;
							p.Y -= client.Top;
							PointF view_size{ client.width(), client.height() };
							PointF xrange{ m_sAutoRange.X ? m_sAutoXRange : m_sXRange };
							PointF yrange{ m_sAutoRange.Y ? m_sAutoYRange : m_sYRange };
							if (m_bVertical)
							{
								float zero{ DataXToView(0, xrange, view_size.X) }, x_pos, x_neg, x;
								float grid_step_y{ view_size.Y / (float)best->getCount() }, bar_size{ grid_step_y * m_fBarSize }, half_bar_padding{ (grid_step_y - bar_size) * 0.5f };
								float y1{ client.Bottom + grid_step_y };
								for (int index = 0; index < best->getCount(); index++)
								{
									y1 -= grid_step_y;
									if (p.Y < y1 - half_bar_padding - bar_size || p.Y >= y1 - half_bar_padding)
										continue;
									x_pos = x_neg = zero;
									for (int i = 0; i < m_pDataSet->getDataCount(); i++)
										if (m_pDataSet->getData(i)->getCount() >= index - 1)
										{
											x = ntl::Abs<float>(DataXToView(m_pDataSet->getData(i)->getX(index), xrange, view_size.X) - zero);
											if (m_pDataSet->getData(i)->getX(index) >= 0)
												x_pos += x;
											else
												x_neg -= x;
										}
									if (p.X >= x_neg && p.X < x_pos)
									{
										hovered_data = best;
										hovered_point = index;
										break;
									}
									break;
								}
							}
							else
							{
								float zero{ DataYToView(0, yrange, view_size.Y) }, y_pos, y_neg, y;
								float grid_step_x{ view_size.X / (float)best->getCount() }, bar_size{ grid_step_x * m_fBarSize }, half_bar_padding{ (grid_step_x - bar_size) * 0.5f };
								float x1{ -grid_step_x };
								for (int index = 0; index < best->getCount(); index++)
								{
									x1 += grid_step_x;
									if (p.X < x1 + half_bar_padding || p.X >= x1 + half_bar_padding + bar_size)
										continue;
									y_pos = y_neg = zero;
									for (int i = 0; i < m_pDataSet->getDataCount(); i++)
										if (m_pDataSet->getData(i)->getCount() >= index - 1)
										{
											y = ntl::Abs<float>(DataYToView(m_pDataSet->getData(i)->getY(index), yrange, view_size.Y) - zero);
											if (m_pDataSet->getData(i)->getY(index) >= 0)
												y_pos -= y;
											else
												y_neg += y;
										}
									if (p.Y >= y_pos && p.Y < y_neg)
									{
										hovered_data = best;
										hovered_point = index;
										break;
									}
									break;
								}
							}
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
		void CStackedBarChart::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			RectF rect{ 0, 0, getWidth(), getHeight() };
			if (PrepareCanvas(renderer, &m_pCanvas, rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				RectF client{ getClientRect() };
				IFont *font{ getFont() };
				IPlatformFont *pf{ font ? font->getPlatformFont(renderer) : nullptr };
				RenderBackground(renderer, rect);
				if (!client.is_zero())
				{
					IChartData *best{ FindBestData() };
					PointF xrange{ m_sAutoRange.X ? m_sAutoXRange : m_sXRange }, yrange{ m_sAutoRange.Y ? m_sAutoYRange : m_sYRange };
					PointF grid_step{ m_sAutoGrid.X ? m_sAutoGridStep.X : m_sGridStep.X, m_sAutoGrid.Y ? m_sAutoGridStep.Y : m_sGridStep.Y };
					PointF view_size{ client.width(), client.height() };
					RenderAxesAndGridEx(renderer, client, xrange, yrange, grid_step, best, view_size);
					if (font && pf)
						RenderLabelsEx(renderer, client, font, pf, xrange, yrange, grid_step, best, view_size);
					RenderDataSetEx(renderer, client, xrange, yrange, best, view_size);
				}

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}

		void CStackedBarChart::RenderBackground(IRenderer *renderer, const RectF &rect)
		{
			if (m_cBackgroundGradient.getPointCount() >= 2)
				renderer->DrawGradient(rect, m_cBackgroundGradient);
			else if (m_sBackgroundColor.A > 0)
				renderer->DrawRectangle(rect, m_sBackgroundColor);
		}

		void CStackedBarChart::RenderAxesAndGridEx(IRenderer *renderer, const RectF &client, const PointF &xrange, const PointF &yrange, const PointF &grid_step, IChartData *best, const PointF &view_size)
		{
			// Vertical grid
			if (m_sShowGrid.X && m_sXGridColor.A > 0)
			{
				if (best && !m_bVertical)
				{
					float grid_step_x{ view_size.X / (float)best->getCount() }, x1{ 0 }, x2{ view_size.X };
					while (x1 <= x2)
					{
						float x{ client.Left + x1 };
						if (x >= client.Left && x < client.Right && (ntl::IsNotEqual<float>(x1, 0) || !m_sShowAxes.X))
							renderer->DrawLine(PointF{ x, client.Top }, PointF{ x, client.Bottom }, m_sXGridColor);
						x1 += grid_step_x;
					}
				}
				else
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
			}
			// Horizontal grid
			if (m_sShowGrid.Y && m_sYGridColor.A > 0)
			{
				if (best && m_bVertical)
				{
					float grid_step_y{ view_size.Y / (float)best->getCount() }, y1{ 0 }, y2{ view_size.Y };
					while (y1 <= y2)
					{
						float y{ client.Bottom - y1 };
						if (y >= client.Top && y < client.Bottom && (ntl::IsNotEqual<float>(y1, 0) || !m_sShowAxes.Y))
							renderer->DrawLine(PointF{ client.Left, y }, PointF{ client.Right, y }, m_sYGridColor);
						y1 += grid_step_y;
					}
				}
				else
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
			}
			// X-axis
			if (best && m_bVertical)
			{
				if (m_sShowAxes.X && m_sXAxisColor.A > 0)
				{
					float y{ client.Bottom };
					renderer->DrawLine(PointF{ client.Left, y }, PointF{ client.Right, y }, m_sXAxisColor);
				}
			}
			else
			{
				if (m_sShowAxes.X && yrange.X <= 0 && yrange.Y >= 0 && m_sXAxisColor.A > 0)
				{
					float y{ client.Bottom + yrange.X * client.height() / (yrange.Y - yrange.X) };
					renderer->DrawLine(PointF{ client.Left, y }, PointF{ client.Right, y }, m_sXAxisColor);
				}
			}
			// Y-axis
			if (best && !m_bVertical)
			{
				if (m_sShowAxes.Y && m_sYAxisColor.A > 0)
				{
					float x{ client.Left };
					renderer->DrawLine(PointF{ x, client.Top }, PointF{ x, client.Bottom }, m_sYAxisColor);
				}
			}
			else
			{
				if (m_sShowAxes.Y && xrange.X <= 0 && xrange.Y >= 0 && m_sYAxisColor.A > 0)
				{
					float x{ client.Left - xrange.X * client.width() / (xrange.Y - xrange.X) };
					renderer->DrawLine(PointF{ x, client.Top }, PointF{ x, client.Bottom }, m_sYAxisColor);
				}
			}
		}

		void CStackedBarChart::RenderLabelsEx(IRenderer *renderer, const RectF &client, IFont *font, IPlatformFont *pf, const PointF &xrange, const PointF &yrange, const PointF &grid_step, IChartData *best, const PointF &view_size)
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
					if (best && !m_bVertical)
					{
						float x1{ 0 }, grid_step_x{ view_size.X / (float)best->getCount() };
						for (int index = 0; index < best->getCount(); index++)
						{
							float x{ client.Left + x1 };
							label = best->getLabel(index);
							if (!label.empty())
							{
								size = pf->getStringSize(label, font->Distance);
								renderer
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(x - (size.X - grid_step_x) * 0.5f), std::round(m_bXLabelsAtTop ? (m_sLabelPadding.Y - size.Y) : client.Bottom), 0))
									->DrawText(label, pf, font->Distance, color);
							}
							x1 += grid_step_x;
						}
					}
					else
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
			}
			if (m_sShowLabels.Y)
			{
				color = m_sYLabelsColor.A > 0 ? m_sYLabelsColor : font->Color;
				if (color.A > 0)
				{
					if (best && m_bVertical)
					{
						float y1{ 0 }, grid_step_y{ view_size.Y / (float)best->getCount() };
						for (int index = 0; index < best->getCount(); index++)
						{
							float y{ client.Bottom - y1 };
							label = best->getLabel(index);
							if (!label.empty())
							{
								size = pf->getStringSize(label, font->Distance);
								renderer
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(m_bYLabelsAtRight ? client.Right : (m_sLabelPadding.X - size.X)), std::round(y - (size.Y + grid_step_y) * 0.5f), 0))
									->DrawText(label, pf, font->Distance, color);
							}
							y1 += grid_step_y;
						}
					}
					else
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
		}

		void CStackedBarChart::RenderDataSetEx(IRenderer *renderer, const RectF &client, const PointF &xrange, const PointF &yrange, IChartData *best, const PointF &view_size)
		{
			if (best)
			{
				ITexture *target{ renderer->CreateTexture(ntl::Round<int>(client.width()), ntl::Round<int>(client.height()), 1, TextureFormat::RGBA, true) };
				if (target)
				{
					renderer
						->ActivateTarget(target)
						->Clear(Color{ 0, 0, 0, 0 });

					if (m_bVertical)
					{
						float zero{ DataXToView(0, xrange, view_size.X) }, x;
						RectF r_pos, r_neg;
						Color color;
						float grid_step_y{ view_size.Y / (float)best->getCount() }, bar_size{ grid_step_y * m_fBarSize }, y1{ 0 };
						float half_bar_padding{ (grid_step_y - bar_size) * 0.5f };
						for (int index = 0; index < best->getCount(); index++)
						{
							r_pos.Bottom = r_neg.Bottom = client.Bottom - y1 - half_bar_padding;
							r_pos.Top = r_neg.Top = r_pos.Bottom - bar_size;
							r_pos.Left = r_neg.Right = zero;
							for (int i = 0; i < m_pDataSet->getDataCount(); i++)
								if (m_pDataSet->getData(i)->getCount() >= index - 1)
								{
									x = ntl::Abs<float>(DataXToView(m_pDataSet->getData(i)->getX(index), xrange, view_size.X) - zero);
									if (m_pDataSet->getData(i)->getX(index) >= 0)
									{
										r_pos.Right = r_pos.Left + x;
										if (!r_pos.is_zero())
										{
											if (m_pHoveredData && index == m_iHoveredPoint)
												color = m_aActiveBackgroundColors[i % (int)m_aActiveBackgroundColors.size()];
											else
												color = m_aNormalBackgroundColors[i % (int)m_aNormalBackgroundColors.size()];
											renderer->DrawPolygon({ PointF{ r_pos.Left, r_pos.Top }, PointF{ r_pos.Right, r_pos.Top }, PointF{ r_pos.Right, r_pos.Bottom }, PointF{ r_pos.Left, r_pos.Bottom } }, color);
											r_pos.Left = r_pos.Right;
										}
									}
									else
									{
										r_neg.Left = r_neg.Right - x;
										if (!r_neg.is_zero())
										{
											if (m_pHoveredData && index == m_iHoveredPoint)
												color = m_aActiveBackgroundColors[i % (int)m_aActiveBackgroundColors.size()];
											else
												color = m_aNormalBackgroundColors[i % (int)m_aNormalBackgroundColors.size()];
											renderer->DrawPolygon({ PointF{ r_neg.Left, r_neg.Top }, PointF{ r_neg.Right, r_neg.Top }, PointF{ r_neg.Right, r_neg.Bottom }, PointF{ r_neg.Left, r_neg.Bottom } }, color);
											r_neg.Right = r_neg.Left;
										}
									}
								}
							y1 += grid_step_y;
						}
					}
					else
					{
						float zero{ DataYToView(0, yrange, view_size.Y) }, y;
						RectF r_pos, r_neg;
						Color color;
						float grid_step_x{ view_size.X / (float)best->getCount() }, bar_size{ grid_step_x * m_fBarSize }, x1{ 0 };
						float half_bar_padding{ (grid_step_x - bar_size) * 0.5f };
						for (int index = 0; index < best->getCount(); index++)
						{
							r_pos.Left = r_neg.Left = x1 + half_bar_padding;
							r_pos.Right = r_neg.Right = r_pos.Left + bar_size;
							r_pos.Bottom = r_neg.Top = zero;
							for (int i = 0; i < m_pDataSet->getDataCount(); i++)
								if (m_pDataSet->getData(i)->getCount() >= index - 1)
								{
									y = ntl::Abs<float>(DataYToView(m_pDataSet->getData(i)->getY(index), yrange, view_size.Y) - zero);
									if (m_pDataSet->getData(i)->getY(index) >= 0)
									{
										r_pos.Top = r_pos.Bottom - y;
										if (!r_pos.is_zero())
										{
											if (m_pHoveredData && index == m_iHoveredPoint)
												color = m_aActiveBackgroundColors[i % (int)m_aActiveBackgroundColors.size()];
											else
												color = m_aNormalBackgroundColors[i % (int)m_aNormalBackgroundColors.size()];
											renderer->DrawPolygon({ PointF{ r_pos.Left, r_pos.Top }, PointF{ r_pos.Right, r_pos.Top }, PointF{ r_pos.Right, r_pos.Bottom }, PointF{ r_pos.Left, r_pos.Bottom } }, color);
											r_pos.Bottom = r_pos.Top;
										}
									}
									else
									{
										r_neg.Bottom = r_neg.Top + y;
										if (!r_neg.is_zero())
										{
											if (m_pHoveredData && index == m_iHoveredPoint)
												color = m_aActiveBackgroundColors[i % (int)m_aActiveBackgroundColors.size()];
											else
												color = m_aNormalBackgroundColors[i % (int)m_aNormalBackgroundColors.size()];
											renderer->DrawPolygon({ PointF{ r_neg.Left, r_neg.Top }, PointF{ r_neg.Right, r_neg.Top }, PointF{ r_neg.Right, r_neg.Bottom }, PointF{ r_neg.Left, r_neg.Bottom } }, color);
											r_neg.Top = r_neg.Bottom;
										}
									}
								}
							x1 += grid_step_x;
						}
					}

					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivateTarget(m_pCanvas)
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(client.Left, client.Top, 0))
						->DrawImage(target, 1);
					target->Release();
				}
			}
		}

		void CStackedBarChart::RenderData(IRenderer *renderer, const RectF &client, IChartData *data, const int index, ITexture *target, const PointF &xrange, const PointF &yrange)
		{
			// Unused
		}
	#pragma endregion
	}
}