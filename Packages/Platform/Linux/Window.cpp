// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#if defined(__linux__) && !defined(__ANDROID__)
#include <string.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#ifdef None
#undef None
#endif

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
		#pragma region Constructor and destructor
			CWindow::CWindow() : CWindow(0)
			{

			}

			CWindow::CWindow(void *parent) :
				m_pApplication{ cast<CApplication*>(Application) },
				m_pParent{ nullptr },
				m_pModalFor{ nullptr },
				m_pService{ nullptr },
				m_eCurrentCursor{ CursorType::None },
				m_eModalResult{ ModalResult::None },
				m_iID{ 1 },
				m_sOldRect{ 0, 0, 0, 0 },
				m_bCursorSet{ false },
				m_bModal{ false },
				m_bEnabled{ false },
				m_bVisible{ false },
				m_hParent{ 0 },
				m_hVisualInfo{ 0 },
				m_hColormap{ 0 }
			{
				m_hHandle = 0;
				m_pListener = nullptr;
			}

			CWindow::~CWindow()
			{
				if (m_pService)
					m_pService->Release();
				if (*reinterpret_cast<Colormap*>(&m_hColormap))
					XFreeColormap(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Colormap*>(&m_hColormap));
				if (*reinterpret_cast<XVisualInfo**>(&m_hVisualInfo))
					XFree(*reinterpret_cast<XVisualInfo**>(&m_hVisualInfo));
			}

			void CWindow::Release()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
					XDestroyWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle));
				else
					delete this;
			}
		#pragma endregion

		#pragma region Getters
			bool CWindow::isCreated()
			{
				return *reinterpret_cast<Window*>(&m_hHandle) ? true : false;
			}

			bool CWindow::isVisible()
			{
				return *reinterpret_cast<Window*>(&m_hHandle) && m_bVisible;
			}

			bool CWindow::isEnabled()
			{
				return *reinterpret_cast<Window*>(&m_hHandle) && m_bEnabled;
			}

			bool CWindow::isAcceptDragAndDrop()
			{
				return false;
			}

			bool CWindow::isAcceptDropFiles()
			{
				return false;
			}

			String CWindow::getCaption()
			{
				String result;
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					bool succeeded;
					result = m_pApplication->ReadUTF8Property(m_hHandle, m_pApplication->m_h_NET_WM_NAME, succeeded);
					if (!succeeded)
					{
						char *name{ nullptr };
						if (XFetchName(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), &name) && name)
						{
							result = AnsiToString(name);
							XFree(name);
						}
					}
				}
				return result;
			}

			Rect CWindow::getRect()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					Window root;
					int x, y;
					unsigned int width, height, border, depth;
					if (XGetGeometry(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), &root, &x, &y, &width, &height, &border, &depth))
					{
						Point p{ ClientToScreen(Point{ x, y }) };
						return Rect{ p.X, p.Y, p.X + (int)width, p.Y + (int)height };
					}
				}
				return m_sOldRect;
			}

			Point CWindow::getSize()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					Window root;
					int x, y;
					unsigned int width, height, border, depth;
					if (XGetGeometry(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), &root, &x, &y, &width, &height, &border, &depth))
						return Point{ (int)width, (int)height };
				}
				return Point{ m_sOldRect.width(), m_sOldRect.height() };
			}

			Point CWindow::getPosition()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					Window root;
					int x, y;
					unsigned int width, height, border, depth;
					if (XGetGeometry(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), &root, &x, &y, &width, &height, &border, &depth))
						return ClientToScreen(Point{ x, y });
				}
				return m_sOldRect.LeftTop;
			}

			int CWindow::getLeft()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					Window root;
					int x, y;
					unsigned int width, height, border, depth;
					if (XGetGeometry(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), &root, &x, &y, &width, &height, &border, &depth))
						return ClientToScreen(Point{ x, y }).X;
				}
				return m_sOldRect.Left;
			}

			int CWindow::getTop()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					Window root;
					int x, y;
					unsigned int width, height, border, depth;
					if (XGetGeometry(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), &root, &x, &y, &width, &height, &border, &depth))
						return ClientToScreen(Point{ x, y }).Y;
				}
				return m_sOldRect.Top;
			}

			int CWindow::getWidth()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					Window root;
					int x, y;
					unsigned int width, height, border, depth;
					if (XGetGeometry(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), &root, &x, &y, &width, &height, &border, &depth))
						return (int)width;
				}
				return m_sOldRect.width();
			}

			int CWindow::getHeight()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					Window root;
					int x, y;
					unsigned int width, height, border, depth;
					if (XGetGeometry(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), &root, &x, &y, &width, &height, &border, &depth))
						return (int)height;
				}
				return m_sOldRect.height();
			}

			Rect CWindow::getClientRect()
			{
				Rect result{ getRect() };
				result.Right -= result.Left;
				result.Bottom -= result.Top;
				result.Left = result.Top = 0;
				return result;
			}

			Point CWindow::getClientSize()
			{
				return getSize();
			}

			int CWindow::getClientWidth()
			{
				return getWidth();
			}

			int CWindow::getClientHeight()
			{
				return getHeight();
			}

			WindowState CWindow::getState()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					if (!isVisible())
						return WindowState::Hidden;
					if (isMaximized())
						return WindowState::Maximized;
					if (isMinimized())
						return WindowState::Minimized;
				}
				return WindowState::Normal;
			}

			CreateParams CWindow::getCreateParams()
			{
				return m_sCreateParams;
			}

			IWindow *CWindow::getParent()
			{
				return m_pParent;
			}

			bool CWindow::hasProgressBar()
			{
				return false;
			}
		#pragma endregion

		#pragma region Setters
			bool CWindow::setVisible(const bool value)
			{
				return value ? Show() : Hide();
			}

			bool CWindow::setEnabled(const bool value)
			{
				if (value != m_bEnabled)
				{
					m_bEnabled = value;
					if (m_pListener)
						m_bEnabled ? m_pListener->OnEnable() : m_pListener->OnDisable();
					return true;
				}
				return false;
			}

			bool CWindow::setAcceptDrawAndDrop(const bool value)
			{
				return false;
			}

			bool CWindow::setAcceptDropFiles(const bool value)
			{
				return false;
			}

			bool CWindow::setCaption(const String &value)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					UTF8String caption{ StringToUTF8(value) };
					XChangeProperty(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_NAME),
						*reinterpret_cast<Atom*>(&m_pApplication->m_hUTF8_STRING), 8, PropModeReplace, reinterpret_cast<const unsigned char*>(caption.c_str()), (int)caption.length());
					//XStoreName(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), StringToAnsi(value).c_str());
					return true;
				}
				return false;
			}

			bool CWindow::setRect(const Rect &value)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					XWindowChanges changes;
					changes.x = value.Left;
					changes.y = value.Top;
					changes.width = value.width();
					changes.height = value.height();
					if (!m_sCreateParams.HasSizeBox)
						Constraints(Rect{ 0, 0, 0, 0 });
					XConfigureWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), CWX | CWY | CWWidth | CWHeight, &changes);
					if (!m_sCreateParams.HasSizeBox)
						Constraints(Rect{ changes.width, changes.height, changes.width, changes.height });
					return true;
				}
				return false;
			}

			bool CWindow::setSize(const Point &value)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					XWindowChanges changes;
					changes.width = value.X;
					changes.height = value.Y;
					if (!m_sCreateParams.HasSizeBox)
						Constraints(Rect{ 0, 0, 0, 0 });
					XConfigureWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), CWWidth | CWHeight, &changes);
					if (!m_sCreateParams.HasSizeBox)
						Constraints(Rect{ value.X, value.Y, value.X, value.Y });
					return true;
				}
				return false;
			}

			bool CWindow::setPosition(const Point &value)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					XWindowChanges changes;
					changes.x = value.X;
					changes.y = value.Y;
					XConfigureWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), CWX | CWY, &changes);
					return true;
				}
				return false;
			}

			bool CWindow::setLeft(const int value)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					XWindowChanges changes;
					changes.x = value;
					XConfigureWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), CWX, &changes);
					return true;
				}
				return false;
			}

			bool CWindow::setTop(const int value)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					XWindowChanges changes;
					changes.y = value;
					XConfigureWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), CWY, &changes);
					return true;
				}
				return false;
			}

			bool CWindow::setWidth(const int value)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					XWindowChanges changes;
					changes.width = value;
					if (!m_sCreateParams.HasSizeBox)
						Constraints(Rect{ 0, 0, 0, 0 });
					XConfigureWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), CWWidth, &changes);
					if (!m_sCreateParams.HasSizeBox)
						Constraints(Rect{ value, getHeight(), value, getHeight() });
					return true;
				}
				return false;
			}

			bool CWindow::setHeight(const int value)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					XWindowChanges changes;
					changes.height = value;
					if (!m_sCreateParams.HasSizeBox)
						Constraints(Rect{ 0, 0, 0, 0 });
					XConfigureWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), CWHeight, &changes);
					if (!m_sCreateParams.HasSizeBox)
						Constraints(Rect{ getWidth(), value, getWidth(), value });
					return true;
				}
				return false;
			}

			bool CWindow::setClientSize(const Point &value)
			{
				return setSize(value);
			}

			bool CWindow::setCursor(const CursorType value)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle) && (value != m_eCurrentCursor || !m_bCursorSet))
				{
					PlatformHandle cursor{ m_pApplication->CreateCursor(value) };
					if (cursor)
						XDefineCursor(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), *reinterpret_cast<Cursor*>(&cursor));
					else
						XUndefineCursor(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle));
					m_eCurrentCursor = value;
					m_bCursorSet = true;
					return true;
				}
				return false;
			}

			bool CWindow::setState(const WindowState value)
			{
				switch (value)
				{
				case WindowState::Normal:
					if (!isVisible())
						return Show();
					return Restore();
				case WindowState::Maximized:
					return Maximize();
				case WindowState::Minimized:
					return Minimize();
				case WindowState::Hidden:
					return Hide();
				}
				return false;
			}

			bool CWindow::setCreateParams(const CreateParams &value)
			{
				m_sCreateParams = value;
				return true;
			}

			bool CWindow::setParent(IWindow *value)
			{
				if (value != m_pParent)
				{
					if (*reinterpret_cast<Window*>(&m_hHandle))
					{
						if (value && !(*reinterpret_cast<const Window*>(&value->Handle)))
							return false;
						Window handle{ value ? *reinterpret_cast<const Window*>(&value->Handle) : *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow) };
						XReparentWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), handle, getLeft(), getTop());
					}
					m_pParent = value;
					return true;
				}
				return false;
			}

			bool CWindow::setModalResult(const ModalResult value)
			{
				if (m_bModal && value != m_eModalResult)
				{
					m_eModalResult = value;
					m_bModal = false;
					return true;
				}
				return false;
			}

			bool CWindow::setWindowPosition(const WindowPosition value)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle) && value != WindowPosition::Custom && getState() == WindowState::Normal)
					return setPosition(CalculateCreatePosition(getSize()));
				return false;
			}

			bool CWindow::setProgressType(const ProgressType value)
			{
				return false;
			}

			bool CWindow::setProgressValue(const float value)
			{
				return false;
			}
		#pragma endregion

		#pragma region Helpers
			void CWindow::Constraints(const Rect &constraints)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					XSizeHints *hints{ XAllocSizeHints() };
					if (hints)
					{
						hints->flags = PMinSize | PMaxSize;
						hints->min_width = constraints.Left;
						hints->max_width = constraints.Right;
						hints->min_height = constraints.Top;
						hints->max_height = constraints.Bottom;
						XSetWMNormalHints(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), hints);
						XFree(hints);
					}
				}
			}

			bool CWindow::hasAtom(PlatformHandle name, PlatformHandle needed, bool &succeeded)
			{
				succeeded = false;
				if (m_hHandle && *reinterpret_cast<Atom*>(&name) && *reinterpret_cast<Atom*>(&needed))
				{
					Atom ret_type;
					int ret_format;
					unsigned long ret_nitems, ret_bytes_after;
					unsigned char *ret_prop;
					if (XGetWindowProperty(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), *reinterpret_cast<Atom*>(&name), 0, 1024, False, XA_ATOM, &ret_type, &ret_format, &ret_nitems, &ret_bytes_after, &ret_prop) != Success)
						return false;
					if (ret_type != XA_ATOM)
					{
						XFree(ret_prop);
						return false;
					}
					Atom *atoms{ reinterpret_cast<Atom*>(ret_prop) };
					bool result{ false };
					for (unsigned long i = 0; i < ret_nitems; i++)
						if (atoms[i] == *reinterpret_cast<Atom*>(&needed))
						{
							result = true;
							break;
						}
					XFree(ret_prop);
					succeeded = true;
					return result;
				}
				return false;
			}

			bool CWindow::isMaximized()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle) && m_bVisible)
				{
					bool succeeded, minimized{ hasAtom(m_pApplication->m_h_NET_WM_STATE, m_pApplication->m_h_NET_WM_STATE_HIDDEN, succeeded) };
					if (succeeded && !minimized)
					{
						if (hasAtom(m_pApplication->m_h_NET_WM_STATE, m_pApplication->m_h_NET_WM_STATE_MAXIMIZED_VERT, succeeded) && succeeded)
							if (hasAtom(m_pApplication->m_h_NET_WM_STATE, m_pApplication->m_h_NET_WM_STATE_MAXIMIZED_HORZ, succeeded) && succeeded)
								return true;
					}
				}
				return false;
			}

			bool CWindow::isMinimized()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle) && m_bVisible)
				{
					bool succeeded, minimized{ hasAtom(m_pApplication->m_h_NET_WM_STATE, m_pApplication->m_h_NET_WM_STATE_HIDDEN, succeeded) };
					if (succeeded)
						return minimized;
				}
				return false;
			}

			bool CWindow::ActivateWindow()
			{
				if (*reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow) && *reinterpret_cast<Window*>(&m_hHandle))
				{
					XEvent e;
					memset(&e, 0, sizeof(XEvent));
					e.type = ClientMessage;
					e.xclient.send_event = True;
					e.xclient.message_type = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_ACTIVE_WINDOW);
					e.xclient.window = *reinterpret_cast<Window*>(&m_hHandle);
					e.xclient.format = 32;
					e.xclient.data.l[0] = 1;
					e.xclient.data.l[1] = CurrentTime;
					return XSendEvent(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), False, SubstructureRedirectMask | SubstructureNotifyMask, &e);
				}
				return false;
			}

			bool CWindow::Modal(IWindow *modal_for)
			{
				if (*reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow) && *reinterpret_cast<Window*>(&m_hHandle))
				{
					XEvent e;
					memset(&e, 0, sizeof(XEvent));
					e.type = ClientMessage;
					e.xclient.window = *reinterpret_cast<Window*>(&m_hHandle);
					e.xclient.message_type = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_STATE);
					e.xclient.format = 32;
					e.xclient.data.l[0] = CApplication::_NET_WM_STATE_ADD;
					e.xclient.data.l[1] = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_STATE_MODAL);
					XSendEvent(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), False, SubstructureNotifyMask | SubstructureRedirectMask, &e);
					if (modal_for)
					{
						e.xclient.data.l[1] = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_STATE_SKIP_TASKBAR);
						XSendEvent(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), False, SubstructureNotifyMask | SubstructureRedirectMask, &e);
						e.xclient.data.l[1] = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_STATE_SKIP_PAGER);
						XSendEvent(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), False, SubstructureNotifyMask | SubstructureRedirectMask, &e);
					}
					return true;
				}
				return false;
			}

			bool CWindow::Normal(IWindow *modal_for)
			{
				if (*reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow) && *reinterpret_cast<Window*>(&m_hHandle))
				{
					XEvent e;
					memset(&e, 0, sizeof(XEvent));
					e.type = ClientMessage;
					e.xclient.window = *reinterpret_cast<Window*>(&m_hHandle);
					e.xclient.message_type = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_STATE);
					e.xclient.format = 32;
					e.xclient.data.l[0] = CApplication::_NET_WM_STATE_REMOVE;
					e.xclient.data.l[1] = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_STATE_MODAL);
					XSendEvent(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), False, SubstructureNotifyMask | SubstructureRedirectMask, &e);
					if (modal_for)
					{
						e.xclient.data.l[1] = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_STATE_SKIP_TASKBAR);
						XSendEvent(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), False, SubstructureNotifyMask | SubstructureRedirectMask, &e);
						e.xclient.data.l[1] = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_STATE_SKIP_PAGER);
						XSendEvent(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), False, SubstructureNotifyMask | SubstructureRedirectMask, &e);
					}
					return true;
				}
				return false;
			}

			bool CWindow::DoClose()
			{
				if (*reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow) && *reinterpret_cast<Window*>(&m_hHandle))
				{
					XEvent e;
					memset(&e, 0, sizeof(XEvent));
					e.type = ClientMessage;
					e.xclient.window = *reinterpret_cast<Window*>(&m_hHandle);
					e.xclient.message_type = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_CLOSE_WINDOW);
					e.xclient.format = 32;
					return XSendEvent(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), False, SubstructureNotifyMask | SubstructureRedirectMask, &e);
				}
				return false;
			}

			Key CWindow::KeyCodeToKey(const PlatformHandle keycode)
			{
				Key result{ Key::Unknown };
				if (m_pApplication->m_hHandle)
				{
					int count;
					KeySym *syms{ XGetKeyboardMapping(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<const KeyCode*>(&keycode), 1, &count) };
					if (syms)
					{
						for (int i = 0; i < count; i++)
							if (syms[i] != NoSymbol)
							{
								result = VirtualToKey((int)syms[i]);
								if (result != Key::Unknown)
									break;
							}
						XFree(syms);
					}
				}
				return result;
			}

			bool CWindow::Show()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
					return XMapWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle)) ? true : false;
				return false;
			}

			ModalResult CWindow::ShowModal()
			{
				m_eModalResult = ModalResult::None;
				if (*reinterpret_cast<Window*>(&m_hHandle) && !m_bModal)
				{
					bool succeeded;
					PlatformHandle parent{ m_pApplication->getActiveWindow(succeeded) };
					int index;
					if (succeeded && *reinterpret_cast<Window*>(&parent) && *reinterpret_cast<Window*>(&parent) != *reinterpret_cast<Window*>(&m_hHandle) &&
						(index = m_pApplication->FindWindowIndex(parent)) >= 0)
					{
						m_pModalFor = m_pApplication->getWindow(index);
						XSetTransientForHint(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), *reinterpret_cast<Window*>(&parent));
					}
					else
						m_pModalFor = nullptr;
					setEnabled(true);
					ActivateWindow();
					XMapRaised(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle));
					Modal(m_pModalFor);
					m_bModal = true;
					while (m_bModal)
						m_pApplication->ProcessMessage(this);
					if (*reinterpret_cast<Window*>(&m_hHandle))
						DoClose();
				}
				return m_eModalResult;
			}

			bool CWindow::Hide()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
					return XUnmapWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle)) == Success;
				return false;
			}

			bool CWindow::Create()
			{
				if (m_pParent)
					return Create(m_pParent);
				return Create(m_hParent);
			}

			bool CWindow::Create(IWindow *parent)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
					return false;
				if (parent && !(*reinterpret_cast<const Window*>(&parent->Handle)))
					return false;
				m_pParent = parent;
				return Create(m_pParent ? m_pParent->Handle : 0);
			}

			bool CWindow::Create(const PlatformHandle parent)
			{
				if (*reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow))
				{
					const Window hparent{ *reinterpret_cast<const Window*>(&parent) ? *reinterpret_cast<const Window*>(&parent) : *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow) };
					Point position{ CalculateCreatePosition(m_sCreateParams.Size) };
					XSetWindowAttributes attributes, *pattributes{ nullptr };
					attributes.override_redirect = True;
					unsigned long attributes_mask{ 0 };
					if (m_sCreateParams.IsPopup)
					{
						attributes_mask |= CWOverrideRedirect;
						pattributes = &attributes;
					}
					if (*reinterpret_cast<XVisualInfo**>(&m_hVisualInfo))
					{
						attributes.colormap = *reinterpret_cast<Colormap*>(&m_hColormap) = XCreateColormap(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle),
							*reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), (*reinterpret_cast<XVisualInfo**>(&m_hVisualInfo))->visual, AllocNone);
						attributes_mask |= CWColormap;
						pattributes = &attributes;
					}
					if ((*reinterpret_cast<Window*>(&m_hHandle) = XCreateWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), hparent, position.X, position.Y,
						m_sCreateParams.Size.X, m_sCreateParams.Size.Y, 0, (*reinterpret_cast<XVisualInfo**>(&m_hVisualInfo))->depth, InputOutput, (*reinterpret_cast<XVisualInfo**>(&m_hVisualInfo))->visual,
						attributes_mask, pattributes)))
					{
						XSelectInput(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), KeyPressMask | KeyReleaseMask | ButtonPressMask |
							ButtonReleaseMask | EnterWindowMask | LeaveWindowMask | PointerMotionMask | ButtonMotionMask | ExposureMask | StructureNotifyMask | SubstructureNotifyMask |
							FocusChangeMask | PropertyChangeMask);
						m_bEnabled = m_sCreateParams.IsEnabled;
						XSetWMProtocols(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), reinterpret_cast<Atom*>(&m_pApplication->m_hWM_DELETE_WINDOW), 1);
						XChangeProperty(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_WINDOW_TYPE),
							XA_ATOM, 32, PropModeAppend, reinterpret_cast<unsigned char*>(&m_pApplication->m_h_NET_WM_WINDOW_TYPE_NORMAL), 1);
						XChangeProperty(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_WINDOW_TYPE),
							XA_ATOM, 32, PropModeAppend, reinterpret_cast<unsigned char*>(&m_pApplication->m_h_NET_WM_WINDOW_TYPE_DIALOG), 1);
						m_pApplication->AddWindow(m_hHandle, this, nullptr, m_bEnabled);
						if (m_sCreateParams.IsTopMost)
						{
							XEvent e;
							memset(&e, 0, sizeof(XEvent));
							e.type = ClientMessage;
							e.xclient.window = *reinterpret_cast<Window*>(&m_hHandle);
							e.xclient.message_type = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_STATE);
							e.xclient.format = 32;
							e.xclient.data.l[0] = CApplication::_NET_WM_STATE_ADD;
							e.xclient.data.l[1] = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_STATE_ABOVE);
							XSendEvent(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), False, SubstructureNotifyMask | SubstructureRedirectMask, &e);
						}
						if (!m_sCreateParams.HasSizeBox)
							Constraints(Rect{ getWidth(), getHeight(), getWidth(), getHeight() });
						switch (m_sCreateParams.State)
						{
						case WindowState::Maximized:
							Maximize();
							XMapWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle));
							break;
						case WindowState::Minimized:
							XMapWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle));
							Minimize();
							break;
						case WindowState::Normal:
							XMapWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle));
							break;
						default:
							break;
						}
						setCursor(m_eCurrentCursor);
						setCaption(m_sCreateParams.Caption);
						return true;
					}
				}
				return false;
			}

			bool CWindow::Create(const CreateParams &params)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
					return false;
				m_sCreateParams = params;
				return Create();
			}

			bool CWindow::Create(const CreateParams &params, IWindow *parent)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
					return false;
				m_sCreateParams = params;
				return Create(parent);
			}

			PlatformHandle CWindow::CreateTimer(ITimerListener *listener, const float interval)
			{
				if (!(*reinterpret_cast<Window*>(&m_hHandle)) || !listener || ntl::IsLess<float>(interval, 0))
					return nullptr;
				return m_pApplication->CreateTimer(this, listener, interval);
			}

			bool CWindow::DeleteTimer(const PlatformHandle id)
			{
				return m_pApplication->DeleteTimer(id);
			}

			void CWindow::DeleteTimers()
			{
				m_pApplication->DeleteTimers(this);
			}

			bool CWindow::ResetTimer(const PlatformHandle id, const float interval)
			{
				if (ntl::IsLess<float>(interval, 0))
					return false;
				return m_pApplication->ResetTimer(id, interval);
			}

			bool CWindow::CaptureMouse()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					PlatformHandle cursor{ m_pApplication->CreateCursor(m_eCurrentCursor) };
					return XGrabPointer(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), False, ButtonPressMask | ButtonReleaseMask |
						PointerMotionMask | ButtonMotionMask, GrabModeAsync, GrabModeAsync, 0, *reinterpret_cast<Cursor*>(&cursor), CurrentTime) == GrabSuccess;
				}
				return false;
			}

			void CWindow::ReleaseMouseCapture()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
					XUngrabPointer(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), CurrentTime);
			}

			bool CWindow::Maximize()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					XEvent e;
					memset(&e, 0, sizeof(XEvent));
					e.type = ClientMessage;
					e.xclient.window = *reinterpret_cast<Window*>(&m_hHandle);
					e.xclient.message_type = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_STATE);
					e.xclient.format = 32;
					e.xclient.data.l[0] = CApplication::_NET_WM_STATE_ADD;
					e.xclient.data.l[1] = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_STATE_MAXIMIZED_HORZ);
					e.xclient.data.l[2] = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_STATE_MAXIMIZED_VERT);
					return XSendEvent(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), False, SubstructureNotifyMask | SubstructureRedirectMask, &e);
				}
				return false;
			}

			bool CWindow::Minimize()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
					return XIconifyWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), DefaultScreen(*reinterpret_cast<Display**>(m_pApplication->m_hHandle))) == Success;
				return false;
			}

			bool CWindow::Restore()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					switch (getState())
					{
					case WindowState::Maximized:
					{
						XEvent e;
						memset(&e, 0, sizeof(XEvent));
						e.type = ClientMessage;
						e.xclient.window = *reinterpret_cast<Window*>(&m_hHandle);
						e.xclient.message_type = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_STATE);
						e.xclient.format = 32;
						e.xclient.data.l[0] = CApplication::_NET_WM_STATE_REMOVE;
						e.xclient.data.l[1] = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_STATE_MAXIMIZED_HORZ);
						e.xclient.data.l[2] = *reinterpret_cast<Atom*>(&m_pApplication->m_h_NET_WM_STATE_MAXIMIZED_VERT);
						return XSendEvent(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), False, SubstructureNotifyMask | SubstructureRedirectMask, &e);
					}
					case WindowState::Minimized:
						return ActivateWindow();
					case WindowState::Hidden:
						return Show();
					default:
						break;
					}
				}
				return false;
			}

			bool CWindow::Close()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
					return DoClose();
				return false;
			}

			int CWindow::GenerateID()
			{
				return m_iID++;
			}

			bool CWindow::CopyStringToClipboard(const String &str)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle) && str.length() > 0 && *reinterpret_cast<Window*>(&m_pApplication->m_hClipboardWindow))
				{
					m_pApplication->m_sClipboardString = str;
					XSetSelectionOwner(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Atom*>(&m_pApplication->m_hCLIPBOARD),
						*reinterpret_cast<Window*>(&m_pApplication->m_hClipboardWindow), CurrentTime);
					return true;
				}
				return false;
			}

			bool CWindow::CopyStringFromClipboard()
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					Window owner{ XGetSelectionOwner(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Atom*>(&m_pApplication->m_hCLIPBOARD)) };
					if (owner)
					{
						XConvertSelection(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Atom*>(&m_pApplication->m_hCLIPBOARD),
							*reinterpret_cast<Atom*>(&m_pApplication->m_hUTF8_STRING), *reinterpret_cast<Atom*>(&m_pApplication->m_hCLIPBOARD), *reinterpret_cast<Window*>(&m_hHandle), CurrentTime);
						return true;
					}
				}
				return false;
			}

			Rect CWindow::ScreenToClient(const Rect &rect)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					Rect result;
					Window child;
					if (XTranslateCoordinates(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), *reinterpret_cast<Window*>(&m_hHandle),
							rect.Left, rect.Top, &result.Left, &result.Top, &child) == True &&
						XTranslateCoordinates(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), *reinterpret_cast<Window*>(&m_hHandle),
							rect.Right, rect.Bottom, &result.Right, &result.Bottom, &child) == True)
						return result;
				}
				return rect;
			}

			Point CWindow::ScreenToClient(const Point &pos)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					Point result;
					Window child;
					if (XTranslateCoordinates(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), *reinterpret_cast<Window*>(&m_hHandle),
						pos.X, pos.Y, &result.X, &result.Y, &child) == True)
						return result;
				}
				return pos;
			}

			Rect CWindow::ClientToScreen(const Rect &rect)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					Rect result;
					Window child;
					if (XTranslateCoordinates(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow),
							rect.Left, rect.Top, &result.Left, &result.Top, &child) == True &&
						XTranslateCoordinates(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow),
							rect.Right, rect.Bottom, &result.Right, &result.Bottom, &child) == True)
						return result;
				}
				return rect;
			}

			Point CWindow::ClientToScreen(const Point &pos)
			{
				if (*reinterpret_cast<Window*>(&m_hHandle))
				{
					Point result;
					Window child;
					if (XTranslateCoordinates(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow),
						pos.X, pos.Y, &result.X, &result.Y, &child) == True)
						return result;
				}
				return pos;
			}

			IWindowService *CWindow::QueryService()
			{
				if (!m_pService)
					m_pService = new CWindowService(this);
				return m_pService;
			}

			Point CWindow::CalculateCreatePosition(const Point &size)
			{
				switch (m_sCreateParams.WindowPosition)
				{
				case WindowPosition::ScreenLeftTop:
					return Point{ 0, 0 };
				case WindowPosition::ScreenRightTop:
					return Point{ XWidthOfScreen(ScreenOfDisplay(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), DefaultScreen(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle)))) - size.X, 0 };
				case WindowPosition::ScreenLeftBottom:
					return Point{ 0, XHeightOfScreen(ScreenOfDisplay(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), DefaultScreen(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle)))) - size.Y };
				case WindowPosition::ScreenRightBottom:
					return Point{
						XWidthOfScreen(ScreenOfDisplay(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), DefaultScreen(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle)))) - size.X,
						XHeightOfScreen(ScreenOfDisplay(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), DefaultScreen(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle)))) - size.Y };
				case WindowPosition::ScreenCenter:
					return Point{
						(XWidthOfScreen(ScreenOfDisplay(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), DefaultScreen(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle)))) - size.X) / 2,
						(XHeightOfScreen(ScreenOfDisplay(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), DefaultScreen(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle)))) - size.Y) / 2 };
				case WindowPosition::MainFormLeftTop:
					if (m_pParent)
						return m_pParent->getRect().LeftTop;
					break;
				case WindowPosition::MainFormRightTop:
					if (m_pParent)
					{
						Rect r{ m_pParent->getRect() };
						return Point{ r.Right - size.X, r.Top };
					}
					break;
				case WindowPosition::MainFormLeftBottom:
					if (m_pParent)
					{
						Rect r{ m_pParent->getRect() };
						return Point{ r.Left, r.Bottom - size.Y };
					}
					break;
				case WindowPosition::MainFormRightBottom:
					if (m_pParent)
					{
						Rect r{ m_pParent->getRect() };
						return Point{ r.Right - size.X, r.Bottom - size.Y };
					}
					break;
				case WindowPosition::MainFormCenter:
					if (m_pParent)
					{
						Rect r{ m_pParent->getRect() };
						return Point{ (r.Left + r.Right - size.X) / 2, (r.Top + r.Bottom - size.Y) / 2 };
					}
					break;
				default:
					break;
				}
				return Point{
					((unsigned int)m_sCreateParams.Position.X == 0x80000000) ? 0 : m_sCreateParams.Position.X,
					((unsigned int)m_sCreateParams.Position.Y == 0x80000000) ? 0 : m_sCreateParams.Position.Y };
			}

			IWindow *CWindow::CreateInstance()
			{
				return new CWindow();
			}

			void CWindow::ProcessKeyPress(const void *ev)
			{
				if (m_pListener && m_bEnabled)
				{
					KeyCode kc{ KeyCode(((XKeyPressedEvent*)ev)->keycode) };
					m_pListener->OnKeyDown(MessageKey{ KeyCodeToKey(*reinterpret_cast<PlatformHandle*>(&kc)), nullptr });
				}
			}

			void CWindow::ProcessKeyRelease(const void *ev)
			{
				if (m_pListener && m_bEnabled)
				{
					KeyCode kc{ KeyCode(((XKeyReleasedEvent*)ev)->keycode) };
					m_pListener->OnKeyUp(MessageKey{ KeyCodeToKey(*reinterpret_cast<PlatformHandle*>(&kc)), nullptr });
				}
			}

			void CWindow::ProcessButtonPress(const void *ev)
			{
				if (m_pListener && m_bEnabled)
				{
					XButtonPressedEvent *e{ (XButtonPressedEvent*)ev };
					bool left{ (e->state & Button1Mask) != 0 };
					bool right{ (e->state & Button3Mask) != 0 };
					bool middle{ (e->state & Button2Mask) != 0 };
					bool shift{ (e->state & ShiftMask) != 0 };
					bool ctrl{ (e->state & ControlMask) != 0 };
					bool alt{ (e->state & Mod1Mask) != 0 };
					switch (e->button)
					{
					case Button1:
						m_pListener->OnLeftMouseButtonDown(MessageMouse{ PointF{ (float)e->x, (float)e->y }, ctrl, alt, shift, true, middle, right, nullptr });
						break;
					case Button3:
						m_pListener->OnRightMouseButtonDown(MessageMouse{ PointF{ (float)e->x, (float)e->y }, ctrl, alt, shift, left, middle, true, nullptr });
						break;
					case Button2:
						m_pListener->OnMiddleMouseButtonDown(MessageMouse{ PointF{ (float)e->x, (float)e->y }, ctrl, alt, shift, left, true, right, nullptr });
						break;
					case Button4:
						m_pListener->OnMouseVerticalWheel(MessageMouseWheel{ PointF{ (float)e->x, (float)e->y }, ctrl, alt, shift, left, middle, right, 1, nullptr });
						break;
					case Button5:
						m_pListener->OnMouseVerticalWheel(MessageMouseWheel{ PointF{ (float)e->x, (float)e->y }, ctrl, alt, shift, left, middle, right, -1, nullptr });
						break;
					}
				}
			}

			void CWindow::ProcessButtonRelease(const void *ev)
			{
				if (m_pListener && m_bEnabled)
				{
					XButtonReleasedEvent *e{ (XButtonReleasedEvent*)ev };
					bool left{ (e->state & Button1Mask) != 0 };
					bool right{ (e->state & Button3Mask) != 0 };
					bool middle{ (e->state & Button2Mask) != 0 };
					bool shift{ (e->state & ShiftMask) != 0 };
					bool ctrl{ (e->state & ControlMask) != 0 };
					bool alt{ (e->state & Mod1Mask) != 0 };
					switch (e->button)
					{
					case Button1:
						m_pListener->OnLeftMouseButtonUp(MessageMouse{ PointF{ (float)e->x, (float)e->y }, ctrl, alt, shift, true, middle, right, nullptr });
						break;
					case Button3:
						m_pListener->OnRightMouseButtonUp(MessageMouse{ PointF{ (float)e->x, (float)e->y }, ctrl, alt, shift, left, middle, true, nullptr });
						break;
					case Button2:
						m_pListener->OnMiddleMouseButtonUp(MessageMouse{ PointF{ (float)e->x, (float)e->y }, ctrl, alt, shift, left, true, right, nullptr });
						break;
					}
				}
			}

			void CWindow::ProcessMotion(const void *ev)
			{
				if (m_pListener && m_bEnabled)
				{
					XPointerMovedEvent *e{ (XPointerMovedEvent*)ev };
					bool left{ (e->state & Button1Mask) != 0 };
					bool right{ (e->state & Button3Mask) != 0 };
					bool middle{ (e->state & Button2Mask) != 0 };
					bool shift{ (e->state & ShiftMask) != 0 };
					bool ctrl{ (e->state & ControlMask) != 0 };
					bool alt{ (e->state & Mod1Mask) != 0 };
					m_pListener->OnMouseMove(MessageMouse{ PointF{ (float)e->x, (float)e->y }, ctrl, alt, shift, left, middle, right, nullptr });
				}
			}

			void CWindow::ProcessEnter(const void *ev)
			{
				if (m_pListener && m_bEnabled)
				{
					XEnterWindowEvent *e{ (XEnterWindowEvent*)ev };
					bool left{ (e->state & Button1Mask) != 0 };
					bool right{ (e->state & Button3Mask) != 0 };
					bool middle{ (e->state & Button2Mask) != 0 };
					bool shift{ (e->state & ShiftMask) != 0 };
					bool ctrl{ (e->state & ControlMask) != 0 };
					bool alt{ (e->state & Mod1Mask) != 0 };
					m_pListener->OnMouseHover(MessageMouse{ PointF{ (float)e->x, (float)e->y }, ctrl, alt, shift, left, middle, right, nullptr });
				}
			}

			void CWindow::ProcessLeave()
			{
				if (m_pListener && m_bEnabled)
					m_pListener->OnMouseLeave();
			}

			void CWindow::ProcessFocusIn()
			{
				if (m_pListener)
					m_pListener->OnSetFocus();
			}

			void CWindow::ProcessFocusOut()
			{
				if (m_pListener)
					m_pListener->OnKillFocus();
			}

			void CWindow::ProcessExpose(const void *ev)
			{
				XExposeEvent *e{ (XExposeEvent*)ev };
				if (m_pListener && e->count == 0)
					m_pListener->OnPaint(MessageRect{ (RectF)getClientRect() });
			}

			void CWindow::ProcessConfigure(const void *ev)
			{
				XConfigureEvent *e{ (XConfigureEvent*)ev };
				if (m_pListener && (e->x != m_sOldRect.Left || e->y != m_sOldRect.Top || e->width != m_sOldRect.width() || e->height != m_sOldRect.height()))
				{
					if (e->width != m_sOldRect.width() || e->height != m_sOldRect.height())
					{
						MessageWindowResizing m{ Rect{ e->x, e->y, e->x + e->width, e->y + e->height }, EdgeType::None };
						if (e->x == m_sOldRect.Left && e->y == m_sOldRect.Top && e->width == m_sOldRect.width() && e->height != m_sOldRect.height())
							m.Edge = EdgeType::Bottom;
						else if (e->x != m_sOldRect.Left && e->y == m_sOldRect.Top && e->x + e->width == m_sOldRect.Right && e->height != m_sOldRect.height())
							m.Edge = EdgeType::BottomLeft;
						else if (e->x == m_sOldRect.Left && e->y == m_sOldRect.Top && e->width != m_sOldRect.width() && e->height != m_sOldRect.height())
							m.Edge = EdgeType::BottomRight;
						else if (e->x != m_sOldRect.Left && e->y == m_sOldRect.Top && e->x + e->width == m_sOldRect.Right && e->height == m_sOldRect.height())
							m.Edge = EdgeType::Left;
						else if (e->x == m_sOldRect.Left && e->y == m_sOldRect.Top && e->width != m_sOldRect.width() && e->height == m_sOldRect.height())
							m.Edge = EdgeType::Right;
						else if (e->x == m_sOldRect.Left && e->y != m_sOldRect.Top && e->width == m_sOldRect.width() && e->y + e->height == m_sOldRect.Bottom)
							m.Edge = EdgeType::Top;
						else if (e->x != m_sOldRect.Left && e->y != m_sOldRect.Top && e->x + e->width == m_sOldRect.Right && e->y + e->height == m_sOldRect.Bottom)
							m.Edge = EdgeType::TopLeft;
						else if (e->x == m_sOldRect.Left && e->y != m_sOldRect.Top && e->width != m_sOldRect.width() && e->y + e->height == m_sOldRect.Bottom)
							m.Edge = EdgeType::TopRight;
						m_pListener->OnResizing(m);
					}
					else
						m_pListener->OnMove(MessagePosition{ PointF{ (float)e->x, (float)e->y } });
					m_sOldRect = Rect{ e->x, e->y, e->x + e->width, e->y + e->height };
				}
			}

			void CWindow::ProcessDestroy()
			{
				if (m_pListener)
					m_pListener->OnDestroy();
				m_bModal = false;
				m_hHandle = 0;
			}

			void CWindow::ProcessMap()
			{
				m_bVisible = true;
				if (m_pListener)
					m_pListener->OnShow();
			}

			void CWindow::ProcessUnmap()
			{
				m_bVisible = false;
				if (m_pListener)
					m_pListener->OnHide();
				if (m_bModal)
				{
					m_bModal = false;
					Normal(m_pModalFor);
					m_pModalFor = nullptr;
					XDeleteProperty(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle), XA_WM_TRANSIENT_FOR);
				}
			}

			bool CWindow::ProcessClientMessage(const void *ev)
			{
				XClientMessageEvent *e{ (XClientMessageEvent*)ev };
				if (e->message_type == *reinterpret_cast<Atom*>(&m_pApplication->m_hWM_PROTOCOLS))
				{
					if (e->format == 32 && (Atom)e->data.l[0] == *reinterpret_cast<Atom*>(&m_pApplication->m_hWM_DELETE_WINDOW))
					{
						CloseAction action{ m_pApplication->getCloseAction(this) };
						if (m_pListener)
							m_pListener->OnClose(action);
						switch (action)
						{
						case CloseAction::Hide:
							Hide();
							break;
						case CloseAction::Free:
							if (m_pListener)
							{
								m_pListener->OnDestroy();
								m_pListener = nullptr;
							}
							m_bModal = false;
							m_pModalFor = nullptr;
							XDestroyWindow(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_hHandle));
							m_hHandle = 0;
							break;
						case CloseAction::Minimize:
							Minimize();
							if (m_bModal && m_pModalFor && m_pApplication->hasWindow(m_pModalFor))
								m_pModalFor->Minimize();
							break;
						default:
							break;
						}
					}
					return true;
				}
				return false;
			}

			void CWindow::ProcessPropertyNotify(const void *ev)
			{

			}

			void CWindow::WindowProc(void *ev)
			{
				XEvent *e{ (XEvent*)ev };
				switch (e->type)
				{
				case KeyPress:
					ProcessKeyPress(ev);
					return;
				case KeyRelease:
					ProcessKeyRelease(ev);
					return;
				case ButtonPress:
					ProcessButtonPress(ev);
					return;
				case ButtonRelease:
					ProcessButtonRelease(ev);
					return;
				case MotionNotify:
					ProcessMotion(ev);
					return;
				case EnterNotify:
					ProcessEnter(ev);
					return;
				case LeaveNotify:
					ProcessLeave();
					return;
				case FocusIn:
					ProcessFocusIn();
					return;
				case FocusOut:
					ProcessFocusOut();
					return;
				case Expose:
					ProcessExpose(ev);
					return;
				case ConfigureNotify:
					ProcessConfigure(ev);
					return;
				case DestroyNotify:
					ProcessDestroy();
					return;
				case MapNotify:
					ProcessMap();
					return;
				case UnmapNotify:
					ProcessUnmap();
					return;
				case ClientMessage:
					if (ProcessClientMessage(ev))
						return;
					break;
				case PropertyNotify:
					ProcessPropertyNotify(ev);
					break;
				}
				if (*reinterpret_cast<Window*>(&m_hHandle) && m_pListener)
				{
					long long result{ 0 };
					m_pListener->OnMessage((unsigned long)e->type, (unsigned long long)e, 0, result);
				}
			}

			Key CWindow::VirtualToKey(const int value)
			{
				switch (value)
				{
				case XK_Pointer_Button1:		return Key::LButton;
				case XK_Pointer_Button2:		return Key::RButton;
				case XK_Cancel:					return Key::Cancel;
				case XK_Pointer_Button3:		return Key::MButton;
				case XK_Pointer_Button4:		return Key::XButton1;
				case XK_Pointer_Button5:		return Key::XButton2;
				case XK_BackSpace:				return Key::Backspace;
				case XK_Tab:					return Key::Tab;
				case XK_Clear:					return Key::Clear;
				case XK_Return:					return Key::Return;
				//case VK_SHIFT:				return Key::Shift;
				//case VK_CONTROL:				return Key::Control;
				case XK_Menu:					return Key::Menu;
				case XK_Pause:					return Key::Pause;
				case XK_Caps_Lock:				return Key::CapsLock;
				case XK_Katakana:				return Key::Kana;
				//case VK_JUNJA:				return Key::Junja;
				//case VK_FINAL:				return Key::Final;
				//case VK_HANJA:				return Key::Hanja;
				case XK_Escape:					return Key::Escape;
				//case VK_CONVERT:				return Key::Convert;
				//case VK_NONCONVERT:			return Key::NonConvert;
				//case VK_ACCEPT:				return Key::Accept;
				case XK_Mode_switch:			return Key::ModeChange;
				case XK_space:					return Key::Space;
				case XK_Prior:					return Key::Prior;
				case XK_Next:					return Key::Next;
				case XK_End:					return Key::End;
				case XK_Home:					return Key::Home;
				case XK_Left:					return Key::Left;
				case XK_Up:						return Key::Up;
				case XK_Right:					return Key::Right;
				case XK_Down:					return Key::Down;
				case XK_Select:					return Key::Select;
				case XK_Print:					return Key::Print;
				case XK_Execute:				return Key::Execute;
				//case VK_SNAPSHOT:				return Key::Snapshot;
				case XK_Insert:					return Key::Insert;
				case XK_Delete:					return Key::Delete;
				case XK_Help:					return Key::Help;
				case XK_0:						return Key::Key0;
				case XK_parenright:				return Key::Key0;
				case XK_1:						return Key::Key1;
				case XK_exclam:					return Key::Key1;
				case XK_2:						return Key::Key2;
				case XK_quotedbl:				return Key::Key2;
				case XK_at:						return Key::Key2;
				case XK_3:						return Key::Key3;
				case XK_numbersign:				return Key::Key3;
				case XK_4:						return Key::Key4;
				case XK_dollar:					return Key::Key4;
				case XK_5:						return Key::Key5;
				case XK_percent:				return Key::Key5;
				case XK_6:						return Key::Key6;
				case XK_7:						return Key::Key7;
				case XK_ampersand:				return Key::Key7;
				case XK_8:						return Key::Key8;
				case XK_asterisk:				return Key::Key8;
				case XK_9:						return Key::Key9;
				case XK_parenleft:				return Key::Key9;
				case XK_A:						return Key::A;
				case XK_B:						return Key::B;
				case XK_C:						return Key::C;
				case XK_D:						return Key::D;
				case XK_E:						return Key::E;
				case XK_F:						return Key::F;
				case XK_G:						return Key::G;
				case XK_H:						return Key::H;
				case XK_I:						return Key::I;
				case XK_J:						return Key::J;
				case XK_K:						return Key::K;
				case XK_L:						return Key::L;
				case XK_M:						return Key::M;
				case XK_N:						return Key::N;
				case XK_O:						return Key::O;
				case XK_P:						return Key::P;
				case XK_Q:						return Key::Q;
				case XK_R:						return Key::R;
				case XK_S:						return Key::S;
				case XK_T:						return Key::T;
				case XK_U:						return Key::U;
				case XK_V:						return Key::V;
				case XK_W:						return Key::W;
				case XK_X:						return Key::X;
				case XK_Y:						return Key::Y;
				case XK_Z:						return Key::Z;
				case XK_a:						return Key::A;
				case XK_b:						return Key::B;
				case XK_c:						return Key::C;
				case XK_d:						return Key::D;
				case XK_e:						return Key::E;
				case XK_f:						return Key::F;
				case XK_g:						return Key::G;
				case XK_h:						return Key::H;
				case XK_i:						return Key::I;
				case XK_j:						return Key::J;
				case XK_k:						return Key::K;
				case XK_l:						return Key::L;
				case XK_m:						return Key::M;
				case XK_n:						return Key::N;
				case XK_o:						return Key::O;
				case XK_p:						return Key::P;
				case XK_q:						return Key::Q;
				case XK_r:						return Key::R;
				case XK_s:						return Key::S;
				case XK_t:						return Key::T;
				case XK_u:						return Key::U;
				case XK_v:						return Key::V;
				case XK_w:						return Key::W;
				case XK_x:						return Key::X;
				case XK_y:						return Key::Y;
				case XK_z:						return Key::Z;
				//case VK_LWIN:					return Key::LWin;
				//case VK_RWIN:					return Key::RWin;
				//case VK_APPS:					return Key::Apps;
				//case VK_SLEEP:				return Key::Sleep;
				case XK_KP_Insert:				return Key::Numpad0;
				case XK_KP_End:					return Key::Numpad1;
				case XK_KP_Down:				return Key::Numpad2;
				case XK_KP_Page_Down:			return Key::Numpad3;
				case XK_KP_Left:				return Key::Numpad4;
				case XK_KP_Space:				return Key::Numpad5;
				case XK_KP_Begin:				return Key::Numpad5;
				case XK_KP_Right:				return Key::Numpad6;
				case XK_KP_Home:				return Key::Numpad7;
				case XK_KP_Up:					return Key::Numpad8;
				case XK_KP_Page_Up:				return Key::Numpad9;
				case XK_KP_Multiply:			return Key::Multiply;
				case XK_KP_Add:					return Key::Add;
				case XK_KP_Enter:				return Key::Separator;
				case XK_KP_Subtract:			return Key::Subtract;
				case XK_KP_Delete:				return Key::Decimal;
				case XK_KP_Decimal:				return Key::Decimal;
				case XK_KP_Divide:				return Key::Divide;
				case XK_KP_0:					return Key::Numpad0;
				case XK_KP_1:					return Key::Numpad1;
				case XK_KP_2:					return Key::Numpad2;
				case XK_KP_3:					return Key::Numpad3;
				case XK_KP_4:					return Key::Numpad4;
				case XK_KP_5:					return Key::Numpad5;
				case XK_KP_6:					return Key::Numpad6;
				case XK_KP_7:					return Key::Numpad7;
				case XK_KP_8:					return Key::Numpad8;
				case XK_KP_9:					return Key::Numpad9;
				case XK_F1:						return Key::F1;
				case XK_F2:						return Key::F2;
				case XK_F3:						return Key::F3;
				case XK_F4:						return Key::F4;
				case XK_F5:						return Key::F5;
				case XK_F6:						return Key::F6;
				case XK_F7:						return Key::F7;
				case XK_F8:						return Key::F8;
				case XK_F9:						return Key::F9;
				case XK_F10:					return Key::F10;
				case XK_F11:					return Key::F11;
				case XK_F12:					return Key::F12;
				case XK_F13:					return Key::F13;
				case XK_F14:					return Key::F14;
				case XK_F15:					return Key::F15;
				case XK_F16:					return Key::F16;
				case XK_F17:					return Key::F17;
				case XK_F18:					return Key::F18;
				case XK_F19:					return Key::F19;
				case XK_F20:					return Key::F20;
				case XK_F21:					return Key::F21;
				case XK_F22:					return Key::F22;
				case XK_F23:					return Key::F23;
				case XK_F24:					return Key::F24;
				case XK_Num_Lock:				return Key::NumLock;
				case XK_Scroll_Lock:			return Key::ScrollLock;
				case XK_Shift_L:				return Key::LShift;
				case XK_Shift_R:				return Key::RShift;
				case XK_Control_L:				return Key::LControl;
				case XK_Control_R:				return Key::RControl;
				case XK_Alt_L:					return Key::LMenu;
				case XK_Alt_R:					return Key::RMenu;
				//case VK_BROWSER_BACK:			return Key::BrowserBack;
				//case VK_BROWSER_FORWARD:		return Key::BrowserForward;
				//case VK_BROWSER_REFRESH:		return Key::BrowserRefresh;
				//case VK_BROWSER_STOP:			return Key::BrowserStop;
				//case VK_BROWSER_SEARCH:		return Key::BrowserSearch;
				//case VK_BROWSER_FAVORITES:	return Key::BrowserFavorites;
				//case VK_BROWSER_HOME:			return Key::BrowserHome;
				//case VK_VOLUME_MUTE:			return Key::VolumeMute;
				//case VK_VOLUME_DOWN:			return Key::VolumeDown;
				//case VK_VOLUME_UP:			return Key::VolumeUp;
				//case VK_MEDIA_NEXT_TRACK:		return Key::MediaNextTrack;
				//case VK_MEDIA_PREV_TRACK:		return Key::MediaPrevTrack;
				//case VK_MEDIA_STOP:			return Key::MediaStop;
				//case VK_MEDIA_PLAY_PAUSE:		return Key::MediaPlayPause;
				//case VK_LAUNCH_MAIL:			return Key::LaunchMail;
				//case VK_LAUNCH_MEDIA_SELECT:	return Key::LaunchMediaSelect;
				//case VK_LAUNCH_APP1:			return Key::LaunchApp1;
				//case VK_LAUNCH_APP2:			return Key::LaunchApp2;
				case XK_colon:					return Key::Semicolon;
				case XK_semicolon:				return Key::Semicolon;
				case XK_plus:					return Key::OemPlus;
				case XK_equal:					return Key::OemPlus;
				case XK_comma:					return Key::OemComma;
				case XK_less:					return Key::OemComma;
				case XK_minus:					return Key::OemMinus;
				case XK_underscore:				return Key::OemMinus;
				case XK_period:					return Key::OemPeriod;
				case XK_greater:				return Key::OemPeriod;
				case XK_slash:					return Key::Slash;
				case XK_question:				return Key::Slash;
				case XK_asciitilde:				return Key::Tilde;
				case XK_grave:					return Key::Tilde;
				case XK_bracketleft:			return Key::LeftBracket;
				case XK_backslash:				return Key::BackSlash;
				case XK_bracketright:			return Key::RightBracket;
				case XK_apostrophe:				return Key::Apostrophe;
				//case VK_OEM_8:				return Key::Oem8;
				//case VK_OEM_102:				return Key::Oem102;
				//case VK_PROCESSKEY:			return Key::ProcessKey;
				//case VK_PACKET:				return Key::Packet;
				//case VK_ATTN:					return Key::Attn;
				//case VK_CRSEL:				return Key::CrSel;
				//case VK_EXSEL:				return Key::ExSel;
				//case VK_EREOF:				return Key::ErEOF;
				//case VK_PLAY:					return Key::Play;
				//case VK_ZOOM:					return Key::Zoom;
				//case VK_PA1:					return Key::PA1;
				//case VK_OEM_CLEAR:			return Key::OemClear;
				default:						return Key::Unknown;
				}
			}

			int CWindow::KeyToVirtual(const Key value)
			{
				switch (value)
				{
				case Key::LButton:					return XK_Pointer_Button1;
				case Key::RButton:					return XK_Pointer_Button2;
				case Key::Cancel:					return XK_Cancel;
				case Key::MButton:					return XK_Pointer_Button3;
				case Key::XButton1:					return XK_Pointer_Button4;
				case Key::XButton2:					return XK_Pointer_Button5;
				case Key::Backspace:				return XK_BackSpace;
				case Key::Tab:						return XK_Tab;
				case Key::Clear:					return XK_Clear;
				case Key::Return:					return XK_Return;
				//case Key::Shift:					return VK_SHIFT;
				//case Key::Control:				return VK_CONTROL;
				case Key::Menu:						return XK_Menu;
				case Key::Pause:					return XK_Pause;
				case Key::CapsLock:					return XK_Caps_Lock;
				case Key::Kana:						return XK_Katakana;
				//case Key::Junja:					return VK_JUNJA;
				//case Key::Final:					return VK_FINAL;
				//case Key::Hanja:					return VK_HANJA;
				case Key::Escape:					return XK_Escape;
				//case Key::Convert:				return VK_CONVERT;
				//case Key::NonConvert:				return VK_NONCONVERT;
				//case Key::Accept:					return VK_ACCEPT;
				case Key::ModeChange:				return XK_Mode_switch;
				case Key::Space:					return XK_space;
				case Key::Prior:					return XK_Prior;
				case Key::Next:						return XK_Next;
				case Key::End:						return XK_End;
				case Key::Home:						return XK_Home;
				case Key::Left:						return XK_Left;
				case Key::Up:						return XK_Up;
				case Key::Right:					return XK_Right;
				case Key::Down:						return XK_Down;
				case Key::Select:					return XK_Select;
				case Key::Print:					return XK_Print;
				case Key::Execute:					return XK_Execute;
				//case Key::Snapshot:				return VK_SNAPSHOT;
				case Key::Insert:					return XK_Insert;
				case Key::Delete:					return XK_Delete;
				case Key::Help:						return XK_Help;
				case Key::Key0:						return XK_0;
				case Key::Key1:						return XK_1;
				case Key::Key2:						return XK_2;
				case Key::Key3:						return XK_3;
				case Key::Key4:						return XK_4;
				case Key::Key5:						return XK_5;
				case Key::Key6:						return XK_6;
				case Key::Key7:						return XK_7;
				case Key::Key8:						return XK_8;
				case Key::Key9:						return XK_9;
				case Key::A:						return XK_A;
				case Key::B:						return XK_B;
				case Key::C:						return XK_C;
				case Key::D:						return XK_D;
				case Key::E:						return XK_E;
				case Key::F:						return XK_F;
				case Key::G:						return XK_G;
				case Key::H:						return XK_H;
				case Key::I:						return XK_I;
				case Key::J:						return XK_J;
				case Key::K:						return XK_K;
				case Key::L:						return XK_L;
				case Key::M:						return XK_M;
				case Key::N:						return XK_N;
				case Key::O:						return XK_O;
				case Key::P:						return XK_P;
				case Key::Q:						return XK_Q;
				case Key::R:						return XK_R;
				case Key::S:						return XK_S;
				case Key::T:						return XK_T;
				case Key::U:						return XK_U;
				case Key::V:						return XK_V;
				case Key::W:						return XK_W;
				case Key::X:						return XK_X;
				case Key::Y:						return XK_Y;
				case Key::Z:						return XK_Z;
				//case Key::LWin:					return VK_LWIN;
				//case Key::RWin:					return VK_RWIN;
				//case Key::Apps:					return VK_APPS;
				//case Key::Sleep:					return VK_SLEEP;
				case Key::Numpad0:					return XK_KP_0;
				case Key::Numpad1:					return XK_KP_1;
				case Key::Numpad2:					return XK_KP_2;
				case Key::Numpad3:					return XK_KP_3;
				case Key::Numpad4:					return XK_KP_4;
				case Key::Numpad5:					return XK_KP_5;
				case Key::Numpad6:					return XK_KP_6;
				case Key::Numpad7:					return XK_KP_7;
				case Key::Numpad8:					return XK_KP_8;
				case Key::Numpad9:					return XK_KP_9;
				case Key::Multiply:					return XK_KP_Multiply;
				case Key::Add:						return XK_KP_Add;
				case Key::Separator:				return XK_KP_Enter;
				case Key::Subtract:					return XK_KP_Subtract;
				case Key::Decimal:					return XK_KP_Delete;
				case Key::Divide:					return XK_KP_Divide;
				case Key::F1:						return XK_F1;
				case Key::F2:						return XK_F2;
				case Key::F3:						return XK_F3;
				case Key::F4:						return XK_F4;
				case Key::F5:						return XK_F5;
				case Key::F6:						return XK_F6;
				case Key::F7:						return XK_F7;
				case Key::F8:						return XK_F8;
				case Key::F9:						return XK_F9;
				case Key::F10:						return XK_F10;
				case Key::F11:						return XK_F11;
				case Key::F12:						return XK_F12;
				case Key::F13:						return XK_F13;
				case Key::F14:						return XK_F14;
				case Key::F15:						return XK_F15;
				case Key::F16:						return XK_F16;
				case Key::F17:						return XK_F17;
				case Key::F18:						return XK_F18;
				case Key::F19:						return XK_F19;
				case Key::F20:						return XK_F20;
				case Key::F21:						return XK_F21;
				case Key::F22:						return XK_F22;
				case Key::F23:						return XK_F23;
				case Key::F24:						return XK_F24;
				case Key::NumLock:					return XK_Num_Lock;
				case Key::ScrollLock:				return XK_Scroll_Lock;
				case Key::LShift:					return XK_Shift_L;
				case Key::RShift:					return XK_Shift_R;
				case Key::LControl:					return XK_Control_L;
				case Key::RControl:					return XK_Control_R;
				case Key::LMenu:					return XK_Alt_L;
				case Key::RMenu:					return XK_Alt_R;
				//case Key::BrowserBack:			return VK_BROWSER_BACK;
				//case Key::BrowserForward:			return VK_BROWSER_FORWARD;
				//case Key::BrowserRefresh:			return VK_BROWSER_REFRESH;
				//case Key::BrowserStop:			return VK_BROWSER_STOP;
				//case Key::BrowserSearch:			return VK_BROWSER_SEARCH;
				//case Key::BrowserFavorites:		return VK_BROWSER_FAVORITES;
				//case Key::BrowserHome:			return VK_BROWSER_HOME;
				//case Key::VolumeMute:				return VK_VOLUME_MUTE;
				//case Key::VolumeDown:				return VK_VOLUME_DOWN;
				//case Key::VolumeUp:				return VK_VOLUME_UP;
				//case Key::MediaNextTrack:			return VK_MEDIA_NEXT_TRACK;
				//case Key::MediaPrevTrack:			return VK_MEDIA_PREV_TRACK;
				//case Key::MediaStop:				return VK_MEDIA_STOP;
				//case Key::MediaPlayPause:			return VK_MEDIA_PLAY_PAUSE;
				//case Key::LaunchMail:				return VK_LAUNCH_MAIL;
				//case Key::LaunchMediaSelect:		return VK_LAUNCH_MEDIA_SELECT;
				//case Key::LaunchApp1:				return VK_LAUNCH_APP1;
				//case Key::LaunchApp2:				return VK_LAUNCH_APP2;
				case Key::Semicolon:				return XK_colon;
				case Key::OemPlus:					return XK_plus;
				case Key::OemComma:					return XK_comma;
				case Key::OemMinus:					return XK_minus;
				case Key::OemPeriod:				return XK_period;
				case Key::Slash:					return XK_slash;
				case Key::Tilde:					return XK_asciitilde;
				case Key::LeftBracket:				return XK_bracketleft;
				case Key::BackSlash:				return XK_backslash;
				case Key::RightBracket:				return XK_bracketright;
				case Key::Apostrophe:				return XK_apostrophe;
				//case Key::Oem8:					return VK_OEM_8;
				//case Key::Oem102:					return VK_OEM_102;
				//case Key::ProcessKey:				return VK_PROCESSKEY;
				//case Key::Packet:					return VK_PACKET;
				//case Key::Attn:					return VK_ATTN;
				//case Key::CrSel:					return VK_CRSEL;
				//case Key::ExSel:					return VK_EXSEL;
				//case Key::ErEOF:					return VK_EREOF;
				//case Key::Play:					return VK_PLAY;
				//case Key::Zoom:					return VK_ZOOM;
				//case Key::PA1:					return VK_PA1;
				//case Key::OemClear:				return VK_OEM_CLEAR;
				default: return 0;
				}
			}
		#pragma endregion
		}
	}
}
#endif