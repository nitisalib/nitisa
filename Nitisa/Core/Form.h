// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

// Should ignore destroy window event after call of release of window object
#include "../Image/Color.h"
#include "../Interfaces/IFeedback.h"
#include "../Interfaces/IForm.h"
#include "../Interfaces/IFeedbackExListener.h"
#include "../Interfaces/ITimerListener.h"
#include "../Interfaces/IWindowListener.h"
#include "../Math/Mat4f.h"
#include "../Math/Point.h"
#include "../Math/PointF.h"
#include "../Math/Rect.h"
#include "../Math/RectF.h"
#include "../Math/Transform.h"
#include "Aliases.h"
#include "Class.h"
#include "CloseAction.h"
#include "CreateParams.h"
#include "CursorType.h"
#include "FocusedBy.h"
#include "Hotkey.h"
#include "Key.h"
#include "Messages.h"
#include "ModalResult.h"
#include "RotateOrder.h"
#include "Strings.h"
#include "Transform.h"
#include "TransformOrder.h"
#include "WindowPosition.h"
#include "WindowState.h"
#include <vector>

#pragma warning(disable: 4250)

namespace nitisa
{
	class ICaret;
	class IComponent;
	class IControl;
	class IDialogBox;
	class IFont;
	class IFontProperties;
	class IFormListener;
	class IFormService;
	class IHint;
	class IRenderer;
	class IStyle;
	class ITask;
	class ITransform;
	class IWindow;
	class IWindowListenerOnMessage;

	class CFormService;

	// Form should notify all child controls using child->QueryService()->NotifyOnParentXXX() method about changes of style and font which appears directly in form, and about
	// component and control detach
	// When deriving form from this one you should assign renderer and window and create controls in constructor(you may do it between LockRepaint() and UnlockRepaint() to
	// prevent multiple repaints
	// Managing different controls:
	//	Capture keyboard
	//		visible, enabled, on modal
	//	Capture mouse
	//		visible, enabled, on modal
	//	Focused
	//		visible, enabled, on modal
	//	Hovered
	//		visible
	//	Active
	//		visible, enabled, on modal
	//	Modal
	//		visible
	//	Active dialog box
	//		visible,        , on modal
	class CForm :public virtual IForm, public CClass
	{
		friend CFormService;
	private:
		struct FormHotkey :public Hotkey
		{
			IComponent *Component; // If both Component & Control are null, then hotkey belongs to form
			IControl *Control;
			int RefCount;

			FormHotkey(const nitisa::Key key, const bool ctrl, const bool alt, const bool shift, const bool down, IComponent *component, IControl *control);
		};

		struct MESSAGE_LISTENER
		{
			IComponent *Component;
			IWindowListenerOnMessage *Listener;
		};

		struct CAPTURE_MOUSE
		{
			IControl *Control;
			bool System;
		};

		class CWindowListener :public virtual IWindowListener
		{
		private:
			CForm *m_pForm;

