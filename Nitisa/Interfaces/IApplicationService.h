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
	class IForm;

	class IApplicationService
	{
	protected:
		IApplicationService() = default;
		~IApplicationService() = default;
		IApplicationService(const IApplicationService &other) = delete;
		IApplicationService(IApplicationService &&other) = delete;
		IApplicationService &operator=(const IApplicationService &other) = delete;
		IApplicationService &operator=(IApplicationService &&other) = delete;
	public:
		virtual void Release() = 0; // Destroy service
		virtual void Add(IForm *form) = 0; // Register form in application. Should be called in form constructor
		virtual void Remove(IForm *form) = 0; // Unregister form in application. Should be called in form destructor.
		virtual void SendTranslateChangeNotification() = 0; // Send translation change notification to all forms, components, and controls. Changing current language in ITranslation call this automatically. In all other cases of changing translation matrix you have to call this method to reflect changes
	};
}