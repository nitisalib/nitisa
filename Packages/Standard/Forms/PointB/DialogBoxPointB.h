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
#include "Nitisa/Math/PointB.h"
#include "../IFormPointB.h"
#include "IDialogBoxPointBProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CDialogBoxPointB :public virtual IFormPointB, public IDialogBoxPointBProto
		{
		private:
			class CDialogBoxPointBService :public IDialogBoxPointBProtoService
			{
			private:
				CDialogBoxPointB * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxPointBService(CDialogBoxPointB *control);
			};
		private:
			void LoadTranslatableTexts();
		protected:
			void FormPointBProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			PointB getValue() override;

			bool setValue(const PointB &value) override;

			void ActivateFirstEnabledInput() override;

			CDialogBoxPointB();
			CDialogBoxPointB(IForm *parent);
			CDialogBoxPointB(IControl *parent);
		};
	}
}