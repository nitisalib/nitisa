// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "NTL/Core/Consts.h"
#include "Nitisa/Core/BaseTexture.h"
#include "Nitisa/Core/Releasable.h"
#include "Nitisa/Core/TextureCompareFunction.h"
#include "Nitisa/Core/TextureCompareMode.h"
#include "Nitisa/Core/TextureDepthStencilMode.h"
#include "Nitisa/Core/TextureFormat.h"
#include "Nitisa/Core/TextureMagFilter.h"
#include "Nitisa/Core/TextureMinFilter.h"
#include "Nitisa/Core/TextureSwizzle.h"
#include "Nitisa/Core/TextureWrap.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Interfaces/IReleasableListener.h"
#include "Nitisa/Interfaces/ITexture.h"
#include "Nitisa/Math/Rect.h"

namespace nitisa
{
	class IFramebuffer;
	class IReleasable;
	class IRenderer;

	class COpenGL;

	namespace platform
	{
		namespace android
		{
			namespace gles31d
			{
				class CRenderer;
			}

			namespace gles31r
			{
				class CRenderer;
			}

			namespace gles
			{
				class CTexture :public virtual ITexture, public CBaseTexture
				{
					friend gles31d::CRenderer;
					friend gles31r::CRenderer;
				private:
					class CDataAlpha :public virtual IData, public CReleasable
					{
					private:
						struct DATA
						{
							unsigned char A;
						};
					private:
						CTexture *m_pTexture;
						bool m_bReadOnly;
						DATA *m_aData;
					protected:
						void BeforeRelease() override;
					public:
						// IData getters
						Color getColor(const int x, const int y) const override;
						void getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha) override;
						void getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha) override;
						float getDepth(const int x, const int y) const override;
						unsigned char getStencil(const int x, const int y) const override;
						unsigned char *getData() override;

						// IData setters
						void setColor(const int x, const int y, const Color &value) override;
						void setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha) override;
						void setDepth(const int x, const int y, const float value) override;
						void setStencil(const int x, const int y, const unsigned char value) override;

						CDataAlpha(CTexture *texture, const int level, const bool read_only);
					};

					class CDataAlphaFloat :public virtual IData, public CReleasable
					{
					private:
						struct DATA
						{
							float A;
						};
					private:
						CTexture *m_pTexture;
						bool m_bReadOnly;
						DATA *m_aData;
					protected:
						void BeforeRelease() override;
					public:
						// IData getters
						Color getColor(const int x, const int y) const override;
						void getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha) override;
						void getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha) override;
						float getDepth(const int x, const int y) const override;
						unsigned char getStencil(const int x, const int y) const override;
						unsigned char *getData() override;

