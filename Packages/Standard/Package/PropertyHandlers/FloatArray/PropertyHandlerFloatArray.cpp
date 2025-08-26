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
		CPropertyHandlerFloatArray::CPropertyHandlerFloatArray(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerFloatArray),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerFloatArray::isEditable(IProperty *property)
		{
			return cast<IPropertyFloatArray*>(property) || cast<IPropertyFloatArrayState*>(property);
		}

		IProperty *CPropertyHandlerFloatArray::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerFloatArray::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerFloatArray::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyFloatArrayState *p{ cast<IPropertyFloatArrayState*>(m_pProperty) };
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
					IPropertyFloatArray *p{ cast<IPropertyFloatArray*>(m_pProperty) };
					IPropertyFloatArrayState *ps{ cast<IPropertyFloatArrayState*>(m_pProperty) };
					if (ps)
						setDialogValue(ps->getValue(m_sState), ps->getMinCount(), ps->hasMin(), ps->hasMax(), ps->getMin(), ps->getMax());
					else
						setDialogValue(p->getValue(), p->getMinCount(), p->hasMin(), p->hasMax(), p->getMin(), p->getMax());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerFloatArray::setPropertyState(const String &value)
		{
			IPropertyFloatArrayState *p{ cast<IPropertyFloatArrayState*>(m_pProperty) };
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

		IFormFloatArray *CPropertyHandlerFloatArray::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormFloatArray::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormFloatArray*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxFloatArray *CPropertyHandlerFloatArray::getDialogBox()
		{
			CDialogBoxFloatArray *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxFloatArray*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxFloatArray(getControl()->getForm());
		}

		void CPropertyHandlerFloatArray::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxFloatArray *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyFloatArray *p{ cast<IPropertyFloatArray*>(m_pProperty) };
					IPropertyFloatArrayState *ps{ cast<IPropertyFloatArrayState*>(m_pProperty) };
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
							CPropertyHandlerFloatArray *handler{ (CPropertyHandlerFloatArray*)(void*)sender->Tag };
							CDialogBoxFloatArray *dlg{ cast<CDialogBoxFloatArray*>(sender) };
							IPropertyFloatArray *p{ cast<IPropertyFloatArray*>(handler->m_pProperty) };
							IPropertyFloatArrayState *ps{ cast<IPropertyFloatArrayState*>(handler->m_pProperty) };
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
				IFormFloatArray *form{ getForm() };
				if (form)
				{
					IPropertyFloatArray *p{ cast<IPropertyFloatArray*>(m_pProperty) };
					IPropertyFloatArrayState *ps{ cast<IPropertyFloatArrayState*>(m_pProperty) };
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

		void CPropertyHandlerFloatArray::setDialogValue(const FloatArray &value, const int min_count, const bool has_min, const bool has_max, const float min, const float max)
		{
			IFormFloatArray *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
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