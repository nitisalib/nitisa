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
#include "../../Core/Enums.h"
#include "../IFormLineInterpolationPositionArray.h"
#include "IDialogBoxLineInterpolationPositionArrayProto.h"
#include <vector>

namespace nitisa
{
	class IControl;
	class IForm;
	class IListItem;

	namespace charts
	{
		class CDialogBoxLineInterpolationPositionArray : public virtual IFormLineInterpolationPositionArray, public IDialogBoxLineInterpolationPositionArrayProto
		{
		private:
			class CDialogBoxLineInterpolationPositionArrayService :public IDialogBoxLineInterpolationPositionArrayProtoService
			{
			private:
				CDialogBoxLineInterpolationPositionArray * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxLineInterpolationPositionArrayService(CDialogBoxLineInterpolationPositionArray *control);
			};
		private:
			std::vector<LineInterpolationPosition> m_aArray;
			int m_iMinCount;

			void LoadTranslatableTexts();
			int SelectedPointIndex();
		protected:
			void FormLineInterpolationPositionArrayProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void ListBoxArray_OnSelect(IControl *sender, IListItem *item) override;
			void ButtonAdd_OnClick(IControl *sender) override;
			void ButtonUpdate_OnClick(IControl *sender) override;
			void ButtonDelete_OnClick(IControl *sender) override;
			void ButtonClear_OnClick(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			std::vector<LineInterpolationPosition> getValue() override;
			int getMinCount() override;

			bool setValue(const std::vector<LineInterpolationPosition> &value) override;
			bool setMinCount(const int value) override;

			CDialogBoxLineInterpolationPositionArray();
			CDialogBoxLineInterpolationPositionArray(IForm *parent);
			CDialogBoxLineInterpolationPositionArray(IControl *parent);
		};
	}
}