// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "../Core/CloseAction.h"
#include "../Core/CreateParams.h"
#include "../Core/CursorType.h"
#include "../Core/Key.h"
#include "../Core/Messages.h"
#include "../Core/ModalResult.h"
#include "../Core/Strings.h"
#include "../Core/WindowPosition.h"
#include "../Core/WindowState.h"
#include "../Image/Color.h"
#include "../Math/Point.h"
#include "../Math/PointF.h"
#include "../Math/Rect.h"
#include "../Math/RectF.h"
#include "IClass.h"

namespace nitisa
{
	class ICaret;
	class IControl;
	class IComponent;
	class IDialogBox;
	class IFont;
	class IFormListener;
	class IFormService;
	class IHint;
	class IRenderer;
	class IStyle;
	class ITask;
	class ITimerListener;
	class ITransform;

	// Form should notify all child controls using child->QueryService()->NotifyOnParentXXX() method about changes of style and font which appears directly in form, and about component and control detach
	class IForm : public virtual IClass
	{
	protected:
		IForm() = default;
		~IForm() = default;
		IForm(const IForm &other) = delete;
		IForm(IForm &&other) = delete;
		IForm &operator=(const IForm &other) = delete;
		IForm &operator=(IForm &&other) = delete;
	public:
		// Events from child controls
		void(*OnChildStyleChange)(IForm *sender, IControl *control); // Event called when style of child control has been changed
		void(*OnChildFontChange)(IForm *sender, IControl *control); // Event called when font of child control has been changed
		void(*OnChildTransform)(IForm *sender, IControl *control); // Event called when child control has been transformed
		void(*OnChildResize)(IForm *sender, IControl *control); // Event called when child control has been resized
		void(*OnChildShow)(IForm *sender, IControl *control); // Event called when child control has been shown
		void(*OnChildHide)(IForm *sender, IControl *control); // Event called when child control has been hidden
		void(*OnChildEnable)(IForm *sender, IControl *control); // Event called when child control has been enabled
		void(*OnChildDisable)(IForm *sender, IControl *control); // Event called when child control has been disabled
		void(*OnChildBeforeTransform)(IForm *sender, IControl *control, bool &allowed) = 0; // Event called before applying transformation to control. Set allowed to false to forbid the change
		void(*OnChildBeforeResize)(IForm *sender, IControl *control, bool &allowed) = 0; // Event called before resizing control. Set allowed to false to forbid the change
		void(*OnChildBeforeShow)(IForm *sender, IControl *control, bool &allowed) = 0; // Event called before showing control. Set allowed to false to forbid the change
		void(*OnChildBeforeHide)(IForm *sender, IControl *control, bool &allowed) = 0; // Event called before hiding control. Set allowed to false to forbid the change
		void(*OnChildBeforeEnable)(IForm *sender, IControl *control, bool &allowed) = 0; // Event called before enabling control. Set allowed to false to forbid the change
		void(*OnChildBeforeDisable)(IForm *sender, IControl *control, bool &allowed) = 0; // Event called before disabling control. Set allowed to false to forbid the change

		// State change events
		void(*OnResize)(IForm *sender); // Event called when the form has been resized
		void(*OnTransform)(IForm *sender); // Event called when the form has been transformed(moved)
		void(*OnTransformControls)(IForm *sender); // Event called when child control transformation has been changed
		void(*OnStyleChange)(IForm *sender); // Event called when style has been changed
		void(*OnFontChange)(IForm *sender); // Event called when font has been changed

		// Component events
		void(*OnComponentAttach)(IForm *sender, IComponent *component); // Event called when component has been attached
		void(*OnComponentDetach)(IForm *sender, IComponent *component); // Event called when component has been detached

