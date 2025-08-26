// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace fb
	{
	#pragma region CFormTransform
		CFormEmpty::CFormTransform::CFormTransform(IForm *form, IFeedbackExListener *listener) :
			CTransform(listener),
			m_pForm{ form },
			m_sTransform{ 0, 0, 0, 1, 1, 1, 0, 0, 0, RotateOrder::ZYX, TransformOrder::TSR }
		{

		}

		void CFormEmpty::CFormTransform::Release()
		{
			// Do nothing
		}

		float CFormEmpty::CFormTransform::getTx() const
		{
			return (float)m_pForm->getLeft();
		}

		float CFormEmpty::CFormTransform::getTy() const
		{
			return (float)m_pForm->getTop();
		}

		const Mat4f &CFormEmpty::CFormTransform::getMatrix()
		{
			return Identity;
		}

		const Mat4f &CFormEmpty::CFormTransform::getMatrixInversed()
		{
			return Identity;
		}

		const Mat4f &CFormEmpty::CFormTransform::getMatrixTranslate()
		{
			return Identity;
		}

		const Mat4f &CFormEmpty::CFormTransform::getMatrixScale()
		{
			return Identity;
		}

		const Mat4f &CFormEmpty::CFormTransform::getMatrixRotate()
		{
			return Identity;
		}

		const nitisa::Transform &CFormEmpty::CFormTransform::getTransform()
		{
			m_sTransform.Tx = (float)m_pForm->getLeft();
			m_sTransform.Ty = (float)m_pForm->getTop();
			return m_sTransform;
		}

		bool CFormEmpty::CFormTransform::isTranslateIdentity() const
		{
			return m_pForm->getLeft() == 0 && m_pForm->getTop() == 0;
		}

		bool CFormEmpty::CFormTransform::isScaleIdentity() const
		{
			return true;
		}

		bool CFormEmpty::CFormTransform::isRotateIdentity() const
		{
			return true;
		}

		bool CFormEmpty::CFormTransform::isIdentity() const
		{
			return m_pForm->getLeft() == 0 && m_pForm->getTop() == 0;
		}

		bool CFormEmpty::CFormTransform::setTx(const float value)
		{
			return m_pForm->setLeft(ntl::Round<int>(value));
		}

		bool CFormEmpty::CFormTransform::setTy(const float value)
		{
			return m_pForm->setTop(ntl::Round<int>(value));
		}

		bool CFormEmpty::CFormTransform::setTz(const float value)
		{
			return false;
		}

		bool CFormEmpty::CFormTransform::setSx(const float value)
		{
			return false;
		}

		bool CFormEmpty::CFormTransform::setSy(const float value)
		{
			return false;
		}

		bool CFormEmpty::CFormTransform::setSz(const float value)
		{
			return false;
		}

		bool CFormEmpty::CFormTransform::setRx(const float value)
		{
			return false;
		}

		bool CFormEmpty::CFormTransform::setRy(const float value)
		{
			return false;
		}

		bool CFormEmpty::CFormTransform::setRz(const float value)
		{
			return false;
		}

		bool CFormEmpty::CFormTransform::setTransformOrder(const TransformOrder value)
		{
			return false;
		}

		bool CFormEmpty::CFormTransform::setRotateOrder(const RotateOrder value)
		{
			return false;
		}

		bool CFormEmpty::CFormTransform::setTransform(const nitisa::Transform &value)
		{
			return m_pForm->setPosition(Point{ ntl::Round<int>(value.Tx), ntl::Round<int>(value.Ty) });
		}

		bool CFormEmpty::CFormTransform::Translate(const float tx, const float ty, const float tz)
		{
			return m_pForm->setPosition(Point{ ntl::Round<int>(tx), ntl::Round<int>(ty) });
		}

		bool CFormEmpty::CFormTransform::Scale(const float sx, const float sy, const float sz)
		{
			return false;
		}

		bool CFormEmpty::CFormTransform::Rotate(const float rx, const float ry, const float rz)
		{
			return false;
		}

		bool CFormEmpty::CFormTransform::Transform(const float tx, const float ty, const float tz, const float sx, const float sy, const float sz, const float rx, const float ry, const float rz)
		{
			return m_pForm->setPosition(Point{ ntl::Round<int>(tx), ntl::Round<int>(ty) });
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CFormEmpty::CFormEmpty(CFormMain *form) :
			m_pForm{ form },
			m_cTransform{ this, nullptr },
			m_cTransformControls{ nullptr },
			m_sBackgroundColor{ 240, 240, 240, 255 },
			m_pStyle{ nullptr },
			m_fHintDelay{ 0.5f },
			m_bShowHint{ true },
			m_sHintShift{ 0, 20 },
			m_sBorderWidth{ 0, 0, 0, 0 },
			m_sPadding{ 0, 0, 0, 0 },
			OnBackgroundChange{ nullptr },
			OnPaddingChange{ nullptr },
			HasSettings{ false }
		{
			m_sName = m_sClassName = L"Form1";

			m_sCreateParams.Caption = L"Form1";
			m_sCreateParams.Position = Point{ 0, 0 };
			m_sCreateParams.Size = Point{ 640, 480 };

			// Events from child controls
			OnChildStyleChange = nullptr;
			OnChildFontChange = nullptr;
			OnChildTransform = nullptr;
			OnChildResize = nullptr;
			OnChildShow = nullptr;
			OnChildHide = nullptr;
			OnChildEnable = nullptr;
			OnChildDisable = nullptr;
			OnChildBeforeTransform = nullptr;
			OnChildBeforeResize = nullptr;
			OnChildBeforeShow = nullptr;
			OnChildBeforeHide = nullptr;
			OnChildBeforeEnable = nullptr;
			OnChildBeforeDisable = nullptr;

			// State change events
			OnResize = nullptr;
			OnTransform = nullptr;
			OnTransformControls = nullptr;
			OnStyleChange = nullptr;
			OnFontChange = nullptr;

			// Component events
			OnComponentAttach = nullptr;
			OnComponentDetach = nullptr;

			// Control events
			OnControlAttach = nullptr;
			OnControlDetach = nullptr;
			OnControlSetModal = nullptr;
			OnControlKillModal = nullptr;
			OnControlSetFocus = nullptr;
			OnControlKillFocus = nullptr;
			OnControlMouseHover = nullptr;
			OnControlMouseLeave = nullptr;
			OnControlSetCaptureKeyboard = nullptr;
			OnControlKillCaptureKeyboard = nullptr;
			OnControlSetCaptureMouse = nullptr;
			OnControlKillCaptureMouse = nullptr;
			OnControlActivate = nullptr;
			OnControlDeactivate = nullptr;

			// Paint events
			OnPaint = nullptr;

			// Keyboard input events
			OnKeyDown = nullptr;
			OnKeyUp = nullptr;
			OnChar = nullptr;
			OnDeadChar = nullptr;

			// Mouse input events
			OnMouseHover = nullptr;
			OnMouseLeave = nullptr;
			OnMouseMove = nullptr;
			OnLeftMouseButtonDown = nullptr;
			OnLeftMouseButtonUp = nullptr;
			OnLeftMouseButtonDoubleClick = nullptr;
			OnRightMouseButtonDown = nullptr;
			OnRightMouseButtonUp = nullptr;
			OnRightMouseButtonDoubleClick = nullptr;
			OnMiddleMouseButtonDown = nullptr;
			OnMiddleMouseButtonUp = nullptr;
			OnMiddleMouseButtonDoubleClick = nullptr;
			OnMouseVerticalWheel = nullptr;
			OnMouseHorizontalWheel = nullptr;

			// Other input events
			OnDropFiles = nullptr;
			OnHotkey = nullptr;
			OnGestureZoom = nullptr;
			OnGesturePan = nullptr;
			OnGestureRotate = nullptr;
			OnGestureTwoFingerTap = nullptr;
			OnGesturePressAndTap = nullptr;
			OnGestureNotify = nullptr;
			OnTouch = nullptr;

			// Application events
			OnApplicationActivate = nullptr;
			OnApplicationDeactivate = nullptr;
			OnQueryEndSession = nullptr;
			OnQueryOpen = nullptr;
			OnEndSession = nullptr;
			OnDeviceModeChange = nullptr;
			OnTimeChange = nullptr;
			OnInputLanguageChangeRequest = nullptr;
			OnInputLanguageChange = nullptr;
			OnDisplayChange = nullptr;
			OnThemeChange = nullptr;
			OnClipboardUpdate = nullptr;

			// Window events
			OnDestroy = nullptr;
			OnActivate = nullptr;
			OnDeactivate = nullptr;
			OnSetFocus = nullptr;
			OnKillFocus = nullptr;
			OnEnable = nullptr;
			OnDisable = nullptr;
			OnClose = nullptr;
			OnShow = nullptr;
			OnHide = nullptr;
			OnMove = nullptr;
			OnRestore = nullptr;
			OnMinimize = nullptr;
			OnMaximize = nullptr;
			OnResizing = nullptr;
			OnMoving = nullptr;
			OnEnterSizeMove = nullptr;
			OnExitSizeMove = nullptr;
			OnHScroll = nullptr;
			OnVScroll = nullptr;
			OnLoseCapture = nullptr;
		}

		CFormEmpty::~CFormEmpty()
		{

		}

		void CFormEmpty::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Getters
		IRenderer *CFormEmpty::getRenderer()
		{
			return nullptr;
		}

		IHint *CFormEmpty::getHint()
		{
			return nullptr;
		}

		IStyle *CFormEmpty::getStyle()
		{
			return m_pStyle;
		}

		IFont *CFormEmpty::getFont()
		{
			return &m_cFont;
		}

		ICaret *CFormEmpty::getCaret()
		{
			return nullptr;
		}

		IControl *CFormEmpty::getModalControl()
		{
			return nullptr;
		}

		IControl *CFormEmpty::getFocusedControl()
		{
			return nullptr;
		}

		IControl *CFormEmpty::getCaptureKeyboardControl()
		{
			return nullptr;
		}

		IControl *CFormEmpty::getCaptureMouseControl()
		{
			return nullptr;
		}

		IControl *CFormEmpty::getHoveredControl()
		{
			return nullptr;
		}

		IControl *CFormEmpty::getActiveControl()
		{
			return nullptr;
		}

		int CFormEmpty::getControlCount(const bool total)
		{
			return 0;
		}

		IControl *CFormEmpty::getControl(const int index)
		{
			return nullptr;
		}

		IControl *CFormEmpty::getControl(const String &name)
		{
			return nullptr;
		}

		IControl *CFormEmpty::getControl(const PointF &position)
		{
			return nullptr;
		}

		int CFormEmpty::getControlIndex(IControl *control)
		{
			return -1;
		}

		int CFormEmpty::getComponentCount()
		{
			return 0;
		}

		IComponent *CFormEmpty::getComponent(const int index)
		{
			return nullptr;
		}

		IComponent *CFormEmpty::getComponent(const String &name)
		{
			return nullptr;
		}

		int CFormEmpty::getComponentIndex(IComponent *component)
		{
			return -1;
		}

		ITransform *CFormEmpty::getTransform()
		{
			return &m_cTransform;
		}

		ITransform *CFormEmpty::getTransformControls()
		{
			return &m_cTransformControls;
		}

		CursorType CFormEmpty::getCursor()
		{
			return CursorType::Arrow;
		}

		String CFormEmpty::getHintText()
		{
			return L"";
		}

		float CFormEmpty::getHintDelay()
		{
			return m_fHintDelay;
		}

		PointF CFormEmpty::getHintShift()
		{
			return m_sHintShift;
		}

		Color CFormEmpty::getBackgroundColor()
		{
			return m_sBackgroundColor;
		}

		RectF CFormEmpty::getBorderWidth()
		{
			return m_sBorderWidth;
		}

		RectF CFormEmpty::getPadding()
		{
			return m_sPadding;
		}

		bool CFormEmpty::isShowHint()
		{
			return m_bShowHint;
		}

		bool CFormEmpty::isFocusByLMB()
		{
			return true;
		}

		bool CFormEmpty::isFocusByRMB()
		{
			return true;
		}

		bool CFormEmpty::isFocusByMMB()
		{
			return true;
		}

		bool CFormEmpty::isFocusByTab()
		{
			return true;
		}

		bool CFormEmpty::isInterceptEnable()
		{
			return false;
		}

		bool CFormEmpty::isVisible()
		{
			return true;
		}

		bool CFormEmpty::isEnabled()
		{
			return true;
		}

		bool CFormEmpty::isAcceptDragAndDrop()
		{
			return false;
		}

		bool CFormEmpty::isAcceptDropFiles()
		{
			return false;
		}

		String CFormEmpty::getCaption()
		{
			return m_sCreateParams.Caption;
		}

		Rect CFormEmpty::getRect()
		{
			return Rect{ m_sCreateParams.Position.X, m_sCreateParams.Position.Y, m_sCreateParams.Position.X + m_sCreateParams.Size.X, m_sCreateParams.Position.Y + m_sCreateParams.Size.Y };
		}

		Point CFormEmpty::getSize()
		{
			return m_sCreateParams.Size;
		}

		Point CFormEmpty::getPosition()
		{
			return m_sCreateParams.Position;
		}

		int CFormEmpty::getLeft()
		{
			return m_sCreateParams.Position.X;
		}

		int CFormEmpty::getTop()
		{
			return m_sCreateParams.Position.Y;
		}

		int CFormEmpty::getWidth()
		{
			return m_sCreateParams.Size.X;
		}

		int CFormEmpty::getHeight()
		{
			return m_sCreateParams.Size.Y;
		}

		Rect CFormEmpty::getClientRect()
		{
			return getRect();
		}

		Point CFormEmpty::getClientSize()
		{
			return m_sCreateParams.Size;
		}

		int CFormEmpty::getClientWidth()
		{
			return m_sCreateParams.Size.X;
		}

		int CFormEmpty::getClientHeight()
		{
			return m_sCreateParams.Size.Y;
		}

		WindowState CFormEmpty::getState()
		{
			return WindowState::Normal;
		}

		CreateParams CFormEmpty::getCreateParams()
		{
			return m_sCreateParams;
		}

		int CFormEmpty::getTaskCount()
		{
			return 0;
		}

		ITask *CFormEmpty::getTask(const int index)
		{
			return nullptr;
		}

		bool CFormEmpty::hasBorder()
		{
			return false;
		}

		bool CFormEmpty::hasCaption()
		{
			return true;
		}

		bool CFormEmpty::hasDialogFrame()
		{
			return false;
		}

		bool CFormEmpty::hasHorizontalScroll()
		{
			return false;
		}

		bool CFormEmpty::hasVerticalScroll()
		{
			return false;
		}

		bool CFormEmpty::hasMaximizeBox()
		{
			return true;
		}

		bool CFormEmpty::hasMinimizeBox()
		{
			return true;
		}

		bool CFormEmpty::hasSizeBox()
		{
			return true;
		}

		bool CFormEmpty::hasSystemMenu()
		{
			return true;
		}

		bool CFormEmpty::hasClientEdge()
		{
			return true;
		}

		bool CFormEmpty::hasContextHelp()
		{
			return false;
		}

		bool CFormEmpty::hasDialogModalFrame()
		{
			return false;
		}

		bool CFormEmpty::hasStaticEdge()
		{
			return false;
		}

		bool CFormEmpty::hasWindowEdge()
		{
			return true;
		}

		bool CFormEmpty::isPopup()
		{
			return false;
		}

		bool CFormEmpty::isTabStop()
		{
			return false;
		}

		bool CFormEmpty::isMDIChild()
		{
			return false;
		}

		bool CFormEmpty::isToolWindow()
		{
			return false;
		}

		bool CFormEmpty::isTopMost()
		{
			return false;
		}

		IControl *CFormEmpty::getInputControl()
		{
			return nullptr;
		}

		Point CFormEmpty::getDPI()
		{
			return DesignDPI;
		}

		IDialogBox *CFormEmpty::getActiveDialogBox()
		{
			return nullptr;
		}

		IFormListener *CFormEmpty::getListener()
		{
			return nullptr;
		}
	#pragma endregion

	#pragma region Setters
		bool CFormEmpty::setName(const String &value)
		{
			m_sName = value;
			return true;
		}

		bool CFormEmpty::setHint(IHint *value)
		{
			return false;
		}

		bool CFormEmpty::setStyle(IStyle *value)
		{
			if (value != m_pStyle)
			{
				m_pStyle = value;
				if (OnStyleChange)
					OnStyleChange(m_pForm);
				return true;
			}
			return false;
		}

		bool CFormEmpty::setFont(IFont *value, const bool copy)
		{
			if (m_cFont.Copy(value))
			{
				if (OnFontChange)
					OnFontChange(m_pForm);
				return true;
			}
			return false;
		}

		bool CFormEmpty::setCaret(ICaret *value)
		{
			return false;
		}

		bool CFormEmpty::setModalControl(IControl *value)
		{
			return false;
		}

		bool CFormEmpty::setFocusedControl(IControl *value)
		{
			return false;
		}

		bool CFormEmpty::setActiveControl(IControl *value)
		{
			return false;
		}

		bool CFormEmpty::setTransformControls(ITransform *value)
		{
			return false;
		}

		bool CFormEmpty::setCursor(const CursorType value)
		{
			return false;
		}

		bool CFormEmpty::setHintText(const String &value)
		{
			return false;
		}

		bool CFormEmpty::setHintDelay(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fHintDelay))
			{
				m_fHintDelay = value;
				return true;
			}
			return false;
		}

		bool CFormEmpty::setHintShift(const PointF &value)
		{
			if (IsNotEqual(value, m_sHintShift))
			{
				m_sHintShift = value;
				return true;
			}
			return false;
		}

		bool CFormEmpty::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				if (OnBackgroundChange)
					OnBackgroundChange(m_pForm);
				return true;
			}
			return false;
		}

		bool CFormEmpty::setBorderWidth(const RectF &value)
		{
			if (IsNotEqual(value, m_sBorderWidth))
			{
				m_sBorderWidth = value;
				return true;
			}
			return false;
		}

		bool CFormEmpty::setPadding(const RectF &value)
		{
			if (IsNotEqual(value, m_sPadding))
			{
				m_sPadding = value;
				if (OnPaddingChange)
					OnPaddingChange(m_pForm);
				return true;
			}
			return false;
		}

		bool CFormEmpty::setShowHint(const bool value)
		{
			if (value != m_bShowHint)
			{
				m_bShowHint = value;
				return true;
			}
			return false;
		}

		bool CFormEmpty::setFocusByLMB(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setFocusByMMB(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setFocusByRMB(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setFocusByTab(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setInterceptEnable(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setVisible(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setEnabled(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setAcceptDrawAndDrop(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setAcceptDropFiles(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setCaption(const String &value)
		{
			m_sCreateParams.Caption = value;
			return true;
		}

		bool CFormEmpty::setRect(const Rect &value)
		{
			if (value.LeftTop != m_sCreateParams.Position || value.width() != m_sCreateParams.Size.X || value.height() != m_sCreateParams.Size.Y)
			{
				m_sCreateParams.Position = value.LeftTop;
				m_sCreateParams.Size.X = value.width();
				m_sCreateParams.Size.Y = value.height();
				return true;
			}
			return false;
		}

		bool CFormEmpty::setSize(const Point &value)
		{
			if (value != m_sCreateParams.Size)
			{
				m_sCreateParams.Size = value;
				return true;
			}
			return false;
		}

		bool CFormEmpty::setPosition(const Point &value)
		{
			if (value != m_sCreateParams.Position)
			{
				m_sCreateParams.Position = value;
				return true;
			}
			return false;
		}

		bool CFormEmpty::setLeft(const int value)
		{
			if (value != m_sCreateParams.Position.X)
			{
				m_sCreateParams.Position.X = value;
				return true;
			}
			return false;
		}

		bool CFormEmpty::setTop(const int value)
		{
			if (value != m_sCreateParams.Position.Y)
			{
				m_sCreateParams.Position.Y = value;
				return true;
			}
			return false;
		}

		bool CFormEmpty::setWidth(const int value)
		{
			if (value != m_sCreateParams.Size.X)
			{
				m_sCreateParams.Size.X = value;
				return true;
			}
			return false;
		}

		bool CFormEmpty::setHeight(const int value)
		{
			if (value != m_sCreateParams.Size.Y)
			{
				m_sCreateParams.Size.Y = value;
				return true;
			}
			return false;
		}

		bool CFormEmpty::setClientSize(const Point &value)
		{
			return setSize(value);
		}

		bool CFormEmpty::setState(const WindowState value)
		{
			return false;
		}

		bool CFormEmpty::setModalResult(const ModalResult value)
		{
			return false;
		}

		bool CFormEmpty::setWindowPosition(const WindowPosition value)
		{
			return false;
		}

		void CFormEmpty::setCreateParams(const CreateParams &value)
		{
			m_sCreateParams = value;
		}

		bool CFormEmpty::setHasBorder(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setHasCaption(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setHasDialogFrame(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setHasHorizontalScroll(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setHasVerticalScroll(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setHasMaximizeBox(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setHasMinimizeBox(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setHasSizeBox(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setHasSystemMenu(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setHasClientEdge(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setHasContextHelp(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setHasDialogModalFrame(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setHasStaticEdge(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setHasWindowEdge(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setIsPopup(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setIsTabStop(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setIsMDIChild(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setIsToolWindow(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setIsTopMost(const bool value)
		{
			return false;
		}

		bool CFormEmpty::setInputControl(IControl *value)
		{
			return false;
		}

		void CFormEmpty::setService(IFormService *value, const bool release_prev)
		{

		}

		bool CFormEmpty::setDPI(const Point &value)
		{
			return false;
		}

		bool CFormEmpty::setActiveDialogBox(IDialogBox *value)
		{
			return false;
		}

		void CFormEmpty::setListener(IFormListener *value)
		{

		}
	#pragma endregion

	#pragma region Components
		bool CFormEmpty::AttachComponent(IComponent *component)
		{
			return false;
		}

		bool CFormEmpty::DeleteComponent(const int index)
		{
			return false;
		}

		bool CFormEmpty::DeleteComponent(IComponent *component)
		{
			return false;
		}

		bool CFormEmpty::DeleteComponents()
		{
			return false;
		}

		bool CFormEmpty::DetachComponent(IComponent *component)
		{
			return false;
		}
	#pragma endregion

	#pragma region Constrols
		bool CFormEmpty::AttachControl(IControl *control)
		{
			return false;
		}

		bool CFormEmpty::InsertControl(IControl *control, const int before)
		{
			return false;
		}

		bool CFormEmpty::DeleteControl(const int index)
		{
			return false;
		}

		bool CFormEmpty::DeleteControl(IControl *control)
		{
			return false;
		}

		bool CFormEmpty::DeleteControls()
		{
			return false;
		}

		bool CFormEmpty::DetachControl(IControl *control)
		{
			return false;
		}

		IControl *CFormEmpty::FindControl(const String &name, IControl *exclude)
		{
			return nullptr;
		}

		bool CFormEmpty::FocusPrevControl()
		{
			return false;
		}

		bool CFormEmpty::FocusNextControl()
		{
			return false;
		}

		bool CFormEmpty::CaptureKeyboard(IControl *control)
		{
			return false;
		}

		bool CFormEmpty::CaptureMouse(IControl *control, const bool system_capture)
		{
			return false;
		}

		void CFormEmpty::ReleaseCaptureKeyboard()
		{

		}

		void CFormEmpty::ReleaseCaptureMouse()
		{

		}

		void CFormEmpty::UpdateHoveredControl()
		{

		}

		void CFormEmpty::ReleaseModal()
		{

		}
	#pragma endregion

	#pragma region Paint
		void CFormEmpty::LockRepaint()
		{

		}

		void CFormEmpty::UnlockRepaint()
		{

		}

		void CFormEmpty::Repaint()
		{

		}

		void CFormEmpty::Refresh()
		{

		}


		void CFormEmpty::Repaint(const Rect &rect, const bool force)
		{

		}

		void CFormEmpty::Repaint(const RectF &rect, const bool force)
		{

		}
	#pragma endregion

	#pragma region Hotkeys
		bool CFormEmpty::RegisterHotkey(const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down)
		{
			return false;
		}

		bool CFormEmpty::UnregisterHotkey(const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down)
		{
			return false;
		}

		bool CFormEmpty::UnregisterHotkeys()
		{
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		IFormService *CFormEmpty::QueryService()
		{
			return nullptr;
		}

		bool CFormEmpty::Show()
		{
			return false;
		}

		ModalResult CFormEmpty::ShowModal()
		{
			return ModalResult::None;
		}

		bool CFormEmpty::Hide()
		{
			return false;
		}

		PlatformHandle CFormEmpty::CreateTimer(ITimerListener *listener, const float interval)
		{
			return 0;
		}

		bool CFormEmpty::DeleteTimer(const PlatformHandle id)
		{
			return false;
		}

		void CFormEmpty::DeleteTimers()
		{

		}

		bool CFormEmpty::ResetTimer(const PlatformHandle id, const float interval)
		{
			return false;
		}

		bool CFormEmpty::Maximize()
		{
			return false;
		}

		bool CFormEmpty::Minimize()
		{
			return false;
		}

		bool CFormEmpty::Restore()
		{
			return false;
		}

		bool CFormEmpty::Close()
		{
			return false;
		}

		bool CFormEmpty::CopyStringToClipboard(const String &str)
		{
			return false;
		}

		bool CFormEmpty::CopyStringFromClipboard()
		{
			return false;
		}

		Rect CFormEmpty::ScreenToClient(const Rect &rect)
		{
			return rect;
		}

		Point CFormEmpty::ScreenToClient(const Point &pos)
		{
			return pos;
		}

		Rect CFormEmpty::ClientToScreen(const Rect &rect)
		{
			return rect;
		}

		Point CFormEmpty::ClientToScreen(const Point &pos)
		{
			return pos;
		}
	#pragma endregion

	#pragma region Tasks
		bool CFormEmpty::AddTask(ITask *task)
		{
			return false;
		}

		bool CFormEmpty::DeleteTask(const int index)
		{
			return false;
		}

		bool CFormEmpty::DeleteTask(ITask *task)
		{
			return false;
		}

		void CFormEmpty::DeleteTasks()
		{

		}

		void CFormEmpty::RunTasks()
		{

		}
	#pragma endregion

	#pragma region Hint actions
		bool CFormEmpty::ShowHint(const String &text, const Point &position)
		{
			return false;
		}

		bool CFormEmpty::ShowHint(IControl *control, const PointF &position)
		{
			return false;
		}
	#pragma endregion
	}
}