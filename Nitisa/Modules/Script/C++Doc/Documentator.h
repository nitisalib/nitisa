// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Aliases.h"
#include "../../../Core/Strings.h"
#include "../../../Db/DbRelation.h"
#include "Models/Tag.h"
#include "Decoder.h"
#include "Identifier.h"
#include "Range.h"
#include "Version.h"
#include <set>
#include <vector>

namespace nitisa
{
	class IErrorListener;
	class IWarningListener;

	namespace script
	{
		class IProgressListener;

		namespace cppdoc
		{
			class CEntity;

			namespace entities
			{
				class CBlock;
				class CClass;
				class CConcept;
				class CEnum;
				class CExport;
				class CFunction;
				class CLanguageLinkage;
				class CModule;
				class CNamespace;
				class CNamespaceAlias;
				class CRoot;
				class CSimpleDeclaration;
				class CTemplate;
				class CTypeAlias;
			}

			/*
			* Supported tags:
			*	module
			*		"@exclude"
			*		"@private"
			*	namespace
			*		"@exclude"
			*		"@private"
			*	namespace-alias
			*		"@exclude"
			*		"@private"
			*		"@qualified quailified-id" - can be used to specify qualified name for aliased namespace
			*	alias
			*		"@exclude"
			*		"@private"
			*		"@qualified quailified-id" - can be used to specify qualified name for aliased type
			*	typedef
			*		"@exclude"
			*		"@private"
			*		"@qualified quailified-id" - can be used to specify qualified name for aliased type
			*	variable/const
			*		"@exclude"
			*		"@private"
			*		"@const"
			*		"@variable"
			*		"@qualified quailified-id" - can be used to specify qualified name for variable/const type
			*	interface/class
			*		"@exclude"
			*		"@private"
			*		"@interface"
			*	struct
			*		"@exclude"
			*		"@private"
			*	interface/class/struct base
			*		"@qualified quailified-id" - can be used to specify qualified name for aliased namespace
			*	union/enum
			*		"@exclude"
			*		"@private"
			*	function
			*		"@exclude"
			*		"@private"
			*		"@param [type] [ [in]/[out]/[inout] ] [$name] [Description]"
			*		"@return [type] [Description]"
			*		"@qualified quailified-id" - can be used to specify qualified name for aliased namespace
			*	function parameter
			*		"@qualified quailified-id" - can be used to specify qualified name for aliased namespace
			*	concept
			*		"@exclude"
			*		"@private"
			* 
			*	All comments can have html tags.
			*/
			class CDocumentator
			{
			public:
				struct Options
				{
					bool IncludePrivateMembers;
					bool IncludeProtectedMembers;
					bool IncludePublicMembers;
					bool IncludePrivateModules;
					bool IncludePublicModules;
					bool IncludePrivateEntities;
					bool IncludePublicEntities;
					bool IncludeWithoutComments;
					bool IIsInterface;
					bool ConstIsConst;
					bool StaticIsConst;
					bool ConstexprIsConst;
					bool ConstinitIsConst;
					String Version;
					String File;
					std::unordered_set<String> NoWarnNamespaces;
					std::unordered_set<String> NoWarnSpecifiers;

					Options();
				};
			private:
				enum class AccessType
				{
					None,
					Private,
					Protected,
					Public
				};

				struct Tag
				{
					String Name;
					StringKeyValueArray Options;
				};

				struct MetaData
				{
					std::vector<Tag> Tags;
					StringArray Comments;

					bool hasTag(const String &name) const;
				};

