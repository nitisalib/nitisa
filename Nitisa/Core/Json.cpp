// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	String json_encode(const Variant &source, const bool compact, script::IProgressListener *progress_listener)
	{
		return script::json::Encoder::Encode(source, compact, progress_listener);
	}

	String json_encode(const script::Variable &source, const bool compact, script::IProgressListener *progress_listener)
	{
		return script::json::Encoder::Encode(source, compact, progress_listener);
	}

	bool json_decode(const String &source, Variant &target, IErrorListener *error_listener, script::IProgressListener *progress_listener)
	{
		return script::json::Decoder::Decode(source, target, error_listener, progress_listener);
	}

	bool json_decode(const String &source, script::Variable &target, IErrorListener *error_listener, script::IProgressListener *progress_listener)
	{
		return script::json::Decoder::Decode(source, target, error_listener, progress_listener);
	}
}