			void ActivateDialogBox(IControl *control);
		public:
			void OnCreate() override;
			void OnDestroy() override;
			void OnActivate(const MessageWindowActivate &m) override;
			void OnDeactivate() override;
			void OnSetFocus() override;
			void OnKillFocus() override;
			void OnEnable() override;
			void OnDisable() override;
			void OnClose(CloseAction &action) override;
			void OnShow() override;
			void OnHide() override;
			void OnActivateApp() override;
			void OnDeactivateApp() override;
			void OnMove(const MessagePosition &m) override;
			void OnRestore(const MessageSize &m) override;
			void OnMinimize(const MessageSize &m) override;
			void OnMaximize(const MessageSize &m) override;
			void OnResizing(const MessageWindowResizing &m) override;
			void OnMoving(const MessageRect &m) override;
			void OnEnterSizeMove() override;
			void OnExitSizeMove() override;
			void OnKeyDown(const MessageKey &m) override;
			void OnKeyUp(const MessageKey &m) override;
			void OnChar(const MessageChar &m) override;
			void OnDeadChar(const MessageChar &m) override;
			void OnHScroll(const MessageWindowScroll &m) override;
			void OnVScroll(const MessageWindowScroll &m) override;
			void OnGestureZoom(const MessagePosition &m) override;
			void OnGesturePan(const MessagePosition &m) override;
			void OnGestureRotate(const MessagePosition &m) override;
			void OnGestureTwoFingerTap(const MessagePosition &m) override;
			void OnGesturePressAndTap(const MessagePosition &m) override;
			void OnGestureNotify() override;
			void OnMouseMove(const MessageMouse &m) override;
			void OnLeftMouseButtonDown(const MessageMouse &m) override;
			void OnLeftMouseButtonUp(const MessageMouse &m) override;
			void OnLeftMouseButtonDoubleClick(const MessageMouse &m) override;
			void OnRightMouseButtonDown(const MessageMouse &m) override;
			void OnRightMouseButtonUp(const MessageMouse &m) override;
			void OnRightMouseButtonDoubleClick(const MessageMouse &m) override;
			void OnMiddleMouseButtonDown(const MessageMouse &m) override;
			void OnMiddleMouseButtonUp(const MessageMouse &m) override;
			void OnMiddleMouseButtonDoubleClick(const MessageMouse &m) override;
			void OnMouseVerticalWheel(const MessageMouseWheel &m) override;
			void OnMouseHorizontalWheel(const MessageMouseWheel &m) override;
			void OnMouseHover(const MessageMouse &m) override;
			void OnMouseLeave() override;
			void OnLoseCapture() override;
			void OnPaint(const MessageRect &m) override;
			void OnQueryEndSession(bool &restricted) override;
			void OnQueryOpen(bool &restricted) override;
			void OnEndSession(const MessageEndSession &m) override;
			void OnDeviceModeChange() override;
			void OnTimeChange() override;
			void OnInputLanguageChangeRequest(bool &restricted) override;
			void OnInputLanguageChange() override;
			void OnDisplayChange(const MessageSize &m) override;
			void OnThemeChanged() override;
			void OnClipboardUpdate() override;
			void OnDropFiles(const MessageDropFiles &m, bool accepted) override;
			void OnTouch(const MessageTouch &m) override;
			bool OnMessage(const unsigned int uMsg, const unsigned long long wParam, const long long lParam, long long &result) override;
			void OnPasteString(const MessagePasteString &m) override;

			CWindowListener(CForm *form);
			virtual ~CWindowListener() = default;
		};

		class CFormTransform :public CTransform
		{
		private:
			IForm *m_pForm;
		public:
			float getTx() const override;
			float getTy() const override;
			const Mat4f &getMatrix() override;
			const Mat4f &getMatrixInversed() override;
			const Mat4f &getMatrixTranslate() override;
			const Mat4f &getMatrixScale() override;
			const Mat4f &getMatrixRotate() override;
			const nitisa::Transform &getTransform() override;
			bool isTranslateIdentity() const override;
			bool isScaleIdentity() const override;
			bool isRotateIdentity() const override;
			bool isIdentity() const override;

			bool setTx(const float value) override;
			bool setTy(const float value) override;
			bool setTz(const float value) override;
			bool setSx(const float value) override;
			bool setSy(const float value) override;
			bool setSz(const float value) override;
			bool setRx(const float value) override;
			bool setRy(const float value) override;
			bool setRz(const float value) override;
			bool setTransformOrder(const TransformOrder value) override;
			bool setRotateOrder(const RotateOrder value) override;
			bool setTransform(const nitisa::Transform &value) override;

			bool Translate(const float tx, const float ty, const float tz) override;
			bool Scale(const float sx, const float sy, const float sz) override;
			bool Rotate(const float rx, const float ry, const float rz) override;
			bool Transform(const float tx, const float ty, const float tz, const float sx, const float sy, const float sz, const float rx, const float ry, const float rz) override;

