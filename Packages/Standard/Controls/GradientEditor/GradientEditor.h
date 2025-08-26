// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "../IGradientEditor.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CGradientEditorService;

		class CGradientEditor :public virtual IGradientEditor, public CControl
		{
			friend CGradientEditorService;
		public:
			enum class ArrowState // States of arrows
			{
				Normal,
				Hovered,
				Active,
				ActiveHovered
			};
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CGradientEditor *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CGradientEditor *control);
			};
		private:
			CGradientListener m_cGradientListener;
			Gradient m_cGradient;
			int m_iActivePoint;
			int m_iHoveredPoint;
			Color m_sBackgroundColor;
			float m_fArrowSize;
			Color m_aArrowColor[(int)ArrowState::ActiveHovered + 1];
			Color m_aArrowBorderColor[(int)ArrowState::ActiveHovered + 1];

			ITexture *m_pCanvas;
			bool m_bDown;
			bool m_bIgnoreGradient;

			void UpdateFromStyle(IStyle *style);
			bool UpdateHoveredArrow(const PointF &position);
			void Render();
			void RenderGradient(IRenderer *renderer);
			void RenderArrows(IRenderer *renderer);
		public:
			void(*OnChange)(IControl *sender); // Event called when Gradiend has been changed

			// IControl methods
			void Refresh(const bool refresh_children) override;

			Gradient *getGradient() override;
			int getActivePoint() override;

			bool setDPI(const Point &value) override;
			bool setActivePoint(const int value) override;

			CGradientEditor();
			CGradientEditor(IControl *parent);
			CGradientEditor(IForm *parent);

			// Return layout properties
			Color getBackgroundColor() const;
			float getArrowSize() const;
			Color getArrowColor(const ArrowState state) const;
			Color getArrowBorderColor(const ArrowState state) const;

			// Set background properties
			bool setBackgroundColor(const Color &value);
			bool setArrowSize(const float value);
			bool setArrowColor(const ArrowState state, const Color &value);
			bool setArrowBorderColor(const ArrowState state, const Color &value);
		};
	}
}