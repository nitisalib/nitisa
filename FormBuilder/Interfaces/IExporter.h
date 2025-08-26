// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../Core/Types.h"

namespace nitisa
{
	class IEventList;
	class IPropertyList;

	namespace fb
	{
		class CComponentList;
		class CControlList;

		class IExporter
		{
		protected:
			IExporter() = default;
			~IExporter() = default;
			IExporter(const IExporter &other) = delete;
			IExporter(IExporter &&other) = delete;
			IExporter &operator=(const IExporter &other) = delete;
			IExporter &operator=(IExporter &&other) = delete;
		public:
			enum ErrorType // Error types
			{
				None, // No error
				FileOpen, // Cannot open file for writing
				NotBaseDialogBox // Base dialog box is not found
			};

			struct Form // Store information about form
			{
				String Name; // Form name
				IEventList *Events; // Form events
				IPropertyList *Properties; // Form properties
			};
		public:
			virtual String getName() const = 0; // Return exporter name
			virtual String getDescription() const = 0; // Return exporter description
			virtual String getVersion() const = 0; // Return exporter version
			virtual ErrorType getLastError() const = 0; // Return error happened in export

			virtual void Release() = 0; // Destroy exporter

			virtual bool Export( // Export to specified file
				const String &filename, // Filename where to export
				const EXPORT_SETTINGS &settings, // Exporting settings
				CComponentList *components, // Information about components
				CControlList *controls, // Information about controls
				Form &form, // Information about form
				const String &ver, // Form Builder version
				IControl *parent) = 0; // FormEditor where all form controls are
			virtual String PrepareFormName(const String &name) = 0; // Replace placeholder in form name with needed value
		};
	}
}