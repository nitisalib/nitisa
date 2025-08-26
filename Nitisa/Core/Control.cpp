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
#pragma region CTransformListener
	CControl::CTransformListener::CTransformListener(CControl *control) :
		m_pControl{ control }
	{

	}

	void CControl::CTransformListener::NotifyOnBeforeChange()
	{
		if (!m_pControl->m_bIgnoreTransform)
		{
			if (m_pControl->CheckTransformAllowed())
			{
				if (m_pControl->getForm())
					m_pControl->getForm()->LockRepaint();
				m_pControl->Repaint(true);
			}
		}
	}

	void CControl::CTransformListener::NotifyOnBeforeChange(bool &allowed)
	{
		if (!m_pControl->m_bIgnoreTransform)
		{
			if (m_pControl->CheckTransformAllowed())
			{
				if (m_pControl->getForm())
					m_pControl->getForm()->LockRepaint();
				m_pControl->Repaint(true);
			}
			else
				allowed = false;
		}
	}

	void CControl::CTransformListener::NotifyOnAfterChange()
	{
		if (!m_pControl->m_bIgnoreTransform)
		{
			m_pControl->NotifyTransform();
			if (m_pControl->m_eAlign != Align::None)
			{
				if (m_pControl->getParent())
					m_pControl->getParent()->QueryService()->AlignControls();
				else if (m_pControl->getForm())
					m_pControl->getForm()->QueryService()->AlignControls();
			}
			m_pControl->Repaint(true);
			if (m_pControl->getForm())
			{
				m_pControl->getForm()->UpdateHoveredControl();
				m_pControl->getForm()->UnlockRepaint();
			}
		}
	}
#pragma endregion

#pragma region CTransformControlsListener
	CControl::CTransformControlsListener::CTransformControlsListener(CControl *control) :
		m_pControl{ control }
	{

	}

	void CControl::CTransformControlsListener::NotifyOnBeforeChange()
	{
		if (!m_pControl->m_bIgnoreTransformControls)
		{
			if (m_pControl->getForm())
				m_pControl->getForm()->LockRepaint();
			m_pControl->Repaint(true);
		}
	}

	void CControl::CTransformControlsListener::NotifyOnBeforeChange(bool &allowed)
	{
		if (!m_pControl->m_bIgnoreTransformControls)
		{
			if (m_pControl->getForm())
				m_pControl->getForm()->LockRepaint();
			m_pControl->Repaint(true);
		}
	}

	void CControl::CTransformControlsListener::NotifyOnAfterChange()
	{
		if (!m_pControl->m_bIgnoreTransformControls)
		{
			m_pControl->NotifyTransformControls();
			m_pControl->Repaint(true);
			if (m_pControl->getForm())
			{
				m_pControl->getForm()->UpdateHoveredControl();
				m_pControl->getForm()->UnlockRepaint();
			}
		}
	}
#pragma endregion

#pragma region CFontListener
	CControl::CFontListener::CFontListener(CControl *control) :
		m_pControl{ control }
	{

	}

	void CControl::CFontListener::NotifyOnBeforeChange()
	{
		if (!m_pControl->m_bIgnoreFont)
		{
			if (m_pControl->getForm())
				m_pControl->getForm()->LockRepaint();
			m_pControl->Repaint(true);
		}
	}

	void CControl::CFontListener::NotifyOnBeforeChange(bool &allowed)
	{
		if (!m_pControl->m_bIgnoreFont)
		{
			if (m_pControl->getForm())
				m_pControl->getForm()->LockRepaint();
			m_pControl->Repaint(true);
		}
	}

	void CControl::CFontListener::NotifyOnAfterChange()
	{
		if (!m_pControl->m_bIgnoreFont)
		{
			m_pControl->m_bUseParentFont = false;
			m_pControl->NotifyFontChange();
			m_pControl->Repaint(true);
			if (m_pControl->getForm())
			{
				m_pControl->getForm()->UpdateHoveredControl();
				m_pControl->getForm()->UnlockRepaint();
			}
		}
	}
#pragma endregion

