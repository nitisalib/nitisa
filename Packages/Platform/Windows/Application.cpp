// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#include "../OpenGL/ngl.h"
#include <ShObjIdl.h>
#include <shellapi.h>
#include <windowsx.h>

namespace nitisa
{
	IApplication *Application{ nullptr };

	namespace platform
	{
		namespace windows
		{
			const String DefaultWindowClassName{ L"nitisa_window_default_classex" };
			UINT MsgTaskBarButtonCreated{ 0 };
			bool MsgTaskBarButtonCreatedInitialized{ false };
			ITaskbarList3 *TaskBar{ nullptr };

			HMODULE GetCurrentModuleHandle()
			{
				HMODULE hMod{ NULL };
				GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&GetCurrentModuleHandle), &hMod);
				return hMod;
			}

		#pragma region PD_APPLICATION
			struct PD_APPLICATION
			{
				WNDCLASSEX m_sWindowClassInfo;
				ATOM m_hWindowClassHandle;
				WPARAM m_iExitCode;

				PD_APPLICATION() :
					m_hWindowClassHandle{ 0 },
					m_iExitCode{ 0 }
				{

				}

				void WindowClassRegister()
				{
					m_sWindowClassInfo.cbClsExtra = 0;
					m_sWindowClassInfo.cbSize = sizeof(WNDCLASSEX);
					m_sWindowClassInfo.cbWndExtra = 0;
					m_sWindowClassInfo.hbrBackground = NULL;// (HBRUSH)COLOR_WINDOW;
					m_sWindowClassInfo.hCursor = LoadCursorW(0, IDC_ARROW);
					m_sWindowClassInfo.hIcon = 0;
					m_sWindowClassInfo.hIconSm = 0;
					m_sWindowClassInfo.hInstance = *reinterpret_cast<const HINSTANCE*>(&Application->Handle);
					m_sWindowClassInfo.lpfnWndProc = WindowProc;
					m_sWindowClassInfo.lpszClassName = DefaultWindowClassName.c_str();
					m_sWindowClassInfo.lpszMenuName = 0;
					m_sWindowClassInfo.style = CS_CLASSDC | CS_DBLCLKS | CS_OWNDC;
					m_hWindowClassHandle = RegisterClassExW(&m_sWindowClassInfo);
				}

				void WindowClassUnregister()
				{
					if (m_hWindowClassHandle)
					{
						UnregisterClassW(DefaultWindowClassName.c_str(), *reinterpret_cast<const HINSTANCE*>(&Application->Handle));
						m_hWindowClassHandle = 0;
					}
				}

				
				static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
				{
					CApplication *app{ cast<CApplication*>(Application) };
					if (uMsg == WM_NCCREATE)
					{
						IWindow *window{ (IWindow*)((CREATESTRUCT*)(lParam))->lpCreateParams };
						if (window)
							window->QueryService()->setHandle(*reinterpret_cast<PlatformHandle*>(&hWnd));
						app->m_aWindows.push_back(CApplication::WINDOW{ *reinterpret_cast<PlatformHandle*>(&hWnd), window, nullptr });
						app->m_bWindowsSorted = false;
					}
					else
					{
						int index{ app->FindWindowIndex(*reinterpret_cast<PlatformHandle*>(&hWnd)) };
						if (uMsg == WM_NCDESTROY)
						{
							if (index >= 0)
							{
								CApplication::WINDOW info{ app->m_aWindows[index] };
								app->m_aWindows.erase(app->m_aWindows.begin() + index);
								if (((info.Form && info.Form == app->m_pMainForm) || app->m_aWindows.size() == 0) && app->Global)
								{
									std::vector<CApplication::WINDOW> to_destroy;
									for (auto pos : app->m_aWindows)
										if (pos.Form != app->m_pMainForm)
										{
											if (pos.Window)
											{
												if (pos.Window->getParent())
													continue;
											}
											else if (GetWindow(*reinterpret_cast<HWND*>(&pos.Handle), GW_OWNER))
												continue;
											to_destroy.push_back(pos);
										}
									for (auto pos : to_destroy)
										DestroyWindow(*reinterpret_cast<HWND*>(&pos.Handle));
									app->m_pMainForm = nullptr;
									PostQuitMessage(0);
								}
								if (info.Form)
									info.Form->Release();
								if (info.Window)
								{
									info.Window->QueryService()->setListener(nullptr);
									info.Window->QueryService()->setHandle(0);
									info.Window->Release();
								}
							}
							if (app->OnDestroyLastWindow && app->m_aWindows.size() == 0)
								app->OnDestroyLastWindow();
							return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						}
						else if (index >= 0)
						{
							CWindow *window{ cast<CWindow*>(app->m_aWindows[index].Window) };
							if (window)
								return WindowProcedure(window, hWnd, uMsg, wParam, lParam);
						}
					}
					return DefWindowProcW(hWnd, uMsg, wParam, lParam);
				}

