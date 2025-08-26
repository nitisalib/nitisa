// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Utils.h"
#include <cmath>

namespace ntl
{
	template<class TYPE> union TVec1;
	template<class TYPE> union TVec2;
	template<class TYPE> union TVec3;
	template<class TYPE> union TVec4;
	template<class TYPE> union TQuaternion;

	// Row-major order
	template<class TYPE, size_t ROWS, size_t COLUMNS>
	union TMatrix
	{
		struct ROW // Represents row
		{
			TYPE Data[COLUMNS]; // Row elements

			TYPE operator[](const size_t col) const // Return element at specified column. Used when matrix is a constant object only
			{
				return Data[col];
			}

			TYPE &operator[](const size_t col) // Return element at specified column
			{
				return Data[col];
			}
		};

		ROW Rows[ROWS]; // Array of rows
		TYPE Data[ROWS][COLUMNS]; // Array of elements

		ROW operator[](const size_t row) const // Return row at specified position. Used when matrix is a constant object only
		{
			return Rows[row];
		}

		ROW &operator[](const size_t row) // Return row at specified position
		{
			return Rows[row];
		}
	};

	template<class TYPE>
	union TPoint
	{
		struct
		{
			union
			{
				TYPE X; // First element
				TVec1<TYPE> V1; // First element as TVec1
			};
			TYPE Y; // Second element
		};
		struct
		{
			TYPE A; // First element
			TYPE B; // Second element
		};
		struct
		{
			TYPE From; // First element
			TYPE Till; // Second element
		};
		struct
		{
			TYPE First; // First element
			TYPE Second; // Second element
		};
		struct
		{
			TYPE _1; // First element
			TYPE _2; // Second element
		};
		TYPE Data[2]; // Array of elements
		TMatrix<TYPE, 1, 2> M; // Elements as matrix
		TVec2<TYPE> V2; // Elements as TVec2

		TYPE operator[](const size_t index) const // Return element by index. Only 0 and 1 are accepted as indices. Used only when TPoint object is a constant object
		{
			return Data[index];
		}

		TYPE &operator[](const size_t index) // Return element by index. Only 0 and 1 are accepted as indices
		{
			return Data[index];
		}

		explicit operator TVec3<TYPE>() const // Convert to TVec3
		{
			return TVec3<TYPE>{ X, Y, 0 };
		}

		explicit operator TVec4<TYPE>() const // Convert to TVec4
		{
			return TVec4<TYPE>{ X, Y, 0, 1 };
		}

		explicit operator TQuaternion<TYPE>() const // Convert to TQuaternion
		{
			return TQuaternion<TYPE>{ X, Y, 0, 1 };
		}
	};

	template<class TYPE>
	union TRect
	{
		struct // As borders
		{
			TYPE Left;
			TYPE Top;
			TYPE Right;
			TYPE Bottom;
		};
		struct // As vector
		{
			TYPE X;
			TYPE Y;
			TYPE Z;
			TYPE W;
		};
		struct // As components
		{
			TYPE A;
			TYPE B;
			TYPE C;
			TYPE D;
		};
		struct // As parts
		{
			TYPE First;
			TYPE Second;
			TYPE Third;
			TYPE Fourth;
		};
		struct // As color
		{
			TYPE Red;
			TYPE Green;
			TYPE Blue;
			TYPE Alpha;
		};
		struct // As elements
		{
			TYPE _1;
			TYPE _2;
			TYPE _3;
			TYPE _4;
		};
		struct // As corners
		{
			TPoint<TYPE> LeftTop;
			TPoint<TYPE> RightBottom;
		};
		struct // As points
		{
			TPoint<TYPE> _12;
			TPoint<TYPE> _34;
		};
		TYPE Data[4]; // Array of elements
		TMatrix<TYPE, 1, 4> M; // As matrix
		TVec4<TYPE> V4; // As TVec4
		TQuaternion<TYPE> Q; // As TQuaternion

