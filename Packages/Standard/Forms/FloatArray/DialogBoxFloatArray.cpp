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
		const String CDialogBoxFloatArray::ClassName{ L"DialogBoxFloatArray" };

	#pragma region Service
		CDialogBoxFloatArray::CDialogBoxFloatArrayService::CDialogBoxFloatArrayService(CDialogBoxFloatArray *control) :
			IDialogBoxFloatArrayProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxFloatArray::CDialogBoxFloatArrayService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxFloatArray::CDialogBoxFloatArray() :
			IDialogBoxFloatArrayProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxFloatArrayService(this)),
			m_iMinCount{ 0 },
			m_bHasMin{ false },
			m_bHasMax{ false },
			m_fMin{ 0 },
			m_fMax{ 0 }
		{
			setStaticTabOrder(true);
			setUseMask(false);
			LoadTranslatableTexts();
		}

		CDialogBoxFloatArray::CDialogBoxFloatArray(IForm *parent) :CDialogBoxFloatArray()
		{
			setForm(parent);
		}

		CDialogBoxFloatArray::CDialogBoxFloatArray(IControl *parent) : CDialogBoxFloatArray()
		{
			setParent(parent);
		}

		void CDialogBoxFloatArray::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Manage float-array"));
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
		FloatArray CDialogBoxFloatArray::getValue()
		{
			return m_aArray;
		}

		int CDialogBoxFloatArray::getMinCount()
		{
			return m_iMinCount;
		}

		bool CDialogBoxFloatArray::hasMin()
		{
			return m_bHasMin;
		}

		bool CDialogBoxFloatArray::hasMax()
		{
			return m_bHasMax;
		}

		float CDialogBoxFloatArray::getMin()
		{
			return m_fMin;
		}

		float CDialogBoxFloatArray::getMax()
		{
			return m_fMax;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxFloatArray::setValue(const FloatArray &value)
		{
			bool equal{ value.size() == m_aArray.size() };
			if (equal)
			{
				for (size_t i = 0; i < value.size(); i++)
					if (ntl::IsNotEqual<float>(value[i], m_aArray[i]))
					{
						equal = false;
						break;
					}
				if (equal)
					return false;
			}
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

		bool CDialogBoxFloatArray::setMinCount(const int value)
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

		bool CDialogBoxFloatArray::setHasMin(const bool value)
		{
			if (value != m_bHasMin)
			{
				m_bHasMin = value;
				m_pLabelMinValue->setCaption(m_bHasMin ? ToString(m_fMin) : L"");
				return true;
			}
			return false;
		}

		bool CDialogBoxFloatArray::setHasMax(const bool value)
		{
			if (value != m_bHasMax)
			{
				m_bHasMax = value;
				m_pLabelMaxValue->setCaption(m_bHasMax ? ToString(m_fMax) : L"");
				return true;
			}
			return false;
		}

		bool CDialogBoxFloatArray::setMin(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMin))
			{
				m_fMin = value;
				if (m_bHasMin)
					m_pLabelMinValue->setCaption(ToString(m_fMin));
				return true;
			}
			return false;
		}

		bool CDialogBoxFloatArray::setMax(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMax))
			{
				m_fMax = value;
				if (m_bHasMax)
					m_pLabelMaxValue->setCaption(ToString(m_fMax));
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		int CDialogBoxFloatArray::SelectedPointIndex()
		{
			for (int i = 0; i < m_pListBoxArray->getItemCount(); i++)
				if (m_pListBoxArray->getItem(i)->isSelected())
					return i;
			return -1;
		}
	#pragma endregion

	#pragma region Events
		void CDialogBoxFloatArray::FormFloatArrayProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
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

		void CDialogBoxFloatArray::ListBoxArray_OnSelect(IControl *sender, IListItem *item)
		{
			int index{ SelectedPointIndex() };
			m_pEditValue->setText(ToString(m_aArray[index]));
			m_pButtonUpdate->setEnabled(true);
			m_pButtonDelete->setEnabled(true);
		}

		void CDialogBoxFloatArray::ButtonAdd_OnClick(IControl *sender)
		{
			float v;
			if (!TryStringToFloat(m_pEditValue->getText(), v))
			{
				Application->Dialogs->Error(Application->Translate->t(m_sClassName, L"Floating point value expected"));
				m_pEditValue->SelectAll();
				m_pEditValue->setFocus();
				return;
			}
			if (m_bHasMin && ntl::IsLess<float>(v, m_fMin))
			{
				Application->Dialogs->Error(Application->Translate->t(m_sClassName, L"Value is too small"));
				m_pEditValue->SelectAll();
				m_pEditValue->setFocus();
				return;
			}
			if (m_bHasMax && ntl::IsGreater<float>(v, m_fMax))
			{
				Application->Dialogs->Error(Application->Translate->t(m_sClassName, L"Value is too big"));
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

		void CDialogBoxFloatArray::ButtonUpdate_OnClick(IControl *sender)
		{
			float v;
			if (!TryStringToFloat(m_pEditValue->getText(), v))
			{
				Application->Dialogs->Error(Application->Translate->t(m_sClassName, L"Floating point value expected"));
				m_pEditValue->SelectAll();
				m_pEditValue->setFocus();
				return;
			}
			if (m_bHasMin && ntl::IsLess<float>(v, m_fMin))
			{
				Application->Dialogs->Error(Application->Translate->t(m_sClassName, L"Value is too small"));
				m_pEditValue->SelectAll();
				m_pEditValue->setFocus();
				return;
			}
			if (m_bHasMax && ntl::IsGreater<float>(v, m_fMax))
			{
				Application->Dialogs->Error(Application->Translate->t(m_sClassName, L"Value is too big"));
				m_pEditValue->SelectAll();
				m_pEditValue->setFocus();
				return;
			}
			int index{ SelectedPointIndex() };
			m_aArray[index] = v;
			cast<IListItemLabel*>(m_pListBoxArray->getItem(index))->setCaption(ToString(v));
		}

		void CDialogBoxFloatArray::ButtonDelete_OnClick(IControl *sender)
		{
			int index{ SelectedPointIndex() };
			m_aArray.erase(m_aArray.begin() + index);
			m_pListBoxArray->Delete(index);
			m_pButtonUpdate->setEnabled(false);
			m_pButtonClear->setEnabled(m_aArray.size() > 0);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CDialogBoxFloatArray::ButtonClear_OnClick(IControl *sender)
		{
			m_aArray.clear();
			m_pListBoxArray->Clear();
			m_pButtonUpdate->setEnabled(false);
			m_pButtonDelete->setEnabled(false);
			m_pButtonClear->setEnabled(false);
			m_pButtonOk->setEnabled((int)m_aArray.size() >= m_iMinCount);
		}

		void CDialogBoxFloatArray::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxFloatArray::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion
	}
}