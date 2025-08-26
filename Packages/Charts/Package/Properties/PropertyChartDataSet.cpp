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
		CPropertyChartDataSet::CPropertyChartDataSet(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetter getter, FSetter setter, FUpdate update) :
			CProperty(list, parent, name, PropertyHandlerChartDataSet, skip, false),
			m_fGetter{ getter },
			m_fSetter{ setter },
			m_fUpdate{ update },
			m_bChanged{ false }
		{
			AddHeaderFile(L"Charts/Core/ChartDataSet.h");
		}
	#pragma endregion

	#pragma region IProperty getters
		String CPropertyChartDataSet::getPreview()
		{
			if (getValue())
				return ToString(getValue()->getDataCount()) + L" datas";
			return L"";
		}

		String CPropertyChartDataSet::getPreview(const String &state)
		{
			return L"";
		}

		bool CPropertyChartDataSet::isChanged()
		{
			return m_bChanged || getValue();
		}
	#pragma endregion

	#pragma region IProperty setters
		IProperty *CPropertyChartDataSet::setChanged(const bool value)
		{
			m_bChanged = value;
			return this;
		}
	#pragma endregion

	#pragma region IProperty methods
		bool CPropertyChartDataSet::Copy(IProperty *dest)
		{
			IPropertyChartDataSet *d{ cast<IPropertyChartDataSet*>(dest) };
			if (d)
			{
				IChartDataSet *dataset{ getValue() };
				if (dataset)
					dataset = dataset->Clone();
				d->setValue(dataset);
				return true;
			}
			return false;
		}

		void CPropertyChartDataSet::Save(Variant &dest)
		{
			if (getValue())
			{
				IChartDataSet *dataset{ getValue() };
				for (int i = 0; i < dataset->getDataCount(); i++)
				{
					Variant data;
					data[L"Name"] = dataset->getData(i)->getName();
					for (int j = 0; j < dataset->getData(i)->getCount(); j++)
					{
						Variant point;
						point[L"X"] = dataset->getData(i)->getX(j);
						point[L"Y"] = dataset->getData(i)->getY(j);
						point[L"Label"] = dataset->getData(i)->getLabel(j);
						data[L"Points"].push_back(point);
					}
					dest.push_back(data);
				}
			}
		}

		void CPropertyChartDataSet::Load(const Variant &src)
		{
			CChartDataSet *dataset{ new CChartDataSet() };
			for (auto v : src)
				if (v.second.isSet(L"Name") && v.second.isSet(L"Points"))
				{
					Variant items{ v.second.get(L"Points") };
					if (items.getType() == Variant::VariantType::Array && items.size() > 0)
					{
						CChartData *data{ new CChartData((String)v.second.get(L"Name")) };
						for (auto item : items)
							if (item.second.isSet(L"X") && item.second.isSet(L"Y") && item.second.isSet(L"Label"))
								data->AddPoint((float)item.second[L"X"], (float)item.second[L"Y"], (String)item.second[L"Label"]);
						dataset->AddData(data);
					}
				}
			if (dataset->getDataCount() > 0)
				setValue(dataset);
			else
				dataset->Release();
		}

		void CPropertyChartDataSet::Export(std::wofstream &f, const String &shift, const String &control)
		{
			if (getValue())
			{
				IChartDataSet *dataset{ getValue() };
				f << shift << L"{" << std::endl;
				f << shift << L"\t" << L"charts::CChartDataSet *dataset{ new " << L"charts::CChartDataSet() };" << std::endl;
				for (int i = 0; i < dataset->getDataCount(); i++)
					f << shift << L"\tdataset->AddData(new " << L"charts::CChartData({ " << DataToString(dataset->getData(i)) << L" }));" << std::endl;
				if (control.empty())
					f << shift << L"\tset" << m_sName << L"(dataset, true);" << std::endl;
				else
					f << shift << L"\t" << control << L"->set" << m_sName << L"(dataset, true);" << std::endl;
				f << shift << L"}" << std::endl;
			}
		}
	#pragma endregion

	#pragma region IPropertyChartDataSet getters
		IChartDataSet *CPropertyChartDataSet::getValue()
		{
			return m_fGetter(m_pParent);
		}
	#pragma endregion

	#pragma region IPropertyChartDataSet setters
		bool CPropertyChartDataSet::setValue(IChartDataSet *value)
		{
			return m_fSetter(m_pParent, value);
		}
	#pragma endregion

	#pragma region IPropertyChartDataSet methods
		void CPropertyChartDataSet::Update()
		{
			m_fUpdate(m_pParent);
		}
	#pragma endregion

	#pragma region Helpers
		String CPropertyChartDataSet::DataToString(IChartData *data)
		{
			String result;
			for (int i = 0; i < data->getCount(); i++)
			{
				if (i > 0)
					result += L", ";
				result += L"{ " + AsSourceCode(data->getX(i)) + L", " + AsSourceCode(data->getY(i)) + L", UTF8ToString(\"" + ReplaceAll(data->getLabel(i), EncodeEscape) + L"\") }";
			}
			return result;
		}
	#pragma endregion
	}
}