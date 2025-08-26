// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#include "Platform/OpenGL/ngl.h"
#ifdef VS_INTEGRATION
#include "Platform/Windows/Window.h"
#endif
#include <shellapi.h>

#ifdef DialogBox
#undef DialogBox
#endif

namespace nitisa
{
	namespace fb
	{
		CFormMain *FormMain{ nullptr };

	#ifdef VS_INTEGRATION
		const CreateParams WindowCreateParams{
			// Style
			false,
			false,
			true,
			true,
			true,
			false,
			false,
			false,
			false,
			false,
			false,
			false,
			false,
			false,
			// StyleEx
			false,
			false,
			false,
			false,
			false,
			false,
			false,
			false,
			false,
			false,
			// Other
			L"Window",
			Point{ 0, 0 },
			Point{ 1420, 720 },
			WindowState::Normal,
			WindowPosition::Custom
		};
	#else
		const CreateParams WindowCreateParams{
			// Style
			false,
			true,
			false,
			false,
			true,
			false,
			false,
			false,
			true,
			true,
			true,
			true,
			false,
			false,
			// StyleEx
			false,
			false,
			false,
			false,
			false,
			false,
			false,
			false,
			false,
			true,
			// Other
			L"Window",
			Point{ (int)0x80000000, (int)0x80000000 },
			Point{ 1420, 720 },
			WindowState::Hidden,
			WindowPosition::Custom
	};
	#endif

		/*class CErrorListener :public virtual IErrorListener
		{
		public:
			void NotifyOnError(const AnsiString &function, const int line, const int code, const String &text) override
			{
				std::wcout << L"ERROR in " << AnsiToString(function) << L"[" << line << L"] " << text << std::endl;
			}
		};

		CErrorListener ErrorListener;*/

	#pragma region Constructor & destructor
	#ifndef VS_INTEGRATION
		CFormMain::CFormMain() :
			IFormMain(CWindow::Create(), CRenderer::Create(), L"FormMain", &WindowCreateParams),
			m_cFormEmpty{ this },
			m_pFormPropertyList{ nullptr },
			m_pFormEventList{ nullptr },
			m_bIsModified{ false },
			m_pService{ nullptr },
			m_bIgnoreDeselectListItemsInHierarchy{ false },
			m_bIgnoreAttach{ true },
			m_pComponents{ new CComponentList() },
			m_pControls{ new CControlList() },
			m_pExporterForm{ new CExporterHeaderForm() },
			m_pExporterDialogBox{ new CExporterHeaderDialogBox() },
			m_pSaver{ new CSaver() },
			m_pLoaderDefault{ new CLoaderDefault() },
			m_bSettingsWidgetsInited{ false },
			m_cPackageComponentListener{ this },
			m_cPackageControlListener{ this },
		#ifdef USE_DIALOGBOXES
			m_pDialogBoxConfiguration{ nullptr },
		#endif
			m_iFormViewLayout{ -1 }
		{
			CLockRepaint lock{ this };
			CDateTime d;
			setCaption(L"(c) Nitisa's Visual Form Builder, " + ToString(d.getYear()));
			HICON icon{ LoadIcon(*reinterpret_cast<const HINSTANCE*>(&Application->Handle), MAKEINTRESOURCE(MAINICON)) };
			SendMessage(*reinterpret_cast<const HWND*>(&QueryService()->getWindow()->Handle), WM_SETICON, ICON_BIG, (LPARAM)icon);
			SendMessage(*reinterpret_cast<const HWND*>(&QueryService()->getWindow()->Handle), WM_SETICON, ICON_SMALL, (LPARAM)icon);
			setState(WindowState::Maximized);
			CEditor::Create();
			LoadFormViewLayouts();
			InitInterface();
			InitPackages();
			LoadSettings();
			m_cFormEmpty.OnStyleChange = EmptyForm_OnStyleChange;
			m_cFormEmpty.OnFontChange = EmptyForm_OnFontChange;
			m_cFormEmpty.OnBackgroundChange = EmptyForm_OnBackgroundChange;
			m_cFormEmpty.OnPaddingChange = EmptyForm_OnPaddingChange;

			ShowInitializationStatus();
			UpdateIsModified(false);
			UpdateChecker_Run();
		}

	#else
		CFormMain::CFormMain(HWND parent, HWND *window, const Rect &area) :
			IFormMain(new platform::windows::CWindow(*reinterpret_cast<PlatformHandle*>(&parent)), CRenderer::Create(), L"FormMain", &WindowCreateParams),
			m_cFormEmpty{ this },
			m_pFormPropertyList{ nullptr },
			m_pFormEventList{ nullptr },
			m_bIsModified{ false },
			m_pService{ nullptr },
			m_bIgnoreDeselectListItemsInHierarchy{ false },
			m_bIgnoreAttach{ true },
			m_pComponents{ new CComponentList() },
			m_pControls{ new CControlList() },
			m_pExporterForm{ new CExporterHeaderForm() },
			m_pExporterDialogBox{ new CExporterHeaderDialogBox() },
			m_pSaver{ new CSaver() },
			m_pLoaderDefault{ new CLoaderDefault() },
			m_bSettingsWidgetsInited{ false },
			m_cPackageComponentListener{ this },
			m_cPackageControlListener{ this },
			m_pDialogBoxConfiguration{ nullptr },
			m_iFormViewLayout{ -1 }
		{
			CLockRepaint lock{ this };
			OnUpdateIsModified = nullptr;
			*window = (HWND)QueryService()->getWindow();
			setPosition(area.LeftTop);
			setSize(area.RightBottom);
			m_pIconButtonNew->setEnabled(false);
			m_pIconButtonOpen->setEnabled(false);
			m_pIconButtonSaveAs->setEnabled(false);
			CEditor::Create();
			LoadFormViewLayouts();
			InitInterface();
			InitPackages();
			LoadSettings();
			m_cFormEmpty.OnStyleChange = EmptyForm_OnStyleChange;
			m_cFormEmpty.OnFontChange = EmptyForm_OnFontChange;
			m_cFormEmpty.OnBackgroundChange = EmptyForm_OnBackgroundChange;

			ShowInitializationStatus();
			UpdateIsModified(false);
			UpdateChecker_Run();
		}
	#endif

		CFormMain::~CFormMain()
		{
			CLockRepaint lock{ this };
			delete m_pComponents;
			delete m_pControls;
			if (m_pFormPropertyList)
				m_pFormPropertyList->Release();
			if (m_pFormEventList)
				m_pFormEventList->Release();
			if (m_pService)
				m_pService->Release();
			m_pExporterForm->Release();
			m_pExporterDialogBox->Release();
			m_pSaver->Release();
			m_pLoaderDefault->Release();
		}
	#pragma endregion

	#pragma region Initialization
		void CFormMain::LoadFormViewLayouts()
		{
			String dir{ Application->ModuleDirectory };
			if (!Application->FileSystem->DirectoryExists(dir + L"FormLayouts"))
			{
				dir = Application->ModuleDirectory + L"..\\";
				if (!Application->FileSystem->DirectoryExists(dir + L"FormLayouts"))
				{
					dir = Application->ModuleDirectory + L"..\\..\\";
					if (!Application->FileSystem->DirectoryExists(dir + L"FormLayouts"))
					{
						dir = Application->ModuleDirectory + L"..\\..\\..\\";
						if (!Application->FileSystem->DirectoryExists(dir + L"FormLayouts"))
							dir = Application->ModuleDirectory + L"..\\..\\..\\..\\";
					}
				}
			}
			IFileSystem::SearchFilesResult folders, files;
			if (Application->FileSystem->SearchFiles(dir + L"FormLayouts\\*.*", folders))
				for (auto folder : folders)
					if (folder.Directory && folder.Name != L"." && folder.Name != L"..")
						if (Application->FileSystem->SearchFiles(dir + L"FormLayouts\\" + folder.Name + L"\\*.json", files))
							for (auto file : files)
								if (!file.Directory)
								{
									String filename{ dir + L"FormLayouts\\" + folder.Name + L"\\" + file.Name };
									String content{ GetUTF8FileContent(filename) };
									Variant config;
									if (content.length() > 0 && json_decode(content, config) && config.isSet(L"title"))
										m_aFormViewLayouts.push_back(FORMVIEW_LAYOUT{ (String)config[L"title"], filename });
								}
		}

