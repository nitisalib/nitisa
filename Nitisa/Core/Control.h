// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IControl.h"
#include "../Interfaces/IFeedbackExListener.h"
#include "../Math/Mat4f.h"
#include "../Math/Point.h"
#include "../Math/PointF.h"
#include "../Math/RectF.h"
#include "Align.h"
#include "Component.h"
#include "Consts.h"
#include "CursorType.h"
#include "Strings.h"
#include <vector>

namespace nitisa
{
	class IControl;
	class IControlService;
	class IFont;
	class IFontProperties;
	class IForm;
	class IStyle;
	class ITransform;

	class CControlService;

	class CControl :public virtual IControl, public CComponent
	{
		friend CControlService;
	private:
		class CTransformListener :public virtual IFeedbackExListener
		{
		private:
			CControl *m_pControl;
		public:
			void NotifyOnBeforeChange() override;
			void NotifyOnBeforeChange(bool &allowed) override;
			void NotifyOnAfterChange() override;

			CTransformListener(CControl *control);
		};

		class CTransformControlsListener :public virtual IFeedbackExListener
		{
		private:
			CControl *m_pControl;
		public:
			void NotifyOnBeforeChange() override;
			void NotifyOnBeforeChange(bool &allowed) override;
			void NotifyOnAfterChange() override;

			CTransformControlsListener(CControl *control);
		};

		class CFontListener :public virtual IFeedbackExListener
		{
		private:
			CControl *m_pControl;
		public:
			void NotifyOnBeforeChange() override;
			void NotifyOnBeforeChange(bool &allowed) override;
			void NotifyOnAfterChange() override;

			CFontListener(CControl *control);
		};
	private:
		IControl *m_pParent;
		IStyle *m_pStyle;
		IFont *m_pFont;
		ITransform *m_pTransform;
		ITransform *m_pTransformControls;
		std::vector<IControl*> m_aControls;
		Align m_eAlign;
		RectF m_sConstraints;
		PointF m_sSize;
		PointF m_sSizeRequested;
		int m_iZIndex;
		CursorType m_eCursor;
		int m_iTabOrder;
		String m_sHintText;
		float m_fHintDelay;
		PointF m_sHintShift;
		bool m_bWantTabs;
		bool m_bTabStop;
		bool m_bDeactivateByTab;
		bool m_bVisible;
		bool m_bEnabled;
		bool m_bShowHint;
		bool m_bUseParentStyle;
		bool m_bUseParentFont;
		bool m_bUseParentShowHint;
		bool m_bUseParentHintDelay;
		bool m_bUseParentHintShift;
		IControlService *m_pService;
		bool m_bIgnoreTransform;
		bool m_bIgnoreTransformControls;
		bool m_bIgnoreFont;
		bool m_bRepaintedBeforeFontChange;
		bool m_bAcceptForm;
		bool m_bAcceptControl;
		bool m_bAcceptControls;
		bool m_bAcceptFocus;
		bool m_bAcceptModal;
		Point m_sDPI;
		bool m_bStaticTabOrder;

		CTransformListener m_cTransformListener;
		CTransformControlsListener m_cTransformControlsListener;
		CFontListener m_cFontListener;

		bool CheckTransformAllowed();
		bool CheckResizeAllowed();
		bool CheckShowAllowed();
		bool CheckHideAllowed();
		bool CheckEnableAllowed();
		bool CheckDisableAllowed();
		void AdjustSize();
		void CopyFont(IFont *dest, IFontProperties *src);
		void CopyTransform(ITransform *dest, ITransform *src);
		void SetFormRecursively(IControl *control, IForm *form, const bool static_tab_order);
		void GenerateNameRecursively(IControl *control);
		void NotifyStyleChange();
		void NotifyFontChange();
		void NotifyTransform();
		void NotifyTransformControls();
		void NotifyAttach(IControl *control);
		void NotifyResize(); // This control was resized
	protected:
		void BeforeRelease() override;
	public:
		IControl *getParent() override;
		IStyle *getParentStyle() override;
		IStyle *getControlStyle() override;
		IStyle *getStyle() override;
		IFont *getParentFont() override;
		IFont *getControlFont() override;
		IFont *getFont() override;
		int getControlCount(const bool total = false) override;
		IControl *getControl(const int index) override;
		IControl *getControl(const String &name) override;
		IControl *getControl(const PointF &position) override;
		int getControlIndex(IControl *control) override;
		ITransform *getTransform() override;
		ITransform *getTransformControls() override;
		Mat4f getTransformMatrix() override;
		Align getAlign() override;
		RectF getConstraints() override;
		PointF getMinConstraints() override;
		PointF getMaxConstraints() override;
		float getMinWidth() override;
		float getMinHeight() override;
		float getMaxWidth() override;
		float getMaxHeight() override;
		PointF getSize() override;
		float getWidth() override;
		float getHeight() override;
		RectF getRect() override;
		RectF getClientRect() override;
		RectF getRenderRect() override;
		int getZIndex() override;
		CursorType getCursor() override;
		int getTabOrder() override;
		String getHintText() override;
		float getHintDelay() override;
		PointF getHintShift() override;
		Point getDPI() override;
		bool isAcceptForm() override;
		bool isAcceptForm(IForm *form) override;
		bool isAcceptControl() override;
		bool isAcceptControl(IControl *control) override;
		bool isAcceptControls() override;
		bool isAcceptFocus() override;
		bool isAcceptModal() override;
		bool isWantTabs() override;
		bool isTabStop() override;
		bool isDeactivateByTab() override;
		bool isModal() override;
		bool isHovered() override;
		bool isFocused() override;
		bool isVisible(const bool with_parents) override;
		bool isEnabled(const bool with_parents) override;
		bool isCaptureMouse() override;
		bool isCaptureKeyboard() override;
		bool isActive() override;
		bool isShowHint() override;
		bool isFocusByMouse() override;
		bool isUseParentStyle() override;
		bool isUseParentFont() override;
		bool isUseParentShowHint() override;
		bool isUseParentHintDelay() override;
		bool isUseParentHintShift() override;
		bool isAcceptChild(IControl *control) override; // Always return true
		bool isStaticTabOrder() override; // False by default
		bool isAcceptBubbledEvents() override; // Return false
		bool hasChild(IControl *control) override;
		bool hasParent(IControl *control) override;
		bool hasStyle() const override;
		bool hasFont() const override;
		bool hasExtra() override; // Return false

