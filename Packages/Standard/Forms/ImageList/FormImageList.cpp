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
		const String CFormImageList::ClassName{ L"FormImageList" };

	#pragma region Service
		CFormImageList::CFormImageListService::CFormImageListService(CFormImageList *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormImageList::CFormImageListService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormImageList::CFormImageList(IWindow *window, IRenderer *renderer) :
			IFormImageListProto(window, renderer, ClassName)
		{
			setService(new CFormImageListService(this), true);
			CLockRepaint lock{ this };
			m_pContainerButtons->setOutlineInEditor(false);
			LoadTranslatableTexts();
		}

		void CFormImageList::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Image List"));
			m_pButtonAdd->setCaption(Application->Translate->t(ClassName, L"Add..."));
			m_pButtonDelete->setCaption(Application->Translate->t(ClassName, L"Delete"));
			m_pButtonClear->setCaption(Application->Translate->t(ClassName, L"Clear"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormImageList::ButtonAdd_OnClick(IControl *sender)
		{
			String filter{ Application->Picture->Filter }, filename;
			if (Application->Dialogs->Open(filter, 0, filename, false, false, true, true, false, false))
			{
				Image *bmp{ new Image() };
				*bmp = Application->Picture->Load(filename);
				if (bmp->Width > 0 && bmp->Height > 0)
					m_pImageList->AddImage(bmp);
				else
					delete bmp;
			}
		}

		void CFormImageList::ButtonDelete_OnClick(IControl *sender)
		{
			m_pImageListEditor->DeleteSelectedImages();
		}

		void CFormImageList::ButtonClear_OnClick(IControl *sender)
		{
			m_pImageList->DeleteImages();
		}

		void CFormImageList::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormImageList::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		int CFormImageList::getImageCount()
		{
			return m_pImageList->getImageCount();
		}

		Image *CFormImageList::getImage(const int index)
		{
			return m_pImageList->getImage(index);
		}
	#pragma endregion

	#pragma region Images
		int CFormImageList::AddImage(Image *value)
		{
			return m_pImageList->AddImage(value);
		}

		bool CFormImageList::DeleteImage(const int index)
		{
			return m_pImageList->DeleteImage(index);
		}

		bool CFormImageList::DeleteImages()
		{
			return m_pImageList->DeleteImages();
		}
	#pragma endregion
	}
}