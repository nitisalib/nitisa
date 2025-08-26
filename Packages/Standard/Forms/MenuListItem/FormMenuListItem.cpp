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
		const String CFormMenuListItem::ClassName{ L"FormMenuListItem" };
		CFormMenuListItem *CFormMenuListItem::m_pInstance{ nullptr };

	#pragma region Service
		CFormMenuListItem::CFormMenuListItemService::CFormMenuListItemService(CFormMenuListItem *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormMenuListItem::CFormMenuListItemService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormMenuListItem::CFormMenuListItem(IWindow *window, IRenderer *renderer) :
			IFormMenuListItemProto(window, renderer, ClassName)
		{
			setService(new CFormMenuListItemService(this), true);
			if (!m_pInstance)
				m_pInstance = this;
			LoadTranslatableTexts();
		}

		CFormMenuListItem::~CFormMenuListItem()
		{
			if (m_pInstance == this)
				m_pInstance = nullptr;
		}

		void CFormMenuListItem::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Select Item Type"));
			m_pLabelItemTypeIndex->setCaption(Application->Translate->t(ClassName, L"Item Type:"));
			int index{ ntl::Max<int>(0, m_pDropDownItemTypeIndex->getActiveIndex()) };
			m_pDropDownItemTypeIndex->Clear();
			m_pDropDownItemTypeIndex->Add(Application->Translate->t(ClassName, L"Label"));
			m_pDropDownItemTypeIndex->Add(Application->Translate->t(ClassName, L"Checkbox"));
			m_pDropDownItemTypeIndex->Add(Application->Translate->t(ClassName, L"Radiobutton"));
			m_pDropDownItemTypeIndex->Add(Application->Translate->t(ClassName, L"Separator"));
			m_pDropDownItemTypeIndex->setActiveIndex(index);
			m_pLabelItemCaption->setCaption(Application->Translate->t(ClassName, L"Caption:"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormMenuListItem::FormMenuListItemProto_OnKeyUp(IForm *sender, const MessageKey &m)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if (m.Key == Key::Return || m.Key == Key::Separator)
				setModalResult(ModalResult::Ok);
		}

		void CFormMenuListItem::DropDownItemTypeIndex_OnSelect(IControl *sender, const int index)
		{
			m_pEditItemCaption->setEnabled(index != 3);
		}

		void CFormMenuListItem::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormMenuListItem::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		int CFormMenuListItem::getItemTypeIndex()
		{
			return m_pDropDownItemTypeIndex->getActiveIndex();
		}

		String CFormMenuListItem::getItemCaption()
		{
			return m_pEditItemCaption->getText();
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormMenuListItem::setItemTypeIndex(const int value)
		{
			if (value >= 0 && value < 4 && value != m_pDropDownItemTypeIndex->getActiveIndex())
			{
				m_pDropDownItemTypeIndex->setActiveIndex(value);
				m_pEditItemCaption->setEnabled(m_pDropDownItemTypeIndex->getActiveIndex() != 3);
				return true;
			}
			return false;
		}

		bool CFormMenuListItem::setItemCaption(const String &value)
		{
			return m_pEditItemCaption->setText(value);
		}
	#pragma endregion

	#pragma region Getters
		CFormMenuListItem *CFormMenuListItem::getInstance()
		{
			return m_pInstance;
		}
	#pragma endregion
	}
}