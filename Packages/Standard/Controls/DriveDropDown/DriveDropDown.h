// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h"
#include "Nitisa/BuiltInControls/DropDown/BuiltInDropDownListItemOwner.h"
#include "Nitisa/BuiltInControls/IBuiltInDropDownListener.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../../ListItems/IListItemIcon.h"
#include "../IDriveDropDown.h"

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInDropDown;
	class IControl;
	class IForm;
	class IListItemOwner;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class IDirectoryTree;
		class IListItemIcon;

		class CDriveDropDownService;

		class CDriveDropDown :public virtual IDriveDropDown, public CControl
		{
			friend CDriveDropDownService;
		private:
			class CDropDown;

			class COwner :public virtual IListItemIconOwner, public CBuiltInDropDownListItemOwner
			{
			private:
				CDriveDropDown * m_pDropDown;
			public:
				ITexture * getIcon(IListItemIcon *item, RectF &part) override;

				COwner(CDropDown *dropdown, CDriveDropDown *drivedropdown);
			};

			class CDropDown :public CBuiltInDropDown
			{
			private:
				CDriveDropDown * m_pDropDown;
				COwner m_cOwner;
			public:
				IControl *getControl() override;
				State getState() override;

				IListItemOwner *QueryListItemOwner() override;

				CDropDown(CDriveDropDown *dropdown);
			};

			class CListener :public virtual IBuiltInDropDownListener
			{
			private:
				CDriveDropDown * m_pDropDown;
			public:
				CListener(CDriveDropDown *dropdown);

				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnTextChange(IBuiltInControl *sender) override;
				void NotifyOnSelect(IBuiltInControl *sender, const int index) override;
				void NotifyOnOpen(IBuiltInControl *sender) override;
				void NotifyOnClose(IBuiltInControl *sender) override;
			};
		private:
			IBuiltInDropDown * m_pDropDown;
			CListener m_cListener;
			IDirectoryTree *m_pDirectoryTree;

			bool m_bIgnoreKillCaptureMouse;

			IBuiltInDropDown *getDropDown();
			void UpdateDropDown();
			void UpdateFromStyle(IStyle *style);
			void Render();
			void RenderList();
		public:
			void(*OnSelect)(IControl *sender, const int index); // Event called when drive selected

			// // IControl methods
			void Refresh(const bool refresh_children) override;

			IControl *getControl(const PointF &position) override;
			RectF getClientRect() override;
			RectF getRenderRect() override;
			CursorType getCursor() override;
			int getDriveCount() override;
			String getDrive(const int index) override;
			int getSelectedDriveIndex() override;
			String getSelectedDrive() override;
			IDirectoryTree *getDirectoryTree() override;
			bool hasExtra() override;

			bool setDPI(const Point &value) override;
			bool setSelectedDriveIndex(const int value) override;
			bool setSelectedDrive(const String &value) override;
			bool setDirectoryTree(IDirectoryTree *value) override;

			bool Rescan() override;

			CDriveDropDown();
			CDriveDropDown(IForm *parent);
			CDriveDropDown(IControl *parent);
			~CDriveDropDown() override;

			CBuiltInDropDown::State getState(); // Return state of control
			bool isOpened(); // Return whether is opened
			// Layout getters
			CBuiltInDropDown::OpenDirection getOpenDirection();
			CBuiltInDropDown::ArrowArea getArrowArea();
			float getListWidth();
			float getListMaxHeight();
			float getArrowAreaSize();
			float getArrowSize();
			RectF getBorderWidth();
			RectF getBorderRadius();
			RectF getPadding();
			RectF getArrowBorderWidth();
			RectF getArrowBorderRadius();
			RectF getListBorderWidth();
			RectF getListBorderRadius();
			RectF getListPadding();
			Color getShadowColor(const CBuiltInDropDown::State state);
			PointF getShadowShift(const CBuiltInDropDown::State state);
			int getShadowRadius(const CBuiltInDropDown::State state);
			BorderColor getBorderColor(const CBuiltInDropDown::State state);
			Color getBackgroundColor(const CBuiltInDropDown::State state);
			Gradient *getBackgroundGradient(const CBuiltInDropDown::State state);
			BorderColor getArrowBorderColor(const CBuiltInDropDown::State state);
			Color getArrowBackgroundColor(const CBuiltInDropDown::State state);
			Gradient *getArrowBackgroundGradient(const CBuiltInDropDown::State state);
			Color getArrowColor(const CBuiltInDropDown::State state);
			BorderColor getListBorderColor();
			Color getListBackgroundColor();
			Gradient *getListBackgroundGradient();
			Color getListShadowColor();
			PointF getListShadowShift();
			int getListShadowRadius();

			bool setDropDown(IBuiltInDropDown *value); // Assign another built-in dropdown
			// Set layout properties
			bool setOpenDirection(const CBuiltInDropDown::OpenDirection value);
			bool setListWidth(const float value);
			bool setListMaxHeight(const float value);
			bool setArrowArea(const CBuiltInDropDown::ArrowArea value);
			bool setArrowAreaSize(const float value);
			bool setArrowSize(const float value);
			bool setBorderWidth(const RectF &value);
			bool setBorderRadius(const RectF &value);
			bool setPadding(const RectF &value);
			bool setArrowBorderWidth(const RectF &value);
			bool setArrowBorderRadius(const RectF &value);
			bool setListBorderWidth(const RectF &value);
			bool setListBorderRadius(const RectF &value);
			bool setListPadding(const RectF &value);
			bool setShadowColor(const CBuiltInDropDown::State state, const Color &value);
			bool setShadowShift(const CBuiltInDropDown::State state, const PointF &value);
			bool setShadowRadius(const CBuiltInDropDown::State state, const int value);
			bool setBorderColor(const CBuiltInDropDown::State state, const BorderColor &value);
			bool setLeftBorderColor(const CBuiltInDropDown::State state, const Color &value);
			bool setTopBorderColor(const CBuiltInDropDown::State state, const Color &value);
			bool setRightBorderColor(const CBuiltInDropDown::State state, const Color &value);
			bool setBottomBorderColor(const CBuiltInDropDown::State state, const Color &value);
			bool setBackgroundColor(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowBorderColor(const CBuiltInDropDown::State state, const BorderColor &value);
			bool setArrowLeftBorderColor(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowTopBorderColor(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowRightBorderColor(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowBottomBorderColor(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowBackgroundColor(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowColor(const CBuiltInDropDown::State state, const Color &value);
			bool setListBorderColor(const BorderColor &value);
			bool setListLeftBorderColor(const Color &value);
			bool setListTopBorderColor(const Color &value);
			bool setListRightBorderColor(const Color &value);
			bool setListBottomBorderColor(const Color &value);
			bool setListBackgroundColor(const Color &value);
			bool setListShadowColor(const Color &value);
			bool setListShadowShift(const PointF &value);
			bool setListShadowRadius(const int value);
			
			bool Open(); // Open list
			bool Close(); // Close list
		};
	}
}