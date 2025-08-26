// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IComponent.h"
#include "Nitisa/Modules/Script/Xml/Entity.h"

namespace nitisa
{
	class IErrorListener;

	namespace standard
	{
		class ISimpleXML :public virtual IComponent
		{
		protected:
			ISimpleXML() = default;
			~ISimpleXML() = default;
			ISimpleXML(const ISimpleXML &other) = delete;
			ISimpleXML(ISimpleXML &&other) = delete;
			ISimpleXML &operator=(const ISimpleXML &other) = delete;
			ISimpleXML &operator=(ISimpleXML &&other) = delete;
		public:
			virtual String getVersion() = 0; // Return version
			virtual String getEncoding() = 0; // Return encoding
			virtual String getDoctype() = 0; // Return doc-type data
			virtual script::xml::Entity &getRootNode() = 0; // Return root node which may contain prolog(s), doc-type and root element

			virtual bool setVersion(const String &value) = 0; // Set version
			virtual bool setEncoding(const String &value) = 0; // Set encoding
			virtual bool setDoctype(const String &value) = 0; // Set doc-type data. Space should be the first character. Empty value removes doc-type

			virtual String ToString(const bool compact) = 0; // Convert to string, with or without nice (human readable) formatting
			virtual bool Save(const String &filename, const bool compact) = 0; // Save to file, with or without nice (human readable) formatting
			virtual bool LoadFromFile(const String &filename, IErrorListener *error_listener) = 0; // Load XML from file
			virtual bool LoadFromString(const String &value, IErrorListener *error_listener) = 0; // Load XML from string
		};
	}
}