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
		CPropertyHandlerIntegerArray::CPropertyHandlerIntegerArray(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerIntegerArray),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerIntegerArray::isEditable(IProperty *property)
		{
			return cast<IPropertyIntegerArray*>(property) || cast<IPropertyIntegerArrayState*>(property);
		}

		IProperty *CPropertyHandlerIntegerArray::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerIntegerArray::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerIntegerArray::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyIntegerArrayState *p{ cast<IPropertyIntegerArrayState*>(m_pProperty) };
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
					IPropertyIntegerArray *p{ cast<IPropertyIntegerArray*>(m_pProperty) };
					IPropertyIntegerArrayState *ps{ cast<IPropertyIntegerArrayState*>(m_pProperty) };
					if (ps)
						setDialogValue(ps->getValue(m_sState), ps->getMinCount(), ps->hasMin(), ps->hasMax(), ps->getMin(), ps->getMax());
					else
						setDialogValue(p->getValue(), p->getMinCount(), p->hasMin(), p->hasMax(), p->getMin(), p->getMax());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerIntegerArray::setPropertyState(const String &value)
		{
			IPropertyIntegerArrayState *p{ cast<IPropertyIntegerArrayState*>(m_pProperty) };
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
					setDialogValue(p->getValue(m_sState), p->getMinCount(), p->hasMin(), p->hasMax(), p->getMin(), p->getMax());
					return true;
				}
			}
			return false;
		}

		IFormIntegerArray *CPropertyHandlerIntegerArray::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormIntegerArray::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormIntegerArray*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxIntegerArray *CPropertyHandlerIntegerArray::getDialogBox()
		{
			CDialogBoxIntegerArray *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxIntegerArray*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxIntegerArray(getControl()->getForm());
		}

		void CPropertyHandlerIntegerArray::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxIntegerArray *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyIntegerArray *p{ cast<IPropertyIntegerArray*>(m_pProperty) };
					IPropertyIntegerArrayState *ps{ cast<IPropertyIntegerArrayState*>(m_pProperty) };
					if (ps)
					{
						dlg->setValue(ps->getValue(m_sState));
						dlg->setMinCount(ps->getMinCount());
						dlg->setHasMin(ps->hasMin());
						dlg->setHasMax(ps->hasMax());
						dlg->setMin(ps->getMin());
						dlg->setMax(ps->getMax());
					}
					else
					{
						dlg->setValue(p->getValue());
						dlg->setMinCount(p->getMinCount());
						dlg->setHasMin(p->hasMin());
						dlg->setHasMax(p->hasMax());
						dlg->setMin(p->getMin());
						dlg->setMax(p->getMax());
					}
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerIntegerArray *handler{ (CPropertyHandlerIntegerArray*)(void*)sender->Tag };
							CDialogBoxIntegerArray *dlg{ cast<CDialogBoxIntegerArray*>(sender) };
							IPropertyIntegerArray *p{ cast<IPropertyIntegerArray*>(handler->m_pProperty) };
							IPropertyIntegerArrayState *ps{ cast<IPropertyIntegerArrayState*>(handler->m_pProperty) };
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
				IFormIntegerArray *form{ getForm() };
				if (form)
				{
					IPropertyIntegerArray *p{ cast<IPropertyIntegerArray*>(m_pProperty) };
					IPropertyIntegerArrayState *ps{ cast<IPropertyIntegerArrayState*>(m_pProperty) };
					if (ps)
					{
						form->setValue(ps->getValue(m_sState));
						form->setMinCount(ps->getMinCount());
						form->setHasMin(ps->hasMin());
						form->setHasMax(ps->hasMax());
						form->setMin(ps->getMin());
						form->setMax(ps->getMax());
					}
					else
					{
						form->setValue(p->getValue());
						form->setMinCount(p->getMinCount());
						form->setHasMin(p->hasMin());
						form->setHasMax(p->hasMax());
						form->setMin(p->getMin());
						form->setMax(p->getMax());
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

		void CPropertyHandlerIntegerArray::setDialogValue(const IntegerArray &value, const int min_count, const bool has_min, const bool has_max, const int min, const int max)
		{
			IFormIntegerArray *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
			{
				form->setValue(value);
				form->setMinCount(min_count);
				form->setHasMin(has_min);
				form->setHasMax(has_max);
				form->setMin(min);
				form->setMax(max);
			}
		}
	}
}