// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		namespace xml
		{
			String Encoder::Encode(const Entity &source, const bool compact, IProgressListener *progress_listener)
			{
				if (source.type() != EntityType::Array)
					return L"";
				bool abort{ false }, first{ true };
				size_t total{ progress_listener ? source.count() : 0 }, counter{ 0 };
				String result;
				// Prologs
				for (size_t i = 0; i < source.size(true); i++)
					if (source[i].type() == EntityType::Prolog)
					{
						if (!compact && !first)
							result += L"\n";
						result += (String)source[i];
						first = false;
						counter++;
						if (progress_listener)
						{
							progress_listener->NotifyOnProgress(ProgressStage::Encoding, Progress{ counter, total }, abort);
							if (abort)
								return L"";
						}
					}
				// Doc-types
				for (size_t i = 0; i < source.size(true); i++)
					if (source[i].type() == EntityType::Doctype)
					{
						if (!compact && !first)
							result += L"\n";
						result += (String)source[i];
						first = false;
						counter++;
						if (progress_listener)
						{
							progress_listener->NotifyOnProgress(ProgressStage::Encoding, Progress{ counter, total }, abort);
							if (abort)
								return L"";
						}
					}
				// Elements
				for (size_t i = 0; i < source.size(true); i++)
					switch (source[i].type())
					{
					case EntityType::Element:
						if (compact)
							result += (String)source[i];
						else
						{
							if (!first)
								result += L"\n";
							if (source[i].value().empty())
								result += L"<" + source[i].name() + EncodeAttributes(source[i]) + L" />";
							else
								result += L"<" + source[i].name() + EncodeAttributes(source[i]) + L">" + EncodeValue(source[i]) + L"</" + source[i].name() + L">";
							first = false;
						}
						break;
					case EntityType::Data:
						if (compact)
							result += (String)source[i];
						else
						{
							if (!first)
								result += L"\n";
							if (source[i].value().empty())
								result += L"<" + source[i].name() + EncodeAttributes(source[i]) + L" />";
							else
								result += L"<" + source[i].name() + EncodeAttributes(source[i]) + L"><![CDATA[" + source[i].value() + L"]]></" + source[i].name() + L">";
							first = false;
						}
						counter++;
						if (progress_listener)
						{
							progress_listener->NotifyOnProgress(ProgressStage::Encoding, Progress{ counter, total }, abort);
							if (abort)
								return L"";
						}
						break;
					case EntityType::Array:
						if (!compact && !first)
							result += L"\n";
						result += EncodeArray(source[i], compact, progress_listener, L"", total, counter, abort);
						first = false;
						if (abort)
							return L"";
						break;
					default:
						break;
					}
				if (abort)
					return L"";
				return result;
			}

			String Encoder::EncodeArray(const Entity &source, const bool compact, IProgressListener *progress_listener, const String &shift, const size_t total, size_t &counter, bool &abort)
			{
				if (source.size(true) == 0 && source.value().empty())
				{
					counter++;
					return L"<" + source.name() + EncodeAttributes(source) + L"/>";
				}
				String result{ shift + L"<" + source.name() + EncodeAttributes(source) + L">" }, sh{ compact ? L"" : (shift + L"    ") };
				for (size_t i = 0; i < source.size(true); i++)
					switch (source[i].type())
					{
					case EntityType::Element:
						if (compact)
							result += (String)source[i];
						else
						{
							if (source[i].value().empty())
								result += L"\n" + sh + L"<" + source[i].name() + EncodeAttributes(source[i]) + L" />";
							else
								result += L"\n" + sh + L"<" + source[i].name() + EncodeAttributes(source[i]) + L">" + EncodeValue(source[i]) + L"</" + source[i].name() + L">";
						}
						if (progress_listener)
						{
							progress_listener->NotifyOnProgress(ProgressStage::Encoding, Progress{ counter, total }, abort);
							if (abort)
								return L"";
						}
						break;
					case EntityType::Data:
						if (compact)
							result += (String)source[i];
						else
						{
							if (source[i].value().empty())
								result += L"\n" + sh + L"<" + source[i].name() + EncodeAttributes(source[i]) + L" />";
							else
								result += L"\n" + sh + L"<" + source[i].name() + EncodeAttributes(source[i]) + L"><![CDATA[" + source[i].value() + L"]]></" + source[i].name() + L">";
						}
						counter++;
						if (progress_listener)
						{
							progress_listener->NotifyOnProgress(ProgressStage::Encoding, Progress{ counter, total }, abort);
							if (abort)
								return L"";
						}
						break;
					case EntityType::Array:
						if (!compact)
							result += L"\n";
						result += EncodeArray(source[i], compact, progress_listener, sh, total, counter, abort);
						counter++;
						if (abort)
							return L"";
						break;
					default:
						break;
					}
				if (!compact)
					result += L"\n";
				return result + shift + L"</" + source.name() +L">";
			}

			String Encoder::EncodeAttributes(const Entity &source)
			{
				String result;
				for (auto pos = source.begin(); pos != source.end(); pos++)
					result += L" " + pos->first + L"=\"" + ReplaceAll(pos->second, StringKeyValue{ L"\"", L"\\\"" }) + L"\"";
				return result;
			}

			String Encoder::EncodeValue(const Entity &source)
			{
				return ReplaceAll(source.value(), StringKeyValueArray{ StringKeyValue{ L">", L"&gt;" }, StringKeyValue{ L"<", L"&lt;" } });
			}
		}
	}
}