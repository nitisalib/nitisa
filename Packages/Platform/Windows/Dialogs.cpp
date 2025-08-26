// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <ShlObj.h>
#include <Commdlg.h>

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
		#pragma region Constructor & destructor
			CDialogs::CDialogs(CApplication *application) :
				m_pApplication{ application }
			{
				CoInitialize(nullptr);
			}

			CDialogs::~CDialogs()
			{
				CoUninitialize();
			}
		#pragma endregion

		#pragma region Helpers
			String CDialogs::ExtractPrintDeviceName(void *mode)
			{
				if (mode)
					return ((DEVMODE*)mode)->dmDeviceName;
				return L"";
			}

			bool CDialogs::ExtractPrintLandscape(void *mode)
			{
				if (mode && (((DEVMODE*)mode)->dmFields & DM_ORIENTATION))
					return ((DEVMODE*)mode)->dmOrientation == DMORIENT_LANDSCAPE;
				return false;
			}

			IDialogs::PrintPaperSize CDialogs::ExtractPrintPaperSize(void *mode)
			{
				if (mode && (((DEVMODE*)mode)->dmFields & DM_PAPERSIZE))
				{
					switch (((DEVMODE*)mode)->dmPaperSize)
					{
					case DMPAPER_LETTER:							return PrintPaperSize::Letter;
					case DMPAPER_LEGAL:								return PrintPaperSize::Legal;
					case DMPAPER_9X11:								return PrintPaperSize::Sheet9x11;
					case DMPAPER_10X11:								return PrintPaperSize::Sheet10x11;
					case DMPAPER_10X14:								return PrintPaperSize::Sheet10x14;
					case DMPAPER_15X11:								return PrintPaperSize::Sheet15x11;
					case DMPAPER_11X17:								return PrintPaperSize::Sheet11x17;
					case DMPAPER_12X11:								return PrintPaperSize::Sheet12x11;
					case DMPAPER_A2:								return PrintPaperSize::A2;
					case DMPAPER_A3:								return PrintPaperSize::A3;
					case DMPAPER_A3_EXTRA:							return PrintPaperSize::A3Extra;
					case DMPAPER_A3_ROTATED:						return PrintPaperSize::A3Rotated;
					case DMPAPER_A4:								return PrintPaperSize::A4;
					case DMPAPER_A4_EXTRA:							return PrintPaperSize::A4Extra;
					case DMPAPER_A4_PLUS:							return PrintPaperSize::A4Plus;
					case DMPAPER_A4_ROTATED:						return PrintPaperSize::A4Rotated;
					case DMPAPER_A4SMALL:							return PrintPaperSize::A4Small;
					case DMPAPER_A4_TRANSVERSE:						return PrintPaperSize::A4Transverse;
					case DMPAPER_A5:								return PrintPaperSize::A5;
					case DMPAPER_A5_EXTRA:							return PrintPaperSize::A5Extra;
					case DMPAPER_A5_ROTATED:						return PrintPaperSize::A5Rotated;
					case DMPAPER_A5_TRANSVERSE:						return PrintPaperSize::A5Transverse;
					case DMPAPER_A6:								return PrintPaperSize::A6;
					case DMPAPER_A6_ROTATED:						return PrintPaperSize::A6Rotated;
					case DMPAPER_A_PLUS:							return PrintPaperSize::APlus;
					case DMPAPER_B4:								return PrintPaperSize::B4;
					case DMPAPER_B4_JIS_ROTATED:					return PrintPaperSize::B4JisRotated;
					case DMPAPER_B5:								return PrintPaperSize::B5;
					case DMPAPER_B5_EXTRA:							return PrintPaperSize::B5Extra;
					case DMPAPER_B5_JIS_ROTATED:					return PrintPaperSize::B5JisRotated;
					case DMPAPER_B6_JIS:							return PrintPaperSize::B6Jis;
					case DMPAPER_B6_JIS_ROTATED:					return PrintPaperSize::B6JisRotated;
					case DMPAPER_B_PLUS:							return PrintPaperSize::BPlus;
					case DMPAPER_CSHEET:							return PrintPaperSize::CSheet;
					case DMPAPER_DBL_JAPANESE_POSTCARD:				return PrintPaperSize::DblJapanesePostcard;
					case DMPAPER_DBL_JAPANESE_POSTCARD_ROTATED:		return PrintPaperSize::DblJapanesePostcardRotated;
					case DMPAPER_DSHEET:							return PrintPaperSize::DSheet;
					case DMPAPER_ENV_9:								return PrintPaperSize::Env9;
					case DMPAPER_ENV_10:							return PrintPaperSize::Env10;
					case DMPAPER_ENV_11:							return PrintPaperSize::Env11;
					case DMPAPER_ENV_12:							return PrintPaperSize::Env12;
					case DMPAPER_ENV_14:							return PrintPaperSize::Env14;
					case DMPAPER_ENV_C5:							return PrintPaperSize::EnvC5;
					case DMPAPER_ENV_C3:							return PrintPaperSize::EnvC3;
					case DMPAPER_ENV_C4:							return PrintPaperSize::EnvC4;
					case DMPAPER_ENV_C6:							return PrintPaperSize::EnvC6;
					case DMPAPER_ENV_C65:							return PrintPaperSize::EnvC65;
					case DMPAPER_ENV_B4:							return PrintPaperSize::EnvB4;
					case DMPAPER_ENV_B5:							return PrintPaperSize::EnvB5;
					case DMPAPER_ENV_B6:							return PrintPaperSize::EnvB6;
					case DMPAPER_ENV_DL:							return PrintPaperSize::EnvDL;
					case DMPAPER_ENV_INVITE:						return PrintPaperSize::EnvInvite;
					case DMPAPER_ENV_ITALY:							return PrintPaperSize::EnvItaly;
					case DMPAPER_ENV_MONARCH:						return PrintPaperSize::EnvMonarch;
					case DMPAPER_ENV_PERSONAL:						return PrintPaperSize::EnvPersonal;
					case DMPAPER_ESHEET:							return PrintPaperSize::ESheet;
					case DMPAPER_EXECUTIVE:							return PrintPaperSize::Executive;
					case DMPAPER_FANFOLD_US:						return PrintPaperSize::FanfoldUS;
					case DMPAPER_FANFOLD_STD_GERMAN:				return PrintPaperSize::FanfoldStdGerman;
					case DMPAPER_FANFOLD_LGL_GERMAN:				return PrintPaperSize::FanfoldLglGerman;
					case DMPAPER_FOLIO:								return PrintPaperSize::Folio;
					case DMPAPER_ISO_B4:							return PrintPaperSize::ISOB4;
					case DMPAPER_JAPANESE_POSTCARD:					return PrintPaperSize::JapanesePostcard;
					case DMPAPER_JAPANESE_POSTCARD_ROTATED:			return PrintPaperSize::JapanesePostcardRotated;
					case DMPAPER_JENV_CHOU3:						return PrintPaperSize::JEnvChou3;
					case DMPAPER_JENV_CHOU3_ROTATED:				return PrintPaperSize::JEnvChou3Rotated;
					case DMPAPER_JENV_CHOU4:						return PrintPaperSize::JEnvChou4;
					case DMPAPER_JENV_CHOU4_ROTATED:				return PrintPaperSize::JEnvChou4Rotated;
					case DMPAPER_JENV_KAKU2:						return PrintPaperSize::JEnvKaku2;
					case DMPAPER_JENV_KAKU2_ROTATED:				return PrintPaperSize::JEnvKaku2Rotated;
					case DMPAPER_JENV_KAKU3:						return PrintPaperSize::JEnvKaku3;
					case DMPAPER_JENV_KAKU3_ROTATED:				return PrintPaperSize::JEnvKaku3Rotated;
					case DMPAPER_JENV_YOU4:							return PrintPaperSize::JEnvYou4;
					case DMPAPER_JENV_YOU4_ROTATED:					return PrintPaperSize::JEnvYou4Rotated;
					case DMPAPER_LEDGER:							return PrintPaperSize::Ledger;
					case DMPAPER_LEGAL_EXTRA:						return PrintPaperSize::LegalExtra;
					case DMPAPER_LETTER_EXTRA:						return PrintPaperSize::LetterExtra;
					case DMPAPER_LETTER_EXTRA_TRANSVERSE:			return PrintPaperSize::LetterExtraTransverse;
					case DMPAPER_LETTER_ROTATED:					return PrintPaperSize::LetterRotated;
					case DMPAPER_LETTERSMALL:						return PrintPaperSize::LetterSmall;
					case DMPAPER_LETTER_TRANSVERSE:					return PrintPaperSize::LetterTransverse;
					case DMPAPER_NOTE:								return PrintPaperSize::Note;
					case DMPAPER_P16K:								return PrintPaperSize::P16K;
					case DMPAPER_P16K_ROTATED:						return PrintPaperSize::P16KRotated;
					case DMPAPER_P32K:								return PrintPaperSize::P32K;
					case DMPAPER_P32K_ROTATED:						return PrintPaperSize::P32KRotated;
					case DMPAPER_P32KBIG:							return PrintPaperSize::P32KBig;
					case DMPAPER_P32KBIG_ROTATED:					return PrintPaperSize::P32KBigRotated;
					case DMPAPER_PENV_1:							return PrintPaperSize::Penv1;
					case DMPAPER_PENV_1_ROTATED:					return PrintPaperSize::Penv1Rotated;
					case DMPAPER_PENV_2:							return PrintPaperSize::Penv2;
					case DMPAPER_PENV_2_ROTATED:					return PrintPaperSize::Penv2Rotated;
					case DMPAPER_PENV_3:							return PrintPaperSize::Penv3;
					case DMPAPER_PENV_3_ROTATED:					return PrintPaperSize::Penv3Rotated;
					case DMPAPER_PENV_4:							return PrintPaperSize::Penv4;
					case DMPAPER_PENV_4_ROTATED:					return PrintPaperSize::Penv4Rotated;
					case DMPAPER_PENV_5:							return PrintPaperSize::Penv5;
					case DMPAPER_PENV_5_ROTATED:					return PrintPaperSize::Penv5Rotated;
					case DMPAPER_PENV_6:							return PrintPaperSize::Penv6;
					case DMPAPER_PENV_6_ROTATED:					return PrintPaperSize::Penv6Rotated;
					case DMPAPER_PENV_7:							return PrintPaperSize::Penv7;
					case DMPAPER_PENV_7_ROTATED:					return PrintPaperSize::Penv7Rotated;
					case DMPAPER_PENV_8:							return PrintPaperSize::Penv8;
					case DMPAPER_PENV_8_ROTATED:					return PrintPaperSize::Penv8Rotated;
					case DMPAPER_PENV_9:							return PrintPaperSize::Penv9;
					case DMPAPER_PENV_9_ROTATED:					return PrintPaperSize::Penv9Rotated;
					case DMPAPER_PENV_10:							return PrintPaperSize::Penv10;
					case DMPAPER_PENV_10_ROTATED:					return PrintPaperSize::Penv10Rotated;
					case DMPAPER_QUARTO:							return PrintPaperSize::Quarto;
					case DMPAPER_STATEMENT:							return PrintPaperSize::Statement;
					case DMPAPER_TABLOID:							return PrintPaperSize::Tabloid;
					case DMPAPER_TABLOID_EXTRA:						return PrintPaperSize::TabloidExtra;
					}
				}
				return PrintPaperSize::Unknown;
			}

			float CDialogs::ExtractPrintPaperLength(void *mode)
			{
				if (mode && (((DEVMODE*)mode)->dmFields & DM_PAPERLENGTH))
					return ((DEVMODE*)mode)->dmPaperLength * 0.1f;
				return 0;
			}

			float CDialogs::ExtractPrintPaperWidth(void *mode)
			{
				if (mode && (((DEVMODE*)mode)->dmFields & DM_PAPERWIDTH))
					return ((DEVMODE*)mode)->dmPaperWidth * 0.1f;
				return 0;
			}

			float CDialogs::ExtractPrintScale(void *mode)
			{
				if (mode && (((DEVMODE*)mode)->dmFields & DM_SCALE))
					return ((DEVMODE*)mode)->dmScale * 0.01f;
				return 1;
			}

			int CDialogs::ExtractPrintCopies(void *mode)
			{
				if (mode && (((DEVMODE*)mode)->dmFields & DM_COPIES))
					return ((DEVMODE*)mode)->dmCopies;
				return 1;
			}

			IDialogs::PrintPaperSource CDialogs::ExtractPrintPaperSource(void *mode)
			{
				if (mode && (((DEVMODE*)mode)->dmFields & DM_DEFAULTSOURCE))
				{
					switch (((DEVMODE*)mode)->dmDefaultSource)
					{
					case DMBIN_AUTO:			return PrintPaperSource::Auto;
					case DMBIN_CASSETTE:		return PrintPaperSource::Cassette;
					case DMBIN_ENVELOPE:		return PrintPaperSource::Envelope;
					case DMBIN_ENVMANUAL:		return PrintPaperSource::EnvManual;
					case DMBIN_FORMSOURCE:		return PrintPaperSource::FormSource;
					case DMBIN_LARGECAPACITY:	return PrintPaperSource::LargeCapacity;
					case DMBIN_LARGEFMT:		return PrintPaperSource::LargeFmt;
					case DMBIN_LOWER:			return PrintPaperSource::Lower;
					case DMBIN_MANUAL:			return PrintPaperSource::Manual;
					case DMBIN_MIDDLE:			return PrintPaperSource::Middle;
					case DMBIN_TRACTOR:			return PrintPaperSource::Tractor;
					case DMBIN_SMALLFMT:		return PrintPaperSource::SmallFmt;
					case DMBIN_UPPER:			return PrintPaperSource::Upper;
					}
				}
				return PrintPaperSource::Unknown;
			}

			IDialogs::PrintQuality CDialogs::ExtractPrintQuality(void *mode)
			{
				if (mode && (((DEVMODE*)mode)->dmFields & DM_PRINTQUALITY))
				{
					switch (((DEVMODE*)mode)->dmPrintQuality)
					{
					case DMRES_HIGH:	return PrintQuality::High;
					case DMRES_MEDIUM:	return PrintQuality::Medium;
					case DMRES_LOW:		return PrintQuality::Low;
					case DMRES_DRAFT:	return PrintQuality::Draft;
					}
				}
				return PrintQuality::Unknown;
			}

			bool CDialogs::ExtractPrintMonochrome(void *mode)
			{
				if (mode && (((DEVMODE*)mode)->dmFields & DM_COLOR))
					return ((DEVMODE*)mode)->dmColor == DMCOLOR_MONOCHROME;
				return false;
			}

			IDialogs::PrintDuplex CDialogs::ExtractPrintDuplex(void *mode)
			{
				if (mode && (((DEVMODE*)mode)->dmFields & DM_DUPLEX))
				{
					switch (((DEVMODE*)mode)->dmDuplex)
					{
					case DMDUP_SIMPLEX:		return PrintDuplex::Simplex;
					case DMDUP_HORIZONTAL:	return PrintDuplex::Horizontal;
					case DMDUP_VERTICAL:	return PrintDuplex::Vertical;
					}
				}
				return PrintDuplex::Unknown;
			}

			IDialogs::PrintTTOption CDialogs::ExtractPrintTTOption(void *mode)
			{
				if (mode && (((DEVMODE*)mode)->dmFields & DM_TTOPTION))
				{
					switch (((DEVMODE*)mode)->dmTTOption)
					{
					case DMTT_BITMAP:				return PrintTTOption::Bitmap;
					case DMTT_DOWNLOAD:				return PrintTTOption::Download;
					case DMTT_DOWNLOAD_OUTLINE:		return PrintTTOption::DownloadOutline;
					case DMTT_SUBDEV:				return PrintTTOption::Subdev;
					}
				}
				return PrintTTOption::Unknown;
			}

			bool CDialogs::ExtractPrintCollate(void *mode)
			{
				if (mode && (((DEVMODE*)mode)->dmFields & DM_COLLATE))
					return ((DEVMODE*)mode)->dmCollate == DMCOLLATE_FALSE;
				return false;
			}

			IDialogs::PrintMediaType CDialogs::ExtractPrintMediaType(void *mode)
			{
				if (mode && (((DEVMODE*)mode)->dmFields & DM_MEDIATYPE))
				{
					switch (((DEVMODE*)mode)->dmMediaType)
					{
					case DMMEDIA_STANDARD:		return PrintMediaType::Standard;
					case DMMEDIA_GLOSSY:		return PrintMediaType::Glossy;
					case DMMEDIA_TRANSPARENCY:	return PrintMediaType::Transparency;
					}
				}
				return PrintMediaType::Unknown;
			}

			IDialogs::PrintDitherType CDialogs::ExtractPrintDitherType(void *mode)
			{
				if (mode && (((DEVMODE*)mode)->dmFields & DM_DITHERTYPE))
				{
					switch (((DEVMODE*)mode)->dmDitherType)
					{
					case DMDITHER_NONE:			return PrintDitherType::None;
					case DMDITHER_COARSE:		return PrintDitherType::Coarse;
					case DMDITHER_FINE:			return PrintDitherType::Fine;
					case DMDITHER_LINEART:		return PrintDitherType::LineArt;
					case DMDITHER_GRAYSCALE:	return PrintDitherType::GrayScale;
					}
				}
				return PrintDitherType::Unknown;
			}
		#pragma endregion

		#pragma region Messages
			bool CDialogs::Message(const String &message, const String &caption)
			{
				MessageBox(GetActiveWindow(), message.c_str(), caption.c_str(), MB_OK);
				return true;
			}

			bool CDialogs::Warning(const String &message, const String &caption)
			{
				MessageBox(GetActiveWindow(), message.c_str(), caption.c_str(), MB_OK | MB_ICONWARNING);
				return true;
			}

			bool CDialogs::Information(const String &message, const String &caption)
			{
				MessageBox(GetActiveWindow(), message.c_str(), caption.c_str(), MB_OK | MB_ICONINFORMATION);
				return true;
			}

			bool CDialogs::Question(const String &message, const String &caption)
			{
				MessageBox(GetActiveWindow(), message.c_str(), caption.c_str(), MB_OK | MB_ICONQUESTION);
				return true;
			}

			bool CDialogs::Error(const String &message, const String &caption)
			{
				MessageBox(GetActiveWindow(), message.c_str(), caption.c_str(), MB_OK | MB_ICONERROR);
				return true;
			}

			ModalResult CDialogs::Confirm(const String &message, const String &caption)
			{
				switch (MessageBox(GetActiveWindow(), message.c_str(), caption.c_str(), MB_YESNOCANCEL | MB_ICONQUESTION))
				{
				case IDYES:	return ModalResult::Yes;
				case IDNO:	return ModalResult::No;
				}
				return ModalResult::Cancel;
			}
		#pragma endregion

		#pragma region Dialogs
			bool CDialogs::Open(const String &filter, const int filter_index, String &filename, const bool multiselect, const bool create_prompt, const bool must_exists, const bool show_hidden,
				const bool hide_readonly, const bool no_network)
			{
				wchar_t buffer[64000]{ 0 };
				String zero;
				zero.push_back(0);
				String f{ ReplaceAll(filter, L"|", zero) };
				ReplaceAllDirect(f, L"\n", zero);
				f += zero + zero;
				if (filename.length() > 0)
				{
					memcpy(buffer, filename.c_str(), filename.length() * sizeof(wchar_t));
					buffer[filename.length()] = 0;
				}
				OPENFILENAMEW s;
				ZeroMemory(&s, sizeof(OPENFILENAMEW));
				s.lStructSize = sizeof(OPENFILENAMEW);
				s.hwndOwner = GetActiveWindow();
				s.lpstrFilter = f.c_str();
				s.nFilterIndex = filter_index;
				s.lpstrFile = buffer;
				s.nMaxFile = 64000;
				if (multiselect)
					s.Flags |= OFN_ALLOWMULTISELECT | OFN_EXPLORER;
				if (create_prompt)
					s.Flags |= OFN_CREATEPROMPT;
				if (must_exists)
					s.Flags |= OFN_FILEMUSTEXIST;
				if (show_hidden)
					s.Flags |= OFN_FORCESHOWHIDDEN;
				if (hide_readonly)
					s.Flags |= OFN_HIDEREADONLY;
				if (no_network)
					s.Flags |= OFN_NONETWORKBUTTON;
				if (!GetOpenFileNameW(&s))
					return false;
				if (multiselect)
					for (int i = 0; i < 63999; i++)
						if (buffer[i] == 0)
						{
							if (buffer[i + 1] == 0)
								break;
							else
								buffer[i] = L'\n';
						}
				filename = buffer;
				return true;
			}

			bool CDialogs::Save(const String &filter, const int filter_index, String &filename, const String &default_extension, const bool create_prompt, const bool must_exists,
				const bool show_hidden, const bool hide_readonly, const bool no_network, const bool overwrite_prompt)
			{
				wchar_t buffer[64000]{ 0 };
				String zero;
				zero.push_back(0);
				String f{ ReplaceAll(filter, L"|", zero) };
				ReplaceAllDirect(f, L"\n", zero);
				f += zero + zero;
				if (filename.length() > 0)
				{
					memcpy(buffer, filename.c_str(), filename.length() * sizeof(wchar_t));
					buffer[filename.length()] = 0;
				}
				OPENFILENAMEW s;
				ZeroMemory(&s, sizeof(OPENFILENAMEW));
				s.lStructSize = sizeof(OPENFILENAMEW);
				s.hwndOwner = GetActiveWindow();
				s.lpstrFilter = f.c_str();
				s.nFilterIndex = filter_index;
				s.lpstrFile = buffer;
				s.nMaxFile = 64000;
				if (create_prompt)
					s.Flags |= OFN_CREATEPROMPT;
				if (must_exists)
					s.Flags |= OFN_FILEMUSTEXIST;
				if (show_hidden)
					s.Flags |= OFN_FORCESHOWHIDDEN;
				if (hide_readonly)
					s.Flags |= OFN_HIDEREADONLY;
				if (no_network)
					s.Flags |= OFN_NONETWORKBUTTON;
				if (overwrite_prompt)
					s.Flags |= OFN_OVERWRITEPROMPT;
				s.lpstrDefExt = default_extension.c_str();
				if (!GetSaveFileNameW(&s))
					return false;
				filename = buffer;
				return true;
			}

			bool CDialogs::Font(String &name, int &height, FontWeight &weight, bool &italic, bool &underline, bool &strikeout, nitisa::Color &color)
			{
				LOGFONT f;
				ZeroMemory(&f, sizeof(LOGFONT));
				f.lfHeight = height;
				switch (weight)
				{
				case FontWeight::Thin:
					f.lfWeight = FW_THIN;
					break;
				case FontWeight::ExtraLight:
					f.lfWeight = FW_EXTRALIGHT;
					break;
				case FontWeight::Light:
					f.lfWeight = FW_LIGHT;
					break;
				case FontWeight::Medium:
					f.lfWeight = FW_MEDIUM;
					break;
				case FontWeight::SemiBold:
					f.lfWeight = FW_SEMIBOLD;
					break;
				case FontWeight::Bold:
					f.lfWeight = FW_BOLD;
					break;
				case FontWeight::ExtraBold:
					f.lfWeight = FW_EXTRABOLD;
					break;
				case FontWeight::Heavy:
					f.lfWeight = FW_HEAVY;
					break;
				default:
					f.lfWeight = FW_NORMAL;
				}
				f.lfItalic = italic;
				f.lfUnderline = underline;
				f.lfStrikeOut = strikeout;
				f.lfCharSet = DEFAULT_CHARSET;
				f.lfOutPrecision = OUT_DEFAULT_PRECIS;
				f.lfClipPrecision = CLIP_DEFAULT_PRECIS;
				f.lfQuality = DEFAULT_QUALITY;
				f.lfPitchAndFamily = DEFAULT_PITCH;
				memcpy(f.lfFaceName, name.c_str(), (name.length() + 1) * sizeof(wchar_t));

				CHOOSEFONT s;
				ZeroMemory(&s, sizeof(CHOOSEFONT));
				s.lStructSize = sizeof(CHOOSEFONT);
				s.hwndOwner = GetActiveWindow();
				s.lpLogFont = &f;
				s.Flags = CF_EFFECTS | CF_INITTOLOGFONTSTRUCT;
				s.rgbColors = RGB(color.R, color.G, color.B);
				if (!ChooseFont(&s))
					return false;
				name = f.lfFaceName;
				height = f.lfHeight;
				if (f.lfWeight <= FW_THIN)
					weight = FontWeight::Thin;
				else if (f.lfWeight <= FW_EXTRALIGHT)
					weight = FontWeight::ExtraLight;
				else if (f.lfWeight <= FW_LIGHT)
					weight = FontWeight::Light;
				else if (f.lfWeight <= FW_NORMAL)
					weight = FontWeight::Normal;
				else if (f.lfWeight <= FW_MEDIUM)
					weight = FontWeight::Medium;
				else if (f.lfWeight <= FW_SEMIBOLD)
					weight = FontWeight::SemiBold;
				else if (f.lfWeight <= FW_BOLD)
					weight = FontWeight::Bold;
				else if (f.lfWeight <= FW_EXTRABOLD)
					weight = FontWeight::ExtraBold;
				else
					weight = FontWeight::Heavy;
				italic = f.lfItalic;
				underline = f.lfUnderline;
				strikeout = f.lfStrikeOut;
				color.R = GetRValue(s.rgbColors);
				color.G = GetGValue(s.rgbColors);
				color.B = GetBValue(s.rgbColors);
				return true;
			}

			bool CDialogs::Color(const bool any_color, const bool full_open, const bool prevent_full_open, const bool only_solid_colors, nitisa::Color &color)
			{
				static COLORREF custom_colors[16];
				CHOOSECOLOR s;
				ZeroMemory(&s, sizeof(CHOOSECOLOR));
				s.lStructSize = sizeof(CHOOSECOLOR);
				s.hwndOwner = GetActiveWindow();
				s.rgbResult = RGB(color.R, color.G, color.B);
				s.lpCustColors = custom_colors;
				s.Flags = CC_RGBINIT;
				if (any_color)
					s.Flags |= CC_ANYCOLOR;
				if (full_open)
					s.Flags |= CC_FULLOPEN;
				if (prevent_full_open)
					s.Flags |= CC_PREVENTFULLOPEN;
				if (only_solid_colors)
					s.Flags |= CC_SOLIDCOLOR;
				if (!ChooseColor(&s))
					return false;
				color.R = GetRValue(s.rgbResult);
				color.G = GetGValue(s.rgbResult);
				color.B = GetBValue(s.rgbResult);
				return true;
			}

			bool CDialogs::PageSetup(const bool disable_margins, const bool disable_orientation, const bool disable_page_painting, const bool disable_paper, const bool no_network_button,
				const RectF &min_margins, String &device_name, RectF &margins, bool &landscape, PrintPaperSize &paper_size, float &paper_length, float &paper_width, float &scale, int &copies,
				PrintPaperSource &paper_source, PrintQuality &print_quality, bool &monochrome, PrintDuplex &duplex, PrintTTOption &tt_option, bool &collate, PrintMediaType &media_type,
				PrintDitherType &dither_type, PointF &size)
			{
				PAGESETUPDLG s;
				ZeroMemory(&s, sizeof(PAGESETUPDLG));
				s.lStructSize = sizeof(PAGESETUPDLG);
				s.hwndOwner = GetActiveWindow();
				s.Flags = PSD_INHUNDREDTHSOFMILLIMETERS;
				if (disable_margins)
					s.Flags |= PSD_DISABLEMARGINS;
				if (disable_orientation)
					s.Flags |= PSD_DISABLEORIENTATION;
				if (disable_page_painting)
					s.Flags |= PSD_DISABLEPAGEPAINTING;
				if (disable_paper)
					s.Flags |= PSD_DISABLEPAPER;
				if (no_network_button)
					s.Flags |= PSD_NONETWORKBUTTON;
				if (margins.has_positive())
				{
					s.rtMargin = {
						ntl::Max<int>(0, int(margins.Left * 100)),
						ntl::Max<int>(0, int(margins.Top * 100)),
						ntl::Max<int>(0, int(margins.Right * 100)),
						ntl::Max<int>(0, int(margins.Bottom * 100)) };
					s.Flags += PSD_MARGINS;
				}
				if (min_margins.has_positive())
				{
					s.rtMinMargin = {
						ntl::Max<int>(0, int(min_margins.Left * 100)),
						ntl::Max<int>(0, int(min_margins.Top * 100)),
						ntl::Max<int>(0, int(min_margins.Right * 100)),
						ntl::Max<int>(0, int(min_margins.Bottom * 100)) };
					s.Flags += PSD_MINMARGINS;
				}
				if (PageSetupDlg(&s))
				{
					DEVMODE *dm{ (DEVMODE*)s.hDevMode };
					device_name = ExtractPrintDeviceName((void*)dm);
					landscape = ExtractPrintLandscape((void*)dm);
					paper_size = ExtractPrintPaperSize((void*)dm);
					paper_length = ExtractPrintPaperLength((void*)dm);
					paper_width = ExtractPrintPaperWidth((void*)dm);
					scale = ExtractPrintScale((void*)dm);
					copies = ExtractPrintCopies((void*)dm);
					paper_source = ExtractPrintPaperSource((void*)dm);
					print_quality = ExtractPrintQuality((void*)dm);
					monochrome = ExtractPrintMonochrome((void*)dm);
					duplex = ExtractPrintDuplex((void*)dm);
					tt_option = ExtractPrintTTOption((void*)dm);
					collate = ExtractPrintCollate((void*)dm);
					media_type = ExtractPrintMediaType((void*)dm);
					dither_type = ExtractPrintDitherType((void*)dm);
					size = PointF{ s.ptPaperSize.x * 0.01f, s.ptPaperSize.y * 0.01f };
					margins = RectF{ s.rtMargin.left * 0.01f, s.rtMargin.top * 0.01f, s.rtMargin.right * 0.01f, s.rtMargin.bottom * 0.01f };
					if (s.hDevMode)
						GlobalFree(s.hDevMode);
					if (s.hDevNames)
						GlobalFree(s.hDevNames);
					return true;
				}
				return false;
			}

			IDialogs::PrintDialogResult CDialogs::Print(const bool select_collate, const bool select_current_page, const bool disable_print_to_file, const bool hide_print_to_file,
				const bool disable_current_page, const bool no_page_nums, const bool no_selection, const bool select_page_nums, const bool select_print_to_file, const bool select_selection,
				const int min_page, const int max_page, const int max_page_range_count, int &page_range_count, Point *page_ranges, int &copies, String &device_name,
				bool &landscape, PrintPaperSize &paper_size, float &paper_length, float &paper_width, float &scale, PrintPaperSource &paper_source, PrintQuality &print_quality, bool &monochrome,
				PrintDuplex &duplex, PrintTTOption &tt_option, bool &collate, PrintMediaType &media_type, PrintDitherType &dither_type, void **handle)
			{
				if (max_page_range_count > 0 && !page_ranges)
					return PrintDialogResult::Error;
				PRINTDLGEX s;
				ZeroMemory(&s, sizeof(PRINTDLGEX));
				s.lStructSize = sizeof(PRINTDLGEX);
				s.hwndOwner = GetActiveWindow();
				if (select_collate)
					s.Flags |= PD_COLLATE;
				if (select_current_page)
					s.Flags |= PD_CURRENTPAGE;
				if (disable_print_to_file)
					s.Flags |= PD_DISABLEPRINTTOFILE;
				if (hide_print_to_file)
					s.Flags |= PD_HIDEPRINTTOFILE;
				if (disable_current_page)
					s.Flags |= PD_NOCURRENTPAGE;
				if (no_page_nums)
					s.Flags |= PD_NOPAGENUMS;
				if (no_selection)
					s.Flags |= PD_NOSELECTION;
				if (select_page_nums)
					s.Flags |= PD_PAGENUMS;
				if (select_print_to_file)
					s.Flags |= PD_PRINTTOFILE;
				if (select_selection)
					s.Flags |= PD_SELECTION;
				if (handle)
					s.Flags |= PD_RETURNDC;
				if (min_page > 0)
					s.nMinPage = min_page;
				if (max_page > 0)
					s.nMaxPage = max_page;
				if (copies > 0)
					s.nCopies = copies;
				s.nStartPage = START_PAGE_GENERAL;
				PRINTPAGERANGE *ranges{ nullptr };
				if (max_page_range_count > 0)
				{
					ranges = (PRINTPAGERANGE*)GlobalAlloc(GPTR, sizeof(PRINTPAGERANGE) * max_page_range_count);
					for (int i = 0; i < page_range_count; i++)
					{
						ranges[i].nFromPage = page_ranges[i].X;
						ranges[i].nToPage = page_ranges[i].Y;
					}
					s.nMaxPageRanges = max_page_range_count;
					s.nPageRanges = page_range_count;
					s.lpPageRanges = ranges;
				}
				bool success{ SUCCEEDED(PrintDlgEx(&s)) };
				PrintDialogResult result;
				if (success)
				{
					if (max_page_range_count > 0 && (int)s.nPageRanges <= max_page_range_count)
					{
						page_range_count = s.nPageRanges;
						for (int i = 0; i < page_range_count; i++)
							page_ranges[i] = { (int)ranges[i].nFromPage, (int)ranges[i].nToPage };
					}
					else
						page_range_count = 0;
					copies = s.nCopies;
					if (handle)
						*handle = s.hDC;

					DEVMODE *dm{ (DEVMODE*)s.hDevMode };
					device_name = ExtractPrintDeviceName((void*)dm);
					landscape = ExtractPrintLandscape((void*)dm);
					paper_size = ExtractPrintPaperSize((void*)dm);
					paper_length = ExtractPrintPaperLength((void*)dm);
					paper_width = ExtractPrintPaperWidth((void*)dm);
					scale = ExtractPrintScale((void*)dm);
					paper_source = ExtractPrintPaperSource((void*)dm);
					print_quality = ExtractPrintQuality((void*)dm);
					monochrome = ExtractPrintMonochrome((void*)dm);
					duplex = ExtractPrintDuplex((void*)dm);
					tt_option = ExtractPrintTTOption((void*)dm);
					collate = ExtractPrintCollate((void*)dm);
					media_type = ExtractPrintMediaType((void*)dm);
					dither_type = ExtractPrintDitherType((void*)dm);
					if (s.hDevMode)
						GlobalFree(s.hDevMode);
					if (s.hDevNames)
						GlobalFree(s.hDevNames);
					switch (s.dwResultAction)
					{
					case PD_RESULT_PRINT:
						result = PrintDialogResult::Print;
						break;
					case PD_RESULT_APPLY:
						result = PrintDialogResult::Apply;
						break;
					default:
						result = PrintDialogResult::Cancel;
					}
				}
				else
					result = PrintDialogResult::Error;
				if (ranges)
					GlobalFree(ranges);
				return result;
			}

			bool CDialogs::BrowseFolder(String &folder, const String &title, const bool only_file_system, const bool no_network, const bool only_ancestors, const bool show_edit_box, const bool new_style,
				const bool show_hint, const bool hide_new_folder, const bool dont_translate_targets, const bool only_computers, const bool only_printers, const bool show_files,
				const bool show_shareable)
			{
				BROWSEINFOW bi;
				ZeroMemory(&bi, sizeof(BROWSEINFOW));
				bi.hwndOwner = GetActiveWindow();
				if (title.length() > 0)
					bi.lpszTitle = title.c_str();
				if (only_file_system)
					bi.ulFlags |= BIF_RETURNONLYFSDIRS;
				if (no_network)
					bi.ulFlags |= BIF_DONTGOBELOWDOMAIN;
				if (only_ancestors)
					bi.ulFlags |= BIF_RETURNFSANCESTORS;
				if (show_edit_box)
					bi.ulFlags |= BIF_EDITBOX;
				if (new_style)
					bi.ulFlags |= BIF_NEWDIALOGSTYLE;
				if (show_hint)
					bi.ulFlags |= BIF_UAHINT;
				if (hide_new_folder)
					bi.ulFlags |= BIF_NONEWFOLDERBUTTON;
				if (dont_translate_targets)
					bi.ulFlags |= BIF_NOTRANSLATETARGETS;
				if (only_computers)
					bi.ulFlags |= BIF_BROWSEFORCOMPUTER;
				if (only_printers)
					bi.ulFlags |= BIF_BROWSEFORPRINTER;
				if (show_files)
					bi.ulFlags |= BIF_BROWSEINCLUDEFILES;
				if (show_shareable)
					bi.ulFlags |= BIF_SHAREABLE;
				LPITEMIDLIST id{ SHBrowseForFolderW(&bi) };
				if (id)
				{
					wchar_t path[MAX_PATH]{ 0 };
					bool result;
					if (SHGetPathFromIDListW(id, path))
					{
						folder = path;
						if (folder.length() > 0 && folder[folder.length() - 1] != m_pApplication->System->DirectorySeparator)
							folder += m_pApplication->System->DirectorySeparator;
						result = true;
					}
					else
						result = false;
					CoTaskMemFree(id);
					return result;
				}
				return false;
			}
		#pragma endregion
		}
	}
}
#endif