		bool setName(const String &value) override;
		bool setForm(IForm *value) override;
		bool setParent(IControl *value) override;
		bool setStyle(IStyle *value) override;
		bool setFont(IFont *value, const bool copy = true) override;
		bool setTransform(ITransform *value) override;
		bool setTransformControls(ITransform *value) override;
		bool setAlign(const Align value) override;
		bool setConstraints(const RectF &value) override;
		bool setMinConstraints(const PointF &value) override;
		bool setMaxConstraints(const PointF &value) override;
		bool setMinWidth(const float value) override;
		bool setMinHeight(const float value) override;
		bool setMaxWidth(const float value) override;
		bool setMaxHeight(const float value) override;
		bool setSize(const PointF &value) override;
		bool setWidth(const float value) override;
		bool setHeight(const float value) override;
		bool setZIndex(const int value) override;
		bool setCursor(const CursorType value) override;
		bool setTabOrder(const int value) override;
		bool setHintText(const String &value) override;
		bool setHintDelay(const float value) override;
		bool setHintShift(const PointF &value) override;
		bool setWantTabs(const bool value) override;
		bool setTabStop(const bool value) override;
		bool setDeactivateByTab(const bool value) override;
		bool setModal(const bool value) override;
		bool setFocus() override;
		bool setVisible(const bool value) override;
		bool setEnabled(const bool value) override;
		bool setShowHint(const bool value) override;
		bool setUseParentStyle(const bool value) override;
		bool setUseParentFont(const bool value) override;
		bool setUseParentShowHint(const bool value) override;
		bool setUseParentHintDelay(const bool value) override;
		bool setUseParentHintShift(const bool value) override;
	#ifdef __clang__
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Woverloaded-virtual"
	#endif
		void setService(IControlService *value, const bool release_prev) override final; // Do nothing with previous service
	#ifdef __clang__
	#pragma clang diagnostic pop
	#endif
		bool setDPI(const Point &value) override;
		bool setStaticTabOrder(const bool value) override;

		bool AttachControl(IControl *control) override;
		bool InsertControl(IControl *control, const int before) override;
		bool DeleteControl(const int index) override;
		bool DeleteControl(IControl *control) override;
		bool DeleteControls() override;
		bool DetachControl(IControl *control) override;
		IControl *FindControl(const String &name, IControl *exclude = nullptr) override;

		void Repaint(const bool repaint_children) override;
		void Repaint(const RectF &rect, const bool convert) override;
		void Refresh(const bool refresh_children) override; // Do nothing. Derived controls which use canvas should override this method and clear canvas

		bool BringToFront() override;
		bool BringUp() override;
		bool BringDown() override;
		bool BringBefore(IControl *control) override;
		bool BringBefore(const int index) override;
		bool BringAfter(IControl *control) override;
		bool BringAfter(const int index) override;

		IControlService *QueryService() override final;

		PointF FormToLocal(const PointF &pos) override;
		PointF LocalToForm(const PointF &pos) override;

		// Hint actions
		bool ShowHint(const PointF &position) override;

		/**
		Constructor
		@param class_name Class name of the control(without "C" at the beginning)
		@param accept_form Whether the control could be placed onto a form directly
		@param accept_control Whether the control could be placed onto another controls
		@param accept_controls Whether another controls could be placed onto the control
		@param accept_focus Whether the control could be focused and receive keyboard input
		@param accept_modal Whether the control could be modal
		@param tab_stop Whether the control could be focused by Tab and Shift+Tab when it is on form, enabled, and accept focus
		@param design_dpi DPI at which the control was designed
		*/
		CControl(
			const String &class_name,
			const bool accept_form,
			const bool accept_control,
			const bool accept_controls,
			const bool accept_focus,
			const bool accept_modal,
			const bool tab_stop,
			const Point &design_dpi = DesignDPI);
		~CControl() override;
	};
}