// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"
#include "../Core/Token.h"
#include "Entity.h"

namespace nitisa
{
	class IErrorListener;

	namespace script
	{
		class IProgressListener;
		class ITokenizer;

		namespace xml
		{
			class Decoder final
			{
			private:
				static bool m_bAbort;
				static Token m_sToken;
				static Token *m_pToken;
				static size_t m_iIndex;
				static size_t m_iLength;
				static ITokenizer *m_pTokenizer;
				static IErrorListener *m_pErrorListener;
				static IProgressListener *m_pProgressListener;

				static const StringArray SNOperators;

				static Token *SkipSN(const bool next = false);
				static bool DecodeProlog(Entity &target);
				static bool DecodeDoctype(Entity &target);
				static bool DecodeElement(Entity &target);
				static bool DecodeAttribute(Entity &target);
				static bool SkipDoctype(String &value);
				static bool DecodeElementClose(const String &name);
				static Token *Next();
			public:
				static bool Decode(const String &source, Entity &target, IErrorListener *error_listener = nullptr, IProgressListener *progress_listener = nullptr);
			};
		}
	}
}