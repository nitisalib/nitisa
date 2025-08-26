// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Activators.h"
#include "Errors.h"
#include "Randomizers.h"
#include "Regularizers.h"
#include <chrono>
#include <initializer_list>
#include <vector>
#ifdef _DEBUG
#include <iostream>
#include <iomanip>
#endif

namespace nitisa
{
	namespace ai
	{
		/*
			Sources:
			http://neuralnetworksanddeeplearning.com/index.html
			https://github.com/tensorflow/playground
			https://github.com/sylbarth/mlp
			https://archive.ics.uci.edu/ml/index.php
			https://github.com/tensorflow/playground/blob/master/src/nn.ts
		*/
		template<class FLOAT>
		class TPerceptron
		{
		private:
			using size_type = typename std::vector<FLOAT>::size_type;

			struct WEIGHT
			{
				FLOAT Weight; // Initialized by TPerceptron constructor
				FLOAT Delta; // How much the weight has been changed on prev iteration
				FLOAT AccumulatedErrorDerivative;
				size_type AccumulatedErrorDerivativeCount;
				bool Dead;

				WEIGHT() :
					Delta{ 0 },
					AccumulatedErrorDerivative{ 0 },
					AccumulatedErrorDerivativeCount{ 0 },
					Dead{ false }
				{

				}
			};

			struct NEURON
			{
				std::vector<WEIGHT> Weights;
				IActivator<FLOAT> *Activator;
				FLOAT Amount; // SUM(weight * input)
				FLOAT Output;
				FLOAT Bias; // Initialized by TPerceptron constructor
				FLOAT OutputDerivative;
				FLOAT InputDerivative;
				FLOAT AccumulatedInputDerivative;
				size_type AccumulatedInputDerivativeCount;

				NEURON() :
					Activator{ nullptr },
					Amount{ 0 },
					Output{ 0 },
					OutputDerivative{ 0 },
					InputDerivative{ 0 },
					AccumulatedInputDerivative{ 0 },
					AccumulatedInputDerivativeCount{ 0 }
				{

				}

				void Randomize(IRandomizer<FLOAT> *randomizer)
				{
					for (auto &pos : Weights)
						pos.Weight = randomizer->Generate();
				}

				void Calculate(const std::vector<FLOAT> &inputs)
				{
					Amount = Bias;
					for (size_type i = 0; i < Weights.size(); i++)
						Amount += inputs[i] * Weights[i].Weight;
					Output = Activator->Calculate(Amount);
				}

				void Calculate(const std::vector<NEURON> &neurons)
				{
					Amount = Bias;
					for (size_type i = 0; i < Weights.size(); i++)
						Amount += neurons[i].Output * Weights[i].Weight;
					Output = Activator->Calculate(Amount);
				}
			};

			struct LAYER
			{
				std::vector<NEURON> Neurons;
			};

			std::vector<LAYER> m_aLayers;
			IErrorFunction<FLOAT> *m_pErrorFunction;
			IRegularizeFunction<FLOAT> *m_pRegularizeFunction;
			bool m_bLearning;
			size_type m_iBatchSize;
			FLOAT m_fLearnRate;
			FLOAT m_fRegularizeRate;
			FLOAT m_fMomentumRate;
			size_type m_iBatchCount;
		private:
			void ForwardInternal(const std::vector<FLOAT> &inputs)
			{
				// Set inputs
				auto &input_layer{ m_aLayers[0] };
				for (size_type neuron_index = 0; neuron_index < input_layer.Neurons.size(); neuron_index++)
					input_layer.Neurons[neuron_index].Output = inputs[neuron_index];

				// Calculate layers
				for (size_type layer_index = 1; layer_index < m_aLayers.size(); layer_index++)
					for (auto &neuron : m_aLayers[layer_index].Neurons)
						neuron.Calculate(m_aLayers[layer_index - 1].Neurons);
			}

