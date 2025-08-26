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
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/ColorArray.h"
#include "../IFormColorArray.h"
#include "IDialogBoxColorArrayProto.h"

namespace nitisa
{
	class IComponent;
	class IControl;
	class IForm;
	class IListItem;

	namespace standard
	{
		class CDialogBoxColorArray : public virtual IFormColorArray, public IDialogBoxColorArrayProto
		{
		private:
			class CDialogBoxColorArrayService :public IDialogBoxColorArrayProtoService
			{
			private:
				CDialogBoxColorArray * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxColorArrayService(CDialogBoxColorArray *control);
			};
		private:
			ColorArray m_aArray;
			int m_iMinCount;
			bool m_bColorDialogAdjusted;

			void LoadTranslatableTexts();
			int SelectedPointIndex();
		protected:
			void FormColorArrayProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void ColorDialog1_OnApply(IComponent *sender) override;
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

			bool hasComponent(IComponent *component) override;
			ColorArray getValue() override;
			int getMinCount() override;

			bool setBackgroundColor(const Color &value) override;
			bool setValue(const ColorArray &value) override;
			bool setMinCount(const int value) override;

			CDialogBoxColorArray();
			CDialogBoxColorArray(IForm *parent);
			CDialogBoxColorArray(IControl *parent);
		};
	}
}