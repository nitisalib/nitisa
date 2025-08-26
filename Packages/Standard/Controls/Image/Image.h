// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Image/Image.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IImage.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CImageService;

		class CImage :public virtual IImage, public CControl
		{
			friend CImageService;
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CImage *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CImage *control);
			};
		private:
			CGradientListener m_cGradientListener;
			Image m_cImage;
			RectF m_sBorderWidth;
			RectF m_sBorderRadius;
			BorderColor m_sBorderColor;
			Color m_sBackgroundColor;
			Gradient m_cBackgroundGradient;
			Color m_sShadowColor;
			PointF m_sShadowShift;
			int m_iShadowRadius;
			Mat4f m_sImageTransform;
			float m_fOpacity;

			ITexture *m_pImage;
			bool m_bIgnoreGradient;
			ITexture *m_pCanvas;

			void UpdateFromStyle(IStyle *style);
			void Render();
		public:
			RectF getClientRect() override;
			RectF getRenderRect() override;
			Image *getImage() override; // If you modify image data, call Update() after it

			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			void Assign(const Image &data) override;
			bool Assign(ITexture *texture) override;
			void Update() override;

			CImage();
			CImage(IForm *parent);
			CImage(IControl *parent);

			// Return layout properties
			RectF getBorderWidth() const;
			RectF getBorderRadius() const;
			BorderColor getBorderColor() const;
			Color getLeftBorderColor() const;
			Color getTopBorderColor() const;
			Color getRightBorderColor() const;
			Color getBottomBorderColor() const;
			Color getBackgroundColor() const;
			Gradient *getBackgroundGradient();
			Color getShadowColor() const;
			PointF getShadowShift() const;
			int getShadowRadius() const;
			Mat4f &getImageTransform(); // Return image transformation matrix
			float getOpacity() const; // Return image opacity

			// Set layout properties
			bool setBorderWidth(const RectF &value);
			bool setBorderRadius(const RectF &value);
			bool setBorderColor(const BorderColor &value);
			bool setLeftBorderColor(const Color &value);
			bool setTopBorderColor(const Color &value);
			bool setRightBorderColor(const Color &value);
			bool setBottomBorderColor(const Color &value);
			bool setBackgroundColor(const Color &value);
			bool setShadowColor(const Color &value);
			bool setShadowShift(const PointF &value);
			bool setShadowRadius(const int value);
			bool setImageTransform(const Mat4f &value); // Set image transformation matrix
			bool setOpacity(const float value); // Set image opacity
		};
	}
}