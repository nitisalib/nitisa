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
#pragma region Constructor
	Gradient::Gradient() :
		CFeedback(nullptr),
		m_eType{ GradientType::Vertical },
		m_bSorted{ true }
	{

	}

	Gradient::Gradient(IFeedbackListener *listener) :
		CFeedback(listener),
		m_eType{ GradientType::Vertical },
		m_bSorted{ true }
	{

	}

	Gradient::Gradient(const GradientType type, const Color1DArray &points):
		CFeedback(nullptr),
		m_eType{ type },
		m_aPoints{ points },
		m_bSorted{ points.size() == 0 }
	{

	}

	Gradient::Gradient(const Gradient &other) :
		CFeedback(nullptr)
	{
		m_aPoints = other.m_aPoints;
		m_aSortedPoints = other.m_aSortedPoints;
		m_eType = other.m_eType;
		m_bSorted = other.m_bSorted;
	}

	Gradient::Gradient(Gradient &&other) :
		CFeedback(nullptr)
	{
		m_aPoints = std::move(other.m_aPoints);
		m_aSortedPoints = std::move(other.m_aSortedPoints);
		m_eType = other.m_eType;
		m_bSorted = other.m_bSorted;
	}
#pragma endregion

#pragma region Getters
	int Gradient::getPointCount() const
	{
		return (int)m_aPoints.size();
	}

	Color1D Gradient::getPoint(const int index) const
	{
		if (index >= 0 && index < (int)m_aPoints.size())
			return m_aPoints[(size_t)index];
		return Color1D{ 0, Color{ 0, 0, 0, 0 } };
	}

	Color Gradient::getColor(float position)
	{
		position = ntl::Clamp<float>(position, 0.0f, 1.0f);
		if (m_aPoints.size() >= 2)
		{
			Sort();
			int i1{ 0 }, i2{ 1 }, i;
			float d{ position }, t;
			for (i = 1; i < (int)m_aSortedPoints.size(); i++)
				if (m_aSortedPoints[i].Position >= d)
				{
					i1 = i - 1;
					i2 = i;
					break;
				}
			if (ntl::IsEqual<float>(m_aSortedPoints[i2].Position, m_aSortedPoints[i1].Position))
				t = 0;
			else
				t = (d - m_aSortedPoints[i1].Position) / (m_aSortedPoints[i2].Position - m_aSortedPoints[i1].Position);
			Color c1{ m_aSortedPoints[i1].Color }, c2{ m_aSortedPoints[i2].Color };
			return Color{
				(unsigned char)(c1.R * (1 - t) + c2.R * t),
				(unsigned char)(c1.G * (1 - t) + c2.G * t),
				(unsigned char)(c1.B * (1 - t) + c2.B * t),
				(unsigned char)(c1.A * (1 - t) + c2.A * t) };
		}
		if (m_aPoints.size() == 1)
			return m_aPoints[0].Color;
		return Color{ 0, 0, 0, 0 };
	}

	const Color1DArray &Gradient::getSortedPoints()
	{
		Sort();
		return m_aSortedPoints;
	}
#pragma endregion