#pragma region Constructor & destructor
	CControl::CControl(
		const String &class_name,
		const bool accept_form,
		const bool accept_control,
		const bool accept_controls,
		const bool accept_focus,
		const bool accept_modal,
		const bool tab_stop,
		const Point &design_dpi) :
		CComponent(class_name),
		m_pParent{ nullptr },
		m_pStyle{ nullptr },
		m_pFont{ nullptr },
		m_pTransform{ nullptr },
		m_pTransformControls{ nullptr },
		m_eAlign{ Align::None },
		m_sConstraints{ 0, 0, 0, 0 },
		m_sSize{ 0, 0 },
		m_sSizeRequested{ 0, 0 },
		m_iZIndex{ 0 },
		m_eCursor{ CursorType::Arrow },
		m_iTabOrder{ 0 },
		m_fHintDelay{ 0 },
		m_sHintShift{ 0, 0 },
		m_bWantTabs{ false },
		m_bTabStop{ tab_stop },
		m_bDeactivateByTab{ false },
		m_bVisible{ true },
		m_bEnabled{ true },
		m_bShowHint{ true },
		m_bUseParentStyle{ true },
		m_bUseParentFont{ true },
		m_bUseParentShowHint{ true },
		m_bUseParentHintDelay{ true },
		m_bUseParentHintShift{ true },
		m_pService{ nullptr },
		m_bIgnoreTransform{ false },
		m_bIgnoreTransformControls{ false },
		m_bIgnoreFont{ false },
		m_bRepaintedBeforeFontChange{ false },
		m_bAcceptForm{ accept_form },
		m_bAcceptControl{ accept_control },
		m_bAcceptControls{ accept_controls },
		m_bAcceptFocus{ accept_focus },
		m_bAcceptModal{ accept_modal },
		m_sDPI{ design_dpi },
		m_bStaticTabOrder{ false },
		m_cTransformListener{ this },
		m_cTransformControlsListener{ this },
		m_cFontListener{ this }
	{
		// Events from parent control
		OnParentStyleChange = nullptr;
		OnParentFontChange = nullptr;
		OnParentResize = nullptr;
		OnParentTransform = nullptr;
		OnParentTransformControls = nullptr;

		// Events from child controls
		OnChildStyleChange = nullptr;
		OnChildFontChange = nullptr;
		OnChildTransform = nullptr;
		OnChildResize = nullptr;
		OnChildShow = nullptr;
		OnChildHide = nullptr;
		OnChildAttach = nullptr;
		OnChildDetach = nullptr;
		OnChildEnable = nullptr;
		OnChildDisable = nullptr;
		OnChildBeforeTransform = nullptr;
		OnChildBeforeResize = nullptr;
		OnChildBeforeShow = nullptr;
		OnChildBeforeHide = nullptr;
		OnChildBeforeEnable = nullptr;
		OnChildBeforeDisable = nullptr;

		// State change events
		OnShow = nullptr;
		OnHide = nullptr;
		OnEnable = nullptr;
		OnDisable = nullptr;
		OnResize = nullptr;
		OnTransform = nullptr;
		OnTransformControls = nullptr;
		OnStyleChange = nullptr;
		OnFontChange = nullptr;
		OnSetModal = nullptr;
		OnKillModal = nullptr;
		OnSetFocus = nullptr;
		OnKillFocus = nullptr;
		OnSetCaptureKeyboard = nullptr;
		OnKillCaptureKeyboard = nullptr;
		OnSetCaptureMouse = nullptr;
		OnKillCaptureMouse = nullptr;
		OnActivate = nullptr;
		OnDeactivate = nullptr;

		// Paint events
		OnPaint = nullptr;
		OnPaintEnd = nullptr;

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

		// Clipboard events
		OnPasteString = nullptr;
	}

	CControl::~CControl()
	{
		if (m_pFont)
			m_pFont->Release();
		if (m_pTransform)
			m_pTransform->Release();
		if (m_pTransformControls)
			m_pTransformControls->Release();
		if (m_pService)
			m_pService->Release();
	}

	void CControl::BeforeRelease()
	{
		CLockRepaint lock{ this };
		DeleteControls();
		if (m_pParent)
			m_pParent->DetachControl(this);
		else if (getForm())
			getForm()->DetachControl(this);
		CComponent::BeforeRelease();
	}
#pragma endregion

