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
		const String CFormBoolArray::ClassName{ L"FormBoolArray" };
		CFormBoolArray *CFormBoolArray::m_pInstance{ nullptr };

	#pragma region Service
		CFormBoolArray::CFormBoolArrayService::CFormBoolArrayService(CFormBoolArray *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormBoolArray::CFormBoolArrayService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormBoolArray::CFormBoolArray(IWindow *window, IRenderer *renderer) :
			IFormBoolArrayProto(window, renderer, ClassName),
			m_iMinCount{ 0 }
		{
			setService(new CFormBoolArrayService(this), true);
			if (!m_pInstance)
				m_pInstance = this;
			LoadTranslatableTexts();
		}

		CFormBoolArray::~CFormBoolArray()
		{
			if (m_pInstance == this)
				m_pInstance = nullptr;
		}

		void CFormBoolArray::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Manage bool-array"));
			m_pButtonAdd->setCaption(Application->Translate->t(ClassName, L"Add"));
			m_pButtonDelete->setCaption(Application->Translate->t(ClassName, L"Delete"));
			m_pButtonUpdate->setCaption(Application->Translate->t(ClassName, L"Update"));
			m_pButtonClear->setCaption(Application->Translate->t(ClassName, L"Clear"));
			m_pLabel1->setCaption(Application->Translate->t(ClassName, L"Min count:"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Interface getters
		BoolArray CFormBoolArray::getValue()
		{
			return m_aArray;
		}

		int CFormBoolArray::getMinCount()
		{
			return m_iMinCount;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormBoolArray::setValue(const BoolArray &value)
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
						m_pListBoxArray->Add(v ? L"True" : L"False");
				}
				return true;
			}
			return false;
		}

		bool CFormBoolArray::setMinCount(const int value)
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

	#pragma region Getters
		CFormBoolArray *CFormBoolArray::getInstance()
		{
			return m_pInstance;
		}
	#pragma endregion

		#pragma region Helpers
		int CFormBoolArray::SelectedPointIndex()
		{
			for (int i = 0; i < m_pListBoxArray->getItemCount(); i++)
				if (m_pListBoxArray->getItem(i)->isSelected())
					return i;
			return -1;
		}
	#pragma endregion

	#pragma region Events
		void CFormBoolArray::FormBoolArrayProto_OnKeyUp(IForm *sender, const MessageKey &m)
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

		void CFormBoolArray::ListBoxArray_OnSelect(IControl *sender, IListItem *item)
		{
			int index{ SelectedPointIndex() };
			m_aArray[index] ? m_pRadioButtonTrue->setChecked(true) : m_pRadioButtonFalse->setChecked(true);
			m_pButtonUpdate->setEnabled(true);
			m_pButtonDelete->setEnabled(true);
		}

		void CFormBoolArray::ButtonAdd_OnClick(IControl *sender)
		{
			m_aArray.push_back(m_pRadioButtonTrue->isChecked());
			m_pListBoxArray->Add(m_pRadioButtonTrue->isChecked() ? L"True" : L"False");
			m_pListBoxArray->getItem(m_pListBoxArray->getItemCount() - 1)->setSelected(true);
			m_pButtonClear->setEnabled(true);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CFormBoolArray::ButtonUpdate_OnClick(IControl *sender)
		{
			int index{ SelectedPointIndex() };
			m_aArray[index] = m_pRadioButtonTrue->isChecked();
			cast<IListItemLabel*>(m_pListBoxArray->getItem(index))->setCaption(m_pRadioButtonTrue->isChecked() ? L"True" : L"False");
		}

		void CFormBoolArray::ButtonDelete_OnClick(IControl *sender)
		{
			int index{ SelectedPointIndex() };
			m_aArray.erase(m_aArray.begin() + index);
			m_pListBoxArray->Delete(index);
			m_pButtonUpdate->setEnabled(false);
			m_pButtonClear->setEnabled(m_aArray.size() > 0);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CFormBoolArray::ButtonClear_OnClick(IControl *sender)
		{
			m_aArray.clear();
			m_pListBoxArray->Clear();
			m_pButtonUpdate->setEnabled(false);
			m_pButtonDelete->setEnabled(false);
			m_pButtonClear->setEnabled(false);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CFormBoolArray::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormBoolArray::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion
	}
}