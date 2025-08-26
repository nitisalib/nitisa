// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/VertexFormat.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Math/PointF.h"
#include "../IView.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IForm;
	class IFramebuffer;
	class IModel;
	class IProgram;
	class IRenderer;
	class ITexture;
	class IVertexArray;

	class COpenGL;

	namespace opengl
	{
		class CViewService;

		class CView :public virtual IView, public CControl
		{
			friend CViewService;
		private:
			class CAxes
			{
			private:
				CView *m_pControl;
				bool m_bShowX;
				bool m_bShowY;
				bool m_bShowZ;
				PointF m_sXRange;
				PointF m_sYRange;
				PointF m_sZRange;
				Color m_sXColor;
				Color m_sYColor;
				Color m_sZColor;
				IVertexArray *m_pVertexArray;
				IProgram *m_pProgram;
				bool m_bGeometryValid;
				bool m_bProgramValid;
				PlatformHandle m_hUniformMatrix;

				static const AnsiString m_sVertexShader;
				static const AnsiString m_sFragmentShader;
				static const nitisa::VertexFormat m_sVertexFormat;
			public:
				CAxes(CView *control);

				bool isShowX() const;
				bool isShowY() const;
				bool isShowZ() const;
				PointF getXRange() const;
				PointF getYRange() const;
				PointF getZRange() const;
				Color getXColor() const;
				Color getYColor() const;
				Color getZColor() const;

				bool setShowX(const bool value);
				bool setShowY(const bool value);
				bool setShowZ(const bool value);
				bool setXRange(const PointF &value);
				bool setYRange(const PointF &value);
				bool setZRange(const PointF &value);
				bool setXColor(const Color &value);
				bool setYColor(const Color &value);
				bool setZColor(const Color &value);

				void FreeResources(COpenGL *graphics);
				void Render(COpenGL *graphics, ICamera *camera);
			};

			class CGrid
			{
			private:
				CView *m_pControl;
				bool m_bVisible;
				float m_fXRange;
				float m_fZRange;
				float m_fStep;
				Color m_sColor;
				IVertexArray *m_pVertexArray;
				IProgram *m_pProgram;
				bool m_bGeometryValid;
				bool m_bProgramValid;
				PlatformHandle m_hUniformColor;
				PlatformHandle m_hUniformMatrix;

				static const AnsiString m_sVertexShader;
				static const AnsiString m_sFragmentShader;
				static const nitisa::VertexFormat m_sVertexFormat;
			public:
				CGrid(CView *control);

				bool isVisible() const;
				float getXRange() const;
				float getZRange() const;
				float getStep() const;
				Color getColor() const;

				bool setVisible(const bool value);
				bool setXRange(const float value);
				bool setZRange(const float value);
				bool setStep(const float value);
				bool setColor(const Color &value);

				void FreeResources(COpenGL *graphics);
				void Render(COpenGL *graphics, ICamera *camera);
			};
		private:
			Color m_sBackgroundColor;
			float m_fTurnSpeed;
			float m_fMoveSpeed;
			float m_fMoveSlowMultiplier;
			float m_fMoveFastMultiplier;
			float m_fFOVStep;

			CAxes m_cAxes;
			CGrid m_cGrid;
			ICamera *m_pCamera;
			ITexture *m_pCanvas;
			ITexture *m_pDepthTexture;
			IFramebuffer *m_pFramebuffer;
			int m_iLockCount;
			bool m_bUpdateRequired;
			bool m_bProgramValid;
			IProgram *m_pProgram;
			PlatformHandle m_hUniformMatrixModel;
			PlatformHandle m_hUniformMatrixNormal;
			PlatformHandle m_hUniformMatrixCamera;
			PlatformHandle m_hUniformCameraPosition;

			static const AnsiString m_sProgramVertex;
			static const AnsiString m_sProgramFragment;

			void ForceUpdate();
			void ActivateProgram(COpenGL *graphics, IModel *model, ICamera *camera);
			void Render();
			void RenderError(IRenderer *renderer, const String &error);
			void RenderChildren(IControl *parent, COpenGL *graphics, IRenderer *renderer);
		public:
			// IControl getters
			bool isAcceptChild(IControl *control = nullptr) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// IView getters
			ICamera *getCamera() override;

			// IView setters
			bool setCamera(ICamera *value) override;

			CView();
			CView(IForm *parent);
			CView(IControl *parent);
			~CView() override;

			Color getBackgroundColor() const; // Return background color
			float getTurnSpeed() const; // Return rotate speed
			float getMoveSpeed() const; // Return move speed
			float getMoveSlowMultiplier() const; // Return slow down multiplier
			float getMoveFastMultiplier() const; // Return movement speed increase multiplier
			float getFOVStep() const; // Return field of view change multiplier

			bool setBackgroundColor(const Color &value); // Set background color
			bool setTurnSpeed(const float value); // Set rotate speed
			bool setMoveSpeed(const float value); // Set move speed
			bool setMoveSlowMultiplier(const float value); // Set slow down multiplier
			bool setMoveFastMultiplier(const float value); // Set movement speed increase multiplier
			bool setFOVStep(const float value); // Set field of view change multiplier

			bool isShowXAxis() const; // Return whether X-axis should be shown
			bool isShowYAxis() const; // Return whether Y-axis should be shown
			bool isShowZAxis() const; // Return whether Z-axis should be shown
			PointF getXAxisRange() const; // Return X-axis drawing range
			PointF getYAxisRange() const; // Return Y-axis drawing range
			PointF getZAxisRange() const; // Return Z-axis drawing range
			Color getXAxisColor() const; // Return X-axis color
			Color getYAxisColor() const; // Return Y-axis color
			Color getZAxisColor() const; // Return Z-axis color

			bool setShowXAxis(const bool value); // Set whether X-axis should be shown
			bool setShowYAxis(const bool value); // Set whether Y-axis should be shown
			bool setShowZAxis(const bool value); // Set whether Z-axis should be shown
			bool setXAxisRange(const PointF &value); // Set X-axis drawing range
			bool setYAxisRange(const PointF &value); // Set Y-axis drawing range
			bool setZAxisRange(const PointF &value); // Set Z-axis drawing range
			bool setXAxisColor(const Color &value); // Set X-axis color
			bool setYAxisColor(const Color &value); // Set Y-axis color
			bool setZAxisColor(const Color &value); // Set Z-axis color

			bool isShowGrid() const; // Return whether grid should be shown
			float getGridXRange() const; // Return grid X range
			float getGridZRange() const; // Return grid Z range
			float getGridStep() const; // Return grid step
			Color getGridColor() const; // Return grid color

			bool setShowGrid(const bool value); // Set whether grid should be shown
			bool setGridXRange(const float value); // Set grid X range
			bool setGridZRange(const float value); // Set grid Z range
			bool setGridStep(const float value); // Set grid step
			bool setGridColor(const Color &value); // Set grid color

			void LockUpdate(); // Prevent update while properties changing
			void UnlockUpdate(); // Allow update while properties chaning
		};
	}
}