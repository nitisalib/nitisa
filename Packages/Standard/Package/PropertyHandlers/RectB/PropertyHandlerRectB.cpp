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
		CPropertyHandlerRectB::CPropertyHandlerRectB(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerRectB),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerRectB::isEditable(IProperty *property)
		{
			return cast<IPropertyRectB*>(property) || cast<IPropertyRectBState*>(property);
		}

		IProperty *CPropertyHandlerRectB::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerRectB::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerRectB::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyRectBState *p{ cast<IPropertyRectBState*>(m_pProperty) };
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
					IPropertyRectB *p{ cast<IPropertyRectB*>(m_pProperty) };
					IPropertyRectBState *ps{ cast<IPropertyRectBState*>(m_pProperty) };
					if (ps)
						setDialogData(ps->getValue(m_sState));
					else
						setDialogData(p->getValue());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerRectB::setPropertyState(const String &value)
		{
			IPropertyRectBState *p{ cast<IPropertyRectBState*>(m_pProperty) };
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
					setDialogData(p->getValue(m_sState));
					return true;
				}
			}
			return false;
		}

		IFormRectB *CPropertyHandlerRectB::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormRectB::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormRectB*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxRectB *CPropertyHandlerRectB::getDialogBox()
		{
			CDialogBoxRectB *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxRectB*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxRectB(getControl()->getForm());
		}

		void CPropertyHandlerRectB::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxRectB *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyRectB *p{ cast<IPropertyRectB*>(m_pProperty) };
					IPropertyRectBState *ps{ cast<IPropertyRectBState*>(m_pProperty) };
					if (ps)
						dlg->setValue(ps->getValue(m_sState));
					else
						dlg->setValue(p->getValue());
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerRectB *handler{ (CPropertyHandlerRectB*)(void*)sender->Tag };
							CDialogBoxRectB *dlg{ cast<CDialogBoxRectB*>(sender) };
							IPropertyRectB *p{ cast<IPropertyRectB*>(handler->m_pProperty) };
							IPropertyRectBState *ps{ cast<IPropertyRectBState*>(handler->m_pProperty) };
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
				IFormRectB *form{ getForm() };
				if (form)
				{
					IPropertyRectBState *ps{ cast<IPropertyRectBState*>(m_pProperty) };
					if (ps)
						form->setValue(ps->getValue(m_sState));
					else
						form->setValue(cast<IPropertyRectB*>(m_pProperty)->getValue());
					cast<IForm*>(form)->OnSetFocus = [](IForm *sender) {
						sender->OnSetFocus = nullptr;
						cast<IFormRectB*>(sender)->ActivateFirstEnabledInput();
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
							IPropertyRectB *p{ cast<IPropertyRectB*>(m_pProperty) };
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

		void CPropertyHandlerRectB::setDialogData(const RectB &value)
		{
			IFormRectB *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
				form->setValue(value);
		}
	}
}