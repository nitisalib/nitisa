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
		const String CFormForexChartData::ClassName{ L"FormForexChartData" };
		CFormForexChartData *CFormForexChartData::m_pInstance{ nullptr };

	#pragma region Service
		CFormForexChartData::CFormForexChartDataService::CFormForexChartDataService(CFormForexChartData *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormForexChartData::CFormForexChartDataService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormForexChartData::CFormForexChartData(IWindow *window, IRenderer *renderer) :
			IFormForexChartDataProto(window, renderer, ClassName),
			m_pData{ nullptr },
			m_pListener{ nullptr }
		{
			setService(new CFormForexChartDataService(this), true);
			if (!m_pInstance)
				m_pInstance = this;
			LoadTranslatableTexts();
		}

		CFormForexChartData::~CFormForexChartData()
		{
			if (m_pInstance == this)
				m_pInstance = nullptr;
		}

		void CFormForexChartData::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Manage Forex Data"));
			m_pButtonAdd->setCaption(Application->Translate->t(ClassName, L"Add"));
			m_pButtonDelete->setCaption(Application->Translate->t(ClassName, L"Delete"));
			m_pButtonUpdate->setCaption(Application->Translate->t(ClassName, L"Update"));
			m_pButtonClear->setCaption(Application->Translate->t(ClassName, L"Clear"));
			m_pLabel1->setCaption(Application->Translate->t(ClassName, L"Open:"));
			m_pLabel2->setCaption(Application->Translate->t(ClassName, L"Close:"));
			m_pLabel3->setCaption(Application->Translate->t(ClassName, L"Min:"));
			m_pLabel4->setCaption(Application->Translate->t(ClassName, L"Max:"));
			m_pLabel5->setCaption(Application->Translate->t(ClassName, L"Date:"));
			m_pLabel6->setCaption(Application->Translate->t(ClassName, L"Time:"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Interface getters
		IForexChart::IForexChartData *CFormForexChartData::getValue()
		{
			return m_pData;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormForexChartData::setValue(IForexChart::IForexChartData *value)
		{
			if (value != m_pData)
			{
				CLockRepaint lock{ this };
				m_pData = value;

				m_pListBoxArray->Clear();
				m_pButtonAdd->setEnabled(m_pData != nullptr);
				m_pButtonUpdate->setEnabled(false);
				m_pButtonDelete->setEnabled(false);
				m_pButtonClear->setEnabled(false);
				m_pButtonOk->setEnabled(m_pData != nullptr);

				if (m_pData && m_pData->getCount() > 0)
				{
					m_pButtonClear->setEnabled(true);
					for (int i = 0; i < m_pData->getCount(); i++)
						m_pListBoxArray->Add(ItemToString(i));
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		CFormForexChartData *CFormForexChartData::getInstance()
		{
			return m_pInstance;
		}
	#pragma endregion

	#pragma region Setters
		void CFormForexChartData::setUpdateListener(IUpdateListener *listener)
		{
			m_pListener = listener;
		}
	#pragma endregion

	#pragma region Helpers
		int CFormForexChartData::SelectedPointIndex()
		{
			for (int i = 0; i < m_pListBoxArray->getItemCount(); i++)
				if (m_pListBoxArray->getItem(i)->isSelected())
					return i;
			return -1;
		}

		String CFormForexChartData::ItemToString(const int index)
		{
			return
				ToString(m_pData->getDateTime(index)) + L" -> " +
				Application->Translate->t(m_sClassName, L"Open:") + L" " + ToFixed(m_pData->getOpen(index), 6) + L", " +
				Application->Translate->t(m_sClassName, L"Close:") + L" " + ToFixed(m_pData->getClose(index), 6) + L", " +
				Application->Translate->t(m_sClassName, L"Min:") + L" " + ToFixed(m_pData->getMin(index), 6) + L", " +
				Application->Translate->t(m_sClassName, L"Max:") + L" " + ToFixed(m_pData->getMax(index), 6);
		}

		bool CFormForexChartData::GetValues(float &open, float &close, float &min, float &max)
		{
			if (!TryStringToFloat(m_pEditOpen->getText(), open))
			{
				Application->Dialogs->Error(L"Floating point value is expected");
				m_pEditOpen->SelectAll();
				m_pEditOpen->setFocus();
				return false;
			}
			if (!TryStringToFloat(m_pEditClose->getText(), close))
			{
				Application->Dialogs->Error(L"Floating point value is expected");
				m_pEditClose->SelectAll();
				m_pEditClose->setFocus();
				return false;
			}
			if (!TryStringToFloat(m_pEditMin->getText(), min))
			{
				Application->Dialogs->Error(L"Floating point value is expected");
				m_pEditMin->SelectAll();
				m_pEditMin->setFocus();
				return false;
			}
			if (!TryStringToFloat(m_pEditMax->getText(), max))
			{
				Application->Dialogs->Error(L"Floating point value is expected");
				m_pEditMax->SelectAll();
				m_pEditMax->setFocus();
				return false;
			}
			if (open <= 0)
			{
				Application->Dialogs->Error(L"Positive value is expected");
				m_pEditOpen->SelectAll();
				m_pEditOpen->setFocus();
				return false;
			}
			if (close <= 0)
			{
				Application->Dialogs->Error(L"Positive value is expected");
				m_pEditClose->SelectAll();
				m_pEditClose->setFocus();
				return false;
			}
			if (min <= 0)
			{
				Application->Dialogs->Error(L"Positive value is expected");
				m_pEditMin->SelectAll();
				m_pEditMin->setFocus();
				return false;
			}
			if (max <= 0)
			{
				Application->Dialogs->Error(L"Positive value is expected");
				m_pEditMax->SelectAll();
				m_pEditMax->setFocus();
				return false;
			}
			if (max < min)
			{
				Application->Dialogs->Error(L"Maximum value should not be less than minimum one");
				m_pEditMax->SelectAll();
				m_pEditMax->setFocus();
				return false;
			}
			if (open < min || open > max)
			{
				Application->Dialogs->Error(L"Open value should be between minimum and maximum values");
				m_pEditOpen->SelectAll();
				m_pEditOpen->setFocus();
				return false;
			}
			if (close < min || close > max)
			{
				Application->Dialogs->Error(L"Close value should be between minimum and maximum values");
				m_pEditClose->SelectAll();
				m_pEditClose->setFocus();
				return false;
			}
			return true;
		}
	#pragma endregion

	#pragma region Events
		void CFormForexChartData::FormForexChartDataProto_OnKeyUp(IForm *sender, const MessageKey &m)
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
				if (ctrl && !shift && !alt && m_pData)
					setModalResult(ModalResult::Ok);
				break;
			default:
				break;
			}
		}

		void CFormForexChartData::ButtonAdd_OnClick(IControl *sender)
		{
			float open, close, min, max;
			if (!GetValues(open, close, min, max))
				return;
			CDateTime dt{ m_pDatePicker->getYear(), m_pDatePicker->getMonth(), m_pDatePicker->getDay(), m_pTimePicker->getHour(), m_pTimePicker->getMinute(), m_pTimePicker->getSecond() };
			m_pData->Add(dt, open, close, min, max);
			m_pListBoxArray->Add(ItemToString(m_pData->getCount() - 1));
			m_pListBoxArray->getItem(m_pListBoxArray->getItemCount() - 1)->setSelected(true);
			m_pButtonClear->setEnabled(true);
			if (m_pListener)
				m_pListener->NotifyOnUpdate();
		}

		void CFormForexChartData::ButtonUpdate_OnClick(IControl *sender)
		{
			float open, close, min, max;
			if (!GetValues(open, close, min, max))
				return;
			CDateTime dt{ m_pDatePicker->getYear(), m_pDatePicker->getMonth(), m_pDatePicker->getDay(), m_pTimePicker->getHour(), m_pTimePicker->getMinute(), m_pTimePicker->getSecond() };
			int index{ SelectedPointIndex() };
			m_pData->setDateTime(index, dt);
			m_pData->setOpen(index, open);
			m_pData->setClose(index, close);
			m_pData->setMin(index, min);
			m_pData->setMax(index, max);
			cast<standard::IListItemLabel*>(m_pListBoxArray->getItem(index))->setCaption(ItemToString(index));
			if (m_pListener)
				m_pListener->NotifyOnUpdate();
		}

		void CFormForexChartData::ButtonDelete_OnClick(IControl *sender)
		{
			int index{ SelectedPointIndex() };
			if (index >= 0)
			{
				m_pData->Delete(index);
				m_pListBoxArray->DeleteItem(index);
				m_pButtonUpdate->setEnabled(false);
				m_pButtonDelete->setEnabled(false);
				m_pButtonClear->setEnabled(m_pData->getCount() > 0);

				if (m_pListener)
					m_pListener->NotifyOnUpdate();
			}
		}

		void CFormForexChartData::ButtonClear_OnClick(IControl *sender)
		{
			m_pData->Clear();

			m_pListBoxArray->Clear();
			m_pButtonUpdate->setEnabled(false);
			m_pButtonDelete->setEnabled(false);
			m_pButtonClear->setEnabled(false);

			if (m_pListener)
				m_pListener->NotifyOnUpdate();
		}

		void CFormForexChartData::ListBoxArray_OnSelect(IControl *sender, IListItem *item)
		{
			int index{ SelectedPointIndex() };
			m_pDatePicker->setYear(m_pData->getDateTime(index).getYear());
			m_pDatePicker->setMonth(m_pData->getDateTime(index).getMonth());
			m_pDatePicker->setDay(m_pData->getDateTime(index).getDay());
			m_pTimePicker->setHour(m_pData->getDateTime(index).getHour());
			m_pTimePicker->setMinute(m_pData->getDateTime(index).getMinute());
			m_pTimePicker->setSecond(m_pData->getDateTime(index).getSecond());
			m_pEditOpen->setText(ToFixed(m_pData->getOpen(index), 6));
			m_pEditClose->setText(ToFixed(m_pData->getClose(index), 6));
			m_pEditMin->setText(ToFixed(m_pData->getMin(index), 6));
			m_pEditMax->setText(ToFixed(m_pData->getMax(index), 6));
			m_pButtonUpdate->setEnabled(true);
			m_pButtonDelete->setEnabled(true);
		}

		void CFormForexChartData::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormForexChartData::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion
	}
}