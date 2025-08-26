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
	namespace ide
	{
	#pragma region Constructor & destructor
		CFormView::CFormView() :
			CControl(L"FormView", true, true, true, false, false, false),
			m_sLayout{ false,
				{ Image{}, Image{}, Image{}, Image{}, nullptr, nullptr, nullptr, nullptr, PointF{ 0, 0 }, 0 },
				{ Image{}, Image{}, Image{}, Image{}, nullptr, nullptr, nullptr, nullptr, PointF{ 0, 0 }, 0 },
				{ Image{}, Image{}, Image{}, Image{}, nullptr, nullptr, nullptr, nullptr, PointF{ 0, 0 }, 0 },
				{ Image{}, Image{}, Image{}, Image{}, nullptr, nullptr, nullptr, nullptr, PointF{ 0, 0 }, 0 },
				RectF{ 0, 0, 0, 0 },
				false,
				RectF{ 0, 0, 0, 0 },
				BorderType::Top },
			m_sBorderWidth{ 1, 1, 1, 1 },
			m_aBorderColor{
				BorderColor{ Color{ 0, 0, 0, 32 }, Color{ 0, 0, 0, 32 }, Color{ 0, 0, 0, 32 }, Color{ 0, 0, 0, 32 } },
				BorderColor{ Color{ 0, 0, 255, 255 }, Color{ 0, 0, 255, 255 }, Color{ 0, 0, 255, 255 }, Color{ 0, 0, 255, 255 } } },
			m_pCanvas{ nullptr }
		{
			setService(new CFormViewService(this), true);
			setClientSize(PointF{ 640, 480 });
		}

		CFormView::CFormView(IControl *parent) :CFormView()
		{
			setParent(parent);
		}

		CFormView::CFormView(IForm *parent) : CFormView()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region IControl getters
		IControl *CFormView::getControl(const int index)
		{
			return CControl::getControl(index);
		}

		IControl *CFormView::getControl(const String &name)
		{
			return CControl::getControl(name);
		}

		IControl *CFormView::getControl(const PointF &position)
		{
			IControl *result{ CControl::getControl(position) };
			if (result && result != this)
			{
				Vec4f v{ ntl::Inversed<float>(getTransformMatrix()) * Vec4f{ position.X, position.Y, 0, 1 } };
				RectF client{ getClientRect() };
				if (v.X < 0 || v.X >= getWidth() || v.Y < 0 || v.Y >= getHeight())
					result = nullptr;
				else if (v.X < client.Left || v.X >= client.Right || v.Y < client.Top || v.Y >= client.Bottom)
					result = this;
			}
			return result;
		}

		RectF CFormView::getClientRect()
		{
			RectF result{
				m_sLayout.Left.Size + m_sBorderWidth.Left,
				m_sLayout.Top.Size + m_sBorderWidth.Top,
				getWidth() - m_sLayout.Right.Size - m_sBorderWidth.Right,
				getHeight() - m_sLayout.Bottom.Size - m_sBorderWidth.Bottom
			};
			result.validate();
			return result;
		}

		CursorType CFormView::getCursor()
		{
			if (getForm())
			{
				PointF p{ FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())) };
				if (p.X >= 0 && p.X < getWidth() && p.Y >= 0 && p.Y < getHeight())
				{
					if (p.X >= getWidth() - m_sLayout.Left.Size - m_sBorderWidth.Right && p.X < getWidth() - m_sBorderWidth.Right)
					{
						if (p.Y >= getHeight() - m_sLayout.Bottom.Size - m_sBorderWidth.Bottom && p.Y < getHeight() - m_sBorderWidth.Bottom)
							return CursorType::SizeNorthwestSoutheast;
						return CursorType::SizeWestEast;
					}
					if (p.Y >= getHeight() - m_sLayout.Bottom.Size - m_sBorderWidth.Bottom && p.Y < getHeight() - m_sBorderWidth.Bottom)
						return CursorType::SizeNorthSouth;
				}
			}
			return CControl::getCursor();
		}

		bool CFormView::isAcceptChild(IControl *control)
		{
			return getControlCount() == 0 && cast<IFormEditor*>(control);
		}
	#pragma endregion

	#pragma region IFormView getters
		String CFormView::getCaption()
		{
			return m_sCaption;
		}
	#pragma endregion

	#pragma region IFormView setters
		bool CFormView::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		const CFormView::LAYOUT &CFormView::getLayout() const
		{
			return m_sLayout;
		}

		RectF CFormView::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		BorderColor CFormView::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CFormView::setClientSize(const PointF &value)
		{
			return setSize(PointF{ value.X + m_sLayout.Left.Size + m_sLayout.Right.Size + m_sBorderWidth.Left + m_sBorderWidth.Right,
				value.Y + m_sLayout.Top.Size + m_sLayout.Bottom.Size + m_sBorderWidth.Top + m_sBorderWidth.Bottom });
		}

		bool CFormView::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				m_sBorderWidth = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormView::setBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
				State st{ (getControl(0) && getControl(0)->isFocused()) ? State::Active : State::Normal };
				if (st == state && m_sBorderWidth.has_positive())
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
		void CFormView::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		void CFormView::FreeLayoutTextures()
		{
			FreeBorderTextures(m_sLayout.Left);
			FreeBorderTextures(m_sLayout.Top);
			FreeBorderTextures(m_sLayout.Right);
			FreeBorderTextures(m_sLayout.Bottom);
		}

		void CFormView::FreeBorderTextures(BORDER &border)
		{
			if (border.TextureStart)
			{
				border.TextureStart->Release();
				border.TextureStart = nullptr;
			}
			if (border.TextureMiddle)
			{
				border.TextureMiddle->Release();
				border.TextureMiddle = nullptr;
			}
			if (border.TextureEnd)
			{
				border.TextureEnd->Release();
				border.TextureEnd = nullptr;
			}
			if (border.TextureFill)
			{
				border.TextureFill->Release();
				border.TextureFill = nullptr;
			}
		}

		void CFormView::LoadBorder(Variant &config, BORDER &border, const String &path)
		{
			if (config.isSet(L"start"))
				border.BitmapStart = Application->Picture->Load(path + (String)config[L"start"]);
			else
				border.BitmapStart.setSize(0, 0);
			if (config.isSet(L"middle"))
				border.BitmapMiddle = Application->Picture->Load(path + (String)config[L"middle"]);
			else
				border.BitmapMiddle.setSize(0, 0);
			if (config.isSet(L"end"))
				border.BitmapEnd = Application->Picture->Load(path + (String)config[L"end"]);
			else
				border.BitmapEnd.setSize(0, 0);
			if (config.isSet(L"fill"))
				border.BitmapFill = Application->Picture->Load(path + (String)config[L"fill"]);
			else
				border.BitmapFill.setSize(0, 0);
		}

		void CFormView::CalculateBorder(BORDER &border)
		{
			border.Constraints = PointF{ 0, 0 };
			border.Size = 0;
			if (!border.BitmapStart.isEmpty())
			{
				border.Size = ntl::Max<float>(border.Size, (float)border.BitmapStart.Height);
				border.Constraints.X += (float)border.BitmapStart.Width;
				border.Constraints.Y = border.Constraints.X;
			}
			if (!border.BitmapEnd.isEmpty())
			{
				border.Size = ntl::Max<float>(border.Size, (float)border.BitmapEnd.Height);
				border.Constraints.X += (float)border.BitmapEnd.Width;
				border.Constraints.Y = border.Constraints.X;
			}
			if (!border.BitmapMiddle.isEmpty())
			{
				border.Size = ntl::Max<float>(border.Size, (float)border.BitmapMiddle.Height);
				border.Constraints.X += (float)border.BitmapMiddle.Width;
				border.Constraints.Y = border.Constraints.X;
			}
			if (!border.BitmapFill.isEmpty())
			{
				border.Size = ntl::Max<float>(border.Size, (float)border.BitmapFill.Height);
				border.Constraints.Y = 0;
			}
		}

		bool CFormView::LoadLayout(const String &filename)
		{
			Variant config;
			if (json_decode(GetUTF8FileContent(filename), config))
			{
				CLockRepaint lock{ this };
				String path{ ExtractDirectoryName(filename) + L"\\" };
				FreeLayoutTextures();
				m_sLayout.Landscape = (bool)config[L"landscape"];
				LoadBorder(config[L"left"], m_sLayout.Left, path);
				LoadBorder(config[L"top"], m_sLayout.Top, path);
				LoadBorder(config[L"right"], m_sLayout.Right, path);
				LoadBorder(config[L"bottom"], m_sLayout.Bottom, path);
				CalculateBorder(m_sLayout.Left);
				CalculateBorder(m_sLayout.Top);
				CalculateBorder(m_sLayout.Right);
				CalculateBorder(m_sLayout.Bottom);
				m_sLayout.Constraints.Left = m_sLayout.Left.Size + ntl::Max<float>(m_sLayout.Top.Constraints.X, m_sLayout.Bottom.Constraints.X) + m_sLayout.Right.Size;
				m_sLayout.Constraints.Top = m_sLayout.Top.Size + ntl::Max<float>(m_sLayout.Left.Constraints.X, m_sLayout.Right.Constraints.X) + m_sLayout.Bottom.Size;
				m_sLayout.Constraints.Right = ntl::Max<float>(m_sLayout.Top.Constraints.Y, m_sLayout.Bottom.Constraints.Y);
				m_sLayout.Constraints.Bottom = ntl::Max<float>(m_sLayout.Left.Constraints.Y, m_sLayout.Right.Constraints.Y);
				setConstraints(m_sLayout.Constraints);
				if (config.isSet(L"size"))
					setSize(PointF{ (float)config[L"size"][L"width"], (float)config[L"size"][L"height"] });
				if (config.isSet(L"caption"))
				{
					m_sLayout.Caption = true;
					m_sLayout.CaptionPadding.Left = (float)config[L"caption"][L"padding"][0];
					m_sLayout.CaptionPadding.Top = (float)config[L"caption"][L"padding"][1];
					m_sLayout.CaptionPadding.Right = (float)config[L"caption"][L"padding"][2];
					m_sLayout.CaptionPadding.Bottom = (float)config[L"caption"][L"padding"][3];
					if ((String)config[L"caption"][L"border"] == L"left")
						m_sLayout.CaptionBorder = BorderType::Left;
					else if ((String)config[L"caption"][L"border"] == L"top")
						m_sLayout.CaptionBorder = BorderType::Top;
					else if ((String)config[L"caption"][L"border"] == L"right")
						m_sLayout.CaptionBorder = BorderType::Right;
					else
						m_sLayout.CaptionBorder = BorderType::Bottom;
				}
				else
					m_sLayout.Caption = false;
				QueryService()->AlignControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormView::TextureCreate(IRenderer *renderer, const Image &bitmap, ITexture **result, const bool edge)
		{
			if (!(*result))
			{
				*result = renderer->CreateTextureFromImage(bitmap, 1, TextureFormat::RGBA, true);
				if (*result && edge)
				{
					(*result)->setWrapS(TextureWrap::ClampToEdge);
					(*result)->setWrapT(TextureWrap::ClampToEdge);
				}
			}
			return *result != nullptr;
		}
	#pragma endregion

	#pragma region Paint
		void CFormView::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			if (PrepareCanvas(renderer, &m_pCanvas, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });
				RenderBorder(renderer);
				RenderLeftBorder(renderer, m_sLayout.Left);
				RenderTopBorder(renderer, m_sLayout.Top);
				RenderRightBorder(renderer, m_sLayout.Right);
				RenderBottomBorder(renderer, m_sLayout.Bottom);
				RenderCaption(renderer);
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}

		void CFormView::RenderBorder(IRenderer *renderer)
		{
			if (m_sBorderWidth.has_positive())
			{
				State st{ (getControl(0) && getControl(0)->isFocused()) ? State::Active : State::Normal };
				if (m_aBorderColor[(int)st].Left.A > 0 || m_aBorderColor[(int)st].Top.A > 0 || m_aBorderColor[(int)st].Right.A > 0 || m_aBorderColor[(int)st].Bottom.A > 0)
				{
					BlockColors colors{ m_aBorderColor[(int)st].Left, m_aBorderColor[(int)st].Top, m_aBorderColor[(int)st].Right, m_aBorderColor[(int)st].Bottom, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
					renderer->DrawBlock(getRect(), m_sBorderWidth, RectF{ 0, 0, 0, 0 }, colors);
				}
			}
		}

		void CFormView::RenderLeftBorder(IRenderer *renderer, BORDER &border)
		{
			if (ntl::IsLessOrEqual<float>(border.Size, 0))
				return;
			PointF client{ getHeight() - (m_sLayout.Landscape ? 0 : m_sLayout.Bottom.Size) - m_sBorderWidth.Bottom, (m_sLayout.Landscape ? 0 : m_sLayout.Top.Size) + m_sBorderWidth.Top };
			if (ntl::IsLessOrEqual<float>(client.X - client.Y, 0))
				return;
			Mat4f r, t, s;
			ntl::RotateZ<float>(r, -ntl::HalfPi<float>);
			CStorePrimitiveMatrix s_matrix{ renderer };
			// Start
			if (!border.BitmapStart.isEmpty())
			{
				if (TextureCreate(renderer, border.BitmapStart, &border.TextureStart, false))
				{
					ntl::Scale<float>(s, 1, border.Size / (float)border.BitmapStart.Height, 1);
					ntl::Translate<float>(t, m_sBorderWidth.Left, client.X, 0);
					renderer
						->ActivatePrimitiveMatrix(t * r * s)
						->DrawImage(border.TextureStart, 1);
					client.X -= (float)border.BitmapStart.Width;
				}
			}
			// End
			if (!border.BitmapEnd.isEmpty() && ntl::IsGreater<float>(client.X - client.Y, 0))
			{
				if (TextureCreate(renderer, border.BitmapEnd, &border.TextureEnd, false))
				{
					ntl::Scale<float>(s, 1, border.Size / (float)border.BitmapEnd.Height, 1);
					ntl::Translate<float>(t, m_sBorderWidth.Left, client.Y + (float)border.BitmapEnd.Width, 0);
					renderer
						->ActivatePrimitiveMatrix(t * r * s)
						->DrawImage(border.TextureEnd, 1);
					client.Y += (float)border.BitmapEnd.Width;
				}
			}
			if (ntl::IsGreater<float>(client.X - client.Y, 0))
			{
				// Middle
				bool middle_drawn{ false };
				if (!border.BitmapMiddle.isEmpty())
				{
					if (TextureCreate(renderer, border.BitmapMiddle, &border.TextureMiddle, false))
					{
						ntl::Scale<float>(s, 1, border.Size / (float)border.BitmapMiddle.Height, 1);
						float p{ client.X - (client.X - client.Y - (float)border.BitmapMiddle.Width) / 2 };
						ntl::Translate<float>(t, m_sBorderWidth.Left, p, 0);
						renderer
							->ActivatePrimitiveMatrix(t * r * s)
							->DrawImage(border.TextureMiddle, 1);
						middle_drawn = true;
						if (ntl::IsLess<float>(p, client.X) && !border.BitmapFill.isEmpty())
						{
							// Filler
							if (TextureCreate(renderer, border.BitmapFill, &border.TextureFill, true))
							{
								float w{ client.X - p };
								ntl::Scale<float>(s, (w + 1) / (float)border.BitmapFill.Width, border.Size / (float)border.BitmapFill.Height, 1);
								ntl::Translate<float>(t, m_sBorderWidth.Left, client.X, 0);
								renderer
									->ActivatePrimitiveMatrix(t * r * s)
									->DrawImage(border.TextureFill, 1);
								ntl::Translate<float>(t, m_sBorderWidth.Left, client.X - w - (float)border.BitmapMiddle.Width, 0);
								renderer
									->ActivatePrimitiveMatrix(t * r * s)
									->DrawImage(border.TextureFill, 1);
							}
						}
					}
				}
				if (!middle_drawn && !border.BitmapFill.isEmpty())
				{
					if (TextureCreate(renderer, border.BitmapFill, &border.TextureFill, true))
					{
						ntl::Scale<float>(s, (client.X - client.Y) / (float)border.BitmapFill.Width, border.Size / (float)border.BitmapFill.Height, 1);
						ntl::Translate<float>(t, m_sBorderWidth.Left, client.X, 0);
						renderer
							->ActivatePrimitiveMatrix(t * r * s)
							->DrawImage(border.TextureFill, 1);
					}
				}
			}
		}

		void CFormView::RenderTopBorder(IRenderer *renderer, BORDER &border)
		{
			if (ntl::IsLessOrEqual<float>(border.Size, 0))
				return;
			PointF client{ (m_sLayout.Landscape ? m_sLayout.Left.Size : 0) + m_sBorderWidth.Left, getWidth() - (m_sLayout.Landscape ? m_sLayout.Right.Size : 0) - m_sBorderWidth.Right };
			if (ntl::IsLessOrEqual<float>(client.Y - client.X, 0))
				return;
			Mat4f t, s;
			CStorePrimitiveMatrix s_matrix{ renderer };
			// Start
			if (!border.BitmapStart.isEmpty())
			{
				if (TextureCreate(renderer, border.BitmapStart, &border.TextureStart, false))
				{
					ntl::Scale<float>(s, 1, border.Size / (float)border.BitmapStart.Height, 1);
					ntl::Translate<float>(t, client.X, m_sBorderWidth.Top, 0);
					renderer
						->ActivatePrimitiveMatrix(t * s)
						->DrawImage(border.TextureStart, 1);
					client.X += (float)border.BitmapStart.Width;
				}
			}
			// End
			if (!border.BitmapEnd.isEmpty() && ntl::IsGreater<float>(client.Y - client.X, 0))
			{
				if (TextureCreate(renderer, border.BitmapEnd, &border.TextureEnd, false))
				{
					ntl::Scale<float>(s, 1, border.Size / (float)border.BitmapEnd.Height, 1);
					ntl::Translate<float>(t, client.Y - (float)border.BitmapEnd.Width, m_sBorderWidth.Top, 0);
					renderer
						->ActivatePrimitiveMatrix(t * s)
						->DrawImage(border.TextureEnd, 1);
					client.Y -= (float)border.BitmapEnd.Width;
				}
			}
			if (ntl::IsGreater<float>(client.Y - client.X, 0))
			{
				// Middle
				bool middle_drawn{ false };
				if (!border.BitmapMiddle.isEmpty())
				{
					if (TextureCreate(renderer, border.BitmapMiddle, &border.TextureMiddle, false))
					{
						ntl::Scale<float>(s, 1, border.Size / (float)border.BitmapMiddle.Height, 1);
						float p{ client.X + (client.Y - client.X - (float)border.BitmapMiddle.Width) / 2 };
						ntl::Translate<float>(t, p, m_sBorderWidth.Top, 0);
						renderer
							->ActivatePrimitiveMatrix(t * s)
							->DrawImage(border.TextureMiddle, 1);
						middle_drawn = true;
						if (ntl::IsGreater<float>(p, client.X) && !border.BitmapFill.isEmpty())
						{
							// Filler
							if (TextureCreate(renderer, border.BitmapFill, &border.TextureFill, true))
							{
								float w{ p - client.X };
								ntl::Scale<float>(s, (w + 1) / (float)border.BitmapFill.Width, border.Size / (float)border.BitmapFill.Height, 1);
								ntl::Translate<float>(t, client.X, m_sBorderWidth.Top, 0);
								renderer
									->ActivatePrimitiveMatrix(t * s)
									->DrawImage(border.TextureFill, 1);
								ntl::Translate<float>(t, client.X + w + (float)border.BitmapMiddle.Width, m_sBorderWidth.Top, 0);
								renderer
									->ActivatePrimitiveMatrix(t * s)
									->DrawImage(border.TextureFill, 1);
							}
						}
					}
				}
				if (!middle_drawn && !border.BitmapFill.isEmpty())
				{
					if (TextureCreate(renderer, border.BitmapFill, &border.TextureFill, true))
					{
						ntl::Scale<float>(s, (client.Y - client.X) / (float)border.BitmapFill.Width, border.Size / (float)border.BitmapFill.Height, 1);
						ntl::Translate<float>(t, client.X, m_sBorderWidth.Top, 0);
						renderer
							->ActivatePrimitiveMatrix(t * s)
							->DrawImage(border.TextureFill, 1);
					}
				}
			}
		}

		void CFormView::RenderRightBorder(IRenderer *renderer, BORDER &border)
		{
			if (ntl::IsLessOrEqual<float>(border.Size, 0))
				return;
			PointF client{ (m_sLayout.Landscape ? 0 : m_sLayout.Top.Size) + m_sBorderWidth.Top, getHeight() - (m_sLayout.Landscape ? 0 : m_sLayout.Bottom.Size) - m_sBorderWidth.Bottom };
			if (ntl::IsLessOrEqual<float>(client.Y - client.X, 0))
				return;
			Mat4f r, t, s;
			ntl::RotateZ<float>(r, ntl::HalfPi<float>);
			CStorePrimitiveMatrix s_matrix{ renderer };
			// Start
			if (!border.BitmapStart.isEmpty())
			{
				if (TextureCreate(renderer, border.BitmapStart, &border.TextureStart, false))
				{
					ntl::Scale<float>(s, 1, border.Size / (float)border.BitmapStart.Height, 1);
					ntl::Translate<float>(t, getWidth() - m_sBorderWidth.Right, client.X, 0);
					renderer
						->ActivatePrimitiveMatrix(t * r * s)
						->DrawImage(border.TextureStart, 1);
					client.X += (float)border.BitmapStart.Width;
				}
			}
			// End
			if (!border.BitmapEnd.isEmpty() && ntl::IsGreater<float>(client.Y - client.X, 0))
			{
				if (TextureCreate(renderer, border.BitmapEnd, &border.TextureEnd, false))
				{
					ntl::Scale<float>(s, 1, border.Size / (float)border.BitmapEnd.Height, 1);
					ntl::Translate<float>(t, getWidth() - m_sBorderWidth.Right, client.Y - (float)border.BitmapEnd.Width, 0);
					renderer
						->ActivatePrimitiveMatrix(t * r * s)
						->DrawImage(border.TextureEnd, 1);
					client.Y -= (float)border.BitmapEnd.Width;
				}
			}
			if (ntl::IsGreater<float>(client.Y - client.X, 0))
			{
				// Middle
				bool middle_drawn{ false };
				if (!border.BitmapMiddle.isEmpty())
				{
					if (TextureCreate(renderer, border.BitmapMiddle, &border.TextureMiddle, false))
					{
						ntl::Scale<float>(s, 1, border.Size / (float)border.BitmapMiddle.Height, 1);
						float p{ client.X + (client.Y - client.X - (float)border.BitmapMiddle.Width) / 2 };
						ntl::Translate<float>(t, getWidth() - m_sBorderWidth.Right, p, 0);
						renderer
							->ActivatePrimitiveMatrix(t * r * s)
							->DrawImage(border.TextureMiddle, 1);
						middle_drawn = true;
						if (ntl::IsGreater<float>(p, client.X) && !border.BitmapFill.isEmpty())
						{
							// Filler
							if (TextureCreate(renderer, border.BitmapFill, &border.TextureFill, true))
							{
								float w{ p - client.X };
								ntl::Scale<float>(s, (w + 1) / (float)border.BitmapFill.Width, border.Size / (float)border.BitmapFill.Height, 1);
								ntl::Translate<float>(t, getWidth() - m_sBorderWidth.Right, client.X, 0);
								renderer
									->ActivatePrimitiveMatrix(t * r * s)
									->DrawImage(border.TextureFill, 1);
								ntl::Translate<float>(t, getWidth() - m_sBorderWidth.Right, client.X + w + (float)border.BitmapMiddle.Width, 0);
								renderer
									->ActivatePrimitiveMatrix(t * r * s)
									->DrawImage(border.TextureFill, 1);
							}
						}
					}
				}
				if (!middle_drawn && !border.BitmapFill.isEmpty())
				{
					if (TextureCreate(renderer, border.BitmapFill, &border.TextureFill, true))
					{
						ntl::Scale<float>(s, (client.Y - client.X) / (float)border.BitmapFill.Width, border.Size / (float)border.BitmapFill.Height, 1);
						ntl::Translate<float>(t, getWidth() - m_sBorderWidth.Right, client.X, 0);
						renderer
							->ActivatePrimitiveMatrix(t * r * s)
							->DrawImage(border.TextureFill, 1);
					}
				}
			}
		}

		void CFormView::RenderBottomBorder(IRenderer *renderer, BORDER &border)
		{
			if (ntl::IsLessOrEqual<float>(border.Size, 0))
				return;
			PointF client{ (m_sLayout.Landscape ? m_sLayout.Left.Size : 0) + m_sBorderWidth.Left, getWidth() - (m_sLayout.Landscape ? m_sLayout.Right.Size : 0) - m_sBorderWidth.Right };
			if (ntl::IsLessOrEqual<float>(client.Y - client.X, 0))
				return;
			Mat4f t, s;
			CStorePrimitiveMatrix s_matrix{ renderer };
			// Start
			if (!border.BitmapStart.isEmpty())
			{
				if (TextureCreate(renderer, border.BitmapStart, &border.TextureStart, false))
				{
					ntl::Scale<float>(s, 1, border.Size / (float)border.BitmapStart.Height, 1);
					ntl::Translate<float>(t, client.X, getHeight() - border.Size - m_sBorderWidth.Bottom, 0);
					renderer
						->ActivatePrimitiveMatrix(t * s)
						->DrawImage(border.TextureStart, 1);
					client.X += (float)border.BitmapStart.Width;
				}
			}
			// End
			if (!border.BitmapEnd.isEmpty() && ntl::IsGreater<float>(client.Y - client.X, 0))
			{
				if (TextureCreate(renderer, border.BitmapEnd, &border.TextureEnd, false))
				{
					ntl::Scale<float>(s, 1, border.Size / (float)border.BitmapEnd.Height, 1);
					ntl::Translate<float>(t, client.Y - (float)border.BitmapEnd.Width, getHeight() - border.Size - m_sBorderWidth.Bottom, 0);
					renderer
						->ActivatePrimitiveMatrix(t * s)
						->DrawImage(border.TextureEnd, 1);
					client.Y -= (float)border.BitmapEnd.Width;
				}
			}
			if (ntl::IsGreater<float>(client.Y - client.X, 0))
			{
				// Middle
				bool middle_drawn{ false };
				if (!border.BitmapMiddle.isEmpty())
				{
					if (TextureCreate(renderer, border.BitmapMiddle, &border.TextureMiddle, false))
					{
						ntl::Scale<float>(s, 1, border.Size / (float)border.BitmapMiddle.Height, 1);
						float p{ client.X + (client.Y - client.X - (float)border.BitmapMiddle.Width) / 2 };
						ntl::Translate<float>(t, p, getHeight() - border.Size - m_sBorderWidth.Bottom, 0);
						renderer
							->ActivatePrimitiveMatrix(t * s)
							->DrawImage(border.TextureMiddle, 1);
						middle_drawn = true;
						if (ntl::IsGreater<float>(p, client.X) && !border.BitmapFill.isEmpty())
						{
							// Filler
							if (TextureCreate(renderer, border.BitmapFill, &border.TextureFill, true))
							{
								float w{ p - client.X };
								ntl::Scale<float>(s, (w + 1) / (float)border.BitmapFill.Width, border.Size / (float)border.BitmapFill.Height, 1);
								ntl::Translate<float>(t, client.X, getHeight() - border.Size - m_sBorderWidth.Bottom, 0);
								renderer
									->ActivatePrimitiveMatrix(t * s)
									->DrawImage(border.TextureFill, 1);
								ntl::Translate<float>(t, client.X + w + (float)border.BitmapMiddle.Width, getHeight() - border.Size - m_sBorderWidth.Bottom, 0);
								renderer
									->ActivatePrimitiveMatrix(t * s)
									->DrawImage(border.TextureFill, 1);
							}
						}
					}
				}
				if (!middle_drawn && !border.BitmapFill.isEmpty())
				{
					if (TextureCreate(renderer, border.BitmapFill, &border.TextureFill, true))
					{
						ntl::Scale<float>(s, (client.Y - client.X) / (float)border.BitmapFill.Width, border.Size / (float)border.BitmapFill.Height, 1);
						ntl::Translate<float>(t, client.X, getHeight() - border.Size - m_sBorderWidth.Bottom, 0);
						renderer
							->ActivatePrimitiveMatrix(t * s)
							->DrawImage(border.TextureFill, 1);
					}
				}
			}
		}

		void CFormView::RenderCaption(IRenderer *renderer)
		{
			if (m_sLayout.Caption && m_sCaption.length() > 0)
			{
				IFont *font{ getFont() };
				IPlatformFont *pf{ font->getPlatformFont(renderer) };
				if (pf)
				{
					PointF size{ pf->getStringSize(m_sCaption, font->Distance) };
					Mat4f r, t;
					switch (m_sLayout.CaptionBorder)
					{
					case BorderType::Left:
						ntl::RotateZ<float>(r, -ntl::HalfPi<float>);
						ntl::Translate<float>(t,
							std::round(m_sLayout.CaptionPadding.Top + (m_sLayout.Left.Size - m_sLayout.CaptionPadding.Top - m_sLayout.CaptionPadding.Bottom - size.Y) * 0.5f + m_sBorderWidth.Left),
							getHeight() - m_sLayout.CaptionPadding.Left - m_sBorderWidth.Bottom,
							0
						);
						break;
					case BorderType::Right:
						ntl::RotateZ<float>(r, ntl::HalfPi<float>);
						ntl::Translate<float>(t,
							std::round(getWidth() - m_sLayout.CaptionPadding.Top - (m_sLayout.Right.Size - m_sLayout.CaptionPadding.Top - m_sLayout.CaptionPadding.Bottom - size.Y) * 0.5f - m_sBorderWidth.Right),
							m_sLayout.CaptionPadding.Left + m_sBorderWidth.Top,
							0
						);
						break;
					case BorderType::Bottom:
						ntl::Identity<float>(r);
						ntl::Translate<float>(t,
							m_sLayout.CaptionPadding.Left + m_sBorderWidth.Left,
							std::round(getHeight() - m_sLayout.Bottom.Size + m_sLayout.CaptionPadding.Top + (m_sLayout.Bottom.Size - m_sLayout.CaptionPadding.Top - m_sLayout.CaptionPadding.Bottom - size.Y) * 0.5f - m_sBorderWidth.Bottom),
							0
						);
						break;
					default:
						ntl::Identity<float>(r);
						ntl::Translate<float>(t,
							m_sLayout.CaptionPadding.Left + m_sBorderWidth.Left,
							std::round(m_sLayout.CaptionPadding.Top + (m_sLayout.Top.Size - m_sLayout.CaptionPadding.Top - m_sLayout.CaptionPadding.Bottom - size.Y) * 0.5f + m_sBorderWidth.Top),
							0
						);
					}
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivatePrimitiveMatrix(t * r)
						->DrawText(m_sCaption, pf, font->Distance, font->Color);
				}
			}
		}
	#pragma endregion
	}
}