		void CFormMain::InitInterface()
		{
			m_pIconButtonNew->setOutlineInEditor(false);
			m_pIconButtonOpen->setOutlineInEditor(false);
			m_pIconButtonSave->setOutlineInEditor(false);
			m_pIconButtonSaveAs->setOutlineInEditor(false);
			m_pIconButtonConfiguration->setOutlineInEditor(false);
			m_pIconButtonFoldAll->setOutlineInEditor(false);
			m_pIconButtonUnfoldAll->setOutlineInEditor(false);
			m_pIconButtonAdd->setOutlineInEditor(false);
			m_pIconButtonDelete->setOutlineInEditor(false);
			m_pIconButtonUp->setOutlineInEditor(false);
			m_pIconButtonDown->setOutlineInEditor(false);

			m_pContainerHeader->setOutlineInEditor(false);
			m_pContainerButtons->setOutlineInEditor(false);
			m_pContainerLeft->setOutlineInEditor(false);
			m_pContainerHierarchyButtons->setOutlineInEditor(false);
			
			for (auto pos : m_aFormViewLayouts)
				m_pDropDownLayout->Add(pos.Title);

			m_pFormPropertyList = new CFormPropertyList(nullptr, &m_cFormEmpty, nullptr);
			m_pPropertyEditor->AttachPropertyList(m_pFormPropertyList);

			m_pFormEventList = new CFormEventList(nullptr, &m_cFormEmpty, nullptr);
			m_pEventEditor->AttachEventList(m_pFormEventList);

			m_pFormView->setCaption(m_cFormEmpty.getCaption());
			m_pFormView->setFont(m_cFormEmpty.getFont());
			SetDefaultFormViewLayout();

			m_pFormEditor->setPropertySource(&m_cFormEmpty);

		#if defined(VS_INTEGRATION) || defined(USE_DIALOGBOXES)
			m_pDialogBoxConfiguration = new CDialogBoxConfiguration();
			m_pDialogBoxConfiguration->OnClose = DialogBoxConfiguration_OnClose;
			m_pDialogBoxConfiguration->setBackgroundColor(Color{ 240, 240, 240, 255 });
			m_pDialogBoxConfiguration->setForm(this);
		#endif

		#ifdef VS_INTEGRATION
			m_pStatusBar->getPanel(0)->setCaption(L"Click here to open Nitisa documentation (https://nitisa.com/documentation)");
			cast<standard::CListItemStatusPanelLabel*>(m_pStatusBar->getPanel(0))->setColor(standard::CListItemStatusPanelLabel::State::Hovered, CColors::Blue);
			m_pStatusBar->setCursor(CursorType::Hand);
			m_pStatusBar->OnLeftMouseButtonUp = [](IControl *sender, const MessageMouse &m, bool &processed) {
				ShellExecute(0, 0, L"https://nitisa.com/documentation", 0, 0, SW_SHOW);
			};
		#else
			m_pTimerCheckUpdate->setEnabled(true);
		#endif
		}

		void CFormMain::SetDefaultFormViewLayout()
		{
			int index{ -1 };
			for (auto pos = m_aFormViewLayouts.begin(); pos != m_aFormViewLayouts.end(); pos++)
				if (pos->Title == L"Windows Form")
				{
					index = int(pos - m_aFormViewLayouts.begin());
					break;
				}
			if (index < 0 && m_aFormViewLayouts.size() > 0)
				index = 0;
			if (index >= 0)
			{
				m_pFormView->LoadLayout(m_aFormViewLayouts[index].FileName);
				m_iFormViewLayout = index;
				m_pDropDownLayout->setActiveIndex(index);
			}
		}

		void CFormMain::InitPackages()
		{
			// Components
			for (int i = 0; i < Application->Editor->getComponentCount(); i++)
				if (Application->Editor->isComponentVisible(i) && Application->Editor->getComponent(i)->isVisible())
				{
					standard::CTabSheet *sheet{ FindTabSheet(Application->Editor->getComponent(i)->getCategory()) };
					standard::CToolBar *toolbar;
					if (!sheet)
					{
						sheet = cast<standard::CTabSheet*>(m_pPageControl->CreateTabSheet());
						sheet->setCaption(Application->Editor->getComponent(i)->getCategory());
						toolbar = new standard::CToolBar(sheet);
						toolbar->setBorderWidth(RectF{ 0, 0, 0, 0 });
						toolbar->setAlign(Align::Client);
					}
					else
						toolbar = cast<standard::CToolBar*>(sheet->getControl(0));
					standard::CSpeedButton *btn{ new standard::CSpeedButton(toolbar) };
					btn->Tag = -i - 1;
					btn->setImageList(m_pImageList);
					btn->setHintText(BuildHint(Application->Editor->getComponent(i)));
					btn->OnDown = SpeedButton_OnDown;
					const Image *icon{ Application->Editor->getComponent(i)->getIcon() };
					if (icon)
					{
						Image *copy{ new Image() };
						*copy = *icon;
						btn->setIconIndex(m_pImageList->AddImage(copy));
					}
				}

			// Controls
			for (int i = 0; i < Application->Editor->getControlCount(); i++)
				if (Application->Editor->isControlVisible(i) && Application->Editor->getControl(i)->isVisible())
				{
					standard::CTabSheet *sheet{ FindTabSheet(Application->Editor->getControl(i)->getCategory()) };
					standard::CToolBar *toolbar;
					if (!sheet)
					{
						sheet = cast<standard::CTabSheet*>(m_pPageControl->CreateTabSheet());
						sheet->setCaption(Application->Editor->getControl(i)->getCategory());
						toolbar = new standard::CToolBar(sheet);
						toolbar->setBorderWidth(RectF{ 0, 0, 0, 0 });
						toolbar->setAlign(Align::Client);
					}
					else
						toolbar = cast<standard::CToolBar*>(sheet->getControl(0));
					standard::CSpeedButton *btn{ new standard::CSpeedButton(toolbar) };
					btn->Tag = i;
					btn->setImageList(m_pImageList);
					btn->setHintText(BuildHint(Application->Editor->getControl(i)));
					btn->OnDown = SpeedButton_OnDown;
					const Image *icon{ Application->Editor->getControl(i)->getIcon() };
					if (icon)
					{
						Image *copy{ new Image() };
						*copy = *icon;
						btn->setIconIndex(m_pImageList->AddImage(copy));
					}
				}

			m_pPageControl->setActiveIndex(0);
		}

		void CFormMain::InitSettingsWidgets()
		{
			IEditor *editor{ Application->Editor };
			for (int i = 0; i < editor->getControlCount(); i++)
				if (editor->getControl(i)->isDialogBox())
				#if defined(VS_INTEGRATION) || defined(USE_DIALOGBOXES)
					m_pDialogBoxConfiguration->AddDialogBox(ToString(i), L"[" + editor->getControl(i)->getPackage()->getName() + L"] " + editor->getControl(i)->getClassName());
				#else
					FormConfiguration->AddDialogBox(ToString(i), L"[" + editor->getControl(i)->getPackage()->getName() + L"] " + editor->getControl(i)->getClassName());
				#endif
		}
	#pragma endregion

	#pragma region Setters
		bool CFormMain::setInputControl(IControl *value)
		{
			return false;
		}

		bool CFormMain::setBorderWidth(const RectF &value)
		{
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		IFormService *CFormMain::QueryService()
		{
			if (!m_pService)
				m_pService = new CFormMainService(this);
			return m_pService;
		}

		standard::CTabSheet *CFormMain::FindTabSheet(const String &caption)
		{
			for (int i = 0; i < m_pPageControl->getTabSheetCount(); i++)
				if (m_pPageControl->getTabSheet(i)->getCaption() == caption)
					return cast<standard::CTabSheet*>(m_pPageControl->getTabSheet(i));
			return nullptr;
		}

		void CFormMain::UndownSpeedButtons(const bool skip_active)
		{
			for (int i = 0; i < m_pPageControl->getTabSheetCount(); i++)
			{
				if (skip_active && i == m_pPageControl->getActiveIndex())
					continue;
				for (int j = 0; j < m_pPageControl->getTabSheet(i)->getControl(0)->getControlCount(); j++)
					cast<standard::CSpeedButton*>(m_pPageControl->getTabSheet(i)->getControl(0)->getControl(j))->setDown(false);
			}
		}

		standard::CSpeedButton *CFormMain::FindDownSpeedButton()
		{
			if (m_pPageControl->getTabSheetCount() > 0)
				for (int i = 0; i < m_pPageControl->getActiveTabSheet()->getControl(0)->getControlCount(); i++)
				{
					standard::CSpeedButton *btn{ cast<standard::CSpeedButton*>(m_pPageControl->getActiveTabSheet()->getControl(0)->getControl(i)) };
					if (btn->isDown())
						return btn;
				}
			return nullptr;
		}

		void CFormMain::HierarchyAddItems(IComponent *component, const bool clear)
		{
			IControl *control{ cast<IControl*>(component) };
			IComponentItemTree *tree{ cast<IComponentItemTree*>(component) };
			if (tree)
			{
				ide::IListItemHierarchyEditor *parent{ m_pHierarchyEditor->Find(component, control, nullptr) };
				if (clear)
					parent->DeleteItems();
				HierarchyAddItems(component, control, parent, tree->getRootItem());
			}
			else
			{
				IComponentItemList *list{ cast<IComponentItemList*>(component) };
				if (list)
				{
					ide::IListItemHierarchyEditor *parent{ m_pHierarchyEditor->Find(component, control, nullptr) };
					if (clear)
						parent->DeleteItems();
					for (int i = 0; i < list->getItemCount(); i++)
					{
						IListItemCaption *c{ cast<IListItemCaption*>(list->getItem(i)) };
						ide::IListItemHierarchyEditor *hi{ new ide::CListItemHierarchyEditor(c ? c->getCaption() : (L"Item " + ToString(i)), component, control, list->getItem(i)) };
						hi->setIconIndex(ICON_LISTITEM);
						parent->AddItem(hi);
					}
				}
			}
		}

		void CFormMain::HierarchyAddItems(IComponent *component, IControl *control, ide::IListItemHierarchyEditor *parent_h, IListItem *parent)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				IListItemCaption *c{ cast<IListItemCaption*>(parent->getItem(i)) };
				ide::IListItemHierarchyEditor *new_parent_h{ new ide::CListItemHierarchyEditor(c ? c->getCaption() : (L"Item " + ToString(i)), component, control, parent->getItem(i)) };
				new_parent_h->setIconIndex(ICON_LISTITEM);
				parent_h->AddItem(new_parent_h);
				HierarchyAddItems(component, control, new_parent_h, parent->getItem(i));
			}
		}

