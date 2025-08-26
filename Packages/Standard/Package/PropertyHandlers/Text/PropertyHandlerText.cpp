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
		CPropertyHandlerText::CPropertyHandlerText(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerText),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerText::isEditable(IProperty *property)
		{
			return cast<IPropertyText*>(property) || cast<IPropertyTextState*>(property);
		}

		IProperty *CPropertyHandlerText::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerText::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerText::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyTextState *p{ cast<IPropertyTextState*>(m_pProperty) };
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
					IPropertyText *p{ cast<IPropertyText*>(m_pProperty) };
					IPropertyTextState *ps{ cast<IPropertyTextState*>(m_pProperty) };
					setDialogText(ps ? ps->getValue(m_sState) : p->getValue());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerText::setPropertyState(const String &value)
		{
			IPropertyTextState *p{ cast<IPropertyTextState*>(m_pProperty) };
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
					setDialogText(p->getValue(m_sState));
					return true;
				}
			}
			return false;
		}

		IFormMemo *CPropertyHandlerText::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormMemo::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormMemo*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxMemo *CPropertyHandlerText::getDialogBox()
		{
			CDialogBoxMemo *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxMemo*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxMemo(getControl()->getForm());
		}

		void CPropertyHandlerText::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxMemo *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyText *p{ cast<IPropertyText*>(m_pProperty) };
					IPropertyTextState *ps{ cast<IPropertyTextState*>(m_pProperty) };
					if (ps)
						dlg->setValue(ps->getValue(m_sState));
					else
						dlg->setValue(p->getValue());
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerText *handler{ (CPropertyHandlerText*)(void*)sender->Tag };
							CDialogBoxMemo *dlg{ cast<CDialogBoxMemo*>(sender) };
							IPropertyText *p{ cast<IPropertyText*>(handler->m_pProperty) };
							IPropertyTextState *ps{ cast<IPropertyTextState*>(handler->m_pProperty) };
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
				IFormMemo *form{ getForm() };
				if (form)
				{
					IPropertyTextState *ps{ cast<IPropertyTextState*>(m_pProperty) };
					if (ps)
						form->setValue(ps->getValue(m_sState));
					else
						form->setValue(cast<IPropertyText*>(m_pProperty)->getValue());
					cast<IForm*>(form)->OnSetFocus = [](IForm *sender) {
						sender->OnSetFocus = nullptr;
						cast<IFormMemo*>(sender)->ActivateFirstEnabledInput();
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
							IPropertyText *p{ cast<IPropertyText*>(m_pProperty) };
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

		void CPropertyHandlerText::setDialogText(const String &value)
		{
			IFormMemo *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
				form->setValue(value);
		}
	}
}