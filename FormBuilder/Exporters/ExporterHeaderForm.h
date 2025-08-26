// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../Core/Types.h"
#include "BaseExporter.h"
#include <fstream>

namespace nitisa
{
	class IControl;

	namespace fb
	{
		class CComponentList;
		class CControlList;

		class CExporterHeaderForm :public CBaseExporter
		{
		private:
			void ExportLicense(std::wofstream &f, const EXPORT_SETTINGS &settings, const String &ver, const String &form_name);
			void ExportInitialize(std::wofstream &f, const String &shift, CComponentList *components, CControlList *controls, IControl *parent, const String &prefix, const String &form_name);
			void ExportComponentsInitialize(std::wofstream &f, const String &shift, CComponentList *components, const String &prefix, const String &form_name);
			void ExportControlsInitialize(std::wofstream &f, IControl *parent, const String &shift, CControlList *controls, const String &prefix, const String &form_name);
		public:
			String getName() const override;
			String getDescription() const override;

			bool Export(const String &filename, const EXPORT_SETTINGS &settings, CComponentList *components, CControlList *controls, Form &form, const String &ver, IControl *parent) override;
			String PrepareFormName(const String &name) override;

			CExporterHeaderForm();
		};
	}
}