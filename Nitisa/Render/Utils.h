// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Utils.h"
#include "../Core/Strings.h"
#include "../Core/TextureFormat.h"
#include "../Image/BorderColor.h"
#include "../Image/Color.h"
#include "../Image/Gradient.h"
#include "../Interfaces/IRenderer.h"
#include "../Interfaces/ITexture.h"
#include "../Math/Mat4f.h"
#include "../Math/PointF.h"
#include "../Math/RectF.h"
#include "StorePrimitiveMatrix.h"
#include <utility>
#include <vector>

namespace nitisa
{
	class IPlatformFont;
	class IControlService;

	bool DrawBlockShadow( // Draw block shadow
		IRenderer *renderer, // Renderer
		const RectF &rect, // Block rectangle in control's coordinates
		const RectF &radiuses, // Block border radiuses
		const Color &color, // Shadow color
		const PointF &shift, // Shadow shift
		const int radius); // Shadow radius

	bool DrawSimpleBackground( // Draw background(may have borders, background color, background gradient)
		IRenderer *renderer, // Renderer
		const RectF &rect, // Block rectangle in control's coordinates
		const RectF &borders, // Block border widthes
		const RectF &radiuses, // Block border radiuses
		const BorderColor &border_colors, // Block border colors
		const Color &background_color, // Background color
		Gradient &background_gradient); // Background gradient

	bool DrawDoubleBackground( // Draw background with 2 borders(inner and outer)(may have outer borders, inner borders, background color, background gradient)
		IRenderer *renderer, // Renderer
		const RectF &rect, // Block rectangle in control's coordinates
		const RectF &outer_borders, // Block outer border widthes
		const RectF &inner_borders, // Block inner border widthes
		const RectF &radiuses, // Block border radiuses
		const BorderColor &outer_border_colors, // Block outer border colors
		const BorderColor &inner_border_colors, // Block inner border colors
		const Color &background_color, // Background color
		Gradient &background_gradient); // Background gradient

	bool DrawTripleBackground( // Draw background with 3 borders(inner, middle and outer)(may have outer borders, middle borders, inner borders, background color, background gradient)
		IRenderer *renderer, // Renderer
		const RectF &rect, // Block rectangle in control's coordinates
		const RectF &outer_borders, // Block outer border widthes
		const RectF &middle_borders, // Block middle border widthes
		const RectF &inner_borders, // Block inner border widthes
		const RectF &radiuses, // Block border radiuses
		const BorderColor &outer_border_colors, // Block outer border colors
		const BorderColor &middle_border_colors, // Block middle border colors
		const BorderColor &inner_border_colors, // Block inner border colors
		const Color &background_color, // Background color
		Gradient &background_gradient); // Background gradient

	bool DrawTripleSharpBackground( // Draw background with 3 borders and inner border has no round corners(inner, middle and outer)(may have outer borders, middle borders, inner borders, background color, background gradient)
		IRenderer *renderer, // Renderer
		const RectF &rect, // Block rectangle in control's coordinates
		const RectF &outer_borders, // Block outer border widthes
		const RectF &middle_borders, // Block middle border widthes
		const RectF &inner_borders, // Block inner border widthes
		const RectF &radiuses, // Block outer border radiuses
		const BorderColor &outer_border_colors, // Block outer border colors
		const BorderColor &middle_border_colors, // Block middle border colors
		const BorderColor &inner_border_colors, // Block inner border colors
		const Color &background_color, // Background color
		Gradient &background_gradient); // Background gradient

	bool DrawTextShadow( // Draw text shadow using optimal size shadow texture. Before calling, provide clipping using mask(if required)
		IRenderer *renderer, // Renderer
		IPlatformFont *pf, // Platform font used to draw text
		const float distance, // Additional distance between text characters
		const Mat4f &matrix, // Control transformation matrix
		const RectF &client, // Client area of control where shadow should be drawn(if client area has not rectangular form use mask
		const PointF &position, // Text position in control coordinates
		const String &text, // Text
		const Color &color, // Shadow color
		const PointF &shift, // Shadow shift
		const int radius); // Shadow radius

	bool DrawFrame(
		IRenderer *renderer, // Renderer
		const RectF &rect, // Frame rectangle
		const RectF &outer_borders, // Outer border widthes
		const RectF &middle_borders, // Middle border widthes
		const RectF &inner_borders, // Innner border widthes
		const RectF &radiuses, // Outer border radiuses
		const BorderColor &outer_border_colors, // Outer border colors
		const BorderColor &middle_border_colors, // Middle border colors
		const BorderColor &inner_border_colors, // Inner border colors
		Gradient &middle_gradient, // Gradient used to draw middle borders
		const Color &background_color, // Background color
		Gradient &background_gradient); // Background gradient

	bool DrawBezierCurve( // Draw cubic bezier curve of specified width
		IRenderer *renderer, // Renderer
		const PointF &p1, // First point
		const PointF &p2, // Second point
		const PointF &cp1, // First control point
		const PointF &cp2, // Second control point
		const Color &color, // Curve color
		const float width, // Curve width
		const float dT = -1); // Custom step value. Set negative to use calculated optimal one