			void Release() override;

			CFormTransform(IForm *form);
		};

		class CTimerListener :public virtual ITimerListener
		{
		private:
			CForm *m_pForm;
		public:
			void NotifyOnTimer(const PlatformHandle id) override;

			CTimerListener(CForm *form);
		};

		class CTransformControlsListener :public virtual IFeedbackExListener
		{
		private:
			CForm *m_pForm;
		public:
			void NotifyOnBeforeChange() override;
			void NotifyOnBeforeChange(bool &allowed) override;
			void NotifyOnAfterChange() override;

			CTransformControlsListener(CForm *form);
		};

		class CFontListener :public virtual IFeedbackExListener
		{
		private:
			CForm *m_pForm;
		public:
			void NotifyOnBeforeChange() override;
			void NotifyOnBeforeChange(bool &allowed) override;
			void NotifyOnAfterChange() override;

			CFontListener(CForm *form);
		};
	private:
		IWindow *m_pWindow;
		IRenderer *m_pRenderer;
		IHint *m_pHint;
		IStyle *m_pStyle;
		IFont *m_pFont;
		ICaret *m_pCaret;
		IControl *m_pFocusedControl;
		IControl *m_pFocusedControlOld;
		IControl *m_pHoveredControl;
		IControl *m_pActiveControl;
		std::vector<IControl*> m_aControls;
		std::vector<IControl*> m_aCaptureKeyboardControls;
		std::vector<IDialogBox*> m_aActiveDialogBoxes;
		std::vector<IControl*> m_aModalControls;
		std::vector<CAPTURE_MOUSE> m_aCaptureMouseControls;
		std::vector<IComponent*> m_aComponents;
		std::vector<FormHotkey> m_aHotkeys;
		std::vector<ITask*> m_aTasks;
		std::vector<MESSAGE_LISTENER> m_aMessageListeners;
		CFormTransform *m_pTransform;
		ITransform *m_pTransformControls;
		CursorType m_eCursor;
		String m_sHintText;
		float m_fHintDelay;
		PointF m_sHintShift;
		Color m_sBackgroundColor;
		bool m_bShowHint;
		bool m_bFocusByLMB;
		bool m_bFocusByMMB;
		bool m_bFocusByRMB;
		bool m_bFocusByTab;
		bool m_bInterceptEnabled;
		RectF m_sBorderWidth;
		RectF m_sPadding;
		IControl *m_pInputControl;
		Point m_sDPI;
		IFormListener *m_pListener;

		IFormService *m_pService;
		int m_iRepaintLockCount;
		Rect m_sRepaintRect;
		bool m_bRepaintRequired;
		bool m_bIsTrackingMouseLeave;
		Rect m_sOldClientRect;
		bool m_bTabDownProcessed; // Indicate whether special TAB key was processed in previous notification(like in key down)
		bool m_bIgnoreTransformControls;
		bool m_bIgnoreCaret;
		bool m_bIgnoreFont;
		PlatformHandle m_hTimerHintDelay;
		bool m_bDestroying;
		bool m_bHintShown;
		bool m_bAcceptDragAndDrop;
		CWindowListener *m_pWindowListener;
		CreateParams m_sCreateParams;
		bool m_bTasksRunning;
		bool m_bRendering;
		CTimerListener m_cTimerListener;
		CTransformControlsListener m_cTransformControlsListener;
		CFontListener m_cFontListener;

