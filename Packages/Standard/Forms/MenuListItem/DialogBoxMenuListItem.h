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
#include "../IFormMenuListItem.h"
#include "IDialogBoxMenuListItemProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CDialogBoxMenuListItem :public virtual IFormMenuListItem, public IDialogBoxMenuListItemProto
		{
		private:
			class CDialogBoxMenuListItemService :public IDialogBoxMenuListItemProtoService
			{
			private:
				CDialogBoxMenuListItem * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxMenuListItemService(CDialogBoxMenuListItem *control);
			};
		private:
			void LoadTranslatableTexts();
		protected:
			void FormMenuListItemProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void DropDownItemTypeIndex_OnSelect(IControl *sender, const int index) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			int getItemTypeIndex() override;
			String getItemCaption() override;

			bool setItemTypeIndex(const int value) override;
			bool setItemCaption(const String &value) override;

			CDialogBoxMenuListItem();
			CDialogBoxMenuListItem(IForm *parent);
			CDialogBoxMenuListItem(IControl *parent);
		};
	}
}