		TYPE operator[](const size_t index) const // Return element by index. Only 0, 1, 2 and 3 are accepted as indices. Used only when TRect object is a constant object
		{
			return Data[index];
		}

		TYPE &operator[](const size_t index) // Return element by index. Only 0, 1, 2 and 3 are accepted as indices
		{
			return Data[index];
		}
	};

	template<class TYPE>
	union TVec1
	{
		struct // As coordinate
		{
			TYPE X;
		};
		struct // As element
		{
			TYPE _1;
		};
		TYPE Data[1]; // Array of elements
		TMatrix<TYPE, 1, 1> M; // As matrix

		TYPE operator[](const size_t index) const // Return element by index. Only 0 is accepted as index. Used only when TVec1 object is a constant object
		{
			return Data[index];
		}

		TYPE &operator[](const size_t index) // Return element by index. Only 0 is accepted as index
		{
			return Data[index];
		}

		explicit operator TYPE() const // Convert to scalar
		{
			return X;
		}

		explicit operator TPoint<TYPE>() const // Convert to TPoint
		{
			return TPoint<TYPE>{ X, 0 };
		}

		explicit operator TVec2<TYPE>() const // Convert to TVec2
		{
			return TVec2<TYPE>{ X, 0 };
		}

		explicit operator TVec3<TYPE>() const // Convert to TVec3
		{
			return TVec3<TYPE>{ X, 0, 0 };
		}

		explicit operator TVec4<TYPE>() const // Convert to TVec4
		{
			return TVec4<TYPE>{ X, 0, 0, 1 };
		}

		explicit operator TQuaternion<TYPE>() const // Convert to TQuaternion
		{
			return TQuaternion<TYPE>{ X, 0, 0, 1 };
		}
	};

	template<class TYPE>
	union TVec2
	{
		struct // As coordinate
		{
			union
			{
				TYPE X;
				TVec1<TYPE> V1;
			};
			TYPE Y;
		};
		struct // As elements
		{
			TYPE _1;
			TYPE _2;
		};
		TYPE Data[2]; // Array of elements
		TMatrix<TYPE, 1, 2> M; // As matrix

		TYPE operator[](const size_t index) const // Return element by index. Only 0 and 1 are accepted as indices. Used only when TVec2 object is a constant object
		{
			return Data[index];
		}

		TYPE &operator[](const size_t index) // Return element by index. Only 0 and 1 are accepted as indices
		{
			return Data[index];
		}

		explicit operator TPoint<TYPE>() const // Convert to TPoint
		{
			return TPoint<TYPE>{ X, Y };
		}

		explicit operator TVec3<TYPE>() const // Convert to TVec3
		{
			return TVec3<TYPE>{ X, Y, 0 };
		}

		explicit operator TVec4<TYPE>() const // Convert to TVec4
		{
			return TVec4<TYPE>{ X, Y, 0, 1 };
		}

		explicit operator TQuaternion<TYPE>() const // Convert to TQuaternion
		{
			return TQuaternion<TYPE>{ X, Y, 0, 1 };
		}
	};

	template<class TYPE>
	union TVec3
	{
		struct // As coordinates
		{
			union
			{
				struct
				{
					union
					{
						TYPE X;
						TVec1<TYPE> V1;
					};
					TYPE Y;
				};
				TVec2<TYPE> V2;
			};
			TYPE Z;
		};
		struct // As elements
		{
			TYPE _1;
			TYPE _2;
			TYPE _3;
		};
		TYPE Data[3]; // Array of elements
		TMatrix<TYPE, 1, 3> M; // As matrix

		TYPE operator[](const size_t index) const // Return element by index. Only 0, 1 and 2 are accepted as indices. Used only when TVec3 object is a constant object
		{
			return Data[index];
		}

		TYPE &operator[](const size_t index) // Return element by index. Only 0, 1 and 2 are accepted as indices
		{
			return Data[index];
		}