						// IData setters
						void setColor(const int x, const int y, const Color &value) override;
						void setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha) override;
						void setDepth(const int x, const int y, const float value) override;
						void setStencil(const int x, const int y, const unsigned char value) override;

						CDataAlphaFloat(CTexture *texture, const int level, const bool read_only);
					};

					class CDataRGB :public virtual IData, public CReleasable
					{
					private:
						struct DATA
						{
							unsigned char R;
							unsigned char G;
							unsigned char B;
							unsigned char Unused;
						};
					private:
						CTexture *m_pTexture;
						bool m_bReadOnly;
						DATA *m_aData;
					protected:
						void BeforeRelease() override;
					public:
						// IData getters
						Color getColor(const int x, const int y) const override;
						void getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha) override;
						void getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha) override;
						float getDepth(const int x, const int y) const override;
						unsigned char getStencil(const int x, const int y) const override;
						unsigned char *getData() override;

						// IData setters
						void setColor(const int x, const int y, const Color &value) override;
						void setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha) override;
						void setDepth(const int x, const int y, const float value) override;
						void setStencil(const int x, const int y, const unsigned char value) override;

						CDataRGB(CTexture *texture, const int level, const bool read_only);
					};

					class CDataRGBFloat :public virtual IData, public CReleasable
					{
					private:
						struct DATA
						{
							float R;
							float G;
							float B;
						};
					private:
						CTexture *m_pTexture;
						bool m_bReadOnly;
						DATA *m_aData;
					protected:
						void BeforeRelease() override;
					public:
						// IData getters
						Color getColor(const int x, const int y) const override;
						void getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha) override;
						void getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha) override;
						float getDepth(const int x, const int y) const override;
						unsigned char getStencil(const int x, const int y) const override;
						unsigned char *getData() override;

						// IData setters
						void setColor(const int x, const int y, const Color &value) override;
						void setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha) override;
						void setDepth(const int x, const int y, const float value) override;
						void setStencil(const int x, const int y, const unsigned char value) override;

						CDataRGBFloat(CTexture *texture, const int level, const bool read_only);
					};

					class CDataRGBA :public virtual IData, public CReleasable
					{
					private:
						struct DATA
						{
							unsigned char R;
							unsigned char G;
							unsigned char B;
							unsigned char A;
						};
					private:
						CTexture *m_pTexture;
						bool m_bReadOnly;
						DATA *m_aData;
					protected:
						void BeforeRelease() override;
					public:
						// IData getters
						Color getColor(const int x, const int y) const override;
						void getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha) override;
						void getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha) override;
						float getDepth(const int x, const int y) const override;
						unsigned char getStencil(const int x, const int y) const override;
						unsigned char *getData() override;

						// IData setters
						void setColor(const int x, const int y, const Color &value) override;
						void setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha) override;
						void setDepth(const int x, const int y, const float value) override;
						void setStencil(const int x, const int y, const unsigned char value) override;

						CDataRGBA(CTexture *texture, const int level, const bool read_only);
					};

					class CDataRGBAPrecomputed :public virtual IData, public CReleasable
					{
					private:
						struct DATA
						{
							unsigned char R;
							unsigned char G;
							unsigned char B;
							unsigned char A;
						};
					private:
						CTexture *m_pTexture;
						bool m_bReadOnly;
						DATA *m_aData;
					protected:
						void BeforeRelease() override;
					public:
						// IData getters
						Color getColor(const int x, const int y) const override;
						void getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha) override;
						void getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha) override;
						float getDepth(const int x, const int y) const override;
						unsigned char getStencil(const int x, const int y) const override;
						unsigned char *getData() override;

						// IData setters
						void setColor(const int x, const int y, const Color &value) override;
						void setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha) override;
						void setDepth(const int x, const int y, const float value) override;
						void setStencil(const int x, const int y, const unsigned char value) override;

						CDataRGBAPrecomputed(CTexture *texture, const int level, const bool read_only);
					};

					class CDataRGBAFloat :public virtual IData, public CReleasable
					{
					private:
						struct DATA
						{
							float R;
							float G;
							float B;
							float A;
						};
					private:
						CTexture *m_pTexture;
						bool m_bReadOnly;
						DATA *m_aData;
					protected:
						void BeforeRelease() override;
					public:
						// IData getters
						Color getColor(const int x, const int y) const override;
						void getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha) override;
						void getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha) override;
						float getDepth(const int x, const int y) const override;
						unsigned char getStencil(const int x, const int y) const override;
						unsigned char *getData() override;

						// IData setters
						void setColor(const int x, const int y, const Color &value) override;
						void setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha) override;
						void setDepth(const int x, const int y, const float value) override;
						void setStencil(const int x, const int y, const unsigned char value) override;

						CDataRGBAFloat(CTexture *texture, const int level, const bool read_only);
					};

					class CDataRGBAFloatPrecomputed :public virtual IData, public CReleasable
					{
					private:
						struct DATA
						{
							float R;
							float G;
							float B;
							float A;
						};
					private:
						CTexture *m_pTexture;
						bool m_bReadOnly;
						DATA *m_aData;
					protected:
						void BeforeRelease() override;
					public:
						// IData getters
						Color getColor(const int x, const int y) const override;
						void getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha) override;
						void getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha) override;
						float getDepth(const int x, const int y) const override;
						unsigned char getStencil(const int x, const int y) const override;
						unsigned char *getData() override;

						// IData setters
						void setColor(const int x, const int y, const Color &value) override;
						void setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha) override;
						void setDepth(const int x, const int y, const float value) override;
						void setStencil(const int x, const int y, const unsigned char value) override;

						CDataRGBAFloatPrecomputed(CTexture *texture, const int level, const bool read_only);
					};

					class CDataDepth :public virtual IData, public CReleasable
					{
					private:
						struct DATA
						{
							float D;
						};
					private:
						CTexture *m_pTexture;
						bool m_bReadOnly;
						DATA *m_aData;
					protected:
						void BeforeRelease() override;
					public:
						// IData getters
						Color getColor(const int x, const int y) const override;
						void getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha) override;
						void getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha) override;
						float getDepth(const int x, const int y) const override;
						unsigned char getStencil(const int x, const int y) const override;
						unsigned char *getData() override;

						// IData setters
						void setColor(const int x, const int y, const Color &value) override;
						void setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha) override;
						void setDepth(const int x, const int y, const float value) override;
						void setStencil(const int x, const int y, const unsigned char value) override;

						CDataDepth(CTexture *texture, const int level, const bool read_only);
					};

					class CDataStencil :public virtual IData, public CReleasable
					{
					private:
						struct DATA
						{
							unsigned char S;
						};
					private:
						CTexture *m_pTexture;
						bool m_bReadOnly;
						DATA *m_aData;
					protected:
						void BeforeRelease() override;
					public:
						// IData getters
						Color getColor(const int x, const int y) const override;
						void getColor(const int x, const int y, unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha) override;
						void getColor(const int x, const int y, float &red, float &green, float &blue, float &alpha) override;
						float getDepth(const int x, const int y) const override;
						unsigned char getStencil(const int x, const int y) const override;
						unsigned char *getData() override;

						// IData setters
						void setColor(const int x, const int y, const Color &value) override;
						void setColor(const int x, const int y, const float red, const float green, const float blue, const float alpha) override;
						void setDepth(const int x, const int y, const float value) override;
						void setStencil(const int x, const int y, const unsigned char value) override;

						CDataStencil(CTexture *texture, const int level, const bool read_only);
					};

					class CDataReleaseListener :public virtual IReleasableListener
					{
					private:
						CTexture *m_pTexture;
					public:
						void NotifyOnRelease(IReleasable *sender) override;

						CDataReleaseListener(CTexture *texture);
					};
				protected:
					CDataReleaseListener m_cDataReleaseListener;
					COpenGL *m_pGraphics;
					IData *m_pData;
					IRenderer *m_pRenderer;
					IFramebuffer *m_pFramebuffer;

					CTexture(COpenGL *graphics, IRenderer *renderer, const bool precomputed);

					CTexture(const CTexture &other) = delete;
					CTexture(CTexture &&other) = delete;
					CTexture &operator=(const CTexture &other) = delete;
					CTexture &operator=(CTexture &&other) = delete;

					static int CalculateLevelCount(const int width, const int height, const int max_level_count);
					void UpdateParameters();
					void UpdateTexture();
					void BeforeRelease() override;

					static CTexture *Create(COpenGL *graphics, IRenderer *renderer, const bool precomputed);
				public:
					// ITexture setters
					bool setFormat(const TextureFormat value) override;
					bool setRequiredLevelCount(const int value) override;
					bool setSize(const int width, const int height) override;
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

					// ITexture methods
					IData *Lock(const TextureFormat format, const int level, const bool read_only) override;
				};
			}
		}
	}
}
#endif