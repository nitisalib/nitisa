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
		const String CDialogBoxImage::ClassName{ L"DialogBoxImage" };

	#pragma region Service
		CDialogBoxImage::CDialogBoxImageService::CDialogBoxImageService(CDialogBoxImage *control) :
			IDialogBoxImageProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxImage::CDialogBoxImageService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxImage::CDialogBoxImage() :
			IDialogBoxImageProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxImageService(this))
		{
			setStaticTabOrder(true);
			setUseMask(false);
			setHasMinimizeBox(false);
			setHasMaximizeBox(false);
			m_pContainer->setOutlineInEditor(false);
			LoadTranslatableTexts();
		}

		CDialogBoxImage::CDialogBoxImage(IForm *parent) :CDialogBoxImage()
		{
			setForm(parent);
		}

		CDialogBoxImage::CDialogBoxImage(IControl *parent) : CDialogBoxImage()
		{
			setParent(parent);
		}

		void CDialogBoxImage::LoadTranslatableTexts()
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
		void CDialogBoxImage::FormImageProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if ((m.Key == Key::Return || m.Key == Key::Separator) && Application->Keyboard->isDown(Key::Control))
				setModalResult(ModalResult::Ok);
		}

		void CDialogBoxImage::ButtonLoad_OnClick(IControl *sender)
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

		void CDialogBoxImage::ButtonClear_OnClick(IControl *sender)
		{
			m_pImage->setSize(PointF{ 0, 0 });
			m_pImage->getImage()->setSize(0, 0);
			m_pImage->Update();
			m_pLabelSize->setCaption(L"");
		}

		void CDialogBoxImage::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxImage::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		Image *CDialogBoxImage::getValue()
		{
			return m_pImage->getImage();
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxImage::setValue(const Image &value)
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

	#pragma region Helpers
		void CDialogBoxImage::Update()
		{
			CLockRepaint lock{ this };
			m_pImage->setSize(PointF{ (float)m_pImage->getImage()->Width, (float)m_pImage->getImage()->Height });
			m_pImage->Update();
		}
	#pragma endregion
	}
}