// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/FormService.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "../IFormSelectListItem.h"
#include "IFormSelectListItemProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormSelectListItem :public virtual IFormSelectListItem, public IFormSelectListItemProto
		{
		private:
			class CFormSelectListItemService :public CFormService
			{
			private:
				CFormSelectListItem * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormSelectListItemService(CFormSelectListItem *form);
			};
		private:
			static CFormSelectListItem *m_pInstance;

			void LoadTranslatableTexts();
		protected:
			void FormSelectListItemProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			int getItemTypeIndex() override;
			String getItemCaption() override;

			bool setItemTypeIndex(const int value) override;
			bool setItemCaption(const String &value) override;

			CFormSelectListItem(IWindow *window, IRenderer *renderer);
			~CFormSelectListItem() override;

			static CFormSelectListItem *getInstance(); // Return form instance if any was created
		};
	}
}