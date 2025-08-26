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
#include "Nitisa/Math/Mat4f.h"
#include "../IFormMatrix.h"
#include "IFormMatrixProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormMatrix :public virtual IFormMatrix, public IFormMatrixProto
		{
		private:
			class CFormMatrixService :public CFormService
			{
			private:
				CFormMatrix * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormMatrixService(CFormMatrix *form);
			};
		private:
			Mat4f m_sMatrix;

			void InitControls();
			void LoadTranslatableTexts();
			void UpdateEdits();
			bool TryGetTranslate(float &x, float &y, float &z);
			bool TryGetScale(float &x, float &y, float &z);
			bool TryGetRx(float &v);
			bool TryGetRy(float &v);
			bool TryGetRz(float &v);
		protected:
			void FormMatrixProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void OnKillFocus(IControl *sender) override;
			void ButtonMT_OnClick(IControl *sender) override;
			void ButtonT_OnClick(IControl *sender) override;
			void ButtonTM_OnClick(IControl *sender) override;
			void ButtonMS_OnClick(IControl *sender) override;
			void ButtonS_OnClick(IControl *sender) override;
			void ButtonSM_OnClick(IControl *sender) override;
			void ButtonMRx_OnClick(IControl *sender) override;
			void ButtonRx_OnClick(IControl *sender) override;
			void ButtonRxM_OnClick(IControl *sender) override;
			void ButtonMRy_OnClick(IControl *sender) override;
			void ButtonRy_OnClick(IControl *sender) override;
			void ButtonRyM_OnClick(IControl *sender) override;
			void ButtonMRz_OnClick(IControl *sender) override;
			void ButtonRz_OnClick(IControl *sender) override;
			void ButtonRzM_OnClick(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			Mat4f getValue() override;

			bool setValue(const Mat4f &value) override;

			void ActivateFirstEnabledInput() override;

			CFormMatrix(IWindow *window, IRenderer *renderer);
		};
	}
}