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
		CPropertyHandlerImage::CPropertyHandlerImage(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerImage),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerImage::isEditable(IProperty *property)
		{
			return cast<IPropertyImage*>(property) || cast<IPropertyImageState*>(property);
		}

		IProperty *CPropertyHandlerImage::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerImage::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerImage::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyImageState *p{ cast<IPropertyImageState*>(m_pProperty) };
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
					IPropertyImage *p{ cast<IPropertyImage*>(m_pProperty) };
					IPropertyImageState *ps{ cast<IPropertyImageState*>(m_pProperty) };
					setDialogData(ps ? ps->getValue(m_sState) : p->getValue());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerImage::setPropertyState(const String &value)
		{
			IPropertyImageState *p{ cast<IPropertyImageState*>(m_pProperty) };
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

		IFormImage *CPropertyHandlerImage::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormImage::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormImage*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxImage *CPropertyHandlerImage::getDialogBox()
		{
			CDialogBoxImage *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxImage*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxImage(getControl()->getForm());
		}

		void CPropertyHandlerImage::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxImage *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyImage *p{ cast<IPropertyImage*>(m_pProperty) };
					IPropertyImageState *ps{ cast<IPropertyImageState*>(m_pProperty) };
					if (ps)
						dlg->setValue(*ps->getValue(m_sState));
					else
						dlg->setValue(*p->getValue());
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerImage *handler{ (CPropertyHandlerImage*)(void*)sender->Tag };
							CDialogBoxImage *dlg{ cast<CDialogBoxImage*>(sender) };
							IPropertyImage *p{ cast<IPropertyImage*>(handler->m_pProperty) };
							IPropertyImageState *ps{ cast<IPropertyImageState*>(handler->m_pProperty) };
							if (ps)
							{
								*ps->getValue(handler->m_sState) = *dlg->getValue();
								ps->Update();
								if (handler->getListener())
									cast<IPropertyHandlerListener*>(handler->getListener())->NotifyOnPropertyChange(handler, handler->m_pProperty);
							}
							else
							{
								*p->getValue() = *dlg->getValue();
								p->Update();
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
				IFormImage *form{ getForm() };
				if (form)
				{
					IPropertyImageState *ps{ cast<IPropertyImageState*>(m_pProperty) };
					if (ps)
						form->setValue(*ps->getValue(m_sState));
					else
						form->setValue(*cast<IPropertyImage*>(m_pProperty)->getValue());
					if (cast<IForm*>(form)->ShowModal() == ModalResult::Ok)
					{
						if (ps)
						{
							*ps->getValue(m_sState) = *form->getValue();
							ps->Update();
							if (getListener())
								cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
						}
						else
						{
							IPropertyImage *p{ cast<IPropertyImage*>(m_pProperty) };
							if (p)
							{
								*p->getValue() = *form->getValue();
								p->Update();
								if (getListener())
									cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
							}
						}
					}
				}
			}
		}

		void CPropertyHandlerImage::setDialogData(const Image *data)
		{
			IFormImage *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
				form->setValue(*data);
		}
	}
}