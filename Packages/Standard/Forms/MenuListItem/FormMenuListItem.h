// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/FormService.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "../IFormMenuListItem.h"
#include "IFormMenuListItemProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormMenuListItem :public virtual IFormMenuListItem, public IFormMenuListItemProto
		{
		private:
			class CFormMenuListItemService :public CFormService
			{
			private:
				CFormMenuListItem * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormMenuListItemService(CFormMenuListItem *form);
			};
		private:
			static CFormMenuListItem *m_pInstance;

			void LoadTranslatableTexts();
		protected:
			void FormMenuListItemProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void DropDownItemTypeIndex_OnSelect(IControl *sender, const int index) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			int getItemTypeIndex() override;
			String getItemCaption() override;

			bool setItemTypeIndex(const int value) override;
			bool setItemCaption(const String &value) override;

			CFormMenuListItem(IWindow *window, IRenderer *renderer);
			~CFormMenuListItem() override;

			static CFormMenuListItem *getInstance(); // Return form instance if any was created
		};
	}
}