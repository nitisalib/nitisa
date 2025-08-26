// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Interfaces/IBuiltInControlListener.h"

namespace nitisa
{
	class IBuiltInControl;
	class IProperty;

	class IPropertyHandlerListener :public virtual IBuiltInControlListener
	{
	protected:
		IPropertyHandlerListener() = default;
		~IPropertyHandlerListener() = default;
		IPropertyHandlerListener(const IPropertyHandlerListener &other) = delete;
		IPropertyHandlerListener(IPropertyHandlerListener &&other) = delete;
		IPropertyHandlerListener &operator=(const IPropertyHandlerListener &other) = delete;
		IPropertyHandlerListener &operator=(IPropertyHandlerListener &&other) = delete;
	public:
		virtual void NotifyOnPropertyChange(IBuiltInControl *sender, IProperty *property) = 0; // Called each time property has been changed by property handler. Use it in property editor to populate values to all required properties
	};
}