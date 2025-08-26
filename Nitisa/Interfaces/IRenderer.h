// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Bitmask.h"
#include "../Core/BlurType.h"
#include "../Core/FontWeight.h"
#include "../Core/RendererCapabilities.h"
#include "../Core/RendererTechnology.h"
#include "../Core/ShaderType.h"
#include "../Core/Strings.h"
#include "../Core/TextureFormat.h"
#include "../Core/Version2.h"
#include "../Core/VertexFormat.h"
#include "../Image/BlockColors.h"
#include "../Image/BorderColor.h"
#include "../Image/Color.h"
#include "../Image/Gradient.h"
#include "../Image/Image.h"
#include "../Math/Block.h"
#include "../Math/CubicBezierSplineLimits.h"
#include "../Math/Mat4f.h"
#include "../Math/PointF.h"
#include "../Math/Rect.h"
#include "../Math/RectF.h"
#include "IReleasable.h"
#include <utility>
#include <vector>

namespace nitisa
{
	class IBaseTexture;
	class IFramebuffer;
	class INativeGraphics;
	class IPlatformFont;
	class IProgram;
	class IReleasableListener;
	class ITexture;
	class ITextureMultisample;
	class IVertexArray;
	class IWindow;

	class IRenderer : public virtual IReleasable
	{
	protected:
		IRenderer() = default;
		~IRenderer() = default;
		IRenderer(const IRenderer &other) = delete;
		IRenderer(IRenderer &&other) = delete;
		IRenderer &operator=(const IRenderer &other) = delete;
		IRenderer &operator=(IRenderer &&other) = delete;
	public:
		using Bindings = std::vector<std::pair<int, AnsiString>>; // Describes binding points for shader programs
		using Shaders = std::vector<std::pair<ShaderType, AnsiString>>; // Describes shaders for shader program

		enum class InitializationStatus
		{
			Initialized, // Initialized successfully
			NotInitialized, // Initialization was not performed yet
			DeviceContext, // Unable to get platform device context
			LoadNativeGraphics, // Unable to load native graphics
			InitNativeGraphics, // Unable to initialize native graphics
			CreateNativeGraphics, // Unable to create native graphics class instance
			Version, // Native graphics version is too low
			Feature, // Native graphics has no required feature
			FindPixelFormat, // Unable to find suitable pixel format
			SetPixelFormat, // Unable to set pixel format
			FindConfig, // Unable to find configuration for pixel format
			CreateContext, // Unable to create native graphics context
			ActivateContext, // Unable to activate native graphics context
			CreateSurface, // Unable to create window surface
			DefaultVertexArray, // Unable to create default vertex array
			DefaultTextures, // Unable to create default textures
			DefaultProgram, // Unable to create default shader program
			DefaultFramebuffer, // Unable to create default framebuffer
			DefaultTextureFramebuffer, // Unable to create default texture framebuffer
			Window // Specified window is not supported
		};
	protected:
		InitializationStatus m_eInitializationStatus;
		Version2 m_sMinVersion;
		Version2 m_sMaxVersion;
		Version2 m_sVersion;
		RendererCapabilities m_sCapabilities;
		IWindow *m_pWindow;
		INativeGraphics *m_pNativeGraphics;
		IProgram *m_pActiveProgram;
		IFramebuffer *m_pActiveFramebuffer;
		IVertexArray *m_pActiveVertexArray;
		IBaseTexture *m_pActiveTarget;
		ITexture *m_pActiveMask;
		const nitisa::Block *m_pActiveBlock;
		const Bitmask *m_pActiveBitmask;
		const CubicBezierSplineLimits *m_pActiveSplineLimits;
		const Mat4f *m_pActivePrimitiveMatrix;
		Rect m_sViewport;
		RendererTechnology m_eTechnology;
	protected:
		// Helper getters
		virtual IReleasableListener *getProgramReleaseListener() = 0;
		virtual IReleasableListener *getFramebufferReleaseListener() = 0;
		virtual IReleasableListener *getVertexArrayReleaseListener() = 0;
		virtual IReleasableListener *getTextureReleaseListener() = 0;
		virtual IReleasableListener *getTextureMultisampleReleaseListener() = 0;

