// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifndef _WIN32
	#if __has_include(<filesystem>)
		#include <filesystem>
	#else
		#if __has_include(<experimental/filesystem>)
			#include <experimental/filesystem>
		#endif
	#endif
#endif

namespace nitisa
{
#pragma region String/Variant/Type conversion
#pragma region bool
	String ToString(const bool value)
	{
		return value ? L"true" : L"false";
	}

	Variant ToVariant(const bool value)
	{
		return (Variant)value;
	}

	void FromVariant(const Variant &value, bool &dest)
	{
		dest = (bool)value;
	}
#pragma endregion

#pragma region float
	Variant ToVariant(const float value)
	{
		return (Variant)value;
	}

	void FromVariant(const Variant &value, float &dest)
	{
		dest = (float)value;
	}
#pragma endregion

#pragma region double
	Variant ToVariant(const double value)
	{
		return (Variant)ToString(value);
	}

	void FromVariant(const Variant &value, double &dest)
	{
		dest = StringToDouble((String)value);
	}
#pragma endregion

#pragma region int
	Variant ToVariant(const int value)
	{
		return (Variant)value;
	}

	void FromVariant(const Variant &value, int &dest)
	{
		dest = (int)value;
	}
#pragma endregion

#pragma region long long
	Variant ToVariant(const long long value)
	{
		return (Variant)ToString(value);
	}

	void FromVariant(const Variant &value, long long &dest)
	{
		dest = StringToInt64((String)value);
	}
#pragma endregion

#pragma region unsigned int
	Variant ToVariant(const unsigned int value)
	{
		return (Variant)value;
	}

	void FromVariant(const Variant &value, unsigned int &dest)
	{
		dest = (unsigned int)value;
	}
#pragma endregion

#pragma region String
	Variant ToVariant(const String &value)
	{
		return (Variant)value;
	}

	void FromVariant(const Variant &value, String &dest)
	{
		dest = (String)value;
	}
#pragma endregion
#pragma endregion

#pragma region Convert to string as source code
	String AsSourceCode(const float a)
	{
		String result{ ToStringCompact(a) };
		if (result.find(L'.', 0) != String::npos || result.find(L'e', 0) != String::npos)
			return result + L'f';
		return result + L".0f";
	}

	String AsSourceCode(const double a)
	{
		String result{ ToStringCompact(a) };
		if (result.find(L'.', 0) == String::npos && result.find(L'e', 0) == String::npos)
			return result + L".0";
		return result;
	}
#pragma endregion

#pragma region Pathes and file names
	String ExtractDirectoryName(const String &path, const wchar_t separator)
	{
		String result{ path };
		if (result.length() > 0 && result[result.length() - 1] == separator)
		{
			result.erase(result.length() - 1, 1);
			return result;
		}
		auto pos{ result.find_last_of(separator) };
		if (pos != String::npos)
			result.erase(pos, result.length() - pos);
		return result;
	}

	String ExtractFileExtension(const String &filename)
	{
		auto pos{ filename.find_last_of(L'.') };
		if (pos != String::npos)
			return filename.substr(pos + 1, filename.length() - pos - 1);
		return L"";
	}

	String ExtractFileName(const String &path, const wchar_t path_separator, const wchar_t drive_separator)
	{
		if (path.length() > 0 && path[path.length() - 1] == path_separator)
			return L"";
		auto pos_path_separator{ path.find_last_of(path_separator) };
		if (pos_path_separator != String::npos)
			return path.substr(pos_path_separator + 1, path.length() - pos_path_separator - 1);
		auto pos_drive_separator{ path.find_last_of(drive_separator) };
		if (pos_drive_separator != String::npos)
			return path.substr(pos_drive_separator + 1, path.length() - pos_drive_separator - 1);
		return path;
	}

	String ExtractDriveName(const String &path, const wchar_t separator)
	{
		auto pos{ path.find_first_of(separator) };
		if (pos != String::npos)
			return path.substr(0, pos);
		return L"";
	}
#pragma endregion

#pragma region Read/write files
	AnsiString GetAnsiFileContent(const String &filename)
	{
	#ifdef _WIN32
		std::ifstream f{ filename };
	#else
		#if __has_include(<filesystem>)
			std::ifstream f{ std::filesystem::path(filename) };
		#else
			#if __has_include(<experimental/filesystem>)
				std::ifstream f{ std::experimental::filesystem::path(filename) };
			#else
				std::ifstream f{ StringToAnsi(filename) };
			#endif
		#endif
	#endif
		if (!f.bad())
		{
			std::stringstream ss;
			ss << f.rdbuf();
			f.close();
			return ss.str();
		}
		return "";
	}

