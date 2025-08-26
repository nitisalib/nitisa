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
	#pragma region CGradientListener
		CGradientEditor::CGradientListener::CGradientListener(CGradientEditor *control) :
			m_pControl{ control }
		{

		}

		void CGradientEditor::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient)
			{
				if (m_pControl->m_iActivePoint >= m_pControl->m_cGradient.getPointCount())
					m_pControl->m_iActivePoint = -1;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CGradientEditor::CGradientEditor() :
			CControl(L"GradientEditor", true, true, false, false, false, false),
			m_cGradientListener{ this },
			m_cGradient{ &m_cGradientListener },
			m_iActivePoint{ -1 },
			m_iHoveredPoint{ -1 },
			m_sBackgroundColor{ 127, 127, 127, 255 },
			m_fArrowSize{ 11 },
			m_aArrowColor{
				Color{ 127, 127, 127, 255 },
				Color{ 160, 160, 160, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 } },
			m_aArrowBorderColor{
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 255, 255 } },
			m_pCanvas{ nullptr },
			m_bDown{ false },
			m_bIgnoreGradient{ true },
			OnChange{ nullptr }
		{
			setService(new CGradientEditorService(this), true);
			m_cGradient.setPointCount(2);
			m_cGradient.setPointColor(0, Color{ 0, 255, 0, 255 });
			m_cGradient.setPointColor(1, Color{ 255, 0, 0, 255 });
			setSize(PointF{ 300, 50 });
			m_bIgnoreGradient = false;
		}

		CGradientEditor::CGradientEditor(IControl *parent) :CGradientEditor()
		{
			setParent(parent);
		}

		CGradientEditor::CGradientEditor(IForm *parent) : CGradientEditor()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		Gradient *CGradientEditor::getGradient()
		{
			return &m_cGradient;
		}

		int CGradientEditor::getActivePoint()
		{
			return m_iActivePoint;
		}
	#pragma endregion

	#pragma region Getters
		Color CGradientEditor::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		float CGradientEditor::getArrowSize() const
		{
			return m_fArrowSize;
		}

		Color CGradientEditor::getArrowColor(const ArrowState state) const
		{
			return m_aArrowColor[(int)state];
		}

		Color CGradientEditor::getArrowBorderColor(const ArrowState state) const
		{
			return m_aArrowBorderColor[(int)state];
		}
	#pragma endregion

	#pragma region Interface setters
		bool CGradientEditor::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				m_fArrowSize *= (s.X + s.Y) * 0.5f;
				UpdateHoveredArrow(FormToLocal((PointF)Application->Mouse->getPosition()));
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CGradientEditor::setActivePoint(const int value)
		{
			if (value < 0 && m_iActivePoint < 0)
				return false;
			if (value < m_cGradient.getPointCount() && value != m_iActivePoint)
			{
				m_iActivePoint = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CGradientEditor::setBackgroundColor(const Color &value)
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

		bool CGradientEditor::setArrowSize(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fArrowSize))
			{
				m_fArrowSize = value;
				if (m_pCanvas && m_cGradient.getPointCount() > 0)
				{
					UpdateHoveredArrow(FormToLocal((PointF)Application->Mouse->getPosition()));
					m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGradientEditor::setArrowColor(const ArrowState state, const Color &value)
		{
			if (value != m_aArrowColor[(int)state])
			{
				m_aArrowColor[(int)state] = value;
				if (ntl::IsGreater<float>(m_fArrowSize, 0) && m_cGradient.getPointCount() > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CGradientEditor::setArrowBorderColor(const ArrowState state, const Color &value)
		{
			if (value != m_aArrowBorderColor[(int)state])
			{
				m_aArrowBorderColor[(int)state] = value;
				if (ntl::IsGreater<float>(m_fArrowSize, 0) && m_cGradient.getPointCount() > 0)
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
		void CGradientEditor::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		void CGradientEditor::UpdateFromStyle(IStyle *style)
		{
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".ArrowSize", m_fArrowSize);
			for (int i = 0; i <= (int)ArrowState::ActiveHovered; i++)
			{
				String state;
				switch ((ArrowState)i)
				{
				case ArrowState::Hovered:
					state = L"Hovered";
					break;
				case ArrowState::Active:
					state = L"Active";
					break;
				case ArrowState::ActiveHovered:
					state = L"ActiveHovered";
					break;
				default:
					state = L"Normal";
				}
				style->getOption(m_sClassName + L".ArrowColor[" + state + L"]", m_aArrowColor[i]);
				style->getOption(m_sClassName + L".ArrowBorderColor[" + state + L"]", m_aArrowBorderColor[i]);
			}
		}

		bool CGradientEditor::UpdateHoveredArrow(const PointF &position)
		{
			if (m_cGradient.getPointCount() > 0)
			{
				int new_index{ -1 };
				if (ntl::IsGreater<float>(m_fArrowSize, 0))
				{
					RectF r{ 0, getHeight() - m_fArrowSize, getWidth(), getHeight() };
					if (r.is_valid() && !r.is_zero() && position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
						for (int i = 0; i < m_cGradient.getPointCount(); i++)
						{
							r.Left = (getWidth() - m_fArrowSize) * m_cGradient.getPoint(i).Position;
							r.Right = r.Left + m_fArrowSize;
							if (position.X >= r.Left && position.X < r.Right)
							{
								new_index = i;
								break;
							}
						}
				}
				if (new_index != m_iHoveredPoint)
				{
					m_iHoveredPoint = new_index;
					return true;
				}
			}
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CGradientEditor::Render()
		{
			if (getWidth() > 0 && getHeight() > 0)
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				if (PrepareCanvas(renderer, &m_pCanvas, getSize()))
				{
					CStoreTarget s_target{ renderer };
					renderer
						->ActivateTarget(m_pCanvas)
						->Clear(Color{ 0, 0, 0, 0 });
					RenderGradient(renderer);
					RenderArrows(renderer);
					m_pCanvas->setValid(true);
				}
				DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
			}
		}

		void CGradientEditor::RenderGradient(IRenderer *renderer)
		{
			float hw{ m_fArrowSize / 2 };
			RectF r{ hw, 0, getWidth() - m_fArrowSize + hw, getHeight() - m_fArrowSize };
			if (r.is_valid() && !r.is_zero())
			{
				if (m_cGradient.getPointCount() >= 2)
				{
					Gradient g{ m_cGradient };
					g.setType(GradientType::Horizontal);
					renderer->DrawGradient(r, g);
				}
				else if (m_sBackgroundColor.A > 0)
					renderer->DrawRectangle(r, m_sBackgroundColor);
			}
		}

		void CGradientEditor::RenderArrows(IRenderer *renderer)
		{
			if (m_cGradient.getPointCount() > 0)
			{
				float hw{ m_fArrowSize / 2 };
				RectF r{ 0, getHeight() - m_fArrowSize, getWidth(), getHeight() };
				if (r.is_valid() && !r.is_zero())
				{
					ITexture *arrow{ renderer->CreateTexture(ntl::Round<int>(m_fArrowSize), ntl::Round<int>(m_fArrowSize), 1, TextureFormat::RGBA, true) };
					if (arrow)
					{
						for (int i = 0; i < m_cGradient.getPointCount(); i++)
						{
							r.Left = (getWidth() - m_fArrowSize) * m_cGradient.getPoint(i).Position;
							r.Right = r.Left + m_fArrowSize;
							ArrowState state{ i == m_iActivePoint ? (i == m_iHoveredPoint ? ArrowState::ActiveHovered : ArrowState::Active) : (i == m_iHoveredPoint ? ArrowState::Hovered : ArrowState::Normal) };
							CStorePrimitiveMatrix s_matrix{ renderer };
							renderer
								->ActivateTarget(arrow)
								->Clear(Color{ 0, 0, 0, 0 })
								->DrawRectangle(RectF{ 0, hw, m_fArrowSize - 1, m_fArrowSize - 1 }, m_aArrowColor[(int)state])
								->DrawTriangle(PointF{ 0, hw }, PointF{ hw, 0 }, PointF{ m_fArrowSize - 1, hw }, m_aArrowColor[(int)state])
								->DrawLines({
									PointF{ 1, m_fArrowSize - 1 },
									PointF{ 0, hw - 0.5f },
									PointF{ hw - 0.5f, 0 },
									PointF{ m_fArrowSize - 1, hw },
									PointF{ m_fArrowSize - 1, m_fArrowSize - 1 },
									PointF{ 0 , m_fArrowSize - 1 } },
									m_aArrowBorderColor[(int)state],
									false)
								->ActivateTarget(m_pCanvas)
								->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(r.Left), std::round(r.Top), 0))
								->DrawImage(arrow, 1);
						}
						arrow->Release();
					}
				}
			}
		}
	#pragma endregion
	}
}