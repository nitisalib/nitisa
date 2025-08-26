// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	// https://github.com/Auburns/FastNoise
	class CNoise
	{
	public:
		enum class NoiseType
		{
			White,
			Value,
			ValueFractal,
			Perlin,
			PerlinFractal,
			Simplex,
			SimplexFractal,
			Cubic,
			CubicFractal,
			Cellular
		};

		enum class InterpolationType // Interpolation method used to smooth between noise values(lowest to highest quality). Used in Value, Perlin Noise and Position Warping
		{
			Linear,
			Hermite,
			Quintic
		};

		enum class FractalType
		{
			FBM,
			Billow,
			RigidMulti
		};

		enum class CellularDistance
		{
			Euclidean,
			Manhattan,
			Natural
		};

		enum class CellularReturn
		{
			CellValue,
			Distance,
			Distance2,
			Distance2Add,
			Distance2Sub,
			Distance2Mul,
			Distance2Div,
			NoiseLookup
		};
	private:
		int m_iSeed;
		int m_iOctaves;
		double m_fFrequency;
		double m_fLacunarity;
		double m_fGain;
		NoiseType m_eNoiseType;
		InterpolationType m_eInterpolationType;
		FractalType m_eFractalType;
		CellularDistance m_eCellularDistance;
		CellularReturn m_eCellularReturn;
		int m_iCellularDistanceIndex0;
		int m_iCellularDistanceIndex1;
		double m_fCellularJitter;
		double m_fGradientPerturbAmplitude;
		CNoise *m_pCellularNoiseLookup;

		double m_fFractalBounding;
		unsigned char m_aPerm[512];
		unsigned char m_aPerm12[512];

		void CalculateFractalBounding();
		int FastFloor(const double f) const;
		int FastRound(const double f) const;
		int FastAbs(const int i) const;
		double FastAbs(const double f) const;
		double Lerp(const double a, const double b, const double t) const;
		double InterpHermiteFunc(const double t) const;
		double InterpQuinticFunc(const double t) const;
		double CubicLerp(const double a, const double b, const double c, const double d, const double t) const;
		double ValCoord2D(const int seed, const int x, const int y) const;
		double ValCoord3D(const int seed, const int x, const int y, const int z) const;
		double ValCoord4D(const int seed, const int x, const int y, const int z, const int w) const;
		unsigned char Index2D_12(const unsigned char offset, const int x, const int y) const;
		unsigned char Index3D_12(const unsigned char offset, const int x, const int y, const int z) const;
		unsigned char Index4D_32(const unsigned char offset, const int x, const int y, const int z, const int w) const;
		unsigned char Index2D_256(const unsigned char offset, const int x, const int y) const;
		unsigned char Index3D_256(const unsigned char offset, const int x, const int y, const int z) const;
		unsigned char Index4D_256(const unsigned char offset, const int x, const int y, const int z, const int w) const;
		double ValCoord2DFast(const unsigned char offset, const int x, const int y) const;
		double ValCoord3DFast(const unsigned char offset, const int x, const int y, const int z) const;
		double GradCoord2D(const unsigned char offset, const int x, const int y, const double xd, const double yd) const;
		double GradCoord3D(const unsigned char offset, const int x, const int y, const int z, const double xd, const double yd, const double zd) const;
		double GradCoord4D(const unsigned char offset, const int x, const int y, const int z, const int w, const double xd, const double yd, const double zd, const double wd) const;

		// 2D noise helpers
		double SingleValueFractalFBM(const double in_x, const double in_y) const;
		double SingleValueFractalBillow(const double in_x, const double in_y) const;
		double SingleValueFractalRigidMulti(const double in_x, const double in_y) const;
		double SingleValue(const unsigned char offset, const double in_x, const double in_y) const;
		double SinglePerlinFractalFBM(const double in_x, const double in_y) const;
		double SinglePerlinFractalBillow(const double in_x, const double in_y) const;
		double SinglePerlinFractalRigidMulti(const double in_x, const double in_y) const;
		double SinglePerlin(unsigned char offset, const double in_x, const double in_y) const;
		double SingleSimplexFractalFBM(const double in_x, const double in_y) const;
		double SingleSimplexFractalBillow(const double in_x, const double in_y) const;
		double SingleSimplexFractalRigidMulti(const double in_x, const double in_y) const;
		double SingleSimplexFractalBlend(const double in_x, const double in_y) const;
		double SingleSimplex(const unsigned char offset, const double in_x, const double in_y) const;
		double SingleCubicFractalFBM(const double in_x, const double in_y) const;
		double SingleCubicFractalBillow(const double in_x, const double in_y) const;
		double SingleCubicFractalRigidMulti(const double in_x, const double in_y) const;
		double SingleCubic(const unsigned char offset, const double in_x, const double in_y) const;
		double SingleCellular(const double in_x, const double in_y) const;
		double SingleCellular2Edge(const double in_x, const double in_y) const;
		void SingleGradientPerturb(const unsigned char offset, const double warpAmp, const double frequency, double &x, double &y) const;

		// 3D noise helpers
		double SingleValueFractalFBM(const double in_x, const double in_y, const double in_z) const;
		double SingleValueFractalBillow(const double in_x, const double in_y, const double in_z) const;
		double SingleValueFractalRigidMulti(const double in_x, const double in_y, const double in_z) const;
		double SingleValue(const unsigned char offset, const double in_x, const double in_y, const double in_z) const;
		double SinglePerlinFractalFBM(const double in_x, const double in_y, const double in_z) const;
		double SinglePerlinFractalBillow(const double in_x, const double in_y, const double in_z) const;
		double SinglePerlinFractalRigidMulti(const double in_x, const double in_y, const double in_z) const;
		double SinglePerlin(const unsigned char offset, const double in_x, const double in_y, const double in_z) const;
		double SingleSimplexFractalFBM(const double in_x, const double in_y, const double in_z) const;
		double SingleSimplexFractalBillow(const double in_x, const double in_y, const double in_z) const;
		double SingleSimplexFractalRigidMulti(const double in_x, const double in_y, const double in_z) const;
		double SingleSimplex(const unsigned char offset, const double in_x, const double in_y, const double in_z) const;
		double SingleCubicFractalFBM(const double in_x, const double in_y, const double in_z) const;
		double SingleCubicFractalBillow(const double in_x, const double in_y, const double in_z) const;
		double SingleCubicFractalRigidMulti(const double in_x, const double in_y, const double in_z) const;
		double SingleCubic(const unsigned char offset, const double in_x, const double in_y, const double in_z) const;
		double SingleCellular(const double in_x, const double in_y, const double in_z) const;
		double SingleCellular2Edge(const double in_x, const double in_y, const double in_z) const;
		void SingleGradientPerturb(const unsigned char offset, const double warpAmp, const double frequency, double &x, double &y, double &z) const;

		// 4D noise helpers
		double SingleSimplex(const unsigned char offset, const double in_x, const double in_y, const double in_z, const double in_w) const;
	public:
		CNoise(const int seed = 1337);

		int getSeed() const; // Return seed
		int getOctaves() const; // Return octave count(for fractal noise)
		double getFrequency() const; // Return frequency
		double getLacunarity() const; // Return lacunarity
		double getGain() const; // Return gain
		NoiseType getNoiseType() const; // Return noise type
		InterpolationType getInterpolationType() const; // Return interpolation type
		FractalType getFractalType() const; // Return fractal type
		CellularDistance getCellularDistance() const; // Return cellular distance type
		CellularReturn getCellularReturn() const; // Return cellular return type
		int getCellularDistanceIndex0() const; // Return cellular distance first index
		int getCellularDistanceIndex1() const; // Return cellular distance second index
		double getCellularJitter() const; // Return cellular jitter
		double getGradientPerturbAmplitude() const; // Return gradient perturbation amplitude
		CNoise *getCellularNoiseLookup(); // Return cellular lookup noise

		bool setSeed(const int value); // Set seed
		bool setOctaves(const int value); // Set octave count. >= 1
		bool setFrequency(const double value); // Set frequency
		bool setLacunarity(const double value); // Set lacunarity
		bool setGain(const double value); // Set gain
		bool setNoiseType(const NoiseType value); // Set noise type
		bool setInterpolationType(const InterpolationType value); // Set interpolation type
		bool setFractalType(const FractalType value); // Set fractal type
		bool setCellularDistance(const CellularDistance value); // Set cellular distance type
		bool setCellularReturn(const CellularReturn value); // Set cellular return type
		bool setCellularDistanceIndex0(const int value); // Set cellular distance first index
		bool setCellularDistanceIndex1(const int value); // Set cellular distance second index
		bool setCellularJitter(const double value); // Set cellular jitter
		bool setGradientPerturbAmplitude(const double value); // Set gradient perturbation amplitude
		bool setCellularNoiseLookup(CNoise *value); // Set cellular lookup noise

		// Calculate 2D/3D noise in specified position depending on current settings
		double CalculateNoise(const double x, const double y) const;
		double CalculateNoise(const double x, const double y, const double z) const;

		// White noise calculation methods
		double CalculateWhiteNoise(const double x, const double y) const;
		double CalculateWhiteNoiseInt(const int x, const int y) const;
		double CalculateWhiteNoise(const double x, const double y, const double z) const;
		double CalculateWhiteNoiseInt(const int x, const int y, const int z) const;
		double CalculateWhiteNoise(const double x, const double y, const double z, const double w) const;
		double CalculateWhiteNoiseInt(const int x, const int y, const int z, const int w) const;

		// Value noise calculation methods
		double CalculateValue(const double x, const double y) const;
		double CalculateValueFractal(const double x, const double y) const;
		double CalculateValue(const double x, const double y, const double z) const;
		double CalculateValueFractal(const double x, const double y, const double z) const;

		// Perlin noise calculation methods
		double CalculatePerlin(const double x, const double y) const;
		double CalculatePerlinFractal(const double x, const double y) const;
		double CalculatePerlin(const double x, const double y, const double z) const;
		double CalculatePerlinFractal(const double x, const double y, const double z) const;

		// Simplex noise calculation methods
		double CalculateSimplex(const double x, const double y) const;
		double CalculateSimplexFractal(const double x, const double y) const;
		double CalculateSimplex(const double x, const double y, const double z) const;
		double CalculateSimplexFractal(const double x, const double y, const double z) const;
		double CalculateSimplex(const double x, const double y, const double z, const double w) const;

		// Cubic noise calculation methods
		double CalculateCubic(const double x, const double y) const;
		double CalculateCubicFractal(const double x, const double y) const;
		double CalculateCubic(const double x, const double y, const double z) const;
		double CalculateCubicFractal(const double x, const double y, const double z) const;

		// Cellular noise calculation methods
		double CalculateCellular(const double x, const double y) const;
		double CalculateCellular(const double x, const double y, const double z) const;

		// Gradient perturbation calculation methods
		void GradientPerturb(double &x, double &y) const;
		void GradientPerturbFractal(double &x, double &y) const;
		void GradientPerturb(double &x, double &y, double &z) const;
		void GradientPerturbFractal(double &x, double &y, double &z) const;
	};
}