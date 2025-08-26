// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "../IFormSelectListItem.h"
#include "IDialogBoxSelectListItemProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CDialogBoxSelectListItem :public virtual IFormSelectListItem, public IDialogBoxSelectListItemProto
		{
		private:
			class CDialogBoxSelectListItemService :public IDialogBoxSelectListItemProtoService
			{
			private:
				CDialogBoxSelectListItem * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxSelectListItemService(CDialogBoxSelectListItem *control);
			};
		private:
			void LoadTranslatableTexts();
		protected:
			void DialogBoxSelectListItemProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			int getItemTypeIndex() override;
			String getItemCaption() override;

			bool setItemTypeIndex(const int value) override;
			bool setItemCaption(const String &value) override;

			CDialogBoxSelectListItem();
			CDialogBoxSelectListItem(IForm *parent);
			CDialogBoxSelectListItem(IControl *parent);
		};
	}
}