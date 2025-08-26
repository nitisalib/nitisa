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
		CMultiBarChart::CMultiBarChart() :
			CCustomCartesianChart(L"MultiBarChart", true, true, false, false, false, false),
			m_aDrawNormalBorders{ true },
			m_aDrawActiveBorders{ true },
			m_aDrawNormalBackgrounds{ true },
			m_aDrawActiveBackgrounds{ true },
			m_aNormalBorderWidthes{ 2 },
			m_aActiveBorderWidthes{ 2 },
			m_aNormalBorderColors{
				Color{ 255, 123, 151, 200 },
				Color{ 73, 171, 236, 200 },
				Color{ 255, 208, 98, 200 },
				Color{ 88, 255, 196, 200 },
				Color{ 220, 20, 60, 200 },
				Color{ 160, 113, 255, 200 },
				Color{ 205, 206, 210, 200 },
				Color{ 255, 166, 77, 200 } },
			m_aActiveBorderColors{
				Color{ 255, 123, 151, 255 },
				Color{ 73, 171, 236, 255 },
				Color{ 255, 208, 98, 255 },
				Color{ 88, 255, 196, 255 },
				Color{ 220, 20, 60, 255 },
				Color{ 160, 113, 255, 255 },
				Color{ 205, 206, 210, 255 },
				Color{ 255, 166, 77, 255 } },
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
			m_fContentSize{ 0.95f },
			m_fBarDistance{ 0.1f }
		{
			setSize(PointF{ 370, 210 });
		}

		CMultiBarChart::CMultiBarChart(IForm *parent) : CMultiBarChart()
		{
			setForm(parent);
		}

		CMultiBarChart::CMultiBarChart(IControl *parent) : CMultiBarChart()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IControl setters
		bool CMultiBarChart::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CCustomCartesianChart::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				for (auto &value : m_aNormalBorderWidthes)
					value *= avg;
				for (auto &value : m_aActiveBorderWidthes)
					value *= avg;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		bool CMultiBarChart::isVertical() const
		{
			return m_bVertical;
		}

		float CMultiBarChart::getContentSize() const
		{
			return m_fContentSize;
		}

		float CMultiBarChart::getBarDistance() const
		{
			return m_fBarDistance;
		}

		const BoolArray &CMultiBarChart::getDrawNormalBorders() const
		{
			return m_aDrawNormalBorders;
		}

		const BoolArray &CMultiBarChart::getDrawActiveBorders() const
		{
			return m_aDrawActiveBorders;
		}

		const BoolArray &CMultiBarChart::getDrawNormalBackgrounds() const
		{
			return m_aDrawNormalBackgrounds;
		}

		const BoolArray &CMultiBarChart::getDrawActiveBackgrounds() const
		{
			return m_aDrawActiveBackgrounds;
		}

		const FloatArray &CMultiBarChart::getNormalBorderWidthes() const
		{
			return m_aNormalBorderWidthes;
		}

		const FloatArray &CMultiBarChart::getActiveBorderWidthes() const
		{
			return m_aActiveBorderWidthes;
		}

		const ColorArray &CMultiBarChart::getNormalBorderColors() const
		{
			return m_aNormalBorderColors;
		}

		const ColorArray &CMultiBarChart::getActiveBorderColors() const
		{
			return m_aActiveBorderColors;
		}

		const ColorArray &CMultiBarChart::getNormalBackgroundColors() const
		{
			return m_aNormalBackgroundColors;
		}

		const ColorArray &CMultiBarChart::getActiveBackgroundColors() const
		{
			return m_aActiveBackgroundColors;
		}
	#pragma endregion

	#pragma region Setters
		bool CMultiBarChart::setVertical(const bool value)
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

		bool CMultiBarChart::setContentSize(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsLessOrEqual<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fContentSize))
			{
				m_fContentSize = value;
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

		bool CMultiBarChart::setBarDistance(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsLess<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fBarDistance))
			{
				m_fBarDistance = value;
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

		bool CMultiBarChart::setDrawNormalBorders(const BoolArray &values)
		{
			if (values.size() > 0)
			{
				m_aDrawNormalBorders = values;
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

		bool CMultiBarChart::setDrawActiveBorders(const BoolArray &values)
		{
			if (values.size() > 0)
			{
				m_aDrawActiveBorders = values;
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

		bool CMultiBarChart::setDrawNormalBackgrounds(const BoolArray &values)
		{
			if (values.size() > 0)
			{
				m_aDrawNormalBackgrounds = values;
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

		bool CMultiBarChart::setDrawActiveBackgrounds(const BoolArray &values)
		{
			if (values.size() > 0)
			{
				m_aDrawActiveBackgrounds = values;
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

		bool CMultiBarChart::setNormalBorderWidthes(const FloatArray &values)
		{
			if (values.size() > 0)
			{
				for (auto v : values)
					if (ntl::IsLess<float>(v, 0))
						return false;
				m_aNormalBorderWidthes = values;
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

		bool CMultiBarChart::setActiveBorderWidthes(const FloatArray &values)
		{
			if (values.size() > 0)
			{
				for (auto v : values)
					if (ntl::IsLess<float>(v, 0))
						return false;
				m_aActiveBorderWidthes = values;
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

		bool CMultiBarChart::setNormalBorderColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aNormalBorderColors = values;
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

		bool CMultiBarChart::setActiveBorderColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aActiveBorderColors = values;
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

		bool CMultiBarChart::setNormalBackgroundColors(const ColorArray &values)
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

		bool CMultiBarChart::setActiveBackgroundColors(const ColorArray &values)
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
		void CMultiBarChart::UpdateFromStyle(IStyle *style)
		{
			CCustomCartesianChart::UpdateFromStyle(style);
			bool vb;
			int index;
			float vf;
			Color vc;
			index = 0;
			while (style->getOption(m_sClassName + L".DrawNormalBorders[" + ToString(index) + L"]", vb))
			{
				if (index == 0)
					m_aDrawNormalBorders.clear();
				m_aDrawNormalBorders.push_back(vb);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".DrawActiveBorders[" + ToString(index) + L"]", vb))
			{
				if (index == 0)
					m_aDrawActiveBorders.clear();
				m_aDrawActiveBorders.push_back(vb);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".DrawNormalBackgrounds[" + ToString(index) + L"]", vb))
			{
				if (index == 0)
					m_aDrawNormalBackgrounds.clear();
				m_aDrawNormalBackgrounds.push_back(vb);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".DrawActiveBackgrounds[" + ToString(index) + L"]", vb))
			{
				if (index == 0)
					m_aDrawActiveBackgrounds.clear();
				m_aDrawActiveBackgrounds.push_back(vb);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".NormalBorderWidthes[" + ToString(index) + L"]", vf))
			{
				if (index == 0)
					m_aNormalBorderWidthes.clear();
				m_aNormalBorderWidthes.push_back(vf);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".ActiveBorderWidthes[" + ToString(index) + L"]", vf))
			{
				if (index == 0)
					m_aActiveBorderWidthes.clear();
				m_aActiveBorderWidthes.push_back(vf);
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

		IChartData *CMultiBarChart::FindBestData() const
		{
			IChartData *result{ nullptr };
			if (m_pDataSet)
				for (int i = 0; i < m_pDataSet->getDataCount(); i++)
					if (m_pDataSet->getData(i)->getCount() > 0 && (!result || m_pDataSet->getData(i)->getCount() > result->getCount()))
						result = m_pDataSet->getData(i);
			return result;
		}

		bool CMultiBarChart::UpdateHoveredPoint(const PointF &position)
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
							if (m_bVertical)
							{
								PointF xrange{ m_sAutoRange.X ? m_sAutoXRange : m_sXRange };
								float zero{ DataXToView(0, xrange, view_size.X) };
								float grid_step_y{ view_size.Y / (float)best->getCount() }, content_size{ grid_step_y * m_fContentSize }, bar_size{ content_size / (float)m_pDataSet->getDataCount() };
								float bar_half_padding{ bar_size * m_fBarDistance * 0.5f }, content_half_padding{ (grid_step_y - content_size) * 0.5f }, real_bar_size{ bar_size - bar_half_padding * 2 };
								float left_disp{ content_half_padding + bar_half_padding };
								float y1{ 0 };
								for (int index = 0; index < best->getCount(); index++)
								{
									for (int i = 0; i < m_pDataSet->getDataCount(); i++)
										if (m_pDataSet->getData(i)->getCount() >= index - 1)
										{
											RectF r;
											r.Left = DataXToView(m_pDataSet->getData(i)->getX(index), xrange, view_size.X);
											r.Right = zero;
											r.Bottom = client.Bottom - y1 - left_disp - bar_size * (float)i;
											r.Top = r.Bottom - real_bar_size;
											if (r.Right < r.Left)
												ntl::Swap<float>(r.Right, r.Left);
											if (p.X >= r.Left && p.X < r.Right && p.Y >= r.Top && p.Y < r.Bottom)
											{
												hovered_data = m_pDataSet->getData(i);
												hovered_point = index;
												break;
											}
										}
									if (hovered_data)
										break;
									y1 += grid_step_y;
								}
							}
							else
							{
								PointF yrange{ m_sAutoRange.Y ? m_sAutoYRange : m_sYRange };
								float zero{ DataYToView(0, yrange, view_size.Y) };
								float grid_step_x{ view_size.X / (float)best->getCount() }, content_size{ grid_step_x * m_fContentSize }, bar_size{ content_size / (float)m_pDataSet->getDataCount() };
								float bar_half_padding{ bar_size * m_fBarDistance * 0.5f }, content_half_padding{ (grid_step_x - content_size) * 0.5f }, real_bar_size{ bar_size - bar_half_padding * 2 };
								float left_disp{ content_half_padding + bar_half_padding };
								float x1{ 0 };
								for (int index = 0; index < best->getCount(); index++)
								{
									for (int i = 0; i < m_pDataSet->getDataCount(); i++)
										if (m_pDataSet->getData(i)->getCount() >= index - 1)
										{
											RectF r;
											r.Left = x1 + left_disp + bar_size * (float)i;
											r.Right = r.Left + real_bar_size;
											r.Top = DataYToView(m_pDataSet->getData(i)->getY(index), yrange, view_size.Y);
											r.Bottom = zero;
											if (r.Bottom < r.Top)
												ntl::Swap<float>(r.Top, r.Bottom);
											if (p.X >= r.Left && p.X < r.Right && p.Y >= r.Top && p.Y < r.Bottom)
											{
												hovered_data = m_pDataSet->getData(i);
												hovered_point = index;
												break;
											}
										}
									if (hovered_data)
										break;
									x1 += grid_step_x;
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
		void CMultiBarChart::Render()
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

		void CMultiBarChart::RenderBackground(IRenderer *renderer, const RectF &rect)
		{
			if (m_cBackgroundGradient.getPointCount() >= 2)
				renderer->DrawGradient(rect, m_cBackgroundGradient);
			else if (m_sBackgroundColor.A > 0)
				renderer->DrawRectangle(rect, m_sBackgroundColor);
		}

		void CMultiBarChart::RenderAxesAndGridEx(IRenderer *renderer, const RectF &client, const PointF &xrange, const PointF &yrange, const PointF &grid_step, IChartData *best, const PointF &view_size)
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

		void CMultiBarChart::RenderLabelsEx(IRenderer *renderer, const RectF &client, IFont *font, IPlatformFont *pf, const PointF &xrange, const PointF &yrange, const PointF &grid_step, IChartData *best, const PointF &view_size)
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

		void CMultiBarChart::RenderDataSetEx(IRenderer *renderer, const RectF &client, const PointF &xrange, const PointF &yrange, IChartData *best, const PointF &view_size)
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
						float grid_step_y{ view_size.Y / (float)best->getCount() }, content_size{ grid_step_y * m_fContentSize }, bar_size{ content_size / (float)m_pDataSet->getDataCount() };
						float bar_half_padding{ bar_size * m_fBarDistance * 0.5f }, content_half_padding{ (grid_step_y - content_size) * 0.5f }, real_bar_size{ bar_size - bar_half_padding * 2 };
						float left_disp{ content_half_padding + bar_half_padding };
						float y1{ 0 }, zero{ DataXToView(0, xrange, view_size.X) };
						RectF r;
						RectF borders;
						bool draw_border, draw_background;
						Color border_color, background_color;
						float border_width;
						BlockColors colors{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
						for (int index = 0; index < best->getCount(); index++)
						{
							for (int i = 0; i < m_pDataSet->getDataCount(); i++)
								if (m_pDataSet->getData(i)->getCount() >= index - 1)
								{
									r.Bottom = client.Bottom - y1 - left_disp - bar_size * (float)i;
									r.Top = r.Bottom - real_bar_size;
									r.Left = DataXToView(m_pDataSet->getData(i)->getX(index), xrange, view_size.X);
									r.Right = zero;
									if (m_pDataSet->getData(i) == m_pHoveredData && index == m_iHoveredPoint)
									{
										draw_border = m_aDrawActiveBorders[i % (int)m_aDrawActiveBorders.size()];
										draw_background = m_aDrawActiveBackgrounds[i % (int)m_aDrawActiveBackgrounds.size()];
										border_color = m_aActiveBorderColors[i % (int)m_aActiveBorderColors.size()];
										background_color = m_aActiveBackgroundColors[i % (int)m_aActiveBackgroundColors.size()];
										border_width = m_aActiveBorderWidthes[i % (int)m_aActiveBorderWidthes.size()];
									}
									else
									{
										draw_border = m_aDrawNormalBorders[i % (int)m_aDrawNormalBorders.size()];
										draw_background = m_aDrawNormalBackgrounds[i % (int)m_aDrawNormalBackgrounds.size()];
										border_color = m_aNormalBorderColors[i % (int)m_aNormalBorderColors.size()];
										background_color = m_aNormalBackgroundColors[i % (int)m_aNormalBackgroundColors.size()];
										border_width = m_aNormalBorderWidthes[i % (int)m_aNormalBorderWidthes.size()];
									}
									if (draw_border && border_color.A > 0)
									{
										colors[0] = colors[1] = colors[2] = colors[3] = border_color;
										colors[4] = draw_background ? background_color : Color{ 0, 0, 0, 0 };
										borders.Left = borders.Top = borders.Bottom = border_width;
										borders.Right = 0;
										if (r.Right < r.Left)
										{
											ntl::Swap<float>(r.Right, r.Left);
											ntl::Swap<float>(borders.Left, borders.Right);
										}
										renderer->DrawBlock(r, borders, RectF{ 0, 0, 0, 0 }, colors);
									}
									else if (draw_background && background_color.A > 0)
									{
										if (r.Right < r.Left)
											ntl::Swap<float>(r.Right, r.Left);
										renderer->DrawPolygon({ PointF{ r.Left, r.Top }, PointF{ r.Right, r.Top }, PointF{ r.Right, r.Bottom }, PointF{ r.Left, r.Bottom } }, background_color);
									}
								}
							y1 += grid_step_y;
						}
					}
					else
					{
						float grid_step_x{ view_size.X / (float)best->getCount() }, content_size{ grid_step_x * m_fContentSize }, bar_size{ content_size / (float)m_pDataSet->getDataCount() };
						float bar_half_padding{ bar_size * m_fBarDistance * 0.5f }, content_half_padding{ (grid_step_x - content_size) * 0.5f }, real_bar_size{ bar_size - bar_half_padding * 2 };
						float left_disp{ content_half_padding + bar_half_padding };
						float x1{ 0 }, zero{ DataYToView(0, yrange, view_size.Y) };
						RectF r;
						RectF borders;
						bool draw_border, draw_background;
						Color border_color, background_color;
						float border_width;
						BlockColors colors{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
						for (int index = 0; index < best->getCount(); index++)
						{
							for (int i = 0; i < m_pDataSet->getDataCount(); i++)
								if (m_pDataSet->getData(i)->getCount() >= index - 1)
								{
									r.Left = x1 + left_disp + bar_size * (float)i;
									r.Right = r.Left + real_bar_size;
									r.Top = DataYToView(m_pDataSet->getData(i)->getY(index), yrange, view_size.Y);
									r.Bottom = zero;
									if (m_pDataSet->getData(i) == m_pHoveredData && index == m_iHoveredPoint)
									{
										draw_border = m_aDrawActiveBorders[i % (int)m_aDrawActiveBorders.size()];
										draw_background = m_aDrawActiveBackgrounds[i % (int)m_aDrawActiveBackgrounds.size()];
										border_color = m_aActiveBorderColors[i % (int)m_aActiveBorderColors.size()];
										background_color = m_aActiveBackgroundColors[i % (int)m_aActiveBackgroundColors.size()];
										border_width = m_aActiveBorderWidthes[i % (int)m_aActiveBorderWidthes.size()];
									}
									else
									{
										draw_border = m_aDrawNormalBorders[i % (int)m_aDrawNormalBorders.size()];
										draw_background = m_aDrawNormalBackgrounds[i % (int)m_aDrawNormalBackgrounds.size()];
										border_color = m_aNormalBorderColors[i % (int)m_aNormalBorderColors.size()];
										background_color = m_aNormalBackgroundColors[i % (int)m_aNormalBackgroundColors.size()];
										border_width = m_aNormalBorderWidthes[i % (int)m_aNormalBorderWidthes.size()];
									}
									if (draw_border && border_color.A > 0)
									{
										colors[0] = colors[1] = colors[2] = colors[3] = border_color;
										colors[4] = draw_background ? background_color : Color{ 0, 0, 0, 0 };
										borders.Left = borders.Top = borders.Right = border_width;
										borders.Bottom = 0;
										if (r.Bottom < r.Top)
										{
											ntl::Swap<float>(r.Top, r.Bottom);
											ntl::Swap<float>(borders.Top, borders.Bottom);
										}
										renderer->DrawBlock(r, borders, RectF{ 0, 0, 0, 0 }, colors);
									}
									else if (draw_background && background_color.A > 0)
									{
										if (r.Bottom < r.Top)
											ntl::Swap<float>(r.Top, r.Bottom);
										renderer->DrawPolygon({ PointF{ r.Left, r.Top }, PointF{ r.Right, r.Top }, PointF{ r.Right, r.Bottom }, PointF{ r.Left, r.Bottom } }, background_color);
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

		void CMultiBarChart::RenderData(IRenderer *renderer, const RectF &client, IChartData *data, const int index, ITexture *target, const PointF &xrange, const PointF &yrange)
		{
			// Unused
		}
	#pragma endregion
	}
}