			void BackwardInternal(const std::vector<FLOAT> &expected_output)
			{
				auto &output_layer{ m_aLayers[m_aLayers.size() - 1] };
				for (size_type neuron_index = 0; neuron_index < output_layer.Neurons.size(); neuron_index++)
				{
					auto &neuron{ output_layer.Neurons[neuron_index] };
					neuron.OutputDerivative = m_pErrorFunction->Derivative(neuron.Output, expected_output[neuron_index], neuron.Amount, neuron.Activator);
				}

				for (size_type layer_index = m_aLayers.size() - 1; layer_index >= 1; layer_index--)
				{
					auto &layer{ m_aLayers[layer_index] };
					for (auto &neuron : layer.Neurons)
					{
						if (layer_index == m_aLayers.size() - 1) // Special case: output derivative is completely calculated by error function in output layer
							neuron.InputDerivative = neuron.OutputDerivative;
						else
							neuron.InputDerivative = neuron.OutputDerivative * neuron.Activator->Derivative(neuron.Amount);
						neuron.AccumulatedInputDerivative += neuron.InputDerivative;
						neuron.AccumulatedInputDerivativeCount++;
					}
					for (auto &neuron : layer.Neurons)
						for (size_type weight_index = 0; weight_index < neuron.Weights.size(); weight_index++)
						{
							auto &weight{ neuron.Weights[weight_index] };
							if (weight.Dead)
								continue;
							weight.AccumulatedErrorDerivative += neuron.InputDerivative * m_aLayers[layer_index - 1].Neurons[weight_index].Output;
							weight.AccumulatedErrorDerivativeCount++;
						}
					if (layer_index > 1)
					{
						auto &prev_layer{ m_aLayers[layer_index - 1] };
						for (size_type neuron_index = 0; neuron_index < prev_layer.Neurons.size(); neuron_index++)
						{
							auto &neuron{ prev_layer.Neurons[neuron_index] };
							neuron.OutputDerivative = 0;
							for (size_type next_index = 0; next_index < layer.Neurons.size(); next_index++)
							{
								auto &n{ layer.Neurons[next_index] };
								neuron.OutputDerivative += n.Weights[neuron_index].Weight * n.InputDerivative;
							}
						}
					}
				}
			}

			void UpdateWeightsInternal()
			{
				for (size_type layer_index = 1; layer_index < m_aLayers.size(); layer_index++)
				{
					auto &layer{ m_aLayers[layer_index] };
					for (auto &neuron : layer.Neurons)
					{
						if (neuron.AccumulatedInputDerivativeCount > 0)
						{
							neuron.Bias -= m_fLearnRate * neuron.AccumulatedInputDerivative / (FLOAT)neuron.AccumulatedInputDerivativeCount;
							neuron.AccumulatedInputDerivative = 0;
							neuron.AccumulatedInputDerivativeCount = 0;
						}
						for (auto &weight : neuron.Weights)
						{
							if (weight.Dead)
								continue;
							if (weight.AccumulatedErrorDerivativeCount > 0)
							{
								FLOAT old_weight{ weight.Weight };
								weight.Weight -= m_fLearnRate * weight.AccumulatedErrorDerivative / (FLOAT)weight.AccumulatedErrorDerivativeCount - m_fMomentumRate * weight.Delta;
								FLOAT regularize_derivative{ m_pRegularizeFunction ? m_pRegularizeFunction->Derivative(weight.Weight) : 0 };
								FLOAT new_weight{ weight.Weight - m_fLearnRate * m_fRegularizeRate * regularize_derivative };
								if (m_pRegularizeFunction && m_pRegularizeFunction->IsDead(weight.Weight, new_weight))
								{
									weight.Weight = 0;
									weight.Dead = true;
								}
								else
									weight.Weight = new_weight;
								weight.Delta = weight.Weight - old_weight;
								weight.AccumulatedErrorDerivative = 0;
								weight.AccumulatedErrorDerivativeCount = 0;
							}
						}
					}
				}
			}
		public:
		#pragma region Constructor & destructor
			TPerceptron() = default;

