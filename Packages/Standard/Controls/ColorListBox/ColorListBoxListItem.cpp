// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace standard
	{
		CColorListBoxListItem::CColorListBoxListItem(const Color &color, const String &caption) : CListItemColor(color, caption)
		{
			setCaptionColor(State::Hovered, Color{ 0, 0, 0, 0 });
			setCaptionColor(State::Active, Color{ 0, 0, 0, 0 });
			setCaptionColor(State::ActiveHovered, Color{ 0, 0, 0, 0 });
			setBackgroundColor(State::Hovered, Color{ 0, 0, 0, 0 });
			for (int i = (int)State::Active; i <= (int)State::ActiveSelectedHovered; i++)
			{
				setBorderWidth((State)i, RectF{ 1, 1, 1, 1 });
				setBorderColor((State)i, BorderColor{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } });

				setColorBorderWidth((State)i, RectF{ 1, 1, 1, 1 });
				setColorBorderColor((State)i, BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } });
			}
			setBackgroundColor(State::Active, Color{ 0, 0, 0, 0 });
			setBackgroundColor(State::ActiveHovered, Color{ 0, 0, 0, 0 });
			setColorBorderWidth(State::Hovered, RectF{ 0, 0, 0, 0 });

			setColorBorderWidth(State::Selected, RectF{ 1, 1, 1, 1 });
			setColorBorderColor(State::Selected, BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } });
			setColorBorderWidth(State::SelectedHovered, RectF{ 1, 1, 1, 1 });
			setColorBorderColor(State::SelectedHovered, BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } });
		}
	}
}