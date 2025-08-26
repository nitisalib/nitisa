// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Align.h"
#include "../Core/CursorType.h"
#include "../Core/Messages.h"
#include "../Core/Strings.h"
#include "../Math/Mat4f.h"
#include "../Math/Point.h"
#include "../Math/PointF.h"
#include "../Math/RectF.h"
#include "IComponent.h"
#include "IControlService.h"

namespace nitisa
{
	class IFont;
	class IForm;
	class IStyle;
	class ITransform;

	// Control should notify all child controls using child->QueryService()->NotifyOnParentXXX() method about changes of style and font which appears directly in control, and about child control detach
	class IControl : public virtual IComponent
	{
	protected:
		IControl() = default;
		~IControl() = default;
		IControl(const IControl &other) = delete;
		IControl(IControl &&other) = delete;
		IControl &operator=(const IControl &other) = delete;
		IControl &operator=(IControl &&other) = delete;
	public:
		// Events from parent control
		void(*OnParentStyleChange)(IControl *sender); // Event called when parent style has been changed and this control uses it
		void(*OnParentFontChange)(IControl *sender); // Event called when parent font has been changed and this control uses it
		void(*OnParentResize)(IControl *sender); // Event called when parent size has been changed
		void(*OnParentTransform)(IControl *sender); // Event called when parent has been transformed
		void(*OnParentTransformControls)(IControl *sender); // Event called when parent child transformation has been changed

		// Events from child controls
		void(*OnChildStyleChange)(IControl *sender, IControl *control); // Event called when child control style has been changed
		void(*OnChildFontChange)(IControl *sender, IControl *control); // Event called when child control font has been changed
		void(*OnChildTransform)(IControl *sender, IControl *control); // Event called when child control has been transformed
		void(*OnChildResize)(IControl *sender, IControl *control); // Event called when child control size has been changed
		void(*OnChildShow)(IControl *sender, IControl *control); // Event called when child control has became visible
		void(*OnChildHide)(IControl *sender, IControl *control); // Event called when child control has became invisible
		void(*OnChildAttach)(IControl *sender, IControl *control); // Event called when child control has been added
		void(*OnChildDetach)(IControl *sender, IControl *control); // Event called when child control has been removed
		void(*OnChildEnable)(IControl *sender, IControl *control); // Event called when child control has become enabled
		void(*OnChildDisable)(IControl *sender, IControl *control); // Event called when child control has became disabled
		void(*OnChildBeforeTransform)(IControl *sender, IControl *control, bool &allowed) = 0; // Event called before applying transformation to control. Set allowed to false to forbid the change
		void(*OnChildBeforeResize)(IControl *sender, IControl *control, bool &allowed) = 0; // Event called before resizing control. Set allowed to false to forbid the change
		void(*OnChildBeforeShow)(IControl *sender, IControl *control, bool &allowed) = 0; // Event called before showing control. Set allowed to false to forbid the change
		void(*OnChildBeforeHide)(IControl *sender, IControl *control, bool &allowed) = 0; // Event called before hiding control. Set allowed to false to forbid the change
		void(*OnChildBeforeEnable)(IControl *sender, IControl *control, bool &allowed) = 0; // Event called before enabling control. Set allowed to false to forbid the change
		void(*OnChildBeforeDisable)(IControl *sender, IControl *control, bool &allowed) = 0; // Event called before disabling control. Set allowed to false to forbid the change

