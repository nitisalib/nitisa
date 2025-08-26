// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Releasable.h"
#include "../../../Core/Strings.h"
#include "../Core/Variable.h"
#include "EntityType.h"
#include <vector>

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			namespace entities
			{
				class CComment;
			}

			class CAttributeList;

			class CEntity: public CReleasable
			{
			public:
				struct Comment
				{
					String Content;
					bool isMultiline;
					bool isAfter;
				};
			protected:
				EntityType m_eType;

				void BeforeRelease() override;

				CEntity(const EntityType &type);

				String toStringPrecedingComments(const String &tabs) const;
				String toStringAttributes(const String &tabs, const bool nl, const bool is_after) const;
				String toStringTrailingComments(const bool nl) const;
				void toVariableAttributesAndComments(Variable &target, const bool attributes, const bool comments) const;
			public:
				EntityType const &Type{ m_eType };

				std::vector<CEntity *> Entities;
				std::vector<CAttributeList *> AttributeLists;
				std::vector<Comment> Comments;

				virtual String toString(const String &tabs, const bool is_last) const = 0;
				virtual void toVariable(Variable &target, const bool attributes, const bool comments) const = 0;
			};
		}
	}
}