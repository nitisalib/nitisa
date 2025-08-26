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
	#pragma region Constructor & destructor
		CPropertyForexChartData::CPropertyForexChartData(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetter getter, FSetter setter, FUpdate update) :
			CProperty(list, parent, name, PropertyHandlerForexChartData, skip, false),
			m_fGetter{ getter },
			m_fSetter{ setter },
			m_fUpdate{ update },
			m_bChanged{ false }
		{
			AddHeaderFile(L"Charts/Controls/ForexChart/ForexChart.h");
		}
	#pragma endregion

	#pragma region IProperty getters
		String CPropertyForexChartData::getPreview()
		{
			if (getValue())
				return ToString(getValue()->getCount()) + L" points";
			return L"";
		}

		String CPropertyForexChartData::getPreview(const String &state)
		{
			return L"";
		}

		bool CPropertyForexChartData::isChanged()
		{
			return m_bChanged || getValue();
		}
	#pragma endregion

	#pragma region IProperty setters
		IProperty *CPropertyForexChartData::setChanged(const bool value)
		{
			m_bChanged = value;
			return this;
		}
	#pragma endregion

	#pragma region IProperty methods
		bool CPropertyForexChartData::Copy(IProperty *dest)
		{
			IPropertyForexChartData *d{ cast<IPropertyForexChartData*>(dest) };
			if (d)
			{
				IForexChart::IForexChartData *data{ getValue() };
				if (data)
					data = data->Clone();
				d->setValue(data);
				return true;
			}
			return false;
		}

		void CPropertyForexChartData::Save(Variant &dest)
		{
			if (getValue())
			{
				IForexChart::IForexChartData *data{ getValue() };
				for (int i = 0; i < data->getCount(); i++)
				{
					Variant point;
					point[L"DateTime"] = ToVariant(data->getDateTime(i));
					point[L"Open"] = data->getOpen(i);
					point[L"Close"] = data->getClose(i);
					point[L"Min"] = data->getMin(i);
					point[L"Max"] = data->getMax(i);
					dest.push_back(point);
				}
			}
		}

		void CPropertyForexChartData::Load(const Variant &src)
		{
			CForexChart::CForexChartData *data{ new CForexChart::CForexChartData() };
			for (auto v : src)
				if (v.second.isSet(L"DateTime") && v.second.isSet(L"Open") && v.second.isSet(L"Close") && v.second.isSet(L"Min") && v.second.isSet(L"Max"))
				{
					CDateTime dt;
					FromVariant(v.second.get(L"DateTime"), dt);
					data->Add(dt, (float)v.second.get(L"Open"), (float)v.second.get(L"Close"), (float)v.second.get(L"Min"), (float)v.second.get(L"Max"));

				}
			if (data->getCount() > 0)
				setValue(data);
			else
				data->Release();
		}

		void CPropertyForexChartData::Export(std::wofstream &f, const String &shift, const String &control)
		{
			if (getValue())
			{
				IForexChart::IForexChartData *data{ getValue() };
				if (control.empty())
					f << shift << L"set" << m_sName << L"(new " << L"charts::CForexChart::CForexChartData(std::vector<charts::CForexChart::CForexChartData::ChartData>{ " + DataToString(data, shift + L"\t") + L" }), true);" << std::endl;
				else
					f << shift << L"" << control << L"->set" << m_sName << L"(new " << L"charts::CForexChart::CForexChartData(std::vector<charts::CForexChart::CForexChartData::ChartData>{ " + DataToString(data, shift + L"\t") + L" }), true);" << std::endl;
			}
		}
	#pragma endregion

	#pragma region IPropertyForexChartData getters
		IForexChart::IForexChartData *CPropertyForexChartData::getValue()
		{
			return m_fGetter(m_pParent);
		}
	#pragma endregion

	#pragma region IPropertyForexChartData setters
		bool CPropertyForexChartData::setValue(IForexChart::IForexChartData *value)
		{
			return m_fSetter(m_pParent, value);
		}
	#pragma endregion

	#pragma region IPropertyForexChartData methods
		void CPropertyForexChartData::Update()
		{
			m_fUpdate(m_pParent);
		}
	#pragma endregion

	#pragma region Helpers
		String CPropertyForexChartData::DataToString(IForexChart::IForexChartData *data, const String &shift)
		{
			String result;
			for (int i = 0; i < data->getCount(); i++)
			{
				if (i > 0)
					result += L",\n";
				else
					result += L"\n";
				result +=
					shift + L"{ { " + ToString(data->getDateTime(i).getYear()) + L", " +
					ToString(data->getDateTime(i).getMonth()) + L", " +
					ToString(data->getDateTime(i).getDay()) + L", " +
					ToString(data->getDateTime(i).getHour()) + L", " +
					ToString(data->getDateTime(i).getMinute()) + L", " +
					ToString(data->getDateTime(i).getSecond()) + L" }, " +
					AsSourceCode(data->getOpen(i)) + L", " +
					AsSourceCode(data->getClose(i)) + L", " +
					AsSourceCode(data->getMin(i)) + L", " +
					AsSourceCode(data->getMax(i)) + L" }";
			}
			return result;
		}
	#pragma endregion
	}
}