		// Control events
		void(*OnControlAttach)(IForm *sender, IControl *control); // Event called when control has been attached
		void(*OnControlDetach)(IForm *sender, IControl *control); // Event called when control has been detached
		void(*OnControlSetModal)(IForm *sender, IControl *control); // Event called when control has got modal state
		void(*OnControlKillModal)(IForm *sender, IControl *control); // Event called when control has lost modal state
		void(*OnControlSetFocus)(IForm *sender, IControl *control, const MessageFocus &m); // Event called when control has became focused
		void(*OnControlKillFocus)(IForm *sender, IControl *control); // Event called when control has lost focus
		void(*OnControlMouseHover)(IForm *sender, IControl *control, const MessagePosition &m); // Event called when control has became hovered
		void(*OnControlMouseLeave)(IForm *sender, IControl *control); // Event called when control has become unhovered
		void(*OnControlSetCaptureKeyboard)(IForm *sender, IControl *control); // Event called when control has got capture keyboard input
		void(*OnControlKillCaptureKeyboard)(IForm *sender, IControl *control); // Event called when control has lost capture keyboard input
		void(*OnControlSetCaptureMouse)(IForm *sender, IControl *control); // Event called when control has got capture mouse input
		void(*OnControlKillCaptureMouse)(IForm *sender, IControl *control); // Event called when control has lost capture mouse input
		void(*OnControlActivate)(IForm *sender, IControl *control); // Event called when control has became active
		void(*OnControlDeactivate)(IForm *sender, IControl *control); // Event called when control has lost active state

		// Paint events
		void(*OnPaint)(IForm *sender, const MessagePaint &m, bool &draw_children); // Event called at the beginning of drawing the form
		void(*OnPaintEnd)(IForm *sender, const MessagePaint &m); // Event called at the end of drawing the form and controls

		// Keyboard input events
		void(*OnKeyDown)(IForm *sender, const MessageKey &m); // Event called when keyboard key has been down
		void(*OnKeyUp)(IForm *sender, const MessageKey &m); // Event called when keyboard key has been released
		void(*OnChar)(IForm *sender, const MessageChar &m); // Event called when character has been received via keyboard input
		void(*OnDeadChar)(IForm *sender, const MessageChar &m); // Event called when composite character has been received via keyboard input

		// Mouse input events
		void(*OnMouseHover)(IForm *sender, const MessageMouse &m); // Event called when mouse pointer hover the form
		void(*OnMouseLeave)(IForm *sender); // Event called when mouse pointer leaves the form
		void(*OnMouseMove)(IForm *sender, const MessageMouse &m); // Event called when mouse pointer is moving
		void(*OnLeftMouseButtonDown)(IForm *sender, const MessageMouse &m); // Event called when left mouse button has been down
		void(*OnLeftMouseButtonUp)(IForm *sender, const MessageMouse &m); // Event called when left mouse button has been released
		void(*OnLeftMouseButtonDoubleClick)(IForm *sender, const MessageMouse &m); // Event called when left mouse button has been double clicked
		void(*OnRightMouseButtonDown)(IForm *sender, const MessageMouse &m); // Event called when right mouse button has been down
		void(*OnRightMouseButtonUp)(IForm *sender, const MessageMouse &m); // Event called when right mouse button has been released
		void(*OnRightMouseButtonDoubleClick)(IForm *sender, const MessageMouse &m); // Event called when right mouse button has been double clicked
		void(*OnMiddleMouseButtonDown)(IForm *sender, const MessageMouse &m); // Event called when middle mouse button has been down
		void(*OnMiddleMouseButtonUp)(IForm *sender, const MessageMouse &m); // Event called when middle mouse button has been released
		void(*OnMiddleMouseButtonDoubleClick)(IForm *sender, const MessageMouse &m); // Event called when middle mouse button has been double clicked
		void(*OnMouseVerticalWheel)(IForm *sender, const MessageMouseWheel &m); // Event called when mouse vertical wheel has been scrolled
		void(*OnMouseHorizontalWheel)(IForm *sender, const MessageMouseWheel &m); // Event called when mouse horizontal wheel has been scrolled

		// Other input events
		void(*OnDropFiles)(IForm *sender, const MessageDropFiles &m, bool &accepted); // Event called when files has been dropped over the form
		void(*OnHotkey)(IForm *sender, const MessageHotkey &m); // Event called when registered combination of keys has been detected
		void(*OnGestureZoom)(IForm *sender, const MessagePosition &m); // Event called on gestures zoom
		void(*OnGesturePan)(IForm *sender, const MessagePosition &m); // Event called on gestures pan
		void(*OnGestureRotate)(IForm *sender, const MessagePosition &m); // Event called on gestures rotate
		void(*OnGestureTwoFingerTap)(IForm *sender, const MessagePosition &m); // Event called on gestures two finger tap
		void(*OnGesturePressAndTap)(IForm *sender, const MessagePosition &m); // Event called on gestures press and tap
		void(*OnGestureNotify)(IForm *sender); // Event called on gestures notify
		void(*OnTouch)(IForm *sender, const MessageTouch &m); // Event called on touch

