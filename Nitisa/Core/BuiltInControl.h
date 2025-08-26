// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IBuiltInControl.h"
#include "../Math/Point.h"
#include "../Math/PointF.h"
#include "../Math/RectF.h"
#include "Class.h"
#include "CursorType.h"
#include "Strings.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class CBuiltInControl :public virtual IBuiltInControl, public CClass
	{
	private:
		bool m_bEnabled;
		bool m_bFocused;
		PointF m_sSize;
		PointF m_sPosition;
		Point m_sDPI;
	public:
		bool isEnabled() override;
		bool isHovered() override;
		bool isFocused() override;
		bool isInside(const PointF &position) override;
		PointF getSize() override;
		float getWidth() override;
		float getHeight() override;
		RectF getRect() override;
		PointF getPosition() override;
		float getLeft() override;
		float getTop() override;
		RectF getClientRect() override;
		RectF getRenderRect() override;
		CursorType getCursor(const PointF &position, const CursorType def) override;
		Point getDPI() override;

		bool setName(const String &value) override;
		bool setEnabled(const bool value) override;
		bool setFocused(const bool value) override;
		bool setSize(const PointF &value) override;
		bool setPosition(const PointF &value) override;
		bool setDPI(const Point &value) override;

		void Update() override;
		void Release() override;
		void Refresh() override; // Do nothing

		CBuiltInControl(const String &class_name); // Constructor
		CBuiltInControl(const String &class_name, const PointF &size); // Constructor with default size
		virtual ~CBuiltInControl() = default;
	};
}