		void CopyFont(IFont *dest, IFontProperties *src);
		void CopyTransform(ITransform *dest, ITransform *src);
		void CopyCaret(ICaret *dest, ICaret *src);
		void GenerateComponentName(IComponent *component);
		void SetFormRecursively(IControl *control, IForm *form, const bool static_tab_order);
		void GenerateNameRecursively(IControl *control);
		IControl *SearchPrevControl(IControl *control, const bool tab_stop_only);
		IControl *SearchNextControl(IControl *control, const bool tab_stop_only);
		void EnumControls(std::vector<IControl*> &controls, IControl *control, IControl *exclude, const bool tab_stop_only);
		void Render();
		bool ProcessTabDown(const Key key);
		void ProcessDownHotkeys(const Key key);
		void ProcessUpHotkeys(const Key key);
		bool setFocusedControl(IControl *value, const FocusedBy focused_by, const bool activate_dialog_box);
		void InitializeWindow();
		void DoOnChangeModalControl();
		
		bool InterceptSetCursor(IControl *parent, IControl *control);
		IControl *InterceptMouseHover(IControl *parent, IControl *control);
		bool InterceptShowHint(IControl *parent, IControl *control, String &hint);
		bool InterceptHotkeys(IControl *parent, IControl *control, const MessageHotkey &m);
		bool InterceptKeyDown(IControl *parent, IControl *control, const MessageKey &m);
		bool InterceptKeyUp(IControl *parent, IControl *control, const MessageKey &m);
		bool InterceptChar(IControl *parent, IControl *control, const MessageChar &m);
		bool InterceptDeadChar(IControl *parent, IControl *control, const MessageChar &m);
		bool InterceptMouseMove(IControl *parent, IControl *control, const MessageMouse &m);
		bool InterceptLeftMouseButtonDown(IControl *parent, IControl *control, const MessageMouse &m);
		bool InterceptLeftMouseButtonUp(IControl *parent, IControl *control, const MessageMouse &m);
		bool InterceptLeftMouseButtonDoubleClick(IControl *parent, IControl *control, const MessageMouse &m);
		bool InterceptMiddleMouseButtonDown(IControl *parent, IControl *control, const MessageMouse &m);
		bool InterceptMiddleMouseButtonUp(IControl *parent, IControl *control, const MessageMouse &m);
		bool InterceptMiddleMouseButtonDoubleClick(IControl *parent, IControl *control, const MessageMouse &m);
		bool InterceptRightMouseButtonDown(IControl *parent, IControl *control, const MessageMouse &m);
		bool InterceptRightMouseButtonUp(IControl *parent, IControl *control, const MessageMouse &m);
		bool InterceptRightMouseButtonDoubleClick(IControl *parent, IControl *control, const MessageMouse &m);
		bool InterceptMouseVerticalWheel(IControl *parent, IControl *control, const MessageMouseWheel &m);
		bool InterceptMouseHorizontalWheel(IControl *parent, IControl *control, const MessageMouseWheel &m);
		bool InterceptDropFiles(IControl *parent, IControl *control, const MessageDropFiles &m);
		IControl *InterceptFocus(IControl *parent, IControl *control, const FocusedBy focused_by);
	public:
	#ifdef _DEBUG
		void(*OnRender)(IForm *sender, const float fps); // Event called when actual rendering occurs
	#endif

		IRenderer *getRenderer() override;
		IHint *getHint() override;
		IStyle *getStyle() override;
		IFont *getFont() override;
		ICaret *getCaret() override;
		IControl *getModalControl() override;
		IControl *getFocusedControl() override;
		IControl *getCaptureKeyboardControl() override;
		IControl *getCaptureMouseControl() override;
		IControl *getHoveredControl() override;
		IControl *getActiveControl() override;
		IControl *getInputControl() override;
		int getControlCount(const bool total = false) override;
		IControl *getControl(const int index) override;
		IControl *getControl(const String &name) override;
		IControl *getControl(const PointF &position) override;
		int getControlIndex(IControl *control) override;
		int getComponentCount() override;
		IComponent *getComponent(const int index) override;
		IComponent *getComponent(const String &name) override;
		int getComponentIndex(IComponent *component) override;
		ITransform *getTransform() override;
		ITransform *getTransformControls() override;
		CursorType getCursor() override;
		String getHintText() override;
		float getHintDelay() override;
		PointF getHintShift() override;
		Color getBackgroundColor() override;
		bool isShowHint() override;
		bool isFocusByLMB() override;
		bool isFocusByMMB() override;
		bool isFocusByRMB() override;
		bool isFocusByTab() override;
		bool isInterceptEnable() override;
		int getTaskCount() override;
		ITask *getTask(const int index) override;
		RectF getBorderWidth() override;
		RectF getPadding() override;
		Point getDPI() override;
		IDialogBox *getActiveDialogBox() override;
		IFormListener *getListener() override;

