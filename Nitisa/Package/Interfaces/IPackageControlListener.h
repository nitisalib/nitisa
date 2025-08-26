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
	class IControl;
	class IListItem;
	class IPackageControl;

	class IPackageControlListener
	{
	protected:
		IPackageControlListener() = default;
		~IPackageControlListener() = default;
		IPackageControlListener(const IPackageControlListener &other) = delete;
		IPackageControlListener(IPackageControlListener &&other) = delete;
		IPackageControlListener &operator=(const IPackageControlListener &other) = delete;
		IPackageControlListener &operator=(IPackageControlListener &&other) = delete;
	public:
		virtual void OnCreateChild( // Event called when package control successfully created new child control
			IPackageControl *sender, // Package control which called this method
			IControl *parent, // Parent control of the created one. Equals to the one passed to CreateChild() method
			IControl *control) = 0; // Created control
		virtual void OnCreateListItem( // Event called when package control successfully created new list item
			IPackageControl *sender, // Package control which called this method
			IListItem *parent, // Parent item of the created one. Equals to the one passed to CreateListItem() method
			IListItem *item) = 0; // Created list item
	};
}