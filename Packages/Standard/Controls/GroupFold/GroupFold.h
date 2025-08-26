// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/TextAlign.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IGroupFold.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CGroupFold :public virtual IGroupFold, public CControl
		{
			friend class CGroupFoldService;
		public:
			enum class State
			{
				FoldedNormal,
				FoldedHovered,
				FoldedDisabled,
				Normal,
				Hovered,
				Disabled
			};
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CGroupFold *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CGroupFold *control);
			};
		private:
			CGradientListener m_cGradientListener;
			// IGroupFold properties
			bool m_bFolded;
			String m_sCaption;
			// Shadow properties
			int m_aShadowRadius[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			// Border properties
			RectF m_aBorderWidth[(int)State::Disabled + 1];
			RectF m_aBorderRadius[(int)State::Disabled + 1];
			BorderColor m_aBorderColor[(int)State::Disabled + 1];
			// Background properties
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			// Caption properties
			TextAlign m_eCaptionAlign;
			bool m_bCaptionPlusLeft; // Whether "+" is at left or at right of the caption
			Color m_aCaptionColor[(int)State::Disabled + 1];
			float m_aCaptionMargin[(int)State::Disabled + 1]; // Left & Right of caption block distance from borders
			PointF m_aCaptionPadding[(int)State::Disabled + 1]; // Left|Right, Top & Bottom
			RectF m_aCaptionBorderWidth[(int)State::Disabled + 1];
			RectF m_aCaptionBorderRadius[(int)State::Disabled + 1];
			BorderColor m_aCaptionBorderColor[(int)State::Disabled + 1];
			Color m_aCaptionBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aCaptionBackgroundGradient[(int)State::Disabled + 1];
			float m_aPlusSize[(int)State::Disabled + 1];
			float m_aPlusPadding[(int)State::Disabled + 1];
			// Client area properties
			RectF m_aPadding[(int)State::Disabled + 1];
			// Other properties
			bool m_bUseMask;
			
			bool m_bIgnoreGradient;
			bool m_bCaptionChanged;
			ITexture *m_pCanvas;
			ITexture *m_pMask;
			float m_fUnfoldedHeight;
			bool m_bHovered;

			// Helpers
			void UpdateFromStyle(IStyle *style);
			State getState();
			RectF CalculateCaptionRect();
			bool UpdateHovered(const PointF &position);
			// Render
			void Render(IRenderer *renderer, const Mat4f &matrix);
			void RenderMask(IRenderer *renderer);
		public:
			void(*OnToggle)(IControl *sender); // Event called when folded state changed

			// IControl getters
			IControl *getControl(const int index) override;
			IControl *getControl(const String &name) override;
			IControl *getControl(const PointF &position) override;
			RectF getClientRect() override;
			RectF getRenderRect() override;
			CursorType getCursor() override;

			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// IGroupFold getters
			bool isFolded() override;
			String getCaption() override;

			// IGroupFold setters
			bool setFolded(const bool value) override;
			bool setCaption(const String &value) override;

			// IGroupFold methods
			void Toggle() override;

			CGroupFold();
			CGroupFold(IControl *parent);
			CGroupFold(IForm *parent);

			// Layout getters
			int getShadowRadius(const State state) const;
			Color getShadowColor(const State state) const;
			PointF getShadowShift(const State state) const;
			RectF getBorderWidth(const State state) const;
			RectF getBorderRadius(const State state) const;
			BorderColor getBorderColor(const State state) const;
			Color getBackgroundColor(const State state) const;
			Gradient *getBackgroundGradient(const State state);
			TextAlign getCaptionAlign() const;
			bool isCaptionPlusLeft() const;
			Color getCaptionColor(const State state) const;
			float getCaptionMargin(const State state) const;
			PointF getCaptionPadding(const State state) const;
			RectF getCaptionBorderWidth(const State state) const;
			RectF getCaptionBorderRadius(const State state) const;
			BorderColor getCaptionBorderColor(const State state) const;
			Color getCaptionBackgroundColor(const State state) const;
			Gradient *getCaptionBackgroundGradient(const State state);
			float getPlusSize(const State state) const;
			float getPlusPadding(const State state) const;
			RectF getPadding(const State state) const;
			bool isUseMask() const;

			// Layout setters
			bool setShadowRadius(const State state, const int value);
			bool setShadowColor(const State state, const Color &value);
			bool setShadowShift(const State state, const PointF &value);
			bool setBorderWidth(const State state, const RectF &value);
			bool setBorderRadius(const State state, const RectF &value);
			bool setBorderColor(const State state, const BorderColor &value);
			bool setBackgroundColor(const State state, const Color &value);
			bool setCaptionAlign(const TextAlign value);
			bool setCaptionPlusLeft(const bool value);
			bool setCaptionColor(const State state, const Color &value);
			bool setCaptionMargin(const State state, const float value);
			bool setCaptionPadding(const State state, const PointF &value);
			bool setCaptionBorderWidth(const State state, const RectF &value);
			bool setCaptionBorderRadius(const State state, const RectF &value);
			bool setCaptionBorderColor(const State state, const BorderColor &value);
			bool setCaptionBackgroundColor(const State state, const Color &value);
			bool setPlusSize(const State state, const float value);
			bool setPlusPadding(const State state, const float value);
			bool setPadding(const State state, const RectF &value);
			bool setUseMask(const bool value);
		};
	}
}