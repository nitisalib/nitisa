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
		CBezierChartRenderer::CBezierChartRenderer() :
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
			m_fTension{ 0.4f },
			m_iActivePoint{ -1 },
			m_bVertical{ false },
			m_iCurveRecursionLimit{ 16 },
			m_fDistanceTolerance{ 0.5f },
			m_fAngleTolerance{ ntl::DegToRad<float>(1.0f) },
			m_fCuspLimit{ ntl::DegToRad<float>(1.0f) },
			m_fCurveAngleTolerance{ ntl::DegToRad<float>(1.0f) },
			m_fCurveCollinearityTolerance{ 1 }
		{

		}

		void CBezierChartRenderer::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Getters
		bool CBezierChartRenderer::isDrawPoints() const
		{
			return m_bDrawPoints;
		}

		bool CBezierChartRenderer::isDrawLine() const
		{
			return m_bDrawLine;
		}

		bool CBezierChartRenderer::isDrawBackground() const
		{
			return m_bDrawBackground;
		}

		float CBezierChartRenderer::getPointSize(const PointState state) const
		{
			return m_aPointSize[(int)state];
		}

		float CBezierChartRenderer::getPointHole(const PointState state) const
		{
			return m_aPointHole[(int)state];
		}

		Color CBezierChartRenderer::getPointColor(const PointState state) const
		{
			return m_aPointColor[(int)state];
		}

		Color CBezierChartRenderer::getPointHoleColor(const PointState state) const
		{
			return m_aPointHoleColor[(int)state];
		}

		float CBezierChartRenderer::getLineWidth() const
		{
			return m_fLineWidth;
		}

		Color CBezierChartRenderer::getLineColor() const
		{
			return m_sLineColor;
		}

		Color CBezierChartRenderer::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		float CBezierChartRenderer::getTension() const
		{
			return m_fTension;
		}

		int CBezierChartRenderer::getActivePoint() const
		{
			return m_iActivePoint;
		}

		bool CBezierChartRenderer::isVertical() const
		{
			return m_bVertical;
		}

		int CBezierChartRenderer::getCurveRecursionLimit() const
		{
			return m_iCurveRecursionLimit;
		}

		float CBezierChartRenderer::getDistanceTolerance() const
		{
			return m_fDistanceTolerance;
		}

		float CBezierChartRenderer::getAngleTolerance() const
		{
			return m_fAngleTolerance;
		}

		float CBezierChartRenderer::getCuspLimit() const
		{
			return m_fCuspLimit;
		}

		float CBezierChartRenderer::getCurveAngleTolerance() const
		{
			return m_fCurveAngleTolerance;
		}

		float CBezierChartRenderer::getCurveCollinearityTolerance() const
		{
			return m_fCurveCollinearityTolerance;
		}
	#pragma endregion

	#pragma region Setters
		bool CBezierChartRenderer::setDrawPoints(const bool value)
		{
			if (value != m_bDrawPoints)
			{
				m_bDrawPoints = value;
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setDrawLine(const bool value)
		{
			if (value != m_bDrawLine)
			{
				m_bDrawLine = value;
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setDrawBackground(const bool value)
		{
			if (value != m_bDrawBackground)
			{
				m_bDrawBackground = value;
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setPointSize(const PointState state, const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_aPointSize[(int)state]))
			{
				m_aPointSize[(int)state] = value;
				if (ntl::IsGreaterOrEqual<float>(m_aPointHole[(int)state], value))
					m_aPointHole[(int)state] = ntl::Max<float>(0.0f, m_aPointSize[(int)state] - 1);
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setPointHole(const PointState state, const float value)
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

		bool CBezierChartRenderer::setPointColor(const PointState state, const Color &value)
		{
			if (value != m_aPointColor[(int)state])
			{
				m_aPointColor[(int)state] = value;
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setPointHoleColor(const PointState state, const Color &value)
		{
			if (value != m_aPointHoleColor[(int)state])
			{
				m_aPointHoleColor[(int)state] = value;
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setLineWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fLineWidth))
			{
				m_fLineWidth = value;
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setLineColor(const Color &value)
		{
			if (value != m_sLineColor)
			{
				m_sLineColor = value;
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setTension(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fTension))
			{
				m_fTension = value;
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setActivePoint(const int value)
		{
			if (value != m_iActivePoint)
			{
				m_iActivePoint = value;
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setVertical(const bool value)
		{
			if (value != m_bVertical)
			{
				m_bVertical = value;
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setCurveRecursionLimit(const int value)
		{
			if (value >= 1 && value != m_iCurveRecursionLimit)
			{
				m_iCurveRecursionLimit = value;
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setDistanceTolerance(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fDistanceTolerance))
			{
				m_fDistanceTolerance = value;
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setAngleTolerance(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fAngleTolerance))
			{
				m_fAngleTolerance = value;
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setCuspLimit(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fCuspLimit))
			{
				m_fCuspLimit = value;
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setCurveAngleTolerance(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fCurveAngleTolerance))
			{
				m_fCurveAngleTolerance = value;
				return true;
			}
			return false;
		}

		bool CBezierChartRenderer::setCurveCollinearityTolerance(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fCurveCollinearityTolerance))
			{
				m_fCurveCollinearityTolerance = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CBezierChartRenderer::CalculatePointData(IChartData *data, const PointF &xrange, const PointF &yrange, const PointF &texture_size, std::vector<POINT_DATA> &point_data)
		{
			point_data.resize(data->getCount());
			PointF prev, point, next;
			for (int i = 0; i < data->getCount(); i++)
			{
				point = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, texture_size);
				prev = (i == 0) ? point : DataToView(PointF{ data->getX(i - 1), data->getY(i - 1) }, xrange, yrange, texture_size);
				next = (i == data->getCount() - 1) ? point : DataToView(PointF{ data->getX(i + 1), data->getY(i + 1) }, xrange, yrange, texture_size);
				Bezier(prev, point, next, m_fTension, point_data[i].cp1, point_data[i].cp2);
			}
		}
	#pragma endregion

	#pragma region Paint
		void CBezierChartRenderer::Render(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange)
		{
			if (data->getCount() >= 2)
			{
				std::vector<POINT_DATA> point_data;
				CalculatePointData(data, xrange, yrange, PointF{ texture->Widthf, texture->Heightf }, point_data);
				if (m_bDrawBackground && m_sBackgroundColor.A > 0)
					m_bVertical ? RenderBackgroundToY(renderer, texture, data, xrange, yrange, point_data) : RenderBackgroundToX(renderer, texture, data, xrange, yrange, point_data);
				if (m_bDrawLine && ntl::IsGreater<float>(m_fLineWidth, 0) && m_sLineColor.A > 0)
					RenderSpline(renderer, texture, data, xrange, yrange, point_data);
			}
			if (m_bDrawPoints && (ntl::IsGreater<float>(m_aPointSize[(int)PointState::Normal], 0) ||
				ntl::IsGreater<float>(m_aPointSize[(int)PointState::Active], 0)) && (m_aPointColor[(int)PointState::Normal].A > 0 || m_aPointColor[(int)PointState::Active].A > 0))
				RenderPoints(renderer, texture, data, xrange, yrange);
		}

		void CBezierChartRenderer::RenderPoints(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange)
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
			PointF view_size{ texture->Widthf, texture->Heightf }, p;
			float hsn{ m_aPointSize[(int)PointState::Normal] * 0.5f }, hsa{ m_aPointSize[(int)PointState::Active] * 0.5f };
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

		void CBezierChartRenderer::RenderSpline(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange, const std::vector<POINT_DATA> &point_data)
		{
			PointF view_size{ texture->Widthf, texture->Heightf };
			std::vector<PointF> points;
			if (ntl::IsGreater<float>(m_fLineWidth, 1))
			{
				std::vector<std::vector<PointF>> polygons;
				static const Vec3f z{ 0, 0, 1 };
				Vec3f n, v1, v2, v, a1, a2, a3, a4, b1, b2, b3, b4, a21, a34, b21, b34, qa1, qa2, qb1, qb2;
				float hw{ m_fLineWidth * 0.5f }, da, db;
				struct POINT_DATA
				{
					PointF P1;
					PointF P2;
				};
				std::vector<POINT_DATA> polygon_points;

				PointF prev, point;
				for (int i = 1; i < data->getCount(); i++)
				{
					prev = DataToView(PointF{ data->getX(i - 1), data->getY(i - 1) }, xrange, yrange, view_size);
					point = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
					if (i == 1)
						points.push_back(prev);
					BezierSubdivide(prev, point_data[i - 1].cp2, point_data[i].cp1, point, points, m_iCurveRecursionLimit, m_fDistanceTolerance, m_fAngleTolerance, m_fCuspLimit,
						m_fCurveAngleTolerance, m_fCurveCollinearityTolerance);
					points.push_back(point);
				}
				polygon_points.resize(points.size());
				for (size_t j = 0; j < points.size(); j++)
				{
					v1 = { points[j].X, points[j].Y, 0 };
					if (j == 0)
					{
						v2 = { points[j + 1].X, points[j + 1].Y, 0 };
						n = v2 - v1;
						n ^= z;
						ntl::Normalize<float>(n);
						v = v1 + n * hw;
						polygon_points[j].P1 = PointF{ v.X, v.Y };
						v = v1 - n * hw;
						polygon_points[j].P2 = PointF{ v.X, v.Y };
						continue;
					}
					if (j == points.size() - 1)
					{
						v2 = { points[j - 1].X, points[j - 1].Y, 0 };
						n = v1 - v2;
						n ^= z;
						ntl::Normalize<float>(n);
						v = v1 + n * hw;
						polygon_points[j].P1 = PointF{ v.X, v.Y };
						v = v1 - n * hw;
						polygon_points[j].P2 = PointF{ v.X, v.Y };
						continue;
					}
					v2 = { points[j - 1].X, points[j - 1].Y, 0 };
					n = v1 - v2;
					n ^= z;
					ntl::Normalize<float>(n);
					a1 = v2 + n * hw;
					a2 = v1 + n * hw;
					b1 = v2 - n * hw;
					b2 = v1 - n * hw;

					v2 = { points[j + 1].X, points[j + 1].Y, 0 };
					n = v2 - v1;
					n ^= z;
					ntl::Normalize<float>(n);
					a3 = v1 + n * hw;
					a4 = v2 + n * hw;
					b3 = v1 - n * hw;
					b4 = v2 - n * hw;

					if (ntl::IsEqual<float>(a2, a3) || ntl::IsEqual<float>(b2, b3))
					{
						polygon_points[j].P1 = PointF{ a2.X, a2.Y };
						polygon_points[j].P2 = PointF{ b2.X, b2.Y };
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
						polygon_points[j].P1 = PointF{ a2.X, a2.Y };
						polygon_points[j].P2 = PointF{ b2.X, b2.Y };
						continue;
					}
					polygon_points[j].P1.X = (a1.X * qa1.Y * qa2.X + (a4.Y - a1.Y) * qa1.X * qa2.X - a4.X * qa1.X * qa2.Y) / da;
					if (ntl::IsZero<float>(qa1.X))
						polygon_points[j].P1.Y = ((polygon_points[j].P1.X - a4.X) * qa2.Y) / qa2.X + a4.Y;
					else
						polygon_points[j].P1.Y = ((polygon_points[j].P1.X - a1.X) * qa1.Y) / qa1.X + a1.Y;
					polygon_points[j].P2.X = (b1.X * qb1.Y * qb2.X + (b4.Y - b1.Y) * qb1.X * qb2.X - b4.X * qb1.X * qb2.Y) / db;
					if (ntl::IsZero<float>(qb1.X))
						polygon_points[j].P2.Y = ((polygon_points[j].P2.X - b4.X) * qb2.Y) / qb2.X + b4.Y;
					else
						polygon_points[j].P2.Y = ((polygon_points[j].P2.X - b1.X) * qb1.Y) / qb1.X + b1.Y;
				}
				polygons.resize(polygon_points.size() - 1);
				for (size_t j = 1; j < polygon_points.size(); j++)
				{
					polygons[j - 1].resize(4);
					polygons[j - 1][0] = polygon_points[j - 1].P1;
					polygons[j - 1][1] = polygon_points[j].P1;
					polygons[j - 1][2] = polygon_points[j].P2;
					polygons[j - 1][3] = polygon_points[j - 1].P2;
				}
				renderer->DrawPolygons(polygons, m_sLineColor);
			}
			else
			{
				std::vector<PointF> line_points;
				PointF prev, point;
				for (int i = 1; i < data->getCount(); i++)
				{
					prev = DataToView(PointF{ data->getX(i - 1), data->getY(i - 1) }, xrange, yrange, view_size);
					point = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
					if (i == 1)
						points.push_back(prev);
					BezierSubdivide(prev, point_data[i - 1].cp2, point_data[i].cp1, point, points, m_iCurveRecursionLimit, m_fDistanceTolerance, m_fAngleTolerance, m_fCuspLimit,
						m_fCurveAngleTolerance, m_fCurveCollinearityTolerance);
					points.push_back(point);
				}
				line_points.resize(points.size());
				for (size_t j = 0; j < points.size(); j++)
					line_points[j] = points[j];
				renderer->DrawLines(line_points, Color{ 0, 0, 0, 255 }, false);
			}
		}

		void CBezierChartRenderer::RenderBackgroundToX(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange, const std::vector<POINT_DATA> &point_data)
		{
			CStoreSplineLimits s_limits{ renderer };
			PointF view_size{ texture->Widthf, texture->Heightf };
			float zero{ ntl::Clamp<float>(DataYToView(0, yrange, view_size.Y), 0.0f, view_size.Y - 1) };
			CubicBezierSplineLimits limits;
			limits.isY = true;
			limits.Spline2 = CubicBezierSpline{ PointF{ 0, zero }, PointF{ 0, zero }, PointF{ view_size.X, zero }, PointF{ view_size.X, zero } };
			for (int i = 1; i < data->getCount(); i++)
			{
				limits.Spline1.P1 = DataToView(PointF{ data->getX(i - 1), data->getY(i - 1) }, xrange, yrange, view_size);
				limits.Spline1.P2 = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
				limits.Spline1.C1 = point_data[i - 1].cp2;
				limits.Spline1.C2 = point_data[i].cp1;
				renderer
					->ActivateSplineLimits(&limits)
					->DrawRectangle(RectF{ ntl::Min<float>(limits.Spline1.P1.X, limits.Spline1.P2.X), 0, ntl::Max<float>(limits.Spline1.P1.X, limits.Spline1.P2.X), texture->Heightf }, m_sBackgroundColor);
			}
		}

		void CBezierChartRenderer::RenderBackgroundToY(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange, const std::vector<POINT_DATA> &point_data)
		{
			CStoreSplineLimits s_limits{ renderer };
			PointF view_size{ texture->Widthf, texture->Heightf };
			float zero{ ntl::Clamp<float>(DataXToView(0, xrange, view_size.X), 0.0f, view_size.X - 1) };
			CubicBezierSplineLimits limits;
			limits.isY = false; 
			limits.Spline2 = CubicBezierSpline{ PointF{ zero, 0 }, PointF{ zero, 0 }, PointF{ zero, view_size.Y }, PointF{ zero, view_size.Y } };
			for (int i = 1; i < data->getCount(); i++)
			{
				limits.Spline1.P1 = DataToView(PointF{ data->getX(i - 1), data->getY(i - 1) }, xrange, yrange, view_size);
				limits.Spline1.P2 = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
				limits.Spline1.C1 = point_data[i - 1].cp2;
				limits.Spline1.C2 = point_data[i].cp1;
				renderer
					->ActivateSplineLimits(&limits)
					->DrawRectangle(RectF{ 0, ntl::Min<float>(limits.Spline1.P1.Y, limits.Spline1.P2.Y), texture->Widthf, ntl::Max<float>(limits.Spline1.P1.Y, limits.Spline1.P2.Y) }, m_sBackgroundColor);
			}
		}
	#pragma endregion
	}
}