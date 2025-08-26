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
#include "../../Core/Enums.h"
#include "../IFormLineInterpolationPositionArray.h"
#include "IFormLineInterpolationPositionArrayProto.h"
#include <vector>

namespace nitisa
{
	class IControl;
	class IForm;
	class IListItem;
	class IRenderer;
	class IWindow;

	namespace charts
	{
		class CFormLineInterpolationPositionArray : public virtual IFormLineInterpolationPositionArray, public IFormLineInterpolationPositionArrayProto
		{
		private:
			class CFormLineInterpolationPositionArrayService :public CFormService
			{
			private:
				CFormLineInterpolationPositionArray * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormLineInterpolationPositionArrayService(CFormLineInterpolationPositionArray *form);
			};
		private:
			std::vector<LineInterpolationPosition> m_aArray;
			int m_iMinCount;

			static CFormLineInterpolationPositionArray *m_pInstance;

			void LoadTranslatableTexts();
			int SelectedPointIndex();
		protected:
			void FormLineInterpolationPositionArrayProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
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

			CFormLineInterpolationPositionArray(IWindow *window, IRenderer *renderer);
			~CFormLineInterpolationPositionArray() override;

			static CFormLineInterpolationPositionArray *getInstance(); // Return form instance if any was created
		};
	}
}