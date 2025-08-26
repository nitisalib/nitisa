// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	namespace standard
	{
		class IBevel :public virtual IControl
		{
		protected:
			IBevel() = default;
			~IBevel() = default;
			IBevel(const IBevel &other) = delete;
			IBevel(IBevel &&other) = delete;
			IBevel &operator=(const IBevel &other) = delete;
			IBevel &operator=(IBevel &&other) = delete;
		public:
			enum class BevelKind // Bevel kind
			{
				Box, // Have all 4 borders which look like a panel
				Frame, // Have all 4 borders which look like frame
				LeftEdge, // Show only left border
				TopEdge, // Show only top border
				RightEdge, // Show only right border
				BottomEdge // Show only bottom border
			};

			enum class BevelStyle // Border style
			{
				Lowered, // Lowered style
				Raised // Raised style(inverse colors)
			};
		public:
			virtual BevelKind getBevelKind() = 0; // Return bevel kind
			virtual BevelStyle getBevelStyle() = 0; // Return bevel border style

			virtual bool setBevelKind(const BevelKind value) = 0; // Set bevel kind
			virtual bool setBevelStyle(const BevelStyle value) = 0; // Set bevel border style
		};
	}
}