			TPerceptron(
				// Required parameters
				IActivator<FLOAT> *activator, // Hidden layers activation function
				IActivator<FLOAT> *activator_output, // Output layer activation function
				IErrorFunction<FLOAT> *error_function, // Error function
				const size_type feature_count, // Feature/Input count
				const size_type output_count, // Output/Class count
				const std::initializer_list<size_type> &hidden_layers, // Number of neurons in hidden layers
				// Optional parameters
				IRandomizer<FLOAT> *randomizer = nullptr, // Randomization function. If empty, weights will be initialized with gauss random distribution with mean = 0 and sigma = 1 / sqrt(weight_count). The same for bias except the sigma is 1
				IRegularizeFunction<FLOAT> *regularize_function = nullptr, // Regularization function
				const size_type batch_size = 10, // Learning batch size for Stohastic Gradient Descent. Min = 1 for online learning
				const FLOAT learn_rate = 0.03, // Learning rate
				const FLOAT regularize_rate = 0, // Regularization rate. Used when regularization function is not empty
				const FLOAT momentum_rate = 0 // Momentum rate
				) :

				m_pErrorFunction{ error_function },
				m_pRegularizeFunction{ regularize_function },
				m_bLearning{ true },
				m_iBatchSize{ batch_size },
				m_fLearnRate{ learn_rate },
				m_fRegularizeRate{ regularize_rate },
				m_fMomentumRate{ momentum_rate },
				m_iBatchCount{ 0 }
			{
				// Check if parameters are valid
				if (feature_count == 0 || output_count == 0 || batch_size < 1 || !activator || !activator_output || !error_function)
					return;
				for (auto pos : hidden_layers)
					if (pos == 0)
						return;
				// Create net
				size_type layer_count{ 2 + hidden_layers.size() };
				m_aLayers.resize(layer_count);
				auto pos{ hidden_layers.begin() };
				for (size_type layer_index = 0; layer_index < layer_count; layer_index++)
				{
					auto &layer{ m_aLayers[layer_index] };
					bool is_input{ layer_index == 0 }, is_output{ layer_index == layer_count - 1 };
					layer.Neurons.resize(is_input ? feature_count : (is_output ? output_count : *pos));
					for (auto &neuron : layer.Neurons)
					{
						neuron.Activator = is_output ? activator_output : activator;
						if (!is_input)
							neuron.Weights.resize(m_aLayers[layer_index - 1].Neurons.size());
					}
					if (!is_input && !is_output)
						pos++;
				}
				if (randomizer)
					Randomize(randomizer);
				else
				{
					auto now{ std::chrono::system_clock::now() };
					std::chrono::milliseconds duration{ std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) };
					randomizers::TGauss<FLOAT> randomizer{ (FLOAT)0, (FLOAT)1, (unsigned char)duration.count() };
					randomizers::TGauss<FLOAT> randomizer_bias{ (FLOAT)0, (FLOAT)1, (unsigned int)duration.count() };
					for (auto &layer : m_aLayers)
						for (auto &neuron : layer.Neurons)
						{
							randomizer.setParams((FLOAT)0, (FLOAT)1 / std::sqrt((FLOAT)neuron.Weights.size()));
							neuron.Randomize(&randomizer);
							neuron.Bias = randomizer_bias.Generate();
						}
				}
			}
		#pragma endregion

		#pragma region Getters
			bool isValid() const // Return true if net is valid
			{
				return m_aLayers.size() > 0;
			}

			bool isLearning() const // Return whether the net is in learning mode
			{
				return m_bLearning;
			}

			size_type getBatchSize() const // Return batch size
			{
				return m_iBatchSize;
			}

			FLOAT getLearnRate() const // Return learning rate
			{
				return m_fLearnRate;
			}

			FLOAT getRegularizeRate() const // Return regularize rate
			{
				return m_fRegularizeRate;
			}

			FLOAT getMomentumRate() const // Return momentum rate
			{
				return m_fMomentumRate;
			}

			size_type getInputCount() const // Return input/feature count(number of neurons in input layer)
			{
				if (m_aLayers.size() > 0)
					return m_aLayers[0].Neurons.size();
				return 0;
			}

			FLOAT getInput(const size_type index) const // Return input value
			{
				if (m_aLayers.size() > 0 && index < m_aLayers[0].Neurons.size())
					return m_aLayers[0].Neurons[index].Output;
				return 0;
			}

			size_type getOutputCount() const // Return output/class count(number of neurons in output layer)
			{
				if (m_aLayers.size() > 0)
					return m_aLayers[m_aLayers.size() - 1].Neurons.size();
				return 0;
			}

