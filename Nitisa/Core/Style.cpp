// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region CStyle::OPTION
	CStyle::OPTION::OPTION() :
		Name{ L"" },
		Type{ OptionType::Integer },
		ValueS{ L"" },
		ValueI{ 0 }
	{

	}
#pragma endregion

#pragma region CStyle
	CStyle::CStyle(const String &class_name) :
		m_bIsImagesSorted{ true },
		m_bIsSkinsSorted{ true },
		m_bIsFontsSorted{ true },
		m_bIsOptionsSorted{ true }
	{
		m_sClassName = class_name;
	}

	CStyle::~CStyle()
	{
		for (auto pos = m_aImages.begin(); pos != m_aImages.end(); pos++)
			delete (*pos);
		for (auto pos = m_aSkins.begin(); pos != m_aSkins.end(); pos++)
			delete (*pos);
		for (auto pos = m_aFonts.begin(); pos != m_aFonts.end(); pos++)
			delete (*pos);
		for (auto pos = m_aOptions.begin(); pos != m_aOptions.end(); pos++)
			delete (*pos);
	}

	void CStyle::Release()
	{
		delete this;
	}

	void CStyle::SortImages()
	{
		if (!m_bIsImagesSorted)
		{
			std::sort(m_aImages.begin(), m_aImages.end(), [](CStyleImage *a, CStyleImage *b) { return a->Name < b->Name; });
			m_bIsImagesSorted = true;
		}
	}

	void CStyle::SortSkins()
	{
		if (!m_bIsSkinsSorted)
		{
			std::sort(m_aSkins.begin(), m_aSkins.end(), [](CStyleSkin *a, CStyleSkin *b) { return a->Name < b->Name; });
			m_bIsSkinsSorted = true;
		}
	}

	void CStyle::SortFonts()
	{
		if (!m_bIsFontsSorted)
		{
			std::sort(m_aFonts.begin(), m_aFonts.end(), [](CStyleFont *a, CStyleFont *b) { return a->Name < b->Name; });
			m_bIsFontsSorted = true;
		}
	}

	void CStyle::SortOptions()
	{
		if (!m_bIsOptionsSorted)
		{
			std::sort(m_aOptions.begin(), m_aOptions.end(), [](OPTION *a, OPTION *b) { return a->Name < b->Name; });
			m_bIsOptionsSorted = true;
		}
	}

	int CStyle::FindImageIndex(const String &name)
	{
		SortImages();
		CStyleImage search{ name, 0, 0, nullptr };
		auto pos = std::lower_bound(m_aImages.begin(), m_aImages.end(), &search, [](CStyleImage *a, CStyleImage *b) { return a->Name < b->Name; });
		if (pos == m_aImages.end())
			return -1;
		if ((*pos)->Name != search.Name)
			return -1;
		return int(pos - m_aImages.begin());
	}

	int CStyle::FindSkinIndex(const String &name)
	{
		SortSkins();
		CStyleSkin search{ name, nullptr, RectF{ 0, 0, 0, 0 } };
		auto pos = std::lower_bound(m_aSkins.begin(), m_aSkins.end(), &search, [](CStyleSkin *a, CStyleSkin *b) { return a->Name < b->Name; });
		if (pos == m_aSkins.end())
			return -1;
		if ((*pos)->Name != search.Name)
			return -1;
		return int(pos - m_aSkins.begin());
	}

	int CStyle::FindFontIndex(const String &name)
	{
		SortFonts();
		CStyleFont search{ name };
		auto pos = std::lower_bound(m_aFonts.begin(), m_aFonts.end(), &search, [](CStyleFont *a, CStyleFont *b) { return a->Name < b->Name; });
		if (pos == m_aFonts.end())
			return -1;
		if ((*pos)->Name != search.Name)
			return -1;
		return int(pos - m_aFonts.begin());
	}

	int CStyle::FindOptionIndex(const String &name)
	{
		SortOptions();
		OPTION search;
		search.Name = name;
		auto pos = std::lower_bound(m_aOptions.begin(), m_aOptions.end(), &search, [](OPTION *a, OPTION *b) { return a->Name < b->Name; });
		if (pos == m_aOptions.end())
			return -1;
		if ((*pos)->Name != search.Name)
			return -1;
		return int(pos - m_aOptions.begin());
	}

	bool CStyle::AddImage(CStyleImage *image)
	{
		if (!image || image->Name.empty())
			return false;
		m_aImages.push_back(image);
		m_bIsImagesSorted = false;
		return true;
	}

	bool CStyle::AddSkin(CStyleSkin *skin)
	{
		if (!skin || skin->Name.empty())
			return false;
		m_aSkins.push_back(skin);
		m_bIsSkinsSorted = false;
		return true;
	}

	bool CStyle::AddFont(CStyleFont *font)
	{
		if (!font || font->Name.empty())
			return false;
		m_aFonts.push_back(font);
		m_bIsFontsSorted = false;
		return true;
	}

	int CStyle::getImageCount()
	{
		return (int)m_aImages.size();
	}

	IStyleImage *CStyle::getImage(const int index)
	{
		if (index < 0 || index >= (int)m_aImages.size())
			return nullptr;
		SortImages();
		return m_aImages[index];
	}

	IStyleImage *CStyle::getImage(const String &name)
	{
		return getImage(FindImageIndex(name));
	}

	int CStyle::getSkinCount()
	{
		return (int)m_aSkins.size();
	}

	IStyleSkin *CStyle::getSkin(const int index)
	{
		if (index < 0 || index >= (int)m_aSkins.size())
			return nullptr;
		SortSkins();
		return m_aSkins[index];
	}

	IStyleSkin *CStyle::getSkin(const String &name)
	{
		return getSkin(FindSkinIndex(name));
	}

	int CStyle::getFontCount()
	{
		return (int)m_aFonts.size();
	}

	IStyleFont *CStyle::getFont(const int index)
	{
		if (index < 0 || index >= (int)m_aFonts.size())
			return nullptr;
		SortFonts();
		return m_aFonts[index];
	}

	IStyleFont *CStyle::getFont(const String &name)
	{
		return getFont(FindFontIndex(name));
	}

	int CStyle::getOptionCount()
	{
		return (int)m_aOptions.size();
	}

	bool CStyle::getOption(const String &name, String &value)
	{
		int index{ FindOptionIndex(name) };
		if (index < 0)
			return false;
		if (m_aOptions[index]->ValueS != value)
		{
			value = m_aOptions[index]->ValueS;
			return true;
		}
		return false;
	}

	bool CStyle::getOption(const String &name, int &value)
	{
		int index{ FindOptionIndex(name) };
		if (index < 0)
			return false;
		if (m_aOptions[index]->ValueI != value)
		{
			value = m_aOptions[index]->ValueI;
			return true;
		}
		return false;
	}

	bool CStyle::getOption(const String &name, float &value)
	{
		int index{ FindOptionIndex(name) };
		if (index < 0)
			return false;
		if (ntl::IsNotEqual<float>(m_aOptions[index]->ValueF, value))
		{
			value = m_aOptions[index]->ValueF;
			return true;
		}
		return false;
	}

	bool CStyle::getOption(const String &name, bool &value)
	{
		int index{ FindOptionIndex(name) };
		if (index < 0)
			return false;
		if (m_aOptions[index]->ValueB != value)
		{
			value = m_aOptions[index]->ValueB;
			return true;
		}
		return false;
	}

	bool CStyle::getOption(const String &name, Rect &value)
	{
		int index{ FindOptionIndex(name) };
		if (index < 0)
			return false;
		if (m_aOptions[index]->ValueRect != value)
		{
			value = m_aOptions[index]->ValueRect;
			return true;
		}
		return false;
	}

	bool CStyle::getOption(const String &name, RectF &value)
	{
		int index{ FindOptionIndex(name) };
		if (index < 0)
			return false;
		if (IsNotEqual(m_aOptions[index]->ValueRectF, value))
		{
			value = m_aOptions[index]->ValueRectF;
			return true;
		}
		return false;
	}

	bool CStyle::getOption(const String &name, RectB &value)
	{
		int index{ FindOptionIndex(name) };
		if (index < 0)
			return false;
		if (m_aOptions[index]->ValueRectB != value)
		{
			value = m_aOptions[index]->ValueRectB;
			return true;
		}
		return false;
	}

	bool CStyle::getOption(const String &name, BorderColor &value)
	{
		int index{ FindOptionIndex(name) };
		if (index < 0)
			return false;
		if (m_aOptions[index]->ValueBorderColor != value)
		{
			value = m_aOptions[index]->ValueBorderColor;
			return true;
		}
		return false;
	}

	bool CStyle::getOption(const String &name, Color &value)
	{
		int index{ FindOptionIndex(name) };
		if (index < 0)
			return false;
		if (m_aOptions[index]->ValueC != value)
		{
			value = m_aOptions[index]->ValueC;
			return true;
		}
		return false;
	}

	bool CStyle::getOption(const String &name, Point &value)
	{
		int index{ FindOptionIndex(name) };
		if (index < 0)
			return false;
		if (m_aOptions[index]->ValuePoint != value)
		{
			value = m_aOptions[index]->ValuePoint;
			return true;
		}
		return false;
	}

	bool CStyle::getOption(const String &name, PointF &value)
	{
		int index{ FindOptionIndex(name) };
		if (index < 0)
			return false;
		if (IsNotEqual(m_aOptions[index]->ValuePointF, value))
		{
			value = m_aOptions[index]->ValuePointF;
			return true;
		}
		return false;
	}

	bool CStyle::getOption(const String &name, PointB &value)
	{
		int index{ FindOptionIndex(name) };
		if (index < 0)
			return false;
		if (m_aOptions[index]->ValuePointB != value)
		{
			value = m_aOptions[index]->ValuePointB;
			return true;
		}
		return false;
	}

	bool CStyle::getOption(const String &name, Gradient &value)
	{
		int index{ FindOptionIndex(name) };
		if (index < 0)
			return false;
		if (m_aOptions[index]->ValueG.isNotEqual(value))
		{
			value = m_aOptions[index]->ValueG;
			return true;
		}
		return false;
	}

	bool CStyle::getOption(const String &name, unsigned int &value)
	{
		int index{ FindOptionIndex(name) };
		if (index < 0)
			return false;
		if (m_aOptions[index]->ValueUInt != value)
		{
			value = m_aOptions[index]->ValueUInt;
			return true;
		}
		return false;
	}

	bool CStyle::setOption(const String &name, const String &value)
	{
		if (name.empty())
			return false;
		int index{ FindOptionIndex(name) };
		OPTION *option;
		if (index < 0)
		{
			option = new OPTION;
			option->Name = name;
			m_aOptions.push_back(option);
			m_bIsOptionsSorted = false;
		}
		else
			option = m_aOptions[index];
		option->ValueS = value;
		option->Type = OptionType::String;
		return true;
	}

	bool CStyle::setOption(const String &name, const int value)
	{
		if (name.empty())
			return false;
		int index{ FindOptionIndex(name) };
		OPTION *option;
		if (index < 0)
		{
			option = new OPTION;
			option->Name = name;
			m_aOptions.push_back(option);
			m_bIsOptionsSorted = false;
		}
		else
			option = m_aOptions[index];
		option->ValueI = value;
		option->Type = OptionType::Integer;
		return true;
	}

	bool CStyle::setOption(const String &name, const float value)
	{
		if (name.empty())
			return false;
		int index{ FindOptionIndex(name) };
		OPTION *option;
		if (index < 0)
		{
			option = new OPTION;
			option->Name = name;
			m_aOptions.push_back(option);
			m_bIsOptionsSorted = false;
		}
		else
			option = m_aOptions[index];
		option->ValueF = value;
		option->Type = OptionType::Float;
		return true;
	}

	bool CStyle::setOption(const String &name, const bool value)
	{
		if (name.empty())
			return false;
		int index{ FindOptionIndex(name) };
		OPTION *option;
		if (index < 0)
		{
			option = new OPTION;
			option->Name = name;
			m_aOptions.push_back(option);
			m_bIsOptionsSorted = false;
		}
		else
			option = m_aOptions[index];
		option->ValueB = value;
		option->Type = OptionType::Bool;
		return true;
	}

	bool CStyle::setOption(const String &name, const Rect &value)
	{
		if (name.empty())
			return false;
		int index{ FindOptionIndex(name) };
		OPTION *option;
		if (index < 0)
		{
			option = new OPTION;
			option->Name = name;
			m_aOptions.push_back(option);
			m_bIsOptionsSorted = false;
		}
		else
			option = m_aOptions[index];
		option->ValueRect = value;
		option->Type = OptionType::Rect;
		return true;
	}

	bool CStyle::setOption(const String &name, const RectF &value)
	{
		if (name.empty())
			return false;
		int index{ FindOptionIndex(name) };
		OPTION *option;
		if (index < 0)
		{
			option = new OPTION;
			option->Name = name;
			m_aOptions.push_back(option);
			m_bIsOptionsSorted = false;
		}
		else
			option = m_aOptions[index];
		option->ValueRectF = value;
		option->Type = OptionType::RectF;
		return true;
	}

	bool CStyle::setOption(const String &name, const RectB &value)
	{
		if (name.empty())
			return false;
		int index{ FindOptionIndex(name) };
		OPTION *option;
		if (index < 0)
		{
			option = new OPTION;
			option->Name = name;
			m_aOptions.push_back(option);
			m_bIsOptionsSorted = false;
		}
		else
			option = m_aOptions[index];
		option->ValueRectB = value;
		option->Type = OptionType::RectB;
		return true;
	}

	bool CStyle::setOption(const String &name, const BorderColor &value)
	{
		if (name.empty())
			return false;
		int index{ FindOptionIndex(name) };
		OPTION *option;
		if (index < 0)
		{
			option = new OPTION;
			option->Name = name;
			m_aOptions.push_back(option);
			m_bIsOptionsSorted = false;
		}
		else
			option = m_aOptions[index];
		option->ValueBorderColor = value;
		option->Type = OptionType::BorderColor;
		return true;
	}

	bool CStyle::setOption(const String &name, const Point &value)
	{
		if (name.empty())
			return false;
		int index{ FindOptionIndex(name) };
		OPTION *option;
		if (index < 0)
		{
			option = new OPTION;
			option->Name = name;
			m_aOptions.push_back(option);
			m_bIsOptionsSorted = false;
		}
		else
			option = m_aOptions[index];
		option->ValuePoint = value;
		option->Type = OptionType::Point;
		return true;
	}

	bool CStyle::setOption(const String &name, const PointF &value)
	{
		if (name.empty())
			return false;
		int index{ FindOptionIndex(name) };
		OPTION *option;
		if (index < 0)
		{
			option = new OPTION;
			option->Name = name;
			m_aOptions.push_back(option);
			m_bIsOptionsSorted = false;
		}
		else
			option = m_aOptions[index];
		option->ValuePointF = value;
		option->Type = OptionType::PointF;
		return true;
	}

	bool CStyle::setOption(const String &name, const PointB &value)
	{
		if (name.empty())
			return false;
		int index{ FindOptionIndex(name) };
		OPTION *option;
		if (index < 0)
		{
			option = new OPTION;
			option->Name = name;
			m_aOptions.push_back(option);
			m_bIsOptionsSorted = false;
		}
		else
			option = m_aOptions[index];
		option->ValuePointB = value;
		option->Type = OptionType::PointB;
		return true;
	}

	bool CStyle::setOption(const String &name, const Color &value)
	{
		if (name.empty())
			return false;
		int index{ FindOptionIndex(name) };
		OPTION *option;
		if (index < 0)
		{
			option = new OPTION;
			option->Name = name;
			m_aOptions.push_back(option);
			m_bIsOptionsSorted = false;
		}
		else
			option = m_aOptions[index];
		option->ValueC = value;
		option->Type = OptionType::Color;
		return true;
	}

	bool CStyle::setOption(const String &name, const Gradient &value)
	{
		if (name.empty())
			return false;
		int index{ FindOptionIndex(name) };
		OPTION *option;
		if (index < 0)
		{
			option = new OPTION;
			option->Name = name;
			m_aOptions.push_back(option);
			m_bIsOptionsSorted = false;
		}
		else
			option = m_aOptions[index];
		option->ValueG = value;
		option->Type = OptionType::Gradient;
		return true;
	}

	bool CStyle::setOption(const String &name, const unsigned int value)
	{
		if (name.empty())
			return false;
		int index{ FindOptionIndex(name) };
		OPTION *option;
		if (index < 0)
		{
			option = new OPTION;
			option->Name = name;
			m_aOptions.push_back(option);
			m_bIsOptionsSorted = false;
		}
		else
			option = m_aOptions[index];
		option->ValueUInt = value;
		option->Type = OptionType::UInt;
		return true;
	}
#pragma endregion
}