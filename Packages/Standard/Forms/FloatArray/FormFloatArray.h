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
#include "Nitisa/Math/FloatArray.h"
#include "../IFormFloatArray.h"
#include "IFormFloatArrayProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormFloatArray : public virtual IFormFloatArray, public IFormFloatArrayProto
		{
		private:
			class CFormFloatArrayService :public CFormService
			{
			private:
				CFormFloatArray * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormFloatArrayService(CFormFloatArray *form);
			};
		private:
			FloatArray m_aArray;
			int m_iMinCount;
			bool m_bHasMin;
			bool m_bHasMax;
			float m_fMin;
			float m_fMax;

			static CFormFloatArray *m_pInstance;

			void LoadTranslatableTexts();
			int SelectedPointIndex();
		protected:
			void FormFloatArrayProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void ListBoxArray_OnSelect(IControl *sender, IListItem *item) override;
			void ButtonAdd_OnClick(IControl *sender) override;
			void ButtonUpdate_OnClick(IControl *sender) override;
			void ButtonDelete_OnClick(IControl *sender) override;
			void ButtonClear_OnClick(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			FloatArray getValue() override;
			int getMinCount() override;
			bool hasMin() override;
			bool hasMax() override;
			float getMin() override;
			float getMax() override;

			bool setValue(const FloatArray &value) override;
			bool setMinCount(const int value) override;
			bool setHasMin(const bool value) override;
			bool setHasMax(const bool value) override;
			bool setMin(const float value) override;
			bool setMax(const float value) override;

			CFormFloatArray(IWindow *window, IRenderer *renderer);
			~CFormFloatArray() override;

			static CFormFloatArray *getInstance(); // Return form instance if any was created
		};
	}
}