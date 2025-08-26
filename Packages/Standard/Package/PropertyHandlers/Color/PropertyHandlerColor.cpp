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
		CPropertyHandlerColor::CPropertyHandlerColor(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerColor),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerColor::isEditable(IProperty *property)
		{
			return cast<IPropertyColor*>(property) || cast<IPropertyColorState*>(property);
		}

		IProperty *CPropertyHandlerColor::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerColor::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerColor::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyColorState *p{ cast<IPropertyColorState*>(m_pProperty) };
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
					IPropertyColor *p{ cast<IPropertyColor*>(m_pProperty) };
					IPropertyColorState *ps{ cast<IPropertyColorState*>(m_pProperty) };
					setDialogColor(ps ? ps->getValue(m_sState) : p->getValue());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerColor::setPropertyState(const String &value)
		{
			IPropertyColorState *p{ cast<IPropertyColorState*>(m_pProperty) };
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
					setDialogColor(p->getValue(m_sState));
					return true;
				}
			}
			return false;
		}

		IFormColor *CPropertyHandlerColor::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormColor::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormColor*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxColor *CPropertyHandlerColor::getDialogBox()
		{
			CDialogBoxColor *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxColor*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxColor(getControl()->getForm());
		}

		void CPropertyHandlerColor::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxColor *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyColor *p{ cast<IPropertyColor*>(m_pProperty) };
					IPropertyColorState *ps{ cast<IPropertyColorState*>(m_pProperty) };
					if (ps)
						dlg->setValue(ps->getValue(m_sState));
					else
						dlg->setValue(p->getValue());
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerColor *handler{ (CPropertyHandlerColor*)(void*)sender->Tag };
							CDialogBoxColor *dlg{ cast<CDialogBoxColor*>(sender) };
							IPropertyColor *p{ cast<IPropertyColor*>(handler->m_pProperty) };
							IPropertyColorState *ps{ cast<IPropertyColorState*>(handler->m_pProperty) };
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
				IFormColor *form{ getForm() };
				if (form)
				{
					IPropertyColorState *ps{ cast<IPropertyColorState*>(m_pProperty) };
					if (ps)
						form->setValue(ps->getValue(m_sState));
					else
						form->setValue(cast<IPropertyColor*>(m_pProperty)->getValue());
					cast<IForm*>(form)->OnSetFocus = [](IForm *sender) {
						sender->OnSetFocus = nullptr;
						cast<IFormColor*>(sender)->ActivateFirstEnabledInput();
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
							IPropertyColor *p{ cast<IPropertyColor*>(m_pProperty) };
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

		void CPropertyHandlerColor::setDialogColor(const Color &color)
		{
			IFormColor *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
				form->setValue(color);
		}
	}
}