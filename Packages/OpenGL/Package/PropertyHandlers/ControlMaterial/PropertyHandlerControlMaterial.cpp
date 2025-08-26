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
	namespace opengl
	{
		CPropertyHandlerControlMaterial::CPropertyHandlerControlMaterial(IPackage *package) :
			standard::CPropertyHandlerDropDown(package, PropertyHandlerControlMaterial),
			m_pProperty{ nullptr }
		{

		}

		bool CPropertyHandlerControlMaterial::isEditable(IProperty *property)
		{
			return cast<IPropertyControlMaterial*>(property) || cast<IPropertyControlMaterialState*>(property);
		}

		IProperty *CPropertyHandlerControlMaterial::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerControlMaterial::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerControlMaterial::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyControlMaterialState *p{ cast<IPropertyControlMaterialState*>(m_pProperty) };
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
					IPropertyControlMaterial *p{ cast<IPropertyControlMaterial*>(m_pProperty) };
					IPropertyControlMaterialState *ps{ cast<IPropertyControlMaterialState*>(m_pProperty) };
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
									IMaterialControl *ctrl{ cast<IMaterialControl*>(control->getParent()->getControl(i)) };
									if (ctrl)
									{
										Add(ctrl->Name);
										if (ps)
										{
											if (!m_sState.empty() && ps->getValue(m_sState) == ctrl)
												index = getItemCount() - 1;
										}
										else if (p->getValue() == ctrl)
											index = getItemCount() - 1;
									}
								}
						}
						else if (control->getForm())
						{
							for (int i = 0; i < control->getForm()->getControlCount(); i++)
								if (control->getForm()->getControl(i) != control)
								{
									IMaterialControl *ctrl{ cast<IMaterialControl*>(control->getForm()->getControl(i)) };
									if (ctrl)
									{
										Add(ctrl->Name);
										if (ps)
										{
											if (!m_sState.empty() && ps->getValue(m_sState) == ctrl)
												index = getItemCount() - 1;
										}
										else if (p->getValue() == ctrl)
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

		bool CPropertyHandlerControlMaterial::setPropertyState(const String &value)
		{
			IPropertyControlMaterialState *p{ cast<IPropertyControlMaterialState*>(m_pProperty) };
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
									IMaterialControl *ctrl{ cast<IMaterialControl*>(control->getParent()->getControl(i)) };
									if (ctrl)
									{
										if (p->getValue(m_sState) == ctrl)
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
									IMaterialControl *ctrl{ cast<IMaterialControl*>(control->getForm()->getControl(i)) };
									if (ctrl)
									{
										if (p->getValue(m_sState) == ctrl)
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

		void CPropertyHandlerControlMaterial::NotifyOnSelect(const int index)
		{
			if (m_pProperty)
			{
				IMaterialControl *selected{ nullptr };
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
									IMaterialControl *ctrl{ cast<IMaterialControl*>(control->getParent()->getControl(i)) };
									if (ctrl)
									{
										if (idx == index)
										{
											selected = ctrl;
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
									IMaterialControl *ctrl{ cast<IMaterialControl*>(control->getForm()->getControl(i)) };
									if (ctrl)
									{
										if (idx == index)
										{
											selected = ctrl;
											break;
										}
										else
											idx++;
									}
								}
						}
					}
				}
				IPropertyControlMaterialState *ps{ cast<IPropertyControlMaterialState*>(m_pProperty) };
				bool changed;
				if (ps)
					changed = ps->setValue(m_sState, selected);
				else
					changed = cast<IPropertyControlMaterial*>(m_pProperty)->setValue(selected);
				if (changed && getListener() && cast<IPropertyHandlerListener*>(getListener()))
					cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
			}
		}
	}
}