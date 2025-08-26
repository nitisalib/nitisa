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
		CPropertyHotkeyList::CPropertyHotkeyList(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetCount get_count, FGetHotkey get_hotkey, FAdd add, FDelete del, FClear clear) :
			CProperty(list, parent, name, PropertyHandlerHotkeyList, skip, false),
			m_fGetCount{ get_count },
			m_fGetHotkey{ get_hotkey },
			m_fAdd{ add },
			m_fDelete{ del },
			m_fClear{ clear },
			m_bChanged{ false }
		{
			AddHeaderFile(L"Nitisa/Core/Key.h");
		}
	#pragma endregion

	#pragma region IProperty getters
		String CPropertyHotkeyList::getPreview()
		{
			return L"[Hotkey(" + ToString(getCount()) + L")]";
		}

		String CPropertyHotkeyList::getPreview(const String &state)
		{
			return L"";
		}

		bool CPropertyHotkeyList::isChanged()
		{
			return m_bChanged || getCount() > 0;
		}
	#pragma endregion

	#pragma region IProperty setters
		IProperty *CPropertyHotkeyList::setChanged(const bool value)
		{
			m_bChanged = value;
			return this;
		}
	#pragma endregion

	#pragma region IProperty methods
		bool CPropertyHotkeyList::Copy(IProperty *dest)
		{
			IPropertyHotkeyList *d{ cast<IPropertyHotkeyList*>(dest) };
			if (d)
			{
				d->Clear();
				for (int i = 0; getCount(); i++)
					d->Add(getHotkey(i));
				return true;
			}
			return false;
		}

		void CPropertyHotkeyList::Save(Variant &dest)
		{
			dest.Reset();
			for (int i = 0; i < getCount(); i++)
				dest.push_back(ToVariant(getHotkey(i)));
		}

		void CPropertyHotkeyList::Load(const Variant &src)
		{
			Clear();
			for (int i = 0; i < (int)src.size(); i++)
			{
				Hotkey h;
				FromVariant(src.get(i), h);
				Add(h);
			}
		}

		void CPropertyHotkeyList::Export(std::wofstream &f, const String &shift, const String &control)
		{
			for (int i = 0; i < getCount(); i++)
			{
				Hotkey h{ getHotkey(i) };
				if (control.empty())
					f << shift << L"AddHotkey(" << KeyToString(h.Key) << L", " << ToString(h.Ctrl) << L", " << ToString(h.Alt) << L", " << ToString(h.Shift) << L", "
					<< ToString(h.Down) << L");" << std::endl;
				else
					f << shift << control << L"->AddHotkey(" << KeyToString(h.Key) << L", " << ToString(h.Ctrl) << L", " << ToString(h.Alt) << L", " << ToString(h.Shift) << L", "
					<< ToString(h.Down) << L");" << std::endl;
			}
		}
	#pragma endregion

	#pragma region IPropertyHotkeyList getters
		int CPropertyHotkeyList::getCount()
		{
			return m_fGetCount(m_pParent);
		}

		Hotkey CPropertyHotkeyList::getHotkey(const int index)
		{
			return m_fGetHotkey(m_pParent, index);
		}
	#pragma endregion

	#pragma region IPropertyHotkeyList methods
		int CPropertyHotkeyList::Add(Hotkey value)
		{
			return m_fAdd(m_pParent, value);
		}

		bool CPropertyHotkeyList::Delete(const int index)
		{
			return m_fDelete(m_pParent, index);
		}

		bool CPropertyHotkeyList::Clear()
		{
			return m_fClear(m_pParent);
		}
	#pragma endregion
	}
}