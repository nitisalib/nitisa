// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IListItemOwner.h"

namespace nitisa
{
	class CListItemOwner :public virtual IListItemOwner
	{
	private:
		bool m_bIgnoreSizeChange;
		bool m_bIgnoreRepaintRequired;
		bool m_bIgnoreShow;
		bool m_bIgnoreHide;
		bool m_bIgnoreEnable;
		bool m_bIgnoreDisable;
		bool m_bIgnoreSelect;
		bool m_bIgnoreDeselect;
		bool m_bIgnoreActivate;
		bool m_bIgnoreDeactivate;
	public:
		bool isIgnoreSizeChange() override;
		bool isIgnoreRepaintRequired() override;
		bool isIgnoreShow() override;
		bool isIgnoreHide() override;
		bool isIgnoreEnable() override;
		bool isIgnoreDisable() override;
		bool isIgnoreSelect() override;
		bool isIgnoreDeselect() override;
		bool isIgnoreActivate() override;
		bool isIgnoreDeactivate() override;

		void setIgnoreSizeChange(const bool value) override;
		void setIgnoreRepaintRequired(const bool value) override;
		void setIgnoreShow(const bool value) override;
		void setIgnoreHide(const bool value) override;
		void setIgnoreEnable(const bool value) override;
		void setIgnoreDisable(const bool value) override;
		void setIgnoreSelect(const bool value) override;
		void setIgnoreDeselect(const bool value) override;
		void setIgnoreActivate(const bool value) override;
		void setIgnoreDeactivate(const bool value) override;

		void Release() override;

		CListItemOwner();
		virtual ~CListItemOwner() = default;
	};
}