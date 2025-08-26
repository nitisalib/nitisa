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
	namespace charts
	{
		CPropertyHandlerLineInterpolationPositionArray::CPropertyHandlerLineInterpolationPositionArray(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerLineInterpolationPositionArray),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerLineInterpolationPositionArray::isEditable(IProperty *property)
		{
			return cast<IPropertyLineInterpolationPositionArray*>(property);
		}

		IProperty *CPropertyHandlerLineInterpolationPositionArray::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerLineInterpolationPositionArray::getPropertyState()
		{
			return L"";
		}

		bool CPropertyHandlerLineInterpolationPositionArray::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (m_pProperty)
				{
					IPropertyLineInterpolationPositionArray *p{ cast<IPropertyLineInterpolationPositionArray*>(m_pProperty) };
					setDialogValue(p->getValue(), p->getMinCount());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerLineInterpolationPositionArray::setPropertyState(const String &value)
		{
			return false;
		}

		IFormLineInterpolationPositionArray *CPropertyHandlerLineInterpolationPositionArray::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormLineInterpolationPositionArray::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormLineInterpolationPositionArray*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxLineInterpolationPositionArray *CPropertyHandlerLineInterpolationPositionArray::getDialogBox()
		{
			CDialogBoxLineInterpolationPositionArray *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxLineInterpolationPositionArray*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxLineInterpolationPositionArray(getControl()->getForm());
		}

		void CPropertyHandlerLineInterpolationPositionArray::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxLineInterpolationPositionArray *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyLineInterpolationPositionArray *p{ cast<IPropertyLineInterpolationPositionArray*>(m_pProperty) };
					dlg->setValue(p->getValue());
					dlg->setMinCount(p->getMinCount());
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerLineInterpolationPositionArray *handler{ (CPropertyHandlerLineInterpolationPositionArray*)(void*)sender->Tag };
							IPropertyLineInterpolationPositionArray *p{ cast<IPropertyLineInterpolationPositionArray*>(handler->m_pProperty) };
							p->setValue(cast<CDialogBoxLineInterpolationPositionArray*>(sender)->getValue());
							if (handler->getListener())
								cast<IPropertyHandlerListener*>(handler->getListener())->NotifyOnPropertyChange(handler, handler->m_pProperty);
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
				IFormLineInterpolationPositionArray *form{ getForm() };
				if (form)
				{
					IPropertyLineInterpolationPositionArray *p{ cast<IPropertyLineInterpolationPositionArray*>(m_pProperty) };
					form->setValue(p->getValue());
					form->setMinCount(p->getMinCount());
					if (cast<IForm*>(form)->ShowModal() == ModalResult::Ok)
					{
						p->setValue(form->getValue());
						if (getListener())
							cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
					}
				}
			}
		}

		void CPropertyHandlerLineInterpolationPositionArray::setDialogValue(const std::vector<LineInterpolationPosition> &value, const int min_count)
		{
			IFormLineInterpolationPositionArray *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
			{
				form->setValue(value);
				form->setMinCount(min_count);
			}
		}
	}
}