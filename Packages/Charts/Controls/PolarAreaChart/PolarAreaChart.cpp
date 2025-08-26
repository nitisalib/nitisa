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
		CPolarAreaChart::CGradientListener::CGradientListener(CPolarAreaChart *control) :
			m_pControl{ control }
		{

		}

		void CPolarAreaChart::CGradientListener::NotifyOnChange()
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
		CPolarAreaChart::CPolarAreaChart():
			CControl(L"PolarAreaChart", true, true, false, false, false, false),
			m_cGradientListener{ this },
			m_pDataSet{ nullptr },
			m_bAutoRange{ true },
			m_fRange{ 100 },
			m_fAutoRange{ 100 },
			m_sBackgroundColor{ 255, 255, 255, 255 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_bDrawGrid{ true },
			m_bAutoGridStep{ true },
			m_fGridStep{ 20 },
			m_fDefaultGridStep{ 20 },
			m_fAutoGridStep{ 20 },
			m_sGridColor{ 232, 232, 232, 255 },
			m_bDrawLabels{ true },
			m_sLabelsColor{ 0, 0, 0, 0 },
			m_fBorderWidth{ 1 },
			m_fQuality{ 0.2f },
			m_iLabelSigns{ 0 },
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
			m_aActiveBorderColors{ Color{ 255, 255, 255, 255 } },
			m_pCanvas{ nullptr },
			m_bIgnoreGradient{ false },
			m_iHoveredPoint{ -1 }
		{
			OnHoverPoint = nullptr;
			OnLeavePoint = nullptr;

			setService(new CPolarAreaChartService(this), true);
			setSize(PointF{ 210, 210 });
		}

			
		CPolarAreaChart::CPolarAreaChart(IForm *parent) :CPolarAreaChart()
		{
			setForm(parent);
		}

		CPolarAreaChart::CPolarAreaChart(IControl *parent) : CPolarAreaChart()
		{
			setParent(parent);
		}

		CPolarAreaChart::~CPolarAreaChart()
		{
			if (m_pDataSet)
				m_pDataSet->Release();
		}
	#pragma endregion

	#pragma region IControl setters
		bool CPolarAreaChart::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_fBorderWidth *= avg;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IControl methods
		void CPolarAreaChart::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region IRadialChart getters
		IChartDataSet *CPolarAreaChart::getDataSet()
		{
			if (!m_pDataSet)
				m_pDataSet = new CChartDataSet();
			return m_pDataSet;
		}
	#pragma endregion

	#pragma region IRadialChart setters
		bool CPolarAreaChart::setDataSet(IChartDataSet *value, const bool release_old)
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

	#pragma region IRadialChart methods
		void CPolarAreaChart::Update()
		{
			UpdateAutoRanges();
			UpdateHoveredPoint();
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
		}
	#pragma endregion

	#pragma region IPolarAreaChart getters
		bool CPolarAreaChart::isAutoRange()
		{
			return m_bAutoRange;
		}

		float CPolarAreaChart::getRange()
		{
			return m_fRange;
		}
	#pragma endregion

	#pragma region IPolarAreaChart setters
		bool CPolarAreaChart::setAutoRange(const bool value)
		{
			if (value != m_bAutoRange)
			{
				m_bAutoRange = value;
				UpdateAutoRanges();
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPolarAreaChart::setRange(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fRange))
			{
				m_fRange = value;
				m_bAutoRange = false;
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

	#pragma region Getters
		Color CPolarAreaChart::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CPolarAreaChart::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		bool CPolarAreaChart::isDrawGrid() const
		{
			return m_bDrawGrid;
		}

		bool CPolarAreaChart::isAutoGridStep() const
		{
			return m_bAutoGridStep;
		}

		float CPolarAreaChart::getGridStep() const
		{
			return m_fGridStep;
		}

		float CPolarAreaChart::getDefaultGridStep() const
		{
			return m_fDefaultGridStep;
		}

		Color CPolarAreaChart::getGridColor() const
		{
			return m_sGridColor;
		}

		bool CPolarAreaChart::isDrawLabels() const
		{
			return m_bDrawLabels;
		}

		Color CPolarAreaChart::getLabelsColor() const
		{
			return m_sLabelsColor;
		}

		float CPolarAreaChart::getBorderWidth() const
		{
			return m_fBorderWidth;
		}

		float CPolarAreaChart::getQuality() const
		{
			return m_fQuality;
		}

		int CPolarAreaChart::getLabelSigns() const
		{
			return m_iLabelSigns;
		}

		const ColorArray &CPolarAreaChart::getNormalColors() const
		{
			return m_aNormalColors;
		}

		const ColorArray &CPolarAreaChart::getActiveColors() const
		{
			return m_aActiveColors;
		}

		const ColorArray &CPolarAreaChart::getNormalBorderColors() const
		{
			return m_aNormalBorderColors;
		}

		const ColorArray &CPolarAreaChart::getActiveBorderColors() const
		{
			return m_aActiveBorderColors;
		}
	#pragma endregion

	#pragma region Setters
		bool CPolarAreaChart::setBackgroundColor(const Color &value)
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

		bool CPolarAreaChart::setDrawGrid(const bool value)
		{
			if (value != m_bDrawGrid)
			{
				m_bDrawGrid = value;
				if (m_sGridColor.A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPolarAreaChart::setAutoGridStep(const bool value)
		{
			if (value != m_bAutoGridStep)
			{
				m_bAutoGridStep = value;
				UpdateAutoRanges();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPolarAreaChart::setGridStep(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fGridStep))
			{
				m_fGridStep = value;
				m_bAutoGridStep = false;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPolarAreaChart::setDefaultGridStep(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fDefaultGridStep))
			{
				m_fDefaultGridStep = value;
				if (m_bAutoGridStep)
				{
					UpdateAutoRanges();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPolarAreaChart::setGridColor(const Color &value)
		{
			if (value != m_sGridColor)
			{
				m_sGridColor = value;
				if (m_bDrawGrid)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPolarAreaChart::setDrawLabels(const bool value)
		{
			if (value != m_bDrawLabels)
			{
				m_bDrawLabels = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPolarAreaChart::setLabelsColor(const Color &value)
		{
			if (value != m_sLabelsColor)
			{
				m_sLabelsColor = value;
				if (m_bDrawLabels)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPolarAreaChart::setBorderWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fBorderWidth))
			{
				m_fBorderWidth = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPolarAreaChart::setQuality(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsLessOrEqual<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fQuality))
			{
				m_fQuality = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPolarAreaChart::setLabelSigns(const int value)
		{
			if (value >= 0 && value <= 9 && value != m_iLabelSigns)
			{
				m_iLabelSigns = value;
				if (m_bDrawLabels)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPolarAreaChart::setNormalColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aNormalColors = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPolarAreaChart::setActiveColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aActiveColors = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPolarAreaChart::setNormalBorderColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aNormalBorderColors = values;
				if (ntl::IsGreater<float>(m_fBorderWidth, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPolarAreaChart::setActiveBorderColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aActiveBorderColors = values;
				if (ntl::IsGreater<float>(m_fBorderWidth, 0))
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
		void CPolarAreaChart::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L".GridColor", m_sGridColor);
			style->getOption(m_sClassName + L".LabelsColor", m_sLabelsColor);
			style->getOption(m_sClassName + L".BorderWidth", m_fBorderWidth);
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
			m_bIgnoreGradient = false;
		}

		bool CPolarAreaChart::UpdateHoveredPoint()
		{
			if (getForm())
				return UpdateHoveredPoint((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition()));
			if (m_iHoveredPoint >= 0)
			{
				m_iHoveredPoint = -1;
				if (OnLeavePoint)
					OnLeavePoint(this);
				return true;
			}
			return false;
		}

		bool CPolarAreaChart::UpdateHoveredPoint(const PointF &position)
		{
			int hovered_point{ -1 };
			if (m_pDataSet && m_pDataSet->getDataCount() >= 1 && m_pDataSet->getData(0)->getCount() > 0 && isEnabled(true))
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
						float d{ (p.X - center.X) * (p.X - center.X) + (p.Y - center.Y) * (p.Y - center.Y) };
						if (d < radius * radius)
						{
							if (m_pDataSet->getData(0)->getCount() == 1)
								hovered_point = 0;
							else
							{
								float angle{ Angle(p.X, p.Y, center.X, center.Y) + ntl::HalfPi<float> };
								if (angle >= ntl::DoublePi<float>)
									angle -= ntl::DoublePi<float>;
								int index{ int(angle * (float)m_pDataSet->getData(0)->getCount() / ntl::DoublePi<float>) };
								float scale{ radius / (m_bAutoRange ? m_fAutoRange : m_fRange) };
								if (m_pDataSet->getData(0)->getY(index) > 0)
								{
									float r{ m_pDataSet->getData(0)->getY(index) * scale };
									if (d < r * r)
										hovered_point = index;
								}
							}
						}
					}
				}
			}
			if (hovered_point != m_iHoveredPoint)
			{
				m_iHoveredPoint = hovered_point;
				if (m_iHoveredPoint >= 0)
				{
					if (OnHoverPoint)
						OnHoverPoint(this, m_pDataSet->getData(0), m_iHoveredPoint);
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

		void CPolarAreaChart::UpdateAutoRanges()
		{
			RectF client{ getClientRect() };
			if (client.is_zero())
				return;
			float radius{ ntl::Min<float>(client.width(), client.height()) * 0.5f };
			if (m_bAutoRange)
			{
				m_fAutoRange = radius * 1.05f;
				if (m_pDataSet && m_pDataSet->getDataCount() > 0 && m_pDataSet->getData(0)->getCount() > 0)
				{
					float max{ 0 };
					for (int i = 0; i < m_pDataSet->getData(0)->getCount(); i++)
						max = ntl::Max<float>(max, m_pDataSet->getData(0)->getY(i));
					if (ntl::IsGreater<float>(max, 0))
						m_fAutoRange = max * 1.05f;
				}
			}
			if (m_bAutoGridStep)
			{
				float range{ m_bAutoRange ? m_fAutoRange : m_fRange }, scale{ radius / range };
				float step{ m_fDefaultGridStep }, p{ step * scale };
				if (p < m_fDefaultGridStep * 0.5f)
				{
					while (p < m_fDefaultGridStep * 0.5f)
					{
						step *= 2;
						p = step * scale;
					}
				}
				else if (p > m_fDefaultGridStep * 2)
				{
					while (p > m_fDefaultGridStep * 2)
					{
						step *= 0.5f;
						p = step * scale;
					}
				}
				m_fAutoGridStep = step;
			}
		}
	#pragma endregion

	#pragma region Paint
		void CPolarAreaChart::Render()
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
					PointF center{ (client.Left + client.Right) * 0.5f, (client.Top + client.Bottom) * 0.5f };
					float radius{ ntl::Min<float>(client.width(), client.height()) * 0.5f };
					float range{ m_bAutoRange ? m_fAutoRange : m_fRange }, scale{ radius / range }, grid_step{ (m_bAutoGridStep ? m_fAutoGridStep : m_fGridStep) * scale };
					RenderGrid(renderer, center, radius, grid_step);
					if (m_pDataSet && m_pDataSet->getDataCount() > 0 && m_pDataSet->getData(0)->getCount() > 0)
					{
						RenderData(renderer, center, radius, scale, m_pDataSet->getData(0));
						RenderBorders(renderer, center, radius, scale, m_pDataSet->getData(0));
					}
					if (font && pf)
						RenderLabels(renderer, center, radius, grid_step, scale, pf, font);
				}

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}

		void CPolarAreaChart::RenderBackground(IRenderer *renderer, const RectF &client)
		{
			if (m_cBackgroundGradient.getPointCount() >= 2)
				renderer->DrawGradient(client, m_cBackgroundGradient);
			else if (m_sBackgroundColor.A > 0)
				renderer->DrawRectangle(client, m_sBackgroundColor);
		}

		void CPolarAreaChart::RenderGrid(IRenderer *renderer, const PointF &center, const float radius, const float grid_step)
		{
			if (m_bDrawGrid && m_sGridColor.A > 0 && grid_step < radius)
			{
				std::vector<PointF> lines;
				int line_count;
				float r{ grid_step }, circle_length;
				while (r < radius)
				{
					circle_length = r * ntl::DoublePi<float>;
					line_count = ntl::Clamp<int>(ntl::Round<int>(circle_length * m_fQuality), 3, MaxPolygonPoints - 1);
					lines.resize(line_count + 1);
					lines[0] = PointF{ center.X, center.Y - r };
					for (int i = 0; i < line_count; i++)
						lines[i + 1] = PointF{ center.X + std::sin(float(i + 1) * ntl::DoublePi<float> / (float)line_count) * r, center.Y - std::cos(float(i + 1) * ntl::DoublePi<float> / (float)line_count) * r };
					renderer->DrawLines(lines, m_sGridColor, false);
					r += grid_step;
				}
			}
		}

		void CPolarAreaChart::RenderLabels(IRenderer *renderer, const PointF &center, const float radius, const float grid_step, const float scale, IPlatformFont *pf, IFont *f)
		{
			if (m_bDrawLabels && grid_step < radius)
			{
				Color color{ (m_sLabelsColor.A > 0) ? m_sLabelsColor : f->Color };
				if (color.A > 0)
				{
					CStorePrimitiveMatrix s_matrix{ renderer };
					float r{ grid_step };
					PointF size;
					String label;
					while (r < radius)
					{
						label = ToFixed(r / scale, m_iLabelSigns);
						if (m_pDataSet)
							label = m_pDataSet->getYLabel(r, label);
						if (!label.empty())
						{
							size = pf->getStringSize(label, f->Distance);
							renderer
								->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(center.X - size.X * 0.5f), std::round(center.Y - r - size.Y * 0.5f), 0))
								->DrawText(label, pf, f->Distance, color);
						}
						r += grid_step;
					}
				}
			}
		}

		void CPolarAreaChart::RenderData(IRenderer *renderer, const PointF &center, const float radius, const float scale, IChartData *data)
		{
			if (data->getCount() == 1)
			{
				if (data->getY(0) > 0)
				{
					Color color{ (m_iHoveredPoint == 0) ? m_aActiveColors[0] : m_aNormalColors[0] };
					Color border_color{ (m_iHoveredPoint == 0) ? m_aActiveBorderColors[0] : m_aNormalBorderColors[0] };
					if (color.A > 0 || (ntl::IsGreater<float>(m_fBorderWidth, 0) && border_color.A > 0))
					{
						float r{ data->getY(0) * scale };
						Gradient g;
						g.setType(GradientType::Circle);
						if (ntl::IsEqual<float>(m_fBorderWidth, 0))
							g.setPoints(Color1DArray{ Color1D{ 0, color }, Color1D{ 1, color } });
						else if (r <= 2 * m_fBorderWidth)
							g.setPoints(Color1DArray{ Color1D{ 0, border_color }, Color1D{ 1, border_color } });
						else
							g.setPoints(Color1DArray{
								Color1D{ 0, color },
								Color1D{ (r - m_fBorderWidth) / r - 0.000002f, color },
								Color1D{ (r - m_fBorderWidth) / r - 0.000001f, border_color },
								Color1D{ 1, border_color } });
						renderer->DrawGradient(RectF{ center.X - r, center.Y - r, center.X + r, center.Y + r }, g);
					}
				}
			}
			else
			{
				float a1, a2, r, da;
				int triangle_count;
				std::vector<PointF> polygon;
				Color color;
				for (int i = 0; i < data->getCount(); i++)
					if (data->getY(i) > 0)
					{
						r = data->getY(i) * scale;
						a1 = (float)i * ntl::DoublePi<float> / (float)data->getCount();
						a2 = float(i + 1) * ntl::DoublePi<float> / (float)data->getCount();
						color = (m_iHoveredPoint == i) ? m_aActiveColors[i % (int)m_aActiveColors.size()] : m_aNormalColors[i % (int)m_aNormalColors.size()];
						if (color.A > 0)
						{
							triangle_count = ntl::Clamp<int>(ntl::Round<int>(r * ntl::DoublePi<float> * m_fQuality / (float)data->getCount()), 1, MaxPolygonPoints - 2);
							da = (a2 - a1) / (float)triangle_count;
							polygon.resize(triangle_count + 2);
							polygon[0] = center;
							polygon[1] = PointF{ center.X + std::sin(a1) * r, center.Y - std::cos(a1) * r };
							for (int j = 0; j < triangle_count; j++)
								polygon[j + 2] = PointF{ center.X + std::sin(a1 + da * float(j + 1)) * r, center.Y - std::cos(a1 + da * float(j + 1)) * r };
							renderer->DrawPolygon(polygon, color);
						}
					}
			}
		}

		void CPolarAreaChart::RenderBorders(IRenderer *renderer, const PointF &center, const float radius, const float scale, IChartData *data)
		{
			if (data->getCount() > 1)
			{
				float a1, a2, r, da;
				Color border_color;
				int line_count;
				std::vector<PointF> line_points, polygon;
				std::vector<std::pair<PointF, PointF>> polygon_points;
				polygon.resize(4);
				for (int i = 0; i < data->getCount(); i++)
					if (data->getY(i) > 0)
					{
						r = data->getY(i) * scale;
						a1 = (float)i * ntl::DoublePi<float> / (float)data->getCount();
						a2 = float(i + 1) * ntl::DoublePi<float> / (float)data->getCount();
						border_color = (m_iHoveredPoint == i) ? m_aActiveBorderColors[i % (int)m_aActiveBorderColors.size()] : m_aNormalBorderColors[i % (int)m_aNormalBorderColors.size()];
						if (border_color.A > 0)
						{
							line_count = ntl::Clamp<int>(ntl::Round<int>(r * ntl::DoublePi<float> * m_fQuality / (float)data->getCount()), 1, MaxPolygonPoints - 2);
							da = (a2 - a1) / (float)line_count;
							line_points.resize(line_count + 2);
							for (int j = 0; j < line_count; j++)
								line_points[j] = PointF{ center.X + std::sin(a1 + da * (float)j) * r, center.Y - std::cos(a1 + da * (float)j) * r };
							line_points[line_count] = PointF{ center.X + std::sin(a2) * r, center.Y - std::cos(a2) * r };
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
				}
			}
		}
	#pragma endregion
	}
}