			FLOAT getOutput(const size_type index) const // Return output
			{
				if (m_aLayers.size() > 0 && index < m_aLayers[m_aLayers.size() - 1].Neurons.size())
					return m_aLayers[m_aLayers.size() - 1].Neurons[index].Output;
				return 0;
			}

			size_type getLayerCount() const // Return layer count
			{
				return m_aLayers.size();
			}

			size_type getNeuronCount(const size_type layer) const // Return neuron count in specified layer
			{
				if (layer < m_aLayers.size())
					return m_aLayers[layer].Neurons.size();
				return 0;
			}

			FLOAT getNeuronBias(const size_type layer, const size_type neuron) const // Return bias value of specified neuron
			{
				if (layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size())
					return m_aLayers[layer].Neurons[neuron].Bias;
				return 0;
			}

			FLOAT getNeuronAmount(const size_type layer, const size_type neuron) const // Return neuron weighted sum
			{
				if (layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size())
					return m_aLayers[layer].Neurons[neuron].Amount;
				return 0;
			}

			FLOAT getNeuronOutput(const size_type layer, const size_type neuron) const // Return neuron output(result of applying an activation function to weighted sum of the neuron)
			{
				if (layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size())
					return m_aLayers[layer].Neurons[neuron].Output;
				return 0;
			}

			IActivator<FLOAT> *getNeuronActivator(const size_type layer, const size_type neuron) const // Return activation function of specified neuron
			{
				if (layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size())
					return m_aLayers[layer].Neurons[neuron].Activator;
				return nullptr;
			}

			FLOAT getNeuronAccumulatedInputDerivative(const size_type layer, const size_type neuron) const // Return accumulated input derivative of specified neuron
			{
				if (layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size())
					return m_aLayers[layer].Neurons[neuron].AccumulatedInputDerivative;
				return 0;
			}

			size_type getNeuronAccumulatedInputDerivativeCount(const size_type layer, const size_type neuron) const // Return accumulated input derivative count of specified neuron
			{
				if (layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size())
					return m_aLayers[layer].Neurons[neuron].AccumulatedInputDerivativeCount;
				return 0;
			}

			bool getNeuronState(const size_type layer, const size_type neuron, FLOAT &bias, FLOAT &amount, FLOAT &output) const // Return specified neuron bias, weighted sum, and output
			{
				if (layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size())
				{
					bias = m_aLayers[layer].Neurons[neuron].Bias;
					amount = m_aLayers[layer].Neurons[neuron].Amount;
					output = m_aLayers[layer].Neurons[neuron].Output;
					return true;
				}
				return false;
			}

			size_type getWeightCount(const size_type layer, const size_type neuron) const // Return weight count of specified neuron
			{
				if (layer >= 1 && layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size())
					return m_aLayers[layer].Neurons[neuron].Weights.size();
				return 0;
			}

			FLOAT getWeight(const size_type layer, const size_type neuron, const size_type weight) const // Return specified weight
			{
				if (layer >= 1 && layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size() && weight < m_aLayers[layer].Neurons[neuron].Weights.size())
					return m_aLayers[layer].Neurons[neuron].Weights[weight].Weight;
				return 0;
			}

			FLOAT getWeightAccumulatedErrorDerivative(const size_type layer, const size_type neuron, const size_type weight) const // Return accumulated error derivative of specified weight
			{
				if (layer >= 1 && layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size() && weight < m_aLayers[layer].Neurons[neuron].Weights.size())
					return m_aLayers[layer].Neurons[neuron].Weights[weight].AccumulatedErrorDerivative;
				return 0;
			}

			size_type getWeightAccumulatedErrorDerivativeCount(const size_type layer, const size_type neuron, const size_type weight) const // Return accumulated error derivative count of specified weight
			{
				if (layer >= 1 && layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size() && weight < m_aLayers[layer].Neurons[neuron].Weights.size())
					return m_aLayers[layer].Neurons[neuron].Weights[weight].AccumulatedErrorDerivativeCount;
				return 0;
			}