#pragma region Getters
	IControl *CControl::getParent()
	{
		return m_pParent;
	}

	IStyle *CControl::getParentStyle()
	{
		if (m_pParent)
			return m_pParent->getStyle();
		if (getForm())
			return getForm()->getStyle();
		return nullptr;
	}

	IStyle *CControl::getControlStyle()
	{
		return m_pStyle;
	}

	IStyle *CControl::getStyle()
	{
		if (m_bUseParentStyle)
		{
			IStyle *style{ getParentStyle() };
			if (style)
				return style;
		}
		return m_pStyle;
	}

	IFont *CControl::getParentFont()
	{
		if (m_pParent)
			return m_pParent->getFont();
		if (getForm())
			return getForm()->getFont();
		return nullptr;
	}

	IFont *CControl::getControlFont()
	{
		if (!m_pFont)
			m_pFont = new CFont(&m_cFontListener);
		return m_pFont;
	}

	IFont *CControl::getFont()
	{
		if (m_bUseParentFont)
		{
			IFont *font{ getParentFont() };
			if (font)
				return font;
		}
		return getControlFont();
	}

	int CControl::getControlCount(const bool total)
	{
		int result{ (int)m_aControls.size() };
		if (total)
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				result += (*pos)->getControlCount(true);
		return result;
	}

	IControl *CControl::getControl(const int index)
	{
		if (index >= 0 && index < (int)m_aControls.size())
			return m_aControls[(size_t)index];
		return nullptr;
	}

	IControl *CControl::getControl(const String &name)
	{
		for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
			if ((*pos)->Name == name)
				return *pos;
		return nullptr;
	}

	IControl *CControl::getControl(const PointF &position)
	{
		if (m_bVisible)
		{
			std::vector<IControl*> controls{ m_aControls };
			std::sort(controls.begin(), controls.end(), [](IControl *a, IControl *b) { return a->getZIndex() < b->getZIndex(); });
			for (auto pos = controls.rbegin(); pos != controls.rend(); pos++)
			{
				IControl *control{ (*pos)->getControl(position) };
				if (control)
					return control;
			}
			Mat4f m{ ntl::Inversed<float>(getTransformMatrix()) };
			Vec4f v{ m * Vec4f{ position.X, position.Y, 0, 1 } };
			if (v.X >= 0 && v.X < getWidth() && v.Y >= 0 && v.Y < getHeight())
				return this;
		}
		return nullptr;
	}

	int CControl::getControlIndex(IControl *control)
	{
		int result{ 0 };
		for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++, result++)
			if (*pos == control)
				return result;
		return -1;
	}

	ITransform *CControl::getTransform()
	{
		if (!m_pTransform)
			m_pTransform = new CTransform(&m_cTransformListener);
		return m_pTransform;
	}

	ITransform *CControl::getTransformControls()
	{
		if (!m_pTransformControls)
			m_pTransformControls = new CTransform(&m_cTransformControlsListener);
		return m_pTransformControls;
	}

	Mat4f CControl::getTransformMatrix()
	{
		Mat4f result{ getTransform()->getMatrix() };
		if (m_eAlign == Align::None)
		{
			if (m_pParent)
				result = m_pParent->getTransformControls()->getMatrix() * result;
			else if (getForm())
				result = getForm()->getTransformControls()->getMatrix() * result;
		}
		if (m_pParent)
			result = m_pParent->getTransformMatrix() * result;
		return result;
	}

	Align CControl::getAlign()
	{
		return m_eAlign;
	}

	RectF CControl::getConstraints()
	{
		return m_sConstraints;
	}

	PointF CControl::getMinConstraints()
	{
		return m_sConstraints.LeftTop;
	}

	PointF CControl::getMaxConstraints()
	{
		return m_sConstraints.RightBottom;
	}

	float CControl::getMinWidth()
	{
		return m_sConstraints.Left;
	}

	float CControl::getMinHeight()
	{
		return m_sConstraints.Top;
	}

	float CControl::getMaxWidth()
	{
		return m_sConstraints.Right;
	}

	float CControl::getMaxHeight()
	{
		return m_sConstraints.Bottom;
	}

	PointF CControl::getSize()
	{
		return m_sSize;
	}

	float CControl::getWidth()
	{
		return m_sSize.X;
	}

	float CControl::getHeight()
	{
		return m_sSize.Y;
	}

	RectF CControl::getRect()
	{
		return RectF{ 0, 0, m_sSize.X, m_sSize.Y };
	}

	RectF CControl::getClientRect()
	{
		return RectF{ 0, 0, m_sSize.X, m_sSize.Y };
	}

	RectF CControl::getRenderRect()
	{
		return RectF{ 0, 0, m_sSize.X, m_sSize.Y };
	}

	int CControl::getZIndex()
	{
		return m_iZIndex;
	}

	CursorType CControl::getCursor()
	{
		return m_eCursor;
	}

	int CControl::getTabOrder()
	{
		return m_iTabOrder;
	}

	String CControl::getHintText()
	{
		return m_sHintText;
	}

	float CControl::getHintDelay()
	{
		if (m_bUseParentHintDelay)
		{
			if (m_pParent)
				return m_pParent->getHintDelay();
			if (getForm())
				return getForm()->getHintDelay();
		}
		return m_fHintDelay;
	}

	PointF CControl::getHintShift()
	{
		if (m_bUseParentHintShift)
		{
			if (m_pParent)
				return m_pParent->getHintShift();
			if (getForm())
				return getForm()->getHintShift();
		}
		return m_sHintShift;
	}

	Point CControl::getDPI()
	{
		return m_sDPI;
	}

	bool CControl::isAcceptForm()
	{
		return m_bAcceptForm;
	}

	bool CControl::isAcceptForm(IForm *form)
	{
		return m_bAcceptForm && form;
	}

	bool CControl::isAcceptControl()
	{
		return m_bAcceptControl;
	}

	bool CControl::isAcceptControl(IControl *control)
	{
		return m_bAcceptControl && control;
	}

	bool CControl::isAcceptControls()
	{
		return m_bAcceptControls;
	}

	bool CControl::isAcceptFocus()
	{
		return m_bAcceptFocus;
	}

	bool CControl::isAcceptModal()
	{
		return m_bAcceptModal;
	}

	bool CControl::isWantTabs()
	{
		return m_bWantTabs;
	}

	bool CControl::isTabStop()
	{
		return m_bTabStop;
	}

	bool CControl::isDeactivateByTab()
	{
		return m_bDeactivateByTab;
	}

	bool CControl::isModal()
	{
		return getForm() && getForm()->getModalControl() == this;
	}

	bool CControl::isHovered()
	{
		return getForm() && getForm()->getHoveredControl() == this;
	}

	bool CControl::isFocused()
	{
		return getForm() && getForm()->getFocusedControl() == this;
	}

	bool CControl::isVisible(const bool with_parents)
	{
		if (with_parents && m_pParent)
			return m_bVisible && m_pParent->isVisible(true);
		return m_bVisible;
	}

	bool CControl::isEnabled(const bool with_parents)
	{
		if (with_parents && m_pParent)
			return m_bEnabled && m_pParent->isEnabled(true);
		return m_bEnabled;
	}

	bool CControl::isCaptureMouse()
	{
		return getForm() && getForm()->getCaptureMouseControl() == this;
	}

	bool CControl::isCaptureKeyboard()
	{
		return getForm() && getForm()->getCaptureKeyboardControl() == this;
	}

	bool CControl::isActive()
	{
		return getForm() && getForm()->getActiveControl() == this;
	}

	bool CControl::isShowHint()
	{
		if (m_bUseParentShowHint)
		{
			if (m_pParent)
				return m_pParent->isShowHint();
			if (getForm())
				return getForm()->isShowHint();
		}
		return m_bShowHint;
	}

	bool CControl::isFocusByMouse()
	{
		return true;
	}

	bool CControl::isUseParentStyle()
	{
		return m_bUseParentStyle;
	}

	bool CControl::isUseParentFont()
	{
		return m_bUseParentFont;
	}

	bool CControl::isUseParentShowHint()
	{
		return m_bUseParentShowHint;
	}

	bool CControl::isUseParentHintDelay()
	{
		return m_bUseParentHintDelay;
	}

	bool CControl::isUseParentHintShift()
	{
		return m_bUseParentHintShift;
	}

	bool CControl::isAcceptChild(IControl *control)
	{
		return true;
	}

	bool CControl::isStaticTabOrder()
	{
		return m_bStaticTabOrder;
	}

	bool CControl::isAcceptBubbledEvents()
	{
		return false;
	}

	bool CControl::hasChild(IControl *control)
	{
		if (!control)
			return false;
		for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
		{
			if (*pos == control)
				return true;
			if ((*pos)->hasChild(control))
				return true;
		}
		return false;
	}

	bool CControl::hasParent(IControl *control)
	{
		if (!control)
			return false;
		if (m_pParent == control)
			return true;
		if (m_pParent)
			return m_pParent->hasParent(control);
		return false;
	}

	bool CControl::hasStyle() const
	{
		return m_pStyle != nullptr;
	}

	bool CControl::hasFont() const
	{
		return m_pFont != nullptr;
	}

	bool CControl::hasExtra()
	{
		return false;
	}
#pragma endregion

