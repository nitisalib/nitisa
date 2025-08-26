// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/BoolArray.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "../IFormBoolArray.h"
#include "IDialogBoxBoolArrayProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IListItem;

	namespace standard
	{
		class CDialogBoxBoolArray : public virtual IFormBoolArray, public IDialogBoxBoolArrayProto
		{
		private:
			class CDialogBoxBoolArrayService :public IDialogBoxBoolArrayProtoService
			{
			private:
				CDialogBoxBoolArray * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxBoolArrayService(CDialogBoxBoolArray *form);
			};
		private:
			BoolArray m_aArray;
			int m_iMinCount;

			void LoadTranslatableTexts();
			int SelectedPointIndex();
		protected:
			void FormBoolArrayProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void ListBoxArray_OnSelect(IControl *sender, IListItem *item) override;
			void ButtonAdd_OnClick(IControl *sender) override;
			void ButtonUpdate_OnClick(IControl *sender) override;
			void ButtonDelete_OnClick(IControl *sender) override;
			void ButtonClear_OnClick(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			BoolArray getValue() override;
			int getMinCount() override;

			bool setValue(const BoolArray &value) override;
			bool setMinCount(const int value) override;

			CDialogBoxBoolArray();
			CDialogBoxBoolArray(IForm *parent);
			CDialogBoxBoolArray(IControl *parent);
		};
	}
}