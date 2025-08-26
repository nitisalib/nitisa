// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IContainer.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CContainerService;

		class CContainer :public virtual IContainer, public CControl
		{
			friend CContainerService;
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CContainer *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CContainer *control);
			};
		private:
			CGradientListener m_cGradientListener;
			Color m_sBackgroundColor; // When alpha is equal to 0 it means no background and control isn't renderable. Used only if there is no gradient
			Gradient m_cBackgroundGradient;
			bool m_bUseMask;
			ITexture *m_pMask;
			RectF m_sPadding;
			bool m_bOutlineInEditor;

			bool m_bIgnoreGradient;

			void UpdateFromStyle(IStyle *style);
			void Render(IRenderer *renderer, const Mat4f &matrix);
			void RenderMask(IRenderer *renderer, const Mat4f &matrix);
		public:
			IControl *getControl(const int index) override;
			IControl *getControl(const String &name) override;
			IControl *getControl(const PointF &position) override;
			RectF getClientRect() override;

			RectF getPadding() override;

			bool setDPI(const Point &value) override;
			bool setPadding(const RectF &value) override;

			CContainer();
			CContainer(IForm *parent);
			CContainer(IControl *parent);

			Color getBackgroundColor() const; // Return background color
			Gradient *getBackgroundGradient(); // Return background gradient
			bool isUseMask() const; // Whether to use mask
			bool isOutlineInEditor() const; // Return whether the widget should be outlined in the Form Builder

			bool setBackgroundColor(const Color &value); // Set background color
			bool setUseMask(const bool value); // Set whether to use mask
			bool setOutlineInEditor(const bool value); // Set whether the widget should be outlined in the Form Builder
		};
	}
}