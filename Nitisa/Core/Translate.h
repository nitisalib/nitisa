// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/ITranslate.h"
#include "Hotkey.h"
#include "Key.h"
#include "Strings.h"
#include <vector>

namespace nitisa
{
	class CTranslate :public virtual ITranslate
	{
	private:
		struct ITEM
		{
			String Language;
			String Category;
			String Key;
			String Value;
		};

		String m_sLanguage;
		std::vector<ITEM> m_aItems;
		bool m_bSorted;

		void Sort();
	public:
		String getLanguage() override;

		bool setLanguage(const String &value) override;

		String t(const String &category, const String &key) override;
		String t(const String &category, const String &key, const StringKeyValueArray &params) override;

		bool Add(const String &language, const String &category, const String &key, const String &value) override;
		bool Set(const String &language, const String &category, const String &key, const String &value) override;

		CTranslate();

		static String KeyName(const Key key);
		static String Hotkey(const nitisa::Hotkey &hotkey);
		static String Month(const String &month);
		static String Day(const String &day);
	};
}