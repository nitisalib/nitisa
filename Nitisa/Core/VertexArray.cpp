// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region CVertex
	CVertexArray::CVertex::CVertex(CVertexArray *vertex_array, const size_t index, IPolygon *polygon):
		CReleasable(),
		m_pVertexArray{ vertex_array }
	{
		m_pVA = vertex_array;
		m_iVAIndex = index;
		m_pPolygon = polygon;
	}

	void CVertexArray::CVertex::BeforeRelease()
	{
		if (m_pPolygon)
			m_pPolygon->DetachVertex(this);
		m_pVertexArray->EraseVertex(m_iVAIndex);
	}

	const Vec2f *CVertexArray::CVertex::getTextureCoords() const
	{
		if (m_pVertexArray->m_sFormat.TextureCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
			return &m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.TextureCoordIndex][m_iVAIndex];
		return nullptr;
	}

	const Vec2f *CVertexArray::CVertex::getBitmaskCoords() const
	{
		if (m_pVertexArray->m_sFormat.BitmaskCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
			return &m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BitmaskCoordIndex][m_iVAIndex];
		return nullptr;
	}

	const Vec2f *CVertexArray::CVertex::getNormalCoords() const
	{
		if (m_pVertexArray->m_sFormat.NormalCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
			return &m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.NormalCoordIndex][m_iVAIndex];
		return nullptr;
	}

	const Vec2f *CVertexArray::CVertex::getBumpCoords() const
	{
		if (m_pVertexArray->m_sFormat.BumpCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
			return &m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BumpCoordIndex][m_iVAIndex];
		return nullptr;
	}

	const Vec2f *CVertexArray::CVertex::getPosition2D() const
	{
		if (m_pVertexArray->m_sFormat.Position2DIndex < m_pVertexArray->m_sFormat.Vec2fCount)
			return &m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.Position2DIndex][m_iVAIndex];
		if (m_pVertexArray->m_sFormat.Position3DIndex < m_pVertexArray->m_sFormat.Vec3fCount)
			return &m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_iVAIndex].V2;
		if (m_pVertexArray->m_sFormat.Position4DIndex < m_pVertexArray->m_sFormat.Vec4fCount)
			return &m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.Position4DIndex][m_iVAIndex].V2;
		return nullptr;
	}

	const Vec3f *CVertexArray::CVertex::getPosition3D() const
	{
		if (m_pVertexArray->m_sFormat.Position3DIndex < m_pVertexArray->m_sFormat.Vec3fCount)
			return &m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_iVAIndex];
		if (m_pVertexArray->m_sFormat.Position4DIndex < m_pVertexArray->m_sFormat.Vec4fCount)
			return &m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.Position4DIndex][m_iVAIndex].V3;
		return nullptr;
	}

	const Vec4f *CVertexArray::CVertex::getPosition4D() const
	{
		if (m_pVertexArray->m_sFormat.Position4DIndex < m_pVertexArray->m_sFormat.Vec4fCount)
			return &m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.Position4DIndex][m_iVAIndex];
		return nullptr;
	}

	const Vec3f *CVertexArray::CVertex::getNormal() const
	{
		if (m_pVertexArray->m_sFormat.NormalIndex < m_pVertexArray->m_sFormat.Vec3fCount)
			return &m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.NormalIndex][m_iVAIndex];
		return nullptr;
	}

	const Vec4f *CVertexArray::CVertex::getColor() const
	{
		if (m_pVertexArray->m_sFormat.ColorIndex < m_pVertexArray->m_sFormat.Vec4fCount)
			return &m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.ColorIndex][m_iVAIndex];
		return nullptr;
	}

	Vec2f CVertexArray::CVertex::getTextureCoords(const Vec2f &def) const
	{
		if (m_pVertexArray->m_sFormat.TextureCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
			return m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.TextureCoordIndex][m_iVAIndex];
		return def;
	}

	Vec2f CVertexArray::CVertex::getBitmaskCoords(const Vec2f &def) const
	{
		if (m_pVertexArray->m_sFormat.BitmaskCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
			return m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BitmaskCoordIndex][m_iVAIndex];
		return def;
	}

	Vec2f CVertexArray::CVertex::getNormalCoords(const Vec2f &def) const
	{
		if (m_pVertexArray->m_sFormat.NormalCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
			return m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.NormalCoordIndex][m_iVAIndex];
		return def;
	}

	Vec2f CVertexArray::CVertex::getBumpCoords(const Vec2f &def) const
	{
		if (m_pVertexArray->m_sFormat.BumpCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
			return m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BumpCoordIndex][m_iVAIndex];
		return def;
	}

	Vec2f CVertexArray::CVertex::getPosition2D(const Vec2f &def) const
	{
		if (m_pVertexArray->m_sFormat.Position2DIndex < m_pVertexArray->m_sFormat.Vec2fCount)
			return m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.Position2DIndex][m_iVAIndex];
		if (m_pVertexArray->m_sFormat.Position3DIndex < m_pVertexArray->m_sFormat.Vec3fCount)
			return m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_iVAIndex].V2;
		if (m_pVertexArray->m_sFormat.Position4DIndex < m_pVertexArray->m_sFormat.Vec4fCount)
			return m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.Position4DIndex][m_iVAIndex].V2;
		return def;
	}

	Vec3f CVertexArray::CVertex::getPosition3D(const Vec3f &def) const
	{
		if (m_pVertexArray->m_sFormat.Position3DIndex < m_pVertexArray->m_sFormat.Vec3fCount)
			return m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_iVAIndex];
		if (m_pVertexArray->m_sFormat.Position4DIndex < m_pVertexArray->m_sFormat.Vec4fCount)
			return m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.Position4DIndex][m_iVAIndex].V3;
		if (m_pVertexArray->m_sFormat.Position2DIndex < m_pVertexArray->m_sFormat.Vec2fCount)
			return (Vec3f)m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.Position2DIndex][m_iVAIndex];
		return def;
	}

	Vec4f CVertexArray::CVertex::getPosition4D(const Vec4f &def) const
	{
		if (m_pVertexArray->m_sFormat.Position4DIndex < m_pVertexArray->m_sFormat.Vec4fCount)
			return m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.Position4DIndex][m_iVAIndex];
		if (m_pVertexArray->m_sFormat.Position3DIndex < m_pVertexArray->m_sFormat.Vec3fCount)
			return (Vec4f)m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_iVAIndex];
		if (m_pVertexArray->m_sFormat.Position2DIndex < m_pVertexArray->m_sFormat.Vec2fCount)
			return (Vec4f)m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.Position2DIndex][m_iVAIndex];
		return def;
	}

	Vec3f CVertexArray::CVertex::getNormal(const Vec3f &def) const
	{
		if (m_pVertexArray->m_sFormat.NormalIndex < m_pVertexArray->m_sFormat.Vec3fCount)
			return m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.NormalIndex][m_iVAIndex];
		return def;
	}

	Vec4f CVertexArray::CVertex::getColor(const Vec4f &def) const
	{
		if (m_pVertexArray->m_sFormat.ColorIndex < m_pVertexArray->m_sFormat.Vec4fCount)
			return m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.ColorIndex][m_iVAIndex];
		return def;
	}

	bool CVertexArray::CVertex::setTextureCoords(const Vec2f &value)
	{
		if (m_pVertexArray->m_sFormat.TextureCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.TextureCoordIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setBitmaskCoords(const Vec2f &value)
	{
		if (m_pVertexArray->m_sFormat.BitmaskCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BitmaskCoordIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setNormalCoords(const Vec2f &value)
	{
		if (m_pVertexArray->m_sFormat.NormalCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.NormalCoordIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setBumpCoords(const Vec2f &value)
	{
		if (m_pVertexArray->m_sFormat.BumpCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BumpCoordIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setPosition2D(const Vec2f &value)
	{
		if (m_pVertexArray->m_sFormat.Position2DIndex < m_pVertexArray->m_sFormat.Vec2fCount)
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.Position2DIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setPosition3D(const Vec3f &value)
	{
		if (m_pVertexArray->m_sFormat.Position3DIndex < m_pVertexArray->m_sFormat.Vec3fCount)
		{
			m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setPosition4D(const Vec4f &value)
	{
		if (m_pVertexArray->m_sFormat.Position4DIndex < m_pVertexArray->m_sFormat.Vec4fCount)
		{
			m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.Position4DIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setNormal(const Vec3f &value)
	{
		if (m_pVertexArray->m_sFormat.NormalIndex < m_pVertexArray->m_sFormat.Vec3fCount)
		{
			m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.NormalIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setColor(const Vec4f &value)
	{
		if (m_pVertexArray->m_sFormat.ColorIndex < m_pVertexArray->m_sFormat.Vec4fCount)
		{
			m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.ColorIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setTextureCoords(const Vec2f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.TextureCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.TextureCoordIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.TextureCoordIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setBitmaskCoords(const Vec2f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.BitmaskCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BitmaskCoordIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BitmaskCoordIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setNormalCoords(const Vec2f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.NormalCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.NormalCoordIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.NormalCoordIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setBumpCoords(const Vec2f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.BumpCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BumpCoordIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BumpCoordIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setPosition2D(const Vec2f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.Position2DIndex < m_pVertexArray->m_sFormat.Vec2fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.Position2DIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.Position2DIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setPosition3D(const Vec3f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.Position3DIndex < m_pVertexArray->m_sFormat.Vec3fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setPosition4D(const Vec4f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.Position4DIndex < m_pVertexArray->m_sFormat.Vec4fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.Position4DIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.Position4DIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setNormal(const Vec3f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.NormalIndex < m_pVertexArray->m_sFormat.Vec3fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.NormalIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.NormalIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::setColor(const Vec4f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.ColorIndex < m_pVertexArray->m_sFormat.Vec4fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.ColorIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.ColorIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	IVertex *CVertexArray::CVertex::putTextureCoords(const Vec2f &value)
	{
		if (m_pVertexArray->m_sFormat.TextureCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.TextureCoordIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putBitmaskCoords(const Vec2f &value)
	{
		if (m_pVertexArray->m_sFormat.BitmaskCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BitmaskCoordIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putNormalCoords(const Vec2f &value)
	{
		if (m_pVertexArray->m_sFormat.NormalCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.NormalCoordIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putBumpCoords(const Vec2f &value)
	{
		if (m_pVertexArray->m_sFormat.BumpCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BumpCoordIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putPosition2D(const Vec2f &value)
	{
		if (m_pVertexArray->m_sFormat.Position2DIndex < m_pVertexArray->m_sFormat.Vec2fCount)
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.Position2DIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putPosition3D(const Vec3f &value)
	{
		if (m_pVertexArray->m_sFormat.Position3DIndex < m_pVertexArray->m_sFormat.Vec3fCount)
		{
			m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putPosition4D(const Vec4f &value)
	{
		if (m_pVertexArray->m_sFormat.Position4DIndex < m_pVertexArray->m_sFormat.Vec4fCount)
		{
			m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.Position4DIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putNormal(const Vec3f &value)
	{
		if (m_pVertexArray->m_sFormat.NormalIndex < m_pVertexArray->m_sFormat.Vec3fCount)
		{
			m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.NormalIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putColor(const Vec4f &value)
	{
		if (m_pVertexArray->m_sFormat.ColorIndex < m_pVertexArray->m_sFormat.Vec4fCount)
		{
			m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.ColorIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putTextureCoords(const Vec2f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.TextureCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.TextureCoordIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.TextureCoordIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putBitmaskCoords(const Vec2f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.BitmaskCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BitmaskCoordIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BitmaskCoordIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putNormalCoords(const Vec2f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.NormalCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.NormalCoordIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.NormalCoordIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putBumpCoords(const Vec2f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.BumpCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BumpCoordIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BumpCoordIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putPosition2D(const Vec2f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.Position2DIndex < m_pVertexArray->m_sFormat.Vec2fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.Position2DIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.Position2DIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putPosition3D(const Vec3f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.Position3DIndex < m_pVertexArray->m_sFormat.Vec3fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putPosition4D(const Vec4f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.Position4DIndex < m_pVertexArray->m_sFormat.Vec4fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.Position4DIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.Position4DIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putNormal(const Vec3f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.NormalIndex < m_pVertexArray->m_sFormat.Vec3fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.NormalIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.NormalIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	IVertex *CVertexArray::CVertex::putColor(const Vec4f &value, const float relative_tolerance)
	{
		if (m_pVertexArray->m_sFormat.ColorIndex < m_pVertexArray->m_sFormat.Vec4fCount &&
			ntl::NotEquals<float>(value, m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.ColorIndex][m_iVAIndex], relative_tolerance))
		{
			m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.ColorIndex][m_iVAIndex] = value;
			m_pVertexArray->m_bChanged = true;
		}
		return this;
	}

	bool CVertexArray::CVertex::CloneTo(IVertex *target) const
	{
		if (target && target != this)
		{
			if (m_pVertexArray->m_sFormat.TextureCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				target->putTextureCoords(m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.TextureCoordIndex][m_iVAIndex]);
			if (m_pVertexArray->m_sFormat.BitmaskCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				target->putBitmaskCoords(m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BitmaskCoordIndex][m_iVAIndex]);
			if (m_pVertexArray->m_sFormat.NormalCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				target->putNormalCoords(m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.NormalCoordIndex][m_iVAIndex]);
			if (m_pVertexArray->m_sFormat.BumpCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				target->putBumpCoords(m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BumpCoordIndex][m_iVAIndex]);
			if (m_pVertexArray->m_sFormat.Position2DIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				target->putPosition2D(m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.Position2DIndex][m_iVAIndex]);
			if (m_pVertexArray->m_sFormat.Position3DIndex < m_pVertexArray->m_sFormat.Vec3fCount)
				target->putPosition3D(m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_iVAIndex]);
			if (m_pVertexArray->m_sFormat.Position4DIndex < m_pVertexArray->m_sFormat.Vec4fCount)
				target->putPosition4D(m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.Position4DIndex][m_iVAIndex]);
			if (m_pVertexArray->m_sFormat.NormalIndex < m_pVertexArray->m_sFormat.Vec3fCount)
				target->putNormal(m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.NormalIndex][m_iVAIndex]);
			if (m_pVertexArray->m_sFormat.ColorIndex < m_pVertexArray->m_sFormat.Vec4fCount)
				target->putColor(m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.ColorIndex][m_iVAIndex]);
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::CloneFrom(IVertex *source)
	{
		if (source && source != this)
		{
			if (m_pVertexArray->m_sFormat.TextureCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.TextureCoordIndex][m_iVAIndex] = source->getTextureCoords(Vec2f{ 0, 0 });
			if (m_pVertexArray->m_sFormat.BitmaskCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BitmaskCoordIndex][m_iVAIndex] = source->getBitmaskCoords(Vec2f{ 0, 0 });
			if (m_pVertexArray->m_sFormat.NormalCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.NormalCoordIndex][m_iVAIndex] = source->getNormalCoords(Vec2f{ 0, 0 });
			if (m_pVertexArray->m_sFormat.BumpCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BumpCoordIndex][m_iVAIndex] = source->getBumpCoords(Vec2f{ 0, 0 });
			if (m_pVertexArray->m_sFormat.Position2DIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.Position2DIndex][m_iVAIndex] = source->getPosition2D(Vec2f{ 0, 0 });
			if (m_pVertexArray->m_sFormat.Position3DIndex < m_pVertexArray->m_sFormat.Vec3fCount)
				m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_iVAIndex] = source->getPosition3D(Vec3f{ 0, 0, 0 });
			if (m_pVertexArray->m_sFormat.Position4DIndex < m_pVertexArray->m_sFormat.Vec4fCount)
				m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.Position4DIndex][m_iVAIndex] = source->getPosition4D(Vec4f{ 0, 0, 0, 0 });
			if (m_pVertexArray->m_sFormat.NormalIndex < m_pVertexArray->m_sFormat.Vec3fCount)
				m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.NormalIndex][m_iVAIndex] = source->getNormal(Vec3f{ 0, 0, 0 });
			if (m_pVertexArray->m_sFormat.ColorIndex < m_pVertexArray->m_sFormat.Vec4fCount)
				m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.ColorIndex][m_iVAIndex] = source->getColor(Vec4f{ 0, 0, 0, 0 });
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::CloneFrom(IVertex *source, const float k)
	{
		if (source && source != this)
		{
			if (m_pVertexArray->m_sFormat.TextureCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.TextureCoordIndex][m_iVAIndex] = source->getTextureCoords(Vec2f{ 0, 0 }) * k;
			if (m_pVertexArray->m_sFormat.BitmaskCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BitmaskCoordIndex][m_iVAIndex] = source->getBitmaskCoords(Vec2f{ 0, 0 }) * k;
			if (m_pVertexArray->m_sFormat.NormalCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.NormalCoordIndex][m_iVAIndex] = source->getNormalCoords(Vec2f{ 0, 0 }) * k;
			if (m_pVertexArray->m_sFormat.BumpCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BumpCoordIndex][m_iVAIndex] = source->getBumpCoords(Vec2f{ 0, 0 }) * k;
			if (m_pVertexArray->m_sFormat.Position2DIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.Position2DIndex][m_iVAIndex] = source->getPosition2D(Vec2f{ 0, 0 }) * k;
			if (m_pVertexArray->m_sFormat.Position3DIndex < m_pVertexArray->m_sFormat.Vec3fCount)
				m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_iVAIndex] = source->getPosition3D(Vec3f{ 0, 0, 0 }) * k;
			if (m_pVertexArray->m_sFormat.Position4DIndex < m_pVertexArray->m_sFormat.Vec4fCount)
				m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.Position4DIndex][m_iVAIndex] = source->getPosition4D(Vec4f{ 0, 0, 0, 0 }) * k;
			if (m_pVertexArray->m_sFormat.NormalIndex < m_pVertexArray->m_sFormat.Vec3fCount)
				m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.NormalIndex][m_iVAIndex] = source->getNormal(Vec3f{ 0, 0, 0 }) * k;
			if (m_pVertexArray->m_sFormat.ColorIndex < m_pVertexArray->m_sFormat.Vec4fCount)
				m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.ColorIndex][m_iVAIndex] = source->getColor(Vec4f{ 0, 0, 0, 0 }) * k;
			return true;
		}
		return false;
	}

	bool CVertexArray::CVertex::CloneFrom(IVertex *source1, IVertex *source2, const float k1, const float k2)
	{
		if (source1 && source1 != this && source2 && source2 != this)
		{
			if (m_pVertexArray->m_sFormat.TextureCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.TextureCoordIndex][m_iVAIndex] = source1->getTextureCoords(Vec2f{ 0, 0 }) * k1 + source2->getTextureCoords(Vec2f{ 0, 0 }) * k2;
			if (m_pVertexArray->m_sFormat.BitmaskCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BitmaskCoordIndex][m_iVAIndex] = source1->getBitmaskCoords(Vec2f{ 0, 0 }) * k1 + source2->getBitmaskCoords(Vec2f{ 0, 0 }) * k2;
			if (m_pVertexArray->m_sFormat.NormalCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.NormalCoordIndex][m_iVAIndex] = source1->getNormalCoords(Vec2f{ 0, 0 }) * k1 + source2->getNormalCoords(Vec2f{ 0, 0 }) * k2;
			if (m_pVertexArray->m_sFormat.BumpCoordIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.BumpCoordIndex][m_iVAIndex] = source1->getBumpCoords(Vec2f{ 0, 0 }) * k1 + source2->getBumpCoords(Vec2f{ 0, 0 }) * k2;
			if (m_pVertexArray->m_sFormat.Position2DIndex < m_pVertexArray->m_sFormat.Vec2fCount)
				m_pVertexArray->m_aVec2f[m_pVertexArray->m_sFormat.Position2DIndex][m_iVAIndex] = source1->getPosition2D(Vec2f{ 0, 0 }) * k1 + source2->getPosition2D(Vec2f{ 0, 0 }) * k2;
			if (m_pVertexArray->m_sFormat.Position3DIndex < m_pVertexArray->m_sFormat.Vec3fCount)
				m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_iVAIndex] = source1->getPosition3D(Vec3f{ 0, 0, 0 }) * k1 + source2->getPosition3D(Vec3f{ 0, 0, 0 }) * k2;
			if (m_pVertexArray->m_sFormat.Position4DIndex < m_pVertexArray->m_sFormat.Vec4fCount)
				m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.Position4DIndex][m_iVAIndex] = source1->getPosition4D(Vec4f{ 0, 0, 0, 0 }) * k1 + source2->getPosition4D(Vec4f{ 0, 0, 0, 0 }) * k2;
			if (m_pVertexArray->m_sFormat.NormalIndex < m_pVertexArray->m_sFormat.Vec3fCount)
				m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.NormalIndex][m_iVAIndex] = source1->getNormal(Vec3f{ 0, 0, 0 }) * k1 + source2->getNormal(Vec3f{ 0, 0, 0 }) * k2;
			if (m_pVertexArray->m_sFormat.ColorIndex < m_pVertexArray->m_sFormat.Vec4fCount)
				m_pVertexArray->m_aVec4f[m_pVertexArray->m_sFormat.ColorIndex][m_iVAIndex] = source1->getColor(Vec4f{ 0, 0, 0, 0 }) * k1 + source2->getColor(Vec4f{ 0, 0, 0, 0 }) * k2;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region CPolygon
	CVertexArray::CPolygon::CPolygon(CVertexArray *vertex_array, const size_t index):
		CReleasable(),
		m_pVertexArray{ vertex_array },
		m_bPlaneValid{ false }
	{
		m_pVA = vertex_array;
		m_iVAIndex = index;
	}

	void CVertexArray::CPolygon::BeforeRelease()
	{
		for (auto v : m_aVertices)
			m_pVertexArray->EraseVertex(v->VAIndex);
		m_pVertexArray->m_bChanged = true;
	}

	size_t CVertexArray::CPolygon::getVertexCount() const
	{
		return m_aVertices.size();
	}

	IVertex *CVertexArray::CPolygon::getVertex(const size_t index)
	{
		if (index < m_aVertices.size())
			return m_aVertices[index];
		return nullptr;
	}

	const Plane &CVertexArray::CPolygon::getPlane()
	{
		if (!m_bPlaneValid)
		{
			if (m_aVertices.size() >= 3)
			{
				const Vec3f &p1{ m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_aVertices[2]->VAIndex] };
				const Vec3f &p2{ m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_aVertices[1]->VAIndex] };
				const Vec3f &p3{ m_pVertexArray->m_aVec3f[m_pVertexArray->m_sFormat.Position3DIndex][m_aVertices[0]->VAIndex] };
				if (ntl::NotEquals<float>(p1, p2, ntl::RelativeTolerance<float>) &&
					ntl::NotEquals<float>(p1, p3, ntl::RelativeTolerance<float>) &&
					ntl::NotEquals<float>(p2, p3, ntl::RelativeTolerance<float>))
					m_sPlane = Plane{ p1, p2, p3 };
				else
					m_sPlane = Plane{};
			}
			m_bPlaneValid = true;
		}
		return m_sPlane;
	}

	float CVertexArray::CPolygon::getArea() const
	{
		float result{ 0 };
		if (m_aVertices.size() >= 3)
		{
			float a{ ntl::Distance<float>(*m_aVertices[0]->getPosition3D(), *m_aVertices[1]->getPosition3D()) }, b, c, p;
			for (size_t i = 2; i < m_aVertices.size(); i++)
			{
				b = ntl::Distance<float>(*m_aVertices[i - 1]->getPosition3D(), *m_aVertices[i]->getPosition3D());
				c = ntl::Distance<float>(*m_aVertices[0]->getPosition3D(), *m_aVertices[i]->getPosition3D());
				p = (a + b + c) / 2;
				result += std::sqrt(p * (p - a) * (p - b) * (p - c));
				a = c;
			}
		}
		return result;
	}

	bool CVertexArray::CPolygon::setVertexCount(const size_t value)
	{
		if (value > 0 || m_aVertices.size() > 0)
		{
			for (auto v : m_aVertices)
				m_pVertexArray->EraseVertex(v->VAIndex);
			m_aVertices.resize(value);
			for (auto &v : m_aVertices)
				v = m_pVertexArray->AddVertex(this);
			m_bPlaneValid = false;
			return true;
		}
		return false;
	}

	bool CVertexArray::CPolygon::setVertices(std::vector<IVertex*> &vertices)
	{
		if (vertices.size() > 0 || m_aVertices.size() > 0)
		{
			for (auto v : vertices)
				if (!v || v->VA != m_pVA)
					return false;
			for (auto v : vertices)
				if (v->Polygon)
					v->Polygon->DetachVertex(v);
			for (auto v : m_aVertices)
				m_pVertexArray->EraseVertex(v->VAIndex);
			m_aVertices = vertices;
			for (auto v : m_aVertices)
				const_cast<IPolygon*&>(v->Polygon) = this;
			m_bPlaneValid = false;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	IVertex *CVertexArray::CPolygon::AddVertex()
	{
		IVertex *result{ m_pVertexArray->AddVertex(this) };
		if (result)
		{
			m_aVertices.push_back(result);
			if (m_aVertices.size() <= 3)
				m_bPlaneValid = false;
			return result;
		}
		return nullptr;
	}

	bool CVertexArray::CPolygon::AddVertex(IVertex *vertex)
	{
		if (vertex && vertex->Polygon != this)
		{
			if (vertex->Polygon)
				vertex->Polygon->DetachVertex(vertex);
			m_aVertices.push_back(vertex);
			const_cast<IPolygon*&>(vertex->Polygon) = this;
			if (m_aVertices.size() <= 3)
				m_bPlaneValid = false;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	IVertex *CVertexArray::CPolygon::InsertVertex(const size_t before)
	{
		IVertex *result{ m_pVertexArray->AddVertex(this) };
		if (result)
		{
			if (before < 3 || m_aVertices.size() <= 3)
				m_bPlaneValid = false;
			if (before < m_aVertices.size())
				m_aVertices.insert(m_aVertices.begin() + before, result);
			else
				m_aVertices.push_back(result);
			return result;
		}
		return nullptr;
	}

	bool CVertexArray::CPolygon::InsertVertex(IVertex *vertex, const size_t before)
	{
		if (vertex && vertex->Polygon != this)
		{
			if (vertex->Polygon)
				vertex->Polygon->DetachVertex(vertex);
			const_cast<IPolygon*&>(vertex->Polygon) = this;
			if (before < 3 || m_aVertices.size() <= 3)
				m_bPlaneValid = false;
			if (before < m_aVertices.size())
				m_aVertices.insert(m_aVertices.begin() + before, vertex);
			else
				m_aVertices.push_back(vertex);
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CPolygon::DetachVertex(const size_t index)
	{
		if (index < m_aVertices.size())
		{
			const_cast<IPolygon*&>(m_aVertices[index]->Polygon) = nullptr;
			m_aVertices.erase(m_aVertices.begin() + index);
			if (index < 3)
				m_bPlaneValid = false;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CPolygon::DetachVertex(IVertex *vertex)
	{
		if (vertex && vertex->Polygon == this)
		{
			const_cast<IPolygon*&>(vertex->Polygon) = nullptr;
			if (m_bPlaneValid && (m_aVertices.size() <= 3 || m_aVertices[0] == vertex || m_aVertices[1] == vertex || m_aVertices[2] == vertex))
				m_bPlaneValid = false;
			for (auto pos = m_aVertices.begin(); pos != m_aVertices.end(); pos++)
				if (*pos == vertex)
				{
					m_aVertices.erase(pos);
					break;
				}
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CPolygon::DeleteVertex(const size_t index)
	{
		if (index < m_aVertices.size())
		{
			const_cast<IPolygon*&>(m_aVertices[index]->Polygon) = nullptr;
			m_pVertexArray->EraseVertex(m_aVertices[index]->VAIndex);
			m_aVertices.erase(m_aVertices.begin() + index);
			if (index < 3)
				m_bPlaneValid = false;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CPolygon::DeleteVertex(IVertex *vertex)
	{
		if (vertex && vertex->Polygon == this)
			for (auto pos = m_aVertices.begin(); pos != m_aVertices.end(); pos++)
				if (*pos == vertex)
				{
					const_cast<IPolygon*&>((*pos)->Polygon) = nullptr;
					m_pVertexArray->EraseVertex((*pos)->VAIndex);
					if (pos - m_aVertices.begin() < 3)
						m_bPlaneValid = false;
					m_aVertices.erase(pos);
					m_pVertexArray->m_bChanged = true;
					return true;
				}
		return false;
	}

	bool CVertexArray::CPolygon::DeleteVertices()
	{
		if (m_aVertices.size() > 0)
		{
			for (auto v : m_aVertices)
			{
				const_cast<IPolygon*&>(v->Polygon) = nullptr;
				m_pVertexArray->EraseVertex(v->VAIndex);
			}
			m_aVertices.clear();
			m_bPlaneValid = false;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CPolygon::Flip()
	{
		if (m_aVertices.size() > 1)
		{
			std::reverse(m_aVertices.begin(), m_aVertices.end());
			m_bPlaneValid = false;
			m_pVertexArray->m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::CPolygon::Split(const Plane &plane, IPolygon **front, IPolygon **back, const float tolerance) const
	{
		if ((!(*back) || (*back != this && *back != *front)) && (!(*front) || *front != this))
		{
			if (*front)
				(*front)->DeleteVertices();
			else
				*front = m_pVertexArray->AddPolygon();
			if (*back)
				(*back)->DeleteVertices();
			else
				*back = m_pVertexArray->AddPolygon();
			IVertex *v1, *v2;
			float t1, t2, k1, k2;
			Vec3f t;
			for (size_t i = 0; i < m_aVertices.size(); i++)
			{
				v1 = m_aVertices[i];
				v2 = m_aVertices[(i + 1) % m_aVertices.size()];
				t1 = ntl::Distance<float>(plane, v1->getPosition3D(Vec3f{ 0, 0, 0 }));
				t2 = ntl::Distance<float>(plane, v2->getPosition3D(Vec3f{ 0, 0, 0 }));
				if (t1 < tolerance)
				{
					if ((*back)->getVertexCount() == 0 ||
						ntl::Distance<float>(v1->getPosition3D(Vec3f{ 0, 0, 0 }), (*back)->getVertex((*back)->getVertexCount() - 1)->getPosition3D(Vec3f{ 0, 0, 0 })) > tolerance)
						v1->CloneTo((*back)->AddVertex());
				}
				if (t1 > -tolerance)
				{
					if ((*front)->getVertexCount() == 0 ||
						ntl::Distance<float>(v1->getPosition3D(Vec3f{ 0, 0, 0 }), (*front)->getVertex((*front)->getVertexCount() - 1)->getPosition3D(Vec3f{ 0, 0, 0 })) > tolerance)
						v1->CloneTo((*front)->AddVertex());
				}
				if (t1 * t2 < -tolerance)
				{
					k1 = t2 / (t2 - t1);
					k2 = t1 / (t1 - t2);
					t = v1->getPosition3D(Vec3f{ 0, 0, 0 }) * k1 + v2->getPosition3D(Vec3f{ 0, 0, 0 }) * k2;
					if ((*back)->getVertexCount() == 0 || ntl::Distance<float>(t, (*back)->getVertex((*back)->getVertexCount() - 1)->getPosition3D(Vec3f{ 0, 0, 0 })) > tolerance)
						(*back)->AddVertex()->CloneFrom(v1, v2, k1, k2);
					if ((*front)->getVertexCount() == 0 || ntl::Distance<float>(t, (*front)->getVertex((*front)->getVertexCount() - 1)->getPosition3D(Vec3f{ 0, 0, 0 })) > tolerance)
						(*front)->AddVertex()->CloneFrom(v1, v2, k1, k2);
				}
			}
			return true;
		}
		return false;
	}

	void CVertexArray::CPolygon::CutBack(const Plane &plane, const float tolerance)
	{
		std::vector<IVertex*> vertices{ m_aVertices };
		BoolArray used;
		used.resize(m_aVertices.size(), false);
		m_aVertices.clear();
		IVertex *v1, *v2;
		float t1, t2, k1, k2;
		Vec3f t;
		for (size_t i = 0; i < vertices.size(); i++)
		{
			v1 = vertices[i];
			v2 = vertices[(i + 1) % vertices.size()];
			t1 = ntl::Distance<float>(plane, v1->getPosition3D(Vec3f{ 0, 0, 0 }));
			t2 = ntl::Distance<float>(plane, v2->getPosition3D(Vec3f{ 0, 0, 0 }));
			if (t1 > -tolerance)
			{
				if (m_aVertices.size() == 0 ||
					ntl::Distance<float>(v1->getPosition3D(Vec3f{ 0, 0, 0 }), m_aVertices[m_aVertices.size() - 1]->getPosition3D(Vec3f{ 0, 0, 0 })) > tolerance)
				{
					m_aVertices.push_back(v1);
					used[i] = true;
				}
			}
			if (t1 * t2 < -tolerance)
			{
				k1 = t2 / (t2 - t1);
				k2 = t1 / (t1 - t2);
				t = v1->getPosition3D(Vec3f{ 0, 0, 0 }) * k1 + v2->getPosition3D(Vec3f{ 0, 0, 0 }) * k2;
				if (m_aVertices.size() == 0 || ntl::Distance<float>(t, m_aVertices[m_aVertices.size() - 1]->getPosition3D(Vec3f{ 0, 0, 0 })) > tolerance)
					AddVertex()->CloneFrom(v1, v2, k1, k2);
			}
		}
		for (size_t i = 0; i < vertices.size(); i++)
			if (!used[i])
			{
				const_cast<IPolygon*&>(vertices[i]->Polygon) = nullptr;
				m_pVertexArray->EraseVertex(vertices[i]->VAIndex);
			}
		m_bPlaneValid = false;
	}

	void CVertexArray::CPolygon::CutBack(const Plane &plane, IPolygon **back, const float tolerance)
	{
		std::vector<IVertex*> vertices{ m_aVertices };
		BoolArray used;
		used.resize(m_aVertices.size(), false);
		m_aVertices.clear();
		if (*back)
			(*back)->DeleteVertices();
		else
			*back = m_pVertexArray->AddPolygon();
		IVertex *v1, *v2;
		float t1, t2, k1, k2;
		Vec3f t;
		for (size_t i = 0; i < vertices.size(); i++)
		{
			v1 = vertices[i];
			v2 = vertices[(i + 1) % vertices.size()];
			t1 = ntl::Distance<float>(plane, v1->getPosition3D(Vec3f{ 0, 0, 0 }));
			t2 = ntl::Distance<float>(plane, v2->getPosition3D(Vec3f{ 0, 0, 0 }));
			if (t1 < tolerance)
			{
				if ((*back)->getVertexCount() == 0 ||
					ntl::Distance<float>(v1->getPosition3D(Vec3f{ 0, 0, 0 }), (*back)->getVertex((*back)->getVertexCount() - 1)->getPosition3D(Vec3f{ 0, 0, 0 })) > tolerance)
					v1->CloneTo((*back)->AddVertex());
			}
			if (t1 > -tolerance)
			{
				if (m_aVertices.size() == 0 ||
					ntl::Distance<float>(v1->getPosition3D(Vec3f{ 0, 0, 0 }), m_aVertices[m_aVertices.size() - 1]->getPosition3D(Vec3f{ 0, 0, 0 })) > tolerance)
				{
					m_aVertices.push_back(v1);
					used[i] = true;
				}
			}
			if (t1 * t2 < -tolerance)
			{
				k1 = t2 / (t2 - t1);
				k2 = t1 / (t1 - t2);
				t = v1->getPosition3D(Vec3f{ 0, 0, 0 }) * k1 + v2->getPosition3D(Vec3f{ 0, 0, 0 }) * k2;
				if (m_aVertices.size() == 0 || ntl::Distance<float>(t, m_aVertices[m_aVertices.size() - 1]->getPosition3D(Vec3f{ 0, 0, 0 })) > tolerance)
					AddVertex()->CloneFrom(v1, v2, k1, k2);
				if ((*back)->getVertexCount() == 0 || ntl::Distance<float>(t, (*back)->getVertex((*back)->getVertexCount() - 1)->getPosition3D(Vec3f{ 0, 0, 0 })) > tolerance)
					(*back)->AddVertex()->CloneFrom(v1, v2, k1, k2);
			}
		}
		for (size_t i = 0; i < vertices.size(); i++)
			if (!used[i])
			{
				const_cast<IPolygon*&>(vertices[i]->Polygon) = nullptr;
				m_pVertexArray->EraseVertex(vertices[i]->VAIndex);
			}
		m_bPlaneValid = false;
	}

	void CVertexArray::CPolygon::CutFront(const Plane &plane, const float tolerance)
	{
		std::vector<IVertex*> vertices{ m_aVertices };
		BoolArray used;
		used.resize(m_aVertices.size(), false);
		m_aVertices.clear();
		IVertex *v1, *v2;
		float t1, t2, k1, k2;
		Vec3f t;
		for (size_t i = 0; i < vertices.size(); i++)
		{
			v1 = vertices[i];
			v2 = vertices[(i + 1) % vertices.size()];
			t1 = ntl::Distance<float>(plane, v1->getPosition3D(Vec3f{ 0, 0, 0 }));
			t2 = ntl::Distance<float>(plane, v2->getPosition3D(Vec3f{ 0, 0, 0 }));
			if (t1 < tolerance)
			{
				if (m_aVertices.size() == 0 ||
					ntl::Distance<float>(v1->getPosition3D(Vec3f{ 0, 0, 0 }), m_aVertices[m_aVertices.size() - 1]->getPosition3D(Vec3f{ 0, 0, 0 })) > tolerance)
				{
					m_aVertices.push_back(v1);
					used[i] = true;
				}
			}
			if (t1 * t2 < -tolerance)
			{
				k1 = t2 / (t2 - t1);
				k2 = t1 / (t1 - t2);
				t = v1->getPosition3D(Vec3f{ 0, 0, 0 }) * k1 + v2->getPosition3D(Vec3f{ 0, 0, 0 }) * k2;
				if (m_aVertices.size() == 0 || ntl::Distance<float>(t, m_aVertices[m_aVertices.size() - 1]->getPosition3D(Vec3f{ 0, 0, 0 })) > tolerance)
					AddVertex()->CloneFrom(v1, v2, k1, k2);
			}
		}
		for (size_t i = 0; i < vertices.size(); i++)
			if (!used[i])
			{
				const_cast<IPolygon*&>(vertices[i]->Polygon) = nullptr;
				m_pVertexArray->EraseVertex(vertices[i]->VAIndex);
			}
		m_bPlaneValid = false;
	}

	void CVertexArray::CPolygon::CutFront(const Plane &plane, IPolygon **front, const float tolerance)
	{
		std::vector<IVertex*> vertices{ m_aVertices };
		BoolArray used;
		used.resize(m_aVertices.size(), false);
		m_aVertices.clear();
		if (*front)
			(*front)->DeleteVertices();
		else
			*front = m_pVertexArray->AddPolygon();
		IVertex *v1, *v2;
		float t1, t2, k1, k2;
		Vec3f t;
		for (size_t i = 0; i < vertices.size(); i++)
		{
			v1 = vertices[i];
			v2 = vertices[(i + 1) % vertices.size()];
			t1 = ntl::Distance<float>(plane, v1->getPosition3D(Vec3f{ 0, 0, 0 }));
			t2 = ntl::Distance<float>(plane, v2->getPosition3D(Vec3f{ 0, 0, 0 }));
			if (t1 < tolerance)
			{
				if (m_aVertices.size() == 0 ||
					ntl::Distance<float>(v1->getPosition3D(Vec3f{ 0, 0, 0 }), m_aVertices[m_aVertices.size() - 1]->getPosition3D(Vec3f{ 0, 0, 0 })) > tolerance)
				{
					m_aVertices.push_back(v1);
					used[i] = true;
				}
			}
			if (t1 > -tolerance)
			{
				if ((*front)->getVertexCount() == 0 ||
					ntl::Distance<float>(v1->getPosition3D(Vec3f{ 0, 0, 0 }), (*front)->getVertex((*front)->getVertexCount() - 1)->getPosition3D(Vec3f{ 0, 0, 0 })) > tolerance)
					v1->CloneTo((*front)->AddVertex());
			}
			if (t1 * t2 < -tolerance)
			{
				k1 = t2 / (t2 - t1);
				k2 = t1 / (t1 - t2);
				t = v1->getPosition3D(Vec3f{ 0, 0, 0 }) * k1 + v2->getPosition3D(Vec3f{ 0, 0, 0 }) * k2;
				if (m_aVertices.size() == 0 || ntl::Distance<float>(t, m_aVertices[m_aVertices.size() - 1]->getPosition3D(Vec3f{ 0, 0, 0 })) > tolerance)
					AddVertex()->CloneFrom(v1, v2, k1, k2);
				if ((*front)->getVertexCount() == 0 || ntl::Distance<float>(t, (*front)->getVertex((*front)->getVertexCount() - 1)->getPosition3D(Vec3f{ 0, 0, 0 })) > tolerance)
					(*front)->AddVertex()->CloneFrom(v1, v2, k1, k2);
			}
		}
		for (size_t i = 0; i < vertices.size(); i++)
			if (!used[i])
			{
				const_cast<IPolygon*&>(vertices[i]->Polygon) = nullptr;
				m_pVertexArray->EraseVertex(vertices[i]->VAIndex);
			}
		m_bPlaneValid = false;
	}
#pragma endregion

#pragma region Constructor & destructor
	CVertexArray::CVertexArray(const VertexFormat &format):
		CReleasable(),
		m_iLastRenderedPrimitives{ PRIMITIVE_NONE }
	{
		m_sFormat = format;
		m_hHandle = 0;
		m_bChanged = true;
	}

	CVertexArray::CVertexArray(const VertexFormat &format, const size_t vertex_count) :
		CVertexArray(format)
	{
		if (vertex_count > 0)
			ResizeVertices(vertex_count);
	}

	CVertexArray::CVertexArray(const VertexFormat &format, const size_t polygon_count, const size_t polygon_size) :
		CVertexArray(format)
	{
		if (polygon_count > 0)
			ResizePolygons(polygon_count, polygon_size);
	}

	void CVertexArray::BeforeRelease()
	{
		for (auto p : m_aPolygons)
			delete p;
		for (auto v : m_aVertices)
			delete v;
	}
#pragma endregion

#pragma region IVertexArray getters
	size_t CVertexArray::getVertexCount() const
	{
		return m_aVertices.size();
	}

	IVertex *CVertexArray::getVertex(const size_t index)
	{
		if (index < m_aVertices.size())
			return m_aVertices[index];
		return nullptr;
	}

	size_t CVertexArray::getPolygonCount() const
	{
		return m_aPolygons.size();
	}

	IPolygon *CVertexArray::getPolygon(const size_t index)
	{
		if (index < m_aPolygons.size())
			return m_aPolygons[index];
		return nullptr;
	}

	const Vec1f *CVertexArray::getVec1f(const byte coord_index, const size_t index) const
	{
		if (coord_index < m_sFormat.Vec1fCount && index < m_aVertices.size())
			return &m_aVec1f[coord_index][index];
		return nullptr;
	}

	const Vec2f *CVertexArray::getVec2f(const byte coord_index, const size_t index) const
	{
		if (coord_index < m_sFormat.Vec2fCount && index < m_aVertices.size())
			return &m_aVec2f[coord_index][index];
		return nullptr;
	}

	const Vec3f *CVertexArray::getVec3f(const byte coord_index, const size_t index) const
	{
		if (coord_index < m_sFormat.Vec3fCount && index < m_aVertices.size())
			return &m_aVec3f[coord_index][index];
		return nullptr;
	}

	const Vec4f *CVertexArray::getVec4f(const byte coord_index, const size_t index) const
	{
		if (coord_index < m_sFormat.Vec4fCount && index < m_aVertices.size())
			return &m_aVec4f[coord_index][index];
		return nullptr;
	}

	const Vec1i *CVertexArray::getVec1i(const byte coord_index, const size_t index) const
	{
		if (coord_index < m_sFormat.Vec1iCount && index < m_aVertices.size())
			return &m_aVec1i[coord_index][index];
		return nullptr;
	}

	const Vec2i *CVertexArray::getVec2i(const byte coord_index, const size_t index) const
	{
		if (coord_index < m_sFormat.Vec2iCount && index < m_aVertices.size())
			return &m_aVec2i[coord_index][index];
		return nullptr;
	}

	const Vec3i *CVertexArray::getVec3i(const byte coord_index, const size_t index) const
	{
		if (coord_index < m_sFormat.Vec3iCount && index < m_aVertices.size())
			return &m_aVec3i[coord_index][index];
		return nullptr;
	}

	const Vec4i *CVertexArray::getVec4i(const byte coord_index, const size_t index) const
	{
		if (coord_index < m_sFormat.Vec4iCount && index < m_aVertices.size())
			return &m_aVec4i[coord_index][index];
		return nullptr;
	}

	const Vec1f *CVertexArray::getVec1fArray(const byte coord_index) const
	{
		if (coord_index < m_sFormat.Vec1fCount)
			return m_aVec1f[coord_index].data();
		return nullptr;
	}

	const Vec2f *CVertexArray::getVec2fArray(const byte coord_index) const
	{
		if (coord_index < m_sFormat.Vec2fCount)
			return m_aVec2f[coord_index].data();
		return nullptr;
	}

	const Vec3f *CVertexArray::getVec3fArray(const byte coord_index) const
	{
		if (coord_index < m_sFormat.Vec3fCount)
			return m_aVec3f[coord_index].data();
		return nullptr;
	}

	const Vec4f *CVertexArray::getVec4fArray(const byte coord_index) const
	{
		if (coord_index < m_sFormat.Vec4fCount)
			return m_aVec4f[coord_index].data();
		return nullptr;
	}

	const Vec1i *CVertexArray::getVec1iArray(const byte coord_index) const
	{
		if (coord_index < m_sFormat.Vec1iCount)
			return m_aVec1i[coord_index].data();
		return nullptr;
	}

	const Vec2i *CVertexArray::getVec2iArray(const byte coord_index) const
	{
		if (coord_index < m_sFormat.Vec2iCount)
			return m_aVec2i[coord_index].data();
		return nullptr;
	}

	const Vec3i *CVertexArray::getVec3iArray(const byte coord_index) const
	{
		if (coord_index < m_sFormat.Vec3iCount)
			return m_aVec3i[coord_index].data();
		return nullptr;
	}

	const Vec4i *CVertexArray::getVec4iArray(const byte coord_index) const
	{
		if (coord_index < m_sFormat.Vec4iCount)
			return m_aVec4i[coord_index].data();
		return nullptr;
	}
#pragma endregion

#pragma region IVertexArray setters
	bool CVertexArray::setVertexCount(const size_t value)
	{
		if (value > 0 || m_aVertices.size() > 0)
		{
			for (auto v : m_aVertices)
				if (v->Polygon)
					v->Polygon->DetachVertex(v);
			ResizeVertices(value);
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setPolygonCount(const size_t value)
	{
		if (value > 0 || m_aPolygons.size() > 0)
		{
			ResizePolygons(value);
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setPolygonCount(const size_t count, const size_t size)
	{
		if (count > 0 || m_aPolygons.size() > 0)
		{
			ResizePolygons(count, size);
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec1f(const byte coord_index, const size_t index, const Vec1f &value)
	{
		if (coord_index < m_sFormat.Vec1fCount && index < m_aVertices.size())
		{
			m_aVec1f[coord_index][index] = value;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec2f(const byte coord_index, const size_t index, const Vec2f &value)
	{
		if (coord_index < m_sFormat.Vec2fCount && index < m_aVertices.size())
		{
			m_aVec2f[coord_index][index] = value;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec3f(const byte coord_index, const size_t index, const Vec3f &value)
	{
		if (coord_index < m_sFormat.Vec3fCount && index < m_aVertices.size())
		{
			m_aVec3f[coord_index][index] = value;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec4f(const byte coord_index, const size_t index, const Vec4f &value)
	{
		if (coord_index < m_sFormat.Vec4fCount && index < m_aVertices.size())
		{
			m_aVec4f[coord_index][index] = value;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec1f(const byte coord_index, const size_t index, const Vec1f &value, const float relative_tolerance)
	{
		if (coord_index < m_sFormat.Vec1fCount && index < m_aVertices.size() && ntl::NotEquals<float>(value, m_aVec1f[coord_index][index], relative_tolerance))
		{
			m_aVec1f[coord_index][index] = value;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec2f(const byte coord_index, const size_t index, const Vec2f &value, const float relative_tolerance)
	{
		if (coord_index < m_sFormat.Vec2fCount && index < m_aVertices.size() && ntl::NotEquals<float>(value, m_aVec2f[coord_index][index], relative_tolerance))
		{
			m_aVec2f[coord_index][index] = value;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec3f(const byte coord_index, const size_t index, const Vec3f &value, const float relative_tolerance)
	{
		if (coord_index < m_sFormat.Vec3fCount && index < m_aVertices.size() && ntl::NotEquals<float>(value, m_aVec3f[coord_index][index], relative_tolerance))
		{
			m_aVec3f[coord_index][index] = value;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec4f(const byte coord_index, const size_t index, const Vec4f &value, const float relative_tolerance)
	{
		if (coord_index < m_sFormat.Vec4fCount && index < m_aVertices.size() && ntl::NotEquals<float>(value, m_aVec4f[coord_index][index], relative_tolerance))
		{
			m_aVec4f[coord_index][index] = value;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec1f(const size_t index, const Vec1f &value)
	{
		if (index < m_aVertices.size())
		{
			bool result{ false };
			for (byte i = 0; i < m_sFormat.Vec1fCount; i++)
			{
				m_aVec1f[i][index] = value;
				result = true;
			}
			if (result)
				m_bChanged = true;
			return result;
		}
		return false;
	}

	bool CVertexArray::setVec2f(const size_t index, const Vec2f &value)
	{
		if (index < m_aVertices.size())
		{
			bool result{ false };
			for (byte i = 0; i < m_sFormat.Vec2fCount; i++)
			{
				m_aVec2f[i][index] = value;
				result = true;
			}
			if (result)
				m_bChanged = true;
			return result;
		}
		return false;
	}

	bool CVertexArray::setVec3f(const size_t index, const Vec3f &value)
	{
		if (index < m_aVertices.size())
		{
			bool result{ false };
			for (byte i = 0; i < m_sFormat.Vec3fCount; i++)
			{
				m_aVec3f[i][index] = value;
				result = true;
			}
			if (result)
				m_bChanged = true;
			return result;
		}
		return false;
	}

	bool CVertexArray::setVec4f(const size_t index, const Vec4f &value)
	{
		if (index < m_aVertices.size())
		{
			bool result{ false };
			for (byte i = 0; i < m_sFormat.Vec4fCount; i++)
			{
				m_aVec4f[i][index] = value;
				result = true;
			}
			if (result)
				m_bChanged = true;
			return result;
		}
		return false;
	}

	bool CVertexArray::setVec1f(const size_t index, const Vec1f &value, const float relative_tolerance)
	{
		if (index < m_aVertices.size())
		{
			bool result{ false };
			for (byte i = 0; i < m_sFormat.Vec1fCount; i++)
				if (ntl::NotEquals<float>(value, m_aVec1f[i][index], relative_tolerance))
				{
					m_aVec1f[i][index] = value;
					result = true;
				}
			if (result)
				m_bChanged = true;
			return result;
		}
		return false;
	}

	bool CVertexArray::setVec2f(const size_t index, const Vec2f &value, const float relative_tolerance)
	{
		if (index < m_aVertices.size())
		{
			bool result{ false };
			for (byte i = 0; i < m_sFormat.Vec2fCount; i++)
				if (ntl::NotEquals<float>(value, m_aVec2f[i][index], relative_tolerance))
				{
					m_aVec2f[i][index] = value;
					result = true;
				}
			if (result)
				m_bChanged = true;
			return result;
		}
		return false;
	}

	bool CVertexArray::setVec3f(const size_t index, const Vec3f &value, const float relative_tolerance)
	{
		if (index < m_aVertices.size())
		{
			bool result{ false };
			for (byte i = 0; i < m_sFormat.Vec3fCount; i++)
				if (ntl::NotEquals<float>(value, m_aVec3f[i][index], relative_tolerance))
				{
					m_aVec3f[i][index] = value;
					result = true;
				}
			if (result)
				m_bChanged = true;
			return result;
		}
		return false;
	}

	bool CVertexArray::setVec4f(const size_t index, const Vec4f &value, const float relative_tolerance)
	{
		if (index < m_aVertices.size())
		{
			bool result{ false };
			for (byte i = 0; i < m_sFormat.Vec4fCount; i++)
				if (ntl::NotEquals<float>(value, m_aVec4f[i][index], relative_tolerance))
				{
					m_aVec4f[i][index] = value;
					result = true;
				}
			if (result)
				m_bChanged = true;
			return result;
		}
		return false;
	}

	bool CVertexArray::setVec1i(const byte coord_index, const size_t index, const Vec1i &value)
	{
		if (coord_index < m_sFormat.Vec1iCount && index < m_aVertices.size())
		{
			m_aVec1i[coord_index][index] = value;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec2i(const byte coord_index, const size_t index, const Vec2i &value)
	{
		if (coord_index < m_sFormat.Vec2iCount && index < m_aVertices.size())
		{
			m_aVec2i[coord_index][index] = value;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec3i(const byte coord_index, const size_t index, const Vec3i &value)
	{
		if (coord_index < m_sFormat.Vec3iCount && index < m_aVertices.size())
		{
			m_aVec3i[coord_index][index] = value;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec4i(const byte coord_index, const size_t index, const Vec4i &value)
	{
		if (coord_index < m_sFormat.Vec4iCount && index < m_aVertices.size())
		{
			m_aVec4i[coord_index][index] = value;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec1i(const byte coord_index, const size_t index, const Vec1i &value, const float relative_tolerance)
	{
		if (coord_index < m_sFormat.Vec1iCount && index < m_aVertices.size() && ntl::NotEquals<int, float>(value, m_aVec1i[coord_index][index], relative_tolerance))
		{
			m_aVec1i[coord_index][index] = value;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec2i(const byte coord_index, const size_t index, const Vec2i &value, const float relative_tolerance)
	{
		if (coord_index < m_sFormat.Vec2iCount && index < m_aVertices.size() && ntl::NotEquals<int, float>(value, m_aVec2i[coord_index][index], relative_tolerance))
		{
			m_aVec2i[coord_index][index] = value;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec3i(const byte coord_index, const size_t index, const Vec3i &value, const float relative_tolerance)
	{
		if (coord_index < m_sFormat.Vec3iCount && index < m_aVertices.size() && ntl::NotEquals<int, float>(value, m_aVec3i[coord_index][index], relative_tolerance))
		{
			m_aVec3i[coord_index][index] = value;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec4i(const byte coord_index, const size_t index, const Vec4i &value, const float relative_tolerance)
	{
		if (coord_index < m_sFormat.Vec4iCount && index < m_aVertices.size() && ntl::NotEquals<int, float>(value, m_aVec4i[coord_index][index], relative_tolerance))
		{
			m_aVec4i[coord_index][index] = value;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::setVec1i(const size_t index, const Vec1i &value)
	{
		if (index < m_aVertices.size())
		{
			bool result{ false };
			for (byte i = 0; i < m_sFormat.Vec1iCount; i++)
			{
				m_aVec1i[i][index] = value;
				result = true;
			}
			if (result)
				m_bChanged = true;
			return result;
		}
		return false;
	}

	bool CVertexArray::setVec2i(const size_t index, const Vec2i &value)
	{
		if (index < m_aVertices.size())
		{
			bool result{ false };
			for (byte i = 0; i < m_sFormat.Vec2iCount; i++)
			{
				m_aVec2i[i][index] = value;
				result = true;
			}
			if (result)
				m_bChanged = true;
			return result;
		}
		return false;
	}

	bool CVertexArray::setVec3i(const size_t index, const Vec3i &value)
	{
		if (index < m_aVertices.size())
		{
			bool result{ false };
			for (byte i = 0; i < m_sFormat.Vec3iCount; i++)
			{
				m_aVec3i[i][index] = value;
				result = true;
			}
			if (result)
				m_bChanged = true;
			return result;
		}
		return false;
	}

	bool CVertexArray::setVec4i(const size_t index, const Vec4i &value)
	{
		if (index < m_aVertices.size())
		{
			bool result{ false };
			for (byte i = 0; i < m_sFormat.Vec4iCount; i++)
			{
				m_aVec4i[i][index] = value;
				result = true;
			}
			if (result)
				m_bChanged = true;
			return result;
		}
		return false;
	}

	bool CVertexArray::setVec1i(const size_t index, const Vec1i &value, const float relative_tolerance)
	{
		if (index < m_aVertices.size())
		{
			bool result{ false };
			for (byte i = 0; i < m_sFormat.Vec1iCount; i++)
				if (ntl::NotEquals<int, float>(value, m_aVec1i[i][index], relative_tolerance))
				{
					m_aVec1i[i][index] = value;
					result = true;
				}
			if (result)
				m_bChanged = true;
			return result;
		}
		return false;
	}

	bool CVertexArray::setVec2i(const size_t index, const Vec2i &value, const float relative_tolerance)
	{
		if (index < m_aVertices.size())
		{
			bool result{ false };
			for (byte i = 0; i < m_sFormat.Vec2iCount; i++)
				if (ntl::NotEquals<int, float>(value, m_aVec2i[i][index], relative_tolerance))
				{
					m_aVec2i[i][index] = value;
					result = true;
				}
			if (result)
				m_bChanged = true;
			return result;
		}
		return false;
	}

	bool CVertexArray::setVec3i(const size_t index, const Vec3i &value, const float relative_tolerance)
	{
		if (index < m_aVertices.size())
		{
			bool result{ false };
			for (byte i = 0; i < m_sFormat.Vec3iCount; i++)
				if (ntl::NotEquals<int, float>(value, m_aVec3i[i][index], relative_tolerance))
				{
					m_aVec3i[i][index] = value;
					result = true;
				}
			if (result)
				m_bChanged = true;
			return result;
		}
		return false;
	}

	bool CVertexArray::setVec4i(const size_t index, const Vec4i &value, const float relative_tolerance)
	{
		if (index < m_aVertices.size())
		{
			bool result{ false };
			for (byte i = 0; i < m_sFormat.Vec4iCount; i++)
				if (ntl::NotEquals<int, float>(value, m_aVec4i[i][index], relative_tolerance))
				{
					m_aVec4i[i][index] = value;
					result = true;
				}
			if (result)
				m_bChanged = true;
			return result;
		}
		return false;
	}
#pragma endregion

#pragma region IVertexArray vertices
	IVertex *CVertexArray::AddVertex(IPolygon *polygon)
	{
		CVertex *result{ new CVertex(this, m_aVertices.size(), polygon) };
		m_aVertices.push_back(result);
		for (byte i = 0; i < m_sFormat.Vec1fCount; i++)
			m_aVec1f[i].push_back(Vec1f{ 0 });
		for (byte i = 0; i < m_sFormat.Vec2fCount; i++)
			m_aVec2f[i].push_back(Vec2f{ 0, 0 });
		for (byte i = 0; i < m_sFormat.Vec3fCount; i++)
			m_aVec3f[i].push_back(Vec3f{ 0, 0, 0 });
		for (byte i = 0; i < m_sFormat.Vec4fCount; i++)
			m_aVec4f[i].push_back(Vec4f{ 0, 0, 0, 0 });
		for (byte i = 0; i < m_sFormat.Vec1iCount; i++)
			m_aVec1i[i].push_back(Vec1i{ 0 });
		for (byte i = 0; i < m_sFormat.Vec2iCount; i++)
			m_aVec2i[i].push_back(Vec2i{ 0, 0 });
		for (byte i = 0; i < m_sFormat.Vec3iCount; i++)
			m_aVec3i[i].push_back(Vec3i{ 0, 0, 0 });
		for (byte i = 0; i < m_sFormat.Vec4iCount; i++)
			m_aVec4i[i].push_back(Vec4i{ 0, 0, 0, 0 });
		m_bChanged = true;
		return result;
	}

	IVertex *CVertexArray::AddVertex(const size_t before, IPolygon *polygon)
	{
		CVertex *result;
		if (before < m_aVertices.size())
		{
			result = new CVertex(this, before, polygon);
			m_aVertices.insert(m_aVertices.begin() + before, result);
			for (size_t i = before + 1; i < m_aVertices.size(); i++)
				m_aVertices[i]->m_iVAIndex++;
			for (byte i = 0; i < m_sFormat.Vec1fCount; i++)
				m_aVec1f[i].insert(m_aVec1f[i].begin() + before, Vec1f{ 0 });
			for (byte i = 0; i < m_sFormat.Vec2fCount; i++)
				m_aVec2f[i].insert(m_aVec2f[i].begin() + before, Vec2f{ 0, 0 });
			for (byte i = 0; i < m_sFormat.Vec3fCount; i++)
				m_aVec3f[i].insert(m_aVec3f[i].begin() + before, Vec3f{ 0, 0, 0 });
			for (byte i = 0; i < m_sFormat.Vec4fCount; i++)
				m_aVec4f[i].insert(m_aVec4f[i].begin() + before, Vec4f{ 0, 0, 0, 0 });
			for (byte i = 0; i < m_sFormat.Vec1iCount; i++)
				m_aVec1i[i].insert(m_aVec1i[i].begin() + before, Vec1i{ 0 });
			for (byte i = 0; i < m_sFormat.Vec2iCount; i++)
				m_aVec2i[i].insert(m_aVec2i[i].begin() + before, Vec2i{ 0, 0 });
			for (byte i = 0; i < m_sFormat.Vec3iCount; i++)
				m_aVec3i[i].insert(m_aVec3i[i].begin() + before, Vec3i{ 0, 0, 0 });
			for (byte i = 0; i < m_sFormat.Vec4iCount; i++)
				m_aVec4i[i].insert(m_aVec4i[i].begin() + before, Vec4i{ 0, 0, 0, 0 });
		}
		else
		{
			result = new CVertex(this, m_aVertices.size(), polygon);
			m_aVertices.push_back(result);
			for (byte i = 0; i < m_sFormat.Vec1fCount; i++)
				m_aVec1f[i].push_back(Vec1f{ 0 });
			for (byte i = 0; i < m_sFormat.Vec2fCount; i++)
				m_aVec2f[i].push_back(Vec2f{ 0, 0 });
			for (byte i = 0; i < m_sFormat.Vec3fCount; i++)
				m_aVec3f[i].push_back(Vec3f{ 0, 0, 0 });
			for (byte i = 0; i < m_sFormat.Vec4fCount; i++)
				m_aVec4f[i].push_back(Vec4f{ 0, 0, 0, 0 });
			for (byte i = 0; i < m_sFormat.Vec1iCount; i++)
				m_aVec1i[i].push_back(Vec1i{ 0 });
			for (byte i = 0; i < m_sFormat.Vec2iCount; i++)
				m_aVec2i[i].push_back(Vec2i{ 0, 0 });
			for (byte i = 0; i < m_sFormat.Vec3iCount; i++)
				m_aVec3i[i].push_back(Vec3i{ 0, 0, 0 });
			for (byte i = 0; i < m_sFormat.Vec4iCount; i++)
				m_aVec4i[i].push_back(Vec4i{ 0, 0, 0, 0 });
		}
		m_bChanged = true;
		return result;
	}

	bool CVertexArray::DeleteVertex(const size_t index)
	{
		if (index < m_aVertices.size())
		{
			if (m_aVertices[index]->Polygon)
				m_aVertices[index]->Polygon->DetachVertex(m_aVertices[index]);
			EraseVertex(index);
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::DeleteVertex(IVertex *vertex)
	{
		CVertex *v{ cast<CVertex*>(vertex) };
		if (v && v->m_pVertexArray == this)
			return DeleteVertex(v->VAIndex);
		return false;
	}

	bool CVertexArray::DeleteVertices()
	{
		if (m_aVertices.size() > 0)
		{
			for (auto v : m_aVertices)
			{
				if (v->Polygon)
					v->Polygon->DetachVertex(v);
				delete v;
			}
			m_aVertices.clear();
			for (byte i = 0; i < m_sFormat.Vec1fCount; i++)
				m_aVec1f[i].clear();
			for (byte i = 0; i < m_sFormat.Vec2fCount; i++)
				m_aVec2f[i].clear();
			for (byte i = 0; i < m_sFormat.Vec3fCount; i++)
				m_aVec3f[i].clear();
			for (byte i = 0; i < m_sFormat.Vec4fCount; i++)
				m_aVec4f[i].clear();
			for (byte i = 0; i < m_sFormat.Vec1iCount; i++)
				m_aVec1i[i].clear();
			for (byte i = 0; i < m_sFormat.Vec2iCount; i++)
				m_aVec2i[i].clear();
			for (byte i = 0; i < m_sFormat.Vec3iCount; i++)
				m_aVec3i[i].clear();
			for (byte i = 0; i < m_sFormat.Vec4iCount; i++)
				m_aVec4i[i].clear();
			m_bChanged = true;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region IVertexArray polygons
	IPolygon *CVertexArray::AddPolygon()
	{
		CPolygon *result{ new CPolygon(this, m_aPolygons.size()) };
		m_aPolygons.push_back(result);
		return result;
	}

	IPolygon *CVertexArray::AddPolygon(const size_t before)
	{
		CPolygon *result;
		if (before < m_aPolygons.size())
		{
			result = new CPolygon(this, before);
			m_aPolygons.insert(m_aPolygons.begin() + before, result);
			for (size_t i = before + 1; i < m_aPolygons.size(); i++)
				m_aPolygons[i]->m_iVAIndex++;
		}
		else
		{
			result = new CPolygon(this, m_aPolygons.size());
			m_aPolygons.push_back(result);
		}
		m_bChanged = true;
		return result;
	}

	bool CVertexArray::DeletePolygon(const size_t index)
	{
		if (index < m_aPolygons.size())
		{
			for (auto v : m_aPolygons[index]->m_aVertices)
				EraseVertex(v->VAIndex);
			delete m_aPolygons[index];
			m_aPolygons.erase(m_aPolygons.begin() + index);
			for (size_t i = index; i < m_aPolygons.size(); i++)
				m_aPolygons[index]->m_iVAIndex--;
			m_bChanged = true;
			return true;
		}
		return false;
	}

	bool CVertexArray::DeletePolygon(IPolygon *value)
	{
		CPolygon *p{ cast<CPolygon*>(value) };
		if (p && p->m_pVertexArray == this)
			return DeletePolygon(p->m_iVAIndex);
		return false;
	}

	bool CVertexArray::DeletePolygons()
	{
		if (m_aPolygons.size() > 0)
		{
			for (auto p : m_aPolygons)
			{
				for (auto v : p->m_aVertices)
					EraseVertex(v->VAIndex);
				delete p;
			}
			m_aPolygons.clear();
			m_bChanged = true;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region IVertexArray helpers
	bool CVertexArray::Clear()
	{
		if (m_aPolygons.size() > 0 || m_aVertices.size() > 0)
		{
			for (auto p : m_aPolygons)
				delete p;
			m_aPolygons.clear();
			ResizeVertices(0);
			m_bChanged = true;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Helpers
	bool CVertexArray::CheckFormat(const VertexFormat &format)
	{
		if (format.Vec1fCount + format.Vec2fCount + format.Vec3fCount + format.Vec4fCount + format.Vec1iCount + format.Vec2iCount + format.Vec3iCount + format.Vec4iCount == 0)
			return false;
		return true;
	}

	void CVertexArray::EraseVertex(const size_t index)
	{
		delete m_aVertices[index];
		m_aVertices.erase(m_aVertices.begin() + index);
		for (size_t i = index; i < m_aVertices.size(); i++)
			m_aVertices[i]->m_iVAIndex--;
		for (byte i = 0; i < m_sFormat.Vec1fCount; i++)
			m_aVec1f[i].erase(m_aVec1f[i].begin() + index);
		for (byte i = 0; i < m_sFormat.Vec2fCount; i++)
			m_aVec2f[i].erase(m_aVec2f[i].begin() + index);
		for (byte i = 0; i < m_sFormat.Vec3fCount; i++)
			m_aVec3f[i].erase(m_aVec3f[i].begin() + index);
		for (byte i = 0; i < m_sFormat.Vec4fCount; i++)
			m_aVec4f[i].erase(m_aVec4f[i].begin() + index);
		for (byte i = 0; i < m_sFormat.Vec1iCount; i++)
			m_aVec1i[i].erase(m_aVec1i[i].begin() + index);
		for (byte i = 0; i < m_sFormat.Vec2iCount; i++)
			m_aVec2i[i].erase(m_aVec2i[i].begin() + index);
		for (byte i = 0; i < m_sFormat.Vec3iCount; i++)
			m_aVec3i[i].erase(m_aVec3i[i].begin() + index);
		for (byte i = 0; i < m_sFormat.Vec4iCount; i++)
			m_aVec4i[i].erase(m_aVec4i[i].begin() + index);
	}

	void CVertexArray::ResizeVertices(const size_t count)
	{
		for (auto v : m_aVertices)
			delete v;
		m_aVertices.resize(count);
		for (size_t i = 0; i < count; i++)
			m_aVertices[i] = new CVertex(this, i, nullptr);
		for (byte i = 0; i < m_sFormat.Vec1fCount; i++)
		{
			m_aVec1f[i].clear();
			m_aVec1f[i].resize(count, Vec1f{ 0 });
		}
		for (byte i = 0; i < m_sFormat.Vec2fCount; i++)
		{
			m_aVec2f[i].clear();
			m_aVec2f[i].resize(count, Vec2f{ 0, 0 });
		}
		for (byte i = 0; i < m_sFormat.Vec3fCount; i++)
		{
			m_aVec3f[i].clear();
			m_aVec3f[i].resize(count, Vec3f{ 0, 0, 0 });
		}
		for (byte i = 0; i < m_sFormat.Vec4fCount; i++)
		{
			m_aVec4f[i].clear();
			m_aVec4f[i].resize(count, Vec4f{ 0, 0, 0, 0 });
		}
		for (byte i = 0; i < m_sFormat.Vec1iCount; i++)
		{
			m_aVec1i[i].clear();
			m_aVec1i[i].resize(count, Vec1i{ 0 });
		}
		for (byte i = 0; i < m_sFormat.Vec2iCount; i++)
		{
			m_aVec2i[i].clear();
			m_aVec2i[i].resize(count, Vec2i{ 0, 0 });
		}
		for (byte i = 0; i < m_sFormat.Vec3iCount; i++)
		{
			m_aVec3i[i].clear();
			m_aVec3i[i].resize(count, Vec3i{ 0, 0, 0 });
		}
		for (byte i = 0; i < m_sFormat.Vec4iCount; i++)
		{
			m_aVec4i[i].clear();
			m_aVec4i[i].resize(count, Vec4i{ 0, 0, 0, 0 });
		}
	}

	void CVertexArray::ResizePolygons(const size_t count)
	{
		for (auto p : m_aPolygons)
		{
			for (auto v : p->m_aVertices)
				EraseVertex(v->VAIndex);
			delete p;
		}
		m_aPolygons.resize(count);
		for (size_t i = 0; i < count; i++)
			m_aPolygons[i] = new CPolygon(this, i);
	}

	void CVertexArray::ResizePolygons(const size_t count, const size_t size)
	{
		ResizeVertices(count * size);
		for (auto p : m_aPolygons)
			delete p;
		m_aPolygons.resize(count);
		size_t polygon_index{ 0 }, vertex_index{ 0 };
		for (auto &p : m_aPolygons)
		{
			p = new CPolygon(this, polygon_index++);
			for (size_t i = 0; i < size; i++, vertex_index++)
				p->AddVertex(m_aVertices[vertex_index]);
		}
	}
#pragma endregion
}