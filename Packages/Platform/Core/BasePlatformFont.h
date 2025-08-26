// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Releasable.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IPlatformFont.h"
#include "Nitisa/Math/PointF.h"
#include <vector>

namespace nitisa
{
	namespace platform
	{
		class CBasePlatformFont :public virtual IPlatformFont, public CReleasable
		{
		private:
			bool m_bSorted;
			Char m_sSearch;

			void ClearChars();
			void SortChars();
			int FindCharIndex(const wchar_t chr);
		protected:
			std::vector<Char*> m_aChars; // List of characters data

			Char *GetChar(const wchar_t chr); // Find character informataion. Create if not found and possible

			virtual Char *CreateChar(const wchar_t chr) = 0; // Create character data

			CBasePlatformFont();
		public:
			PointF getStringSize(const String &str, const float distance) override;
		};
	}
}