		// State change events
		void(*OnShow)(IControl *sender); // Event called when the control has became visible
		void(*OnHide)(IControl *sender); // Event called when the control has became invisible
		void(*OnEnable)(IControl *sender); // Event called when the control has became enabled
		void(*OnDisable)(IControl *sender); // Event called when the control has became disabled
		void(*OnResize)(IControl *sender); // Event called when the control size had been changed
		void(*OnTransform)(IControl *sender); // Event called when the control has been transformed
		void(*OnTransformControls)(IControl *sender); // Event called when the control child transformation has been changed
		void(*OnStyleChange)(IControl *sender); // Event called when the control style has been changed
		void(*OnFontChange)(IControl *sender); // Event called when the control font has been changed
		void(*OnSetModal)(IControl *sender); // Event called when the control has became modal
		void(*OnKillModal)(IControl *sender); // Event called when the control has lost modal state
		void(*OnSetFocus)(IControl *sender, const MessageFocus &m); // Event called when the control has received keyboard focus
		void(*OnKillFocus)(IControl *sender); // Event called when the control has lost keyboard focus
		void(*OnSetCaptureKeyboard)(IControl *sender); // Event called when the control has captured keyboard input
		void(*OnKillCaptureKeyboard)(IControl *sender); // Event called when the control has lost capture of keyboard input
		void(*OnSetCaptureMouse)(IControl *sender); // Event called when the control has captured mouse input
		void(*OnKillCaptureMouse)(IControl *sender); // Event called when the control has lost capture of mouse input
		void(*OnActivate)(IControl *sender); // Event called when the control has became active
		void(*OnDeactivate)(IControl *sender); // Event called when the control has lost active state

		// Paint events
		void(*OnPaint)(IControl *sender, const MessagePaint &m, bool &draw_children); // Event called at the beginning of the control painting
		void(*OnPaintEnd)(IControl *sender, const MessagePaint &m); // Event called at the end of the control painting

		// Keyboard input events
		void(*OnKeyDown)(IControl *sender, const MessageKey &m, bool &processed); // Event called when keyboard key has been down
		void(*OnKeyUp)(IControl *sender, const MessageKey &m, bool &processed); // Event called when keyboard key has been released
		void(*OnChar)(IControl *sender, const MessageChar &m, bool &processed); // Event called when character has been received from keyboard input
		void(*OnDeadChar)(IControl *sender, const MessageChar &m, bool &processed); // Event called when composite character(like umlaut-O) has been received fro keyboard input

		// Mouse input events
		void(*OnMouseHover)(IControl *sender, const MessagePosition &m); // Event called when the control appears under mouse pointer
		void(*OnMouseLeave)(IControl *sender); // Event called when mouse pointer left control area
		void(*OnMouseMove)(IControl *sender, const MessageMouse &m, bool &processed); // Event called when mouse pointer is moving
		void(*OnLeftMouseButtonDown)(IControl *sender, const MessageMouse &m, bool &processed); // Event called when left mouse button has been down
		void(*OnLeftMouseButtonUp)(IControl *sender, const MessageMouse &m, bool &processed); // Event called when left mouse button has been released
		void(*OnLeftMouseButtonDoubleClick)(IControl *sender, const MessageMouse &m, bool &processed); // Event called when left mouse button has been double clicked
		void(*OnRightMouseButtonDown)(IControl *sender, const MessageMouse &m, bool &processed); // Event called when right mouse button has been down
		void(*OnRightMouseButtonUp)(IControl *sender, const MessageMouse &m, bool &processed); // Event called when right mouse button has been released
		void(*OnRightMouseButtonDoubleClick)(IControl *sender, const MessageMouse &m, bool &processed); // Event called when right mouse button has been double clicked
		void(*OnMiddleMouseButtonDown)(IControl *sender, const MessageMouse &m, bool &processed); // Event called when middle mouse button has been down
		void(*OnMiddleMouseButtonUp)(IControl *sender, const MessageMouse &m, bool &processed); // Event called when middle mouse button has been released
		void(*OnMiddleMouseButtonDoubleClick)(IControl *sender, const MessageMouse &m, bool &processed); // Event called when middle mouse button has been double clicked
		void(*OnMouseVerticalWheel)(IControl *sender, const MessageMouseWheel &m, bool &processed); // Event called when mouse vertical wheel has been scrolled
		void(*OnMouseHorizontalWheel)(IControl *sender, const MessageMouseWheel &m, bool &processed); // Event called when mouse horizontal wheel has been scrolled

		// Other input events
		void(*OnDropFiles)(IControl *sender, const MessageDropFiles &m, bool &processed, bool &accepted); // Event called when files have been dropped over control

		// Clipboard events
		void(*OnPasteString)(IControl *sender, const MessagePasteString &m); // Event called when a string to paste becomes available after paste request