		// Window getters
		bool isVisible() override;
		bool isEnabled() override;
		bool isAcceptDragAndDrop() override;
		bool isAcceptDropFiles() override;
		String getCaption() override;
		Rect getRect() override;
		Point getSize() override;
		Point getPosition() override;
		int getLeft() override;
		int getTop() override;
		int getWidth() override;
		int getHeight() override;
		Rect getClientRect() override;
		Point getClientSize() override;
		int getClientWidth() override;
		int getClientHeight() override;
		WindowState getState() override;
		CreateParams getCreateParams() override;
		bool hasBorder() override;
		bool hasCaption() override;
		bool hasDialogFrame() override;
		bool hasHorizontalScroll() override;
		bool hasVerticalScroll() override;
		bool hasMaximizeBox() override;
		bool hasMinimizeBox() override;
		bool hasSizeBox() override;
		bool hasSystemMenu() override;
		bool hasClientEdge() override;
		bool hasContextHelp() override;
		bool hasDialogModalFrame() override;
		bool hasStaticEdge() override;
		bool hasWindowEdge() override;
		bool isPopup() override;
		bool isTabStop() override;
		bool isMDIChild() override;
		bool isToolWindow() override;
		bool isTopMost() override;

		bool setName(const String &value) override;
		bool setHint(IHint *value) override;
		bool setStyle(IStyle *value) override;
		bool setFont(IFont *value, const bool copy = true) override;
		bool setCaret(ICaret *value) override;
		bool setModalControl(IControl *value) override;
		bool setFocusedControl(IControl *value) override;
		bool setActiveControl(IControl *value) override;
		bool setInputControl(IControl *value) override;
		bool setTransformControls(ITransform *value) override;
		bool setCursor(const CursorType value) override;
		bool setHintText(const String &value) override;
		bool setHintDelay(const float value) override;
		bool setHintShift(const PointF &value) override;
		bool setBackgroundColor(const Color &value) override;
		bool setShowHint(const bool value) override;
		bool setFocusByLMB(const bool value) override;
		bool setFocusByRMB(const bool value) override;
		bool setFocusByMMB(const bool value) override;
		bool setFocusByTab(const bool value) override;
		bool setInterceptEnable(const bool value) override;
		bool setBorderWidth(const RectF &value) override;
		bool setPadding(const RectF &value) override;
		void setService(IFormService *value, const bool release_prev) override final;
		bool setDPI(const Point &value) override;
		bool setActiveDialogBox(IDialogBox *value) override;
		void setListener(IFormListener *value) override;