		// Helper methods
		virtual void AddProgram(IProgram *program) = 0;
		virtual void AddFramebuffer(IFramebuffer *framebuffer) = 0;
		virtual void AddVertexArray(IVertexArray *vertex_array) = 0;
		virtual void AddTexture(ITexture *texture) = 0;
		virtual void AddTextureMultisample(ITextureMultisample *texture) = 0;
	public:
		// Properties
		InitializationStatus const &InitializationStatus{ m_eInitializationStatus }; // Initialization status
		Version2 const &MinVersion{ m_sMinVersion }; // Minimum native graphics version supported
		Version2 const &MaxVersion{ m_sMaxVersion }; // Minimum native graphics version supported
		Version2 const &Version{ m_sVersion }; // Currently used native graphics version
		RendererCapabilities const &Capabilities{ m_sCapabilities }; // Some renderer capabilities
		IWindow* const &Window{ m_pWindow }; // Assigned window
		INativeGraphics* const &NativeGraphics{ m_pNativeGraphics }; // Native graphics object
		IProgram* const &ActiveProgram{ m_pActiveProgram }; // Active shader program
		IFramebuffer* const &ActiveFramebuffer{ m_pActiveFramebuffer }; // Active framebuffer
		IVertexArray* const &ActiveVertexArray{ m_pActiveVertexArray }; // Active vertex array
		IBaseTexture* const &ActiveTarget{ m_pActiveTarget }; // Active render target
		ITexture* const &ActiveMask{ m_pActiveMask }; // Active mask
		const nitisa::Block* const &ActiveBlock{ m_pActiveBlock }; // Active block clipper
		const Bitmask* const &ActiveBitmask{ m_pActiveBitmask }; // Active binary mask
		const CubicBezierSplineLimits* const &ActiveSplineLimits{ m_pActiveSplineLimits }; // Active cubic bezier spline clipping
		const Mat4f* const &ActivePrimitiveMatrix{ m_pActivePrimitiveMatrix }; // Active primitive transformation matrix
		Rect const &Viewport{ m_sViewport }; // Current viewport
		RendererTechnology const &Technology{ m_eTechnology }; // Technology renderer uses

		// Getters
		virtual bool isWindowSupported(IWindow *window) = 0; // Return whether specified window can be used with the renderer. Should be called before real platform window creation. Usually handled by form automatically. May also change window private data so it will be created compatible with the renderer

		// Object getters
		virtual int getPlatformFontCount() = 0; // Return count of platform fonts
		virtual IPlatformFont *getPlatformFont(const int index) = 0; // Return platform font by index
		virtual int getProgramCount() = 0; // Return count of shader programs
		virtual IProgram *getProgram(const int index) = 0; // Return shader program by index
		virtual int getFramebufferCount() = 0; // Return count of framebuffers
		virtual IFramebuffer *getFramebuffer(const int index) = 0; // Return framebuffer by index
		virtual int getVertexArrayCount() = 0; // Return count of vertex arrays
		virtual IVertexArray *getVertexArray(const int index) = 0; // Return vertex array by index
		virtual int getTextureCount() = 0; // Return count of textures
		virtual ITexture *getTexture(const int index) = 0; // Return texture by index
		virtual int getImageTextureCount() = 0; // Return count of textures created from system memory images
		virtual ITexture *getImageTexture(const int index) = 0; // Return texture created from system memory image by index
		virtual const nitisa::Image *getImageTextureData(const int index) = 0; // Return image of texture created from system memory image by index
		virtual int getMaskCount() = 0; // Return mask count
		virtual ITexture *getMask(const int index) = 0; // Return mask by index
		virtual const Mat4f *getMaskMatrix(const int index) = 0; // Return mask matrix by index
		virtual int getTextureMultisampleCount() = 0; // Return count of multi-sample textures
		virtual ITextureMultisample *getTextureMultisample(const int index) = 0; // Return multi-sample texture by index

