#include "Platform/Core/Renderer.h" // Helper class CRenderer is declared here. It's being used to create renderer
#include "Platform/Core/Window.h" // Helper class CWindow is declared here. It's being used to create window

#include "Charts/Core/ChartData.h" // Helper class CChartData describing data for chart widgets is declared here

#include "FormMain.h" // Header file of the form

namespace nitisa
{
	namespace app
	{
		CFormMain *FormMain{ nullptr };

		// Constructor just calls parent class constructor giving him window and renderer
		CFormMain::CFormMain() :
			IFormMain(CWindow::Create(), CRenderer::Create())
		{

		}

		// When form's size is changed we change chart widgets height so all the three widgets have the same height
		void CFormMain::FormMain_OnResize(IForm *sender)
		{
			float area_height{ ntl::Max<float>(0, (float)getClientHeight()) }; // Form's free space height
			m_pSplineChartMain->setHeight(area_height / 3); // Change height of the top chart widget
			m_pSplineChartInfectious->setHeight(area_height / 3); // Change height of the bottom chart widget
			// We don't need to change chart widget in the middle height because it is changed automatically due to its alignment (its Client)
		}

		// Perform calculations when user clicks on Calculate button
		void CFormMain::ButtonCalculate_OnClick(IControl *sender)
		{
			// Store initial values into members to avoid calling widgets' methods many times later
			m_fPopulation = (float)m_pUpDownPopulation->getValue();
			m_fInfected = (float)m_pUpDownInfected->getValue();
			m_fInfectious = m_pUpDownExInfectious->getValue();
			// Resize days array accordingly to specified day count
			m_aDays.resize(m_pUpDownDays->getValue());
			// Fill first day values
			m_aDays[0].Vulnerable = m_fPopulation; // All population is vulnerable at the beginning
			m_aDays[0].Infected = m_fInfected; // First day infected people count is equal to the value specified in parameters
			m_aDays[0].CurrentInfected = m_fInfected; // The same is for currently infected people
			m_aDays[0].CurrentInfectious = 0; // No infectious people at the first day
			m_aDays[0].CurrentSick = 0; // No sick people at the first day
			m_aDays[0].TotalCases = m_fInfected; // Total cases equals currently infected people
			m_aDays[0].TotalWell = 0; // No recovered people yet
			float max_sick{ 0 }, max_daily{ 0 }; // This variables will store maximum sick people and maximum daily new cases
			for (size_t i = 1; i < m_aDays.size(); i++) // For all days starting from the second one
			{
				ProcessDay(i); // Calculate this day values
				max_sick = ntl::Max<float>(max_sick, m_aDays[i].CurrentSick); // Update maximum sick people count
				max_daily = ntl::Max<float>(max_daily, m_aDays[i].Infected); // Update maximum daily new cases count
			}
			// Show data on charts
			UpdateMainChart();
			UpdateCasesChart();
			UpdateInfectiousChart();
			// Show final total cases in the edit widget below Calculate button as well as maximum values calculated above
			m_pEditTotalCases->setText(ToString(ntl::Round<int>(m_aDays[m_aDays.size() - 1].TotalCases)));
			m_pEditMaxSick->setText(ToString(ntl::Round<int>(max_sick)));
			m_pEditMaxDaily->setText(ToString(ntl::Round<int>(max_daily)));
		}

		void CFormMain::UpdateMainChart()
		{
			// Remove all existing from previous modeling data
			m_pSplineChartMain->getDataSet()->DeleteDatas();
			// Create data with specified sizes
			charts::CChartData *total_cases{ new charts::CChartData((int)m_aDays.size()) };
			charts::CChartData *current_sick{ new charts::CChartData((int)m_aDays.size()) };
			charts::CChartData *total_well{ new charts::CChartData((int)m_aDays.size()) };
			// Fill data
			for (size_t i = 0; i < m_aDays.size(); i++)
			{
				total_cases->setPoint((int)i, { (float)i, m_aDays[i].TotalCases, L"" });
				current_sick->setPoint((int)i, { (float)i, m_aDays[i].CurrentSick, L"" });
				total_well->setPoint((int)i, { (float)i, m_aDays[i].TotalWell, L"" });
			}
			// Add data to widget data set
			m_pSplineChartMain->getDataSet()->AddData(total_cases);
			m_pSplineChartMain->getDataSet()->AddData(current_sick);
			m_pSplineChartMain->getDataSet()->AddData(total_well);
			// Call widget update manually
			m_pSplineChartMain->Update();
		}

