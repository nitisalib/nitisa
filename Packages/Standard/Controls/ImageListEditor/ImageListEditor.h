// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/Scroll/BuiltInScroll.h"
#include "Nitisa/BuiltInControls/IBuiltInScrollListener.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IImageListEditor.h"
#include <vector>

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInScroll;
	class IControl;
	class IForm;
	class IPlatformFont;
	class IRenderer;
	class IStyle;
	class ITexture;

	class Image;

	struct Block;

	namespace standard
	{
		class IImageList;

		class CImageListEditorService;

		class CImageListEditor :public virtual IImageListEditor, public CControl
		{
			friend CImageListEditorService;
		public:
			enum class State // Possible control states
			{
				Normal,
				Hovered,
				Disabled
			};

			enum class ItemState // Possible states of items(images)
			{
				Normal,
				Hovered,
				Selected,
				SelectedHovered,
				SelectedDisabled,
				Disabled
			};
		private:
			enum class Element
			{
				None,
				Scroll,
				Item
			};

			struct ITEM
			{
				const Image *Bmp;
				bool Selected;
			};

			class CScroll :public CBuiltInScroll
			{
			private:
				CImageListEditor *m_pEditor;
			public:
				IControl *getControl() override;

				CScroll(CImageListEditor *editor);
			};

			class CScrollListener :public IBuiltInScrollListener
			{
			private:
				CImageListEditor *m_pEditor;
			public:
				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnScroll(IBuiltInControl *sender) override;

				CScrollListener(CImageListEditor *editor);
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CImageListEditor *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CImageListEditor *control);
			};
		private:
			CGradientListener m_cGradientListener;
			IImageList *m_pImageList;
			std::vector<ITEM> m_aItems;
			RectF m_sBorderWidth;
			RectF m_sBorderRadius;
			RectF m_sPadding;
			float m_fItemDistance; // Distance between items
			BorderColor m_aBorderColor[(int)State::Disabled + 1];
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];
			RectF m_aItemBorderWidth[(int)ItemState::Disabled + 1];
			BorderColor m_aItemBorderColor[(int)ItemState::Disabled + 1];
			Color m_aItemBackgroundColor[(int)ItemState::Disabled + 1];
			Gradient m_aItemBackgroundGradient[(int)ItemState::Disabled + 1];
			Color m_aItemTextColor[(int)ItemState::Disabled + 1];
			Color m_aItemTextShadowColor[(int)ItemState::Disabled + 1];
			PointF m_aItemTextShadowShift[(int)ItemState::Disabled + 1];
			int m_aItemTextShadowRadius[(int)ItemState::Disabled + 1];

			ITexture *m_pCanvas;
			IBuiltInScroll *m_pScroll;
			CScrollListener m_cScrollListener;
			bool m_bIgnoreGradient;
			Element m_eHoveredElement;
			int m_iHoveredItemIndex;

			void UpdateFromStyle(IStyle *style);
			RectF getRenderRect(const State state);
			IBuiltInScroll *getScroll();
			bool UpdateHoveredElement();
			bool UpdateHoveredElement(const PointF &position);
			void Update();
			void ImageListDetach(IImageList *imagelist);
			void ImageListChange(IImageList *imagelist);
			void Render();
			void RenderItems(IRenderer *renderer, IPlatformFont *pf, const Block *block);
			void RenderScroll(IRenderer *renderer, const Block *block);
		public:
			RectF getClientRect() override;
			RectF getRenderRect() override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			IImageList *getImageList() override;
			int getImageCount() override;
			Image *getImage(const int index) override;
			bool isImageSelected(const int index) override;

			bool setDPI(const Point &value) override;
			bool setImageList(IImageList *value) override;
			bool setImageSelected(const int index, const bool value) override;

			bool DeleteSelectedImages() override;

			CImageListEditor();
			CImageListEditor(IControl *parent);
			CImageListEditor(IForm *parent);
			~CImageListEditor() override;

			State getState(); // Return control state
			ItemState getItemState(const int index); // Return specified item state
			// Return layout properties
			RectF getBorderWidth() const;
			RectF getBorderRadius() const;
			RectF getPadding() const;
			float getItemDistance() const; // Return distance between items
			BorderColor getBorderColor(const State state) const;
			Color getBackgroundColor(const State state) const;
			Gradient *getBackgroundGradient(const State state);
			Color getShadowColor(const State state) const;
			PointF getShadowShift(const State state) const;
			int getShadowRadius(const State state) const;
			RectF getItemBorderWidth(const ItemState state) const;
			BorderColor getItemBorderColor(const ItemState state) const;
			Color getItemBackgroundColor(const ItemState state) const;
			Gradient *getItemBackgroundGradient(const ItemState state);
			Color getItemTextColor(const ItemState state) const;
			Color getItemTextShadowColor(const ItemState state) const;
			PointF getItemTextShadowShift(const ItemState state) const;
			int getItemTextShadowRadius(const ItemState state) const;

			bool setScroll(IBuiltInScroll *value); // Assign new built-in scroll
			// Set layout properties
			bool setBorderWidth(const RectF &value);
			bool setBorderRadius(const RectF &value);
			bool setPadding(const RectF &value);
			bool setItemDistance(const float value); // Set distance between items
			bool setBorderColor(const State state, const BorderColor &value);
			bool setBackgroundColor(const State state, const Color &value);
			bool setShadowColor(const State state, const Color &value);
			bool setShadowShift(const State state, const PointF &value);
			bool setShadowRadius(const State state, const int value);
			bool setItemBorderWidth(const ItemState state, const RectF &value);
			bool setItemBorderColor(const ItemState state, const BorderColor &value);
			bool setItemBackgroundColor(const ItemState state, const Color &value);
			bool setItemTextColor(const ItemState state, const Color &value);
			bool setItemTextShadowColor(const ItemState state, const Color &value);
			bool setItemTextShadowShift(const ItemState state, const PointF &value);
			bool setItemTextShadowRadius(const ItemState state, const int value);
		};
	}
}