		void CFormMain::NotifyOnComponentAttach(IComponent *component)
		{
			if (!m_bIgnoreAttach)
			{
				ide::IListItemHierarchyEditor *item{ m_pHierarchyEditor->Add(component->Name, component, nullptr, nullptr) };
				item->setIconIndex(ICON_COMPONENT);
				HierarchyAddItems(component, false);
				UpdateIsModified(true);
			}
		}

		void CFormMain::NotifyOnControlAttach(IControl *control)
		{
			if (!m_bIgnoreAttach)
			{
				IControl *parent{ control->getParent() == m_pFormEditor ? nullptr : control->getParent() };
				ide::IListItemHierarchyEditor *item;
				if (parent)
					item = m_pHierarchyEditor->Add(control->Name, control, control, nullptr, parent, false);
				else
					item = m_pHierarchyEditor->Add(control->Name, control, control, nullptr);
				item->setIconIndex(ICON_CONTROL);
				HierarchyAddItems(control, false);
				UpdateIsModified(true);
			}
		}

		String CFormMain::BuildHint(IPackageEntity *entity)
		{
			String result{ entity->getTitle() }, platforms{ BuildHintPlatforms(entity) };
			if (!platforms.empty())
				result += L"\n" + platforms;
			return result;
		}

		String CFormMain::BuildHintPlatforms(IPackageEntity *entity)
		{
			if (entity->getPlatformCount() > 0)
			{
				String result{ L"Platforms: " };
				bool first{ true };
				for (int i = 0; i < entity->getPlatformCount(); i++)
				{
					if (!first)
						result += L", ";
					first = false;
					switch (entity->getPlatform(i).Platform)
					{
					case PlatformType::Windows:
						result += L"Windows";
						break;
					case PlatformType::Linux:
						result += L"Linux";
						break;
					case PlatformType::Android:
						result += L"Android";
						break;
					case PlatformType::iOS:
						result += L"iOS";
						break;
					default:
						result += L"Other";
					}
					if (!entity->getPlatform(i).MinVersion.empty())
						if (!entity->getPlatform(i).MaxVersion.empty())
							result += L" " + entity->getPlatform(i).MinVersion + L" .. " + entity->getPlatform(i).MaxVersion;
						else
							result += L" " + entity->getPlatform(i).MinVersion;
					else
						if (!entity->getPlatform(i).MaxVersion.empty())
							result += L" <= " + entity->getPlatform(i).MaxVersion;
				}
				return result;
			}
			if (entity->getPackage()->getPlatformCount() > 0)
			{
				String result{ L"Platforms: " };
				bool first{ true };
				for (int i = 0; i < entity->getPackage()->getPlatformCount(); i++)
				{
					if (!first)
						result += L", ";
					first = false;
					switch (entity->getPackage()->getPlatform(i).Platform)
					{
					case PlatformType::Windows:
						result += L"Windows";
						break;
					case PlatformType::Linux:
						result += L"Linux";
						break;
					case PlatformType::Android:
						result += L"Android";
						break;
					case PlatformType::iOS:
						result += L"iOS";
						break;
					default:
						result += L"Other";
					}
					if (!entity->getPackage()->getPlatform(i).MinVersion.empty())
						if (!entity->getPackage()->getPlatform(i).MaxVersion.empty())
							result += L" " + entity->getPackage()->getPlatform(i).MinVersion + L" .. " + entity->getPackage()->getPlatform(i).MaxVersion;
						else
							result += L" " + entity->getPackage()->getPlatform(i).MinVersion;
					else
						if (!entity->getPackage()->getPlatform(i).MaxVersion.empty())
							result += L" <= " + entity->getPackage()->getPlatform(i).MaxVersion;
				}
				return result;
			}
			return L"";
		}

		void CFormMain::UpdateIsModified(const bool is_modified)
		{
			if (is_modified != m_bIsModified)
			{
				m_bIsModified = is_modified;
			#ifdef VS_INTEGRATION
				if (OnUpdateIsModified)
					OnUpdateIsModified(this, is_modified);
			#else
				m_pIconButtonSave->setEnabled(is_modified);
			#endif
			}
		}

		String CFormMain::Save(const String &filename)
		{
			m_sFileName = filename;
			return m_pSaver->Save(
				m_pComponents,
				m_pControls,
				ISaver::Form{ m_pFormEventList, m_pFormPropertyList },
				m_pFormEditor,
				(m_iFormViewLayout >= 0) ? m_aFormViewLayouts[m_iFormViewLayout].Title : L"",
				m_cFormEmpty.HasSettings ? &m_cFormEmpty.Settings : nullptr);
		}

		void CFormMain::Load(Variant &data, const String &filename)
		{
			ActionNew();
			// Load settings
			if (data.isSet(L"Settings"))
			{
				FromVariant(data.get(L"Settings"), m_cFormEmpty.Settings);
				m_cFormEmpty.HasSettings = true;
				ApplySettings();
			}
			else
				m_cFormEmpty.HasSettings = false;
			// Load layout
			if (data.isSet(L"Layout"))
			{
				int index{ -1 };
				for (auto pos = m_aFormViewLayouts.begin(); pos != m_aFormViewLayouts.end(); pos++)
					if (pos->Title == (String)data.get(L"Layout"))
					{
						index = int(pos - m_aFormViewLayouts.begin());
						break;
					}
				if (index >= 0 && index != m_iFormViewLayout)
				{
					m_pFormView->LoadLayout(m_aFormViewLayouts[index].FileName);
					m_iFormViewLayout = index;
					m_pDropDownLayout->setActiveIndex(index);
				}
			}
			// Load form
			ILoader *loader{ m_pLoaderDefault }; // Select loader depending on version stored in data[L"Version"]
			if (!loader->Load(data, m_pComponents, m_pControls, ILoader::Form{ m_pFormEventList, m_pFormPropertyList, this }, m_pFormEditor, m_bIgnoreAttach, OnLoadComponent, OnLoadControl))
			{
				Application->Dialogs->Error(L"Unknown error happend during loading form from '" + filename + L"'");
			}
			// Apply changes
			m_pFormView->setClientSize((PointF)m_cFormEmpty.getSize());
			m_pFormView->setCaption(m_cFormEmpty.getCaption());
			m_pFormView->setFont(m_cFormEmpty.getFont());
			m_sFileName = filename;
			UpdateIsModified(false);
			m_pPropertyEditor->Refresh(false);
			m_pEventEditor->Refresh(false);
			Repaint();
		}

