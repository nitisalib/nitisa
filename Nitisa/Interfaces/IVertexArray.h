// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "../Core/VertexFormat.h"
#include "../Math/Vec1f.h"
#include "../Math/Vec1i.h"
#include "../Math/Vec2f.h"
#include "../Math/Vec2i.h"
#include "../Math/Vec3f.h"
#include "../Math/Vec3i.h"
#include "../Math/Vec4f.h"
#include "../Math/Vec4i.h"
#include "IReleasable.h"

namespace nitisa
{
	class IPolygon;
	class IVertex;

	class IVertexArray :public virtual IReleasable
	{
	protected:
		IVertexArray() = default;
		~IVertexArray() = default;
		IVertexArray(const IVertexArray &other) = delete;
		IVertexArray(IVertexArray &&other) = delete;
		IVertexArray &operator=(const IVertexArray &other) = delete;
		IVertexArray &operator=(IVertexArray &&other) = delete;
	protected:
		VertexFormat m_sFormat;
		PlatformHandle m_hHandle;
		bool m_bChanged;
	public:
		VertexFormat const &Format{ m_sFormat }; // Vertex format
		PlatformHandle const &Handle{ m_hHandle }; // Platform-dependent handle
		bool const &Changed{ m_bChanged }; // Whether it was changed

		// Getters
		virtual size_t getVertexCount() const = 0;
		virtual IVertex *getVertex(const size_t index) = 0;
		virtual size_t getPolygonCount() const = 0;
		virtual IPolygon *getPolygon(const size_t index) = 0;
		virtual const Vec1f *getVec1f(const byte coord_index, const size_t index) const = 0;
		virtual const Vec2f *getVec2f(const byte coord_index, const size_t index) const = 0;
		virtual const Vec3f *getVec3f(const byte coord_index, const size_t index) const = 0;
		virtual const Vec4f *getVec4f(const byte coord_index, const size_t index) const = 0;
		virtual const Vec1i *getVec1i(const byte coord_index, const size_t index) const = 0;
		virtual const Vec2i *getVec2i(const byte coord_index, const size_t index) const = 0;
		virtual const Vec3i *getVec3i(const byte coord_index, const size_t index) const = 0;
		virtual const Vec4i *getVec4i(const byte coord_index, const size_t index) const = 0;
		virtual const Vec1f *getVec1fArray(const byte coord_index) const = 0;
		virtual const Vec2f *getVec2fArray(const byte coord_index) const = 0;
		virtual const Vec3f *getVec3fArray(const byte coord_index) const = 0;
		virtual const Vec4f *getVec4fArray(const byte coord_index) const = 0;
		virtual const Vec1i *getVec1iArray(const byte coord_index) const = 0;
		virtual const Vec2i *getVec2iArray(const byte coord_index) const = 0;
		virtual const Vec3i *getVec3iArray(const byte coord_index) const = 0;
		virtual const Vec4i *getVec4iArray(const byte coord_index) const = 0;

		// Setters
		virtual bool setVertexCount(const size_t value) = 0;
		virtual bool setPolygonCount(const size_t value) = 0;
		virtual bool setPolygonCount(const size_t count, const size_t size) = 0;
		virtual bool setVec1f(const byte coord_index, const size_t index, const Vec1f &value) = 0;
		virtual bool setVec2f(const byte coord_index, const size_t index, const Vec2f &value) = 0;
		virtual bool setVec3f(const byte coord_index, const size_t index, const Vec3f &value) = 0;
		virtual bool setVec4f(const byte coord_index, const size_t index, const Vec4f &value) = 0;
		virtual bool setVec1f(const byte coord_index, const size_t index, const Vec1f &value, const float relative_tolerance) = 0;
		virtual bool setVec2f(const byte coord_index, const size_t index, const Vec2f &value, const float relative_tolerance) = 0;
		virtual bool setVec3f(const byte coord_index, const size_t index, const Vec3f &value, const float relative_tolerance) = 0;
		virtual bool setVec4f(const byte coord_index, const size_t index, const Vec4f &value, const float relative_tolerance) = 0;
		virtual bool setVec1f(const size_t index, const Vec1f &value) = 0;
		virtual bool setVec2f(const size_t index, const Vec2f &value) = 0;
		virtual bool setVec3f(const size_t index, const Vec3f &value) = 0;
		virtual bool setVec4f(const size_t index, const Vec4f &value) = 0;
		virtual bool setVec1f(const size_t index, const Vec1f &value, const float relative_tolerance) = 0;
		virtual bool setVec2f(const size_t index, const Vec2f &value, const float relative_tolerance) = 0;
		virtual bool setVec3f(const size_t index, const Vec3f &value, const float relative_tolerance) = 0;
		virtual bool setVec4f(const size_t index, const Vec4f &value, const float relative_tolerance) = 0;
		virtual bool setVec1i(const byte coord_index, const size_t index, const Vec1i &value) = 0;
		virtual bool setVec2i(const byte coord_index, const size_t index, const Vec2i &value) = 0;
		virtual bool setVec3i(const byte coord_index, const size_t index, const Vec3i &value) = 0;
		virtual bool setVec4i(const byte coord_index, const size_t index, const Vec4i &value) = 0;
		virtual bool setVec1i(const byte coord_index, const size_t index, const Vec1i &value, const float relative_tolerance) = 0;
		virtual bool setVec2i(const byte coord_index, const size_t index, const Vec2i &value, const float relative_tolerance) = 0;
		virtual bool setVec3i(const byte coord_index, const size_t index, const Vec3i &value, const float relative_tolerance) = 0;
		virtual bool setVec4i(const byte coord_index, const size_t index, const Vec4i &value, const float relative_tolerance) = 0;
		virtual bool setVec1i(const size_t index, const Vec1i &value) = 0;
		virtual bool setVec2i(const size_t index, const Vec2i &value) = 0;
		virtual bool setVec3i(const size_t index, const Vec3i &value) = 0;
		virtual bool setVec4i(const size_t index, const Vec4i &value) = 0;
		virtual bool setVec1i(const size_t index, const Vec1i &value, const float relative_tolerance) = 0;
		virtual bool setVec2i(const size_t index, const Vec2i &value, const float relative_tolerance) = 0;
		virtual bool setVec3i(const size_t index, const Vec3i &value, const float relative_tolerance) = 0;
		virtual bool setVec4i(const size_t index, const Vec4i &value, const float relative_tolerance) = 0;

		// Vertex methods
		virtual IVertex *AddVertex(IPolygon *polygon = nullptr) = 0;
		virtual IVertex *AddVertex(const size_t before, IPolygon *polygon = nullptr) = 0;
		virtual bool DeleteVertex(const size_t index) = 0;
		virtual bool DeleteVertex(IVertex *vertex) = 0;
		virtual bool DeleteVertices() = 0;

		// Polygon methods
		virtual IPolygon *AddPolygon() = 0;
		virtual IPolygon *AddPolygon(const size_t before) = 0;
		virtual bool DeletePolygon(const size_t index) = 0;
		virtual bool DeletePolygon(IPolygon *value) = 0;
		virtual bool DeletePolygons() = 0;

		// Helper methods
		virtual bool Clear() = 0;

		// Rendering methods
		virtual bool RenderPoints() = 0; // Each polygon's vertex is rendered as point
		virtual bool RenderLines() = 0; // Each polygon's edge is rendered as line. First and last vertices are not connected
		virtual bool RenderWires() = 0; // Each polygon's edge is rendered as line. First and last vertices are connected
		virtual bool RenderPolygons() = 0; // Each polygon is rendered as triangle fan
	};
}