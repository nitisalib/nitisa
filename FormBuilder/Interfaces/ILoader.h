// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Variant.h"
#include "../Core/Types.h"

#pragma once

namespace nitisa
{
	class IEventList;
	class IPropertyList;
	class IForm;

	namespace ide
	{
		class IFormEditor;
	}

	namespace fb
	{
		struct SETTINGS;

		class CComponentList;
		class CControlList;

		class ILoader
		{
		protected:
			ILoader() = default;
			~ILoader() = default;
			ILoader(const ILoader &other) = delete;
			ILoader(ILoader &&other) = delete;
			ILoader &operator=(const ILoader &other) = delete;
			ILoader &operator=(ILoader &&other) = delete;
		public:
			enum class ErrorType // Error types
			{
				None // No error
			};

			struct Form
			{
				IEventList *Events;
				IPropertyList *Properties;
				IForm *Form;
			};

			using OnLoadComponent = void(*)(IForm *form, COMPONENT_INFO *info);
			using OnLoadControl = void(*)(IForm *form, CONTROL_INFO *info);
		public:
			virtual String getName() const = 0; // Return exporter name
			virtual String getDescription() const = 0; // Return exporter description
			virtual String getVersion() const = 0; // Return exporter version
			virtual ErrorType getLastError() const = 0; // Return error happened in export

			virtual void Release() = 0; // Destroy exporter

			virtual bool Load( // Save form to specified file
				Variant &data,  // Filename where to save
				CComponentList *components, // Information about components
				CControlList *controls, // Information about controls
				Form &form, // Information about form
				ide::IFormEditor *form_editor, // Parent for all controls
				bool &ignore_attach,
				OnLoadComponent on_load_component,
				OnLoadControl on_load_control) = 0;
		};
	}
}