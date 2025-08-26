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
		CPropertyHandlerColorArray::CPropertyHandlerColorArray(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerColorArray),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerColorArray::isEditable(IProperty *property)
		{
			return cast<IPropertyColorArray*>(property) || cast<IPropertyColorArrayState*>(property);
		}

		IProperty *CPropertyHandlerColorArray::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerColorArray::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerColorArray::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyColorArrayState *p{ cast<IPropertyColorArrayState*>(m_pProperty) };
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
					IPropertyColorArray *p{ cast<IPropertyColorArray*>(m_pProperty) };
					IPropertyColorArrayState *ps{ cast<IPropertyColorArrayState*>(m_pProperty) };
					if (ps)
						setDialogValue(ps->getValue(m_sState), ps->getMinCount());
					else
						setDialogValue(p->getValue(), p->getMinCount());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerColorArray::setPropertyState(const String &value)
		{
			IPropertyColorArrayState *p{ cast<IPropertyColorArrayState*>(m_pProperty) };
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
					setDialogValue(p->getValue(m_sState), p->getMinCount());
					return true;
				}
			}
			return false;
		}

		IFormColorArray *CPropertyHandlerColorArray::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormColorArray::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormColorArray*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxColorArray *CPropertyHandlerColorArray::getDialogBox()
		{
			CDialogBoxColorArray *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxColorArray*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxColorArray(getControl()->getForm());
		}

		void CPropertyHandlerColorArray::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxColorArray *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyColorArray *p{ cast<IPropertyColorArray*>(m_pProperty) };
					IPropertyColorArrayState *ps{ cast<IPropertyColorArrayState*>(m_pProperty) };
					if (ps)
					{
						dlg->setValue(ps->getValue(m_sState));
						dlg->setMinCount(ps->getMinCount());
					}
					else
					{
						dlg->setValue(p->getValue());
						dlg->setMinCount(p->getMinCount());
					}
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerColorArray *handler{ (CPropertyHandlerColorArray*)(void*)sender->Tag };
							CDialogBoxColorArray *dlg{ cast<CDialogBoxColorArray*>(sender) };
							IPropertyColorArray *p{ cast<IPropertyColorArray*>(handler->m_pProperty) };
							IPropertyColorArrayState *ps{ cast<IPropertyColorArrayState*>(handler->m_pProperty) };
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
				IFormColorArray *form{ getForm() };
				if (form)
				{
					IPropertyColorArray *p{ cast<IPropertyColorArray*>(m_pProperty) };
					IPropertyColorArrayState *ps{ cast<IPropertyColorArrayState*>(m_pProperty) };
					if (ps)
					{
						form->setValue(ps->getValue(m_sState));
						form->setMinCount(ps->getMinCount());
					}
					else
					{
						form->setValue(p->getValue());
						form->setMinCount(p->getMinCount());
					}
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
							p->setValue(form->getValue());
							if (getListener())
								cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
						}
					}
				}
			}
		}

		void CPropertyHandlerColorArray::setDialogValue(const ColorArray &value, const int min_count)
		{
			IFormColorArray *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
			{
				form->setValue(value);
				form->setMinCount(min_count);
			}
		}
	}
}