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
		const String CDialogBoxMenuListItem::ClassName{ L"DialogBoxMenuListItem" };

	#pragma region Service
		CDialogBoxMenuListItem::CDialogBoxMenuListItemService::CDialogBoxMenuListItemService(CDialogBoxMenuListItem *control) :
			IDialogBoxMenuListItemProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxMenuListItem::CDialogBoxMenuListItemService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxMenuListItem::CDialogBoxMenuListItem() :
			IDialogBoxMenuListItemProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxMenuListItemService(this))
		{
			setStaticTabOrder(true);
			setUseMask(false);
			LoadTranslatableTexts();
		}

		CDialogBoxMenuListItem::CDialogBoxMenuListItem(IForm *parent) :CDialogBoxMenuListItem()
		{
			setForm(parent);
		}

		CDialogBoxMenuListItem::CDialogBoxMenuListItem(IControl *parent) : CDialogBoxMenuListItem()
		{
			setParent(parent);
		}

		void CDialogBoxMenuListItem::LoadTranslatableTexts()
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
		void CDialogBoxMenuListItem::FormMenuListItemProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if (m.Key == Key::Return || m.Key == Key::Separator)
				setModalResult(ModalResult::Ok);
		}

		void CDialogBoxMenuListItem::DropDownItemTypeIndex_OnSelect(IControl *sender, const int index)
		{
			m_pEditItemCaption->setEnabled(index != 3);
		}

		void CDialogBoxMenuListItem::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxMenuListItem::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		int CDialogBoxMenuListItem::getItemTypeIndex()
		{
			return m_pDropDownItemTypeIndex->getActiveIndex();
		}

		String CDialogBoxMenuListItem::getItemCaption()
		{
			return m_pEditItemCaption->getText();
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxMenuListItem::setItemTypeIndex(const int value)
		{
			if (value >= 0 && value < 4 && value != m_pDropDownItemTypeIndex->getActiveIndex())
			{
				m_pDropDownItemTypeIndex->setActiveIndex(value);
				m_pEditItemCaption->setEnabled(m_pDropDownItemTypeIndex->getActiveIndex() != 3);
				return true;
			}
			return false;
		}

		bool CDialogBoxMenuListItem::setItemCaption(const String &value)
		{
			return m_pEditItemCaption->setText(value);
		}
	#pragma endregion
	}
}