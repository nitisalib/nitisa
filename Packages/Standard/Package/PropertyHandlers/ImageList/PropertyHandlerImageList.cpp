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
		CPropertyHandlerImageList::CPropertyHandlerImageList(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerImageList),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerImageList::isEditable(IProperty *property)
		{
			return cast<IPropertyImageList*>(property) || cast<IPropertyImageListState*>(property);
		}

		IProperty *CPropertyHandlerImageList::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerImageList::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerImageList::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyImageListState *p{ cast<IPropertyImageListState*>(m_pProperty) };
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
					setDialogData();
				return true;
			}
			return false;
		}

		bool CPropertyHandlerImageList::setPropertyState(const String &value)
		{
			IPropertyImageListState *p{ cast<IPropertyImageListState*>(m_pProperty) };
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
					setDialogData();
					return true;
				}
			}
			return false;
		}

		IFormImageList *CPropertyHandlerImageList::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormImageList::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormImageList*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxImageList *CPropertyHandlerImageList::getDialogBox()
		{
			CDialogBoxImageList *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxImageList*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxImageList(getControl()->getForm());
		}

		void CPropertyHandlerImageList::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxImageList *dlg{ getDialogBox() };
				if (dlg)
				{
					setDialogData();
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerImageList *handler{ (CPropertyHandlerImageList*)(void*)sender->Tag };
							CDialogBoxImageList *dlg{ cast<CDialogBoxImageList*>(sender) };
							IPropertyImageList *p{ cast<IPropertyImageList*>(handler->m_pProperty) };
							IPropertyImageListState *ps{ cast<IPropertyImageListState*>(handler->m_pProperty) };
							if (ps)
							{
								ps->Clear(handler->m_sState);
								for (int i = 0; i < dlg->getImageCount(); i++)
								{
									Image *bmp{ new Image() };
									*bmp = *dlg->getImage(i);
									ps->Add(handler->m_sState, bmp);
								}
								if (handler->getListener())
									cast<IPropertyHandlerListener*>(handler->getListener())->NotifyOnPropertyChange(handler, handler->m_pProperty);
							}
							else
							{
								p->Clear();
								for (int i = 0; i < dlg->getImageCount(); i++)
								{
									Image *bmp{ new Image() };
									*bmp = *dlg->getImage(i);
									p->Add(bmp);
								}
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
				IFormImageList *form{ getForm() };
				if (form)
				{
					IPropertyImageListState *ps{ cast<IPropertyImageListState*>(m_pProperty) };
					setDialogData();
					if (cast<IForm*>(form)->ShowModal() == ModalResult::Ok)
					{
						if (ps)
						{
							ps->Clear(m_sState);
							for (int i = 0; i < form->getImageCount(); i++)
							{
								Image *bmp{ new Image() };
								*bmp = *form->getImage(i);
								ps->Add(m_sState, bmp);
							}
							if (getListener())
								cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
						}
						else
						{
							IPropertyImageList *p{ cast<IPropertyImageList*>(m_pProperty) };
							if (p)
							{
								p->Clear();
								for (int i = 0; i < form->getImageCount(); i++)
								{
									Image *bmp{ new Image() };
									*bmp = *form->getImage(i);
									p->Add(bmp);
								}
								if (getListener())
									cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
							}
						}
					}
				}
			}
		}

		void CPropertyHandlerImageList::setDialogData()
		{
			IFormImageList *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
			{
				form->DeleteImages();
				IPropertyImageListState *ps{ cast<IPropertyImageListState*>(m_pProperty) };
				if (ps)
				{
					for (int i = 0; i < ps->getCount(m_sState); i++)
					{
						Image *bmp{ new Image() };
						*bmp = *ps->getImage(m_sState, i);
						form->AddImage(bmp);
					}
				}
				else
				{
					IPropertyImageList *p{ cast<IPropertyImageList*>(m_pProperty) };
					for (int i = 0; i < p->getCount(); i++)
					{
						Image *bmp{ new Image() };
						*bmp = *p->getImage(i);
						form->AddImage(bmp);
					}
				}
			}
		}
	}
}