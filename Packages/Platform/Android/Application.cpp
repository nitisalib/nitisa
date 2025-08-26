// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef __ANDROID__
#include "../OpenGL/ngl.h"
#include "NativeApplication.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include <unistd.h>

#define pd ((PD_APPLICATION*)m_pPlatformData)

namespace nitisa
{
	IApplication *Application{ nullptr };

	namespace platform
	{
		namespace android
		{
			#include "../Data/DefaultFontData.inc"

			FT_Library FreeTypeLibrary{ nullptr };

		#pragma region Constructor & destructor
			CApplication::CApplication() :
				m_cScreen{ this },
				m_cPicture{ this },
				m_cFileSystem{ this },
				m_pService{ nullptr },
				m_iLastTimerId{ nullptr },
				m_pRenderer{ nullptr },
				OnSaveState{ nullptr },
				OnLowMemory{ nullptr }
			{
				if (Application)
					throw "Only one application instance should exists";
				Application = this;

				*reinterpret_cast<EGLDisplay*>(&m_hHandle) = nullptr;
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
				m_cStyles.Add(new CDefaultStyle());

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

				// FreeType
				FT_Init_FreeType(&FreeTypeLibrary);
			}

			CApplication::~CApplication()
			{
				CleanUp();
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

			void CApplication::CleanUp()
			{
				while (m_aWindows.size() > 0)
				{
					if (m_aWindows[0].Form)
						m_aWindows[0].Form->Release();
					m_aWindows[0].Window->Release();
				}
				for (auto feature : m_aFeatures)
					feature->Release();
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

			IApplicationService *CApplication::QueryService()
			{
				if (!m_pService)
					m_pService = new CApplicationService(this);
				return m_pService;
			}

			AConfiguration *CApplication::getConfiguration()
			{
				return NativeApplication::getConfiguration();
			}

			AAssetManager *CApplication::getAssetManager()
			{
				return NativeApplication::getAssetManager();
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

		#pragma region Helpers
			bool CApplication::ProcessMessage()
			{
				int events;
				void* source;
				if (ALooper_pollAll(10, nullptr, &events, &source) >= 0)
				{
					int id{ *((int*)source) };
					switch (id)
					{
					case liMain:
						ProcessMessageMain();
						break;
					case liInput:
						ProcessMessageInput();
						break;
					}

					return true;
				}
				return false;
			}

			void CApplication::ProcessMessageMain()
			{
				int8_t cmd{ NativeApplication::ReadCommand() };
				switch (cmd)
				{
				case acDestroy:
					CommandDestroy();
					break;
				case acStart:
					CommandStart();
					break;
				case acResume:
					CommandResume();
					break;
				case acPause:
					CommandPause();
					break;
				case acStop:
					CommandStop();
					break;
				case acConfigChanged:
					CommandConfigChanged();
					break;
				case acSetFocus:
					CommandSetFocus();
					break;
				case acKillFocus:
					CommandKillFocus();
					break;
				case acTerminate:
					CommandTerminate();
					break;
				case acInitialize:
					CommandInitialize();
					break;
				case acInputChanged:
					CommandInputChanged();
					break;
				case acResize:
					CommandResize();
					break;
				case acPaint:
					CommandPaint();
					break;
				case acRectChanged:
					CommandRectChanged();
					break;
				case acSaveState:
					CommandSaveState();
					break;
				case acLowMemory:
					CommandLowMemory();
					break;
				}
				NativeApplication::PostProcess(cmd);
			}

			void CApplication::ProcessMessageInput()
			{
				if (NativeApplication::getInputQueue())
				{
					AInputEvent * event {nullptr};
					while (AInputQueue_getEvent(NativeApplication::getInputQueue(), &event) >= 0)
					{
						if (AInputQueue_preDispatchEvent(NativeApplication::getInputQueue(), event))
							continue;
						AInputQueue_finishEvent(NativeApplication::getInputQueue(), event, ProcessInput(event) ? 1 : 0);
					}
				}
			}

			int CApplication::Run()
			{
				while (!NativeApplication::isTerminated())
				{
					if (!ProcessMessage() && OnIdle)
						OnIdle();
					ProcessTimers();
				};
				return 0;
			}

			void CApplication::ProcessMessages()
			{
				while (!NativeApplication::isTerminated() && ProcessMessage());
			}

			void CApplication::RepaintAll()
			{
				for (auto pos : m_aWindows)
					if (pos.Form && pos.Form->isVisible())
						pos.Form->Repaint();
			}

			void CApplication::ProcessTimers()
			{
				std::chrono::high_resolution_clock::time_point now{ std::chrono::high_resolution_clock::now() };
				for (auto &pos : m_aTimers)
				{
					std::chrono::microseconds duration{ std::chrono::duration_cast<std::chrono::microseconds>(now - pos.Last) };
					if (duration.count() / 1000000.0f >= pos.Interval)
					{
						pos.Listener->NotifyOnTimer(pos.Id);
						pos.Last = now;
					}
				}
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
				if (!getAssetManager())
					return nullptr;
				AAsset *asset{ AAssetManager_open(getAssetManager(), StringToAnsi(filename).c_str(), AASSET_MODE_BUFFER) };
				if (!asset)
					return nullptr;
				int size{ (int)AAsset_getLength(asset) };
				const void *data{ AAsset_getBuffer(asset) };
				if (data && size > 0)
				{
					FT_Face face;
					if (FT_New_Memory_Face(FreeTypeLibrary, (const FT_Byte*)data, size, 0, &face) == 0)
					{
						result = new FONT_FACE;
						result->Face = face;
						result->Name = filename;
						result->RefCount = 1;
						result->Default = false;
					}
				}
				AAsset_close(asset);
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

			Key CApplication::KeyCodeToKey(const int32_t code)
			{
				// TODO: Check and make more accurate
				switch (code)
				{
					//case AKEYCODE_SOFT_LEFT
					//case AKEYCODE_SOFT_RIGHT
				case AKEYCODE_HOME: return Key::Home;
					//case AKEYCODE_BACK
					//case AKEYCODE_CALL
					//case AKEYCODE_ENDCALL
				case AKEYCODE_0: return Key::Key0;
				case AKEYCODE_1: return Key::Key1;
				case AKEYCODE_2: return Key::Key2;
				case AKEYCODE_3: return Key::Key3;
				case AKEYCODE_4: return Key::Key4;
				case AKEYCODE_5: return Key::Key5;
				case AKEYCODE_6: return Key::Key6;
				case AKEYCODE_7: return Key::Key7;
				case AKEYCODE_8: return Key::Key8;
				case AKEYCODE_9: return Key::Key9;
				case AKEYCODE_STAR: return Key::Key8;
				case AKEYCODE_POUND: return Key::Key3;
					//case AKEYCODE_DPAD_UP
					//case AKEYCODE_DPAD_DOWN
					//case AKEYCODE_DPAD_LEFT
					//case AKEYCODE_DPAD_RIGHT
					//case AKEYCODE_DPAD_CENTER
				case AKEYCODE_VOLUME_UP: return Key::VolumeUp;
				case AKEYCODE_VOLUME_DOWN: return Key::VolumeDown;
					//case AKEYCODE_POWER
					//case AKEYCODE_CAMERA
				case AKEYCODE_CLEAR: return Key::Clear;
				case AKEYCODE_A: return Key::A;
				case AKEYCODE_B: return Key::B;
				case AKEYCODE_C: return Key::C;
				case AKEYCODE_D: return Key::D;
				case AKEYCODE_E: return Key::E;
				case AKEYCODE_F: return Key::F;
				case AKEYCODE_G: return Key::G;
				case AKEYCODE_H: return Key::H;
				case AKEYCODE_I: return Key::I;
				case AKEYCODE_J: return Key::J;
				case AKEYCODE_K: return Key::K;
				case AKEYCODE_L: return Key::L;
				case AKEYCODE_M: return Key::M;
				case AKEYCODE_N: return Key::N;
				case AKEYCODE_O: return Key::O;
				case AKEYCODE_P: return Key::P;
				case AKEYCODE_Q: return Key::Q;
				case AKEYCODE_R: return Key::R;
				case AKEYCODE_S: return Key::S;
				case AKEYCODE_T: return Key::T;
				case AKEYCODE_U: return Key::U;
				case AKEYCODE_V: return Key::V;
				case AKEYCODE_W: return Key::W;
				case AKEYCODE_X: return Key::X;
				case AKEYCODE_Y: return Key::Y;
				case AKEYCODE_Z: return Key::Z;
				case AKEYCODE_COMMA: return Key::OemComma;
				case AKEYCODE_PERIOD: return Key::Decimal;
				case AKEYCODE_ALT_LEFT: return Key::LMenu;
				case AKEYCODE_ALT_RIGHT: return Key::RMenu;
				case AKEYCODE_SHIFT_LEFT: return Key::LShift;
				case AKEYCODE_SHIFT_RIGHT: return Key::RShift;
				case AKEYCODE_TAB: return Key::Tab;
				case AKEYCODE_SPACE: return Key::Space;
					//case AKEYCODE_SYM
					//case AKEYCODE_EXPLORER
					//case AKEYCODE_ENVELOPE
				case AKEYCODE_ENTER: return Key::Return;
				case AKEYCODE_DEL: return Key::Backspace;
				case AKEYCODE_GRAVE: return Key::Tilde;
				case AKEYCODE_MINUS: return Key::Subtract;
				case AKEYCODE_EQUALS: return Key::Add;
				case AKEYCODE_LEFT_BRACKET: return Key::LeftBracket;
				case AKEYCODE_RIGHT_BRACKET: return Key::RightBracket;
				case AKEYCODE_BACKSLASH: return Key::BackSlash;
				case AKEYCODE_SEMICOLON: return Key::Semicolon;
				case AKEYCODE_APOSTROPHE: return Key::Apostrophe;
				case AKEYCODE_SLASH: return Key::Slash;
				case AKEYCODE_AT: return Key::Key2;
					//case AKEYCODE_NUM
					//case AKEYCODE_HEADSETHOOK
					//case AKEYCODE_FOCUS
				case AKEYCODE_PLUS: return Key::OemPlus;
				case AKEYCODE_MENU: return Key::Menu;
					//case AKEYCODE_NOTIFICATION
					//case AKEYCODE_SEARCH
				case AKEYCODE_MEDIA_PLAY_PAUSE: return Key::MediaPlayPause;
				case AKEYCODE_MEDIA_STOP: return Key::MediaStop;
				case AKEYCODE_MEDIA_NEXT: return Key::MediaNextTrack;
				case AKEYCODE_MEDIA_PREVIOUS: return Key::MediaPrevTrack;
					//case AKEYCODE_MEDIA_REWIND
					//case AKEYCODE_MEDIA_FAST_FORWARD
					//case AKEYCODE_MUTE
				case AKEYCODE_PAGE_UP: return Key::Prior;
				case AKEYCODE_PAGE_DOWN: return Key::Next;
					//case AKEYCODE_PICTSYMBOLS
					//case AKEYCODE_SWITCH_CHARSET
					//case AKEYCODE_BUTTON_A
					//case AKEYCODE_BUTTON_B
					//case AKEYCODE_BUTTON_C
					//case AKEYCODE_BUTTON_X
					//case AKEYCODE_BUTTON_Y
					//case AKEYCODE_BUTTON_Z
					//case AKEYCODE_BUTTON_L1
					//case AKEYCODE_BUTTON_R1
					//case AKEYCODE_BUTTON_L2
					//case AKEYCODE_BUTTON_R2
					//case AKEYCODE_BUTTON_THUMBL
					//case AKEYCODE_BUTTON_THUMBR
					//case AKEYCODE_BUTTON_START
					//case AKEYCODE_BUTTON_SELECT
					//case AKEYCODE_BUTTON_MODE
				case AKEYCODE_ESCAPE: return Key::Escape;
					//case AKEYCODE_FORWARD_DEL
				case AKEYCODE_CTRL_LEFT: return Key::LControl;
				case AKEYCODE_CTRL_RIGHT: return Key::RControl;
				case AKEYCODE_CAPS_LOCK: return Key::CapsLock;
				case AKEYCODE_SCROLL_LOCK: return Key::ScrollLock;
					//case AKEYCODE_META_LEFT
					//case AKEYCODE_META_RIGHT
					//case AKEYCODE_FUNCTION
					//case AKEYCODE_SYSRQ
				case AKEYCODE_BREAK: return Key::Pause;
					//case AKEYCODE_MOVE_HOME
					//case AKEYCODE_MOVE_END
				case AKEYCODE_INSERT: return Key::Insert;
					//case AKEYCODE_FORWARD
					//case AKEYCODE_MEDIA_PLAY
					//case AKEYCODE_MEDIA_PAUSE
					//case AKEYCODE_MEDIA_CLOSE
					//case AKEYCODE_MEDIA_EJECT
					//case AKEYCODE_MEDIA_RECORD
				case AKEYCODE_F1: return Key::F1;
				case AKEYCODE_F2: return Key::F2;
				case AKEYCODE_F3: return Key::F3;
				case AKEYCODE_F4: return Key::F4;
				case AKEYCODE_F5: return Key::F5;
				case AKEYCODE_F6: return Key::F6;
				case AKEYCODE_F7: return Key::F7;
				case AKEYCODE_F8: return Key::F8;
				case AKEYCODE_F9: return Key::F9;
				case AKEYCODE_F10: return Key::F10;
				case AKEYCODE_F11: return Key::F11;
				case AKEYCODE_F12: return Key::F12;
				case AKEYCODE_NUM_LOCK: return Key::NumLock;
				case AKEYCODE_NUMPAD_0: return Key::Numpad0;
				case AKEYCODE_NUMPAD_1: return Key::Numpad1;
				case AKEYCODE_NUMPAD_2: return Key::Numpad2;
				case AKEYCODE_NUMPAD_3: return Key::Numpad3;
				case AKEYCODE_NUMPAD_4: return Key::Numpad4;
				case AKEYCODE_NUMPAD_5: return Key::Numpad5;
				case AKEYCODE_NUMPAD_6: return Key::Numpad6;
				case AKEYCODE_NUMPAD_7: return Key::Numpad7;
				case AKEYCODE_NUMPAD_8: return Key::Numpad8;
				case AKEYCODE_NUMPAD_9: return Key::Numpad9;
				case AKEYCODE_NUMPAD_DIVIDE: return Key::Divide;
				case AKEYCODE_NUMPAD_MULTIPLY: return Key::Multiply;
				case AKEYCODE_NUMPAD_SUBTRACT: return Key::Subtract;
				case AKEYCODE_NUMPAD_ADD: return Key::Add;
				case AKEYCODE_NUMPAD_DOT: return Key::Decimal;
				case AKEYCODE_NUMPAD_COMMA: return Key::Decimal;
				case AKEYCODE_NUMPAD_ENTER: return Key::Separator;
				case AKEYCODE_NUMPAD_EQUALS: return Key::Separator;
					//case AKEYCODE_NUMPAD_LEFT_PAREN
					//case AKEYCODE_NUMPAD_RIGHT_PAREN
				case AKEYCODE_VOLUME_MUTE: return Key::VolumeMute;
					//case AKEYCODE_INFO
					//case AKEYCODE_CHANNEL_UP
					//case AKEYCODE_CHANNEL_DOWN
					//case AKEYCODE_ZOOM_IN
					//case AKEYCODE_ZOOM_OUT
					//case AKEYCODE_TV
					//case AKEYCODE_WINDOW
					//case AKEYCODE_GUIDE
					//case AKEYCODE_DVR
					//case AKEYCODE_BOOKMARK
					//case AKEYCODE_CAPTIONS
					//case AKEYCODE_SETTINGS
					//case AKEYCODE_TV_POWER
					//case AKEYCODE_TV_INPUT
					//case AKEYCODE_STB_POWER
					//case AKEYCODE_STB_INPUT
					//case AKEYCODE_AVR_POWER
					//case AKEYCODE_AVR_INPUT
					//case AKEYCODE_PROG_RED
					//case AKEYCODE_PROG_GREEN
					//case AKEYCODE_PROG_YELLOW
					//case AKEYCODE_PROG_BLUE
					//case AKEYCODE_APP_SWITCH
					//case AKEYCODE_BUTTON_1
					//case AKEYCODE_BUTTON_2
					//case AKEYCODE_BUTTON_3
					//case AKEYCODE_BUTTON_4
					//case AKEYCODE_BUTTON_5
					//case AKEYCODE_BUTTON_6
					//case AKEYCODE_BUTTON_7
					//case AKEYCODE_BUTTON_8
					//case AKEYCODE_BUTTON_9
					//case AKEYCODE_BUTTON_10
					//case AKEYCODE_BUTTON_11
					//case AKEYCODE_BUTTON_12
					//case AKEYCODE_BUTTON_13
					//case AKEYCODE_BUTTON_14
					//case AKEYCODE_BUTTON_15
					//case AKEYCODE_BUTTON_16
					//case AKEYCODE_LANGUAGE_SWITCH
					//case AKEYCODE_MANNER_MODE
					//case AKEYCODE_3D_MODE
					//case AKEYCODE_CONTACTS
					//case AKEYCODE_CALENDAR
					//case AKEYCODE_MUSIC
					//case AKEYCODE_CALCULATOR
					//case AKEYCODE_ZENKAKU_HANKAKU
					//case AKEYCODE_EISU
					//case AKEYCODE_MUHENKAN
					//case AKEYCODE_HENKAN
					//case AKEYCODE_KATAKANA_HIRAGANA
					//case AKEYCODE_YEN
					//case AKEYCODE_RO
				case AKEYCODE_KANA: return Key::Kana;
					//case AKEYCODE_ASSIST
					//case AKEYCODE_BRIGHTNESS_DOWN
					//case AKEYCODE_BRIGHTNESS_UP
					//case AKEYCODE_MEDIA_AUDIO_TRACK
				case AKEYCODE_SLEEP: return Key::Sleep;
					//case AKEYCODE_WAKEUP
					//case AKEYCODE_PAIRING
					//case AKEYCODE_MEDIA_TOP_MENU
					//case AKEYCODE_11
					//case AKEYCODE_12
					//case AKEYCODE_LAST_CHANNEL
					//case AKEYCODE_TV_DATA_SERVICE
					//case AKEYCODE_VOICE_ASSIST
					//case AKEYCODE_TV_RADIO_SERVICE
					//case AKEYCODE_TV_TELETEXT
					//case AKEYCODE_TV_NUMBER_ENTRY
					//case AKEYCODE_TV_TERRESTRIAL_ANALOG
					//case AKEYCODE_TV_TERRESTRIAL_DIGITAL
					//case AKEYCODE_TV_SATELLITE
					//case AKEYCODE_TV_SATELLITE_BS
					//case AKEYCODE_TV_SATELLITE_CS
					//case AKEYCODE_TV_SATELLITE_SERVICE
					//case AKEYCODE_TV_NETWORK
					//case AKEYCODE_TV_ANTENNA_CABLE
					//case AKEYCODE_TV_INPUT_HDMI_1
					//case AKEYCODE_TV_INPUT_HDMI_2
					//case AKEYCODE_TV_INPUT_HDMI_3
					//case AKEYCODE_TV_INPUT_HDMI_4
					//case AKEYCODE_TV_INPUT_COMPOSITE_1
					//case AKEYCODE_TV_INPUT_COMPOSITE_2
					//case AKEYCODE_TV_INPUT_COMPONENT_1
					//case AKEYCODE_TV_INPUT_COMPONENT_2
					//case AKEYCODE_TV_INPUT_VGA_1
					//case AKEYCODE_TV_AUDIO_DESCRIPTION
					//case AKEYCODE_TV_AUDIO_DESCRIPTION_MIX_UP
					//case AKEYCODE_TV_AUDIO_DESCRIPTION_MIX_DOWN
					//case AKEYCODE_TV_ZOOM_MODE
					//case AKEYCODE_TV_CONTENTS_MENU
					//case AKEYCODE_TV_MEDIA_CONTEXT_MENU
					//case AKEYCODE_TV_TIMER_PROGRAMMING
					//case AKEYCODE_HELP
				default:
					return Key::Unknown;
				}
			}
		#pragma endregion

		#pragma region Native activity changes
			void CApplication::CommandInitialize()
			{
				// Get display
				if (!(*reinterpret_cast<EGLDisplay*>(&m_hHandle) = eglGetDisplay(EGL_DEFAULT_DISPLAY)))
					return;
				//eglQuerySurface(pd->m_pEGLDisplay, pd->m_pEGLSurface, EGL_WIDTH, &w);
				//eglQuerySurface(pd->m_pEGLDisplay, pd->m_pEGLSurface, EGL_HEIGHT, &h);
				//m_iEGLSurfaceWidth = w;
				//m_iEGLSurfaceHeight = h;

				//glFrontFace(GL_CW);
				//glCullFace(GL_BACK);
				//glEnable(GL_CULL_FACE);
				//glEnable(GL_BLEND);
				//glDisable(GL_DEPTH_TEST);
				//glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);

				android_main();
			}

			void CApplication::CommandTerminate()
			{
				CleanUp();
			}

			void CApplication::CommandResize()
			{
				IWindow *window{ m_pMainForm ? m_pMainForm->QueryService()->getWindow() : (m_aWindows.size() > 0 ? m_aWindows[0].Window : nullptr) };
				if (window && window->QueryService()->getListener())
				{
					MessageWindowResizing m{ Rect{ 0, 0, ANativeWindow_getWidth(NativeApplication::getWindow()), ANativeWindow_getHeight(NativeApplication::getWindow()) }, EdgeType::None };
					window->QueryService()->getListener()->OnResizing(m);
				}
			}

			void CApplication::CommandPaint()
			{
				IWindow *window{ m_pMainForm ? m_pMainForm->QueryService()->getWindow() : (m_aWindows.size() > 0 ? m_aWindows[0].Window : nullptr) };
				if (window && window->QueryService()->getListener())
				{
					MessageRect m{ RectF{ 0, 0, (float)ANativeWindow_getWidth(NativeApplication::getWindow()), (float)ANativeWindow_getHeight(NativeApplication::getWindow()) } };
					window->QueryService()->getListener()->OnPaint(m);
				}
			}

			void CApplication::CommandSetFocus()
			{
				IWindow *window{ m_pMainForm ? m_pMainForm->QueryService()->getWindow() : (m_aWindows.size() > 0 ? m_aWindows[0].Window : nullptr) };
				if (window && window->QueryService()->getListener())
					window->QueryService()->getListener()->OnSetFocus();
			}

			void CApplication::CommandKillFocus()
			{
				IWindow *window{ m_pMainForm ? m_pMainForm->QueryService()->getWindow() : (m_aWindows.size() > 0 ? m_aWindows[0].Window : nullptr) };
				if (window && window->QueryService()->getListener())
					window->QueryService()->getListener()->OnKillFocus();
			}

			void CApplication::CommandResume()
			{
				IWindow *window{ m_pMainForm ? m_pMainForm->QueryService()->getWindow() : (m_aWindows.size() > 0 ? m_aWindows[0].Window : nullptr) };
				if (window && window->QueryService()->getListener())
				{
					MessageWindowActivate m{ false };
					window->QueryService()->getListener()->OnActivateApp();
					window->QueryService()->getListener()->OnActivate(m);
					window->QueryService()->getListener()->OnShow();
				}
			}

			void CApplication::CommandPause()
			{
				IWindow *window{ m_pMainForm ? m_pMainForm->QueryService()->getWindow() : (m_aWindows.size() > 0 ? m_aWindows[0].Window : nullptr) };
				if (window && window->QueryService()->getListener())
				{
					window->QueryService()->getListener()->OnHide();
					window->QueryService()->getListener()->OnDeactivate();
					window->QueryService()->getListener()->OnDeactivateApp();
				}
			}

			void CApplication::CommandConfigChanged()
			{
				IWindow *window{ m_pMainForm ? m_pMainForm->QueryService()->getWindow() : (m_aWindows.size() > 0 ? m_aWindows[0].Window : nullptr) };
				if (window && window->QueryService()->getListener())
					window->QueryService()->getListener()->OnDeviceModeChange();
			}

			void CApplication::CommandDestroy()
			{
				// Not required
			}

			void CApplication::CommandStart()
			{
				// Not required
			}

			void CApplication::CommandStop()
			{
				// Not required
			}

			void CApplication::CommandRectChanged()
			{
				// Not required
			}

			void CApplication::CommandInputChanged()
			{
				// Not required
			}

			void CApplication::CommandSaveState()
			{
				if (OnSaveState)
					OnSaveState(this);
			}

			void CApplication::CommandLowMemory()
			{
				if (OnLowMemory)
					OnLowMemory(this);
			}
		#pragma endregion

		#pragma region Process input
			bool CApplication::ProcessInput(AInputEvent *e)
			{
				IWindow *window{ m_pMainForm ? m_pMainForm->QueryService()->getWindow() : (m_aWindows.size() > 0 ? m_aWindows[0].Window : nullptr) };
				if (window && window->QueryService()->getListener())
				{
					IWindowListener *listener{ window->QueryService()->getListener() };
					switch (AInputEvent_getType(e))
					{
					case AINPUT_EVENT_TYPE_KEY:
						return ProcessInputKey(e, listener);
					case AINPUT_EVENT_TYPE_MOTION:
						return ProcessInputMotion(e, listener);
					}
				}
				return false;
			}

			bool CApplication::ProcessInputKey(AInputEvent *e, IWindowListener *listener)
			{
				bool is_down{ false };
				switch (AKeyEvent_getAction(e))
				{
				case AKEY_EVENT_ACTION_DOWN:
					is_down = true;
					break;
				case AKEY_EVENT_ACTION_UP:
					break;
				default: // TODO: process AKEY_EVENT_ACTION_MULTIPLE type as well
					return false;
				}
				int32_t code{ AKeyEvent_getKeyCode(e) };
				MESSAGE_KEY_ANDROID m;
				m.Key = KeyCodeToKey(code);
				m.KeyCode = code;
				m.Target = nullptr;
				int32_t meta_state{ AKeyEvent_getMetaState(e) };
				m_cKeyboard.m_bAlt = meta_state & AMETA_ALT_ON;
				m_cKeyboard.m_bShift = meta_state & AMETA_SHIFT_ON;
				m_cKeyboard.m_bCtrl = meta_state & AMETA_CTRL_ON;
				m_cKeyboard.m_bCapsLock = meta_state & AMETA_CAPS_LOCK_ON;
				m_cKeyboard.m_bScrollLock = meta_state & AMETA_SCROLL_LOCK_ON;
				m_cKeyboard.m_bNumLock = meta_state & AMETA_NUM_LOCK_ON;
				is_down ? listener->OnKeyDown(m) : listener->OnKeyUp(m);
				return true;
			}

			bool CApplication::ProcessInputMotion(AInputEvent *e, IWindowListener *listener)
			{
				if (AMotionEvent_getPointerCount(e) > 1)
					return false;
				int32_t action{ AMotionEvent_getAction(e) };
				uint32_t flags{ uint32_t(action & AMOTION_EVENT_ACTION_MASK) };
				uint32_t pointer{ uint32_t((action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT) };
				int32_t meta_state{ AMotionEvent_getMetaState(e) };
				m_cKeyboard.m_bAlt = meta_state & AMETA_ALT_ON;
				m_cKeyboard.m_bShift = meta_state & AMETA_SHIFT_ON;
				m_cKeyboard.m_bCtrl = meta_state & AMETA_CTRL_ON;
				m_cKeyboard.m_bCapsLock = meta_state & AMETA_CAPS_LOCK_ON;
				m_cKeyboard.m_bScrollLock = meta_state & AMETA_SCROLL_LOCK_ON;
				m_cKeyboard.m_bNumLock = meta_state & AMETA_NUM_LOCK_ON;
				Point p{ (int)AMotionEvent_getX(e, 0), (int)AMotionEvent_getY(e, 0) };
				if (p != m_cMouse.m_sPosition)
				{
					m_cMouse.m_sPosition = p;
					listener->OnMouseMove(MessageMouse{ (PointF)m_cMouse.m_sPosition, m_cKeyboard.m_bCtrl, m_cKeyboard.m_bAlt, m_cKeyboard.m_bShift,
						flags == AMOTION_EVENT_ACTION_MOVE || flags == AMOTION_EVENT_ACTION_DOWN || flags == AMOTION_EVENT_ACTION_UP || flags == AMOTION_EVENT_ACTION_CANCEL,
						false,
						flags == AMOTION_EVENT_ACTION_POINTER_DOWN || flags == AMOTION_EVENT_ACTION_POINTER_UP,
						nullptr });
				}
				// TODO: probably separate events by source(mouse, touchscreen,...)
				switch (flags)
				{
				case AMOTION_EVENT_ACTION_DOWN:
					listener->OnLeftMouseButtonDown(MessageMouse{ (PointF)m_cMouse.m_sPosition, m_cKeyboard.m_bCtrl, m_cKeyboard.m_bAlt, m_cKeyboard.m_bShift, true, false, false, nullptr });
					return true;
				case AMOTION_EVENT_ACTION_CANCEL:
				case AMOTION_EVENT_ACTION_UP:
					listener->OnLeftMouseButtonUp(MessageMouse{ (PointF)m_cMouse.m_sPosition, m_cKeyboard.m_bCtrl, m_cKeyboard.m_bAlt, m_cKeyboard.m_bShift, true, false, false, nullptr });
					return true;
				case AMOTION_EVENT_ACTION_POINTER_DOWN:
					listener->OnRightMouseButtonDown(MessageMouse{ PointF{ AMotionEvent_getX(e, pointer), AMotionEvent_getY(e, pointer) }, m_cKeyboard.m_bCtrl, m_cKeyboard.m_bAlt,
						m_cKeyboard.m_bShift, false, false, true, nullptr });
					return true;
				case AMOTION_EVENT_ACTION_POINTER_UP:
					listener->OnRightMouseButtonUp(MessageMouse{ PointF{ AMotionEvent_getX(e, pointer), AMotionEvent_getY(e, pointer) }, m_cKeyboard.m_bCtrl, m_cKeyboard.m_bAlt,
						m_cKeyboard.m_bShift, false, false, true, nullptr });
					return true;
				default:
					return false;
				}
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
		#pragma endregion
		}
	}
}
#endif