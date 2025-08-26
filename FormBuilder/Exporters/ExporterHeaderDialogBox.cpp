// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace fb
	{
	#pragma region CEmptyDialogBox
		CExporterHeaderDialogBox::CEmptyDialogBox::CEmptyDialogBox() :
			CDialogBox(L"EmptyDialogBox", false, false, false, false, DesignDPI, nullptr),
			m_sBackgroundColor{ 0, 0, 0, 0 },
			m_eState{ WindowState::Normal },
			m_sBorderWidth{ 0, 0, 0, 0 },
			m_bHasCloseBox{ true },
			m_bHasMinimizeBox{ true },
			m_bHasMaximizeBox{ true },
			m_bHasSizeBox{ true },
			m_bHasSystemMenu{ true },
			m_bHasBorder{ true },
			m_bHasCaption{ true },
			m_bIsPopup{ false }
		{

		}

		Color CExporterHeaderDialogBox::CEmptyDialogBox::getBackgroundColor()
		{
			return m_sBackgroundColor;
		}

		String CExporterHeaderDialogBox::CEmptyDialogBox::getCaption()
		{
			return m_sCaption;
		}

		WindowState CExporterHeaderDialogBox::CEmptyDialogBox::getState()
		{
			return m_eState;
		}

		RectF CExporterHeaderDialogBox::CEmptyDialogBox::getBorderWidth()
		{
			return m_sBorderWidth;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::hasCloseBox()
		{
			return m_bHasCloseBox;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::hasMaximizeBox()
		{
			return m_bHasMaximizeBox;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::hasMinimizeBox()
		{
			return m_bHasMinimizeBox;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::hasSizeBox()
		{
			return m_bHasSizeBox;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::hasSystemMenu()
		{
			return m_bHasSystemMenu;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::hasBorder()
		{
			return m_bHasBorder;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::hasCaption()
		{
			return m_bHasCaption;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::isPopup()
		{
			return m_bIsPopup;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				return true;
			}
			return false;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				return true;
			}
			return false;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::setClientSize(const Point &value)
		{
			if (value.X >= 0 && value.Y >= 0 && value != getClientSize())
				return setSize(PointF{ value.X + m_sBorderWidth.Left + m_sBorderWidth.Right, value.Y + m_sBorderWidth.Top + m_sBorderWidth.Bottom });
			return false;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::setState(const WindowState value)
		{
			if (value != m_eState)
			{
				m_eState = value;
				return true;
			}
			return false;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				m_sBorderWidth = value;
				return true;
			}
			return false;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::setHasCloseBox(const bool value)
		{
			if (value != m_bHasCloseBox)
			{
				m_bHasCloseBox = value;
				return true;
			}
			return false;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::setHasMaximizeBox(const bool value)
		{
			if (value != m_bHasMaximizeBox)
			{
				m_bHasMaximizeBox = value;
				return true;
			}
			return false;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::setHasMinimizeBox(const bool value)
		{
			if (value != m_bHasMinimizeBox)
			{
				m_bHasMinimizeBox = value;
				return true;
			}
			return false;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::setHasSizeBox(const bool value)
		{
			if (value != m_bHasSizeBox)
			{
				m_bHasSizeBox = value;
				return true;
			}
			return false;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::setHasSystemMenu(const bool value)
		{
			if (value != m_bHasSystemMenu)
			{
				m_bHasSystemMenu = value;
				return true;
			}
			return false;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::setHasBorder(const bool value)
		{
			if (value != m_bHasBorder)
			{
				m_bHasBorder = value;
				return true;
			}
			return false;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::setHasCaption(const bool value)
		{
			if (value != m_bHasCaption)
			{
				m_bHasCaption = value;
				return true;
			}
			return false;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::setIsPopup(const bool value)
		{
			if (value != m_bIsPopup)
			{
				m_bIsPopup = value;
				return true;
			}
			return false;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::Maximize()
		{
			return false;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::Minimize()
		{
			return false;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::Restore()
		{
			return false;
		}

		bool CExporterHeaderDialogBox::CEmptyDialogBox::Hide()
		{
			return false;
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CExporterHeaderDialogBox::CExporterHeaderDialogBox() : CBaseExporter()
		{

		}
	#pragma endregion

	#pragma region Interface getters
		String CExporterHeaderDialogBox::getName() const
		{
			return L"C++ dialog box prototype";
		}

		String CExporterHeaderDialogBox::getDescription() const
		{
			return L"Export dialog box widget prototype into C++ header file";
		}
	#pragma endregion

	#pragma region Helpers
		void CExporterHeaderDialogBox::CopyFormEvents(IEventList *dst, IEventList *src)
		{
			for (int i = 0; i < dst->getCount(); i++)
			{
				IEvent *e{ src->getEvent(dst->getEvent(i)->getName()) };
				if (e && e->isChanged())
					dst->getEvent(i)->setValue(e->getValue());
			}
		}

		void CExporterHeaderDialogBox::CopyFormProperties(IPropertyList *dst, IPropertyList *src)
		{
			for (int i = 0; i < dst->getCount(); i++)
			{
				IProperty *p{ src->getProperty(dst->getProperty(i)->Name) };
				if (p && p->isChanged())
					p->Copy(dst->getProperty(i));
			}
		}
	#pragma endregion

	#pragma region Export
		bool CExporterHeaderDialogBox::Export(const String &filename, const EXPORT_SETTINGS &settings, CComponentList *components, CControlList *controls, Form &form, const String &ver, IControl *parent)
		{
			m_eLastError = ErrorType::None;
			IPackageControl *base{ nullptr };
			{
				IEditor *editor{ Application->Editor };
				IPackageControl *ctrl;
				for (int i = 0; i < editor->getControlCount(); i++)
				{
					ctrl = editor->getControl(i);
					if (ctrl->isDialogBox() && ctrl->getClassName() == settings.DialogBoxClass && ctrl->getPackage()->getName() == settings.DialogBoxPackage)
					{
						base = ctrl;
						break;
					}
				}
				if (!base)
				{
					m_eLastError = ErrorType::NotBaseDialogBox;
					return false;
				}
			}
			std::wofstream f{ filename };
			if (f.bad())
			{
				m_eLastError = ErrorType::FileOpen;
				return false;
			}
			OverwriteNamespaces(settings.OverwriteNamespaces);

			CEmptyDialogBox dialog_box;
			CDialogBoxEventList events{ nullptr, &dialog_box, nullptr };
			CDialogBoxPropertyList properties{ nullptr, &dialog_box, nullptr };
			StringArray includes;
			properties.Delete(L"Size");
			CopyFormEvents(&events, form.Events);
			CopyFormProperties(&properties, form.Properties);

			String shift{ settings.Namespace.empty() ? L"" : L"\t" };
			const std::locale utf8_locale{ std::locale(std::locale(), new std::codecvt_utf8<wchar_t>()) };
			f.imbue(utf8_locale);
			ExportLicense(f, settings, ver, form.Name);
			f << L"#pragma once" << std::endl;
			f << std::endl;
			ExportIncludes(f, components, controls, form, settings, includes);
			f << L"namespace nitisa" << std::endl;
			f << L"{" << std::endl;
			ExportForwardDeclarations(f, components, controls, form, settings, includes);
			if (!settings.Namespace.empty())
			{
				f << L"\tnamespace " << settings.Namespace << std::endl;
				f << L"\t{" << std::endl;
			}
			f << shift << L"\tclass I" << form.Name << L" : public " << PrepareNamespace(base->getNamespace()) << L"C" << base->getClassName() << std::endl;
			f << shift << L"\t{" << std::endl;
			f << shift << L"\tpublic:" << std::endl;
			ExportService(f, shift + L"\t\t", components, settings.Prefix, form.Name, base);
			f << shift << L"\t" << settings.WidgetsSection << L":" << std::endl;
			ExportComponentDeclarations(f, shift, components, settings.Prefix);
			ExportControlDeclarations(f, shift, controls, settings.Prefix);
			ExportEventDeclarations(f, shift, components, controls, &events, settings.OverwriteNamespaces);
			f << shift << L"\tprivate:" << std::endl;
			ExportInitialize(f, shift, components, controls, parent, settings.Prefix, form.Name);
			f << shift << L"\tpublic:" << std::endl;
			f << shift << L"\t\tI" << form.Name <<
				L"(const String &class_name, const bool accept_form, const bool accept_control, const bool accept_focus, const bool tab_stop, const Point &design_dpi = DesignDPI, IDialogBoxService *service = nullptr) :" << std::endl;
			f << shift << L"\t\t\t" << PrepareNamespace(base->getNamespace()) << L"C" << base->getClassName() << L"(class_name, accept_form, accept_control, accept_focus, tab_stop, design_dpi, service ? service : new I" << form.Name << L"Service(this))";
			ExportDefaultValues(f, shift, components, controls, settings.Prefix);
			f << std::endl;
			f << shift << L"\t\t{" << std::endl;
			f << shift << L"\t\t\tCLockRepaint lock(this);" << std::endl;
			IPropertyIdentifier *property_name{ cast<IPropertyIdentifier*>(properties.getProperty(L"Name")) };
			if (property_name && property_name->getValue().find(L"{type}") != String::npos)
			{
				String old{ property_name->getValue() };
				property_name->setValue(PrepareFormName(old));
				properties.Export(f, L"\t\t\t" + shift, L"");
				property_name->setValue(old);
			}
			else
				properties.Export(f, L"\t\t\t" + shift, L"");
			ExportComponentsExtra(f, L"\t\t\t" + shift, components);
			ExportControlsExtra(f, L"\t\t\t" + shift, controls);
			f << shift << L"\t\t\tInitialize();" << std::endl;
			events.Export(f, L"\t\t\t" + shift, L"", L"", form.Name);
			f << shift << L"\t\t}" << std::endl;
			f << std::endl;
			ExportDestructor(f, shift + L"\t\t", components, settings.Prefix, form.Name);
			if (settings.GenerateGetters)
			{
				ExportGetters(f, shift + L"\t\t", components, controls, settings.Prefix);
				f << std::endl;
			}
			ExportGetComponent(f, shift + L"\t\t", components, settings.Prefix);
			ExportHasComponent(f, shift + L"\t\t", components, settings.Prefix);
			ExportFindControl(f, shift + L"\t\t", controls, settings.Prefix);
			f << shift << L"\t};" << std::endl;
			if (!settings.Namespace.empty())
				f << L"\t}" << std::endl;
			f << L"}" << std::endl;
			f << std::endl;
			f.close();

			RestoreNamespaces(settings.OverwriteNamespaces);
			return true;
		}

		void CExporterHeaderDialogBox::ExportLicense(std::wofstream &f, const EXPORT_SETTINGS &settings, const String &ver, const String &form_name)
		{
			f << L"// This file was generated by Form Builder from Nitisa C++ GUI framework" << std::endl;
			f << L"// Framework site: http://nitisa.com" << std::endl;
			f << L"// Framework download: http://nitisa.com/downloads" << std::endl;
			f << L"// Framework documentation: http://nitisa.com/documentation" << std::endl;
			f << L"// Framework license: http://nitisa.com/site/license" << std::endl;
			f << L"// Form Builder version: " << ver << std::endl;
			f << L"// Form Builder documentation: http://nitisa.com/guide/form-builder" << std::endl;
			f << L"// Generated: " << CDateTime{} << std::endl;
			f << std::endl;

			String shift, ns1, ns2;
			if (!settings.Namespace.empty())
			{
				shift += L"    ";
				ns1 = L"//             namespace " + settings.Namespace + L"\n//             {\n";
				ns2 = L"//             }\n";
			}
			f << L"// !!! ATTENTION !!!" << std::endl;
			f << L"// This is an auto-generated file with dialog box widget prototype declaration and initialization." << std::endl;
			f << L"// Include it into your dialog box widget class header file and derive your widget from the class implemented here." << std::endl;
			f << L"// Add constructor and implement event processing methods(if exist) from \"protected\" section." << std::endl;
			f << L"// Also add service(if your widget need one) derived from service prototype below(do not forget to call parent class methods wher overwriting methods)." << std::endl;

			f << L"// For example:" << std::endl;
			f << L"//     " << form_name << L".h:" << std::endl;
			f << L"//         #include \"Nitisa/Core/Consts.h\" // DesignDPI constant is declared here" << std::endl;
			f << L"//         #include \"Nitisa/Image/Color.h\" // Color declaration is here" << std::endl;
			f << L"//         #include \"I" << form_name << L".h\" // Include this file" << std::endl;
			f << L"//" << std::endl;
			f << L"//         namespace nitisa" << std::endl;
			f << L"//         {" << std::endl;
			f << L"//             class IControl;" << std::endl;
			f << L"//" << std::endl;
			f << ns1;
			f << L"//             " << shift << L"class C" << form_name << L" : public I" << form_name << L" // Derive your widget from class from this file" << std::endl;
			f << L"//             " << shift << L"{" << std::endl;
			f << L"//             " << shift << L"private: // Private members for handling widget logic" << std::endl;
			f << L"//             " << shift << L"    Color m_sBackgroundColor; // Store background color" << std::endl;
			f << L"//             " << shift << L"protected: // Declare overridden methods handling events if there ones in this class" << std::endl;
			f << L"//             " << shift << L"    void ButtonAdd_OnClick(IControl *sender) override;" << std::endl;
			f << L"//             " << shift << L"public:" << std::endl;
			f << L"//             " << shift << L"    // IDialogBox's abstract methods re-declaration" << std::endl;
			f << L"//             " << shift << L"    Color getBackgroundColor() override;" << std::endl;
			f << L"//             " << shift << L"    // Add other abstract methods needed to be implemented" << std::endl;
			f << L"//" << std::endl;
			f << L"//             " << shift << L"    C" << form_name << L"(); // Declare constructor" << std::endl;
			f << L"//             " << shift << L"};" << std::endl;
			f << ns2;
			f << L"//         }" << std::endl;
			f << L"//" << std::endl;

			f << L"//     " << form_name << L".cpp:" << std::endl;
			f << L"//         #include \"" << form_name << L".h\" // Include header class of your form" << std::endl;
			f << L"//" << std::endl;
			f << L"//         namespace nitisa" << std::endl;
			f << L"//         {" << std::endl;
			f << ns1;
			f << L"//             " << shift << L"C" << form_name << L"::C" << form_name << L"(): // Implement constructor of your widget" << std::endl;
			f << L"//             " << shift << L"    I" << form_name << L"(L\"" << form_name << L"\", true, true, false, false, DesignDPI) // Here you may add your service implementation as the latest parameter" << std::endl;
			f << L"//             " << shift << L"{" << std::endl;
			f << L"//             " << shift << L"    // Insert your code here" << std::endl;
			f << L"//             " << shift << L"}" << std::endl;
			f << L"//" << std::endl;
			f << L"//             " << shift << L"void C" << form_name << L"::ButtonAdd_OnClick(IControl *sender) // Implement event processing methods" << std::endl;
			f << L"//             " << shift << L"{" << std::endl;
			f << L"//             " << shift << L"    // Insert your code here" << std::endl;
			f << L"//             " << shift << L"}" << std::endl;
			f << L"//" << std::endl;
			f << L"//             " << shift << L"Color C" << form_name << L"::getBackgroundColor() // Implement IDialogBox's getBackgroundColor() methods" << std::endl;
			f << L"//             " << shift << L"{" << std::endl;
			f << L"//             " << shift << L"    return m_sBackgroundColor;" << std::endl;
			f << L"//             " << shift << L"}" << std::endl;
			f << L"//             " << shift << L"// Implement other IDialogBox's abstract methods" << std::endl;
			f << ns2;
			f << L"//         }" << std::endl;
			f << std::endl;
		}

		void CExporterHeaderDialogBox::ExportInitialize(std::wofstream &f, const String &shift, CComponentList *components, CControlList *controls, IControl *parent, const String &prefix, const String &form_name)
		{
			f << shift << L"\t\tvoid Initialize()" << std::endl;
			f << shift << L"\t\t{" << std::endl;
			ExportComponentsCreationInitialize(f, shift, components, prefix, L"");
			if (parent->getControlCount() > 0)
			{
				f << shift << L"\t\t\t// Create controls" << std::endl;
				ExportControlsCreationInitialize(f, parent, L"this", shift, prefix, controls);
				f << std::endl;
			}
			ExportComponentsInitialize(f, shift, components, prefix, form_name);
			if (parent->getControlCount() > 0)
			{
				f << shift << L"\t\t\t// Initialize controls" << std::endl;
				ExportControlsInitialize(f, parent, shift, controls, prefix, form_name);
				f << std::endl;
			}
			f << shift << L"\t\t}" << std::endl;
			f << std::endl;
		}

		void CExporterHeaderDialogBox::ExportComponentsInitialize(std::wofstream &f, const String &shift, CComponentList *components, const String &prefix, const String &form_name)
		{
			if (components->getCount() > 0)
			{
				f << shift << L"\t\t\t// Initialize components" << std::endl;
				for (int i = 0; i < components->getCount(); i++)
				{
					COMPONENT_INFO *info{ components->getInfo(i) };
					info->PackageComponent->Export(f, L"\t\t\t" + shift, prefix + info->Component->Name, info->Properties, info->Events, L"", form_name);
					f << std::endl;
				}
			}
		}

		void CExporterHeaderDialogBox::ExportControlsInitialize(std::wofstream &f, IControl *parent, const String &shift, CControlList *controls, const String &prefix, const String &form_name)
		{
			for (int i = 0; i < parent->getControlCount(); i++)
			{
				CONTROL_INFO *info{ controls->getInfo(parent->getControl(i)) };
				info->PackageControl->Export(f, L"\t\t\t" + shift, prefix + info->Control->Name, info->Properties, info->Events, L"", form_name);
				f << std::endl;
				ExportControlsInitialize(f, info->Control, shift, controls, prefix, form_name);
			}
		}

		void CExporterHeaderDialogBox::ExportGetComponent(std::wofstream &f, const String &shift, CComponentList *components, const String &prefix)
		{
			f << shift << L"IComponent *getComponent(const String &name)" << std::endl;
			f << shift << L"{" << std::endl;
			for (int i = 0; i < components->getCount(); i++)
			{
				f << shift << L"\tif (name == L\"" << components->getInfo(i)->Component->Name << L"\")" << std::endl;
				f << shift << L"\t\treturn " << prefix << components->getInfo(i)->Component->Name << L";" << std::endl;
			}
			f << shift << L"\treturn nullptr;" << std::endl;
			f << shift << L"}" << std::endl;
			f << std::endl;
		}

		void CExporterHeaderDialogBox::ExportHasComponent(std::wofstream &f, const String &shift, CComponentList *components, const String &prefix)
		{
			if (components->getCount() > 0)
			{
				f << shift << L"bool hasComponent(IComponent *component) override" << std::endl;
				f << shift << L"{" << std::endl;
				for (int i = 0; i < components->getCount(); i++)
				{
					f << shift << L"\tif (component == " << prefix << components->getInfo(i)->Component->Name << L")" << std::endl;
					f << shift << L"\t\treturn true;" << std::endl;
				}
				f << shift << L"\treturn false;" << std::endl;
				f << shift << L"}" << std::endl;
				f << std::endl;
			}
		}

		void CExporterHeaderDialogBox::ExportService(std::wofstream &f, const String &shift, CComponentList *components, const String &prefix, const String &form, IPackageControl *base)
		{
			f << shift << L"class I" << form << L"Service: public " << PrepareNamespace(base->getNamespace()) << L"C" << base->getClassName() << L"Service" << std::endl;
			f << shift << L"{" << std::endl;
			f << shift << L"private:" << std::endl;
			f << shift << L"\tI" << form << L" *m_pControl;" << std::endl;
			f << shift << L"public:" << std::endl;

			f << shift << L"\tvoid NotifyOnAttach() override" << std::endl;
			f << shift << L"\t{" << std::endl;
			f << shift << L"\t\t" << PrepareNamespace(base->getNamespace()) << L"C" << base->getClassName() << L"Service::NotifyOnAttach();" << std::endl;
			f << shift << L"\t\tif (m_pControl->getForm())" << std::endl;
			f << shift << L"\t\t{" << std::endl;
			for (int i = 0; i < components->getCount(); i++)
				f << shift << L"\t\t\tm_pControl->" << prefix << components->getInfo(i)->Component->Name << L"->setForm(m_pControl->getForm());" << std::endl;
			f << shift << L"\t\t}" << std::endl;
			f << shift << L"\t}" << std::endl;
			f << std::endl;

			f << shift << L"\tvoid NotifyOnDetaching() override" << std::endl;
			f << shift << L"\t{" << std::endl;
			f << shift << L"\t\t" << PrepareNamespace(base->getNamespace()) << L"C" << base->getClassName() << L"Service::NotifyOnDetaching();" << std::endl;
			for (int i = 0; i < components->getCount(); i++)
				f << shift << L"\t\tm_pControl->" << prefix << components->getInfo(i)->Component->Name << L"->setForm(nullptr);" << std::endl;
			f << shift << L"\t}" << std::endl;
			f << std::endl;

			f << shift << L"\tI" << form << L"Service(I" << form << L" *control) : " << PrepareNamespace(base->getNamespace()) << L"C" << base->getClassName() << L"Service(control)," << std::endl;
			f << shift << L"\t\tm_pControl{ control }" << std::endl;
			f << shift << L"\t{" << std::endl;
			f << std::endl;
			f << shift << L"\t}" << std::endl;
			f << shift << L"};" << std::endl;
		}

		void CExporterHeaderDialogBox::ExportDestructor(std::wofstream &f, const String &shift, CComponentList *components, const String &prefix, const String &form)
		{
			if (components->getCount() > 0)
			{
				f << shift << L"~I" << form << L"() override" << std::endl;
				f << shift << L"{" << std::endl;
				for (int i = 0; i < components->getCount(); i++)
					f << shift << L"\t" << prefix << components->getInfo(i)->Component->Name << L"->Release();" << std::endl;
				f << shift << L"}" << std::endl;
				f << std::endl;
			}
		}

		void CExporterHeaderDialogBox::ExportFindControl(std::wofstream &f, const String &shift, CControlList *controls, const String &prefix)
		{
			f << shift << L"IControl *FindControl(const String &name, IControl *exclude = nullptr) override" << std::endl;
			f << shift << L"{" << std::endl;
			for (int i = 0; i < controls->getCount(); i++)
			{
				f << shift << L"\tif (name == L\"" << controls->getInfo(i)->Control->Name << L"\" && " << prefix << controls->getInfo(i)->Control->Name << L" != exclude)" << std::endl;
				f << shift << L"\t\treturn " << prefix << controls->getInfo(i)->Control->Name << L";" << std::endl;
			}
			f << shift << L"\treturn nullptr;" << std::endl;
			f << shift << L"}" << std::endl;
			f << std::endl;
		}

		String CExporterHeaderDialogBox::PrepareFormName(const String &name)
		{
			return Replace(name, L"{type}", L"DialogBox");
		}
	#pragma endregion
	}
}