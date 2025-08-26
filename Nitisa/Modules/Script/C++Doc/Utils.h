// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"
#include "../../../Interfaces/IDb.h"
#include "../Core/Tokens.h"
#include "../Tokenizers/C++/Tokenizer.h"
#include "List.h"

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			void Tokenize(cpp::CTokenizer &tokenizer, const String &source, Tokens &tokens);
			List *MakeList(Tokens &tokens, List **tail);
			bool isSLComment(List &list);
			bool isMLComment(List &list);
			bool isComment(List &list);
			bool isSpaces(List &list);
			bool isNewLines(List &list);
			List *Next(List &list, const bool skip_spaces, const bool skip_ml_comments, const bool skip_sl_comments, const bool skip_new_lines);
			List *Next(List &list, List &end, const bool skip_spaces, const bool skip_ml_comments, const bool skip_sl_comments, const bool skip_new_lines); // If beyond "end" return nullptr
			List *Prev(List &list, const bool skip_spaces, const bool skip_ml_comments, const bool skip_sl_comments, const bool skip_new_lines);
			StringKeyValueArray E(const String &key1, const String &val1);
			StringKeyValueArray E(const String &key1, const String &val1, const String &key2, const String &val2);
			StringKeyValueArray E(const String &key1, const String &val1, const String &key2, const String &val2, const String &key3, const String &val3);
			String DumpTokens(List &list, const String &before, const String &after, const size_t before_count, const size_t after_count);
			IDb::Migrations GetMigrations();
		}
	}
}