		// Setters
		virtual bool setWindow(IWindow *value, const bool fast_switch, const bool force) = 0; // Assign window and initialize if it's not a fast switch. Clean up if nullptr. "force" is used with "fast_switch" equal to true only. If "force" is true, previous window resources won't be cleaned up

		// Active state setters
		virtual IRenderer *ActivateProgram(IProgram *value) = 0; // Activate new shader program. Use nullptr to activate default program
		virtual IRenderer *ActivateFramebuffer(IFramebuffer *value) = 0; // Activate new framebuffer. Use nullptr to activate default framebuffer
		virtual IRenderer *ActivateVertexArray(IVertexArray *value) = 0; // Activate new vertex array. Use nullptr to activate default vertex array
		virtual IRenderer *ActivateTarget(IBaseTexture *value) = 0; // Activate new rendering target. Use nullptr to remove active rendering target. If it's nullptr, draw on window. If it's not nullptr, draw on rendering target
		virtual IRenderer *ActivateMask(ITexture *value) = 0; // Activate new mask. Use nullptr to deactivate mask usage
		virtual IRenderer *ActivateBlock(const Block *value) = 0; // Activate new block clipper. Use nullptr to remove block clipper
		virtual IRenderer *ActivateBlock(const Block &value) = 0; // Activate new block clipper
		virtual IRenderer *ActivateBitmask(const Bitmask *value) = 0; // Activate new binary mask. Use nullptr to deactivate binary mask usage
		virtual IRenderer *ActivateBitmask(const Bitmask &value) = 0; // Activate new binary mask
		virtual IRenderer *ActivateSplineLimits(const CubicBezierSplineLimits *value) = 0; // Activate new spline clipper. Use nullptr to remove spline clipper
		virtual IRenderer *ActivateSplineLimits(const CubicBezierSplineLimits &value) = 0; // Activate new spline clipper
		virtual IRenderer *ActivatePrimitiveMatrix(const Mat4f *value) = 0; // Activate new primitive matrix. Use nullptr to activate default (identity) primitive matrix
		virtual IRenderer *ActivatePrimitiveMatrix(const Mat4f &value) = 0; // Activate new primitive matrix

		// Platform fonts
		virtual IPlatformFont *CreatePlatformFont(const String &fontname, const int height, const FontWeight weight, const bool italic, const bool underline, const bool strikeout, const bool monospace) = 0; // Create platform font with specified parameters. Create only if not exists with same parameters

		// Programs
		virtual IProgram *CreateProgram(const AnsiString &vertex, const AnsiString &fragment, const Bindings &bindings = { }) = 0; // Create shader program from specified source codes of vertex and fragment shaders. May return nullptr not only when error happend but also if shader programs are not supported
		virtual IProgram *CreateProgram(const AnsiString &fragment) = 0; // Create shader program from source code of predefined format. May return nullptr
		virtual IProgram *CreateProgram(const Shaders &shaders, const Bindings &bindings = { }) = 0; // Create shader program from list of shader sources with their types. Can return nullptr in case of error or if shader programs are not supported

		// Framebuffers
		virtual IFramebuffer *CreateFramebuffer() = 0; // Create new framebuffer

		// Vertex arrays
		virtual IVertexArray *CreateVertexArray(const VertexFormat &format) = 0; // Create new vertex array with specified vertex format
		virtual IVertexArray *CreateVertexArray(const VertexFormat &format, const size_t vertex_count, const bool immutable) = 0; // Create new vertex array with specified vertex format and vertex count. Can be either immutable (unchangable) or dynamic
		virtual IVertexArray *CreateVertexArray(const VertexFormat &format, const size_t polygon_count, const size_t polygon_size, const bool immutable) = 0; // Create new vertex array with specified vertex format, polygon count and size of each polygon. Can be either immutable (unchangable) or dynamic
		
