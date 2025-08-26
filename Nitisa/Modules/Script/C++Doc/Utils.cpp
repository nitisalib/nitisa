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
			void Tokenize(cpp::CTokenizer &tokenizer, const String &source, Tokens &tokens)
			{
				tokens.clear();
				tokenizer.Reader->setSource(source);
				size_t index{ 0 };
				while (tokenizer.Next(index, tokens));
				
				// Remove new lines and spaces from the beginning
				for (index = 0; index < tokens.size(); index++)
				{
					if ((tokens[index].Type == TokenType::Group || tokens[index].Type == TokenType::Operator) && 
						(tokens[index].Op->Group == GROUP_NEW_LINE || tokens[index].Op->Group == GROUP_SPACE))
						continue;
					break;
				}
				if (index > 0)
					tokens.erase(tokens.begin(), tokens.begin() + index);

				// Remove new lines and spaces from the end
				for (index = tokens.size(); index > 0; index--)
				{
					if ((tokens[index - 1].Type == TokenType::Group || tokens[index - 1].Type == TokenType::Operator) &&
						(tokens[index - 1].Op->Group == GROUP_NEW_LINE || tokens[index - 1].Op->Group == GROUP_SPACE))
						continue;
					break;
				}
				if (index < tokens.size())
					tokens.erase(tokens.begin() + index, tokens.end());
			}

			List *MakeList(Tokens &tokens, List **tail)
			{
				List *head{ nullptr }, *t{ nullptr };
				for (auto &token : tokens)
					t = Append(head, t, TokenEx{ &token, token.Index });
				if (tail)
					*tail = t;
				return head;
			}

			bool isSLComment(List &list)
			{
				return list.Item->Type == TokenType::String && list.Item->Op->Name == L"//";
			}

			bool isMLComment(List &list)
			{
				return list.Item->Type == TokenType::String && list.Item->Op->Name == L"/*";
			}

			bool isComment(List &list)
			{
				return list.Item->Type == TokenType::String && (list.Item->Op->Name == L"//" || list.Item->Op->Name == L"/*");
			}

			bool isSpaces(List &list)
			{
				return (list.Item->Type == TokenType::Group || list.Item->Type == TokenType::Operator) && list.Item->Op->Group == GROUP_SPACE;
			}

			bool isNewLines(List &list)
			{
				return (list.Item->Type == TokenType::Group || list.Item->Type == TokenType::Operator) && list.Item->Op->Group == GROUP_NEW_LINE;
			}

			List *Next(List &list, const bool skip_spaces, const bool skip_ml_comments, const bool skip_sl_comments, const bool skip_new_lines)
			{
				List *current{ list.Next };
				while (current)
				{
					if (skip_spaces && isSpaces(*current))
					{
						current = current->Next;
						continue;
					}
					if (skip_ml_comments && isMLComment(*current))
					{
						current = current->Next;
						continue;
					}
					if (skip_sl_comments && isSLComment(*current))
					{
						current = current->Next;
						continue;
					}
					if (skip_new_lines && isNewLines(*current))
					{
						current = current->Next;
						continue;
					}
					break;
				}
				return current;
			}

			List *Next(List &list, List &end, const bool skip_spaces, const bool skip_ml_comments, const bool skip_sl_comments, const bool skip_new_lines)
			{
				if (&list == &end)
					return nullptr;
				List *current{ list.Next };
				while (current)
				{
					if (skip_spaces && isSpaces(*current))
					{
						if (current == &end)
							return nullptr;
						current = current->Next;
						continue;
					}
					if (skip_ml_comments && isMLComment(*current))
					{
						if (current == &end)
							return nullptr;
						current = current->Next;
						continue;
					}
					if (skip_sl_comments && isSLComment(*current))
					{
						if (current == &end)
							return nullptr;
						current = current->Next;
						continue;
					}
					if (skip_new_lines && isNewLines(*current))
					{
						if (current == &end)
							return nullptr;
						current = current->Next;
						continue;
					}
					break;
				}
				return current;
			}

			List *Prev(List &list, const bool skip_spaces, const bool skip_ml_comments, const bool skip_sl_comments, const bool skip_new_lines)
			{
				List *current{ list.Prev };
				while (current)
				{
					if (skip_spaces && isSpaces(*current))
					{
						current = current->Prev;
						continue;
					}
					if (skip_ml_comments && isMLComment(*current))
					{
						current = current->Prev;
						continue;
					}
					if (skip_sl_comments && isSLComment(*current))
					{
						current = current->Prev;
						continue;
					}
					if (skip_new_lines && isNewLines(*current))
					{
						current = current->Prev;
						continue;
					}
					break;
				}
				return current;
			}

			StringKeyValueArray E(const String &key1, const String &val1)
			{
				return StringKeyValueArray{
					StringKeyValue{ key1, val1 }
				};
			}

			StringKeyValueArray E(const String &key1, const String &val1, const String &key2, const String &val2)
			{
				return StringKeyValueArray{
					StringKeyValue{ key1, val1 },
					StringKeyValue{ key2, val2 }
				};
			}

			StringKeyValueArray E(const String &key1, const String &val1, const String &key2, const String &val2, const String &key3, const String &val3)
			{
				return StringKeyValueArray{
					StringKeyValue{ key1, val1 },
					StringKeyValue{ key2, val2 },
					StringKeyValue{ key3, val3 }
				};
			}

			String DumpTokens(List &list, const String &before, const String &after, const size_t before_count, const size_t after_count)
			{
				String result;
				List *current{ list.Prev };
				for (size_t i = 0; i < before_count && current; i++, current = current->Prev)
					if (result.empty())
						result = TokenToString(*current->Item);
					else
						result = TokenToString(*current->Item) + L" " + result;
				if (!result.empty())
					result += L" ";
				result += before + TokenToString(*list.Item) + after;
				current = list.Next;
				for (size_t i = 0; i < after_count && current; i++, current = current->Next)
					result += L" " + TokenToString(*current->Item);
				return result;
			}

			IDb::Migrations GetMigrations()
			{
				return IDb::Migrations{
					new migrations::CMigrationV1()
				};
			}
		}
	}
}