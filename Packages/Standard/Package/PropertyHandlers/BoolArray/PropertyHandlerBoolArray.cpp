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
		CPropertyHandlerBoolArray::CPropertyHandlerBoolArray(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerBoolArray),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerBoolArray::isEditable(IProperty *property)
		{
			return cast<IPropertyBoolArray*>(property) || cast<IPropertyBoolArrayState*>(property);
		}

		IProperty *CPropertyHandlerBoolArray::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerBoolArray::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerBoolArray::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyBoolArrayState *p{ cast<IPropertyBoolArrayState*>(m_pProperty) };
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
					IPropertyBoolArray *p{ cast<IPropertyBoolArray*>(m_pProperty) };
					IPropertyBoolArrayState *ps{ cast<IPropertyBoolArrayState*>(m_pProperty) };
					if (ps)
						setDialogValue(ps->getValue(m_sState), ps->getMinCount());
					else
						setDialogValue(p->getValue(), p->getMinCount());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerBoolArray::setPropertyState(const String &value)
		{
			IPropertyBoolArrayState *p{ cast<IPropertyBoolArrayState*>(m_pProperty) };
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

		IFormBoolArray *CPropertyHandlerBoolArray::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormBoolArray::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormBoolArray*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxBoolArray *CPropertyHandlerBoolArray::getDialogBox()
		{
			CDialogBoxBoolArray *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxBoolArray*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxBoolArray(getControl()->getForm());
		}

		void CPropertyHandlerBoolArray::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxBoolArray *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyBoolArray *p{ cast<IPropertyBoolArray*>(m_pProperty) };
					IPropertyBoolArrayState *ps{ cast<IPropertyBoolArrayState*>(m_pProperty) };
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
							CPropertyHandlerBoolArray *handler{ (CPropertyHandlerBoolArray*)(void*)sender->Tag };
							CDialogBoxBoolArray *dlg{ cast<CDialogBoxBoolArray*>(sender) };
							IPropertyBoolArray *p{ cast<IPropertyBoolArray*>(handler->m_pProperty) };
							IPropertyBoolArrayState *ps{ cast<IPropertyBoolArrayState*>(handler->m_pProperty) };
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
				IFormBoolArray *form{ getForm() };
				if (form)
				{
					IPropertyBoolArray *p{ cast<IPropertyBoolArray*>(m_pProperty) };
					IPropertyBoolArrayState *ps{ cast<IPropertyBoolArrayState*>(m_pProperty) };
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

		void CPropertyHandlerBoolArray::setDialogValue(const BoolArray &value, const int min_count)
		{
			IFormBoolArray *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
			{
				form->setValue(value);
				form->setMinCount(min_count);
			}
		}
	}
}