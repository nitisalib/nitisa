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
#include "../../Controls/IForexChart.h"
#include "../IFormForexChartData.h"
#include "IDialogBoxForexChartDataProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IListItem;

	namespace charts
	{
		class IUpdateListener;

		class CDialogBoxForexChartData : public virtual IFormForexChartData, public IDialogBoxForexChartDataProto
		{
		private:
			class CDialogBoxForexChartDataService :public IDialogBoxForexChartDataProtoService
			{
			private:
				CDialogBoxForexChartData * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxForexChartDataService(CDialogBoxForexChartData *control);
			};
		private:
			IForexChart::IForexChartData *m_pData;
			IUpdateListener *m_pListener;

			void LoadTranslatableTexts();
			int SelectedPointIndex();
			String ItemToString(const int index);
			bool GetValues(float &open, float &close, float &min, float &max);
		protected:
			void FormForexChartDataProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void ButtonAdd_OnClick(IControl *sender) override;
			void ButtonDelete_OnClick(IControl *sender) override;
			void ButtonUpdate_OnClick(IControl *sender) override;
			void ButtonClear_OnClick(IControl *sender) override;
			void ListBoxArray_OnSelect(IControl *sender, IListItem *item) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			IForexChart::IForexChartData *getValue() override;

			bool setValue(IForexChart::IForexChartData *value) override;

			CDialogBoxForexChartData();
			CDialogBoxForexChartData(IForm *parent);
			CDialogBoxForexChartData(IControl *parent);

			void setUpdateListener(IUpdateListener *listener) override;
		};
	}
}