// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "../Math/Point.h"
#include "../Math/Rect.h"

namespace nitisa
{
	class IHintService;

	class IHint
	{
	protected:
		IHint() = default;
		~IHint() = default;
		IHint(const IHint &other) = delete;
		IHint(IHint &&other) = delete;
		IHint &operator=(const IHint &other) = delete;
		IHint &operator=(IHint &&other) = delete;
	public:
		virtual void Release() = 0; // Destroy instance
		virtual void Render() = 0; // Should render itself. Called after form repaint specified clip rect
		virtual void Show(const String &hint, const Point &pos, const Rect &client) = 0; // Show hint at specified position(or best one in client rect)
		virtual void Hide(const bool immediately) = 0; // Hide hint if visible
		virtual IHintService *QueryService() = 0; // Return service
	};
}