		// Textures
		virtual ITexture *CreateTexture(const int width, const int height, const int level_count, const TextureFormat format, const bool precomputed) = 0; // Create texture with specified size and format
		virtual ITexture *CreateTextureFromImage(const nitisa::Image &data, const int level_count, const TextureFormat format, const bool precomputed) = 0; // Create texture by image data, if corresponding to data texture already exists, return existing one
		virtual ITexture *CreateTextureFromFile(const String &filename, const int level_count, const TextureFormat format, const bool precomputed) = 0; // Create texture from image in file. If corresponding texture(same filename and format) already was loaded, return it instead of loading it again
		virtual ITextureMultisample *CreateTextureMultisample(const int width, const int height, const TextureFormat format, const int samples, const bool fixed_sample_locations) = 0; // Create multi-sample texture

		// Helpers
		virtual IRenderer *CreateInstance() = 0; // Create same class object(without initializing, with same constructor parameters - double buffering and multisampling if supported)
		virtual IRenderer *RestoreState() = 0; // Restore state(VAO, VBO, Program, Program subroutines, ...)
		virtual IRenderer *Activate() = 0; // Should be called before drawing outside DrawBegin()/DrawEnd() block if using multiple renderers. DrawBegin() calls it automatically. Also when form is being destroyed(receive OnDestroy notification), it also calls this method
		
		// Draw and present
		virtual bool DrawBegin(Rect &viewport, IWindow *window) = 0; // Prepare for drawing. Viewport may be changed(if client area of window was changed, it will be set to new client area). Should always be called before start drawing. It is done automatically in default form implementation
		virtual bool DrawEnd() = 0; // Clean up after drawing. Should be called after all drawings. It is called automatically by default form implementation
		virtual bool Present() = 0; // Draw to screen. Render target should be set to nullptr

		// Masks
		virtual bool PushMask(ITexture *mask, const Mat4f &matrix) = 0; // Add mask in list. The matrix should be relative to prev mask. Texture is unchanged. Alpha channel of masks is used for clipping
		virtual void PopMask() = 0; // Delete last added masking texture. Texture is unchanged

		// Fill entire area of current render target
		virtual IRenderer *Clear(const Color &color) = 0; // Clear with specified color. Clear color is unchanged after it. Use it for texture clean(when render target is texture)

		virtual IRenderer *DrawLine(const PointF &p1, const PointF &p2, const Color &color) = 0; // Draw line
		virtual IRenderer *DrawLine(const PointF &p1, const PointF &p2, const Color &c1, const Color &c2) = 0; // Draw line. Points can have different colors

		virtual IRenderer *DrawLines(const std::vector<PointF> &points, const Color &color, const bool loop) = 0; // Draw lines

