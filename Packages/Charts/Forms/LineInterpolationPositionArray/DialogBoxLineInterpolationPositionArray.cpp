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
	namespace charts
	{
		const String CDialogBoxLineInterpolationPositionArray::ClassName{ L"DialogBoxLineInterpolationPositionArray" };

	#pragma region Service
		CDialogBoxLineInterpolationPositionArray::CDialogBoxLineInterpolationPositionArrayService::CDialogBoxLineInterpolationPositionArrayService(CDialogBoxLineInterpolationPositionArray *control) :
			IDialogBoxLineInterpolationPositionArrayProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxLineInterpolationPositionArray::CDialogBoxLineInterpolationPositionArrayService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxLineInterpolationPositionArray::CDialogBoxLineInterpolationPositionArray() :
			IDialogBoxLineInterpolationPositionArrayProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxLineInterpolationPositionArrayService(this)),
			m_iMinCount{ 0 }
		{
			setStaticTabOrder(true);
			setUseMask(false);
			LoadTranslatableTexts();
		}

		CDialogBoxLineInterpolationPositionArray::CDialogBoxLineInterpolationPositionArray(IForm *parent) :CDialogBoxLineInterpolationPositionArray()
		{
			setForm(parent);
		}

		CDialogBoxLineInterpolationPositionArray::CDialogBoxLineInterpolationPositionArray(IControl *parent) : CDialogBoxLineInterpolationPositionArray()
		{
			setParent(parent);
		}

		void CDialogBoxLineInterpolationPositionArray::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Manage line interpolation position array"));
			m_pButtonAdd->setCaption(Application->Translate->t(ClassName, L"Add"));
			m_pButtonDelete->setCaption(Application->Translate->t(ClassName, L"Delete"));
			m_pButtonUpdate->setCaption(Application->Translate->t(ClassName, L"Update"));
			m_pButtonClear->setCaption(Application->Translate->t(ClassName, L"Clear"));
			m_pLabel1->setCaption(Application->Translate->t(ClassName, L"Min count:"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
			m_pRadioButtonBefore->setCaption(Application->Translate->t(ClassName, L"Before"));
			m_pRadioButtonMiddle->setCaption(Application->Translate->t(ClassName, L"Middle"));
			m_pRadioButtonAfter->setCaption(Application->Translate->t(ClassName, L"After"));
		}
	#pragma endregion

	#pragma region Interface getters
		std::vector<LineInterpolationPosition> CDialogBoxLineInterpolationPositionArray::getValue()
		{
			return m_aArray;
		}

		int CDialogBoxLineInterpolationPositionArray::getMinCount()
		{
			return m_iMinCount;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxLineInterpolationPositionArray::setValue(const std::vector<LineInterpolationPosition> &value)
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
						m_pListBoxArray->Add(LineInterpolationPositionToString(v));
				}
				return true;
			}
			return false;
		}

		bool CDialogBoxLineInterpolationPositionArray::setMinCount(const int value)
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
	#pragma endregion

	#pragma region Helpers
		int CDialogBoxLineInterpolationPositionArray::SelectedPointIndex()
		{
			for (int i = 0; i < m_pListBoxArray->getItemCount(); i++)
				if (m_pListBoxArray->getItem(i)->isSelected())
					return i;
			return -1;
		}
	#pragma endregion

	#pragma region Events
		void CDialogBoxLineInterpolationPositionArray::FormLineInterpolationPositionArrayProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
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

		void CDialogBoxLineInterpolationPositionArray::ListBoxArray_OnSelect(IControl *sender, IListItem *item)
		{
			int index{ SelectedPointIndex() };
			switch (m_aArray[index])
			{
			case LineInterpolationPosition::Before:
				m_pRadioButtonBefore->setChecked(true);
				break;
			case LineInterpolationPosition::After:
				m_pRadioButtonAfter->setChecked(true);
				break;
			default:
				m_pRadioButtonMiddle->setChecked(true);
			}
			m_pButtonUpdate->setEnabled(true);
			m_pButtonDelete->setEnabled(true);
		}

		void CDialogBoxLineInterpolationPositionArray::ButtonAdd_OnClick(IControl *sender)
		{
			m_aArray.push_back(m_pRadioButtonBefore->isChecked() ? LineInterpolationPosition::Before : (m_pRadioButtonAfter->isChecked() ? LineInterpolationPosition::After : LineInterpolationPosition::Middle));
			m_pListBoxArray->Add(LineInterpolationPositionToString(m_aArray[m_aArray.size() - 1]));
			m_pListBoxArray->getItem(m_pListBoxArray->getItemCount() - 1)->setSelected(true);
			m_pButtonClear->setEnabled(true);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CDialogBoxLineInterpolationPositionArray::ButtonUpdate_OnClick(IControl *sender)
		{
			int index{ SelectedPointIndex() };
			m_aArray[index] = m_pRadioButtonBefore->isChecked() ? LineInterpolationPosition::Before : (m_pRadioButtonAfter->isChecked() ? LineInterpolationPosition::After : LineInterpolationPosition::Middle);
			cast<standard::IListItemLabel*>(m_pListBoxArray->getItem(index))->setCaption(LineInterpolationPositionToString(m_aArray[index]));
		}

		void CDialogBoxLineInterpolationPositionArray::ButtonDelete_OnClick(IControl *sender)
		{
			int index{ SelectedPointIndex() };
			m_aArray.erase(m_aArray.begin() + index);
			m_pListBoxArray->Delete(index);
			m_pButtonUpdate->setEnabled(false);
			m_pButtonClear->setEnabled(m_aArray.size() > 0);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CDialogBoxLineInterpolationPositionArray::ButtonClear_OnClick(IControl *sender)
		{
			m_aArray.clear();
			m_pListBoxArray->Clear();
			m_pButtonUpdate->setEnabled(false);
			m_pButtonDelete->setEnabled(false);
			m_pButtonClear->setEnabled(false);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CDialogBoxLineInterpolationPositionArray::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxLineInterpolationPositionArray::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion
	}
}