		virtual IControl *getParent() = 0; // Return parent control
		virtual IStyle *getParentStyle() = 0; // Return parent style
		virtual IStyle *getStyle() = 0; // Return style. It could be either its own or parent control/form style, depending on settings
		virtual IStyle *getControlStyle() = 0; // Return its own style
		virtual IFont *getFont() = 0; // Return font. It could be either its own or parent control/form font, depending on settings
		virtual IFont *getParentFont() = 0; // Return parent font
		virtual IFont *getControlFont() = 0; // Return its own font
		virtual int getControlCount(const bool total = false) = 0; // Return direct or all child control count
		virtual IControl *getControl(const int index) = 0; // Return child control by index
		virtual IControl *getControl(const String &name) = 0; // Return child control by name
		virtual IControl *getControl(const PointF &position) = 0; // Return child control at specified position. Position is in form client area coordinates
		virtual int getControlIndex(IControl *control) = 0; // Return child control index or -1
		virtual ITransform *getTransform() = 0; // Return transformation
		virtual ITransform *getTransformControls() = 0; // Return child controls transformation
		virtual Mat4f getTransformMatrix() = 0; // Return transformation matrix. Absolute to form client coordinate system
		virtual Align getAlign() = 0; // Return alignment. By default alNone
		virtual RectF getConstraints() = 0; // Return constraints. Left, Top - minimum width and height. Right, Bottom - maximum width and height. 0 - no limits. By default none(0, 0, 0, 0)
		virtual PointF getMinConstraints() = 0; // Return minimum allowed width and height
		virtual PointF getMaxConstraints() = 0; // Return maximum allowed width and height
		virtual float getMinWidth() = 0; // Return minimum allowed width
		virtual float getMinHeight() = 0; // Return minimum allowed height
		virtual float getMaxWidth() = 0; // Return maximum allowed width
		virtual float getMaxHeight() = 0; // Return maximum allowed height
		virtual PointF getSize() = 0; // Return width and height
		virtual float getWidth() = 0; // Return width
		virtual float getHeight() = 0; // Return height
		virtual RectF getRect() = 0; // Return rectangle. Left, Top is always 0, 0. Right, Bottom is equal to width, height
		virtual RectF getClientRect() = 0; // Return rectangle of client area in local coordinates. By default return the same as getRect()
		virtual RectF getRenderRect() = 0; // Return rectangle of rendering area(for example, control + it's shadow) in local coordinates. By default return the same as getRect()
		virtual int getZIndex() = 0; // Return Z-index. By default all controls have z-index equal to 0. It affects drawing order
		virtual CursorType getCursor() = 0; // Return cursor type when mouse pointer is over the control. But default crArrow
		virtual int getTabOrder() = 0; // Return tab order. Affects order in which controls will get focus by Tab and Shift+Tab. It set automatically when control is added to form
		virtual String getHintText() = 0; // Return hint text for the control. By default empty
		virtual float getHintDelay() = 0; // Return delay before hint appear(in seconds). By default 0
		virtual PointF getHintShift() = 0; // Return shift of the hint around the control. By default 0, 0
		virtual Point getDPI() = 0; // Return DPI for which control parameters where adopted. { 96, 96 } by default
		virtual bool isAcceptForm() = 0; // Whether it can be placed on a form directly
		virtual bool isAcceptForm(IForm *form) = 0; // Whether it can be placed on the specified form directly
		virtual bool isAcceptControl() = 0; // Whether it can be placed on a control
		virtual bool isAcceptControl(IControl *control) = 0; // Whether it can be placed on the specified control
		virtual bool isAcceptControls() = 0; // Whether another control can be placed on it
		virtual bool isAcceptFocus() = 0; // Whether can be focused
		virtual bool isAcceptModal() = 0; // Whether can be modal
		virtual bool isWantTabs() = 0; // Whether uses tab key itself. By default false
		virtual bool isTabStop() = 0; // Whether can be focused by Tab and Shift+Tab
		virtual bool isDeactivateByTab() = 0; // Whether another control can be activated by Tab key if this control is active. Has no sense for modal state. For active non-modal state only. By default true
		virtual bool isModal() = 0; // Whether in modal state
		virtual bool isHovered() = 0; // Whether is under mouse pointer
		virtual bool isFocused() = 0; // Whether is focused
		virtual bool isVisible(const bool with_parents) = 0; // Whether is visible. If with_parents is true, then check all parents and return false if one of them is invisible
		virtual bool isEnabled(const bool with_parents) = 0; // Whether is enabled. If with_parents is true, then check all parents and return false if one of them is inactive
		virtual bool isCaptureMouse() = 0; // Whether the control is capturing mouse input
		virtual bool isCaptureKeyboard() = 0; // Whether the control is capturing keyboard input
		virtual bool isActive() = 0; // Whether is active
		virtual bool isShowHint() = 0; // Whether hint should be shown.
		virtual bool isFocusByMouse() = 0; // Whether it could be focused by mouse click on it. True by default. Work only if isAcceptFocus() is true. By default true
		virtual bool isUseParentStyle() = 0; // Whether parent or local style should be used. By default true
		virtual bool isUseParentFont() = 0; // Whether parent or local font should be used. By default true
		virtual bool isUseParentShowHint() = 0; // Whether parent or local hint visibility settings should be used. By default true
		virtual bool isUseParentHintDelay() = 0; // Whether parent or local hint delay should be used. By default true
		virtual bool isUseParentHintShift() = 0; // Whether parent or local hint shift should be used. By default true
		virtual bool isAcceptChild(IControl *control) = 0; // Return true if child could be placed onto this control
		virtual bool isStaticTabOrder() = 0; // Return true if control and its children tab order should not be changed when adding it to a form. Should only return true if control is used as modal one or it will result in wrong switching between controls by Tab and Shift+Tab keys
		virtual bool isAcceptBubbledEvents() = 0; // Return whether bubbled mouse and keyboard events should be sent to this control
		virtual bool hasChild(IControl *control) = 0; // Check whether specified control is a child of this one in entire hierarchy of child controls
		virtual bool hasParent(IControl *control) = 0; // Check whether specified control is a parent of this one in entire hierarchy up to topmost one
		virtual bool hasStyle() const = 0; // Return whether control has style
		virtual bool hasFont() const = 0; // Return whether control has style
		virtual bool hasExtra() = 0; // Return true only if control is in state where it has extra part shown. For example, drop down with shown list.

