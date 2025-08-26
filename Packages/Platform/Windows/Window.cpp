// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#include <ShObjIdl.h>
#include <Windows.h>

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
		#pragma region Functions
			DWORD GetStyle(const CreateParams &cp)
			{
				DWORD style{ 0 };
				if (cp.HasBorder)
					style |= WS_BORDER;
				if (cp.HasCaption)
					style |= WS_CAPTION;
				if (cp.IsChild)
					style |= WS_CHILD;
				if (cp.IsClipChildren)
					style |= WS_CLIPCHILDREN;
				if (!cp.IsEnabled)
					style |= WS_DISABLED;
				if (cp.HasDialogFrame)
					style |= WS_DLGFRAME;
				if (cp.HasHorizontalScroll)
					style |= WS_HSCROLL;
				if (cp.HasVerticalScroll)
					style |= WS_VSCROLL;
				if (cp.HasMaximizeBox)
					style |= WS_MAXIMIZEBOX;
				if (cp.HasMinimizeBox)
					style |= WS_MINIMIZEBOX;
				if (cp.HasSizeBox)
					style |= WS_SIZEBOX;
				if (cp.HasSystemMenu)
					style |= WS_SYSMENU;
				if (cp.IsPopup)
					style |= WS_POPUP;
				if (cp.IsTabStop)
					style |= WS_TABSTOP;
				return style;
			}

			DWORD GetStyleEx(const CreateParams &cp)
			{
				DWORD style_ex{ 0 };
				if (cp.IsAcceptFiles)
					style_ex |= WS_EX_ACCEPTFILES;
				if (cp.IsApplicationWindow)
					style_ex |= WS_EX_APPWINDOW;
				if (cp.HasClientEdge)
					style_ex |= WS_EX_CLIENTEDGE;
				if (cp.HasContextHelp)
					style_ex |= WS_EX_CONTEXTHELP;
				if (cp.HasDialogModalFrame)
					style_ex |= WS_EX_DLGMODALFRAME;
				if (cp.IsMDIChild)
					style_ex |= WS_EX_MDICHILD;
				if (cp.HasStaticEdge)
					style_ex |= WS_EX_STATICEDGE;
				if (cp.IsToolWindow)
					style_ex |= WS_EX_TOOLWINDOW;
				if (cp.IsTopMost)
					style_ex |= WS_EX_TOPMOST;
				if (cp.HasWindowEdge)
					style_ex |= WS_EX_WINDOWEDGE;
				return style_ex;
			}
		#pragma endregion

		#pragma region Constructor and destructor
			CWindow::CWindow() : CWindow(0)
			{
			
			}

			CWindow::CWindow(PlatformHandle parent) :
				m_pApplication{ cast<CApplication*>(Application) },
				m_eCurrentCursor{ CursorType::None },
				m_bCursorSet{ false },
				m_bAcceptDragAndDrop{ false },
				m_bAcceptDropFiles{ false },
				m_pService{ nullptr },
				m_pParent{ nullptr },
				m_bModal{ false },
				m_eModalResult{ ModalResult::None },
				m_iID{ 1 },
				m_hParent{ parent },
				m_iPixelFormatIndex{ -1 }
			{
				*reinterpret_cast<HWND*>(&m_hHandle) = 0;
				m_pListener = nullptr;
			}

			CWindow::~CWindow()
			{
				if (m_pService)
					m_pService->Release();
			}

			void CWindow::Release()
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					DestroyWindow(*reinterpret_cast<HWND*>(&m_hHandle));
				else
					delete this;
			}
		#pragma endregion

		#pragma region Getters
			bool CWindow::isCreated()
			{
				return *reinterpret_cast<HWND*>(&m_hHandle) > 0;
			}

			bool CWindow::isVisible()
			{
				return *reinterpret_cast<HWND*>(&m_hHandle) && IsWindowVisible(*reinterpret_cast<HWND*>(&m_hHandle));
			}

			bool CWindow::isEnabled()
			{
				return *reinterpret_cast<HWND*>(&m_hHandle) && IsWindowEnabled(*reinterpret_cast<HWND*>(&m_hHandle));
			}

			bool CWindow::isAcceptDragAndDrop()
			{
				return m_bAcceptDragAndDrop;
			}

			bool CWindow::isAcceptDropFiles()
			{
				return m_bAcceptDropFiles;
			}

			String CWindow::getCaption()
			{
				String result;
				if (*reinterpret_cast<HWND*>(&m_hHandle))
				{
					int len = GetWindowTextLengthW(*reinterpret_cast<HWND*>(&m_hHandle));
					if (len > 0)
					{
						wchar_t *buffer = new wchar_t[len + 1];
						if (GetWindowTextW(*reinterpret_cast<HWND*>(&m_hHandle), buffer, len + 1))
							result = buffer;
						delete[] buffer;
					}
				}
				return result;
			}

			Rect CWindow::getRect()
			{
				RECT result{ 0, 0, 0, 0 };
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					GetWindowRect(*reinterpret_cast<HWND*>(&m_hHandle), &result);
				return{ result.left, result.top, result.right, result.bottom };
			}

			Point CWindow::getSize()
			{
				Rect r{ getRect() };
				return Point{ r.width(), r.height() };
			}

			Point CWindow::getPosition()
			{
				return getRect().LeftTop;
			}

			int CWindow::getLeft()
			{
				return getRect().Left;
			}

			int CWindow::getTop()
			{
				return getRect().Top;
			}

			int CWindow::getWidth()
			{
				return getRect().width();
			}

			int CWindow::getHeight()
			{
				return getRect().height();
			}

			Rect CWindow::getClientRect()
			{
				RECT result{ 0, 0, 0, 0 };
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					GetClientRect(*reinterpret_cast<HWND*>(&m_hHandle), &result);
				return Rect{ result.left, result.top, result.right, result.bottom };
			}

			Point CWindow::getClientSize()
			{
				Rect r{ getClientRect() };
				return Point{ r.width(), r.height() };
			}

			int CWindow::getClientWidth()
			{
				return getClientRect().width();
			}

			int CWindow::getClientHeight()
			{
				return getClientRect().height();
			}

			WindowState CWindow::getState()
			{
				WindowState result{ WindowState::Normal };
				if (*reinterpret_cast<HWND*>(&m_hHandle))
				{
					WINDOWPLACEMENT p;
					p.length = sizeof(WINDOWPLACEMENT);
					if (GetWindowPlacement(*reinterpret_cast<HWND*>(&m_hHandle), &p))
						switch (p.showCmd)
						{
						case SW_HIDE:
							result = WindowState::Hidden;
							break;
						case SW_MAXIMIZE:
							result = WindowState::Maximized;
							break;
						case SW_MINIMIZE:
						case SW_SHOWMINIMIZED:
						case SW_SHOWMINNOACTIVE:
							result = WindowState::Minimized;
							break;
						case SW_RESTORE:
						case SW_SHOW:
						case SW_SHOWNA:
						case SW_SHOWNOACTIVATE:
						case SW_SHOWNORMAL:
							result = WindowState::Normal;
							break;
						}
				}
				return result;
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
				return m_pApplication->hasTaskBar();
			}
		#pragma endregion

		#pragma region Setters
			bool CWindow::setVisible(const bool value)
			{
				return value ? Show() : Hide();
			}

			bool CWindow::setEnabled(const bool value)
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return EnableWindow(*reinterpret_cast<HWND*>(&m_hHandle), value ? TRUE : FALSE) ? true : false;
				return false;
			}

			bool CWindow::setAcceptDrawAndDrop(const bool value)
			{
				//TODO: Implement drag & drop using OLE
				return false;
			}

			bool CWindow::setAcceptDropFiles(const bool value)
			{
				if (!(*reinterpret_cast<HWND*>(&m_hHandle)))
					return false;
				if (value == m_bAcceptDropFiles)
					return true;
				DragAcceptFiles(*reinterpret_cast<HWND*>(&m_hHandle), value ? TRUE : FALSE);
				m_bAcceptDropFiles = value;
				return true;
			}

			bool CWindow::setCaption(const String &value)
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return SetWindowTextW(*reinterpret_cast<HWND*>(&m_hHandle), value.c_str()) ? true : false;
				return false;
			}

			bool CWindow::setRect(const Rect &value)
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return SetWindowPos(*reinterpret_cast<HWND*>(&m_hHandle), 0, value.Left, value.Right, value.width(), value.height(), SWP_NOZORDER) ? true : false;
				return false;
			}

			bool CWindow::setSize(const Point &value)
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return SetWindowPos(*reinterpret_cast<HWND*>(&m_hHandle), 0, 0, 0, value.X, value.Y, SWP_NOZORDER | SWP_NOMOVE) ? true : false;
				return false;
			}

			bool CWindow::setPosition(const Point &value)
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return SetWindowPos(*reinterpret_cast<HWND*>(&m_hHandle), 0, value.X, value.Y, 0, 0, SWP_NOZORDER | SWP_NOSIZE) ? true : false;
				return false;
			}

			bool CWindow::setLeft(const int value)
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return SetWindowPos(*reinterpret_cast<HWND*>(&m_hHandle), 0, value, getTop(), 0, 0, SWP_NOZORDER | SWP_NOSIZE) ? true : false;
				return false;
			}

			bool CWindow::setTop(const int value)
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return SetWindowPos(*reinterpret_cast<HWND*>(&m_hHandle), 0, getLeft(), value, 0, 0, SWP_NOZORDER | SWP_NOSIZE) ? true : false;
				return false;
			}

			bool CWindow::setWidth(const int value)
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return SetWindowPos(*reinterpret_cast<HWND*>(&m_hHandle), 0, 0, 0, value, getHeight(), SWP_NOZORDER | SWP_NOMOVE) ? true : false;
				return false;
			}

			bool CWindow::setHeight(const int value)
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return SetWindowPos(*reinterpret_cast<HWND*>(&m_hHandle), 0, 0, 0, getWidth(), value, SWP_NOZORDER | SWP_NOMOVE) ? true : false;
				return false;
			}

			bool CWindow::setClientSize(const Point &value)
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle) && value.X > 0 && value.Y > 0)
				{
					::RECT r{ 0, 0, value.X, value.Y };
					if (AdjustWindowRectEx(&r, GetStyle(m_sCreateParams), false, GetStyleEx(m_sCreateParams)))
						return setSize(Point{ r.right - r.left, r.bottom - r.top });
				}
				return false;
			}

			bool CWindow::setCursor(const CursorType value)
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle) && (value != m_eCurrentCursor || !m_bCursorSet))
				{
					HCURSOR h{ 0 };
					switch (value)
					{
					case CursorType::AppStarting:
						h = LoadCursor(0, IDC_APPSTARTING);
						break;
					case CursorType::Arrow:
						h = LoadCursor(0, IDC_ARROW);
						break;
					case CursorType::Cross:
						h = LoadCursor(0, IDC_CROSS);
						break;
					case CursorType::Hand:
						h = LoadCursor(0, IDC_HAND);
						break;
					case CursorType::Help:
						h = LoadCursor(0, IDC_HELP);
						break;
					case CursorType::IBeam:
						h = LoadCursor(0, IDC_IBEAM);
						break;
					case CursorType::No:
						h = LoadCursor(0, IDC_NO);
						break;
					case CursorType::SizeAll:
						h = LoadCursor(0, IDC_SIZEALL);
						break;
					case CursorType::SizeNortheastSouthwest:
						h = LoadCursor(0, IDC_SIZENESW);
						break;
					case CursorType::SizeNorthSouth:
						h = LoadCursor(0, IDC_SIZENS);
						break;
					case CursorType::SizeNorthwestSoutheast:
						h = LoadCursor(0, IDC_SIZENWSE);
						break;
					case CursorType::SizeWestEast:
						h = LoadCursor(0, IDC_SIZEWE);
						break;
					case CursorType::UpArrow:
						h = LoadCursor(0, IDC_UPARROW);
						break;
					case CursorType::Wait:
						h = LoadCursor(0, IDC_WAIT);
						break;
					}
					if (h)
						SetCursor(h);
					if (value == CursorType::None)
						SetCursor(0);
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
					if (*reinterpret_cast<HWND*>(&m_hHandle))
					{
						if (value && !(*reinterpret_cast<const HWND*>(&value->Handle)))
							return false;
						if (!SetParent(*reinterpret_cast<HWND*>(&m_hHandle), value ? *reinterpret_cast<const HWND*>(&value->Handle) : 0))
							return false;
					}
					m_pParent = value;
					m_hHandle = m_pParent ? m_pParent->Handle : 0;
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
				if (*reinterpret_cast<HWND*>(&m_hHandle) && value != WindowPosition::Custom && getState() == WindowState::Normal)
					return setPosition(CalculateCreatePosition(getSize()));
				return false;
			}

			bool CWindow::setProgressType(const ProgressType value)
			{
				return m_pApplication->SetProgressState(this, value);
			}

			bool CWindow::setProgressValue(const float value)
			{
				return m_pApplication->SetProgressValue(this, value);
			}
		#pragma endregion

		#pragma region Helpers
			bool CWindow::CreatePlatformWindow()
			{
				DWORD style{ GetStyle(m_sCreateParams) }, style_ex{ GetStyleEx(m_sCreateParams) };
				Point size{ m_sCreateParams.Size };
				::RECT r{ 0, 0, size.X, size.Y };
				if (AdjustWindowRectEx(&r, style, false, style_ex))
				{
					size.X = r.right - r.left;
					size.Y = r.bottom - r.top;
				}
				Point position{ CalculateCreatePosition(size) };
				if (*reinterpret_cast<HWND*>(&m_hHandle) = CreateWindowExW(style_ex, DefaultWindowClassName.c_str(), m_sCreateParams.Caption.c_str(), style, position.X, position.Y, size.X, size.Y,
					*reinterpret_cast<HWND*>(&m_hParent), 0, *reinterpret_cast<const HINSTANCE*>(&m_pApplication->Handle), LPVOID(cast<IWindow*>(this))))
				{
					switch (m_sCreateParams.State)
					{
					case WindowState::Normal:
						ShowWindow(*reinterpret_cast<HWND*>(&m_hHandle), SW_SHOW);
						break;
					case WindowState::Maximized:
						ShowWindow(*reinterpret_cast<HWND*>(&m_hHandle), SW_MAXIMIZE);
						break;
					case WindowState::Minimized:
						ShowWindow(*reinterpret_cast<HWND*>(&m_hHandle), SW_MINIMIZE);
						break;
					}
					return true;
				}
				return false;
			}

			bool CWindow::Show()
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return ShowWindow(*reinterpret_cast<HWND*>(&m_hHandle), SW_SHOWNORMAL) ? true : false;
				return false;
			}

			ModalResult CWindow::ShowModal()
			{
				return m_pApplication->ShowModal(this);
			}

			void CWindow::ExitModal()
			{
				m_pApplication->ExitModal(this);
			}

			bool CWindow::Hide()
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return ShowWindow(*reinterpret_cast<HWND*>(&m_hHandle), SW_HIDE) ? true : false;
				return false;
			}

			bool CWindow::Create()
			{
				if (m_pParent)
					return Create(m_pParent);
				return CreatePlatformWindow();
			}

			bool CWindow::Create(IWindow *parent)
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return false;
				if (parent && !(*reinterpret_cast<const HWND*>(&parent->Handle)))
					return false;
				if (m_pParent = parent)
					m_hParent = parent->Handle;
				else
					*reinterpret_cast<HWND*>(&m_hParent) = 0;
				return CreatePlatformWindow();
			}

			bool CWindow::Create(const CreateParams &params)
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return false;
				m_sCreateParams = params;
				return Create();
			}

			bool CWindow::Create(const CreateParams &params, IWindow *parent)
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return false;
				m_sCreateParams = params;
				return Create(parent);
			}

			PlatformHandle CWindow::CreateTimer(ITimerListener *listener, const float interval)
			{
				if (!(*reinterpret_cast<HWND*>(&m_hHandle)) || !listener || ntl::IsLess<float>(interval, 0))
					return 0;
				TIMER result{ listener, m_aTimers.size() > 0 ? m_aTimers[m_aTimers.size() - 1].Id : 0 };
				result.Id = (PlatformHandle)SetTimer(*reinterpret_cast<HWND*>(&m_hHandle), (UINT_PTR)result.Id + 1, ntl::Round<int>(interval * 1000), nullptr);
				if (result.Id)
					m_aTimers.push_back(result);
				return result.Id;
			}

			bool CWindow::DeleteTimer(const PlatformHandle id)
			{
				for (auto pos = m_aTimers.begin(); pos != m_aTimers.end(); pos++)
					if ((*pos).Id == id)
					{
						KillTimer(*reinterpret_cast<HWND*>(&m_hHandle), (UINT_PTR)(*pos).Id);
						m_aTimers.erase(pos);
						return true;
					}
				return false;
			}

			void CWindow::DeleteTimers()
			{
				for (auto pos = m_aTimers.begin(); pos != m_aTimers.end(); pos++)
					KillTimer(*reinterpret_cast<HWND*>(&m_hHandle), (UINT_PTR)(*pos).Id);
				m_aTimers.clear();
			}

			bool CWindow::ResetTimer(const PlatformHandle id, const float interval)
			{
				if (ntl::IsLess<float>(interval, 0))
					return false;
				for (auto pos = m_aTimers.begin(); pos != m_aTimers.end(); pos++)
					if ((*pos).Id == id)
					{
						if (!SetTimer(*reinterpret_cast<HWND*>(&m_hHandle), (UINT_PTR)(*pos).Id, ntl::Round<int>(interval * 1000), nullptr))
							return false;
						return true;
					}
				return false;
			}

			bool CWindow::CaptureMouse()
			{
				if (!(*reinterpret_cast<HWND*>(&m_hHandle)))
					return false;
				SetCapture(*reinterpret_cast<HWND*>(&m_hHandle));
				return true;
			}

			void CWindow::ReleaseMouseCapture()
			{
				ReleaseCapture();
			}

			bool CWindow::Maximize()
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return ShowWindow(*reinterpret_cast<HWND*>(&m_hHandle), SW_MAXIMIZE) ? true : false;
				return false;
			}

			bool CWindow::Minimize()
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return ShowWindow(*reinterpret_cast<HWND*>(&m_hHandle), SW_MINIMIZE) ? true : false;
				return false;
			}

			bool CWindow::Restore()
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return ShowWindow(*reinterpret_cast<HWND*>(&m_hHandle), SW_RESTORE) ? true : false;
				return false;
			}

			bool CWindow::Close()
			{
				if (*reinterpret_cast<HWND*>(&m_hHandle))
					return PostMessage(*reinterpret_cast<HWND*>(&m_hHandle), WM_CLOSE, 0, 0) ? true : false;
				return false;
			}

			int CWindow::GenerateID()
			{
				return m_iID++;
			}

			bool CWindow::CopyStringToClipboard(const String &str)
			{
				if (str.length() == 0)
					return false;
				if (!(*reinterpret_cast<HWND*>(&m_hHandle)))
					return false;
				if (!OpenClipboard(*reinterpret_cast<HWND*>(&m_hHandle)))
					return false;
				if (!EmptyClipboard())
				{
					CloseClipboard();
					return false;
				}
				HGLOBAL hmem{ GlobalAlloc(GMEM_MOVEABLE, (str.length() + 1) * sizeof(wchar_t)) };
				if (!hmem)
				{
					CloseClipboard();
					return false;
				}
				LPVOID mem{ GlobalLock(hmem) };
				if (!mem)
				{
					GlobalFree(hmem);
					CloseClipboard();
					return false;
				}
				memcpy(mem, str.c_str(), (str.length() + 1) * sizeof(wchar_t));
				if (GlobalUnlock(hmem))
				{
					GlobalFree(hmem);
					CloseClipboard();
					return false;
				}
				if (!SetClipboardData(CF_UNICODETEXT, hmem))
				{
					GlobalFree(hmem);
					CloseClipboard();
					return false;
				}
				return CloseClipboard() ? true : false;
			}

			bool CWindow::CopyStringFromClipboard()
			{
				if (!(*reinterpret_cast<HWND*>(&m_hHandle)))
					return false;
				if (IsClipboardFormatAvailable(CF_UNICODETEXT))
				{
					if (!OpenClipboard(*reinterpret_cast<HWND*>(&m_hHandle)))
						return false;
					HANDLE hmem{ GetClipboardData(CF_UNICODETEXT) };
					if (!hmem)
					{
						CloseClipboard();
						return false;
					}
					LPVOID mem{ GlobalLock(hmem) };
					if (!mem)
					{
						CloseClipboard();
						return false;
					}
					String result{ (wchar_t*)mem };
					GlobalUnlock(hmem);
					CloseClipboard();
					if (m_pListener)
						m_pListener->OnPasteString(MessagePasteString{ result });
					return true;
				}
				if (IsClipboardFormatAvailable(CF_TEXT))
				{
					if (!OpenClipboard(*reinterpret_cast<HWND*>(&m_hHandle)))
						return false;
					HANDLE hmem{ GetClipboardData(CF_TEXT) };
					if (!hmem)
					{
						CloseClipboard();
						return false;
					}
					LPVOID mem{ GlobalLock(hmem) };
					if (!mem)
					{
						CloseClipboard();
						return false;
					}
					AnsiString result{ (char*)mem };
					GlobalUnlock(hmem);
					CloseClipboard();
					if (m_pListener)
						m_pListener->OnPasteString(MessagePasteString{ AnsiToString(result) });
					return true;
				}
				return false;
			}

			Rect CWindow::ScreenToClient(const Rect &rect)
			{
				::POINT p1{ rect.Left, rect.Top }, p2{ rect.Right, rect.Bottom };
				if (*reinterpret_cast<HWND*>(&m_hHandle) && ::ScreenToClient(*reinterpret_cast<HWND*>(&m_hHandle), &p1) && ::ScreenToClient(*reinterpret_cast<HWND*>(&m_hHandle), &p2))
					return Rect{ p1.x, p1.y, p2.x, p2.y };
				return rect;
			}

			Point CWindow::ScreenToClient(const Point &pos)
			{
				::POINT p{ pos.X, pos.Y };
				if (*reinterpret_cast<HWND*>(&m_hHandle) && ::ScreenToClient(*reinterpret_cast<HWND*>(&m_hHandle), &p))
					return Point{ p.x, p.y };
				return pos;
			}

			Rect CWindow::ClientToScreen(const Rect &rect)
			{
				::POINT p1{ rect.Left, rect.Top }, p2{ rect.Right, rect.Bottom };
				if (*reinterpret_cast<HWND*>(&m_hHandle) && ::ClientToScreen(*reinterpret_cast<HWND*>(&m_hHandle), &p1) && ::ClientToScreen(*reinterpret_cast<HWND*>(&m_hHandle), &p2))
					return Rect{ p1.x, p1.y, p2.x, p2.y };
				return rect;
			}

			Point CWindow::ClientToScreen(const Point &pos)
			{
				::POINT p{ pos.X, pos.Y };
				if (*reinterpret_cast<HWND*>(&m_hHandle) && ::ClientToScreen(*reinterpret_cast<HWND*>(&m_hHandle), &p))
					return Point{ p.x, p.y };
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
					return Point{ GetSystemMetrics(SM_CXSCREEN) - size.X, 0 };
				case WindowPosition::ScreenLeftBottom:
					return Point{ 0, GetSystemMetrics(SM_CYSCREEN) - size.Y };
				case WindowPosition::ScreenRightBottom:
					return Point{ GetSystemMetrics(SM_CXSCREEN) - size.X, GetSystemMetrics(SM_CYSCREEN) - size.Y };
				case WindowPosition::ScreenCenter:
					return Point{ (GetSystemMetrics(SM_CXSCREEN) - size.X) / 2, (GetSystemMetrics(SM_CYSCREEN) - size.Y) / 2 };
				case WindowPosition::MainFormLeftTop:
					if (m_pParent)
						return m_pParent->getRect().LeftTop;
					else if (m_pApplication->MainForm && m_pApplication->MainForm->QueryService()->getWindow() != this)
						return m_pApplication->MainForm->QueryService()->getWindow()->getRect().LeftTop;
					break;
				case WindowPosition::MainFormRightTop:
					if (m_pParent)
					{
						Rect r{ m_pParent->getRect() };
						return Point{ r.Right - size.X, r.Top };
					}
					else if (m_pApplication->MainForm && m_pApplication->MainForm->QueryService()->getWindow() != this)
					{
						Rect r{ m_pApplication->MainForm->QueryService()->getWindow()->getRect() };
						return Point{ r.Right - size.X, r.Top };
					}
					break;
				case WindowPosition::MainFormLeftBottom:
					if (m_pParent)
					{
						Rect r{ m_pParent->getRect() };
						return Point{ r.Left, r.Bottom - size.Y };
					}
					else if (m_pApplication->MainForm && m_pApplication->MainForm->QueryService()->getWindow() != this)
					{
						Rect r{ m_pApplication->MainForm->QueryService()->getWindow()->getRect() };
						return Point{ r.Left, r.Bottom - size.Y };
					}
					break;
				case WindowPosition::MainFormRightBottom:
					if (m_pParent)
					{
						Rect r{ m_pParent->getRect() };
						return Point{ r.Right - size.X, r.Bottom - size.Y };
					}
					else if (m_pApplication->MainForm && m_pApplication->MainForm->QueryService()->getWindow() != this)
					{
						Rect r{ m_pApplication->MainForm->QueryService()->getWindow()->getRect() };
						return Point{ r.Right - size.X, r.Bottom - size.Y };
					}
					break;
				case WindowPosition::MainFormCenter:
					if (m_pParent)
					{
						Rect r{ m_pParent->getRect() };
						return Point{ (r.Left + r.Right - size.X) / 2, (r.Top + r.Bottom - size.Y) / 2 };
					}
					else if (m_pApplication->MainForm && m_pApplication->MainForm->QueryService()->getWindow() != this)
					{
						Rect r{ m_pApplication->MainForm->QueryService()->getWindow()->getRect() };
						return Point{ (r.Left + r.Right - size.X) / 2, (r.Top + r.Bottom - size.Y) / 2 };
					}
					break;
				}
				return m_sCreateParams.Position;
			}

			IWindow *CWindow::CreateInstance()
			{
				return new CWindow();
			}

			Key CWindow::VirtualToKey(const int value)
			{
				switch (value)
				{
				case VK_LBUTTON:				return Key::LButton;
				case VK_RBUTTON:				return Key::RButton;
				case VK_CANCEL:					return Key::Cancel;
				case VK_MBUTTON:				return Key::MButton;
				case VK_XBUTTON1:				return Key::XButton1;
				case VK_XBUTTON2:				return Key::XButton2;
				case VK_BACK:					return Key::Backspace;
				case VK_TAB:					return Key::Tab;
				case VK_CLEAR:					return Key::Clear;
				case VK_RETURN:					return Key::Return;
				case VK_SHIFT:					return Key::Shift;
				case VK_CONTROL:				return Key::Control;
				case VK_MENU:					return Key::Menu;
				case VK_PAUSE:					return Key::Pause;
				case VK_CAPITAL:				return Key::CapsLock;
				case VK_KANA:					return Key::Kana;
				case VK_JUNJA:					return Key::Junja;
				case VK_FINAL:					return Key::Final;
				case VK_HANJA:					return Key::Hanja;
				case VK_ESCAPE:					return Key::Escape;
				case VK_CONVERT:				return Key::Convert;
				case VK_NONCONVERT:				return Key::NonConvert;
				case VK_ACCEPT:					return Key::Accept;
				case VK_MODECHANGE:				return Key::ModeChange;
				case VK_SPACE:					return Key::Space;
				case VK_PRIOR:					return Key::Prior;
				case VK_NEXT:					return Key::Next;
				case VK_END:					return Key::End;
				case VK_HOME:					return Key::Home;
				case VK_LEFT:					return Key::Left;
				case VK_UP:						return Key::Up;
				case VK_RIGHT:					return Key::Right;
				case VK_DOWN:					return Key::Down;
				case VK_SELECT:					return Key::Select;
				case VK_PRINT:					return Key::Print;
				case VK_EXECUTE:				return Key::Execute;
				case VK_SNAPSHOT:				return Key::Snapshot;
				case VK_INSERT:					return Key::Insert;
				case VK_DELETE:					return Key::Delete;
				case VK_HELP:					return Key::Help;
				case 0x30:						return Key::Key0;
				case 0x31:						return Key::Key1;
				case 0x32:						return Key::Key2;
				case 0x33:						return Key::Key3;
				case 0x34:						return Key::Key4;
				case 0x35:						return Key::Key5;
				case 0x36:						return Key::Key6;
				case 0x37:						return Key::Key7;
				case 0x38:						return Key::Key8;
				case 0x39:						return Key::Key9;
				case 0x41:						return Key::A;
				case 0x42:						return Key::B;
				case 0x43:						return Key::C;
				case 0x44:						return Key::D;
				case 0x45:						return Key::E;
				case 0x46:						return Key::F;
				case 0x47:						return Key::G;
				case 0x48:						return Key::H;
				case 0x49:						return Key::I;
				case 0x4A:						return Key::J;
				case 0x4B:						return Key::K;
				case 0x4C:						return Key::L;
				case 0x4D:						return Key::M;
				case 0x4E:						return Key::N;
				case 0x4F:						return Key::O;
				case 0x50:						return Key::P;
				case 0x51:						return Key::Q;
				case 0x52:						return Key::R;
				case 0x53:						return Key::S;
				case 0x54:						return Key::T;
				case 0x55:						return Key::U;
				case 0x56:						return Key::V;
				case 0x57:						return Key::W;
				case 0x58:						return Key::X;
				case 0x59:						return Key::Y;
				case 0x5A:						return Key::Z;
				case VK_LWIN:					return Key::LWin;
				case VK_RWIN:					return Key::RWin;
				case VK_APPS:					return Key::Apps;
				case VK_SLEEP:					return Key::Sleep;
				case VK_NUMPAD0:				return Key::Numpad0;
				case VK_NUMPAD1:				return Key::Numpad1;
				case VK_NUMPAD2:				return Key::Numpad2;
				case VK_NUMPAD3:				return Key::Numpad3;
				case VK_NUMPAD4:				return Key::Numpad4;
				case VK_NUMPAD5:				return Key::Numpad5;
				case VK_NUMPAD6:				return Key::Numpad6;
				case VK_NUMPAD7:				return Key::Numpad7;
				case VK_NUMPAD8:				return Key::Numpad8;
				case VK_NUMPAD9:				return Key::Numpad9;
				case VK_MULTIPLY:				return Key::Multiply;
				case VK_ADD:					return Key::Add;
				case VK_SEPARATOR:				return Key::Separator;
				case VK_SUBTRACT:				return Key::Subtract;
				case VK_DECIMAL:				return Key::Decimal;
				case VK_DIVIDE:					return Key::Divide;
				case VK_F1:						return Key::F1;
				case VK_F2:						return Key::F2;
				case VK_F3:						return Key::F3;
				case VK_F4:						return Key::F4;
				case VK_F5:						return Key::F5;
				case VK_F6:						return Key::F6;
				case VK_F7:						return Key::F7;
				case VK_F8:						return Key::F8;
				case VK_F9:						return Key::F9;
				case VK_F10:					return Key::F10;
				case VK_F11:					return Key::F11;
				case VK_F12:					return Key::F12;
				case VK_F13:					return Key::F13;
				case VK_F14:					return Key::F14;
				case VK_F15:					return Key::F15;
				case VK_F16:					return Key::F16;
				case VK_F17:					return Key::F17;
				case VK_F18:					return Key::F18;
				case VK_F19:					return Key::F19;
				case VK_F20:					return Key::F20;
				case VK_F21:					return Key::F21;
				case VK_F22:					return Key::F22;
				case VK_F23:					return Key::F23;
				case VK_F24:					return Key::F24;
				case VK_NUMLOCK:				return Key::NumLock;
				case VK_SCROLL:					return Key::ScrollLock;
				case VK_LSHIFT:					return Key::LShift;
				case VK_RSHIFT:					return Key::RShift;
				case VK_LCONTROL:				return Key::LControl;
				case VK_RCONTROL:				return Key::RControl;
				case VK_LMENU:					return Key::LMenu;
				case VK_RMENU:					return Key::RMenu;
				case VK_BROWSER_BACK:			return Key::BrowserBack;
				case VK_BROWSER_FORWARD:		return Key::BrowserForward;
				case VK_BROWSER_REFRESH:		return Key::BrowserRefresh;
				case VK_BROWSER_STOP:			return Key::BrowserStop;
				case VK_BROWSER_SEARCH:			return Key::BrowserSearch;
				case VK_BROWSER_FAVORITES:		return Key::BrowserFavorites;
				case VK_BROWSER_HOME:			return Key::BrowserHome;
				case VK_VOLUME_MUTE:			return Key::VolumeMute;
				case VK_VOLUME_DOWN:			return Key::VolumeDown;
				case VK_VOLUME_UP:				return Key::VolumeUp;
				case VK_MEDIA_NEXT_TRACK:		return Key::MediaNextTrack;
				case VK_MEDIA_PREV_TRACK:		return Key::MediaPrevTrack;
				case VK_MEDIA_STOP:				return Key::MediaStop;
				case VK_MEDIA_PLAY_PAUSE:		return Key::MediaPlayPause;
				case VK_LAUNCH_MAIL:			return Key::LaunchMail;
				case VK_LAUNCH_MEDIA_SELECT:	return Key::LaunchMediaSelect;
				case VK_LAUNCH_APP1:			return Key::LaunchApp1;
				case VK_LAUNCH_APP2:			return Key::LaunchApp2;
				case VK_OEM_1:					return Key::Semicolon;
				case VK_OEM_PLUS:				return Key::OemPlus;
				case VK_OEM_COMMA:				return Key::OemComma;
				case VK_OEM_MINUS:				return Key::OemMinus;
				case VK_OEM_PERIOD:				return Key::OemPeriod;
				case VK_OEM_2:					return Key::Slash;
				case VK_OEM_3:					return Key::Tilde;
				case VK_OEM_4:					return Key::LeftBracket;
				case VK_OEM_5:					return Key::BackSlash;
				case VK_OEM_6:					return Key::RightBracket;
				case VK_OEM_7:					return Key::Apostrophe;
				case VK_OEM_8:					return Key::Oem8;
				case VK_OEM_102:				return Key::Oem102;
				case VK_PROCESSKEY:				return Key::ProcessKey;
				case VK_PACKET:					return Key::Packet;
				case VK_ATTN:					return Key::Attn;
				case VK_CRSEL:					return Key::CrSel;
				case VK_EXSEL:					return Key::ExSel;
				case VK_EREOF:					return Key::ErEOF;
				case VK_PLAY:					return Key::Play;
				case VK_ZOOM:					return Key::Zoom;
				case VK_PA1:					return Key::PA1;
				case VK_OEM_CLEAR:				return Key::OemClear;
				default:						return Key::Unknown;
				}
			}

			int CWindow::KeyToVirtual(const Key value)
			{
				switch (value)
				{
				case Key::LButton: return VK_LBUTTON;
				case Key::RButton: return VK_RBUTTON;
				case Key::Cancel: return VK_CANCEL;
				case Key::MButton: return VK_MBUTTON;
				case Key::XButton1: return VK_XBUTTON1;
				case Key::XButton2: return VK_XBUTTON2;
				case Key::Backspace: return VK_BACK;
				case Key::Tab: return VK_TAB;
				case Key::Clear: return VK_CLEAR;
				case Key::Return: return VK_RETURN;
				case Key::Shift: return VK_SHIFT;
				case Key::Control: return VK_CONTROL;
				case Key::Menu: return VK_MENU;
				case Key::Pause: return VK_PAUSE;
				case Key::CapsLock: return VK_CAPITAL;
				case Key::Kana: return VK_KANA;
				case Key::Junja: return VK_JUNJA;
				case Key::Final: return VK_FINAL;
				case Key::Hanja: return VK_HANJA;
				case Key::Escape: return VK_ESCAPE;
				case Key::Convert: return VK_CONVERT;
				case Key::NonConvert: return VK_NONCONVERT;
				case Key::Accept: return VK_ACCEPT;
				case Key::ModeChange: return VK_MODECHANGE;
				case Key::Space: return VK_SPACE;
				case Key::Prior: return VK_PRIOR;
				case Key::Next: return VK_NEXT;
				case Key::End: return VK_END;
				case Key::Home: return VK_HOME;
				case Key::Left: return VK_LEFT;
				case Key::Up: return VK_UP;
				case Key::Right: return VK_RIGHT;
				case Key::Down: return VK_DOWN;
				case Key::Select: return VK_SELECT;
				case Key::Print: return VK_PRINT;
				case Key::Execute: return VK_EXECUTE;
				case Key::Snapshot: return VK_SNAPSHOT;
				case Key::Insert: return VK_INSERT;
				case Key::Delete: return VK_DELETE;
				case Key::Help: return VK_HELP;
				case Key::Key0: return 0x30;
				case Key::Key1: return 0x31;
				case Key::Key2: return 0x32;
				case Key::Key3: return 0x33;
				case Key::Key4: return 0x34;
				case Key::Key5: return 0x35;
				case Key::Key6: return 0x36;
				case Key::Key7: return 0x37;
				case Key::Key8: return 0x38;
				case Key::Key9: return 0x39;
				case Key::A: return 0x41;
				case Key::B: return 0x42;
				case Key::C: return 0x43;
				case Key::D: return 0x44;
				case Key::E: return 0x45;
				case Key::F: return 0x46;
				case Key::G: return 0x47;
				case Key::H: return 0x48;
				case Key::I: return 0x49;
				case Key::J: return 0x4A;
				case Key::K: return 0x4B;
				case Key::L: return 0x4C;
				case Key::M: return 0x4D;
				case Key::N: return 0x4E;
				case Key::O: return 0x4F;
				case Key::P: return 0x50;
				case Key::Q: return 0x51;
				case Key::R: return 0x52;
				case Key::S: return 0x53;
				case Key::T: return 0x54;
				case Key::U: return 0x55;
				case Key::V: return 0x56;
				case Key::W: return 0x57;
				case Key::X: return 0x58;
				case Key::Y: return 0x59;
				case Key::Z: return 0x5A;
				case Key::LWin: return VK_LWIN;
				case Key::RWin: return VK_RWIN;
				case Key::Apps: return VK_APPS;
				case Key::Sleep: return VK_SLEEP;
				case Key::Numpad0: return VK_NUMPAD0;
				case Key::Numpad1: return VK_NUMPAD1;
				case Key::Numpad2: return VK_NUMPAD2;
				case Key::Numpad3: return VK_NUMPAD3;
				case Key::Numpad4: return VK_NUMPAD4;
				case Key::Numpad5: return VK_NUMPAD5;
				case Key::Numpad6: return VK_NUMPAD6;
				case Key::Numpad7: return VK_NUMPAD7;
				case Key::Numpad8: return VK_NUMPAD8;
				case Key::Numpad9: return VK_NUMPAD9;
				case Key::Multiply: return VK_MULTIPLY;
				case Key::Add: return VK_ADD;
				case Key::Separator: return VK_SEPARATOR;
				case Key::Subtract: return VK_SUBTRACT;
				case Key::Decimal: return VK_DECIMAL;
				case Key::Divide: return VK_DIVIDE;
				case Key::F1: return VK_F1;
				case Key::F2: return VK_F2;
				case Key::F3: return VK_F3;
				case Key::F4: return VK_F4;
				case Key::F5: return VK_F5;
				case Key::F6: return VK_F6;
				case Key::F7: return VK_F7;
				case Key::F8: return VK_F8;
				case Key::F9: return VK_F9;
				case Key::F10: return VK_F10;
				case Key::F11: return VK_F11;
				case Key::F12: return VK_F12;
				case Key::F13: return VK_F13;
				case Key::F14: return VK_F14;
				case Key::F15: return VK_F15;
				case Key::F16: return VK_F16;
				case Key::F17: return VK_F17;
				case Key::F18: return VK_F18;
				case Key::F19: return VK_F19;
				case Key::F20: return VK_F20;
				case Key::F21: return VK_F21;
				case Key::F22: return VK_F22;
				case Key::F23: return VK_F23;
				case Key::F24: return VK_F24;
				case Key::NumLock: return VK_NUMLOCK;
				case Key::ScrollLock: return VK_SCROLL;
				case Key::LShift: return VK_LSHIFT;
				case Key::RShift: return VK_RSHIFT;
				case Key::LControl: return VK_LCONTROL;
				case Key::RControl: return VK_RCONTROL;
				case Key::LMenu: return VK_LMENU;
				case Key::RMenu: return VK_RMENU;
				case Key::BrowserBack: return VK_BROWSER_BACK;
				case Key::BrowserForward: return VK_BROWSER_FORWARD;
				case Key::BrowserRefresh: return VK_BROWSER_REFRESH;
				case Key::BrowserStop: return VK_BROWSER_STOP;
				case Key::BrowserSearch: return VK_BROWSER_SEARCH;
				case Key::BrowserFavorites: return VK_BROWSER_FAVORITES;
				case Key::BrowserHome: return VK_BROWSER_HOME;
				case Key::VolumeMute: return VK_VOLUME_MUTE;
				case Key::VolumeDown: return VK_VOLUME_DOWN;
				case Key::VolumeUp: return VK_VOLUME_UP;
				case Key::MediaNextTrack: return VK_MEDIA_NEXT_TRACK;
				case Key::MediaPrevTrack: return VK_MEDIA_PREV_TRACK;
				case Key::MediaStop: return VK_MEDIA_STOP;
				case Key::MediaPlayPause: return VK_MEDIA_PLAY_PAUSE;
				case Key::LaunchMail: return VK_LAUNCH_MAIL;
				case Key::LaunchMediaSelect: return VK_LAUNCH_MEDIA_SELECT;
				case Key::LaunchApp1: return VK_LAUNCH_APP1;
				case Key::LaunchApp2: return VK_LAUNCH_APP2;
				case Key::Semicolon: return VK_OEM_1;
				case Key::OemPlus: return VK_OEM_PLUS;
				case Key::OemComma: return VK_OEM_COMMA;
				case Key::OemMinus: return VK_OEM_MINUS;
				case Key::OemPeriod: return VK_OEM_PERIOD;
				case Key::Slash: return VK_OEM_2;
				case Key::Tilde: return VK_OEM_3;
				case Key::LeftBracket: return VK_OEM_4;
				case Key::BackSlash: return VK_OEM_5;
				case Key::RightBracket: return VK_OEM_6;
				case Key::Apostrophe: return VK_OEM_7;
				case Key::Oem8: return VK_OEM_8;
				case Key::Oem102: return VK_OEM_102;
				case Key::ProcessKey: return VK_PROCESSKEY;
				case Key::Packet: return VK_PACKET;
				case Key::Attn: return VK_ATTN;
				case Key::CrSel: return VK_CRSEL;
				case Key::ExSel: return VK_EXSEL;
				case Key::ErEOF: return VK_EREOF;
				case Key::Play: return VK_PLAY;
				case Key::Zoom: return VK_ZOOM;
				case Key::PA1: return VK_PA1;
				case Key::OemClear: return VK_OEM_CLEAR;
				default: return 0;
				}
			}
		#pragma endregion
		}
	}
}
#endif