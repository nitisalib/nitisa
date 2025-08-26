// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "Nitisa/Core/Bitmask.h"
#include "Nitisa/Core/BlurType.h"
#include "Nitisa/Core/FontWeight.h"
#include "Nitisa/Core/Releasable.h"
#include "Nitisa/Core/ShaderType.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/TextureFormat.h"
#include "Nitisa/Core/Version2.h"
#include "Nitisa/Core/VertexFormat.h"
#include "Nitisa/Image/BlockColors.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/GradientType.h"
#include "Nitisa/Image/Image.h"
#include "Nitisa/Interfaces/IReleasableListener.h"
#include "Nitisa/Interfaces/IRenderer.h"
#include "Nitisa/Math/Block.h"
#include "Nitisa/Math/CubicBezierSplineLimits.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/Rect.h"
#include "Nitisa/Math/RectF.h"
#include "../../Core/BaseRenderer.h"
#include <utility>
#include <vector>

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	class IBaseTexture;
	class IErrorListener;
	class IFramebuffer;
	class IPlatformFont;
	class IProgram;
	class IReleasable;
	class ITexture;
	class ITextureMultisample;
	class IVertexArray;
	class IWindow;

	namespace platform
	{
		namespace linux
		{
			namespace opengl31
			{
				class CProgramBase;
				class CProgramMini;
				class CProgramMain;
				class CVertexArrayImmutable;
			}

			namespace opengl31r
			{
				class CRenderer :public opengl::CBaseRenderer
				{
					template<class ProgramClass, class RendererClass, class NativeGraphicsClass> friend IProgram *nitisa::CreateProgram(RendererClass *renderer);
					template<class FramebufferClass, class RendererClass, class NativeGraphicsClass> friend IFramebuffer *nitisa::CreateFramebuffer(RendererClass *renderer);
					template<class VertexArrayClass, class RendererClass, class NativeGraphicsClass> friend IVertexArray *nitisa::CreateVertexArray(RendererClass *renderer);
					template<class TextureClass, class RendererClass, class NativeGraphicsClass> friend ITexture *nitisa::CreateTexture(RendererClass*, const bool);
					template<class TextureClass, class RendererClass, class NativeGraphicsClass> friend ITextureMultisample *nitisa::CreateTextureMultisample(RendererClass*);
				private:
					class CTextureReleaseListener :public virtual IReleasableListener
					{
					private:
						CRenderer *m_pRenderer;
					public:
						void NotifyOnRelease(IReleasable *sender) override;

						CTextureReleaseListener(CRenderer *renderer);
					};

					class CTextureMultisampleReleaseListener :public virtual IReleasableListener
					{
					private:
						CRenderer *m_pRenderer;
					public:
						void NotifyOnRelease(IReleasable *sender) override;

						CTextureMultisampleReleaseListener(CRenderer *renderer);
					};

					class CPlatformFontReleaseListener :public virtual IReleasableListener
					{
					private:
						CRenderer *m_pRenderer;
					public:
						void NotifyOnRelease(IReleasable *sender) override;

						CPlatformFontReleaseListener(CRenderer *renderer);
					};

					class CProgramReleaseListener :public virtual IReleasableListener
					{
					private:
						CRenderer *m_pRenderer;
					public:
						void NotifyOnRelease(IReleasable *sender) override;

						CProgramReleaseListener(CRenderer *renderer);
					};

					class CFramebufferReleaseListener :public virtual IReleasableListener
					{
					private:
						CRenderer *m_pRenderer;
					public:
						void NotifyOnRelease(IReleasable *sender) override;

						CFramebufferReleaseListener(CRenderer *renderer);
					};

					class CVertexArrayReleaseListener :public virtual IReleasableListener
					{
					private:
						CRenderer *m_pRenderer;
					public:
						void NotifyOnRelease(IReleasable *sender) override;

						CVertexArrayReleaseListener(CRenderer *renderer);
					};
				private:
					CPlatformFontReleaseListener m_cPlatformFontReleaseListener;
					CProgramReleaseListener m_cProgramReleaseListener;
					CFramebufferReleaseListener m_cFramebufferReleaseListener;
					CVertexArrayReleaseListener m_cVertexArrayReleaseListener;
					CTextureReleaseListener m_cTextureReleaseListener;
					CTextureMultisampleReleaseListener m_cTextureMultisampleReleaseListener;
					opengl31::CVertexArrayImmutable *m_pDefaultVertexArray;
					opengl31::CProgramBase *m_pActiveProgramBase;
					opengl31::CProgramMini *m_pActiveProgramMini;
					opengl31::CProgramMain *m_pProgramMain;

					bool Initialize();
					bool CreateMainProgram();
					void ActivateViewportMatrix();
					void ActivateTextureMatrix(const PointF &size);
					void PolygonSetLine(const PointF &p1, const PointF &p2, const Color &c1, const Color &c2);
					void PolygonSetLines(const std::vector<PointF> &points, const Color &color, const size_t offset, const size_t count);
					void PolygonSetTriangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &c1, const Color &c2, const Color &c3);
					void PolygonSetRectangle(const RectF &rect, const Color &c1, const Color &c2, const Color &c3, const Color &c4);
					void PolygonSetRectangle(const RectF &rect);
					void PolygonSetRectangle(const RectF &rect, const PointF &size, const RectF &part);
					void PolygonSetRectangle(const RectF &rect, const PointF &grid_size, const Color &c1, const Color &c2);
					void PolygonSetBlock(const RectF &rect, const RectF &block, const RectF &border, const RectF &radius, const BlockColors &colors);
					void PolygonSetGradientRectangle(const RectF &rect, const GradientType type);
					void PolygonSetPolygon(const std::vector<PointF> &points, const Color &color);
					void SetBlockData(const RectF &block, const RectF &border, const RectF &radius, const int index);
					void SetGradient(nitisa::Gradient &g, const bool precomputed);
				protected:
					void CleanUp() override;
				protected:
					// IRenderer helper getters
					IReleasableListener *getProgramReleaseListener() override;
					IReleasableListener *getFramebufferReleaseListener() override;
					IReleasableListener *getVertexArrayReleaseListener() override;
					IReleasableListener *getTextureReleaseListener() override;
					IReleasableListener *getTextureMultisampleReleaseListener() override;

					// IRenderer helper methods
					void AddProgram(IProgram *program) override;
					void AddFramebuffer(IFramebuffer *framebuffer) override;
					void AddVertexArray(IVertexArray *vertex_array) override;
					void AddTexture(ITexture *texture) override;
					void AddTextureMultisample(ITextureMultisample *texture) override;
				public:
					// IRenderer setters
					bool setWindow(IWindow *value, const bool fast_switch, const bool force) override;

					// IRenderer active state setters
					IRenderer *ActivateProgram(IProgram *value) override;
					IRenderer *ActivateFramebuffer(IFramebuffer *value) override;
					IRenderer *ActivateVertexArray(IVertexArray *value) override;
					IRenderer *ActivateTarget(IBaseTexture *value) override;
					IRenderer *ActivateMask(ITexture *value) override;
					IRenderer *ActivateBlock(const nitisa::Block *value) override;
					IRenderer *ActivateBlock(const nitisa::Block &value) override;
					IRenderer *ActivateBitmask(const Bitmask *value) override;
					IRenderer *ActivateBitmask(const Bitmask &value) override;
					IRenderer *ActivateSplineLimits(const CubicBezierSplineLimits *value) override;
					IRenderer *ActivateSplineLimits(const CubicBezierSplineLimits &value) override;
					IRenderer *ActivatePrimitiveMatrix(const Mat4f *value) override;
					IRenderer *ActivatePrimitiveMatrix(const Mat4f &value) override;

					// IRenderer platform fonts
					IPlatformFont *CreatePlatformFont(const String &fontname, const int height, const FontWeight weight, const bool italic, const bool underline, const bool strikeout, const bool monospace) override;

					// IRenderer programs
					IProgram *CreateProgram(const AnsiString &vertex, const AnsiString &fragment, const Bindings &bindings = { }) override;
					IProgram *CreateProgram(const AnsiString &fragment) override;
					IProgram *CreateProgram(const Shaders &shaders, const Bindings &bindings = { }) override;

					// IRenderer framebuffers
					IFramebuffer *CreateFramebuffer() override;

					// IRenderer vertex arrays
					IVertexArray *CreateVertexArray(const VertexFormat &format) override;
					IVertexArray *CreateVertexArray(const VertexFormat &format, const size_t vertex_count, const bool immutable) override;
					IVertexArray *CreateVertexArray(const VertexFormat &format, const size_t polygon_count, const size_t polygon_size, const bool immutable) override;
					
					// IRenderer textures
					ITexture *CreateTexture(const int width, const int height, const int level_count, const TextureFormat format, const bool precomputed) override;
					ITexture *CreateTextureFromImage(const nitisa::Image &data, const int level_count, const TextureFormat format, const bool precomputed) override;
					ITexture *CreateTextureFromFile(const String &filename, const int level_count, const TextureFormat format, const bool precomputed) override;
					ITextureMultisample *CreateTextureMultisample(const int width, const int height, const TextureFormat format, const int samples, const bool fixed_sample_locations) override;

					// IRenderer helpers
					IRenderer *CreateInstance() override;
					IRenderer *RestoreState() override;

					bool DrawBegin(Rect &viewport, IWindow *window) override;
					bool DrawEnd() override;
					bool Present() override;
					

					// !!! IMPORTANT !!!
					// All the methods below should NOT be called outside logical DrawBegin-DrawEnd block
					// Also you should use correct arguments, there is no check inside due to performance optimization

					bool PushMask(ITexture *mask, const Mat4f &matrix) override;
					void PopMask() override;

					IRenderer *Clear(const Color &color) override;

					// IRenderer draw line
					IRenderer *DrawLine(const PointF &p1, const PointF &p2, const Color &color) override;
					IRenderer *DrawLine(const PointF &p1, const PointF &p2, const Color &c1, const Color &c2) override;

					// IRenderer draw lines
					IRenderer *DrawLines(const std::vector<PointF> &points, const Color &color, const bool loop) override;

					// IRenderer draw triangle
					IRenderer *DrawTriangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &color) override;
					IRenderer *DrawTriangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &c1, const Color &c2, const Color &c3) override;

					// IRenderer draw rectangle
					IRenderer *DrawRectangle(const RectF &rect, const Color &color) override;
					IRenderer *DrawRectangle(const RectF &rect, const BorderColor &colors) override;

					// IRenderer draw checker
					IRenderer *DrawChecker(const RectF &rect, const PointF &grid_size, const Color &c1, const Color &c2) override;

					// IRenderer draw HSV plane
					IRenderer *DrawHSVPlane(const RectF &rect, const float hue) override;

					// IRenderer draw polygon
					IRenderer *DrawPolygon(const std::vector<PointF> &points, const Color &color) override;

					// IRenderer draw polygons
					IRenderer *DrawPolygons(const std::vector<std::vector<PointF>> &polygons, const Color &color) override;

					// IRenderer draw gradient
					IRenderer *DrawGradient(const RectF &rect, nitisa::Gradient &g) override;

					// IRenderer draw HSV gradient
					IRenderer *DrawHSVGradient(const RectF &rect, nitisa::Gradient &g) override;

					// IRenderer draw image
					IRenderer *DrawImage(IBaseTexture *image, const float transparency) override;
					IRenderer *DrawImage(IBaseTexture *image, const float transparency, const RectF &part) override;

					// IRenderer draw block
					IRenderer *DrawBlock(const RectF &block, const RectF &border, const RectF &radius, const BlockColors &colors) override;
					IRenderer *DrawBlock(const RectF &block, const RectF &border, const RectF &radius, const BlockColors &colors, const RectF &rect) override;

					// IRenderer draw text
					IRenderer *DrawText(const String &text, IPlatformFont *pf, const float distance, const Color &color) override;

					// IRenderer blur image
					IRenderer *BlurImage(ITexture *image, const int radius, const BlurType type) override;
					IRenderer *BlurImage(ITexture *source, const int radius, const BlurType type, ITexture *target) override;

					// IRenderer inverse pixels
					IRenderer *InversePixels(const RectF &rect) override;

					CRenderer(
						const bool double_buffered,
						const int multisample,
						const Version2 &max_version = Version2{ 3, 1 }
					); // Multisample will be selected a best one if invalid is specified
				};
			}
		}
	}
}
#endif