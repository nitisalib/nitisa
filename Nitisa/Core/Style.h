// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Image/BorderColor.h"
#include "../Image/Color.h"
#include "../Image/Gradient.h"
#include "../Interfaces/IStyle.h"
#include "../Math/Point.h"
#include "../Math/PointB.h"
#include "../Math/PointF.h"
#include "../Math/Rect.h"
#include "../Math/RectB.h"
#include "../Math/RectF.h"
#include "Strings.h"
#include <vector>

namespace nitisa
{
	class IStyleFont;
	class IStyleImage;
	class IStyleSkin;

	class CStyleFont;
	class CStyleImage;
	class CStyleSkin;

	class CStyle :public virtual IStyle
	{
	private:
		enum class OptionType
		{
			String,
			Integer,
			Float,
			Bool,
			Rect,
			RectF,
			RectB,
			BorderColor,
			Point,
			PointF,
			PointB,
			Color,
			Gradient,
			UInt
		};

		struct OPTION
		{
			String Name;
			OptionType Type;
			String ValueS;
			Gradient ValueG;
			union
			{
				int ValueI;
				float ValueF;
				bool ValueB;
				Rect ValueRect;
				RectF ValueRectF;
				RectB ValueRectB;
				BorderColor ValueBorderColor;
				Point ValuePoint;
				PointF ValuePointF;
				PointB ValuePointB;
				Color ValueC;
				unsigned int ValueUInt;
			};

			OPTION();
		};

		std::vector<CStyleImage*> m_aImages;
		std::vector<CStyleSkin*> m_aSkins;
		std::vector<CStyleFont*> m_aFonts;
		std::vector<OPTION*> m_aOptions;
		bool m_bIsImagesSorted;
		bool m_bIsSkinsSorted;
		bool m_bIsFontsSorted;
		bool m_bIsOptionsSorted;

		void SortImages();
		void SortSkins();
		void SortFonts();
		void SortOptions();
		int FindImageIndex(const String &name);
		int FindSkinIndex(const String &name);
		int FindFontIndex(const String &name);
		int FindOptionIndex(const String &name);
	public:
		int getImageCount() override;
		IStyleImage *getImage(const int index) override;
		IStyleImage *getImage(const String &name) override;
		int getSkinCount() override;
		IStyleSkin *getSkin(const int index) override;
		IStyleSkin *getSkin(const String &name) override;
		int getFontCount() override;
		IStyleFont *getFont(const int index) override;
		IStyleFont *getFont(const String &name) override;
		int getOptionCount() override;
		bool getOption(const String &name, String &value) override;
		bool getOption(const String &name, int &value) override;
		bool getOption(const String &name, float &value) override;
		bool getOption(const String &name, bool &value) override;
		bool getOption(const String &name, Rect &value) override;
		bool getOption(const String &name, RectF &value) override;
		bool getOption(const String &name, RectB &value) override;
		bool getOption(const String &name, BorderColor &value) override;
		bool getOption(const String &name, Color &value) override;
		bool getOption(const String &name, Point &value) override;
		bool getOption(const String &name, PointF &value) override;
		bool getOption(const String &name, PointB &value) override;
		bool getOption(const String &name, Gradient &value) override;
		bool getOption(const String &name, unsigned int &value) override;

		void Release() override;

		bool setOption(const String &name, const String &value); // Set option with String type value
		bool setOption(const String &name, const int value); // Set option with int type value
		bool setOption(const String &name, const float value); // Set option with float type value
		bool setOption(const String &name, const bool value); // Set option with bool type value
		bool setOption(const String &name, const Rect &value); // Set option with Rect type value
		bool setOption(const String &name, const RectF &value); // Set option with RectF type value
		bool setOption(const String &name, const RectB &value); // Set option with RectB type value
		bool setOption(const String &name, const BorderColor &value); // Set option with BorderColor type value
		bool setOption(const String &name, const Point &value); // Set option with Point type value
		bool setOption(const String &name, const PointF &value); // Set option with PointF type value
		bool setOption(const String &name, const PointB &value); // Set option with PointB type value
		bool setOption(const String &name, const Color &value); // Set option with Color type value
		bool setOption(const String &name, const Gradient &value); // Set option with Gradient type value
		bool setOption(const String &name, const unsigned int value); // Set option with unsigned int type value

		CStyle(const String &class_name);
		virtual ~CStyle();

		bool AddImage(CStyleImage *image); // Add image
		bool AddSkin(CStyleSkin *skin); // Add skin
		bool AddFont(CStyleFont *font); // Add font
	};
}