		void CFormMain::ShowInitializationStatus()
		{
			String msg;
			if (getRenderer())
			{
				if (getRenderer()->InitializationStatus == IRenderer::InitializationStatus::Initialized)
					return;
				switch (getRenderer()->InitializationStatus)
				{
				case IRenderer::InitializationStatus::DeviceContext:
					msg = L"Unable to get window device context";
					break;
				case IRenderer::InitializationStatus::LoadNativeGraphics:
					msg = L"Unable to load native graphics";
					break;
				case IRenderer::InitializationStatus::InitNativeGraphics:
					msg = L"Unable to initialize native graphics";
					break;
				case IRenderer::InitializationStatus::CreateNativeGraphics:
					msg = L"Unable to create native graphics class instance";
					break;
				case IRenderer::InitializationStatus::Version:
					msg = L"Native graphics version " + ToString(getRenderer()->MaxVersion) + L" is too low (OpenGL 3.1+ is required)";
					break;
				case IRenderer::InitializationStatus::Feature:
					msg = L"Native graphics has no required feature (wglChoosePixelFormatARB or wglCreateContextAttribsARB function)";
					break;
				case IRenderer::InitializationStatus::FindPixelFormat:
					msg = L"Unable to find suitable pixel format";
					break;
				case IRenderer::InitializationStatus::SetPixelFormat:
					msg = L"Unable to set pixel format";
					break;
				case IRenderer::InitializationStatus::FindConfig:
					msg = L"Unable to find configuration for pixel format";
					break;
				case IRenderer::InitializationStatus::CreateContext:
					msg = L"Unable to create native graphics context";
					break;
				case IRenderer::InitializationStatus::ActivateContext:
					msg = L"Unable to activate native graphics context";
					break;
				case IRenderer::InitializationStatus::CreateSurface:
					msg = L"Unable to create window surface";
					break;
				case IRenderer::InitializationStatus::DefaultVertexArray:
					msg = L"Unable to create default vertex array";
					break;
				case IRenderer::InitializationStatus::DefaultTextures:
					msg = L"Unable to create default textures";
					break;
				case IRenderer::InitializationStatus::DefaultProgram:
					msg = L"Unable to create default shader program";
					break;
				case IRenderer::InitializationStatus::DefaultFramebuffer:
					msg = L"Unable to create default framebuffer";
					break;
				case IRenderer::InitializationStatus::DefaultTextureFramebuffer:
					msg = L"Unable to create default texture framebuffer";
					break;
				case IRenderer::InitializationStatus::Window:
					msg = L"Specified window is not supported";
					break;
				//case IRenderer::InitializationStatus::NotInitialized:
				default:
					msg = L"Initialization was not performed yet";
					break;
				}
			}
			else
			{
				Version2 ver;
				if (ngl::load(&ver))
					msg = L"Native graphics version " + ToString(ver) + L" is too low (OpenGL 3.1+ is required)";
				else
					msg = L"Unable to load native graphics";
			}
			Application->Dialogs->Error(msg);
		}
	#pragma endregion

	#pragma region Settings
		void CFormMain::LoadSettings()
		{
			if (m_cFormEmpty.Settings.Load(Application->ModuleDirectory + L"settings.json"))
				ApplySettings();
		}

		void CFormMain::SaveSettings()
		{
			m_cFormEmpty.Settings.Save(Application->ModuleDirectory + L"settings.json");
		}

		void CFormMain::ApplySettings()
		{
			m_pFormEditor->setGridEnabled({ m_cFormEmpty.Settings.GridX, m_cFormEmpty.Settings.GridY });
			m_pFormEditor->setRotateGridEnabled(m_cFormEmpty.Settings.GridRotate);
			m_pFormEditor->setGridSize({ m_cFormEmpty.Settings.GridXStep, m_cFormEmpty.Settings.GridYStep });
			m_pFormEditor->setRotateGridSize(m_cFormEmpty.Settings.GridRotateStep);
			m_pFormEditor->setRotateShift(m_cFormEmpty.Settings.RotateShift);
			m_pFormEditor->setGridPointSize(m_cFormEmpty.Settings.GridPointSize);
			m_pFormEditor->setGridPointColor(m_cFormEmpty.Settings.GridPointColor);
			m_pFormEditor->setSelectionSize(m_cFormEmpty.Settings.SelectionPointSize);
			m_pFormEditor->setSelectionBorderWidth(m_cFormEmpty.Settings.SelectionBorderWidth);
			m_pFormEditor->setSelectionBorderColor(m_cFormEmpty.Settings.SelectionBorderColor);
			m_pFormEditor->setSelectionBackgroundColor(m_cFormEmpty.Settings.SelectionBackgroundColor);
			m_pFormView->setBorderWidth(m_cFormEmpty.Settings.HighlightBorderWidth);
			m_pFormView->setBorderColor(ide::CFormView::State::Active, m_cFormEmpty.Settings.HighlightBorderColor);
		}
	#pragma endregion

	#pragma region Actions
		void CFormMain::ActionNew()
		{
			CLockRepaint lock{ this };
			// Delete all widgets
			m_pFormEditor->SelectAll();
			m_pFormEditor->DeleteSelected();
			// Detach properties and events and delete them
			m_pPropertyEditor->DetachPropertyList(m_pFormPropertyList);
			m_pEventEditor->DetachEventList(m_pFormEventList);
			m_pFormPropertyList->Release();
			m_pFormEventList->Release();
			// Temporary disable events
			m_cFormEmpty.OnStyleChange = nullptr;
			m_cFormEmpty.OnFontChange = nullptr;
			m_cFormEmpty.OnBackgroundChange = nullptr;
			auto event_on_resize{ m_pFormEditor->OnResize };
			m_pFormEditor->OnResize = nullptr;
			// Reset empty form state to default one
			m_cFormEmpty.getTransform()->setTransform(Transform{ 0, 0, 0, 1, 1, 1, 0, 0, 0, RotateOrder::XYZ, TransformOrder::RST });
			m_cFormEmpty.getTransformControls()->setTransform(Transform{ 0, 0, 0, 1, 1, 1, 0, 0, 0, RotateOrder::XYZ, TransformOrder::RST });
			m_cFormEmpty.setName(L"Form1");
			m_cFormEmpty.setBackgroundColor(Color{ 240, 240, 240, 255 });
			m_cFormEmpty.setStyle(nullptr);
			m_cFormEmpty.setHintDelay(0.5f);
			m_cFormEmpty.setShowHint(true);
			m_cFormEmpty.setHintShift(PointF{ 0, 20 });
			CreateParams params;
			params.Caption = L"Form1";
			params.Position = Point{ 0, 0 };
			params.Size = Point{ 640, 480 };
			m_cFormEmpty.setCreateParams(params);
			m_pFormView->setClientSize(PointF{ 640, 480 });
			m_pFormView->setCaption(m_cFormEmpty.getCaption());
			// Enable events again
			m_pFormEditor->OnResize = event_on_resize;
			m_cFormEmpty.OnStyleChange = EmptyForm_OnStyleChange;
			m_cFormEmpty.OnFontChange = EmptyForm_OnFontChange;
			m_cFormEmpty.OnBackgroundChange = EmptyForm_OnBackgroundChange;
			// Create and attach properties and events
			m_pFormPropertyList = new CFormPropertyList(nullptr, &m_cFormEmpty, nullptr);
			m_pFormEventList = new CFormEventList(nullptr, &m_cFormEmpty, nullptr);
			m_pPropertyEditor->AttachPropertyList(m_pFormPropertyList);
			m_pEventEditor->AttachEventList(m_pFormEventList);
			m_pPageControlPropertyEvent->setActiveIndex(0);
			// Set unmodified state
			m_sFileName = L"";
			UpdateIsModified(false);
			// Repaint all
			Repaint();
		}

		void CFormMain::ActionSave(const bool prompt)
		{
			if (prompt || m_sFileName.empty())
				if (!Application->Dialogs->Save(L"Nitisa Form Resource(*.nfr)|*.nfr", 1, m_sFileName, L"nfr", false, false, true, false, true, true))
					return;
			// Save *.nfr
			std::wofstream f{ m_sFileName };
			if (f.bad())
			{
				Application->Dialogs->Error(L"Unable to open '" + m_sFileName + L"' for writing");
				return;
			}
			const std::locale utf8_locale{ std::locale(std::locale(), new std::codecvt_utf8<wchar_t>()) };
			f.imbue(utf8_locale);
			f << Save(m_sFileName);
			f.close();
			Export();
			UpdateIsModified(false);
		}

		void CFormMain::ActionOpen()
		{
			String filename;
			if (!Application->Dialogs->Open(L"Nitisa Form Resource(*.nfr)|*.nfr", 1, filename, false, false, true, false, false, true))
				return;
			CLockRepaint lock{ this };
			std::wifstream f{ filename };
			if (!f.bad())
			{
				std::wstringstream ss;
				const std::locale utf8_locale{ std::locale(std::locale(), new std::codecvt_utf8<wchar_t>()) };
				f.imbue(utf8_locale);
				ss << f.rdbuf();
				f.close();
				Variant data;
				if (json_decode(ss.str(), data))
					Load(data, filename);
				else
					Application->Dialogs->Error(m_sFileName + L" has no valid JSON data");
			}
			else
				Application->Dialogs->Error(L"Unable to open " + m_sFileName + L" for reading");
		}
	#pragma endregion

	#pragma region SpeedButton callbacks
		void CFormMain::SpeedButton_OnDown(IControl *sender)
		{
			CFormMain *form{ cast<CFormMain*>(sender->getForm()) };
			form->UndownSpeedButtons(true);
		}
	#pragma endregion

