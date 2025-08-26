// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Interfaces/IComponent.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointB.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/Rect.h"
#include "Nitisa/Math/RectB.h"
#include "Nitisa/Math/RectF.h"
#include "Nitisa/Math/Vec4f.h"

namespace nitisa
{
	namespace standard
	{
		class ILogger :public virtual IComponent
		{
		protected:
			ILogger() = default;
			~ILogger() = default;
			ILogger(const ILogger &other) = delete;
			ILogger(ILogger &&other) = delete;
			ILogger &operator=(const ILogger &other) = delete;
			ILogger &operator=(ILogger &&other) = delete;
		public:
			virtual String getFileName() = 0; // Return name of file which stores data

			virtual bool setFileName(const String &value) = 0; // Set name of file which stores data

			// Append different types of data to the file specified in FileName. Return false if data to append is empty of file cannot be opened
			virtual bool Log(const String &value, const bool append_new_line = true) = 0;
			virtual bool Log(const wchar_t *value, const bool append_new_line = true) = 0;
			virtual bool Log(const bool value, const bool append_new_line = true) = 0;
			virtual bool Log(const int value, const bool append_new_line = true) = 0;
			virtual bool Log(const float value, const bool append_new_line = true) = 0;
			virtual bool Log(const Color &value, const bool append_new_line = true) = 0;
			virtual bool Log(const Point &value, const bool append_new_line = true) = 0;
			virtual bool Log(const PointB &value, const bool append_new_line = true) = 0;
			virtual bool Log(const PointF &value, const bool append_new_line = true) = 0;
			virtual bool Log(const Rect &value, const bool append_new_line = true) = 0;
			virtual bool Log(const RectB &value, const bool append_new_line = true) = 0;
			virtual bool Log(const RectF &value, const bool append_new_line = true) = 0;
			virtual bool Log(const BorderColor &value, const bool append_new_line = true) = 0;
			virtual bool Log(const Vec4f &value, const bool append_new_line = true) = 0;
		};
	}
}