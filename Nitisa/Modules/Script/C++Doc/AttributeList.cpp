// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			CAttributeList::CAttributeList() :
				CReleasable(),
				isAfter{ false },
				isPackExpansion{ false },
				AlignAs{ nullptr, nullptr }
			{

			}

			void CAttributeList::BeforeRelease()
			{
				for (auto attribute : Attributes)
					attribute->Release();
				Attributes.clear();
			}
		
			String CAttributeList::toString() const
			{
				if (AlignAs.Begin)
					return L"alignas(" + AlignAs.toString() + L")";
				String result{ L"[[" };
				if (!Namespace.empty())
					result += L"using " + Namespace + L": ";
				for (size_t i = 0; i < Attributes.size(); i++)
				{
					if (i > 0)
						result += L", ";
					result += Attributes[i]->toString();
				}
				if (isPackExpansion)
					result += L"...";
				result += L"]]";
				return result;
			}

			void CAttributeList::toVariable(Variable &target) const
			{
				if (!AlignAs.Begin)
				{
					target[L"namespace"] = Namespace;
					target[L"is_pack_expansion"] = isPackExpansion;
					for (auto const &attr : Attributes)
					{
						Variable a;
						attr->toVariable(a);
						target[L"attributes"].push_back(a);
					}
				}
				else
					target[L"alignas"] = AlignAs.toStringEx();
			}
		}
	}
}