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
		CImage::CGradientListener::CGradientListener(CImage *control) :
			m_pControl{ control }
		{

		}

		void CImage::CGradientListener::NotifyOnChange()
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
		CImage::CImage() :
			CControl(L"Image", true, true, false, false, false, false),
			m_cGradientListener{ this },
			m_sBorderWidth{ 1, 1, 1, 1 },
			m_sBorderRadius{ 0, 0, 0, 0 },
			m_sBorderColor{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } },
			m_sBackgroundColor{ 0, 0, 0, 0 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_sShadowColor{ 0, 0, 0, 0 },
			m_sShadowShift{ 0, 0 },
			m_iShadowRadius{ 1 },
			m_sImageTransform{ Identity },
			m_fOpacity{ 1 },
			m_pImage{ nullptr },
			m_bIgnoreGradient{ false },
			m_pCanvas{ nullptr }
		{
			setService(new CImageService(this), true);
			setSize(PointF{ 100, 100 });
		}

		CImage::CImage(IForm *parent) :CImage()
		{
			setForm(parent);
		}

		CImage::CImage(IControl *parent) : CImage()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region CControl getters
		RectF CImage::getClientRect()
		{
			RectF result{ 0, 0, getWidth(), getHeight() };
			result.Left += m_sBorderWidth.Left;
			result.Top += m_sBorderWidth.Top;
			result.Right -= m_sBorderWidth.Right;
			result.Bottom -= m_sBorderWidth.Bottom;
			result.validate();
			return result;
		}

		RectF CImage::getRenderRect()
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_sShadowColor, m_sShadowShift, m_iShadowRadius);
		}
	#pragma endregion

	#pragma region Getters
		Image *CImage::getImage()
		{
			return &m_cImage;
		}

		RectF CImage::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		RectF CImage::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		BorderColor CImage::getBorderColor() const
		{
			return m_sBorderColor;
		}

		Color CImage::getLeftBorderColor() const
		{
			return m_sBorderColor.Left;
		}

		Color CImage::getTopBorderColor() const
		{
			return m_sBorderColor.Top;
		}

		Color CImage::getRightBorderColor() const
		{
			return m_sBorderColor.Right;
		}

		Color CImage::getBottomBorderColor() const
		{
			return m_sBorderColor.Bottom;
		}

		Color CImage::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CImage::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		Color CImage::getShadowColor() const
		{
			return m_sShadowColor;
		}

		PointF CImage::getShadowShift() const
		{
			return m_sShadowShift;
		}

		int CImage::getShadowRadius() const
		{
			return m_iShadowRadius;
		}

		Mat4f &CImage::getImageTransform()
		{
			return m_sImageTransform;
		}

		float CImage::getOpacity() const
		{
			return m_fOpacity;
		}
	#pragma endregion

	#pragma region Setters
		bool CImage::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sBorderWidth *= s;
				m_sBorderRadius *= avg;
				m_sShadowShift *= s;
				m_iShadowRadius = ntl::Round<int>((float)m_iShadowRadius * avg);
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImage::setBorderWidth(const RectF &value)
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

		bool CImage::setBorderRadius(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderRadius))
			{
				m_sBorderRadius = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImage::setBorderColor(const BorderColor &value)
		{
			if (value != m_sBorderColor)
			{
				m_sBorderColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImage::setLeftBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ value, m_sBorderColor.Top, m_sBorderColor.Right, m_sBorderColor.Bottom });
		}

		bool CImage::setTopBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, value, m_sBorderColor.Right, m_sBorderColor.Bottom });
		}

		bool CImage::setRightBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, m_sBorderColor.Top, value, m_sBorderColor.Bottom });
		}

		bool CImage::setBottomBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, m_sBorderColor.Top, m_sBorderColor.Right, value });
		}

		bool CImage::setBackgroundColor(const Color &value)
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

		bool CImage::setShadowColor(const Color &value)
		{
			if (value != m_sShadowColor)
			{
				m_sShadowColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImage::setShadowShift(const PointF &value)
		{
			if (IsNotEqual(value, m_sShadowShift))
			{
				CLockRepaint lock{ this };
				if (m_sShadowColor.A > 0)
					Repaint(false);
				m_sShadowShift = value;
				if (m_sShadowColor.A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CImage::setShadowRadius(const int value)
		{
			if (value >= 1 && value != m_iShadowRadius)
			{
				CLockRepaint lock{ this };
				if (m_sShadowColor.A > 0)
					Repaint(false);
				m_iShadowRadius = value;
				if (m_sShadowColor.A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CImage::setImageTransform(const Mat4f &value)
		{
			if (ntl::IsNotEqual<float>(value, m_sImageTransform))
			{
				m_sImageTransform = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CImage::setOpacity(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsLessOrEqual<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fOpacity))
			{
				m_fOpacity = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CImage::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		void CImage::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BorderWidth", m_sBorderWidth);
			style->getOption(m_sClassName + L".BorderRadius", m_sBorderRadius);
			style->getOption(m_sClassName + L".BorderColor", m_sBorderColor);
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L".ShadowColor", m_sShadowColor);
			style->getOption(m_sClassName + L".ShadowShift", m_sShadowShift);
			style->getOption(m_sClassName + L".ShadowRadius", m_iShadowRadius);
			style->getOption(m_sClassName + L".Opacity", m_fOpacity);
			m_bIgnoreGradient = false;
		}

		void CImage::Assign(const Image &data)
		{
			m_cImage = data;
			Update();
		}

		bool CImage::Assign(ITexture *texture)
		{
			if (texture)
			{
				ITexture::IData *data{ texture->Lock(TextureFormat::RGBA, 0, true) };
				if (data)
				{
					Point size{ texture->Size };
					m_cImage.setSize(size.X, size.Y);
					for (int y = 0; y < size.Y; y++)
						for (int x = 0; x < size.X; x++)
							m_cImage[x][y] = data->getColor(x, y);
					data->Release();
					Update();
					return true;
				}
			}
			return false;
		}

		void CImage::Update()
		{
			if (m_pImage)
				m_pImage->setValid(false);
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
		}
	#pragma endregion

	#pragma region Paint
		void CImage::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			PointF disp{ DispOnCanvas(m_sShadowColor, m_sShadowShift, m_iShadowRadius) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_sShadowColor, m_sShadowShift, m_iShadowRadius) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				Block b{ RectF{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() }, m_sBorderWidth, m_sBorderRadius, PointLocation::Inside };
				DrawBlockShadow(renderer, b.Rect, m_sBorderRadius, m_sShadowColor, m_sShadowShift, m_iShadowRadius);
				DrawSimpleBackground(renderer, b.Rect, m_sBorderWidth, m_sBorderRadius, m_sBorderColor, m_sBackgroundColor, m_cBackgroundGradient);
				// Image
				int w{ m_cImage.Width }, h{ m_cImage.Height };
				if (w > 0 && h > 0)
				{
					if (PrepareCanvas(renderer, &m_pImage, w, h))
					{
						ITexture::IData *data{ m_pImage->Lock(TextureFormat::RGBA, 0, false) };
						const Image &bmp{ m_cImage };
						if (data)
						{
							for (int y = 0; y < h; y++)
								for (int x = 0; x < w; x++)
									data->setColor(x, y, bmp[x][y]);
							data->Release();
						}
						m_pImage->setValid(true);
					}
					if (m_pImage)
					{
						CStoreBlock s_block{ renderer };
						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer
							->ActivateBlock(&b)
							->ActivatePrimitiveMatrix(m_sImageTransform * ntl::Mat4Translate<float>(b.Rect.Left, b.Rect.Top, 0))
							->DrawImage(m_pImage, m_fOpacity);
					}
				}

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}
	#pragma endregion
	}
}