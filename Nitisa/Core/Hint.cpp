// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region CTimerListener
	CHint::CTimerListener::CTimerListener(CHint *hint) :
		m_pHint{ hint }
	{

	}

	void CHint::CTimerListener::NotifyOnTimer(const PlatformHandle id)
	{
		auto now{ std::chrono::steady_clock::now() };
		std::chrono::milliseconds duration{ std::chrono::duration_cast<std::chrono::milliseconds>(now - m_pHint->m_sStartTime) };
		switch (m_pHint->m_eState)
		{
		case StateType::Showing:
			if ((float)duration.count() > m_pHint->m_fIntervalShowing * 1000)
			{
				m_pHint->m_eState = StateType::Visible;
				m_pHint->m_sStartTime = now;
			}
			break;
		case StateType::Visible:
			if ((float)duration.count() > m_pHint->m_fIntervalVisible * 1000)
			{
				m_pHint->m_eState = m_pHint->m_fIntervalHiding > 0 ? StateType::Hiding : StateType::Hidden;
				m_pHint->m_sStartTime = now;
			}
			break;
		case StateType::Hiding:
			if ((float)duration.count() > m_pHint->m_fIntervalHiding * 1000)
				m_pHint->m_eState = StateType::Hidden;
			break;
		default:
			break;
		}
		if (m_pHint->m_eState == StateType::Hidden)
		{
			m_pHint->m_pForm->DeleteTimer(m_pHint->m_hTimer);
			m_pHint->m_hTimer = nullptr;
			if (m_pHint->m_pRenderTarget && m_pHint->m_pRenderTarget->isValid())
				m_pHint->m_pRenderTarget->setValid(false);
		}
		if (m_pHint->m_eState != StateType::Visible || m_pHint->m_eLastState != m_pHint->m_eState)
			m_pHint->m_pForm->Repaint(m_pHint->m_sRect);
		m_pHint->m_eLastState = m_pHint->m_eState;
	}
#pragma endregion

