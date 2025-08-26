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
		CPropertyHandlerGradient::CPropertyHandlerGradient(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerGradient),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerGradient::isEditable(IProperty *property)
		{
			return cast<IPropertyGradient*>(property) || cast<IPropertyGradientState*>(property);
		}

		IProperty *CPropertyHandlerGradient::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerGradient::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerGradient::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyGradientState *p{ cast<IPropertyGradientState*>(m_pProperty) };
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
					IPropertyGradient *p{ cast<IPropertyGradient*>(m_pProperty) };
					IPropertyGradientState *ps{ cast<IPropertyGradientState*>(m_pProperty) };
					setDialogData(ps ? *ps->getValue(m_sState) : *p->getValue());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerGradient::setPropertyState(const String &value)
		{
			IPropertyGradientState *p{ cast<IPropertyGradientState*>(m_pProperty) };
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
					setDialogData(*p->getValue(m_sState));
					return true;
				}
			}
			return false;
		}

		IFormGradient *CPropertyHandlerGradient::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormGradient::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormGradient*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxGradient *CPropertyHandlerGradient::getDialogBox()
		{
			CDialogBoxGradient *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxGradient*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxGradient(getControl()->getForm());
		}

		void CPropertyHandlerGradient::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxGradient *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyGradient *p{ cast<IPropertyGradient*>(m_pProperty) };
					IPropertyGradientState *ps{ cast<IPropertyGradientState*>(m_pProperty) };
					if (ps)
						dlg->setValue(*ps->getValue(m_sState));
					else
						dlg->setValue(*p->getValue());
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerGradient *handler{ (CPropertyHandlerGradient*)(void*)sender->Tag };
							CDialogBoxGradient *dlg{ cast<CDialogBoxGradient*>(sender) };
							IPropertyGradient *p{ cast<IPropertyGradient*>(handler->m_pProperty) };
							IPropertyGradientState *ps{ cast<IPropertyGradientState*>(handler->m_pProperty) };
							if (ps)
							{
								*ps->getValue(handler->m_sState) = *dlg->getValue();
								if (handler->getListener())
									cast<IPropertyHandlerListener*>(handler->getListener())->NotifyOnPropertyChange(handler, handler->m_pProperty);
							}
							else
							{
								*p->getValue() = *dlg->getValue();
								if (handler->getListener())
									cast<IPropertyHandlerListener*>(handler->getListener())->NotifyOnPropertyChange(handler, handler->m_pProperty);
							}
						}
					};
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
				IFormGradient *form{ getForm() };
				if (form)
				{
					IPropertyGradientState *ps{ cast<IPropertyGradientState*>(m_pProperty) };
					if (ps)
						form->setValue(*ps->getValue(m_sState));
					else
						form->setValue(*cast<IPropertyGradient*>(m_pProperty)->getValue());
					if (cast<IForm*>(form)->ShowModal() == ModalResult::Ok)
					{
						if (ps)
						{
							*ps->getValue(m_sState) = *form->getValue();
							if (getListener())
								cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
						}
						else
						{
							IPropertyGradient *p{ cast<IPropertyGradient*>(m_pProperty) };
							if (p)
							{
								*p->getValue() = *form->getValue();
								if (getListener())
									cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
							}
						}
					}
				}
			}
		}

		void CPropertyHandlerGradient::setDialogData(Gradient &value)
		{
			IFormGradient *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
				form->setValue(value);
		}
	}
}