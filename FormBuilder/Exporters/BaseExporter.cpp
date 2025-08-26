// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

#ifdef DialogBox
#undef DialogBox
#endif

namespace nitisa
{
	namespace fb
	{
	#pragma region Constructor & destructor
		CBaseExporter::CBaseExporter() :
			m_eLastError{ ErrorType::None }
		{

		}

		void CBaseExporter::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Interface getters
		String CBaseExporter::getVersion() const
		{
			return L"1.0.0";
		}

		IExporter::ErrorType CBaseExporter::getLastError() const
		{
			return m_eLastError;
		}
	#pragma endregion

	#pragma region Helpers
		void CBaseExporter::OverwriteNamespaces(const Overwrites &overwrite_namespaces)
		{
			if (overwrite_namespaces.size() > 0)
			{
				for (int i = 0; i < Editor->getComponentCount(); i++)
					for (auto &item : overwrite_namespaces)
						if (item.first == Editor->getComponent(i)->getNamespace())
						{
							Editor->OverwriteComponentNamespace(i, item.second);
							break;
						}
				for (int i = 0; i < Editor->getControlCount(); i++)
					for (auto &item : overwrite_namespaces)
						if (item.first == Editor->getControl(i)->getNamespace())
						{
							Editor->OverwriteControlNamespace(i, item.second);
							break;
						}
			}
		}

		void CBaseExporter::RestoreNamespaces(const Overwrites &overwrite_namespaces)
		{
			if (overwrite_namespaces.size() > 0)
			{
				for (int i = 0; i < Editor->getComponentCount(); i++)
					Editor->RestoreComponentNamespace(i);
				for (int i = 0; i < Editor->getControlCount(); i++)
					Editor->RestoreControlNamespace(i);
			}
		}

