// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h"
#include "Nitisa/Core/Key.h"
#include "Nitisa/Package/Interfaces/IPropertyHandler.h"

namespace nitisa
{
	class IBuiltInControlListener;
	class IControl;
	class IPackage;

	namespace standard
	{
		class CPropertyHandlerTextInputListener;

		class CPropertyHandlerTextInput :public virtual IPropertyHandler, public CBuiltInTextInput
		{
			friend CPropertyHandlerTextInputListener;
		private:
			IControl *m_pControl;
			IPackage *m_pPackage;
			IBuiltInControlListener *m_pListener;
			CPropertyHandlerTextInputListener *m_pTextInputListener;
		protected:
			virtual void UpdatePropertyFromText() = 0; // Called when property value should be updated. Use getText() method to receive current value stored in property handler
			virtual void UpdateTextFromProperty() = 0; // Called when text value should be updated from property. Use setText() to set value in this handler
		public:
			IControl *getControl() override;
			IPackage *getPackage() override;
			IBuiltInControlListener *getListener() override;

			bool setControl(IControl *value) override;
			void setListener(IBuiltInControlListener *value) override;
			bool setFocused(const bool value) override; // On defocus apply changes to property

			bool NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock) override; // Esc - cancel edit, Return - apply changes to property

			CPropertyHandlerTextInput(IPackage *package, const String &name);
			~CPropertyHandlerTextInput() override;
		};
	}
}