	String GetUTF8FileContent(const String &filename)
	{
	#ifdef _WIN32
		std::ifstream f{ filename };
	#else
		#if __has_include(<filesystem>)
			std::ifstream f{ std::filesystem::path(filename) };
		#else
			#if __has_include(<experimental/filesystem>)
				std::ifstream f{ std::experimental::filesystem::path(filename) };
			#else
				std::ifstream f{ StringToAnsi(filename) };
			#endif
		#endif
	#endif
		if (!f.bad())
		{
			std::stringstream ss;
			ss << f.rdbuf();
			f.close();
			return UTF8ToString(ss.str());
		}
		return L"";
	}

	String GetFileContent(const String &filename)
	{
		try
		{
			return GetUTF8FileContent(filename);
		}
		catch (...)
		{
		}
		return AnsiToString(GetAnsiFileContent(filename));
	}

	bool PutAnsiFileContent(const String &filename, const String &content)
	{
	#ifdef _WIN32
		std::ofstream f{ filename };
	#else
		#if __has_include(<filesystem>)
			std::ofstream f{ std::filesystem::path(filename) };
		#else
			#if __has_include(<experimental/filesystem>)
				std::ofstream f{ std::experimental::filesystem::path(filename) };
			#else
				std::ofstream f{ StringToAnsi(filename) };
			#endif
		#endif
	#endif
		if (f.bad())
			return false;
		f << StringToAnsi(content);
		f.close();
		return true;
	}

	bool PutUTF8FileContent(const String &filename, const String &content)
	{
	#ifdef _WIN32
		std::wofstream f{ filename };
	#else
		#if __has_include(<filesystem>)
			std::wofstream f{ std::filesystem::path(filename) };
		#else
			#if __has_include(<experimental/filesystem>)
				std::wofstream f{ std::experimental::filesystem::path(filename) };
			#else
				std::wofstream f{ StringToAnsi(filename) };
			#endif
		#endif
	#endif
		if (f.bad())
			return false;
		const std::locale utf8_locale{ std::locale(std::locale(), new std::codecvt_utf8<wchar_t>()) };
		f.imbue(utf8_locale);
		f << content;
		f.close();
		return true;
	}
#pragma endregion

#pragma region Debugging
	void Log(const String &content, const String &filename, const bool add_date, const bool add_time, const bool add_eol)
	{
	#ifdef _WIN32
		std::wofstream f{ filename, std::ios_base::app };
	#else
		#if __has_include(<filesystem>)
			std::wofstream f{ std::filesystem::path(filename), std::ios_base::app };
		#else
			#if __has_include(<experimental/filesystem>)
				std::wofstream f{ std::experimental::filesystem::path(filename), std::ios_base::app };
			#else
				std::wofstream f{ StringToAnsi(filename), std::ios_base::app };
			#endif
		#endif
	#endif
		if (!f.bad())
		{
			const std::locale utf8_locale{ std::locale(std::locale(), new std::codecvt_utf8<wchar_t>()) };
			f.imbue(utf8_locale);
			if (add_date || add_time)
			{
				CDateTime d;
				f << L"[";
				if (add_date)
					f << PadLeft(ToString(d.getYear()), L'0', 4) << L"-" << PadLeft(ToString(d.getMonth()), L'0', 2) << L"-" << PadLeft(ToString(d.getDay()), L'0', 2);
				if (add_time)
				{
					if (add_date)
						f << L" ";
					f << PadLeft(ToString(d.getHour()), L'0', 2) << L":" << PadLeft(ToString(d.getMinute()), L'0', 2) << L":" << PadLeft(ToString(d.getSecond()), L'0', 2);
					f << L"] ";
				}
			}
			f << content;
			if (add_eol)
				f << std::endl;
			f.close();
		}
	}
#pragma endregion

#pragma region String manipulation
	bool WordWrap(const String &str, const float width, IPlatformFont *pf, const float distance, StringArray &lines, PointF &size, const std::locale &locale)
	{
		lines.clear();
		size = PointF{ 0, 0 };
		if (pf && ntl::IsGreaterOrEqual<float>(width, 32.0f))
		{
			String t;
			size_t index{ 0 }, len{ str.length() }, current_line_start{ 0 }, word_start, new_line_index{ 0 };
			float current_line_width{ 0 };
			PointF s;
			bool found;
			while (index < len)
			{
				word_start = SearchWordStartForward(str, index, locale);
				found = false;
				for (size_t i = index; i < word_start; i++)
					if (str[i] == '\n')
					{
						found = true;
						new_line_index = i;
						break;
					}
				t = str.substr(index, word_start - index);
				s = pf->getStringSize(t, distance);
				if (current_line_start < index && current_line_width + distance + s.X > width)
				{
					lines.push_back(str.substr(current_line_start, index - current_line_start));
					size.X = ntl::Max<float>(size.X, current_line_width);
					size.Y += s.Y;
					current_line_start = index;
					if (found)
					{
						word_start = index;
						current_line_width = 0;
					}
					else
						current_line_width = s.X;
				}
				else if (found)
				{
					t = str.substr(current_line_start, new_line_index - current_line_start);
					s = pf->getStringSize(t, distance);
					lines.push_back(t);
					size.X = ntl::Max<float>(size.X, s.X);
					size.Y += s.Y;
					index = current_line_start = new_line_index + 1;
					current_line_width = 0;
					continue;
				}
				else
				{
					if (current_line_start < index)
						current_line_width += distance;
					current_line_width += s.X;
				}
				index = word_start;
			}
			if (index > current_line_start)
			{
				t = str.substr(current_line_start, index - current_line_start);
				s = pf->getStringSize(t, distance);
				lines.push_back(t);
				size.X = ntl::Max<float>(size.X, s.X);
				size.Y += s.Y;
			}
			return true;
		}
		return false;
	}

