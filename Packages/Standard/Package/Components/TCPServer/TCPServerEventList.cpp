// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
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
		CTCPServerEventList::CTCPServerEventList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentEventList(package, component, entity)
		{
			Add(new CEvent(this, component, L"OnConnect", L"{namespace}ITCPServer *sender, const AnsiString &local_ip, const int local_port, const AnsiString &remote_ip, const int remote_port, bool &accept", L"sender, local_ip, local_port, remote_ip, remote_port, accept"))
				->AddForwardDeclaration(L"class ITCPServer;", L"Standard/Components/ITCPServer.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/Strings.h");
			Add(new CEvent(this, component, L"OnConnected", L"{namespace}ITCPServer *sender, {namespace}ITCPServer::IClient *client", L"sender, client"))
				->AddHeaderFile(L"Standard/Components/ITCPServer.h");
			Add(new CEvent(this, component, L"OnServerError", L"{namespace}ITCPServer *sender, const {namespace}ITCPServer::ErrorType error", L"sender, error"))
				->AddHeaderFile(L"Standard/Components/ITCPServer.h");
			Add(new CEvent(this, component, L"OnClientError", L"{namespace}ITCPServer *sender, {namespace}ITCPServer::IClient *client, const {namespace}ITCPServer::ErrorType error", L"sender, client, error"))
				->AddHeaderFile(L"Standard/Components/ITCPServer.h");
			Add(new CEvent(this, component, L"OnClientDisconnect", L"{namespace}ITCPServer *sender, {namespace}ITCPServer::IClient *client", L"sender, client"))
				->AddHeaderFile(L"Standard/Components/ITCPServer.h");
			Add(new CEvent(this, component, L"OnClientDestroy", L"{namespace}ITCPServer *sender, {namespace}ITCPServer::IClient *client", L"sender, client"))
				->AddHeaderFile(L"Standard/Components/ITCPServer.h");
			Add(new CEvent(this, component, L"OnClientHaveData", L"{namespace}ITCPServer *sender, {namespace}ITCPServer::IClient *client, bool &disconnect", L"sender, client, disconnect"))
				->AddHeaderFile(L"Standard/Components/ITCPServer.h");
		}
	}
}