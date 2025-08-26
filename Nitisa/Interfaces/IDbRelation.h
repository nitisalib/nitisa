// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "../Interfaces/IDbAttribute.h"
#include "../Db/DbActiveRecordPrimaryKey.h"
#include "../Db/DbBaseActiveRecord.h"
#include "IReleasable.h"
#include <vector>

namespace nitisa
{
	class IDbQuery;

	class IDbRelation : public virtual IReleasable
	{
		friend IDbQuery;
	protected:
		~IDbRelation() = default;
		IDbRelation(const IDbRelation &other) = delete;
		IDbRelation(IDbRelation &&other) = delete;
		IDbRelation &operator=(const IDbRelation &other) = delete;
		IDbRelation &operator=(IDbRelation &&other) = delete;
	protected:
		String m_sName; // Relation name
		CDbBaseActiveRecord *m_pParent; // Parent Active Record model

		virtual void LoadRelations(std::vector<CDbBaseActiveRecord *> &parent_models, std::vector<CDbBaseActiveRecord *> &out_models) = 0; // Load relations

		IDbRelation(const String &name, CDbBaseActiveRecord *parent) :
			m_sName{ name },
			m_pParent{ parent }
		{
			m_pParent->m_aRelations.push_back(this);
		}

		// Following helper methods are used to modify Active Record model
		void setActiveRecordNew(CDbBaseActiveRecord *model, const bool value) const { model->m_bNewRecord = value; }
		void setActiveRecordPrimaryKey(CDbBaseActiveRecord *model, const DbActiveRecordPrimaryKey &value) const { model->m_sPrimaryKey = value; }
		void setAttributeValue(IDbAttribute *attr, const DbValue &value) { attr->SetInternal(value, false); }
	public:
		String const &sName{ m_sName }; // Relation name
	};
}