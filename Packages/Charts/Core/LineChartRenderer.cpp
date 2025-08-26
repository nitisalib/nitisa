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
		CLineChartRenderer::CLineChartRenderer():
			m_bDrawPoints{ true },
			m_bDrawLine{ true },
			m_bDrawBackground{ false },
			m_aPointSize{ 6, 8 },
			m_aPointHole{ 4, 6 },
			m_aPointColor{ { 0, 0, 0, 255 }, { 0, 0, 0, 255 } },
			m_aPointHoleColor{ { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
			m_fLineWidth{ 3 },
			m_sLineColor{ 0, 0, 0, 200 },
			m_sBackgroundColor{ 0, 0, 0, 128 },
			m_iActivePoint{ -1 },
			m_bVertical{ false }
		{

		}

		void CLineChartRenderer::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Getters
		bool CLineChartRenderer::isDrawPoints() const
		{
			return m_bDrawPoints;
		}

		bool CLineChartRenderer::isDrawLine() const
		{
			return m_bDrawLine;
		}

		bool CLineChartRenderer::isDrawBackground() const
		{
			return m_bDrawBackground;
		}

		float CLineChartRenderer::getPointSize(const PointState state) const
		{
			return m_aPointSize[(int)state];
		}

		float CLineChartRenderer::getPointHole(const PointState state) const
		{
			return m_aPointHole[(int)state];
		}

		Color CLineChartRenderer::getPointColor(const PointState state) const
		{
			return m_aPointColor[(int)state];
		}

		Color CLineChartRenderer::getPointHoleColor(const PointState state) const
		{
			return m_aPointHoleColor[(int)state];
		}

		float CLineChartRenderer::getLineWidth() const
		{
			return m_fLineWidth;
		}

		Color CLineChartRenderer::getLineColor() const
		{
			return m_sLineColor;
		}

		Color CLineChartRenderer::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		int CLineChartRenderer::getActivePoint() const
		{
			return m_iActivePoint;
		}

		bool CLineChartRenderer::isVertical() const
		{
			return m_bVertical;
		}
	#pragma endregion

	#pragma region Setters
		bool CLineChartRenderer::setDrawPoints(const bool value)
		{
			if (value != m_bDrawPoints)
			{
				m_bDrawPoints = value;
				return true;
			}
			return false;
		}

		bool CLineChartRenderer::setDrawLine(const bool value)
		{
			if (value != m_bDrawLine)
			{
				m_bDrawLine = value;
				return true;
			}
			return false;
		}

		bool CLineChartRenderer::setDrawBackground(const bool value)
		{
			if (value != m_bDrawBackground)
			{
				m_bDrawBackground = value;
				return true;
			}
			return false;
		}

		bool CLineChartRenderer::setPointSize(const PointState state, const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_aPointSize[(int)state]))
			{
				m_aPointSize[(int)state] = value;
				if (ntl::IsGreaterOrEqual<float>(m_aPointHole[(int)state], value))
					m_aPointHole[(int)state] = ntl::Max<float>(0, m_aPointSize[(int)state] - 1);
				return true;
			}
			return false;
		}

		bool CLineChartRenderer::setPointHole(const PointState state, const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_aPointHole[(int)state]))
			{
				m_aPointHole[(int)state] = value;
				if (ntl::IsGreater<float>(m_aPointHole[(int)state], 0) && ntl::IsGreaterOrEqual<float>(m_aPointHole[(int)state], m_aPointSize[(int)state]))
					m_aPointSize[(int)state] = m_aPointHole[(int)state] + 1;
				return true;
			}
			return false;
		}

		bool CLineChartRenderer::setPointColor(const PointState state, const Color &value)
		{
			if (value != m_aPointColor[(int)state])
			{
				m_aPointColor[(int)state] = value;
				return true;
			}
			return false;
		}

		bool CLineChartRenderer::setPointHoleColor(const PointState state, const Color &value)
		{
			if (value != m_aPointHoleColor[(int)state])
			{
				m_aPointHoleColor[(int)state] = value;
				return true;
			}
			return false;
		}

		bool CLineChartRenderer::setLineWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fLineWidth))
			{
				m_fLineWidth = value;
				return true;
			}
			return false;
		}

		bool CLineChartRenderer::setLineColor(const Color &value)
		{
			if (value != m_sLineColor)
			{
				m_sLineColor = value;
				return true;
			}
			return false;
		}

		bool CLineChartRenderer::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				return true;
			}
			return false;
		}

		bool CLineChartRenderer::setActivePoint(const int value)
		{
			if (value != m_iActivePoint)
			{
				m_iActivePoint = value;
				return true;
			}
			return false;
		}

		bool CLineChartRenderer::setVertical(const bool value)
		{
			if (value != m_bVertical)
			{
				m_bVertical = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CLineChartRenderer::CalculatePointData(IChartData *data, const PointF &xrange, const PointF &yrange, const PointF &view_size, std::vector<POINT_DATA> &point_data)
		{
			if (data->getCount() < 2)
				return;
			point_data.resize(data->getCount());
			static const Vec3f z{ 0, 0, 1 };
			Vec3f n, v1, v2, v, a1, a2, a3, a4, b1, b2, b3, b4, a21, a34, b21, b34, qa1, qa2, qb1, qb2;
			float hw{ m_fLineWidth * 0.5f }, da, db;
			for (int i = 0; i < data->getCount(); i++)
			{
				v1 = DataToView3D(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
				if (i == 0)
				{
					v2 = DataToView3D(PointF{ data->getX(i + 1), data->getY(i + 1) }, xrange, yrange, view_size);
					n = v2 - v1;
					n ^= z;
					ntl::Normalize<float>(n);
					v = v1 + n * hw;
					point_data[i].P1 = { v.X, v.Y };
					v = v1 - n * hw;
					point_data[i].P2 = { v.X, v.Y };
					continue;
				}
				if (i == data->getCount() - 1)
				{
					v2 = DataToView3D(PointF{ data->getX(i - 1), data->getY(i - 1) }, xrange, yrange, view_size);
					n = v1 - v2;
					n ^= z;
					ntl::Normalize<float>(n);
					v = v1 + n * hw;
					point_data[i].P1 = { v.X, v.Y };
					v = v1 - n * hw;
					point_data[i].P2 = { v.X, v.Y };
					continue;
				}
				v2 = DataToView3D(PointF{ data->getX(i - 1), data->getY(i - 1) }, xrange, yrange, view_size);
				n = v1 - v2;
				n ^= z;
				ntl::Normalize<float>(n);
				a1 = v2 + n * hw;
				a2 = v1 + n * hw;
				b1 = v2 - n * hw;
				b2 = v1 - n * hw;

				v2 = DataToView3D(PointF{ data->getX(i + 1), data->getY(i + 1) }, xrange, yrange, view_size);
				n = v2 - v1;
				n ^= z;
				ntl::Normalize<float>(n);
				a3 = v1 + n * hw;
				a4 = v2 + n * hw;
				b3 = v1 - n * hw;
				b4 = v2 - n * hw;

				if (ntl::IsEqual<float>(a2, a3) || ntl::IsEqual<float>(b2, b3))
				{
					point_data[i].P1 = PointF{ a2.X, a2.Y };
					point_data[i].P2 = PointF{ b2.X, b2.Y };
					continue;
				}
				a21 = a2 - a1;
				a34 = a3 - a4;
				b21 = b2 - b1;
				b34 = b3 - b4;
				qa1 = ntl::Normalized<float>(a21);
				qa2 = ntl::Normalized<float>(a34);
				qb1 = ntl::Normalized<float>(b21);
				qb2 = ntl::Normalized<float>(b34);
				da = qa1.Y * qa2.X - qa1.X * qa2.Y;
				db = qb1.Y * qb2.X - qb1.X * qb2.Y;
				if (ntl::IsZero<float>(da) || ntl::IsZero<float>(db) || (ntl::IsZero<float>(qa1.X) && ntl::IsZero<float>(qa2.X)) || (ntl::IsZero<float>(qb1.X) && ntl::IsZero<float>(qb2.X)))
				{
					point_data[i].P1 = PointF{ a2.X, a2.Y };
					point_data[i].P2 = PointF{ b2.X, b2.Y };
					continue;
				}
				point_data[i].P1.X = (a1.X * qa1.Y * qa2.X + (a4.Y - a1.Y) * qa1.X * qa2.X - a4.X * qa1.X * qa2.Y) / da;
				if (ntl::IsZero<float>(qa1.X))
					point_data[i].P1.Y = ((point_data[i].P1.X - a4.X) * qa2.Y) / qa2.X + a4.Y;
				else
					point_data[i].P1.Y = ((point_data[i].P1.X - a1.X) * qa1.Y) / qa1.X + a1.Y;
				point_data[i].P2.X = (b1.X * qb1.Y * qb2.X + (b4.Y - b1.Y) * qb1.X * qb2.X - b4.X * qb1.X * qb2.Y) / db;
				if (ntl::IsZero<float>(qb1.X))
					point_data[i].P2.Y = ((point_data[i].P2.X - b4.X) * qb2.Y) / qb2.X + b4.Y;
				else
					point_data[i].P2.Y = ((point_data[i].P2.X - b1.X) * qb1.Y) / qb1.X + b1.Y;
			}
		}
	#pragma endregion

	#pragma region Paint
		void CLineChartRenderer::Render(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange)
		{
			if (data->getCount() >= 2)
			{
				if (m_bDrawBackground && m_sBackgroundColor.A > 0)
					m_bVertical ? RenderBackgroundToY(renderer, texture, data, xrange, yrange) : RenderBackgroundToX(renderer, texture, data, xrange, yrange);
				if (m_bDrawLine && ntl::IsGreater<float>(m_fLineWidth, 0) && m_sLineColor.A > 0)
					RenderSpline(renderer, texture, data, xrange, yrange);
			}
			if (m_bDrawPoints && (ntl::IsGreater<float>(m_aPointSize[(int)PointState::Normal], 0) || ntl::IsGreater<float>(m_aPointSize[(int)PointState::Active], 0)) && (m_aPointColor[(int)PointState::Normal].A > 0 || m_aPointColor[(int)PointState::Active].A > 0))
				RenderPoints(renderer, texture, data, xrange, yrange);
		}

		void CLineChartRenderer::RenderPoints(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange)
		{
			Gradient gn, ga;
			gn.setType(GradientType::Circle);
			ga.setType(GradientType::Circle);
			if (ntl::IsGreater<float>(m_aPointHole[(int)PointState::Normal], 0) && ntl::IsGreater<float>(m_aPointSize[(int)PointState::Normal], 0))
			{
				gn.setPointCount(4);
				gn.setPoint(0, Color1D{ 0, m_aPointHoleColor[(int)PointState::Normal] });
				gn.setPoint(1, Color1D{ m_aPointHole[(int)PointState::Normal] / m_aPointSize[(int)PointState::Normal] - 0.000001f, m_aPointHoleColor[(int)PointState::Normal] });
				gn.setPoint(2, Color1D{ m_aPointHole[(int)PointState::Normal] / m_aPointSize[(int)PointState::Normal], m_aPointColor[(int)PointState::Normal] });
				gn.setPoint(3, Color1D{ 1, m_aPointColor[(int)PointState::Normal] });
			}
			else
				gn.setPoints(Color1DArray{ Color1D{ 0, m_aPointColor[(int)PointState::Normal] }, Color1D{ 1, m_aPointColor[(int)PointState::Normal] } });
			if (ntl::IsGreater<float>(m_aPointHole[(int)PointState::Active], 0) && ntl::IsGreater<float>(m_aPointSize[(int)PointState::Active], 0))
			{
				ga.setPointCount(4);
				ga.setPoint(0, Color1D{ 0, m_aPointHoleColor[(int)PointState::Active] });
				ga.setPoint(1, Color1D{ m_aPointHole[(int)PointState::Active] / m_aPointSize[(int)PointState::Active] - 0.000001f, m_aPointHoleColor[(int)PointState::Active] });
				ga.setPoint(2, Color1D{ m_aPointHole[(int)PointState::Active] / m_aPointSize[(int)PointState::Active], m_aPointColor[(int)PointState::Active] });
				ga.setPoint(3, Color1D{ 1, m_aPointColor[(int)PointState::Active] });
			}
			else
				ga.setPoints(Color1DArray{ Color1D{ 0, m_aPointColor[(int)PointState::Active] }, Color1D{ 1, m_aPointColor[(int)PointState::Active] } });
			RectF r;
			float hsn{ m_aPointSize[(int)PointState::Normal] * 0.5f }, hsa{ m_aPointSize[(int)PointState::Active] * 0.5f };
			PointF view_size{ texture->Widthf, texture->Heightf }, p;
			for (int i = 0; i < data->getCount(); i++)
			{
				p = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
				if (i == m_iActivePoint)
				{
					if (ntl::IsGreater<float>(m_aPointSize[(int)PointState::Active], 0))
					{
						r.Left = p.X - hsa;
						r.Top = p.Y - hsa;
						r.Right = r.Left + m_aPointSize[(int)PointState::Active];
						r.Bottom = r.Top + m_aPointSize[(int)PointState::Active];
						renderer->DrawGradient(r, ga);
					}
				}
				else
				{
					if (ntl::IsGreater<float>(m_aPointSize[(int)PointState::Normal], 0))
					{
						r.Left = p.X - hsn;
						r.Top = p.Y - hsn;
						r.Right = r.Left + m_aPointSize[(int)PointState::Normal];
						r.Bottom = r.Top + m_aPointSize[(int)PointState::Normal];
						renderer->DrawGradient(r, gn);
					}
				}
			}
		}

		void CLineChartRenderer::RenderSpline(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange)
		{
			PointF view_size{ texture->Widthf, texture->Heightf };
			if (ntl::IsGreater<float>(m_fLineWidth, 1))
			{
				std::vector<POINT_DATA> point_data;
				CalculatePointData(data, xrange, yrange, view_size, point_data);
				for (int i = 1; i < data->getCount(); i++)
					renderer->DrawPolygon({ point_data[i - 1].P1, point_data[i].P1, point_data[i].P2, point_data[i - 1].P2 }, m_sLineColor);
			}
			else
			{
				PointF prev, point;
				for (int i = 1; i < data->getCount(); i++)
				{
					prev = DataToView(PointF{ data->getX(i - 1), data->getY(i - 1) }, xrange, yrange, view_size);
					point = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
					renderer->DrawLine(prev, point, m_sLineColor);
				}
			}
		}

		void CLineChartRenderer::RenderBackgroundToX(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange)
		{
			CStoreSplineLimits s_limits{ renderer };
			PointF view_size{ texture->Widthf, texture->Heightf };
			float zero{ ntl::Clamp<float>(DataYToView(0, yrange, view_size.Y), 0.0f, view_size.Y - 1) };
			CubicBezierSplineLimits limits;
			limits.isY = true;
			limits.Spline2 = CubicBezierSpline{ PointF{ 0, zero }, PointF{ 0, zero }, PointF{ view_size.X, zero }, PointF{ view_size.X, zero } };
			for (int i = 1; i < data->getCount(); i++)
			{
				limits.Spline1.P1 = limits.Spline1.C1 = DataToView(PointF{ data->getX(i - 1), data->getY(i - 1) }, xrange, yrange, view_size);
				limits.Spline1.P2 = limits.Spline1.C2 = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
				renderer
					->ActivateSplineLimits(&limits)
					->DrawRectangle(RectF{ ntl::Min<float>(limits.Spline1.P1.X, limits.Spline1.P2.X), 0, ntl::Max<float>(limits.Spline1.P1.X, limits.Spline1.P2.X), texture->Heightf }, m_sBackgroundColor);
			}
		}

		void CLineChartRenderer::RenderBackgroundToY(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange)
		{
			CStoreSplineLimits s_limits{ renderer };
			PointF view_size{ texture->Widthf, texture->Heightf };
			float zero{ ntl::Clamp<float>(DataXToView(0, xrange, view_size.X), 0.0f, view_size.X - 1) };
			CubicBezierSplineLimits limits;
			limits.isY = false;
			limits.Spline2 = CubicBezierSpline{ PointF{ zero, 0 }, PointF{ zero, 0 }, PointF{ zero, view_size.Y }, PointF{ zero, view_size.Y } };
			for (int i = 1; i < data->getCount(); i++)
			{
				limits.Spline1.P1 = limits.Spline1.C1 = DataToView(PointF{ data->getX(i - 1), data->getY(i - 1) }, xrange, yrange, view_size);
				limits.Spline1.P2 = limits.Spline1.C2 = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
				renderer
					->ActivateSplineLimits(&limits)
					->DrawRectangle(RectF{ 0, ntl::Min<float>(limits.Spline1.P1.Y, limits.Spline1.P2.Y), texture->Widthf, ntl::Max<float>(limits.Spline1.P1.Y, limits.Spline1.P2.Y) }, m_sBackgroundColor);
			}
		}
	#pragma endregion
	}
}