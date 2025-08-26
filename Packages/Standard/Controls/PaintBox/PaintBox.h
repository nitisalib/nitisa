// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/BlurType.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Image/BlockColors.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/ITexture.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IPaintBox.h"
#include <vector>

namespace nitisa
{
	class IBaseTexture;
	class IControl;
	class IForm;
	class IPlatformFont;

	namespace standard
	{
		class CPaintBoxService;

		class CPaintBox :public virtual IPaintBox, public CControl
		{
			friend CPaintBoxService;
		private:
			ITexture * m_pCanvas;
			IBaseTexture *m_pOldActiveTarget;
			bool m_bDrawing;
			nitisa::Gradient m_cGradient;
			bool m_bOutlineInEditor;

			bool PrepareCanvas();
			void Render();
		public:
			// IControl methods
			void Refresh(const bool refresh_children) override;

			ITexture::IData *Lock(const bool readonly) override;
			bool DrawBegin() override;
			bool DrawEnd() override;

			void Clear(const Color &color) override;

			void Line(const PointF &p1, const PointF &p2, const Color &color) override;
			void Line(const PointF &p1, const PointF &p2, const Color &color, const Mat4f &m) override;
			void Line(const PointF &p1, const PointF &p2, const Color &c1, const Color &c2) override;
			void Line(const PointF &p1, const PointF &p2, const Color &c1, const Color &c2, const Mat4f &m) override;
			void Line(const PointF &p1, const PointF &p2, const Color &color, const unsigned int bitmask) override;
			void Line(const PointF &p1, const PointF &p2, const Color &color, const Mat4f &m, const unsigned int bitmask) override;
			void Line(const PointF &p1, const PointF &p2, const Color &c1, const Color &c2, const unsigned int bitmask) override;
			void Line(const PointF &p1, const PointF &p2, const Color &c1, const Color &c2, const Mat4f &m, const unsigned int bitmask) override;

			void Lines(const std::vector<PointF> &points, const Color &color, const bool loop) override;
			void Lines(const std::vector<PointF> &points, const Color &color, const bool loop, const Mat4f &m) override;
			void Lines(const std::vector<PointF> &points, const Color &color, const bool loop, const unsigned int bitmask) override;
			void Lines(const std::vector<PointF> &points, const Color &color, const bool loop, const Mat4f &m, const unsigned int bitmask) override;