		void CBaseExporter::CollectIncludes(StringArray &includes, CComponentList *components, CControlList *controls, Form &form, const EXPORT_SETTINGS &settings)
		{
			StringArray list;
			if (settings.ExportAs == ExportAs::DialogBox)
			{
				IEditor *editor{ Application->Editor };
				IPackageDialogBox *dlg{ nullptr };
				for (int i = 0; i < editor->getControlCount(); i++)
					if (editor->getControl(i)->isDialogBox() && 
						editor->getControl(i)->getClassName() == settings.DialogBoxClass &&
						editor->getControl(i)->getPackage()->getName() == settings.DialogBoxPackage &&
						(dlg = cast<IPackageDialogBox*>(editor->getControl(i))))
					{
						for (int j = 0; j < dlg->getHeaderFileCount(); j++)
							list.push_back(dlg->getHeaderFile(j));
						for (int j = 0; j < dlg->getDialogBoxHeaderFileCount(); j++)
							list.push_back(dlg->getDialogBoxHeaderFile(j));
						break;
					}
			}
			for (int i = 0; i < components->getCount(); i++)
			{
				for (int j = 0; j < components->getInfo(i)->PackageComponent->getHeaderFileCount(); j++)
					list.push_back(components->getInfo(i)->PackageComponent->getHeaderFile(j));
				for (int j = 0; j < components->getInfo(i)->Events->getCount(); j++)
					if (components->getInfo(i)->Events->getEvent(j)->isChanged())
						for (int k = 0; k < components->getInfo(i)->Events->getEvent(j)->getHeaderFileCount(); k++)
							list.push_back(components->getInfo(i)->Events->getEvent(j)->getHeaderFile(k));
				for (int j = 0; j < components->getInfo(i)->Properties->getCount(); j++)
					if (components->getInfo(i)->Properties->getProperty(j)->isChanged() && !components->getInfo(i)->Properties->getProperty(j)->isSkip())
						for (int k = 0; k < components->getInfo(i)->Properties->getProperty(j)->getHeaderFileCount(); k++)
							list.push_back(components->getInfo(i)->Properties->getProperty(j)->getHeaderFile(k));
			}
			for (int i = 0; i < controls->getCount(); i++)
			{
				for (int j = 0; j < controls->getInfo(i)->PackageControl->getHeaderFileCount(); j++)
					list.push_back(controls->getInfo(i)->PackageControl->getHeaderFile(j));
				for (int j = 0; j < controls->getInfo(i)->Events->getCount(); j++)
					if (controls->getInfo(i)->Events->getEvent(j)->isChanged())
						for (int k = 0; k < controls->getInfo(i)->Events->getEvent(j)->getHeaderFileCount(); k++)
							list.push_back(controls->getInfo(i)->Events->getEvent(j)->getHeaderFile(k));
				for (int j = 0; j < controls->getInfo(i)->Properties->getCount(); j++)
					if (controls->getInfo(i)->Properties->getProperty(j)->isChanged() && !controls->getInfo(i)->Properties->getProperty(j)->isSkip())
						for (int k = 0; k < controls->getInfo(i)->Properties->getProperty(j)->getHeaderFileCount(); k++)
							list.push_back(controls->getInfo(i)->Properties->getProperty(j)->getHeaderFile(k));
			}
			for (int j = 0; j < form.Events->getCount(); j++)
				if (form.Events->getEvent(j)->isChanged())
					for (int k = 0; k < form.Events->getEvent(j)->getHeaderFileCount(); k++)
						list.push_back(form.Events->getEvent(j)->getHeaderFile(k));
			for (int j = 0; j < form.Properties->getCount(); j++)
				if (form.Properties->getProperty(j)->isChanged() && !form.Properties->getProperty(j)->isSkip())
					for (int k = 0; k < form.Properties->getProperty(j)->getHeaderFileCount(); k++)
						list.push_back(form.Properties->getProperty(j)->getHeaderFile(k));
			list.push_back(L"Nitisa/Core/LockRepaint.h");
			list.push_back(L"Nitisa/Core/Strings.h");
			list.push_back(L"Nitisa/Core/Utils.h");
			list.push_back(L"Nitisa/Interfaces/IApplication.h");
			list.push_back(L"Nitisa/Interfaces/IApplicationService.h");
			if (settings.ExportAs == ExportAs::DialogBox)
			{
				list.push_back(L"Nitisa/Core/Consts.h");
			}
			else
			{
				list.push_back(L"Nitisa/Core/Form.h");
				list.push_back(L"Nitisa/Interfaces/IFormService.h");
			}
			std::sort(list.begin(), list.end());
			String last;
			for (auto v : list)
				if (v != last)
				{
					includes.push_back(v);
					last = v;
				}
		}

		String CBaseExporter::PrepareNamespace(const String &ns)
		{
			if (ns.empty())
				return L"";
			return ns + L"::";
		}

		String CBaseExporter::OverwriteEventSignature(IEvent *e, const Overwrites &overwrite_namespaces)
		{
			String ns{ (e->getEventList() && e->getEventList()->getEntity()) ? e->getEventList()->getEntity()->getNamespace() : L"" }; // Form events doesn't have entity
			if (!ns.empty())
				for (auto &item : overwrite_namespaces)
					if (ns == item.first)
					{
						ns = item.second;
						break;
					}
			if (!ns.empty())
				ns += L"::";
			return ReplaceAll(e->getSignature(), L"{namespace}", ns);
		}

		void CBaseExporter::CollectEvents(StringArray &events, CComponentList *components, CControlList *controls, IEventList *form_events, const Overwrites &overwrite_namespaces)
		{
			// Form events
			CollectEvents(events, form_events, overwrite_namespaces);
			// Components events
			for (int i = 0; i < components->getCount(); i++)
				CollectEvents(events, components->getInfo(i)->Events, overwrite_namespaces);
			// Controls events
			for (int i = 0; i < controls->getCount(); i++)
				CollectEvents(events, controls->getInfo(i)->Events, overwrite_namespaces);
		}

