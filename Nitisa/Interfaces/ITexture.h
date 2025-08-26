// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Consts.h"
#include "../Core/Aliases.h"
#include "../Core/Strings.h"
#include "../Core/TextureCompareFunction.h"
#include "../Core/TextureCompareMode.h"
#include "../Core/TextureDepthStencilMode.h"
#include "../Core/TextureFormat.h"
#include "../Core/TextureMagFilter.h"
#include "../Core/TextureMinFilter.h"
#include "../Core/TextureSwizzle.h"
#include "../Core/TextureWrap.h"
#include "../Image/Color.h"
#include "../Math/Rect.h"
#include "../Math/RectF.h"
#include "IBaseTexture.h"
#include "IReleasable.h"

namespace nitisa
{
	class ITexture : public virtual IBaseTexture
	{
	protected:
		ITexture() = default;
		~ITexture() = default;
		ITexture(const ITexture &other) = delete;
		ITexture(ITexture &&other) = delete;
		ITexture &operator=(const ITexture &other) = delete;
		ITexture &operator=(ITexture &&other) = delete;
	public:
		class IData : public virtual IReleasable
		{
		protected:
			IData() = default;
			~IData() = default;
			IData(const IData &other) = delete;
			IData(IData &&other) = delete;
			IData &operator=(const IData &other) = delete;
			IData &operator=(IData &&other) = delete;
		protected:
			int m_iLevel;
			int m_iWidth;
			int m_iHeight;
			bool m_bPrecomputed;
		public:
			const int &Level{ m_iLevel };
			const int &Width{ m_iWidth };
			const int &Height{ m_iHeight };
			const bool &Precomputed{ m_bPrecomputed };

			virtual Color getColor(const int x, const int y) const = 0;
			virtual void getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha) = 0;
			virtual void getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha) = 0;
			virtual float getDepth(const int x, const int y) const = 0;
			virtual unsigned char getStencil(const int x, const int y) const = 0;
			virtual unsigned char *getData() = 0;

			virtual void setColor(const int x, const int y, const Color &color) = 0;
			virtual void setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha) = 0;
			virtual void setDepth(const int x, const int y, const float value) = 0;
			virtual void setStencil(const int x, const int y, const unsigned char value) = 0;
		};
	protected:
		String m_sFilename;
		int m_iRequiredLevelCount;
		int m_iActualLevelCount;
		bool m_bPrecomputed;
		TextureMinFilter m_eMinFilter;
		TextureMagFilter m_eMagFilter;
		TextureDepthStencilMode m_eDepthStencilMode;
		int m_iBaseLevel;
		float m_fMinLOD;
		float m_fMaxLOD;
		TextureWrap m_eWrapS;
		TextureWrap m_eWrapT;
		TextureWrap m_eWrapR;
		Color m_sBorderColor;
		TextureCompareMode m_eCompareMode;
		TextureCompareFunction m_eCompareFunction;
		float m_fLODBias;
		int m_iMaxLevel;
		TextureSwizzle m_eSwizzleR;
		TextureSwizzle m_eSwizzleG;
		TextureSwizzle m_eSwizzleB;
		TextureSwizzle m_eSwizzleA;
	public:
		String const &Filename{ m_sFilename };
		int const &RequiredLevelCount{ m_iRequiredLevelCount }; // How much layers texture should have. 0 - maximum allowed. If specified to big value, maximum allowed level count will be created
		int const &ActualLevelCount{ m_iActualLevelCount }; // How many levels texture really has
		bool const &Precomputed{ m_bPrecomputed }; // Whether color values are multiplied by alpha(for RGBA textures only). Used to facilitate blending
		TextureMinFilter const &MinFilter{ m_eMinFilter };
		TextureMagFilter const &MagFilter{ m_eMagFilter };
		TextureDepthStencilMode const &DepthStencilMode{ m_eDepthStencilMode };
		int const &BaseLevel{ m_iBaseLevel }; // Starting level to generate mipmaps
		float const &MinLOD{ m_fMinLOD };
		float const &MaxLOD{ m_fMaxLOD };
		TextureWrap const &WrapS{ m_eWrapS };
		TextureWrap const &WrapT{ m_eWrapT };
		TextureWrap const &WrapR{ m_eWrapR };
		Color const &BorderColor{ m_sBorderColor };
		TextureCompareMode const &CompareMode{ m_eCompareMode };
		TextureCompareFunction const &CompareFunction{ m_eCompareFunction };
		float const &LODBias{ m_fLODBias };
		int const &MaxLevel{ m_iMaxLevel }; // Max level to generate mipmaps
		TextureSwizzle const &SwizzleR{ m_eSwizzleR };
		TextureSwizzle const &SwizzleG{ m_eSwizzleG };
		TextureSwizzle const &SwizzleB{ m_eSwizzleB };
		TextureSwizzle const &SwizzleA{ m_eSwizzleA };

		virtual bool setRequiredLevelCount(const int value) = 0;
		virtual bool setDepthStencilMode(const TextureDepthStencilMode value) = 0;
		virtual bool setBaseLevel(const int value) = 0;
		virtual bool setMinFilter(const TextureMinFilter value) = 0; // Set minifying mode
		virtual bool setMagFilter(const TextureMagFilter value) = 0; // Set magnification mode
		virtual bool setMinLOD(const float value, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setMaxLOD(const float value, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setWrapS(const TextureWrap value) = 0;
		virtual bool setWrapT(const TextureWrap value) = 0;
		virtual bool setWrapR(const TextureWrap value) = 0;
		virtual bool setBorderColor(const Color &value) = 0;
		virtual bool setCompareMode(const TextureCompareMode value) = 0;
		virtual bool setCompareFunction(const TextureCompareFunction value) = 0;
		virtual bool setLODBias(const float value, const float relative_tolerance = ntl::RelativeTolerance<float>) = 0;
		virtual bool setMaxLevel(const int value) = 0;
		virtual bool setSwizzleR(const TextureSwizzle value) = 0;
		virtual bool setSwizzleG(const TextureSwizzle value) = 0;
		virtual bool setSwizzleB(const TextureSwizzle value) = 0;
		virtual bool setSwizzleA(const TextureSwizzle value) = 0;
		virtual bool setSwizzleRGBA(const TextureSwizzle value) = 0;

		virtual IData *Lock(const TextureFormat format, const int level, const bool read_only) = 0; // Return data which could be accessed directly and changed. DepthStencil format is not allowed, use separately Depth and Stencil instead
	};
}