		// Application events
		void(*OnApplicationActivate)(IForm *sender); // Event called when application has been activated
		void(*OnApplicationDeactivate)(IForm *sender); // Event called when application has been deactivated
		void(*OnQueryEndSession)(IForm *sender, bool &restricted); // Event called when system tries to end user session
		void(*OnQueryOpen)(IForm *sender, bool &restricted); // Event called when query is opened
		void(*OnEndSession)(IForm *sender, const MessageEndSession &m); // Event called when user session is ending
		void(*OnDeviceModeChange)(IForm *sender); // Event called when device mode has been changed
		void(*OnTimeChange)(IForm *sender); // Event called when system time has been changed
		void(*OnInputLanguageChangeRequest)(IForm *sender, bool &restricted); // Event called when system queries if language could be changed
		void(*OnInputLanguageChange)(IForm *sender); // Event called when language has been changed
		void(*OnDisplayChange)(IForm *sender, const MessageSize &m); // Event called when display settings has been changed
		void(*OnThemeChange)(IForm *sender); // Event called when theme has been changed
		void(*OnClipboardUpdate)(IForm *sender); // Event called when clipboard data has been changed
		void(*OnTranslateChange)(IForm *sender); // Event called when application gets information about changes in translation matrix

		// Window events
		void(*OnDestroy)(IForm *sender); // Event called when form is about to be destroyed
		void(*OnActivate)(IForm *sender, const MessageWindowActivate &m); // Event called when application has been activated
		void(*OnDeactivate)(IForm *sender); // Event called when application has been deactivated
		void(*OnSetFocus)(IForm *sender); // Event called when form has got focus
		void(*OnKillFocus)(IForm *sender); // Event called when form has lost focus
		void(*OnEnable)(IForm *sender); // Event called when form became enabled
		void(*OnDisable)(IForm *sender); // Event called when form became disabled
		void(*OnClose)(IForm *sender, CloseAction &action); // Event called when user tries to close the form. Action could be changed to prevent default behavior
		void(*OnShow)(IForm *sender); // Event called when form has been shown
		void(*OnHide)(IForm *sender); // Event called when form has been hidden
		void(*OnMove)(IForm *sender, const MessagePosition &m); // Event called when form is moving
		void(*OnRestore)(IForm *sender, const MessageSize &m); // Event called when form has been restored
		void(*OnMinimize)(IForm *sender, const MessageSize &m); // Event called when form has been minimized
		void(*OnMaximize)(IForm *sender, const MessageSize &m); // Event called when form has been maximized
		void(*OnResizing)(IForm *sender, const MessageWindowResizing &m); // Event called when form is being resized
		void(*OnMoving)(IForm *sender, const MessageRect &m); // Event called when form is being moved
		void(*OnEnterSizeMove)(IForm *sender); // Event called when form has entered resizing and moving state
		void(*OnExitSizeMove)(IForm *sender); // Event called when form has existed resizing and moving state
		void(*OnHScroll)(IForm *sender, const MessageWindowScroll &m); // Event called when horizontal scroll has happened
		void(*OnVScroll)(IForm *sender, const MessageWindowScroll &m); // Event called when vertical scroll has happened
		void(*OnLoseCapture)(IForm *sender); // Event called when form has lost capture

		// Dialog box events
		void(*OnDialogBoxActivate)(IForm *sender, IDialogBox *control); // Event called when dialog box becomes active
		void(*OnDialogBoxDeactivate)(IForm *sender, IDialogBox *control); // Event called when dialog box loses active state

		// Clipboard events
		void(*OnPasteString)(IForm *sender, const MessagePasteString &m); // Event called when a string to paste becomes available after paste request

