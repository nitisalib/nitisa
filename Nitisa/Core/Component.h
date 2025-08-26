// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IComponent.h"
#include "Class.h"
#include "Releasable.h"
#include "Strings.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class IComponentService;
	class IForm;

	class CComponentService;

	class CComponent :public virtual IComponent, public CClass, public CReleasable
	{
		friend CComponentService;
	private:
		IForm *m_pForm;
		IComponentService *m_pService;
	protected:
		void BeforeRelease() override;
	public:
		IForm *getForm() override;

		bool setName(const String &value) override;
		bool setForm(IForm *value) override;
		void setService(IComponentService *value, const bool release_prev) override final;

		IComponentService *QueryService() override;

		CComponent(const String &class_name); // Create with specified class name
		~CComponent() override;
	};
}