				static LRESULT WindowProcedure(CWindow *window, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
				{
					if (MsgTaskBarButtonCreatedInitialized && MsgTaskBarButtonCreated > 0 && uMsg == MsgTaskBarButtonCreated)
					{
						if (TaskBar)
						{
							TaskBar->Release();
							TaskBar = nullptr;
						}
						CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_ALL, IID_ITaskbarList3, (void**)&TaskBar);
						return 0;
					}
					switch (uMsg)
					{
					case WM_CREATE:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							window->m_pListener->OnCreate();
						if (!MsgTaskBarButtonCreatedInitialized)
						{
							MsgTaskBarButtonCreated = RegisterWindowMessage(L"TaskbarButtonCreated");
							MsgTaskBarButtonCreatedInitialized = true;
						}
						if (MsgTaskBarButtonCreated > 0)
						{
							CHANGEFILTERSTRUCT c{ sizeof(CHANGEFILTERSTRUCT) };
							ChangeWindowMessageFilterEx(hWnd, MsgTaskBarButtonCreated, MSGFLT_ALLOW, &c);
						}
						return 0;
					case WM_DESTROY:
						window->DeleteTimers();
						if (window->m_pListener)
							window->m_pListener->OnDestroy();
						if (window->m_bAcceptDragAndDrop)
							RevokeDragDrop(hWnd);
						if (window->m_bAcceptDropFiles)
							DragAcceptFiles(hWnd, FALSE);
						*reinterpret_cast<HWND*>(&window->m_hHandle) = 0;
						return 0;
					case WM_MOVE:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessagePosition m{ PointF{ (float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam) } };
							window->m_pListener->OnMove(m);
						}
						return 0;
					case WM_SIZE:
						switch (wParam)
						{
						case SIZE_RESTORED:
							if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							{
								MessageSize m{ PointF{ (float)LOWORD(lParam), (float)HIWORD(lParam) } };
								window->m_pListener->OnRestore(m);
							}
							return 0;
						case SIZE_MINIMIZED:
							if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							{
								MessageSize m{ PointF{ (float)LOWORD(lParam), (float)HIWORD(lParam) } };
								window->m_pListener->OnMinimize(m);
							}
							return 0;
						case SIZE_MAXIMIZED:
							if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							{
								MessageSize m{ PointF{ (float)LOWORD(lParam), (float)HIWORD(lParam) } };
								window->m_pListener->OnMaximize(m);
							}
							return 0;
						}
						break;
					case WM_ACTIVATE:
						switch (LOWORD(wParam))
						{
						case WA_ACTIVE:
							if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							{
								MessageWindowActivate m{ false };
								window->m_pListener->OnActivate(m);
							}
							break;
						case WA_CLICKACTIVE:
							if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							{
								MessageWindowActivate m{ true };
								window->m_pListener->OnActivate(m);
							}
							break;
						default:
							if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
								window->m_pListener->OnDeactivate();
						}
						return 0;
					case WM_SETFOCUS:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							window->m_pListener->OnSetFocus();
						return 0;
					case WM_KILLFOCUS:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							window->m_pListener->OnKillFocus();
						return 0;
					case WM_ENABLE:
						if (wParam == TRUE)
						{
							if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
								window->m_pListener->OnEnable();
						}
						else
							if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
								window->m_pListener->OnDisable();
						return 0;
					case WM_PAINT: // Renderer is fully responsible for drawing. It should call BeginPaint() and EndPaint() if it is required
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							PAINTSTRUCT p;
							BeginPaint(*reinterpret_cast<HWND*>(&window->m_hHandle), &p);
							window->m_pListener->OnPaint(MessageRect{ RectF{ (float)p.rcPaint.left, (float)p.rcPaint.top, (float)p.rcPaint.right, (float)p.rcPaint.bottom } });
							EndPaint(*reinterpret_cast<HWND*>(&window->m_hHandle), &p);
						}
						return 0;
					case WM_CLOSE:
					{
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							CloseAction action{ cast<CApplication*>(Application)->getCloseAction(window) };
							window->m_pListener->OnClose(action);
							switch (action)
							{
							case CloseAction::None:
								return 0;
							case CloseAction::Hide:
								window->ExitModal();
								ShowWindow(hWnd, SW_HIDE);
								return 0;
							case CloseAction::Minimize:
								window->ExitModal();
								ShowWindow(hWnd, SW_MINIMIZE);
								return 0;
							}
						}
						window->ExitModal();
					}
					return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_QUERYENDSESSION:
					{
						bool restricted{ false };
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							window->m_pListener->OnQueryEndSession(restricted);
						return restricted ? FALSE : TRUE;
					}
					case WM_QUERYOPEN:
					{
						bool restricted{ false };
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							window->m_pListener->OnQueryOpen(restricted);
						return restricted ? FALSE : TRUE;
					}
					case WM_ENDSESSION:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageEndSession m{ wParam ? true : false };
							window->m_pListener->OnEndSession(m);
						}
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_SHOWWINDOW:
						if (wParam)
						{
							if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
								window->m_pListener->OnShow();
						}
						else
							if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
								window->m_pListener->OnHide();
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_DEVMODECHANGE:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							window->m_pListener->OnDeviceModeChange();
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_ACTIVATEAPP:
						if (wParam)
						{
							if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
								window->m_pListener->OnActivateApp();
						}
						else
							if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
								window->m_pListener->OnDeactivateApp();
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_TIMECHANGE:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							window->m_pListener->OnTimeChange();
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_INPUTLANGCHANGEREQUEST:
					{
						bool restricted{ false };
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							window->m_pListener->OnInputLanguageChangeRequest(restricted);
						return restricted ? 0 : DefWindowProcW(hWnd, uMsg, wParam, lParam);
					}
					case WM_INPUTLANGCHANGE:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							window->m_pListener->OnInputLanguageChange();
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_DISPLAYCHANGE:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageSize m{ PointF{ (float)LOWORD(lParam), (float)HIWORD(lParam) } };
							window->m_pListener->OnDisplayChange(m);
						}
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_KEYDOWN:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageKey m{ CWindow::VirtualToKey((int)wParam), nullptr };
							window->m_pListener->OnKeyDown(m);
						}
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_KEYUP:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageKey m{ CWindow::VirtualToKey((int)wParam), nullptr };
							window->m_pListener->OnKeyUp(m);
						}
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_CHAR:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageChar m{ (wchar_t)wParam, nullptr };
							window->m_pListener->OnChar(m);
						}
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_DEADCHAR:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageChar m{ (wchar_t)wParam, nullptr };
							window->m_pListener->OnDeadChar(m);
						}
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_SYSKEYDOWN:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageKey m{ CWindow::VirtualToKey((int)wParam), nullptr };
							window->m_pListener->OnKeyDown(m);
						}
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_SYSKEYUP:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageKey m{ CWindow::VirtualToKey((int)wParam), nullptr };
							window->m_pListener->OnKeyUp(m);
						}
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_SYSCHAR:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageChar m{ (wchar_t)wParam, nullptr };
							window->m_pListener->OnChar(m);
						}
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_SYSDEADCHAR:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageChar m{ (wchar_t)wParam, nullptr };
							window->m_pListener->OnDeadChar(m);
						}
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_HSCROLL:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							ScrollType type{ ScrollType::None };
							switch (LOWORD(wParam))
							{
							case SB_ENDSCROLL:
								type = ScrollType::EndScroll;
								break;
							case SB_LEFT:
								type = ScrollType::Left;
								break;
							case SB_RIGHT:
								type = ScrollType::Right;
								break;
							case SB_LINELEFT:
								type = ScrollType::LineLeft;
								break;
							case SB_LINERIGHT:
								type = ScrollType::LineRight;
								break;
							case SB_PAGELEFT:
								type = ScrollType::PageLeft;
								break;
							case SB_PAGERIGHT:
								type = ScrollType::PageRight;
								break;
							case SB_THUMBPOSITION:
								type = ScrollType::ThumbPosition;
								break;
							case SB_THUMBTRACK:
								type = ScrollType::ThumbTrack;
								break;
							}
							MessageWindowScroll m{ type, HIWORD(wParam) };
							window->m_pListener->OnHScroll(m);
						}
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_VSCROLL:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							ScrollType type{ ScrollType::None };
							switch (LOWORD(wParam))
							{
							case SB_ENDSCROLL:
								type = ScrollType::EndScroll;
								break;
							case SB_LEFT:
								type = ScrollType::Left;
								break;
							case SB_RIGHT:
								type = ScrollType::Right;
								break;
							case SB_LINELEFT:
								type = ScrollType::LineLeft;
								break;
							case SB_LINERIGHT:
								type = ScrollType::LineRight;
								break;
							case SB_PAGELEFT:
								type = ScrollType::PageLeft;
								break;
							case SB_PAGERIGHT:
								type = ScrollType::PageRight;
								break;
							case SB_THUMBPOSITION:
								type = ScrollType::ThumbPosition;
								break;
							case SB_THUMBTRACK:
								type = ScrollType::ThumbTrack;
								break;
							}
							MessageWindowScroll m{ type, HIWORD(wParam) };
							window->m_pListener->OnVScroll(m);
						}
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_GESTURE:
						GESTUREINFO gesture;
						ZeroMemory(&gesture, sizeof(GESTUREINFO));
						gesture.cbSize = sizeof(GESTUREINFO);
						if (GetGestureInfo((HGESTUREINFO)lParam, &gesture))
							switch (gesture.dwID)
							{
							case GID_ZOOM:
								if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
								{
									MessagePosition m{ (PointF)window->ScreenToClient(Point{ gesture.ptsLocation.x, gesture.ptsLocation.y }) };
									window->m_pListener->OnGestureZoom(m);
								}
								return 0;
							case GID_PAN:
								if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
								{
									MessagePosition m{ (PointF)window->ScreenToClient(Point{ gesture.ptsLocation.x, gesture.ptsLocation.y }) };
									window->m_pListener->OnGesturePan(m);
								}
								return 0;
							case GID_ROTATE:
								if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
								{
									MessagePosition m{ (PointF)window->ScreenToClient(Point{ gesture.ptsLocation.x, gesture.ptsLocation.y }) };
									window->m_pListener->OnGestureRotate(m);
								}
								return 0;
							case GID_TWOFINGERTAP:
								if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
								{
									MessagePosition m{ (PointF)window->ScreenToClient(Point{ gesture.ptsLocation.x, gesture.ptsLocation.y }) };
									window->m_pListener->OnGestureTwoFingerTap(m);
								}
								return 0;
							case GID_PRESSANDTAP:
								if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
								{
									MessagePosition m{ (PointF)window->ScreenToClient(Point{ gesture.ptsLocation.x, gesture.ptsLocation.y }) };
									window->m_pListener->OnGesturePressAndTap(m);
								}
								return 0;
							}
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_GESTURENOTIFY:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							window->m_pListener->OnGestureNotify();
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_MOUSEMOVE:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageMouse m{
								PointF{ (float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam) },
								(wParam & MK_CONTROL) ? true : false,
								Application->Keyboard->isDown(Key::Menu),
								(wParam & MK_SHIFT) ? true : false,
								(wParam & MK_LBUTTON) ? true : false,
								(wParam & MK_MBUTTON) ? true : false,
								(wParam & MK_RBUTTON) ? true : false,
								nullptr };
							window->m_pListener->OnMouseMove(m);
						}
						return 0;
					case WM_LBUTTONDOWN:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageMouse m{
								PointF{ (float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam) },
								(wParam & MK_CONTROL) ? true : false,
								Application->Keyboard->isDown(Key::Menu),
								(wParam & MK_SHIFT) ? true : false,
								true,
								(wParam & MK_MBUTTON) ? true : false,
								(wParam & MK_RBUTTON) ? true : false,
								nullptr };
							window->m_pListener->OnLeftMouseButtonDown(m);
						}
						return 0;
					case WM_LBUTTONUP:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageMouse m{
								PointF{ (float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam) },
								(wParam & MK_CONTROL) ? true : false,
								Application->Keyboard->isDown(Key::Menu),
								(wParam & MK_SHIFT) ? true : false,
								true,
								(wParam & MK_MBUTTON) ? true : false,
								(wParam & MK_RBUTTON) ? true : false,
								nullptr };
							window->m_pListener->OnLeftMouseButtonUp(m);
						}
						return 0;
					case WM_LBUTTONDBLCLK:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageMouse m{
								PointF{ (float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam) },
								(wParam & MK_CONTROL) ? true : false,
								Application->Keyboard->isDown(Key::Menu),
								(wParam & MK_SHIFT) ? true : false,
								true,
								(wParam & MK_MBUTTON) ? true : false,
								(wParam & MK_RBUTTON) ? true : false,
								nullptr };
							window->m_pListener->OnLeftMouseButtonDoubleClick(m);
						}
						return 0;
					case WM_RBUTTONDOWN:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageMouse m{
								PointF{ (float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam) },
								(wParam & MK_CONTROL) ? true : false,
								Application->Keyboard->isDown(Key::Menu),
								(wParam & MK_SHIFT) ? true : false,
								(wParam & MK_LBUTTON) ? true : false,
								(wParam & MK_MBUTTON) ? true : false,
								true,
								nullptr };
							window->m_pListener->OnRightMouseButtonDown(m);
						}
						return 0;
					case WM_RBUTTONUP:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageMouse m{
								PointF{ (float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam) },
								(wParam & MK_CONTROL) ? true : false,
								Application->Keyboard->isDown(Key::Menu),
								(wParam & MK_SHIFT) ? true : false,
								(wParam & MK_LBUTTON) ? true : false,
								(wParam & MK_MBUTTON) ? true : false,
								true,
								nullptr };
							window->m_pListener->OnRightMouseButtonUp(m);
						}
						return 0;
					case WM_RBUTTONDBLCLK:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageMouse m{
								PointF{ (float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam) },
								(wParam & MK_CONTROL) ? true : false,
								Application->Keyboard->isDown(Key::Menu),
								(wParam & MK_SHIFT) ? true : false,
								(wParam & MK_LBUTTON) ? true : false,
								(wParam & MK_MBUTTON) ? true : false,
								true,
								nullptr };
							window->m_pListener->OnRightMouseButtonDoubleClick(m);
						}
						return 0;
					case WM_MBUTTONDOWN:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageMouse m{
								PointF{ (float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam) },
								(wParam & MK_CONTROL) ? true : false,
								Application->Keyboard->isDown(Key::Menu),
								(wParam & MK_SHIFT) ? true : false,
								(wParam & MK_LBUTTON) ? true : false,
								true,
								(wParam & MK_RBUTTON) ? true : false,
								nullptr };
							window->m_pListener->OnMiddleMouseButtonDown(m);
						}
						return 0;
					case WM_MBUTTONUP:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageMouse m{
								PointF{ (float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam) },
								(wParam & MK_CONTROL) ? true : false,
								Application->Keyboard->isDown(Key::Menu),
								(wParam & MK_SHIFT) ? true : false,
								(wParam & MK_LBUTTON) ? true : false,
								true,
								(wParam & MK_RBUTTON) ? true : false,
								nullptr };
							window->m_pListener->OnMiddleMouseButtonUp(m);
						}
						return 0;
					case WM_MBUTTONDBLCLK:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageMouse m{
								PointF{ (float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam) },
								(wParam & MK_CONTROL) ? true : false,
								Application->Keyboard->isDown(Key::Menu),
								(wParam & MK_SHIFT) ? true : false,
								(wParam & MK_LBUTTON) ? true : false,
								true,
								(wParam & MK_RBUTTON) ? true : false,
								nullptr };
							window->m_pListener->OnMiddleMouseButtonDoubleClick(m);
						}
						return 0;
					case WM_MOUSEWHEEL:
					{
						int keys{ GET_KEYSTATE_WPARAM(wParam) }, delta{ GET_WHEEL_DELTA_WPARAM(wParam) };
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageMouseWheel m{
								(PointF)window->ScreenToClient(Point{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) }),
								(wParam & MK_CONTROL) ? true : false,
								Application->Keyboard->isDown(Key::Menu),
								(wParam & MK_SHIFT) ? true : false,
								(wParam & MK_LBUTTON) ? true : false,
								(wParam & MK_MBUTTON) ? true : false,
								(wParam & MK_RBUTTON) ? true : false,
								(int)delta,
								nullptr };
							window->m_pListener->OnMouseVerticalWheel(m);
						}
					}
					return 0;
					case WM_MOUSEHWHEEL:
					{
						int keys{ GET_KEYSTATE_WPARAM(wParam) }, delta{ GET_WHEEL_DELTA_WPARAM(wParam) };
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageMouseWheel m{
								(PointF)window->ScreenToClient(Point{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) }),
								(wParam & MK_CONTROL) ? true : false,
								Application->Keyboard->isDown(Key::Menu),
								(wParam & MK_SHIFT) ? true : false,
								(wParam & MK_LBUTTON) ? true : false,
								(wParam & MK_MBUTTON) ? true : false,
								(wParam & MK_RBUTTON) ? true : false,
								(int)delta,
								nullptr };
							window->m_pListener->OnMouseHorizontalWheel(m);
						}
					}
					return 0;
					case WM_SIZING:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							EdgeType edge{ EdgeType::None };
							switch (wParam)
							{
							case WMSZ_BOTTOM:
								edge = EdgeType::Bottom;
								break;
							case WMSZ_BOTTOMLEFT:
								edge = EdgeType::BottomLeft;
								break;
							case WMSZ_BOTTOMRIGHT:
								edge = EdgeType::BottomRight;
								break;
							case WMSZ_LEFT:
								edge = EdgeType::Left;
								break;
							case WMSZ_RIGHT:
								edge = EdgeType::Right;
								break;
							case WMSZ_TOP:
								edge = EdgeType::Top;
								break;
							case WMSZ_TOPLEFT:
								edge = EdgeType::TopLeft;
								break;
							case WMSZ_TOPRIGHT:
								edge = EdgeType::TopRight;
								break;
							}
							MessageWindowResizing m{ Rect{ ((RECT*)lParam)->left, ((RECT*)lParam)->top, ((RECT*)lParam)->right, ((RECT*)lParam)->bottom }, edge };
							window->m_pListener->OnResizing(m);
						}
						return TRUE;
					case WM_CAPTURECHANGED:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							window->m_pListener->OnLoseCapture();
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_MOVING:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageRect m{ RectF{ (float)((RECT*)lParam)->left, (float)((RECT*)lParam)->top, (float)((RECT*)lParam)->right, (float)((RECT*)lParam)->bottom } };
							window->m_pListener->OnMoving(m);
						}
						return TRUE;
					case WM_ENTERSIZEMOVE:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							window->m_pListener->OnEnterSizeMove();
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_EXITSIZEMOVE:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							window->m_pListener->OnExitSizeMove();
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_DROPFILES:
					{
						bool accepted{ false };
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							::POINT p;
							if (DragQueryPoint((HDROP)wParam, &p))
							{
								MessageDropFiles m;
								UINT count{ DragQueryFile((HDROP)wParam, 0xFFFFFFFF, 0, 0) };
								for (UINT i = 0; i < count; i++)
								{
									UINT buffer_size{ DragQueryFile((HDROP)wParam, i, 0, 0) };
									if (buffer_size > 0)
									{
										wchar_t *buffer = new wchar_t[buffer_size + 1];
										buffer[buffer_size] = 0;
										if (DragQueryFile((HDROP)wParam, i, buffer, buffer_size + 1))
										{
											String s{ buffer };
											m.FileNames.push_back(s);
										}
										delete[] buffer;
									}
								}
								m.Position = (PointF)window->ScreenToClient(Point{ p.x, p.y });
								m.Target = nullptr;
								bool accepted{ false };
								window->m_pListener->OnDropFiles(m, accepted);
								if (accepted)
									DragFinish((HDROP)wParam);
							}
						}
						return accepted ? 0 : DefWindowProcW(hWnd, uMsg, wParam, lParam);
					}
					case WM_TOUCH:
					{
						int count = LOWORD(wParam);
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && count > 0 && window->m_pListener)
						{
							TOUCHINPUT *inputs = new TOUCHINPUT[count];
							if (GetTouchInputInfo((HTOUCHINPUT)lParam, count, inputs, sizeof(TOUCHINPUT)))
							{
								MessageTouch m;
								for (int i = 0; i < count; i++)
								{
									TouchPoint point;
									point.Pos = (PointF)window->ScreenToClient(Point{ ntl::Round<int>(inputs[i].x * 0.01f), ntl::Round<int>(inputs[i].y * 0.01f) });
									point.Id = (int)inputs[i].dwID;
									point.IsMove = (inputs[i].dwFlags & TOUCHEVENTF_MOVE) > 0;
									point.IsDown = (inputs[i].dwFlags & TOUCHEVENTF_DOWN) > 0;
									point.IsUp = (inputs[i].dwFlags & TOUCHEVENTF_UP) > 0;
									point.IsInRange = (inputs[i].dwFlags & TOUCHEVENTF_INRANGE) > 0;
									point.IsPrimary = (inputs[i].dwFlags & TOUCHEVENTF_PRIMARY) > 0;
									point.IsNoCoalesce = (inputs[i].dwFlags & TOUCHEVENTF_NOCOALESCE) > 0;
									point.IsPalm = (inputs[i].dwFlags & TOUCHEVENTF_PALM) > 0;
									point.IsContactAreaValid = (inputs[i].dwMask & TOUCHINPUTMASKF_CONTACTAREA) > 0;
									point.IsTimeValid = (inputs[i].dwMask & TOUCHINPUTMASKF_TIMEFROMSYSTEM) > 0;
									if (point.IsTimeValid)
										point.Time = inputs[i].dwTime * 0.001f;
									if (point.IsContactAreaValid)
										point.ContactAreaSize = PointF{ inputs[i].cxContact * 0.01f, inputs[i].cyContact * 0.01f };
									m.Points.push_back(point);
								}
								delete[] inputs;
								CloseTouchInputHandle((HTOUCHINPUT)lParam);
								window->m_pListener->OnTouch(m);
								return 0;
							}
							delete[] inputs;
						}
					}
					return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_MOUSEHOVER:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
						{
							MessageMouse m{
								PointF{ (float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam) },
								(wParam & MK_CONTROL) ? true : false,
								Application->Keyboard->isDown(Key::Menu),
								(wParam & MK_SHIFT) ? true : false,
								(wParam & MK_LBUTTON) ? true : false,
								(wParam & MK_MBUTTON) ? true : false,
								(wParam & MK_RBUTTON) ? true : false,
								nullptr };
							window->m_pListener->OnMouseHover(m);
						}
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_MOUSELEAVE:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							window->m_pListener->OnMouseLeave();
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_THEMECHANGED:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							window->m_pListener->OnThemeChanged();
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_CLIPBOARDUPDATE:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
							window->m_pListener->OnClipboardUpdate();
						return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					case WM_TIMER:
						if (*reinterpret_cast<HWND*>(&window->m_hHandle))
						{
							for (auto pos : window->m_aTimers)
								if (pos.Id == (PlatformHandle)wParam)
								{
									pos.Listener->NotifyOnTimer(pos.Id);
									break;
								}
						}
						return 0;
					case WM_SETCURSOR:
						if (LOWORD(lParam) == HTCLIENT)
						{
							CursorType type{ CursorType::None };
							HCURSOR h{ GetCursor() };
							if (h == LoadCursor(0, IDC_APPSTARTING))
								type = CursorType::AppStarting;
							else if (h == LoadCursor(0, IDC_ARROW))
								type = CursorType::Arrow;
							else if (h == LoadCursor(0, IDC_CROSS))
								type = CursorType::Cross;
							else if (h == LoadCursor(0, IDC_HAND))
								type = CursorType::Hand;
							else if (h == LoadCursor(0, IDC_HELP))
								type = CursorType::Help;
							else if (h == LoadCursor(0, IDC_IBEAM))
								type = CursorType::IBeam;
							else if (h == LoadCursor(0, IDC_NO))
								type = CursorType::No;
							else if (h == LoadCursor(0, IDC_SIZEALL))
								type = CursorType::SizeAll;
							else if (h == LoadCursor(0, IDC_SIZENESW))
								type = CursorType::SizeNortheastSouthwest;
							else if (h == LoadCursor(0, IDC_SIZENS))
								type = CursorType::SizeNorthSouth;
							else if (h == LoadCursor(0, IDC_SIZENWSE))
								type = CursorType::SizeNorthwestSoutheast;
							else if (h == LoadCursor(0, IDC_SIZEWE))
								type = CursorType::SizeWestEast;
							else if (h == LoadCursor(0, IDC_UPARROW))
								type = CursorType::UpArrow;
							else if (h == LoadCursor(0, IDC_WAIT))
								type = CursorType::Wait;
							if (type != window->m_eCurrentCursor)
							{
								CursorType old{ window->m_eCurrentCursor };
								window->m_eCurrentCursor = type;
								window->setCursor(old);
							}
							return TRUE;
						}
						break;
					case WM_NCHITTEST:
						return DefWindowProc(hWnd, uMsg, wParam, lParam);
						//case WM_HELP:
						//	return OnHelp && OnHelp((HELPINFO*)lParam, m_pCallbackParam) ? 0 : DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_CONTEXTMENU:
						//	return OnContextMenu && m_fOnContextMenu(LOWORD(lParam), HIWORD(lParam), m_pCallbackParam) ? 0 : DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_NCPAINT:
						//	return OnNonClientPaint && m_fOnNonClientPaint((HRGN)wParam, m_pCallbackParam) ? 0 : DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_NCMOUSEMOVE:
						//	if (OnNonClientMouseMove)
						//		m_fOnNonClientMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_NCLBUTTONDOWN:
						//	if (OnNonClientLeftMouseButtonDown)
						//		m_fOnNonClientLeftMouseButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_NCLBUTTONUP:
						//	if (OnNonClientLeftMouseButtonUp)
						//		m_fOnNonClientLeftMouseButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_NCLBUTTONDBLCLK:
						//	if (OnNonClientLeftMouseButtonUp)
						//		m_fOnNonClientLeftMouseButtonDoubleClick(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_NCRBUTTONDOWN:
						//	if (OnNonClientRightMouseButtonDown)
						//		m_fOnNonClientRightMouseButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_NCRBUTTONUP:
						//	if (OnNonClientRightMouseButtonUp)
						//		m_fOnNonClientRightMouseButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_NCRBUTTONDBLCLK:
						//	if (OnNonClientRightMouseButtonDoubleClick)
						//		m_fOnNonClientRightMouseButtonDoubleClick(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_NCMBUTTONDOWN:
						//	if (OnNonClientMiddleMouseButtonDown)
						//		m_fOnNonClientMiddleMouseButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_NCMBUTTONUP:
						//	if (OnNonClientMiddleMouseButtonUp)
						//		m_fOnNonClientMiddleMouseButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_NCMBUTTONDBLCLK:
						//	if (OnNonClientMiddleMouseButtonDoubleClick)
						//		m_fOnNonClientMiddleMouseButtonDoubleClick(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_INITDIALOG:
						//	return OnInitDialog && !m_fOnInitDialog(m_pCallbackParam) ? FALSE : TRUE;
						//case WM_SYSCOMMAND:
						//	if (OnSysCommand)
						//	{
						//		SYSTEM_COMMAND_TYPE type{ syscmdNone };
						//		switch (wParam)
						//		{
						//		case SC_CLOSE:
						//			type = syscmdClose;
						//			break;
						//		case SC_CONTEXTHELP:
						//			type = syscmdContextHelp;
						//			break;
						//		case SC_DEFAULT:
						//			type = syscmdDefault;
						//			break;
						//		case SC_HOTKEY:
						//			type = syscmdHotKey;
						//			break;
						//		case SC_HSCROLL:
						//			type = syscmdHScroll;
						//			break;
						//		case SCF_ISSECURE:
						//			type = syscmdIsSecure;
						//			break;
						//		case SC_KEYMENU:
						//			type = syscmdKeyMenu;
						//			break;
						//		case SC_MAXIMIZE:
						//			type = syscmdMaximize;
						//			break;
						//		case SC_MINIMIZE:
						//			type = syscmdMinimize;
						//			break;
						//		case SC_MONITORPOWER:
						//			type = syscmdMonitorPower;
						//			break;
						//		case SC_MOUSEMENU:
						//			type = syscmdMouseMenu;
						//			break;
						//		case SC_MOVE:
						//			type = syscmdMove;
						//			break;
						//		case SC_NEXTWINDOW:
						//			type = syscmdNextWindow;
						//			break;
						//		case SC_PREVWINDOW:
						//			type = syscmdPrevWindow;
						//			break;
						//		case SC_RESTORE:
						//			type = syscmdRestore;
						//			break;
						//		case SC_SCREENSAVE:
						//			type = syscmdScreenSave;
						//			break;
						//		case SC_SIZE:
						//			type = syscmdSize;
						//			break;
						//		case SC_TASKLIST:
						//			type = syscmdTaskList;
						//			break;
						//		case SC_VSCROLL:
						//			type = syscmdVScroll;
						//			break;
						//		}
						//		m_fOnSysCommand(type, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
						//	}
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_INITMENU:
						//	if (OnInitMenu)
						//		m_fOnInitMenu((HMENU)wParam, m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_INITMENUPOPUP:
						//	if (OnInitMenuPopup)
						//		m_fOnInitMenuPopup((HMENU)wParam, LOWORD(lParam), HIWORD(lParam) ? true : false, m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_MENUSELECT:
						//	if (HIWORD(wParam) == 0xFFFF && !lParam)
						//	{
						//		if (OnMenuClose)
						//			OnMenuClose(m_pCallbackParam);
						//	}
						//	else
						//		if (OnMenuSelect)
						//			OnMenuSelect(LOWORD(wParam), HIWORD(wParam), (HMENU)lParam, m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_ENTERIDLE:
						//	if (wParam == MSGF_DIALOGBOX)
						//	{
						//		if (OnEnterIdleDialog)
						//			OnEnterIdleDialog(m_pCallbackParam);
						//	}
						//	else if (wParam == MSGF_MENU)
						//	{
						//		if (OnEnterIdleMenu)
						//			OnEnterIdleMenu(m_pCallbackParam);
						//	}
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_MENURBUTTONUP:
						//	if (OnMenuRightMouseButtonUp)
						//		OnMenuRightMouseButtonUp(wParam, (HMENU)lParam, m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_MENUDRAG:
						//{
						//	LRESULT result = 2;
						//	if (OnMenuDrag)
						//		OnMenuDrag(wParam, (HMENU)lParam, result, m_pCallbackParam);
						//	if (result == MND_CONTINUE || result == MND_ENDMENU)
						//		return result;
						//}
						//return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_UNINITMENUPOPUP:
						//	if (OnUninitMenuPopup)
						//		OnUninitMenuPopup((HMENU)wParam, m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_MENUCOMMAND:
						//	if (OnMenuCommand)
						//		OnMenuCommand(wParam, (HMENU)lParam, m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_ENTERMENULOOP:
						//	if (OnEnterMenuLoop)
						//		OnEnterMenuLoop(wParam ? true : false, m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_EXITMENULOOP:
						//	if (OnExitMenuLoop)
						//		OnExitMenuLoop(wParam ? true : false, m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_NEXTMENU:
						//	if (OnNextMenu && OnNextMenu(wParam, (MDINEXTMENU*)lParam, m_pCallbackParam))
						//		return 0;
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_NCMOUSEHOVER:
						//	if (OnNonClientMouseHover)
						//		OnNonClientMouseHover(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_NCMOUSELEAVE:
						//	if (OnNonClientMouseLeave)
						//		OnNonClientMouseLeave(m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_HOTKEY:
						//	if (OnHotKey)
						//		OnHotKey(wParam == IDHOT_SNAPDESKTOP, VirtualToKey(HIWORD(lParam)), (LOWORD(lParam) & MOD_ALT) ? true : false, (LOWORD(lParam) & MOD_CONTROL) ? true : false, (LOWORD(lParam) & MOD_SHIFT) ? true : false, (LOWORD(lParam) & MOD_WIN) ? true : false, m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_PRINT:
						//	if (OnPrint)
						//		OnPrint((HDC)wParam, lParam, m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_PRINTCLIENT:
						//	if (OnPrintClient)
						//		OnPrintClient((HDC)wParam, lParam, m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
						//case WM_COPYDATA:
						//	if (OnCopyData)
						//		OnCopyData((HWND)wParam, (COPYDATASTRUCT*)lParam, m_pCallbackParam);
						//	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
					}
					if (*reinterpret_cast<HWND*>(&window->m_hHandle) && window->m_pListener)
					{
						long long result{ 0 };
						if (window->m_pListener->OnMessage((unsigned long)uMsg, (unsigned long long)wParam, (long long)lParam, result))
							return (LRESULT)result;
					}
					return DefWindowProcW(hWnd, uMsg, wParam, lParam);
				}
			};
		#pragma endregion

		#pragma region Constructor and destructor
			CApplication::CApplication() :
				m_pPlatformData{ new PD_APPLICATION() },
				m_pService{ nullptr },
				m_cDialogs{ this },
				m_bWindowsSorted{ true },
				OnDestroyLastWindow{ nullptr }
			{
				if (Application)
					throw "Only one application instance should exist";
				Application = this;

				*reinterpret_cast<HINSTANCE*>(&m_hHandle) = GetCurrentModuleHandle();
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
				((PD_APPLICATION*)m_pPlatformData)->WindowClassRegister();
				m_cStyles.Add(new CDefaultStyle());
				ReceiveApplicationPath();
				ReceiveModulePath();
			}

			CApplication::~CApplication()
			{
				((PD_APPLICATION*)m_pPlatformData)->WindowClassUnregister();
				for (auto feature : m_aFeatures)
					feature->Release();
				if (m_pService)
					m_pService->Release();
				ngl::unload();
				Application = nullptr;
				delete (PD_APPLICATION*)m_pPlatformData;
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
					return m_aWindows[index].Window;
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

		#pragma region Window messages
			bool CApplication::ProcessMessage()
			{
				MSG msg;
				if (!PeekMessageW(&msg, 0, 0, 0, PM_NOREMOVE))
				{
					Sleep(1);
					return false;
				}
				bool exists = PeekMessageW(&msg, 0, 0, 0, PM_REMOVE) ? true : false;
				if (!exists)
					return false;
				if (msg.message != WM_QUIT)
				{
					TranslateMessage(&msg);
					DispatchMessageW(&msg);
				}
				else
				{
					m_bTerminated = true;
					((PD_APPLICATION*)m_pPlatformData)->m_iExitCode = msg.wParam;
				}
				return true;
			}

			void CApplication::ProcessMessages()
			{
				while (ProcessMessage());
			}
		#pragma endregion

		#pragma region Helpers
			CloseAction CApplication::getCloseAction(IWindow *window)
			{
				if (m_pMainForm)
					for (auto pos : m_aWindows)
						if (pos.Window == window)
						{
							if (pos.Form && pos.Form != m_pMainForm)
								return CloseAction::Hide;
							break;
						}
				return CloseAction::Free;
			}

			bool CApplication::hasTaskBar() const
			{
				return TaskBar != nullptr;
			}

			int CApplication::Run()
			{
				if (m_aWindows.size() == 0)
					return (int)((PD_APPLICATION*)m_pPlatformData)->m_iExitCode;
				m_bTerminated = false;
				do
				{
					if (!ProcessMessage())
						if (OnIdle)
							OnIdle();
				} while (!m_bTerminated);
				return (int)((PD_APPLICATION*)m_pPlatformData)->m_iExitCode;
			}

			void CApplication::RepaintAll()
			{
				for (auto pos : m_aWindows)
					if (pos.Form && pos.Form->isVisible())
						pos.Form->Repaint();
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
				wchar_t buffer[2048];
				DWORD length{ GetModuleFileNameW(NULL, buffer, 2048) };
				if (length > 0)
				{
					String name{ buffer };
					size_t pos{ name.find_last_of(L'\\') };
					if (pos != String::npos)
					{
						m_sApplicationDirectory = name.substr(0, pos + 1);
						m_sApplicationFileName = name.substr(pos + 1);
					}
				}
			}

			void CApplication::ReceiveModulePath()
			{
				wchar_t buffer[2048];
				DWORD length{ GetModuleFileNameW(*reinterpret_cast<HMODULE*>(&m_hHandle), buffer, 2048) };
				if (length > 0)
				{
					String name{ buffer };
					size_t pos{ name.find_last_of(L'\\') };
					if (pos != String::npos)
					{
						m_sModuleDirectory = name.substr(0, pos + 1);
						m_sModuleFileName = name.substr(pos + 1);
					}
				}
			}

			bool CApplication::SetProgressState(CWindow *window, const IWindow::ProgressType value)
			{
				if (*reinterpret_cast<HWND*>(&window->m_hHandle) && TaskBar)
				{
					TBPFLAG f;
					switch (value)
					{
					case IWindow::ProgressType::Indeterminate:
						f = TBPF_INDETERMINATE;
						break;
					case IWindow::ProgressType::Normal:
						f = TBPF_NORMAL;
						break;
					case IWindow::ProgressType::Paused:
						f = TBPF_PAUSED;
						break;
					case IWindow::ProgressType::Error:
						f = TBPF_ERROR;
						break;
					default:
						f = TBPF_NOPROGRESS;
					}
					return TaskBar->SetProgressState(*reinterpret_cast<HWND*>(&window->m_hHandle), f) == S_OK;
				}
				return false;
			}

			bool CApplication::SetProgressValue(CWindow *window, const float value)
			{
				if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsLessOrEqual<float>(value, 1) && *reinterpret_cast<HWND*>(&window->m_hHandle) && TaskBar)
					return TaskBar->SetProgressValue(*reinterpret_cast<HWND*>(&window->m_hHandle), ULONGLONG(1000 * value), 1000) == S_OK;
				return false;
			}

			ModalResult CApplication::ShowModal(CWindow *window)
			{
				window->m_eModalResult = ModalResult::None;
				if (*reinterpret_cast<HWND*>(&window->m_hHandle) && !window->m_bModal)
				{
					HWND old{ GetActiveWindow() };
					for (auto pos : m_aWindows)
						if (*reinterpret_cast<HWND*>(&pos.Handle) != *reinterpret_cast<HWND*>(&window->m_hHandle))
							window->m_aStates.push_back(CWindow::WINDOW_ENABLE{ pos.Handle, IsWindowEnabled(*reinterpret_cast<HWND*>(&pos.Handle)) ? true : false });
					// Disable all other enabled windows of application
					for (auto pos : window->m_aStates)
						if (pos.Enabled)
							EnableWindow(*reinterpret_cast<HWND*>(&pos.Handle), FALSE);
					ShowWindow(*reinterpret_cast<HWND*>(&window->m_hHandle), SW_SHOWNORMAL);
					EnableWindow(*reinterpret_cast<HWND*>(&window->m_hHandle), TRUE);
					SetActiveWindow(*reinterpret_cast<HWND*>(&window->m_hHandle));

					// Enter into modal loop
					window->m_bModal = true;
					while (window->m_bModal)
					{
						ProcessMessage();
						bool found{ false };
						for (auto pos : m_aWindows)
							if (*reinterpret_cast<HWND*>(&pos.Handle) == *reinterpret_cast<HWND*>(&window->m_hHandle))
							{
								found = true;
								break;
							}
						if (!found)
							return ModalResult::Close;
					}
					// Re-enable disabled window
					for (auto pos : window->m_aStates)
						if (pos.Enabled)
						{
							bool found{ false };
							for (auto w : m_aWindows)
								if (*reinterpret_cast<HWND*>(&w.Handle) == *reinterpret_cast<HWND*>(&pos.Handle))
								{
									found = true;
									break;
								}
							if (found)
								EnableWindow(*reinterpret_cast<HWND*>(&pos.Handle), TRUE);
						}
					// Close current window
					PostMessage(*reinterpret_cast<HWND*>(&window->m_hHandle), WM_CLOSE, 0, 0);
					// Re-activate previous active window
					if (old)
						for (auto w : m_aWindows)
							if (*reinterpret_cast<HWND*>(&w.Handle) == old)
							{
								SetActiveWindow(old);
								break;
							}
				}
				return window->m_eModalResult;
			}

			void CApplication::ExitModal(CWindow *window)
			{
				if (window->m_bModal)
				{
					for (auto pos : window->m_aStates)
						if (pos.Enabled)
						{
							bool found{ false };
							for (auto w : m_aWindows)
								if (*reinterpret_cast<HWND*>(&w.Handle) == *reinterpret_cast<HWND*>(&pos.Handle))
								{
									found = true;
									break;
								}
							if (found)
								EnableWindow(*reinterpret_cast<HWND*>(&pos.Handle), TRUE);
						}
					window->m_bModal = false;
				}
			}

			int CApplication::FindWindowIndex(const PlatformHandle handle)
			{
				SortWindows();
				m_sSearchWindow.Handle = handle;
				auto pos{ std::lower_bound(m_aWindows.begin(), m_aWindows.end(), m_sSearchWindow, [](const WINDOW &a, const WINDOW &b) {
					return *reinterpret_cast<const HWND*>(&a.Handle) < *reinterpret_cast<const HWND*>(&b.Handle); })
				};
				if (pos != m_aWindows.end() && *reinterpret_cast<const HWND*>(&pos->Handle) == *reinterpret_cast<const HWND*>(&handle))
					return int(pos - m_aWindows.begin());
				return -1;
			}

			void CApplication::SortWindows()
			{
				if (!m_bWindowsSorted)
				{
					std::sort(m_aWindows.begin(), m_aWindows.end(), [](const WINDOW &a, const WINDOW &b) {
						return *reinterpret_cast<const HWND*>(&a.Handle) < *reinterpret_cast<const HWND*>(&b.Handle);
					});
					m_bWindowsSorted = true;
				}
			}
		#pragma endregion
		}
	}
}
#endif