	#pragma region EmptyForm callbacks
		void CFormMain::EmptyForm_OnStyleChange(IForm *sender)
		{
			CFormMain *form{ cast<CFormMain*>(sender) };
			if (form->m_pFormEditor)
			{
				CLockRepaint lock{ form };
				CNotifier::ParentStyleChange(form->m_pFormEditor);
			}
		}

		void CFormMain::EmptyForm_OnFontChange(IForm *sender)
		{
			CFormMain *form{ cast<CFormMain*>(sender) };
			if (form->m_pFormEditor)
			{
				CLockRepaint lock{ form };
				CNotifier::ParentFontChange(form->m_pFormEditor);
			}
		}

		void CFormMain::EmptyForm_OnBackgroundChange(IForm *sender)
		{
			CFormMain *form{ cast<CFormMain*>(sender) };
			if (form->m_pFormEditor)
				form->m_pFormEditor->setBackgroundColor(form->m_cFormEmpty.getBackgroundColor());
		}

		void CFormMain::EmptyForm_OnPaddingChange(IForm *sender)
		{
			CFormMain *form{ cast<CFormMain*>(sender) };
			if (form->m_pFormEditor)
				form->m_pFormEditor->setPadding(form->m_cFormEmpty.getPadding());
		}
	#pragma endregion

	#pragma region Form events
		void CFormMain::FormMain_OnKeyDown(IForm *sender, const MessageKey &m)
		{
			if (m.Key == Key::Delete && getFocusedControl() == m_pFormEditor)
			{
				if (m_pFormEditor->DeleteSelected())
					UpdateIsModified(true);
				return;
			}
		#ifndef VS_INTEGRATION
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (ctrl && !alt && !shift)
				switch (m.Key)
				{
				case Key::S:
					if (m_bIsModified)
						ActionSave(false);
					return;
				case Key::O:
					ActionOpen();
					return;
				}
		#endif
		}

		void CFormMain::FormMain_OnDestroy(IForm *sender)
		{
			m_pFormEditor->OnResize = nullptr;
			m_pHierarchyEditor->DeselectAll(); // Clear hierarchy editor because it may be destroyed after another controls and may cause of interaction with them in events(that is why it should be cleaned first, while all other controls still exist)
			ide::IListItemHierarchyEditor *active{ cast<ide::IListItemHierarchyEditor*>(m_pHierarchyEditor->getActiveItem()) };
			if (active)
				active->setActive(false);
		}

		void CFormMain::FormMain_OnClose(IForm *sender, CloseAction &action)
		{
			FormMain_OnDestroy(sender);
		}
	#pragma endregion

	#pragma region Update timer events
		void CFormMain::TimerCheckUpdate_OnTimer(IComponent *sender)
		{
			if (!UpdateChecker_IsInProgress())
			{
				cast<standard::ITimer*>(sender)->setEnabled(false);
				standard::IListItemStatusPanelLabel *panel{ m_pStatusBar->getPanel(0) };
				if (UpdateChecker_IsFailed())
				{
					panel->setCaption(L"Unable to check for updates. Please try again later");
					return;
				}
				String v{ UpdateChecker_GetVersion() };
				if (v == FB_VERSION)
				{
					panel->setCaption(L"You are using the latest version of Form Builder");
					return;
				}
				StringArray a;
				Explode(v, L".", a);
				int i;
				if (a.size() != 3 || !TryStringToInt(a[0], i) || !TryStringToInt(a[1], i) || !TryStringToInt(a[2], i))
				{
					panel->setCaption(L"Unable to check for updates. Please try again later");
					return;
				}
				panel->setCaption(L"Newer version " + v + L" is found. Click here to go to download page");
				m_pStatusBar->getControlFont()->setColor(CColors::Red);
				m_pStatusBar->setCursor(CursorType::Hand);
				m_pStatusBar->OnLeftMouseButtonDown = [](IControl *sender, const MessageMouse &m, bool &processed)
				{
					ShellExecute(0, nullptr, L"http://nitisa.com/downloads/index", nullptr, nullptr, SW_SHOW);
					sender->setUseParentFont(true);
				};
			}
		}
	#pragma endregion

	#pragma region Icon buttons events
		void CFormMain::IconButtonNew_OnClick(IControl *sender)
		{
			if (m_bIsModified)
				switch (Application->Dialogs->Confirm(L"Do you want to save changes before creating new form?", L"Save changes"))
				{
				case ModalResult::Yes:
					ActionSave(false);
					break;
				case ModalResult::Cancel:
					return;
				}
			ActionNew();
		}

		void CFormMain::IconButtonOpen_OnClick(IControl *sender)
		{
			if (m_bIsModified)
				switch (Application->Dialogs->Confirm(L"Do you want to save changes before opening another form?", L"Save changes"))
				{
				case ModalResult::Yes:
					ActionSave(false);
					break;
				case ModalResult::Cancel:
					return;
				}
			ActionOpen();
		}

		void CFormMain::IconButtonSave_OnClick(IControl *sender)
		{
			ActionSave(false);
		}

		void CFormMain::IconButtonSaveAs_OnClick(IControl *sender)
		{
			ActionSave(true);
		}

		void CFormMain::IconButtonConfiguration_OnClick(IControl *sender)
		{
			if (!m_bSettingsWidgetsInited)
				InitSettingsWidgets();
		#if defined(VS_INTEGRATION) || defined(USE_DIALOGBOXES)
			m_pDialogBoxConfiguration->FromSettings(m_cFormEmpty.Settings);
			m_pDialogBoxConfiguration->ShowModal();
			if (!m_bSettingsWidgetsInited)
			{
				m_pDialogBoxConfiguration->AutoResize(true);
				m_bSettingsWidgetsInited = true;
			}
		#else
			FormConfiguration->FromSettings(m_cFormEmpty.Settings);
			if (FormConfiguration->ShowModal() == ModalResult::Ok)
			{
				FormConfiguration->ToSettings(m_cFormEmpty.Settings);
				if (FormConfiguration->isGlobal())
				{
					m_cFormEmpty.HasSettings = false;
					SaveSettings();
				}
				else
				{
					m_cFormEmpty.HasSettings = true;
					UpdateIsModified(true);
				}
				ApplySettings();
			}
		#endif
		}

		void CFormMain::IconButtonFoldAll_OnClick(IControl *sender)
		{
			m_pHierarchyEditor->FoldAll();
		}

		void CFormMain::IconButtonUnfoldAll_OnClick(IControl *sender)
		{
			m_pHierarchyEditor->UnfoldAll();
		}

		void CFormMain::IconButtonAdd_OnClick(IControl *sender)
		{
			ide::IListItemHierarchyEditor *active{ cast<ide::IListItemHierarchyEditor*>(m_pHierarchyEditor->getActiveItem()) };
			if (active)
			{
				if (active->getAssignedListItem() || cast<IComponentItemList*>(active->getAssignedComponent()) || cast<IComponentItemTree*>(active->getAssignedComponent()))
				{
					if (active->getAssignedControl())
					{
						CONTROL_INFO *info{ m_pControls->getInfo(active->getAssignedControl()) };
						if (info)
						{
							m_cPackageControlListener.m_pActive = active;
							info->PackageControl->CreateListItem(info->Control, active->getAssignedListItem(), nullptr, &m_cPackageControlListener);
						}
					}
					else if (active->getAssignedComponent())
					{
						COMPONENT_INFO *info{ m_pComponents->getInfo(active->getAssignedComponent()) };
						if (info)
						{
							m_cPackageComponentListener.m_pActive = active;
							info->PackageComponent->CreateListItem(info->Component, active->getAssignedListItem(), nullptr, &m_cPackageComponentListener);
						}
					}
				}
				else if (active->getAssignedControl())
				{
					m_cPackageControlListener.m_pActive = active;
					m_cPackageControlListener.m_pInfo = m_pControls->getInfo(active->getAssignedControl());
					m_cPackageControlListener.m_pInfo->PackageControl->CreateChild(m_cPackageControlListener.m_pInfo->Control, nullptr, &m_cPackageControlListener);
				}
			}
		}

		void CFormMain::IconButtonDelete_OnClick(IControl *sender)
		{
			if (m_pHierarchyEditor->DeleteSelected())
				UpdateIsModified(true);
		}

		void CFormMain::IconButtonUp_OnClick(IControl *sender)
		{
			ide::IListItemHierarchyEditor *active{ cast<ide::IListItemHierarchyEditor*>(m_pHierarchyEditor->getActiveItem()) };
			if (active)
				if (active->getAssignedListItem())
				{
					if (active->getAssignedListItem()->BringUp())
					{
						active->BringUp();
						UpdateIsModified(true);
					}
				}
				else if (active->getAssignedControl())
				{
					if (active->getAssignedControl()->BringUp())
					{
						active->BringUp();
						UpdateIsModified(true);
					}
				}
		}

