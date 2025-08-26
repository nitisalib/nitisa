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
		CPropertyHandlerHotkey::CPropertyHandlerHotkey(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerHotkey),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerHotkey::isEditable(IProperty *property)
		{
			return cast<IPropertyHotkey*>(property) || cast<IPropertyHotkeyState*>(property);
		}

		IProperty *CPropertyHandlerHotkey::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerHotkey::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerHotkey::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyHotkeyState *p{ cast<IPropertyHotkeyState*>(m_pProperty) };
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
					IPropertyHotkey *p{ cast<IPropertyHotkey*>(m_pProperty) };
					IPropertyHotkeyState *ps{ cast<IPropertyHotkeyState*>(m_pProperty) };
					setDialogHotkey(ps ? ps->getValue(m_sState) : p->getValue());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerHotkey::setPropertyState(const String &value)
		{
			IPropertyHotkeyState *p{ cast<IPropertyHotkeyState*>(m_pProperty) };
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
					setDialogHotkey(p->getValue(m_sState));
					return true;
				}
			}
			return false;
		}

		IFormHotkey *CPropertyHandlerHotkey::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormHotkey::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormHotkey*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxHotkey *CPropertyHandlerHotkey::getDialogBox()
		{
			CDialogBoxHotkey *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxHotkey*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxHotkey(getControl()->getForm());
		}

		void CPropertyHandlerHotkey::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxHotkey *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyHotkey *p{ cast<IPropertyHotkey*>(m_pProperty) };
					IPropertyHotkeyState *ps{ cast<IPropertyHotkeyState*>(m_pProperty) };
					if (ps)
						dlg->setValue(ps->getValue(m_sState));
					else
						dlg->setValue(p->getValue());
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerHotkey *handler{ (CPropertyHandlerHotkey*)(void*)sender->Tag };
							CDialogBoxHotkey *dlg{ cast<CDialogBoxHotkey*>(sender) };
							IPropertyHotkey *p{ cast<IPropertyHotkey*>(handler->m_pProperty) };
							IPropertyHotkeyState *ps{ cast<IPropertyHotkeyState*>(handler->m_pProperty) };
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
				IFormHotkey *form{ getForm() };
				if (form)
				{
					IPropertyHotkeyState *ps{ cast<IPropertyHotkeyState*>(m_pProperty) };
					if (ps)
						form->setValue(ps->getValue(m_sState));
					else
						form->setValue(cast<IPropertyHotkey*>(m_pProperty)->getValue());
					cast<IForm*>(form)->OnSetFocus = [](IForm *sender) {
						sender->OnSetFocus = nullptr;
						cast<IFormHotkey*>(sender)->ActivateFirstEnabledInput();
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
							IPropertyHotkey *p{ cast<IPropertyHotkey*>(m_pProperty) };
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

		void CPropertyHandlerHotkey::setDialogHotkey(const Hotkey &value)
		{
			IFormHotkey *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
				form->setValue(value);
		}
	}
}