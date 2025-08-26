// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	class IListItem;
	class IPackageComponent;

	class IPackageComponentListener
	{
	protected:
		IPackageComponentListener() = default;
		~IPackageComponentListener() = default;
		IPackageComponentListener(const IPackageComponentListener &other) = delete;
		IPackageComponentListener(IPackageComponentListener &&other) = delete;
		IPackageComponentListener &operator=(const IPackageComponentListener &other) = delete;
		IPackageComponentListener &operator=(IPackageComponentListener &&other) = delete;
	public:
		virtual void OnCreateListItem( // Event called when package component successfully created new list item
			IPackageComponent *sender, // Package component which called this method
			IListItem *parent, // Parent item of the created one. Equals to the one passed to CreateListItem() method
			IListItem *item) = 0; // Created list item
	};
}