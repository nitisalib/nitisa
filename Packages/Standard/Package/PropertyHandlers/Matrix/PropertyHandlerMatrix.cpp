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
		CPropertyHandlerMatrix::CPropertyHandlerMatrix(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerMatrix),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerMatrix::isEditable(IProperty *property)
		{
			return cast<IPropertyMatrix*>(property) || cast<IPropertyMatrixState*>(property);
		}

		IProperty *CPropertyHandlerMatrix::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerMatrix::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerMatrix::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyMatrixState *p{ cast<IPropertyMatrixState*>(m_pProperty) };
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
					IPropertyMatrix *p{ cast<IPropertyMatrix*>(m_pProperty) };
					IPropertyMatrixState *ps{ cast<IPropertyMatrixState*>(m_pProperty) };
					setDialogMatrix(ps ? ps->getValue(m_sState) : p->getValue());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerMatrix::setPropertyState(const String &value)
		{
			IPropertyMatrixState *p{ cast<IPropertyMatrixState*>(m_pProperty) };
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
					setDialogMatrix(p->getValue(m_sState));
					return true;
				}
			}
			return false;
		}

		IFormMatrix *CPropertyHandlerMatrix::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormMatrix::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormMatrix*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxMatrix *CPropertyHandlerMatrix::getDialogBox()
		{
			CDialogBoxMatrix *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxMatrix*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxMatrix(getControl()->getForm());
		}

		void CPropertyHandlerMatrix::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxMatrix *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyMatrix *p{ cast<IPropertyMatrix*>(m_pProperty) };
					IPropertyMatrixState *ps{ cast<IPropertyMatrixState*>(m_pProperty) };
					if (ps)
						dlg->setValue(ps->getValue(m_sState));
					else
						dlg->setValue(p->getValue());
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerMatrix *handler{ (CPropertyHandlerMatrix*)(void*)sender->Tag };
							CDialogBoxMatrix *dlg{ cast<CDialogBoxMatrix*>(sender) };
							IPropertyMatrix *p{ cast<IPropertyMatrix*>(handler->m_pProperty) };
							IPropertyMatrixState *ps{ cast<IPropertyMatrixState*>(handler->m_pProperty) };
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
				IFormMatrix *form{ getForm() };
				if (form)
				{
					IPropertyMatrixState *ps{ cast<IPropertyMatrixState*>(m_pProperty) };
					if (ps)
						form->setValue(ps->getValue(m_sState));
					else
						form->setValue(cast<IPropertyMatrix*>(m_pProperty)->getValue());
					cast<IForm*>(form)->OnSetFocus = [](IForm *sender) {
						sender->OnSetFocus = nullptr;
						cast<IFormMatrix*>(sender)->ActivateFirstEnabledInput();
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
							IPropertyMatrix *p{ cast<IPropertyMatrix*>(m_pProperty) };
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

		void CPropertyHandlerMatrix::setDialogMatrix(const Mat4f &value)
		{
			IFormMatrix *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
				form->setValue(value);
		}
	}
}