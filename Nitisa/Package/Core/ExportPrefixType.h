// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	enum class ExportPrefixType // Export prefix types
	{
		None, // No prefix(only state name will be used, like stDisabled)
		Parent, // Parent class name(like CButton::stDisabled)
		Namespace, // Namespace only(like standard::stDisabled)
		NamespaceParent // Namespace and parent class name(like standard::CButton::stDisabled)
	};
}