// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
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
		const String CFormImage::ClassName{ L"FormImage" };
		CFormImage *CFormImage::m_pInstance{ nullptr };

	#pragma region Service
		CFormImage::CFormImageService::CFormImageService(CFormImage *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormImage::CFormImageService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormImage::CFormImage(IWindow *window, IRenderer *renderer) :
			IFormImageProto(window, renderer, ClassName)
		{
			setService(new CFormImageService(this), true);
			if (!m_pInstance)
				m_pInstance = this;
			CLockRepaint lock{ this };
			m_pContainer->setOutlineInEditor(false);
			LoadTranslatableTexts();
		}

		CFormImage::~CFormImage()
		{
			if (m_pInstance == this)
				m_pInstance = nullptr;
		}

		void CFormImage::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Image"));
			m_pPanelWarning->setCaption(Application->Translate->t(ClassName, L"If you add big image, the form save and load time will take awhile!"));
			m_pButtonLoad->setCaption(Application->Translate->t(ClassName, L"Load..."));
			m_pButtonClear->setCaption(Application->Translate->t(ClassName, L"Clear"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
			m_pLabelSize->setCaption(Application->Translate->t(ClassName, L"W: {width}\nH: {height}",
				{ { L"{width}", ToString(m_pImage->getImage()->Width) },{ L"{height}", ToString(m_pImage->getImage()->Height) } }));
		}
	#pragma endregion

	#pragma region Events
		void CFormImage::FormImageProto_OnKeyUp(IForm *sender, const MessageKey &m)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if ((m.Key == Key::Return || m.Key == Key::Separator) && Application->Keyboard->isDown(Key::Control))
				setModalResult(ModalResult::Ok);
		}

		void CFormImage::ButtonLoad_OnClick(IControl *sender)
		{
			String filter{ Application->Picture->Filter }, filename;
			if (Application->Dialogs->Open(filter, 0, filename, false, false, true, true, false, false))
			{
				Image bmp{ Application->Picture->Load(filename) };
				if (bmp.Width > 0 && bmp.Height > 0)
				{
					*m_pImage->getImage() = bmp;
					m_pImage->setSize(PointF{ (float)m_pImage->getImage()->Width, (float)m_pImage->getImage()->Height });
					m_pImage->Update();
					m_pLabelSize->setCaption(Application->Translate->t(ClassName, L"W: {width}\nH: {height}",
						{ {L"{width}", ToString(bmp.Width)}, {L"{height}", ToString(bmp.Height)} }));
				}
			}
		}

		void CFormImage::ButtonClear_OnClick(IControl *sender)
		{
			m_pImage->setSize(PointF{ 0, 0 });
			m_pImage->getImage()->setSize(0, 0);
			m_pImage->Update();
			m_pLabelSize->setCaption(L"");
		}

		void CFormImage::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormImage::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		Image *CFormImage::getValue()
		{
			return m_pImage->getImage();
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormImage::setValue(const Image &value)
		{
			CLockRepaint lock{ this };
			m_pImage->setSize(PointF{ (float)value.Width, (float)value.Height });
			*m_pImage->getImage() = value;
			m_pImage->Update();
			if (value.isEmpty())
				m_pLabelSize->setCaption(L"");
			else
				m_pLabelSize->setCaption(Application->Translate->t(ClassName, L"W: {width}\nH: {height}", 
					{ {L"{width}", ToString(value.Width)}, {L"{height}", ToString(value.Height)} }));
			return true;
		}
	#pragma endregion

	#pragma region Getters
		CFormImage *CFormImage::getInstance()
		{
			return m_pInstance;
		}
	#pragma endregion

	#pragma region Helpers
		void CFormImage::Update()
		{
			CLockRepaint lock{ this };
			m_pImage->setSize(PointF{ (float)m_pImage->getImage()->Width, (float)m_pImage->getImage()->Height });
			m_pImage->Update();
		}
	#pragma endregion
	}
}