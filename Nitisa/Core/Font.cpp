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
#pragma region CFont
	CFont::CFont() :
		CFeedbackEx{ nullptr },
		CFontProperties(),
		m_pPlatformFont{ nullptr }
	{
		
	}

	CFont::CFont(IFeedbackExListener *listener) :
		CFeedbackEx(listener),
		CFontProperties(),
		m_pPlatformFont{ nullptr }
	{
		
	}

	CFont::CFont(IFeedbackExListener *listener, IFont *font) :
		CFeedbackEx{ listener },
		CFontProperties(font),
		m_pPlatformFont{ nullptr }
	{
		
	}

	CFont::~CFont()
	{
		if (m_pPlatformFont)
			m_pPlatformFont->Release();
	}

	void CFont::Release()
	{
		delete this;
	}

	IPlatformFont *CFont::getPlatformFont(IRenderer *renderer)
	{
		if (renderer && !m_pPlatformFont)
		{
			IPlatformFont *font{ renderer->CreatePlatformFont(m_sFontName, m_iHeight, m_eWeight, m_bItalic, m_bUnderline, m_bStrikeOut, m_bMonospace) };
			if (font)
			{
				if (m_pPlatformFont)
					m_pPlatformFont->Release();
				m_pPlatformFont = font;
			}
		}
		return m_pPlatformFont;
	}

	bool CFont::setFontName(const String &value)
	{
		if (value != m_sFontName && FeedbackBefore())
		{
			if (m_pPlatformFont)
			{
				m_pPlatformFont->Release();
				m_pPlatformFont = nullptr;
			}
			m_sFontName = value;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CFont::setHeight(const int value)
	{
		if (value != m_iHeight && FeedbackBefore())
		{
			if (m_pPlatformFont)
			{
				m_pPlatformFont->Release();
				m_pPlatformFont = nullptr;
			}
			m_iHeight = value;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CFont::setWeight(const FontWeight value)
	{
		if (value != m_eWeight && FeedbackBefore())
		{
			if (m_pPlatformFont)
			{
				m_pPlatformFont->Release();
				m_pPlatformFont = nullptr;
			}
			m_eWeight = value;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CFont::setDistance(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_fDistance) && FeedbackBefore())
		{
			m_fDistance = value;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CFont::setColor(const nitisa::Color &value)
	{
		if (value != m_sColor && FeedbackBefore())
		{
			m_sColor = value;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CFont::setShadowShift(const PointF &value)
	{
		if (IsNotEqual(value, m_sShadowShift) && FeedbackBefore())
		{
			m_sShadowShift = value;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CFont::setShadowRadius(const int value)
	{
		if (value > 0 && value != m_iShadowRadius && FeedbackBefore())
		{
			m_iShadowRadius = value;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CFont::setShadowColor(const nitisa::Color &value)
	{
		if (value != m_sShadowColor && FeedbackBefore())
		{
			m_sShadowColor = value;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CFont::setItalic(const bool value)
	{
		if (value != m_bItalic && FeedbackBefore())
		{
			if (m_pPlatformFont)
			{
				m_pPlatformFont->Release();
				m_pPlatformFont = nullptr;
			}
			m_bItalic = value;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CFont::setUnderline(const bool value)
	{
		if (value != m_bUnderline && FeedbackBefore())
		{
			if (m_pPlatformFont)
			{
				m_pPlatformFont->Release();
				m_pPlatformFont = nullptr;
			}
			m_bUnderline = value;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CFont::setStrikeOut(const bool value)
	{
		if (value != m_bStrikeOut && FeedbackBefore())
		{
			if (m_pPlatformFont)
			{
				m_pPlatformFont->Release();
				m_pPlatformFont = nullptr;
			}
			m_bStrikeOut = value;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CFont::setMonospace(const bool value)
	{
		if (value != m_bMonospace && FeedbackBefore())
		{
			if (m_pPlatformFont)
			{
				m_pPlatformFont->Release();
				m_pPlatformFont = nullptr;
			}
			m_bMonospace = value;
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	bool CFont::Copy(IFontProperties *src)
	{
		if (src && src != this && !isEqual(src) && FeedbackBefore())
		{
			bool invalidate{
				src->FontName != m_sFontName ||
				src->Height != m_iHeight ||
				src->Weight != m_eWeight ||
				src->Italic != m_bItalic ||
				src->Underline != m_bUnderline ||
				src->StrikeOut != m_bStrikeOut ||
				src->Monospace != m_bMonospace
			};
			if (CFontProperties::Copy(src) && invalidate && m_pPlatformFont)
			{
				m_pPlatformFont->Release();
				m_pPlatformFont = nullptr;
			}
			if (m_pListener)
				m_pListener->NotifyOnAfterChange();
			return true;
		}
		return false;
	}

	void CFont::NotifyOnFreeResources()
	{
		if (m_pPlatformFont)
		{
			m_pPlatformFont->Release();
			m_pPlatformFont = nullptr;
		}
	}

	bool CFont::FeedbackBefore()
	{
		if (m_pListener)
		{
			bool allowed{ true };
			m_pListener->NotifyOnBeforeChange(allowed);
			return allowed;
		}
		return true;
	}
#pragma endregion

#pragma region Functions
	bool FontToVariant(IFontProperties *font, Variant &out)
	{
		if (font)
		{
			out.Reset();
			out[L"FontName"] = font->FontName;
			out[L"Height"] = font->Height;
			out[L"Weight"] = (int)font->Weight;
			out[L"Distance"] = font->Distance;
			out[L"Color"].push_back(Variant(font->Color.R));
			out[L"Color"].push_back(Variant(font->Color.G));
			out[L"Color"].push_back(Variant(font->Color.B));
			out[L"Color"].push_back(Variant(font->Color.A));
			out[L"ShadowShift"].push_back(Variant(font->ShadowShift.X));
			out[L"ShadowShift"].push_back(Variant(font->ShadowShift.Y));
			out[L"ShadowRadius"] = font->ShadowRadius;
			out[L"ShadowColor"].push_back(Variant(font->ShadowColor.R));
			out[L"ShadowColor"].push_back(Variant(font->ShadowColor.G));
			out[L"ShadowColor"].push_back(Variant(font->ShadowColor.B));
			out[L"ShadowColor"].push_back(Variant(font->ShadowColor.A));
			out[L"Italic"] = font->Italic;
			out[L"Underline"] = font->Underline;
			out[L"StrikeOut"] = font->StrikeOut;
			out[L"Monospace"] = font->Monospace;
			return true;
		}
		return false;
	}

	bool VariantToFont(IFont *font, const Variant &value)
	{
		bool result{ false };
		if (font && value.getType() == Variant::VariantType::Map)
		{
			if (value.isSet(L"FontName"))
				result = font->setFontName(String(value.get(L"FontName"))) || result;
			if (value.isSet(L"Height"))
				result = font->setHeight(int(value.get(L"Height"))) || result;
			if (value.isSet(L"Weight"))
				result = font->setWeight((FontWeight)(int)value.get(L"Weight")) || result;
			if (value.isSet(L"Distance"))
				result = font->setDistance(float(value.get(L"Distance"))) || result;
			if (value.isSet(L"Color") && value.get(L"Color").getType() == Variant::VariantType::Array && value.get(L"Color").size() == 4)
			{
				Color c;
				FromVariant(value.get(L"Color"), c);
				result = font->setColor(c) || result;
			}
			if (value.isSet(L"ShadowShift") && value.get(L"ShadowShift").getType() == Variant::VariantType::Array && value.get(L"ShadowShift").size() == 2)
			{
				PointF v;
				FromVariant(value.get(L"ShadowShift"), v);
				result = font->setShadowShift(v) || result;
			}
			if (value.isSet(L"ShadowRadius"))
				result = font->setShadowRadius(int(value.get(L"ShadowRadius"))) || result;
			if (value.isSet(L"ShadowColor") && value.get(L"ShadowColor").getType() == Variant::VariantType::Array && value.get(L"ShadowColor").size() == 4)
			{
				Color c;
				FromVariant(value.get(L"ShadowColor"), c);
				result = font->setShadowColor(c) || result;
			}
			if (value.isSet(L"Italic"))
				result = font->setItalic(bool(value.get(L"Italic"))) || result;
			if (value.isSet(L"Underline"))
				result = font->setUnderline(bool(value.get(L"Underline"))) || result;
			if (value.isSet(L"StrikeOut"))
				result = font->setStrikeOut(bool(value.get(L"StrikeOut"))) || result;
			if (value.isSet(L"Monospace"))
				result = font->setMonospace(bool(value.get(L"Monospace"))) || result;
		}
		return result;
	}
#pragma endregion
}