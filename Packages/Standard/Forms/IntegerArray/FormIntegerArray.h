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
#include "Nitisa/Math/IntegerArray.h"
#include "../IFormIntegerArray.h"
#include "IFormIntegerArrayProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IListItem;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormIntegerArray : public virtual IFormIntegerArray, public IFormIntegerArrayProto
		{
		private:
			class CFormIntegerArrayService :public CFormService
			{
			private:
				CFormIntegerArray * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormIntegerArrayService(CFormIntegerArray *form);
			};
		private:
			IntegerArray m_aArray;
			int m_iMinCount;
			bool m_bHasMin;
			bool m_bHasMax;
			int m_iMin;
			int m_iMax;

			static CFormIntegerArray *m_pInstance;

			void LoadTranslatableTexts();
			int SelectedPointIndex();
		protected:
			void FormIntegerArrayProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
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

			CFormIntegerArray(IWindow *window, IRenderer *renderer);
			~CFormIntegerArray() override;

			static CFormIntegerArray *getInstance(); // Return form instance if any was created
		};
	}
}