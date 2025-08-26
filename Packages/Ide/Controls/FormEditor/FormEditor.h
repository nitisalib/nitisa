// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointB.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IFormEditor.h"
#include <vector>

namespace nitisa
{
	class IComponent;
	class IControl;
	class IFont;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;
	class ITransform;

	namespace ide
	{
		class CFormEditorService;

		// Grid is not available if there is child control transformation
		class CFormEditor :public virtual IFormEditor, public CControl
		{
			friend CFormEditorService;
		public:
			enum class SelectionState // Selection marker states
			{
				Normal, // One element is selected and no mouse transformation is active
				Hovered, // One element is selected, no mouse transformation is active and some selection element is hovered
				Active, // One element is selected and mouse transformation is active
				Disabled // More than one elements are selected
			};
		private:
			struct COMPONENT
			{
				IComponent *Component;
				IControl *Control;
				PointF Position;
				bool Selected;
				PointF DownPosition; // Start translate
				bool DownSelected;
			};

			struct CONTROL
			{
				IControl *Control;
				bool Selected;
				PointF DownPointLocal; // Mouse position in control coordinate system at mouse down moment
				PointF DownPosition; // Start translate
				float DownRotate; // Start rotate
				PointF DownSize; // Start size
				bool DownSelected;
				Mat4f FormToLocal; // Transfrom form coordinates to control ones
				Mat4f ParentToForm; // Transform parent coordinates to form ones
				Mat4f LocalToParent; // Transform control coordinates to parent
			};

			enum class Part
			{
				None,
				ResizeLeft,
				ResizeTop,
				ResizeRight,
				ResizeBottom,
				ResizeLeftTop,
				ResizeRightTop,
				ResizeRightBottom,
				ResizeLeftBottom,
				Rotate, // Is near the Right resize marker
				Translate, // Used only in m_eOperation
				Select // Used only in m_eOperation
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CFormEditor *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CFormEditor *control);
			};
		private:
			static const PointF ComponentIconSize;

			CGradientListener m_cGradientListener;
			std::vector<COMPONENT> m_aComponents;
			std::vector<CONTROL> m_aControls;
			Color m_sBackgroundColor;
			Gradient m_cBackgroundGradient;
			float m_fSelectionSize;
			Color m_aSelectionColor[(int)SelectionState::Disabled + 1];
			PointB m_sGridEnabled;
			PointF m_sGridSize;
			float m_fGridPointSize;
			Color m_sGridPointColor;
			bool m_bRotateGridEnabled;
			float m_fRotateGridSize;
			bool m_bUseMask;
			float m_fRotateShift;
			float m_fSelectionBorderWidth;
			Color m_sSelectionBorderColor;
			Color m_sSelectionBackgroundColor;
			RectF m_sPadding;

			ITexture *m_pCanvas;
			ITexture *m_pCanvasControl;
			ITexture *m_pCanvasControlBackground;
			ITexture *m_pMask;
			bool m_bIgnoreGradient;
			Part m_eHoveredPart;
			Part m_eOperation;
			bool m_bMouseDown;
			IForm *m_pPropertySource;

			bool isMultipleSelect();
			int getFirstSelectedComponent();
			int getFirstSelectedControl();
			Part getControlPart(const int index, const PointF &position); // Position is in form coordinate system
			bool DeselectChildren(IControl *parent);
			bool UpdateHoveredPart(const PointF &position); // Position is in form coordinate system
			int getComponent(const PointF &position); // Position is in form coodinate system
			SelectionState getSelectionState(const bool is_multiple_select, const int first_selected_control, const int control_index, const Part part);
			Mat4f getComponentMatrix(const PointF &position);
			void SetFormRecursively(IControl *control, IForm *form);
			void GenerateNameRecursively(IControl *control);
			void NotifyAttach(IControl *control);
			void UpdateFromStyle(IStyle *style);
			void Render(IRenderer *renderer, const Mat4f &matrix);
			void RenderComponents(IRenderer *renderer);
			void RenderComponentCanvas(IRenderer *renderer);
			void RenderSelection(IRenderer *renderer);
			void RenderSelectionRectangle(IRenderer *renderer, const RectF &rect);
			void RenderMask(IRenderer *renderer);
		public:
			// IControl getters
			CursorType getCursor() override;
			IFont *getFont() override;
			IStyle *getStyle() override;
			ITransform *getTransformControls() override;
			bool isShowHint() override;
			float getHintDelay() override;
			PointF getHintShift() override;
			RectF getClientRect() override;

			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			bool InsertControl(IControl *control, const int before) override;
			void Refresh(const bool refresh_children) override;