				struct EntityInfo
				{
					CEntity *Entity; // nullptr for root
					entities::CTemplate *Template;
					MetaData Meta;
					bool Exported;
					String Language;
					String Name;
					AccessType Access;
					std::vector<EntityInfo> Namespaces;
					std::vector<EntityInfo> NamespaceAliases;
					std::vector<EntityInfo> Modules;
					std::vector<EntityInfo> Aliases;
					std::vector<EntityInfo> Typedefs;
					std::vector<EntityInfo> Variables;
					std::vector<EntityInfo> Consts;
					std::vector<EntityInfo> Interfaces;
					std::vector<EntityInfo> Classes;
					std::vector<EntityInfo> Structs;
					std::vector<EntityInfo> Unions;
					std::vector<EntityInfo> Enums;
					std::vector<EntityInfo> Functions;
					std::vector<EntityInfo> Concepts;

					EntityInfo();
					EntityInfo(CEntity *entity, const enum AccessType access);
					EntityInfo(CEntity *entity, const enum AccessType access, const MetaData &meta);

					bool isEmpty() const;
					void Merge(EntityInfo &from);
					void setExported();
					void setLanguage(const String &language);
					void Clear();
				};

				struct PathEntry
				{
					uint Id;
					String Name;
				};

				using Path = std::vector<PathEntry>;
			private:
				IErrorListener *m_pErrorListener;
				IProgressListener *m_pProgressListener;
				IWarningListener *m_pWarningListener;
				bool m_bAborted;
				EntityInfo m_sInfo;
				CDecoder m_cDecoder;

				static const String TAG_EXCLUDE;
				static const String TAG_PRIVATE;
				static const String TAG_CONST;
				static const String TAG_VARIABLE;
				static const String TAG_INTERFACE;
				static const String TAG_PARAM;
				static const String TAG_RETURN;
				static const String TAG_QUALIFIED;

				static const StringArray EXCLUDE_TAGS;

				static const int64 BATCH_SIZE{ 100 };

				MetaData GetEntityMetaData(CEntity *entity, const bool use_prior_comments, const bool use_trail_comments);
				StringKeyValueArray GetTagOptions(const String &tag, const String &options);
				bool GetParamOptions(StringKeyValueArray &result, const String &options);
				bool GetReturnOptions(StringKeyValueArray &result, const String &options);
				bool GetQualifiedOptions(StringKeyValueArray &result, const String &options);
				void AddMetaData(Variable &target, const MetaData &metadata) const;
				void AddAccess(Variable &target, const AccessType &access) const;
				bool ShouldSkip(const MetaData &metadata, const bool check_comments, const Options &options);
				bool CheckDeclaratorName(CEntity *declarator, String &name);
				bool isFunction(CEntity *declarator);
				entities::CFunction *getFunction(CEntity *declarator);
				String PathToString(const Path &path) const;
				String PathToJson(const Path &path) const;
				String AttributesToJson(const CEntity *entity) const;
				String TemplateParametersToString(const entities::CTemplate *temp) const;
				bool GetQualifiedNameFromTags(TDbRelation<models::CTag> &tags, String &name);

				void CollectEntity(EntityInfo &parent, CEntity *entity, const AccessType access, const bool check_comments, const Options &options);
				void CollectModule(EntityInfo &parent, entities::CModule *entity, const AccessType access, const bool check_comments, const Options &options);
				void CollectExport(EntityInfo &parent, entities::CExport *entity, const AccessType access, const bool check_comments, const Options &options);
				void CollectLanguageLinkage(EntityInfo &parent, entities::CLanguageLinkage *entity, const AccessType access, const bool check_comments, const Options &options);
				void CollectBlock(EntityInfo &parent, entities::CBlock *entity, const AccessType access, const bool check_comments, const Options &options);
				void CollectNamespaceAlias(EntityInfo &parent, entities::CNamespaceAlias *entity, const AccessType access, const bool check_comments, const Options &options);
				void CollectNamespace(EntityInfo &parent, entities::CNamespace *entity, const AccessType access, const bool check_comments, const Options &options);
				void CollectTypeAlias(EntityInfo &parent, entities::CTypeAlias *entity, const AccessType access, const bool check_comments, const Options &options);
				void CollectTemplate(EntityInfo &parent, entities::CTemplate *entity, const AccessType access, const bool check_comments, const Options &options);
				void CollectRoot(EntityInfo &parent, entities::CRoot *entity, const AccessType access, const bool check_comments, const Options &options);
				void CollectSimpleDeclaration(EntityInfo &parent, entities::CSimpleDeclaration *entity, const AccessType access, const bool check_comments, const Options &options);
				void CollectClass(EntityInfo &parent, entities::CClass *entity, const AccessType access, const bool check_comments, const Options &options);
				void CollectEnum(EntityInfo &parent, entities::CEnum *entity, const AccessType access, const bool check_comments, const Options &options);
				void CollectFunction(EntityInfo &parent, entities::CSimpleDeclaration *entity, const AccessType access, const bool check_comments, const Options &options);
				void CollectVariable(EntityInfo &parent, entities::CSimpleDeclaration *entity, const AccessType access, const bool check_comments, const Options &options);
				void CollectTypedef(EntityInfo &parent, entities::CSimpleDeclaration *entity, const AccessType access, const bool check_comments, const Options &options);
				void CollectConcept(EntityInfo &parent, entities::CConcept *entity, const AccessType access, const bool check_comments, const Options &options);

