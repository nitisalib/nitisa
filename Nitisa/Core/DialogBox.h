// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IDialogBox.h"
#include "../Math/Point.h"
#include "Control.h"
#include "ModalResult.h"
#include "Strings.h"
#include "WindowPosition.h"

namespace nitisa
{
	class IComponent;
	class IDialogBoxListener;
	class IDialogBoxService;

	class CDialogBox :public virtual IDialogBox, public CControl
	{
	private:
		ModalResult m_eModalResult;
		WindowPosition m_eWindowPosition;
		bool m_bTranslated;
		IDialogBoxListener *m_pDialogBoxListener;
	protected:
		void Translate(); // Set position according to WindowPosition property

		void BeforeRelease() override;
	public:
		// IDialogBox getters
		IDialogBoxListener *getDialogBoxListener() override;
		Point getClientSize() override;
		int getClientWidth() override;
		int getClientHeight() override;
		WindowPosition getWindowPosition() override;
		ModalResult getModalResult() override;
		bool isActiveDialogBox() override;
		bool hasComponent(IComponent *component) override; // Return false

		// IDialogBox setters
		void setDialogBoxListener(IDialogBoxListener *value) override;
		bool setWindowPosition(const WindowPosition value) override;
		bool setModalResult(const ModalResult value) override;

		// IDialogBox actions
		bool Show() override;
		bool ShowModal() override;
		bool Close() override;

		CDialogBox(const String &class_name, const bool accept_form, const bool accept_control, const bool accept_focus, const bool tab_stop, const Point &design_dpi, IDialogBoxService *service);
	};
}