			bool isWeightDead(const size_type layer, const size_type neuron, const size_type weight) const // Return whether specified weight is not active
			{
				if (layer >= 1 && layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size() && weight < m_aLayers[layer].Neurons[neuron].Weights.size())
					return m_aLayers[layer].Neurons[neuron].Weights[weight].Dead;
				return false;
			}
		#pragma endregion

		#pragma region Setters
			bool setLearning(const bool value) // Set leraning mode
			{
				if (value != m_bLearning)
				{
					m_bLearning = value;
					return true;
				}
				return false;
			}

			bool setBatchSize(const size_type value) // Set batch size
			{
				if (value > 0 && value != m_iBatchSize)
				{
					m_iBatchSize = value;
					return true;
				}
				return false;
			}

			bool setLearnRate(const FLOAT value) // Set learning rate
			{
				if (value != m_fLearnRate)
				{
					m_fLearnRate = value;
					return true;
				}
				return false;
			}

			bool setRegularizeRate(const FLOAT value) // Set regularization rate
			{
				if (value != m_fRegularizeRate)
				{
					m_fRegularizeRate = value;
					return true;
				}
				return false;
			}

			bool setMomentumRate(const FLOAT value) // Set momentum rate
			{
				if (value != m_fMomentumRate)
				{
					m_fMomentumRate = value;
					return true;
				}
				return false;
			}

			bool setInput(const size_type index, const FLOAT value) // Set input value
			{
				if (m_aLayers.size() > 0 && index < m_aLayers[0].Neurons.size() && m_aLayers[0].Neurons[index].Output != value)
				{
					m_aLayers[0].Neurons[index].Output = value;
					return true;
				}
				return false;
			}

			bool setLayerActivator(const size_type layer, IActivator<FLOAT> *value) // Set activation function to entire layer
			{
				bool result{ false };
				if (value && layer >= 1 && layer < m_aLayers.size())
					for (auto &neuron : m_aLayers[layer].Neurons)
						if (neuron.Activator != value)
						{
							neuron.Activator = value;
							result = true;
						}
				return result;
			}

			bool setNeuronBias(const size_type layer, const size_type neuron, const FLOAT value) // Set specified neuron bias
			{
				if (layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size() && value != m_aLayers[layer].Neurons[neuron].Bias)
				{
					m_aLayers[layer].Neurons[neuron].Bias = value;
					return true;
				}
				return false;
			}

			bool setNeuronActivator(const size_type layer, const size_type neuron, IActivator<FLOAT> *value) // Set specified neuron activation function
			{
				if (value && layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size() && value != m_aLayers[layer].Neurons[neuron].Activator)
				{
					m_aLayers[layer].Neurons[neuron].Activator = value;
					return true;
				}
				return false;
			}

			bool setWeight(const size_type layer, const size_type neuron, const size_type weight, const FLOAT value) // Set sepcified weight value
			{
				if (layer >= 1 && layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size() && weight < m_aLayers[layer].Neurons[neuron].Weights.size() && value != m_aLayers[layer].Neurons[neuron].Weights[weight].Weight)
				{
					m_aLayers[layer].Neurons[neuron].Weights[weight].Weight = value;
					return true;
				}
				return false;
			}

			bool setWeightDead(const size_type layer, const size_type neuron, const size_type weight, const bool value) // Enable/disable specified weight
			{
				if (layer >= 1 && layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size() && weight < m_aLayers[layer].Neurons[neuron].Weights.size() && value != m_aLayers[layer].Neurons[neuron].Weights[weight].Dead)
				{
					m_aLayers[layer].Neurons[neuron].Weights[weight].Dead = value;
					return true;
				}
				return false;
			}
		#pragma endregion

		#pragma region Helpers
			void ResetBatch() // Reset current batch counter
			{
				m_iBatchCount = 0;
			}

			bool Randomize(IRandomizer<FLOAT> *randomizer) // Initialize weights and biases of neurons using specified randomizer
			{
				if (randomizer)
				{
					for (auto &layer : m_aLayers)
						for (auto &neuron : layer.Neurons)
							neuron.Randomize(randomizer);
					return true;
				}
				return false;
			}