		void CFormMain::UpdateCasesChart()
		{
			m_pBarChartCases->getDataSet()->DeleteDatas();
			charts::CChartData *cases{ new charts::CChartData((int)m_aDays.size()) };
			for (size_t i = 0; i < m_aDays.size(); i++)
				cases->setPoint((int)i, { (float)i, m_aDays[i].Infected, L"" });
			m_pBarChartCases->getDataSet()->AddData(cases);
			m_pBarChartCases->Update();

		}

		void CFormMain::UpdateInfectiousChart()
		{
			m_pSplineChartInfectious->getDataSet()->DeleteDatas();
			charts::CChartData *infectious{ new charts::CChartData((int)m_aDays.size()) }, *line{ new charts::CChartData(2, 0, 1) };
			for (size_t i = 0; i < m_aDays.size(); i++)
				infectious->setPoint((int)i, { (float)i, m_fInfectious * m_aDays[i].Vulnerable / m_fPopulation, L"" });
			line->setX(0, 0);
			line->setX(1, (float)m_aDays.size() - 1);
			m_pSplineChartInfectious->getDataSet()->AddData(infectious);
			m_pSplineChartInfectious->getDataSet()->AddData(line);
			m_pSplineChartInfectious->setYRange(PointF{ 0, m_fInfectious + 1 }); // Update Y range
			m_pSplineChartInfectious->Update();
		}

		void CFormMain::ProcessDay(const size_t index)
		{
			m_aDays[index].Vulnerable = ntl::Max<float>(0, m_aDays[index - 1].Vulnerable - m_aDays[index - 1].Infected); // How many people are vulnerable this day
			m_aDays[index].Infected = m_aDays[index - 1].CurrentInfectious * m_fInfectious / (DAYS_TILL_SICK - DAYS_TILL_INFECTIOUS) * m_aDays[index].Vulnerable / m_fPopulation; // How many people get infected this day
			m_aDays[index].TotalCases = m_aDays[index - 1].TotalCases + m_aDays[index].Infected; // Update total cases
			
																								 // Calculate how many people are infected but not yet infectious this day
			m_aDays[index].CurrentInfected = m_aDays[index - 1].CurrentInfected + m_aDays[index].Infected; // Add number of people infected today
			if (index >= DAYS_TILL_INFECTIOUS)
			{
				// Decrease by number of people infected DAYS_TILL_INFECTIOUS days ago
				m_aDays[index].CurrentInfected = ntl::Max<float>(0, m_aDays[index].CurrentInfected - m_aDays[index - DAYS_TILL_INFECTIOUS].Infected);
			}
			
			// Calculate how many people are infectious this day
			m_aDays[index].CurrentInfectious = m_aDays[index - 1].CurrentInfectious;
			if (index >= DAYS_TILL_INFECTIOUS)
			{
				m_aDays[index].CurrentInfectious += m_aDays[index - DAYS_TILL_INFECTIOUS].Infected; // Increase by number of people got infected DAYS_TILL_INFECTIOUS days ago
				if (index >= DAYS_TILL_SICK)
				{
					// Decrease by number of people infected DAYS_TILL_SICK days ago
					m_aDays[index].CurrentInfectious = ntl::Max<float>(0, m_aDays[index].CurrentInfectious - m_aDays[index - DAYS_TILL_SICK].Infected);
				}
			}
			
			// Calculate how many people are sick this day
			m_aDays[index].CurrentSick = m_aDays[index - 1].CurrentSick;
			if (index >= DAYS_TILL_SICK)
			{
				m_aDays[index].CurrentSick += m_aDays[index - DAYS_TILL_SICK].Infected; // Increase by number of people got infected DAYS_TILL_SICK days ago
				if (index >= DAYS_TILL_WELL)
				{
					// Decrease by number of people infected DAYS_TILL_WELL days ago
					m_aDays[index].CurrentSick = ntl::Max<float>(0, m_aDays[index].CurrentSick - m_aDays[index - DAYS_TILL_WELL].Infected);
				}
			}
			
			// Calculate how many people are well again
			m_aDays[index].TotalWell = m_aDays[index - 1].TotalWell;
			if (index >= DAYS_TILL_WELL)
				m_aDays[index].TotalWell += m_aDays[index - DAYS_TILL_WELL].Infected;
		}
	}
}