#pragma region Setters
	bool Gradient::setType(const GradientType value)
	{
		if (value != m_eType)
		{
			m_eType = value;
			if (m_pListener)
				m_pListener->NotifyOnChange();
			return true;
		}
		return false;
	}

	bool Gradient::setPointCount(const int value)
	{
		if (value < 0 || value == (int)m_aPoints.size())
			return false;
		if (m_aPoints.size() > 0)
		{
			m_aPoints.clear();
			m_aSortedPoints.clear();
		}
		if (value > 1)
		{
			for (int i = 0; i < value; i++)
			{
				m_aPoints.push_back(Color1D{ (float)i / float(value - 1), Color{ 0, 0, 0, 0 } });
				m_aSortedPoints.push_back(Color1D{ (float)i / float(value - 1), Color{ 0, 0, 0, 0 } });
			}
		}
		else if (value > 0)
		{
			for (int i = 0; i < value; i++)
			{
				m_aPoints.push_back(Color1D{ 0, Color{ 0, 0, 0, 0 } });
				m_aSortedPoints.push_back(Color1D{ 0, Color{ 0, 0, 0, 0 } });
			}
		}
		m_bSorted = true;
		if (m_pListener)
			m_pListener->NotifyOnChange();
		return true;
	}

	bool Gradient::setPoints(const int count, Color1D *points)
	{
		if (count < 0 || count == 1 || (count >= 2 && !points))
			return false;
		if (m_aPoints.size() > 0)
		{
			m_aPoints.clear();
			m_aSortedPoints.clear();
			m_bSorted = true;
		}
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
				m_aPoints.push_back(points[i]);
			m_bSorted = false;
		}
		if (m_pListener)
			m_pListener->NotifyOnChange();
		return true;
	}

	bool Gradient::setPoint(const int index, const Color1D &value)
	{
		if (index < 0 || index >= (int)m_aPoints.size() || IsEqual(value, m_aPoints[(size_t)index]))
			return false;
		m_aPoints[(size_t)index] = value;
		m_bSorted = false;
		if (m_pListener)
			m_pListener->NotifyOnChange();
		return true;
	}

	bool Gradient::setPoint(const int index, const float position, const Color color)
	{
		if (index < 0 || index >= (int)m_aPoints.size() || (ntl::IsEqual<float>(position, m_aPoints[(size_t)index].Position) && color == m_aPoints[(size_t)index].Color))
			return false;
		m_aPoints[(size_t)index].Position = position;
		m_aPoints[(size_t)index].Color = color;
		m_bSorted = false;
		if (m_pListener)
			m_pListener->NotifyOnChange();
		return true;
	}

	bool Gradient::setPointPosition(const int index, const float position)
	{
		if (index < 0 || index >= (int)m_aPoints.size() || ntl::IsEqual<float>(position, m_aPoints[(size_t)index].Position))
			return false;
		m_aPoints[(size_t)index].Position = position;
		m_bSorted = false;
		if (m_pListener)
			m_pListener->NotifyOnChange();
		return true;
	}

	bool Gradient::setPointColor(const int index, const Color color)
	{
		if (index < 0 || index >= (int)m_aPoints.size() || color == m_aPoints[(size_t)index].Color)
			return false;
		m_aPoints[(size_t)index].Color = color;
		m_bSorted = false;
		if (m_pListener)
			m_pListener->NotifyOnChange();
		return true;
	}

	bool Gradient::setPoints(const Color1DArray &points)
	{
		if (points.size() == 1)
			return false;
		m_aPoints = points;
		m_bSorted = m_aPoints.size() == 0;
		if (m_pListener)
			m_pListener->NotifyOnChange();
		return true;
	}
#pragma endregion

#pragma region Helpers
	void Gradient::Sort()
	{
		if (!m_bSorted)
		{
			m_aSortedPoints = m_aPoints;
			std::sort(m_aSortedPoints.begin(), m_aSortedPoints.end(), [](const Color1D &a, const Color1D &b) { return a.Position < b.Position; });
			m_bSorted = true;
		}
	}

	void Gradient::AddPoint(const float position, const Color &color)
	{
		m_aPoints.push_back({ position, color });
		m_bSorted = false;
	}

	bool Gradient::DeletePoint(const int index)
	{
		if (index >= 0 && index < (int)m_aPoints.size())
		{
			m_aPoints.erase(m_aPoints.begin() + index);
			m_bSorted = false;
			if (m_pListener)
				m_pListener->NotifyOnChange();
			return true;
		}
		return false;
	}

	bool Gradient::Clear()
	{
		if (m_aPoints.size() > 0)
		{
			m_aPoints.clear();
			m_bSorted = true;
			if (m_pListener)
				m_pListener->NotifyOnChange();
			return true;
		}
		return false;
	}

	void Gradient::Reverse()
	{
		for (size_t i = 0; i < m_aPoints.size(); i++)
			m_aPoints[i].Position = 1 - m_aPoints[i].Position;
		m_bSorted = false;
	}
#pragma endregion

