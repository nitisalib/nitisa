// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../IFormChartDataSet.h"
#include "IDialogBoxChartDataSetProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IListItem;

	namespace charts
	{
		class IChartDataSet;
		class IUpdateListener;

		class CDialogBoxChartDataSet : public virtual IFormChartDataSet, public IDialogBoxChartDataSetProto
		{
		private:
			class CDialogBoxChartDataSetService :public IDialogBoxChartDataSetProtoService
			{
			private:
				CDialogBoxChartDataSet * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxChartDataSetService(CDialogBoxChartDataSet *control);
			};
		private:
			IChartDataSet *m_pDataSet;
			IUpdateListener *m_pListener;

			void LoadTranslatableTexts();
			int SelectedDataIndex();
			int SelectedPointIndex();
		protected:
			void ButtonAddData_OnClick(IControl *sender) override;
			void ButtonDeleteData_OnClick(IControl *sender) override;
			void ListBoxDatas_OnSelect(IControl *sender, IListItem *item) override;
			void ListBoxDatas_OnDeselect(IControl *sender, IListItem *item) override;
			void ButtonUpdateData_OnClick(IControl *sender) override;
			void ButtonClearDatas_OnClick(IControl *sender) override;
			void ListBoxPoints_OnSelect(IControl *sender, IListItem *item) override;
			void ListBoxPoints_OnDeselect(IControl *sender, IListItem *item) override;
			void ButtonAddPoint_OnClick(IControl *sender) override;
			void ButtonUpdatePoint_OnClick(IControl *sender) override;
			void ButtonDeletePoint_OnClick(IControl *sender) override;
			void ButtonClearPoints_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			IChartDataSet *getValue() override;

			bool setValue(IChartDataSet *value) override;

			CDialogBoxChartDataSet();
			CDialogBoxChartDataSet(IForm *parent);
			CDialogBoxChartDataSet(IControl *parent);

			void setUpdateListener(IUpdateListener *listener) override;
		};
	}
}