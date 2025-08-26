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
#pragma region CTranslate
	CTranslate::CTranslate():
		m_bSorted{ true }
	{
		
	}

	void CTranslate::Sort()
	{
		if (!m_bSorted)
		{
			std::sort(m_aItems.begin(), m_aItems.end(), [](const ITEM &a, const ITEM &b) {
				if (a.Language < b.Language)
					return true;
				if (a.Category < b.Category)
					return true;
				return a.Key < b.Key;
			});
			m_bSorted = true;
		}
	}

	String CTranslate::getLanguage()
	{
		return m_sLanguage;
	}

	bool CTranslate::setLanguage(const String &value)
	{
		if (value != m_sLanguage)
		{
			m_sLanguage = value;
			if (Application)
				Application->QueryService()->SendTranslateChangeNotification();
			return true;
		}
		return false;
	}

	bool CTranslate::Add(const String &language, const String &category, const String &key, const String &value)
	{
		if (language.length() > 0 && category.length() > 0 && key.length() > 0)
		{
			m_aItems.push_back({ language, category, key, value });
			m_bSorted = false;
			return true;
		}
		return false;
	}

	bool CTranslate::Set(const String &language, const String &category, const String &key, const String &value)
	{
		if (language.length() > 0 && category.length() > 0 && key.length() > 0)
		{
			Sort();
			ITEM search{ language, category, key };
			auto pos = std::lower_bound(m_aItems.begin(), m_aItems.end(), search, [](const ITEM &a, const ITEM &b) {
				if (a.Language < b.Language)
					return true;
				if (a.Category < b.Category)
					return true;
				return a.Key < b.Key;
			});
			if (pos == m_aItems.end() || pos->Language != language || pos->Category != category || pos->Key != key)
			{
				m_aItems.push_back({ language, category, key, value });
				m_bSorted = false;
				return true;
			}
			if (pos->Value != value)
			{
				pos->Value = value;
				return true;
			}
		}
		return false;
	}

	String CTranslate::t(const String &category, const String &key)
	{
		Sort();
		ITEM search{ m_sLanguage, category, key };
		auto pos = std::lower_bound(m_aItems.begin(), m_aItems.end(), search, [](const ITEM &a, const ITEM &b) {
			if (a.Language < b.Language)
				return true;
			if (a.Category < b.Category)
				return true;
			return a.Key < b.Key;
		});
		if (pos == m_aItems.end() || pos->Language != m_sLanguage || pos->Category != category || pos->Key != key)
			return key;
		return pos->Value;
	}

	String CTranslate::t(const String &category, const String &key, const StringKeyValueArray &params)
	{
		Sort();
		ITEM search{ m_sLanguage, category, key };
		auto pos = std::lower_bound(m_aItems.begin(), m_aItems.end(), search, [](const ITEM &a, const ITEM &b) {
			if (a.Language < b.Language)
				return true;
			if (a.Category < b.Category)
				return true;
			return a.Key < b.Key;
		});
		String result;
		if (pos == m_aItems.end() || pos->Language != m_sLanguage || pos->Category != category || pos->Key != key)
			result = key;
		else
			result = pos->Value;
		ReplaceAllDirect(result, params);
		return result;
	}

	String CTranslate::KeyName(const Key key)
	{
		switch (key)
		{
		case Key::LButton: return Application->Translate->t(TranslateCategoryKeys, L"Left Mouse Button");
		case Key::RButton: return Application->Translate->t(TranslateCategoryKeys, L"Right Mouse Button");
		case Key::Cancel: return Application->Translate->t(TranslateCategoryKeys, L"Cancel");
		case Key::MButton: return Application->Translate->t(TranslateCategoryKeys, L"Middle Mouse Button");
		case Key::XButton1: return Application->Translate->t(TranslateCategoryKeys, L"XButton1");
		case Key::XButton2: return Application->Translate->t(TranslateCategoryKeys, L"XButton2");
		case Key::Backspace: return Application->Translate->t(TranslateCategoryKeys, L"Backspace");
		case Key::Tab: return Application->Translate->t(TranslateCategoryKeys, L"Tab");
		case Key::Clear: return Application->Translate->t(TranslateCategoryKeys, L"Clear");
		case Key::Return: return Application->Translate->t(TranslateCategoryKeys, L"Enter");
		case Key::Shift: return Application->Translate->t(TranslateCategoryKeys, L"Shift");
		case Key::Control: return Application->Translate->t(TranslateCategoryKeys, L"Ctrl");
		case Key::Menu: return Application->Translate->t(TranslateCategoryKeys, L"Alt");
		case Key::Pause: return Application->Translate->t(TranslateCategoryKeys, L"Pause");
		case Key::CapsLock: return Application->Translate->t(TranslateCategoryKeys, L"CapsLock");
		case Key::Kana: return Application->Translate->t(TranslateCategoryKeys, L"Kana");
		case Key::Junja: return Application->Translate->t(TranslateCategoryKeys, L"Junja");
		case Key::Final: return Application->Translate->t(TranslateCategoryKeys, L"Final");
		case Key::Hanja: return Application->Translate->t(TranslateCategoryKeys, L"Hanja");
		case Key::Escape: return Application->Translate->t(TranslateCategoryKeys, L"Esc");
		case Key::Convert: return Application->Translate->t(TranslateCategoryKeys, L"Convert");
		case Key::NonConvert: return Application->Translate->t(TranslateCategoryKeys, L"NonConvert");
		case Key::Accept: return Application->Translate->t(TranslateCategoryKeys, L"Accept");
		case Key::ModeChange: return Application->Translate->t(TranslateCategoryKeys, L"Mode Change");
		case Key::Space: return Application->Translate->t(TranslateCategoryKeys, L"Space");
		case Key::Prior: return Application->Translate->t(TranslateCategoryKeys, L"PageUp");
		case Key::Next: return Application->Translate->t(TranslateCategoryKeys, L"PageDown");
		case Key::End: return Application->Translate->t(TranslateCategoryKeys, L"End");
		case Key::Home: return Application->Translate->t(TranslateCategoryKeys, L"Home");
		case Key::Left: return Application->Translate->t(TranslateCategoryKeys, L"Left");
		case Key::Up: return Application->Translate->t(TranslateCategoryKeys, L"Up");
		case Key::Right: return Application->Translate->t(TranslateCategoryKeys, L"Right");
		case Key::Down: return Application->Translate->t(TranslateCategoryKeys, L"Down");
		case Key::Select: return Application->Translate->t(TranslateCategoryKeys, L"Select");
		case Key::Print: return Application->Translate->t(TranslateCategoryKeys, L"Print");
		case Key::Execute: return Application->Translate->t(TranslateCategoryKeys, L"Execute");
		case Key::Snapshot: return Application->Translate->t(TranslateCategoryKeys, L"PrtScn");
		case Key::Insert: return Application->Translate->t(TranslateCategoryKeys, L"Ins");
		case Key::Delete: return Application->Translate->t(TranslateCategoryKeys, L"Del");
		case Key::Help: return Application->Translate->t(TranslateCategoryKeys, L"Help");
		case Key::Key0: return Application->Translate->t(TranslateCategoryKeys, L"0");
		case Key::Key1: return Application->Translate->t(TranslateCategoryKeys, L"1");
		case Key::Key2: return Application->Translate->t(TranslateCategoryKeys, L"2");
		case Key::Key3: return Application->Translate->t(TranslateCategoryKeys, L"3");
		case Key::Key4: return Application->Translate->t(TranslateCategoryKeys, L"4");
		case Key::Key5: return Application->Translate->t(TranslateCategoryKeys, L"5");
		case Key::Key6: return Application->Translate->t(TranslateCategoryKeys, L"6");
		case Key::Key7: return Application->Translate->t(TranslateCategoryKeys, L"7");
		case Key::Key8: return Application->Translate->t(TranslateCategoryKeys, L"8");
		case Key::Key9: return Application->Translate->t(TranslateCategoryKeys, L"9");
		case Key::A: return Application->Translate->t(TranslateCategoryKeys, L"A");
		case Key::B: return Application->Translate->t(TranslateCategoryKeys, L"B");
		case Key::C: return Application->Translate->t(TranslateCategoryKeys, L"C");
		case Key::D: return Application->Translate->t(TranslateCategoryKeys, L"D");
		case Key::E: return Application->Translate->t(TranslateCategoryKeys, L"E");
		case Key::F: return Application->Translate->t(TranslateCategoryKeys, L"F");
		case Key::G: return Application->Translate->t(TranslateCategoryKeys, L"G");
		case Key::H: return Application->Translate->t(TranslateCategoryKeys, L"H");
		case Key::I: return Application->Translate->t(TranslateCategoryKeys, L"I");
		case Key::J: return Application->Translate->t(TranslateCategoryKeys, L"J");
		case Key::K: return Application->Translate->t(TranslateCategoryKeys, L"K");
		case Key::L: return Application->Translate->t(TranslateCategoryKeys, L"L");
		case Key::M: return Application->Translate->t(TranslateCategoryKeys, L"M");
		case Key::N: return Application->Translate->t(TranslateCategoryKeys, L"N");
		case Key::O: return Application->Translate->t(TranslateCategoryKeys, L"O");
		case Key::P: return Application->Translate->t(TranslateCategoryKeys, L"P");
		case Key::Q: return Application->Translate->t(TranslateCategoryKeys, L"Q");
		case Key::R: return Application->Translate->t(TranslateCategoryKeys, L"R");
		case Key::S: return Application->Translate->t(TranslateCategoryKeys, L"S");
		case Key::T: return Application->Translate->t(TranslateCategoryKeys, L"T");
		case Key::U: return Application->Translate->t(TranslateCategoryKeys, L"U");
		case Key::V: return Application->Translate->t(TranslateCategoryKeys, L"V");
		case Key::W: return Application->Translate->t(TranslateCategoryKeys, L"W");
		case Key::X: return Application->Translate->t(TranslateCategoryKeys, L"X");
		case Key::Y: return Application->Translate->t(TranslateCategoryKeys, L"Y");
		case Key::Z: return Application->Translate->t(TranslateCategoryKeys, L"Z");
		case Key::LWin: return Application->Translate->t(TranslateCategoryKeys, L"Left Win");
		case Key::RWin: return Application->Translate->t(TranslateCategoryKeys, L"Right Win");
		case Key::Apps: return Application->Translate->t(TranslateCategoryKeys, L"Apps");
		case Key::Sleep: return Application->Translate->t(TranslateCategoryKeys, L"Sleep");
		case Key::Numpad0: return Application->Translate->t(TranslateCategoryKeys, L"Num0");
		case Key::Numpad1: return Application->Translate->t(TranslateCategoryKeys, L"Num1");
		case Key::Numpad2: return Application->Translate->t(TranslateCategoryKeys, L"Num2");
		case Key::Numpad3: return Application->Translate->t(TranslateCategoryKeys, L"Num3");
		case Key::Numpad4: return Application->Translate->t(TranslateCategoryKeys, L"Num4");
		case Key::Numpad5: return Application->Translate->t(TranslateCategoryKeys, L"Num5");
		case Key::Numpad6: return Application->Translate->t(TranslateCategoryKeys, L"Num6");
		case Key::Numpad7: return Application->Translate->t(TranslateCategoryKeys, L"Num7");
		case Key::Numpad8: return Application->Translate->t(TranslateCategoryKeys, L"Num8");
		case Key::Numpad9: return Application->Translate->t(TranslateCategoryKeys, L"Num9");
		case Key::Multiply: return Application->Translate->t(TranslateCategoryKeys, L"Num*");
		case Key::Add: return Application->Translate->t(TranslateCategoryKeys, L"Num+");
		case Key::Separator: return Application->Translate->t(TranslateCategoryKeys, L"Num Enter");
		case Key::Subtract: return Application->Translate->t(TranslateCategoryKeys, L"Num-");
		case Key::Decimal: return Application->Translate->t(TranslateCategoryKeys, L"Num.");
		case Key::Divide: return Application->Translate->t(TranslateCategoryKeys, L"Num/");
		case Key::F1: return Application->Translate->t(TranslateCategoryKeys, L"F1");
		case Key::F2: return Application->Translate->t(TranslateCategoryKeys, L"F2");
		case Key::F3: return Application->Translate->t(TranslateCategoryKeys, L"F3");
		case Key::F4: return Application->Translate->t(TranslateCategoryKeys, L"F4");
		case Key::F5: return Application->Translate->t(TranslateCategoryKeys, L"F5");
		case Key::F6: return Application->Translate->t(TranslateCategoryKeys, L"F6");
		case Key::F7: return Application->Translate->t(TranslateCategoryKeys, L"F7");
		case Key::F8: return Application->Translate->t(TranslateCategoryKeys, L"F8");
		case Key::F9: return Application->Translate->t(TranslateCategoryKeys, L"F9");
		case Key::F10: return Application->Translate->t(TranslateCategoryKeys, L"F10");
		case Key::F11: return Application->Translate->t(TranslateCategoryKeys, L"F11");
		case Key::F12: return Application->Translate->t(TranslateCategoryKeys, L"F12");
		case Key::F13: return Application->Translate->t(TranslateCategoryKeys, L"F13");
		case Key::F14: return Application->Translate->t(TranslateCategoryKeys, L"F14");
		case Key::F15: return Application->Translate->t(TranslateCategoryKeys, L"F15");
		case Key::F16: return Application->Translate->t(TranslateCategoryKeys, L"F16");
		case Key::F17: return Application->Translate->t(TranslateCategoryKeys, L"F17");
		case Key::F18: return Application->Translate->t(TranslateCategoryKeys, L"F18");
		case Key::F19: return Application->Translate->t(TranslateCategoryKeys, L"F19");
		case Key::F20: return Application->Translate->t(TranslateCategoryKeys, L"F20");
		case Key::F21: return Application->Translate->t(TranslateCategoryKeys, L"F21");
		case Key::F22: return Application->Translate->t(TranslateCategoryKeys, L"F22");
		case Key::F23: return Application->Translate->t(TranslateCategoryKeys, L"F23");
		case Key::F24: return Application->Translate->t(TranslateCategoryKeys, L"F24");
		case Key::NumLock: return Application->Translate->t(TranslateCategoryKeys, L"NumLock");
		case Key::ScrollLock: return Application->Translate->t(TranslateCategoryKeys, L"ScrollLock");
		case Key::LShift: return Application->Translate->t(TranslateCategoryKeys, L"Left Shift");
		case Key::RShift: return Application->Translate->t(TranslateCategoryKeys, L"Right Shift");
		case Key::LControl: return Application->Translate->t(TranslateCategoryKeys, L"Left Ctrl");
		case Key::RControl: return Application->Translate->t(TranslateCategoryKeys, L"Right Ctrl");
		case Key::LMenu: return Application->Translate->t(TranslateCategoryKeys, L"Left Alt");
		case Key::RMenu: return Application->Translate->t(TranslateCategoryKeys, L"Right Alt");
		case Key::BrowserBack: return Application->Translate->t(TranslateCategoryKeys, L"Browser Back");
		case Key::BrowserForward: return Application->Translate->t(TranslateCategoryKeys, L"Browser Forward");
		case Key::BrowserRefresh: return Application->Translate->t(TranslateCategoryKeys, L"Browser Refresh");
		case Key::BrowserStop: return Application->Translate->t(TranslateCategoryKeys, L"Browser Stop");
		case Key::BrowserSearch: return Application->Translate->t(TranslateCategoryKeys, L"Browser Search");
		case Key::BrowserFavorites: return Application->Translate->t(TranslateCategoryKeys, L"Browser Favorites");
		case Key::BrowserHome: return Application->Translate->t(TranslateCategoryKeys, L"Browser Home");
		case Key::VolumeMute: return Application->Translate->t(TranslateCategoryKeys, L"Volume Mute");
		case Key::VolumeDown: return Application->Translate->t(TranslateCategoryKeys, L"Volume Down");
		case Key::VolumeUp: return Application->Translate->t(TranslateCategoryKeys, L"Volume Up");
		case Key::MediaNextTrack: return Application->Translate->t(TranslateCategoryKeys, L"Next Media Track");
		case Key::MediaPrevTrack: return Application->Translate->t(TranslateCategoryKeys, L"Prev Media Track");
		case Key::MediaStop: return Application->Translate->t(TranslateCategoryKeys, L"Media Stop");
		case Key::MediaPlayPause: return Application->Translate->t(TranslateCategoryKeys, L"Media Play/Pause");
		case Key::LaunchMail: return Application->Translate->t(TranslateCategoryKeys, L"Launch Mail");
		case Key::LaunchMediaSelect: return Application->Translate->t(TranslateCategoryKeys, L"Launch Media Select");
		case Key::LaunchApp1: return Application->Translate->t(TranslateCategoryKeys, L"Launch App1");
		case Key::LaunchApp2: return Application->Translate->t(TranslateCategoryKeys, L"Launch App2");
		case Key::Semicolon: return Application->Translate->t(TranslateCategoryKeys, L";");
		case Key::OemPlus: return Application->Translate->t(TranslateCategoryKeys, L"+");
		case Key::OemComma: return Application->Translate->t(TranslateCategoryKeys, L",");
		case Key::OemMinus: return Application->Translate->t(TranslateCategoryKeys, L"-");
		case Key::OemPeriod: return Application->Translate->t(TranslateCategoryKeys, L".");
		case Key::Slash: return Application->Translate->t(TranslateCategoryKeys, L"/");
		case Key::Tilde: return Application->Translate->t(TranslateCategoryKeys, L"~");
		case Key::LeftBracket: return Application->Translate->t(TranslateCategoryKeys, L"[");
		case Key::BackSlash: return Application->Translate->t(TranslateCategoryKeys, L"\\");
		case Key::RightBracket: return Application->Translate->t(TranslateCategoryKeys, L"]");
		case Key::Apostrophe: return Application->Translate->t(TranslateCategoryKeys, L"'");
		case Key::Oem8: return Application->Translate->t(TranslateCategoryKeys, L"Oem8");
		case Key::Oem102: return Application->Translate->t(TranslateCategoryKeys, L"Oem102");
		case Key::ProcessKey: return Application->Translate->t(TranslateCategoryKeys, L"Process");
		case Key::Packet: return Application->Translate->t(TranslateCategoryKeys, L"Packet");
		case Key::Attn: return Application->Translate->t(TranslateCategoryKeys, L"Attn");
		case Key::CrSel: return Application->Translate->t(TranslateCategoryKeys, L"CrSel");
		case Key::ExSel: return Application->Translate->t(TranslateCategoryKeys, L"ExSel");
		case Key::ErEOF: return Application->Translate->t(TranslateCategoryKeys, L"ErEOF");
		case Key::Play: return Application->Translate->t(TranslateCategoryKeys, L"Play");
		case Key::Zoom: return Application->Translate->t(TranslateCategoryKeys, L"Zoom");
		case Key::PA1: return Application->Translate->t(TranslateCategoryKeys, L"PA1");
		case Key::OemClear: return Application->Translate->t(TranslateCategoryKeys, L"OemClear");
		default:
			break;
		}
		return L"";
	}

	String CTranslate::Hotkey(const nitisa::Hotkey &hotkey)
	{
		String result;
		if (hotkey.Ctrl)
			result = KeyName(Key::Control);
		if (hotkey.Alt)
		{
			if (result.length() > 0)
				result += KeyName(Key::OemPlus);
			result += KeyName(Key::Menu);
		}
		if (hotkey.Shift)
		{
			if (result.length() > 0)
				result += KeyName(Key::OemPlus);
			result += KeyName(Key::Shift);
		}
		if (result.length() > 0)
			result += KeyName(Key::OemPlus);
		result += KeyName(hotkey.Key);
		return result;
	}

	String CTranslate::Month(const String &month)
	{
		return Application->Translate->t(TranslateCategoryCalendar, month);
	}

	String CTranslate::Day(const String &day)
	{
		return Application->Translate->t(TranslateCategoryCalendar, day);
	}
#pragma endregion
}