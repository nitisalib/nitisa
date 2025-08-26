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
		CPropertyHandlerFont::CPropertyHandlerFont(IPackage *package) :
			CPropertyHandlerModal(package, PropertyHandlerFont),
			m_pProperty{ nullptr }
		{

		}

		bool CPropertyHandlerFont::isEditable(IProperty *property)
		{
			return cast<IPropertyFont*>(property) || cast<IPropertyFontState*>(property);
		}

		IProperty *CPropertyHandlerFont::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerFont::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerFont::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyFontState *p{ cast<IPropertyFontState*>(m_pProperty) };
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
				return true;
			}
			return false;
		}

		bool CPropertyHandlerFont::setPropertyState(const String &value)
		{
			IPropertyFontState *p{ cast<IPropertyFontState*>(m_pProperty) };
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
					return true;
				}
			}
			return false;
		}

		void CPropertyHandlerFont::NotifyOnActivateModal()
		{
			String name{ L"Tahoma" };
			int height{ -11 };
			FontWeight weight{ FontWeight::Normal };
			bool italic{ false }, underline{ false }, strikeout{ false };
			Color color{ 0, 0, 0, 255 };
			IFont *f{ nullptr };
			IPropertyFontState *ps{ cast<IPropertyFontState*>(m_pProperty) };
			IPropertyFont *p{ cast<IPropertyFont*>(m_pProperty) };
			if (ps)
				f = ps->getValue(m_sState);
			else
				if (p)
					f = p->getValue();
				else
					return;
			if (f)
			{
				name = f->FontName;
				height = f->Height;
				weight = f->Weight;
				italic = f->Italic;
				underline = f->Underline;
				strikeout = f->StrikeOut;
				color = f->Color;
			}
			if (Application->Dialogs->Font(name, height, weight, italic, underline, strikeout, color))
			{
				CFont font;
				font.setFontName(name);
				font.setHeight(height);
				font.setWeight(weight);
				font.setItalic(italic);
				font.setUnderline(underline);
				font.setStrikeOut(strikeout);
				font.setColor(color);
				if (ps)
					ps->setValue(m_sState, &font);
				else
					p->setValue(&font);
				if (getListener())
					cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
			}
		}
	}
}