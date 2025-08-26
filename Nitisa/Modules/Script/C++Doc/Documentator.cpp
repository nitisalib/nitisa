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
			using entities::CArray;
			using entities::CBlock;
			using entities::CClass;
			using entities::CConcept;
			using entities::CEnum;
			using entities::CEnumerator;
			using entities::CExport;
			using entities::CFunction;
			using entities::CFunctionParameter;
			using entities::CIdDeclarator;
			using entities::CLanguageLinkage;
			using entities::CLValueDeclarator;
			using entities::CModule;
			using entities::CNamespace;
			using entities::CNamespaceAlias;
			using entities::CNoPtrDeclarator;
			using entities::CPtrDeclarator;
			using entities::CRoot;
			using entities::CRValueDeclarator;
			using entities::CSimpleDeclaration;
			using entities::CTemplate;
			using entities::CTypeAlias;

		#pragma region Options
			CDocumentator::Options::Options() :
				IncludePrivateMembers{ false },
				IncludeProtectedMembers{ false },
				IncludePublicMembers{ true },
				IncludePrivateModules{ false },
				IncludePublicModules{ true },
				IncludePrivateEntities{ false },
				IncludePublicEntities{ true },
				IncludeWithoutComments{ true },
				IIsInterface{ true },
				ConstIsConst{ true },
				StaticIsConst{ true },
				ConstexprIsConst{ true },
				ConstinitIsConst{ true }
			{

			}
		#pragma endregion

		#pragma region MetaData
			bool CDocumentator::MetaData::hasTag(const String &name) const
			{
				for (auto const &tag : Tags)
					if (tag.Name == name)
						return true;
				return false;
			}
		#pragma endregion

		#pragma region EntityInfo
			CDocumentator::EntityInfo::EntityInfo() :
				Entity{ nullptr },
				Template{ nullptr },
				Exported{ false },
				Access{ AccessType::None }
			{

			}

			CDocumentator::EntityInfo::EntityInfo(CEntity *entity, const enum AccessType access) :
				Entity{ entity },
				Template{ nullptr },
				Exported{ false },
				Access{ access }
			{

			}

			CDocumentator::EntityInfo::EntityInfo(CEntity *entity, const enum AccessType access, const MetaData &meta) :
				Entity{ entity },
				Template{ nullptr },
				Meta{ meta },
				Exported{ false },
				Access{ access }
			{

			}

			bool CDocumentator::EntityInfo::isEmpty() const
			{
				return
					Namespaces.empty() &&
					NamespaceAliases.empty() &&
					Modules.empty() &&
					Aliases.empty() &&
					Typedefs.empty() &&
					Variables.empty() &&
					Consts.empty() &&
					Interfaces.empty() &&
					Classes.empty() &&
					Structs.empty() &&
					Unions.empty() &&
					Enums.empty() &&
					Functions.empty() &&
					Concepts.empty();
			}

			void CDocumentator::EntityInfo::Merge(EntityInfo &from)
			{
				Namespaces.insert(Namespaces.end(), from.Namespaces.begin(), from.Namespaces.end());
				NamespaceAliases.insert(NamespaceAliases.end(), from.NamespaceAliases.begin(), from.NamespaceAliases.end());
				Modules.insert(Modules.end(), from.Modules.begin(), from.Modules.end());
				Aliases.insert(Aliases.end(), from.Aliases.begin(), from.Aliases.end());
				Typedefs.insert(Typedefs.end(), from.Typedefs.begin(), from.Typedefs.end());
				Variables.insert(Variables.end(), from.Variables.begin(), from.Variables.end());
				Consts.insert(Consts.end(), from.Consts.begin(), from.Consts.end());
				Interfaces.insert(Interfaces.end(), from.Interfaces.begin(), from.Interfaces.end());
				Classes.insert(Classes.end(), from.Classes.begin(), from.Classes.end());
				Structs.insert(Structs.end(), from.Structs.begin(), from.Structs.end());
				Unions.insert(Unions.end(), from.Unions.begin(), from.Unions.end());
				Enums.insert(Enums.end(), from.Enums.begin(), from.Enums.end());
				Functions.insert(Functions.end(), from.Functions.begin(), from.Functions.end());
				Concepts.insert(Concepts.end(), from.Concepts.begin(), from.Concepts.end());
			}

			void CDocumentator::EntityInfo::setExported()
			{
				for (auto &e : Namespaces)
					e.Exported = true;
				for (auto &e : NamespaceAliases)
					e.Exported = true;
				for (auto &e : Modules)
					e.Exported = true;
				for (auto &e : Aliases)
					e.Exported = true;
				for (auto &e : Typedefs)
					e.Exported = true;
				for (auto &e : Variables)
					e.Exported = true;
				for (auto &e : Consts)
					e.Exported = true;
				for (auto &e : Interfaces)
					e.Exported = true;
				for (auto &e : Classes)
					e.Exported = true;
				for (auto &e : Structs)
					e.Exported = true;
				for (auto &e : Unions)
					e.Exported = true;
				for (auto &e : Enums)
					e.Exported = true;
				for (auto &e : Functions)
					e.Exported = true;
				for (auto &e : Concepts)
					e.Exported = true;
			}

			void CDocumentator::EntityInfo::setLanguage(const String &language)
			{
				for (auto &e : Namespaces)
					e.Language = language;
				for (auto &e : NamespaceAliases)
					e.Language = language;
				for (auto &e : Modules)
					e.Language = language;
				for (auto &e : Aliases)
					e.Language = language;
				for (auto &e : Typedefs)
					e.Language = language;
				for (auto &e : Variables)
					e.Language = language;
				for (auto &e : Consts)
					e.Language = language;
				for (auto &e : Interfaces)
					e.Language = language;
				for (auto &e : Classes)
					e.Language = language;
				for (auto &e : Structs)
					e.Language = language;
				for (auto &e : Unions)
					e.Language = language;
				for (auto &e : Enums)
					e.Language = language;
				for (auto &e : Functions)
					e.Language = language;
				for (auto &e : Concepts)
					e.Language = language;
			}

			void CDocumentator::EntityInfo::Clear()
			{
				Entity = nullptr;
				Template = nullptr;
				Meta.Tags.clear();
				Meta.Comments.clear();
				Exported = false;
				Language = L"";
				Name = L"";
				Access = AccessType::None;
				Namespaces.clear();
				NamespaceAliases.clear();
				Modules.clear();
				Aliases.clear();
				Typedefs.clear();
				Variables.clear();
				Consts.clear();
				Interfaces.clear();
				Classes.clear();
				Structs.clear();
				Unions.clear();
				Enums.clear();
				Functions.clear();
				Concepts.clear();
			}
		#pragma endregion

		#pragma region Constants
			const String CDocumentator::TAG_EXCLUDE{ L"exclude" };
			const String CDocumentator::TAG_PRIVATE{ L"private" };
			const String CDocumentator::TAG_CONST{ L"const" };
			const String CDocumentator::TAG_VARIABLE{ L"variable" };
			const String CDocumentator::TAG_INTERFACE{ L"interface" };
			const String CDocumentator::TAG_PARAM{ L"param" };
			const String CDocumentator::TAG_RETURN{ L"return" };
			const String CDocumentator::TAG_QUALIFIED{ L"qualified" };

			const StringArray CDocumentator::EXCLUDE_TAGS{ L"exclude", L"private", L"const", L"variable", L"interface" };
		#pragma endregion

		#pragma region Constructor & destructor
			CDocumentator::CDocumentator(IErrorListener *error_listener, IWarningListener *warning_listener, IProgressListener *progress_listener) :
				m_pErrorListener{ error_listener },
				m_pProgressListener{ progress_listener },
				m_pWarningListener{ warning_listener },
				m_bAborted{ false },
				m_cDecoder{ error_listener }
			{

			}
		#pragma endregion

		#pragma region Helpers
			CDocumentator::MetaData CDocumentator::GetEntityMetaData(CEntity *entity, const bool use_prior_comments, const bool use_trail_comments)
			{
				MetaData result;
				StringArray lines;
				for (auto comment : entity->Comments)
				{
					if (comment.isAfter && !use_trail_comments)
						continue;
					if (!comment.isAfter && !use_prior_comments)
						continue;
					if (comment.isMultiline)
					{
						String content{ Trim(ReplaceAll(comment.Content, L"\t", L"")) };
						ReplaceAllDirect(content, L"\r\n", L"\n");
						ReplaceAllDirect(content, L"\r", L"\n");
						size_t l{ content.length() };
						while (true)
						{
							ReplaceAllDirect(content, L"\n\n", L"\n");
							if (content.length() == l)
								break;
							l = content.length();
						}
						lines = Explode(content, L"\n");
						for (auto &line : lines)
						{
							TrimDirect(line);
							if (!line.empty() && line[0] == L'*')
							{
								line.erase(line.begin());
								TrimDirect(line);
							}
						}
					}
					else
						lines.push_back(Trim(comment.Content));
				}
				for (auto line : lines)
				{
					if (line.empty())
						continue;
					if (line[0] != L'@' || line.length() < 2 || line[1] == L'@')
					{
						result.Comments.push_back(line);
						continue;
					}
					size_t space_index{ line.find(L' ') };
					if (space_index != String::npos)
					{
						String tag{ line.substr(1, space_index - 1) };
						String options{ line.substr(space_index + 1) };
						result.Tags.push_back(Tag{ tag, GetTagOptions(tag, options) });
					}
					else
						result.Tags.push_back(Tag{ line.substr(1), EmptyStringKeyValueArray });
				}
				return result;
			}

			StringKeyValueArray CDocumentator::GetTagOptions(const String &tag, const String &options)
			{
				if (tag == TAG_PARAM)
				{
					StringKeyValueArray result;
					if (GetParamOptions(result, options))
						return result;
				}
				if (tag == TAG_RETURN)
				{
					StringKeyValueArray result;
					if (GetReturnOptions(result, options))
						return result;
				}
				if (tag == TAG_QUALIFIED)
				{
					StringKeyValueArray result;
					if (GetQualifiedOptions(result, options))
						return result;
				}

				return StringKeyValueArray{ StringKeyValue{ L"options", options } };
			}

			bool CDocumentator::GetParamOptions(StringKeyValueArray &result, const String &options)
			{
				bool has_type{ false }, has_inout{ false }, has_name{ false }, has_error{ false };
				size_t type_start{ String::npos }, type_end{ String::npos }, i{ 0 };
				while (i < options.length())
				{
					// [in]/[out]/[inout]
					if (options[i] == L'[')
					{
						if (has_inout || has_name)
						{
							has_error = true;
							break;
						}
						if (has_type && type_end == String::npos)
							type_end = i - 1;
						if (options.substr(i, 4) == L"[in]")
						{
							i += 4;
							if (i < options.length())
							{
								if (options[i] != L' ')
								{
									has_error = true;
									break;
								}
								i++;
							}
							result.push_back(StringKeyValue{ L"direction", L"in" });
						}
						else if (options.substr(i, 5) == L"[out]")
						{
							i += 5;
							if (i < options.length())
							{
								if (options[i] != L' ')
								{
									has_error = true;
									break;
								}
								i++;
							}
							result.push_back(StringKeyValue{ L"direction", L"out" });
						}
						else if (options.substr(i, 7) == L"[inout]")
						{
							i += 7;
							if (i < options.length())
							{
								if (options[i] != L' ')
								{
									has_error = true;
									break;
								}
								i++;
							}
							result.push_back(StringKeyValue{ L"direction", L"inout" });
						}
						else
						{
							has_error = true;
							break;
						}
						has_inout = true;
						continue;
					}
					// $name
					if (options[i] == L'$')
					{
						if (has_type && type_end == String::npos)
							type_end = i - 1;
						size_t space{ options.find(L' ', i) };
						if (space == String::npos)
						{
							result.push_back(StringKeyValue{ L"name", options.substr(i + 1) });
							break;
						}
						result.push_back(StringKeyValue{ L"name", options.substr(i + 1, space - i - 1) });
						i = space + 1;
						has_name = true;
						continue;
					}
					// Description
					if (std::isupper(options[i]))
					{
						if (has_type && type_end == String::npos)
							type_end = i - 1;
						result.push_back(StringKeyValue{ L"description", options.substr(i) });
						break;
					}
					// type
					if (has_name)
					{
						has_error = true;
						break;
					}
					if (!has_type)
					{
						type_start = i;
						has_type = true;
					}
					i++;
				}
				if (has_error)
					return false;
				if (has_type)
					result.push_back(StringKeyValue{ L"type", Trim(options.substr(type_start, type_end - type_start)) });
				return true;
			}

			bool CDocumentator::GetReturnOptions(StringKeyValueArray &result, const String &options)
			{
				bool has_type{ false }, has_error{ false };
				size_t type_start{ String::npos }, type_end{ String::npos }, i{ 0 };
				while (i < options.length())
				{
					// Description
					if (std::isupper(options[i]))
					{
						if (has_type && type_end == String::npos)
							type_end = i - 1;
						result.push_back(StringKeyValue{ L"description", options.substr(i) });
						break;
					}
					// type
					if (!has_type)
					{

						type_start = i;
						has_type = true;
					}
					i++;
				}
				if (has_error)
					return false;
				if (has_type)
					result.push_back(StringKeyValue{ L"type", Trim(options.substr(type_start, type_end - type_start)) });
				return true;
			}

			bool CDocumentator::GetQualifiedOptions(StringKeyValueArray &result, const String &options)
			{
				result = StringKeyValueArray{ StringKeyValue{ L"name", options} };
				return true;
			}

			void CDocumentator::AddMetaData(Variable &target, const MetaData &metadata) const
			{
				for (auto const &tag : metadata.Tags)
				{
					Variable t;
					t[L"name"] = tag.Name;
					for (auto const &option : tag.Options)
					{
						Variable o;
						o[L"name"] = option.first;
						o[L"value"] = option.second;
						t[L"options"].push_back(o);
					}
					target[L"metadata"][L"tags"].push_back(t);
				}
				for (auto &comment : metadata.Comments)
					target[L"metadata"][L"comments"].push_back(comment);
			}

			void CDocumentator::AddAccess(Variable &target, const AccessType &access) const
			{
				switch (access)
				{
				case AccessType::Private:
					target[L"access"] = L"private";
					break;
				case AccessType::Protected:
					target[L"access"] = L"protected";
					break;
				case AccessType::Public:
					target[L"access"] = L"public";
					break;
				default:
					break;
				}
			}

			bool CDocumentator::ShouldSkip(const MetaData &metadata, const bool check_comments, const Options &options)
			{
				if (check_comments && !options.IncludeWithoutComments && metadata.Comments.empty())
					return true;
				if (metadata.hasTag(TAG_EXCLUDE))
					return true;
				if (!options.IncludePrivateEntities && metadata.hasTag(TAG_PRIVATE))
					return true;
				return false;
			}

			bool CDocumentator::CheckDeclaratorName(CEntity *declarator, String &name)
			{
				while (declarator)
				{
					if (declarator->Type == EntityType::IdDeclarator)
					{
						CIdDeclarator *d{ cast<CIdDeclarator *>(declarator) };
						if (d->Declarator)
						{
							declarator = d->Declarator;
							continue;
						}
						if (d->Identifier.Names.size() == 1)
						{
							name = L"";
							if (d->Identifier.Destructor)
								name = L"~";
							name += d->Identifier.Names[0].Name;
							if (d->Identifier.UserDefinedOperator)
								name += L" \"\"" + d->Identifier.Operator;
							else if (!d->Identifier.Operator.empty())
								name += L" " + d->Identifier.Operator;
							return true;
						}
						break;
					}
					if (declarator->Type == EntityType::LValueDeclarator)
					{
						CLValueDeclarator *d{ cast<CLValueDeclarator *>(declarator) };
						declarator = d->Declarator;
						continue;
					}
					if (declarator->Type == EntityType::RValueDeclarator)
					{
						CRValueDeclarator *d{ cast<CRValueDeclarator *>(declarator) };
						declarator = d->Declarator;
						continue;
					}
					if (declarator->Type == EntityType::NoPtrDeclarator)
					{
						CNoPtrDeclarator *d{ cast<CNoPtrDeclarator *>(declarator) };
						declarator = d->Declarator;
						continue;
					}
					if (declarator->Type == EntityType::PtrDeclarator)
					{
						CPtrDeclarator *d{ cast<CPtrDeclarator *>(declarator) };
						declarator = d->Declarator;
						continue;
					}
					if (declarator->Type == EntityType::Function)
					{
						CFunction *d{ cast<CFunction *>(declarator) };
						declarator = d->Declarator;
						continue;
					}
					if (declarator->Type == EntityType::Array)
					{
						CArray *d{ cast<CArray *>(declarator) };
						declarator = d->Declarator;
						continue;
					}
					break;
				}
				return false;
			}

			bool CDocumentator::isFunction(CEntity *declarator)
			{
				while (declarator)
				{
					if (declarator->Type == EntityType::LValueDeclarator)
					{
						CLValueDeclarator *d{ cast<CLValueDeclarator *>(declarator) };
						declarator = d->Declarator;
						continue;
					}
					if (declarator->Type == EntityType::RValueDeclarator)
					{
						CRValueDeclarator *d{ cast<CRValueDeclarator *>(declarator) };
						declarator = d->Declarator;
						continue;
					}
					if (declarator->Type == EntityType::PtrDeclarator)
					{
						CPtrDeclarator *d{ cast<CPtrDeclarator *>(declarator) };
						declarator = d->Declarator;
						continue;
					}
					if (declarator->Type == EntityType::Function)
					{
						CFunction *d{ cast<CFunction *>(declarator) };
						if (!d->Declarator)
							return false;
						if (!in(d->Declarator->Type, { EntityType::IdDeclarator, EntityType::LValueDeclarator, EntityType::RValueDeclarator, EntityType::PtrDeclarator }))
							return false;
						return true;
					}
					break;
				}
				return false;
			}

			CFunction *CDocumentator::getFunction(CEntity *declarator)
			{
				while (declarator)
				{
					if (declarator->Type == EntityType::LValueDeclarator)
					{
						CLValueDeclarator *d{ cast<CLValueDeclarator *>(declarator) };
						declarator = d->Declarator;
						continue;
					}
					if (declarator->Type == EntityType::RValueDeclarator)
					{
						CRValueDeclarator *d{ cast<CRValueDeclarator *>(declarator) };
						declarator = d->Declarator;
						continue;
					}
					if (declarator->Type == EntityType::PtrDeclarator)
					{
						CPtrDeclarator *d{ cast<CPtrDeclarator *>(declarator) };
						declarator = d->Declarator;
						continue;
					}
					if (declarator->Type == EntityType::Function)
						return cast<CFunction*>(declarator);
					break;
				}
				return nullptr;
			}

			String CDocumentator::PathToString(const Path &path) const
			{
				String result;
				for (auto const &p : path)
					result += p.Name + L"::";
				return result;
			}

			String CDocumentator::PathToJson(const Path &path) const
			{
				if (path.empty())
					return L"[]";
				Variable v;
				for (auto const &p : path)
				{
					Variable t;
					t[L"name"] = p.Name;
					t[L"id"] = (int64)p.Id;
					v.push_back(t);
				}
				return json::Encoder::Encode(v);
			}

			String CDocumentator::AttributesToJson(const CEntity *entity) const
			{
				if (entity->AttributeLists.empty())
					return L"[]";
				Variable v;
				for (auto const &a : entity->AttributeLists)
				{
					Variable t;
					a->toVariable(t);
					v.push_back(t);
				}
				return json::Encoder::Encode(v);
			}

			String CDocumentator::TemplateParametersToString(const CTemplate *temp) const
			{
				Variable v{ VariableType::Array };
				for (auto const &p : temp->Parameters)
					v.push_back(p.toStringEx());
				return json::Encoder::Encode(v);
			}

			bool CDocumentator::GetQualifiedNameFromTags(TDbRelation<models::CTag> &tags, String &name)
			{
				for (auto tag : tags)
				{
					if (String(tag->Name) != TAG_QUALIFIED)
						continue;
					Variable options;
					if (!json::Decoder::Decode(tag->Options, options))
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ErrorInfo{ 0, L"Cannot decode Options of tag #{id}" },
								E(L"{id}", ToString((uint)tag->Id))
							);
						}
						return false;
					}
					if (options.type() != VariableType::Array || options.size() != 1)
					{
						if (m_pErrorListener)
						{
							m_pErrorListener->NotifyOnError(
								__FUNCTION__,
								__LINE__,
								ErrorInfo{ 0, L"Invalid Options of tag #{id}" },
								E(L"{id}", ToString((uint)tag->Id))
							);
						}
						return false;
					}
					name = String(options[(size_t)0][L"name"]);
					return true;
				}
				return false;
			}
		#pragma endregion

		#pragma region Collecting entities
			void CDocumentator::CollectEntity(EntityInfo &parent, CEntity *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				if (m_pProgressListener)
				{
					m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
					if (m_bAborted)
						return;
				}
				switch (entity->Type)
				{
				case EntityType::Root:
					CollectRoot(parent, cast<CRoot *>(entity), access, check_comments, options);
					break;
				case EntityType::Module:
					CollectModule(parent, cast<CModule *>(entity), access, check_comments, options);
					break;
				case EntityType::Export:
					CollectExport(parent, cast<CExport *>(entity), access, check_comments, options);
					break;
				case EntityType::LanguageLinkage:
					CollectLanguageLinkage(parent, cast<CLanguageLinkage *>(entity), access, check_comments, options);
					break;
				case EntityType::Block:
					CollectBlock(parent, cast<CBlock *>(entity), access, check_comments, options);
					break;
				case EntityType::NamespaceAlias:
					CollectNamespaceAlias(parent, cast<CNamespaceAlias *>(entity), access, check_comments, options);
					break;
				case EntityType::Namespace:
					CollectNamespace(parent, cast<CNamespace *>(entity), access, check_comments, options);
					break;
				case EntityType::TypeAlias:
					CollectTypeAlias(parent, cast<CTypeAlias *>(entity), access, check_comments, options);
					break;
				case EntityType::Template:
					CollectTemplate(parent, cast<CTemplate *>(entity), access, check_comments, options);
					break;
				case EntityType::SimpleDeclaration:
					CollectSimpleDeclaration(parent, cast<CSimpleDeclaration *>(entity), access, check_comments, options);
					break;
				case EntityType::Concept:
					CollectConcept(parent, cast<CConcept *>(entity), access, check_comments, options);
					break;
				default:
					break;
				}
			}

			void CDocumentator::CollectModule(EntityInfo &parent, entities::CModule *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				if (entity->isPrivate && !options.IncludePrivateModules)
					return;
				if (!entity->isPrivate && !options.IncludePublicModules)
					return;
				EntityInfo info{ entity, AccessType::None, GetEntityMetaData(entity, true, true) };
				if (ShouldSkip(info.Meta, true, options))
					return;
				for (auto &search : parent.Modules)
				{
					CModule *m{ cast<CModule *>(search.Entity) };
					if (m->isPrivate != entity->isPrivate || m->isExport != entity->isExport || m->Name != entity->Name || m->Partition != entity->Partition)
						continue;
					/*if (m_pWarningListener)
						m_pWarningListener->NotifyOnWarning("", 0, ErrorInfo{ 0, L"Found module '{name}'" }, E(L"{name}", entity->Name + entity->Partition));*/
					for (auto e : entity->Entities)
						CollectEntity(search, e, AccessType::None, true, options);
					search.Merge(info);
					return;
				}
				info.Name = entity->Name + entity->Partition;
				/*if (m_pWarningListener)
					m_pWarningListener->NotifyOnWarning("", 0, ErrorInfo{ 0, L"Found module '{name}'" }, StringKeyValueArray{ StringKeyValue{ L"{name}", info.Name } });*/
				for (auto e : entity->Entities)
					CollectEntity(info, e, AccessType::None, true, options);
				parent.Modules.push_back(info);
			}

			void CDocumentator::CollectExport(EntityInfo &parent, entities::CExport *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				EntityInfo info{ entity, access, GetEntityMetaData(entity, true, true) };
				if (ShouldSkip(info.Meta, entity->Entities[0]->Type != EntityType::Block, options))
					return;
				CollectEntity(info, entity->Entities[0], access, entity->Entities[0]->Type == EntityType::Block, options);
				if (info.isEmpty())
					return;
				info.setExported();
				parent.Merge(info);
			}

			void CDocumentator::CollectLanguageLinkage(EntityInfo &parent, entities::CLanguageLinkage *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				EntityInfo info{ entity, access, GetEntityMetaData(entity, true, true) };
				if (ShouldSkip(info.Meta, entity->Entities[0]->Type != EntityType::Block, options))
					return;
				CollectEntity(info, entity->Entities[0], access, entity->Entities[0]->Type == EntityType::Block, options);
				if (info.isEmpty())
					return;
				info.setLanguage(entity->Name);
				parent.Merge(info);
			}

			void CDocumentator::CollectBlock(EntityInfo &parent, entities::CBlock *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				for (auto e : entity->Entities)
					CollectEntity(parent, e, access, check_comments, options);
			}

			void CDocumentator::CollectNamespaceAlias(EntityInfo &parent, entities::CNamespaceAlias *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				EntityInfo info{ entity, access, GetEntityMetaData(entity, true, true) };
				if (ShouldSkip(info.Meta, check_comments, options))
					return;
				info.Name = entity->Alias;
				/*if (m_pWarningListener)
					m_pWarningListener->NotifyOnWarning("", 0, ErrorInfo{ 0, L"Found namespace alias '{name}'" }, StringKeyValueArray{ StringKeyValue{ L"{name}", info.Name } });*/
				parent.NamespaceAliases.push_back(info);
			}

			void CDocumentator::CollectNamespace(EntityInfo &parent, entities::CNamespace *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				EntityInfo info{ entity, access, GetEntityMetaData(entity, true, true) };
				if (ShouldSkip(info.Meta, check_comments, options))
					return;
				for (auto &search : parent.Namespaces)
				{
					CNamespace *n{ cast<CNamespace *>(search.Entity) };
					if (n->isInline != entity->isInline || n->Name != entity->Name)
						continue;
					/*if (m_pWarningListener)
						m_pWarningListener->NotifyOnWarning("", 0, ErrorInfo{ 0, L"Found namespace '{name}'" }, StringKeyValueArray{ StringKeyValue{ L"{name}", entity->Name } });*/
					CollectEntity(search, entity->Entities[0], AccessType::None, true, options);
					search.Merge(info);
					return;
				}
				info.Name = entity->Name;
				/*if (m_pWarningListener)
					m_pWarningListener->NotifyOnWarning("", 0, ErrorInfo{ 0, L"Found namespace '{name}'" }, StringKeyValueArray{ StringKeyValue{ L"{name}", info.Name } });*/
				CollectEntity(info, entity->Entities[0], AccessType::None, true, options);
				parent.Namespaces.push_back(info);
			}

			void CDocumentator::CollectTypeAlias(EntityInfo &parent, entities::CTypeAlias *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				EntityInfo info{ entity, access, GetEntityMetaData(entity, true, true) };
				if (ShouldSkip(info.Meta, check_comments, options))
					return;
				info.Name = entity->Alias;
				/*if (m_pWarningListener)
					m_pWarningListener->NotifyOnWarning("", 0, ErrorInfo{ 0, L"Found type alias '{name}'" }, StringKeyValueArray{ StringKeyValue{ L"{name}", info.Name } });*/
				parent.Aliases.push_back(info);
			}

			void CDocumentator::CollectTemplate(EntityInfo &parent, entities::CTemplate *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				if (!in(entity->Entities[0]->Type, { EntityType::NamespaceAlias, EntityType::TypeAlias, EntityType::Template, EntityType::SimpleDeclaration }))
					return;
				EntityInfo info{ entity, access, GetEntityMetaData(entity, true, true) };
				if (ShouldSkip(info.Meta, check_comments, options))
					return;
				CollectEntity(info, entity->Entities[0], AccessType::None, false, options);
				if (info.isEmpty())
					return;
				if (!info.Aliases.empty())
				{
					info.Aliases[0].Template = entity;
					info.Aliases[0].Meta = info.Meta;
				}
				else if (!info.Typedefs.empty())
				{
					info.Typedefs[0].Template = entity;
					info.Typedefs[0].Meta = info.Meta;
				}
				else if (!info.Consts.empty())
				{
					info.Consts[0].Template = entity;
					info.Consts[0].Meta = info.Meta;
				}
				else if (!info.Interfaces.empty())
				{
					info.Interfaces[0].Template = entity;
					info.Interfaces[0].Meta = info.Meta;
				}
				else if (!info.Classes.empty())
				{
					info.Classes[0].Template = entity;
					info.Classes[0].Meta = info.Meta;
				}
				else if (!info.Structs.empty())
				{
					info.Structs[0].Template = entity;
					info.Structs[0].Meta = info.Meta;
				}
				else if (!info.Unions.empty())
				{
					info.Unions[0].Template = entity;
					info.Unions[0].Meta = info.Meta;
				}
				else if (!info.Enums.empty())
				{
					info.Enums[0].Template = entity;
					info.Enums[0].Meta = info.Meta;
				}
				else if (!info.Functions.empty())
				{
					info.Functions[0].Template = entity;
					info.Functions[0].Meta = info.Meta;
				}
				else if (!info.Concepts.empty())
				{
					info.Concepts[0].Template = entity;
					info.Concepts[0].Meta = info.Meta;
				}
				else
					return;
				parent.Merge(info);
			}

			void CDocumentator::CollectRoot(EntityInfo &parent, entities::CRoot *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				for (auto e : entity->Entities)
					CollectEntity(parent, e, AccessType::None, true, options);
			}

			void CDocumentator::CollectSimpleDeclaration(EntityInfo &parent, entities::CSimpleDeclaration *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				// class/struct/union/enum
				if (entity->Declarators.empty() && entity->Specifiers.size() == 1)
				{
					if (entity->Specifiers[0]->Type == EntityType::Class)
					{
						CollectClass(parent, cast<CClass *>(entity->Specifiers[0]), access, check_comments, options);
						return;
					}
					if (entity->Specifiers[0]->Type == EntityType::Enum)
					{
						CollectEnum(parent, cast<CEnum *>(entity->Specifiers[0]), access, check_comments, options);
						return;
					}
				}
				// Skip if class/enum has body
				for (auto specifier : entity->Specifiers)
				{
					if (specifier->Type == EntityType::Class && !cast<CClass *>(specifier)->isForward)
						return;
					if (specifier->Type == EntityType::Enum && !cast<CEnum *>(specifier)->isOpaque)
						return;
				}
				// Only 1 declarator can be documented
				if (entity->Declarators.size() != 1)
					return;
				// function
				if (isFunction(entity->Declarators[0]))
				{
					CollectFunction(parent, entity, access, check_comments, options);
					return;
				}
				// typedef
				for (auto specifier : entity->Specifiers)
					if (specifier->Type == EntityType::Typedef)
					{
						CollectTypedef(parent, entity, access, check_comments, options);
						return;
					}
				// array/typedef/variables
				CollectVariable(parent, entity, access, check_comments, options);
			}

			void CDocumentator::CollectClass(EntityInfo &parent, entities::CClass *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				if (entity->isForward || entity->Identifier.Names.size() != 1)
					return;
				EntityInfo info{ entity, access, GetEntityMetaData(entity, true, true) };
				if (ShouldSkip(info.Meta, check_comments, options))
					return;
				info.Name = entity->Identifier.Names[0].Name;
				/*if (m_pWarningListener)
					m_pWarningListener->NotifyOnWarning("", 0, ErrorInfo{ 0, L"Found class '{name}'" }, StringKeyValueArray{ StringKeyValue{ L"{name}", info.Name } });*/
				AccessType t_access{ (entity->ClassType == CClass::ClassType::Class) ? AccessType::Private : AccessType::Public };
				for (auto e : entity->Entities)
				{
					if (e->Type == EntityType::Private)
					{
						t_access = AccessType::Private;
						continue;
					}
					if (e->Type == EntityType::Protected)
					{
						t_access = AccessType::Protected;
						continue;
					}
					if (e->Type == EntityType::Public)
					{
						t_access = AccessType::Public;
						continue;
					}
					if (t_access == AccessType::Private && !options.IncludePrivateMembers)
						continue;
					if (t_access == AccessType::Protected && !options.IncludeProtectedMembers)
						continue;
					if (t_access == AccessType::Public && !options.IncludePublicMembers)
						continue;
					CollectEntity(info, e, t_access, true, options);
				}
				if (entity->ClassType == CClass::ClassType::Struct)
					parent.Structs.push_back(info);
				else if (entity->ClassType == CClass::ClassType::Union)
					parent.Unions.push_back(info);
				else
				{
					if ((options.IIsInterface && info.Name[0] == L'I') || info.Meta.hasTag(TAG_INTERFACE))
						parent.Interfaces.push_back(info);
					else
						parent.Classes.push_back(info);
				}
			}

			void CDocumentator::CollectEnum(EntityInfo &parent, entities::CEnum *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				if (entity->isOpaque || entity->Identifier.Names.size() != 1)
					return;
				EntityInfo info{ entity, access, GetEntityMetaData(entity, true, true) };
				if (ShouldSkip(info.Meta, check_comments, options))
					return;
				info.Name = entity->Identifier.Names[0].Name;
				/*if (m_pWarningListener)
					m_pWarningListener->NotifyOnWarning("", 0, ErrorInfo{ 0, L"Found enum '{name}'" }, StringKeyValueArray{ StringKeyValue{ L"{name}", info.Name } });*/
				parent.Enums.push_back(info);
			}

			void CDocumentator::CollectFunction(EntityInfo &parent, entities::CSimpleDeclaration *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				EntityInfo info{ entity, access, GetEntityMetaData(entity, true, true) };
				if (ShouldSkip(info.Meta, check_comments, options))
					return;
				if (!CheckDeclaratorName(entity->Declarators[0], info.Name))
					return;
				/*if (m_pWarningListener)
					m_pWarningListener->NotifyOnWarning("", 0, ErrorInfo{ 0, L"Found function '{name}'" }, StringKeyValueArray{ StringKeyValue{ L"{name}", info.Name } });*/
				parent.Functions.push_back(info);
			}

			void CDocumentator::CollectVariable(EntityInfo &parent, entities::CSimpleDeclaration *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				EntityInfo info{ entity, access, GetEntityMetaData(entity, true, true) };
				if (ShouldSkip(info.Meta, check_comments, options))
					return;
				if (!CheckDeclaratorName(entity->Declarators[0], info.Name))
					return;
				/*if (m_pWarningListener)
					m_pWarningListener->NotifyOnWarning("", 0, ErrorInfo{ 0, L"Found variable '{name}'" }, StringKeyValueArray{ StringKeyValue{ L"{name}", info.Name } });*/
				bool is_const{ false };
				if (!info.Meta.hasTag(TAG_VARIABLE))
				{
					if (info.Meta.hasTag(TAG_CONST))
						is_const = true;
					else
					{
						for (auto specifier : entity->Specifiers)
						{
							if (options.ConstIsConst && specifier->Type == EntityType::Const)
							{
								is_const = true;
								break;
							}
							if (options.StaticIsConst && specifier->Type == EntityType::Static)
							{
								is_const = true;
								break;
							}
							if (options.ConstexprIsConst && specifier->Type == EntityType::Constexpr)
							{
								is_const = true;
								break;
							}
							if (options.ConstinitIsConst && specifier->Type == EntityType::Constinit)
							{
								is_const = true;
								break;
							}
						}
					}
				}
				if (is_const)
					parent.Consts.push_back(info);
				else
					parent.Variables.push_back(info);
			}

			void CDocumentator::CollectTypedef(EntityInfo &parent, entities::CSimpleDeclaration *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				EntityInfo info{ entity, access, GetEntityMetaData(entity, true, true) };
				if (ShouldSkip(info.Meta, check_comments, options))
					return;
				if (!CheckDeclaratorName(entity->Declarators[0], info.Name))
					return;
				/*if (m_pWarningListener)
					m_pWarningListener->NotifyOnWarning("", 0, ErrorInfo{ 0, L"Found typedef '{name}'" }, StringKeyValueArray{ StringKeyValue{ L"{name}", info.Name } });*/
				parent.Typedefs.push_back(info);
			}

			void CDocumentator::CollectConcept(EntityInfo &parent, entities::CConcept *entity, const AccessType access, const bool check_comments, const Options &options)
			{
				EntityInfo info{ entity, access, GetEntityMetaData(entity, true, true) };
				if (ShouldSkip(info.Meta, check_comments, options))
					return;
				info.Name = entity->Name;
				/*if (m_pWarningListener)
					m_pWarningListener->NotifyOnWarning("", 0, ErrorInfo{ 0, L"Found concept '{name}'" }, StringKeyValueArray{ StringKeyValue{ L"{name}", info.Name } });*/
				parent.Concepts.push_back(info);
			}
		#pragma endregion

		#pragma region Processing
			bool CDocumentator::Make(const String &source, const Options &options, String &error)
			{
				m_bAborted = false;
				if (!m_cDecoder.Decode(source))
				{
					error = L"Failed to decode source";
					return false;
				}
				if (m_cDecoder.Aborted)
				{
					m_bAborted = true;
					return true;
				}
				m_sInfo.Clear();
				CollectEntity(m_sInfo, m_cDecoder.Root, AccessType::None, true, options);
				if (m_bAborted)
					return true;
				try
				{
					SaveToDbEntities(m_sInfo, options, Path{});
				}
				catch (const std::exception &e)
				{
					error = L"Failed to save documentation with error '" + AnsiToString(e.what()) + L"'";
					return false;
				}
				catch (...)
				{
					error = L"Failed to save documentation with unknown error";
					return false;
				}
				return true;
			}

			uint CDocumentator::SaveToDbFile(const Options &options)
			{
				uint result{ 0 };
				if (!options.File.empty())
				{
					auto model{ models::CFile::Find()->Where(DbConditions{ db::eqcv(L"version", options.Version), db::eqcv(L"name", options.File) })->One() };
					if (!model)
					{
						model = new models::CFile();
						model->Version = options.Version;
						model->Name = options.File;
						model->Save(false);
					}
					result = (uint)model->Id;
				}
				return result;
			}

			void CDocumentator::SaveToDbMetaData(const uint &entity_id, const MetaData &meta, const String &version)
			{
				for (auto const &tag : meta.Tags)
				{
					if (in(tag.Name, EXCLUDE_TAGS))
						continue;
					ReleasablePtr<models::CTag> model{ new models::CTag() };
					model->Version = version;
					model->EntityId = entity_id;
					model->Name = tag.Name;
					Variable o{ VariableType::Object };
					for (auto const &option : tag.Options)
						o[option.first] = option.second;
					model->Options = json::Encoder::Encode(o);
					model->Save(false);
				}
				for (auto const &comment : meta.Comments)
				{
					ReleasablePtr<models::CComment> model{ new models::CComment() };
					model->Version = version;
					model->EntityId = entity_id;
					model->Comment = comment;
					model->Save(false);
				}
			}

			void CDocumentator::SaveToDbEntities(EntityInfo &info, const Options &options, const Path &path)
			{
				for (auto e : info.Namespaces)
				{
					if (m_pProgressListener)
					{
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
						if (m_bAborted)
							return;
					}
					SaveToDbNamespace(cast<CNamespace *>(e.Entity), e, options, path);
				}
				for (auto e : info.NamespaceAliases)
				{
					if (m_pProgressListener)
					{
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
						if (m_bAborted)
							return;
					}
					SaveToDbNamespaceAlias(cast<CNamespaceAlias *>(e.Entity), e, options, path);
				}
				for (auto e : info.Modules)
				{
					if (m_pProgressListener)
					{
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
						if (m_bAborted)
							return;
					}
					SaveToDbModule(cast<CModule *>(e.Entity), e, options, path);
				}
				for (auto e : info.Aliases)
				{
					if (m_pProgressListener)
					{
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
						if (m_bAborted)
							return;
					}
					SaveToDbAlias(cast<CTypeAlias *>(e.Entity), e, options, path);
				}
				for (auto e : info.Typedefs)
				{
					if (m_pProgressListener)
					{
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
						if (m_bAborted)
							return;
					}
					SaveToDbTypedef(cast<CSimpleDeclaration *>(e.Entity), e, options, path);
				}
				for (auto e : info.Variables)
				{
					if (m_pProgressListener)
					{
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
						if (m_bAborted)
							return;
					}
					SaveToDbVariable(cast<CSimpleDeclaration *>(e.Entity), e, options, path);
				}
				for (auto e : info.Consts)
				{
					if (m_pProgressListener)
					{
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
						if (m_bAborted)
							return;
					}
					SaveToDbConst(cast<CSimpleDeclaration *>(e.Entity), e, options, path);
				}
				for (auto e : info.Interfaces)
				{
					if (m_pProgressListener)
					{
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
						if (m_bAborted)
							return;
					}
					SaveToDbInterface(cast<CClass *>(e.Entity), e, options, path);
				}
				for (auto e : info.Classes)
				{
					if (m_pProgressListener)
					{
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
						if (m_bAborted)
							return;
					}
					SaveToDbClass(cast<CClass *>(e.Entity), e, options, path);
				}
				for (auto e : info.Structs)
				{
					if (m_pProgressListener)
					{
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
						if (m_bAborted)
							return;
					}
					SaveToDbStruct(cast<CClass *>(e.Entity), e, options, path);
				}
				for (auto e : info.Unions)
				{
					if (m_pProgressListener)
					{
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
						if (m_bAborted)
							return;
					}
					SaveToDbUnion(cast<CClass *>(e.Entity), e, options, path);
				}
				for (auto e : info.Enums)
				{
					if (m_pProgressListener)
					{
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
						if (m_bAborted)
							return;
					}
					SaveToDbEnum(cast<CEnum *>(e.Entity), e, options, path);
				}
				for (auto e : info.Functions)
				{
					if (m_pProgressListener)
					{
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
						if (m_bAborted)
							return;
					}
					SaveToDbFunction(cast<CSimpleDeclaration *>(e.Entity), e, options, path);
				}
				for (auto e : info.Concepts)
				{
					if (m_pProgressListener)
					{
						m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
						if (m_bAborted)
							return;
					}
					SaveToDbConcept(cast<CConcept *>(e.Entity), e, options, path);
				}
			}

			void CDocumentator::SaveToDbNamespace(entities::CNamespace *entity, EntityInfo &info, const Options &options, const Path &path)
			{
				String qualified{ PathToString(path) + info.Name };
				auto e{ models::CEntity::Find()
					->Where(DbConditions{
						db::eqcv(L"version", options.Version),
						db::eqcv(L"qualified", qualified),
						db::eqcv(L"type", L"namespace")
						})
					->One()
				};
				if (!e)
				{
					e = new models::CEntity();
					e->Version = options.Version;
					if (!path.empty())
						e->ParentId = path[path.size() - 1].Id;
					e->Name = info.Name;
					e->Qualified = qualified;
					e->Path = PathToJson(path);
					e->Type = (String)L"namespace";
					e->isExported = info.Exported;
					if (!info.Language.empty())
						e->Language = info.Language;
					e->Save(false);
					SaveToDbMetaData(e->Id, info.Meta, options.Version);

					ReleasablePtr<models::CNamespace> n{ new models::CNamespace() };
					n->Version = options.Version;
					n->EntityId = (uint)e->Id;
					n->AttributeLists = AttributesToJson(entity);
					n->isInline = entity->isInline;
					n->Save(false);
				}
				Path new_path{ path };
				new_path.push_back(PathEntry{ e->Id, info.Name });
				SaveToDbEntities(info, options, new_path);
			}

			void CDocumentator::SaveToDbNamespaceAlias(entities::CNamespaceAlias *entity, EntityInfo &info, const Options &options, const Path &path)
			{
				String qualified{ PathToString(path) + info.Name };
				if (m_pWarningListener && models::CEntity::Find()
					->Where(DbConditions{
						db::eqcv(L"version", options.Version),
						db::eqcv(L"qualified", qualified),
						db::eqcv(L"type", L"namespace_alias")
						})
					->Exists())
				{
					m_pWarningListener->NotifyOnWarning(
						__FUNCTION__,
						__LINE__,
						ErrorInfo{ 0, L"'{name}' namespace alias already exists" },
						E(L"{name}", qualified)
					);
				}
				uint file_id{ SaveToDbFile(options) };
				ReleasablePtr<models::CEntity> e{ new models::CEntity() };
				e->Version = options.Version;
				if (!path.empty())
					e->ParentId = path[path.size() - 1].Id;
				e->Name = info.Name;
				e->Qualified = qualified;
				e->Path = PathToJson(path);
				e->Type = (String)L"namespace_alias";
				e->isExported = info.Exported;
				if (!info.Language.empty())
					e->Language = info.Language;
				if (file_id > 0)
					e->FileId = file_id;
				e->Save(false);
				SaveToDbMetaData(e->Id, info.Meta, options.Version);

				ReleasablePtr<models::CNamespaceAlias> a{ new models::CNamespaceAlias() };
				a->Version = options.Version;
				a->EntityId = (uint)e->Id;
				a->AttributeLists = AttributesToJson(entity);
				a->NamespaceName = entity->Identifier.toString(false);
				a->Save(false);
			}

			void CDocumentator::SaveToDbModule(entities::CModule *entity, EntityInfo &info, const Options &options, const Path &path)
			{
				String qualified{ PathToString(path) + info.Name };
				auto e{ models::CEntity::Find()
					->Where(DbConditions{
						db::eqcv(L"version", options.Version),
						db::eqcv(L"qualified", qualified),
						db::eqcv(L"type", L"module")
						})
					->One()
				};
				if (!e)
				{
					e = new models::CEntity();
					e->Version = options.Version;
					if (!path.empty())
						e->ParentId = path[path.size() - 1].Id;
					e->Name = info.Name;
					e->Qualified = qualified;
					e->Path = PathToJson(path);
					e->Type = (String)L"module";
					e->isExported = false;
					e->Save(false);
					SaveToDbMetaData(e->Id, info.Meta, options.Version);

					ReleasablePtr<models::CModule> m{ new models::CModule() };
					m->Version = options.Version;
					m->EntityId = (uint)e->Id;
					m->AttributeLists = AttributesToJson(entity);
					m->Name = entity->Name;
					m->Partition = entity->Partition;
					m->isExported = entity->isExport;
					m->isPrivate = entity->isPrivate;
					m->Save(false);
				}
				Path new_path{ path };
				new_path.push_back(PathEntry{ e->Id, info.Name });
				SaveToDbEntities(info, options, new_path);
			}

			void CDocumentator::SaveToDbAlias(entities::CTypeAlias *entity, EntityInfo &info, const Options &options, const Path &path)
			{
				String qualified{ PathToString(path) + info.Name };
				if (m_pWarningListener && models::CEntity::Find()
					->Where(DbConditions{
						db::eqcv(L"version", options.Version),
						db::eqcv(L"qualified", qualified),
						db::eqcv(L"type", L"alias")
						})
					->Exists())
				{
					m_pWarningListener->NotifyOnWarning(
						__FUNCTION__,
						__LINE__,
						ErrorInfo{ 0, L"'{name}' alias already exists" },
						E(L"{name}", qualified)
					);
				}
				uint file_id{ SaveToDbFile(options) };
				ReleasablePtr<models::CEntity> e{ new models::CEntity() };
				e->Version = options.Version;
				if (!path.empty())
					e->ParentId = path[path.size() - 1].Id;
				e->Name = info.Name;
				e->Qualified = qualified;
				e->Path = PathToJson(path);
				e->Type = (String)L"alias";
				e->isExported = info.Exported;
				if (!info.Language.empty())
					e->Language = info.Language;
				if (file_id > 0)
					e->FileId = file_id;
				switch (info.Access)
				{
				case AccessType::Private:
					e->Access = (String)L"private";
					break;
				case AccessType::Protected:
					e->Access = (String)L"protected";
					break;
				case AccessType::Public:
					e->Access = (String)L"public";
					break;
				default:
					break;
				}
				e->Save(false);
				SaveToDbMetaData(e->Id, info.Meta, options.Version);

				ReleasablePtr<models::CAlias> a{ new models::CAlias() };
				a->Version = options.Version;
				a->EntityId = (uint)e->Id;
				a->AttributeLists = AttributesToJson(entity);
				if (info.Template)
				{
					a->isTemplate = true;
					a->TemplateParameters = TemplateParametersToString(info.Template);
					a->TemplateRequires = info.Template->Requires.toStringEx();
				}
				else
					a->isTemplate = false;
				a->TypeName = entity->TypeId.toStringEx();
				a->Save(false);
			}

			void CDocumentator::SaveToDbTypedef(entities::CSimpleDeclaration *entity, EntityInfo &info, const Options &options, const Path &path)
			{
				String qualified{ PathToString(path) + info.Name };
				if (m_pWarningListener && models::CEntity::Find()
					->Where(DbConditions{
						db::eqcv(L"version", options.Version),
						db::eqcv(L"qualified", qualified),
						db::eqcv(L"type", L"typedef")
						})
					->Exists())
				{
					m_pWarningListener->NotifyOnWarning(
						__FUNCTION__,
						__LINE__,
						ErrorInfo{ 0, L"'{name}' typedef already exists" },
						E(L"{name}", qualified)
					);
				}
				uint file_id{ SaveToDbFile(options) };
				ReleasablePtr<models::CEntity> e{ new models::CEntity() };
				e->Version = options.Version;
				if (!path.empty())
					e->ParentId = path[path.size() - 1].Id;
				e->Name = info.Name;
				e->Qualified = qualified;
				e->Path = PathToJson(path);
				e->Type = (String)L"typedef";
				e->isExported = info.Exported;
				if (!info.Language.empty())
					e->Language = info.Language;
				if (file_id > 0)
					e->FileId = file_id;
				switch (info.Access)
				{
				case AccessType::Private:
					e->Access = (String)L"private";
					break;
				case AccessType::Protected:
					e->Access = (String)L"protected";
					break;
				case AccessType::Public:
					e->Access = (String)L"public";
					break;
				default:
					break;
				}
				e->Save(false);
				SaveToDbMetaData(e->Id, info.Meta, options.Version);

				ReleasablePtr<models::CTypedef> a{ new models::CTypedef() };
				a->Version = options.Version;
				a->EntityId = (uint)e->Id;
				a->AttributeLists = AttributesToJson(entity);
				if (info.Template)
				{
					a->isTemplate = true;
					a->TemplateParameters = TemplateParametersToString(info.Template);
					a->TemplateRequires = info.Template->Requires.toStringEx();
				}
				else
					a->isTemplate = false;
				{
					Variable t;
					entity->toVariable(t, false, false);
					a->Declaration = json::Encoder::Encode(t);
				}
				a->Save(false);
			}

			void CDocumentator::SaveToDbVariable(entities::CSimpleDeclaration *entity, EntityInfo &info, const Options &options, const Path &path)
			{
				String qualified{ PathToString(path) + info.Name };
				if (m_pWarningListener && models::CEntity::Find()
					->Where(DbConditions{
						db::eqcv(L"version", options.Version),
						db::eqcv(L"qualified", qualified),
						db::eqcv(L"type", L"variable")
						})
					->Exists())
				{
					m_pWarningListener->NotifyOnWarning(
						__FUNCTION__,
						__LINE__,
						ErrorInfo{ 0, L"'{name}' variable already exists" },
						E(L"{name}", qualified)
					);
				}
				uint file_id{ SaveToDbFile(options) };
				ReleasablePtr<models::CEntity> e{ new models::CEntity() };
				e->Version = options.Version;
				if (!path.empty())
					e->ParentId = path[path.size() - 1].Id;
				e->Name = info.Name;
				e->Qualified = qualified;
				e->Path = PathToJson(path);
				e->Type = (String)L"variable";
				e->isExported = info.Exported;
				if (!info.Language.empty())
					e->Language = info.Language;
				if (file_id > 0)
					e->FileId = file_id;
				switch (info.Access)
				{
				case AccessType::Private:
					e->Access = (String)L"private";
					break;
				case AccessType::Protected:
					e->Access = (String)L"protected";
					break;
				case AccessType::Public:
					e->Access = (String)L"public";
					break;
				default:
					break;
				}
				e->Save(false);
				SaveToDbMetaData(e->Id, info.Meta, options.Version);

				ReleasablePtr<models::CVariable> v{ new models::CVariable() };
				v->Version = options.Version;
				v->EntityId = (uint)e->Id;
				v->AttributeLists = AttributesToJson(entity);
				if (info.Template)
				{
					v->isTemplate = true;
					v->TemplateParameters = TemplateParametersToString(info.Template);
					v->TemplateRequires = info.Template->Requires.toStringEx();
				}
				else
					v->isTemplate = false;
				{
					Variable t;
					entity->toVariable(t, false, false);
					v->Declaration = json::Encoder::Encode(t);
				}
				v->Save(false);
			}

			void CDocumentator::SaveToDbConst(entities::CSimpleDeclaration *entity, EntityInfo &info, const Options &options, const Path &path)
			{
				String qualified{ PathToString(path) + info.Name };
				if (m_pWarningListener && models::CEntity::Find()
					->Where(DbConditions{
						db::eqcv(L"version", options.Version),
						db::eqcv(L"qualified", qualified),
						db::eqcv(L"type", L"const")
						})
					->Exists())
				{
					m_pWarningListener->NotifyOnWarning(
						__FUNCTION__,
						__LINE__,
						ErrorInfo{ 0, L"'{name}' const already exists" },
						E(L"{name}", qualified)
					);
				}
				uint file_id{ SaveToDbFile(options) };
				ReleasablePtr<models::CEntity> e{ new models::CEntity() };
				e->Version = options.Version;
				if (!path.empty())
					e->ParentId = path[path.size() - 1].Id;
				e->Name = info.Name;
				e->Qualified = qualified;
				e->Path = PathToJson(path);
				e->Type = (String)L"const";
				e->isExported = info.Exported;
				if (!info.Language.empty())
					e->Language = info.Language;
				if (file_id > 0)
					e->FileId = file_id;
				switch (info.Access)
				{
				case AccessType::Private:
					e->Access = (String)L"private";
					break;
				case AccessType::Protected:
					e->Access = (String)L"protected";
					break;
				case AccessType::Public:
					e->Access = (String)L"public";
					break;
				default:
					break;
				}
				e->Save(false);
				SaveToDbMetaData(e->Id, info.Meta, options.Version);

				ReleasablePtr<models::CConst> c{ new models::CConst() };
				c->Version = options.Version;
				c->EntityId = (uint)e->Id;
				c->AttributeLists = AttributesToJson(entity);
				if (info.Template)
				{
					c->isTemplate = true;
					c->TemplateParameters = TemplateParametersToString(info.Template);
					c->TemplateRequires = info.Template->Requires.toStringEx();
				}
				else
					c->isTemplate = false;
				{
					Variable t;
					entity->toVariable(t, false, false);
					c->Declaration = json::Encoder::Encode(t);
				}
				c->Save(false);
			}

			void CDocumentator::SaveToDbInterface(entities::CClass *entity, EntityInfo &info, const Options &options, const Path &path)
			{
				String qualified{ PathToString(path) + info.Name };
				if (m_pWarningListener && models::CEntity::Find()
					->Where(DbConditions{
						db::eqcv(L"version", options.Version),
						db::eqcv(L"qualified", qualified),
						db::eqcv(L"type", L"interface")
						})
					->Exists())
				{
					m_pWarningListener->NotifyOnWarning(
						__FUNCTION__,
						__LINE__,
						ErrorInfo{ 0, L"'{name}' interface already exists" },
						E(L"{name}", qualified)
					);
				}
				uint file_id{ SaveToDbFile(options) };
				ReleasablePtr<models::CEntity> e{ new models::CEntity() };
				e->Version = options.Version;
				if (!path.empty())
					e->ParentId = path[path.size() - 1].Id;
				e->Name = info.Name;
				e->Qualified = qualified;
				e->Path = PathToJson(path);
				e->Type = (String)L"interface";
				e->isExported = info.Exported;
				if (!info.Language.empty())
					e->Language = info.Language;
				if (file_id > 0)
					e->FileId = file_id;
				switch (info.Access)
				{
				case AccessType::Private:
					e->Access = (String)L"private";
					break;
				case AccessType::Protected:
					e->Access = (String)L"protected";
					break;
				case AccessType::Public:
					e->Access = (String)L"public";
					break;
				default:
					break;
				}
				e->Save(false);
				SaveToDbMetaData(e->Id, info.Meta, options.Version);

				ReleasablePtr<models::CInterface> i{ new models::CInterface() };
				i->Version = options.Version;
				i->EntityId = (uint)e->Id;
				i->AttributeLists = AttributesToJson(entity);
				if (info.Template)
				{
					i->isTemplate = true;
					i->TemplateParameters = TemplateParametersToString(info.Template);
					i->TemplateRequires = info.Template->Requires.toStringEx();
				}
				else
					i->isTemplate = false;
				i->isFinal = entity->isFinal;
				i->isTriviallyRelocatableIfEligible = entity->isTriviallyRelocatableIfEligible;
				i->isReplaceableIfEligible = entity->isReplaceableIfEligible;
				Variable t;
				for (auto base : entity->Bases)
				{
					Variable b;
					base->toVariable(b, false, false);
					MetaData md{ GetEntityMetaData(base, true, true) };
					for (auto tag : md.Tags)
						if (tag.Name == TAG_QUALIFIED)
						{
							if (tag.Options.size() == 1)
								b[L"qualified"] = tag.Options[0].second;
							break;
						}
					t.push_back(b);
				}
				if (t.type() == VariableType::Array)
					i->Bases = json::Encoder::Encode(t);
				i->Save(false);

				Path new_path{ path };
				new_path.push_back(PathEntry{ e->Id, info.Name });
				SaveToDbEntities(info, options, new_path);
			}

			void CDocumentator::SaveToDbClass(entities::CClass *entity, EntityInfo &info, const Options &options, const Path &path)
			{
				String qualified{ PathToString(path) + info.Name };
				if (m_pWarningListener && models::CEntity::Find()
					->Where(DbConditions{
						db::eqcv(L"version", options.Version),
						db::eqcv(L"qualified", qualified),
						db::eqcv(L"type", L"class")
						})
					->Exists())
				{
					m_pWarningListener->NotifyOnWarning(
						__FUNCTION__,
						__LINE__,
						ErrorInfo{ 0, L"'{name}' class already exists" },
						E(L"{name}", qualified)
					);
				}
				uint file_id{ SaveToDbFile(options) };
				ReleasablePtr<models::CEntity> e{ new models::CEntity() };
				e->Version = options.Version;
				if (!path.empty())
					e->ParentId = path[path.size() - 1].Id;
				e->Name = info.Name;
				e->Qualified = qualified;
				e->Path = PathToJson(path);
				e->Type = (String)L"class";
				e->isExported = info.Exported;
				if (!info.Language.empty())
					e->Language = info.Language;
				if (file_id > 0)
					e->FileId = file_id;
				switch (info.Access)
				{
				case AccessType::Private:
					e->Access = (String)L"private";
					break;
				case AccessType::Protected:
					e->Access = (String)L"protected";
					break;
				case AccessType::Public:
					e->Access = (String)L"public";
					break;
				default:
					break;
				}
				e->Save(false);
				SaveToDbMetaData(e->Id, info.Meta, options.Version);

				ReleasablePtr<models::CClass> c{ new models::CClass() };
				c->Version = options.Version;
				c->EntityId = (uint)e->Id;
				c->AttributeLists = AttributesToJson(entity);
				if (info.Template)
				{
					c->isTemplate = true;
					c->TemplateParameters = TemplateParametersToString(info.Template);
					c->TemplateRequires = info.Template->Requires.toStringEx();
				}
				else
					c->isTemplate = false;
				c->isFinal = entity->isFinal;
				c->isTriviallyRelocatableIfEligible = entity->isTriviallyRelocatableIfEligible;
				c->isReplaceableIfEligible = entity->isReplaceableIfEligible;
				Variable t;
				for (auto base : entity->Bases)
				{
					Variable b;
					base->toVariable(b, false, false);
					MetaData md{ GetEntityMetaData(base, true, true) };
					for (auto tag : md.Tags)
						if (tag.Name == TAG_QUALIFIED)
						{
							if (tag.Options.size() == 1)
								b[L"qualified"] = tag.Options[0].second;
							break;
						}
					t.push_back(b);
				}
				if (t.type() == VariableType::Array)
					c->Bases = json::Encoder::Encode(t);
				c->Save(false);

				Path new_path{ path };
				new_path.push_back(PathEntry{ e->Id, info.Name });
				SaveToDbEntities(info, options, new_path);
			}

			void CDocumentator::SaveToDbStruct(entities::CClass *entity, EntityInfo &info, const Options &options, const Path &path)
			{
				String qualified{ PathToString(path) + info.Name };
				if (m_pWarningListener && models::CEntity::Find()
					->Where(DbConditions{
						db::eqcv(L"version", options.Version),
						db::eqcv(L"qualified", qualified),
						db::eqcv(L"type", L"struct")
						})
					->Exists())
				{
					m_pWarningListener->NotifyOnWarning(
						__FUNCTION__,
						__LINE__,
						ErrorInfo{ 0, L"'{name}' struct already exists" },
						E(L"{name}", qualified)
					);
				}
				uint file_id{ SaveToDbFile(options) };
				ReleasablePtr<models::CEntity> e{ new models::CEntity() };
				e->Version = options.Version;
				if (!path.empty())
					e->ParentId = path[path.size() - 1].Id;
				e->Name = info.Name;
				e->Qualified = qualified;
				e->Path = PathToJson(path);
				e->Type = (String)L"struct";
				e->isExported = info.Exported;
				if (!info.Language.empty())
					e->Language = info.Language;
				if (file_id > 0)
					e->FileId = file_id;
				switch (info.Access)
				{
				case AccessType::Private:
					e->Access = (String)L"private";
					break;
				case AccessType::Protected:
					e->Access = (String)L"protected";
					break;
				case AccessType::Public:
					e->Access = (String)L"public";
					break;
				default:
					break;
				}
				e->Save(false);
				SaveToDbMetaData(e->Id, info.Meta, options.Version);

				ReleasablePtr<models::CStruct> s{ new models::CStruct() };
				s->Version = options.Version;
				s->EntityId = (uint)e->Id;
				s->AttributeLists = AttributesToJson(entity);
				if (info.Template)
				{
					s->isTemplate = true;
					s->TemplateParameters = TemplateParametersToString(info.Template);
					s->TemplateRequires = info.Template->Requires.toStringEx();
				}
				else
					s->isTemplate = false;
				s->isFinal = entity->isFinal;
				s->isTriviallyRelocatableIfEligible = entity->isTriviallyRelocatableIfEligible;
				s->isReplaceableIfEligible = entity->isReplaceableIfEligible;
				Variable t;
				for (auto base : entity->Bases)
				{
					Variable b;
					base->toVariable(b, false, false);
					MetaData md{ GetEntityMetaData(base, true, true) };
					for (auto tag : md.Tags)
						if (tag.Name == TAG_QUALIFIED)
						{
							if (tag.Options.size() == 1)
								b[L"qualified"] = tag.Options[0].second;
							break;
						}
					t.push_back(b);
				}
				if (t.type() == VariableType::Array)
					s->Bases = json::Encoder::Encode(t);
				s->Save(false);

				Path new_path{ path };
				new_path.push_back(PathEntry{ e->Id, info.Name });
				SaveToDbEntities(info, options, new_path);
			}

			void CDocumentator::SaveToDbUnion(entities::CClass *entity, EntityInfo &info, const Options &options, const Path &path)
			{
				String qualified{ PathToString(path) + info.Name };
				if (m_pWarningListener && models::CEntity::Find()
					->Where(DbConditions{
						db::eqcv(L"version", options.Version),
						db::eqcv(L"qualified", qualified),
						db::eqcv(L"type", L"union")
						})
					->Exists())
				{
					m_pWarningListener->NotifyOnWarning(
						__FUNCTION__,
						__LINE__,
						ErrorInfo{ 0, L"'{name}' union already exists" },
						E(L"{name}", qualified)
					);
				}
				uint file_id{ SaveToDbFile(options) };
				ReleasablePtr<models::CEntity> e{ new models::CEntity() };
				e->Version = options.Version;
				if (!path.empty())
					e->ParentId = path[path.size() - 1].Id;
				e->Name = info.Name;
				e->Qualified = qualified;
				e->Path = PathToJson(path);
				e->Type = (String)L"union";
				e->isExported = info.Exported;
				if (!info.Language.empty())
					e->Language = info.Language;
				if (file_id > 0)
					e->FileId = file_id;
				switch (info.Access)
				{
				case AccessType::Private:
					e->Access = (String)L"private";
					break;
				case AccessType::Protected:
					e->Access = (String)L"protected";
					break;
				case AccessType::Public:
					e->Access = (String)L"public";
					break;
				default:
					break;
				}
				e->Save(false);
				SaveToDbMetaData(e->Id, info.Meta, options.Version);

				ReleasablePtr<models::CUnion> u{ new models::CUnion() };
				u->Version = options.Version;
				u->EntityId = (uint)e->Id;
				u->AttributeLists = AttributesToJson(entity);
				if (info.Template)
				{
					u->isTemplate = true;
					u->TemplateParameters = TemplateParametersToString(info.Template);
					u->TemplateRequires = info.Template->Requires.toStringEx();
				}
				else
					u->isTemplate = false;
				u->isFinal = entity->isFinal;
				u->isTriviallyRelocatableIfEligible = entity->isTriviallyRelocatableIfEligible;
				u->isReplaceableIfEligible = entity->isReplaceableIfEligible;
				u->Save(false);

				Path new_path{ path };
				new_path.push_back(PathEntry{ e->Id, info.Name });
				SaveToDbEntities(info, options, new_path);
			}

			void CDocumentator::SaveToDbEnum(entities::CEnum *entity, EntityInfo &info, const Options &options, const Path &path)
			{
				String qualified{ PathToString(path) + info.Name };
				if (m_pWarningListener && models::CEntity::Find()
					->Where(DbConditions{
						db::eqcv(L"version", options.Version),
						db::eqcv(L"qualified", qualified),
						db::eqcv(L"type", L"enum")
						})
					->Exists())
				{
					m_pWarningListener->NotifyOnWarning(
						__FUNCTION__,
						__LINE__,
						ErrorInfo{ 0, L"'{name}' enum already exists" },
						E(L"{name}", qualified)
					);
				}
				uint file_id{ SaveToDbFile(options) };
				ReleasablePtr<models::CEntity> e{ new models::CEntity() };
				e->Version = options.Version;
				if (!path.empty())
					e->ParentId = path[path.size() - 1].Id;
				e->Name = info.Name;
				e->Qualified = qualified;
				e->Path = PathToJson(path);
				e->Type = (String)L"enum";
				e->isExported = info.Exported;
				if (!info.Language.empty())
					e->Language = info.Language;
				if (file_id > 0)
					e->FileId = file_id;
				switch (info.Access)
				{
				case AccessType::Private:
					e->Access = (String)L"private";
					break;
				case AccessType::Protected:
					e->Access = (String)L"protected";
					break;
				case AccessType::Public:
					e->Access = (String)L"public";
					break;
				default:
					break;
				}
				e->Save(false);
				SaveToDbMetaData(e->Id, info.Meta, options.Version);

				ReleasablePtr<models::CEnum> m{ new models::CEnum() };
				m->Version = options.Version;
				m->EntityId = (uint)e->Id;
				m->AttributeLists = AttributesToJson(entity);
				if (info.Template)
				{
					m->isTemplate = true;
					m->TemplateParameters = TemplateParametersToString(info.Template);
					m->TemplateRequires = info.Template->Requires.toStringEx();
				}
				else
					m->isTemplate = false;
				if (!entity->Scope.empty())
					m->Scope = entity->Scope;
				if (entity->Base.Begin)
					m->Base = entity->Base.toStringEx();
				m->Save(false);

				Path new_path{ path };
				new_path.push_back(PathEntry{ e->Id, info.Name });
				for (auto en : entity->Entities)
				{
					CEnumerator *enumerator{ cast<CEnumerator *>(en) };

					ReleasablePtr<models::CEntity> ent{ new models::CEntity() };
					ent->Version = options.Version;
					ent->ParentId = (uint)e->Id;
					ent->Name = enumerator->Name;
					ent->Qualified = qualified + L"::" + enumerator->Name;
					ent->Path = PathToJson(new_path);
					ent->Type = (String)L"enumerator";
					ent->isExported = false;
					ent->Save(false);
					MetaData md{ GetEntityMetaData(en, true, true) };
					SaveToDbMetaData(ent->Id, md, options.Version);

					ReleasablePtr<models::CEnumerator> model{ new models::CEnumerator() };
					model->Version = options.Version;
					model->EntityId = (uint)ent->Id;
					model->AttributeLists = AttributesToJson(entity);
					model->Name = enumerator->Name;
					if (enumerator->Value.Begin)
						model->Value = enumerator->Value.toStringEx();
					model->Save(false);
				}
			}

			void CDocumentator::SaveToDbFunction(entities::CSimpleDeclaration *entity, EntityInfo &info, const Options &options, const Path &path)
			{
				String qualified{ PathToString(path) + info.Name };
				uint file_id{ SaveToDbFile(options) };
				ReleasablePtr<models::CEntity> e{ new models::CEntity() };
				e->Version = options.Version;
				if (!path.empty())
					e->ParentId = path[path.size() - 1].Id;
				e->Name = info.Name;
				e->Qualified = qualified;
				e->Path = PathToJson(path);
				e->Type = (String)L"function";
				e->isExported = info.Exported;
				if (!info.Language.empty())
					e->Language = info.Language;
				if (file_id > 0)
					e->FileId = file_id;
				switch (info.Access)
				{
				case AccessType::Private:
					e->Access = (String)L"private";
					break;
				case AccessType::Protected:
					e->Access = (String)L"protected";
					break;
				case AccessType::Public:
					e->Access = (String)L"public";
					break;
				default:
					break;
				}
				e->Save(false);

				ReleasablePtr<models::CFunction> f{ new models::CFunction() };
				CFunction *fun{ getFunction(entity->Declarators[0]) }; // nullptr will never be returned bacuse isFunction() was called before adding entity as a function
				f->Version = options.Version;
				f->EntityId = (uint)e->Id;
				f->AttributeLists = AttributesToJson(entity);
				if (info.Template)
				{
					f->isTemplate = true;
					f->TemplateParameters = TemplateParametersToString(info.Template);
					f->TemplateRequires = info.Template->Requires.toStringEx();
				}
				else
					f->isTemplate = false;
				{
					Variable t;
					for (auto specifier : entity->Specifiers)
					{
						Variable s;
						specifier->toVariable(s, false, false);
						t.push_back(s);
					}
					for (auto specifier : fun->CallSpecifiers)
					{
						Variable s;
						specifier->toVariable(s, false, false);
						t.push_back(s);
					}
					if (t.type() == VariableType::Array)
						f->Specifiers = json::Encoder::Encode(t);
				}
				{
					String t;
					for (auto cont : fun->Contracts)
					{
						if (!t.empty())
							t += L" ";
						t += cont->toString(L"", false);
					}
					if (!t.empty())
						f->Contracts = t;
				}
				f->isThrow = fun->Throw;
				if (fun->ThrowBody.Begin)
					f->Throw = fun->ThrowBody.toStringEx();
				f->isNoexcept = fun->NoExcept;
				if (fun->NoExceptBody.Begin)
					f->Noexcept = fun->NoExceptBody.toStringEx();
				if (fun->Trailing.Begin)
					f->Trailing = fun->Trailing.toStringEx();
				if (fun->Requires.Begin)
					f->Requires = fun->Requires.toStringEx();
				f->isAbstract = fun->Abstract;
				f->isDefault = fun->Default;
				f->isDeleted = fun->Deleted;
				if (!fun->DeleteReason.empty())
					f->DeleteReason = fun->DeleteReason;
				f->Save(false);

				Path new_path{ path };
				new_path.push_back(PathEntry{ e->Id, info.Name });
				for (auto param : fun->Parameters)
				{
					CFunctionParameter *par{ cast<CFunctionParameter *>(param) };
					MetaData md{ GetEntityMetaData(param, true, true) };
					String name;
					CheckDeclaratorName(par->Declarator, name);

					// Move @param tags related to this parameter to this parameter metadata
					auto pos{ info.Meta.Tags.begin() };
					while (pos != info.Meta.Tags.end())
					{
						if (pos->Name == TAG_PARAM)
						{
							bool found{ false };
							for (auto o : pos->Options)
								if (o.first == L"name" && o.second == name)
								{
									found = true;
									break;
								}
							if (found)
							{
								md.Tags.push_back(*pos);
								pos = info.Meta.Tags.erase(pos);
								continue;
							}
						}
						pos++;
					}

					ReleasablePtr<models::CEntity> ent{ new models::CEntity() };
					ent->Version = options.Version;
					ent->ParentId = (uint)e->Id;
					ent->Name = name;
					ent->Qualified = qualified + L"::" + (String)ent->Name;
					ent->Path = PathToJson(new_path);
					ent->Type = (String)L"parameter";
					ent->isExported = false;
					ent->Save(false);
					SaveToDbMetaData(ent->Id, md, options.Version);

					ReleasablePtr<models::CParameter> model{ new models::CParameter() };
					model->Version = options.Version;
					model->EntityId = (uint)ent->Id;
					model->AttributeLists = AttributesToJson(entity);
					{
						Variable t;
						param->toVariable(t, false, false);
						model->Declaration = json::Encoder::Encode(t);
					}
					model->Save(false);
				}

				SaveToDbMetaData(e->Id, info.Meta, options.Version);
			}

			void CDocumentator::SaveToDbConcept(entities::CConcept *entity, EntityInfo &info, const Options &options, const Path &path)
			{
				String qualified{ PathToString(path) + info.Name };
				if (m_pWarningListener && models::CEntity::Find()
					->Where(DbConditions{
						db::eqcv(L"version", options.Version),
						db::eqcv(L"qualified", qualified),
						db::eqcv(L"type", L"concept")
						})
					->Exists())
				{
					m_pWarningListener->NotifyOnWarning(
						__FUNCTION__,
						__LINE__,
						ErrorInfo{ 0, L"'{name}' concept already exists" },
						E(L"{name}", qualified)
					);
				}
				uint file_id{ SaveToDbFile(options) };
				ReleasablePtr<models::CEntity> e{ new models::CEntity() };
				e->Version = options.Version;
				if (!path.empty())
					e->ParentId = path[path.size() - 1].Id;
				e->Name = info.Name;
				e->Qualified = qualified;
				e->Path = PathToJson(path);
				e->Type = (String)L"concept";
				e->isExported = info.Exported;
				if (!info.Language.empty())
					e->Language = info.Language;
				if (file_id > 0)
					e->FileId = file_id;
				switch (info.Access)
				{
				case AccessType::Private:
					e->Access = (String)L"private";
					break;
				case AccessType::Protected:
					e->Access = (String)L"protected";
					break;
				case AccessType::Public:
					e->Access = (String)L"public";
					break;
				default:
					break;
				}
				e->Save(false);
				SaveToDbMetaData(e->Id, info.Meta, options.Version);

				ReleasablePtr<models::CConcept> c{ new models::CConcept() };
				c->Version = options.Version;
				c->EntityId = (uint)e->Id;
				c->AttributeLists = AttributesToJson(entity);
				c->TemplateParameters = TemplateParametersToString(info.Template);
				c->TemplateRequires = info.Template->Requires.toStringEx();
				c->Save(false);
			}
		#pragma endregion

		#pragma region Add ids
			bool CDocumentator::AddIds(const Options &options, String &error)
			{
				m_bAborted = false;
				try
				{
					AddIdsToNamespaceAliases(options);
					if (m_bAborted)
						return true;
					AddIdsToTypedefs(options);
					if (m_bAborted)
						return true;
					AddIdsToVariables(options);
					if (m_bAborted)
						return true;
					AddIdsToConsts(options);
					if (m_bAborted)
						return true;
					AddIdsToInterfaces(options);
					if (m_bAborted)
						return true;
					AddIdsToClasses(options);
					if (m_bAborted)
						return true;
					AddIdsToStructs(options);
					if (m_bAborted)
						return true;
					AddIdsToFunctions(options);
					if (m_bAborted)
						return true;
					AddIdsToParameters(options);
					if (m_bAborted)
						return true;
					AddIdsToAliases(options);
				}
				catch (const std::exception &e)
				{
					error = L"Failed to add ids with error '" + AnsiToString(e.what()) + L"'";
					return false;
				}
				catch (...)
				{
					error = L"Failed to add ids with unknown error";
					return false;
				}
				return true;
			}

			void CDocumentator::AddIdsToNamespaceAliases(const Options &options)
			{
				// CNamespaceAlias::Namespace (json)
				int64 offset{ 0 };
				std::vector<ReleasablePtr<models::CNamespaceAlias>> models;
				do
				{
					models = models::CNamespaceAlias::Find()->Limit(BATCH_SIZE)->Offset(offset)->With(L"Entity.Tags")->All();
					for (auto model : models)
					{
						if (m_pProgressListener)
						{
							m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
							if (m_bAborted)
								return;
						}
						String name{ model->NamespaceName };
						bool root_only{ GetQualifiedNameFromTags(model->Entity->Tags, name) };
						if (!root_only && name.find(L"::") == 0)
						{
							name.erase(0, 2);
							root_only = true;
						}
						if (!root_only && options.NoWarnNamespaces.find(name) != options.NoWarnNamespaces.end())
							continue;
						if (name.empty())
							continue;
						std::vector<ReleasablePtr<models::CEntity>> entities;
						if (root_only)
						{
							entities = models::CEntity::Find()
								->Where(
									DbConditions{
										db::eqcv(L"version", options.Version),
										db::eqcv(L"qualified", name),
										db::eqcv(L"type", L"namespace")
									})
								->Limit(2)
								->All();
						}
						else
						{
							entities = models::CEntity::Find()
								->Where(
									DbConditions{
										db::eqcv(L"version", options.Version),
										db::o(db::eqcv(L"qualified", name), db::lkc(L"qualified", L"%::" + name)),
										db::eqcv(L"type", L"namespace")
									})
								->Limit(2)
								->All();
						}
						if (entities.empty())
						{
							if (m_pWarningListener)
							{
								m_pWarningListener->NotifyOnWarning(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Namespace '{name}' is not found for namespace alias #{id}" },
									E(L"{name}", name, L"{id}", ToString((uint)model->Id))
								);
							}
							continue;
						}
						if (entities.size() != 1)
						{
							if (m_pWarningListener)
							{
								m_pWarningListener->NotifyOnWarning(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Multiple '{name}' namespaces are found for namespace alias #{id}" },
									E(L"{name}", name, L"{id}", ToString((uint)model->Id))
								);
							}
							continue;
						}
						model->NamespaceId = (uint)entities[0]->Id;
						model->Save(false);
					}
					offset += BATCH_SIZE;
				} while (!models.empty());
			}

			void CDocumentator::AddIdsToTypedefs(const Options &options)
			{
				// CTypedef::Declaration (json)
				int64 offset{ 0 };
				std::vector<ReleasablePtr<models::CTypedef>> models;
				do
				{
					models = models::CTypedef::Find()->Limit(BATCH_SIZE)->Offset(offset)->With(L"Entity.Tags")->All();
					for (auto model : models)
					{
						if (m_pProgressListener)
						{
							m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
							if (m_bAborted)
								return;
						}
						Variable v_declaration;
						if (!json::Decoder::Decode(model->Declaration, v_declaration))
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Cannot decode Declaration of typedef #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						if (!v_declaration.has(L"specifiers"))
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Invalid Declaration of typedef #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						Variable &v_specifiers{ v_declaration[L"specifiers"] };
						if (v_specifiers.type() != VariableType::Array)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Invalid Declaration of typedef #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						String name, type;
						for (size_t specifier_i = 0; specifier_i < v_specifiers.size(); specifier_i++)
						{
							Variable &v_specifier{ v_specifiers[specifier_i] };
							if (String(v_specifier[L"type"]) == L"enum")
							{
								name = String(v_specifier[L"name"]);
								type = L"enum";
								break;
							}
							if (String(v_specifier[L"type"]) == L"class")
							{
								name = String(v_specifier[L"name"]);
								type = L"class";
								break;
							}
							if (String(v_specifier[L"type"]) == L"struct")
							{
								name = String(v_specifier[L"name"]);
								type = L"struct";
								break;
							}
							if (String(v_specifier[L"type"]) == L"union")
							{
								name = String(v_specifier[L"name"]);
								type = L"union";
								break;
							}
							if (String(v_specifier[L"type"]) == L"name")
							{
								name = String(v_specifier[L"name"]);
								break;
							}
						}
						bool root_only{ GetQualifiedNameFromTags(model->Entity->Tags, name) };
						if (!root_only && name.find(L"::") == 0)
						{
							name.erase(0, 2);
							root_only = true;
						}
						if (!root_only && type.empty() && options.NoWarnSpecifiers.find(name) != options.NoWarnSpecifiers.end())
							continue;
						if (name.empty())
							continue;
						std::vector<ReleasablePtr<models::CEntity>> entities;
						DbConditions conditions;
						conditions.push_back(db::eqcv(L"version", options.Version));
						if (root_only)
							conditions.push_back(db::eqcv(L"qualified", name));
						else
							conditions.push_back(db::o(db::eqcv(L"qualified", name), db::lkc(L"qualified", L"%::" + name)));
						if (type.empty())
							conditions.push_back(db::inc(L"type", DbRow{ L"interface", L"class", L"struct", L"union", L"enum", L"alias", L"typedef", L"function", L"concept" }));
						else if (type == L"class")
							conditions.push_back(db::inc(L"type", DbRow{ L"interface", L"class" }));
						else
							conditions.push_back(db::eqcv(L"type", type));
						entities= models::CEntity::Find()->Where(conditions)->Limit(2)->All();
						if (entities.empty())
						{
							if (m_pWarningListener)
							{
								m_pWarningListener->NotifyOnWarning(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Specifier '{name}' is not found for typedef #{id}" },
									E(L"{name}", name, L"{id}", ToString((uint)model->Id))
								);
							}
							continue;
						}
						if (entities.size() != 1)
						{
							if (m_pWarningListener)
							{
								m_pWarningListener->NotifyOnWarning(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Multiple '{name}' specifiers are found for typedef #{id}" },
									E(L"{name}", name, L"{id}", ToString((uint)model->Id))
								);
							}
							continue;
						}
						model->SpecifierId = (uint)entities[0]->Id;
						model->Save(false);
					}
					offset += BATCH_SIZE;
				} while (!models.empty());
			}

			void CDocumentator::AddIdsToVariables(const Options &options)
			{
				// CVariable::Declaration (json)
				int64 offset{ 0 };
				std::vector<ReleasablePtr<models::CVariable>> models;
				do
				{
					models = models::CVariable::Find()->Limit(BATCH_SIZE)->Offset(offset)->All();
					for (auto model : models)
					{
						if (m_pProgressListener)
						{
							m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
							if (m_bAborted)
								return;
						}
						Variable v_declaration;
						if (!json::Decoder::Decode(model->Declaration, v_declaration))
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Cannot decode Declaration of variable #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						if (!v_declaration.has(L"specifiers"))
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Invalid Declaration of variable #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						Variable &v_specifiers{ v_declaration[L"specifiers"] };
						if (v_specifiers.type() != VariableType::Array)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Invalid Declaration of variable #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						String name, type;
						for (size_t specifier_i = 0; specifier_i < v_specifiers.size(); specifier_i++)
						{
							Variable &v_specifier{ v_specifiers[specifier_i] };
							if (String(v_specifier[L"type"]) == L"enum")
							{
								name = String(v_specifier[L"name"]);
								type = L"enum";
								break;
							}
							if (String(v_specifier[L"type"]) == L"class")
							{
								name = String(v_specifier[L"name"]);
								type = L"class";
								break;
							}
							if (String(v_specifier[L"type"]) == L"struct")
							{
								name = String(v_specifier[L"name"]);
								type = L"struct";
								break;
							}
							if (String(v_specifier[L"type"]) == L"union")
							{
								name = String(v_specifier[L"name"]);
								type = L"union";
								break;
							}
							if (String(v_specifier[L"type"]) == L"name")
							{
								name = String(v_specifier[L"name"]);
								break;
							}
						}
						bool root_only{ GetQualifiedNameFromTags(model->Entity->Tags, name) };
						if (!root_only && name.find(L"::") == 0)
						{
							name.erase(0, 2);
							root_only = true;
						}
						if (!root_only && type.empty() && options.NoWarnSpecifiers.find(name) != options.NoWarnSpecifiers.end())
							continue;
						if (name.empty())
							continue;
						std::vector<ReleasablePtr<models::CEntity>> entities;
						DbConditions conditions;
						conditions.push_back(db::eqcv(L"version", options.Version));
						if (root_only)
							conditions.push_back(db::eqcv(L"qualified", name));
						else
							conditions.push_back(db::o(db::eqcv(L"qualified", name), db::lkc(L"qualified", L"%::" + name)));
						if (type.empty())
							conditions.push_back(db::inc(L"type", DbRow{ L"interface", L"class", L"struct", L"union", L"enum", L"alias", L"typedef" }));
						else if (type == L"class")
							conditions.push_back(db::inc(L"type", DbRow{ L"interface", L"class" }));
						else
							conditions.push_back(db::eqcv(L"type", type));
						entities = models::CEntity::Find()->Where(conditions)->Limit(2)->All();
						if (entities.empty())
						{
							if (m_pWarningListener)
							{
								m_pWarningListener->NotifyOnWarning(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Specifier '{name}' is not found for variable #{id}" },
									E(L"{name}", name, L"{id}", ToString((uint)model->Id))
								);
							}
							continue;
						}
						if (entities.size() != 1)
						{
							if (m_pWarningListener)
							{
								m_pWarningListener->NotifyOnWarning(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Multiple '{name}' specifiers are found for variable #{id}" },
									E(L"{name}", name, L"{id}", ToString((uint)model->Id))
								);
							}
							continue;
						}
						model->SpecifierId = (uint)entities[0]->Id;
						model->Save(false);
					}
					offset += BATCH_SIZE;
				} while (!models.empty());
			}

			void CDocumentator::AddIdsToConsts(const Options &options)
			{
				// CConst::Declaration (json)
				int64 offset{ 0 };
				std::vector<ReleasablePtr<models::CConst>> models;
				do
				{
					models = models::CConst::Find()->Limit(BATCH_SIZE)->Offset(offset)->All();
					for (auto model : models)
					{
						if (m_pProgressListener)
						{
							m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
							if (m_bAborted)
								return;
						}
						Variable v_declaration;
						if (!json::Decoder::Decode(model->Declaration, v_declaration))
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Cannot decode Declaration of const #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						if (!v_declaration.has(L"specifiers"))
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Invalid Declaration of const #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						Variable &v_specifiers{ v_declaration[L"specifiers"] };
						if (v_specifiers.type() != VariableType::Array)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Invalid Declaration of const #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						String name, type;
						for (size_t specifier_i = 0; specifier_i < v_specifiers.size(); specifier_i++)
						{
							Variable &v_specifier{ v_specifiers[specifier_i] };
							if (String(v_specifier[L"type"]) == L"enum")
							{
								name = String(v_specifier[L"name"]);
								type = L"enum";
								break;
							}
							if (String(v_specifier[L"type"]) == L"class")
							{
								name = String(v_specifier[L"name"]);
								type = L"class";
								break;
							}
							if (String(v_specifier[L"type"]) == L"struct")
							{
								name = String(v_specifier[L"name"]);
								type = L"struct";
								break;
							}
							if (String(v_specifier[L"type"]) == L"union")
							{
								name = String(v_specifier[L"name"]);
								type = L"union";
								break;
							}
							if (String(v_specifier[L"type"]) == L"name")
							{
								name = String(v_specifier[L"name"]);
								break;
							}
						}
						bool root_only{ GetQualifiedNameFromTags(model->Entity->Tags, name) };
						if (!root_only && name.find(L"::") == 0)
						{
							name.erase(0, 2);
							root_only = true;
						}
						if (!root_only && type.empty() && options.NoWarnSpecifiers.find(name) != options.NoWarnSpecifiers.end())
							continue;
						if (name.empty())
							continue;
						std::vector<ReleasablePtr<models::CEntity>> entities;
						DbConditions conditions;
						conditions.push_back(db::eqcv(L"version", options.Version));
						if (root_only)
							conditions.push_back(db::eqcv(L"qualified", name));
						else
							conditions.push_back(db::o(db::eqcv(L"qualified", name), db::lkc(L"qualified", L"%::" + name)));
						if (type.empty())
							conditions.push_back(db::inc(L"type", DbRow{ L"interface", L"class", L"struct", L"union", L"enum", L"alias", L"typedef" }));
						else if (type == L"class")
							conditions.push_back(db::inc(L"type", DbRow{ L"interface", L"class" }));
						else
							conditions.push_back(db::eqcv(L"type", type));
						entities = models::CEntity::Find()->Where(conditions)->Limit(2)->All();
						if (entities.empty())
						{
							if (m_pWarningListener)
							{
								m_pWarningListener->NotifyOnWarning(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Specifier '{name}' is not found for const #{id}" },
									E(L"{name}", name, L"{id}", ToString((uint)model->Id))
								);
							}
							continue;
						}
						if (entities.size() != 1)
						{
							if (m_pWarningListener)
							{
								m_pWarningListener->NotifyOnWarning(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Multiple '{name}' specifiers are found for const #{id}" },
									E(L"{name}", name, L"{id}", ToString((uint)model->Id))
								);
							}
							continue;
						}
						model->SpecifierId = (uint)entities[0]->Id;
						model->Save(false);
					}
					offset += BATCH_SIZE;
				} while (!models.empty());
			}

			void CDocumentator::AddIdsToInterfaces(const Options &options)
			{
				// CInterface::Bases (json)
				int64 offset{ 0 };
				std::vector<ReleasablePtr<models::CInterface>> models;
				do
				{
					models = models::CInterface::Find()->Limit(BATCH_SIZE)->Offset(offset)->All();
					for (auto model : models)
					{
						if (m_pProgressListener)
						{
							m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
							if (m_bAborted)
								return;
						}
						if (model->Bases.bNull)
							continue;
						Variable v_bases;
						if (!json::Decoder::Decode(model->Bases, v_bases))
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Cannot decode Bases of interface #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						if (v_bases.type() != VariableType::Array)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Invalid Bases of interface #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						bool changed{ false };
						for (size_t base_i = 0; base_i < v_bases.size(); base_i++)
						{
							String name;
							if (v_bases[base_i].has(L"qualified"))
								name = String(v_bases[base_i][L"qualified"]);
							else
								name = String(v_bases[base_i][L"name"]);
							bool root_only{ false };
							if (name.find(L"::") == 0)
							{
								name.erase(0, 2);
								root_only = true;
							}
							if (!root_only && options.NoWarnSpecifiers.find(name) != options.NoWarnSpecifiers.end())
								continue;
							if (name.empty())
								continue;
							auto entities{ models::CEntity::Find()->Where(DbConditions{
									db::eqcv(L"version", options.Version),
									root_only ? db::eqcv(L"qualified", name) : db::o(db::eqcv(L"qualified", name), db::lkc(L"qualified", L"%::" + name)),
									db::inc(L"type", DbRow{ L"interface", L"class", L"struct" })
								})->Limit(2)->All()
							};
							if (entities.empty())
							{
								if (m_pWarningListener)
								{
									m_pWarningListener->NotifyOnWarning(
										__FUNCTION__,
										__LINE__,
										ErrorInfo{ 0, L"Base '{name}' is not found for interface #{id}" },
										E(L"{name}", name, L"{id}", ToString((uint)model->Id))
									);
								}
								continue;
							}
							if (entities.size() != 1)
							{
								if (m_pWarningListener)
								{
									m_pWarningListener->NotifyOnWarning(
										__FUNCTION__,
										__LINE__,
										ErrorInfo{ 0, L"Multiple '{name}' bases are found for interface #{id}" },
										E(L"{name}", name, L"{id}", ToString((uint)model->Id))
									);
								}
								continue;
							}
							v_bases[base_i][L"id"] = (int64)entities[0]->Id;
							changed = true;
						}
						if (changed)
						{
							model->Bases = json::Encoder::Encode(v_bases);
							model->Save(false);
						}
					}
					offset += BATCH_SIZE;
				} while (!models.empty());
			}

			void CDocumentator::AddIdsToClasses(const Options &options)
			{
				// CClass::Bases (json)
				int64 offset{ 0 };
				std::vector<ReleasablePtr<models::CClass>> models;
				do
				{
					models = models::CClass::Find()->Limit(BATCH_SIZE)->Offset(offset)->All();
					for (auto model : models)
					{
						if (m_pProgressListener)
						{
							m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
							if (m_bAborted)
								return;
						}
						if (model->Bases.bNull)
							continue;
						Variable v_bases;
						if (!json::Decoder::Decode(model->Bases, v_bases))
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Cannot decode Bases of class #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						if (v_bases.type() != VariableType::Array)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Invalid Bases of class #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						bool changed{ false };
						for (size_t base_i = 0; base_i < v_bases.size(); base_i++)
						{
							String name;
							if (v_bases[base_i].has(L"qualified"))
								name = String(v_bases[base_i][L"qualified"]);
							else
								name = String(v_bases[base_i][L"name"]);
							bool root_only{ false };
							if (name.find(L"::") == 0)
							{
								name.erase(0, 2);
								root_only = true;
							}
							if (!root_only && options.NoWarnSpecifiers.find(name) != options.NoWarnSpecifiers.end())
								continue;
							if (name.empty())
								continue;
							auto entities{ models::CEntity::Find()->Where(DbConditions{
									db::eqcv(L"version", options.Version),
									root_only ? db::eqcv(L"qualified", name) : db::o(db::eqcv(L"qualified", name), db::lkc(L"qualified", L"%::" + name)),
									db::inc(L"type", DbRow{ L"interface", L"class", L"struct" })
								})->Limit(2)->All()
							};
							if (entities.empty())
							{
								if (m_pWarningListener)
								{
									m_pWarningListener->NotifyOnWarning(
										__FUNCTION__,
										__LINE__,
										ErrorInfo{ 0, L"Base '{name}' is not found for class #{id}" },
										E(L"{name}", name, L"{id}", ToString((uint)model->Id))
									);
								}
								continue;
							}
							if (entities.size() != 1)
							{
								if (m_pWarningListener)
								{
									m_pWarningListener->NotifyOnWarning(
										__FUNCTION__,
										__LINE__,
										ErrorInfo{ 0, L"Multiple '{name}' bases are found for class #{id}" },
										E(L"{name}", name, L"{id}", ToString((uint)model->Id))
									);
								}
								continue;
							}
							v_bases[base_i][L"id"] = (int64)entities[0]->Id;
							changed = true;
						}
						if (changed)
						{
							model->Bases = json::Encoder::Encode(v_bases);
							model->Save(false);
						}
					}
					offset += BATCH_SIZE;
				} while (!models.empty());
			}

			void CDocumentator::AddIdsToStructs(const Options &options)
			{
				// CStruct::Bases (json)
				int64 offset{ 0 };
				std::vector<ReleasablePtr<models::CStruct>> models;
				do
				{
					models = models::CStruct::Find()->Limit(BATCH_SIZE)->Offset(offset)->All();
					for (auto model : models)
					{
						if (m_pProgressListener)
						{
							m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
							if (m_bAborted)
								return;
						}
						if (model->Bases.bNull)
							continue;
						Variable v_bases;
						if (!json::Decoder::Decode(model->Bases, v_bases))
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Cannot decode Bases of struct #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						if (v_bases.type() != VariableType::Array)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Invalid Bases of struct #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						bool changed{ false };
						for (size_t base_i = 0; base_i < v_bases.size(); base_i++)
						{
							String name;
							if (v_bases[base_i].has(L"qualified"))
								name = String(v_bases[base_i][L"qualified"]);
							else
								name = String(v_bases[base_i][L"name"]);
							bool root_only{ false };
							if (name.find(L"::") == 0)
							{
								name.erase(0, 2);
								root_only = true;
							}
							if (!root_only && options.NoWarnSpecifiers.find(name) != options.NoWarnSpecifiers.end())
								continue;
							if (name.empty())
								continue;
							auto entities{ models::CEntity::Find()->Where(DbConditions{
									db::eqcv(L"version", options.Version),
									root_only ? db::eqcv(L"qualified", name) : db::o(db::eqcv(L"qualified", name), db::lkc(L"qualified", L"%::" + name)),
									db::inc(L"type", DbRow{ L"interface", L"class", L"struct" })
								})->Limit(2)->All()
							};
							if (entities.empty())
							{
								if (m_pWarningListener)
								{
									m_pWarningListener->NotifyOnWarning(
										__FUNCTION__,
										__LINE__,
										ErrorInfo{ 0, L"Base '{name}' is not found for struct #{id}" },
										E(L"{name}", name, L"{id}", ToString((uint)model->Id))
									);
								}
								continue;
							}
							if (entities.size() != 1)
							{
								if (m_pWarningListener)
								{
									m_pWarningListener->NotifyOnWarning(
										__FUNCTION__,
										__LINE__,
										ErrorInfo{ 0, L"Multiple '{name}' bases are found for struct #{id}" },
										E(L"{name}", name, L"{id}", ToString((uint)model->Id))
									);
								}
								continue;
							}
							v_bases[base_i][L"id"] = (int64)entities[0]->Id;
							changed = true;
						}
						if (changed)
						{
							model->Bases = json::Encoder::Encode(v_bases);
							model->Save(false);
						}
					}
					offset += BATCH_SIZE;
				} while (!models.empty());
			}

			void CDocumentator::AddIdsToFunctions(const Options &options)
			{
				// CFunction::Specifiers (json)
				// CFunction::Trailing (string) ?
				int64 offset{ 0 };
				std::vector<ReleasablePtr<models::CFunction>> models;
				do
				{
					models = models::CFunction::Find()->Limit(BATCH_SIZE)->Offset(offset)->With(L"Entity.Tags")->All();
					for (auto model : models)
					{
						if (m_pProgressListener)
						{
							m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
							if (m_bAborted)
								return;
						}
						if (model->Specifiers.bNull)
							continue;
						Variable v_specifiers;
						if (!json::Decoder::Decode(model->Specifiers, v_specifiers))
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Cannot decode Specifiers of function #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						if (v_specifiers.type() != VariableType::Array)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Invalid Specifiers of function #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						String name, type;
						for (size_t specifier_i = 0; specifier_i < v_specifiers.size(); specifier_i++)
						{
							Variable &v_specifier{ v_specifiers[specifier_i] };
							if (String(v_specifier[L"type"]) == L"enum")
							{
								name = String(v_specifier[L"name"]);
								type = L"enum";
								break;
							}
							if (String(v_specifier[L"type"]) == L"class")
							{
								name = String(v_specifier[L"name"]);
								type = L"class";
								break;
							}
							if (String(v_specifier[L"type"]) == L"struct")
							{
								name = String(v_specifier[L"name"]);
								type = L"struct";
								break;
							}
							if (String(v_specifier[L"type"]) == L"union")
							{
								name = String(v_specifier[L"name"]);
								type = L"union";
								break;
							}
							if (String(v_specifier[L"type"]) == L"name")
							{
								name = String(v_specifier[L"name"]);
								break;
							}
						}
						bool root_only{ GetQualifiedNameFromTags(model->Entity->Tags, name) };
						if (!root_only && name.find(L"::") == 0)
						{
							name.erase(0, 2);
							root_only = true;
						}
						if (!root_only && type.empty() && options.NoWarnSpecifiers.find(name) != options.NoWarnSpecifiers.end())
							continue;
						if (name.empty())
							continue;
						std::vector<ReleasablePtr<models::CEntity>> entities;
						DbConditions conditions;
						conditions.push_back(db::eqcv(L"version", options.Version));
						if (root_only)
							conditions.push_back(db::eqcv(L"qualified", name));
						else
							conditions.push_back(db::o(db::eqcv(L"qualified", name), db::lkc(L"qualified", L"%::" + name)));
						if (type.empty())
							conditions.push_back(db::inc(L"type", DbRow{ L"interface", L"class", L"struct", L"union", L"enum", L"alias", L"typedef" }));
						else if (type == L"class")
							conditions.push_back(db::inc(L"type", DbRow{ L"interface", L"class" }));
						else
							conditions.push_back(db::eqcv(L"type", type));
						entities = models::CEntity::Find()->Where(conditions)->Limit(2)->All();
						if (entities.empty())
						{
							if (m_pWarningListener)
							{
								m_pWarningListener->NotifyOnWarning(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Specifier '{name}' is not found for function #{id}" },
									E(L"{name}", name, L"{id}", ToString((uint)model->Id))
								);
							}
							continue;
						}
						if (entities.size() != 1)
						{
							if (m_pWarningListener)
							{
								m_pWarningListener->NotifyOnWarning(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Multiple '{name}' specifiers are found for function #{id}" },
									E(L"{name}", name, L"{id}", ToString((uint)model->Id))
								);
							}
							continue;
						}
						model->SpecifierId = (uint)entities[0]->Id;
						model->Save(false);
					}
					offset += BATCH_SIZE;
				} while (!models.empty());
			}

			void CDocumentator::AddIdsToParameters(const Options &options)
			{
				// CParameter::Declaration (json)
				int64 offset{ 0 };
				std::vector<ReleasablePtr<models::CParameter>> models;
				do
				{
					models = models::CParameter::Find()->Limit(BATCH_SIZE)->Offset(offset)->With(L"Entity.Tags")->All();
					for (auto model : models)
					{
						if (m_pProgressListener)
						{
							m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
							if (m_bAborted)
								return;
						}
						Variable v_declaration;
						if (!json::Decoder::Decode(model->Declaration, v_declaration))
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Cannot decode Declaration of parameter #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						if (!v_declaration.has(L"specifiers"))
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Invalid Declaration of parameter #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						Variable &v_specifiers{ v_declaration[L"specifiers"] };
						if (v_specifiers.type() != VariableType::Array)
						{
							if (m_pErrorListener)
							{
								m_pErrorListener->NotifyOnError(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Invalid Declaration of parameter #{id}" },
									E(L"{id}", ToString((uint)model->Id))
								);
							}
							break;
						}
						String name, type;
						for (size_t specifier_i = 0; specifier_i < v_specifiers.size(); specifier_i++)
						{
							Variable &v_specifier{ v_specifiers[specifier_i] };
							if (String(v_specifier[L"type"]) == L"enum")
							{
								name = String(v_specifier[L"name"]);
								type = L"enum";
								break;
							}
							if (String(v_specifier[L"type"]) == L"class")
							{
								name = String(v_specifier[L"name"]);
								type = L"class";
								break;
							}
							if (String(v_specifier[L"type"]) == L"struct")
							{
								name = String(v_specifier[L"name"]);
								type = L"struct";
								break;
							}
							if (String(v_specifier[L"type"]) == L"union")
							{
								name = String(v_specifier[L"name"]);
								type = L"union";
								break;
							}
							if (String(v_specifier[L"type"]) == L"name")
							{
								name = String(v_specifier[L"name"]);
								break;
							}
						}
						bool root_only{ GetQualifiedNameFromTags(model->Entity->Tags, name) };
						if (!root_only && name.find(L"::") == 0)
						{
							name.erase(0, 2);
							root_only = true;
						}
						if (!root_only && type.empty() && options.NoWarnSpecifiers.find(name) != options.NoWarnSpecifiers.end())
							continue;
						if (name.empty())
							continue;
						std::vector<ReleasablePtr<models::CEntity>> entities;
						DbConditions conditions;
						conditions.push_back(db::eqcv(L"version", options.Version));
						if (root_only)
							conditions.push_back(db::eqcv(L"qualified", name));
						else
							conditions.push_back(db::o(db::eqcv(L"qualified", name), db::lkc(L"qualified", L"%::" + name)));
						if (type.empty())
							conditions.push_back(db::inc(L"type", DbRow{ L"interface", L"class", L"struct", L"union", L"enum", L"alias", L"typedef" }));
						else if (type == L"class")
							conditions.push_back(db::inc(L"type", DbRow{ L"interface", L"class" }));
						else
							conditions.push_back(db::eqcv(L"type", type));
						entities = models::CEntity::Find()->Where(conditions)->Limit(2)->All();
						if (entities.empty())
						{
							if (m_pWarningListener)
							{
								m_pWarningListener->NotifyOnWarning(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Specifier '{name}' is not found for parameter #{id}" },
									E(L"{name}", name, L"{id}", ToString((uint)model->Id))
								);
							}
							continue;
						}
						if (entities.size() != 1)
						{
							if (m_pWarningListener)
							{
								m_pWarningListener->NotifyOnWarning(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Multiple '{name}' specifiers are found for parameter #{id}" },
									E(L"{name}", name, L"{id}", ToString((uint)model->Id))
								);
							}
							continue;
						}
						model->SpecifierId = (uint)entities[0]->Id;
						model->Save(false);
					}
					offset += BATCH_SIZE;
				} while (!models.empty());
			}

			void CDocumentator::AddIdsToAliases(const Options &options)
			{
				// CAlias::Type (string) ?
				int64 offset{ 0 };
				std::vector<ReleasablePtr<models::CAlias>> models;
				do
				{
					models = models::CAlias::Find()->Limit(BATCH_SIZE)->Offset(offset)->With(L"Entity.Tags")->All();
					for (auto model : models)
					{
						if (m_pProgressListener)
						{
							m_pProgressListener->NotifyOnProgress(ProgressStage::Decoding, Progress{ 0, 0 }, m_bAborted);
							if (m_bAborted)
								return;
						}
						String name;
						bool root_only{ GetQualifiedNameFromTags(model->Entity->Tags, name) };
						if (!root_only && name.find(L"::") == 0)
						{
							name.erase(0, 2);
							root_only = true;
						}
						if (name.empty())
							continue;
						std::vector<ReleasablePtr<models::CEntity>> entities;
						if (root_only)
						{
							entities = models::CEntity::Find()
								->Where(
									DbConditions{
										db::eqcv(L"version", options.Version),
										db::eqcv(L"qualified", name)
									})
								->Limit(2)
								->All();
						}
						else
						{
							entities = models::CEntity::Find()
								->Where(
									DbConditions{
										db::eqcv(L"version", options.Version),
										db::o(db::eqcv(L"qualified", name), db::lkc(L"qualified", L"%::" + name))
									})
								->Limit(2)
								->All();
						}
						if (entities.empty())
						{
							if (m_pWarningListener)
							{
								m_pWarningListener->NotifyOnWarning(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Type '{name}' is not found for alias #{id}" },
									E(L"{name}", name, L"{id}", ToString((uint)model->Id))
								);
							}
							continue;
						}
						if (entities.size() != 1)
						{
							if (m_pWarningListener)
							{
								m_pWarningListener->NotifyOnWarning(
									__FUNCTION__,
									__LINE__,
									ErrorInfo{ 0, L"Multiple '{name}' types are found for alias #{id}" },
									E(L"{name}", name, L"{id}", ToString((uint)model->Id))
								);
							}
							continue;
						}
						model->TypeId = (uint)entities[0]->Id;
						model->Save(false);
					}
					offset += BATCH_SIZE;
				} while (!models.empty());
			}
		#pragma endregion
		}
	}
}