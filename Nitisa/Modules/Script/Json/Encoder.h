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
#include "../Core/Variable.h"
#include "../Lexics/Json/Lexic.h"

namespace nitisa
{
	class IErrorListener;

	namespace script
	{
		class IProgressListener;

		namespace json
		{
			class Encoder final
			{
			private:
				Encoder() = delete;
				~Encoder() = delete;
				Encoder(const Encoder &other) = delete;
				Encoder(Encoder &&other) = delete;
				Encoder &operator=(const Encoder &other) = delete;
				Encoder &operator=(Encoder &&other) = delete;
			private:
				static CLexic m_cLexic;

				static String Escape(const String &value);
				static bool IsIdentifier(const String &name);
				static String EncodeObject(const Variable &source, const bool compact, IProgressListener *progress_listener, const String &shift, const size_t total, size_t &counter, bool &abort);
				static String EncodeArray(const Variable &source, const bool compact, IProgressListener *progress_listener, const String &shift, const size_t total, size_t &counter, bool &abort);
				static String EncodeObject(const Variant &source, const bool compact, IProgressListener *progress_listener, const String &shift, const size_t total, size_t &counter, bool &abort);
				static String EncodeArray(const Variant &source, const bool compact, IProgressListener *progress_listener, const String &shift, const size_t total, size_t &counter, bool &abort);
			public:
				static String Encode(const Variable &source, const bool compact = true, IProgressListener *progress_listener = nullptr);
				static String Encode(const Variant &source, const bool compact = true, IProgressListener *progress_listener = nullptr);
			};
		}
	}
}