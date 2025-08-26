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
	namespace charts
	{
	#pragma region CGradientListener
		CCustomRadialChart::CGradientListener::CGradientListener(CCustomRadialChart *control) :
			m_pControl{ control }
		{

		}

		void CCustomRadialChart::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CCustomRadialChart::CCustomRadialChart(
			const String &class_name,
			const bool accept_form,
			const bool accept_control,
			const bool accept_controls,
			const bool accept_focus,
			const bool accept_modal,
			const bool tab_stop,
			const Point &design_dpi) :
			CControl(class_name, accept_form, accept_control, accept_controls, accept_focus, accept_modal, tab_stop, design_dpi),
			m_cGradientListener{ this },
			m_pDataSet{ nullptr },
			m_sBackgroundColor{ 255, 255, 255, 255 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_pCanvas{ nullptr },
			m_pHoveredData{ nullptr },
			m_iHoveredPoint{ -1 },
			m_bIgnoreGradient{ false }
		{
			OnHoverPoint = nullptr;
			OnLeavePoint = nullptr;

			setService(new CCustomRadialChartService(this), true);
		}

		CCustomRadialChart::~CCustomRadialChart()
		{
			if (m_pDataSet)
				m_pDataSet->Release();
		}
	#pragma endregion

	#pragma region IControl methods
		void CCustomRadialChart::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			CControl::Refresh(refresh_children);
		}
	#pragma endregion

	#pragma region IRadialChart getters
		IChartDataSet *CCustomRadialChart::getDataSet()
		{
			if (!m_pDataSet)
				m_pDataSet = new CChartDataSet();
			return m_pDataSet;
		}
	#pragma endregion

	#pragma region IRadialChart setters
		bool CCustomRadialChart::setDataSet(IChartDataSet *value, const bool release_old)
		{
			if (value != m_pDataSet)
			{
				if (m_pDataSet && release_old)
					m_pDataSet->Release();
				m_pDataSet = value;
				UpdateHoveredPoint();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IRadialChart methods
		void CCustomRadialChart::Update()
		{
			UpdateHoveredPoint();
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
		}
	#pragma endregion

	#pragma region Getters
		Color CCustomRadialChart::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CCustomRadialChart::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}
	#pragma endregion

	#pragma region Setters
		bool CCustomRadialChart::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				if (m_cBackgroundGradient.getPointCount() < 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CCustomRadialChart::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			m_bIgnoreGradient = false;
		}

		bool CCustomRadialChart::UpdateHoveredPoint()
		{
			if (getForm())
				return UpdateHoveredPoint((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition()));
			if (m_iHoveredPoint >= 0)
			{
				m_pHoveredData = nullptr;
				m_iHoveredPoint = -1;
				if (OnLeavePoint)
					OnLeavePoint(this);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CCustomRadialChart::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			RectF rect{ 0, 0, getWidth(), getHeight() };
			if (PrepareCanvas(renderer, &m_pCanvas, rect))
			{
				IBaseTexture *old{ renderer->ActiveTarget };
				renderer->ActivateTarget(m_pCanvas);
				renderer->Clear(Color{ 0, 0, 0, 0 });

				RenderBackground(renderer, rect);
				RenderDataSet(renderer, rect);

				renderer->ActivateTarget(old);
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}

		void CCustomRadialChart::RenderBackground(IRenderer *renderer, const RectF &rect)
		{
			if (m_cBackgroundGradient.getPointCount() >= 2)
				renderer->DrawGradient(rect, m_cBackgroundGradient);
			else if (m_sBackgroundColor.A > 0)
				renderer->DrawRectangle(rect, m_sBackgroundColor);
		}
	#pragma endregion
	}
}