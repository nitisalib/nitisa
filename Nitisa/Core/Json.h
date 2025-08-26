// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Modules/Script/Core/Variable.h"
#include "Strings.h"
#include "Variant.h"

namespace nitisa
{
	class IErrorListener;

	namespace script
	{
		class IProgressListener;
	}

	String json_encode(const Variant &source, const bool compact = false, script::IProgressListener *progress_listener = nullptr);
	String json_encode(const script::Variable &source, const bool compact = false, script::IProgressListener *progress_listener = nullptr);
	bool json_decode(const String &source, Variant &target, IErrorListener *error_listener = nullptr, script::IProgressListener *progress_listener = nullptr);
	bool json_decode(const String &source, script::Variable &target, IErrorListener *error_listener = nullptr, script::IProgressListener *progress_listener = nullptr);
}