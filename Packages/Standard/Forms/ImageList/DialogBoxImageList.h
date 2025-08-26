// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../IFormImageList.h"
#include "IDialogBoxImageListProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	class Image;

	namespace standard
	{
		class CDialogBoxImageList :public virtual IFormImageList, public IDialogBoxImageListProto
		{
		private:
			class CDialogBoxImageListService :public IDialogBoxImageListProtoService
			{
			private:
				CDialogBoxImageList * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxImageListService(CDialogBoxImageList *control);
			};
		private:
			void LoadTranslatableTexts();
		protected:
			void ButtonAdd_OnClick(IControl *sender) override;
			void ButtonDelete_OnClick(IControl *sender) override;
			void ButtonClear_OnClick(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			int getImageCount() override;
			Image *getImage(const int index) override;

			int AddImage(Image *value) override;
			bool DeleteImage(const int index) override;
			bool DeleteImages() override;

			CDialogBoxImageList();
			CDialogBoxImageList(IForm *parent);
			CDialogBoxImageList(IControl *parent);
		};
	}
}