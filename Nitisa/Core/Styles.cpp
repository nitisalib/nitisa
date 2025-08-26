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
	CStyles::~CStyles()
	{
		for (auto pos : m_aStyles)
			pos.Style->Release();
	}

	bool CStyles::Add(IStyle *style)
	{
		if (!style || style->ClassName.empty())
			return false;
		for (auto pos : m_aStyles)
			if (pos.Style == style)
				return false;
		m_aStyles.push_back({ L"", style });
		return true;
	}

	bool CStyles::Add(const String &package, IStyle *style)
	{
		if (!style || style->ClassName.empty())
			return false;
		for (auto pos : m_aStyles)
			if (pos.Style == style)
				return false;
		m_aStyles.push_back({ package, style });
		return true;
	}

	int CStyles::getStyleCount()
	{
		return (int)m_aStyles.size();
	}

	IStyle *CStyles::getStyle(const int index)
	{
		if (index < 0 || index >= (int)m_aStyles.size())
			return nullptr;
		return m_aStyles[index].Style;
	}

	IStyle *CStyles::getStyle(const String &class_name)
	{
		for (auto pos : m_aStyles)
			if (pos.Style->ClassName == class_name)
				return pos.Style;
		return nullptr;
	}

	IStyle *CStyles::getStyle(const String &package, const String &class_name)
	{
		for (auto pos : m_aStyles)
			if (pos.Package == package && pos.Style->ClassName == class_name)
				return pos.Style;
		return nullptr;
	}
}