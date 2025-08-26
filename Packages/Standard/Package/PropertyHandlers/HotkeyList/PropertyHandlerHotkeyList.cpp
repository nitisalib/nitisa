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
		CPropertyHandlerHotkeyList::CPropertyHandlerHotkeyList(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerHotkeyList),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerHotkeyList::isEditable(IProperty *property)
		{
			return cast<IPropertyHotkeyList*>(property) != nullptr;
		}

		IProperty *CPropertyHandlerHotkeyList::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerHotkeyList::getPropertyState()
		{
			return L"";
		}

		bool CPropertyHandlerHotkeyList::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (m_pProperty)
					setDialogData();
				return true;
			}
			return false;
		}

		bool CPropertyHandlerHotkeyList::setPropertyState(const String &value)
		{
			return false;
		}

		IFormHotkeyList *CPropertyHandlerHotkeyList::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormHotkeyList::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormHotkeyList*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxHotkeyList *CPropertyHandlerHotkeyList::getDialogBox()
		{
			CDialogBoxHotkeyList *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxHotkeyList*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxHotkeyList(getControl()->getForm());
		}

		void CPropertyHandlerHotkeyList::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxHotkeyList *dlg{ getDialogBox() };
				if (dlg)
				{
					setDialogData();
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerHotkeyList *handler{ (CPropertyHandlerHotkeyList*)(void*)sender->Tag };
							CDialogBoxHotkeyList *dlg{ cast<CDialogBoxHotkeyList*>(sender) };
							IPropertyHotkeyList *p{ cast<IPropertyHotkeyList*>(handler->m_pProperty) };
							if (p)
							{
								p->Clear();
								for (int i = 0; i < dlg->getHotkeyCount(); i++)
									p->Add(dlg->getHotkey(i));
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
				IFormHotkeyList *form{ getForm() };
				if (form)
				{
					setDialogData();
					cast<IForm*>(form)->OnSetFocus = [](IForm *sender) {
						sender->OnSetFocus = nullptr;
						cast<IFormHotkeyList*>(sender)->ActivateFirstEnabledInput();
					};
					if (cast<IForm*>(form)->ShowModal() == ModalResult::Ok)
					{
						IPropertyHotkeyList *p{ cast<IPropertyHotkeyList*>(m_pProperty) };
						if (p)
						{
							p->Clear();
							for (int i = 0; i < form->getHotkeyCount(); i++)
								p->Add(form->getHotkey(i));
							if (getListener())
								cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
						}
					}
				}
			}
		}

		void CPropertyHandlerHotkeyList::setDialogData()
		{
			IFormHotkeyList *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
			{
				IPropertyHotkeyList *p{ cast<IPropertyHotkeyList*>(m_pProperty) };
				CLockRepaint lock{ getControl() };
				form->DeleteHotkeys();
				for (int i = 0; i < p->getCount(); i++)
					form->AddHotkey(p->getHotkey(i));
			}
		}
	}
}