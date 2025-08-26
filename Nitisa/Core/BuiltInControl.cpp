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
#pragma region Constructor & destructor
	CBuiltInControl::CBuiltInControl(const String &class_name) :
		CClass(class_name),
		m_bEnabled{ true },
		m_bFocused{ false },
		m_sSize{ 0, 0 },
		m_sPosition{ 0, 0 },
		m_sDPI{ DesignDPI }
	{

	}

	CBuiltInControl::CBuiltInControl(const String &class_name, const PointF &size) :CBuiltInControl(class_name)
	{
		m_sSize = PointF{ ntl::Max<float>(0.0f, size.X), ntl::Max<float>(0.0f, size.Y) };
	}

	void CBuiltInControl::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Getters
	bool CBuiltInControl::isEnabled()
	{
		return m_bEnabled;
	}

	bool CBuiltInControl::isHovered()
	{
		return false;
	}

	bool CBuiltInControl::isFocused()
	{
		return m_bFocused;
	}

	bool CBuiltInControl::isInside(const PointF &position)
	{
		return position.X >= m_sPosition.X && position.X < m_sPosition.X + m_sSize.X && position.Y >= m_sPosition.Y && position.Y < m_sPosition.Y + m_sSize.Y;
	}

	PointF CBuiltInControl::getSize()
	{
		return m_sSize;
	}

	float CBuiltInControl::getWidth()
	{
		return m_sSize.X;
	}

	float CBuiltInControl::getHeight()
	{
		return m_sSize.Y;
	}

	RectF CBuiltInControl::getRect()
	{
		return RectF{ m_sPosition.X, m_sPosition.Y, m_sPosition.X + m_sSize.X, m_sPosition.Y + m_sSize.Y };
	}

	PointF CBuiltInControl::getPosition()
	{
		return m_sPosition;
	}

	float CBuiltInControl::getLeft()
	{
		return m_sPosition.X;
	}

	float CBuiltInControl::getTop()
	{
		return m_sPosition.Y;
	}

	RectF CBuiltInControl::getClientRect()
	{
		return RectF{ m_sPosition.X, m_sPosition.Y, m_sPosition.X + m_sSize.X, m_sPosition.Y + m_sSize.Y };
	}

	RectF CBuiltInControl::getRenderRect()
	{
		return RectF{ m_sPosition.X, m_sPosition.Y, m_sPosition.X + m_sSize.X, m_sPosition.Y + m_sSize.Y };
	}

	CursorType CBuiltInControl::getCursor(const PointF &position, const CursorType def)
	{
		return def;
	}

	Point CBuiltInControl::getDPI()
	{
		return m_sDPI;
	}
#pragma endregion

#pragma region Setters
	bool CBuiltInControl::setName(const String &value)
	{
		return false;
	}

	bool CBuiltInControl::setEnabled(const bool value)
	{
		if (value != m_bEnabled)
		{
			m_bEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInControl::setFocused(const bool value)
	{
		if (value != m_bFocused)
		{
			m_bFocused = value;
			return true;
		}
		return false;
	}

	bool CBuiltInControl::setSize(const PointF &value)
	{
		if (ntl::IsGreater<float>(value.X, 0) && ntl::IsGreater<float>(value.Y, 0) && IsNotEqual(value, m_sSize))
		{
			m_sSize = value;
			return true;
		}
		return false;
	}

	bool CBuiltInControl::setPosition(const PointF &value)
	{
		if (IsNotEqual(value, m_sPosition))
		{
			m_sPosition = value;
			return true;
		}
		return false;
	}

	bool CBuiltInControl::setDPI(const Point &value)
	{
		if (value.X > 0 && value.Y > 0 && value != m_sDPI)
		{
			PointF s{ (float)value.X / (float)m_sDPI.X, (float)value.Y / (float)m_sDPI.Y };
			m_sDPI = value;
			m_sSize *= s;
			m_sPosition *= s;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Helpers
	void CBuiltInControl::Update()
	{
		// Nothing
	}

	void CBuiltInControl::Refresh()
	{
		// Nothing
	}
#pragma endregion
}