		virtual IRenderer *getRenderer() = 0;
		virtual IHint *getHint() = 0; // Return hint. If not assigned, creates default one
		virtual IStyle *getStyle() = 0; // Return style. By default nullptr
		virtual IFont *getFont() = 0; // Return font. If not assigned, creates default one
		virtual ICaret *getCaret() = 0; // Return caret. If not assigned, creates default one
		virtual IControl *getModalControl() = 0; // Return current modal control
		virtual IControl *getFocusedControl() = 0; // Return current focused control
		virtual IControl *getCaptureKeyboardControl() = 0; // Return current control which captures keyboard input
		virtual IControl *getCaptureMouseControl() = 0; // Return current control which captures mouse input
		virtual IControl *getHoveredControl() = 0; // Return current hovered control
		virtual IControl *getActiveControl() = 0; // Return current active control
		virtual IControl *getInputControl() = 0; // Return control which handle all input which was not processed by other controls. It is used by controls which customize borders and caption to handle moving, resizing and other operations
		virtual int getControlCount(const bool total = false) = 0; // Return control count. Either only direct children or all in hierarchy
		virtual IControl *getControl(const int index) = 0; // Return control by index
		virtual IControl *getControl(const String &name) = 0; // Return control by name
		virtual IControl *getControl(const PointF &position) = 0; // Return control at specified position. Position is in form client area coordinates
		virtual int getControlIndex(IControl *control) = 0; // Return control index in list or -1
		virtual int getComponentCount() = 0; // Return component count
		virtual IComponent *getComponent(const int index) = 0; // Return component by index
		virtual IComponent *getComponent(const String &name) = 0; // Return component by name
		virtual int getComponentIndex(IComponent *component) = 0; // Return component index in list or -1
		virtual ITransform *getTransform() = 0; // Return transformation
		virtual ITransform *getTransformControls() = 0; // Return child controls transformation
		virtual CursorType getCursor() = 0; // Return cursor type. By default Arrow
		virtual String getHintText() = 0; // Return hint text. By default empty
		virtual float getHintDelay() = 0; // Return hint appearance delay(in seconds). By default 0.5 seconds
		virtual PointF getHintShift() = 0; // Return hint shift. By default 0, 20
		virtual Color getBackgroundColor() = 0; // Return background color. By default {240, 240, 240, 255}
		virtual bool isShowHint() = 0; // Return whether to show hint. By default true
		virtual bool isFocusByLMB() = 0; // Return whether to focus controls by left mouse button. By default true
		virtual bool isFocusByRMB() = 0; // Return whether to focus controls by right mouse button. By default true
		virtual bool isFocusByMMB() = 0; // Return whether to focus controls by middle mouse button. By default true
		virtual bool isFocusByTab() = 0; // Return whether to focus controls by Tab and Shift+Tab. By default true
		virtual bool isInterceptEnable() = 0; // Return whether interception mechanisms is enabled. By default false
		virtual int getTaskCount() = 0; // Return number of tasks in list
		virtual ITask *getTask(const int index) = 0; // Return task by index
		virtual RectF getBorderWidth() = 0; // Return border width which is used only when aligning controls. By default {0, 0, 0, 0}. Borders space could be used to draw custom borders and caption area(popup style form/window is also might be used to prevent appearing of default borders and caption)
		virtual RectF getPadding() = 0; // Return padding which is used only when aligning controls. By default {0, 0, 0, 0}
		virtual Point getDPI() = 0; // Return DPI for which form controls' parameters where adopted. { 96, 96 } by default
		virtual IDialogBox *getActiveDialogBox() = 0; // Return active dialog box
		virtual IFormListener *getListener() = 0; // Return assigned listener
		
		// Window getters
		virtual bool isVisible() = 0; // Return whether is visible
		virtual bool isEnabled() = 0; // Return whether is enabled
		virtual bool isAcceptDragAndDrop() = 0; // Return whether accepts drag and drop
		virtual bool isAcceptDropFiles() = 0; // Return whether accepts drop files
		virtual String getCaption() = 0; // Return caption
		virtual Rect getRect() = 0; // Return rectangle in screen coordinates
		virtual Point getSize() = 0; // Return width and height
		virtual Point getPosition() = 0; // Return position in screen coordinates
		virtual int getLeft() = 0; // Return left position in screen coordinates
		virtual int getTop() = 0; // Return top position in screen coordinated
		virtual int getWidth() = 0; // Return width
		virtual int getHeight() = 0; // Return height
		virtual Rect getClientRect() = 0; // Return client rectangle
		virtual Point getClientSize() = 0; // Return client area size
		virtual int getClientWidth() = 0; // Return client area width
		virtual int getClientHeight() = 0; // Return client area height
		virtual WindowState getState() = 0; // Return state
		virtual CreateParams getCreateParams() = 0; // Return window creation parameters
		virtual bool hasBorder() = 0; // Return whether form has standard border
		virtual bool hasCaption() = 0; // Return whether form has standard caption area
		virtual bool hasDialogFrame() = 0; // Return whether form has standard dialog frame
		virtual bool hasHorizontalScroll() = 0; // Return whether form has standard horizontal scrollbar
		virtual bool hasVerticalScroll() = 0; // Return whether form has standard vertical scrollbar
		virtual bool hasMaximizeBox() = 0; // Return whether form has standard minimize button
		virtual bool hasMinimizeBox() = 0; // Return whether form has standard maximize button
		virtual bool hasSizeBox() = 0; // Return whether form can be resized
		virtual bool hasSystemMenu() = 0; // Return whether form has standard system menu
		virtual bool hasClientEdge() = 0; // Return whether form has standard client edge
		virtual bool hasContextHelp() = 0; // Return whether form has standard context help
		virtual bool hasDialogModalFrame() = 0; // Return whether form has standard dialog modal frame
		virtual bool hasStaticEdge() = 0; // Return whether form has standard static edge
		virtual bool hasWindowEdge() = 0; // Return whether form has standard window edge
		virtual bool isPopup() = 0; // Return whether form is popup
		virtual bool isTabStop() = 0; // Return whether form is a control which could be activated by Tab
		virtual bool isMDIChild() = 0; // Return whether form is MDI child
		virtual bool isToolWindow() = 0; // Return whether form is tool one
		virtual bool isTopMost() = 0; // Return whether form is always on top of other ones

