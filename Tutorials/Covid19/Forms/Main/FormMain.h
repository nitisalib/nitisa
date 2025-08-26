#pragma once

#include "IFormMain.h" // Include form prototype header file

namespace nitisa
{
	namespace app
	{
		class CFormMain :public IFormMain // Declare form class derived from form prototype class
		{
		private:
			struct Day // Structure describes values we are going to have for each day
			{
				float Vulnerable; // Number of people available to infect
				float Infected; // Number of people infected this day
				float CurrentInfected; // Number of currently infected, but not yet infectious, people
				float CurrentInfectious; // Number of currently infectious people
				float CurrentSick; // Number currently sick, but not infectious anymore, people
				float TotalCases; // Total number of people infected till this day
				float TotalWell; // Total number of people recovered till this day
			};

			const size_t DAYS_TILL_INFECTIOUS{ 5 }; // Days from infection till person becomes infectious
			const size_t DAYS_TILL_SICK{ 5 + 7 }; // Days from infection till person becomes ill
			const size_t DAYS_TILL_WELL{ 5 + 7 + 14 }; // Days from infection till person becomes well again

			float m_fPopulation; // Initial population
			float m_fInfected; // Initial number of infected people
			float m_fInfectious; // Initial infectious rate
			std::vector<Day> m_aDays; // Statistic by day

			void ProcessDay(const size_t index); // Calculate specified by index day values
			// Update charts
			void UpdateMainChart();
			void UpdateCasesChart();
			void UpdateInfectiousChart();
		protected:
			// Event processing methods taken from the corresponding (protected) section of the form prototype class
			void FormMain_OnResize(IForm *sender) override;
			void ButtonCalculate_OnClick(IControl *sender) override;
		public:
			CFormMain(); // Constructor
		};

		extern CFormMain *FormMain; // Variable to store form instance pointer
	}
}