		virtual bool setParent(IControl *value) = 0; // Set or remove parent
		virtual bool setStyle(IStyle *value) = 0; // Set style. It also change UseParentStyle to false
		virtual bool setFont(IFont *value, const bool copy = true) = 0; // Set font. It also change UseParentFont to false
		virtual bool setTransform(ITransform *value) = 0; // Set transform
		virtual bool setTransformControls(ITransform *value) = 0; // Set child controls transform
		virtual bool setAlign(const Align value) = 0; // Set alignment
		virtual bool setConstraints(const RectF &value) = 0; // Set constraints
		virtual bool setMinConstraints(const PointF &value) = 0; // Set minimum allowed width and height
		virtual bool setMaxConstraints(const PointF &value) = 0; // Set maximum allowed width and height
		virtual bool setMinWidth(const float value) = 0; // Set minimum allowed width
		virtual bool setMinHeight(const float value) = 0; // Set minimum allowed height
		virtual bool setMaxWidth(const float value) = 0; // Set maximum allowed width
		virtual bool setMaxHeight(const float value) = 0; // Set maximum allowed width
		virtual bool setSize(const PointF &value) = 0; // Set width and height. Don't change alignment
		virtual bool setWidth(const float value) = 0; // Set width. Don't change alignment
		virtual bool setHeight(const float value) = 0; // Set height. Don't change alignment
		virtual bool setZIndex(const int value) = 0; // Set Z-index
		virtual bool setCursor(const CursorType value) = 0; // Set cursor
		virtual bool setTabOrder(const int value) = 0; // Set tab order
		virtual bool setHintText(const String &value) = 0; // Set hint text
		virtual bool setHintDelay(const float value) = 0; // Set hint appearance delay. Also change UseParentHintDelay to false
		virtual bool setHintShift(const PointF &value) = 0; // Set hint shift. Also change UseParentHintShift to false
		virtual bool setWantTabs(const bool value) = 0; // Set whether the control uses Tab key in its own matter and form shouldn't process it
		virtual bool setTabStop(const bool value) = 0; // Set whether control could be focused by Tab and Shift+Tab
		virtual bool setDeactivateByTab(const bool value) = 0; // Set whether modal control can be deactivated by Tab
		virtual bool setModal(const bool value) = 0; // Activate/deactivate modal state
		virtual bool setFocus() = 0; // Set focused
		virtual bool setVisible(const bool value) = 0; // Show and hide
		virtual bool setEnabled(const bool value) = 0; // Enable and disable
		virtual bool setShowHint(const bool value) = 0; // Set whether to show hint or not. Also changes UseParentShowHint to false
		virtual bool setUseParentStyle(const bool value) = 0; // Set which style to use, parent or own
		virtual bool setUseParentFont(const bool value) = 0; // Set which font to use, parent or own
		virtual bool setUseParentShowHint(const bool value) = 0; // Set which hint visibility settings to use, parent or own
		virtual bool setUseParentHintDelay(const bool value) = 0; // Set which hint appearance settings to use, parent or own
		virtual bool setUseParentHintShift(const bool value) = 0; // Set which hint shift settings to use, parent or own
	#ifdef __clang__
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Woverloaded-virtual"
	#endif
		virtual void setService(IControlService *value, const bool release_prev) = 0; // Set new service. Use only compatible services and avoid setting empty value
	#ifdef __clang__
	#pragma clang diagnostic pop
	#endif
		virtual bool setDPI(const Point &value) = 0; // Adopt control parameters for new DPI
		virtual bool setStaticTabOrder(const bool value) = 0; // Set whether control and its children tab order should not be changed when adding it to a form. Should only be true if control is used as modal one or it will result in wrong switching between controls by Tab and Shift+Tab keys

