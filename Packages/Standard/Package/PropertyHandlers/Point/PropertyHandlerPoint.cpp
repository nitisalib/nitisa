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
	namespace standard
	{
		CPropertyHandlerPoint::CPropertyHandlerPoint(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerPoint),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerPoint::isEditable(IProperty *property)
		{
			return cast<IPropertyPoint*>(property) || cast<IPropertyPointState*>(property);
		}

		IProperty *CPropertyHandlerPoint::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerPoint::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerPoint::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyPointState *p{ cast<IPropertyPointState*>(m_pProperty) };
					bool found{ false };
					if (p)
					{
						for (int i = 0; i < p->getStateCount(); i++)
							if (p->getState(i) == m_sState)
							{
								found = true;
								break;
							}
					}
					if (!found)
						m_sState.clear();
				}
				if (m_pProperty)
				{
					IPropertyPoint *p{ cast<IPropertyPoint*>(m_pProperty) };
					IPropertyPointState *ps{ cast<IPropertyPointState*>(m_pProperty) };
					if (ps)
						setDialogData(ps->getValue(m_sState), ps->hasMin(), ps->hasMax(), ps->getMin(), ps->getMax());
					else
						setDialogData(p->getValue(), p->hasMin(), p->hasMax(), p->getMin(), p->getMax());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerPoint::setPropertyState(const String &value)
		{
			IPropertyPointState *p{ cast<IPropertyPointState*>(m_pProperty) };
			if (p)
			{
				bool found{ false };
				for (int i = 0; i < p->getStateCount(); i++)
					if (p->getState(i) == value)
					{
						found = true;
						break;
					}
				if (found && value != m_sState)
				{
					m_sState = value;
					setDialogData(p->getValue(m_sState), p->hasMin(), p->hasMax(), p->getMin(), p->getMax());
					return true;
				}
			}
			return false;
		}

		IFormPoint *CPropertyHandlerPoint::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormPoint::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormPoint*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxPoint *CPropertyHandlerPoint::getDialogBox()
		{
			CDialogBoxPoint *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxPoint*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxPoint(getControl()->getForm());
		}

		void CPropertyHandlerPoint::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxPoint *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyPoint *p{ cast<IPropertyPoint*>(m_pProperty) };
					IPropertyPointState *ps{ cast<IPropertyPointState*>(m_pProperty) };
					if (ps)
						dlg->setValue(ps->getValue(m_sState));
					else
						dlg->setValue(p->getValue());
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerPoint *handler{ (CPropertyHandlerPoint*)(void*)sender->Tag };
							CDialogBoxPoint *dlg{ cast<CDialogBoxPoint*>(sender) };
							IPropertyPoint *p{ cast<IPropertyPoint*>(handler->m_pProperty) };
							IPropertyPointState *ps{ cast<IPropertyPointState*>(handler->m_pProperty) };
							if (ps)
							{
								ps->setValue(handler->m_sState, dlg->getValue());
								if (handler->getListener())
									cast<IPropertyHandlerListener*>(handler->getListener())->NotifyOnPropertyChange(handler, handler->m_pProperty);
							}
							else
							{
								p->setValue(dlg->getValue());
								if (handler->getListener())
									cast<IPropertyHandlerListener*>(handler->getListener())->NotifyOnPropertyChange(handler, handler->m_pProperty);
							}
						}
					};
					dlg->ShowModal();
					dlg->ActivateFirstEnabledInput();
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
				IFormPoint *form{ getForm() };
				if (form)
				{
					IPropertyPointState *ps{ cast<IPropertyPointState*>(m_pProperty) };
					if (ps)
						form->setValue(ps->getValue(m_sState));
					else
						form->setValue(cast<IPropertyPoint*>(m_pProperty)->getValue());
					cast<IForm*>(form)->OnSetFocus = [](IForm *sender) {
						sender->OnSetFocus = nullptr;
						cast<IFormPoint*>(sender)->ActivateFirstEnabledInput();
					};
					if (cast<IForm*>(form)->ShowModal() == ModalResult::Ok)
					{
						if (ps)
						{
							ps->setValue(m_sState, form->getValue());
							if (getListener())
								cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
						}
						else
						{
							IPropertyPoint *p{ cast<IPropertyPoint*>(m_pProperty) };
							if (p)
							{
								p->setValue(form->getValue());
								if (getListener())
									cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
							}
						}
					}
				}
			}
		}

		void CPropertyHandlerPoint::setDialogData(const Point &value, const bool has_min, const bool has_max, const int min, const int max)
		{
			IFormPoint *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
			{
				form->setValue(value);
				form->setMin(min);
				form->setMax(max);
				form->setHasMin(has_min);
				form->setHasMax(has_max);
			}
		}
	}
}