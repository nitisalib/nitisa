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
	CCaret::CTimerListener::CTimerListener(CCaret *caret) :
		m_pCaret{ caret }
	{

	}

	void CCaret::CTimerListener::NotifyOnTimer(const PlatformHandle id)
	{
		if (m_pCaret->m_bVisible)
		{
			auto now{ std::chrono::steady_clock::now() };
			std::chrono::milliseconds duration{ std::chrono::duration_cast<std::chrono::milliseconds>(now - m_pCaret->m_sStart) };
			if (m_pCaret->m_bIsVisible && (float)duration.count() >= m_pCaret->m_fIntervalVisible * 1000)
			{
				m_pCaret->m_bIsVisible = false;
				m_pCaret->m_sStart = now;
				if (m_pCaret->m_pListener)
					m_pCaret->m_pListener->NotifyOnChange();
			}
			else if (!m_pCaret->m_bIsVisible && (float)duration.count() >= m_pCaret->m_fIntervalHidden * 1000)
			{
				m_pCaret->m_bIsVisible = true;
				m_pCaret->m_sStart = now;
				if (m_pCaret->m_pListener)
					m_pCaret->m_pListener->NotifyOnChange();
			}
		}
	}
#pragma endregion

#pragma region Constructor & destructor
	CCaret::CCaret(IFeedbackListener *listener) :
		CFeedback(listener),
		m_pRenderer{ nullptr },
		m_bVisible{ false },
		m_sSize{ 1, 1 },
		m_fIntervalVisible{ 0.5f },
		m_fIntervalHidden{ 0.5f },
		m_bIsVisible{ false },
		m_hTimer{ nullptr },
		m_sColor{ 0, 0, 0, 255 },
		m_bInversed{ true },
		m_cTimerListener{ this }
	{

	}

	CCaret::~CCaret()
	{
		setRenderer(nullptr);
	}

	void CCaret::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Getters
	IRenderer *CCaret::getRenderer()
	{
		return m_pRenderer;
	}

	bool CCaret::isVisible()
	{
		return m_bVisible;
	}

	PointF CCaret::getSize()
	{
		return m_sSize;
	}

	float CCaret::getIntervalVisible()
	{
		return m_fIntervalVisible;
	}

	float CCaret::getIntervalHidden()
	{
		return m_fIntervalHidden;
	}

	bool CCaret::isInversed()
	{
		return m_bInversed;
	}
#pragma endregion

#pragma region Setters
	bool CCaret::setRenderer(IRenderer *value)
	{
		if (value != m_pRenderer)
		{
			if (m_hTimer)
			{
				m_pRenderer->Window->DeleteTimer(m_hTimer);
				m_hTimer = nullptr;
			}
			m_pRenderer = value;
			if (m_pRenderer && m_pRenderer->Window && m_pRenderer->Window->isCreated())
			{
				m_hTimer = m_pRenderer->Window->CreateTimer(&m_cTimerListener, 0.03f);
				m_sStart = std::chrono::steady_clock::now();
			}
			return true;
		}
		return false;
	}

	bool CCaret::setVisible(const bool value)
	{
		if (value != m_bVisible)
		{
			m_bVisible = value;
			if (m_pListener)
				m_pListener->NotifyOnChange();
			return true;
		}
		return false;
	}

	bool CCaret::setSize(const PointF &value)
	{
		if (ntl::IsLessOrEqual<float>(value.X, 0) || ntl::IsLessOrEqual<float>(value.Y, 0))
			return false;
		if (IsNotEqual(value, m_sSize))
		{
			m_sSize = value;
			if (m_bVisible && m_pListener)
				m_pListener->NotifyOnChange();
			return true;
		}
		return false;
	}

	bool CCaret::setIntervalVisible(const float value)
	{
		if (ntl::IsLessOrEqual<float>(value, 0))
			return false;
		if (ntl::IsNotEqual<float>(value, m_fIntervalVisible))
		{
			m_fIntervalVisible = value;
			return true;
		}
		return false;
	}

	bool CCaret::setIntervalHidden(const float value)
	{
		if (ntl::IsLessOrEqual<float>(value, 0))
			return false;
		if (ntl::IsNotEqual<float>(value, m_fIntervalHidden))
		{
			m_fIntervalHidden = value;
			return true;
		}
		return false;
	}

	bool CCaret::setInversed(const bool value)
	{
		if (value != m_bInversed)
		{
			m_bInversed = value;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Helpers
	void CCaret::Render(const Mat4f &matrix)
	{
		if (m_bVisible && m_bIsVisible)
		{
			CStorePrimitiveMatrix s_matrix{ m_pRenderer };
			m_pRenderer->ActivatePrimitiveMatrix(&matrix);
			m_bInversed ? m_pRenderer->InversePixels(RectF{ 0, 0, m_sSize.X, m_sSize.Y }) : m_pRenderer->DrawRectangle(RectF{ 0, 0, m_sSize.X, m_sSize.Y }, m_sColor);
		}
	}
#pragma endregion
}