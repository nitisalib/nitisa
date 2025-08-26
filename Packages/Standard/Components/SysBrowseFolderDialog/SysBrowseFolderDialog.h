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
#include "../ISysBrowseFolderDialog.h"

namespace nitisa
{
	class IForm;

	namespace standard
	{
		class CSysBrowseFolderDialog :public virtual ISysBrowseFolderDialog, public CComponent
		{
		private:
			String m_sFolder;
			String m_sTitle;
			bool m_bOnlyFileSystem;
			bool m_bNoNetwork;
			bool m_bNoAncestors;
			bool m_bShowEditBox;
			bool m_bNewStyle;
			bool m_bShowHint;
			bool m_bHideNewFolder;
			bool m_bDontTranslateTargets;
			bool m_bOnlyComputers;
			bool m_bOnlyPrinters;
			bool m_bShowFiles;
			bool m_bShowShareable;
		public:
			String getFolder() override;
			String getTitle() override;
			bool isOnlyFileSystem() override;
			bool isNoNetwork() override;
			bool isNoAncestors() override;
			bool isShowEditBox() override;
			bool isNewStyle() override;
			bool isShowHint() override;
			bool isHideNewFolder() override;
			bool isDontTranslateTargets() override;
			bool isOnlyComputers() override;
			bool isOnlyPrinters() override;
			bool isShowFiles() override;
			bool isShowShareable() override;

			bool setTitle(const String &value) override;
			bool setOnlyFileSystem(const bool value) override;
			bool setNoNetwork(const bool value) override;
			bool setNoAncestors(const bool value) override;
			bool setShowEditBox(const bool value) override;
			bool setNewStyle(const bool value) override;
			bool setShowHint(const bool value) override;
			bool setHideNewFolder(const bool value) override;
			bool setDontTranslateTargets(const bool value) override;
			bool setOnlyComputers(const bool value) override;
			bool setOnlyPrinters(const bool value) override;
			bool setShowFiles(const bool value) override;
			bool setShowShareable(const bool value) override;

			bool Execute() override;

			CSysBrowseFolderDialog();
			CSysBrowseFolderDialog(IForm *parent);
		};
	}
}