// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Math/PointF.h"
#include "../Math/RectF.h"
#include "Strings.h"
#include "Variant.h"
#include <algorithm>
#include <locale>
#include <vector>

namespace nitisa
{
	class IControl;
	class IListItem;
	class IComponentItemList;
	class IForm;
	class IPlatformFont;

#pragma region Template functions
	template<class DstType, class SrcType> DstType cast(SrcType value)
	{
		DstType result{ nullptr };
		try
		{
			result = dynamic_cast<DstType>(value);
		}
		catch (...)
		{
			result = nullptr;
		}
		return result;
	}

	template<class Type> bool in(const Type value, const std::vector<Type> &list)
	{
		return std::find(list.begin(), list.end(), value) != list.end();
	}

	template<class Type, bool UseControl> Type parent(IControl *control)
	{
		if (!control)
			return nullptr;
		IControl *p{ UseControl ? control : control->getParent() };
		Type r;
		while (p)
		{
			if ((r = cast<Type>(p)))
				return r;
			p = p->getParent();
		}
		return nullptr;
	}
#pragma endregion

#pragma region String/Variant/Type conversion
	String ToString(const bool value);
	Variant ToVariant(const bool value);
	void FromVariant(const Variant &value, bool &dest);

	Variant ToVariant(const float value);
	void FromVariant(const Variant &value, float &dest);

	Variant ToVariant(const double value);
	void FromVariant(const Variant &value, double &dest);

	Variant ToVariant(const int value);
	void FromVariant(const Variant &value, int &dest);

	Variant ToVariant(const long long value);
	void FromVariant(const Variant &value, long long &dest);

	Variant ToVariant(const unsigned int value);
	void FromVariant(const Variant &value, unsigned int &dest);

	Variant ToVariant(const String &value);
	void FromVariant(const Variant &value, String &dest);
#pragma endregion

#pragma region Convert to string as source code
	String AsSourceCode(const float a);
	String AsSourceCode(const double a);
#pragma endregion

#pragma region Pathes and file names
	String ExtractDirectoryName(const String &path, const wchar_t separator = L'\\'); // Without separator at the end
	String ExtractFileExtension(const String &filename); // Without "."
	String ExtractFileName(const String &path, const wchar_t path_separator = L'\\', const wchar_t drive_separator = L':');
	String ExtractDriveName(const String &path, const wchar_t separator = L':'); // Without separator at the end
#pragma endregion

#pragma region Read/write files
	AnsiString GetAnsiFileContent(const String &filename);
	String GetUTF8FileContent(const String &filename);
	String GetFileContent(const String &filename);
	bool PutAnsiFileContent(const String &filename, const String &content);
	bool PutUTF8FileContent(const String &filename, const String &content);
#pragma endregion

#pragma region Debugging
	void Log(const String &content, const String &filename = L"C:\\temp\\app.log", const bool add_date = false, const bool add_time = true, const bool add_eol = true);
#pragma endregion

#pragma region String manipulation
	/**
	Split string by words so it to fit into specified width
	@param str String to be split
	@param width Width into which the string to be fit. Should be no less than 32
	@param pf Platform font used to render. Cannot be nullptr
	@param distance Additional distance between characters
	@param [out] lines Resulting lines
	@param [out] size Resulting size. Width can be greater than requested one if there is a very long word(s)
	@param locale Used locale
	@return Whether process was successful or not
	@note Line separator in the string should be '\n' character. If '\n\r' or '\r' is used, it should be replaced with '\n' only
	*/
	bool WordWrap(const String &str, const float width, IPlatformFont *pf, const float distance, StringArray &lines, PointF &size, const std::locale &locale = std::locale());

	/**
	Split string by characters(breaking words) so it to fit into specified width
	@param str String to be split
	@param width Width into which the string to be fit. Should be no less then 8
	@param pf Platform font used to render. Cannot be nullptr
	@param distance Additional distance between characters
	@param [out] lines Resulting lines
	@param [out] size Resulting size. Width can be greater than requested one if there is a very large characters(character size is greater then requested width)
	@param locale Used locale
	@return Whether process was successful or not
	@note Line separator in the string should be '\n' character. If '\n\r' or '\r' is used, it should be replaced with '\n' only
	*/
	bool WordBreak(const String &str, const float width, IPlatformFont *pf, const float distance, StringArray &lines, PointF &size, const std::locale &locale = std::locale());
#pragma endregion

#pragma region Math
	float Angle(const float x, const float y, const float center_x, const float center_y);
	float Angle(const float x, const float y, const float center_x, const float center_y, const float distance);
	PointF AdjustByConstraints(const PointF &size, const RectF &constraints); // Apply constraints to the rectangle
#pragma endregion

#pragma region Order
	bool MoveControl(std::vector<IControl*> &list, IControl *parent, IControl *control, const int before);
	bool MoveControl(std::vector<IControl*> &list, IForm *parent, IControl *control, const int before);
	bool MoveListItem(std::vector<IListItem*> &list, IListItem *parent, IListItem *item, const int before);
	bool MoveListItem(std::vector<IListItem*> &list, IComponentItemList *parent, IListItem *item, const int before);
#pragma endregion
}