		// Control
		virtual bool AttachControl(IControl *control) = 0; // Add child control
		virtual bool InsertControl(IControl *control, const int before) = 0; // Insert child control before specified position
		virtual bool DeleteControl(const int index) = 0; // Delete child control by index. Child control will be destroyed as well
		virtual bool DeleteControl(IControl *control) = 0; // Delete specified child control. Child control will be destroyed as well
		virtual bool DeleteControls() = 0; // Delete and destroy all child controls
		virtual bool DetachControl(IControl *control) = 0; // Delete child control and don't destroy it
		virtual IControl *FindControl(const String &name, IControl *exclude = nullptr) = 0; // Find control in entire hierarchy by name

		// Paint
		virtual void Repaint(const bool repaint_children) = 0; // Repaint entire control area with calling or not Repaint for all child controls (only needed if child control outside the control area should be repainted as well)
		virtual void Repaint(const RectF &rect, const bool convert) = 0; // Repaint specified control part. Convert indicates whether specified part should be converted to form coordinates or it is already converted
		virtual void Refresh(const bool refresh_children) = 0; // Clears internal canvas(drawing buffer). Do not call repaint automatic

		// Order
		virtual bool BringToFront() = 0; // Move the control to end of list or controls on a parent
		virtual bool BringUp() = 0; // Move the control to one position up in list or controls on parent
		virtual bool BringDown() = 0; // Move the control to one position down in list or controls on parent
		virtual bool BringBefore(IControl *control) = 0; // Move the control before specified one in list of controls on a parent
		virtual bool BringBefore(const int index) = 0; // Move the control before specified index in list of controls on a parent
		virtual bool BringAfter(IControl *control) = 0; // Move the control after specified one in list of controls on a parent
		virtual bool BringAfter(const int index) = 0; // Move the control after specified index in list of controls on a parent

		// Helpers
		virtual IControlService *QueryService() = 0; // Return service
		virtual PointF FormToLocal(const PointF &pos) = 0; // Convert from form to local coordinates
		virtual PointF LocalToForm(const PointF &pos) = 0; // Convert from local to form coordinates
		virtual bool ShowHint(const PointF &position) = 0; // Show control's hint. Position is in control coordinates
	};
}