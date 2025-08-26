// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Component.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Modules/Script/Xml/Entity.h"
#include "../ISimpleXML.h"
#include <vector>

namespace nitisa
{
	class IErrorListener;
	class IForm;

	namespace standard
	{
		class CSimpleXML :public virtual ISimpleXML, public CComponent
		{
		private:
			script::xml::Entity m_cEntity;
		public:
			String getVersion() override;
			String getEncoding() override;
			String getDoctype() override;
			script::xml::Entity &getRootNode() override;

			bool setVersion(const String &value) override;
			bool setEncoding(const String &value) override;
			bool setDoctype(const String &value) override;

			String ToString(const bool compact) override;
			bool Save(const String &filename, const bool compact) override;
			bool LoadFromFile(const String &filename, IErrorListener *error_listener) override;
			bool LoadFromString(const String &value, IErrorListener *error_listener) override;

			CSimpleXML();
			CSimpleXML(IForm *parent);
		};
	}
}