			void Triangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &color) override;
			void Triangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &color, const Mat4f &m) override;
			void Triangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &c1, const Color &c2, const Color &c3) override;
			void Triangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &c1, const Color &c2, const Color &c3, const Mat4f &m) override;
			void Triangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &color, const unsigned int bitmask_x, const unsigned int bitmask_y) override;
			void Triangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &color, const Mat4f &m, const unsigned int bitmask_x, const unsigned int bitmask_y) override;
			void Triangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &c1, const Color &c2, const Color &c3, const unsigned int bitmask_x, const unsigned int bitmask_y) override;
			void Triangle(const PointF &p1, const PointF &p2, const PointF &p3, const Color &c1, const Color &c2, const Color &c3, const Mat4f &m, const unsigned int bitmask_x, const unsigned int bitmask_y) override;

			void Rectangle(const RectF &rect, const Color &color) override;
			void Rectangle(const RectF &rect, const Color &color, const Mat4f &m) override;
			void Rectangle(const RectF &rect, const Color &c1, const Color &c2, const Color &c3, const Color &c4) override;
			void Rectangle(const RectF &rect, const Color &c1, const Color &c2, const Color &c3, const Color &c4, const Mat4f &m) override;
			void Rectangle(const RectF &rect, const Color &color, const unsigned int bitmask_x, const unsigned int bitmask_y) override;
			void Rectangle(const RectF &rect, const Color &color, const Mat4f &m, const unsigned int bitmask_x, const unsigned int bitmask_y) override;
			void Rectangle(const RectF &rect, const Color &c1, const Color &c2, const Color &c3, const Color &c4, const unsigned int bitmask_x, const unsigned int bitmask_y) override;
			void Rectangle(const RectF &rect, const Color &c1, const Color &c2, const Color &c3, const Color &c4, const Mat4f &m, const unsigned int bitmask_x, const unsigned int bitmask_y) override;

			void Gradient(const RectF &rect, nitisa::Gradient &g) override;
			void Gradient(const RectF &rect, nitisa::Gradient &g, const Mat4f &m) override;
			void Gradient(const RectF &rect, nitisa::Gradient &g, const unsigned int bitmask_x, const unsigned int bitmask_y) override;
			void Gradient(const RectF &rect, nitisa::Gradient &g, const Mat4f &m, const unsigned int bitmask_x, const unsigned int bitmask_y) override;

			void Image(ITexture *image, const PointF &p, const float transparency) override;
			void Image(ITexture *image, const Mat4f &m, const float transparency) override;
			void Image(ITexture *image, const RectF &part, const PointF &p, const float transparency) override;
			void Image(ITexture *image, const RectF &part, const Mat4f &m, const float transparency) override;
			void Image(ITexture *image, const PointF &p, const float transparency, const unsigned int bitmask_x, const unsigned int bitmask_y) override;
			void Image(ITexture *image, const Mat4f &m, const float transparency, const unsigned int bitmask_x, const unsigned int bitmask_y) override;
			void Image(ITexture *image, const RectF &part, const PointF &p, const float transparency, const unsigned int bitmask_x, const unsigned int bitmask_y) override;
			void Image(ITexture *image, const RectF &part, const Mat4f &m, const float transparency, const unsigned int bitmask_x, const unsigned int bitmask_y) override;

			void Block(const RectF &block, const RectF &border, const RectF &radius, const BlockColors &colors) override;
			void Block(const RectF &rect, const RectF &block, const RectF &border, const RectF &radius, const BlockColors &colors) override;
			void Block(const RectF &block, const RectF &border, const RectF &radius, const BlockColors &colors, const unsigned int bitmask_x, const unsigned int bitmask_y) override;
			void Block(const RectF &rect, const RectF &block, const RectF &border, const RectF &radius, const BlockColors &colors, const unsigned int bitmask_x, const unsigned int bitmask_y) override;

			void Text(const String &text, IPlatformFont *font, const float distance, const Color &color, const PointF &p) override;
			void Text(const String &text, IPlatformFont *font, const float distance, const Color &color, const Mat4f &m) override;
			void Text(const String &text, IPlatformFont *font, const float distance, const Color &color, const PointF &p, const unsigned int bitmask_x, const unsigned int bitmask_y) override;
			void Text(const String &text, IPlatformFont *font, const float distance, const Color &color, const Mat4f &m, const unsigned int bitmask_x, const unsigned int bitmask_y) override;

			void Blur(const int radius, const BlurType type) override;
			void Blur(const int radius, const BlurType type, const unsigned int bitmask_x, const unsigned int bitmask_y) override;

			void Dot(const PointF &p, const Color &color) override;
			void Dot(const PointF &p, const Color &color, const Mat4f &m) override;

			void Circle(const PointF &p, const Color &color, const float radius) override;
			void Circle(const PointF &p, const Color &color, const float radius, const Mat4f &m) override;
			void Circle(const PointF &p, const Color &color, const float radius, const unsigned int bitmask_x, const unsigned int bitmask_y) override;
			void Circle(const PointF &p, const Color &color, const float radius, const Mat4f &m, const unsigned int bitmask_x, const unsigned int bitmask_y) override;

			CPaintBox();
			CPaintBox(IForm *parent);
			CPaintBox(IControl *parent);

			ITexture *getCanvas();
			bool isOutlineInEditor() const; // Return whether the widget should be outlined in the Form Builder

			bool setOutlineInEditor(const bool value); // Set whether the widget should be outlined in the Form Builder
		};
	}
}