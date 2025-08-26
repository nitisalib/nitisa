// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Consts.h"
#include "../Core/Feedback.h"
#include "../Core/Strings.h"
#include "../Core/Variant.h"
#include "Color.h"
#include "Color1D.h"
#include "Color1DArray.h"
#include "GradientType.h"
#include <iostream>

namespace nitisa
{
	class IFeedbackListener;

	class Gradient: public CFeedback
	{
		friend std::wostream &operator<<(std::wostream &stream, const Gradient &a);
	private:
		GradientType m_eType;
		Color1DArray m_aPoints;
		Color1DArray m_aSortedPoints;
		bool m_bSorted;

		void Sort();
	public:
		GradientType const &Type{ m_eType }; // Type

		int getPointCount() const; // Return point count
		Color1D getPoint(const int index) const; // Return point by index
		Color getColor(float position); // Return calculated color at specified position(position is in range 0..1)
		const Color1DArray &getSortedPoints(); // Return points sorted by position

		bool setType(const GradientType value); // Set type
		bool setPointCount(const int count); // Set point count
		bool setPoints(const int count, Color1D *points); // Set points
		bool setPoint(const int index, const Color1D &value); // Set point
		bool setPoint(const int index, const float position, const Color color); // Set point
		bool setPointPosition(const int index, const float position); // Set point position
		bool setPointColor(const int index, const Color color); // Set point color
		bool setPoints(const Color1DArray &points); // Set points

		Gradient();
		Gradient(IFeedbackListener *listener); // Create with listener
		Gradient(const GradientType type, const Color1DArray &points);
		Gradient(const Gradient &other);
		Gradient(Gradient &&other);

		Gradient &operator=(const Gradient &other);
		Gradient &operator=(Gradient &&other);
		Gradient operator-() const; // Return gradient with reversed point order (all point positions changed to 1 - position)

		bool isEqual(Gradient &other, const float tolerance = ntl::Tolerance<float>); // Check whether gradients are equal
		bool isNotEqual(Gradient &other, const float tolerance = ntl::Tolerance<float>); // Check whether gradients are not equal

		void AddPoint(const float position, const Color &color); // Add new point
		bool DeletePoint(const int index); // Delete point by index
		bool Clear(); // Delete all points
		void Reverse(); // Reverse point order (all point positions changed to 1 - position)
	};

	std::wostream &operator<<(std::wostream &stream, const Gradient &a); // Output as source code

	String AsSourceCode(const Gradient &a);
	void GradientToVariant(Gradient &gradient, Variant &out);
	void VariantToGradient(Gradient &gradient, const Variant &value);
}