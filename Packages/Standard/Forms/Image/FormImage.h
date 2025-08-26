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
#include "Nitisa/Image/Image.h"
#include "../IFormImage.h"
#include "IFormImageProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormImage :public virtual IFormImage, public IFormImageProto
		{
		private:
			class CFormImageService :public CFormService
			{
			private:
				CFormImage * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormImageService(CFormImage *form);
			};
		private:
			static CFormImage *m_pInstance;

			void LoadTranslatableTexts();
		protected:
			void FormImageProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void ButtonLoad_OnClick(IControl *sender) override;
			void ButtonClear_OnClick(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			Image *getValue() override;

			bool setValue(const Image &value) override;

			CFormImage(IWindow *window, IRenderer *renderer);
			~CFormImage() override;

			void Update();

			static CFormImage *getInstance(); // Return form instance if any was created
		};
	}
}