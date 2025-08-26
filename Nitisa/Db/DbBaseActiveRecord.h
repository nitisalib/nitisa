// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "../Interfaces/IDbActiveRecord.h"
#include "DbActiveRecordPrimaryKey.h"
#include "DbModel.h"
#include "DbSet.h"
#include <vector>

namespace nitisa
{
	class IDbQuery;
	class IDbRelation;

	class CDbCondition;

	class CDbBaseActiveRecord :public virtual IDbActiveRecord, public CDbModel
	{
		friend IDbQuery;
		friend IDbRelation;
	private:
		bool m_bNewRecord;
		DbActiveRecordPrimaryKey m_sPrimaryKey;
		std::vector<IDbRelation *> m_aRelations;

		void Insert();
		void Update();
	protected:
		String m_sTable; // Table in DB this class is supposed to be connected to

		CDbBaseActiveRecord(const String& table); // Constructor specifying table name

		virtual bool BeforeSave(); // Called before saving this model. Return false to prevent saving
		virtual bool BeforeUpdate(); // Called before updating this model data in DB. Return false to prevent updating
		virtual bool BeforeInsert(); // Called before inserting this model data in DB. Return false to prevent inserting
		virtual bool BeforeDelete(); // Called before deleting this model data from DB. Return false to prevent deleting
		virtual void AfterSave(); // Called after successful saving
		virtual void AfterUpdate(); // Called after successful update model data in DB
		virtual void AfterInsert(); // Called after successful insert model data into DB
		virtual void AfterDelete(); // Called after successful deleting model data from DB
	public:
		virtual const String& getTable() const; // Return table name whether this model data is to be stored
		
		// Getters
		bool isNewRecord() const; // Return whether this model is a new one or it is already has data in DB
		bool hasRelation(const String &name) const; // Check whether model has specified relation
		IDbRelation* getRelation(const String &name) const; // Return specified relation
		const DbActiveRecordPrimaryKey& getPrimaryKey() const; // Return model primary key information

		// Setters
		bool setNewRecord(const bool value); // Set whether the model is a new one. Can only set "true" because otherwise assigning primary key value would have been required

		// Methods
		bool LoadDefaultValues(const bool skip_if_set = true); // Load default values from DB
		bool Refresh(); // Refresh attribute values form DB
		bool Delete(); // Delete model data from DB

		// Virtual methods
		virtual bool Save(const bool validate = true, const StringArray& attributes = EmptyStringArray); // Save model to DB (insert or update), with or without validation of attribute values. If validation is requested, additionally attribute names to validated can be specified (otherwise, all attributes will be validated accordingly to added validation rules)
		virtual void AfterLoad(); // Called after model data is loaded from DB
	};
}