	bool WordBreak(const String &str, const float width, IPlatformFont *pf, const float distance, StringArray &lines, PointF &size, const std::locale &locale)
	{
		lines.clear();
		size = PointF{ 0, 0 };
		if (pf && ntl::IsGreaterOrEqual<float>(width, 8.0f))
		{
			String t;
			size_t index{ 0 }, len{ str.length() }, current_line_start{ 0 }, word_start;
			float current_line_width{ 0 };
			PointF s;
			while (index < len)
			{
				if (str[index] == '\n')
				{
					t = str.substr(current_line_start, index - current_line_start);
					s = pf->getStringSize(t, distance);
					lines.push_back(t);
					size.X = ntl::Max<float>(size.X, s.X);
					size.Y += s.Y;
					index = current_line_start = index + 1;
					current_line_width = 0;
					continue;
				}
				word_start = index + 1;
				t = str.substr(index, word_start - index);
				s = pf->getStringSize(t, distance);
				if (current_line_start < index && current_line_width + distance + s.X > width)
				{
					lines.push_back(str.substr(current_line_start, index - current_line_start));
					size.X = ntl::Max<float>(size.X, current_line_width);
					size.Y += s.Y;
					current_line_start = index;
					current_line_width = s.X;
				}
				else
				{
					if (current_line_start < index)
						current_line_width += distance;
					current_line_width += s.X;
				}
				index = word_start;
			}
			if (index > current_line_start)
			{
				t = str.substr(current_line_start, index - current_line_start);
				s = pf->getStringSize(t, distance);
				lines.push_back(t);
				size.X = ntl::Max<float>(size.X, s.X);
				size.Y += s.Y;
			}
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Math
	float Angle(const float x, const float y, const float center_x, const float center_y)
	{
		if (x > center_x)
		{
			if (y > center_y)
				return std::acos((x - center_x) / std::sqrt((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y)));
			if (y < center_y)
				return ntl::DoublePi<float> - std::acos((x - center_x) / std::sqrt((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y)));
			else
				return 0;
		}
		if (x < center_x)
		{
			if (y > center_y)
				return ntl::Pi<float> - std::acos((center_x - x) / std::sqrt((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y)));
			if (y < center_y)
				return ntl::Pi<float> + std::acos((center_x - x) / std::sqrt((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y)));
			return ntl::Pi<float>;
		}
		if (y > center_y)
			return ntl::HalfPi<float>;
		if (y < center_y)
			return 1.5f * ntl::Pi<float>;
		return 0;
	}

	float Angle(const float x, const float y, const float center_x, const float center_y, const float distance)
	{
		if (x > center_x)
		{
			if (y > center_y)
				return std::acos((x - center_x) / distance);
			if (y < center_y)
				return ntl::DoublePi<float> - std::acos((x - center_x) / distance);
			else
				return 0;
		}
		if (x < center_x)
		{
			if (y > center_y)
				return ntl::Pi<float> - std::acos((center_x - x) / distance);
			if (y < center_y)
				return ntl::Pi<float> + std::acos((center_x - x) / distance);
			return ntl::Pi<float>;
		}
		if (y > center_y)
			return ntl::HalfPi<float>;
		if (y < center_y)
			return 1.5f * ntl::Pi<float>;
		return 0;
	}

	PointF AdjustByConstraints(const PointF &size, const RectF &constraints)
	{
		PointF result{ size };
		if (constraints.Left > 0 && result.X < constraints.Left)
			result.X = constraints.Left;
		else if (constraints.Right > 0 && result.X > constraints.Right)
			result.X = constraints.Right;
		if (constraints.Top > 0 && result.Y < constraints.Top)
			result.Y = constraints.Top;
		else if (constraints.Bottom > 0 && result.Y > constraints.Bottom)
			result.Y = constraints.Bottom;
		return result;
	}
#pragma endregion

#pragma region Order
	bool MoveControl(std::vector<IControl*> &list, IControl *parent, IControl *control, const int before)
	{
		if (!control || !parent || control->getParent() != parent || before < 0 || before > parent->getControlCount() || parent->getControlCount() == 1 ||
			control == parent->getControl(before) || (before > 0 && parent->getControl(before - 1) == control))
			return false;
		std::vector<IControl*> controls;
		IControl *control_before{ parent->getControl(before) };
		for (auto pos = list.begin(); pos != list.end(); pos++)
			if (*pos != control)
			{
				if (*pos == control_before)
					controls.push_back(control);
				controls.push_back(*pos);
			}
		if (!control_before)
			controls.push_back(control);
		list = controls;
		return true;
	}

	bool MoveControl(std::vector<IControl*> &list, IForm *parent, IControl *control, const int before)
	{
		if (!control || !parent || control->getParent() || control->getForm() != parent || before < 0 || before > parent->getControlCount() || parent->getControlCount() == 1 ||
			control == parent->getControl(before) || (before > 0 && parent->getControl(before - 1) == control))
			return false;
		std::vector<IControl*> controls;
		IControl *control_before{ parent->getControl(before) };
		for (auto pos = list.begin(); pos != list.end(); pos++)
			if (*pos != control)
			{
				if (*pos == control_before)
					controls.push_back(control);
				controls.push_back(*pos);
			}
		if (!control_before)
			controls.push_back(control);
		list = controls;
		return true;
	}

	bool MoveListItem(std::vector<IListItem*> &list, IListItem *parent, IListItem *item, const int before)
	{
		if (!item || !parent || item->getParent() != parent || before < 0 || before > parent->getItemCount() || parent->getItemCount() == 1 || item == parent->getItem(before) ||
			(before > 0 && parent->getItem(before - 1) == item))
			return false;
		std::vector<IListItem*> items;
		IListItem *item_before{ parent->getItem(before) };
		for (auto pos = list.begin(); pos != list.end(); pos++)
			if (*pos != item)
			{
				if (*pos == item_before)
					items.push_back(item);
				items.push_back(*pos);
			}
		if (!item_before)
			items.push_back(item);
		list = items;
		if (item->QueryService()->getOwner() && !item->QueryService()->getOwner()->isIgnoreSizeChange())
			item->QueryService()->getOwner()->NotifyOnSizeChange(item);
		return true;
	}

	bool MoveListItem(std::vector<IListItem*> &list, IComponentItemList *parent, IListItem *item, const int before)
	{
		if (!item || !parent || item->getParent() || before < 0 || before > parent->getItemCount() || parent->getItemCount() == 1 || item == parent->getItem(before) ||
			(before > 0 && parent->getItem(before - 1) == item))
			return false;
		std::vector<IListItem*> items;
		IListItem *item_before{ parent->getItem(before) };
		for (auto pos = list.begin(); pos != list.end(); pos++)
			if (*pos != item)
			{
				if (*pos == item_before)
					items.push_back(item);
				items.push_back(*pos);
			}
		if (!item_before)
			items.push_back(item);
		list = items;
		if (item->QueryService()->getOwner() && !item->QueryService()->getOwner()->isIgnoreSizeChange())
			item->QueryService()->getOwner()->NotifyOnSizeChange(item);
		return true;
	}
#pragma endregion
}