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
		CRadarChart::CGradientListener::CGradientListener(CRadarChart *control) :
			m_pControl{ control }
		{

		}

		void CRadarChart::CGradientListener::NotifyOnChange()
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
		CRadarChart::CRadarChart() :
			CControl(L"RadarChart", true, true, false, false, false, false),
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
			m_iLabelSigns{ 0 },
			m_fQuality{ 0.2f },
			m_sPadding{ 48, 16, 48, 16 },
			m_fPointSize{ 6 },
			m_bDrawLegend{ true },
			m_sLegendColor{ 0, 0, 0, 0 },
			m_aBackgroundColors{
				Color{ 255, 123, 151, 32 },
				Color{ 73, 171, 236, 32 },
				Color{ 255, 208, 98, 32 },
				Color{ 88, 255, 196, 32 },
				Color{ 220, 20, 60, 32 },
				Color{ 160, 113, 255, 32 },
				Color{ 205, 206, 210, 32 },
				Color{ 255, 166, 77, 32 } },
			m_aLineWidthes{ 2 },
			m_aLineColors{
				Color{ 255, 123, 151, 200 },
				Color{ 73, 171, 236, 200 },
				Color{ 255, 208, 98, 200 },
				Color{ 88, 255, 196, 200 },
				Color{ 220, 20, 60, 200 },
				Color{ 160, 113, 255, 200 },
				Color{ 205, 206, 210, 200 },
				Color{ 255, 166, 77, 200 } },
			m_aNormalPointSizes{ 6 },
			m_aActivePointSizes{ 8 },
			m_aNormalPointHoles{ 0 },
			m_aActivePointHoles{ 0 },
			m_aNormalPointColors{
				Color{ 255, 123, 151, 200 },
				Color{ 73, 171, 236, 200 },
				Color{ 255, 208, 98, 200 },
				Color{ 88, 255, 196, 200 },
				Color{ 220, 20, 60, 200 },
				Color{ 160, 113, 255, 200 },
				Color{ 205, 206, 210, 200 },
				Color{ 255, 166, 77, 200 } },
			m_aActivePointColors{
				Color{ 255, 123, 151, 255 },
				Color{ 73, 171, 236, 255 },
				Color{ 255, 208, 98, 255 },
				Color{ 88, 255, 196, 255 },
				Color{ 220, 20, 60, 255 },
				Color{ 160, 113, 255, 255 },
				Color{ 205, 206, 210, 255 },
				Color{ 255, 166, 77, 255 } },
			m_aNormalHoleColors{ Color{ 0, 0, 0, 0 } },
			m_aActiveHoleColors{ Color{ 0, 0, 0, 0 } },
			m_aDrawPoints{ true },
			m_pCanvas{ nullptr },
			m_bIgnoreGradient{ false },
			m_pHoveredData{ nullptr },
			m_iHoveredPoint{ -1 }
		{
			OnHoverPoint = nullptr;
			OnLeavePoint = nullptr;

			setService(new CRadarChartService(this), true);
			setSize(PointF{ 274, 210 });
		}


		CRadarChart::CRadarChart(IForm *parent) :CRadarChart()
		{
			setForm(parent);
		}

		CRadarChart::CRadarChart(IControl *parent) : CRadarChart()
		{
			setParent(parent);
		}

		CRadarChart::~CRadarChart()
		{
			if (m_pDataSet)
				m_pDataSet->Release();
		}
	#pragma endregion

	#pragma region IControl getters
		RectF CRadarChart::getClientRect()
		{
			RectF result{ m_sPadding.Left, m_sPadding.Top, getWidth() - m_sPadding.Right, getHeight() - m_sPadding.Bottom };
			result.validate();
			return result;
		}
	#pragma endregion

	#pragma region IControl setters
		bool CRadarChart::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sPadding *= s;
				for (auto &value : m_aLineWidthes)
					value *= avg;
				for (auto &value : m_aNormalPointSizes)
					value *= avg;
				for (auto &value : m_aActivePointSizes)
					value *= avg;
				for (auto &value : m_aNormalPointHoles)
					value *= avg;
				for (auto &value : m_aActivePointHoles)
					value *= avg;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IControl methods
		void CRadarChart::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region IRadialChart getters
		IChartDataSet *CRadarChart::getDataSet()
		{
			if (!m_pDataSet)
				m_pDataSet = new CChartDataSet();
			return m_pDataSet;
		}
	#pragma endregion

	#pragma region IRadialChart setters
		bool CRadarChart::setDataSet(IChartDataSet *value, const bool release_old)
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
		void CRadarChart::Update()
		{
			UpdateAutoRanges();
			UpdateHoveredPoint();
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
		}
	#pragma endregion

	#pragma region IRadarChart getters
		bool CRadarChart::isAutoRange()
		{
			return m_bAutoRange;
		}

		float CRadarChart::getRange()
		{
			return m_fRange;
		}
	#pragma endregion

	#pragma region IRadarChart setters
		bool CRadarChart::setAutoRange(const bool value)
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

		bool CRadarChart::setRange(const float value)
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
		Color CRadarChart::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CRadarChart::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		bool CRadarChart::isDrawGrid() const
		{
			return m_bDrawGrid;
		}

		bool CRadarChart::isAutoGridStep() const
		{
			return m_bAutoGridStep;
		}

		float CRadarChart::getGridStep() const
		{
			return m_fGridStep;
		}

		float CRadarChart::getDefaultGridStep() const
		{
			return m_fDefaultGridStep;
		}

		Color CRadarChart::getGridColor() const
		{
			return m_sGridColor;
		}

		bool CRadarChart::isDrawLabels() const
		{
			return m_bDrawLabels;
		}

		Color CRadarChart::getLabelsColor() const
		{
			return m_sLabelsColor;
		}

		float CRadarChart::getQuality() const
		{
			return m_fQuality;
		}

		RectF CRadarChart::getPadding() const
		{
			return m_sPadding;
		}

		float CRadarChart::getPointSize() const
		{
			return m_fPointSize;
		}

		int CRadarChart::getLabelSigns() const
		{
			return m_iLabelSigns;
		}

		bool CRadarChart::isDrawLegend() const
		{
			return m_bDrawLegend;
		}

		Color CRadarChart::getLegendColor() const
		{
			return m_sLegendColor;
		}

		const ColorArray &CRadarChart::getBackgroundColors() const
		{
			return m_aBackgroundColors;
		}

		const FloatArray &CRadarChart::getLineWidthes() const
		{
			return m_aLineWidthes;
		}

		const ColorArray &CRadarChart::getLineColors() const
		{
			return m_aLineColors;
		}

		const FloatArray &CRadarChart::getNormalPointSizes() const
		{
			return m_aNormalPointSizes;
		}

		const FloatArray &CRadarChart::getActivePointSizes() const
		{
			return m_aActivePointSizes;
		}

		const FloatArray &CRadarChart::getNormalPointHoles() const
		{
			return m_aNormalPointHoles;
		}

		const FloatArray &CRadarChart::getActivePointHoles() const
		{
			return m_aActivePointHoles;
		}

		const ColorArray &CRadarChart::getNormalPointColors() const
		{
			return m_aNormalPointColors;
		}

		const ColorArray &CRadarChart::getActivePointColors() const
		{
			return m_aActivePointColors;
		}

		const ColorArray &CRadarChart::getNormalHoleColors() const
		{
			return m_aNormalHoleColors;
		}

		const ColorArray &CRadarChart::getActiveHoleColors() const
		{
			return m_aActiveHoleColors;
		}

		const BoolArray &CRadarChart::getDrawPoints() const
		{
			return m_aDrawPoints;
		}
	#pragma endregion

	#pragma region Setters
		bool CRadarChart::setBackgroundColor(const Color &value)
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

		bool CRadarChart::setDrawGrid(const bool value)
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

		bool CRadarChart::setAutoGridStep(const bool value)
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

		bool CRadarChart::setGridStep(const float value)
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

		bool CRadarChart::setDefaultGridStep(const float value)
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

		bool CRadarChart::setGridColor(const Color &value)
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

		bool CRadarChart::setDrawLabels(const bool value)
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

		bool CRadarChart::setLabelsColor(const Color &value)
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

		bool CRadarChart::setQuality(const float value)
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

		bool CRadarChart::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				m_sPadding = value;
				UpdateAutoRanges();
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CRadarChart::setPointSize(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fPointSize))
			{
				m_fPointSize = value;
				if (UpdateHoveredPoint())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CRadarChart::setLabelSigns(const int value)
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

		bool CRadarChart::setDrawLegend(const bool value)
		{
			if (value != m_bDrawLegend)
			{
				m_bDrawLegend = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CRadarChart::setLegendColor(const Color &value)
		{
			if (value != m_sLegendColor)
			{
				m_sLegendColor = value;
				if (m_bDrawLegend)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CRadarChart::setBackgroundColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aBackgroundColors = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CRadarChart::setLineWidthes(const FloatArray &values)
		{
			if (values.size() == 0)
				return false;
			for (auto value : values)
				if (ntl::IsLessOrEqual<float>(value, 0))
					return false;
			m_aLineWidthes = values;
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
			return true;
		}

		bool CRadarChart::setLineColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aLineColors = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CRadarChart::setNormalPointSizes(const FloatArray &values)
		{
			if (values.size() == 0)
				return false;
			for (auto value : values)
				if (ntl::IsLess<float>(value, 0))
					return false;
			m_aNormalPointSizes = values;
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
			return true;
		}

		bool CRadarChart::setActivePointSizes(const FloatArray &values)
		{
			if (values.size() == 0)
				return false;
			for (auto value : values)
				if (ntl::IsLess<float>(value, 0))
					return false;
			m_aActivePointSizes = values;
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
			return true;
		}

		bool CRadarChart::setNormalPointHoles(const FloatArray &values)
		{
			if (values.size() == 0)
				return false;
			for (auto value : values)
				if (ntl::IsLess<float>(value, 0))
					return false;
			m_aNormalPointHoles = values;
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
			return true;
		}

		bool CRadarChart::setActivePointHoles(const FloatArray &values)
		{
			if (values.size() == 0)
				return false;
			for (auto value : values)
				if (ntl::IsLess<float>(value, 0))
					return false;
			m_aActivePointHoles = values;
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
			return true;
		}

		bool CRadarChart::setNormalPointColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aNormalPointColors = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CRadarChart::setActivePointColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aActivePointColors = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CRadarChart::setNormalHoleColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aNormalHoleColors = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CRadarChart::setActiveHoleColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aActiveHoleColors = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CRadarChart::setDrawPoints(const BoolArray &values)
		{
			if (values.size() > 0)
			{
				m_aDrawPoints = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CRadarChart::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L".GridColor", m_sGridColor);
			style->getOption(m_sClassName + L".LabelsColor", m_sLabelsColor);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			style->getOption(m_sClassName + L".LegendColor", m_sLegendColor);
			Color vc;
			int index;
			float vf;
			index = 0;
			while (style->getOption(m_sClassName + L".BackgroundColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aBackgroundColors.clear();
				m_aBackgroundColors.push_back(vc);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".LineWidthes[" + ToString(index) + L"]", vf))
			{
				if (index == 0)
					m_aLineWidthes.clear();
				m_aLineWidthes.push_back(vf);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".LineColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aLineColors.clear();
				m_aLineColors.push_back(vc);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".NormalPointSizes[" + ToString(index) + L"]", vf))
			{
				if (index == 0)
					m_aNormalPointSizes.clear();
				m_aNormalPointSizes.push_back(vf);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".ActivePointSizes[" + ToString(index) + L"]", vf))
			{
				if (index == 0)
					m_aActivePointSizes.clear();
				m_aActivePointSizes.push_back(vf);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".NormalPointHoles[" + ToString(index) + L"]", vf))
			{
				if (index == 0)
					m_aNormalPointHoles.clear();
				m_aNormalPointHoles.push_back(vf);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".ActivePointHoles[" + ToString(index) + L"]", vf))
			{
				if (index == 0)
					m_aActivePointHoles.clear();
				m_aActivePointHoles.push_back(vf);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".NormalPointColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aNormalPointColors.clear();
				m_aNormalPointColors.push_back(vc);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".ActivePointColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aActivePointColors.clear();
				m_aActivePointColors.push_back(vc);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".NormalHoleColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aNormalHoleColors.clear();
				m_aNormalHoleColors.push_back(vc);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".ActiveHoleColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aActiveHoleColors.clear();
				m_aActiveHoleColors.push_back(vc);
				index++;
			}
			m_bIgnoreGradient = false;
		}

		bool CRadarChart::UpdateHoveredPoint()
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

		bool CRadarChart::UpdateHoveredPoint(const PointF &position)
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
							PointF center{ (client.Left + client.Right) * 0.5f, (client.Top + client.Bottom) * 0.5f };
							float radius{ ntl::Min<float>(client.width(), client.height()) * 0.5f };
							float range{ m_bAutoRange ? m_fAutoRange : m_fRange }, scale{ radius / range }, a, r;
							PointF pos;
							for (int i = 0; i < m_pDataSet->getDataCount(); i++)
							{
								for (int j = 0; j < m_pDataSet->getData(i)->getCount(); j++)
								{
									a = (float)j * ntl::DoublePi<float> / (float)best->getCount();
									r = ntl::Max<float>(0, m_pDataSet->getData(i)->getY(j)) * scale;
									pos.X = center.X + std::sin(a) * r;
									pos.Y = center.Y - std::cos(a) * r;
									if ((p.X - pos.X) * (p.X - pos.X) + (p.Y - pos.Y) * (p.Y - pos.Y) <= m_fPointSize * m_fPointSize)
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
			}
			if (hovered_data != m_pHoveredData || hovered_point != m_iHoveredPoint)
			{
				m_pHoveredData = hovered_data;
				m_iHoveredPoint = hovered_point;
				if (m_iHoveredPoint >= 0)
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

		IChartData *CRadarChart::FindBestData() const
		{
			IChartData *result{ nullptr };
			if (m_pDataSet)
				for (int i = 0; i < m_pDataSet->getDataCount(); i++)
					if (m_pDataSet->getData(i)->getCount() > 0 && (!result || m_pDataSet->getData(i)->getCount() > result->getCount()))
						result = m_pDataSet->getData(i);
			return result;
		}

		void CRadarChart::UpdateAutoRanges()
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
		void CRadarChart::Render()
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
					IChartData *best{ FindBestData() };
					RenderGrid(renderer, center, radius, grid_step, best);
					if (best)
						for (int i = 0; i < m_pDataSet->getDataCount(); i++)
						{
							RenderBackgrounds(renderer, center, radius, scale, m_pDataSet->getData(i), i, best);
							RenderLines(renderer, center, radius, scale, m_pDataSet->getData(i), i, best);
							RenderPoints(renderer, center, radius, scale, m_pDataSet->getData(i), i, best);
						}
					if (font && pf)
					{
						RenderLabels(renderer, center, radius, grid_step, scale, pf, font);
						RenderLegends(renderer, center, radius, pf, font, best);
					}
				}

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}

		void CRadarChart::RenderBackground(IRenderer *renderer, const RectF &client)
		{
			if (m_cBackgroundGradient.getPointCount() >= 2)
				renderer->DrawGradient(client, m_cBackgroundGradient);
			else if (m_sBackgroundColor.A > 0)
				renderer->DrawRectangle(client, m_sBackgroundColor);
		}

		void CRadarChart::RenderGrid(IRenderer *renderer, const PointF &center, const float radius, const float grid_step, IChartData *best)
		{
			if (best && best->getCount() >= 3 && m_bDrawGrid && m_sGridColor.A > 0 && grid_step < radius)
			{
				std::vector<PointF> lines;
				lines.resize(best->getCount());
				float r{ grid_step }, a;
				while (r < radius)
				{
					for (int i = 0; i < best->getCount(); i++)
					{
						a = (float)i * ntl::DoublePi<float> / (float)best->getCount();
						lines[i] = PointF{ center.X + std::sin(a) * r, center.Y - std::cos(a) * r };
					}
					renderer->DrawLines(lines, m_sGridColor, true);
					r += grid_step;
				}
				for (int i = 0; i < best->getCount(); i++)
				{
					a = (float)i * ntl::DoublePi<float> / (float)best->getCount();
					renderer->DrawLine(center, PointF{ center.X + std::sin(a) * radius, center.Y - std::cos(a) * radius }, m_sGridColor);
				}
			}
		}

		void CRadarChart::RenderLabels(IRenderer *renderer, const PointF &center, const float radius, const float grid_step, const float scale, IPlatformFont *pf, IFont *f)
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

		void CRadarChart::RenderLegends(IRenderer *renderer, const PointF &center, const float radius, IPlatformFont *pf, IFont *f, IChartData *best)
		{
			if (best && best->getCount() >= 3 && m_bDrawLegend)
			{
				Color color{ (m_sLegendColor.A > 0) ? m_sLegendColor : f->Color };
				if (color.A > 0)
				{
					CStorePrimitiveMatrix s_matrix{ renderer };
					float a;
					PointF p, size;
					String legend;
					for (int i = 0; i < best->getCount(); i++)
					{
						legend = best->getLabel(i);
						if (!legend.empty())
						{
							size = pf->getStringSize(legend, f->Distance);
							a = (float)i * ntl::DoublePi<float> / (float)best->getCount();
							p = PointF{ center.X + std::sin(a) * radius, center.Y - std::cos(a) * radius };
							if (ntl::IsEqual<float>(p.Y, center.Y))
								p.Y -= size.Y / 2;
							else if (ntl::IsLess<float>(p.Y, center.Y))
								p.Y -= size.Y;
							if (ntl::IsEqual<float>(p.X, center.X))
								p.X -= size.X / 2;
							else if (ntl::IsLess<float>(p.X, center.X))
								p.X -= size.X;
							renderer
								->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(p.X), std::round(p.Y), 0))
								->DrawText(legend, pf, f->Distance, color);
						}
					}
				}
			}
		}

		void CRadarChart::RenderBackgrounds(IRenderer *renderer, const PointF &center, const float radius, const float scale, IChartData *data, const int index, IChartData *best)
		{
			Color color{ m_aBackgroundColors[index % (int)m_aBackgroundColors.size()] };
			if (color.A > 0 && data->getCount() >= 3)
			{
				float a1, a2, r1, r2;
				PointF p1{ center }, p2, p3;
				for (int i = 1; i <= data->getCount(); i++)
				{
					a1 = float(i - 1) * ntl::DoublePi<float> / (float)best->getCount();
					a2 = float(i % data->getCount()) * ntl::DoublePi<float> / (float)best->getCount();
					r1 = ntl::Max<float>(0, data->getY(i - 1)) * scale;
					r2 = ntl::Max<float>(0, data->getY(i % data->getCount())) * scale;
					p2 = PointF{ center.X + std::sin(a1) * r1, center.Y - std::cos(a1) * r1 };
					p3 = PointF{ center.X + std::sin(a2) * r2, center.Y - std::cos(a2) * r2 };
					renderer->DrawTriangle(p1, p2, p3, color);
				}
			}
		}

		void CRadarChart::RenderLines(IRenderer *renderer, const PointF &center, const float radius, const float scale, IChartData *data, const int index, IChartData *best)
		{
			Color color{ m_aLineColors[index % (int)m_aLineColors.size()] };
			if (color.A > 0)
			{
				float width{ m_aLineWidthes[index % (int)m_aLineWidthes.size()] };
				float a, r;
				if (ntl::IsGreater<float>(width, 1))
				{
					std::vector<PointF> points;
					std::vector<std::pair<PointF, PointF>> polygon_data;
					if (data->getCount() >= 3)
					{
						points.resize(data->getCount());
						for (int i = 0; i < data->getCount(); i++)
						{
							a = (float)i * ntl::DoublePi<float> / (float)best->getCount();
							r = ntl::Max<float>(0, data->getY(i)) * scale;
							points[i] = PointF{ center.X + std::sin(a) * r, center.Y - std::cos(a) * r };
						}
					}
					else if (data->getCount() == 2)
					{
						points.resize(2);
						r = ntl::Max<float>(0, data->getY(0)) * scale;
						a = ntl::DoublePi<float> / (float)best->getCount();
						points[0] = PointF{ center.X, center.Y - r };
						points[1] = PointF{ center.X + std::sin(a) * r, center.Y - std::cos(a) * r };
					}
					else if (data->getCount() == 1)
					{
						points.resize(2);
						r = ntl::Max<float>(0, data->getY(0)) * scale;
						points[0] = center;
						points[1] = PointF{ center.X, center.Y - r };
					}
					MakeThickPath(points, points.size() > 2, width, true, polygon_data);
					for (size_t i = 1; i < polygon_data.size(); i++)
						renderer->DrawPolygon({ polygon_data[i - 1].first, polygon_data[i].first, polygon_data[i].second, polygon_data[i - 1].second }, color);
					if (polygon_data.size() > 2)
						renderer->DrawPolygon({ polygon_data[polygon_data.size() - 1].first, polygon_data[0].first, polygon_data[0].second, polygon_data[polygon_data.size() - 1].second }, color);
				}
				else
				{
					if (data->getCount() >= 3)
					{
						std::vector<PointF> lines;
						lines.resize(data->getCount());
						for (int i = 0; i < data->getCount(); i++)
						{
							a = (float)i * ntl::DoublePi<float> / (float)best->getCount();
							r = ntl::Max<float>(0, data->getY(i)) * scale;
							lines[i] = PointF{ center.X + std::sin(a) * r, center.Y - std::cos(a) * r };
						}
						renderer->DrawLines(lines, color, true);
					}
					else if (data->getCount() == 2)
					{
						r = ntl::Max<float>(0, data->getY(0)) * scale;
						a = ntl::DoublePi<float> / (float)best->getCount();
						PointF p1{ center.X, center.Y - r }, p2{ center.X + std::sin(a) * r, center.Y - std::cos(a) * r };
						renderer->DrawLine(p1, p2, color);
					}
					else if (data->getCount() == 1)
					{
						r = ntl::Max<float>(0, data->getY(0)) * scale;
						PointF p1{ center }, p2{ p1.X, center.Y - r };
						renderer->DrawLine(p1, p2, color);
					}
				}
			}
		}

		void CRadarChart::RenderPoints(IRenderer *renderer, const PointF &center, const float radius, const float scale, IChartData *data, const int index, IChartData *best)
		{
			if (m_aDrawPoints[index % (int)m_aDrawPoints.size()])
			{
				float size, hole;
				Color color, color_hole;
				Gradient g;
				g.setType(GradientType::Circle);
				RectF rect;
				float a, r;
				for (int i = 0; i < data->getCount(); i++)
				{
					if (data == m_pHoveredData && i == m_iHoveredPoint)
					{
						size = m_aActivePointSizes[index % (int)m_aActivePointSizes.size()];
						hole = m_aActivePointHoles[index % (int)m_aActivePointHoles.size()];
						color = m_aActivePointColors[index % (int)m_aActivePointColors.size()];
						color_hole = m_aActiveHoleColors[index % (int)m_aActiveHoleColors.size()];
					}
					else
					{
						size = m_aNormalPointSizes[index % (int)m_aNormalPointSizes.size()];
						hole = m_aNormalPointHoles[index % (int)m_aNormalPointHoles.size()];
						color = m_aNormalPointColors[index % (int)m_aNormalPointColors.size()];
						color_hole = m_aNormalHoleColors[index % (int)m_aNormalHoleColors.size()];
					}
					if (color.A == 0 && color_hole.A == 0)
						continue;
					if (ntl::IsEqual<float>(size, 0))
						continue;
					hole = ntl::Min<float>(hole, size);
					if (ntl::IsEqual<float>(hole, size) && color_hole.A == 0)
						continue;
					if (ntl::IsEqual<float>(hole, 0) && color.A == 0)
						continue;
					a = (float)i * ntl::DoublePi<float> / (float)best->getCount();
					r = ntl::Max<float>(0, data->getY(i)) * scale;
					rect.Left = center.X + std::sin(a) * r - size * 0.5f;
					rect.Top = center.Y - std::cos(a) * r - size * 0.5f;
					rect.Right = rect.Left + size;
					rect.Bottom = rect.Top + size;
					if (ntl::IsEqual<float>(hole, 0))
						g.setPoints(Color1DArray{ Color1D{ 0, color }, Color1D{ 1, color } });
					else if (ntl::IsEqual<float>(hole, size))
						g.setPoints(Color1DArray{ Color1D{ 0, color_hole }, Color1D{ 1, color_hole } });
					else
						g.setPoints(Color1DArray{ Color1D{ 0, color_hole }, Color1D{ hole / size, color_hole }, Color1D{ hole / size + 0.000001f, color}, Color1D{ 1, color } });
					renderer->DrawGradient(rect, g);
				}
			}
		}
	#pragma endregion
	}
}