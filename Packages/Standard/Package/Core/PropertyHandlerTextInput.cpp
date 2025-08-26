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
	#pragma region Constructor & destructor
		CPropertyHandlerTextInput::CPropertyHandlerTextInput(IPackage *package, const String &name) :
			CBuiltInTextInput(),
			m_pControl{ nullptr },
			m_pPackage{ package },
			m_pListener{ nullptr }
		{
			m_sName = name;
			m_pTextInputListener = new CPropertyHandlerTextInputListener(this);
			CBuiltInTextInput::setListener(m_pTextInputListener);
		}

		CPropertyHandlerTextInput::~CPropertyHandlerTextInput()
		{
			CBuiltInTextInput::setListener(nullptr);
			delete m_pTextInputListener;
		}
	#pragma endregion

	#pragma region IBuiltInControl getters
		IControl *CPropertyHandlerTextInput::getControl()
		{
			return m_pControl;
		}

		IPackage *CPropertyHandlerTextInput::getPackage()
		{
			return m_pPackage;
		}

		IBuiltInControlListener *CPropertyHandlerTextInput::getListener()
		{
			return m_pListener;
		}
	#pragma endregion

	#pragma region IBuiltInControl setters
		bool CPropertyHandlerTextInput::setControl(IControl *value)
		{
			if (value != m_pControl)
			{
				m_pControl = value;
				return true;
			}
			return false;
		}

		void CPropertyHandlerTextInput::setListener(IBuiltInControlListener *value)
		{
			m_pListener = value;
		}

		bool CPropertyHandlerTextInput::setFocused(const bool value)
		{
			if (CBuiltInTextInput::setFocused(value))
			{
				if (!isFocused())
					UpdatePropertyFromText();
				else
					setSelection({ 0, (int)getText().length() });
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		bool CPropertyHandlerTextInput::NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
		{
			if (!ctrl && !alt && !shift)
				switch (key)
				{
				case Key::Escape:
					UpdateTextFromProperty();
					setSelection({ 0, (int)getText().length() });
					return true;
				case Key::Return:
				case Key::Separator:
					UpdatePropertyFromText();
					setSelection({ 0, (int)getText().length() });
					return true;
				default:
					break;
				}
			return CBuiltInTextInput::NotifyOnKeyDown(key, ctrl, alt, shift, numlock);
		}
	#pragma endregion
	}
}