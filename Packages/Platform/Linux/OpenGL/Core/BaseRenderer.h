// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "NTL/Core/Consts.h"
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Bitmask.h"
#include "Nitisa/Core/BlurType.h"
#include "Nitisa/Core/Releasable.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/TextureCompareFunction.h"
#include "Nitisa/Core/TextureCompareMode.h"
#include "Nitisa/Core/TextureDepthStencilMode.h"
#include "Nitisa/Core/TextureFormat.h"
#include "Nitisa/Core/TextureMagFilter.h"
#include "Nitisa/Core/TextureMinFilter.h"
#include "Nitisa/Core/TextureSwizzle.h"
#include "Nitisa/Core/TextureWrap.h"
#include "Nitisa/Core/Version2.h"
#include "Nitisa/Image/BlockColors.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IPlatformFont.h"
#include "Nitisa/Interfaces/IRenderer.h"
#include "Nitisa/Interfaces/ITexture.h"
#include "Nitisa/Math/Block.h"
#include "Nitisa/Math/CubicBezierSplineLimits.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/Rect.h"
#include "Nitisa/Math/RectF.h"
#include <vector>

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	class IFramebuffer;
	class IProgram;
	class ITextureMultisample;
	class IVertexArray;
	class IWindow;

	class COpenGL;

	class Image;

	namespace platform
	{
		namespace linux
		{
			class CApplication;

			namespace opengl
			{
				class CBaseRenderer :public virtual IRenderer, public CReleasable
				{
				protected:
					struct IMAGE_TEXTURE
					{
						const nitisa::Image *Data;
						ITexture *Texture;

						bool operator==(const IMAGE_TEXTURE &other) const
						{
							return Texture == other.Texture;
						}
					};

					struct MASK
					{
						ITexture *Texture;
						Mat4f MInv;
						Mat4f M;
					};

					class CSearchPlatformFont :public virtual IPlatformFont
					{
					public:
						bool RegisterReleaseListener(IReleasableListener *value) override;
						bool UnregisterReleaseListener(IReleasableListener *value) override;
						int AddRef() override;
						bool Release(const bool force = false) override;
						Char *getChar(const wchar_t chr) override;
						PointF getStringSize(const String &str, const float distance) override;
						ITexture *getTexture() override;
					};

					class CSearchTexture :public virtual ITexture
					{
					public:
						bool RegisterReleaseListener(IReleasableListener *value) override;
						bool UnregisterReleaseListener(IReleasableListener *value) override;
						int AddRef() override;
						bool Release(const bool force = false) override;
						bool isValid() const override;
						bool setFormat(const TextureFormat value) override;
						bool setRequiredLevelCount(const int value) override;
						bool setSize(const int width, const int height) override;
						bool setValid(const bool value) override;
						bool setInvalidRect(const nitisa::Rect &value) override;
						bool setDepthStencilMode(const TextureDepthStencilMode value) override;
						bool setBaseLevel(const int value) override;
						bool setMinFilter(const TextureMinFilter value) override;
						bool setMagFilter(const TextureMagFilter value) override;
						bool setMinLOD(const float value, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
						bool setMaxLOD(const float value, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
						bool setWrapS(const TextureWrap value) override;
						bool setWrapT(const TextureWrap value) override;
						bool setWrapR(const TextureWrap value) override;
						bool setBorderColor(const Color &value) override;
						bool setCompareMode(const TextureCompareMode value) override;
						bool setCompareFunction(const TextureCompareFunction value) override;
						bool setLODBias(const float value, const float relative_tolerance = ntl::RelativeTolerance<float>) override;
						bool setMaxLevel(const int value) override;
						bool setSwizzleR(const TextureSwizzle value) override;
						bool setSwizzleG(const TextureSwizzle value) override;
						bool setSwizzleB(const TextureSwizzle value) override;
						bool setSwizzleA(const TextureSwizzle value) override;
						bool setSwizzleRGBA(const TextureSwizzle value) override;
						IData *Lock(const TextureFormat format, const int level, const bool read_only) override;
					};
				protected:
					std::vector<IPlatformFont*> m_aFonts;
					std::vector<IProgram*> m_aPrograms;
					std::vector<IFramebuffer*> m_aFramebuffers;
					std::vector<IVertexArray*> m_aVertexArrays;
					std::vector<ITexture*> m_aTextures;
					std::vector<ITextureMultisample*> m_aTextureMultisamples;
					std::vector<ITexture*> m_aFileTextures;
					std::vector<IMAGE_TEXTURE> m_aImageTextures;
					std::vector<MASK> m_aMasks;
					IFramebuffer *m_pDefaultFramebuffer;
					IFramebuffer *m_pFramebuffer;
					ITexture *m_pGradientPositions;
					ITexture *m_pGradientColors;
					nitisa::Block m_sActiveBlock;
					Bitmask m_sActiveBitmask;
					CubicBezierSplineLimits m_sActiveSplineLimits;
					Mat4f m_sActivePrimitiveMatrix;
					bool m_bDoubleBuffered;
					int m_iMultisample;
					Version2 m_sRequestedVersion;
					bool m_bFontsSorted;
					bool m_bFileTexturesSorted;
					bool m_bImageTexturesSorted;
					bool m_bDrawing;
					Rect m_sViewportForm; // Viewport of window(no render target assigned)
					Mat4f m_sMatrixFormToGL;
					TextureMinFilter m_eActiveTargetMinFilter;
					TextureMagFilter m_eActiveTargetMagFilter;
					Mat4f m_sTempMatrix;
					CSearchPlatformFont m_cSearchPlatformFont;
					CSearchTexture m_cSearchTexture;
					IMAGE_TEXTURE m_sSearchImageTexture;
					PlatformHandle m_hContext;
					COpenGL *m_pGraphics;
					CApplication *m_pApplication;

					static bool CompareFonts(IPlatformFont *a, IPlatformFont *b);
					static bool CompareTextures(ITexture *a, ITexture *b);
					static bool CompareImageTextures(const IMAGE_TEXTURE &a, const IMAGE_TEXTURE &b);

					void SortFonts();
					void SortFileTextures();
					void SortImageTextures();

					bool FindPixelFormat(PlatformHandle &config, const bool double_buffered, int &multisample);

					virtual void CleanUp() = 0;
				protected:
					void BeforeRelease() override;
				public:
					// IRenderer getters
					int getPlatformFontCount() override;
					IPlatformFont *getPlatformFont(const int index) override;
					int getProgramCount() override;
					IProgram *getProgram(const int index) override;
					int getFramebufferCount() override;
					IFramebuffer *getFramebuffer(const int index) override;
					int getVertexArrayCount() override;
					IVertexArray *getVertexArray(const int index) override;
					int getTextureCount() override;
					ITexture *getTexture(const int index) override;
					int getImageTextureCount() override;
					ITexture *getImageTexture(const int index) override;
					const nitisa::Image *getImageTextureData(const int index) override;
					int getMaskCount() override;
					ITexture *getMask(const int index) override;
					const Mat4f *getMaskMatrix(const int index) override;
					bool isWindowSupported(IWindow *window) override;
					int getTextureMultisampleCount() override;
					ITextureMultisample *getTextureMultisample(const int index) override;

					// IRenderer helpers
					IRenderer *Activate() override;

					CBaseRenderer(const bool double_buffered, const int multisample, const Version2 &max_version);
				};
			}
		}
	}
}
#endif