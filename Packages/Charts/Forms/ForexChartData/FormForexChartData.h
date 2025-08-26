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
#include "Nitisa/Core/Messages.h"
#include "../../Controls/IForexChart.h"
#include "../IFormForexChartData.h"
#include "IFormForexChartDataProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IListItem;
	class IRenderer;
	class IWindow;

	namespace charts
	{
		class IUpdateListener;

		class CFormForexChartData : public virtual IFormForexChartData, public IFormForexChartDataProto
		{
		private:
			class CFormForexChartDataService :public CFormService
			{
			private:
				CFormForexChartData * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormForexChartDataService(CFormForexChartData *form);
			};
		private:
			IForexChart::IForexChartData *m_pData;
			IUpdateListener *m_pListener;

			static CFormForexChartData *m_pInstance;

			void LoadTranslatableTexts();
			int SelectedPointIndex();
			String ItemToString(const int index);
			bool GetValues(float &open, float &close, float &min, float &max);
		protected:
			void FormForexChartDataProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
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

			CFormForexChartData(IWindow *window, IRenderer *renderer);
			~CFormForexChartData() override;

			static CFormForexChartData *getInstance(); // Return form instance if any was created

			void setUpdateListener(IUpdateListener *listener) override;
		};
	}
}