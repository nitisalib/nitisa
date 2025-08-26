// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
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
		CPropertyHandlerForexChartData::CPropertyHandlerForexChartData(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerForexChartData),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerForexChartData::isEditable(IProperty *property)
		{
			return cast<IPropertyForexChartData*>(property);
		}

		IProperty *CPropertyHandlerForexChartData::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerForexChartData::getPropertyState()
		{
			return L"";
		}

		bool CPropertyHandlerForexChartData::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (m_pProperty)
				{
					IPropertyForexChartData *p{ cast<IPropertyForexChartData*>(m_pProperty) };
					setDialogValue(p->getValue());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerForexChartData::setPropertyState(const String &value)
		{
			return false;
		}

		IFormForexChartData *CPropertyHandlerForexChartData::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormForexChartData::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormForexChartData*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxForexChartData *CPropertyHandlerForexChartData::getDialogBox()
		{
			CDialogBoxForexChartData *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxForexChartData*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxForexChartData(getControl()->getForm());
		}

		void CPropertyHandlerForexChartData::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxForexChartData *dlg{ getDialogBox() };
				if (dlg)
				{
					dlg->setUpdateListener(this);
					dlg->setValue(cast<IPropertyForexChartData*>(m_pProperty)->getValue());
					dlg->ShowModal();
					if (!m_bDialogBoxAdjusted)
					{
						dlg->setBackgroundColor(Color{ 240, 240, 240, 255 });
						dlg->AutoResize(true);
						m_bDialogBoxAdjusted = true;
					}
				}
			}
			else
			{
				IFormForexChartData *form{ getForm() };
				if (form)
				{
					form->setUpdateListener(this);
					form->setValue(cast<IPropertyForexChartData*>(m_pProperty)->getValue());
					// Show in task to allow online updates
					getControl()->getForm()->AddTask(CreateTask([form]() {
						cast<IForm*>(form)->ShowModal();
					}));

				}
			}
		}

		void CPropertyHandlerForexChartData::setDialogValue(IForexChart::IForexChartData *value)
		{
			IFormForexChartData *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
			{
				form->setUpdateListener(this);
				form->setValue(value);
			}
		}

		void CPropertyHandlerForexChartData::NotifyOnUpdate()
		{
			IFormForexChartData *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
			{
				IPropertyForexChartData *p{ cast<IPropertyForexChartData*>(m_pProperty) };
				if (p)
				{
					p->Update();
					if (getListener())
						cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
				}
			}
		}
	}
}