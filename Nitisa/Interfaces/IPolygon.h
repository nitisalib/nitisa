// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Math/Plane.h"
#include "IReleasable.h"
#include <vector>

namespace nitisa
{
	class IVertex;
	class IVertexArray;

	class IPolygon :public virtual IReleasable
	{
	protected:
		IPolygon() = default;
		~IPolygon() = default;
		IPolygon(const IPolygon &other) = delete;
		IPolygon(IPolygon &&other) = delete;
		IPolygon &operator=(const IPolygon &other) = delete;
		IPolygon &operator=(IPolygon &&other) = delete;
	protected:
		IVertexArray *m_pVA;
		size_t m_iVAIndex;
	public:
		IVertexArray* const &VA{ m_pVA }; // Parent vertex array
		size_t const &VAIndex{ m_iVAIndex }; // Index in vertex array

		virtual size_t getVertexCount() const = 0; // Return count of vertices
		virtual IVertex *getVertex(const size_t index) = 0; // Return vertex by index
		virtual const Plane &getPlane() = 0; // Return plane
		virtual float getArea() const = 0; // Return area

		virtual bool setVertexCount(const size_t value) = 0; // Allocate new vertex count
		virtual bool setVertices(std::vector<IVertex*> &vertices) = 0; // Set vertices

		virtual IVertex *AddVertex() = 0; // Create vertex
		virtual bool AddVertex(IVertex *vertex) = 0; // Add vertex
		virtual IVertex *InsertVertex(const size_t before) = 0; // Create vertex before specified index
		virtual bool InsertVertex(IVertex *vertex, const size_t before) = 0; // Insert vertex before specified index
		virtual bool DetachVertex(const size_t index) = 0; // Detach vertex by index
		virtual bool DetachVertex(IVertex *vertex) = 0; // Detach vertex
		virtual bool DeleteVertex(const size_t index) = 0; // Delete vertex by index
		virtual bool DeleteVertex(IVertex *vertex) = 0; // Delete vertex
		virtual bool DeleteVertices() = 0; // Delete all vertices

		virtual bool Flip() = 0; // Flip
		virtual bool Split(const Plane &plane, IPolygon **front, IPolygon **back, const float tolerance) const = 0; // Split by plane
		virtual void CutBack(const Plane &plane, const float tolerance) = 0; // Cut back part
		virtual void CutBack(const Plane &plane, IPolygon **back, const float tolerance) = 0; // Cut back part
		virtual void CutFront(const Plane &plane, const float tolerance) = 0; // Cut front part
		virtual void CutFront(const Plane &plane, IPolygon **front, const float tolerance) = 0; // Cut front part
	};
}