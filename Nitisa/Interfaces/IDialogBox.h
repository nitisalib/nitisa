// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/CloseAction.h"
#include "../Core/ModalResult.h"
#include "../Core/Strings.h"
#include "../Core/WindowPosition.h"
#include "../Core/WindowState.h"
#include "../Math/Point.h"
#include "../Math/RectF.h"
#include "../Image/Color.h"
#include "IControl.h"

namespace nitisa
{
	class IComponent;
	class IDialogBoxListener;

	class IDialogBox :public virtual IControl
	{
	protected:
		IDialogBox() = default;
		~IDialogBox() = default;
		IDialogBox(const IDialogBox &other) = delete;
		IDialogBox(IDialogBox &&other) = delete;
		IDialogBox &operator=(const IDialogBox &other) = delete;
		IDialogBox &operator=(IDialogBox &&other) = delete;
	public:
		// Events
		void(*OnDestroy)(IDialogBox *sender); // Event called when control is about to be destroyed
		void(*OnClose)(IDialogBox *sender, CloseAction &action); // Event called when user tries to close the control. Action could be changed to prevent default behavior
		void(*OnRestore)(IDialogBox *sender); // Event called when control has been restored
		void(*OnMinimize)(IDialogBox *sender); // Event called when control has been minimized
		void(*OnMaximize)(IDialogBox *sender); // Event called when control has been maximized
		void(*OnSetActive)(IDialogBox *sender); // Event called when the control has became active dialog box
		void(*OnKillActive)(IDialogBox *sender); // Event called when the control has lost active dialog box state

		// Getters
		virtual IDialogBoxListener *getDialogBoxListener() = 0; // Return assigned listener
		virtual Color getBackgroundColor() = 0; // Return background color
		virtual String getCaption() = 0; // Return caption
		virtual Point getClientSize() = 0; // Return client area size
		virtual int getClientWidth() = 0; // Return client area width
		virtual int getClientHeight() = 0; // Return client area height
		virtual WindowState getState() = 0; // Return state
		virtual WindowPosition getWindowPosition() = 0; // Return dialog box position set by Show() and ShowModal() methods
		virtual RectF getBorderWidth() = 0; // Return border width which is used only when aligning controls. By default {0, 0, 0, 0}. Borders space could be used to draw custom borders and caption area
		virtual bool hasCloseBox() = 0; // Return whether control can be closed
		virtual bool hasMaximizeBox() = 0; // Return whether control has minimize button
		virtual bool hasMinimizeBox() = 0; // Return whether control has maximize button
		virtual bool hasSizeBox() = 0; // Return whether control can be resized
		virtual bool hasSystemMenu() = 0; // Return whether control has system menu or at least an icon
		virtual bool hasBorder() = 0; // Return whether control has border
		virtual bool hasCaption() = 0; // Return whether control has caption
		virtual bool isPopup() = 0; // Return whether control is popup one(has no border, caption, system menu)
		virtual ModalResult getModalResult() = 0; // Return modal result. mrNone by default
		virtual bool isActiveDialogBox() = 0; // Return whether this dialog box is active on form or not
		virtual bool hasComponent(IComponent *component) = 0; // Return whether component belongs to dialog box

		// Setters
		virtual void setDialogBoxListener(IDialogBoxListener *value) = 0; // Assign listener
		virtual bool setBackgroundColor(const Color &value) = 0; // Set background color
		virtual bool setCaption(const String &value) = 0; // Set caption
		virtual bool setClientSize(const Point &value) = 0; // Set client area size
		virtual bool setState(const WindowState value) = 0; // Set state
		virtual bool setWindowPosition(const WindowPosition value) = 0; // Set dialog box position which will be set by Show() and ShowModal() methods
		virtual bool setBorderWidth(const RectF &value) = 0; // Set border width. Used in alignment. Border could be used for drawing custom borders and caption area. When you add control which customizes borders and caption area it sets this property
		virtual bool setHasCloseBox(const bool value) = 0; // Set whether control can be closed
		virtual bool setHasMaximizeBox(const bool value) = 0; // Set whether control has minimize button
		virtual bool setHasMinimizeBox(const bool value) = 0; // Set whether control has maximize button
		virtual bool setHasSizeBox(const bool value) = 0; // Set whether control can be resized
		virtual bool setHasSystemMenu(const bool value) = 0; // Set whether control has system menu or at least an icon
		virtual bool setHasBorder(const bool value) = 0; // Set whether control has border
		virtual bool setHasCaption(const bool value) = 0; // Set whether control has caption
		virtual bool setIsPopup(const bool value) = 0; // Set whether control is popup one(has no border, caption, system menu)
		virtual bool setModalResult(const ModalResult value) = 0; // Set modal result and call Close

		// Actions
		virtual bool Show() = 0; // Show
		virtual bool ShowModal() = 0; // Show and set as modal control
		virtual bool Hide() = 0; // Hide
		virtual bool Maximize() = 0; // Maximize
		virtual bool Minimize() = 0; // Minimize
		virtual bool Restore() = 0; // Restore
		virtual bool Close() = 0; // Close(action depends on OnClose event, hide by default)
	};
}