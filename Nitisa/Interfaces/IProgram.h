// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "IReleasable.h"

namespace nitisa
{
	// Usage:
	//		1. Create using either IRenderer::CreateProgram methods or CreateShaderProgram function
	//		2. Activate using IRenderer
	//		3. Render using IRenderer or native graphics object
	//		4. Activate previous shader program in IRenderer
	class IProgram : public virtual IReleasable
	{
	protected:
		IProgram() = default;
		~IProgram() = default;
		IProgram(const IProgram &other) = delete;
		IProgram(IProgram &&other) = delete;
		IProgram &operator=(const IProgram &other) = delete;
		IProgram &operator=(IProgram &&other) = delete;
	protected:
		PlatformHandle m_hHandle;
	public:
		PlatformHandle const &Handle{ m_hHandle };

		virtual void NotifyOnActivate() = 0; // Called after renderer activates the program. Program can, for example, set subroutines
	};
}