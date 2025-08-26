// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

/*
	In case of using custom style objects and styles list which allow to edit and delete values which may affect existing forms layout, the Application->RepaintAll() should be called after such modification
*/
#pragma once

#include "../Core/Strings.h"

namespace nitisa
{
	class IStyle;

	class IStyles
	{
	protected:
		IStyles() = default;
		~IStyles() = default;
		IStyles(const IStyles &other) = delete;
		IStyles(IStyles &&other) = delete;
		IStyles &operator=(const IStyles &other) = delete;
		IStyles &operator=(IStyles &&other) = delete;
	public:
		virtual int getStyleCount() = 0; // Return style count
		virtual IStyle *getStyle(const int index) = 0; // Return style by index
		virtual IStyle *getStyle(const String &class_name) = 0; // Return style by class name
		virtual IStyle *getStyle(const String &package, const String &class_name) = 0; // Return style by package name and class name

		virtual bool Add(IStyle *style) = 0; // Add style to list
		virtual bool Add(const String &package, IStyle *style) = 0; // Add style to list and associate package name with it
	};
}