			bool RandomizeLayer(const size_type layer, IRandomizer<FLOAT> *randomizer) // Initialize weights and biases of neurons of specified layer using specified randomizer
			{
				if (randomizer && layer >= 1 && layer < m_aLayers.size())
				{
					for (auto &neuron : m_aLayers[layer].Neurons)
						neuron.Randomize(randomizer);
					return true;
				}
				return false;
			}

			bool RandomizeNeuron(const size_type layer, const size_type neuron, IRandomizer<FLOAT> *randomizer) // Initialize weights and biase of specified neurons using specified randomizer
			{
				if (randomizer && layer >= 1 && layer < m_aLayers.size() && neuron < m_aLayers[layer].Neurons.size())
				{
					m_aLayers[layer].Neurons[neuron].Randomize(randomizer);
					return true;
				}
				return false;
			}

			bool Forward(const std::vector<FLOAT> &inputs) // Forward step
			{
				if (m_aLayers.size() > 0 && m_aLayers[0].Neurons.size() == inputs.size())
				{
					ForwardInternal(inputs);
					return true;
				}
				return false;
			}

			bool Backward(const std::vector<FLOAT> &expected_output) // Backward step
			{
				if (m_aLayers.size() > 0 && m_aLayers[m_aLayers.size() - 1].Neurons.size() == expected_output.size())
				{
					BackwardInternal(expected_output);
					return true;
				}
				return false;
			}

			bool UpdateWeights() // Update weights(learn)
			{
				if (m_aLayers.size() > 0)
				{
					UpdateWeightsInternal();
					return true;
				}
				return false;
			}

			bool Simulate(const std::vector<FLOAT> &inputs, const std::vector<FLOAT> &expected_output) // Main processing method. Perform forward, backward, and update weights(if needed).
			{
				if (m_aLayers.size() > 0 && m_aLayers[0].Neurons.size() == inputs.size() && (m_aLayers[m_aLayers.size() - 1].Neurons.size() == expected_output.size() || expected_output.size() == 0))
				{
					ForwardInternal(inputs);
					if (m_bLearning && expected_output.size() > 0)
					{
						BackwardInternal(expected_output);
						m_iBatchCount++;
						if (m_iBatchCount >= m_iBatchSize)
						{
							UpdateWeightsInternal();
							m_iBatchCount = 0;
						}
					}
					return true;
				}
				return false;
			}

			FLOAT Loss(const std::vector<FLOAT> &inputs, const std::vector<FLOAT> &expected_output) // Calculate error
			{
				if (m_aLayers.size() > 0 && m_aLayers[m_aLayers.size() - 1].Neurons.size() == expected_output.size())
				{
					FLOAT result{ 0 };
					ForwardInternal(inputs);
					for (size_type neuron_index = 0; neuron_index < m_aLayers[m_aLayers.size() - 1].Neurons.size(); neuron_index++)
					{
						auto &neuron{ m_aLayers[m_aLayers.size() - 1].Neurons[neuron_index] };
						result += m_pErrorFunction->Error(neuron.Output, expected_output[neuron_index], neuron.Amount, neuron.Activator);
					}
					return result / (FLOAT)m_aLayers[m_aLayers.size() - 1].Neurons.size();
				}
				return -1;
			}
		#pragma endregion

		#ifdef _DEBUG
			void Print()
			{
				std::cout << std::setprecision(3) << "\t\tD";
				bool first_layer{ true };
				for (size_type layer_index = 1; layer_index < m_aLayers.size(); layer_index++)
				{
					auto &layer{ m_aLayers[layer_index] };
					if (!first_layer)
						std::cout << "| ";
					first_layer = false;
					bool first_neuron{ true };
					for (size_type i = 0; i < layer.Neurons.size(); i++)
					{
						if (!first_neuron)
							std::cout << "; ";
						first_neuron = false;
						bool first_weight{ true };
						for (size_type j = 0; j < layer.Neurons[i].Weights.size(); j++)
						{
							if (!first_weight)
								std::cout << ", ";
							std::cout << std::setw(6) << std::left << layer.Neurons[i].Weights[j].Weight;
							first_weight = false;
						}
					}
				}
				std::cout << std::endl;
			}
		#endif
		};
	}
}