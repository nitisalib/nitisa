// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/DialogBox.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/WindowState.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Math/RectF.h"
#include "../Core/Types.h"
#include "BaseExporter.h"
#include <fstream>

namespace nitisa
{
	class IControl;
	class IEventList;
	class IPackageControl;
	class IPropertyList;

	namespace fb
	{
		class CComponentList;
		class CControlList;

		class CExporterHeaderDialogBox :public CBaseExporter
		{
		private:
			class CEmptyDialogBox :public CDialogBox
			{
			private:
				Color m_sBackgroundColor;
				String m_sCaption;
				WindowState m_eState;
				RectF m_sBorderWidth;
				bool m_bHasCloseBox;
				bool m_bHasMinimizeBox;
				bool m_bHasMaximizeBox;
				bool m_bHasSizeBox;
				bool m_bHasSystemMenu;
				bool m_bHasBorder;
				bool m_bHasCaption;
				bool m_bIsPopup;
			public:
				// IDialogBox getters
				Color getBackgroundColor() override;
				String getCaption() override;
				WindowState getState() override;
				RectF getBorderWidth() override;
				bool hasCloseBox() override;
				bool hasMaximizeBox() override;
				bool hasMinimizeBox() override;
				bool hasSizeBox() override;
				bool hasSystemMenu() override;
				bool hasBorder() override;
				bool hasCaption() override;
				bool isPopup() override;

				// IDialogBox setters
				bool setBackgroundColor(const Color &value) override;
				bool setCaption(const String &value) override;
				bool setClientSize(const Point &value) override;
				bool setState(const WindowState value) override;
				bool setBorderWidth(const RectF &value) override;
				bool setHasCloseBox(const bool value) override;
				bool setHasMaximizeBox(const bool value) override;
				bool setHasMinimizeBox(const bool value) override;
				bool setHasSizeBox(const bool value) override;
				bool setHasSystemMenu(const bool value) override;
				bool setHasBorder(const bool value) override;
				bool setHasCaption(const bool value) override;
				bool setIsPopup(const bool value) override;

				// IDialogBox actions
				bool Maximize() override;
				bool Minimize() override;
				bool Restore() override;
				bool Hide() override;

				CEmptyDialogBox();
			};
		private:
			void CopyFormEvents(IEventList *dst, IEventList *src);
			void CopyFormProperties(IPropertyList *dst, IPropertyList *src);

			void ExportLicense(std::wofstream &f, const EXPORT_SETTINGS &settings, const String &ver, const String &form_name);
			void ExportInitialize(std::wofstream &f, const String &shift, CComponentList *components, CControlList *controls, IControl *parent, const String &prefix, const String &form_name);
			void ExportComponentsInitialize(std::wofstream &f, const String &shift, CComponentList *components, const String &prefix, const String &form_name);
			void ExportControlsInitialize(std::wofstream &f, IControl *parent, const String &shift, CControlList *controls, const String &prefix, const String &form_name);
			void ExportGetComponent(std::wofstream &f, const String &shift, CComponentList *components, const String &prefix);
			void ExportHasComponent(std::wofstream &f, const String &shift, CComponentList *components, const String &prefix);
			void ExportService(std::wofstream &f, const String &shift, CComponentList *components, const String &prefix, const String &form, IPackageControl *base);
			void ExportDestructor(std::wofstream &f, const String &shift, CComponentList *components, const String &prefix, const String &form);
			void ExportFindControl(std::wofstream &f, const String &shift, CControlList *controls, const String &prefix);
		public:
			String getName() const override;
			String getDescription() const override;

			bool Export(const String &filename, const EXPORT_SETTINGS &settings, CComponentList *components, CControlList *controls, Form &form, const String &ver, IControl *parent) override;
			String PrepareFormName(const String &name) override;

			CExporterHeaderDialogBox();
		};
	}
}