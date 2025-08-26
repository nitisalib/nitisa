// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/CreateParams.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Core/Font.h"
#include "Nitisa/Core/Key.h"
#include "Nitisa/Core/ModalResult.h"
#include "Nitisa/Core/RotateOrder.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Transform.h"
#include "Nitisa/Core/TransformOrder.h"
#include "Nitisa/Core/WindowPosition.h"
#include "Nitisa/Core/WindowState.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Interfaces/IForm.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/Rect.h"
#include "Nitisa/Math/RectF.h"
#include "Nitisa/Math/Transform.h"
#include "../../Core/Types.h"

namespace nitisa
{
	class ICarent;
	class IComponent;
	class IControl;
	class IDialogBox;
	class IFeedbackExListener;
	class IFont;
	class IFormListener;
	class IFormService;
	class IHint;
	class IRenderer;
	class IStyle;
	class ITask;
	class ITimerListener;
	class ITransform;

	namespace fb
	{
		class CFormMain;

		class CFormEmpty :public virtual IForm
		{
		private:
			class CFormTransform :public CTransform
			{
			private:
				IForm *m_pForm;
				nitisa::Transform m_sTransform;
			public:
				CFormTransform(IForm *form, IFeedbackExListener *listener);

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
			};
		private:
			CFormMain *m_pForm;
			CFormTransform m_cTransform;
			CTransform m_cTransformControls;
			Color m_sBackgroundColor;
			CFont m_cFont;
			IStyle *m_pStyle;
			float m_fHintDelay;
			bool m_bShowHint;
			PointF m_sHintShift;
			RectF m_sBorderWidth;
			RectF m_sPadding;
			CreateParams m_sCreateParams;
		public:
			void(*OnBackgroundChange)(IForm *sender);
			void(*OnPaddingChange)(IForm *sender);

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
			RectF getBorderWidth() override;
			RectF getPadding() override;
			bool isShowHint() override;
			bool isFocusByLMB() override;
			bool isFocusByRMB() override;
			bool isFocusByMMB() override;
			bool isFocusByTab() override;
			bool isInterceptEnable() override;
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
			int getTaskCount() override;
			ITask *getTask(const int index) override;
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
			IControl *getInputControl() override;
			Point getDPI() override;
			IDialogBox *getActiveDialogBox() override;
			IFormListener *getListener() override;

			bool setName(const String &value) override;
			bool setHint(IHint *value) override;
			bool setStyle(IStyle *value) override;
			bool setFont(IFont *value, const bool copy = true) override;
			bool setCaret(ICaret *value) override;
			bool setModalControl(IControl *value) override;
			bool setFocusedControl(IControl *value) override;
			bool setActiveControl(IControl *value) override;
			bool setTransformControls(ITransform *value) override;
			bool setCursor(const CursorType value) override;
			bool setHintText(const String &value) override;
			bool setHintDelay(const float value) override;
			bool setHintShift(const PointF &value) override;
			bool setBackgroundColor(const Color &value) override;
			bool setBorderWidth(const RectF &value) override;
			bool setPadding(const RectF &value) override;
			bool setShowHint(const bool value) override;
			bool setFocusByLMB(const bool value) override;
			bool setFocusByMMB(const bool value) override;
			bool setFocusByRMB(const bool value) override;
			bool setFocusByTab(const bool value) override;
			bool setInterceptEnable(const bool value) override;
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
			bool setInputControl(IControl *value) override;
			void setService(IFormService *value, const bool release_prev) override;
			bool setDPI(const Point &value) override;
			bool setActiveDialogBox(IDialogBox *value) override;
			void setListener(IFormListener *value) override;

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

			bool AddTask(ITask *task) override;
			bool DeleteTask(const int index) override;
			bool DeleteTask(ITask *task) override;
			void DeleteTasks() override;
			void RunTasks() override;

			bool ShowHint(const String &text, const Point &position) override;
			bool ShowHint(IControl *control, const PointF &position) override;

			CFormEmpty(CFormMain *form);
			~CFormEmpty();

			bool HasSettings;
			SETTINGS Settings;
		};
	}
}