		virtual IRenderer *DrawTriangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &color) = 0; // Draw triangle
		virtual IRenderer *DrawTriangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &c1, const Color &c2, const Color &c3) = 0; // Draw triangle. Points can have different colors

		virtual IRenderer *DrawRectangle(const RectF &rect, const Color &color) = 0; // Draw rectangle
		virtual IRenderer *DrawRectangle(const RectF &rect, const BorderColor &colors) = 0; // Draw rectangle. Points can have different colors

		virtual IRenderer *DrawChecker(const RectF &rect, const PointF &grid_size, const Color &c1, const Color &c2) = 0; // Draw checker pattern

		virtual IRenderer *DrawHSVPlane(const RectF &rect, const float hue) = 0; // Draw HSV rectangle with specified Hue value

		virtual IRenderer *DrawPolygon(const std::vector<PointF> &points, const Color &color) = 0; // Draw polygon

		virtual IRenderer *DrawPolygons(const std::vector<std::vector<PointF>> &polygons, const Color &color) = 0; // Draw polygons

		virtual IRenderer *DrawGradient(const RectF &rect, nitisa::Gradient &g) = 0; // Draw gradient

		virtual IRenderer *DrawHSVGradient(const RectF &rect, nitisa::Gradient &g) = 0; // Draw gradient. Gradient point colors are in HSV color space

		virtual IRenderer *DrawImage(IBaseTexture *image, const float transparency) = 0; // Draw image
		virtual IRenderer *DrawImage(IBaseTexture *image, const float transparency, const RectF &part) = 0; // Draw image part

		virtual IRenderer *DrawBlock(const RectF &block, const RectF &border, const RectF &radius, const BlockColors &colors) = 0; // Draw block
		virtual IRenderer *DrawBlock(const RectF &block, const RectF &border, const RectF &radius, const BlockColors &colors, const RectF &rect) = 0; // Draw block part

		virtual IRenderer *DrawText(const String &text, IPlatformFont *pf, const float distance, const Color &color) = 0; // Draw text

		virtual IRenderer *BlurImage(ITexture *image, const int radius, const BlurType type) = 0; // Blur image
		virtual IRenderer *BlurImage(ITexture *source, const int radius, const BlurType type, ITexture *target) = 0; // Blur image without modifying original one

		virtual IRenderer *InversePixels(const RectF &rect) = 0; // Inverse pixels in specified rectangle on current target
	};

	// Helper function to create and register in renderer custom shader programs.
	// To function properly ProgramClass should have method declared as static ProgramClass *Create(IReleasableListener*, NativeGraphicsClass*, IRenderer*) and this function should be made a friend of ProgramClass.
	// The first argument should be set in ProgramClass constructor as release listener. It is recommended that ProgramClass be derived from IReleasable/CReleasable for this purpose.
	// The second argument will be the native graphics class used by renderer and thus should be named by NativeGraphicsClass.
	// If ProgramClass::Create() fails it should return nullptr.
	// CreateProgram() function return nullptr if "renderer" argument is missing, or renderer's native graphics isn't an instance of NativeGraphicsClass, or ProgramClass::Create() returns nullptr.
	// In case of using with custom renderers the function should be made a friend of that renderer in order to have access to its protected methods.
	template<class ProgramClass, class RendererClass, class NativeGraphicsClass>
	IProgram *CreateProgram(RendererClass *renderer)
	{
		if (renderer && cast<NativeGraphicsClass*>(renderer->NativeGraphics))
		{
			ProgramClass *result{ ProgramClass::Create(renderer->getProgramReleaseListener(), cast<NativeGraphicsClass*>(renderer->NativeGraphics), renderer) };
			if (result)
				renderer->AddProgram(result);
			return result;
		}
		return nullptr;
	}

	// Helper function to create and register in renderer custom framebuffers.
	// To function properly FramebufferClass should have method declared as static FramebufferClass *Create(IReleasableListener*, NativeGraphicsClass*, IRenderer*) and this function should be made a friend of FramebufferClass.
	// The first argument should be set in FramebufferClass constructor as release listener. It is recommended that FramebufferClass be derived from IReleasable/CReleasable for this purpose.
	// The second argument will be the native graphics class used by renderer and thus should be named by NativeGraphicsClass.
	// If FramebufferClass::Create() fails it should return nullptr.
	// CreateFramebuffer() function return nullptr if "renderer" argument is missing, or renderer's native graphics isn't an instance of NativeGraphicsClass, or FramebufferClass::Create() returns nullptr.
	// In case of using with custom renderers the function should be made a friend of that renderer in order to have access to its protected methods.
	template<class FramebufferClass, class RendererClass, class NativeGraphicsClass>
	IFramebuffer *CreateFramebuffer(RendererClass *renderer)
	{
		if (renderer && cast<NativeGraphicsClass*>(renderer->NativeGraphics))
		{
			FramebufferClass *result{ FramebufferClass::Create(renderer->getFramebufferReleaseListener(), cast<NativeGraphicsClass*>(renderer->NativeGraphics), renderer) };
			if (result)
				renderer->AddFramebuffer(result);
			return result;
		}
		return nullptr;
	}

	// Helper function to create and register in renderer custom vertex arrays.
	// To function properly VertexArrayClass should have method declared as static VertexArrayClass *Create(IReleasableListener*, NativeGraphicsClass*, IRenderer*) and this function should be made a friend of VertexArrayClass.
	// The first argument should be set in VertexArrayClass constructor as release listener. It is recommended that VertexArrayClass be derived from IReleasable/CReleasable for this purpose.
	// The second argument will be the native graphics class used by renderer and thus should be named by NativeGraphicsClass.
	// If VertexArrayClass::Create() fails it should return nullptr.
	// CreateVertexArray() function return nullptr if "renderer" argument is missing, or renderer's native graphics isn't an instance of NativeGraphicsClass, or VertexArrayClass::Create() returns nullptr.
	// In case of using with custom renderers the function should be made a friend of that renderer in order to have access to its protected methods.
	template<class VertexArrayClass, class RendererClass, class NativeGraphicsClass>
	IVertexArray *CreateVertexArray(RendererClass *renderer)
	{
		if (renderer && cast<NativeGraphicsClass*>(renderer->NativeGraphics))
		{
			VertexArrayClass *result{ VertexArrayClass::Create(renderer->getVertexArrayReleaseListener(), cast<NativeGraphicsClass*>(renderer->NativeGraphics), renderer) };
			if (result)
				renderer->AddVertexArray(result);
			return result;
		}
		return nullptr;
	}

	// Helper function to create and register in renderer custom textures.
	// To function properly TextureClass should have method declared as static TextureClass *Create(IReleasableListener*, NativeGraphicsClass*, IRenderer*, bool) and this function should be made a friend of TextureClass.
	// The first argument should be set in TextureClass constructor as release listener. It is recommended that TextureClass be derived from IReleasable/CReleasable for this purpose.
	// The second argument will be the native graphics class used by renderer and thus should be named by NativeGraphicsClass.
	// If TextureClass::Create() fails it should return nullptr.
	// CreateTexture() function return nullptr if "renderer" argument is missing, or renderer's native graphics isn't an instance of NativeGraphicsClass, or TextureClass::Create() returns nullptr.
	// In case of using with custom renderers the function should be made a friend of that renderer in order to have access to its protected methods.
	template<class TextureClass, class RendererClass, class NativeGraphicsClass>
	ITexture *CreateTexture(RendererClass *renderer, const bool precomputed)
	{
		if (renderer && cast<NativeGraphicsClass*>(renderer->NativeGraphics))
		{
			TextureClass *result{ TextureClass::Create(renderer->getTextureReleaseListener(), cast<NativeGraphicsClass*>(renderer->NativeGraphics), renderer, precomputed) };
			if (result)
				renderer->AddTexture(result);
			return result;
		}
		return nullptr;
	}

	// Helper function to create and register in renderer custom multi-sample textures.
	// To function properly TextureClass should have method declared as static TextureClass *Create(IReleasableListener*, NativeGraphicsClass*, IRenderer*) and this function should be made a friend of TextureClass.
	// The first argument should be set in TextureClass constructor as release listener. It is recommended that TextureClass be derived from IReleasable/CReleasable for this purpose.
	// The second argument will be the native graphics class used by renderer and thus should be named by NativeGraphicsClass.
	// If TextureClass::Create() fails it should return nullptr.
	// CreateTextureMultisample() function return nullptr if "renderer" argument is missing, or renderer's native graphics isn't an instance of NativeGraphicsClass, or TextureClass::Create() returns nullptr.
	// In case of using with custom renderers the function should be made a friend of that renderer in order to have access to its protected methods.
	template<class TextureClass, class RendererClass, class NativeGraphicsClass>
	ITextureMultisample *CreateTextureMultisample(RendererClass *renderer)
	{
		if (renderer && cast<NativeGraphicsClass*>(renderer->NativeGraphics))
		{
			TextureClass *result{ TextureClass::Create(renderer->getTextureMultisampleReleaseListener(), cast<NativeGraphicsClass*>(renderer->NativeGraphics), renderer) };
			if (result)
				renderer->AddTextureMultisample(result);
			return result;
		}
		return nullptr;
	}
}