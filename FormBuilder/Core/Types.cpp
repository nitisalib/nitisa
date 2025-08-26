// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
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
	#pragma region EXPORT_SETTINGS
		EXPORT_SETTINGS::EXPORT_SETTINGS():
			Namespace{ L"app" },
			Prefix{ L"m_p" },
			WidgetsSection{ L"protected" },
			GenerateGetters{ false },
			ExportAs{ ExportAs::Form }
		{

		}
	#pragma endregion

	#pragma region SETTINGS
		SETTINGS::SETTINGS() :
			EXPORT_SETTINGS(),
			GridX{ true },
			GridY{ true },
			GridRotate{ true },
			GridXStep{ 8 },
			GridYStep{ 8 },
			GridRotateStep{ ntl::DegToRad<float>(1) },
			RotateShift{ 2 },
			GridPointSize{ 1 },
			GridPointColor{ 113, 21, 36, 255 },
			SelectionPointSize{ 4 },
			SelectionBorderWidth{ 1 },
			SelectionBorderColor{ 0, 0, 255, 150 },
			SelectionBackgroundColor{ 0, 0, 255, 50 },
			HighlightBorderWidth{ 1, 1, 1, 1 },
			HighlightBorderColor{ Color{ 0, 0, 255, 255 }, Color{ 0, 0, 255, 255 }, Color{ 0, 0, 255, 255 }, Color{ 0, 0, 255, 255 } }
		{

		}

		bool SETTINGS::Load(const String &filename)
		{
			Variant data;
			if (json_decode(GetUTF8FileContent(filename), data))
			{
				FromVariant(data, *this);
				return true;
			}
			return false;
		}

		bool SETTINGS::Save(const String &filename)
		{
			Variant data{ ToVariant(*this) };
			json_encode(data);
			std::wofstream f{ filename };
			if (!f.bad())
			{
				const std::locale utf8_locale{ std::locale(std::locale(), new std::codecvt_utf8<wchar_t>()) };
				f.imbue(utf8_locale);
				f << json_encode(data);
				f.close();
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}