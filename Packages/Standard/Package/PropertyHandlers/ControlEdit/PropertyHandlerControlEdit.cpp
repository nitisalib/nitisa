// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
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
		CPropertyHandlerControlEdit::CPropertyHandlerControlEdit(IPackage *package) :
			CPropertyHandlerDropDown(package, PropertyHandlerControlEdit),
			m_pProperty{ nullptr }
		{

		}

		bool CPropertyHandlerControlEdit::isEditable(IProperty *property)
		{
			return cast<IPropertyControlEdit*>(property) || cast<IPropertyControlEditState*>(property);
		}

		IProperty *CPropertyHandlerControlEdit::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerControlEdit::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerControlEdit::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyControlEditState *p{ cast<IPropertyControlEditState*>(m_pProperty) };
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
					IPropertyControlEdit *p{ cast<IPropertyControlEdit*>(m_pProperty) };
					IPropertyControlEditState *ps{ cast<IPropertyControlEditState*>(m_pProperty) };
					DeleteItems();
					IControl *control{ cast<IControl*>(m_pProperty->Parent) };
					if (control)
					{
						Add(L"(Empty)");
						int index{ 0 };
						if (control->getParent())
						{
							for (int i = 0; i < control->getParent()->getControlCount(); i++)
								if (control->getParent()->getControl(i) != control)
								{
									IEdit *edit{ cast<IEdit*>(control->getParent()->getControl(i)) };
									if (edit)
									{
										Add(edit->Name);
										if (ps)
										{
											if (!m_sState.empty() && ps->getValue(m_sState) == edit)
												index = getItemCount() - 1;
										}
										else if (p->getValue() == edit)
											index = getItemCount() - 1;
									}
								}
						}
						else if (control->getForm())
						{
							for (int i = 0; i < control->getForm()->getControlCount(); i++)
								if (control->getForm()->getControl(i) != control)
								{
									IEdit *edit{ cast<IEdit*>(control->getForm()->getControl(i)) };
									if (edit)
									{
										Add(edit->Name);
										if (ps)
										{
											if (!m_sState.empty() && ps->getValue(m_sState) == edit)
												index = getItemCount() - 1;
										}
										else if (p->getValue() == edit)
											index = getItemCount() - 1;
									}
								}
						}
						setActiveIndex(index);
					}
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerControlEdit::setPropertyState(const String &value)
		{
			IPropertyControlEditState *p{ cast<IPropertyControlEditState*>(m_pProperty) };
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
					int index{ 0 };
					IControl *control{ cast<IControl*>(m_pProperty->Parent) };
					if (control)
					{
						if (control->getParent())
						{
							int idx{ 0 };
							for (int i = 0; i < control->getParent()->getControlCount(); i++)
								if (control->getParent()->getControl(i) != control)
								{
									IEdit *edit{ cast<IEdit*>(control->getParent()->getControl(i)) };
									if (edit)
									{
										if (p->getValue(m_sState) == edit)
										{
											index = idx;
											break;
										}
										else
											idx++;
									}
								}
						}
						else if (control->getForm())
						{
							int idx{ 0 };
							for (int i = 0; i < control->getForm()->getControlCount(); i++)
								if (control->getForm()->getControl(i) != control)
								{
									IEdit *edit{ cast<IEdit*>(control->getForm()->getControl(i)) };
									if (edit)
									{
										if (p->getValue(m_sState) == edit)
										{
											index = idx;
											break;
										}
										else
											idx++;
									}
								}
						}
					}
					setActiveIndex(index);
					return true;
				}
			}
			return false;
		}

		void CPropertyHandlerControlEdit::NotifyOnSelect(const int index)
		{
			if (m_pProperty)
			{
				IEdit *selected{ nullptr };
				if (index > 0)
				{
					IControl *control{ cast<IControl*>(m_pProperty->Parent) };
					if (control)
					{
						if (control->getParent())
						{
							int idx{ 1 };
							for (int i = 0; i < control->getParent()->getControlCount(); i++)
								if (control->getParent()->getControl(i) != control)
								{
									IEdit *edit{ cast<IEdit*>(control->getParent()->getControl(i)) };
									if (edit)
									{
										if (idx == index)
										{
											selected = edit;
											break;
										}
										else
											idx++;
									}
								}
						}
						else if (control->getForm())
						{
							int idx{ 1 };
							for (int i = 0; i < control->getForm()->getControlCount(); i++)
								if (control->getForm()->getControl(i) != control)
								{
									IEdit *edit{ cast<IEdit*>(control->getForm()->getControl(i)) };
									if (edit)
									{
										if (idx == index)
										{
											selected = edit;
											break;
										}
										else
											idx++;
									}
								}
						}
					}
				}
				IPropertyControlEditState *ps{ cast<IPropertyControlEditState*>(m_pProperty) };
				bool changed;
				if (ps)
					changed = ps->setValue(m_sState, selected);
				else
					changed = cast<IPropertyControlEdit*>(m_pProperty)->setValue(selected);
				if (changed && getListener() && cast<IPropertyHandlerListener*>(getListener()))
					cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
			}
		}
	}
}