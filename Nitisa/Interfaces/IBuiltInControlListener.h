// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Math/RectF.h"

namespace nitisa
{
	class IBuiltInControl;

	class IBuiltInControlListener // Listener can be set by owner to get notifications when built-in control state is changed by timer or other method which isn't initiated by owner
	{
	protected:
		IBuiltInControlListener() = default;
		~IBuiltInControlListener() = default;
		IBuiltInControlListener(const IBuiltInControlListener &other) = delete;
		IBuiltInControlListener(IBuiltInControlListener &&other) = delete;
		IBuiltInControlListener &operator=(const IBuiltInControlListener &other) = delete;
		IBuiltInControlListener &operator=(IBuiltInControlListener &&other) = delete;
	public:
		virtual void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) = 0; // Notify parent about repainting required
	};
}