		void CBaseExporter::CollectEvents(StringArray &events, IEventList *list, const Overwrites &overwrite_namespaces)
		{
			for (int i = 0; i < list->getCount(); i++)
				if (list->getEvent(i)->isChanged() && !list->getEvent(i)->getValue().empty())
				{
					String s{ L"virtual void " + list->getEvent(i)->getValue() + L"(" + OverwriteEventSignature(list->getEvent(i), overwrite_namespaces) + L") = 0;" };
					if (std::find(events.begin(), events.end(), s) == events.end())
						events.push_back(s);
				}
		}

		void CBaseExporter::CollectForwardDeclarations(std::vector<ForwardDeclaration> &declarations, CComponentList *components, CControlList *controls, Form &form, const EXPORT_SETTINGS &settings, const StringArray &includes)
		{
			// Collect all declarations
			std::vector<ForwardDeclaration> list;
			if (settings.ExportAs == ExportAs::DialogBox)
			{
				IEditor *editor{ Application->Editor };
				IPackageDialogBox *dlg{ nullptr };
				for (int i = 0; i < editor->getControlCount(); i++)
					if (editor->getControl(i)->isDialogBox() &&
						editor->getControl(i)->getClassName() == settings.DialogBoxClass &&
						editor->getControl(i)->getPackage()->getName() == settings.DialogBoxPackage &&
						(dlg = cast<IPackageDialogBox*>(editor->getControl(i))))
					{
						for (int j = 0; j < dlg->getForwardDeclarationCount(); j++)
						{
							auto fd{ dlg->getForwardDeclaration(j) };
							list.push_back(ForwardDeclaration{ fd.Declaration, fd.HeaderFile, fd.Namespace });
						}
						break;
					}
			}
			for (int i = 0; i < components->getCount(); i++)
			{
				for (int j = 0; j < components->getInfo(i)->PackageComponent->getForwardDeclarationCount(); j++)
				{
					auto fd{ components->getInfo(i)->PackageComponent->getForwardDeclaration(j) };
					list.push_back(ForwardDeclaration{ fd.Declaration, fd.HeaderFile, fd.Namespace });
				}
				for (int j = 0; j < components->getInfo(i)->Events->getCount(); j++)
					if (components->getInfo(i)->Events->getEvent(j)->isChanged())
						for (int k = 0; k < components->getInfo(i)->Events->getEvent(j)->getForwardDeclarationCount(); k++)
						{
							auto fd{ components->getInfo(i)->Events->getEvent(j)->getForwardDeclaration(k) };
							list.push_back(ForwardDeclaration{ fd.Declaration, fd.HeaderFile, fd.Namespace });
						}
				for (int j = 0; j < components->getInfo(i)->Properties->getCount(); j++)
					if (components->getInfo(i)->Properties->getProperty(j)->isChanged() && !components->getInfo(i)->Properties->getProperty(j)->isSkip())
						for (int k = 0; k < components->getInfo(i)->Properties->getProperty(j)->getForwardDeclarationCount(); k++)
						{
							auto fd{ components->getInfo(i)->Properties->getProperty(j)->getForwardDeclaration(k) };
							list.push_back(ForwardDeclaration{ fd.Declaration, fd.HeaderFile, fd.Namespace });
						}
			}
			for (int i = 0; i < controls->getCount(); i++)
			{
				for (int j = 0; j < controls->getInfo(i)->PackageControl->getForwardDeclarationCount(); j++)
				{
					auto fd{ controls->getInfo(i)->PackageControl->getForwardDeclaration(j) };
					list.push_back(ForwardDeclaration{ fd.Declaration, fd.HeaderFile, fd.Namespace });
				}
				for (int j = 0; j < controls->getInfo(i)->Events->getCount(); j++)
					if (controls->getInfo(i)->Events->getEvent(j)->isChanged())
						for (int k = 0; k < controls->getInfo(i)->Events->getEvent(j)->getForwardDeclarationCount(); k++)
						{
							auto fd{ controls->getInfo(i)->Events->getEvent(j)->getForwardDeclaration(k) };
							list.push_back(ForwardDeclaration{ fd.Declaration, fd.HeaderFile, fd.Namespace });
						}
				for (int j = 0; j < controls->getInfo(i)->Properties->getCount(); j++)
					if (controls->getInfo(i)->Properties->getProperty(j)->isChanged() && !controls->getInfo(i)->Properties->getProperty(j)->isSkip())
						for (int k = 0; k < controls->getInfo(i)->Properties->getProperty(j)->getForwardDeclarationCount(); k++)
						{
							auto fd{ controls->getInfo(i)->Properties->getProperty(j)->getForwardDeclaration(k) };
							list.push_back(ForwardDeclaration{ fd.Declaration, fd.HeaderFile, fd.Namespace });
						}
			}
			for (int j = 0; j < form.Events->getCount(); j++)
				if (form.Events->getEvent(j)->isChanged())
					for (int k = 0; k < form.Events->getEvent(j)->getForwardDeclarationCount(); k++)
					{
						auto fd{ form.Events->getEvent(j)->getForwardDeclaration(k) };
						list.push_back(ForwardDeclaration{ fd.Declaration, fd.HeaderFile, fd.Namespace });
					}
			for (int j = 0; j < form.Properties->getCount(); j++)
				if (form.Properties->getProperty(j)->isChanged() && !form.Properties->getProperty(j)->isSkip())
					for (int k = 0; k < form.Properties->getProperty(j)->getForwardDeclarationCount(); k++)
					{
						auto fd{ form.Properties->getProperty(j)->getForwardDeclaration(k) };
						list.push_back(ForwardDeclaration{ fd.Declaration, fd.HeaderFile, fd.Namespace });
					}
			if (settings.ExportAs == ExportAs::DialogBox)
			{
				list.push_back(ForwardDeclaration{ L"class IDialogBoxService;", L"Nitisa/Interfaces/IDialogBoxService.h", L"" });
			}
			else
			{
				list.push_back(ForwardDeclaration{ L"class IWindow;", L"Nitisa/Interfaces/IWindow.h", L"" });
				list.push_back(ForwardDeclaration{ L"class IRenderer;", L"Nitisa/Interfaces/IRenderer.h", L"" });
				list.push_back(ForwardDeclaration{ L"struct CreateParams;", L"Nitisa/Core/CreateParams.h", L"" });
			}
			// Collect only unique declarations, which were not included by their header files yet
			std::sort(list.begin(), list.end(), [](const ForwardDeclaration &a, const ForwardDeclaration &b) {
				return (a.Declaration < b.Declaration) || (a.Declaration == b.Declaration && a.Namespace < b.Namespace);
			});
			ForwardDeclaration last;
			for (auto v : list)
				if (v.Declaration != last.Declaration || v.Namespace != last.Namespace)
				{
					auto pos{ std::lower_bound(includes.begin(), includes.end(), v.HeaderFile) };
					if (pos == includes.end() || *pos != v.HeaderFile)
						declarations.push_back(v);
					last = v;
				}
			// Overwrite namespaces
			if (settings.OverwriteNamespaces.size() > 0)
			{
				bool changed{ false };
				for (auto &v : declarations)
					for (auto item : settings.OverwriteNamespaces)
						if (item.first == v.Namespace)
						{
							v.Namespace = item.second;
							changed = true;
							break;
						}
				if (changed)
				{
					std::sort(list.begin(), list.end(), [](const ForwardDeclaration &a, const ForwardDeclaration &b) {
						return (a.Namespace < b.Namespace) || (a.Namespace == b.Namespace && a.Declaration < b.Declaration);
					});
				}
			}
		}
	#pragma endregion

