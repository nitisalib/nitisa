// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include <map>

namespace nitisa
{
	class ITranslate
	{
	protected:
		ITranslate() = default;
		~ITranslate() = default;
		ITranslate(const ITranslate &other) = delete;
		ITranslate(ITranslate &&other) = delete;
		ITranslate &operator=(const ITranslate &other) = delete;
		ITranslate &operator=(ITranslate &&other) = delete;
	public:
		virtual String getLanguage() = 0; // Return current active language name

		virtual bool setLanguage(const String &value) = 0; // Activate language by name and send translation change notifications to every entity(via IApplicationService::SendTranslateChangeNotification method)

		virtual String t(const String &category, const String &key) = 0; // Translate specified key located in specified category with current active language
		virtual String t(const String &category, const String &key, const StringKeyValueArray &params) = 0; // Translate specified key located in specified category with current active language. Replace all occurances of keys in params with corresponding values

		virtual bool Add(const String &language, const String &category, const String &key, const String &value) = 0; // Add new translation key
		virtual bool Set(const String &language, const String &category, const String &key, const String &value) = 0; // Add new or replace existing translation key
	};
}