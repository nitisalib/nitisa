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
		CSteppedLineChartRenderer::CSteppedLineChartRenderer() :
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
			m_bVertical{ false },
			m_eInterpolationPosition{ LineInterpolationPosition::Middle }
		{

		}

		void CSteppedLineChartRenderer::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Getters
		bool CSteppedLineChartRenderer::isDrawPoints() const
		{
			return m_bDrawPoints;
		}

		bool CSteppedLineChartRenderer::isDrawLine() const
		{
			return m_bDrawLine;
		}

		bool CSteppedLineChartRenderer::isDrawBackground() const
		{
			return m_bDrawBackground;
		}

		float CSteppedLineChartRenderer::getPointSize(const PointState state) const
		{
			return m_aPointSize[(int)state];
		}

		float CSteppedLineChartRenderer::getPointHole(const PointState state) const
		{
			return m_aPointHole[(int)state];
		}

		Color CSteppedLineChartRenderer::getPointColor(const PointState state) const
		{
			return m_aPointColor[(int)state];
		}

		Color CSteppedLineChartRenderer::getPointHoleColor(const PointState state) const
		{
			return m_aPointHoleColor[(int)state];
		}

		float CSteppedLineChartRenderer::getLineWidth() const
		{
			return m_fLineWidth;
		}

		Color CSteppedLineChartRenderer::getLineColor() const
		{
			return m_sLineColor;
		}

		Color CSteppedLineChartRenderer::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		int CSteppedLineChartRenderer::getActivePoint() const
		{
			return m_iActivePoint;
		}

		bool CSteppedLineChartRenderer::isVertical() const
		{
			return m_bVertical;
		}

		LineInterpolationPosition CSteppedLineChartRenderer::getInterpolationPosition() const
		{
			return m_eInterpolationPosition;
		}
	#pragma endregion

	#pragma region Setters
		bool CSteppedLineChartRenderer::setDrawPoints(const bool value)
		{
			if (value != m_bDrawPoints)
			{
				m_bDrawPoints = value;
				return true;
			}
			return false;
		}

		bool CSteppedLineChartRenderer::setDrawLine(const bool value)
		{
			if (value != m_bDrawLine)
			{
				m_bDrawLine = value;
				return true;
			}
			return false;
		}

		bool CSteppedLineChartRenderer::setDrawBackground(const bool value)
		{
			if (value != m_bDrawBackground)
			{
				m_bDrawBackground = value;
				return true;
			}
			return false;
		}

		bool CSteppedLineChartRenderer::setPointSize(const PointState state, const float value)
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

		bool CSteppedLineChartRenderer::setPointHole(const PointState state, const float value)
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

		bool CSteppedLineChartRenderer::setPointColor(const PointState state, const Color &value)
		{
			if (value != m_aPointColor[(int)state])
			{
				m_aPointColor[(int)state] = value;
				return true;
			}
			return false;
		}

		bool CSteppedLineChartRenderer::setPointHoleColor(const PointState state, const Color &value)
		{
			if (value != m_aPointHoleColor[(int)state])
			{
				m_aPointHoleColor[(int)state] = value;
				return true;
			}
			return false;
		}

		bool CSteppedLineChartRenderer::setLineWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fLineWidth))
			{
				m_fLineWidth = value;
				return true;
			}
			return false;
		}

		bool CSteppedLineChartRenderer::setLineColor(const Color &value)
		{
			if (value != m_sLineColor)
			{
				m_sLineColor = value;
				return true;
			}
			return false;
		}

		bool CSteppedLineChartRenderer::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				return true;
			}
			return false;
		}

		bool CSteppedLineChartRenderer::setActivePoint(const int value)
		{
			if (value != m_iActivePoint)
			{
				m_iActivePoint = value;
				return true;
			}
			return false;
		}

		bool CSteppedLineChartRenderer::setVertical(const bool value)
		{
			if (value != m_bVertical)
			{
				m_bVertical = value;
				return true;
			}
			return false;
		}

		bool CSteppedLineChartRenderer::setInterpolationPosition(const LineInterpolationPosition value)
		{
			if (value != m_eInterpolationPosition)
			{
				m_eInterpolationPosition = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CSteppedLineChartRenderer::TransformBeforeH(IChartData *data, const PointF &xrange, const PointF &yrange, const PointF &view_size, std::vector<POINT_DATA> &point_data)
		{
			point_data.resize(data->getCount() * 2 - 1);
			point_data[0].P0 = DataToView(PointF{ data->getX(0), data->getY(0) }, xrange, yrange, view_size);
			size_t index{ 1 };
			for (int i = 1; i < data->getCount(); i++)
			{
				point_data[index + 1].P0 = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
				point_data[index + 0].P0 = PointF{ point_data[index + 1].P0.X, point_data[index - 1].P0.Y };
				index += 2;
			}
		}

		void CSteppedLineChartRenderer::TransformMiddleH(IChartData *data, const PointF &xrange, const PointF &yrange, const PointF &view_size, std::vector<POINT_DATA> &point_data)
		{
			point_data.resize(data->getCount() + (data->getCount() - 1) * 2);
			point_data[0].P0 = DataToView(PointF{ data->getX(0), data->getY(0) }, xrange, yrange, view_size);
			size_t index{ 1 };
			for (int i = 1; i < data->getCount(); i++)
			{
				point_data[index + 2].P0 = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
				point_data[index + 0].P0 = PointF{ (point_data[index - 1].P0.X + point_data[index + 2].P0.X) * 0.5f, point_data[index - 1].P0.Y };
				point_data[index + 1].P0 = PointF{ point_data[index + 0].P0.X, point_data[index + 2].P0.Y };
				index += 3;
			}
		}

		void CSteppedLineChartRenderer::TransformAfterH(IChartData *data, const PointF &xrange, const PointF &yrange, const PointF &view_size, std::vector<POINT_DATA> &point_data)
		{
			point_data.resize(data->getCount() * 2 - 1);
			point_data[0].P0 = DataToView(PointF{ data->getX(0), data->getY(0) }, xrange, yrange, view_size);
			size_t index{ 1 };
			for (int i = 1; i < data->getCount(); i++)
			{
				point_data[index + 1].P0 = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
				point_data[index + 0].P0 = PointF{ point_data[index - 1].P0.X, point_data[index + 1].P0.Y };
				index += 2;
			}
		}

		void CSteppedLineChartRenderer::TransformBeforeV(IChartData *data, const PointF &xrange, const PointF &yrange, const PointF &view_size, std::vector<POINT_DATA> &point_data)
		{
			point_data.resize(data->getCount() * 2 - 1);
			point_data[0].P0 = DataToView(PointF{ data->getX(0), data->getY(0) }, xrange, yrange, view_size);
			size_t index{ 1 };
			for (int i = 1; i < data->getCount(); i++)
			{
				point_data[index + 1].P0 = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
				point_data[index + 0].P0 = PointF{ point_data[index - 1].P0.X, point_data[index + 1].P0.Y };
				index += 2;
			}
		}

		void CSteppedLineChartRenderer::TransformMiddleV(IChartData *data, const PointF &xrange, const PointF &yrange, const PointF &view_size, std::vector<POINT_DATA> &point_data)
		{
			point_data.resize(data->getCount() + (data->getCount() - 1) * 2);
			point_data[0].P0 = DataToView(PointF{ data->getX(0), data->getY(0) }, xrange, yrange, view_size);
			size_t index{ 1 };
			for (int i = 1; i < data->getCount(); i++)
			{
				point_data[index + 2].P0 = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
				point_data[index + 0].P0 = PointF{ point_data[index - 1].P0.X, (point_data[index - 1].P0.Y + point_data[index + 2].P0.Y) * 0.5f  };
				point_data[index + 1].P0 = PointF{ point_data[index + 2].P0.X, point_data[index + 0].P0.Y };
				index += 3;
			}
		}

		void CSteppedLineChartRenderer::TransformAfterV(IChartData *data, const PointF &xrange, const PointF &yrange, const PointF &view_size, std::vector<POINT_DATA> &point_data)
		{
			point_data.resize(data->getCount() * 2 - 1);
			point_data[0].P0 = DataToView(PointF{ data->getX(0), data->getY(0) }, xrange, yrange, view_size);
			size_t index{ 1 };
			for (int i = 1; i < data->getCount(); i++)
			{
				point_data[index + 1].P0 = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
				point_data[index + 0].P0 = PointF{ point_data[index + 1].P0.X, point_data[index - 1].P0.Y };
				index += 2;
			}
		}

		void CSteppedLineChartRenderer::CalculatePointData(std::vector<POINT_DATA> &point_data)
		{
			static const Vec3f z{ 0, 0, 1 };
			Vec3f n, v1, v2, v, a1, a2, a3, a4, b1, b2, b3, b4, a21, a34, b21, b34, qa1, qa2, qb1, qb2;
			float hw{ m_fLineWidth * 0.5f }, da, db;
			for (size_t i = 0; i < point_data.size(); i++)
			{
				v1 = { point_data[i].P0.X, point_data[i].P0.Y, 0 };
				if (i == 0)
				{
					v2 = { point_data[i + 1].P0.X, point_data[i + 1].P0.Y, 0 };
					n = v2 - v1;
					n ^= z;
					ntl::Normalize<float>(n);
					v = v1 + n * hw;
					point_data[i].P1 = { v.X, v.Y };
					v = v1 - n * hw;
					point_data[i].P2 = { v.X, v.Y };
					continue;
				}
				if (i == point_data.size() - 1)
				{
					v2 = { point_data[i - 1].P0.X, point_data[i - 1].P0.Y, 0 };
					n = v1 - v2;
					n ^= z;
					ntl::Normalize<float>(n);
					v = v1 + n * hw;
					point_data[i].P1 = { v.X, v.Y };
					v = v1 - n * hw;
					point_data[i].P2 = { v.X, v.Y };
					continue;
				}
				v2 = { point_data[i - 1].P0.X, point_data[i - 1].P0.Y, 0 };
				n = v1 - v2;
				n ^= z;
				ntl::Normalize<float>(n);
				a1 = v2 + n * hw;
				a2 = v1 + n * hw;
				b1 = v2 - n * hw;
				b2 = v1 - n * hw;

				v2 = { point_data[i + 1].P0.X, point_data[i + 1].P0.Y, 0 };
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
		void CSteppedLineChartRenderer::Render(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange)
		{
			if (data->getCount() >= 2)
			{
				PointF view_size{ texture->Widthf, texture->Heightf };
				std::vector<POINT_DATA> point_data;
				switch (m_eInterpolationPosition)
				{
				case LineInterpolationPosition::Before:
					m_bVertical ? TransformBeforeV(data, xrange, yrange, view_size, point_data) : TransformBeforeH(data, xrange, yrange, view_size, point_data);
					break;
				case LineInterpolationPosition::After:
					m_bVertical ? TransformAfterV(data, xrange, yrange, view_size, point_data) : TransformAfterH(data, xrange, yrange, view_size, point_data);
					break;
				default:
					m_bVertical ? TransformMiddleV(data, xrange, yrange, view_size, point_data) : TransformMiddleH(data, xrange, yrange, view_size, point_data);
				}

				if (m_bDrawBackground && m_sBackgroundColor.A > 0)
					m_bVertical ? RenderBackgroundV(renderer, view_size, data, xrange, yrange, point_data) : RenderBackgroundH(renderer, view_size, data, xrange, yrange, point_data);
				if (m_bDrawLine && ntl::IsGreater<float>(m_fLineWidth, 0) && m_sLineColor.A > 0)
					RenderSpline(renderer, point_data);
			}
			if (m_bDrawPoints && (ntl::IsGreater<float>(m_aPointSize[(int)PointState::Normal], 0) || ntl::IsGreater<float>(m_aPointSize[(int)PointState::Active], 0)) && (m_aPointColor[(int)PointState::Normal].A > 0 || m_aPointColor[(int)PointState::Active].A > 0))
				RenderPoints(renderer, texture, data, xrange, yrange);
		}

		void CSteppedLineChartRenderer::RenderPoints(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange)
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

		void CSteppedLineChartRenderer::RenderSpline(IRenderer *renderer, std::vector<POINT_DATA> &point_data)
		{
			if (ntl::IsGreater<float>(m_fLineWidth, 1))
			{
				CalculatePointData(point_data);
				for (size_t i = 1; i < point_data.size(); i++)
					renderer->DrawPolygon({ point_data[i - 1].P1, point_data[i].P1, point_data[i].P2, point_data[i - 1].P2 }, m_sLineColor);
			}
			else
			{
				for (size_t i = 1; i < point_data.size(); i++)
					renderer->DrawLine(PointF{ point_data[i - 1].P0.X, point_data[i - 1].P0.Y }, PointF{ point_data[i].P0.X, point_data[i].P0.Y }, m_sLineColor);
			}
		}

		void CSteppedLineChartRenderer::RenderBackgroundH(IRenderer *renderer, const PointF &view_size, IChartData *data, const PointF &xrange, const PointF &yrange, const std::vector<POINT_DATA> &point_data)
		{
			float zero{ ntl::Clamp<float>(DataYToView(0, yrange, view_size.Y), 0.0f, view_size.Y - 1) };
			size_t index;
			RectF rect;
			switch (m_eInterpolationPosition)
			{
			case LineInterpolationPosition::Before:
				index = 1;
				while (index < point_data.size())
				{
					rect.Left = ntl::Min<float>(point_data[index - 1].P0.X, point_data[index].P0.X);
					rect.Right = ntl::Max<float>(point_data[index - 1].P0.X, point_data[index].P0.X);
					rect.Top = ntl::Min<float>(point_data[index - 1].P0.Y, zero);
					rect.Bottom = ntl::Max<float>(point_data[index - 1].P0.Y, zero);
					if (!rect.is_zero())
						renderer->DrawRectangle(rect, m_sBackgroundColor);
					index += 2;
				}
				break;
			case LineInterpolationPosition::Middle:
				rect.Left = ntl::Min<float>(point_data[0].P0.X, point_data[1].P0.X);
				rect.Right = ntl::Max<float>(point_data[0].P0.X, point_data[1].P0.X);
				rect.Top = ntl::Min<float>(point_data[0].P0.Y, zero);
				rect.Bottom = ntl::Max<float>(point_data[0].P0.Y, zero);
				if (!rect.is_zero())
					renderer->DrawRectangle(rect, m_sBackgroundColor);

				index = point_data.size() - 1;
				rect.Left = ntl::Min<float>(point_data[index - 1].P0.X, point_data[index].P0.X);
				rect.Right = ntl::Max<float>(point_data[index - 1].P0.X, point_data[index].P0.X);
				rect.Top = ntl::Min<float>(point_data[index].P0.Y, zero);
				rect.Bottom = ntl::Max<float>(point_data[index].P0.Y, zero);
				if (!rect.is_zero())
					renderer->DrawRectangle(rect, m_sBackgroundColor);

				index = 2;
				while (index < point_data.size() - 2)
				{
					rect.Left = ntl::Min<float>(point_data[index].P0.X, point_data[index + 2].P0.X);
					rect.Right = ntl::Max<float>(point_data[index].P0.X, point_data[index + 2].P0.X);
					rect.Top = ntl::Min<float>(point_data[index].P0.Y, zero);
					rect.Bottom = ntl::Max<float>(point_data[index].P0.Y, zero);
					if (!rect.is_zero())
						renderer->DrawRectangle(rect, m_sBackgroundColor);
					index += 3;
				}
				break;
			case LineInterpolationPosition::After:
				index = 2;
				while (index < point_data.size())
				{
					rect.Left = ntl::Min<float>(point_data[index - 1].P0.X, point_data[index].P0.X);
					rect.Right = ntl::Max<float>(point_data[index - 1].P0.X, point_data[index].P0.X);
					rect.Top = ntl::Min<float>(point_data[index].P0.Y, zero);
					rect.Bottom = ntl::Max<float>(point_data[index].P0.Y, zero);
					if (!rect.is_zero())
						renderer->DrawRectangle(rect, m_sBackgroundColor);
					index += 2;
				}
				break;
			}
		}

		void CSteppedLineChartRenderer::RenderBackgroundV(IRenderer *renderer, const PointF &view_size, IChartData *data, const PointF &xrange, const PointF &yrange, const std::vector<POINT_DATA> &point_data)
		{
			float zero{ ntl::Clamp<float>(DataXToView(0, xrange, view_size.X), 0.0f, view_size.X - 1) };
			size_t index;
			RectF rect;
			switch (m_eInterpolationPosition)
			{
			case LineInterpolationPosition::Before:
				index = 1;
				while (index < point_data.size())
				{
					rect.Left = ntl::Min<float>(point_data[index - 1].P0.X, zero);
					rect.Right = ntl::Max<float>(point_data[index - 1].P0.X, zero);
					rect.Top = ntl::Min<float>(point_data[index - 1].P0.Y, point_data[index].P0.Y);
					rect.Bottom = ntl::Max<float>(point_data[index - 1].P0.Y, point_data[index].P0.Y);
					if (!rect.is_zero())
						renderer->DrawRectangle(rect, m_sBackgroundColor);
					index += 2;
				}
				break;
			case LineInterpolationPosition::Middle:
				rect.Left = ntl::Min<float>(point_data[0].P0.X, zero);
				rect.Right = ntl::Max<float>(point_data[0].P0.X, zero);
				rect.Top = ntl::Min<float>(point_data[0].P0.Y, point_data[1].P0.Y);
				rect.Bottom = ntl::Max<float>(point_data[0].P0.Y, point_data[1].P0.Y);
				if (!rect.is_zero())
					renderer->DrawRectangle(rect, m_sBackgroundColor);

				index = point_data.size() - 1;
				rect.Left = ntl::Min<float>(point_data[index].P0.X, zero);
				rect.Right = ntl::Max<float>(point_data[index].P0.X, zero);
				rect.Top = ntl::Min<float>(point_data[index - 1].P0.Y, point_data[index].P0.Y);
				rect.Bottom = ntl::Max<float>(point_data[index - 1].P0.Y, point_data[index].P0.Y);
				if (!rect.is_zero())
					renderer->DrawRectangle(rect, m_sBackgroundColor);

				index = 2;
				while (index < point_data.size() - 2)
				{
					rect.Left = ntl::Min<float>(point_data[index].P0.X, zero);
					rect.Right = ntl::Max<float>(point_data[index].P0.X, zero);
					rect.Top = ntl::Min<float>(point_data[index].P0.Y, point_data[index + 2].P0.Y);
					rect.Bottom = ntl::Max<float>(point_data[index].P0.Y, point_data[index + 2].P0.Y);
					if (!rect.is_zero())
						renderer->DrawRectangle(rect, m_sBackgroundColor);
					index += 3;
				}
				break;
			case LineInterpolationPosition::After:
				index = 2;
				while (index < point_data.size())
				{
					rect.Left = ntl::Min<float>(point_data[index].P0.X, zero);
					rect.Right = ntl::Max<float>(point_data[index].P0.X, zero);
					rect.Top = ntl::Min<float>(point_data[index - 1].P0.Y, point_data[index].P0.Y);
					rect.Bottom = ntl::Max<float>(point_data[index - 1].P0.Y, point_data[index].P0.Y);
					if (!rect.is_zero())
						renderer->DrawRectangle(rect, m_sBackgroundColor);
					index += 2;
				}
				break;
			}
		}
	#pragma endregion
	}
}