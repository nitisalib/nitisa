// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Component.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointB.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/Rect.h"
#include "Nitisa/Math/RectB.h"
#include "Nitisa/Math/RectF.h"
#include "Nitisa/Math/Vec4f.h"
#include "../ILogger.h"

namespace nitisa
{
	class IForm;

	namespace standard
	{
		class CLogger :public virtual ILogger, public CComponent
		{
		private:
			String m_sFileName;
		public:
			String getFileName() override;

			bool setFileName(const String &value) override;

			bool Log(const String &value, const bool append_new_line = true) override;
			bool Log(const wchar_t *value, const bool append_new_line = true) override;
			bool Log(const bool value, const bool append_new_line = true) override;
			bool Log(const int value, const bool append_new_line = true) override;
			bool Log(const float value, const bool append_new_line = true) override;
			bool Log(const Color &value, const bool append_new_line = true) override;
			bool Log(const Point &value, const bool append_new_line = true) override;
			bool Log(const PointB &value, const bool append_new_line = true) override;
			bool Log(const PointF &value, const bool append_new_line = true) override;
			bool Log(const Rect &value, const bool append_new_line = true) override;
			bool Log(const RectB &value, const bool append_new_line = true) override;
			bool Log(const RectF &value, const bool append_new_line = true) override;
			bool Log(const BorderColor &value, const bool append_new_line = true) override;
			bool Log(const Vec4f &value, const bool append_new_line = true) override;

			CLogger();
			CLogger(IForm *parent);
		};
	}
}