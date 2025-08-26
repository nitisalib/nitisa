// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/Scroll/BuiltInScroll.h"
#include "Nitisa/BuiltInControls/IBuiltInScrollListener.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "Nitisa/Package/Interfaces/IPropertyHandlerListener.h"
#include "../IPropertyEditor.h"
#include <vector>

namespace nitisa
{
	class IBuiltInControl;
	class IControl;
	class IForm;
	class IProperty;
	class IPropertyHandler;
	class IPropertyState;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace ide
	{
		class CPropertyEditorService;

		class CPropertyEditor :public virtual IPropertyEditor, public CControl
		{
			friend CPropertyEditorService;
		public:
			enum class FolderState // Folder states
			{
				Folded, // Closed
				Unfolded // Opened
			};

			enum class PropertyState // Property states
			{
				Normal, // Normal
				Hovered, // Hovered
				Focused // Focused
			};
		private:
			enum class Element
			{
				None,
				Folder,
				CaptionSeparator,
				Property,
				Scroll
			};

			struct PROPERTY
			{
				IProperty *Property;
				IPropertyState *PropertyState;
				bool Folded;
			};

			class CScroll :public CBuiltInScroll
			{
			private:
				CPropertyEditor *m_pEditor;
			public:
				CScroll(CPropertyEditor *editor);

				IControl *getControl() override;
			};

			class CScrollListener :public virtual IBuiltInScrollListener
			{
			private:
				CPropertyEditor *m_pEditor;
			public:
				CScrollListener(CPropertyEditor *editor);

				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnScroll(IBuiltInControl *sender) override;
			};

			class CPropertyHandlerListener :public virtual IPropertyHandlerListener
			{
			private:
				CPropertyEditor *m_pEditor;
			public:
				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnPropertyChange(IBuiltInControl *sender, IProperty *property) override;

				CPropertyHandlerListener(CPropertyEditor *editor);
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CPropertyEditor *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CPropertyEditor *control);
			};
		private:
			CGradientListener m_cGradientListener;
			std::vector<IPropertyList*> m_aPropertyLists;
			std::vector<PROPERTY> m_aProperties;
			// Background
			RectF m_sBorderWidth;
			BorderColor m_sBorderColor;
			Color m_sBackgroundColor;
			Gradient m_cBackgroundGradient;
			// Folder
			float m_fFolderWidth;
			Color m_sFolderBackgroundColor;
			Gradient m_cFolderBackgroundGradient;
			// Folder icon
			float m_fFolderIconPadding; // Left & right
			float m_fFolderIconBorderWidth;
			float m_fFolderIconBorderRadius;
			Color m_sFolderIconBorderColor;
			Color m_sFolderIconBackgroundColor;
			Gradient m_cFolderIconBackgroundGradient;
			float m_fFolderIconInnerPadding;
			Color m_aFolderIconLineColor[(int)FolderState::Unfolded + 1];
			// Folder & caption separator
			float m_fFolderSeparatorWidth;
			Color m_sFolderSeparatorColor;
			Gradient m_cFolderSeparatorGradient;
			// Caption
			float m_fCaptionWidth; // 0..1
			float m_fCaptionPadding;
			float m_fCaptionStatePadding; // Additional left padding for unfolded property state captions
			Color m_aCaptionColor[(int)PropertyState::Focused + 1];
			float m_aCaptionBorderWidth[(int)PropertyState::Focused + 1];
			Color m_aCaptionBorderColor[(int)PropertyState::Focused + 1];
			Color m_aCaptionBackgroundColor[(int)PropertyState::Focused + 1];
			Gradient m_aCaptionBackgroundGradient[(int)PropertyState::Focused + 1];
			// Caption & handler separator
			float m_fCaptionSeparatorWidth;
			Color m_sCaptionSeparatorColor;
			Gradient m_cCaptionSeparatorGradient;

			ITexture *m_pCanvas;
			IBuiltInScroll *m_pScroll;
			bool m_bIgnoreGradient;
			CPropertyHandlerListener m_cListener;
			Element m_eHoveredElement;
			Element m_eDownElement;
			int m_iHoveredPropertyIndex;
			int m_iHoveredPropertyStateIndex;
			int m_iFocusedPropertyIndex;
			int m_iFocusedPropertyStateIndex;
			float m_fRowHeight;
			IPropertyHandler *m_pHandler;
			float m_fHandlerY; // Without scroll
			CScrollListener m_cScrollListener;
			bool m_bUpdateRequired;
			IPropertyHandler *m_pDefaultPropertyHandler;

			void NotifyOnPropertyChange(IProperty *property);

