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
		CPropertyHandlerModal::CPropertyHandlerModal(IPackage *package, const String &name) :
			CPropertyHandler(package, name),
			m_pListener{ nullptr },
			m_sBorderWidth{ 2, 2, 2, 2 },
			m_sBorderColor{ Color{ 250, 250, 250, 255 }, Color{ 250, 250, 250, 200 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 } },
			m_sBackgroundColor{ 240, 240, 240, 255 },
			m_bDown{ false },
			m_bOverButton{ false }
		{

		}
	#pragma endregion

	#pragma region Interface getters
		IBuiltInControlListener *CPropertyHandlerModal::getListener()
		{
			return m_pListener;
		}

		bool CPropertyHandlerModal::isDown()
		{
			return false;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CPropertyHandlerModal::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			if (CPropertyHandler::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				m_sBorderWidth *= s;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		RectF CPropertyHandlerModal::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		BorderColor CPropertyHandlerModal::getBorderColor() const
		{
			return m_sBorderColor;
		}

		Color CPropertyHandlerModal::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}
	#pragma endregion

	#pragma region Interface setters
		void CPropertyHandlerModal::setListener(IBuiltInControlListener *value)
		{
			m_pListener = value;
		}
	#pragma endregion

	#pragma region Setters
		bool CPropertyHandlerModal::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				m_sBorderWidth = value;
				return true;
			}
			return false;
		}

		bool CPropertyHandlerModal::setBorderColor(const BorderColor &value)
		{
			if (value != m_sBorderColor)
			{
				m_sBorderColor = value;
				return true;
			}
			return false;
		}

		bool CPropertyHandlerModal::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CPropertyHandlerModal::UpdateFromStyle(IStyle *style, const String &class_name)
		{
			style->getOption(class_name + L".BorderWidth", m_sBorderWidth);
			style->getOption(class_name + L".BorderColor", m_sBorderColor);
			style->getOption(class_name + L".BackgroundColor", m_sBackgroundColor);
		}

		String CPropertyHandlerModal::getPreview()
		{
			IPropertyState *ps{ cast<IPropertyState*>(getProperty()) };
			if (ps)
				return ps->getPreview(getPropertyState());
			if (getProperty())
				return getProperty()->getPreview();
			return L"";
		}
	#pragma endregion

	#pragma region Paint
		void CPropertyHandlerModal::Render(const bool last_pass, const Mat4f &matrix, const Block *block)
		{
			if (ntl::IsGreater<float>(getWidth(), 0) && ntl::IsGreater<float>(getHeight(), 0) && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IRenderer *renderer{ getControl()->getForm()->getRenderer() };
				ITexture *canvas{ renderer->CreateTexture(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()), 1, TextureFormat::RGBA, true) };
				if (canvas)
				{
					IBaseTexture *old{ renderer->ActiveTarget };
					renderer
						->ActivateTarget(canvas)
						->Clear(Color{ 0, 0, 0, 0 });
					// Preview text
					String preview{ getPreview() };
					if (!preview.empty() && getControl()->getFont())
					{
						IFont *f{ getControl()->getFont() };
						IPlatformFont *pf{ f->getPlatformFont(renderer) };
						if (pf)
						{
							float height{ pf->getStringSize(preview, f->Distance).Y };
							CStorePrimitiveMatrix s_matrix{ renderer };
							renderer
								->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(0, (getHeight() - height) / 2, 0))
								->DrawText(preview, pf, f->Distance, f->Color);
						}
					}
					// Button
					if (m_bDown && m_bOverButton)
					{
						renderer->DrawBlock(
							RectF{ getWidth() - getHeight(), 0, getWidth(), getHeight() },
							m_sBorderWidth,
							RectF{ 0, 0, 0, 0 },
							BlockColors{ m_sBorderColor.Right, m_sBorderColor.Bottom, m_sBorderColor.Left, m_sBorderColor.Top, m_sBackgroundColor, Color{ 0, 0, 0, 0 } });
					}
					else
					{
						renderer->DrawBlock(
							RectF{ getWidth() - getHeight(), 0, getWidth(), getHeight() },
							m_sBorderWidth,
							RectF{ 0, 0, 0, 0 },
							BlockColors{ m_sBorderColor.Left, m_sBorderColor.Top, m_sBorderColor.Right, m_sBorderColor.Bottom, m_sBackgroundColor, Color{ 0, 0, 0, 0 } });
					}
					PointF center{ getWidth() - getHeight() / 2, getHeight() / 2 };
					CStoreBlock s_block{ renderer };
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->DrawRectangle(RectF{ center.X - 3, center.Y, center.X - 2, center.Y + 1 }, Color{ 0, 0, 0, 255 })
						->DrawRectangle(RectF{ center.X - 1, center.Y, center.X, center.Y + 1 }, Color{ 0, 0, 0, 255 })
						->DrawRectangle(RectF{ center.X + 1, center.Y, center.X + 2, center.Y + 1 }, Color{ 0, 0, 0, 255 })
						// Render canvas
						->ActivateTarget(old)
						->ActivateBlock(block)
						->ActivatePrimitiveMatrix(matrix)
						->DrawImage(canvas, 1);
					canvas->Release();
				}
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CPropertyHandlerModal::NotifyOnAttach()
		{
			// No action
		}

		void CPropertyHandlerModal::NotifyOnDeactivate()
		{
			// No action
		}

		void CPropertyHandlerModal::NotifyOnFreeResources()
		{
			// No acquired resources
		}
	#pragma endregion

	#pragma region Mouse input notifications
		bool CPropertyHandlerModal::NotifyOnMouseHover(const PointF &position)
		{
			if (position.X >= getWidth() - getHeight())
			{
				m_bOverButton = true;
				if (m_bDown)
					return true;
			}
			return false;
		}

		bool CPropertyHandlerModal::NotifyOnMouseLeave()
		{
			if (m_bOverButton)
			{
				m_bOverButton = false;
				if (m_bDown)
					return true;
			}
			return false;
		}

		bool CPropertyHandlerModal::NotifyOnMouseMove(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			bool over{ position.X >= getWidth() - getHeight() && position.X < getWidth() && position.Y >= 0 && position.Y < getHeight() };
			if (over != m_bOverButton)
			{
				m_bOverButton = over;
				if (m_bDown)
					return true;
			}
			return false;
		}

		bool CPropertyHandlerModal::NotifyOnMouseLeftDown(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			if (!m_bDown && !middle && !right && m_bOverButton)
			{
				m_bDown = true;
				m_bOverButton = position.X >= getWidth() - getHeight() && position.X < getWidth() && position.Y >= 0 && position.Y < getHeight();
				return true;
			}
			return false;
		}

		bool CPropertyHandlerModal::NotifyOnMouseLeftUp(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			if (m_bDown)
			{
				m_bDown = false;
				if (m_bOverButton)
					NotifyOnActivateModal();
				return true;
			}
			return false;
		}

		bool CPropertyHandlerModal::NotifyOnMouseLeftDoubleClick(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			if (m_bDown)
			{
				m_bDown = false;
				return true;
			}
			if (position.X >= 0 && position.X < getWidth() - getHeight() && position.Y >= 0 && position.Y < getHeight())
				NotifyOnActivateModal();
			return false;
		}

		bool CPropertyHandlerModal::NotifyOnMouseMiddleDown(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			if (m_bDown)
			{
				m_bDown = false;
				return true;
			}
			return false;
		}

		bool CPropertyHandlerModal::NotifyOnMouseMiddleUp(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			if (m_bDown)
			{
				m_bDown = false;
				return true;
			}
			return false;
		}

		bool CPropertyHandlerModal::NotifyOnMouseMiddleDoubleClick(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			if (m_bDown)
			{
				m_bDown = false;
				return true;
			}
			return false;
		}

		bool CPropertyHandlerModal::NotifyOnMouseRightDown(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
		{
			if (m_bDown)
			{
				m_bDown = false;
				return true;
			}
			return false;
		}

		bool CPropertyHandlerModal::NotifyOnMouseRightUp(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
		{
			if (m_bDown)
			{
				m_bDown = false;
				return true;
			}
			return false;
		}

		bool CPropertyHandlerModal::NotifyOnMouseRightDoubleClick(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
		{
			if (m_bDown)
			{
				m_bDown = false;
				return true;
			}
			return false;
		}

		void CPropertyHandlerModal::NotifyOnMouseDownCancel()
		{
			m_bDown = false;
		}

		bool CPropertyHandlerModal::NotifyOnMouseVerticalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
		{
			return false;
		}

		bool CPropertyHandlerModal::NotifyOnMouseHorizontalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
		{
			return false;
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		bool CPropertyHandlerModal::NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
		{
			return false;
		}

		bool CPropertyHandlerModal::NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
		{
			if (!m_bDown && (key == Key::Return || key == Key::Separator))
				NotifyOnActivateModal();
			return false;
		}

		bool CPropertyHandlerModal::NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
		{
			return false;
		}

		bool CPropertyHandlerModal::NotifyOnDeadChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
		{
			return false;
		}
	#pragma endregion

	#pragma region Other input notifications
		bool CPropertyHandlerModal::NotifyOnDropFiles(const PointF &position, const StringArray &filenames)
		{
			return false;
		}
	#pragma endregion

	#pragma region Clipboard notifications
		bool CPropertyHandlerModal::NotifyOnPasteString(const String &text)
		{
			return false;
		}
	#pragma endregion
	}
}