		virtual bool setHint(IHint *value) = 0; // Assign hint
		virtual bool setStyle(IStyle *value) = 0; // Assign style
		virtual bool setFont(IFont *value, const bool copy = true) = 0; // Assign font
		virtual bool setCaret(ICaret *value) = 0; // Assign caret
		virtual bool setModalControl(IControl *value) = 0; // Set new modal control. nullptr clears history of modal control changes. When control wants just release modal state and pass modal state to previously modal control, it should call ReleaseModal() method
		virtual bool setFocusedControl(IControl *value) = 0; // Set new focused control
		virtual bool setActiveControl(IControl *value) = 0; // Set new active control
		virtual bool setInputControl(IControl *value) = 0; // Set control which handle all input which was not processed by other controls. May be nullptr. It is used by controls which customize borders and caption to handle moving, resizing and other operations. Usually called by such a control itself at moment of adding to form
		virtual bool setTransformControls(ITransform *value) = 0; // Set child controls transformation
		virtual bool setCursor(const CursorType value) = 0; // Set cursor type
		virtual bool setHintText(const String &value) = 0; // Set hint text
		virtual bool setHintDelay(const float value) = 0; // Set hint appearance delay
		virtual bool setHintShift(const PointF &value) = 0; // Set hint shift
		virtual bool setBackgroundColor(const Color &value) = 0; // Set background color
		virtual bool setShowHint(const bool value) = 0; // Set whether hint should be shown
		virtual bool setFocusByLMB(const bool value) = 0; // Set whether controls could be focused by left mouse button
		virtual bool setFocusByMMB(const bool value) = 0; // Set whether controls could be focused by middle mouse button
		virtual bool setFocusByRMB(const bool value) = 0; // Set whether controls could be focused by right mouse button
		virtual bool setFocusByTab(const bool value) = 0; // Set whether controls could be focused by Tab and Shift+Tab
		virtual bool setInterceptEnable(const bool value) = 0; // Set whether intercepts are enabled
		virtual bool setBorderWidth(const RectF &value) = 0; // Set border width. Used in alignment. Border could be used for drawing custom borders and caption area. When you add control which customizes form borders and caption area it sets this property
		virtual bool setPadding(const RectF &value) = 0; // Set padding. Used in alignment
		virtual void setService(IFormService *value, const bool release_prev) = 0; // Set new service. Use only compatible services and avoid setting empty value
		virtual bool setDPI(const Point &value) = 0; // Adopt form controls' parameters for new DPI
		virtual bool setActiveDialogBox(IDialogBox *value) = 0; // Set active dialog box. nullptr clears dialog box activity history
		virtual void setListener(IFormListener *value) = 0; // Assign listener
		
