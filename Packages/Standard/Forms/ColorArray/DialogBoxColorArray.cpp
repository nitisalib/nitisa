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
		const String CDialogBoxColorArray::ClassName{ L"DialogBoxColorArray" };

	#pragma region Service
		CDialogBoxColorArray::CDialogBoxColorArrayService::CDialogBoxColorArrayService(CDialogBoxColorArray *control) :
			IDialogBoxColorArrayProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxColorArray::CDialogBoxColorArrayService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxColorArray::CDialogBoxColorArray() :
			IDialogBoxColorArrayProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxColorArrayService(this)),
			m_iMinCount{ 0 },
			m_bColorDialogAdjusted{ false }
		{
			setStaticTabOrder(true);
			setUseMask(false);
			LoadTranslatableTexts();
		}

		CDialogBoxColorArray::CDialogBoxColorArray(IForm *parent) :CDialogBoxColorArray()
		{
			setForm(parent);
		}

		CDialogBoxColorArray::CDialogBoxColorArray(IControl *parent) : CDialogBoxColorArray()
		{
			setParent(parent);
		}

		void CDialogBoxColorArray::LoadTranslatableTexts()
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
		bool CDialogBoxColorArray::hasComponent(IComponent *component)
		{
			if (IDialogBoxColorArrayProto::hasComponent(component))
				return true;
			if (m_pColorDialog1->getDialogBox() && m_pColorDialog1->getDialogBox()->hasComponent(component))
				return true;
			return false;
		}

		ColorArray CDialogBoxColorArray::getValue()
		{
			return m_aArray;
		}

		int CDialogBoxColorArray::getMinCount()
		{
			return m_iMinCount;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxColorArray::setBackgroundColor(const Color &value)
		{
			if (m_pColorDialog1->getDialogBox())
				m_pColorDialog1->getDialogBox()->setBackgroundColor(value);
			return IDialogBoxColorArrayProto::setBackgroundColor(value);
		}

		bool CDialogBoxColorArray::setValue(const ColorArray &value)
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

		bool CDialogBoxColorArray::setMinCount(const int value)
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
		int CDialogBoxColorArray::SelectedPointIndex()
		{
			for (int i = 0; i < m_pListBoxArray->getItemCount(); i++)
				if (m_pListBoxArray->getItem(i)->isSelected())
					return i;
			return -1;
		}
	#pragma endregion

	#pragma region Events
		void CDialogBoxColorArray::FormColorArrayProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
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

		void CDialogBoxColorArray::ColorDialog1_OnApply(IComponent *sender)
		{
			m_pPanelColor->setBackgroundColor(m_pColorDialog1->getColor());
		}

		void CDialogBoxColorArray::ListBoxArray_OnSelect(IControl *sender, IListItem *item)
		{
			int index{ SelectedPointIndex() };
			for (int i = 0; i < m_pColorListBox->getItemCount(); i++)
				m_pColorListBox->getItem(i)->setSelected(cast<IListItemColor*>(m_pColorListBox->getItem(i))->getColor() == m_aArray[index]);
			m_pPanelColor->setBackgroundColor(m_aArray[index]);
			m_pButtonUpdate->setEnabled(true);
			m_pButtonDelete->setEnabled(true);
		}

		void CDialogBoxColorArray::ButtonAdd_OnClick(IControl *sender)
		{
			m_aArray.push_back(m_pPanelColor->getBackgroundColor());
			m_pListBoxArray->Add(ToString(m_pPanelColor->getBackgroundColor()));
			m_pListBoxArray->getItem(m_pListBoxArray->getItemCount() - 1)->setSelected(true);
			m_pButtonClear->setEnabled(true);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CDialogBoxColorArray::ButtonUpdate_OnClick(IControl *sender)
		{
			int index{ SelectedPointIndex() };
			m_aArray[index] = m_pPanelColor->getBackgroundColor();
			cast<IListItemLabel*>(m_pListBoxArray->getItem(index))->setCaption(ToString(m_pPanelColor->getBackgroundColor()));
		}

		void CDialogBoxColorArray::ButtonDelete_OnClick(IControl *sender)
		{
			int index{ SelectedPointIndex() };
			m_aArray.erase(m_aArray.begin() + index);
			m_pListBoxArray->Delete(index);
			m_pButtonUpdate->setEnabled(false);
			m_pButtonClear->setEnabled(m_aArray.size() > 0);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CDialogBoxColorArray::ButtonClear_OnClick(IControl *sender)
		{
			m_aArray.clear();
			m_pListBoxArray->Clear();
			m_pButtonUpdate->setEnabled(false);
			m_pButtonDelete->setEnabled(false);
			m_pButtonClear->setEnabled(false);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CDialogBoxColorArray::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxColorArray::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}

		void CDialogBoxColorArray::ColorListBox_OnSelect(IControl *sender, IListItem *item)
		{
			m_pPanelColor->setBackgroundColor(cast<IListItemColor*>(item)->getColor());
		}

		void CDialogBoxColorArray::PanelColor_OnLeftMouseButtonDown(IControl *sender, const MessageMouse &m, bool &processed)
		{
			m_pColorDialog1->setColor(m_pPanelColor->getBackgroundColor());
			m_pColorDialog1->Execute();
			if (!m_bColorDialogAdjusted)
			{
				m_pColorDialog1->getDialogBox()->setBackgroundColor(getBackgroundColor());
				m_pColorDialog1->getDialogBox()->AutoResize(true);
				m_bColorDialogAdjusted = true;
			}
		}
	#pragma endregion
	}
}