	#pragma region Export
		void CBaseExporter::ExportIncludes(std::wofstream &f, CComponentList *components, CControlList *controls, Form &form, const EXPORT_SETTINGS &settings, StringArray &includes)
		{
			includes.clear();
			CollectIncludes(includes, components, controls, form, settings);
			if (settings.OverwriteIncludes.size() > 0)
				for (auto &include : includes)
					for (auto &item : settings.OverwriteIncludes)
						if (include.find(item.first, 0) == 0)
						{
							include = item.second + include.substr(item.first.length());
							break;
						}
			if (includes.size() > 0)
			{
				for (auto pos : includes)
					f << L"#include \"" + pos + L"\"" << std::endl;
				f << std::endl;
			}
		}

		void CBaseExporter::ExportComponentDeclarations(std::wofstream &f, const String &shift, CComponentList *components, const String &prefix)
		{
			if (components->getCount() > 0)
			{
				f << shift << L"\t\t// Components" << std::endl;
				for (int i = 0; i < components->getCount(); i++)
				{
					COMPONENT_INFO *info{ components->getInfo(i) };
					f << shift << L"\t\t" << PrepareNamespace(info->PackageComponent->getNamespace()) << L"C" << info->Component->ClassName << L" *" << prefix
						<< info->Component->Name << L";" << std::endl;
				}
				f << std::endl;
			}
		}

