// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"

namespace nitisa
{
	class IEventList;
	class IPropertyList;

	namespace ide
	{
		class IFormEditor;
	}

	namespace fb
	{
		class CComponentList;
		class CControlList;

		struct SETTINGS;

		class ISaver
		{
		protected:
			ISaver() = default;
			~ISaver() = default;
			ISaver(const ISaver &other) = delete;
			ISaver(ISaver &&other) = delete;
			ISaver &operator=(const ISaver &other) = delete;
			ISaver &operator=(ISaver &&other) = delete;
		public:
			enum class ErrorType // Error types
			{
				None, // No error
				FileOpen // Cannot open file for writing
			};

			struct Form
			{
				IEventList *Events;
				IPropertyList *Properties;
			};
		public:
			virtual String getName() const = 0; // Return exporter name
			virtual String getDescription() const = 0; // Return exporter description
			virtual String getVersion() const = 0; // Return exporter version
			virtual ErrorType getLastError() const = 0; // Return error happened in export

			virtual void Release() = 0; // Destroy exporter

			virtual String Save( // Save form and return as string
				CComponentList *components, // Information about components
				CControlList *controls, // Information about controls
				Form &form, // Information about form
				ide::IFormEditor *form_editor, // Parent for all controls
				const String &layout = L"", // Layout name
				const SETTINGS *settings = nullptr) = 0; // Settings to be saved with form or nullptr
		};
	}
}