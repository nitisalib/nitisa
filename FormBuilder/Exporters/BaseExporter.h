// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/DialogBox.h"
#include "Nitisa/Core/Strings.h"
#include "../Interfaces/IExporter.h"
#include "../Core/Types.h"
#include <fstream>
#include <utility>
#include <vector>

namespace nitisa
{
	class IEvent;
	class IEventList;

	namespace fb
	{
		class CComponentList;
		class CControlList;

		class CBaseExporter :public virtual IExporter
		{
		private:
			struct ForwardDeclaration
			{
				String Declaration;
				String HeaderFile;
				String Namespace;
			};
		protected:
			using Overwrites = std::vector<std::pair<String, String>>;
		protected:
			ErrorType m_eLastError;

			void OverwriteNamespaces(const Overwrites &overwrite_namespaces);
			void RestoreNamespaces(const Overwrites &overwrite_namespaces);
			void CollectIncludes(StringArray &includes, CComponentList *components, CControlList *controls, Form &form, const EXPORT_SETTINGS &settings);
			String PrepareNamespace(const String &ns);
			String OverwriteEventSignature(IEvent *e, const Overwrites &overwrite_namespaces);
			void CollectEvents(StringArray &events, CComponentList *components, CControlList *controls, IEventList *form_events, const Overwrites &overwrite_namespaces);
			void CollectEvents(StringArray &events, IEventList *list, const Overwrites &overwrite_namespaces);
			void CollectForwardDeclarations(std::vector<ForwardDeclaration> &declarations, CComponentList *components, CControlList *controls, Form &form, const EXPORT_SETTINGS &settings, const StringArray &includes);

			void ExportIncludes(std::wofstream &f, CComponentList *components, CControlList *controls, Form &form, const EXPORT_SETTINGS &settings, StringArray &includes);
			void ExportComponentDeclarations(std::wofstream &f, const String &shift, CComponentList *components, const String &prefix);
			void ExportControlDeclarations(std::wofstream &f, const String &shift, CControlList *controls, const String &prefix);
			void ExportEventDeclarations(std::wofstream &f, const String &shift, CComponentList *components, CControlList *controls, IEventList *form_events, const Overwrites &overwrite_namespaces);
			void ExportComponentsCreationInitialize(std::wofstream &f, const String &shift, CComponentList *components, const String &prefix, const String &parent);
			void ExportControlsCreationInitialize(std::wofstream &f, IControl *parent, const String &parent_name, const String &shift, const String &prefix, CControlList *controls);
			void ExportDefaultValues(std::wofstream &f, const String &shift, CComponentList *components, CControlList *controls, const String &prefix);
			void ExportComponentsExtra(std::wofstream &f, const String &shift, CComponentList *components);
			void ExportControlsExtra(std::wofstream &f, const String &shift, CControlList *controls);
			void ExportGetters(std::wofstream &f, const String &shift, CComponentList *components, CControlList *controls, const String &prefix);
			void ExportForwardDeclarations(std::wofstream &f, CComponentList *components, CControlList *controls, Form &form, const EXPORT_SETTINGS &settings, const StringArray &includes);
		public:
			String getVersion() const override;
			ErrorType getLastError() const override;

			void Release() override;

			CBaseExporter();
			virtual ~CBaseExporter() = default;
		};
	}
}