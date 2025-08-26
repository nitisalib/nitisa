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
		CPieChart::CPieChart():
			CCustomRadialChart(L"PieChart", true, true, false, false, false, false),
			m_fBorderWidth{ 1 },
			m_fQuality{ 0.2f },
			m_bRestartColors{ true },
			m_aNormalColors{
				Color{ 255, 123, 151, 128 },
				Color{ 73, 171, 236, 128 },
				Color{ 255, 208, 98, 128 },
				Color{ 88, 255, 196, 128 },
				Color{ 220, 20, 60, 128 },
				Color{ 160, 113, 255, 128 },
				Color{ 205, 206, 210, 128 },
				Color{ 255, 166, 77, 128 } },
			m_aActiveColors{
				Color{ 255, 123, 151, 156 },
				Color{ 73, 171, 236, 156 },
				Color{ 255, 208, 98, 156 },
				Color{ 88, 255, 196, 156 },
				Color{ 220, 20, 60, 156 },
				Color{ 160, 113, 255, 156 },
				Color{ 205, 206, 210, 156 },
				Color{ 255, 166, 77, 156 } },
			m_aNormalBorderColors{ Color{ 255, 255, 255, 255 } },
			m_aActiveBorderColors{ Color{ 255, 255, 255, 255 } }
		{
			setSize(PointF{ 210, 210 });
		}

		CPieChart::CPieChart(IForm *parent) :CPieChart()
		{
			setForm(parent);
		}

		CPieChart::CPieChart(IControl *parent) : CPieChart()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IControl setters
		bool CPieChart::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_fBorderWidth *= avg;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		float CPieChart::getBorderWidth() const
		{
			return m_fBorderWidth;
		}

		float CPieChart::getQuality() const
		{
			return m_fQuality;
		}

		bool CPieChart::isRestartColors() const
		{
			return m_bRestartColors;
		}

		const ColorArray &CPieChart::getNormalColors() const
		{
			return m_aNormalColors;
		}

		const ColorArray &CPieChart::getActiveColors() const
		{
			return m_aActiveColors;
		}

		const ColorArray &CPieChart::getNormalBorderColors() const
		{
			return m_aNormalBorderColors;
		}

		const ColorArray &CPieChart::getActiveBorderColors() const
		{
			return m_aActiveBorderColors;
		}
	#pragma endregion

	#pragma region Setters
		bool CPieChart::setBorderWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fBorderWidth))
			{
				m_fBorderWidth = value;
				if (m_pDataSet && m_pDataSet->getDataCount() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPieChart::setQuality(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsLessOrEqual<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fQuality))
			{
				m_fQuality = value;
				if (m_pDataSet && m_pDataSet->getDataCount() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPieChart::setRestartColors(const bool value)
		{
			if (value != m_bRestartColors)
			{
				m_bRestartColors = value;
				if (m_pDataSet && m_pDataSet->getDataCount() > 0)
				{
					CCustomRadialChart::UpdateHoveredPoint();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPieChart::setNormalColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aNormalColors = values;
				if (m_pDataSet && m_pDataSet->getDataCount() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPieChart::setActiveColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aActiveColors = values;
				if (m_pDataSet && m_pDataSet->getDataCount() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPieChart::setNormalBorderColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aNormalBorderColors = values;
				if (m_pDataSet && m_pDataSet->getDataCount() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPieChart::setActiveBorderColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aActiveBorderColors = values;
				if (m_pDataSet && m_pDataSet->getDataCount() > 0)
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
		void CPieChart::UpdateFromStyle(IStyle *style)
		{
			CCustomRadialChart::UpdateFromStyle(style);
			Color vc;
			int index;
			index = 0;
			while (style->getOption(m_sClassName + L".NormalColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aNormalColors.clear();
				m_aNormalColors.push_back(vc);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".ActiveColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aActiveColors.clear();
				m_aActiveColors.push_back(vc);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".NormalBorderColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aNormalBorderColors.clear();
				m_aNormalBorderColors.push_back(vc);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".ActiveBorderColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aActiveBorderColors.clear();
				m_aActiveBorderColors.push_back(vc);
				index++;
			}
		}

		bool CPieChart::UpdateHoveredPoint(const PointF &position)
		{
			IChartData *hovered_data{ nullptr };
			int hovered_point{ -1 };
			if (m_pDataSet && m_pDataSet->getDataCount() > 0 && isEnabled(true))
			{
				RectF client{ getClientRect() };
				if (!client.is_zero())
				{
					PointF p{ FormToLocal(position) };
					if (p.X >= client.Left && p.X < client.Right && p.Y >= client.Top && p.Y < client.Bottom)
					{
						p.X -= client.Left;
						p.Y -= client.Top;
						PointF center{ (client.Left + client.Right) * 0.5f, (client.Top + client.Bottom) * 0.5f };
						float radius{ ntl::Min<float>(client.width(), client.height()) * 0.5f };
						float dr{ radius / (float)m_pDataSet->getDataCount() }, r_outer, r_inner, sum, a1, a2, a;
						float d{ (p.X - center.X) * (p.X - center.X) + (p.Y - center.Y) * (p.Y - center.Y) };
						if (d < radius * radius)
						{
							for (int i = 0; i < m_pDataSet->getDataCount(); i++)
							{
								if (m_pDataSet->getData(i)->getCount() > 0)
								{
									r_outer = radius - (float)i * dr;
									r_inner = radius - float(i + 1) * dr;
									if (d < r_outer * r_outer && d >= r_inner * r_inner)
									{
										if (m_pDataSet->getData(i)->getCount() == 1)
										{
											hovered_data = m_pDataSet->getData(i);
											hovered_point = 0;
											break;
										}
										sum = 0;
										for (int j = 0; j < m_pDataSet->getData(i)->getCount(); j++)
											if (m_pDataSet->getData(i)->getY(j) >= 0)
												sum += m_pDataSet->getData(i)->getY(j);
										if (ntl::IsEqual<float>(sum, 0))
											sum = (float)m_pDataSet->getData(i)->getCount();
										a1 = 0;
										for (int j = 0; j < m_pDataSet->getData(i)->getCount(); j++)
											if (m_pDataSet->getData(i)->getY(j) >= 0)
											{

												a2 = a1 + m_pDataSet->getData(i)->getY(j) / sum * ntl::DoublePi<float>;
												a = Angle(p.X, p.Y, center.X, center.Y) + ntl::HalfPi<float>;
												if (a >= ntl::DoublePi<float>)
													a -= ntl::DoublePi<float>;
												if (a >= a1 && a < a2)
												{
													hovered_data = m_pDataSet->getData(i);
													hovered_point = j;
													break;
												}
												a1 = a2;
											}
									}
								}
								if (hovered_data)
									break;
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
		void CPieChart::RenderDataSet(IRenderer *renderer, const RectF &rect)
		{
			if (m_pDataSet && m_pDataSet->getDataCount() > 0)
			{
				PointF center{ (rect.Left + rect.Right) * 0.5f, (rect.Top + rect.Bottom) * 0.5f };
				float radius{ ntl::Min<float>(rect.width(), rect.height()) * 0.5f };
				float dr{ radius / (float)m_pDataSet->getDataCount() }, r_outer, r_inner;
				int color_index{ 0 };
				for (int i = 0; i < m_pDataSet->getDataCount(); i++)
					if (m_pDataSet->getData(i)->getCount() > 0)
					{
						r_outer = radius - (float)i * dr;
						r_inner = radius - float(i + 1) * dr;
						RenderData(renderer, center, r_outer, r_inner, m_pDataSet->getData(i), color_index);
						if (ntl::IsGreater<float>(m_fBorderWidth, 0))
							RenderBorders(renderer, center, r_outer, r_inner, m_pDataSet->getData(i), color_index);
						if (!m_bRestartColors)
							color_index += m_pDataSet->getData(i)->getCount();
					}
			}
		}

		void CPieChart::RenderData(IRenderer *renderer, const PointF &center, const float r_outer, const float r_inner, IChartData *data, const int color_index)
		{
			if (data->getCount() == 1)
			{
				Color color{
					(m_pHoveredData == data && m_iHoveredPoint == 0) ?
					m_aActiveColors[color_index % (int)m_aActiveColors.size()] :
					m_aNormalColors[color_index % (int)m_aNormalColors.size()] };
				Color border_color{
					(m_pHoveredData == data && m_iHoveredPoint == 0) ?
					m_aActiveBorderColors[color_index % (int)m_aActiveBorderColors.size()] :
					m_aNormalBorderColors[color_index % (int)m_aNormalBorderColors.size()] };
				if (color.A > 0 || (ntl::IsGreater<float>(m_fBorderWidth, 0) && border_color.A > 0))
				{
					Gradient g;
					g.setType(GradientType::Circle);
					if (ntl::IsEqual<float>(m_fBorderWidth, 0))
						g.setPoints(Color1DArray{
						Color1D{ 0, Color{ 0, 0, 0, 0 } },
						Color1D{ r_inner / r_outer, Color{ 0, 0, 0, 0 } },
						Color1D{ r_inner / r_outer + 0.000001f, color },
						Color1D{ 1, color } });
					else if (r_outer - r_inner <= 2.0 * m_fBorderWidth)
						g.setPoints(Color1DArray{
						Color1D{ 0, Color{ 0, 0, 0, 0 } },
						Color1D{ r_inner / r_outer, Color{ 0, 0, 0, 0 } },
						Color1D{ r_inner / r_outer + 0.000001f, border_color },
						Color1D{ 1.0, border_color } });
					else
						g.setPoints(Color1DArray{
							Color1D{ 0, Color{ 0, 0, 0, 0 } },
							Color1D{ r_inner / r_outer + 0.000001f, Color{ 0, 0, 0, 0 } },
							Color1D{ r_inner / r_outer + 0.000002f, border_color },
							Color1D{ (r_inner + m_fBorderWidth) / r_outer, border_color },
							Color1D{ (r_inner + m_fBorderWidth) / r_outer + 0.000001f, color },
							Color1D{ (r_outer - m_fBorderWidth) / r_outer - 0.000002f, color },
							Color1D{ (r_outer - m_fBorderWidth) / r_outer - 0.000001f, border_color },
							Color1D{ 1, border_color } });
					renderer->DrawGradient(RectF{ center.X - r_outer, center.Y - r_outer, center.X + r_outer, center.Y + r_outer }, g);
				}
			}
			else
			{
				float sum{ 0 };
				for (int i = 0; i < data->getCount(); i++)
					sum += data->getY(i);
				if (ntl::IsEqual<float>(sum, 0))
					sum = (float)data->getCount();
				float a1{ 0 }, a2, a, circle_length{ ntl::DoublePi<float> * r_outer }, da;
				int triangle_count;
				std::vector<PointF> polygon;
				Color color;
				bool is_central{ data == m_pDataSet->getData(m_pDataSet->getDataCount() - 1) };
				for (int i = 0; i < data->getCount(); i++)
				{
					a = data->getY(i) / sum;
					if (a > 0)
					{
						a2 = a1 + a * ntl::DoublePi<float>;
						color = (m_pHoveredData == data && m_iHoveredPoint == i) ? m_aActiveColors[(color_index + i) % (int)m_aActiveColors.size()] : m_aNormalColors[(color_index + i) % (int)m_aNormalColors.size()];
						if (color.A > 0)
						{
							triangle_count = ntl::Clamp<int>(ntl::Round<int>(circle_length * a * m_fQuality), 1, MaxPolygonPoints - 2);
							da = a * ntl::DoublePi<float> / (float)triangle_count;
							if (is_central)
							{
								polygon.resize(triangle_count + 2);
								polygon[0] = center;
								polygon[1] = PointF{ center.X + std::sin(a1) * r_outer, center.Y - std::cos(a1) * r_outer };
								for (int j = 0; j < triangle_count; j++)
									polygon[j + 2] = PointF{ center.X + std::sin(a1 + da * float(j + 1)) * r_outer, center.Y - std::cos(a1 + da * float(j + 1)) * r_outer };
								renderer->DrawPolygon(polygon, color);
							}
							else
							{
								polygon.resize(4);
								for (int j = 0; j < triangle_count; j++)
								{
									polygon[0] = PointF{ center.X + std::sin(a1 + da * (float)j) * r_inner, center.Y - std::cos(a1 + da * (float)j) * r_inner };
									polygon[1] = PointF{ center.X + std::sin(a1 + da * (float)j) * r_outer, center.Y - std::cos(a1 + da * (float)j) * r_outer };
									polygon[2] = PointF{ center.X + std::sin(a1 + da * float(j + 1)) * r_outer, center.Y - std::cos(a1 + da * float(j + 1)) * r_outer };
									polygon[3] = PointF{ center.X + std::sin(a1 + da * float(j + 1)) * r_inner, center.Y - std::cos(a1 + da * float(j + 1)) * r_inner };
									renderer->DrawPolygon(polygon, color);
								}
							}
						}
						a1 = a2;
					}
				}
			}
		}

		void CPieChart::RenderBorders(IRenderer *renderer, const PointF &center, const float r_outer, const float r_inner, IChartData *data, const int color_index)
		{
			if (data->getCount() > 1)
			{
				float sum{ 0 };
				for (int i = 0; i < data->getCount(); i++)
					sum += data->getY(i);
				if (ntl::IsEqual<float>(sum, 0))
					sum = (float)data->getCount();
				float a1{ 0 }, a2, a, circle_length{ ntl::DoublePi<float> * r_outer }, da;
				Color border_color;
				int line_count;
				std::vector<PointF> line_points, polygon;
				std::vector<std::pair<PointF, PointF>> polygon_points;
				bool is_central{ data == m_pDataSet->getData(m_pDataSet->getDataCount() - 1) };
				polygon.resize(4);
				for (int i = 0; i < data->getCount(); i++)
				{
					a = data->getY(i) / sum;
					if (a > 0)
					{
						a2 = a1 + a * ntl::DoublePi<float>;
						border_color = (m_pHoveredData == data && m_iHoveredPoint == i) ? m_aActiveBorderColors[(color_index + i) % (int)m_aActiveBorderColors.size()] : m_aNormalBorderColors[(color_index + i) % (int)m_aNormalBorderColors.size()];
						if (border_color.A > 0)
						{
							line_count = ntl::Clamp<int>(ntl::Round<int>(circle_length * a * m_fQuality), 1, MaxPolygonPoints - 2);
							da = (a2 - a1) / (float)line_count;
							if (is_central)
							{
								line_points.resize(line_count + 2);
								for (int j = 0; j < line_count; j++)
									line_points[j] = PointF{ center.X + std::sin(a1 + da * (float)j) * r_outer, center.Y - std::cos(a1 + da * (float)j) * r_outer };
								line_points[line_count] = PointF{ center.X + std::sin(a2) * r_outer, center.Y - std::cos(a2) * r_outer };
								line_points[line_count + 1] = center;
								MakeThickPath(line_points, true, -m_fBorderWidth, false, polygon_points);
								for (size_t j = 0; j < polygon_points.size(); j++)
								{
									if (j == 0)
									{
										polygon[0] = polygon_points[polygon_points.size() - 1].first;
										polygon[1] = polygon_points[j].first;
										polygon[2] = polygon_points[j].second;
										polygon[3] = polygon_points[polygon_points.size() - 1].second;
									}
									else
									{
										polygon[0] = polygon_points[j - 1].first;
										polygon[1] = polygon_points[j].first;
										polygon[2] = polygon_points[j].second;
										polygon[3] = polygon_points[j - 1].second;
									}
									renderer->DrawPolygon(polygon, border_color);
								}
							}
							else
							{
								for (int j = 0; j < line_count; j++)
								{
									polygon[0] = PointF{ center.X + std::sin(a1 + da * (float)j) * (r_outer - m_fBorderWidth), center.Y - std::cos(a1 + da * (float)j) * (r_outer - m_fBorderWidth) };
									polygon[1] = PointF{ center.X + std::sin(a1 + da * (float)j) * r_outer, center.Y - std::cos(a1 + da * (float)j) * r_outer };
									polygon[2] = PointF{ center.X + std::sin(a1 + da * float(j + 1)) * r_outer, center.Y - std::cos(a1 + da * float(j + 1)) * r_outer };
									polygon[3] = PointF{ center.X + std::sin(a1 + da * float(j + 1)) * (r_outer - m_fBorderWidth), center.Y - std::cos(a1 + da * float(j + 1)) * (r_outer - m_fBorderWidth) };
									renderer->DrawPolygon(polygon, border_color);

									polygon[0] = PointF{ center.X + std::sin(a1 + da * (float)j) * r_inner, center.Y - std::cos(a1 + da * (float)j) * r_inner };
									polygon[1] = PointF{ center.X + std::sin(a1 + da * (float)j) * (r_inner + m_fBorderWidth), center.Y - std::cos(a1 + da * (float)j) * (r_inner + m_fBorderWidth) };
									polygon[2] = PointF{ center.X + std::sin(a1 + da * float(j + 1)) * (r_inner + m_fBorderWidth), center.Y - std::cos(a1 + da * float(j + 1)) * (r_inner + m_fBorderWidth) };
									polygon[3] = PointF{ center.X + std::sin(a1 + da * float(j + 1)) * r_inner, center.Y - std::cos(a1 + da * float(j + 1)) * r_inner };
									renderer->DrawPolygon(polygon, border_color);
								}

								line_points.resize(2);
								line_points[0] = PointF{ center.X + std::sin(a1) * (r_inner + m_fBorderWidth), center.Y - std::cos(a1) * (r_inner + m_fBorderWidth) };
								line_points[1] = PointF{ center.X + std::sin(a1) * (r_outer - m_fBorderWidth), center.Y - std::cos(a1) * (r_outer - m_fBorderWidth) };
								MakeThickPath(line_points, false, -m_fBorderWidth, false, polygon_points);
								polygon[0] = polygon_points[0].first;
								polygon[1] = polygon_points[1].first;
								polygon[2] = polygon_points[1].second;
								polygon[3] = polygon_points[0].second;
								renderer->DrawPolygon(polygon, border_color);

								line_points[0] = PointF{ center.X + std::sin(a2) * (r_outer - m_fBorderWidth), center.Y - std::cos(a2) * (r_outer - m_fBorderWidth) };
								line_points[1] = PointF{ center.X + std::sin(a2) * (r_inner + m_fBorderWidth), center.Y - std::cos(a2) * (r_inner + m_fBorderWidth) };
								MakeThickPath(line_points, false, -m_fBorderWidth, false, polygon_points);
								polygon[0] = polygon_points[0].first;
								polygon[1] = polygon_points[1].first;
								polygon[2] = polygon_points[1].second;
								polygon[3] = polygon_points[0].second;
								renderer->DrawPolygon(polygon, border_color);
							}
						}
						a1 = a2;
					}
				}
			}
		}
	#pragma endregion
	}
}