			// IFormEditor getters
			bool isControlSelected(IControl *control) override;
			bool isComponentSelected(IComponent *component) override;
			PointF getComponentPosition(IComponent *component) override;
			PointF getControlPosition(IControl *control) override;

			// FormEditor setters
			bool setComponentPosition(IComponent *component, const PointF &value) override;
			bool setControlPosition(IControl *control, const PointF &value) override;

			// IFormEditor methods
			bool SelectControl(IControl *control) override;
			bool SelectComponent(IComponent *component) override;
			bool SelectAllControls() override;
			bool SelectAllComponents() override;
			bool SelectAll() override;
			bool DeselectControl(IControl *control) override;
			bool DeselectComponent(IComponent *component) override;
			bool DeselectAllControls() override;
			bool DeselectAllComponents() override;
			bool DeselectAll() override;
			bool DeleteSelected() override;

			CFormEditor();
			CFormEditor(IForm *parent);
			CFormEditor(IControl *parent);

			IForm *getPropertySource(); // Return assigned form to be used to get some properties
			Color getBackgroundColor(); // Return background color
			Gradient *getBackgroundGradient(); // Return background gradient
			float getSelectionSize() const; // Return selection markers size
			Color getSelectionColor(const SelectionState state) const; // Return selection markers color depending on state
			PointB getGridEnabled() const; // Return whether the move grid is enabled
			PointF getGridSize() const; // Return the move grid steps
			float getGridPointSize() const; // Return grid point size
			Color getGridPointColor() const; // Return grid point color
			bool isRotateGridEnabled() const; // Return whether rotation grid enabled
			float getRotateGridSize() const; // Return rotation grid step
			bool isUseMask() const; // Return whether clipping mask should be used
			float getRotateShift() const; // Return rotation marker shift
			float getSelectionBorderWidth() const; // Return border width of selection rectangle
			Color getSelectionBorderColor() const; // Return border color of selection rectangle
			Color getSelectionBackgroundColor() const; // Return background color of selection rectangle
			RectF getPadding() const; // Return padding

			bool setPropertySource(IForm *value); // Assign form to be used to get some properties
			bool setBackgroundColor(const Color &value); // Set background color
			bool setSelectionSize(const float value); // Set selection markers size
			bool setSelectionColor(const SelectionState state, const Color &value); // Set selection markers color depending on state
			bool setGridEnabled(const PointB &value); // Set whether the move grid enabled
			bool setGridSize(const PointF &value); // Set the move grid steps
			bool setGridPointSize(const float value); // Set grid point size
			bool setGridPointColor(const Color &value); // Set grid point color
			bool setRotateGridEnabled(const bool value); // Set whether rotation grid enabled
			bool setRotateGridSize(const float value); // Set rotation grid step
			bool setUseMask(const bool value); // Set whether clipping mask should be used
			bool setRotateShift(const float value); // Set rotate marker shift
			bool setSelectionBorderWidth(const float value); // Set border width of selection rectangle
			bool setSelectionBorderColor(const Color &value); // Set border color of selection rectangle
			bool setSelectionBackgroundColor(const Color &value); // Set background color of selection rectangle
			bool setPadding(const RectF &value); // Set padding
		};
	}
}