#pragma region Operators
	Gradient &Gradient::operator=(const Gradient &other)
	{
		m_aPoints = other.m_aPoints;
		m_aSortedPoints = other.m_aSortedPoints;
		m_eType = other.m_eType;
		m_bSorted = other.m_bSorted;
		if (m_pListener)
			m_pListener->NotifyOnChange();
		return *this;
	}

	Gradient &Gradient::operator=(Gradient &&other)
	{
		m_aPoints = std::move(other.m_aPoints);
		m_aSortedPoints = std::move(other.m_aSortedPoints);
		m_eType = other.m_eType;
		m_bSorted = other.m_bSorted;
		if (m_pListener)
			m_pListener->NotifyOnChange();
		return *this;
	}

	Gradient Gradient::operator-() const
	{
		Gradient result{ *this };
		for (size_t i = 0; i < result.m_aPoints.size(); i++)
			result.m_aPoints[i].Position = 1 - result.m_aPoints[i].Position;
		result.m_bSorted = false;
		return result;
	}

	bool Gradient::isEqual(Gradient &other, const float tolerance)
	{
		if (other.m_eType != m_eType || m_aPoints.size() != other.m_aPoints.size())
			return false;
		Sort();
		other.Sort();
		auto p1{ m_aSortedPoints.begin() };
		auto p2{ other.m_aSortedPoints.begin() };
		while (p1 != m_aSortedPoints.end())
		{
			if (IsNotEqual(*p1, *p2, tolerance))
				return false;
			p1++;
			p2++;
		}
		return true;
	}

	bool Gradient::isNotEqual(Gradient &other, const float tolerance)
	{
		if (other.m_eType != m_eType || m_aPoints.size() != other.m_aPoints.size())
			return true;
		Sort();
		other.Sort();
		auto p1{ m_aSortedPoints.begin() };
		auto p2{ other.m_aSortedPoints.begin() };
		while (p1 != m_aSortedPoints.end())
		{
			if (IsNotEqual(*p1, *p2, tolerance))
				return true;
			p1++;
			p2++;
		}
		return false;
	}
#pragma endregion

#pragma region Standalone operators
	std::wostream &operator<<(std::wostream &stream, const Gradient &a)
	{
		stream << L"{ ";
		for (auto point : a.m_aPoints)
			stream << L"Color1D{ " << AsSourceCode(point.Position) << L", Color" << point.Color << L" }, ";
		stream << L"}";
		return stream;
	}
#pragma endregion

#pragma region Functions
	String AsSourceCode(const Gradient &a)
	{
		String result{ L"Color1DArray{ " };
		for (int i = 0; i < a.getPointCount(); i++)
			if (i > 0)
				result += L", Color1D{ " + AsSourceCode(a.getPoint(i).Position) + L", " + AsSourceCode(a.getPoint(i).Color) + L" }";
			else
				result += L"Color1D{ " + AsSourceCode(a.getPoint(i).Position) + L", " + AsSourceCode(a.getPoint(i).Color) + L" }";
		if (a.getPointCount() > 0)
			return result + L" }";
		return result + L"}";
	}
#pragma endregion

#pragma region Functions
	void GradientToVariant(Gradient &gradient, Variant &out)
	{
		out.Reset();
		out[L"Type"] = (int)gradient.Type;
		for (int i = 0; i < gradient.getPointCount(); i++)
		{
			Variant p;
			p[L"Position"] = gradient.getPoint(i).Position;
			p[L"Color"] = ToVariant(gradient.getPoint(i).Color);
			out[L"Points"].push_back(p);
		}
	}

	void VariantToGradient(Gradient &gradient, const Variant &value)
	{
		if (value.isSet(L"Type"))
			gradient.setType((GradientType)(int)value.get(L"Type"));
		gradient.setPointCount((int)value.get(L"Points").size());
		for (int i = 0; i < (int)value.get(L"Points").size(); i++)
		{
			Variant p{ value.get(L"Points").get(i) };
			if (p.isSet(L"Position"))
				gradient.setPointPosition(i, (float)p.get(L"Position"));
			if (p.isSet(L"Color") && p.get(L"Color").getType() == Variant::VariantType::Array && p.get(L"Color").size() == 4)
			{
				Color c;
				FromVariant(p.get(L"Color"), c);
				gradient.setPointColor(i, c);
			}
		}
	}
#pragma endregion
}