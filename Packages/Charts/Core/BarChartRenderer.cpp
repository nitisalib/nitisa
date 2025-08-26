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
		CBarChartRenderer::CBarChartRenderer() :
			m_aDrawBorder{ true, true },
			m_aDrawBackground{ true, true },
			m_aBorderWidth{ 2, 2 },
			m_aBorderColor{ Color{ 255, 123, 151, 200 }, Color{ 255, 123, 151, 255 } },
			m_aBackgroundColor{ Color{ 255, 123, 151, 128 }, Color{ 255, 123, 151, 156 } },
			m_iActivePoint{ -1 },
			m_bVertical{ false },
			m_fBarWidth{ 10 }
		{

		}

		void CBarChartRenderer::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Getters
		bool CBarChartRenderer::isDrawBorder(const PointState state) const
		{
			return m_aDrawBorder[(int)state];
		}

		bool CBarChartRenderer::isDrawBackground(const PointState state) const
		{
			return m_aDrawBackground[(int)state];
		}

		float CBarChartRenderer::getBorderWidth(const PointState state) const
		{
			return m_aBorderWidth[(int)state];
		}

		Color CBarChartRenderer::getBorderColor(const PointState state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CBarChartRenderer::getBackgroundColor(const PointState state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		int CBarChartRenderer::getActivePoint() const
		{
			return m_iActivePoint;
		}

		bool CBarChartRenderer::isVertical() const
		{
			return m_bVertical;
		}

		float CBarChartRenderer::getBarWidth() const
		{
			return m_fBarWidth;
		}
	#pragma endregion

	#pragma region Setters
		bool CBarChartRenderer::setDrawBorder(const PointState state, const bool value)
		{
			if (value != m_aDrawBorder[(int)state])
			{
				m_aDrawBorder[(int)state] = value;
				return true;
			}
			return false;
		}

		bool CBarChartRenderer::setDrawBackground(const PointState state, const bool value)
		{
			if (value != m_aDrawBackground[(int)state])
			{
				m_aDrawBackground[(int)state] = value;
				return true;
			}
			return false;
		}

		bool CBarChartRenderer::setBorderWidth(const PointState state, const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_aBorderWidth[(int)state]))
			{
				m_aBorderWidth[(int)state] = value;
				return true;
			}
			return false;
		}

		bool CBarChartRenderer::setBorderColor(const PointState state, const Color &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
				return true;
			}
			return false;
		}

		bool CBarChartRenderer::setBackgroundColor(const PointState state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
				return true;
			}
			return false;
		}

		bool CBarChartRenderer::setActivePoint(const int value)
		{
			if (value != m_iActivePoint)
			{
				m_iActivePoint = value;
				return true;
			}
			return false;
		}

		bool CBarChartRenderer::setVertical(const bool value)
		{
			if (value != m_bVertical)
			{
				m_bVertical = value;
				return true;
			}
			return false;
		}

		bool CBarChartRenderer::setBarWidth(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fBarWidth))
			{
				m_fBarWidth = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CBarChartRenderer::Render(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange)
		{
			if (data->getCount() > 0)
				m_bVertical ? RenderBarsV(renderer, texture, data, xrange, yrange) : RenderBarsH(renderer, texture, data, xrange, yrange);
		}

		void CBarChartRenderer::RenderBarsH(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange)
		{
			PointF view_size{ texture->Widthf, texture->Heightf }, p;
			float zero{ DataYToView(0, yrange, view_size.Y) };
			RectF r, borders;
			PointState state;
			BlockColors colors{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
			for (int i = 0; i < data->getCount(); i++)
			{
				p = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
				r.Left = p.X - m_fBarWidth * 0.5f;
				r.Right = r.Left + m_fBarWidth;
				r.Top = p.Y;
				r.Bottom = zero;
				state = (i == m_iActivePoint) ? PointState::Active : PointState::Normal;
				if (m_aDrawBorder[(int)state] && m_aBorderColor[(int)state].A > 0)
				{
					borders.Left = borders.Top = borders.Right = m_aBorderWidth[(int)state];
					borders.Bottom = 0;
					if (r.Bottom < r.Top)
					{
						ntl::Swap<float>(r.Top, r.Bottom);
						ntl::Swap<float>(borders.Top, borders.Bottom);
					}
					colors[0] = colors[1] = colors[2] = colors[3] = m_aBorderColor[(int)state];
					colors[4] = m_aDrawBackground[(int)state] ? m_aBackgroundColor[(int)state] : Color{ 0, 0, 0, 0 };
					renderer->DrawBlock(r, borders, RectF{ 0, 0, 0, 0 }, colors);
				}
				else if (m_aDrawBackground[(int)state] && m_aBackgroundColor[(int)state].A > 0)
				{
					if (r.Bottom < r.Top)
						ntl::Swap<float>(r.Top, r.Bottom);
					renderer->DrawRectangle(r, m_aBackgroundColor[(int)state]);
				}
			}
		}

		void CBarChartRenderer::RenderBarsV(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange)
		{
			PointF view_size{ texture->Widthf, texture->Heightf }, p;
			float zero{ DataXToView(0, xrange, view_size.X) };
			RectF r, borders;
			PointState state;
			BlockColors colors{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
			for (int i = 0; i < data->getCount(); i++)
			{
				p = DataToView(PointF{ data->getX(i), data->getY(i) }, xrange, yrange, view_size);
				r.Left = p.X;
				r.Right = zero;
				r.Top = p.Y - m_fBarWidth * 0.5f;
				r.Bottom = r.Top + m_fBarWidth;
				state = (i == m_iActivePoint) ? PointState::Active : PointState::Normal;
				if (m_aDrawBorder[(int)state] && m_aBorderColor[(int)state].A > 0)
				{
					borders.Right = 0;
					borders.Top = borders.Left = borders.Bottom = m_aBorderWidth[(int)state];
					if (r.Right < r.Left)
					{
						ntl::Swap<float>(r.Right, r.Left);
						ntl::Swap<float>(borders.Left, borders.Right);
					}
					colors[0] = colors[1] = colors[2] = colors[3] = m_aBorderColor[(int)state];
					colors[4] = m_aBackgroundColor[(int)state];
					renderer->DrawBlock(r, borders, RectF{ 0, 0, 0, 0 }, colors);
				}
				else if (m_aDrawBackground[(int)state] && m_aBackgroundColor[(int)state].A > 0)
				{
					if (r.Bottom < r.Top)
						ntl::Swap<float>(r.Top, r.Bottom);
					renderer->DrawRectangle(r, m_aBackgroundColor[(int)state]);
				}
			}
		}
	#pragma endregion
	}
}