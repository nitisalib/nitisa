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
		CPropertyHandlerBorderColor::CPropertyHandlerBorderColor(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerBorderColor),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerBorderColor::isEditable(IProperty *property)
		{
			return cast<IPropertyBorderColor*>(property) || cast<IPropertyBorderColorState*>(property);
		}

		IProperty *CPropertyHandlerBorderColor::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerBorderColor::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerBorderColor::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyBorderColorState *p{ cast<IPropertyBorderColorState*>(m_pProperty) };
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
					IPropertyBorderColor *p{ cast<IPropertyBorderColor*>(m_pProperty) };
					IPropertyBorderColorState *ps{ cast<IPropertyBorderColorState*>(m_pProperty) };
					if (ps)
						setDialogData(ps->getValue(m_sState));
					else
						setDialogData(p->getValue());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerBorderColor::setPropertyState(const String &value)
		{
			IPropertyBorderColorState *p{ cast<IPropertyBorderColorState*>(m_pProperty) };
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

		IFormBorderColor *CPropertyHandlerBorderColor::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormBorderColor::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormBorderColor*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxBorderColor *CPropertyHandlerBorderColor::getDialogBox()
		{
			CDialogBoxBorderColor *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxBorderColor*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxBorderColor(getControl()->getForm());
		}

		void CPropertyHandlerBorderColor::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxBorderColor *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyBorderColor *p{ cast<IPropertyBorderColor*>(m_pProperty) };
					IPropertyBorderColorState *ps{ cast<IPropertyBorderColorState*>(m_pProperty) };
					if (ps)
						dlg->setValue(ps->getValue(m_sState));
					else
						dlg->setValue(p->getValue());
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerBorderColor *handler{ (CPropertyHandlerBorderColor*)(void*)sender->Tag };
							CDialogBoxBorderColor *dlg{ cast<CDialogBoxBorderColor*>(sender) };
							IPropertyBorderColor *p{ cast<IPropertyBorderColor*>(handler->m_pProperty) };
							IPropertyBorderColorState *ps{ cast<IPropertyBorderColorState*>(handler->m_pProperty) };
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
				IFormBorderColor *form{ getForm() };
				if (form)
				{
					IPropertyBorderColorState *ps{ cast<IPropertyBorderColorState*>(m_pProperty) };
					if (ps)
						form->setValue(ps->getValue(m_sState));
					else
						form->setValue(cast<IPropertyBorderColor*>(m_pProperty)->getValue());
					cast<IForm*>(form)->OnSetFocus = [](IForm *sender) {
						sender->OnSetFocus = nullptr;
						cast<IFormBorderColor*>(sender)->ActivateFirstEnabledInput();
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
							IPropertyBorderColor *p{ cast<IPropertyBorderColor*>(m_pProperty) };
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

		void CPropertyHandlerBorderColor::setDialogData(const BorderColor &value)
		{
			IFormBorderColor *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
				form->setValue(value);
		}
	}
}