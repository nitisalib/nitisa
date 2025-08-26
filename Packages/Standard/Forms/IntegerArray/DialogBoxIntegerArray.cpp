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
		const String CDialogBoxIntegerArray::ClassName{ L"DialogBoxIntegerArray" };

	#pragma region Service
		CDialogBoxIntegerArray::CDialogBoxIntegerArrayService::CDialogBoxIntegerArrayService(CDialogBoxIntegerArray *control) :
			IDialogBoxIntegerArrayProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxIntegerArray::CDialogBoxIntegerArrayService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxIntegerArray::CDialogBoxIntegerArray() :
			IDialogBoxIntegerArrayProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxIntegerArrayService(this)),
			m_iMinCount{ 0 },
			m_bHasMin{ false },
			m_bHasMax{ false },
			m_iMin{ 0 },
			m_iMax{ 0 }
		{
			setStaticTabOrder(true);
			setUseMask(false);
			LoadTranslatableTexts();
		}

		CDialogBoxIntegerArray::CDialogBoxIntegerArray(IForm *parent) :CDialogBoxIntegerArray()
		{
			setForm(parent);
		}

		CDialogBoxIntegerArray::CDialogBoxIntegerArray(IControl *parent) : CDialogBoxIntegerArray()
		{
			setParent(parent);
		}

		void CDialogBoxIntegerArray::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Manage integer-array"));
			m_pButtonAdd->setCaption(Application->Translate->t(ClassName, L"Add"));
			m_pButtonDelete->setCaption(Application->Translate->t(ClassName, L"Delete"));
			m_pButtonUpdate->setCaption(Application->Translate->t(ClassName, L"Update"));
			m_pButtonClear->setCaption(Application->Translate->t(ClassName, L"Clear"));
			m_pLabel1->setCaption(Application->Translate->t(ClassName, L"Min count:"));
			m_pLabel2->setCaption(Application->Translate->t(ClassName, L"Min value:"));
			m_pLabel3->setCaption(Application->Translate->t(ClassName, L"Max value:"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Interface getters
		IntegerArray CDialogBoxIntegerArray::getValue()
		{
			return m_aArray;
		}

		int CDialogBoxIntegerArray::getMinCount()
		{
			return m_iMinCount;
		}

		bool CDialogBoxIntegerArray::hasMin()
		{
			return m_bHasMin;
		}

		bool CDialogBoxIntegerArray::hasMax()
		{
			return m_bHasMax;
		}

		int CDialogBoxIntegerArray::getMin()
		{
			return m_iMin;
		}

		int CDialogBoxIntegerArray::getMax()
		{
			return m_iMax;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxIntegerArray::setValue(const IntegerArray &value)
		{
			if (value != m_aArray)
			{
				CLockRepaint lock{ this };
				m_aArray = value;

				m_pListBoxArray->Clear();
				m_pButtonUpdate->setEnabled(false);
				m_pButtonDelete->setEnabled(false);
				m_pButtonClear->setEnabled(false);
				m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);

				if (m_aArray.size() > 0)
				{
					m_pButtonClear->setEnabled(true);

					for (auto v : m_aArray)
						m_pListBoxArray->Add(ToString(v));
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxIntegerArray::setMinCount(const int value)
		{
			if (value >= 0 && value != m_iMinCount)
			{
				m_iMinCount = value;
				m_pLabelMinCount->setCaption(ToString(m_iMinCount));
				m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
				return true;
			}
			return false;
		}

		bool CDialogBoxIntegerArray::setHasMin(const bool value)
		{
			if (value != m_bHasMin)
			{
				m_bHasMin = value;
				m_pLabelMinValue->setCaption(m_bHasMin ? ToString(m_iMin) : L"");
				return true;
			}
			return false;
		}

		bool CDialogBoxIntegerArray::setHasMax(const bool value)
		{
			if (value != m_bHasMax)
			{
				m_bHasMax = value;
				m_pLabelMaxValue->setCaption(m_bHasMax ? ToString(m_iMax) : L"");
				return true;
			}
			return false;
		}

		bool CDialogBoxIntegerArray::setMin(const int value)
		{
			if (value != m_iMin)
			{
				m_iMin = value;
				if (m_bHasMin)
					m_pLabelMinValue->setCaption(ToString(m_iMin));
				return true;
			}
			return false;
		}

		bool CDialogBoxIntegerArray::setMax(const int value)
		{
			if (value != m_iMax)
			{
				m_iMax = value;
				if (m_bHasMax)
					m_pLabelMaxValue->setCaption(ToString(m_iMax));
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		int CDialogBoxIntegerArray::SelectedPointIndex()
		{
			for (int i = 0; i < m_pListBoxArray->getItemCount(); i++)
				if (m_pListBoxArray->getItem(i)->isSelected())
					return i;
			return -1;
		}
	#pragma endregion

	#pragma region Events
		void CDialogBoxIntegerArray::FormIntegerArrayProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			switch (m.Key)
			{
			case Key::Escape:
				if (!ctrl && !alt && !shift)
					setModalResult(ModalResult::Cancel);
				break;
			case Key::Return:
				if (ctrl && !shift && !alt && (int)m_aArray.size() >= m_iMinCount)
					setModalResult(ModalResult::Ok);
				break;
			default:
				break;
			}
		}

		void CDialogBoxIntegerArray::ListBoxArray_OnSelect(IControl *sender, IListItem *item)
		{
			int index{ SelectedPointIndex() };
			m_pEditValue->setText(ToString(m_aArray[index]));
			m_pButtonUpdate->setEnabled(true);
			m_pButtonDelete->setEnabled(true);
		}

		void CDialogBoxIntegerArray::ButtonAdd_OnClick(IControl *sender)
		{
			int v;
			if (!TryStringToInt(m_pEditValue->getText(), v))
			{
				Application->Dialogs->Error(Application->Translate->t(ClassName, L"Integer value expected"));
				m_pEditValue->SelectAll();
				m_pEditValue->setFocus();
				return;
			}
			if (m_bHasMin && v < m_iMin)
			{
				Application->Dialogs->Error(Application->Translate->t(ClassName, L"Value is too small"));
				m_pEditValue->SelectAll();
				m_pEditValue->setFocus();
				return;
			}
			if (m_bHasMax && v > m_iMax)
			{
				Application->Dialogs->Error(Application->Translate->t(ClassName, L"Value is too big"));
				m_pEditValue->SelectAll();
				m_pEditValue->setFocus();
				return;
			}
			m_aArray.push_back(v);
			m_pListBoxArray->Add(ToString(v));
			m_pListBoxArray->getItem(m_pListBoxArray->getItemCount() - 1)->setSelected(true);
			m_pButtonClear->setEnabled(true);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CDialogBoxIntegerArray::ButtonUpdate_OnClick(IControl *sender)
		{
			int v;
			if (!TryStringToInt(m_pEditValue->getText(), v))
			{
				Application->Dialogs->Error(Application->Translate->t(ClassName, L"Integer value expected"));
				m_pEditValue->SelectAll();
				m_pEditValue->setFocus();
				return;
			}
			if (m_bHasMin && v < m_iMin)
			{
				Application->Dialogs->Error(Application->Translate->t(ClassName, L"Value is too small"));
				m_pEditValue->SelectAll();
				m_pEditValue->setFocus();
				return;
			}
			if (m_bHasMax && v > m_iMax)
			{
				Application->Dialogs->Error(Application->Translate->t(ClassName, L"Value is too big"));
				m_pEditValue->SelectAll();
				m_pEditValue->setFocus();
				return;
			}
			int index{ SelectedPointIndex() };
			m_aArray[index] = v;
			cast<IListItemLabel*>(m_pListBoxArray->getItem(index))->setCaption(ToString(v));
		}

		void CDialogBoxIntegerArray::ButtonDelete_OnClick(IControl *sender)
		{
			int index{ SelectedPointIndex() };
			m_aArray.erase(m_aArray.begin() + index);
			m_pListBoxArray->Delete(index);
			m_pButtonUpdate->setEnabled(false);
			m_pButtonClear->setEnabled(m_aArray.size() > 0);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CDialogBoxIntegerArray::ButtonClear_OnClick(IControl *sender)
		{
			m_aArray.clear();
			m_pListBoxArray->Clear();
			m_pButtonUpdate->setEnabled(false);
			m_pButtonDelete->setEnabled(false);
			m_pButtonClear->setEnabled(false);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CDialogBoxIntegerArray::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxIntegerArray::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion
	}
}