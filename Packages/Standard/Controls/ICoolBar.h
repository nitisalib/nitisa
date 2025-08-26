// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IDialogBox.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "NTL/Core/Consts.h"

namespace nitisa
{
	class IControl;
	class ITexture;

	namespace standard
	{
		/*
			If control is on another control, only move before/after another controls on that parent is allowed as well as changing size of previous cool bar widget if there is one.
		*/
		class ICoolBar :public virtual IDialogBox
		{
		public:
			class IVisibilityManager
			{
			protected:
				IVisibilityManager() = default;
				~IVisibilityManager() = default;
				IVisibilityManager(const IVisibilityManager &other) = delete;
				IVisibilityManager(IVisibilityManager &&other) = delete;
				IVisibilityManager &operator=(const IVisibilityManager &other) = delete;
				IVisibilityManager &operator=(IVisibilityManager &&other) = delete;
			public:
				virtual bool isVisible(IControl *control, const int index) = 0; // Whether control should be shown on CoolBar
				virtual bool isExtraVisible(IControl *control, const int index) = 0; // Whether control is visible on extra list
				virtual bool isTogglable(IControl *control, const int index) = 0; // Whether control visibility can be toggled
				virtual String getTitle(IControl *control, const int index) = 0; // Return control title
				virtual ITexture *getIcon(IControl *control, const int index, RectF &part) = 0; // Return control icon

				virtual bool setVisible(IControl *control, const int index, const bool value) = 0; // Set control visibility
			};
		protected:
			ICoolBar() = default;
			~ICoolBar() = default;
			ICoolBar(const ICoolBar &other) = delete;
			ICoolBar(ICoolBar &&other) = delete;
			ICoolBar &operator=(const ICoolBar &other) = delete;
			ICoolBar &operator=(ICoolBar &&other) = delete;
		public:
			enum class Orientation // Control orientations. Defines where moving part is and direction of child controls alignment
			{
				LeftToRight, // Moving part is at the left and children are aligned from left to top if they are
				TopToBottom, // Moving part is at the top and children are aligned from top to bottom if they are
				RightToLeft, // Moving part is at the right and children are aligned from right to left if they are
				BottomToTop // Moving part is at the bottom and children are aligned from bottom to top if they are
			};
		public:
			virtual Orientation getOrientation() = 0; // Return current orientation
			virtual float getStickDistance() = 0; // Return distance to form edges and/or another cool bars at which control sticks to them
			virtual bool isAutoAlign() = 0; // Return whether control alignment should be selected automatically depending on where is it being moved
			virtual bool isLocked() = 0; // Return whether control can be moved by user
			virtual bool isResizable() = 0; // Return whether control can be resized
			virtual IVisibilityManager *getVisibilityManager() = 0; // Return assigned visibility manager. Visibility manager is not destroyed automatically when widget is being destroyed
			virtual PointF getResizeLimits() = 0; // Return min and max allowed sizes during resizing

			virtual bool setOrientation(const Orientation value) = 0; // Set orientation, change Align to proper one if control is aligned
			virtual bool setStickDistance(const float value, const float tolerance = ntl::Tolerance<float>) = 0; // Set distance to form edges and/or another cool bars at which control sticks to them
			virtual bool setAutoAlign(const bool value) = 0; // Set whether control alignment should be selected automatically depending on where is it being moved
			virtual bool setLocked(const bool value) = 0; // Set whether control can be moved by user
			virtual bool setResizable(const bool value) = 0; // Set whether control can be resized
			virtual bool setVisibilityManager(IVisibilityManager *value) = 0; // Assign new visibility manager. Previous visibility manager is not destroyed automatically
		};
	}
}