#pragma region Constructor & destructor
	CHint::CHint() :
		m_eState{ StateType::Hidden },
		m_pForm{ nullptr },
		m_fBorderWidth{ 1 },
		m_fPadding{ 3 },
		m_sBorderColor{ 0, 0, 0, 255 },
		m_sBackgroundColor{ 255, 255, 255, 255 },
		m_cFont(nullptr),
		m_fIntervalShowing{ 0.5f },
		m_fIntervalVisible{ 5.0f },
		m_fIntervalHiding{ 0.5f },
		m_hTimer{ nullptr },
		m_pRenderTarget{ nullptr },
		m_pService{ nullptr },
		m_cTimerListener{ this }
	{

	}

	CHint::~CHint()
	{
		QueryService()->setForm(nullptr);
		if (m_pService)
			m_pService->Release();
	}

	void CHint::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Helpers
	void CHint::Render()
	{
		if (!m_pForm || !m_pForm->getRenderer() || m_eState == StateType::Hidden)
			return;
		IRenderer *renderer{ m_pForm->getRenderer() };
		RectF rect{ 0, 0, (float)m_sRect.width(), (float)m_sRect.height() };
		if (!m_pRenderTarget || !m_pRenderTarget->isValid())
		{
			if (!m_pRenderTarget)
				m_pRenderTarget = renderer->CreateTexture(ntl::Round<int>(m_sRect.width()), ntl::Round<int>(m_sRect.height()), 1, TextureFormat::RGBA, true);
			else
				m_pRenderTarget->setSize(ntl::Round<int>(m_sRect.width()), ntl::Round<int>(m_sRect.height()));
			if (m_pRenderTarget)
			{
				CStoreTarget s_target{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateTarget(m_pRenderTarget)
					->Clear(Color{ 0, 0, 0, 0 });
				// Draw background
				if (ntl::IsGreater<float>(m_fBorderWidth, 0))
				{
					BlockColors colors{
						m_sBorderColor,
						m_sBorderColor,
						m_sBorderColor,
						m_sBorderColor,
						m_sBackgroundColor,
						Color{ 0, 0, 0, 0 },
					};
					renderer->DrawBlock(rect, RectF{ m_fBorderWidth, m_fBorderWidth, m_fBorderWidth, m_fBorderWidth }, RectF{ 0, 0, 0, 0 }, colors);
				}
				else
					renderer->DrawRectangle(rect, m_sBackgroundColor);
				// Draw lines
				float x{ m_fBorderWidth + m_fPadding }, y{ m_fBorderWidth + m_fPadding };
				for (auto pos : m_aLines)
				{
					renderer
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(x, y, 0))
						->DrawText(pos, m_cFont.getPlatformFont(m_pForm->getRenderer()), m_cFont.Distance, m_cFont.Color);
					y += m_fLineHeight;
				}
				m_pRenderTarget->setValid(true);
			}
		}
		if (m_pRenderTarget)
		{
			// Render
			auto now{ std::chrono::steady_clock::now() };
			float transparency{ 1 };
			switch (m_eState)
			{
			case StateType::Showing:
				transparency = ntl::Min<float>(1.0f, (float)std::chrono::duration_cast<std::chrono::milliseconds>(now - m_sStartTime).count() / (m_fIntervalShowing * 1000));
				break;
			case StateType::Hiding:
				transparency = 1 - ntl::Min<float>(1.0f, (float)std::chrono::duration_cast<std::chrono::milliseconds>(now - m_sStartTime).count() / (m_fIntervalShowing * 1000));
				break;
			default:
				break;
			}
			CStorePrimitiveMatrix s_matrix{ renderer };
			renderer
				->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>((float)m_sRect.Left, (float)m_sRect.Top, 0))
				->DrawImage(m_pRenderTarget, transparency);
		}
	}

	void CHint::Show(const String &hint, const Point &pos, const Rect &client)
	{
		if (!m_pForm || !m_pForm->getRenderer())
			return;
		IPlatformFont *platform_font{ m_cFont.getPlatformFont(m_pForm->getRenderer()) };
		if (!platform_font)
			return;
		Hide(true);
		if (hint.empty())
			return;
		// Split on lines and calculate size
		m_aLines.clear();
		String s;
		std::wstringstream stream{ hint };
		PointF size{ 0, 0 };
		bool empty{ true };
		while (std::getline(stream, s, L'\n'))
		{
			m_aLines.push_back(s);
			PointF sz{ platform_font->getStringSize(s, m_cFont.Distance) };
			size.X = ntl::Max<float>(size.X, sz.X);
			size.Y = ntl::Max<float>(size.Y, sz.Y);
			if (s.length() > 0)
				empty = false;
		}
		if (empty || ntl::IsEqual<float>(size.X, 0) || ntl::IsEqual<float>(size.Y, 0))
			return;
		m_fLineHeight = size.Y;
		size.Y *= (float)m_aLines.size();
		size.X += (m_fBorderWidth + m_fPadding) * 2;
		size.Y += (m_fBorderWidth + m_fPadding) * 2;
		// Calculate rectangle
		m_sRect.Left = (float)pos.X;
		m_sRect.Top = (float)pos.Y;
		if (m_sRect.Left + size.X > (float)client.Right)
			m_sRect.Left = (float)client.Right - size.X;
		if (m_sRect.Left < 0)
			m_sRect.Left = 0;
		if (m_sRect.Top + size.Y > (float)client.Bottom)
			m_sRect.Top = (float)client.Bottom - size.Y;
		if (m_sRect.Top < 0)
			m_sRect.Top = 0;
		m_sRect.Right = m_sRect.Left + size.X;
		m_sRect.Bottom = m_sRect.Top + size.Y;
		// Start showing and render
		m_hTimer = m_pForm->CreateTimer(&m_cTimerListener, 0.03f);
		if (!m_hTimer)
			return;
		m_sStartTime = std::chrono::steady_clock::now();
		m_eState = m_eLastState = ntl::IsPositive<float>(m_fIntervalShowing) ? StateType::Showing : StateType::Visible;
		if (m_pRenderTarget)
			m_pRenderTarget->setValid(false);
		m_pForm->Repaint(m_sRect);
	}

	void CHint::Hide(const bool immediately)
	{
		if (m_eState != StateType::Hidden)
		{
			if (immediately || ntl::IsZero<float>(m_fIntervalHiding))
			{
				m_eState = m_eLastState = StateType::Hidden;
				if (m_hTimer)
				{
					m_pForm->DeleteTimer(m_hTimer);
					m_hTimer = nullptr;
				}
				if (m_pRenderTarget && m_pRenderTarget->isValid())
				{
					m_pForm->Repaint(m_sRect);
					m_pRenderTarget->setValid(false);
				}
			}
			else
			{
				m_eState = StateType::Hiding;
				m_sStartTime = std::chrono::steady_clock::now();
				m_pForm->Repaint(m_sRect);
			}
		}
	}

	IHintService *CHint::QueryService()
	{
		if (!m_pService)
			m_pService = new CHintService(this);
		return m_pService;
	}
#pragma endregion
}