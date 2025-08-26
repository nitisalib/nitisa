// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/FormService.h"
#include "Nitisa/Core/Strings.h"
#include "../IFormChartDataSet.h"
#include "IFormChartDataSetProto.h"

namespace nitisa
{
	class IControl;
	class IListItem;
	class IRenderer;
	class IWindow;

	namespace charts
	{
		class IChartDataSet;
		class IUpdateListener;

		class CFormChartDataSet : public virtual IFormChartDataSet, public IFormChartDataSetProto
		{
		private:
			class CFormChartDataSetService :public CFormService
			{
			private:
				CFormChartDataSet * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormChartDataSetService(CFormChartDataSet *form);
			};
		private:
			IChartDataSet *m_pDataSet;
			IUpdateListener *m_pListener;

			static CFormChartDataSet *m_pInstance;

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

			CFormChartDataSet(IWindow *window, IRenderer *renderer);
			~CFormChartDataSet() override;

			static CFormChartDataSet *getInstance(); // Return form instance if any was created

			void setUpdateListener(IUpdateListener *listener) override;
		};
	}
}