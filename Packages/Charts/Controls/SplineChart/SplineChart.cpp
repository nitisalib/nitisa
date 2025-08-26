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
		CSplineChart::CSplineChart() :
			CCustomCartesianChart(L"SplineChart", true, true, false, false, false, false),
			m_aChartDrawPoints{ true },
			m_aChartDrawLines{ true },
			m_aChartDrawBackgrounds{ false },
			m_aChartNormalPointSizes{ 6 },
			m_aChartActivePointSizes{ 8 },
			m_aChartNormalPointHoles{ 0 },
			m_aChartActivePointHoles{ 0 },
			m_aChartNormalPointColors{
				Color{ 255, 123, 151, 200 },
				Color{ 73, 171, 236, 200 },
				Color{ 255, 208, 98, 200 },
				Color{ 88, 255, 196, 200 },
				Color{ 220, 20, 60, 200 },
				Color{ 160, 113, 255, 200 },
				Color{ 205, 206, 210, 200 },
				Color{ 255, 166, 77, 200 } },
			m_aChartActivePointColors{
				Color{ 255, 123, 151, 255 },
				Color{ 73, 171, 236, 255 },
				Color{ 255, 208, 98, 255 },
				Color{ 88, 255, 196, 255 },
				Color{ 220, 20, 60, 255 },
				Color{ 160, 113, 255, 255 },
				Color{ 205, 206, 210, 255 },
				Color{ 255, 166, 77, 255 } },
			m_aChartNormalPointHoleColors{ Color{ 0, 0, 0, 0 } },
			m_aChartActivePointHoleColors{ Color{ 0, 0, 0, 0 } },
			m_aChartLineWidthes{ 2 },
			m_aChartLineColors{
				Color{ 255, 123, 151, 200 },
				Color{ 73, 171, 236, 200 },
				Color{ 255, 208, 98, 200 },
				Color{ 88, 255, 196, 200 },
				Color{ 220, 20, 60, 200 },
				Color{ 160, 113, 255, 200 },
				Color{ 205, 206, 210, 200 },
				Color{ 255, 166, 77, 200 } },
			m_aChartBackgroundColors{
				Color{ 255, 123, 151, 128 },
				Color{ 73, 171, 236, 128 },
				Color{ 255, 208, 98, 128 },
				Color{ 88, 255, 196, 128 },
				Color{ 220, 20, 60, 128 },
				Color{ 160, 113, 255, 128 },
				Color{ 205, 206, 210, 128 },
				Color{ 255, 166, 77, 128 } },
			m_aChartVerticals{ false },
			m_aChartTensions{ 0.4f },
			m_aChartCurveRecursionLimits{ 16 },
			m_aChartDistanceTolerances{ 0.5f },
			m_aChartAngleTolerances{ ntl::DegToRad<float>(1) },
			m_aChartCuspLimits{ ntl::DegToRad<float>(1) },
			m_aChartCurveAngleTolerances{ ntl::DegToRad<float>(1) },
			m_aChartCurveCollinearityTolerances{ 1 },
			m_pRenderer{ new CBezierChartRenderer() }
		{
			setSize(PointF{ 370, 210 });
		}

		CSplineChart::CSplineChart(IForm *parent) : CSplineChart()
		{
			setForm(parent);
		}

		CSplineChart::CSplineChart(IControl *parent) : CSplineChart()
		{
			setParent(parent);
		}

		CSplineChart::~CSplineChart()
		{
			m_pRenderer->Release();
		}
	#pragma endregion

	#pragma region IControl setters
		bool CSplineChart::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CCustomCartesianChart::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				for (auto &value : m_aChartNormalPointSizes)
					value *= avg;
				for (auto &value : m_aChartActivePointSizes)
					value *= avg;
				for (auto &value : m_aChartNormalPointHoles)
					value *= avg;
				for (auto &value : m_aChartActivePointHoles)
					value *= avg;
				for (auto &value : m_aChartLineWidthes)
					value *= avg;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		const BoolArray &CSplineChart::getChartDrawPoints() const
		{
			return m_aChartDrawPoints;
		}

		const BoolArray &CSplineChart::getChartDrawLines() const
		{
			return m_aChartDrawLines;
		}

		const BoolArray &CSplineChart::getChartDrawBackgrounds() const
		{
			return m_aChartDrawBackgrounds;
		}

		const FloatArray &CSplineChart::getChartNormalPointSizes() const
		{
			return m_aChartNormalPointSizes;
		}

		const FloatArray &CSplineChart::getChartActivePointSizes() const
		{
			return m_aChartActivePointSizes;
		}

		const FloatArray &CSplineChart::getChartNormalPointHoles() const
		{
			return m_aChartNormalPointHoles;
		}

		const FloatArray &CSplineChart::getChartActivePointHoles() const
		{
			return m_aChartActivePointHoles;
		}

		const ColorArray &CSplineChart::getChartNormalPointColors() const
		{
			return m_aChartNormalPointColors;
		}

		const ColorArray &CSplineChart::getChartActivePointColors() const
		{
			return m_aChartActivePointColors;
		}

		const ColorArray &CSplineChart::getChartNormalPointHoleColors() const
		{
			return m_aChartNormalPointHoleColors;
		}

		const ColorArray &CSplineChart::getChartActivePointHoleColors() const
		{
			return m_aChartActivePointHoleColors;
		}

		const FloatArray &CSplineChart::getChartLineWidthes() const
		{
			return m_aChartLineWidthes;
		}

		const ColorArray &CSplineChart::getChartLineColors() const
		{
			return m_aChartLineColors;
		}

		const ColorArray &CSplineChart::getChartBackgroundColors() const
		{
			return m_aChartBackgroundColors;
		}

		const BoolArray &CSplineChart::getChartVerticals() const
		{
			return m_aChartVerticals;
		}

		const FloatArray &CSplineChart::getChartTensions() const
		{
			return m_aChartTensions;
		}

		const IntegerArray &CSplineChart::getChartCurveRecursionLimits() const
		{
			return m_aChartCurveRecursionLimits;
		}

		const FloatArray &CSplineChart::getChartDistanceTolerances() const
		{
			return m_aChartDistanceTolerances;
		}

		const FloatArray &CSplineChart::getChartAngleTolerances() const
		{
			return m_aChartAngleTolerances;
		}

		const FloatArray &CSplineChart::getChartCuspLimits() const
		{
			return m_aChartCuspLimits;
		}

		const FloatArray &CSplineChart::getChartCurveAngleTolerances() const
		{
			return m_aChartCurveAngleTolerances;
		}

		const FloatArray &CSplineChart::getChartCurveCollinearityTolerances() const
		{
			return m_aChartCurveCollinearityTolerances;
		}
	#pragma endregion

	#pragma region Setters
		bool CSplineChart::setChartDrawPoints(const BoolArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartDrawPoints = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartDrawLines(const BoolArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartDrawLines = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartDrawBackgrounds(const BoolArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartDrawBackgrounds = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartNormalPointSizes(const FloatArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartNormalPointSizes = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartActivePointSizes(const FloatArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartActivePointSizes = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartNormalPointHoles(const FloatArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartNormalPointHoles = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartActivePointHoles(const FloatArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartActivePointHoles = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartNormalPointColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartNormalPointColors = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartActivePointColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartActivePointColors = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartNormalPointHoleColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartNormalPointHoleColors = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartActivePointHoleColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartActivePointHoleColors = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartLineWidthes(const FloatArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartLineWidthes = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartLineColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartLineColors = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartBackgroundColors(const ColorArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartBackgroundColors = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartVerticals(const BoolArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartVerticals = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartTensions(const FloatArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartTensions = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartCurveRecursionLimits(const IntegerArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartCurveRecursionLimits = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartDistanceTolerances(const FloatArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartDistanceTolerances = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartAngleTolerances(const FloatArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartAngleTolerances = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartCuspLimits(const FloatArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartCuspLimits = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartCurveAngleTolerances(const FloatArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartCurveAngleTolerances = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CSplineChart::setChartCurveCollinearityTolerances(const FloatArray &values)
		{
			if (values.size() > 0)
			{
				m_aChartCurveCollinearityTolerances = values;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CSplineChart::UpdateFromStyle(IStyle *style)
		{
			CCustomCartesianChart::UpdateFromStyle(style);
			bool vb;
			int index;
			float vf;
			Color vc;
			index = 0;
			while (style->getOption(m_sClassName + L".DrawPoints[" + ToString(index) + L"]", vb))
			{
				if (index == 0)
					m_aChartDrawPoints.clear();
				m_aChartDrawPoints.push_back(vb);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".DrawLines[" + ToString(index) + L"]", vb))
			{
				if (index == 0)
					m_aChartDrawLines.clear();
				m_aChartDrawLines.push_back(vb);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".DrawBackgrounds[" + ToString(index) + L"]", vb))
			{
				if (index == 0)
					m_aChartDrawBackgrounds.clear();
				m_aChartDrawBackgrounds.push_back(vb);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".NormalPointSizes[" + ToString(index) + L"]", vf))
			{
				if (index == 0)
					m_aChartNormalPointSizes.clear();
				m_aChartNormalPointSizes.push_back(vf);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".ActivePointSizes[" + ToString(index) + L"]", vf))
			{
				if (index == 0)
					m_aChartActivePointSizes.clear();
				m_aChartActivePointSizes.push_back(vf);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".NormalPointHoles[" + ToString(index) + L"]", vf))
			{
				if (index == 0)
					m_aChartNormalPointHoles.clear();
				m_aChartNormalPointHoles.push_back(vf);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".ActivePointHoles[" + ToString(index) + L"]", vf))
			{
				if (index == 0)
					m_aChartActivePointHoles.clear();
				m_aChartActivePointHoles.push_back(vf);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".NormalPointColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aChartNormalPointColors.clear();
				m_aChartNormalPointColors.push_back(vc);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".ActivePointColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aChartActivePointColors.clear();
				m_aChartActivePointColors.push_back(vc);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".NormalPointHoleColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aChartNormalPointHoleColors.clear();
				m_aChartNormalPointHoleColors.push_back(vc);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".ActivePointHoleColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aChartActivePointHoleColors.clear();
				m_aChartActivePointHoleColors.push_back(vc);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".LineWidthes[" + ToString(index) + L"]", vf))
			{
				if (index == 0)
					m_aChartLineWidthes.clear();
				m_aChartLineWidthes.push_back(vf);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".LineColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aChartLineColors.clear();
				m_aChartLineColors.push_back(vc);
				index++;
			}
			index = 0;
			while (style->getOption(m_sClassName + L".BackgroundColors[" + ToString(index) + L"]", vc))
			{
				if (index == 0)
					m_aChartBackgroundColors.clear();
				m_aChartBackgroundColors.push_back(vc);
				index++;
			}
		}
	#pragma endregion

	#pragma region Paint
		void CSplineChart::RenderData(IRenderer *renderer, const RectF &client, IChartData *data, const int index, ITexture *target, const PointF &xrange, const PointF &yrange)
		{
			if (data && data->getCount() > 0)
			{
				IChartRenderer *r;
				if (data->getRenderer())
					r = data->getRenderer();
				else
				{
					m_pRenderer->setDrawPoints(m_aChartDrawPoints[index % (int)m_aChartDrawPoints.size()]);
					m_pRenderer->setDrawLine(m_aChartDrawLines[index % (int)m_aChartDrawLines.size()]);
					m_pRenderer->setDrawBackground(m_aChartDrawBackgrounds[index % (int)m_aChartDrawBackgrounds.size()]);
					m_pRenderer->setPointSize(CBezierChartRenderer::PointState::Normal, m_aChartNormalPointSizes[index % (int)m_aChartNormalPointSizes.size()]);
					m_pRenderer->setPointSize(CBezierChartRenderer::PointState::Active, m_aChartActivePointSizes[index % (int)m_aChartActivePointSizes.size()]);
					m_pRenderer->setPointHole(CBezierChartRenderer::PointState::Normal, m_aChartNormalPointHoles[index % (int)m_aChartNormalPointHoles.size()]);
					m_pRenderer->setPointHole(CBezierChartRenderer::PointState::Active, m_aChartActivePointHoles[index % (int)m_aChartActivePointHoles.size()]);
					m_pRenderer->setPointColor(CBezierChartRenderer::PointState::Normal, m_aChartNormalPointColors[index % (int)m_aChartNormalPointColors.size()]);
					m_pRenderer->setPointColor(CBezierChartRenderer::PointState::Active, m_aChartActivePointColors[index % (int)m_aChartActivePointColors.size()]);
					m_pRenderer->setPointHoleColor(CBezierChartRenderer::PointState::Normal, m_aChartNormalPointHoleColors[index % (int)m_aChartNormalPointHoleColors.size()]);
					m_pRenderer->setPointHoleColor(CBezierChartRenderer::PointState::Active, m_aChartActivePointHoleColors[index % (int)m_aChartActivePointHoleColors.size()]);
					m_pRenderer->setLineWidth(m_aChartLineWidthes[index % (int)m_aChartLineWidthes.size()]);
					m_pRenderer->setLineColor(m_aChartLineColors[index % (int)m_aChartLineColors.size()]);
					m_pRenderer->setBackgroundColor(m_aChartBackgroundColors[index % (int)m_aChartBackgroundColors.size()]);
					m_pRenderer->setVertical(m_aChartVerticals[index % (int)m_aChartVerticals.size()]);
					m_pRenderer->setTension(m_aChartTensions[index % (int)m_aChartTensions.size()]);
					m_pRenderer->setCurveRecursionLimit(m_aChartCurveRecursionLimits[index % (int)m_aChartCurveRecursionLimits.size()]);
					m_pRenderer->setDistanceTolerance(m_aChartDistanceTolerances[index % (int)m_aChartDistanceTolerances.size()]);
					m_pRenderer->setAngleTolerance(m_aChartAngleTolerances[index % (int)m_aChartAngleTolerances.size()]);
					m_pRenderer->setCuspLimit(m_aChartCuspLimits[index % (int)m_aChartCuspLimits.size()]);
					m_pRenderer->setCurveAngleTolerance(m_aChartCurveAngleTolerances[index % (int)m_aChartCurveAngleTolerances.size()]);
					m_pRenderer->setCurveCollinearityTolerance(m_aChartCurveCollinearityTolerances[index % (int)m_aChartCurveCollinearityTolerances.size()]);
					m_pRenderer->setActivePoint((data == m_pHoveredData) ? m_iHoveredPoint : -1);
					r = m_pRenderer;
				}
				r->Render(renderer, target, data, xrange, yrange);
			}
		}
	#pragma endregion
	}
}