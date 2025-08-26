// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "../StringGrid/CustomStringGridService.h"

namespace nitisa
{
	class IListItem;

	namespace standard
	{
		class CValueListEditor;

		class CValueListEditorService :public CCustomStringGridService
		{
		private:
			CValueListEditor * m_pControl;
		public:
			// Keyboard input notifications
			void NotifyOnKeyDown(const MessageKey &m, bool &processed) override;

			// Cell status change notifications
			void NotifyOnActivateCell(const int column, const int row, IListItem *item) override;
			void NotifyOnCellChange(const int column, const int row, const String &value, bool &allowed) override;

			// TODO: when adding row set key-cell editable equal to m_pControl->m_bKeysEditable

			CValueListEditorService(CValueListEditor *control);
		};
	}
}