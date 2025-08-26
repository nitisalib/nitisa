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
		const String CDialogBoxImageList::ClassName{ L"DialogBoxImageList" };

	#pragma region Service
		CDialogBoxImageList::CDialogBoxImageListService::CDialogBoxImageListService(CDialogBoxImageList *control) :
			IDialogBoxImageListProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxImageList::CDialogBoxImageListService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxImageList::CDialogBoxImageList() :
			IDialogBoxImageListProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxImageListService(this))
		{
			setStaticTabOrder(true);
			setUseMask(false);
			setHasMinimizeBox(false);
			setHasMaximizeBox(false);
			m_pContainerButtons->setOutlineInEditor(false);
			LoadTranslatableTexts();
		}

		CDialogBoxImageList::CDialogBoxImageList(IForm *parent) :CDialogBoxImageList()
		{
			setForm(parent);
		}

		CDialogBoxImageList::CDialogBoxImageList(IControl *parent) : CDialogBoxImageList()
		{
			setParent(parent);
		}

		void CDialogBoxImageList::LoadTranslatableTexts()
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
		void CDialogBoxImageList::ButtonAdd_OnClick(IControl *sender)
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

		void CDialogBoxImageList::ButtonDelete_OnClick(IControl *sender)
		{
			m_pImageListEditor->DeleteSelectedImages();
		}

		void CDialogBoxImageList::ButtonClear_OnClick(IControl *sender)
		{
			m_pImageList->DeleteImages();
		}

		void CDialogBoxImageList::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxImageList::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		int CDialogBoxImageList::getImageCount()
		{
			return m_pImageList->getImageCount();
		}

		Image *CDialogBoxImageList::getImage(const int index)
		{
			return m_pImageList->getImage(index);
		}
	#pragma endregion

	#pragma region Images
		int CDialogBoxImageList::AddImage(Image *value)
		{
			return m_pImageList->AddImage(value);
		}

		bool CDialogBoxImageList::DeleteImage(const int index)
		{
			return m_pImageList->DeleteImage(index);
		}

		bool CDialogBoxImageList::DeleteImages()
		{
			return m_pImageList->DeleteImages();
		}
	#pragma endregion
	}
}