// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h"
#include "Nitisa/BuiltInControls/Scroll/BuiltInScroll.h"
#include "Nitisa/BuiltInControls/IBuiltInDropDownListener.h"
#include "Nitisa/BuiltInControls/IBuiltInScroll.h"
#include "Nitisa/BuiltInControls/IBuiltInScrollListener.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IEventEditor.h"
#include <vector>

namespace nitisa
{
	class IBuiltInControl;
	class IControl;
	class IEvent;
	class IEventList;
	class IForm;
	class IListItem;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace ide
	{
		class CEventEditorService;

		class CEventEditor :public virtual IEventEditor, public CControl
		{
			friend CEventEditorService;
		public:
			enum class EventState // Describe event states
			{
				Normal, // Normal
				Hovered, // Event is hovered
				Focused // Event is focused
			};
		private:
			enum class Element
			{
				None,
				CaptionSeparator,
				Event,
				Scroll
			};

			class CScroll :public CBuiltInScroll
			{
			private:
				CEventEditor *m_pEditor;
			public:
				CScroll(CEventEditor *editor);

				IControl *getControl() override;
			};

			class CScrollListener :public virtual IBuiltInScrollListener
			{
			private:
				CEventEditor *m_pEditor;
			public:
				CScrollListener(CEventEditor *editor);

				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnScroll(IBuiltInControl *sender) override;
			};

			class CDropDown :public CBuiltInDropDown
			{
			private:
				CEventEditor *m_pEditor;

				static String GetItemText(IListItem *item);
			public:
				CDropDown(CEventEditor *editor);

				IControl *getControl() override;
			};

			class CDropDownListener :public virtual IBuiltInDropDownListener
			{
			private:
				CEventEditor *m_pEditor;
			public:
				CDropDownListener(CEventEditor *editor);

				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnTextChange(IBuiltInControl *sender) override;
				void NotifyOnSelect(IBuiltInControl *sender, const int index) override;
				void NotifyOnOpen(IBuiltInControl *sender) override;
				void NotifyOnClose(IBuiltInControl *sender) override;
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CEventEditor *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CEventEditor *control);
			};
		private:
			CGradientListener m_cGradientListener;
			std::vector<IEventList*> m_aEventLists;
			std::vector<IEvent*> m_aEvents;
			// Background
			RectF m_sBorderWidth;
			BorderColor m_sBorderColor;
			Color m_sBackgroundColor;
			Gradient m_cBackgroundGradient;
			// Caption
			float m_fCaptionWidth; // 0..1
			float m_fCaptionPadding;
			Color m_aCaptionColor[(int)EventState::Focused + 1];
			float m_aCaptionBorderWidth[(int)EventState::Focused + 1];
			Color m_aCaptionBorderColor[(int)EventState::Focused + 1];
			Color m_aCaptionBackgroundColor[(int)EventState::Focused + 1];
			Gradient m_aCaptionBackgroundGradient[(int)EventState::Focused + 1];
			// Caption & handler separator
			float m_fCaptionSeparatorWidth;
			Color m_sCaptionSeparatorColor;
			Gradient m_cCaptionSeparatorGradient;

			ITexture *m_pCanvas;
			IBuiltInScroll *m_pScroll;
			bool m_bIgnoreGradient;
			Element m_eHoveredElement;
			Element m_eDownElement;
			int m_iHoveredEventIndex;
			int m_iFocusedEventIndex;
			float m_fRowHeight;
			float m_fHandlerY; // Without scroll
			CDropDown *m_pHandler;
			CDropDown m_cDropDown;
			CDropDownListener m_cDropDownListener;
			CScrollListener m_cScrollListener;
			bool m_bUpdateRequired;

			void NotifyOnEventChange(IEvent *event);

			bool isPointOverCaptionSeparator(const PointF &position);
			void Update();
			void UpdateEventList();
			void UpdateScroll();
			float CalculateCaptionWidth();
			float CalculateHandlerWidth();
			float CalculateHandlerX();
			float CalculateHandlerAndSetOpenDirectionY();
			EventState getEventState(const int index);
			Element getElement(const PointF &position, int &event_index, PointF &event_position);
			bool UpdateHoveredElement(const PointF &position);
			void FreeHandler();
			PointF FormToHandler(const PointF &position);
			bool CompareEvents(IEvent *a, IEvent *b);
			void UpdateFormStyle(IStyle *style);
			void Render();
			void RenderHandler(); // Render only active property
			void RenderControl(IRenderer *renderer);
		public:
			CursorType getCursor() override;

			bool setDPI(const Point &value) override;

			void Refresh(const bool refresh_children) override;

			int getEventListCount() override;
			IEventList *getEventList(const int index) override;
			int getEventCount() override;
			IEvent *getEvent(const int index) override;
			int getActiveEventIndex() override;

			bool AttachEventList(IEventList *list) override;
			bool DetachEventList(const int index) override;
			bool DetachEventList(IEventList *list) override;
			bool DetachEventLists() override;

			CEventEditor();
			CEventEditor(IForm *parent);
			CEventEditor(IControl *parent);
			~CEventEditor() override;

			IBuiltInScroll *getScroll(); // Return scroll
			RectF getBorderWidth() const; // Return border width
			BorderColor getBorderColor() const; // Return border color
			Color getLeftBorderColor() const; // Return left border color
			Color getTopBorderColor() const; // Return top border color
			Color getRightBorderColor() const; // Return right border color
			Color getBottomBorderColor() const; // Return bottom border color
			Color getBackgroundColor() const; // Return background color
			Gradient *getBackgroundGradient(); // Return background gradient
			float getCaptionWidth() const; // Return caption width in parts of control width(0..1)
			float getCaptionPadding() const; // Return caption padding
			Color getCaptionColor(const EventState state) const; // Return caption color depending on state
			float getCaptionBorderWidth(const EventState state) const; // Return caption border width depending on state
			Color getCaptionBorderColor(const EventState state) const; // Return caption border color depending on state
			Color getCaptionBackgroundColor(const EventState state) const; // Return caption background color depending on state
			Gradient *getCaptionBackgroundGradient(const EventState state); // Return caption background gradient depending on state
			float getCaptionSeparatorWidth() const; // Return caption separator width
			Color getCaptionSeparatorColor() const; // Return caption separator color
			Gradient *getCaptionSeparatorGradient(); // Return caption separator gradient

			bool setScroll(IBuiltInScroll *value); // Set scroll
			bool setBorderWidth(const RectF &value); // Set border width
			bool setBorderColor(const BorderColor &value); // Set border color
			bool setLeftBorderColor(const Color &value); // Set left border color
			bool setTopBorderColor(const Color &value); // Set top border color
			bool setRightBorderColor(const Color &value); // Set right border color
			bool setBottomBorderColor(const Color &value); // Set bottom border color
			bool setBackgroundColor(const Color &value); // Set background color
			bool setCaptionWidth(const float value); // Set caption width in parts of control width(0..1)
			bool setCaptionPadding(const float value); // Set caption padding
			bool setCaptionColor(const EventState state, const Color &value); // Set caption color depending on state
			bool setCaptionBorderWidth(const EventState state, const float value); // Set caption border width depending on state
			bool setCaptionBorderColor(const EventState state, const Color &value); // Set caption border color depending on state
			bool setCaptionBackgroundColor(const EventState state, const Color &value); // Set caption background color depending on state
			bool setCaptionSeparatorWidth(const float value); // Set caption separator width
			bool setCaptionSeparatorColor(const Color &value); // Set caption separator color
		};
	}
}