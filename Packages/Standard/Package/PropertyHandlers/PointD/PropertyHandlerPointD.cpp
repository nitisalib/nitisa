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
		CPropertyHandlerPointD::CPropertyHandlerPointD(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerPointD),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerPointD::isEditable(IProperty *property)
		{
			return cast<IPropertyPointD*>(property) || cast<IPropertyPointDState*>(property);
		}

		IProperty *CPropertyHandlerPointD::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerPointD::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerPointD::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyPointDState *p{ cast<IPropertyPointDState*>(m_pProperty) };
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
					IPropertyPointD *p{ cast<IPropertyPointD*>(m_pProperty) };
					IPropertyPointDState *ps{ cast<IPropertyPointDState*>(m_pProperty) };
					if (ps)
						setDialogData(ps->getValue(m_sState), ps->hasMin(), ps->hasMax(), ps->getMin(), ps->getMax());
					else
						setDialogData(p->getValue(), p->hasMin(), p->hasMax(), p->getMin(), p->getMax());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerPointD::setPropertyState(const String &value)
		{
			IPropertyPointDState *p{ cast<IPropertyPointDState*>(m_pProperty) };
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

		IFormPointD *CPropertyHandlerPointD::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormPointD::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormPointD*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxPointD *CPropertyHandlerPointD::getDialogBox()
		{
			CDialogBoxPointD *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxPointD*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxPointD(getControl()->getForm());
		}

		void CPropertyHandlerPointD::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxPointD *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyPointD *p{ cast<IPropertyPointD*>(m_pProperty) };
					IPropertyPointDState *ps{ cast<IPropertyPointDState*>(m_pProperty) };
					if (ps)
						dlg->setValue(ps->getValue(m_sState));
					else
						dlg->setValue(p->getValue());
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerPointD *handler{ (CPropertyHandlerPointD*)(void*)sender->Tag };
							CDialogBoxPointD *dlg{ cast<CDialogBoxPointD*>(sender) };
							IPropertyPointD *p{ cast<IPropertyPointD*>(handler->m_pProperty) };
							IPropertyPointDState *ps{ cast<IPropertyPointDState*>(handler->m_pProperty) };
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
				IFormPointD *form{ getForm() };
				if (form)
				{
					IPropertyPointDState *ps{ cast<IPropertyPointDState*>(m_pProperty) };
					if (ps)
						form->setValue(ps->getValue(m_sState));
					else
						form->setValue(cast<IPropertyPointD*>(m_pProperty)->getValue());
					cast<IForm*>(form)->OnSetFocus = [](IForm *sender) {
						sender->OnSetFocus = nullptr;
						cast<IFormPointD*>(sender)->ActivateFirstEnabledInput();
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
							IPropertyPointD *p{ cast<IPropertyPointD*>(m_pProperty) };
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

		void CPropertyHandlerPointD::setDialogData(const PointD &value, const bool has_min, const bool has_max, const double min, const double max)
		{
			IFormPointD *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
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