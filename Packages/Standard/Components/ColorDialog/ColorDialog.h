// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Component.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Interfaces/IDialogBoxListener.h"
#include "../IColorDialog.h"

namespace nitisa
{
	class IDialogBox;
	class IForm;

	namespace standard
	{
		class CColorDialogService;
		class CDialogBoxColor;

		class CColorDialog :public virtual IColorDialog, public CComponent
		{
			friend CColorDialogService;
		private:
			class CDialogBoxListener :public virtual IDialogBoxListener
			{
			private:
				CColorDialog *m_pComponent;
			public:
				void OnClose(IDialogBox *sender) override;
				void OnRestore(IDialogBox *sender) override;
				void OnMinimize(IDialogBox *sender) override;
				void OnMaximize(IDialogBox *sender) override;

				CDialogBoxListener(CColorDialog *component);
			};
		private:
			Color m_sColor;
			bool m_bUseDialogBox;
			CDialogBoxColor *m_pDialogBoxColor;
			IColorDialogListener *m_pColorDialogListener;
			CDialogBoxListener m_cDialogBoxListener;
		public:
			Color getColor() override;
			bool isUseDialogBox() override;
			IColorDialogListener *getColorDialogListener() override;

			bool setColor(const Color &value) override;
			bool setUseDialogBox(const bool value) override;
			void setColorDialogListener(IColorDialogListener *value) override;

			bool Execute() override;

			CColorDialog();
			CColorDialog(IForm *parent);

			CDialogBoxColor *getDialogBox();
		};
	}
}