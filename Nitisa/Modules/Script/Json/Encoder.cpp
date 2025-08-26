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
		namespace json
		{
			CLexic Encoder::m_cLexic{ nullptr };

		#pragma region From Object
			String Encoder::Encode(const Variable &source, const bool compact, IProgressListener *progress_listener)
			{
				bool abort{ false };
				size_t total{ progress_listener ? source.count() : 0 }, counter{ 0 };
				switch (source.type())
				{
				case VariableType::Object:
					return EncodeObject(source, compact, progress_listener, L"", total, counter, abort);
				case VariableType::Array:
					return EncodeArray(source, compact, progress_listener, L"", total, counter, abort);
				case VariableType::Bool:
				case VariableType::Integer:
				case VariableType::Float:
					return (String)source;
				case VariableType::Null:
					return L"null";
				case VariableType::String:
					return L"\"" + Escape((String)source) + L"\"";
				default:
					return L"";
				}
			}

			String Encoder::EncodeObject(const Variable &source, const bool compact, IProgressListener *progress_listener, const String &shift, const size_t total, size_t &counter, bool &abort)
			{
				String result{ L"{" }, sh{ compact ? L"" : (shift + L"    ") };
				if (!compact)
					result += L"\n";
				size_t index{ 0 };
				for (auto pos = source.begin(); pos != source.end(); pos++, index++)
				{
					if (!compact)
						result += sh;
					result += L"\"" + Escape(pos->first) + L"\":";
					if (!compact)
						result += L" ";
					switch (pos->second.type())
					{
					case VariableType::String:
						result += L"\"" + Escape((String)pos->second) + L"\"";
						break;
					case VariableType::Null:
						result += L"null";
						break;
					case VariableType::Object:
						result += EncodeObject(pos->second, compact, progress_listener, sh, total, counter, abort);
						break;
					case VariableType::Array:
						result += EncodeArray(pos->second, compact, progress_listener, sh, total, counter, abort);
						break;
					default:
						result += (String)pos->second;
					}
					if (index < source.size() - 1)
						result += L",";
					if (!compact)
						result += L"\n";
					if (progress_listener)
					{
						if (pos->second.type() != VariableType::Object && pos->second.type() != VariableType::Array)
							counter++;
						progress_listener->NotifyOnProgress(ProgressStage::Encoding, Progress{ counter, total }, abort);
						if (abort)
							return L"";
					}
				}
				result += shift + L"}";
				if (progress_listener)
				{
					progress_listener->NotifyOnProgress(ProgressStage::Encoding, Progress{ counter++, total }, abort);
					if (abort)
						return L"";
				}
				return result;
			}

			String Encoder::EncodeArray(const Variable &source, const bool compact, IProgressListener *progress_listener, const String &shift, const size_t total, size_t &counter, bool &abort)
			{
				String result{ L"[" }, sh{ compact ? L"" : (shift + L"    ") };
				if (!compact)
					result += L"\n";
				for (size_t i = 0; i < source.size(); i++)
				{
					if (!compact)
						result += sh;
					switch (source[i].type())
					{
					case VariableType::String:
						result += L"\"" + Escape((String)source[i]) + L"\"";
						break;
					case VariableType::Null:
						result += L"null";
						break;
					case VariableType::Object:
						result += EncodeObject(source[i], compact, progress_listener, sh, total, counter, abort);
						break;
					case VariableType::Array:
						result += EncodeArray(source[i], compact, progress_listener, sh, total, counter, abort);
						break;
					default:
						result += (String)source[i];
					}
					if (i < source.size() - 1)
						result += L",";
					if (!compact)
						result += L"\n";
					if (progress_listener)
					{
						if (source[i].type() != VariableType::Object && source[i].type() != VariableType::Array)
							counter++;
						progress_listener->NotifyOnProgress(ProgressStage::Encoding, Progress{ counter, total }, abort);
						if (abort)
							return L"";
					}
				}
				result += shift + L"]";
				if (progress_listener)
				{
					progress_listener->NotifyOnProgress(ProgressStage::Encoding, Progress{ counter++, total }, abort);
					if (abort)
						return L"";
				}
				return result;
			}
		#pragma endregion

		#pragma region From Variant
			String Encoder::Encode(const Variant &source, const bool compact, IProgressListener *progress_listener)
			{
				bool abort{ false };
				size_t total{ 0 }, counter{ 0 };
				switch (source.getType())
				{
				case Variant::VariantType::Map:
					return EncodeObject(source, compact, progress_listener, L"", total, counter, abort);
				case Variant::VariantType::Array:
					return EncodeArray(source, compact, progress_listener, L"", total, counter, abort);
				case Variant::VariantType::Pointer:
					return L"null";
				case Variant::VariantType::Bool:
				case Variant::VariantType::Integer:
				case Variant::VariantType::UnsignedInteger:
					return (String)source;
				case Variant::VariantType::Float:
					return ToStringCompact((float)source);
				case Variant::VariantType::String:
					return L"\"" + Escape((String)source) + L"\"";
				default:
					return L"";
				}
			}

			String Encoder::EncodeObject(const Variant &source, const bool compact, IProgressListener *progress_listener, const String &shift, const size_t total, size_t &counter, bool &abort)
			{
				String result{ L"{" }, sh{ compact ? L"" : (shift + L"    ") };
				if (!compact)
					result += L"\n";
				size_t index{ 0 };
				for (auto pos = source.begin(); pos != source.end(); pos++, index++)
				{
					if (!compact)
						result += sh;
					result += L"\"" + Escape(pos->first) + L"\":";
					if (!compact)
						result += L" ";
					switch (pos->second.getType())
					{
					case Variant::VariantType::Pointer:
						result += L"null";
						break;
					case Variant::VariantType::Float:
						result += ToStringCompact((float)pos->second);
						break;
					case Variant::VariantType::String:
						result += L"\"" + Escape((String)pos->second) + L"\"";
						break;
					case Variant::VariantType::Map:
						result += EncodeObject(pos->second, compact, progress_listener, sh, total, counter, abort);
						break;
					case Variant::VariantType::Array:
						result += EncodeArray(pos->second, compact, progress_listener, sh, total, counter, abort);
						break;
					default:
						result += (String)pos->second;
					}
					if (index < source.size() - 1)
						result += L",";
					if (!compact)
						result += L"\n";
					if (progress_listener)
					{
						if (pos->second.getType() != Variant::VariantType::Map && pos->second.getType() != Variant::VariantType::Array)
							counter++;
						progress_listener->NotifyOnProgress(ProgressStage::Encoding, Progress{ counter, total }, abort);
						if (abort)
							return L"";
					}
				}
				result += shift + L"}";
				if (progress_listener)
				{
					progress_listener->NotifyOnProgress(ProgressStage::Encoding, Progress{ counter++, total }, abort);
					if (abort)
						return L"";
				}
				return result;
			}

			String Encoder::EncodeArray(const Variant &source, const bool compact, IProgressListener *progress_listener, const String &shift, const size_t total, size_t &counter, bool &abort)
			{
				String result{ L"[" }, sh{ compact ? L"" : (shift + L"    ") };
				if (!compact)
					result += L"\n";
				for (int i = 0; i < (int)source.size(); i++)
				{
					if (!compact)
						result += sh;
					Variant s{ source.get(i) };
					switch (s.getType())
					{
					case Variant::VariantType::Pointer:
						result += L"null";
						break;
					case Variant::VariantType::Float:
						result += ToStringCompact((float)s);
						break;
					case Variant::VariantType::String:
						result += L"\"" + Escape((String)s) + L"\"";
						break;
					case Variant::VariantType::Map:
						result += EncodeObject(s, compact, progress_listener, sh, total, counter, abort);
						break;
					case Variant::VariantType::Array:
						result += EncodeArray(s, compact, progress_listener, sh, total, counter, abort);
						break;
					default:
						result += (String)s;
					}
					if (i < (int)source.size() - 1)
						result += L",";
					if (!compact)
						result += L"\n";
					if (progress_listener)
					{
						if (s.getType() != Variant::VariantType::Map && s.getType() != Variant::VariantType::Array)
							counter++;
						progress_listener->NotifyOnProgress(ProgressStage::Encoding, Progress{ counter, total }, abort);
						if (abort)
							return L"";
					}
				}
				result += shift + L"]";
				if (progress_listener)
				{
					progress_listener->NotifyOnProgress(ProgressStage::Encoding, Progress{ counter++, total }, abort);
					if (abort)
						return L"";
				}
				return result;
			}
		#pragma endregion

		#pragma region Helpers
			String Encoder::Escape(const String &value)
			{
				String result;
				size_t i{ 0 };
				while (i < value.length())
				{
					if (value[i] == L'"')
					{
						result += L"\\\"";
						i++;
						continue;
					}
					if (value[i] == L'\\')
					{
						result += L"\\\\";
						i++;
						continue;
					}
					if (value[i] == L'\n')
					{
						result += L"\\n";
						i++;
						continue;
					}
					if (value[i] == L'\r')
					{
						result += L"\\r";
						i++;
						continue;
					}
					if (value[i] == L'\t')
					{
						result += L"\\t";
						i++;
						continue;
					}
					result += value[i++];
				}
				return result;

				/*String result{ ReplaceAll(value, L"\\\\", L"\\") };
				ReplaceAllDirect(result, L"\\\"", L"\"");
				ReplaceAllDirect(result, L"\\\n", L"\n");
				ReplaceAllDirect(result, L"\\\r", L"\r");
				ReplaceAllDirect(result, L"\\\t", L"\t");
				ReplaceAllDirect(result, L"\\", L"\\\\");
				ReplaceAllDirect(result, L"\"", L"\\\"");
				ReplaceAllDirect(result, L"\n", L"\\n");
				ReplaceAllDirect(result, L"\r", L"\\r");
				ReplaceAllDirect(result, L"\t", L"\\t");
				return result;*/
			}

			bool Encoder::IsIdentifier(const String &name)
			{
				if (name.empty())
					return false;
				if (!m_cLexic.IsIdentifier(name[0]) && !m_cLexic.IsIdentifierNotAll(name[0]))
					return false;
				for (size_t i = 1; i < name.length(); i++)
					if (!m_cLexic.IsIdentifier(name[i]) && !m_cLexic.IsIdentifierNotStart(name[i]) && !m_cLexic.IsIdentifierNotAll(name[i]))
						return false;
				return true;
			}
		#pragma endregion
		}
	}
}