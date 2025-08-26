// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"
#include "Entity.h"

namespace nitisa
{
	class IErrorListener;

	namespace script
	{
		class IProgressListener;

		namespace xml
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
				static String EncodeArray(const Entity &source, const bool compact, IProgressListener *progress_listener, const String &shift, const size_t total, size_t &counter, bool &abort);
				static String EncodeAttributes(const Entity &source);
				static String EncodeValue(const Entity &source);
			public:
				static String Encode(const Entity &source, const bool compact = true, IProgressListener *progress_listener = nullptr);
			};
		}
	}
}