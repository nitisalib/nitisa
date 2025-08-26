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
		CPropertyHandlerTransform::CPropertyHandlerTransform(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerTransform),
			m_pProperty{ nullptr },
			m_bDialogBoxAdjusted{ false }
		{

		}

		bool CPropertyHandlerTransform::isEditable(IProperty *property)
		{
			return cast<IPropertyTransform*>(property) || cast<IPropertyTransformState*>(property);
		}

		IProperty *CPropertyHandlerTransform::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerTransform::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerTransform::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyTransformState *p{ cast<IPropertyTransformState*>(m_pProperty) };
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
					IPropertyTransform *p{ cast<IPropertyTransform*>(m_pProperty) };
					IPropertyTransformState *ps{ cast<IPropertyTransformState*>(m_pProperty) };
					if (ps)
						setDialogData(ps->getValue(m_sState),
							ps->isAllowedTx(), ps->isAllowedTy(), ps->isAllowedTz(),
							ps->isAllowedSx(), ps->isAllowedSy(), ps->isAllowedSz(),
							ps->isAllowedRx(), ps->isAllowedRy(), ps->isAllowedRz(),
							ps->isAllowedRotateOrder(), ps->isAllowedTransformOrder(),
							ps->hasMinTx(), ps->hasMinTy(), ps->hasMinTz(),
							ps->hasMinSx(), ps->hasMinSy(), ps->hasMinSz(),
							ps->hasMinRx(), ps->hasMinRy(), ps->hasMinRz(),
							ps->hasMaxTx(), ps->hasMaxTy(), ps->hasMaxTz(),
							ps->hasMaxSx(), ps->hasMaxSy(), ps->hasMaxSz(),
							ps->hasMaxRx(), ps->hasMaxRy(), ps->hasMaxRz(),
							ps->getMinTx(), ps->getMinTy(), ps->getMinTz(),
							ps->getMinSx(), ps->getMinSy(), ps->getMinSz(),
							ps->getMinRx(), ps->getMinRy(), ps->getMinRz(),
							ps->getMaxTx(), ps->getMaxTy(), ps->getMaxTz(),
							ps->getMaxSx(), ps->getMaxSy(), ps->getMaxSz(),
							ps->getMaxRx(), ps->getMaxRy(), ps->getMaxRz()
						);
					else
						setDialogData(p->getValue(),
							p->isAllowedTx(), p->isAllowedTy(), p->isAllowedTz(),
							p->isAllowedSx(), p->isAllowedSy(), p->isAllowedSz(),
							p->isAllowedRx(), p->isAllowedRy(), p->isAllowedRz(),
							p->isAllowedRotateOrder(), p->isAllowedTransformOrder(),
							p->hasMinTx(), p->hasMinTy(), p->hasMinTz(),
							p->hasMinSx(), p->hasMinSy(), p->hasMinSz(),
							p->hasMinRx(), p->hasMinRy(), p->hasMinRz(),
							p->hasMaxTx(), p->hasMaxTy(), p->hasMaxTz(),
							p->hasMaxSx(), p->hasMaxSy(), p->hasMaxSz(),
							p->hasMaxRx(), p->hasMaxRy(), p->hasMaxRz(),
							p->getMinTx(), p->getMinTy(), p->getMinTz(),
							p->getMinSx(), p->getMinSy(), p->getMinSz(),
							p->getMinRx(), p->getMinRy(), p->getMinRz(),
							p->getMaxTx(), p->getMaxTy(), p->getMaxTz(),
							p->getMaxSx(), p->getMaxSy(), p->getMaxSz(),
							p->getMaxRx(), p->getMaxRy(), p->getMaxRz()
						);
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerTransform::setPropertyState(const String &value)
		{
			IPropertyTransformState *p{ cast<IPropertyTransformState*>(m_pProperty) };
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
					setDialogData(p->getValue(m_sState),
						p->isAllowedTx(), p->isAllowedTy(), p->isAllowedTz(),
						p->isAllowedSx(), p->isAllowedSy(), p->isAllowedSz(),
						p->isAllowedRx(), p->isAllowedRy(), p->isAllowedRz(),
						p->isAllowedRotateOrder(), p->isAllowedTransformOrder(),
						p->hasMinTx(), p->hasMinTy(), p->hasMinTz(),
						p->hasMinSx(), p->hasMinSy(), p->hasMinSz(),
						p->hasMinRx(), p->hasMinRy(), p->hasMinRz(),
						p->hasMaxTx(), p->hasMaxTy(), p->hasMaxTz(),
						p->hasMaxSx(), p->hasMaxSy(), p->hasMaxSz(),
						p->hasMaxRx(), p->hasMaxRy(), p->hasMaxRz(),
						p->getMinTx(), p->getMinTy(), p->getMinTz(),
						p->getMinSx(), p->getMinSy(), p->getMinSz(),
						p->getMinRx(), p->getMinRy(), p->getMinRz(),
						p->getMaxTx(), p->getMaxTy(), p->getMaxTz(),
						p->getMaxSx(), p->getMaxSy(), p->getMaxSz(),
						p->getMaxRx(), p->getMaxRy(), p->getMaxRz()
					);
					return true;
				}
			}
			return false;
		}

		IFormTransform *CPropertyHandlerTransform::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormTransform::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormTransform*>(f);
				}
			}
			return nullptr;
		}

		CDialogBoxTransform *CPropertyHandlerTransform::getDialogBox()
		{
			CDialogBoxTransform *result;
			for (int i = getControl()->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((result = cast<CDialogBoxTransform*>(getControl()->getForm()->getControl(i))))
					return result;
			m_bDialogBoxAdjusted = false;
			return new CDialogBoxTransform(getControl()->getForm());
		}

		void CPropertyHandlerTransform::NotifyOnActivateModal()
		{
			if (Application->DialogBoxes)
			{
				CDialogBoxTransform *dlg{ getDialogBox() };
				if (dlg)
				{
					IPropertyTransform *p{ cast<IPropertyTransform*>(m_pProperty) };
					IPropertyTransformState *ps{ cast<IPropertyTransformState*>(m_pProperty) };
					if (ps)
						dlg->setValue(ps->getValue(m_sState));
					else
						dlg->setValue(p->getValue());
					dlg->Tag = (void*)this;
					dlg->OnClose = [](IDialogBox *sender, CloseAction &action) {
						if (sender->getModalResult() == ModalResult::Ok)
						{
							CPropertyHandlerTransform *handler{ (CPropertyHandlerTransform*)(void*)sender->Tag };
							CDialogBoxTransform *dlg{ cast<CDialogBoxTransform*>(sender) };
							IPropertyTransform *p{ cast<IPropertyTransform*>(handler->m_pProperty) };
							IPropertyTransformState *ps{ cast<IPropertyTransformState*>(handler->m_pProperty) };
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
				IFormTransform *form{ getForm() };
				if (form)
				{
					IPropertyTransformState *ps{ cast<IPropertyTransformState*>(m_pProperty) };
					if (ps)
						form->setValue(ps->getValue(m_sState));
					else
						form->setValue(cast<IPropertyTransform*>(m_pProperty)->getValue());
					cast<IForm*>(form)->OnSetFocus = [](IForm *sender) {
						sender->OnSetFocus = nullptr;
						cast<IFormTransform*>(sender)->ActivateFirstEnabledInput();
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
							IPropertyTransform *p{ cast<IPropertyTransform*>(m_pProperty) };
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

		void CPropertyHandlerTransform::setDialogData(const Transform &value,
			const bool allowed_tx, const bool allowed_ty, const bool allowed_tz,
			const bool allowed_sx, const bool allowed_sy, const bool allowed_sz,
			const bool allowed_rx, const bool allowed_ry, const bool allowed_rz,
			const bool allowed_ro, const bool allowed_to,
			const bool has_min_tx, const bool has_min_ty, const bool has_min_tz,
			const bool has_min_sx, const bool has_min_sy, const bool has_min_sz,
			const bool has_min_rx, const bool has_min_ry, const bool has_min_rz,
			const bool has_max_tx, const bool has_max_ty, const bool has_max_tz,
			const bool has_max_sx, const bool has_max_sy, const bool has_max_sz,
			const bool has_max_rx, const bool has_max_ry, const bool has_max_rz,
			const float min_tx, const float min_ty, const float min_tz,
			const float min_sx, const float min_sy, const float min_sz,
			const float min_rx, const float min_ry, const float min_rz,
			const float max_tx, const float max_ty, const float max_tz,
			const float max_sx, const float max_sy, const float max_sz,
			const float max_rx, const float max_ry, const float max_rz)
		{
			IFormTransform *form{ Application->DialogBoxes ? getDialogBox() : getForm() };
			if (form)
			{
				form->setValue(value);
				form->setAllowedTx(allowed_tx);
				form->setAllowedTy(allowed_ty);
				form->setAllowedTz(allowed_tz);
				form->setAllowedSx(allowed_sx);
				form->setAllowedSy(allowed_sy);
				form->setAllowedSz(allowed_sz);
				form->setAllowedRx(allowed_rx);
				form->setAllowedRy(allowed_ry);
				form->setAllowedRz(allowed_rz);
				form->setAllowedRotateOrder(allowed_ro);
				form->setAllowedTransformOrder(allowed_to);
				form->setMinTx(min_tx);
				form->setMinTy(min_ty);
				form->setMinTz(min_tz);
				form->setMinSx(min_sx);
				form->setMinSy(min_sy);
				form->setMinSz(min_sz);
				form->setMinRx(min_rx);
				form->setMinRy(min_ry);
				form->setMinRz(min_rz);
				form->setMaxTx(max_tx);
				form->setMaxTy(max_ty);
				form->setMaxTz(max_tz);
				form->setMaxSx(max_sx);
				form->setMaxSy(max_sy);
				form->setMaxSz(max_sz);
				form->setMaxRx(max_rx);
				form->setMaxRy(max_ry);
				form->setMaxRz(max_rz);
				form->setHasMinTx(has_min_tx);
				form->setHasMinTy(has_min_ty);
				form->setHasMinTz(has_min_tz);
				form->setHasMinSx(has_min_sx);
				form->setHasMinSy(has_min_sy);
				form->setHasMinSz(has_min_sz);
				form->setHasMinRx(has_min_rx);
				form->setHasMinRy(has_min_ry);
				form->setHasMinRz(has_min_rz);
				form->setHasMaxTx(has_max_tx);
				form->setHasMaxTy(has_max_ty);
				form->setHasMaxTz(has_max_tz);
				form->setHasMaxSx(has_max_sx);
				form->setHasMaxSy(has_max_sy);
				form->setHasMaxSz(has_max_sz);
				form->setHasMaxRx(has_max_rx);
				form->setHasMaxRy(has_max_ry);
				form->setHasMaxRz(has_max_rz);
			}
		}
	}
}