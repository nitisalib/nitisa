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
			namespace migrations
			{
				using Ref = IDbMigrationKey::RefOption;

				CMigrationV1::CMigrationV1() :
					CDbMigration(L"MigrationV1")
				{

				}

				void CMigrationV1::Run()
				{
					// files
					CreateTable(
						L"files",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"name")->VarChar(255)->NotNull(),
						},
						MigrationKeys{
							Unique(StringArray{ L"version", L"name" }),
						}
					);

					// entities
					CreateTable(
						L"entities",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"parent_id")->Integer()->Unsigned(),
							Column(L"name")->VarChar(255)->NotNull()->Comment(L"Unqualified"),
							Column(L"qualified")->VarChar(255)->NotNull()->Comment(L"Qualified name"),
							Column(L"path")->Json()->NotNull()->Comment(L"Qualified in form of array with added 'id' to those enties that are stored in db"),
							Column(L"type")->Enum(StringArray{
								L"namespace",
								L"namespace_alias",
								L"module",
								L"alias",
								L"typedef",
								L"variable",
								L"const",
								L"interface",
								L"class",
								L"struct",
								L"union",
								L"enum",
								L"enumerator",
								L"function",
								L"parameter",
								L"concept",
							})->NotNull(),
							Column(L"access")->Enum(StringArray{ L"private", L"protected", L"public" }),
							Column(L"language")->VarChar(32),
							Column(L"is_exported")->Boolean()->NotNull(),
							Column(L"file_id")->Integer()->Unsigned(),
						},
						MigrationKeys{
							//Index(L"parent_id", L"idx_parent_id"),
							Index(StringArray{ L"version", L"parent_id" }),
							Index(StringArray{ L"version", L"qualified", L"type" }),
							ForeignKey(L"parent_id", L"entities", L"id", L"fk_entities_to_entities", Ref::Cascade, Ref::Cascade),
						}
					);

					// tags
					CreateTable(
						L"tags",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"name")->VarChar(255)->NotNull(),
							Column(L"options")->Json()->NotNull(),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_tags_to_entities", Ref::Cascade, Ref::Cascade),
						}
					);

					// comments
					CreateTable(
						L"comments",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"comment")->MediumText()->NotNull(),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_comments_to_entities", Ref::Cascade, Ref::Cascade),
						}
					);

					// namespaces
					CreateTable(
						L"namespaces",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"attributes")->Json()->NotNull(),
							Column(L"is_inline")->Boolean()->NotNull(),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_namespaces_to_entities", Ref::Cascade, Ref::Cascade),
						}
					);

					// namespace_aliases
					CreateTable(
						L"namespace_aliases",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"attributes")->Json()->NotNull(),
							Column(L"namespace_name")->VarChar(255)->NotNull(),
							Column(L"namespace_id")->Integer()->Unsigned(),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_namespace_aliases_to_entities", Ref::Cascade, Ref::Cascade),
							ForeignKey(L"namespace_id", L"entities", L"id", L"fk_namespace_aliases_to_namespaces", Ref::Cascade, Ref::Cascade),
						}
					);

					// modules
					CreateTable(
						L"modules",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"attributes")->Json()->NotNull(),
							Column(L"name")->VarChar(255),
							Column(L"partition")->VarChar(255),
							Column(L"is_exported")->Boolean()->NotNull(),
							Column(L"is_private")->Boolean()->NotNull(),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_modules_to_entities", Ref::Cascade, Ref::Cascade),
						}
					);

					// aliases
					CreateTable(
						L"aliases",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"attributes")->Json()->NotNull(),
							Column(L"is_template")->Boolean()->NotNull(),
							Column(L"template_parameters")->Json()->Comment(L"[string, ...]"),
							Column(L"template_requires")->MediumText(),
							Column(L"type_name")->VarChar(255)->NotNull(),
							Column(L"type_id")->Integer()->Unsigned(),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_aliases_to_entities", Ref::Cascade, Ref::Cascade),
							ForeignKey(L"type_id", L"entities", L"id", L"fk_aliases_to_types", Ref::Cascade, Ref::Cascade),
						}
					);

					// typedefs
					CreateTable(
						L"typedefs",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"attributes")->Json()->NotNull(),
							Column(L"is_template")->Boolean()->NotNull(),
							Column(L"template_parameters")->Json()->Comment(L"[string, ...]"),
							Column(L"template_requires")->MediumText(),
							Column(L"declaration")->Json()->NotNull(),
							Column(L"specifier_id")->Integer()->Unsigned(),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_typedefs_to_entities", Ref::Cascade, Ref::Cascade),
						}
					);

					// variables
					CreateTable(
						L"variables",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"attributes")->Json()->NotNull(),
							Column(L"is_template")->Boolean()->NotNull(),
							Column(L"template_parameters")->Json()->Comment(L"[string, ...]"),
							Column(L"template_requires")->MediumText(),
							Column(L"declaration")->Json()->NotNull(),
							Column(L"specifier_id")->Integer()->Unsigned(),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_variables_to_entities", Ref::Cascade, Ref::Cascade),
						}
					);

					// consts
					CreateTable(
						L"consts",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"attributes")->Json()->NotNull(),
							Column(L"is_template")->Boolean()->NotNull(),
							Column(L"template_parameters")->Json()->Comment(L"[string, ...]"),
							Column(L"template_requires")->MediumText(),
							Column(L"declaration")->Json()->NotNull(),
							Column(L"specifier_id")->Integer()->Unsigned(),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_consts_to_entities", Ref::Cascade, Ref::Cascade),
						}
					);

					// interfaces
					CreateTable(
						L"interfaces",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"attributes")->Json()->NotNull(),
							Column(L"is_template")->Boolean()->NotNull(),
							Column(L"template_parameters")->Json()->Comment(L"[string, ...]"),
							Column(L"template_requires")->MediumText(),
							Column(L"is_final")->Boolean()->NotNull(),
							Column(L"is_trivially_relocatable_if_eligible")->Boolean()->NotNull(),
							Column(L"is_replaceable_if_eligible")->Boolean()->NotNull(),
							Column(L"bases")->Json()->Comment(L"Bases data with added 'id' to names if corresponding type is found"),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_interfaces_to_entities", Ref::Cascade, Ref::Cascade),
						}
					);
					
					// classes
					CreateTable(
						L"classes",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"attributes")->Json()->NotNull(),
							Column(L"is_template")->Boolean()->NotNull(),
							Column(L"template_parameters")->Json()->Comment(L"[string, ...]"),
							Column(L"template_requires")->MediumText(),
							Column(L"is_final")->Boolean()->NotNull(),
							Column(L"is_trivially_relocatable_if_eligible")->Boolean()->NotNull(),
							Column(L"is_replaceable_if_eligible")->Boolean()->NotNull(),
							Column(L"bases")->Json()->Comment(L"Bases data with added 'id' to names if corresponding type is found"),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_classes_to_entities", Ref::Cascade, Ref::Cascade),
						}
					);
					
					// structs
					CreateTable(
						L"structs",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"attributes")->Json()->NotNull(),
							Column(L"is_template")->Boolean()->NotNull(),
							Column(L"template_parameters")->Json()->Comment(L"[string, ...]"),
							Column(L"template_requires")->MediumText(),
							Column(L"is_final")->Boolean()->NotNull(),
							Column(L"is_trivially_relocatable_if_eligible")->Boolean()->NotNull(),
							Column(L"is_replaceable_if_eligible")->Boolean()->NotNull(),
							Column(L"bases")->Json()->Comment(L"Bases data with added 'id' to names if corresponding type is found"),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_structs_to_entities", Ref::Cascade, Ref::Cascade),
						}
					);
					
					// unions
					CreateTable(
						L"unions",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"attributes")->Json()->NotNull(),
							Column(L"is_template")->Boolean()->NotNull(),
							Column(L"template_parameters")->Json()->Comment(L"[string, ...]"),
							Column(L"template_requires")->MediumText(),
							Column(L"is_final")->Boolean()->NotNull(),
							Column(L"is_trivially_relocatable_if_eligible")->Boolean()->NotNull(),
							Column(L"is_replaceable_if_eligible")->Boolean()->NotNull(),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_unions_to_entities", Ref::Cascade, Ref::Cascade),
						}
					);

					// enums
					CreateTable(
						L"enums",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"attributes")->Json()->NotNull(),
							Column(L"is_template")->Boolean()->NotNull(),
							Column(L"template_parameters")->Json()->Comment(L"[string, ...]"),
							Column(L"template_requires")->MediumText(),
							Column(L"scope")->Enum(StringArray{ L"class", L"struct" }),
							Column(L"base")->VarChar(255),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_enums_to_entities", Ref::Cascade, Ref::Cascade),
						}
					);

					// enumerators
					CreateTable(
						L"enumerators",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"attributes")->Json()->NotNull(),
							Column(L"name")->VarChar(255)->NotNull(),
							Column(L"value")->VarChar(255),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_enumerators_to_entities", Ref::Cascade, Ref::Cascade),
						}
					);
					
					// functions
					CreateTable(
						L"functions",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"attributes")->Json()->NotNull(),
							Column(L"is_template")->Boolean()->NotNull(),
							Column(L"template_parameters")->Json()->Comment(L"[string, ...]"),
							Column(L"template_requires")->MediumText(),
							Column(L"specifiers")->Json()->Comment(L"Specifiers data with added 'id' to specifiers if corresponding specifier custom type is found"),
							Column(L"specifier_id")->Integer()->Unsigned(),
							Column(L"contracts")->MediumText(),
							Column(L"is_throw")->Boolean()->NotNull(),
							Column(L"throw")->VarChar(255),
							Column(L"is_noexcept")->Boolean()->NotNull(),
							Column(L"noexcept")->VarChar(255),
							Column(L"trailing")->VarChar(255),
							Column(L"requires")->VarChar(255),
							Column(L"is_abstract")->Boolean()->NotNull(),
							Column(L"is_default")->Boolean()->NotNull(),
							Column(L"is_deleted")->Boolean()->NotNull(),
							Column(L"delete_reason")->VarChar(255),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_functions_to_entities", Ref::Cascade, Ref::Cascade),
							ForeignKey(L"specifier_id", L"entities", L"id", L"fk_functions_to_specifiers", Ref::Cascade, Ref::Cascade),
						}
					);

					// parameters
					CreateTable(
						L"parameters",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"attributes")->Json()->NotNull(),
							Column(L"declaration")->Json()->Comment(L"Declaration data with added 'id' to specifiers if corresponding specifier custom type is found"),
							Column(L"specifier_id")->Integer()->Unsigned(),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_parameters_to_entities", Ref::Cascade, Ref::Cascade),
						}
					);
					
					// concepts
					CreateTable(
						L"concepts",
						MigrationColumns{
							Column(L"id")->Integer()->Unsigned()->NotNull()->AutoIncrement()->PrimaryKey(),
							Column(L"version")->VarChar(32)->NotNull(),
							Column(L"entity_id")->Integer()->Unsigned()->NotNull(),
							Column(L"attributes")->Json()->NotNull(),
							Column(L"template_parameters")->Json()->Comment(L"[string, ...]"),
							Column(L"template_requires")->MediumText(),
						},
						MigrationKeys{
							ForeignKey(L"entity_id", L"entities", L"id", L"fk_concepts_to_entities", Ref::Cascade, Ref::Cascade),
						}
					);
				}
			}
		}
	}
}