		// Window setters
		virtual bool setVisible(const bool value) = 0; // Show/hide
		virtual bool setEnabled(const bool value) = 0; // Enable/disable
		virtual bool setAcceptDrawAndDrop(const bool value) = 0; // Set whether drag and drop is accepted
		virtual bool setAcceptDropFiles(const bool value) = 0; // Set whether drop files is accepted
		virtual bool setCaption(const String &value) = 0; // Set caption
		virtual bool setRect(const Rect &value) = 0; // Set position and size
		virtual bool setSize(const Point &value) = 0; // Set size
		virtual bool setPosition(const Point &value) = 0; // Set position
		virtual bool setLeft(const int value) = 0; // Set left coordinate
		virtual bool setTop(const int value) = 0; // Set top coordinate
		virtual bool setWidth(const int value) = 0; // Set width
		virtual bool setHeight(const int value) = 0; // Set height
		virtual bool setClientSize(const Point &value) = 0; // Set client area size
		virtual bool setState(const WindowState value) = 0; // Set state
		virtual bool setModalResult(const ModalResult value) = 0; // Set modal result. Only work when form is show by ShowModal()
		virtual bool setWindowPosition(const WindowPosition value) = 0; // Set window position
		virtual void setCreateParams(const CreateParams &value) = 0; // Set window creation parameters
		virtual bool setHasBorder(const bool value) = 0; // Set whether form has standard border. Work only if called before form window creation
		virtual bool setHasCaption(const bool value) = 0; // Set whether form has standard caption area. Work only if called before form window creation
		virtual bool setHasDialogFrame(const bool value) = 0; // Set whether form has standard dialog frame. Work only if called before form window creation
		virtual bool setHasHorizontalScroll(const bool value) = 0; // Set whether form has standard horizontal scrollbar. Work only if called before form window creation
		virtual bool setHasVerticalScroll(const bool value) = 0; // Set whether form has standard vertical scrollbar. Work only if called before form window creation
		virtual bool setHasMaximizeBox(const bool value) = 0; // Set whether form has standard minimize button. Work only if called before form window creation
		virtual bool setHasMinimizeBox(const bool value) = 0; // Set whether form has standard maximize button. Work only if called before form window creation
		virtual bool setHasSizeBox(const bool value) = 0; // Set whether form can be resized. Work only if called before form window creation
		virtual bool setHasSystemMenu(const bool value) = 0; // Set whether form has standard system menu. Work only if called before form window creation
		virtual bool setHasClientEdge(const bool value) = 0; // Set whether form has standard client edge. Work only if called before form window creation
		virtual bool setHasContextHelp(const bool value) = 0; // Set whether form has standard context help. Work only if called before form window creation
		virtual bool setHasDialogModalFrame(const bool value) = 0; // Set whether form has standard dialog modal frame. Work only if called before form window creation
		virtual bool setHasStaticEdge(const bool value) = 0; // Set whether form has standard static edge. Work only if called before form window creation
		virtual bool setHasWindowEdge(const bool value) = 0; // Set whether form has standard window edge. Work only if called before form window creation
		virtual bool setIsPopup(const bool value) = 0; // Set whether form is popup. Work only if called before form window creation
		virtual bool setIsTabStop(const bool value) = 0; // Set whether form is a control which could be activated by Tab. Work only if called before form window creation
		virtual bool setIsMDIChild(const bool value) = 0; // Set whether form is MDI child. Work only if called before form window creation
		virtual bool setIsToolWindow(const bool value) = 0; // Set whether form is tool one. Work only if called before form window creation
		virtual bool setIsTopMost(const bool value) = 0; // Set whether form is always on top of other ones. Work only if called before form window creation

		// Components
		virtual bool AttachComponent(IComponent *component) = 0; // Add component
		virtual bool DeleteComponent(const int index) = 0; // Delete and destroy component by index
		virtual bool DeleteComponent(IComponent *component) = 0; // Delete and destroy specified component
		virtual bool DeleteComponents() = 0; // Delete and destroy all components
		virtual bool DetachComponent(IComponent *component) = 0; // Detach but don't destroy specified component

