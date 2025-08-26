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
	namespace standard
	{
	#pragma region Constructor & destructor
		CLogger::CLogger() :
			CComponent(L"Logger"),
			m_sFileName{ L"Application.log" }
		{

		}

		CLogger::CLogger(IForm *parent) :CLogger()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Getters
		String CLogger::getFileName()
		{
			return m_sFileName;
		}
	#pragma endregion

	#pragma region Setters
		bool CLogger::setFileName(const String &value)
		{
			if (value != m_sFileName)
			{
				m_sFileName = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		bool CLogger::Log(const String &value, const bool append_new_line)
		{
			if (m_sFileName.empty())
				return false;
			String v{ value };
			if (v.empty() && !append_new_line)
				return false;
		#if defined(__clang__) || defined(__GNUC__)
			std::wofstream f{ StringToAnsi(m_sFileName), std::ios::app };
		#else
			std::wofstream f{ m_sFileName, std::ios::app };
		#endif
			if (f.bad())
				return false;
			const std::locale utf8_locale{ std::locale(std::locale(), new std::codecvt_utf8<wchar_t>()) };
			f.imbue(utf8_locale);
			f << v;
			if (append_new_line)
				f << std::endl;
			f.close();
			return true;
		}

		bool CLogger::Log(const wchar_t *value, const bool append_new_line)
		{
			return Log((String)value, append_new_line);
		}

		bool CLogger::Log(const bool value, const bool append_new_line)
		{
			return Log(value ? L"true" : L"false", append_new_line);
		}

		bool CLogger::Log(const int value, const bool append_new_line)
		{
			return Log(ToString(value), append_new_line);
		}

		bool CLogger::Log(const float value, const bool append_new_line)
		{
			return Log(ToString(value), append_new_line);
		}

		bool CLogger::Log(const Color &value, const bool append_new_line)
		{
			return Log(ToString(value), append_new_line);
		}

		bool CLogger::Log(const Point &value, const bool append_new_line)
		{
			return Log(ToString(value), append_new_line);
		}

		bool CLogger::Log(const PointB &value, const bool append_new_line)
		{
			return Log(ToString(value), append_new_line);
		}

		bool CLogger::Log(const PointF &value, const bool append_new_line)
		{
			return Log(ToString(value), append_new_line);
		}

		bool CLogger::Log(const Rect &value, const bool append_new_line)
		{
			return Log(ToString(value), append_new_line);
		}

		bool CLogger::Log(const RectB &value, const bool append_new_line)
		{
			return Log(ToString(value), append_new_line);
		}

		bool CLogger::Log(const RectF &value, const bool append_new_line)
		{
			return Log(ToString(value), append_new_line);
		}

		bool CLogger::Log(const BorderColor &value, const bool append_new_line)
		{
			return Log(ToString(value), append_new_line);
		}

		bool CLogger::Log(const Vec4f &value, const bool append_new_line)
		{
			return Log(ToString(RectF{ value.X, value.Y, value.Z, value.W }), append_new_line);
		}
	#pragma endregion
	}
}