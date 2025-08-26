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
#include "Nitisa/Image/Image.h"
#include "../IFormImage.h"
#include "IDialogBoxImageProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CDialogBoxImage :public virtual IFormImage, public IDialogBoxImageProto
		{
		private:
			class CDialogBoxImageService :public IDialogBoxImageProtoService
			{
			private:
				CDialogBoxImage * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxImageService(CDialogBoxImage *control);
			};
		private:
			void LoadTranslatableTexts();
		protected:
			void FormImageProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void ButtonLoad_OnClick(IControl *sender) override;
			void ButtonClear_OnClick(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			Image *getValue() override;

			bool setValue(const Image &value) override;

			CDialogBoxImage();
			CDialogBoxImage(IForm *parent);
			CDialogBoxImage(IControl *parent);

			void Update();
		};
	}
}