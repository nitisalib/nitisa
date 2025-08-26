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
	namespace standard
	{
	#pragma region Constructor & destructor
		CShape::CShape():
			CControl(L"Shape", true, true, false, false, false, false),
			m_eShapeType{ ShapeType::Circle },
			m_fBorderWidth{ 1 },
			m_fBorderRadius{ 10 },
			m_sBorderColor{ 0, 0, 0, 255 },
			m_sBackgroundColor{ 255, 255, 255, 255 },
			m_iBorderMask{ 0b00001111000011110000111100001111 },
			m_pCanvas{ nullptr }
		{
			setService(new CShapeService(this), true);
			setSize(PointF{ 50, 50 });
		}

		CShape::CShape(IForm *parent) :CShape()
		{
			setForm(parent);
		}

		CShape::CShape(IControl *parent) : CShape()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IControl setters
		bool CShape::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_fBorderWidth *= avg;
				m_fBorderRadius *= avg;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IControl methods
		void CShape::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region Getters
		CShape::ShapeType CShape::getShapeType() const
		{
			return m_eShapeType;
		}

		float CShape::getBorderWidth() const
		{
			return m_fBorderWidth;
		}

		float CShape::getBorderRadius() const
		{
			return m_fBorderRadius;
		}

		Color CShape::getBorderColor() const
		{
			return m_sBorderColor;
		}

		Color CShape::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		unsigned int CShape::getBorderMask() const
		{
			return m_iBorderMask;
		}
	#pragma endregion

	#pragma region Setters
		bool CShape::setShapeType(const ShapeType value)
		{
			if (value != m_eShapeType)
			{
				m_eShapeType = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CShape::setBorderWidth(const float value)
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

		bool CShape::setBorderRadius(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fBorderRadius))
			{
				m_fBorderRadius = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CShape::setBorderColor(const Color &value)
		{
			if (value != m_sBorderColor)
			{
				m_sBorderColor = value;
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

		bool CShape::setBackgroundColor(const Color &value)
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

		bool CShape::setBorderMask(const unsigned int value)
		{
			if (value != m_iBorderMask)
			{
				m_iBorderMask = value;
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
		void CShape::UpdateFromStyle(IStyle *style)
		{
			style->getOption(m_sClassName + L".BorderWidth", m_fBorderWidth);
			style->getOption(m_sClassName + L".BorderRadius", m_fBorderRadius);
			style->getOption(m_sClassName + L".BorderColor", m_sBorderColor);
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BorderMask", m_iBorderMask);
		}
	#pragma endregion

	#pragma region Paint
		void CShape::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			if (PrepareCanvas(renderer, &m_pCanvas, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				switch (m_eShapeType)
				{
				case ShapeType::Circle:
					RenderCircle(renderer);
					break;
				case ShapeType::Ellipse:
					RenderEllipse(renderer);
					break;
				case ShapeType::Rectangle:
					RenderRectangle(renderer);
					break;
				case ShapeType::Square:
					RenderSquare(renderer);
					break;
				case ShapeType::RoundRectangle:
					RenderRoundRectangle(renderer);
					break;
				case ShapeType::RoundSquare:
					RenderRoundSquare(renderer);
					break;
				case ShapeType::Triangle:
					RenderTriangle(renderer);
					break;
				}

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}

		void CShape::RenderCircle(IRenderer *renderer)
		{
			PointF center{ m_pCanvas->Widthf / 2, m_pCanvas->Heightf / 2 };
			float radius{ ntl::Min<float>(center.X, center.Y) };
			Gradient g;
			g.setType(GradientType::Circle);
			if (ntl::IsGreater<float>(m_fBorderWidth, 0))
			{
				float d{ (radius - m_fBorderWidth) / radius };
				if (ntl::IsLessOrEqual<float>(d, 0))
					g.setPoints(Color1DArray{ Color1D{ 0, m_sBorderColor }, Color1D{ 1, m_sBorderColor } });
				else
					g.setPoints(Color1DArray{ Color1D{ 0, m_sBackgroundColor }, Color1D{ d, m_sBackgroundColor }, Color1D{ d + 0.000001f, m_sBorderColor }, Color1D{ 1, m_sBorderColor } });
			}
			else
				g.setPoints(Color1DArray{ Color1D{ 0, m_sBackgroundColor }, Color1D{ 1, m_sBackgroundColor } });
			renderer->DrawGradient(RectF{ center.X - radius, center.Y - radius, center.X + radius, center.Y + radius }, g);
		}

		void CShape::RenderEllipse(IRenderer *renderer)
		{
			PointF center{ m_pCanvas->Widthf / 2, m_pCanvas->Heightf / 2 };
			float radius, sx, sy;
			if (center.X > center.Y)
			{
				radius = center.X;
				sx = 1;
				sy = center.Y / center.X;
			}
			else
			{
				radius = center.Y;
				sx = center.X / center.Y;
				sy = 1;
			}
			Gradient g;
			g.setType(GradientType::Circle);
			g.setPoints(Color1DArray{ Color1D{ 0, m_sBackgroundColor }, Color1D{ 1, m_sBackgroundColor } });
			CStorePrimitiveMatrix s_matrix{ renderer };
			renderer
				->ActivatePrimitiveMatrix(ntl::Mat4Scale<float>(sx, sy, 1))
				->DrawGradient(RectF{ 0, 0, 2 * radius, 2 * radius }, g);
		}

		void CShape::RenderRectangle(IRenderer *renderer)
		{
			RectF rect{ 0, 0, m_pCanvas->Widthf, m_pCanvas->Heightf };
			if (ntl::IsEqual<float>(m_fBorderWidth, 1) && m_iBorderMask != 0)
			{
				if (m_sBackgroundColor.A > 0)
					renderer->DrawRectangle(rect, m_sBackgroundColor);
				if (m_sBorderColor.A > 0)
				{
					CStoreBitmask s_bitmask{ renderer };
					renderer
						->ActivateBitmask(Bitmask{ m_iBorderMask, 0, true, false })
						->DrawLines({
							PointF{ rect.Left + 1, rect.Top },
							PointF{ rect.Right, rect.Top },
							PointF{ rect.Right, rect.Bottom - 1 },
							PointF{ rect.Left + 1, rect.Bottom - 1 },
							PointF{ rect.Left + 1, rect.Top } },
							m_sBorderColor,
							false);
				}
			}
			else if (ntl::IsEqual<float>(m_fBorderWidth, 0))
			{
				if (m_sBackgroundColor.A > 0)
					renderer->DrawRectangle(rect, m_sBackgroundColor);
			}
			else
			{
				BlockColors colors{ m_sBorderColor, m_sBorderColor, m_sBorderColor, m_sBorderColor, m_sBackgroundColor, Color{ 0, 0, 0, 0 } };
				renderer->DrawBlock(rect, RectF{ m_fBorderWidth, m_fBorderWidth, m_fBorderWidth, m_fBorderWidth }, RectF{ 0, 0, 0, 0 }, colors);
			}
		}

		void CShape::RenderSquare(IRenderer *renderer)
		{
			PointF center{ m_pCanvas->Widthf / 2, m_pCanvas->Heightf / 2 };
			float radius{ ntl::Min<float>(center.X, center.Y) };
			RectF rect{ center.X - radius, center.Y - radius, center.X + radius, center.Y + radius };
			if (ntl::IsEqual<float>(m_fBorderWidth, 1) && m_iBorderMask != 0)
			{
				if (m_sBackgroundColor.A > 0)
					renderer->DrawRectangle(rect, m_sBackgroundColor);
				if (m_sBorderColor.A > 0)
				{
					CStoreBitmask s_bitmask{ renderer };
					renderer
						->ActivateBitmask(Bitmask{ m_iBorderMask, 0, true, false })
						->DrawLines({
							PointF{ rect.Left + 1, rect.Top },
							PointF{ rect.Right, rect.Top },
							PointF{ rect.Right, rect.Bottom - 1 },
							PointF{ rect.Left + 1, rect.Bottom - 1 },
							PointF{ rect.Left + 1, rect.Top } },
							m_sBorderColor,
							false);
				}
			}
			else if (ntl::IsEqual<float>(m_fBorderWidth, 0))
			{
				if (m_sBackgroundColor.A > 0)
					renderer->DrawRectangle(rect, m_sBackgroundColor);
			}
			else
			{
				BlockColors colors{ m_sBorderColor, m_sBorderColor, m_sBorderColor, m_sBorderColor, m_sBackgroundColor, Color{ 0, 0, 0, 0 } };
				renderer->DrawBlock(rect, RectF{ m_fBorderWidth, m_fBorderWidth, m_fBorderWidth, m_fBorderWidth }, RectF{ 0, 0, 0, 0 }, colors);
			}
		}

		void CShape::RenderRoundRectangle(IRenderer *renderer)
		{
			RectF rect{ 0, 0, m_pCanvas->Widthf, m_pCanvas->Heightf };
			if (ntl::IsEqual<float>(m_fBorderWidth, 1) && m_iBorderMask != 0 && ntl::IsEqual<float>(m_fBorderRadius, 0))
			{
				if (m_sBackgroundColor.A > 0)
					renderer->DrawRectangle(rect, m_sBackgroundColor);
				if (m_sBorderColor.A > 0)
				{
					CStoreBitmask s_bitmask{ renderer };
					renderer
						->ActivateBitmask(Bitmask{ m_iBorderMask, 0, true, false })
						->DrawLines({
							PointF{ rect.Left + 1, rect.Top },
							PointF{ rect.Right, rect.Top },
							PointF{ rect.Right, rect.Bottom - 1 },
							PointF{ rect.Left + 1, rect.Bottom - 1 },
							PointF{ rect.Left + 1, rect.Top } },
							m_sBorderColor,
							false);
				}
			}
			else
			{
				BlockColors colors{ m_sBorderColor, m_sBorderColor, m_sBorderColor, m_sBorderColor, m_sBackgroundColor, Color{ 0, 0, 0, 0 } };
				renderer->DrawBlock(rect, RectF{ m_fBorderWidth, m_fBorderWidth, m_fBorderWidth, m_fBorderWidth }, RectF{ m_fBorderRadius, m_fBorderRadius, m_fBorderRadius, m_fBorderRadius }, colors);
			}
		}

		void CShape::RenderRoundSquare(IRenderer *renderer)
		{
			PointF center{ m_pCanvas->Widthf / 2, m_pCanvas->Heightf / 2 };
			float radius{ ntl::Min<float>(center.X, center.Y) };
			RectF rect{ center.X - radius, center.Y - radius, center.X + radius, center.Y + radius };
			if (ntl::IsEqual<float>(m_fBorderWidth, 1) && m_iBorderMask != 0 && ntl::IsEqual<float>(m_fBorderRadius, 0))
			{
				if (m_sBackgroundColor.A > 0)
					renderer->DrawRectangle(rect, m_sBackgroundColor);
				if (m_sBorderColor.A > 0)
				{
					CStoreBitmask s_bitmask{ renderer };
					renderer
						->ActivateBitmask(Bitmask{ m_iBorderMask, 0, true, false })
						->DrawLines({
							PointF{ rect.Left + 1, rect.Top },
							PointF{ rect.Right, rect.Top },
							PointF{ rect.Right, rect.Bottom - 1 },
							PointF{ rect.Left + 1, rect.Bottom - 1 },
							PointF{ rect.Left + 1, rect.Top } },
							m_sBorderColor,
							false);
				}
			}
			else
			{
				BlockColors colors{ m_sBorderColor, m_sBorderColor, m_sBorderColor, m_sBorderColor, m_sBackgroundColor, Color{ 0, 0, 0, 0 } };
				renderer->DrawBlock(rect, RectF{ m_fBorderWidth, m_fBorderWidth, m_fBorderWidth, m_fBorderWidth }, RectF{ m_fBorderRadius, m_fBorderRadius, m_fBorderRadius, m_fBorderRadius }, colors);
			}
		}

		void CShape::RenderTriangle(IRenderer *renderer)
		{
			float center{ m_pCanvas->Widthf / 2 };
			if (m_sBackgroundColor.A > 0)
				renderer->DrawTriangle(PointF{ 0, m_pCanvas->Heightf }, PointF{ center, 0 }, PointF{ m_pCanvas->Widthf, m_pCanvas->Heightf }, m_sBackgroundColor);
			if (ntl::IsEqual<float>(m_fBorderWidth, 1) && m_sBorderColor.A > 0)
			{
				if (m_iBorderMask != 0)
				{
					CStoreBitmask s_bitmask{ renderer };
					renderer
						->ActivateBitmask(Bitmask{ m_iBorderMask, 0, true, false })
						->DrawLines({
							PointF{ 1, m_pCanvas->Heightf - 1 },
							PointF{ center, 0 },
							PointF{ m_pCanvas->Widthf, m_pCanvas->Heightf - 1 },
							PointF{ 1, m_pCanvas->Heightf - 1 } },
							m_sBorderColor,
							false);
				}
				else
					renderer->DrawLines({ PointF{ 1, m_pCanvas->Heightf - 1 }, PointF{ center, 0 }, PointF{ m_pCanvas->Widthf, m_pCanvas->Heightf - 1 } }, m_sBorderColor, true);
			}
		}
	#pragma endregion
	}
}