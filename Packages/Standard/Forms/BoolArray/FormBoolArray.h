// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/BoolArray.h"
#include "Nitisa/Core/FormService.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "../IFormBoolArray.h"
#include "IFormBoolArrayProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IListItem;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormBoolArray : public virtual IFormBoolArray, public IFormBoolArrayProto
		{
		private:
			class CFormBoolArrayService :public CFormService
			{
			private:
				CFormBoolArray * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormBoolArrayService(CFormBoolArray *form);
			};
		private:
			BoolArray m_aArray;
			int m_iMinCount;

			static CFormBoolArray *m_pInstance;

			void LoadTranslatableTexts();
			int SelectedPointIndex();
		protected:
			void FormBoolArrayProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
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

			CFormBoolArray(IWindow *window, IRenderer *renderer);
			~CFormBoolArray() override;

			static CFormBoolArray *getInstance(); // Return form instance if any was created
		};
	}
}