	RectF AddShadow(const RectF &rect, const Color &color, const PointF &shiftF, const int radius); // Extend rect with shadow if shadow exists(color alpha > 0)
	PointF DispOnCanvas(const Color &shadow_color, const PointF &shadow_shift, const int shadow_radius); // Return control position on canvas with control and shadow
	void Bezier(const PointF &prev, const PointF &point, const PointF &next, const float tension, PointF &cp_prev, PointF &cp_next); // Calculate prev and next control point

	// First and second points of curve are not being added to point list by this function. They should be added before and after it call by caller if those points are needed. This allows
	// to build continuous point list for several connected curves
	void BezierSubdivide( // Build list of points for cubic bezier spline so it can be used to draw smooth spline
		const PointF &p1, // First point of curve
		const PointF &c2, // First control point of curve
		const PointF &c3, // Second control point of curve
		const PointF &p4, // Second point of curve
		std::vector<PointF> &points, // Points storage where new points will be added. It is not being cleared during this function call
		const int curve_recursion_limit = 16, // Maximum subdivision depth
		const float distance_tolerance = 0.5f, // Square of maximum allowed visual distance error(for example, if maximum allowed error is 0.5px, then this value should be 0.5 * 0.5 = 0.25)
		const float angle_tolerance = ntl::DegToRad<float>(1.0f), // Angle tolerance in radians
		const float cusp_limit = ntl::DegToRad<float>(1.0f), // Cusp tolerance in radians
		const float curve_angle_tolerance = ntl::DegToRad<float>(1.0f), // Curve angle tolerance in radians
		const float curve_collinearity_tolerance = 1); // Collinearity tolerance

	bool MakeThickPath( // Calculate points required to draw thick path
		const std::vector<PointF> &path, // Path points. Should have at least 2 points
		const bool loop, // Whether the path should be closed one(last point is connected to first one). Can only be used when path has 3 and more points
		const float width, // Path width. If middle is false the positive and negative width can be specified, When positive, the path will be thickened outward(in direction of normal). When negative it will be thickened inward(in direction opposite to normal)
		const bool middle, // Whether the path will be thickened equally in both direction(inward and outward) by half width
		std::vector<std::pair<PointF, PointF>> &points); // Resulting points which can be used to draw polygons. The polygon can be constructed using as { points[i][0], points[i + 1][0], points[i + 1][1], points[i][1] }. This argument will have the same size as path array

	inline bool PrepareCanvas(IRenderer *renderer, ITexture **canvas, const int width, const int height) // Return true if rendering is required
	{
		if (*canvas)
		{
			if (!(*canvas)->isValid())
			{
				(*canvas)->setSize(width, height);
				return true;
			}
		}
		else
		{
			if ((*canvas = renderer->CreateTexture(width, height, 1, TextureFormat::RGBA, true)))
				return true;
		}
		return false;
	}

	inline bool PrepareCanvas(IRenderer *renderer, ITexture **canvas, const float width, const float height) // Return true if rendering is required. Canvas size will be rounded
	{
		if (*canvas)
		{
			if (!(*canvas)->isValid())
			{
				(*canvas)->setSize(ntl::Round<int>(width), ntl::Round<int>(height));
				return true;
			}
		}
		else
		{
			if ((*canvas = renderer->CreateTexture(ntl::Round<int>(width), ntl::Round<int>(height), 1, TextureFormat::RGBA, true)))
				return true;
		}
		return false;
	}

	inline bool PrepareCanvas(IRenderer *renderer, ITexture **canvas, const PointF &size) // Return true if rendering is required. Canvas size will be rounded
	{
		if (*canvas)
		{
			if (!(*canvas)->isValid())
			{
				(*canvas)->setSize(ntl::Round<int>(size.X), ntl::Round<int>(size.Y));
				return true;
			}
		}
		else
		{
			if ((*canvas = renderer->CreateTexture(ntl::Round<int>(size.X), ntl::Round<int>(size.Y), 1, TextureFormat::RGBA, true)))
				return true;
		}
		return false;
	}

	inline bool PrepareCanvas(IRenderer *renderer, ITexture **canvas, const RectF &rect) // Return true if rendering is required. Canvas size, which is the size of the rect, will be rounded
	{
		if (*canvas)
		{
			if (!(*canvas)->isValid())
			{
				(*canvas)->setSize(ntl::Round<int>(rect.width()), ntl::Round<int>(rect.height()));
				return true;
			}
		}
		else
		{
			if ((*canvas = renderer->CreateTexture(ntl::Round<int>(rect.width()), ntl::Round<int>(rect.height()), 1, TextureFormat::RGBA, true)))
				return true;
		}
		return false;
	}

	inline bool DrawCanvas(IRenderer *renderer, const Mat4f &matrix, ITexture *canvas, const PointF &disp)
	{
		if (canvas)
		{
			CStorePrimitiveMatrix s_matrix{ renderer };
			renderer
				->ActivatePrimitiveMatrix(matrix * ntl::Mat4Translate<float>(-disp.X, -disp.Y, 0))
				->DrawImage(canvas, 1);
			return true;
		}
		return false;
	}
}