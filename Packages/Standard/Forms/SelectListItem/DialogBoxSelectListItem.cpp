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
		const String CDialogBoxSelectListItem::ClassName{ L"DialogBoxSelectListItem" };

	#pragma region Service
		CDialogBoxSelectListItem::CDialogBoxSelectListItemService::CDialogBoxSelectListItemService(CDialogBoxSelectListItem *control) :
			IDialogBoxSelectListItemProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxSelectListItem::CDialogBoxSelectListItemService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxSelectListItem::CDialogBoxSelectListItem() :
			IDialogBoxSelectListItemProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxSelectListItemService(this))
		{
			setStaticTabOrder(true);
			setUseMask(false);
			LoadTranslatableTexts();
		}

		CDialogBoxSelectListItem::CDialogBoxSelectListItem(IForm *parent) :CDialogBoxSelectListItem()
		{
			setForm(parent);
		}

		CDialogBoxSelectListItem::CDialogBoxSelectListItem(IControl *parent) : CDialogBoxSelectListItem()
		{
			setParent(parent);
		}

		void CDialogBoxSelectListItem::LoadTranslatableTexts()
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
		void CDialogBoxSelectListItem::DialogBoxSelectListItemProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if (m.Key == Key::Return || m.Key == Key::Separator)
				setModalResult(ModalResult::Ok);
		}

		void CDialogBoxSelectListItem::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxSelectListItem::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		int CDialogBoxSelectListItem::getItemTypeIndex()
		{
			return m_pDropDownItemTypeIndex->getActiveIndex();
		}

		String CDialogBoxSelectListItem::getItemCaption()
		{
			return m_pEditItemCaption->getText();
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxSelectListItem::setItemTypeIndex(const int value)
		{
			if (value >= 0 && value < 2 && value != m_pDropDownItemTypeIndex->getActiveIndex())
			{
				m_pDropDownItemTypeIndex->setActiveIndex(value);
				return true;
			}
			return false;
		}

		bool CDialogBoxSelectListItem::setItemCaption(const String &value)
		{
			return m_pEditItemCaption->setText(value);
		}
	#pragma endregion
	}
}