		// Window setters
		bool setVisible(const bool value) override;
		bool setEnabled(const bool value) override;
		bool setAcceptDrawAndDrop(const bool value) override;
		bool setAcceptDropFiles(const bool value) override;
		bool setCaption(const String &value) override;
		bool setRect(const Rect &value) override;
		bool setSize(const Point &value) override;
		bool setPosition(const Point &value) override;
		bool setLeft(const int value) override;
		bool setTop(const int value) override;
		bool setWidth(const int value) override;
		bool setHeight(const int value) override;
		bool setClientSize(const Point &value) override;
		bool setState(const WindowState value) override;
		bool setModalResult(const ModalResult value) override;
		bool setWindowPosition(const WindowPosition value) override;
		void setCreateParams(const CreateParams &value) override;
		bool setHasBorder(const bool value) override;
		bool setHasCaption(const bool value) override;
		bool setHasDialogFrame(const bool value) override;
		bool setHasHorizontalScroll(const bool value) override;
		bool setHasVerticalScroll(const bool value) override;
		bool setHasMaximizeBox(const bool value) override;
		bool setHasMinimizeBox(const bool value) override;
		bool setHasSizeBox(const bool value) override;
		bool setHasSystemMenu(const bool value) override;
		bool setHasClientEdge(const bool value) override;
		bool setHasContextHelp(const bool value) override;
		bool setHasDialogModalFrame(const bool value) override;
		bool setHasStaticEdge(const bool value) override;
		bool setHasWindowEdge(const bool value) override;
		bool setIsPopup(const bool value) override;
		bool setIsTabStop(const bool value) override;
		bool setIsMDIChild(const bool value) override;
		bool setIsToolWindow(const bool value) override;
		bool setIsTopMost(const bool value) override;
		
		bool AttachComponent(IComponent *component) override;
		bool DeleteComponent(const int index) override;
		bool DeleteComponent(IComponent *component) override;
		bool DeleteComponents() override;
		bool DetachComponent(IComponent *component) override;

		bool AttachControl(IControl *control) override;
		bool InsertControl(IControl *control, const int before) override;
		bool DeleteControl(const int index) override;
		bool DeleteControl(IControl *control) override;
		bool DeleteControls() override;
		bool DetachControl(IControl *control) override;
		IControl *FindControl(const String &name, IControl *exclude = nullptr) override;
		bool FocusPrevControl() override;
		bool FocusNextControl() override;
		bool CaptureKeyboard(IControl *control) override;
		bool CaptureMouse(IControl *control, const bool system_capture) override;
		void ReleaseCaptureKeyboard() override;
		void ReleaseCaptureMouse() override;
		void UpdateHoveredControl() override;
		void ReleaseModal() override;

		void Release() override;

		void LockRepaint() override;
		void UnlockRepaint() override;
		void Repaint() override;
		void Refresh() override;
		void Repaint(const Rect &rect, const bool force = false) override;
		void Repaint(const RectF &rect, const bool force = false) override;

		bool RegisterHotkey(const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down) override;
		bool UnregisterHotkey(const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down) override;
		bool UnregisterHotkeys() override;

		IFormService *QueryService() override;

		// Window actions
		bool Show() override;
		ModalResult ShowModal() override;
		bool Hide() override;
		PlatformHandle CreateTimer(ITimerListener *listener, const float interval) override;
		bool DeleteTimer(const PlatformHandle id) override;
		void DeleteTimers() override;
		bool ResetTimer(const PlatformHandle id, const float interval) override;
		bool Maximize() override;
		bool Minimize() override;
		bool Restore() override;
		bool CopyStringToClipboard(const String &str) override;
		bool CopyStringFromClipboard() override;
		Rect ScreenToClient(const Rect &rect) override;
		Point ScreenToClient(const Point &pos) override;
		Rect ClientToScreen(const Rect &rect) override;
		Point ClientToScreen(const Point &pos) override;
		bool Close() override;

		// Tasks
		bool AddTask(ITask *task) override;
		bool DeleteTask(const int index) override;
		bool DeleteTask(ITask *task) override;
		void DeleteTasks() override;
		void RunTasks() override;

		// Hint actions
		bool ShowHint(const String &text, const Point &position) override;
		bool ShowHint(IControl *control, const PointF &position) override;

		/**
		Constructor
		@param class_name Form class name(without "C" at the beginning)
		@param window Window for the form. Could be nullptr and set using service later
		@param renderer Renderer for the form. Could be nullptr and set using service later
		@param params Creation parameters to overwrite default ones if specified
		*/
		CForm(const String &class_name, IWindow *window, IRenderer *renderer, const CreateParams *params = nullptr);
		~CForm() override;
	};
}