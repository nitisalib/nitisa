// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Messages.h"
#include "Nitisa/Interfaces/IControl.h"
#include "Nitisa/Math/PointF.h"

namespace nitisa
{
	class IComponent;
	class IControl;

	namespace ide
	{
		// Show all form's components. No transform except X, Y is applied to components
		class IFormEditor :public virtual IControl
		{
		protected:
			IFormEditor() = default;
			~IFormEditor() = default;
			IFormEditor(const IFormEditor &other) = delete;
			IFormEditor(IFormEditor &&other) = delete;
			IFormEditor &operator=(const IFormEditor &other) = delete;
			IFormEditor &operator=(IFormEditor &&other) = delete;
		public:
			void(*OnSelectControl)(IFormEditor *sender, IControl *control); // Event called on selection of control
			void(*OnDeselectControl)(IFormEditor *sender, IControl *control); // Event called remove selection from control
			void(*OnSelectComponent)(IFormEditor *sender, IComponent *component); // Event called on selection of component
			void(*OnDeselectComponent)(IFormEditor *sender, IComponent *component); // Event called on remove selection from component
			void(*OnCheckComponentAllowed)(IFormEditor *sender, IComponent *component, bool &allowed); // Event called to check whether component is allowed to be managed
			void(*OnComponentTransform)(IFormEditor *sender, IComponent *component); // Event called on component transformation
			void(*OnControlTransform)(IFormEditor *sender, IComponent *component); // Event called on control transformation
			void(*OnControlResize)(IFormEditor *sender, IComponent *component); // Event called on resizing of control
			void(*OnMouseDown)(IFormEditor *sender, const MessageMouse &m, bool &processed); // Event called on mouse down

			virtual bool isControlSelected(IControl *control) = 0; // Check whether specified control is selected
			virtual bool isComponentSelected(IComponent *component) = 0; // Check whether specified component is selected
			virtual PointF getComponentPosition(IComponent *component) = 0; // Return position of specified component
			virtual PointF getControlPosition(IControl *control) = 0; // Return position of specified control

			virtual bool setComponentPosition(IComponent *component, const PointF &value) = 0; // Set position of component
			virtual bool setControlPosition(IControl *control, const PointF &value) = 0; // Set position of control

			virtual bool SelectControl(IControl *control) = 0; // Select specified control
			virtual bool SelectComponent(IComponent *component) = 0; // Select specified component
			virtual bool SelectAllControls() = 0; // Select all controls
			virtual bool SelectAllComponents() = 0; // Select all components
			virtual bool SelectAll() = 0; // Select all controls and components
			virtual bool DeselectControl(IControl *control) = 0; // Deselect specified control
			virtual bool DeselectComponent(IComponent *component) = 0; // Deselect specified component
			virtual bool DeselectAllControls() = 0; // Deselect all controls
			virtual bool DeselectAllComponents() = 0; // Deselect all components
			virtual bool DeselectAll() = 0; // Deselect all controls and components
			virtual bool DeleteSelected() = 0; // Delete selected controls and components
		};
	}
}