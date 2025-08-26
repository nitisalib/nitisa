// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		const String CFormSelectListItem::ClassName{ L"FormSelectListItem" };
		CFormSelectListItem *CFormSelectListItem::m_pInstance{ nullptr };

	#pragma region Service
		CFormSelectListItem::CFormSelectListItemService::CFormSelectListItemService(CFormSelectListItem *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormSelectListItem::CFormSelectListItemService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormSelectListItem::CFormSelectListItem(IWindow *window, IRenderer *renderer) :
			IFormSelectListItemProto(window, renderer, ClassName)
		{
			setService(new CFormSelectListItemService(this), true);
			if (!m_pInstance)
				m_pInstance = this;
			LoadTranslatableTexts();
		}

		CFormSelectListItem::~CFormSelectListItem()
		{
			if (m_pInstance == this)
				m_pInstance = nullptr;
		}

		void CFormSelectListItem::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Select Item Type"));
			m_pLabelItemTypeIndex->setCaption(Application->Translate->t(ClassName, L"Item Type:"));
			int index{ ntl::Max<int>(0, m_pDropDownItemTypeIndex->getActiveIndex()) };
			m_pDropDownItemTypeIndex->Clear();
			m_pDropDownItemTypeIndex->Add(Application->Translate->t(ClassName, L"Label"));
			m_pDropDownItemTypeIndex->Add(Application->Translate->t(ClassName, L"Category"));
			m_pDropDownItemTypeIndex->setActiveIndex(index);
			m_pLabelItemCaption->setCaption(Application->Translate->t(ClassName, L"Caption:"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormSelectListItem::FormSelectListItemProto_OnKeyUp(IForm *sender, const MessageKey &m)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if (m.Key == Key::Return || m.Key == Key::Separator)
				setModalResult(ModalResult::Ok);
		}

		void CFormSelectListItem::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormSelectListItem::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		int CFormSelectListItem::getItemTypeIndex()
		{
			return m_pDropDownItemTypeIndex->getActiveIndex();
		}

		String CFormSelectListItem::getItemCaption()
		{
			return m_pEditItemCaption->getText();
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormSelectListItem::setItemTypeIndex(const int value)
		{
			if (value >= 0 && value < 2 && value != m_pDropDownItemTypeIndex->getActiveIndex())
			{
				m_pDropDownItemTypeIndex->setActiveIndex(value);
				return true;
			}
			return false;
		}

		bool CFormSelectListItem::setItemCaption(const String &value)
		{
			return m_pEditItemCaption->setText(value);
		}
	#pragma endregion

	#pragma region Getters
		CFormSelectListItem *CFormSelectListItem::getInstance()
		{
			return m_pInstance;
		}
	#pragma endregion
	}
}