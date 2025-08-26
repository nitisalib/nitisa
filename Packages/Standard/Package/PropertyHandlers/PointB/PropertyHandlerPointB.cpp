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
		CPropertyHandlerPointB::CPropertyHandlerPointB(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerPointB),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerPointB::isEditable(IProperty *property)
		{
			return cast<IPropertyPointB*>(property) || cast<IPropertyPointBState*>(property);
		}

		IProperty *CPropertyHandlerPointB::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerPointB::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerPointB::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyPointBState *p{ cast<IPropertyPointBState*>(m_pProperty) };
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
					IPropertyPointB *p{ cast<IPropertyPointB*>(m_pProperty) };
					IPropertyPointBState *ps{ cast<IPropertyPointBState*>(m_pProperty) };
					setDialogPoint(ps ? ps->getValue(m_sState) : p->getValue());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerPointB::setPropertyState(const String &value)
		{
			IPropertyPointBState *p{ cast<IPropertyPointBState*>(m_pProperty) };
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
					setDialogPoint(p->getValue(m_sState));
					return true;
				}
			}
			return false;
		}

		IFormPointB *CPropertyHandlerPointB::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormPointB::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormPointB*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxPointB *CPropertyHandlerPointB::getDialogBox()
		{
			CDialogBoxPointB *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxPointB*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxPointB(getControl()->getForm());
		}

		void CPropertyHandlerPointB::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxPointB *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyPointB *p{ cast<IPropertyPointB*>(m_pProperty) };
					IPropertyPointBState *ps{ cast<IPropertyPointBState*>(m_pProperty) };
					if (ps)
						dlg->setValue(ps->getValue(m_sState));
					else
						dlg->setValue(p->getValue());
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerPointB *handler{ (CPropertyHandlerPointB*)(void*)sender->Tag };
							CDialogBoxPointB *dlg{ cast<CDialogBoxPointB*>(sender) };
							IPropertyPointB *p{ cast<IPropertyPointB*>(handler->m_pProperty) };
							IPropertyPointBState *ps{ cast<IPropertyPointBState*>(handler->m_pProperty) };
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
				IFormPointB *form{ getForm() };
				if (form)
				{
					IPropertyPointBState *ps{ cast<IPropertyPointBState*>(m_pProperty) };
					if (ps)
						form->setValue(ps->getValue(m_sState));
					else
						form->setValue(cast<IPropertyPointB*>(m_pProperty)->getValue());
					cast<IForm*>(form)->OnSetFocus = [](IForm *sender) {
						sender->OnSetFocus = nullptr;
						cast<IFormPointB*>(sender)->ActivateFirstEnabledInput();
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
							IPropertyPointB *p{ cast<IPropertyPointB*>(m_pProperty) };
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

		void CPropertyHandlerPointB::setDialogPoint(const PointB &value)
		{
			IFormPointB *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
				form->setValue(value);
		}
	}
}