		void CBaseExporter::ExportControlDeclarations(std::wofstream &f, const String &shift, CControlList *controls, const String &prefix)
		{
			if (controls->getCount() > 0)
			{
				f << shift << L"\t\t// Controls" << std::endl;
				for (int i = 0; i < controls->getCount(); i++)
				{
					CONTROL_INFO *info{ controls->getInfo(i) };
					f << shift << L"\t\t" << PrepareNamespace(info->PackageControl->getNamespace()) << L"C" << info->Control->ClassName << L" *" << prefix <<
						info->Control->Name << L";" << std::endl;
				}
				f << std::endl;
			}
		}

		void CBaseExporter::ExportEventDeclarations(std::wofstream &f, const String &shift, CComponentList *components, CControlList *controls, IEventList *form_events, const Overwrites &overwrite_namespaces)
		{
			StringArray events;
			CollectEvents(events, components, controls, form_events, overwrite_namespaces);
			if (events.size() > 0)
			{
				f << shift << L"\tprotected:" << std::endl;
				f << shift << L"\t\t// Events(Should be implemented in derived widget)" << std::endl;
				for (auto &e : events)
					f << shift << L"\t\t" << e << std::endl;
				f << std::endl;
			}
		}

		void CBaseExporter::ExportComponentsCreationInitialize(std::wofstream &f, const String &shift, CComponentList *components, const String &prefix, const String &parent)
		{
			if (components->getCount() > 0)
			{
				f << shift << L"\t\t\t// Create components" << std::endl;
				for (int i = 0; i < components->getCount(); i++)
				{
					COMPONENT_INFO *info{ components->getInfo(i) };
					f << shift << L"\t\t\t" << prefix << info->Component->Name << L" = new " << PrepareNamespace(info->PackageComponent->getNamespace()) << L"C" <<
						info->Component->ClassName << L"(" << parent << L");" << std::endl;
					f << shift << L"\t\t\t" << prefix << info->Component->Name << L"->setName(L\"" << info->Component->Name << L"\");" << std::endl;
				}
				f << std::endl;
			}
		}

		void CBaseExporter::ExportControlsCreationInitialize(std::wofstream &f, IControl *parent, const String &parent_name, const String &shift, const String &prefix, CControlList *controls)
		{
			for (int i = 0; i < parent->getControlCount(); i++)
			{
				CONTROL_INFO *info{ controls->getInfo(parent->getControl(i)) };
				f << shift << L"\t\t\t" << prefix << info->Control->Name << L" = new " << PrepareNamespace(info->PackageControl->getNamespace()) << L"C" <<
					info->Control->ClassName << L"(" << parent_name << L");" << std::endl;
				f << shift << L"\t\t\t" << prefix << info->Control->Name << L"->setName(L\"" << info->Control->Name << L"\");" << std::endl;
				ExportControlsCreationInitialize(f, info->Control, prefix + info->Control->Name, shift, prefix, controls);
			}
		}

