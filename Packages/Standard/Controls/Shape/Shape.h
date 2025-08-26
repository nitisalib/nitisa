// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Math/Point.h"
#include "../IShape.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CShapeService;

		// Not all combinations of layout properties works. For example, border mask is not used togather with circle, ellipse, and rounded square and rectangle.
		class CShape :public virtual IShape, public CControl
		{
			friend CShapeService;
		public:
			enum class ShapeType // Shape types
			{
				Circle, // Circle(doesn't have border mask)
				Ellipse, // Ellipse(doesn't have border)
				Rectangle, // Rectangle
				Square, // Square
				RoundRectangle, // Rectangle with round corners(doesn't have border mask)
				RoundSquare, // Square with round corners(doesn't have border mask)
				Triangle // Triangle(border width with only 0 and 1 values are accepted)
			};
		private:
			ShapeType m_eShapeType;
			float m_fBorderWidth;
			float m_fBorderRadius;
			Color m_sBorderColor;
			Color m_sBackgroundColor;
			unsigned int m_iBorderMask;

			ITexture *m_pCanvas;

			void UpdateFromStyle(IStyle *style);
			void Render();
			void RenderCircle(IRenderer *renderer);
			void RenderEllipse(IRenderer *renderer);
			void RenderRectangle(IRenderer *renderer);
			void RenderSquare(IRenderer *renderer);
			void RenderRoundRectangle(IRenderer *renderer);
			void RenderRoundSquare(IRenderer *renderer);
			void RenderTriangle(IRenderer *renderer);
		public:
			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			CShape(); // Create
			CShape(IForm *parent); // Create and place on a form
			CShape(IControl *parent); // Create and place on another control

			// Getters
			ShapeType getShapeType() const; // Return shape type
			float getBorderWidth() const; // Return border width
			float getBorderRadius() const; // Return corner radius. Used in rounded rectangle and square
			Color getBorderColor() const; // Return border color
			Color getBackgroundColor() const; // Return background color
			unsigned int getBorderMask() const; // Return border mask

			// Setters
			bool setShapeType(const ShapeType value); // Set shape type
			bool setBorderWidth(const float value); // Set border width
			bool setBorderRadius(const float value); // Set corner radius. Used in rounded rectangle and square
			bool setBorderColor(const Color &value); // Set border color
			bool setBackgroundColor(const Color &value); // Set background color
			bool setBorderMask(const unsigned int value); // Set border mask
		};
	}
}