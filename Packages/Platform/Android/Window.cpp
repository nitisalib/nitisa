// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef __ANDROID__
#include "NativeApplication.h"

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
		#pragma region Constructor & destructor
			CWindow::CWindow() :
				m_pListener{ nullptr },
				m_pService{ nullptr },
				m_pApplication{ cast<CApplication*>(Application) },
				m_bCreated{ false },
				m_iID{ 1 }
			{
				m_sCreateParams.HasCaption = false;
				m_sCreateParams.HasMaximizeBox = false;
				m_sCreateParams.HasMinimizeBox = false;
				m_sCreateParams.HasSizeBox = false;
				m_sCreateParams.HasSystemMenu = false;
				m_sCreateParams.HasClientEdge = false;
				m_sCreateParams.HasWindowEdge = false;
				m_sCreateParams.Position = { 0, 0 };
				m_sCreateParams.Size = Point{ 0, 0 };
				m_sCreateParams.Caption = L"";
				m_pApplication->m_aWindows.push_back({ this, nullptr, true });
			}

			CWindow::~CWindow()
			{
				if (m_pListener)
					m_pListener->OnDestroy();
				for (auto pos = m_pApplication->m_aWindows.begin(); pos != m_pApplication->m_aWindows.end(); pos++)
					if (pos->Window == this)
					{
						m_pApplication->m_aWindows.erase(pos);
						break;
					}
				if (m_pService)
					m_pService->Release();
			}

			void CWindow::Release()
			{
				delete this;
			}
		#pragma endregion

		#pragma region Getters
			bool CWindow::isCreated()
			{
				return true;
			}

			bool CWindow::isVisible()
			{
				return NativeApplication::getActivityState() == asResume; // If activity is foreground one
			}

			bool CWindow::isEnabled()
			{
				return NativeApplication::getActivityState() == asResume; // If activity is foreground one
			}

			bool CWindow::isAcceptDragAndDrop()
			{
				return false; // Not supported
			}

			bool CWindow::isAcceptDropFiles()
			{
				return false; // Not supported
			}

			String CWindow::getCaption()
			{
				return L""; // Not supported
			}

			Rect CWindow::getRect()
			{
				if (NativeApplication::getWindow())
					return Rect{ 0, 0, ANativeWindow_getWidth(NativeApplication::getWindow()), ANativeWindow_getHeight(NativeApplication::getWindow()) };
				return Rect{ 0, 0, 0, 0 };
			}

			Point CWindow::getSize()
			{
				if (NativeApplication::getWindow())
					return Point{ ANativeWindow_getWidth(NativeApplication::getWindow()), ANativeWindow_getHeight(NativeApplication::getWindow()) };
				return Point{ 0, 0 };
			}

			Point CWindow::getPosition()
			{
				return Point{ 0, 0 };
			}

			int CWindow::getLeft()
			{
				return 0;
			}

			int CWindow::getTop()
			{
				return 0;
			}

			int CWindow::getWidth()
			{
				if (NativeApplication::getWindow())
					return ANativeWindow_getWidth(NativeApplication::getWindow());
				return 0;
			}

			int CWindow::getHeight()
			{
				if (NativeApplication::getWindow())
					return ANativeWindow_getHeight(NativeApplication::getWindow());
				return 0;
			}

			Rect CWindow::getClientRect()
			{
				if (NativeApplication::getWindow())
					return Rect{ 0, 0, ANativeWindow_getWidth(NativeApplication::getWindow()), ANativeWindow_getHeight(NativeApplication::getWindow()) };
				return Rect{ 0, 0, 0, 0 };
			}

			Point CWindow::getClientSize()
			{
				if (NativeApplication::getWindow())
					return Point{ ANativeWindow_getWidth(NativeApplication::getWindow()), ANativeWindow_getHeight(NativeApplication::getWindow()) };
				return Point{ 0, 0 };
			}

			int CWindow::getClientWidth()
			{
				if (NativeApplication::getWindow())
					return ANativeWindow_getWidth(NativeApplication::getWindow());
				return 0;
			}

			int CWindow::getClientHeight()
			{
				if (NativeApplication::getWindow())
					return ANativeWindow_getHeight(NativeApplication::getWindow());
				return 0;
			}

			WindowState CWindow::getState()
			{
				return NativeApplication::getActivityState() == asResume ? WindowState::Normal : WindowState::Hidden; // Normal if activity is foreground one, otherwise is hidden
			}

			CreateParams CWindow::getCreateParams()
			{
				return m_sCreateParams;
			}

			IWindow *CWindow::getParent()
			{
				return nullptr; // Not supported
			}

			bool CWindow::hasProgressBar()
			{
				return false;
			}

			IWindowService *CWindow::QueryService()
			{
				if (!m_pService)
					m_pService = new CWindowService(this);
				return m_pService;
			}
		#pragma endregion

		#pragma region Setters
			bool CWindow::setVisible(const bool value)
			{
				return false; // Not supported
			}

			bool CWindow::setEnabled(const bool value)
			{
				return false; // Not supported
			}

			bool CWindow::setAcceptDrawAndDrop(const bool value)
			{
				return false; // Not supported
			}

			bool CWindow::setAcceptDropFiles(const bool value)
			{
				return false; // Not supported
			}

			bool CWindow::setCaption(const String &value)
			{
				return false; // Not supported
			}

			bool CWindow::setRect(const Rect &value)
			{
				return false; // Not supported
			}

			bool CWindow::setSize(const Point &value)
			{
				return false; // Not supported
			}

			bool CWindow::setPosition(const Point &value)
			{
				return false; // Not supported
			}

			bool CWindow::setLeft(const int value)
			{
				return false; // Not supported
			}

			bool CWindow::setTop(const int value)
			{
				return false; // Not supported
			}

			bool CWindow::setWidth(const int value)
			{
				return false; // Not supported
			}

			bool CWindow::setHeight(const int value)
			{
				return false; // Not supported
			}

			bool CWindow::setClientSize(const Point &value)
			{
				return false; // Not supported
			}

			bool CWindow::setCursor(const CursorType value)
			{
				return false; // Not supported
			}

			bool CWindow::setState(const WindowState value)
			{
				return false; // Not supported
			}

			bool CWindow::setCreateParams(const CreateParams &value)
			{
				m_sCreateParams = value;
				return true;
			}

			bool CWindow::setParent(IWindow *value)
			{
				return false; // Not supported
			}

			bool CWindow::setModalResult(const ModalResult value)
			{
				return false; // Not supported
			}

			bool CWindow::setWindowPosition(const WindowPosition value)
			{
				return false; // Not supported
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
			bool CWindow::Show()
			{
				return false; // Not supported
			}

			ModalResult CWindow::ShowModal()
			{
				return ModalResult::Cancel; // Not supported
			}

			bool CWindow::Hide()
			{
				return false; // Not supported
			}

			bool CWindow::Create()
			{
				if (!m_bCreated)
				{
					if (m_pListener)
						m_pListener->OnCreate();
					m_bCreated = true;
					return true;
				}
				return false;
			}

			bool CWindow::Create(IWindow *parent)
			{
				return Create();
			}

			bool CWindow::Create(const CreateParams &params)
			{
				return Create();
			}

			bool CWindow::Create(const CreateParams &params, IWindow *parent)
			{
				return Create();
			}

			PlatformHandle CWindow::CreateTimer(ITimerListener *listener, const float interval)
			{
				if (listener && interval > 0)
				{
					m_pApplication->m_aTimers.push_back(CApplication::TIMER{ listener, interval, m_pApplication->m_iLastTimerId, std::chrono::high_resolution_clock::now() });
					(*reinterpret_cast<int*>(&m_pApplication->m_iLastTimerId))++;
					return m_pApplication->m_aTimers[m_pApplication->m_aTimers.size() - 1].Id;
				}
				return nullptr;
			}

			bool CWindow::DeleteTimer(const PlatformHandle id)
			{
				for (auto pos = m_pApplication->m_aTimers.begin(); pos != m_pApplication->m_aTimers.end(); pos++)
					if (pos->Id == id)
					{
						m_pApplication->m_aTimers.erase(pos);
						return true;
					}
				return false;
			}

			void CWindow::DeleteTimers()
			{
				m_pApplication->m_aTimers.clear();
			}

			bool CWindow::ResetTimer(const PlatformHandle id, const float interval)
			{
				if (interval > 0)
					for (auto &pos : m_pApplication->m_aTimers)
						if (pos.Id == id)
						{
							pos.Interval = interval;
							pos.Last = std::chrono::high_resolution_clock::now();
							return true;
						}
				return false;
			}

			bool CWindow::CaptureMouse()
			{
				return true; // Not supported
			}

			void CWindow::ReleaseMouseCapture()
			{
				// Not supported
			}

			bool CWindow::Maximize()
			{
				return false; // Not supported
			}

			bool CWindow::Minimize()
			{
				return false; // Not supported
			}

			bool CWindow::Restore()
			{
				return false; // Not supported
			}

			bool CWindow::Close()
			{
				NativeApplication::Finish();
				return true;
			}

			int CWindow::GenerateID()
			{
				return m_iID++;
			}

			bool CWindow::CopyStringToClipboard(const String &str)
			{
				return false; // Not supported
			}

			bool CWindow::CopyStringFromClipboard()
			{
				return false; // Not supported
			}

			Rect CWindow::ScreenToClient(const Rect &rect)
			{
				return rect;
			}

			Point CWindow::ScreenToClient(const Point &pos)
			{
				return pos;
			}

			Rect CWindow::ClientToScreen(const Rect &rect)
			{
				return rect;
			}

			Point CWindow::ClientToScreen(const Point &pos)
			{
				return pos;
			}

			IWindow *CWindow::CreateInstance()
			{
				return new CWindow();
			}
		#pragma endregion
		}
	}
}
#endif