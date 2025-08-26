// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/BlurType.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BlockColors.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IControl.h"
#include "Nitisa/Interfaces/ITexture.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include <vector>

namespace nitisa
{
	class IPlatformFont;

	namespace standard
	{
		// Draw onto associated texture.
		// All drawing methods works only if control is placed onto a form(directly or via parent controls) with valid renderer and if called inside renderer's DrawBegin() and DrawEnd() block.
		class IPaintBox :public virtual IControl
		{
		protected:
			IPaintBox() = default;
			~IPaintBox() = default;
			IPaintBox(const IPaintBox &other) = delete;
			IPaintBox(IPaintBox &&other) = delete;
			IPaintBox &operator=(const IPaintBox &other) = delete;
			IPaintBox &operator=(IPaintBox &&other) = delete;
		public:
			void(*OnDraw)(IPaintBox *sender); // Event called when drawing is required

			virtual ITexture::IData *Lock(const bool readonly) = 0; // Return texture data if succeeded, nullptr otherwise. Use ITexture::IData::Release() to release locking and apply changes if lock was not read only
			virtual bool DrawBegin() = 0; // Start drawing. If you are going to call drawing methods several times to draw you picture, it is better to do it between calling of DrawBegin() and DrawEnd() methods. It will work faster
			virtual bool DrawEnd() = 0; // Finish drawing

			virtual void Clear( // Clear entire control area with specified color
				const Color &color) = 0; // Color

			virtual void Line( // Draw line
				const PointF &p1, // Start point
				const PointF &p2, // End point
				const Color &color) = 0; // Color
			virtual void Line( // Draw line with transformation
				const PointF &p1, // Start point
				const PointF &p2, // End point
				const Color &color, // Color
				const Mat4f &m) = 0; // Transformation matrix
			virtual void Line( // Draw line with gradiental filling
				const PointF &p1, // Start point
				const PointF &p2, // End point
				const Color &c1, // Start point color
				const Color &c2) = 0; // End point color
			virtual void Line( // Draw line with gradiental filling and transformation
				const PointF &p1, // Start point
				const PointF &p2, // End point
				const Color &c1, // Start point color
				const Color &c2, // End point color
				const Mat4f &m) = 0; // Transformation matrix
			virtual void Line( // Draw masked line
				const PointF &p1, // Start point
				const PointF &p2, // End point
				const Color &color, // Color
				const unsigned int bitmask) = 0; // 32-bit binary mask where 1 - draw, 0 - not draw. Calculated starting from start point. Uses distance from p1 to calculate current bit
			virtual void Line( // Draw masked line with transformation
				const PointF &p1, // Start point
				const PointF &p2, // End point
				const Color &color, // Color
				const Mat4f &m, // Transformation matrix
				const unsigned int bitmask) = 0; // 32-bit binary mask where 1 - draw, 0 - not draw. Calculated starting from start point. Uses distance from p1 to calculate current bit
			virtual void Line( // Draw masked line with gradiental filling
				const PointF &p1, // Start point
				const PointF &p2, // End point
				const Color &c1, // Start point color
				const Color &c2, // End point color
				const unsigned int bitmask) = 0; // 32-bit binary mask where 1 - draw, 0 - not draw. Calculated starting from start point. Uses distance from p1 to calculate current bit
			virtual void Line( // Draw masked line with gradiental filling and transformation
				const PointF &p1, // Start point
				const PointF &p2, // End point
				const Color &c1, // Start point color
				const Color &c2, // End point color
				const Mat4f &m, // Transformation matrix
				const unsigned int bitmask) = 0; // 32-bit binary mask where 1 - draw, 0 - not draw. Calculated starting from start point. Uses distance from p1 to calculate current bit

