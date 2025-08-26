// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#if defined(__linux__) && !defined(__ANDROID__)
#include "../OpenGL/ngl.h"
#include <X11/cursorfont.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <string.h>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#if __has_include(<filesystem>)
	#include <filesystem>
#else
	#if __has_include(<experimental/filesystem>)
		#include <experimental/filesystem>
	#endif
#endif

#ifdef None
#undef None
#endif

namespace nitisa
{
	IApplication *Application{ nullptr };

	namespace platform
	{
		namespace linux
		{
			#include "../Data/DefaultFontData.inc"

			FT_Library FreeTypeLibrary{ nullptr };

		#pragma region Constructor and destructor
			CApplication::CApplication() :
				m_pService{ nullptr },
				m_cKeyboard{ this },
				m_cMouse{ this },
				m_cScreen{ this },
				m_cPicture{ this },
				m_cDialogs{ this },
				m_iExitCode{ 0 },
				m_sSearchWindow{ 0, nullptr, nullptr, true },
				m_bWindowsSorted{ true },
				m_aCursors{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				m_hRootWindow{ 0 },
				m_hClipboardWindow{ 0 },
				m_hInputMethod{ 0 },
				m_hInputContext{ 0 },
				m_hUTF8_STRING{ 0 },
				m_hCLIPBOARD{ 0 },
				m_hTIMER{ 0 },
				m_hWM_PROTOCOLS{ 0 },
				m_hWM_DELETE_WINDOW{ 0 },
				m_h_NET_WM_NAME{ 0 },
				m_h_NET_WM_STATE{ 0 },
				m_h_NET_WM_STATE_MODAL{ 0 },
				m_h_NET_WM_STATE_HIDDEN{ 0 },
				m_h_NET_WM_STATE_ABOVE{ 0 },
				m_h_NET_WM_STATE_MAXIMIZED_VERT{ 0 },
				m_h_NET_WM_STATE_MAXIMIZED_HORZ{ 0 },
				m_h_NET_WM_STATE_SKIP_TASKBAR{ 0 },
				m_h_NET_WM_STATE_SKIP_PAGER{ 0 },
				m_h_NET_WM_WINDOW_TYPE{ 0 },
				m_h_NET_WM_WINDOW_TYPE_NORMAL{ 0 },
				m_h_NET_WM_WINDOW_TYPE_DIALOG{ 0 },
				m_h_NET_REQUEST_FRAME_EXTENTS{ 0 },
				m_h_NET_FRAME_EXTENTS{ 0 },
				m_h_NET_ACTIVE_WINDOW{ 0 },
				m_h_NET_CLOSE_WINDOW{ 0 },
				OnDestroyLastWindow{ nullptr }
			{
				if (Application)
					throw "Only one application instance should exist";
				Application = this;

				*reinterpret_cast<int*>(&m_iTimerID) = 1;
				m_hHandle = 0;
				m_bDialogBoxes = false;
				m_bGlobal = true;
				m_pMainForm = nullptr;
				m_pKeyboard = &m_cKeyboard;
				m_pMouse = &m_cMouse;
				m_pTranslate = &m_cTranslate;
				m_pStyles = &m_cStyles;
				m_pScreen = &m_cScreen;
				m_pSystem = &m_cSystem;
				m_pPicture = &m_cPicture;
				m_pDialogs = &m_cDialogs;
				m_pFileSystem = &m_cFileSystem;
				m_pNetwork = &m_cNetwork;
				m_pDb = &m_cDb;
				m_pEditor = nullptr;

				OnIdle = nullptr;
				if ((*reinterpret_cast<Display**>(&m_hHandle) = XOpenDisplay(nullptr)))
				{
					setlocale(LC_ALL, "");
					*reinterpret_cast<Window*>(&m_hRootWindow) = RootWindow(*reinterpret_cast<Display**>(&m_hHandle), DefaultScreen(*reinterpret_cast<Display**>(&m_hHandle)));
					*reinterpret_cast<Window*>(&m_hClipboardWindow) = XCreateSimpleWindow(*reinterpret_cast<Display**>(&m_hHandle), *reinterpret_cast<Window*>(&m_hRootWindow), 0, 0, 640, 480, 0, 0, 0);
					XSetLocaleModifiers("");
					if (!(*reinterpret_cast<XIM*>(&m_hInputMethod) = XOpenIM(*reinterpret_cast<Display**>(&m_hHandle), nullptr, nullptr, nullptr)))
					{
						XSetLocaleModifiers("@im=none");
						*reinterpret_cast<XIM*>(&m_hInputMethod) = XOpenIM(*reinterpret_cast<Display**>(&m_hHandle), nullptr, nullptr, nullptr);
					}
					if (*reinterpret_cast<XIM*>(&m_hInputMethod))
					{
						if ((*reinterpret_cast<XIC*>(&m_hInputContext) = XCreateIC(*reinterpret_cast<XIM*>(&m_hInputMethod), XNInputStyle, XIMPreeditNothing | XIMStatusNothing, XNClientWindow,
							*reinterpret_cast<Window*>(&m_hClipboardWindow), 0)))
							XSetICFocus(*reinterpret_cast<XIC*>(&m_hInputContext));
					}
					*reinterpret_cast<Atom*>(&m_hUTF8_STRING) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "UTF8_STRING", False);
					*reinterpret_cast<Atom*>(&m_hCLIPBOARD) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "CLIPBOARD", False);
					*reinterpret_cast<Atom*>(&m_hTIMER) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "TIMER", False);
					*reinterpret_cast<Atom*>(&m_hWM_PROTOCOLS) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "WM_PROTOCOLS", False);
					*reinterpret_cast<Atom*>(&m_hWM_DELETE_WINDOW) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "WM_DELETE_WINDOW", False);
					*reinterpret_cast<Atom*>(&m_h_NET_WM_NAME) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "_NET_WM_NAME", False);
					*reinterpret_cast<Atom*>(&m_h_NET_WM_STATE) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "_NET_WM_STATE", False);
					*reinterpret_cast<Atom*>(&m_h_NET_WM_STATE_MODAL) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "_NET_WM_STATE_MODAL", False);
					*reinterpret_cast<Atom*>(&m_h_NET_WM_STATE_HIDDEN) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "_NET_WM_STATE_HIDDEN", False);
					*reinterpret_cast<Atom*>(&m_h_NET_WM_STATE_ABOVE) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "_NET_WM_STATE_ABOVE", False);
					*reinterpret_cast<Atom*>(&m_h_NET_WM_STATE_MAXIMIZED_VERT) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "_NET_WM_STATE_MAXIMIZED_VERT", False);
					*reinterpret_cast<Atom*>(&m_h_NET_WM_STATE_MAXIMIZED_HORZ) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "_NET_WM_STATE_MAXIMIZED_HORZ", False);
					*reinterpret_cast<Atom*>(&m_h_NET_WM_STATE_SKIP_TASKBAR) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "_NET_WM_STATE_SKIP_TASKBAR", False);
					*reinterpret_cast<Atom*>(&m_h_NET_WM_STATE_SKIP_PAGER) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "_NET_WM_STATE_SKIP_PAGER", False);
					*reinterpret_cast<Atom*>(&m_h_NET_WM_WINDOW_TYPE) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "_NET_WM_WINDOW_TYPE", False);
					*reinterpret_cast<Atom*>(&m_h_NET_WM_WINDOW_TYPE_NORMAL) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "_NET_WM_WINDOW_TYPE_NORMAL", False);
					*reinterpret_cast<Atom*>(&m_h_NET_WM_WINDOW_TYPE_DIALOG) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "_NET_WM_WINDOW_TYPE_DIALOG", False);
					*reinterpret_cast<Atom*>(&m_h_NET_REQUEST_FRAME_EXTENTS) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "_NET_REQUEST_FRAME_EXTENTS", False);
					*reinterpret_cast<Atom*>(&m_h_NET_FRAME_EXTENTS) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "_NET_FRAME_EXTENTS", False);
					*reinterpret_cast<Atom*>(&m_h_NET_ACTIVE_WINDOW) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "_NET_ACTIVE_WINDOW", False);
					*reinterpret_cast<Atom*>(&m_h_NET_CLOSE_WINDOW) = XInternAtom(*reinterpret_cast<Display**>(&m_hHandle), "_NET_CLOSE_WINDOW", False);
					XSetWMProtocols(*reinterpret_cast<Display**>(&m_hHandle), *reinterpret_cast<Window*>(&m_hClipboardWindow), reinterpret_cast<Atom*>(&m_hWM_DELETE_WINDOW), 1);
				}
				m_cStyles.Add(new CDefaultStyle());
				ReceiveApplicationPath();
				ReceiveModulePath();

				// FreeType
				FT_Init_FreeType(&FreeTypeLibrary);
			}

			CApplication::~CApplication()
			{
				if (*reinterpret_cast<Display**>(&m_hHandle))
				{
					if (*reinterpret_cast<XIC*>(&m_hInputContext))
						XDestroyIC(*reinterpret_cast<XIC*>(&m_hInputContext));
					if (*reinterpret_cast<XIM*>(&m_hInputMethod))
						XCloseIM(*reinterpret_cast<XIM*>(&m_hInputMethod));
					FreeCursors();
					if (*reinterpret_cast<Window*>(&m_hClipboardWindow))
						XDestroyWindow(*reinterpret_cast<Display**>(&m_hHandle), *reinterpret_cast<Window*>(&m_hClipboardWindow));
					XCloseDisplay(*reinterpret_cast<Display**>(&m_hHandle));
				}
				for (auto feature : m_aFeatures)
					feature->Release();
				if (m_pService)
					m_pService->Release();
				if (FreeTypeLibrary)
				{
					for (auto font_face : m_aFontFaces)
					{
						FT_Done_Face((FT_Face)font_face->Face);
						delete font_face;
					}
					FT_Done_FreeType(FreeTypeLibrary);
					FreeTypeLibrary = nullptr;
				}
				ngl::unload();
				Application = nullptr;
			}
		#pragma endregion

		#pragma region Getters
			int CApplication::getWindowCount()
			{
				return (int)m_aWindows.size();
			}

			IWindow *CApplication::getWindow(const int index)
			{
				if (index >= 0 && index < (int)m_aWindows.size())
					return m_aWindows[index].Wnd;
				return nullptr;
			}

			IForm *CApplication::getWindowForm(const int index)
			{
				if (index >= 0 && index < (int)m_aWindows.size())
					return m_aWindows[index].Form;
				return nullptr;
			}

			IApplicationService *CApplication::QueryService()
			{
				if (!m_pService)
					m_pService = new CApplicationService(this);
				return m_pService;
			}

			int CApplication::getFeatureCount()
			{
				return (int)m_aFeatures.size();
			}

			IFeature *CApplication::getFeature(const int index)
			{
				if (index < (int)m_aFeatures.size())
					return m_aFeatures[index];
				return nullptr;
			}

			IFeature *CApplication::getFeature(const String &name)
			{
				for (auto feature : m_aFeatures)
					if (feature->Name == name)
						return feature;
				return nullptr;
			}
		#pragma endregion

		#pragma region Setters
			bool CApplication::setMainForm(IForm *value)
			{
				if (value != m_pMainForm)
				{
					m_pMainForm = value;
					return true;
				}
				return false;
			}
		#pragma endregion

		#pragma region Process messages
			bool CApplication::ProcessMessage(IWindow *modal)
			{
				if (*reinterpret_cast<Display**>(&m_hHandle))
				{
					ProcessTimers();
					if (XPending(*reinterpret_cast<Display**>(&m_hHandle)) <= 0)
					{
						usleep(1000);
						return false;
					}
					XEvent e;
					XNextEvent(*reinterpret_cast<Display**>(&m_hHandle), &e);
					int index;
					CWindow *w;
					switch (e.type)
					{
					case KeyPress:
						w = nullptr;
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xkey.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))) && (!modal || modal == w))
							w->WindowProc(&e);
						if (*reinterpret_cast<XIC*>(&m_hInputContext) && XFilterEvent(&e, e.xkey.window) != True)
						{
							static wchar_t str[65];
							KeySym keysym;
							int status;
							String chars;
							int r{ XwcLookupString(*reinterpret_cast<XIC*>(&m_hInputContext), (XKeyPressedEvent*)&e, str, 64, &keysym, &status) };
							switch (status)
							{
							case XBufferOverflow:
								if (r > 0)
								{
									wchar_t *buffer{ new wchar_t[r + 1] };
									r = XwcLookupString(*reinterpret_cast<XIC*>(&m_hInputContext), (XKeyPressedEvent*)&e, buffer, r, &keysym, &status);
									if (status == XLookupChars || status == XLookupBoth)
									{
										buffer[r] = '\0';
										chars = buffer;
									}
									delete[] buffer;
								}
								break;
							case XLookupChars:
							case XLookupBoth:
								if (r > 0)
								{
									str[r] = '\0';
									chars = str;
								}
								break;
							}
							if (index >= 0 && w && (!modal || modal == w) && w->QueryService()->getListener())
								for (auto c : chars)
									w->QueryService()->getListener()->OnChar(MessageChar{ c });
						}
						break;
					case KeyRelease:
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xkey.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))) && (!modal || modal == w))
							w->WindowProc(&e);
						break;
					case ButtonPress:
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xbutton.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))) && (!modal || modal == w))
							w->WindowProc(&e);
						break;
					case ButtonRelease:
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xbutton.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))) && (!modal || modal == w))
							w->WindowProc(&e);
						break;
					case MotionNotify:
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xmotion.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))) && (!modal || modal == w))
							w->WindowProc(&e);
						break;
					case EnterNotify:
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xcrossing.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))) && (!modal || modal == w))
							w->WindowProc(&e);
						break;
					case LeaveNotify:
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xcrossing.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))) && (!modal || modal == w))
							w->WindowProc(&e);
						break;
					case FocusIn:
						if (*reinterpret_cast<XIC*>(&m_hInputContext))
							XSetICFocus(*reinterpret_cast<XIC*>(&m_hInputContext));
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xfocus.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))) && (!modal || modal == w))
							w->WindowProc(&e);
						break;
					case FocusOut:
						if (*reinterpret_cast<XIC*>(&m_hInputContext))
							XUnsetICFocus(*reinterpret_cast<XIC*>(&m_hInputContext));
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xfocus.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))) && (!modal || modal == w))
							w->WindowProc(&e);
						break;
					case Expose:
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xexpose.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))))
							w->WindowProc(&e);
						break;
					case ConfigureNotify:
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xconfigure.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))))
							w->WindowProc(&e);
						break;
					case DestroyNotify:
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xdestroywindow.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))))
						{
							DeleteTimers(w);
							w->WindowProc(&e);
							IForm *form{ getWindowForm(index) };
							DeleteWindow(index);
							if (((form && form == m_pMainForm) || getWindowCount() == 0) && m_bGlobal)
							{
								PlatformHandle h;
								for (int i = 0; i < getWindowCount(); i++)
									if (getWindowForm(i) != m_pMainForm)
									{
										if (getWindow(i))
										{
											if (getWindow(i)->getParent())
												continue;
										}
										h = getHandle(i);
										XDestroyWindow(*reinterpret_cast<Display**>(&m_hHandle), *reinterpret_cast<::Window*>(&h));
									}
								m_pMainForm = nullptr;
							}
							if (form)
								form->Release();
							w->Release();
							if (getWindowCount() == 0)
							{
								if (OnDestroyLastWindow)
									OnDestroyLastWindow();
								m_bTerminated = true;
							}
						}
						break;
					case MapNotify:
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xmap.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))))
							w->WindowProc(&e);
						break;
					case UnmapNotify:
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xunmap.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))))
							w->WindowProc(&e);
						break;
					case ClientMessage:
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xclient.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))) &&
							(!modal || modal == w || e.xclient.message_type != *reinterpret_cast<Atom*>(&m_hWM_PROTOCOLS) || (Atom)e.xclient.data.l[0] != *reinterpret_cast<Atom*>(&m_hWM_DELETE_WINDOW)))
							w->WindowProc(&e);
						break;
					case PropertyNotify:
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xproperty.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))))
							w->WindowProc(&e);
						break;
					case SelectionClear:
						m_sClipboardString = L"";
						break;
					case SelectionNotify:
						ProcessSelectionNotify(&e);
						break;
					case SelectionRequest:
						ProcessSelectionRequest(&e);
						break;
					default:
						if ((index = FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&e.xmap.window))) >= 0 && (w = cast<CWindow*>(getWindow(index))))
							w->WindowProc(&e);
						break;
					}
				}
				return true;
			}

			void CApplication::ProcessSelectionRequest(const void *ev)
			{
				const XSelectionRequestEvent *e{ (XSelectionRequestEvent*)ev };
				XSelectionEvent r;
				memset(&r, 0, sizeof(XSelectionEvent));
				r.type = SelectionNotify;
				r.requestor = e->requestor;
				r.selection = e->selection;
				r.target = e->target;
				r.time = e->time;
				r.property = 0;
				if (e->target == *reinterpret_cast<Atom*>(&m_hUTF8_STRING) && e->property != 0 && m_sClipboardString.length() > 0 && e->owner == *reinterpret_cast<Window*>(&m_hClipboardWindow))
				{
					UTF8String s{ StringToUTF8(m_sClipboardString) };
					XChangeProperty(
						*reinterpret_cast<Display**>(&m_hHandle),
						e->requestor,
						e->property,
						*reinterpret_cast<Atom*>(&m_hUTF8_STRING),
						8,
						PropModeReplace,
						reinterpret_cast<const unsigned char*>(s.c_str()),
						(int)s.length());
					r.property = e->property;
				}
				XSendEvent(*reinterpret_cast<Display**>(&m_hHandle), e->requestor, True, NoEventMask, reinterpret_cast<XEvent*>(&r));
			}

			void CApplication::ProcessSelectionNotify(const void *ev)
			{
				const XSelectionEvent *e{ (XSelectionEvent*)ev };
				if (e->selection != 0 && e->property != 0)
				{
					int index{ FindWindowIndex(*reinterpret_cast<const PlatformHandle*>(&e->requestor)) };
					if (index >= 0 && getWindow(index) && getWindow(index)->QueryService()->getListener())
					{
						bool succeeded;
						MessagePasteString m{ ReadUTF8Property(*reinterpret_cast<const PlatformHandle*>(&e->requestor), *reinterpret_cast<const PlatformHandle*>(&e->property), succeeded) };
						if (succeeded && m.Text.length() > 0)
							getWindow(index)->QueryService()->getListener()->OnPasteString(m);
					}
				}
			}

			void CApplication::ProcessMessages()
			{
				while (ProcessMessage(nullptr));
			}
		#pragma endregion

		#pragma region Helpers
			void CApplication::SortWindows()
			{
				if (!m_bWindowsSorted)
				{
					std::sort(m_aWindows.begin(), m_aWindows.end(), [](const WINDOW &a, const WINDOW &b) {return a.Handle < b.Handle; });
					m_bWindowsSorted = true;
				}
			}

			unsigned long CApplication::CursorTypeToShape(const CursorType type)
			{
				switch (type)
				{
				case CursorType::AppStarting: return XC_clock;
				case CursorType::Arrow: return XC_arrow;
				case CursorType::Cross: return XC_cross;
				case CursorType::Hand: return XC_hand1;
				case CursorType::Help: return XC_question_arrow;
				case CursorType::IBeam: return XC_xterm;
				case CursorType::No: return XC_circle;
				case CursorType::SizeAll: return XC_sizing;
				case CursorType::SizeNortheastSouthwest: return XC_bottom_right_corner;
				case CursorType::SizeNorthSouth: return XC_sb_v_double_arrow;
				case CursorType::SizeNorthwestSoutheast: return XC_bottom_left_corner;
				case CursorType::SizeWestEast: return XC_sb_h_double_arrow;
				case CursorType::UpArrow: return XC_draft_large;
				case CursorType::Wait: return XC_watch;
				default:
					return 0;
				}
			}

			PlatformHandle CApplication::getHandle(const int index)
			{
				if (index >= 0 && index < (int)m_aWindows.size())
					return m_aWindows[index].Handle;
				return 0;
			}

			bool CApplication::hasWindow(IWindow *window) const
			{
				for (auto info : m_aWindows)
					if (info.Wnd == window)
						return true;
				return false;
			}

			bool CApplication::setForm(const int index, IForm *form)
			{
				if (index >= 0 && index < (int)m_aWindows.size())
				{
					m_aWindows[index].Form = form;
					return true;
				}
				return false;
			}

			int CApplication::AddWindow(PlatformHandle handle, IWindow *window, IForm *form, bool enabled)
			{
				if (handle)
				{
					m_aWindows.push_back(WINDOW{ handle, window, form, enabled });
					m_bWindowsSorted = false;
					return (int)m_aWindows.size() - 1;
				}
				return -1;
			}

			bool CApplication::DeleteWindow(const int index)
			{
				if (index >= 0 && index < (int)m_aWindows.size())
				{
					m_aWindows.erase(m_aWindows.begin() + index);
					return true;
				}
				return false;
			}

			int CApplication::FindWindowIndex(PlatformHandle handle)
			{
				if (handle)
				{
					SortWindows();
					m_sSearchWindow.Handle = handle;
					std::vector<WINDOW>::iterator pos{ std::lower_bound(m_aWindows.begin(), m_aWindows.end(), m_sSearchWindow, [](const WINDOW &a, const WINDOW &b) {return a.Handle < b.Handle; }) };
					if (pos != m_aWindows.end() && pos->Handle == handle)
						return int(pos - m_aWindows.begin());
				}
				return -1;
			}

			PlatformHandle CApplication::CreateCursor(const CursorType type)
			{
				if (*reinterpret_cast<Display**>(&m_hHandle) && m_aCursors[(int)type] == 0 && type != CursorType::None)
				{
					Cursor c{ XCreateFontCursor(*reinterpret_cast<Display**>(&m_hHandle), (unsigned int)CursorTypeToShape(type)) };
					m_aCursors[(int)type] = *reinterpret_cast<PlatformHandle*>(&c);
				}
				return m_aCursors[(int)type];
			}

			void CApplication::FreeCursors()
			{
				if (*reinterpret_cast<Display**>(&m_hHandle))
				{
					for (auto c : m_aCursors)
						if (c > 0)
							XFreeCursor(*reinterpret_cast<Display**>(&m_hHandle), *reinterpret_cast<Cursor*>(&c));
				}
			}

			String CApplication::ReadUTF8Property(PlatformHandle handle, PlatformHandle name, bool &succeeded)
			{
				succeeded = false;
				if (*reinterpret_cast<Display**>(&m_hHandle) && *reinterpret_cast<Window*>(&handle) && *reinterpret_cast<Atom*>(&name))
				{
					Atom ret_type;
					int ret_format;
					unsigned long ret_nitems, ret_bytes_after;
					unsigned char *ret_prop;
					if (XGetWindowProperty(*reinterpret_cast<Display**>(&m_hHandle), *reinterpret_cast<Window*>(&handle), *reinterpret_cast<Atom*>(&name), 0, 1024, False,
						*reinterpret_cast<Atom*>(&m_hUTF8_STRING), &ret_type, &ret_format, &ret_nitems, &ret_bytes_after, &ret_prop) != Success)
						return L"";
					if (ret_type != *reinterpret_cast<Atom*>(&m_hUTF8_STRING))
					{
						XFree(ret_prop);
						return L"";
					}
					int size{ (ret_format / (32 / (int)sizeof(long))) * (int)ret_nitems };
					if (size == 0)
					{
						XFree(ret_prop);
						return L"";
					}
					char *result{ new char[size + 1] };
					memcpy(result, ret_prop, size);
					result[size] = '\0';
					XFree(ret_prop);
					succeeded = true;
					String r{ UTF8ToString(result) };
					delete[] result;
					return r;
				}
				return L"";
			}

			bool CApplication::UpdateUTF8Property(PlatformHandle handle, PlatformHandle name, const String &value)
			{
				if (*reinterpret_cast<Display**>(&m_hHandle) && *reinterpret_cast<Window*>(&handle) && *reinterpret_cast<Atom*>(&name))
				{
					UTF8String s{ StringToUTF8(value) };
					return XChangeProperty(*reinterpret_cast<Display**>(&m_hHandle), *reinterpret_cast<Window*>(&handle), *reinterpret_cast<Atom*>(&name), *reinterpret_cast<Atom*>(&m_hUTF8_STRING), 8,
						PropModeReplace, reinterpret_cast<const unsigned char*>(s.c_str()), (int)s.length()) == Success;
				}
				return false;
			}

			PlatformHandle CApplication::getActiveWindow(bool &succeeded)
			{
				succeeded = false;
				if (*reinterpret_cast<Display**>(&m_hHandle) && *reinterpret_cast<Window*>(&m_hRootWindow))
				{
					Atom type;
					int format;
					unsigned long nitems, bytes_after;
					unsigned char *prop;
					if (XGetWindowProperty(*reinterpret_cast<Display**>(&m_hHandle), *reinterpret_cast<Window*>(&m_hRootWindow), *reinterpret_cast<Atom*>(&m_h_NET_ACTIVE_WINDOW), 0, 1024, False,
						XA_WINDOW, &type, &format, &nitems, &bytes_after, &prop) != Success)
						return 0;
					if (type != XA_WINDOW || nitems < 1)
					{
						XFree(prop);
						return 0;
					}
					PlatformHandle result{ *reinterpret_cast<PlatformHandle*>(prop) };
					XFree(prop);
					succeeded = true;
					return result;
				}
				return 0;
			}

			CloseAction CApplication::getCloseAction(IWindow *window)
			{
				if (m_pMainForm)
					for (int i = 0; i < getWindowCount(); i++)
						if (getWindow(i) == window)
						{
							if (getWindowForm(i) && getWindowForm(i) != m_pMainForm)
								return CloseAction::Hide;
							break;
						}
				return CloseAction::Free;
			}

			CApplication::FONT_FACE *CApplication::FindFontFace(const String &name, bool is_default)
			{
				for (auto font_face : m_aFontFaces)
					if (font_face->Name == name && font_face->Default == is_default)
						return font_face;
				return nullptr;
			}

			CApplication::FONT_FACE *CApplication::LoadFontFace(const String &filename)
			{
				if (!FreeTypeLibrary)
					return nullptr;
				FONT_FACE *result{ FindFontFace(filename, true) };
				if (result)
				{
					result->RefCount++;
					return result;
				}
			#ifdef _WIN32
				std::ifstream f{ filename, std::ios::binary | std::ios::ate };
			#else
				#if __has_include(<filesystem>)
					std::ifstream f{ std::filesystem::path(filename), std::ios::binary | std::ios::ate };
				#else
					#if __has_include(<experimental/filesystem>)
						std::ifstream f{ std::experimental::filesystem::path(filename), std::ios::binary | std::ios::ate };
					#else
						std::ifstream f{ StringToAnsi(filename), std::ios::binary | std::ios::ate };
					#endif
				#endif
			#endif
				if (f.bad())
					return nullptr;
				int size{ (int)f.tellg() };
				if (size > 0)
				{
					char *buffer{ new char[size] };
					f.seekg(0);
					f.read(buffer, size);
					f.close();
					FT_Face face;
					if (FT_New_Memory_Face(FreeTypeLibrary, (const FT_Byte*)buffer, size, 0, &face) == 0)
					{
						result = new FONT_FACE;
						result->Face = face;
						result->Name = filename;
						result->RefCount = 1;
						result->Default = false;
					}
				}
				return result;
			}

			CApplication::FONT_FACE *CApplication::LoadDefaultFontFace(const String &filename)
			{
				if (!FreeTypeLibrary)
					return nullptr;
				FONT_FACE *result{ FindFontFace(filename, false) };
				if (result)
				{
					result->RefCount++;
					return result;
				}
				const FT_Byte *data{ nullptr };
				int size{ 0 };
				if (filename == L"Regular")
				{
					data = DefaultFontData_Regular;
					size = DefaultFontDataSize_Regular;
				}
				else if (filename == L"Italic")
				{
					data = DefaultFontData_Italic;
					size = DefaultFontDataSize_Italic;
				}
				else if (filename == L"Bold")
				{
					data = DefaultFontData_Bold;
					size = DefaultFontDataSize_Bold;
				}
				else if (filename == L"BoldItalic")
				{
					data = DefaultFontData_BoldItalic;
					size = DefaultFontDataSize_BoldItalic;
				}
				if (!data || size <= 0)
					return nullptr;
				FT_Face face;
				if (FT_New_Memory_Face(FreeTypeLibrary, (const FT_Byte*)data, size, 0, &face) == 0)
				{
					FONT_FACE *result{ new FONT_FACE };
					result->Face = face;
					result->Name = filename;
					result->RefCount = 1;
					result->Default = true;
					return result;
				}
				return nullptr;
			}

			void CApplication::FreeFontFace(FONT_FACE *face)
			{
				if (face && --face->RefCount <= 0)
				{
					FT_Done_Face((FT_Face)face->Face);
					for (auto pos = m_aFontFaces.begin(); pos != m_aFontFaces.end(); pos++)
						if ((*pos) == face)
						{
							m_aFontFaces.erase(pos);
							break;
						}
					delete face;
				}
			}

			int CApplication::Run()
			{
				if (getWindowCount() == 0)
					return m_iExitCode;
				m_bTerminated = false;
				do
				{
					if (!ProcessMessage(nullptr))
						if (OnIdle)
							OnIdle();
				} while (!m_bTerminated);
				return m_iExitCode;
			}

			void CApplication::RepaintAll()
			{
				for (int i = 0; i < getWindowCount(); i++)
					if (getWindowForm(i) && getWindowForm(i)->isVisible())
						getWindowForm(i)->Repaint();
			}

			IThread *CApplication::CreateThread(const bool paused, IThreadListener *listener)
			{
				if (listener)
				{
					CThread *thread{ new CThread(paused, listener) };
					if (thread->isCreated())
						return thread;
					thread->Release();
				}
				return nullptr;
			}

			bool CApplication::RegisterFeature(IFeature *feature)
			{
				if (feature)
				{
					m_aFeatures.push_back(feature);
					return true;
				}
				return false;
			}

			bool CApplication::UnregisterFeature(const int index)
			{
				if (index < (int)m_aFeatures.size())
				{
					m_aFeatures[index]->Release();
					m_aFeatures.erase(m_aFeatures.begin() + index);
					return true;
				}
				return false;
			}

			bool CApplication::UnregisterFeature(IFeature *feature)
			{
				if (feature)
				{
					for (auto pos = m_aFeatures.begin(); pos != m_aFeatures.end(); pos++)
						if (*pos == feature)
						{
							m_aFeatures.erase(pos);
							return true;
						}
				}
				return false;
			}

			bool CApplication::UnregisterFeature(const String &name)
			{
				bool changed{ false };
				auto pos{ m_aFeatures.begin() };
				while (pos != m_aFeatures.end())
					if ((*pos)->Name == name)
					{
						(*pos)->Release();
						pos = m_aFeatures.erase(pos);
						changed = true;
					}
					else
						pos++;
				return changed;
			}

			bool CApplication::UnregisterFeatures()
			{
				if (!m_aFeatures.empty())
				{
					for (auto feature : m_aFeatures)
						feature->Release();
					m_aFeatures.clear();
					return true;
				}
				return false;
			}

			void CApplication::ReceiveApplicationPath()
			{
				char buffer[1024];
				ssize_t l{ readlink("/proc/self/exe", buffer, 1024) };
				if (l > 0)
				{
					buffer[l] = 0;
					String name{ AnsiToString(buffer) };
					size_t pos{ name.find_last_of(L'/') };
					if (pos != String::npos)
					{
						m_sApplicationDirectory = name.substr(0, pos + 1);
						m_sApplicationFileName = name.substr(pos + 1);
					}
				}
			}

			void CApplication::ReceiveModulePath()
			{
				m_sModuleDirectory = m_sApplicationDirectory;
				m_sModuleFileName = m_sApplicationFileName;
			}
		#pragma endregion

		#pragma region Timers
			PlatformHandle CApplication::CreateTimer(IWindow *window, ITimerListener *listener, const float interval)
			{
				if (window && window->isCreated() && ntl::IsPositive<float>(interval))
				{
					m_aTimers.push_back(TIMER{ m_iTimerID, interval, window, listener, std::chrono::steady_clock::now() });
					(*reinterpret_cast<int*>(&m_iTimerID))++;
					return m_iTimerID;
				}
				return nullptr;
			}

			bool CApplication::ResetTimer(const PlatformHandle id, const float interval)
			{
				if (id > 0 && ntl::IsPositive<float>(interval))
					for (auto &timer : m_aTimers)
						if (timer.Id == id)
						{
							timer.Interval = interval;
							timer.Start = std::chrono::steady_clock::now();
							return true;
						}
				return false;
			}

			bool CApplication::DeleteTimer(const PlatformHandle id)
			{
				for (auto pos = m_aTimers.begin(); pos != m_aTimers.end(); pos++)
					if (pos->Id == id)
					{
						m_aTimers.erase(pos);
						return true;
					}
				return false;
			}

			bool CApplication::DeleteTimers(IWindow *window)
			{
				bool result{ false };
				if (window)
				{
					std::vector<TIMER>::iterator pos{ m_aTimers.begin() };
					while (pos != m_aTimers.end())
						if (pos->Wnd == window)
						{
							pos = m_aTimers.erase(pos);
							result = true;
						}
						else
							pos++;
				}
				return result;
			}

			void CApplication::DeleteTimers()
			{
				m_aTimers.clear();
			}

			void CApplication::ProcessTimers()
			{
				std::chrono::steady_clock::time_point n{ std::chrono::steady_clock::now() };
				for (auto &timer : m_aTimers)
					if (std::chrono::duration_cast<std::chrono::milliseconds>(n - timer.Start).count() >= int(1000 * timer.Interval))
					{
						timer.Listener->NotifyOnTimer(timer.Id);
						timer.Start = n;
					}
			}
		#pragma endregion
		}
	}
}
#endif