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
#include "Nitisa/Image/ColorArray.h"
#include "../IFormColorArray.h"
#include "IFormColorArrayProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IListItem;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormColorArray : public virtual IFormColorArray, public IFormColorArrayProto
		{
		private:
			class CFormColorArrayService :public CFormService
			{
			private:
				CFormColorArray * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormColorArrayService(CFormColorArray *form);
			};
		private:
			ColorArray m_aArray;
			int m_iMinCount;

			static CFormColorArray *m_pInstance;

			void LoadTranslatableTexts();
			int SelectedPointIndex();
		protected:
			void FormColorArrayProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void ListBoxArray_OnSelect(IControl *sender, IListItem *item) override;
			void ButtonAdd_OnClick(IControl *sender) override;
			void ButtonUpdate_OnClick(IControl *sender) override;
			void ButtonDelete_OnClick(IControl *sender) override;
			void ButtonClear_OnClick(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
			void ColorListBox_OnSelect(IControl *sender, IListItem *item) override;
			void PanelColor_OnLeftMouseButtonDown(IControl *sender, const MessageMouse &m, bool &processed) override;
		public:
			static const String ClassName; // Class name

			ColorArray getValue() override;
			int getMinCount() override;

			bool setValue(const ColorArray &value) override;
			bool setMinCount(const int value) override;

			CFormColorArray(IWindow *window, IRenderer *renderer);
			~CFormColorArray() override;

			static CFormColorArray *getInstance(); // Return form instance if any was created
		};
	}
}