// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Releasable.h"
#include "Nitisa/Core/TextureFormat.h"
#include "Nitisa/Interfaces/IBaseTexture.h"
#include "Nitisa/Math/Rect.h"

namespace nitisa
{
	class CBaseTexture :public virtual IBaseTexture, public CReleasable
	{
	protected:
		CBaseTexture();

		CBaseTexture(const CBaseTexture &other) = delete;
		CBaseTexture(CBaseTexture &&other) = delete;
		CBaseTexture &operator=(const CBaseTexture &other) = delete;
		CBaseTexture &operator=(CBaseTexture &&other) = delete;
	public:
		// IBaseTexture getters
		bool isValid() const override;

		// IBaseTexture setters
		bool setValid(const bool value) override;
		bool setInvalidRect(const nitisa::Rect &value) override;
	};
}