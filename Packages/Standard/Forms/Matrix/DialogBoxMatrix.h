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
#include "Nitisa/Math/Mat4f.h"
#include "../IFormMatrix.h"
#include "IDialogBoxMatrixProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CDialogBoxMatrix :public virtual IFormMatrix, public IDialogBoxMatrixProto
		{
		private:
			class CDialogBoxMatrixService :public IDialogBoxMatrixProtoService
			{
			private:
				CDialogBoxMatrix * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxMatrixService(CDialogBoxMatrix *control);
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
			void FormMatrixProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
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

			CDialogBoxMatrix();
			CDialogBoxMatrix(IForm *parent);
			CDialogBoxMatrix(IControl *parent);
		};
	}
}