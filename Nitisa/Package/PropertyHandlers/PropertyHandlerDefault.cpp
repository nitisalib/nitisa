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
#pragma region Constructor & destructor
	CPropertyHandlerDefault::CPropertyHandlerDefault(IPackage *package) :
		CPropertyHandler(package, L""),
		m_pListener{ nullptr }
	{

	}

	CPropertyHandlerDefault::CPropertyHandlerDefault(IPackage *package, const String &name) :
		CPropertyHandler(package, name)
	{

	}
#pragma endregion

#pragma region IBuiltInControl getters
	IBuiltInControlListener *CPropertyHandlerDefault::getListener()
	{
		return m_pListener;
	}

	bool CPropertyHandlerDefault::isDown()
	{
		return false;
	}
#pragma endregion

#pragma region IPropertyHandler getters
	IProperty *CPropertyHandlerDefault::getProperty()
	{
		return nullptr;
	}

	String CPropertyHandlerDefault::getPropertyState()
	{
		return L"";
	}

	bool CPropertyHandlerDefault::isEditable(IProperty *property)
	{
		return true;
	}
#pragma endregion

#pragma region IBuiltInControl setters
	void CPropertyHandlerDefault::setListener(IBuiltInControlListener *value)
	{
		m_pListener = value;
	}
#pragma endregion

#pragma region IPropertyHandler setters
	bool CPropertyHandlerDefault::setProperty(IProperty *value)
	{
		return true;
	}

	bool CPropertyHandlerDefault::setPropertyState(const String &value)
	{
		return false;
	}
#pragma endregion

#pragma region IBuiltInControl helpers
	void CPropertyHandlerDefault::UpdateFromStyle(IStyle *style, const String &class_name)
	{
	}

	void CPropertyHandlerDefault::Render(const bool last_pass, const Mat4f &matrix, const Block *block)
	{
		if (ntl::IsGreater<float>(getWidth(), 0) && ntl::IsGreater<float>(getHeight(), 0) && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
		{
			IRenderer *renderer{ getControl()->getForm()->getRenderer() };
			ITexture *canvas{ renderer->CreateTexture(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()), 1, TextureFormat::RGBA, true) };
			if (canvas)
			{
				CStoreBlock s_block{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				{
					CStoreTarget s_target{ renderer };
					renderer->ActivateTarget(canvas);
					renderer->Clear(Color{ 0, 0, 0, 0 });
					// Preview text
					String preview{ L"No handler found!" };
					if (getControl()->getFont())
					{
						IFont *f{ getControl()->getFont() };
						IPlatformFont *pf{ f->getPlatformFont(renderer) };
						if (pf)
						{
							float height{ pf->getStringSize(preview, f->Distance).Y };
							renderer
								->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(0, (getHeight() - height) / 2, 0))
								->DrawText(preview, pf, f->Distance, Color{ 255, 0, 0, 255 });
						}
					}
				}
				// Render canvas
				renderer
					->ActivateBlock(block)
					->ActivatePrimitiveMatrix(matrix)
					->DrawImage(canvas, 1);
				canvas->Release();
			}
		}
	}
#pragma endregion

#pragma region State change notifications
	void CPropertyHandlerDefault::NotifyOnAttach()
	{

	}

	void CPropertyHandlerDefault::NotifyOnDeactivate()
	{

	}

	void CPropertyHandlerDefault::NotifyOnFreeResources()
	{

	}
#pragma endregion

#pragma region Mouse input notifications
	bool CPropertyHandlerDefault::NotifyOnMouseHover(const PointF &position)
	{
		return false;
	}

	bool CPropertyHandlerDefault::NotifyOnMouseLeave()
	{
		return false;
	}

	bool CPropertyHandlerDefault::NotifyOnMouseMove(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CPropertyHandlerDefault::NotifyOnMouseLeftDown(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CPropertyHandlerDefault::NotifyOnMouseLeftUp(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CPropertyHandlerDefault::NotifyOnMouseLeftDoubleClick(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CPropertyHandlerDefault::NotifyOnMouseMiddleDown(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CPropertyHandlerDefault::NotifyOnMouseMiddleUp(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CPropertyHandlerDefault::NotifyOnMouseMiddleDoubleClick(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CPropertyHandlerDefault::NotifyOnMouseRightDown(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CPropertyHandlerDefault::NotifyOnMouseRightUp(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CPropertyHandlerDefault::NotifyOnMouseRightDoubleClick(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	void CPropertyHandlerDefault::NotifyOnMouseDownCancel()
	{
	}

	bool CPropertyHandlerDefault::NotifyOnMouseVerticalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		return false;
	}

	bool CPropertyHandlerDefault::NotifyOnMouseHorizontalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		return false;
	}
#pragma endregion

#pragma region Keyboard input notifications
	bool CPropertyHandlerDefault::NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}

	bool CPropertyHandlerDefault::NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}

	bool CPropertyHandlerDefault::NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}

	bool CPropertyHandlerDefault::NotifyOnDeadChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}
#pragma endregion

#pragma region Other input notifications
	bool CPropertyHandlerDefault::NotifyOnDropFiles(const PointF &position, const StringArray &filenames)
	{
		return false;
	}
#pragma endregion

#pragma region Clipboard notifications
	bool CPropertyHandlerDefault::NotifyOnPasteString(const String &text)
	{
		return false;
	}
#pragma endregion
}