#pragma region Setters
	bool CControl::setName(const String &value)
	{
		if (value != m_sName)
		{
			m_sName = value;
			if (getForm())
				QueryService()->setName(getForm()->QueryService()->GenerateControlName(this));
			return true;
		}
		return false;
	}

	bool CControl::setForm(IForm *value)
	{
		if (value == getForm())
			return false;
		if (m_pParent)
			m_pParent->DetachControl(this);
		else if (getForm())
			getForm()->DetachControl(this);
		if (value)
			return value->AttachControl(this);
		return true;
	}

	void CControl::setService(IControlService *value, const bool release_prev)
	{
		if (m_pService && m_pService != value && release_prev)
			m_pService->Release();
		m_pService = value;
	}

	bool CControl::setParent(IControl *value)
	{
		if (value == m_pParent)
			return false;
		IForm *form{ getForm() };
		if (form)
			form->LockRepaint();
		bool result;
		if (value)
			result = value->AttachControl(this);
		else
			if (m_pParent)
				result = m_pParent->DetachControl(this);
			else if (getForm())
				result = getForm()->DetachControl(this);
			else
				result = false;
		if (form)
			form->UnlockRepaint();
		return result;
	}

	bool CControl::setStyle(IStyle *value)
	{
		if (value == m_pStyle && !m_bUseParentStyle)
			return false;
		m_pStyle = value;
		m_bUseParentStyle = false;
		if (m_pStyle)
		{
			CLockRepaint lock{ this };
			Repaint(true);
			CopyFont(getControlFont(), m_pStyle->getFont(m_sClassName));
			NotifyStyleChange();
			Repaint(true);
		}
		return true;
	}

	bool CControl::setFont(IFont *value, const bool copy)
	{
		if (!value || (value == m_pFont && !m_bUseParentFont))
			return false;
		CLockRepaint lock{ this };
		Repaint(true);
		m_bUseParentFont = false;
		if (!copy)
		{
			if (m_pFont)
				m_pFont->Release();
			m_pFont = value;
			m_pFont->setListener(&m_cFontListener);
		}
		else
			CopyFont(getControlFont(), value);
		NotifyFontChange();
		Repaint(true);
		return true;
	}

	bool CControl::setTransform(ITransform *value)
	{
		if (!value || value == m_pTransform || !CheckTransformAllowed())
			return false;
		CLockRepaint lock{ this };
		Repaint(true);
		CopyTransform(value, m_pTransform);
		value->setListener(&m_cTransformListener);
		if (m_pTransform)
			m_pTransform->Release();
		m_pTransform = value;
		if (m_eAlign != Align::None)
		{
			if (m_pParent)
				m_pParent->QueryService()->AlignControls();
			else if (getForm())
				getForm()->QueryService()->AlignControls();
		}
		NotifyTransform();
		Repaint(true);
		return true;
	}

	bool CControl::setTransformControls(ITransform *value)
	{
		if (!value || value == m_pTransformControls)
			return false;
		CLockRepaint lock{ this };
		Repaint(true);
		CopyTransform(value, m_pTransformControls);
		value->setListener(&m_cTransformControlsListener);
		if (m_pTransformControls)
			m_pTransformControls->Release();
		m_pTransformControls = value;
		QueryService()->AlignControls();
		NotifyTransformControls();
		Repaint(true);
		return true;
	}

	bool CControl::setAlign(const Align value)
	{
		if (value == m_eAlign)
			return false;
		CLockRepaint lock{ this };
		Repaint(true);
		m_eAlign = value;
		if (m_eAlign == Align::None)
			m_sSizeRequested = m_sSize;
		if (m_pParent)
			m_pParent->QueryService()->AlignControls();
		else if (getForm())
			getForm()->QueryService()->AlignControls();
		if (m_eAlign == Align::None)
			AdjustSize();
		Repaint(true);
		return true;
	}

	bool CControl::setConstraints(const RectF &value)
	{
		if (IsEqual(value, m_sConstraints) || value.has_negative())
			return false;
		CLockRepaint lock{ this };
		Repaint(true);
		m_sConstraints = value;
		if (m_eAlign != Align::None)
		{
			if (m_pParent)
				m_pParent->QueryService()->AlignControls();
			else if (getForm())
				getForm()->QueryService()->AlignControls();
		}
		else
			AdjustSize();
		Repaint(true);
		return true;
	}

	bool CControl::setMinConstraints(const PointF &value)
	{
		return setConstraints(RectF{ value.X, value.Y, m_sConstraints.Right, m_sConstraints.Bottom });
	}

	bool CControl::setMaxConstraints(const PointF &value)
	{
		return setConstraints(RectF{ m_sConstraints.Left, m_sConstraints.Top, value.X, value.Y });
	}

	bool CControl::setMinWidth(const float value)
	{
		return setConstraints(RectF{ value, m_sConstraints.Top, m_sConstraints.Right, m_sConstraints.Bottom });
	}

	bool CControl::setMinHeight(const float value)
	{
		return setConstraints(RectF{ m_sConstraints.Left, value, m_sConstraints.Right, m_sConstraints.Bottom });
	}

	bool CControl::setMaxWidth(const float value)
	{
		return setConstraints(RectF{ m_sConstraints.Left, m_sConstraints.Top, value, m_sConstraints.Bottom });
	}

	bool CControl::setMaxHeight(const float value)
	{
		return setConstraints(RectF{ m_sConstraints.Left, m_sConstraints.Top, m_sConstraints.Right, value });
	}

	bool CControl::setSize(const PointF &value)
	{
		PointF size{ AdjustByConstraints(value, m_sConstraints) };
		if (ntl::IsLess<float>(value.X, 0) || ntl::IsLess<float>(value.Y, 0) || IsEqual(size, m_sSize) || !CheckResizeAllowed())
			return false;
		CLockRepaint lock{ this };
		Repaint(true);
		m_sSizeRequested = value;
		AdjustSize();
		if (m_eAlign != Align::None)
		{
			if (m_pParent)
				m_pParent->QueryService()->AlignControls();
			else if (getForm())
				getForm()->QueryService()->AlignControls();
		}
		Repaint(true);
		return true;
	}

	bool CControl::setWidth(const float value)
	{
		return setSize(PointF{ value, m_sSize.Y });
	}

	bool CControl::setHeight(const float value)
	{
		return setSize(PointF{ m_sSize.X, value });
	}

	bool CControl::setZIndex(const int value)
	{
		if (value != m_iZIndex)
		{
			m_iZIndex = value;
			CLockRepaint lock{ this };
			Repaint(true);
			return true;
		}
		return false;
	}

	bool CControl::setCursor(const CursorType value)
	{
		if (value != m_eCursor)
		{
			m_eCursor = value;
			if (getForm() && getForm()->getHoveredControl() == this)
				getForm()->UpdateHoveredControl(); // To update cursor
			return true;
		}
		return false;
	}

	bool CControl::setTabOrder(const int value)
	{
		if (value >= 0 && value != m_iTabOrder)
		{
			if (getForm())
				getForm()->QueryService()->UpdateTabOrders(m_iTabOrder, value);
			else
				m_iTabOrder = value;
			return true;
		}
		return false;
	}

	bool CControl::setHintText(const String &value)
	{
		if (value != m_sHintText)
		{
			m_sHintText = value;
			return true;
		}
		return false;
	}

	bool CControl::setHintDelay(const float value)
	{
		if (ntl::IsLessOrEqual<float>(value, 0) || (ntl::IsEqual<float>(value, m_fHintDelay) && !m_bUseParentHintDelay))
			return false;
		m_bUseParentHintDelay = false;
		m_fHintDelay = value;
		return true;
	}

	bool CControl::setHintShift(const PointF &value)
	{
		if (IsEqual(value, m_sHintShift) && !m_bUseParentHintShift)
			return false;
		m_bUseParentHintShift = false;
		m_sHintShift = value;
		return true;
	}

	bool CControl::setWantTabs(const bool value)
	{
		if (value != m_bWantTabs)
		{
			m_bWantTabs = value;
			return true;
		}
		return false;
	}

	bool CControl::setTabStop(const bool value)
	{
		if (value != m_bTabStop)
		{
			m_bTabStop = value;
			return true;
		}
		return false;
	}

	bool CControl::setDeactivateByTab(const bool value)
	{
		if (value != m_bDeactivateByTab)
		{
			m_bDeactivateByTab = value;
			return true;
		}
		return false;
	}

	bool CControl::setModal(const bool value)
	{
		if (!getForm())
			return false;
		return getForm()->setModalControl(value ? this : nullptr);
	}

	bool CControl::setFocus()
	{
		if (!getForm())
			return false;
		return getForm()->setFocusedControl(this);
	}

	bool CControl::setVisible(const bool value)
	{
		if (value != m_bVisible && (value ? CheckShowAllowed() : CheckHideAllowed()))
		{
			CLockRepaint lock{ this };
			Repaint(true);
			m_bVisible = value;
			IForm *form{ getForm() };
			if (m_bVisible)
			{
				if (getAlign() != Align::None)
				{
					if (getParent())
						getParent()->QueryService()->AlignControls();
					else if (form)
						form->QueryService()->AlignControls();
				}
				CNotifier::ControlShow(this);
				if (form)
				{
					form->UpdateHoveredControl();
					Repaint(true);
				}
			}
			else
			{
				if (form)
					form->QueryService()->ProcessControlHide(this);
				if (getAlign() != Align::None)
				{
					if (getParent())
						getParent()->QueryService()->AlignControls();
					else if (form)
						form->QueryService()->AlignControls();
				}
				CNotifier::ControlHide(this);
			}
			return true;
		}
		return false;
	}

	bool CControl::setEnabled(const bool value)
	{
		if (value != m_bEnabled && (value ? CheckEnableAllowed() : CheckDisableAllowed()))
		{
			CLockRepaint lock{ this };
			Repaint(true);
			m_bEnabled = value;
			IForm *form{ getForm() };
			if (m_bEnabled)
			{
				CNotifier::ControlEnable(this);
			}
			else
			{
				if (form)
					form->QueryService()->ProcessControlDisable(this);
				CNotifier::ControlDisable(this);
			}
			Repaint(true);
			return true;
		}
		return false;
	}

	bool CControl::setShowHint(const bool value)
	{
		if (value == m_bShowHint && !m_bUseParentShowHint)
			return false;
		m_bUseParentShowHint = false;
		m_bShowHint = value;
		return true;
	}

	bool CControl::setUseParentStyle(const bool value)
	{
		if (value != m_bUseParentStyle)
		{
			m_bUseParentStyle = value;
			if (getStyle())
			{
				CLockRepaint lock{ this };
				Repaint(true);
				CopyFont(getControlFont(), m_pStyle->getFont(m_sClassName));
				NotifyStyleChange();
				Repaint(true);
			}
			return true;
		}
		return false;
	}

	bool CControl::setUseParentFont(const bool value)
	{
		if (value != m_bUseParentFont)
		{
			CLockRepaint lock{ this };
			Repaint(true);
			m_bUseParentFont = value;
			NotifyFontChange();
			Repaint(true);
			return true;
		}
		return false;
	}

	bool CControl::setUseParentShowHint(const bool value)
	{
		if (value != m_bUseParentShowHint)
		{
			m_bUseParentShowHint = value;
			return true;
		}
		return false;
	}

	bool CControl::setUseParentHintDelay(const bool value)
	{
		if (value != m_bUseParentHintDelay)
		{
			m_bUseParentHintDelay = value;
			return true;
		}
		return false;
	}

	bool CControl::setUseParentHintShift(const bool value)
	{
		if (value != m_bUseParentHintShift)
		{
			m_bUseParentHintShift = value;
			return true;
		}
		return false;
	}

	bool CControl::setDPI(const Point &value)
	{
		if (value.X > 0 && value.Y > 0 && value != m_sDPI)
		{
			CLockRepaint lock{ this };
			PointF s{ (float)value.X / (float)m_sDPI.X, (float)value.Y / (float)m_sDPI.Y };
			m_sDPI = value;
			setConstraints(m_sConstraints * s);
			setSize(m_sSizeRequested * s);
			m_sHintShift *= s;
			getTransform()->Translate(getTransform()->getTx() * s.X, getTransform()->getTy() * s.Y, getTransform()->getTz());
			getTransformControls()->Translate(getTransformControls()->getTx() * s.X, getTransformControls()->getTy() * s.Y, getTransformControls()->getTz());
			for (auto control : m_aControls)
				control->setDPI(value);
			Repaint(false);
			return true;
		}
		return false;
	}

	bool CControl::setStaticTabOrder(const bool value)
	{
		if (value != m_bStaticTabOrder)
		{
			m_bStaticTabOrder = value;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Controls
	bool CControl::AttachControl(IControl *control)
	{
		return InsertControl(control, getControlCount());
	}

	bool CControl::InsertControl(IControl *control, const int before)
	{
		if (!control || control == this) // Control should be specified and it should not be equal to this one
			return false;
		if (!m_bAcceptControls || !control->isAcceptControl() || !isAcceptChild(control) || !control->isAcceptControl(this)) // Both this one and control should accept each other
			return false;
		if (control->getParent() == this) // Control should not be on this one
			return false;
		if (control->hasChild(this)) // This control should not be in the control's hierarchy
			return false;
		CLockRepaint lock1{ this }, lock2{ control };
		Repaint(true);
		// Detach control from parent
		if (control->getParent())
			control->getParent()->DetachControl(control);
		else if (control->getForm())
			control->getForm()->DetachControl(control);
		// Add control to list
		QueryService()->InsertControl(control, before);
		// Set parent, form, names, tab indices
		control->QueryService()->setParent(this);
		SetFormRecursively(control, getForm(), control->isStaticTabOrder());
		GenerateNameRecursively(control);
		// Align controls if attached control is aligned
		if (control->getAlign() != Align::None && control->isVisible(false))
			QueryService()->AlignControls();
		NotifyAttach(control);
		control->setDPI(m_sDPI);
		Repaint(true);
		return true;
	}

	bool CControl::DeleteControl(const int index)
	{
		IControl *control{ getControl(index) };
		if (control)
		{
			control->Release();
			return true;
		}
		return false;
	}

	bool CControl::DeleteControl(IControl *control)
	{
		if (control && control->getParent() == this)
		{
			control->Release();
			return true;
		}
		return false;
	}

	bool CControl::DeleteControls()
	{
		if (getControlCount() == 0)
			return false;
		CLockRepaint{ this };
		while (getControlCount() > 0)
			getControl(0)->Release();
		return true;
	}

	bool CControl::DetachControl(IControl *control)
	{
		if (!control || control->getParent() != this)
			return false;
		CLockRepaint lock{ this };
		Repaint(true);
		CNotifier::Detaching(control);
		if (getForm())
			getForm()->QueryService()->ProcessControlDetach(control);
		// Remove connections
		for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
			if (*pos == control)
			{
				m_aControls.erase(pos);
				break;
			}
		control->QueryService()->setParent(nullptr);
		SetFormRecursively(control, nullptr, control->isStaticTabOrder());
		if (control->getAlign() != Align::None)
		{
			control->QueryService()->AdjustSize();
			if (control->isVisible(false))
				QueryService()->AlignControls();
		}
		CNotifier::ControlDetach(this, control);
		Repaint(true);
		return true;
	}

	IControl *CControl::FindControl(const String &name, IControl *exclude)
	{
		for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
		{
			if (*pos != exclude && (*pos)->Name == name)
				return *pos;
			IControl *control{ (*pos)->FindControl(name, exclude) };
			if (control)
				return control;
		}
		return nullptr;
	}
#pragma endregion

#pragma region Change position
	bool CControl::BringToFront()
	{
		if (m_pParent)
			return m_pParent->QueryService()->MoveControl(this, m_pParent->getControlCount());
		if (getForm())
			return getForm()->QueryService()->MoveControl(this, getForm()->getControlCount());
		return false;
	}

	bool CControl::BringUp()
	{
		if (m_pParent)
			return m_pParent->QueryService()->MoveControl(this, m_pParent->getControlIndex(this) + 2);
		if (getForm())
			return getForm()->QueryService()->MoveControl(this, getForm()->getControlIndex(this) + 2);
		return false;
	}

	bool CControl::BringDown()
	{
		if (m_pParent)
			return m_pParent->QueryService()->MoveControl(this, m_pParent->getControlIndex(this) - 1);
		if (getForm())
			return getForm()->QueryService()->MoveControl(this, getForm()->getControlIndex(this) - 1);
		return false;
	}

	bool CControl::BringBefore(IControl *control)
	{
		if (m_pParent)
			return m_pParent->QueryService()->MoveControl(this, m_pParent->getControlIndex(control));
		if (getForm())
			return getForm()->QueryService()->MoveControl(this, getForm()->getControlIndex(control));
		return false;
	}

	bool CControl::BringBefore(const int index)
	{
		if (m_pParent)
			return m_pParent->QueryService()->MoveControl(this, index);
		if (getForm())
			return getForm()->QueryService()->MoveControl(this, index);
		return false;
	}

	bool CControl::BringAfter(IControl *control)
	{
		if (m_pParent)
			return m_pParent->QueryService()->MoveControl(this, m_pParent->getControlIndex(control) + 1);
		if (getForm())
			return getForm()->QueryService()->MoveControl(this, getForm()->getControlIndex(control) + 1);
		return false;
	}

	bool CControl::BringAfter(const int index)
	{
		if (m_pParent)
			return m_pParent->QueryService()->MoveControl(this, index + 1);
		if (getForm())
			return getForm()->QueryService()->MoveControl(this, index + 1);
		return false;
	}
#pragma endregion

#pragma region Helpers
	void CControl::Repaint(const RectF &rect, const bool convert)
	{
		if (getForm())
			getForm()->Repaint(convert ? TransformRect(rect, getTransformMatrix()) : rect);
	}

	void CControl::Repaint(const bool repaint_children)
	{
		if (getForm() && isVisible(true))
		{
			CLockRepaint lock{ this };
			getForm()->Repaint(TransformRect(getRenderRect(), getTransformMatrix()));
			if (repaint_children)
				for (auto control : m_aControls)
					control->Repaint(true);
		}
	}

	void CControl::Refresh(const bool refresh_children)
	{
		if (refresh_children)
			for (auto control : m_aControls)
				control->Refresh(true);
	}

	IControlService *CControl::QueryService()
	{
		if (!m_pService)
			m_pService = new CControlService(this);
		return m_pService;
	}

	bool CControl::CheckTransformAllowed()
	{
		if (m_pParent)
		{
			bool allowed{ true };
			m_pParent->QueryService()->NotifyOnChildBeforeTransform(this, allowed);
			if (!allowed)
				return false;
			if (m_pParent->OnChildBeforeTransform)
				m_pParent->OnChildBeforeTransform(m_pParent, this, allowed);
			if (!allowed)
				return false;
		}
		else
		{
			IForm *form{ getForm() };
			if (form)
			{
				bool allowed{ true };
				form->QueryService()->NotifyOnChildBeforeTransform(this, allowed);
				if (!allowed)
					return false;
				if (form->OnChildBeforeTransform)
					form->OnChildBeforeTransform(form, this, allowed);
				if (!allowed)
					return false;
			}
		}
		return true;
	}

	bool CControl::CheckResizeAllowed()
	{
		if (m_pParent)
		{
			bool allowed{ true };
			m_pParent->QueryService()->NotifyOnChildBeforeResize(this, allowed);
			if (!allowed)
				return false;
			if (m_pParent->OnChildBeforeResize)
				m_pParent->OnChildBeforeResize(m_pParent, this, allowed);
			if (!allowed)
				return false;
		}
		else
		{
			IForm *form{ getForm() };
			if (form)
			{
				bool allowed{ true };
				form->QueryService()->NotifyOnChildBeforeResize(this, allowed);
				if (!allowed)
					return false;
				if (form->OnChildBeforeResize)
					form->OnChildBeforeResize(form, this, allowed);
				if (!allowed)
					return false;
			}
		}
		return true;
	}

	bool CControl::CheckShowAllowed()
	{
		if (m_pParent)
		{
			bool allowed{ true };
			m_pParent->QueryService()->NotifyOnChildBeforeShow(this, allowed);
			if (!allowed)
				return false;
			if (m_pParent->OnChildBeforeShow)
				m_pParent->OnChildBeforeShow(m_pParent, this, allowed);
			if (!allowed)
				return false;
		}
		else
		{
			IForm *form{ getForm() };
			if (form)
			{
				bool allowed{ true };
				form->QueryService()->NotifyOnChildBeforeShow(this, allowed);
				if (!allowed)
					return false;
				if (form->OnChildBeforeShow)
					form->OnChildBeforeShow(form, this, allowed);
				if (!allowed)
					return false;
			}
		}
		return true;
	}

	bool CControl::CheckHideAllowed()
	{
		if (m_pParent)
		{
			bool allowed{ true };
			m_pParent->QueryService()->NotifyOnChildBeforeHide(this, allowed);
			if (!allowed)
				return false;
			if (m_pParent->OnChildBeforeHide)
				m_pParent->OnChildBeforeHide(m_pParent, this, allowed);
			if (!allowed)
				return false;
		}
		else
		{
			IForm *form{ getForm() };
			if (form)
			{
				bool allowed{ true };
				form->QueryService()->NotifyOnChildBeforeHide(this, allowed);
				if (!allowed)
					return false;
				if (form->OnChildBeforeHide)
					form->OnChildBeforeHide(form, this, allowed);
				if (!allowed)
					return false;
			}
		}
		return true;
	}

	bool CControl::CheckEnableAllowed()
	{
		if (m_pParent)
		{
			bool allowed{ true };
			m_pParent->QueryService()->NotifyOnChildBeforeEnable(this, allowed);
			if (!allowed)
				return false;
			if (m_pParent->OnChildBeforeEnable)
				m_pParent->OnChildBeforeEnable(m_pParent, this, allowed);
			if (!allowed)
				return false;
		}
		else
		{
			IForm *form{ getForm() };
			if (form)
			{
				bool allowed{ true };
				form->QueryService()->NotifyOnChildBeforeEnable(this, allowed);
				if (!allowed)
					return false;
				if (form->OnChildBeforeEnable)
					form->OnChildBeforeEnable(form, this, allowed);
				if (!allowed)
					return false;
			}
		}
		return true;
	}

	bool CControl::CheckDisableAllowed()
	{
		if (m_pParent)
		{
			bool allowed{ true };
			m_pParent->QueryService()->NotifyOnChildBeforeDisable(this, allowed);
			if (!allowed)
				return false;
			if (m_pParent->OnChildBeforeDisable)
				m_pParent->OnChildBeforeDisable(m_pParent, this, allowed);
			if (!allowed)
				return false;
		}
		else
		{
			IForm *form{ getForm() };
			if (form)
			{
				bool allowed{ true };
				form->QueryService()->NotifyOnChildBeforeDisable(this, allowed);
				if (!allowed)
					return false;
				if (form->OnChildBeforeDisable)
					form->OnChildBeforeDisable(form, this, allowed);
				if (!allowed)
					return false;
			}
		}
		return true;
	}

	void CControl::AdjustSize()
	{
		PointF size{ AdjustByConstraints(m_sSizeRequested, m_sConstraints) };
		if (IsNotEqual(size, m_sSize))
		{
			m_sSize = size;
			QueryService()->AlignControls();
			NotifyResize();
		}
	}

	void CControl::CopyFont(IFont *dest, IFontProperties *src)
	{
		if (dest && src)
		{
			m_bIgnoreFont = true;
			dest->Copy(src);
			m_bIgnoreFont = false;
		}
	}

	void CControl::CopyTransform(ITransform *dest, ITransform *src)
	{
		if (dest && src)
		{
			m_bIgnoreTransform = m_bIgnoreTransformControls = true;
			dest->setRotateOrder(src->getRotateOrder());
			dest->setTransformOrder(src->getTransformOrder());
			dest->Transform(src->getTx(), src->getTy(), src->getTz(), src->getSx(), src->getSy(), src->getSz(), src->getRx(), src->getRy(), src->getRz());
			m_bIgnoreTransform = m_bIgnoreTransformControls = false;
		}
	}

	void CControl::SetFormRecursively(IControl *control, IForm *form, const bool static_tab_order)
	{
		control->QueryService()->setForm(form);
		if (form && !static_tab_order && !control->isStaticTabOrder())
			control->QueryService()->setTabOrder(form->QueryService()->GenerateTabOrder(control));
		for (int i = 0; i < control->getControlCount(); i++)
			SetFormRecursively(control->getControl(i), form, static_tab_order || control->isStaticTabOrder());
	}

	void CControl::GenerateNameRecursively(IControl *control)
	{
		if (getForm())
		{
			control->QueryService()->setName(getForm()->QueryService()->GenerateControlName(control));
			for (int i = 0; i < control->getControlCount(); i++)
				GenerateNameRecursively(control->getControl(i));
		}
	}

	PointF CControl::FormToLocal(const PointF &pos)
	{
		Vec4f v{ ntl::Inversed<float>(getTransformMatrix()) * Vec4f { pos.X, pos.Y, 0, 1 } };
		return PointF{ v.X, v.Y };
	}

	PointF CControl::LocalToForm(const PointF &pos)
	{
		Vec4f v{ getTransformMatrix() * Vec4f { pos.X, pos.Y, 0, 1 } };
		return PointF{ v.X, v.Y };
	}
#pragma region

#pragma region Notification senders
	void CControl::NotifyStyleChange()
	{
		QueryService()->NotifyOnStyleChange();
		if (OnStyleChange)
			OnStyleChange(this);
		for (auto pos : m_aControls)
			if (pos->isUseParentStyle())
				CNotifier::ParentStyleChange(pos);
		if (m_pParent)
		{
			m_pParent->QueryService()->NotifyOnChildStyleChange(this);
			if (m_pParent->OnChildStyleChange)
				m_pParent->OnChildStyleChange(m_pParent, this);
		}
		else if (getForm())
		{
			getForm()->QueryService()->NotifyOnChildStyleChange(this);
			if (getForm()->OnChildStyleChange)
				getForm()->OnChildStyleChange(getForm(), this);
		}
	}

	void CControl::NotifyFontChange()
	{
		QueryService()->NotifyOnFontChange();
		if (OnFontChange)
			OnFontChange(this);
		for (auto pos : m_aControls)
			if (pos->isUseParentFont())
				CNotifier::ParentFontChange(pos);
		if (m_pParent)
		{
			m_pParent->QueryService()->NotifyOnChildFontChange(this);
			if (m_pParent->OnChildFontChange)
				m_pParent->OnChildFontChange(m_pParent, this);
		}
		else if (getForm())
		{
			getForm()->QueryService()->NotifyOnChildFontChange(this);
			if (getForm()->OnChildFontChange)
				getForm()->OnChildFontChange(getForm(), this);
		}
	}

	void CControl::NotifyTransform()
	{
		QueryService()->NotifyOnTransform();
		if (OnTransform)
			OnTransform(this);
		for (auto pos : m_aControls)
		{
			pos->QueryService()->NotifyOnParentTransform();
			if (pos->OnParentTransform)
				pos->OnParentTransform(pos);
		}
		if (m_pParent)
		{
			m_pParent->QueryService()->NotifyOnChildTransform(this);
			if (m_pParent->OnChildTransform)
				m_pParent->OnChildTransform(m_pParent, this);
		}
		else if (getForm())
		{
			getForm()->QueryService()->NotifyOnChildTransform(this);
			if (getForm()->OnChildTransform)
				getForm()->OnChildTransform(getForm(), this);
		}
	}

	void CControl::NotifyTransformControls()
	{
		QueryService()->NotifyOnTransformControls();
		if (OnTransformControls)
			OnTransformControls(this);
		for (auto pos : m_aControls)
		{
			pos->QueryService()->NotifyOnParentTransformControls();
			if (pos->OnParentTransformControls)
				pos->OnParentTransformControls(pos);
		}
	}

	void CControl::NotifyAttach(IControl *control)
	{
		// Notify attached control about parent style & font change and attaching
		if (control->isUseParentStyle())
			CNotifier::ParentStyleChange(control);
		if (control->isUseParentFont())
			CNotifier::ParentFontChange(control);
		CNotifier::ControlAttach(this, control);
	}

	void CControl::NotifyResize() // Called when control is resized due to size change
	{
		QueryService()->NotifyOnResize();
		if (OnResize)
			OnResize(this);
		for (auto pos : m_aControls)
		{
			pos->QueryService()->NotifyOnParentResize();
			if (pos->OnParentResize)
				pos->OnParentResize(pos);
		}
		if (m_pParent)
		{
			m_pParent->QueryService()->NotifyOnChildResize(this);
			if (m_pParent->OnChildResize)
				m_pParent->OnChildResize(m_pParent, this);
		}
		else if (getForm())
		{
			getForm()->QueryService()->NotifyOnChildResize(this);
			if (getForm()->OnChildResize)
				getForm()->OnChildResize(getForm(), this);
		}
	}
#pragma endregion

#pragma region Hint actions
	bool CControl::ShowHint(const PointF &position)
	{
		if (getForm())
			return getForm()->ShowHint(this, position);
		return false;
	}
#pragma endregion
}