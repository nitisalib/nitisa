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
		const String CFormColorArray::ClassName{ L"FormColorArray" };
		CFormColorArray *CFormColorArray::m_pInstance{ nullptr };

	#pragma region Service
		CFormColorArray::CFormColorArrayService::CFormColorArrayService(CFormColorArray *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormColorArray::CFormColorArrayService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormColorArray::CFormColorArray(IWindow *window, IRenderer *renderer) :
			IFormColorArrayProto(window, renderer, ClassName),
			m_iMinCount{ 0 }
		{
			setService(new CFormColorArrayService(this), true);
			if (!m_pInstance)
				m_pInstance = this;
			LoadTranslatableTexts();
		}

		CFormColorArray::~CFormColorArray()
		{
			if (m_pInstance == this)
				m_pInstance = nullptr;
		}

		void CFormColorArray::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Manage Color-array"));
			m_pButtonAdd->setCaption(Application->Translate->t(ClassName, L"Add"));
			m_pButtonDelete->setCaption(Application->Translate->t(ClassName, L"Delete"));
			m_pButtonUpdate->setCaption(Application->Translate->t(ClassName, L"Update"));
			m_pButtonClear->setCaption(Application->Translate->t(ClassName, L"Clear"));
			m_pLabel1->setCaption(Application->Translate->t(ClassName, L"Min count:"));
			m_pLabel2->setCaption(Application->Translate->t(ClassName, L"Select color:"));
			m_pLabel3->setCaption(Application->Translate->t(ClassName, L"Or choose custom one:"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Interface getters
		ColorArray CFormColorArray::getValue()
		{
			return m_aArray;
		}

		int CFormColorArray::getMinCount()
		{
			return m_iMinCount;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormColorArray::setValue(const ColorArray &value)
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

		bool CFormColorArray::setMinCount(const int value)
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
		CFormColorArray *CFormColorArray::getInstance()
		{
			return m_pInstance;
		}
	#pragma endregion

	#pragma region Helpers
		int CFormColorArray::SelectedPointIndex()
		{
			for (int i = 0; i < m_pListBoxArray->getItemCount(); i++)
				if (m_pListBoxArray->getItem(i)->isSelected())
					return i;
			return -1;
		}
	#pragma endregion

	#pragma region Events
		void CFormColorArray::FormColorArrayProto_OnKeyUp(IForm *sender, const MessageKey &m)
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

		void CFormColorArray::ListBoxArray_OnSelect(IControl *sender, IListItem *item)
		{
			int index{ SelectedPointIndex() };
			for (int i = 0; i < m_pColorListBox->getItemCount(); i++)
				m_pColorListBox->getItem(i)->setSelected(cast<IListItemColor*>(m_pColorListBox->getItem(i))->getColor() == m_aArray[index]);
			m_pPanelColor->setBackgroundColor(m_aArray[index]);
			m_pButtonUpdate->setEnabled(true);
			m_pButtonDelete->setEnabled(true);
		}

		void CFormColorArray::ButtonAdd_OnClick(IControl *sender)
		{
			m_aArray.push_back(m_pPanelColor->getBackgroundColor());
			m_pListBoxArray->Add(ToString(m_pPanelColor->getBackgroundColor()));
			m_pListBoxArray->getItem(m_pListBoxArray->getItemCount() - 1)->setSelected(true);
			m_pButtonClear->setEnabled(true);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CFormColorArray::ButtonUpdate_OnClick(IControl *sender)
		{
			int index{ SelectedPointIndex() };
			m_aArray[index] = m_pPanelColor->getBackgroundColor();
			cast<IListItemLabel*>(m_pListBoxArray->getItem(index))->setCaption(ToString(m_pPanelColor->getBackgroundColor()));
		}

		void CFormColorArray::ButtonDelete_OnClick(IControl *sender)
		{
			int index{ SelectedPointIndex() };
			m_aArray.erase(m_aArray.begin() + index);
			m_pListBoxArray->Delete(index);
			m_pButtonUpdate->setEnabled(false);
			m_pButtonClear->setEnabled(m_aArray.size() > 0);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CFormColorArray::ButtonClear_OnClick(IControl *sender)
		{
			m_aArray.clear();
			m_pListBoxArray->Clear();
			m_pButtonUpdate->setEnabled(false);
			m_pButtonDelete->setEnabled(false);
			m_pButtonClear->setEnabled(false);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CFormColorArray::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormColorArray::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}

		void CFormColorArray::ColorListBox_OnSelect(IControl *sender, IListItem *item)
		{
			m_pPanelColor->setBackgroundColor(cast<IListItemColor*>(item)->getColor());
		}

		void CFormColorArray::PanelColor_OnLeftMouseButtonDown(IControl *sender, const MessageMouse &m, bool &processed)
		{
			m_pColorDialog1->setColor(m_pPanelColor->getBackgroundColor());
			if (m_pColorDialog1->Execute())
				m_pPanelColor->setBackgroundColor(m_pColorDialog1->getColor());
		}
	#pragma endregion
	}
}