// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Math/Mat4f.h"
#include "../Math/PointF.h"
#include "IFeedback.h"

namespace nitisa
{
	class IRenderer;

	// Feedback callback is called when repaint required
	class ICaret :public virtual IFeedback
	{
	protected:
		ICaret() = default;
		~ICaret() = default;
		ICaret(const ICaret &other) = delete;
		ICaret(ICaret &&other) = delete;
		ICaret &operator=(const ICaret &other) = delete;
		ICaret &operator=(ICaret &&other) = delete;
	public:
		virtual IRenderer *getRenderer() = 0; // Return renderer
		virtual bool isVisible() = 0; // Return whether caret is visible
		virtual PointF getSize() = 0; // Return caret size(untransformed)
		virtual float getIntervalVisible() = 0; // Return how much time caret is visible(in seconds)
		virtual float getIntervalHidden() = 0; // Return how much time caret is invisible(in seconds)
		virtual bool isInversed() = 0; // Return whether inversed drawing mode is set and available

		virtual bool setRenderer(IRenderer *value) = 0; // Set renderer
		virtual bool setVisible(const bool value) = 0; // Set whether caret is visible
		virtual bool setSize(const PointF &value) = 0; // Set caret size(untransformed)
		virtual bool setIntervalVisible(const float value) = 0; // Set how much time caret is visible(in seconds)
		virtual bool setIntervalHidden(const float value) = 0; // Set how much time caret is invisible(in seconds)
		virtual bool setInversed(const bool value) = 0; // Set inversed mode. Return false if already set or not supported

		virtual void Render(const Mat4f &matrix) = 0; // Called when rendering occur(called by control)
		virtual void Release() = 0; // Destroy instance
	};
}