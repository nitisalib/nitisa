// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Component.h"
#include "Nitisa/Core/Strings.h"
#include "../ISysSaveDialog.h"

namespace nitisa
{
	class IForm;

	namespace standard
	{
		class CSysSaveDialog :public virtual ISysSaveDialog, public CComponent
		{
		private:
			String m_sFilter;
			int m_iFilterIndex;
			String m_sFileName;
			String m_sDefaultExtension;
			bool m_bCreatePrompt;
			bool m_bMustExists;
			bool m_bShowHidden;
			bool m_bHideReadOnly;
			bool m_bNoNetwork;
			bool m_bOverwritePrompt;
		public:
			String getFilter() override;
			int getFilterIndex() override;
			String getFileName() override;
			String getDefaultExtension() override;
			bool isCreatePrompt() override;
			bool isMustExists() override;
			bool isShowHidden() override;
			bool isHideReadOnly() override;
			bool isNoNetwork() override;
			bool isOverwritePrompt() override;

			bool setFilter(const String &value) override;
			bool setFilterIndex(const int value) override;
			bool setFileName(const String &value) override;
			bool setDefaultExtension(const String &value) override;
			bool setCreatePrompt(const bool value) override;
			bool setMustExists(const bool value) override;
			bool setShowHidden(const bool value) override;
			bool setHideReadOnly(const bool value) override;
			bool setNoNetwork(const bool value) override;
			bool setOverwritePrompt(const bool value) override;

			bool Execute() override;

			CSysSaveDialog();
			CSysSaveDialog(IForm *parent);
		};
	}
}