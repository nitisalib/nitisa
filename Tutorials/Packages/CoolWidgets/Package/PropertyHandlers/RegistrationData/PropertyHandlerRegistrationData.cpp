#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
		CPropertyHandlerRegistrationData::CPropertyHandlerRegistrationData(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerRegistrationData),
			m_pProperty{ nullptr }
		{

		}

		bool CPropertyHandlerRegistrationData::isEditable(IProperty *property)
		{
			return cast<IPropertyRegistrationData*>(property) || cast<IPropertyRegistrationDataState*>(property);
		}

		IProperty *CPropertyHandlerRegistrationData::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerRegistrationData::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerRegistrationData::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyRegistrationDataState *p{ cast<IPropertyRegistrationDataState*>(m_pProperty) };
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
					IPropertyRegistrationData *p{ cast<IPropertyRegistrationData*>(m_pProperty) };
					IPropertyRegistrationDataState *ps{ cast<IPropertyRegistrationDataState*>(m_pProperty) };
					if (ps)
						setFormData(ps->getValue(m_sState));
					else
						setFormData(p->getValue());
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerRegistrationData::setPropertyState(const String &value)
		{
			IPropertyRegistrationDataState *p{ cast<IPropertyRegistrationDataState*>(m_pProperty) };
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
					setFormData(p->getValue(m_sState));
					return true;
				}
			}
			return false;
		}

		IFormRegistrationData *CPropertyHandlerRegistrationData::getForm()
		{
			if (getPackage() && getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
			{
				IPackageForm *pf{ getPackage()->getForm(CFormRegistrationData::ClassName) };
				if (pf)
				{
					IForm *f{ pf->getInstance() };
					if (!f)
						f = pf->Create(getControl()->getForm()->QueryService()->getWindow()->CreateInstance(), getControl()->getForm()->getRenderer()->CreateInstance());
					return cast<IFormRegistrationData*>(f);
				}
			}
			return nullptr;
		}

		void CPropertyHandlerRegistrationData::setFormData(const IRegistration::RegistrationData &value)
		{
			IFormRegistrationData *form{ getForm() };
			if (form)
				form->setValue(value);
		}

		void CPropertyHandlerRegistrationData::NotifyOnActivateModal()
		{
			
			IFormRegistrationData *form{ getForm() };
			if (form)
			{
				IPropertyRegistrationDataState *ps{ cast<IPropertyRegistrationDataState*>(m_pProperty) };
				if (ps)
					setFormData(ps->getValue(m_sState));
				else
					setFormData(cast<IPropertyRegistrationData*>(m_pProperty)->getValue());
				cast<IForm*>(form)->OnSetFocus = [](IForm *sender) {
					sender->OnSetFocus = nullptr;
					cast<IFormRegistrationData*>(sender)->ActivateFirstEnabledInput();
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
						IPropertyRegistrationData *p{ cast<IPropertyRegistrationData*>(m_pProperty) };
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
}