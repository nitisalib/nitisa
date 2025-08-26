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
		CPropertyHandlerChartDataSet::CPropertyHandlerChartDataSet(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerChartDataSet),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerChartDataSet::isEditable(IProperty *property)
		{
			return cast<IPropertyChartDataSet*>(property);
		}

		IProperty *CPropertyHandlerChartDataSet::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerChartDataSet::getPropertyState()
		{
			return L"";
		}

		bool CPropertyHandlerChartDataSet::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (m_pProperty)
				{
					IPropertyChartDataSet *p{ cast<IPropertyChartDataSet*>(m_pProperty) };
					setDialogValue(p->getValue());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerChartDataSet::setPropertyState(const String &value)
		{
			return false;
		}

		IFormChartDataSet *CPropertyHandlerChartDataSet::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormChartDataSet::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormChartDataSet*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxChartDataSet *CPropertyHandlerChartDataSet::getDialogBox()
		{
			CDialogBoxChartDataSet *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxChartDataSet*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxChartDataSet(getControl()->getForm());
		}

		void CPropertyHandlerChartDataSet::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxChartDataSet *dlg{ getDialogBox() };
				if (dlg)
				{
					dlg->setUpdateListener(this);
					dlg->setValue(cast<IPropertyChartDataSet*>(m_pProperty)->getValue());
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
				IFormChartDataSet *form{ getForm() };
				if (form)
				{
					form->setUpdateListener(this);
					form->setValue(cast<IPropertyChartDataSet*>(m_pProperty)->getValue());
					// Show in task to allow online updates
					getControl()->getForm()->AddTask(CreateTask([form]() {
						cast<IForm*>(form)->ShowModal();
					}));
				}
			}
		}

		void CPropertyHandlerChartDataSet::setDialogValue(IChartDataSet *value)
		{
			IFormChartDataSet *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
			{
				form->setUpdateListener(this);
				form->setValue(value);
			}
		}

		void CPropertyHandlerChartDataSet::NotifyOnUpdate()
		{
			IFormChartDataSet *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
			{
				IPropertyChartDataSet *p{ cast<IPropertyChartDataSet*>(m_pProperty) };
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