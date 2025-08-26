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

	class IHintService
	{
	protected:
		IHintService() = default;
		~IHintService() = default;
		IHintService(const IHintService &other) = delete;
		IHintService(IHintService &&other) = delete;
		IHintService &operator=(const IHintService &other) = delete;
		IHintService &operator=(IHintService &&other) = delete;
	public:
		virtual void setForm(IForm *value) = 0; // Set form. Should hide immediately, clear all renderer resources and assign new form

		virtual void Release() = 0; // Destroy instance
	};
}