		explicit operator TPoint<TYPE>() const // Convert to TPoint
		{
			return TPoint<TYPE>{ X, Y };
		}

		explicit operator TVec4<TYPE>() const // Convert to TVec4
		{
			return TVec4<TYPE>{ X, Y, Z, 1 };
		}

		explicit operator TQuaternion<TYPE>() const // Convert to TQuaternion
		{
			return TQuaternion<TYPE>{ X, Y, Z, 1 };
		}
	};

	template<class TYPE>
	union TVec4
	{
		struct // As coordinates
		{
			union
			{
				struct
				{
					union
					{
						struct
						{
							union
							{
								TYPE X;
								TVec1<TYPE> V1;
							};
							TYPE Y;
						};
						TVec2<TYPE> V2;
					};
					TYPE Z;
				};
				TVec3<TYPE> V3;
			};
			TYPE W;
		};
		struct // As elements
		{
			TYPE _1;
			TYPE _2;
			TYPE _3;
			TYPE _4;
		};
		TYPE Data[4]; // Array of elements
		TMatrix<TYPE, 1, 4> M; // As matrix

		TYPE operator[](const size_t index) const // Return element by index. Only 0, 1, 2 and 3 are accepted as indices. Used only when TVec4 object is a constant object
		{
			return Data[index];
		}

		TYPE &operator[](const size_t index) // Return element by index. Only 0, 1, 2 and 3 are accepted as indices
		{
			return Data[index];
		}

		explicit operator TPoint<TYPE>() const // Convert to TPoint
		{
			return TPoint<TYPE>{ X, Y };
		}

		explicit operator TRect<TYPE>() const // Convert to TRect
		{
			return TRect<TYPE>{ X, Y, Z, W };
		}

		explicit operator TQuaternion<TYPE>() const // Convert to TQuaternion
		{
			return TQuaternion<TYPE>{ X, Y, Z, W };
		}
	};

	template<class TYPE>
	union TQuaternion
	{
		struct // As coordinates
		{
			union
			{
				struct
				{
					union
					{
						struct
						{
							union
							{
								TYPE X;
								TVec1<TYPE> V1;
							};
							TYPE Y;
						};
						TVec2<TYPE> V2;
					};
					TYPE Z;
				};
				TVec3<TYPE> V3;
			};
			TYPE W;
		};
		TYPE Data[4]; // Array of elements
		TMatrix<TYPE, 1, 4> M; // As matrix
		TVec4<TYPE> V4; // As TVec4

		TQuaternion() = default;
		TQuaternion(const TQuaternion &other) = default;
		TQuaternion(TQuaternion &&other) = default;

		TQuaternion(const TYPE x, const TYPE y, const TYPE z, const TYPE w): // Create with specified coordinates
			X{ x },
			Y{ y },
			Z{ z },
			W{ w }
		{

		}

		TQuaternion(const TQuaternion &axis, const TYPE angle) : // Create rotatation quaternion around specified axis by specified angle(in radians)
			W{ std::cos(angle / 2) }
		{
			TYPE s{ std::sin(angle / 2) };
			X = axis.X * s;
			Y = axis.Y * s;
			Z = axis.Z * s;
		}

		TQuaternion &operator=(const TQuaternion &other) = default;
		TQuaternion &operator=(TQuaternion &&other) = default;

		TYPE operator[](const size_t index) const // Return element by index. Only 0, 1, 2 and 3 are accepted as indices. Used only when TQuaternion object is a constant object
		{
			return Data[index];
		}

		TYPE &operator[](const size_t index) // Return element by index. Only 0, 1, 2 and 3 are accepted as indices
		{
			return Data[index];
		}

		explicit operator TPoint<TYPE>() const // Convert to TPoint
		{
			return TPoint<TYPE>{ X, Y };
		}

		explicit operator TRect<TYPE>() const // Convert to TRect
		{
			return TRect<TYPE>{ X, Y, Z, W };
		}
	};
}