		void CFormMain::IconButtonDown_OnClick(IControl *sender)
		{
			ide::IListItemHierarchyEditor *active{ cast<ide::IListItemHierarchyEditor*>(m_pHierarchyEditor->getActiveItem()) };
			if (active)
				if (active->getAssignedListItem())
				{
					if (active->getAssignedListItem()->BringDown())
					{
						active->BringDown();
						UpdateIsModified(true);
					}
				}
				else if (active->getAssignedControl())
				{
					if (active->getAssignedControl()->BringDown())
					{
						active->BringDown();
						UpdateIsModified(true);
					}
				}
		}
	#pragma endregion

	#pragma region Hierarchy editor events
		void CFormMain::HierarchyEditor_OnKeyDown(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Delete)
				m_pHierarchyEditor->DeleteSelected();
		}

		void CFormMain::HierarchyEditor_OnSelectItem(IControl *sender, IListItem *item)
		{
			ide::IListItemHierarchyEditor *t{ cast<ide::IListItemHierarchyEditor*>(item) };
			if (t->getAssignedListItem())
			{
				if (!t->getPropertyList())
				{
					for (int i = 0; i < Application->Editor->getListItemCount(); i++)
						if (Application->Editor->getListItem(i)->isInstance(t->getAssignedListItem()))
						{
							t->setPropertyList(Application->Editor->getListItem(i)->CreatePropertyList(t->getAssignedListItem()));
							break;
						}
				}
				if (t->getPropertyList())
				{
					if (m_pPropertyEditor->getPropertyListCount() == 1 && m_pPropertyEditor->getPropertyList(0) == m_pFormPropertyList)
						m_pPropertyEditor->DetachPropertyLists();
					m_pPropertyEditor->AttachPropertyList(t->getPropertyList());
				}
			}
			else if (t->getAssignedControl())
			{
				m_bIgnoreDeselectListItemsInHierarchy = true;
				m_pFormEditor->SelectControl(t->getAssignedControl());
				m_bIgnoreDeselectListItemsInHierarchy = false;
			}
			else if (t->getAssignedComponent())
			{
				m_bIgnoreDeselectListItemsInHierarchy = true;
				m_pFormEditor->SelectComponent(t->getAssignedComponent());
				m_bIgnoreDeselectListItemsInHierarchy = false;
			}
		}

		void CFormMain::HierarchyEditor_OnDeselectItem(IControl *sender, IListItem *item)
		{
			ide::IListItemHierarchyEditor *t{ cast<ide::IListItemHierarchyEditor*>(item) };
			if (t->getAssignedListItem())
			{
				if (t->getPropertyList())
				{
					m_pPropertyEditor->DetachPropertyList(t->getPropertyList());
					if (m_pPropertyEditor->getPropertyListCount() == 0)
						m_pPropertyEditor->AttachPropertyList(m_pFormPropertyList);
				}
			}
			else if (t->getAssignedControl())
				m_pFormEditor->DeselectControl(t->getAssignedControl());
			else if (t->getAssignedComponent())
				m_pFormEditor->DeselectComponent(t->getAssignedComponent());
		}

		void CFormMain::HierarchyEditor_OnActivateItem(IControl *sender, IListItem *item)
		{
			bool enabled{ false };
			ide::IListItemHierarchyEditor *h_item{ cast<ide::IListItemHierarchyEditor*>(item) };
			if (h_item->getAssignedListItem()) // List item is active, creation allowed, package control must manage parent when creating new item(if parent isn't supported, it should create item at root)
			{
				enabled = true;
			}
			else if (h_item->getAssignedControl()) // Control is active; ItemList, ItemTree and child creation is allowed
			{
				if (cast<IComponentItemList*>(h_item->getAssignedControl()) || cast<IComponentItemTree*>(h_item->getAssignedControl()) || cast<IControlCreateChild*>(h_item->getAssignedControl()))
					enabled = true;
			}
			else // Component is active; ItemList and ItemTree are allowed
			{
				if (cast<IComponentItemTree*>(h_item->getAssignedComponent()) || cast<IComponentItemTree*>(h_item->getAssignedComponent()))
					enabled = true;
			}
			m_pIconButtonAdd->setEnabled(enabled);
			m_pIconButtonDelete->setEnabled(true);
			m_pIconButtonUp->setEnabled(true);
			m_pIconButtonDown->setEnabled(true);
		}

		void CFormMain::HierarchyEditor_OnDeactivateItem(IControl *sender, IListItem *item)
		{
			m_pIconButtonAdd->setEnabled(false);
			m_pIconButtonDelete->setEnabled(false);
			m_pIconButtonUp->setEnabled(false);
			m_pIconButtonDown->setEnabled(false);
		}

		void CFormMain::HierarchyEditor_OnMovingSelection(IControl *sender, IListItem *dest)
		{
			if (m_pHierarchyEditor->isMovable(cast<ide::IListItemHierarchyEditor*>(dest)))
				m_pHierarchyEditor->setCursor(CursorType::Arrow);
			else
				m_pHierarchyEditor->setCursor(CursorType::No);
		}

		void CFormMain::HierarchyEditor_OnMoveSelection(IControl *sender, IListItem *dest)
		{
			m_pHierarchyEditor->setCursor(CursorType::Arrow);
			std::vector<ide::IListItemHierarchyEditor*> items;
			bool move_items;
			ide::IListItemHierarchyEditor *target{ cast<ide::IListItemHierarchyEditor*>(dest) };
			if (m_pHierarchyEditor->isMovable(target, items, move_items))
			{
				if (move_items)
				{
					for (auto pos : items)
					{
						pos->getParent()->DetachItem(pos); // Remove hierarchy item
						pos->getAssignedListItem()->getParent()->DetachItem(pos->getAssignedListItem()); // Remove item from ItemTree
						target->AddItem(pos); // Add hierarchy item
						target->getAssignedListItem()->AddItem(pos->getAssignedListItem()); // Add item to ItemTree
						pos->setSelected(true);
					}
				}
				else
				{
					CFormMainService *service{ cast<CFormMainService*>(QueryService()) };
					service->m_bIgnoreDetach = true;
					for (auto pos : items)
					{
						if (pos->getAssignedControl()->setParent(target ? target->getAssignedControl() : m_pFormEditor))
						{
							pos->getParent()->DetachItem(pos);
							if (target)
								target->AddItem(pos);
							else
								m_pHierarchyEditor->getRootItem()->AddItem(pos);
							pos->setSelected(true);
						}
					}
					service->m_bIgnoreDetach = false;
				}
				UpdateIsModified(true);
			}
		}
	#pragma endregion

	#pragma region Property editor events
		void CFormMain::PropertyEditor_OnPropertyChange(ide::IPropertyEditor *sender, IProperty *property, IPropertyList *property_list, IClass *parent)
		{
			if (property->Name == L"Name" || property->Name == L"Caption")
			{
				IControl *control{ cast<IControl*>(parent) };
				IComponent *component{ cast<IComponent*>(parent) };
				IListItem *item{ cast<IListItem*>(parent) };
				ide::IListItemHierarchyEditor *t{ m_pHierarchyEditor->Find(component, control, item) };
				if (t)
				{
					if (item)
					{
						IListItemCaption *c{ cast<IListItemCaption*>(item) };
						if (c)
							t->setCaption(c->getCaption());
						else
						{
							bool found{ false };
							for (int i = 0; i < t->getParent()->getItemCount(); i++)
								if (t->getParent()->getItem(i) == t)
								{
									t->setCaption(L"Item " + ToString(i));
									found = true;
									break;
								}
							if (!found)
								t->setCaption(L"Item");
						}
					}
					else if (control)
						t->setCaption(control->Name);
					else if (component)
						t->setCaption(component->Name);
				}
			}
			if (property_list == m_pFormPropertyList)
			{
				if (property->Name == L"Caption")
					m_pFormView->setCaption(cast<IPropertyString*>(property)->getValue());
				else if (property->Name == L"Font")
					m_pFormView->setFont(cast<IPropertyFont*>(property)->getValue());
				else if (property->Name == L"ClientSize")
					m_pFormView->setClientSize((PointF)cast<IPropertyPoint*>(property)->getValue());
			}
			if (property->AffectItems)
			{
				IComponent *component{ cast<IComponent*>(parent) };
				HierarchyAddItems(component, true);
			}
			if (property->Name == L"Visible")
			{
				m_pHierarchyEditor->LockUpdate();
				m_pHierarchyEditor->UnlockUpdate();
			}
			m_pFormEditor->Repaint(false);
			UpdateIsModified(true);
		}
	#pragma endregion

	#pragma region Event editor events
		void CFormMain::EventEditor_OnEventChange(ide::IEventEditor *sender, IEvent *event, IEventList *event_list, IClass *parent)
		{
			UpdateIsModified(true);
		}
	#pragma endregion

	#pragma region Form editor events
		void CFormMain::FormEditor_OnResize(IControl *sender)
		{
			IPropertyPoint *p{ cast<IPropertyPoint*>(m_pFormPropertyList->getProperty(L"ClientSize")) };
			p->setValue(Point{ ntl::Round<int>(m_pFormEditor->getWidth()), ntl::Round<int>(m_pFormEditor->getHeight()) });
			if (m_pPropertyEditor->getPropertyListCount() == 1 && m_pPropertyEditor->getPropertyList(0) == m_pFormPropertyList)
			{
				m_pPropertyEditor->Refresh(false);
				m_pPropertyEditor->Repaint(false);
			}
			UpdateIsModified(true);
		}

		void CFormMain::FormEditor_OnSelectControl(ide::IFormEditor *sender, IControl *control)
		{
			// Properties
			CONTROL_INFO *info{ m_pControls->getInfo(control) };
			m_pPropertyEditor->DetachPropertyList(m_pFormPropertyList);
			m_pPropertyEditor->AttachPropertyList(info->Properties);
			// Events
			m_pEventEditor->DetachEventList(m_pFormEventList);
			m_pEventEditor->AttachEventList(info->Events);
			// Hierarchy
			if (!m_bIgnoreDeselectListItemsInHierarchy)
				m_pHierarchyEditor->DeselectAllListItems();
			m_pHierarchyEditor->SelectEx(control, control, nullptr, true, true);
			m_pHierarchyEditor->ScrollToActiveItem();
		}

		void CFormMain::FormEditor_OnDeselectControl(ide::IFormEditor *sender, IControl *control)
		{
			// Properties
			CONTROL_INFO *info{ m_pControls->getInfo(control) };
			m_pPropertyEditor->DetachPropertyList(info->Properties);
			if (m_pPropertyEditor->getPropertyListCount() == 0)
				m_pPropertyEditor->AttachPropertyList(m_pFormPropertyList);
			// Events
			m_pEventEditor->DetachEventList(info->Events);
			if (m_pEventEditor->getEventListCount() == 0)
				m_pEventEditor->AttachEventList(m_pFormEventList);
			// Hierarchy
			m_pHierarchyEditor->SelectEx(control, control, nullptr, false, false);
		}

		void CFormMain::FormEditor_OnSelectComponent(ide::IFormEditor *sender, IComponent *component)
		{
			// Properties
			COMPONENT_INFO *info{ m_pComponents->getInfo(component) };
			m_pPropertyEditor->DetachPropertyList(m_pFormPropertyList);
			m_pPropertyEditor->AttachPropertyList(info->Properties);
			// Events
			m_pEventEditor->DetachEventList(m_pFormEventList);
			m_pEventEditor->AttachEventList(info->Events);
			// Hierarchy
			if (!m_bIgnoreDeselectListItemsInHierarchy)
				m_pHierarchyEditor->DeselectAllListItems();
			m_pHierarchyEditor->SelectEx(component, nullptr, nullptr, true, true);
			m_pHierarchyEditor->ScrollToActiveItem();
		}

		void CFormMain::FormEditor_OnDeselectComponent(ide::IFormEditor *sender, IComponent *component)
		{
			// Properties
			COMPONENT_INFO *info{ m_pComponents->getInfo(component) };
			m_pPropertyEditor->DetachPropertyList(info->Properties);
			if (m_pPropertyEditor->getPropertyListCount() == 0)
				m_pPropertyEditor->AttachPropertyList(m_pFormPropertyList);
			// Events
			m_pEventEditor->DetachEventList(info->Events);
			if (m_pEventEditor->getEventListCount() == 0)
				m_pEventEditor->AttachEventList(m_pFormEventList);
			// Hierarchy
			m_pHierarchyEditor->SelectEx(component, nullptr, nullptr, false, false);
		}

		void CFormMain::FormEditor_OnCheckComponentAllowed(ide::IFormEditor *sender, IComponent *component, bool &allowed)
		{
			// Check own components
			if (component == m_pImageList || component == m_pTimerCheckUpdate)
				allowed = false;
		#if defined(VS_INTEGRATION) || defined(USE_DIALOGBOXES)
			// Check components of dialog boxes assigned to form(all dialog boxes should be assigned to form directly)
			IDialogBox *dlg;
			for (int i = 0; i < getControlCount(); i++)
				if ((dlg = cast<IDialogBox*>(getControl(i))) && dlg->hasComponent(component))
				{
					allowed = false;
					break;
				}
		#endif
		}

		void CFormMain::FormEditor_OnComponentTransform(ide::IFormEditor *sender, IComponent *component)
		{
			UpdateIsModified(true);
			m_pPropertyEditor->Refresh(false);
			m_pPropertyEditor->Repaint(false);
		}

		void CFormMain::FormEditor_OnControlTransform(ide::IFormEditor *sender, IComponent *component)
		{
			UpdateIsModified(true);
			m_pPropertyEditor->Refresh(false);
			m_pPropertyEditor->Repaint(false);
		}

		void CFormMain::FormEditor_OnControlResize(ide::IFormEditor *sender, IComponent *component)
		{
			UpdateIsModified(true);
			m_pPropertyEditor->Refresh(false);
			m_pPropertyEditor->Repaint(false);
		}

		void CFormMain::FormEditor_OnMouseDown(ide::IFormEditor *sender, const MessageMouse &m, bool &processed)
		{
			standard::CSpeedButton *btn{ FindDownSpeedButton() };
			if (m.Left && !m.Right && !m.Middle && btn)
			{
				processed = true;
				if ((int)btn->Tag < 0) // Add component
				{
					COMPONENT_INFO data;
					data.Index = -(int)btn->Tag - 1;
					data.PackageComponent = Application->Editor->getComponent(data.Index);
					data.Component = data.PackageComponent->Create(&data.Properties, &data.Events);
					m_pComponents->Add(data.Component, data.Events, data.Properties, data.PackageComponent, data.Index);
					m_pFormEditor->DeselectAll();
					data.Component->setForm(this);
					ide::IListItemHierarchyEditor *item{ m_pHierarchyEditor->Add(data.Component->Name, data.Component, nullptr, nullptr) };
					item->setActive(true);
					item->setIconIndex(ICON_COMPONENT);
					m_pFormEditor->SelectComponent(data.Component);
					PointF p{ m_pFormEditor->FormToLocal(m.Position) };
					if (m_pFormEditor->getGridEnabled().X)
						p.X = ntl::Round<int>(p.X / m_pFormEditor->getGridSize().X) * m_pFormEditor->getGridSize().X;
					if (m_pFormEditor->getGridEnabled().Y)
						p.Y = ntl::Round<int>(p.Y / m_pFormEditor->getGridSize().Y) * m_pFormEditor->getGridSize().Y;
					m_pFormEditor->setComponentPosition(data.Component, p);
					HierarchyAddItems(data.Component, false);
					UpdateIsModified(true);
				}
				else // Add control
				{
					CONTROL_INFO data;
					data.Index = (int)btn->Tag;
					IControl *parent{ m_pFormEditor->getControl(m.Position) };
					data.PackageControl = Application->Editor->getControl(data.Index);
					data.Control = data.PackageControl->Create(&data.Properties, &data.Events);

					// Check whether target control accept the child if it doesn't accept form and parent accept controls
					if (parent->isAcceptControls() && !data.Control->isAcceptForm())
					{
						String msg;
						if (!parent->isAcceptChild(data.Control))
							msg = L"This control cannot be placed here. The '" + parent->ClassName + L"' control doesn't accept '" + data.Control->ClassName + L"' as child.";
						else if (!data.Control->isAcceptControl(parent))
							msg = L"This control cannot be placed here. The '" + data.Control->ClassName + L"' control doesn't accept '" + parent->ClassName + L"' as parent.";
						if (!msg.empty())
						{
							data.Control->Release();
							data.Properties->Release();
							data.Events->Release();
							btn->setDown(false);
							Application->Dialogs->Error(msg);
							return;
						}
					}

					m_pControls->Add(data.Control, data.Events, data.Properties, data.PackageControl, data.Index);
					m_pFormEditor->DeselectAll();
					while (parent && parent != m_pFormEditor)
						if (data.Control->setParent(parent))
						{
							ide::IListItemHierarchyEditor *item{ m_pHierarchyEditor->Add(data.Control->Name, data.Control, data.Control, nullptr, parent, true) };
							item->setActive(true);
							item->setIconIndex(ICON_CONTROL);
							break;
						}
						else
							parent = parent->getParent();
					if (!data.Control->getParent())
					{
						if (!data.Control->isAcceptForm())
						{
							data.Control->Release();
							data.Events->Release();
							data.Properties->Release();
							btn->setDown(false);
							Application->Dialogs->Error(L"This control cannot be placed onto a form directly.");
							return;
						}
						data.Control->setParent(m_pFormEditor);
						ide::IListItemHierarchyEditor *item{ m_pHierarchyEditor->Add(data.Control->Name, data.Control, data.Control, nullptr) };
						item->setActive(true);
						item->setIconIndex(ICON_CONTROL);
					}
					m_pHierarchyEditor->ScrollToActiveItem();
					m_pFormEditor->SelectControl(data.Control);
					Mat4f mat{ ntl::Inversed<float>(data.Control->getParent()->getTransformControls()->getMatrix() * data.Control->getParent()->getTransformMatrix()) };
					Vec4f vec{ mat * Vec4f{ m.Position.X, m.Position.Y, 0, 1 } };
					PointF p{ vec.X, vec.Y };
					if (m_pFormEditor->getGridEnabled().X)
						p.X = ntl::Round<int>(p.X / m_pFormEditor->getGridSize().X) * m_pFormEditor->getGridSize().X;
					if (m_pFormEditor->getGridEnabled().Y)
						p.Y = ntl::Round<int>(p.Y / m_pFormEditor->getGridSize().Y) * m_pFormEditor->getGridSize().Y;
					if (data.PackageControl->isDisplayIcon())
					{
						p = m_pFormEditor->FormToLocal(m.Position);
						if (m_pFormEditor->getGridEnabled().X)
							p.X = ntl::Round<int>(p.X / m_pFormEditor->getGridSize().X) * m_pFormEditor->getGridSize().X;
						if (m_pFormEditor->getGridEnabled().Y)
							p.Y = ntl::Round<int>(p.Y / m_pFormEditor->getGridSize().Y) * m_pFormEditor->getGridSize().Y;
						m_pFormEditor->setControlPosition(data.Control, p);
					}
					else
						data.Control->getTransform()->Translate(p.X, p.Y, 0);
					HierarchyAddItems(data.Control, false);
					UpdateIsModified(true);
				}
			}
			if (btn)
				btn->setDown(false);
		}
	#pragma endregion

	#pragma region Layout dropdown events
		void CFormMain::DropDownLayout_OnSelect(IControl *sender, const int index)
		{
			m_pFormView->LoadLayout(m_aFormViewLayouts[index].FileName);
			m_iFormViewLayout = index;
			m_cFormEmpty.setSize(Point{ ntl::Round<int>(m_pFormEditor->getWidth()), ntl::Round<int>(m_pFormEditor->getHeight()) });
			if (m_pPropertyEditor->getPropertyListCount() == 1 && m_pPropertyEditor->getPropertyList(0) == m_pFormPropertyList) // To reflect changes of size
			{
				m_pPropertyEditor->Refresh(false);
				m_pPropertyEditor->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Loading callbacks
		void CFormMain::OnLoadComponent(IForm *sender, COMPONENT_INFO *info)
		{
			CFormMain *form{ cast<CFormMain*>(sender) };
			form->HierarchyAddItems(info->Component, true);
			for (int i = 0; i < info->Properties->getCount(); i++)
				if (info->Properties->getProperty(i)->isChanged() &&
					(info->Properties->getProperty(i)->Name == L"Name" || info->Properties->getProperty(i)->Name == L"Caption" || info->Properties->getProperty(i)->AffectItems))
					form->PropertyEditor_OnPropertyChange(form->m_pPropertyEditor, info->Properties->getProperty(i), info->Properties, info->Component);
		}

		void CFormMain::OnLoadControl(IForm *sender, CONTROL_INFO *info)
		{
			CFormMain *form{ cast<CFormMain*>(sender) };
			form->HierarchyAddItems(info->Control, true);
			for (int i = 0; i < info->Properties->getCount(); i++)
				if (info->Properties->getProperty(i)->isChanged() &&
					(info->Properties->getProperty(i)->Name == L"Name" || info->Properties->getProperty(i)->Name == L"Caption" || info->Properties->getProperty(i)->AffectItems))
					form->PropertyEditor_OnPropertyChange(form->m_pPropertyEditor, info->Properties->getProperty(i), info->Properties, info->Control);
		}
	#pragma endregion

	#pragma region Export
		void CFormMain::Export()
		{
			IExporter *exporter{ (m_cFormEmpty.Settings.ExportAs == ExportAs::DialogBox) ? m_pExporterDialogBox : m_pExporterForm };
			String form_name{ exporter->PrepareFormName(m_cFormEmpty.Name) };

			String filename{ ExtractDirectoryName(m_sFileName) + L"\\I" + form_name + L".h" };
			if (!exporter->Export(filename, m_cFormEmpty.Settings, m_pComponents, m_pControls, IExporter::Form{ form_name, m_pFormEventList, m_pFormPropertyList }, FB_VERSION, m_pFormEditor))
			{
				switch (exporter->getLastError())
				{
				case IExporter::ErrorType::FileOpen:
					Application->Dialogs->Error(L"Unable to open '" + filename + L"' for writing");
					break;
				case IExporter::ErrorType::NotBaseDialogBox:
					Application->Dialogs->Error(L"No base dialog box '[" + m_cFormEmpty.Settings.DialogBoxPackage + L"] " + m_cFormEmpty.Settings.DialogBoxClass + L"' found");
					break;
				default:
					Application->Dialogs->Error(L"Unknown error happend during exporting to '" + filename + L"'");
				}
			}
		}
	#pragma endregion

	#pragma region Dialog box callbacks
	#if defined(VS_INTEGRATION) || defined(USE_DIALOGBOXES)
		void CFormMain::DialogBoxConfiguration_OnClose(IDialogBox *sender, CloseAction &action)
		{
			if (sender->getModalResult() == ModalResult::Ok)
			{
				CFormMain *form{ cast<CFormMain*>(sender->getForm()) };
				form->m_pDialogBoxConfiguration->ToSettings(form->m_cFormEmpty.Settings);
				if (form->m_pDialogBoxConfiguration->isGlobal())
				{
					form->m_cFormEmpty.HasSettings = false;
					form->SaveSettings();
				}
				else
				{
					form->m_cFormEmpty.HasSettings = true;
					form->UpdateIsModified(true);
				}
				form->ApplySettings();
			}
		}
	#endif
	#pragma endregion

	#pragma region Create events
		void CFormMain::OnCreateListItem(IListItem *child, ide::IListItemHierarchyEditor *active)
		{
			IListItemCaption *c{ cast<IListItemCaption*>(child) };
			ide::IListItemHierarchyEditor *subitem{ new ide::CListItemHierarchyEditor(c ? c->getCaption() : L"Item", active->getAssignedComponent(), active->getAssignedControl(), child) };
			ide::IListItemHierarchyEditor *old_active{ active };
			subitem->setIconIndex(ICON_LISTITEM);
			if (!(active = m_pHierarchyEditor->Find(active->getAssignedComponent(), active->getAssignedControl(), child->getParent()))) // Item can be created at different location
				active = old_active;
			active->AddItem(subitem);
			m_pHierarchyEditor->Unfold(active);
			m_pFormEditor->DeselectAll();
			m_pHierarchyEditor->DeselectAllListItems();
			subitem->setActive(true);
			subitem->setSelected(true);
			m_pHierarchyEditor->ScrollToActiveItem();
			UpdateIsModified(true);
		}

		void CFormMain::OnCreateChild(CONTROL_INFO *info, IControl *control, ide::IListItemHierarchyEditor *active)
		{
			ide::IListItemHierarchyEditor *subitem{ new ide::CListItemHierarchyEditor(control->Name, control, control, nullptr) };
			subitem->setIconIndex(ICON_CONTROL);
			active->AddItem(subitem);
			int index;
			IPackageControl *package_control{ nullptr };
			for (int i = 0; i < Application->Editor->getControlCount(); i++)
				if (Application->Editor->getControl(i)->isInstance(control))
				{
					index = i;
					package_control = Application->Editor->getControl(i);
					break;
				}
			IPropertyList *properties{ package_control->CreatePropertyList(control) };
			IEventList *events{ package_control->CreateEventList(control) };
			info->PackageControl->getPackage()->QueryService()->NotifyOnCreateControl(control, package_control, properties, events);
			m_pControls->Add(control, events, properties, package_control, index);
			m_pFormEditor->DeselectAll();
			m_pHierarchyEditor->DeselectAllListItems();
			m_pFormEditor->SelectControl(control);
			HierarchyAddItems(control, false);
			m_pHierarchyEditor->Unfold(active);
			subitem->setActive(true);
			m_pHierarchyEditor->ScrollToActiveItem();
			UpdateIsModified(true);
		}
	#pragma endregion
	}
}