		// Controls
		virtual bool AttachControl(IControl *control) = 0; // Add control
		virtual bool InsertControl(IControl *control, const int before) = 0; // Insert control before specified position
		virtual bool DeleteControl(const int index) = 0; // Delete and destroy control by index
		virtual bool DeleteControl(IControl *control) = 0; // Delete and destroy specified control
		virtual bool DeleteControls() = 0; // Delete and destroy all controls
		virtual bool DetachControl(IControl *control) = 0; // Delete but don't destroy specified control
		virtual IControl *FindControl(const String &name, IControl *exclude = nullptr) = 0; // Find control with specified name in entire hierarchy
		virtual bool FocusPrevControl() = 0; // Focus previous control(previous by tab index)
		virtual bool FocusNextControl() = 0; // Focus next control(next by tab index)
		virtual bool CaptureKeyboard(IControl *control) = 0; // Send all keyboard input to specified control. If set to empty it will clear capture queue
		virtual bool CaptureMouse(IControl *control, const bool system_capture) = 0; // Send all mouse input to specified control. If set to empty it will clear capture queue
		virtual void ReleaseCaptureKeyboard() = 0; // Release keyboard capture and set to previous one(if exists)
		virtual void ReleaseCaptureMouse() = 0; // Release mouse capture and set to previpous one(if exists)
		virtual void UpdateHoveredControl() = 0; // Update hovered/unhovered state using current mouse pointer position
		virtual void ReleaseModal() = 0; // Pass modal state to previously modal control. If control is derived from CDialogBox there is usually no need in using this method. Changing dialog boxes is handled by form

		// Paint
		virtual void LockRepaint() = 0; // Stop real drawing. Could be called many times
		virtual void UnlockRepaint() = 0; // Resume real drawing. Should be called the same amount of times as LockRepaint to resume real drawings
		virtual void Repaint() = 0; // Repaint entire form area
		virtual void Refresh() = 0; // Calls Refresh() on all child controls forcing them to clear internal canvas(drawing buffer)
		virtual void Repaint(const Rect &rect, const bool force = false) = 0; // Repaint specified form rectangle. If force is true, current repaint rectangle stored in a form will be rewritten with a new one. If force is false, new rectangle will be added to current form's one. With force equals to true and zero rectangle repainting can be prevented at all
		virtual void Repaint(const RectF &rect, const bool force = false) = 0; // Repaint specified form rectangle. If force is true, current repaint rectangle stored in a form will be rewritten with a new one. If force is false, new rectangle will be added to current form's one. With force equals to true and zero rectangle repainting can be prevented at all

		// Hotkeys
		virtual bool RegisterHotkey(const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down) = 0; // Register hotkey
		virtual bool UnregisterHotkey(const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down) = 0; // Unregister hotkey
		virtual bool UnregisterHotkeys() = 0; // Unregister all registered hotkeys

		// Helpers
		virtual void Release() = 0; // Destroy instance
		virtual IFormService *QueryService() = 0; // Return service

		// Window actions
		virtual bool Show() = 0; // Show
		virtual ModalResult ShowModal() = 0; // Show as modal
		virtual bool Hide() = 0; // Hide
		virtual PlatformHandle CreateTimer(ITimerListener *listener, const float interval) = 0; // Create timer
		virtual bool DeleteTimer(const PlatformHandle id) = 0; // Delete timer
		virtual void DeleteTimers() = 0; // Delete all timers
		virtual bool ResetTimer(const PlatformHandle id, const float interval) = 0; // Change timer interval and reset it to start
		virtual bool Maximize() = 0; // Maximize
		virtual bool Minimize() = 0; // Minimize
		virtual bool Restore() = 0; // Restore
		virtual bool CopyStringToClipboard(const String &str) = 0; // Copy specified string to clipboard
		virtual bool CopyStringFromClipboard() = 0; // Copy string from clipboard. If successful, focused widget will receive NotifyOnPasteString() notification immediately or later(depends on OS)
		virtual Rect ScreenToClient(const Rect &rect) = 0; // Convert from screen to form coordinates
		virtual Point ScreenToClient(const Point &pos) = 0; // Convert from screen to form coordinates
		virtual Rect ClientToScreen(const Rect &rect) = 0; // Convert from form to screen coordinates
		virtual Point ClientToScreen(const Point &pos) = 0; // Convert from form to screen coordinates
		virtual bool Close() = 0; // Close form(send close message to corresponding window)

		// Tasks
		virtual bool AddTask(ITask *task) = 0; // Add task to the form. All tasks executed(one by one) after last unlock repaint and removed after it
		virtual bool DeleteTask(const int index) = 0; // Delete task by id
		virtual bool DeleteTask(ITask *task) = 0; // Delete specified task
		virtual void DeleteTasks() = 0; // Delete all tasks
		virtual void RunTasks() = 0; // Run tasks(only if they are not run yet)

		// Hint actions
		virtual bool ShowHint(const String &text, const Point &position) = 0; // Show hint. Position is in form coordinates
		virtual bool ShowHint(IControl *control, const PointF &position) = 0; // Show control's hint. Position is in control coordinates
	};
}