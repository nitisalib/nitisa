// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ListItem.h"
#include "Nitisa/Core/Strings.h"
#include "../IListItemMultiButton.h"

namespace nitisa
{
	class IListItem;

	namespace standard
	{
		class CListItemMultiButton :public virtual IListItemMultiButton, public CListItem
		{
		private:
			String m_sCaption;
			int m_iImageIndex;
			int m_iImageIndexHovered;
			int m_iImageIndexFocused;
			int m_iImageIndexFocusedHovered;
			int m_iImageIndexDown;
			int m_iImageIndexDownHovered;
			int m_iImageIndexDownFocused;
			int m_iImageIndexDownFocusedHovered;
			int m_iImageIndexActive;
			int m_iImageIndexActiveHovered;
			int m_iImageIndexInactive;
			int m_iImageIndexInactiveHovered;
			int m_iImageIndexDisabled;
		public:
			// IListItem methods
			IListItem *Clone() override;
			bool Copy(IListItem *dest) override;

			// IListItemCaption getters
			String getCaption() override;

			// IListItemCaption setters
			bool setCaption(const String &value) override;

			// IListItemMultiButton getters
			int getImageIndex() const override; // Return image index in normal state

			// IListItemMultiButton setters
			bool setImageIndex(const int value) override; // Sets the same image index to all states

			CListItemMultiButton();
			CListItemMultiButton(const String &caption);

			// Getters
			int getImageIndexNormal() const;
			int getImageIndexHovered() const;
			int getImageIndexFocused() const;
			int getImageIndexFocusedHovered() const;
			int getImageIndexDown() const;
			int getImageIndexDownHovered() const;
			int getImageIndexDownFocused() const;
			int getImageIndexDownFocusedHovered() const;
			int getImageIndexActive() const;
			int getImageIndexActiveHovered() const;
			int getImageIndexInactive() const;
			int getImageIndexInactiveHovered() const;
			int getImageIndexDisabled() const;

			// Setters
			bool setImageIndexNormal(const int value);
			bool setImageIndexHovered(const int value);
			bool setImageIndexFocused(const int value);
			bool setImageIndexFocusedHovered(const int value);
			bool setImageIndexDown(const int value);
			bool setImageIndexDownHovered(const int value);
			bool setImageIndexDownFocused(const int value);
			bool setImageIndexDownFocusedHovered(const int value);
			bool setImageIndexActive(const int value);
			bool setImageIndexActiveHovered(const int value);
			bool setImageIndexInactive(const int value);
			bool setImageIndexInactiveHovered(const int value);
			bool setImageIndexDisabled(const int value);
		};
	}
}