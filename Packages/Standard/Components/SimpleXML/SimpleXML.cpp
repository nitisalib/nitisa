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
	namespace standard
	{
	#pragma region Constructor & destructor
		CSimpleXML::CSimpleXML() :
			CComponent(L"SimpleXML")
		{
			
		}

		CSimpleXML::CSimpleXML(IForm *parent) : CSimpleXML()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Getters
		String CSimpleXML::getVersion()
		{
			for (size_t i = 0; i < m_cEntity.size(); i++)
				if (m_cEntity[i].type() == script::xml::EntityType::Prolog && m_cEntity[i].name() == L"xml" && m_cEntity[i].has(L"version"))
					return m_cEntity[i][L"version"];
			return L"";
		}

		String CSimpleXML::getEncoding()
		{
			for (size_t i = 0; i < m_cEntity.size(); i++)
				if (m_cEntity[i].type() == script::xml::EntityType::Prolog && m_cEntity[i].name() == L"xml" && m_cEntity[i].has(L"encoding"))
					return m_cEntity[i][L"encoding"];
			return L"";
		}

		String CSimpleXML::getDoctype()
		{
			for (size_t i = 0; i < m_cEntity.size(); i++)
				if (m_cEntity[i].type() == script::xml::EntityType::Doctype)
					return m_cEntity[i].value();
			return L"";
		}

		script::xml::Entity &CSimpleXML::getRootNode()
		{
			return m_cEntity;;
		}
	#pragma endregion

	#pragma region Setters
		bool CSimpleXML::setVersion(const String &value)
		{
			for (size_t i = 0; i < m_cEntity.size(); i++)
				if (m_cEntity[i].type() == script::xml::EntityType::Prolog && m_cEntity[i].name() == L"xml" && m_cEntity[i].has(L"version"))
				{
					if (m_cEntity[i][L"version"] != value)
					{
						if (value.empty())
							m_cEntity[i].erase(m_cEntity[i].find(L"version"));
						else
							m_cEntity[i][L"version"] = value;
						return true;
					}
					return false;
				}
			if (!value.empty())
			{
				for (size_t i = 0; i < m_cEntity.size(); i++)
					if (m_cEntity[i].type() == script::xml::EntityType::Prolog && m_cEntity[i].name() == L"xml")
					{
						m_cEntity[i][L"version"] = value;
						return true;
					}
				script::xml::Entity xml{ L"xml" };
				xml.type(script::xml::EntityType::Prolog);
				xml[L"version"] = value;
				m_cEntity.push_back(xml);
				return true;
			}
			return false;
		}

		bool CSimpleXML::setEncoding(const String &value)
		{
			for (size_t i = 0; i < m_cEntity.size(); i++)
				if (m_cEntity[i].type() == script::xml::EntityType::Prolog && m_cEntity[i].name() == L"xml" && m_cEntity[i].has(L"encoding"))
				{
					if (m_cEntity[i][L"encoding"] != value)
					{
						if (value.empty())
							m_cEntity[i].erase(m_cEntity[i].find(L"encoding"));
						else
							m_cEntity[i][L"encoding"] = value;
						return true;
					}
					return false;
				}
			if (!value.empty())
			{
				for (size_t i = 0; i < m_cEntity.size(); i++)
					if (m_cEntity[i].type() == script::xml::EntityType::Prolog && m_cEntity[i].name() == L"xml")
					{
						m_cEntity[i][L"encoding"] = value;
						return true;
					}
				script::xml::Entity xml{ L"xml" };
				xml.type(script::xml::EntityType::Prolog);
				xml[L"encoding"] = value;
				m_cEntity.push_back(xml);
				return true;
			}
			return false;
		}

		bool CSimpleXML::setDoctype(const String &value)
		{
			for (size_t i = 0; i < m_cEntity.size(); i++)
				if (m_cEntity[i].type() == script::xml::EntityType::Doctype)
				{
					if (m_cEntity[i].value() != value)
					{
						if (value.empty())
							m_cEntity.erase(i);
						else
							m_cEntity[i].value(value);
						return true;
					}
					return false;
				}
			if (!value.empty())
			{
				script::xml::Entity doctype{ L"DOCTYPE" };
				doctype.type(script::xml::EntityType::Doctype);
				doctype.value(value);
				m_cEntity.push_back(doctype);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		String CSimpleXML::ToString(const bool compact)
		{
			return script::xml::Encoder::Encode(m_cEntity, compact);
		}

		bool CSimpleXML::Save(const String &filename, const bool compact)
		{
			return PutUTF8FileContent(filename, ToString(compact));
		}

		bool CSimpleXML::LoadFromFile(const String &filename, IErrorListener *error_listener)
		{
			return LoadFromString(GetUTF8FileContent(filename), error_listener);
		}

		bool CSimpleXML::LoadFromString(const String &value, IErrorListener *error_listener)
		{
			if (value.empty())
				return false;
			return script::xml::Decoder::Decode(value, m_cEntity, error_listener);
		}
	#pragma endregion
	}
}