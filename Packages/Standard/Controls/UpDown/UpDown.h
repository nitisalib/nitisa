// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Consts.h"
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Align.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/ControlSpliceService.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IUpDown.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class IEdit;

		class CUpDownService;

		class CUpDown :public virtual IUpDown, public CControl
		{
			friend CUpDownService;
		public:
			enum class State // Control and arrows states
			{
				Normal, // Normal
				Hovered, // Hovered
				Active, // Mouse button was down over arrow and not released yet
				Disabled // Control is disabled
			};
		private:
			enum class Element
			{
				None,
				UpArrow,
				DownArrow
			};

			class CEditSpliceService :public CControlSpliceService
			{
			private:
				CUpDown * m_pUpDown;
			public:
				void NotifyOnKeyDown(const MessageKey &m, bool &processed) override;
				void NotifyOnKeyUp(const MessageKey &m, bool &processed) override;
				void NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed) override;

				CEditSpliceService(IEdit *edit, CUpDown *updown);
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CUpDown *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CUpDown *control);
			};
		private:
			CGradientListener m_cGradientListener;
			int m_iMin;
			int m_iMax;
			int m_iValue;
			int m_iStep;
			IEdit *m_pAssignedTo;
			float m_fTimerInterval;
			float m_aDistance[(int)State::Disabled + 1]; // Between upper and lower parts
			RectF m_aUpArrowOuterBorderWidth[(int)State::Disabled + 1];
			BorderColor m_aUpArrowOuterBorderColor[(int)State::Disabled + 1];
			RectF m_aUpArrowMiddleBorderWidth[(int)State::Disabled + 1];
			BorderColor m_aUpArrowMiddleBorderColor[(int)State::Disabled + 1];
			RectF m_aUpArrowInnerBorderWidth[(int)State::Disabled + 1];
			BorderColor m_aUpArrowInnerBorderColor[(int)State::Disabled + 1];
			Color m_aUpArrowBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aUpArrowBackgroundGradient[(int)State::Disabled + 1];
			RectF m_aUpArrowPadding[(int)State::Disabled + 1];
			Color m_aUpArrowArrowColor[(int)State::Disabled + 1];
			RectF m_aDownArrowOuterBorderWidth[(int)State::Disabled + 1];
			BorderColor m_aDownArrowOuterBorderColor[(int)State::Disabled + 1];
			RectF m_aDownArrowMiddleBorderWidth[(int)State::Disabled + 1];
			BorderColor m_aDownArrowMiddleBorderColor[(int)State::Disabled + 1];
			RectF m_aDownArrowInnerBorderWidth[(int)State::Disabled + 1];
			BorderColor m_aDownArrowInnerBorderColor[(int)State::Disabled + 1];
			Color m_aDownArrowBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aDownArrowBackgroundGradient[(int)State::Disabled + 1];
			RectF m_aDownArrowPadding[(int)State::Disabled + 1];
			Color m_aDownArrowArrowColor[(int)State::Disabled + 1];
			bool m_bChangeByDrag;
			float m_fDragShift;
			float m_fDragScale;
			float m_fDragBase;
			float m_fDragBaseShift;
			float m_fDragBaseScale;

			ITexture *m_pCanvas;
			PlatformHandle m_hTimer;
			bool m_bIgnoreGradient;
			Element m_eHoveredElement;
			Element m_eDownElement;
			CEditSpliceService *m_pSpliceService;

			bool UpdateHoveredElement();
			bool UpdateHoveredElement(const PointF &position);
			State getUpArrowState();
			State getDownArrowState();
			RectF getUpArrowRect(const State state);
			RectF getDownArrowRect(const State state);
			void UpdateFromStyle(IStyle *style);
			void Render();
		public:
			// IControl methods
			void Refresh(const bool refresh_children) override;

			int getMin() override;
			int getMax() override;
			int getValue() override;
			int getStep() override;
			IEdit *getAssignedTo() override;

			bool setDPI(const Point &value) override;
			bool setAlign(const Align value) override;
			bool setMin(const int value) override;
			bool setMax(const int value) override;
			bool setValue(const int value) override;
			bool setStep(const int value) override;
			bool setAssignedTo(IEdit *value) override;

			bool Up() override;
			bool Down() override;

			CUpDown(); // Constructor
			CUpDown(IForm *parent); // Create and place on form
			CUpDown(IControl *parent); // Create and place on another control

			State getState(); // Return current state
			float getTimerInterval(); // Return value change interval when holding mouse button down over up or down arrow
			float getDistance(const State state); // Return distance between up and down arrows
			// Up arrow style getters
			RectF getUpArrowOuterBorderWidth(const State state);
			BorderColor getUpArrowOuterBorderColor(const State state);
			RectF getUpArrowMiddleBorderWidth(const State state);
			BorderColor getUpArrowMiddleBorderColor(const State state);
			RectF getUpArrowInnerBorderWidth(const State state);
			BorderColor getUpArrowInnerBorderColor(const State state);
			Color getUpArrowBackgroundColor(const State state);
			Gradient *getUpArrowBackgroundGradient(const State state);
			RectF getUpArrowPadding(const State state);
			Color getUpArrowArrowColor(const State state);
			// Down arrow style getters
			RectF getDownArrowOuterBorderWidth(const State state);
			BorderColor getDownArrowOuterBorderColor(const State state);
			RectF getDownArrowMiddleBorderWidth(const State state);
			BorderColor getDownArrowMiddleBorderColor(const State state);
			RectF getDownArrowInnerBorderWidth(const State state);
			BorderColor getDownArrowInnerBorderColor(const State state);
			Color getDownArrowBackgroundColor(const State state);
			Gradient *getDownArrowBackgroundGradient(const State state);
			RectF getDownArrowPadding(const State state);
			Color getDownArrowArrowColor(const State state);
			// Change by drag getters
			bool isChangeByDrag() const;
			float getDragShift() const;
			float getDragScale() const;
			float getDragBase() const;
			float getDragBaseShift() const;
			float getDragBaseScale() const;

			bool setTimerInterval(const float value); // Set value change interval when holding mouse button down over up or down arrow
			bool setDistance(const State state, const float value); // Set distance between up and down arrows
			// Up arrow style setters
			bool setUpArrowOuterBorderWidth(const State state, const RectF &value);
			bool setUpArrowOuterBorderColor(const State state, const BorderColor &value);
			bool setUpArrowMiddleBorderWidth(const State state, const RectF &value);
			bool setUpArrowMiddleBorderColor(const State state, const BorderColor &value);
			bool setUpArrowInnerBorderWidth(const State state, const RectF &value);
			bool setUpArrowInnerBorderColor(const State state, const BorderColor &value);
			bool setUpArrowBackgroundColor(const State state, const Color &value);
			bool setUpArrowPadding(const State state, const RectF &value);
			bool setUpArrowArrowColor(const State state, const Color &value);
			// Down arrow style setters
			bool setDownArrowOuterBorderWidth(const State state, const RectF &value);
			bool setDownArrowOuterBorderColor(const State state, const BorderColor &value);
			bool setDownArrowMiddleBorderWidth(const State state, const RectF &value);
			bool setDownArrowMiddleBorderColor(const State state, const BorderColor &value);
			bool setDownArrowInnerBorderWidth(const State state, const RectF &value);
			bool setDownArrowInnerBorderColor(const State state, const BorderColor &value);
			bool setDownArrowBackgroundColor(const State state, const Color &value);
			bool setDownArrowPadding(const State state, const RectF &value);
			bool setDownArrowArrowColor(const State state, const Color &value);
			// Change by drag setters
			bool setChangeByDrag(const bool value);
			bool setDragShift(const float value, const float tolerance = ntl::Tolerance<float>);
			bool setDragScale(const float value, const float tolerance = ntl::Tolerance<float>);
			bool setDragBase(const float value, const float tolerance = ntl::Tolerance<float>);
			bool setDragBaseShift(const float value, const float tolerance = ntl::Tolerance<float>);
			bool setDragBaseScale(const float value, const float tolerance = ntl::Tolerance<float>);
		};
	}
}