				uint SaveToDbFile(const Options &options);
				void SaveToDbMetaData(const uint &entity_id, const MetaData &meta, const String &version);
				void SaveToDbEntities(EntityInfo &info, const Options &options, const Path &path);
				void SaveToDbNamespace(entities::CNamespace *entity, EntityInfo &info, const Options &options, const Path &path);
				void SaveToDbNamespaceAlias(entities::CNamespaceAlias *entity, EntityInfo &info, const Options &options, const Path &path);
				void SaveToDbModule(entities::CModule *entity, EntityInfo &info, const Options &options, const Path &path);
				void SaveToDbAlias(entities::CTypeAlias *entity, EntityInfo &info, const Options &options, const Path &path);
				void SaveToDbTypedef(entities::CSimpleDeclaration *entity, EntityInfo &info, const Options &options, const Path &path);
				void SaveToDbVariable(entities::CSimpleDeclaration *entity, EntityInfo &info, const Options &options, const Path &path);
				void SaveToDbConst(entities::CSimpleDeclaration *entity, EntityInfo &info, const Options &options, const Path &path);
				void SaveToDbInterface(entities::CClass *entity, EntityInfo &info, const Options &options, const Path &path);
				void SaveToDbClass(entities::CClass *entity, EntityInfo &info, const Options &options, const Path &path);
				void SaveToDbStruct(entities::CClass *entity, EntityInfo &info, const Options &options, const Path &path);
				void SaveToDbUnion(entities::CClass *entity, EntityInfo &info, const Options &options, const Path &path);
				void SaveToDbEnum(entities::CEnum *entity, EntityInfo &info, const Options &options, const Path &path);
				void SaveToDbFunction(entities::CSimpleDeclaration *entity, EntityInfo &info, const Options &options, const Path &path);
				void SaveToDbConcept(entities::CConcept *entity, EntityInfo &info, const Options &options, const Path &path);

				void AddIdsToNamespaceAliases(const Options &options);
				void AddIdsToTypedefs(const Options &options);
				void AddIdsToVariables(const Options &options);
				void AddIdsToConsts(const Options &options);
				void AddIdsToInterfaces(const Options &options);
				void AddIdsToClasses(const Options &options);
				void AddIdsToStructs(const Options &options);
				void AddIdsToFunctions(const Options &options);
				void AddIdsToParameters(const Options &options);
				void AddIdsToAliases(const Options &options);
			public:
				bool const &Aborted{ m_bAborted };
				CDecoder *Decoder{ &m_cDecoder };

				CDocumentator(IErrorListener *error_listener = nullptr, IWarningListener *warning_listener = nullptr, IProgressListener *progress_listener = nullptr);

				bool Make(const String &source, const Options &options, String &error);
				bool AddIds(const Options &options, String &error);
			};
		}
	}
}