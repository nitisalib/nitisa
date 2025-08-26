// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Variant.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Image.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IFormView.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class ITexture;

	namespace ide
	{
		class CFormViewService;

		class CFormView :public virtual IFormView, public CControl
		{
			friend CFormViewService;
		public:
			enum class State // Control states
			{
				Normal, // Normal
				Active // Child control is focused
			};
		private:
			struct BORDER
			{
				Image BitmapStart;
				Image BitmapMiddle;
				Image BitmapEnd;
				Image BitmapFill;
				ITexture *TextureStart;
				ITexture *TextureMiddle;
				ITexture *TextureEnd;
				ITexture *TextureFill;
				PointF Constraints;
				float Size;
			};

			enum class BorderType
			{
				Left,
				Top,
				Right,
				Bottom
			};

			struct LAYOUT
			{
				bool Landscape;
				BORDER Left;
				BORDER Top;
				BORDER Right;
				BORDER Bottom;
				RectF Constraints;
				bool Caption;
				RectF CaptionPadding;
				BorderType CaptionBorder;
			};
		private:
			LAYOUT m_sLayout;
			String m_sCaption;
			RectF m_sBorderWidth;
			BorderColor m_aBorderColor[(int)State::Active + 1];

			ITexture *m_pCanvas;

			void FreeLayoutTextures();
			void FreeBorderTextures(BORDER &border);
			void LoadBorder(Variant &config, BORDER &border, const String &path);
			void CalculateBorder(BORDER &border);
			bool TextureCreate(IRenderer *renderer, const Image &bitmap, ITexture **result, const bool edge);
			void Render();
			void RenderBorder(IRenderer *renderer);
			void RenderLeftBorder(IRenderer *renderer, BORDER &border);
			void RenderTopBorder(IRenderer *renderer, BORDER &border);
			void RenderRightBorder(IRenderer *renderer, BORDER &border);
			void RenderBottomBorder(IRenderer *renderer, BORDER &border);
			void RenderCaption(IRenderer *renderer);
		public:
			// IControl getters
			IControl *getControl(const int index) override;
			IControl *getControl(const String &name) override;
			IControl *getControl(const PointF &position) override;
			RectF getClientRect() override;
			CursorType getCursor() override;
			bool isAcceptChild(IControl *control) override; // Only IFormEditor child and only one is accepted

			void Refresh(const bool refresh_children) override;

			// IFormView getters
			String getCaption() override;

			// IFormView setters
			bool setCaption(const String &value) override;

			// IFormView methods
			bool LoadLayout(const String &filename) override;

			CFormView();
			CFormView(IControl *parent);
			CFormView(IForm *parent);

			const LAYOUT &getLayout() const; // Return layout
			RectF getBorderWidth() const; // Return border width
			BorderColor getBorderColor(const State state) const; // Return border color depending on state

			bool setClientSize(const PointF &value); // Set client size
			bool setBorderWidth(const RectF &value); // Set border width
			bool setBorderColor(const State state, const BorderColor &value); // Set border color depending on state
		};
	}
}