			virtual void Lines( // Draw lines
				const std::vector<PointF> &points, // Line points
				const Color &color, // Color of all lines
				const bool loop) = 0; // Whether to draw line from last to first one(close the shape)
			virtual void Lines( // Draw lines with transformation
				const std::vector<PointF> &points, // Line points
				const Color &color, // Color of all lines
				const bool loop, // Whether to draw line from last to first one(close the shape)
				const Mat4f &m) = 0; // Transformation matrix
			virtual void Lines( // Draw masked lines
				const std::vector<PointF> &points, // Line points
				const Color &color, // Color of all lines
				const bool loop, // Whether to draw line from last to first one(close the shape)
				const unsigned int bitmask) = 0; // 32-bit binary mask where 1 - draw, 0 - not draw. Calculated starting from first point. Uses distance from first point to calculate current bit
			virtual void Lines( // Draw masked lines with transformation
				const std::vector<PointF> &points, // Line points
				const Color &color, // Color of all lines
				const bool loop, // Whether to draw line from last to first one(close the shape)
				const Mat4f &m, // Transformation matrix
				const unsigned int bitmask) = 0; // 32-bit binary mask where 1 - draw, 0 - not draw. Calculated starting from first point. Uses distance from first point to calculate current bit

			virtual void Triangle( // Draw solid triangle
				const PointF &p1, // 1st vertex
				const PointF &p2, // 2nd vertex
				const PointF &p3, // 3rd vertex
				const Color &color) = 0; // Triangle color
			virtual void Triangle( // Draw solid triangle with transformation
				const PointF &p1, // 1st vertex
				const PointF &p2, // 2nd vertex
				const PointF &p3, // 3rd vertex
				const Color &color, // Triangle color
				const Mat4f &m) = 0; // Transformation matrix
			virtual void Triangle( // Draw gradientally filled triangle
				const PointF &p1, // 1st vertex
				const PointF &p2, // 2nd vertex
				const PointF &p3, // 3rd vertex
				const Color &c1, // 1st vertex color
				const Color &c2, // 2nd vertex color
				const Color &c3) = 0; // 3rd vertex color
			virtual void Triangle( // Draw gradientally filled triangle with transformation
				const PointF &p1, // 1st vertex
				const PointF &p2, // 2nd vertex
				const PointF &p3, // 3rd vertex
				const Color &c1, // 1st vertex color
				const Color &c2, // 2nd vertex color
				const Color &c3, // 3rd vertex color
				const Mat4f &m) = 0; // Transformation matrix
			virtual void Triangle( // Draw masked solid triangle
				const PointF &p1, // 1st vertex
				const PointF &p2, // 2nd vertex
				const PointF &p3, // 3rd vertex
				const Color &color, // Triangle color
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw
			virtual void Triangle( // Draw masked solid triangle with transformation
				const PointF &p1, // 1st vertex
				const PointF &p2, // 2nd vertex
				const PointF &p3, // 3rd vertex
				const Color &color, // Triangle color
				const Mat4f &m, // Transformation matrix
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw
			virtual void Triangle( // Draw masked gradientally filled triangle
				const PointF &p1, // 1st vertex
				const PointF &p2, // 2nd vertex
				const PointF &p3, // 3rd vertex
				const Color &c1, // 1st vertex color
				const Color &c2, // 2nd vertex color
				const Color &c3, // 3rd vertex color
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw
			virtual void Triangle( // Draw masked gradientally filled triangle with transformation
				const PointF &p1, // 1st vertex
				const PointF &p2, // 2nd vertex
				const PointF &p3, // 3rd vertex
				const Color &c1, // 1st vertex color
				const Color &c2, // 2nd vertex color
				const Color &c3, // 3rd vertex color
				const Mat4f &m, // Transformation matrix
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw

			virtual void Rectangle( // Draw solid rectangle
				const RectF &rect, // Rectangle
				const Color &color) = 0; // Rectangle color
			virtual void Rectangle( // Draw solid rectangle with transformation
				const RectF &rect, // Rectangle
				const Color &color, // Rectangle color
				const Mat4f &m) = 0; // Transformation matrix
			virtual void Rectangle( // Draw gradientally filled rectangle
				const RectF &rect, // Rectangle
				const Color &c1, // Left-top vertex color
				const Color &c2, // Right-top vertex color
				const Color &c3, // Right-bottom vertex color
				const Color &c4) = 0; // Left-bottom vertex color
			virtual void Rectangle( // Draw gradientally filled rectangle with transformation
				const RectF &rect, // Rectangle
				const Color &c1, // Left-top vertex color
				const Color &c2, // Right-top vertex color
				const Color &c3, // Right-bottom vertex color
				const Color &c4, // Left-bottom vertex color
				const Mat4f &m) = 0; // Transformation matrix
			virtual void Rectangle( // Draw masked solid rectangle
				const RectF &rect, // Rectangle
				const Color &color, // Rectangle color
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw
			virtual void Rectangle( // Draw masked solid rectangle with transformation
				const RectF &rect, // Rectangle
				const Color &color, // Rectangle color
				const Mat4f &m, // Transformation matrix
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw
			virtual void Rectangle( // Draw masked gradientally filled rectangle
				const RectF &rect, // Rectangle
				const Color &c1, // Left-top vertex color
				const Color &c2, // Right-top vertex color
				const Color &c3, // Right-bottom vertex color
				const Color &c4, // Left-bottom vertex color
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw
			virtual void Rectangle( // Draw masked gradientally filled rectangle with transformation
				const RectF &rect, // Rectangle
				const Color &c1, // Left-top vertex color
				const Color &c2, // Right-top vertex color
				const Color &c3, // Right-bottom vertex color
				const Color &c4, // Left-bottom vertex color
				const Mat4f &m, // Transformation matrix
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw

			virtual void Gradient( // Draw gradient
				const RectF &rect, // Rectangle
				nitisa::Gradient &g) = 0; // Gradient
			virtual void Gradient( // Draw gradient with transformation
				const RectF &rect, // Rectangle
				nitisa::Gradient &g, // Gradient
				const Mat4f &m) = 0; // Transformation matrix
			virtual void Gradient( // Draw masked gradient
				const RectF &rect, // Rectangle
				nitisa::Gradient &g, // Gradient
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw
			virtual void Gradient( // Draw masked gradient with transformation
				const RectF &rect, // Rectangle
				nitisa::Gradient &g, // Gradient
				const Mat4f &m, // Transformation matrix
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw

			virtual void Image( // Draw image at specified position
				ITexture *image, // Image
				const PointF &p, // Position where to draw
				const float transparency) = 0; // Transparency(0..1)
			virtual void Image( // Draw image with transformation
				ITexture *image, // Image
				const Mat4f &m, // Transformation matrix
				const float transparency) = 0; // Transparency(0..1)
			virtual void Image( // Draw image part at specified position
				ITexture *image, // Image
				const RectF &part, // Part to be drawn
				const PointF &p, // Position where to draw
				const float transparency) = 0; // Transparency(0..1)
			virtual void Image( // Draw image part with transformation
				ITexture *image, // Image
				const RectF &part, // Part to be drawn
				const Mat4f &m, // Transformation matrix
				const float transparency) = 0; // Transparency(0..1)
			virtual void Image( // Draw masked image at specified position
				ITexture *image, // Image
				const PointF &p, // Position where to draw
				const float transparency, // Transparency(0..1)
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw
			virtual void Image( // Draw masked image with transformation
				ITexture *image, // Image
				const Mat4f &m, // Transformation matrix
				const float transparency, // Transparency(0..1)
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw
			virtual void Image( // Draw masked image part at specified position
				ITexture *image, // Image
				const RectF &part, // Part to be drawn
				const PointF &p, // Position where to draw
				const float transparency, // Transparency(0..1)
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw
			virtual void Image( // Draw masked image part with transformation
				ITexture *image, // Image
				const RectF &part, // Part to be drawn
				const Mat4f &m, // Transformation matrix
				const float transparency, // Transparency(0..1)
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw

			virtual void Block( // Draw block
				const RectF &block, // Block rectangle
				const RectF &border, // Border widths
				const RectF &radius, // Corner radii
				const BlockColors &colors) = 0; // Part colors(left border, top border, right border, bottom border, internal area, external area)
			virtual void Block( // Draw block part visible through specified rectangle
				const RectF &rect, // Rectangle to be drawn
				const RectF &block, // Block rectangle
				const RectF &border, // Border widths
				const RectF &radius, // Corner radii
				const BlockColors &colors) = 0; // Part colors(left border, top border, right border, bottom border, internal area, external area)
			virtual void Block( // Draw masked block
				const RectF &block, // Block rectangle
				const RectF &border, // Border widths
				const RectF &radius, // Corner radii
				const BlockColors &colors, // Part colors(left border, top border, right border, bottom border, internal area, external area)
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw
			virtual void Block( // Draw masked block part visible through specified rectangle
				const RectF &rect, // Rectangle to be drawn
				const RectF &block, // Block rectangle
				const RectF &border, // Border widths
				const RectF &radius, // Corner radii
				const BlockColors &colors, // Part colors(left border, top border, right border, bottom border, internal area, external area)
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw
				
			virtual void Text( // Draw text at specified position
				const String &text, // Text
				IPlatformFont *font, // Font. If empty, control font will be used
				const float distance, // Additional distance between characters
				const Color &color, // Color
				const PointF &p) = 0; // Position
			virtual void Text( // Draw text with transformation
				const String &text, // Text
				IPlatformFont *font, // Font. If empty, control font will be used
				const float distance, // Additional distance between characters
				const Color &color, // Color
				const Mat4f &m) = 0; // Transformation matrix
			virtual void Text( // Draw masked text at specified position
				const String &text, // Text
				IPlatformFont *font, // Font. If empty, control font will be used
				const float distance, // Additional distance between characters
				const Color &color, // Color
				const PointF &p, // Position
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw
			virtual void Text( // Draw masked text with transformation
				const String &text, // Text
				IPlatformFont *font, // Font. If empty, control font will be used
				const float distance, // Additional distance between characters
				const Color &color, // Color
				const Mat4f &m, // Transformation matrix
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw

			virtual void Blur( // Add blur to image
				const int radius, // Blur radius(>= 1)
				const BlurType type) = 0; // Blur type
			virtual void Blur( // Add masked blur to image
				const int radius, // Blur radius(>= 1)
				const BlurType type, // Blur type
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw

			virtual void Dot( // Draw dot
				const PointF &p, // Position
				const Color &color) = 0; // Color
			virtual void Dot( // Draw dot with transformation
				const PointF &p, // Position
				const Color &color, // Color
				const Mat4f &m) = 0; // Transformation matrix

			virtual void Circle( // Draw circle
				const PointF &p, // Circle center
				const Color &color, // Color
				const float radius) = 0; // Radius
			virtual void Circle( // Draw circle with transformation
				const PointF &p, // Circle center
				const Color &color, // Color
				const float radius, // Radius
				const Mat4f &m) = 0; // Transformation matrix
			virtual void Circle( // Draw masked circle
				const PointF &p, // Circle center
				const Color &color, // Color
				const float radius, // Radius
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw
			virtual void Circle( // Draw masked circle with transformation
				const PointF &p, // Circle center
				const Color &color, // Color
				const float radius, // Radius
				const Mat4f &m, // Transformation matrix
				const unsigned int bitmask_x, // 32-bit binary mask for X direction where 1 - draw, 0 - not draw
				const unsigned int bitmask_y) = 0; // 32-bit binary mask for Y direction where 1 - draw, 0 - not draw
		};
	}
}