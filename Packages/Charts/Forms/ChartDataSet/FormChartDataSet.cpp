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
		const String CFormChartDataSet::ClassName{ L"FormChartDataSet" };
		CFormChartDataSet *CFormChartDataSet::m_pInstance{ nullptr };

	#pragma region Service
		CFormChartDataSet::CFormChartDataSetService::CFormChartDataSetService(CFormChartDataSet *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormChartDataSet::CFormChartDataSetService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormChartDataSet::CFormChartDataSet(IWindow *window, IRenderer *renderer) :
			IFormChartDataSetProto(window, renderer, ClassName),
			m_pDataSet{ nullptr },
			m_pListener{ nullptr }
		{
			setService(new CFormChartDataSetService(this), true);
			if (!m_pInstance)
				m_pInstance = this;
			LoadTranslatableTexts();
		}

		CFormChartDataSet::~CFormChartDataSet()
		{
			if (m_pInstance == this)
				m_pInstance = nullptr;
		}

		void CFormChartDataSet::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Manage Chart Dataset"));
			m_pGroupBox1->setCaption(Application->Translate->t(ClassName, L"Datas"));
			m_pButtonAddData->setCaption(Application->Translate->t(ClassName, L"Add"));
			m_pEditDataName->setPlaceholder(Application->Translate->t(ClassName, L"Data name"));
			m_pButtonDeleteData->setCaption(Application->Translate->t(ClassName, L"Delete"));
			m_pButtonUpdateData->setCaption(Application->Translate->t(ClassName, L"Update"));
			m_pButtonClearDatas->setCaption(Application->Translate->t(ClassName, L"Clear"));
			m_pGroupBox2->setCaption(Application->Translate->t(ClassName, L"Points"));
			m_pLabel1->setCaption(Application->Translate->t(ClassName, L"X:"));
			m_pLabel2->setCaption(Application->Translate->t(ClassName, L"Y:"));
			m_pLabel3->setCaption(Application->Translate->t(ClassName, L"Label:"));
			m_pEditX->setPlaceholder(Application->Translate->t(ClassName, L"X coordinate"));
			m_pEditY->setPlaceholder(Application->Translate->t(ClassName, L"Y coordinate"));
			m_pEditLabel->setPlaceholder(Application->Translate->t(ClassName, L"Point label"));
			m_pButtonAddPoint->setCaption(Application->Translate->t(ClassName, L"Add"));
			m_pButtonUpdatePoint->setCaption(Application->Translate->t(ClassName, L"Update"));
			m_pButtonDeletePoint->setCaption(Application->Translate->t(ClassName, L"Delete"));
			m_pButtonClearPoints->setCaption(Application->Translate->t(ClassName, L"Clear"));
		}
	#pragma endregion

	#pragma region Interface getters
		IChartDataSet *CFormChartDataSet::getValue()
		{
			return m_pDataSet;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormChartDataSet::setValue(IChartDataSet *value)
		{
			if (value != m_pDataSet)
			{
				CLockRepaint lock{ this };
				m_pDataSet = value;

				m_pListBoxDatas->Clear();
				m_pButtonAddData->setEnabled(false);
				m_pButtonUpdateData->setEnabled(false);
				m_pButtonDeleteData->setEnabled(false);
				m_pButtonClearDatas->setEnabled(false);
				m_pEditDataName->setEnabled(false);

				m_pListBoxPoints->Clear();
				m_pButtonAddPoint->setEnabled(false);
				m_pButtonUpdatePoint->setEnabled(false);
				m_pButtonDeletePoint->setEnabled(false);
				m_pButtonClearPoints->setEnabled(false);
				m_pEditX->setEnabled(false);
				m_pEditY->setEnabled(false);
				m_pEditLabel->setEnabled(false);

				if (m_pDataSet)
				{
					m_pButtonAddData->setEnabled(true);
					m_pEditDataName->setEnabled(true);

					for (int i = 0; i < m_pDataSet->getDataCount(); i++)
						m_pListBoxDatas->Add(m_pDataSet->getData(i)->getName());
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		CFormChartDataSet *CFormChartDataSet::getInstance()
		{
			return m_pInstance;
		}
	#pragma endregion

	#pragma region Setters
		void CFormChartDataSet::setUpdateListener(IUpdateListener *listener)
		{
			m_pListener = listener;
		}
	#pragma endregion

	#pragma region Helpers
		int CFormChartDataSet::SelectedDataIndex()
		{
			for (int i = 0; i < m_pListBoxDatas->getItemCount(); i++)
				if (m_pListBoxDatas->getItem(i)->isSelected())
					return i;
			return -1;
		}

		int CFormChartDataSet::SelectedPointIndex()
		{
			for (int i = 0; i < m_pListBoxPoints->getItemCount(); i++)
				if (m_pListBoxPoints->getItem(i)->isSelected())
					return i;
			return -1;
		}
	#pragma endregion

	#pragma region Events
		void CFormChartDataSet::ButtonAddData_OnClick(IControl *sender)
		{
			String name{ Trim(m_pEditDataName->getText()) };
			m_pDataSet->AddData(new CChartData(name));
			m_pListBoxDatas->Add(name);
			m_pListBoxDatas->getItem(m_pListBoxDatas->getItemCount() - 1)->setSelected(true);
			m_pButtonClearDatas->setEnabled(true);
			if (m_pListener)
				m_pListener->NotifyOnUpdate();
		}

		void CFormChartDataSet::ButtonDeleteData_OnClick(IControl *sender)
		{
			int index{ SelectedDataIndex() };
			if (index >= 0)
			{
				m_pDataSet->DeleteData(index);
				m_pListBoxDatas->DeleteItem(index);
				m_pButtonUpdateData->setEnabled(false);
				m_pButtonDeleteData->setEnabled(false);
				if (m_pDataSet->getDataCount() == 0)
					m_pButtonClearDatas->setEnabled(false);
				
				m_pListBoxPoints->Clear();
				m_pButtonAddPoint->setEnabled(false);
				m_pButtonUpdatePoint->setEnabled(false);
				m_pButtonDeletePoint->setEnabled(false);
				m_pButtonClearPoints->setEnabled(false);
				m_pEditX->setEnabled(false);
				m_pEditY->setEnabled(false);
				m_pEditLabel->setEnabled(false);

				if (m_pListener)
					m_pListener->NotifyOnUpdate();
			}
		}

		void CFormChartDataSet::ListBoxDatas_OnSelect(IControl *sender, IListItem *item)
		{
			int index{ SelectedDataIndex() };
			m_pEditDataName->setText(cast<standard::IListItemLabel*>(item)->getCaption());
			m_pButtonUpdateData->setEnabled(true);
			m_pButtonDeleteData->setEnabled(true);

			m_pListBoxPoints->Clear();
			for (int i = 0; i < m_pDataSet->getData(index)->getCount(); i++)
				m_pListBoxPoints->Add(L"X: " + ToFixed(m_pDataSet->getData(index)->getX(i), 6) + L", Y: " + ToFixed(m_pDataSet->getData(index)->getY(i), 6) + L", Label: " + m_pDataSet->getData(index)->getLabel(i));
			m_pButtonAddPoint->setEnabled(true);
			m_pButtonClearPoints->setEnabled(m_pDataSet->getData(index)->getCount() > 0);
			m_pEditX->setEnabled(true);
			m_pEditY->setEnabled(true);
			m_pEditLabel->setEnabled(true);
		}

		void CFormChartDataSet::ListBoxDatas_OnDeselect(IControl *sender, IListItem *item)
		{

		}

		void CFormChartDataSet::ButtonUpdateData_OnClick(IControl *sender)
		{
			int index{ SelectedDataIndex() };
			String name{ Trim(m_pEditDataName->getText()) };
			m_pDataSet->getData(index)->setName(name);
			cast<standard::IListItemLabel*>(m_pListBoxDatas->getItem(index))->setCaption(name);
			if (m_pListener)
				m_pListener->NotifyOnUpdate();
		}

		void CFormChartDataSet::ButtonClearDatas_OnClick(IControl *sender)
		{
			m_pDataSet->DeleteDatas();

			m_pListBoxDatas->Clear();
			m_pButtonUpdateData->setEnabled(false);
			m_pButtonDeleteData->setEnabled(false);
			m_pButtonClearDatas->setEnabled(false);

			m_pListBoxPoints->Clear();
			m_pButtonAddPoint->setEnabled(false);
			m_pButtonUpdatePoint->setEnabled(false);
			m_pButtonDeletePoint->setEnabled(false);
			m_pButtonClearPoints->setEnabled(false);
			m_pEditX->setEnabled(false);
			m_pEditY->setEnabled(false);
			m_pEditLabel->setEnabled(false);

			if (m_pListener)
				m_pListener->NotifyOnUpdate();
		}

		void CFormChartDataSet::ListBoxPoints_OnSelect(IControl *sender, IListItem *item)
		{
			int data{ SelectedDataIndex() }, point{ SelectedPointIndex() };
			m_pEditX->setText(ToString(m_pDataSet->getData(data)->getX(point)));
			m_pEditY->setText(ToString(m_pDataSet->getData(data)->getY(point)));
			m_pEditLabel->setText(m_pDataSet->getData(data)->getLabel(point));
			m_pButtonUpdatePoint->setEnabled(true);
			m_pButtonDeletePoint->setEnabled(true);
		}

		void CFormChartDataSet::ListBoxPoints_OnDeselect(IControl *sender, IListItem *item)
		{

		}

		void CFormChartDataSet::ButtonAddPoint_OnClick(IControl *sender)
		{
			float x, y;
			if (!TryStringToFloat(m_pEditX->getText(), x))
			{
				Application->Dialogs->Error(Application->Translate->t(m_sClassName, L"Floating point value expected"));
				m_pEditX->SelectAll();
				m_pEditX->setFocus();
				return;
			}
			if (!TryStringToFloat(m_pEditY->getText(), y))
			{
				Application->Dialogs->Error(Application->Translate->t(m_sClassName, L"Floating point value expected"));
				m_pEditY->SelectAll();
				m_pEditY->setFocus();
				return;
			}
			int index{ SelectedDataIndex() };
			m_pDataSet->getData(index)->AddPoint(x, y, m_pEditLabel->getText());
			m_pListBoxPoints->Add(L"X: " + ToFixed(x, 6) + L", Y: " + ToFixed(y, 6) + L", Label: " + m_pEditLabel->getText());
			m_pListBoxPoints->getItem(m_pListBoxPoints->getItemCount() - 1)->setSelected(true);
			m_pButtonClearPoints->setEnabled(true);
			if (m_pListener)
				m_pListener->NotifyOnUpdate();
		}

		void CFormChartDataSet::ButtonUpdatePoint_OnClick(IControl *sender)
		{
			float x, y;
			if (!TryStringToFloat(m_pEditX->getText(), x))
			{
				Application->Dialogs->Error(Application->Translate->t(m_sClassName, L"Floating point value expected"));
				m_pEditX->SelectAll();
				m_pEditX->setFocus();
				return;
			}
			if (!TryStringToFloat(m_pEditY->getText(), y))
			{
				Application->Dialogs->Error(Application->Translate->t(m_sClassName, L"Floating point value expected"));
				m_pEditY->SelectAll();
				m_pEditY->setFocus();
				return;
			}
			int data{ SelectedDataIndex() }, point{ SelectedPointIndex() };
			m_pDataSet->getData(data)->setX(point, x);
			m_pDataSet->getData(data)->setY(point, y);
			m_pDataSet->getData(data)->setLabel(point, m_pEditLabel->getText());
			cast<standard::IListItemLabel*>(m_pListBoxPoints->getItem(point))->setCaption(L"X: " + ToFixed(x, 6) + L", Y: " + ToFixed(y, 6) + L", Label: " + m_pEditLabel->getText());
			if (m_pListener)
				m_pListener->NotifyOnUpdate();
		}

		void CFormChartDataSet::ButtonDeletePoint_OnClick(IControl *sender)
		{
			int data{ SelectedDataIndex() }, point{ SelectedPointIndex() };
			m_pDataSet->getData(data)->DeletePoint(point);
			m_pListBoxPoints->DeleteItem(point);
			m_pButtonUpdatePoint->setEnabled(false);
			m_pButtonDeletePoint->setEnabled(false);
			m_pButtonClearPoints->setEnabled(m_pListBoxPoints->getItemCount() > 0);
			if (m_pListener)
				m_pListener->NotifyOnUpdate();
		}

		void CFormChartDataSet::ButtonClearPoints_OnClick(IControl *sender)
		{
			int index{ SelectedDataIndex() };
			m_pDataSet->getData(index)->DeletePoints();
			m_pListBoxPoints->Clear();
			m_pButtonUpdatePoint->setEnabled(false);
			m_pButtonDeletePoint->setEnabled(false);
			m_pButtonClearPoints->setEnabled(false);
			if (m_pListener)
				m_pListener->NotifyOnUpdate();
		}
	#pragma endregion
	}
}