			bool isPointOverCaptionSeparator(const PointF &position);
			void Update();
			void UpdatePropertyList();
			void UpdateScroll();
			float CalculateCaptionWidth();
			float CalculateHandlerWidth();
			float CalculateHandlerX();
			float CalculateHandlerY();
			PropertyState getPropertyState(const int index);
			PropertyState getPropertyState(const int index, const int state);
			Element getElement(const PointF &position, int &property_index, int &property_state_index, PointF &property_position);
			bool UpdateHoveredElement(const PointF &position);
			void FreeHandler();
			PointF FormToHandler(const PointF &position);
			bool CompareProperties(IProperty *a, IProperty *b);
			IPropertyHandler *getPropertyHandler(const String &name);
			void UpdateFormStyle(IStyle *style);
			void Render();
			void RenderHandler(); // Render only active property
			void RenderControl(IRenderer *renderer);
		public:
			CursorType getCursor() override;

			bool setDPI(const Point &value) override;

			void Refresh(const bool refresh_children) override;

			int getPropertyListCount() override;
			IPropertyList *getPropertyList(const int index) override;
			int getPropertyCount() override;
			IProperty *getProperty(const int index) override;
			int getActivePropertyIndex() override;

			bool AttachPropertyList(IPropertyList *list) override;
			bool DetachPropertyList(const int index) override;
			bool DetachPropertyList(IPropertyList *list) override;
			bool DetachPropertyLists() override;

			CPropertyEditor();
			CPropertyEditor(IForm *parent);
			CPropertyEditor(IControl *parent);
			~CPropertyEditor() override;

			IBuiltInScroll *getScroll(); // Return scroll
			RectF getBorderWidth() const; // Return border width
			BorderColor getBorderColor() const; // Return border color
			Color getLeftBorderColor() const; // Return left border color
			Color getTopBorderColor() const; // Return top border color
			Color getRightBorderColor() const; // Return right border color
			Color getBottomBorderColor() const; // Return bottom border color
			Color getBackgroundColor() const; // Return background color
			Gradient *getBackgroundGradient(); // Return background gradient
			float getFolderWidth() const; // Return folder width
			Color getFolderBackgroundColor() const; // Return folder background color
			Gradient *getFolderBackgroundGradient(); // Return folder background gradient
			float getFolderIconPadding() const; // Return folder icon padding
			float getFolderIconBorderWidth() const; // Return folder icon border width
			float getFolderIconBorderRadius() const; // Return folder icon border corner radius
			Color getFolderIconBorderColor() const; // Return folder icon border color
			Color getFolderIconBackgroundColor() const; // Return folder icon background color
			Gradient *getFolderIconBackgroundGradient(); // Return folder icon background gradient
			float getFolderIconInnerPadding() const; // Return folder icon inner padding
			Color getFolderIconLineColor(const FolderState state); // Return folder icon line color depending on folder state
			float getFolderSeparatorWidth() const; // Return folder separator width
			Color getFolderSeparatorColor() const; // Return folder separator color
			Gradient *getFolderSeparatorGradient(); // Return folder separator gradient
			float getCaptionWidth() const; // Return caption width in parts of control width(0..1)
			float getCaptionPadding() const; // Return caption padding
			float getCaptionStatePadding() const; // Return caption padding for unfolded states
			Color getCaptionColor(const PropertyState state) const; // Return caption color depending on property state
			float getCaptionBorderWidth(const PropertyState state) const; // Return caption border width depending on property state
			Color getCaptionBorderColor(const PropertyState state) const; // Return caption border color depending on property state
			Color getCaptionBackgroundColor(const PropertyState state) const; // Return caption background color depending on property state
			Gradient *getCaptionBackgroundGradient(const PropertyState state); // Return caption background gradient depending on property state
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
			bool setFolderWidth(const float value); // Set folder width
			bool setFolderBackgroundColor(const Color &value); // Set folder background color
			bool setFolderIconPadding(const float value); // Set folder icon padding
			bool setFolderIconBorderWidth(const float value); // Set folder icon border width
			bool setFolderIconBorderRadius(const float value); // Set folder icon border corner radius
			bool setFolderIconBorderColor(const Color &value); // Set folder icon border color
			bool setFolderIconBackgroundColor(const Color &value); // Set folder icon background color
			bool setFolderIconInnerPadding(const float value); // Set folder icon inner padding
			bool setFolderIconLineColor(const FolderState state, const Color &value); // Set folder icon line color depending on folder state
			bool setFolderSeparatorWidth(const float value); // Set folder separator width
			bool setFolderSeparatorColor(const Color &value); // Set folder separator color
			bool setCaptionWidth(const float value); // Set caption width in parts of control width(0..1)
			bool setCaptionPadding(const float value); // Set caption padding
			bool setCaptionStatePadding(const float value); // Set caption padding for unfolded states
			bool setCaptionColor(const PropertyState state, const Color &value); // Set caption color depending on property state
			bool setCaptionBorderWidth(const PropertyState state, const float value); // Set caption border width depending on property state
			bool setCaptionBorderColor(const PropertyState state, const Color &value); // Set caption background color depending on property state
			bool setCaptionBackgroundColor(const PropertyState state, const Color &value); // Set caption background color depending on property state
			bool setCaptionSeparatorWidth(const float value); // Set caption separator width
			bool setCaptionSeparatorColor(const Color &value); // Set caption separator color
		};
	}
}