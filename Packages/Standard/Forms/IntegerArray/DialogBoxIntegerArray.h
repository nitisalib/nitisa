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
#include "Nitisa/Math/IntegerArray.h"
#include "../IFormIntegerArray.h"
#include "IDialogBoxIntegerArrayProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IListItem;

	namespace standard
	{
		class CDialogBoxIntegerArray : public virtual IFormIntegerArray, public IDialogBoxIntegerArrayProto
		{
		private:
			class CDialogBoxIntegerArrayService :public IDialogBoxIntegerArrayProtoService
			{
			private:
				CDialogBoxIntegerArray * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxIntegerArrayService(CDialogBoxIntegerArray *control);
			};
		private:
			IntegerArray m_aArray;
			int m_iMinCount;
			bool m_bHasMin;
			bool m_bHasMax;
			int m_iMin;
			int m_iMax;

			void LoadTranslatableTexts();
			int SelectedPointIndex();
		protected:
			void FormIntegerArrayProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void ListBoxArray_OnSelect(IControl *sender, IListItem *item) override;
			void ButtonAdd_OnClick(IControl *sender) override;
			void ButtonUpdate_OnClick(IControl *sender) override;
			void ButtonDelete_OnClick(IControl *sender) override;
			void ButtonClear_OnClick(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			IntegerArray getValue() override;
			int getMinCount() override;
			bool hasMin() override;
			bool hasMax() override;
			int getMin() override;
			int getMax() override;

			bool setValue(const IntegerArray &value) override;
			bool setMinCount(const int value) override;
			bool setHasMin(const bool value) override;
			bool setHasMax(const bool value) override;
			bool setMin(const int value) override;
			bool setMax(const int value) override;

			CDialogBoxIntegerArray();
			CDialogBoxIntegerArray(IForm *parent);
			CDialogBoxIntegerArray(IControl *parent);
		};
	}
}