// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Key.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "Nitisa/Package/Core/PropertyHandler.h"

namespace nitisa
{
	class IBuiltInControlListener;
	class IPackage;
	class IStyle;

	struct Block;

	namespace standard
	{
		/*
			No inline editing allowed. Show preview and button for modal form editor opening. Derived class should override NotifyOnActivateModal() and show corresponding modal form
		*/
		class CPropertyHandlerModal :public CPropertyHandler
		{
		private:
			IBuiltInControlListener *m_pListener;
			RectF m_sBorderWidth;
			BorderColor m_sBorderColor;
			Color m_sBackgroundColor;

			bool m_bDown;
			bool m_bOverButton;
			
			String getPreview();
		protected:
			virtual void NotifyOnActivateModal() = 0; // Called when modal form of the handler should be shown
		public:
			IBuiltInControlListener *getListener() override;
			bool isDown() override;

			void setListener(IBuiltInControlListener *value) override;
			bool setDPI(const Point &value) override;

			void UpdateFromStyle(IStyle *style, const String &class_name) override;
			void Render(const bool last_pass, const Mat4f &matrix, const Block *block) override;

			// State change notifications
			void NotifyOnAttach() override;
			void NotifyOnDeactivate() override;
			void NotifyOnFreeResources() override;

			// Mouse input notifications
			bool NotifyOnMouseHover(const PointF &position) override;
			bool NotifyOnMouseLeave() override;
			bool NotifyOnMouseMove(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			bool NotifyOnMouseLeftDown(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			bool NotifyOnMouseLeftUp(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			bool NotifyOnMouseLeftDoubleClick(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			bool NotifyOnMouseMiddleDown(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			bool NotifyOnMouseMiddleUp(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			bool NotifyOnMouseMiddleDoubleClick(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift) override;
			bool NotifyOnMouseRightDown(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift) override;
			bool NotifyOnMouseRightUp(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift) override;
			bool NotifyOnMouseRightDoubleClick(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift) override;
			void NotifyOnMouseDownCancel() override;
			bool NotifyOnMouseVerticalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta) override;
			bool NotifyOnMouseHorizontalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta) override;

			// Keyboard input notifications
			bool NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock) override;
			bool NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock) override;
			bool NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock) override;
			bool NotifyOnDeadChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock) override;

			// Other input notifications
			bool NotifyOnDropFiles(const PointF &position, const StringArray &filenames) override;

			// Clipboard notifications
			bool NotifyOnPasteString(const String &text) override;

			CPropertyHandlerModal(IPackage *package, const String &name);

			RectF getBorderWidth() const; // Return open modal button border widths
			BorderColor getBorderColor() const; // Return open modal button border colors
			Color getBackgroundColor() const; // Return open modal button background color

			bool setBorderWidth(const RectF &value); // Set open modal button border widths
			bool setBorderColor(const BorderColor &value); // Set open modal button border colors
			bool setBackgroundColor(const Color &value); // Set open modal button background color
		};
	}
}