// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

namespace ntl
{
	template<class TYPE>
	union TPlane
	{
		struct
		{
			union // Normal
			{
				struct
				{
					TYPE Nx;
					TYPE Ny;
					TYPE Nz;
				};
				TVec3<TYPE> N;
			};
			TYPE D;
		};
		TVec4<TYPE> V4; // As TVec4
		TQuaternion<TYPE> Q; // As TQuaternion
		TMatrix<TYPE, 1, 4> M; // As matrix

		TPlane(const TPlane &other) = default;
		TPlane(TPlane &&other) = default;

		TPlane() : // Create invalid plane(all elements are zero)
			Nx{ 0 },
			Ny{ 0 },
			Nz{ 0 },
			D{ 0 }
		{

		}

		TPlane(const TYPE nx, const TYPE ny, const TYPE nz, const TYPE d) : // Create with specified elements
			Nx{ nx },
			Ny{ ny },
			Nz{ nz },
			D{ d }
		{
			Normalize(N);
		}

		TPlane(const TYPE nx, const TYPE ny, const TYPE nz, const TYPE d, const bool normalize) : // Create with specified elements. Aditionally normal normalization can be requested
			Nx{ nx },
			Ny{ ny },
			Nz{ nz },
			D{ d }
		{
			if (normalize)
				Normalize(N);
		}

		TPlane(const TVec2<TYPE> &n, const TVec2<TYPE> &p) : // Create from normal and point in 2D space
			N{ (TVec3<TYPE>)Normalized(n) },
			D{ -Nx * p.X - Ny * p.Y }
		{

		}

		TPlane(const TVec3<TYPE> &n, const TVec3<TYPE> &p) : // Create from normal and point in 3D space
			N{ Normalized(n) },
			D{ -Nx * p.X - Ny * p.Y - Nz * p.Z }
		{
			
		}

		TPlane(const TVec2<TYPE> &p1, const TVec2<TYPE> &p2, const TVec2<TYPE> &p3) // Create by 2 points in 2D space
		{
			N = ((TVec3<TYPE>)p2 - (TVec3<TYPE>)p1) ^ ((TVec3<TYPE>)p3 - (TVec3<TYPE>)p1);
			Normalize(N);
			D = -Nx * p1.X - Ny * p1.Y;
		}

		TPlane(const TVec3<TYPE> &p1, const TVec3<TYPE> &p2, const TVec3<TYPE> &p3) // Create by 3 points in 3D space
		{
			N = (p2 - p1) ^ (p3 - p1);
			Normalize(N);
			D = -Nx * p1.X - Ny * p1.Y - Nz * p1.Z;
		}

		TPlane &operator=(const TPlane &other) = default;
		TPlane &operator=(TPlane &&other) = default;
	};

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator==(const TPlane<TYPE> &a, const TPlane<TYPE> &b) // Check whether planes are equal. Can be used for non-float data types only
	{
		return a.Nx == b.Nx && a.Ny == b.Ny && a.Nz == b.Nz && a.D == b.D;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator!=(const TPlane<TYPE> &a, const TPlane<TYPE> &b) // Check whether planes aren't equal. Can be used for non-float data types only
	{
		return a.Nx != b.Nx || a.Ny != b.Ny || a.Nz != b.Nz || a.D != b.D;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TPlane<TYPE> &a, const TPlane<TYPE> &b) // Compare whether planes are equal
	{
		return a.Nx == b.Nx && a.Ny == b.Ny && a.Nz == b.Nz && a.D == b.D;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TPlane<TYPE> &a, const TPlane<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether planes are equal
	{
		return IsEqual<TYPE>(a.Nx, b.Nx, tolerance) && IsEqual<TYPE>(a.Ny, b.Ny, tolerance) && IsEqual<TYPE>(a.Nz, b.Nz, tolerance) && IsEqual<TYPE>(a.D, b.D, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TPlane<TYPE> &a, const TPlane<TYPE> &b) // Compare whether planes aren't equal
	{
		return a.Nx != b.Nx || a.Ny != b.Ny || a.Nz != b.Nz || a.D != b.D;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TPlane<TYPE> &a, const TPlane<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether planes aren't equal
	{
		return IsNotEqual<TYPE>(a.Nx, b.Nx, tolerance) || IsNotEqual<TYPE>(a.Ny, b.Ny, tolerance) || IsNotEqual<TYPE>(a.Nz, b.Nz, tolerance) || IsNotEqual<TYPE>(a.D, b.D, tolerance);
	}

	template<class TO, class FROM>
	TPlane<TO> Convert(const TPlane<FROM> &p) // Convert to plane with another data type
	{
		return TPlane<TO>{ (TO)p.Nx, (TO)p.Ny, (TO)p.Nz, (TO)p.D };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Distance(const TPlane<TYPE> &p, const TVec2<TYPE> &v) // Return distance from plane to 2D point
	{
		return p.Nx * v.X + p.Ny * v.Y + p.D;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Distance(const TPlane<TYPE> &p, const TVec3<TYPE> &v) // Return distance from plane to 3D point
	{
		return p.Nx * v.X + p.Ny * v.Y + p.Nz * v.Z + p.D;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Inverse(TPlane<TYPE> &p) // Inverse plane
	{
		p.Nx = -p.Nx;
		p.Ny = -p.Ny;
		p.Nz = -p.Nz;
		p.D = -p.D;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPlane<TYPE>> Inversed(const TPlane<TYPE> &p) // Return inversed plane
	{
		return TPlane<TYPE>{ -p.Nx, -p.Ny, -p.Nz, -p.D };
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Equals(const TPlane<TYPE> &a, const TPlane<TYPE> &b, const FLOAT tolerance) // Check whether planes are equal using relative comparison
	{
		return Equals<TYPE, FLOAT>(a.Nx, b.Nx, tolerance) && Equals<TYPE, FLOAT>(a.Ny, b.Ny, tolerance) && Equals<TYPE, FLOAT>(a.Nz, b.Nz, tolerance) && Equals<TYPE, FLOAT>(a.D, b.D, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Equals(const TPlane<TYPE> &a, const TPlane<TYPE> &b, const TYPE tolerance) // Check whether planes are equal using relative comparison
	{
		return Equals<TYPE>(a.Nx, b.Nx, tolerance) && Equals<TYPE>(a.Ny, b.Ny, tolerance) && Equals<TYPE>(a.Nz, b.Nz, tolerance) && Equals<TYPE>(a.D, b.D, tolerance);
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> NotEquals(const TPlane<TYPE> &a, const TPlane<TYPE> &b, const FLOAT tolerance) // Check whether planes aren't equal using relative comparison
	{
		return NotEquals<TYPE, FLOAT>(a.Nx, b.Nx, tolerance) || NotEquals<TYPE, FLOAT>(a.Ny, b.Ny, tolerance) || NotEquals<TYPE, FLOAT>(a.Nz, b.Nz, tolerance) || NotEquals<TYPE, FLOAT>(a.D, b.D, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> NotEquals(const TPlane<TYPE> &a, const TPlane<TYPE> &b, const TYPE tolerance) // Check whether planes aren't equal using relative comparison
	{
		return NotEquals<TYPE>(a.Nx, b.Nx, tolerance) || NotEquals<TYPE>(a.Ny, b.Ny, tolerance) || NotEquals<TYPE>(a.Nz, b.Nz, tolerance) || NotEquals<TYPE>(a.D, b.D, tolerance);
	}
}