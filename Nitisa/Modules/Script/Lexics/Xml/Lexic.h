// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../../Core/Releasable.h"
#include "../../Interfaces/ILexic.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	namespace script
	{
		class IReader;

		namespace xml
		{
			class CLexic :public virtual ILexic, public CReleasable
			{
			private:
				IReader *m_pReader;
			public:
				// ILixic methods
				bool IsSpace(const wchar_t chr) override;
				bool IsNewLine(const wchar_t chr) override;
				bool IsIdentifier(const wchar_t chr) override;
				bool IsIdentifierNotStart(const wchar_t chr) override;
				bool IsIdentifierNotAll(const wchar_t chr) override;
				bool IsIdentifierBoundary(const wchar_t chr) override;
				size_t Escape(const size_t index) override;

				CLexic(IReader *reader);
			};
		}
	}
}