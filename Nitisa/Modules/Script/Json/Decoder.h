// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"
#include "../../../Core/Variant.h"
#include "../Core/Token.h"
#include "../Core/Variable.h"

namespace nitisa
{
	class IErrorListener;

	namespace script
	{
		class IProgressListener;
		class ITokenizer;

		namespace json
		{
			class Decoder final
			{
			private:
				Decoder() = delete;
				~Decoder() = delete;
				Decoder(const Decoder &other) = delete;
				Decoder(Decoder &&other) = delete;
				Decoder &operator=(const Decoder &other) = delete;
				Decoder &operator=(Decoder &&other) = delete;
			private:
				static bool m_bAbort;
				static bool m_bFailed;
				static Token m_sToken;
				static Token *m_pToken;
				static size_t m_iIndex;
				static size_t m_iLength;
				static ITokenizer *m_pTokenizer;
				static IErrorListener *m_pErrorListener;
				static IProgressListener *m_pProgressListener;

				static bool DecodeObject(Variable &target, const bool allow_comma);
				static bool DecodeArray(Variable &target, const bool allow_comma);
				static bool DecodeMember(Variable &target);

				static bool DecodeObject(Variant &target, const bool allow_comma);
				static bool DecodeArray(Variant &target, const bool allow_comma);
				static bool DecodeMember(Variant &target);

				static Token *Next();
				static String Unescape(const String &value);
			public:
				static bool Decode(const String &source, Variable &target, IErrorListener *error_listener = nullptr, IProgressListener *progress_listener = nullptr);
				static bool Decode(const String &source, Variant &target, IErrorListener *error_listener = nullptr, IProgressListener *progress_listener = nullptr);
			};
		}
	}
}