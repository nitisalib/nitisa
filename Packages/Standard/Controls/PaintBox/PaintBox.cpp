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
		CPaintBox::CPaintBox() :
			CControl(L"PaintBox", true, true, false, false, false, false),
			m_pCanvas{ nullptr },
			m_bDrawing{ false },
			m_bOutlineInEditor{ true }
		{
			OnDraw = nullptr;
			setService(new CPaintBoxService(this), true);
			m_cGradient.setPointCount(2);
			m_cGradient.setType(GradientType::Circle);
			setSize(PointF{ 100, 100 });
		}

		CPaintBox::CPaintBox(IForm *parent) :CPaintBox()
		{
			setForm(parent);
		}

		CPaintBox::CPaintBox(IControl *parent) : CPaintBox()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Helpers
		void CPaintBox::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
			{
				DrawEnd();
				m_pCanvas->setValid(false);
			}
		}

		ITexture::IData *CPaintBox::Lock(const bool readonly)
		{
			if (PrepareCanvas())
				return m_pCanvas->Lock(TextureFormat::RGBA, 0, readonly);
			return nullptr;
		}

		bool CPaintBox::DrawBegin()
		{
			if (!m_bDrawing && PrepareCanvas())
			{
				m_pOldActiveTarget = getForm()->getRenderer()->ActiveTarget;
				if (m_pOldActiveTarget == m_pCanvas || getForm()->getRenderer()->ActivateTarget(m_pCanvas))
				{
					m_bDrawing = true;
					return true;
				}
			}
			return false;
		}

		bool CPaintBox::DrawEnd()
		{
			if (m_bDrawing)
			{
				getForm()->getRenderer()->ActivateTarget(m_pOldActiveTarget);
				m_bDrawing = false;
				return true;
			}
			return false;
		}

		bool CPaintBox::PrepareCanvas()
		{
			if (m_bDrawing)
				return true;
			if (ntl::IsGreater<float>(getWidth(), 0) && ntl::IsGreater<float>(getHeight(), 0) && getForm() && getForm()->getRenderer())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				if (nitisa::PrepareCanvas(renderer, &m_pCanvas, getSize()))
				{
					{
						CStoreTarget s_target{ renderer };
						renderer
							->ActivateTarget(m_pCanvas)
							->Clear(Color{ 0, 0, 0, 0 });
						if (m_bOutlineInEditor && Application->Editor)
						{
							CStoreBitmask s_bitmask{ renderer };
							renderer
								->ActivateBitmask(Bitmask{ OutlineMask, 0, true, false })
								->DrawLines({
									PointF{ 0, 0 },
									PointF{ getWidth() - 1, 0 },
									PointF{ getWidth() - 1, getHeight() - 1 },
									PointF{ 1, getHeight() - 1 }, PointF{ 1, 0 } },
									Color{ 0, 0, 0, 255 },
									false);
						}
					}
					m_pCanvas->setValid(true);
					if (OnDraw)
						OnDraw(this);
				}
				return m_pCanvas != nullptr;
			}
			return false;
		}
	#pragma endregion

	#pragma region Clear
		void CPaintBox::Clear(const Color &color)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				renderer->Clear(color);
			}
		}
	#pragma endregion

	#pragma region Line
		void CPaintBox::Line(const PointF &p1, const PointF &p2, const Color &color)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				renderer->DrawLine(p1, p2, color);
			}
		}

		void CPaintBox::Line(const PointF &p1, const PointF &p2, const Color &color, const Mat4f &m)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(&m)
					->DrawLine(p1, p2, color);
			}
		}

		void CPaintBox::Line(const PointF &p1, const PointF &p2, const Color &c1, const Color &c2)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				renderer->DrawLine(p1, p2, c1, c2);
			}
		}

		void CPaintBox::Line(const PointF &p1, const PointF &p2, const Color &c1, const Color &c2, const Mat4f &m)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(&m)
					->DrawLine(p1, p2, c1, c2);
			}
		}

		void CPaintBox::Line(const PointF &p1, const PointF &p2, const Color &color, const unsigned int bitmask)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask, 0, true, false })
					->DrawLine(p1, p2, color);
			}
		}

		void CPaintBox::Line(const PointF &p1, const PointF &p2, const Color &color, const Mat4f &m, const unsigned int bitmask)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask, 0, true, false })
					->ActivatePrimitiveMatrix(&m)
					->DrawLine(p1, p2, color);
			}
		}

		void CPaintBox::Line(const PointF &p1, const PointF &p2, const Color &c1, const Color &c2, const unsigned int bitmask)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask, 0, true, false })
					->DrawLine(p1, p2, c1, c2);
			}
		}

		void CPaintBox::Line(const PointF &p1, const PointF &p2, const Color &c1, const Color &c2, const Mat4f &m, const unsigned int bitmask)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask, 0, true, false })
					->ActivatePrimitiveMatrix(&m)
					->DrawLine(p1, p2, c1, c2);
			}
		}
	#pragma endregion

	#pragma region Lines
		void CPaintBox::Lines(const std::vector<PointF> &points, const Color &color, const bool loop)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				renderer->DrawLines(points, color, loop);
			}
		}

		void CPaintBox::Lines(const std::vector<PointF> &points, const Color &color, const bool loop, const Mat4f &m)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(&m)
					->DrawLines(points, color, loop);
			}
		}

		void CPaintBox::Lines(const std::vector<PointF> &points, const Color &color, const bool loop, const unsigned int bitmask)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask, 0, true, false })
					->DrawLines(points, color, loop);
			}
		}

		void CPaintBox::Lines(const std::vector<PointF> &points, const Color &color, const bool loop, const Mat4f &m, const unsigned int bitmask)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask, 0, true, false })
					->ActivatePrimitiveMatrix(&m)
					->DrawLines(points, color, loop);
			}
		}
	#pragma endregion

	#pragma region Triangle
		void CPaintBox::Triangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &color)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				renderer->DrawTriangle(p1, p2, p3, color);
			}
		}

		void CPaintBox::Triangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &color, const Mat4f &m)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(&m)
					->DrawTriangle(p1, p2, p3, color);
			}
		}

		void CPaintBox::Triangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &c1, const Color &c2, const Color &c3)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				renderer->DrawTriangle(p1, p2, p3, c1, c2, c3);
			}
		}

		void CPaintBox::Triangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &c1, const Color &c2, const Color &c3, const Mat4f &m)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(&m)
					->DrawTriangle(p1, p2, p3, c1, c2, c3);
			}
		}

		void CPaintBox::Triangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &color, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->DrawTriangle(p1, p2, p3, color);
			}
		}

		void CPaintBox::Triangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &color, const Mat4f &m, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->ActivatePrimitiveMatrix(&m)
					->DrawTriangle(p1, p2, p3, color);
			}
		}

		void CPaintBox::Triangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &c1, const Color &c2, const Color &c3, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->DrawTriangle(p1, p2, p3, c1, c2, c3);
			}
		}

		void CPaintBox::Triangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &c1, const Color &c2, const Color &c3, const Mat4f &m, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->ActivatePrimitiveMatrix(&m)
					->DrawTriangle(p1, p2, p3, c1, c2, c3);
			}
		}
	#pragma endregion

	#pragma region Rectangle
		void CPaintBox::Rectangle(const RectF &rect, const Color &color)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				renderer->DrawRectangle(rect, color);
			}
		}

		void CPaintBox::Rectangle(const RectF &rect, const Color &color, const Mat4f &m)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(&m)
					->DrawRectangle(rect, color);
			}
		}

		void CPaintBox::Rectangle(const RectF &rect, const Color &c1, const Color &c2, const Color &c3, const Color &c4)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				renderer->DrawRectangle(rect, BorderColor{ c1, c2, c3, c4 });
			}
		}

		void CPaintBox::Rectangle(const RectF &rect, const Color &c1, const Color &c2, const Color &c3, const Color &c4, const Mat4f &m)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(&m)
					->DrawRectangle(rect, BorderColor{ c1, c2, c3, c4 });
			}
		}

		void CPaintBox::Rectangle(const RectF &rect, const Color &color, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->DrawRectangle(rect, color);
			}
		}

		void CPaintBox::Rectangle(const RectF &rect, const Color &color, const Mat4f &m, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->ActivatePrimitiveMatrix(&m)
					->DrawRectangle(rect, color);
			}
		}

		void CPaintBox::Rectangle(const RectF &rect, const Color &c1, const Color &c2, const Color &c3, const Color &c4, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->DrawRectangle(rect, BorderColor{ c1, c2, c3, c4 });
			}
		}

		void CPaintBox::Rectangle(const RectF &rect, const Color &c1, const Color &c2, const Color &c3, const Color &c4, const Mat4f &m, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->ActivatePrimitiveMatrix(&m)
					->DrawRectangle(rect, BorderColor{ c1, c2, c3, c4 });
			}
		}
	#pragma endregion

	#pragma region Gradient
		void CPaintBox::Gradient(const RectF &rect, nitisa::Gradient &g)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				renderer->DrawGradient(rect, g);
			}
		}

		void CPaintBox::Gradient(const RectF &rect, nitisa::Gradient &g, const Mat4f &m)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(&m)
					->DrawGradient(rect, g);
			}
		}

		void CPaintBox::Gradient(const RectF &rect, nitisa::Gradient &g, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->DrawGradient(rect, g);
			}
		}

		void CPaintBox::Gradient(const RectF &rect, nitisa::Gradient &g, const Mat4f &m, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->ActivatePrimitiveMatrix(&m)
					->DrawGradient(rect, g);
			}
		}
	#pragma endregion

	#pragma region Image
		void CPaintBox::Image(ITexture *image, const PointF &p, const float transparency)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(p.X, p.Y, 0))
					->DrawImage(image, transparency);
			}
		}

		void CPaintBox::Image(ITexture *image, const Mat4f &m, const float transparency)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(&m)
					->DrawImage(image, transparency);
			}
		}

		void CPaintBox::Image(ITexture *image, const RectF &part, const PointF &p, const float transparency)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(p.X, p.Y, 0))
					->DrawImage(image, transparency, part);
			}
		}

		void CPaintBox::Image(ITexture *image, const RectF &part, const Mat4f &m, const float transparency)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(&m)
					->DrawImage(image, transparency, part);
			}
		}

		void CPaintBox::Image(ITexture *image, const PointF &p, const float transparency, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(p.X, p.Y, 0))
					->DrawImage(image, transparency);
			}
		}

		void CPaintBox::Image(ITexture *image, const Mat4f &m, const float transparency, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->ActivatePrimitiveMatrix(&m)
					->DrawImage(image, transparency);
			}
		}

		void CPaintBox::Image(ITexture *image, const RectF &part, const PointF &p, const float transparency, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(p.X, p.Y, 0))
					->DrawImage(image, transparency, part);
			}
		}

		void CPaintBox::Image(ITexture *image, const RectF &part, const Mat4f &m, const float transparency, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->ActivatePrimitiveMatrix(&m)
					->DrawImage(image, transparency, part);
			}
		}
	#pragma endregion

	#pragma region Block
		void CPaintBox::Block(const RectF &block, const RectF &border, const RectF &radius, const BlockColors &colors)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				renderer->DrawBlock(block, border, radius, colors);
			}
		}

		void CPaintBox::Block(const RectF &rect, const RectF &block, const RectF &border, const RectF &radius, const BlockColors &colors)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				renderer->DrawBlock(block, border, radius, colors, rect);
			}
		}

		void CPaintBox::Block(const RectF &block, const RectF &border, const RectF &radius, const BlockColors &colors, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->DrawBlock(block, border, radius, colors);
			}
		}

		void CPaintBox::Block(const RectF &rect, const RectF &block, const RectF &border, const RectF &radius, const BlockColors &colors, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->DrawBlock(block, border, radius, colors, rect);
			}
		}
	#pragma endregion

	#pragma region Text
		void CPaintBox::Text(const String &text, IPlatformFont *font, const float distance, const Color &color, const PointF &p)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				IPlatformFont *pf{ font ? font : getFont()->getPlatformFont(renderer) };
				if (pf)
				{
					CStoreTarget s_target{ renderer };
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(p.X, p.Y, 0))
						->DrawText(text, pf, distance, color);
				}
			}
		}

		void CPaintBox::Text(const String &text, IPlatformFont *font, const float distance, const Color &color, const Mat4f &m)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				IPlatformFont *pf{ font ? font : getFont()->getPlatformFont(renderer) };
				if (pf)
				{
					CStoreTarget s_target{ renderer };
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivatePrimitiveMatrix(&m)
						->DrawText(text, pf, distance, color);
				}
			}
		}

		void CPaintBox::Text(const String &text, IPlatformFont *font, const float distance, const Color &color, const PointF &p, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				IPlatformFont *pf{ font ? font : getFont()->getPlatformFont(renderer) };
				if (pf)
				{
					CStoreTarget s_target{ renderer };
					CStoreBitmask s_bitmask{ renderer };
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(p.X, p.Y, 0))
						->DrawText(text, pf, distance, color);
				}
			}
		}

		void CPaintBox::Text(const String &text, IPlatformFont *font, const float distance, const Color &color, const Mat4f &m, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				IPlatformFont *pf{ font ? font : getFont()->getPlatformFont(renderer) };
				if (pf)
				{
					CStoreTarget s_target{ renderer };
					CStoreBitmask s_bitmask{ renderer };
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
						->ActivatePrimitiveMatrix(&m)
						->DrawText(text, pf, distance, color);
				}
			}
		}
	#pragma endregion

	#pragma region Blur
		void CPaintBox::Blur(const int radius, const BlurType type)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				renderer->BlurImage(m_pCanvas, radius, type);
			}
		}

		void CPaintBox::Blur(const int radius, const BlurType type, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->BlurImage(m_pCanvas, radius, type);
			}
		}
	#pragma endregion

	#pragma region Dot
		void CPaintBox::Dot(const PointF &p, const Color &color)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer->DrawRectangle(RectF{ p.X, p.Y, p.X + 1, p.Y + 1 }, color);
			}
		}

		void CPaintBox::Dot(const PointF &p, const Color &color, const Mat4f &m)
		{
			if (PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				Vec4f v{ m * Vec4f{ p.X, p.Y, 0, 1 } };
				CStoreTarget s_target{ renderer };
				renderer->DrawRectangle(RectF{ v.X, v.Y, v.X + 1, v.Y + 1 }, color);
			}
		}
	#pragma endregion

	#pragma region Circle
		void CPaintBox::Circle(const PointF &p, const Color &color, const float radius)
		{
			if (radius > 0 && PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				m_cGradient.setPointColor(0, color);
				m_cGradient.setPointColor(1, color);
				renderer->DrawGradient(RectF{ p.X - radius, p.Y - radius, p.X + radius, p.Y + radius }, m_cGradient);
			}
		}

		void CPaintBox::Circle(const PointF &p, const Color &color, const float radius, const Mat4f &m)
		{
			if (radius > 0 && PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				m_cGradient.setPointColor(0, color);
				m_cGradient.setPointColor(1, color);
				renderer
					->ActivatePrimitiveMatrix(&m)
					->DrawGradient(RectF{ p.X - radius, p.Y - radius, p.X + radius, p.Y + radius }, m_cGradient);
			}
		}

		void CPaintBox::Circle(const PointF &p, const Color &color, const float radius, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (radius > 0 && PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				m_cGradient.setPointColor(0, color);
				m_cGradient.setPointColor(1, color);
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->DrawGradient(RectF{ p.X - radius, p.Y - radius, p.X + radius, p.Y + radius }, m_cGradient);
			}
		}

		void CPaintBox::Circle(const PointF &p, const Color &color, const float radius, const Mat4f &m, const unsigned int bitmask_x, const unsigned int bitmask_y)
		{
			if (radius > 0 && PrepareCanvas())
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreTarget s_target{ renderer };
				CStoreBitmask s_bitmask{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				m_cGradient.setPointColor(0, color);
				m_cGradient.setPointColor(1, color);
				renderer
					->ActivateBitmask(Bitmask{ bitmask_x, bitmask_y, false, false })
					->ActivatePrimitiveMatrix(&m)
					->DrawGradient(RectF{ p.X - radius, p.Y - radius, p.X + radius, p.Y + radius }, m_cGradient);
			}
		}
	#pragma endregion

	#pragma region Getters
		ITexture *CPaintBox::getCanvas()
		{
			PrepareCanvas();
			return m_pCanvas;
		}

		bool CPaintBox::isOutlineInEditor() const
		{
			return m_bOutlineInEditor;
		}
	#pragma endregion

	#pragma region Setters
		bool CPaintBox::setOutlineInEditor(const bool value)
		{
			if (value != m_bOutlineInEditor)
			{
				m_bOutlineInEditor = value;
				if (Application->Editor)
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

	#pragma region Paint
		void CPaintBox::Render()
		{
			if (PrepareCanvas())
				DrawCanvas(getForm()->getRenderer(), getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}
	#pragma endregion
	}
}