		void CBaseExporter::ExportDefaultValues(std::wofstream &f, const String &shift, CComponentList *components, CControlList *controls, const String &prefix)
		{
			for (int i = 0; i < components->getCount(); i++)
				f << L"," << std::endl << shift << L"\t\t\t" << prefix << components->getInfo(i)->Component->Name << L"{ nullptr }";
			for (int i = 0; i < controls->getCount(); i++)
				f << L"," << std::endl << shift << L"\t\t\t" << prefix << controls->getInfo(i)->Control->Name << L"{ nullptr }";
		}

		void CBaseExporter::ExportComponentsExtra(std::wofstream &f, const String &shift, CComponentList *components)
		{
			for (int i = 0; i < components->getCount(); i++)
				components->getInfo(i)->PackageComponent->ExportExtra(f, shift, components->getInfo(i)->Component);
		}

		void CBaseExporter::ExportControlsExtra(std::wofstream &f, const String &shift, CControlList *controls)
		{
			for (int i = 0; i < controls->getCount(); i++)
				controls->getInfo(i)->PackageControl->ExportExtra(f, shift, controls->getInfo(i)->Control);
		}

		void CBaseExporter::ExportGetters(std::wofstream &f, const String &shift, CComponentList *components, CControlList *controls, const String &prefix)
		{
			if (components->getCount() > 0 || controls->getCount() > 0)
			{
				f << std::endl;
				if (components->getCount() > 0)
				{
					f << shift << L"// Component getters" << std::endl;
					for (int i = 0; i < components->getCount(); i++)
					{
						COMPONENT_INFO *info{ components->getInfo(i) };
						f << shift << PrepareNamespace(info->PackageComponent->getNamespace()) << L"C" << info->Component->ClassName << L" *get" << info->Component->Name << L"()" << std::endl;
						f << shift << L"{" << std::endl;
						f << shift << L"\treturn " << prefix << info->Component->Name << L";" << std::endl;
						f << shift << L"}" << std::endl << std::endl;
					}
				}
				if (controls->getCount() > 0)
				{
					f << shift << L"// Control getters" << std::endl;
					for (int i = 0; i < controls->getCount(); i++)
					{
						CONTROL_INFO *info{ controls->getInfo(i) };
						f << shift << PrepareNamespace(info->PackageControl->getNamespace()) << L"C" << info->Control->ClassName << L" *get" << info->Control->Name << L"()" << std::endl;
						f << shift << L"{" << std::endl;
						f << shift << L"\treturn " << prefix << info->Control->Name << L";" << std::endl;
						f << shift << L"}" << std::endl << std::endl;
					}
				}
			}
		}

		void CBaseExporter::ExportForwardDeclarations(std::wofstream &f, CComponentList *components, CControlList *controls, Form &form, const EXPORT_SETTINGS &settings, const StringArray &includes)
		{
			std::vector<ForwardDeclaration> declarations;
			CollectForwardDeclarations(declarations, components, controls, form, settings, includes);
			if (declarations.size() > 0)
			{
				String last_ns;
				for (auto pos : declarations)
				{
					if (pos.Namespace != last_ns)
					{
						if (last_ns.length() > 0)
							f << L"\t}" << std::endl << std::endl;
						else
							f << std::endl;
						if (pos.Namespace.length() > 0)
						{
							f << L"\tnamespace " << pos.Namespace << std::endl;
							f << L"\t{" << std::endl;
						}
						last_ns = pos.Namespace;
					}
					if (last_ns.length() > 0)
						f << L"\t\t" << pos.Declaration << std::endl;
					else
						f << L"\t" << pos.Declaration << std::endl;
				}
				if (last_ns.length() > 0)
					f << L"\t}" << std::endl << std::endl;
				else
					f << std::endl;
			}
		}
	#pragma endregion
	}
}