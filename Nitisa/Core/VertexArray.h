// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IPolygon.h"
#include "../Interfaces/IVertex.h"
#include "../Interfaces/IVertexArray.h"
#include "../Math/Plane.h"
#include "../Math/Vec1i.h"
#include "../Math/Vec1f.h"
#include "../Math/Vec2i.h"
#include "../Math/Vec2f.h"
#include "../Math/Vec3i.h"
#include "../Math/Vec3f.h"
#include "../Math/Vec4i.h"
#include "../Math/Vec4f.h"
#include "Aliases.h"
#include "Releasable.h"
#include "VertexFormat.h"
#include <vector>

namespace nitisa
{
	class CVertexArray :public virtual IVertexArray, public CReleasable
	{
	private:
		class CPolygon;

		class CVertex :public virtual IVertex, public CReleasable
		{
			friend CPolygon;
			friend CVertexArray;
		private:
			CVertexArray *m_pVertexArray;
		protected:
			void BeforeRelease() override;
		public:
			// IVertex getters
			const Vec2f *getTextureCoords() const override;
			const Vec2f *getBitmaskCoords() const override;
			const Vec2f *getNormalCoords() const override;
			const Vec2f *getBumpCoords() const override;
			const Vec2f *getPosition2D() const override;
			const Vec3f *getPosition3D() const override;
			const Vec4f *getPosition4D() const override;
			const Vec3f *getNormal() const override;
			const Vec4f *getColor() const override;

			Vec2f getTextureCoords(const Vec2f &def) const override;
			Vec2f getBitmaskCoords(const Vec2f &def) const override;
			Vec2f getNormalCoords(const Vec2f &def) const override;
			Vec2f getBumpCoords(const Vec2f &def) const override;
			Vec2f getPosition2D(const Vec2f &def) const override;
			Vec3f getPosition3D(const Vec3f &def) const override;
			Vec4f getPosition4D(const Vec4f &def) const override;
			Vec3f getNormal(const Vec3f &def) const override;
			Vec4f getColor(const Vec4f &def) const override;

			// IVertex setters
			bool setTextureCoords(const Vec2f &value) override;
			bool setBitmaskCoords(const Vec2f &value) override;
			bool setNormalCoords(const Vec2f &value) override;
			bool setBumpCoords(const Vec2f &value) override;
			bool setPosition2D(const Vec2f &value) override;
			bool setPosition3D(const Vec3f &value) override;
			bool setPosition4D(const Vec4f &value) override;
			bool setNormal(const Vec3f &value) override;
			bool setColor(const Vec4f &value) override;
			bool setTextureCoords(const Vec2f &value, const float relative_tolerance) override;
			bool setBitmaskCoords(const Vec2f &value, const float relative_tolerance) override;
			bool setNormalCoords(const Vec2f &value, const float relative_tolerance) override;
			bool setBumpCoords(const Vec2f &value, const float relative_tolerance) override;
			bool setPosition2D(const Vec2f &value, const float relative_tolerance) override;
			bool setPosition3D(const Vec3f &value, const float relative_tolerance) override;
			bool setPosition4D(const Vec4f &value, const float relative_tolerance) override;
			bool setNormal(const Vec3f &value, const float relative_tolerance) override;
			bool setColor(const Vec4f &value, const float relative_tolerance) override;

			// IVertex putters
			IVertex *putTextureCoords(const Vec2f &value) override;
			IVertex *putBitmaskCoords(const Vec2f &value) override;
			IVertex *putNormalCoords(const Vec2f &value) override;
			IVertex *putBumpCoords(const Vec2f &value) override;
			IVertex *putPosition2D(const Vec2f &value) override;
			IVertex *putPosition3D(const Vec3f &value) override;
			IVertex *putPosition4D(const Vec4f &value) override;
			IVertex *putNormal(const Vec3f &value) override;
			IVertex *putColor(const Vec4f &value) override;
			IVertex *putTextureCoords(const Vec2f &value, const float relative_tolerance) override;
			IVertex *putBitmaskCoords(const Vec2f &value, const float relative_tolerance) override;
			IVertex *putNormalCoords(const Vec2f &value, const float relative_tolerance) override;
			IVertex *putBumpCoords(const Vec2f &value, const float relative_tolerance) override;
			IVertex *putPosition2D(const Vec2f &value, const float relative_tolerance) override;
			IVertex *putPosition3D(const Vec3f &value, const float relative_tolerance) override;
			IVertex *putPosition4D(const Vec4f &value, const float relative_tolerance) override;
			IVertex *putNormal(const Vec3f &value, const float relative_tolerance) override;
			IVertex *putColor(const Vec4f &value, const float relative_tolerance) override;

			// IVertex helpers
			bool CloneTo(IVertex *target) const override;
			bool CloneFrom(IVertex *source) override;
			bool CloneFrom(IVertex *source, const float k) override;
			bool CloneFrom(IVertex *source1, IVertex *source2, const float k1, const float k2) override;

			CVertex(CVertexArray *vertex_array, const size_t index, IPolygon *polygon);
		};

		class CPolygon : public virtual IPolygon, public CReleasable
		{
			friend CVertexArray;
		private:
			CVertexArray *m_pVertexArray;
			std::vector<IVertex*> m_aVertices;
			Plane m_sPlane;
			bool m_bPlaneValid;
		protected:
			void BeforeRelease() override;
		public:
			// IPolygon getters
			size_t getVertexCount() const override;
			IVertex *getVertex(const size_t index) override;
			const Plane &getPlane() override;
			float getArea() const override;

			// IPolygon setters
			bool setVertexCount(const size_t value) override;
			bool setVertices(std::vector<IVertex*> &vertices) override;

			// IPolygon vertices
			IVertex *AddVertex() override;
			bool AddVertex(IVertex *vertex) override;
			IVertex *InsertVertex(const size_t before) override;
			bool InsertVertex(IVertex *vertex, const size_t before) override;
			bool DetachVertex(const size_t index) override;
			bool DetachVertex(IVertex *vertex) override;
			bool DeleteVertex(const size_t index) override;
			bool DeleteVertex(IVertex *vertex) override;
			bool DeleteVertices() override;

			// IPolygon helpers
			bool Flip() override;
			bool Split(const Plane &plane, IPolygon **front, IPolygon **back, const float tolerance) const override;
			void CutBack(const Plane &plane, const float tolerance) override;
			void CutBack(const Plane &plane, IPolygon **back, const float tolerance) override;
			void CutFront(const Plane &plane, const float tolerance) override;
			void CutFront(const Plane &plane, IPolygon **front, const float tolerance) override;

			CPolygon(CVertexArray *vertex_array, const size_t index);

			CPolygon(const CPolygon&) = delete;
			CPolygon(CPolygon&&) = delete;
			CPolygon &operator=(const CPolygon&) = delete;
			CPolygon &operator=(CPolygon&&) = delete;
		};
	private:
		void EraseVertex(const size_t index);
		void ResizeVertices(const size_t count);
		void ResizePolygons(const size_t count);
		void ResizePolygons(const size_t count, const size_t size);
	protected:
		std::vector<CVertex*> m_aVertices;
		std::vector<CPolygon*> m_aPolygons;
		std::vector<Vec1f> m_aVec1f[8];
		std::vector<Vec2f> m_aVec2f[8];
		std::vector<Vec3f> m_aVec3f[8];
		std::vector<Vec4f> m_aVec4f[8];
		std::vector<Vec1i> m_aVec1i[8];
		std::vector<Vec2i> m_aVec2i[8];
		std::vector<Vec3i> m_aVec3i[8];
		std::vector<Vec4i> m_aVec4i[8];
		int m_iLastRenderedPrimitives;

		static const int PRIMITIVE_NONE{ 0 };
		static const int PRIMITIVE_POINT{ 1 };
		static const int PRIMITIVE_LINE{ 2 };
		static const int PRIMITIVE_WIRE{ 3 };
		static const int PRIMITIVE_POLYGON{ 4 };

		CVertexArray(const VertexFormat &format);
		CVertexArray(const VertexFormat &format, const size_t vertex_count);
		CVertexArray(const VertexFormat &format, const size_t polygon_count, const size_t polygon_size);

		CVertexArray(const CVertexArray&) = delete;
		CVertexArray(CVertexArray&&) = delete;
		CVertexArray &operator=(const CVertexArray&) = delete;
		CVertexArray &operator=(CVertexArray&&) = delete;

		void BeforeRelease() override;

		static bool CheckFormat(const VertexFormat &format);
	public:
		// IVertexArray getters
		size_t getVertexCount() const override;
		IVertex *getVertex(const size_t index) override;
		size_t getPolygonCount() const override;
		IPolygon *getPolygon(const size_t index) override;
		const Vec1f *getVec1f(const byte coord_index, const size_t index) const override;
		const Vec2f *getVec2f(const byte coord_index, const size_t index) const override;
		const Vec3f *getVec3f(const byte coord_index, const size_t index) const override;
		const Vec4f *getVec4f(const byte coord_index, const size_t index) const override;
		const Vec1i *getVec1i(const byte coord_index, const size_t index) const override;
		const Vec2i *getVec2i(const byte coord_index, const size_t index) const override;
		const Vec3i *getVec3i(const byte coord_index, const size_t index) const override;
		const Vec4i *getVec4i(const byte coord_index, const size_t index) const override;
		const Vec1f *getVec1fArray(const byte coord_index) const override;
		const Vec2f *getVec2fArray(const byte coord_index) const override;
		const Vec3f *getVec3fArray(const byte coord_index) const override;
		const Vec4f *getVec4fArray(const byte coord_index) const override;
		const Vec1i *getVec1iArray(const byte coord_index) const override;
		const Vec2i *getVec2iArray(const byte coord_index) const override;
		const Vec3i *getVec3iArray(const byte coord_index) const override;
		const Vec4i *getVec4iArray(const byte coord_index) const override;

		// IVertexArray setters
		bool setVertexCount(const size_t value) override;
		bool setPolygonCount(const size_t value) override;
		bool setPolygonCount(const size_t count, const size_t size) override;
		bool setVec1f(const byte coord_index, const size_t index, const Vec1f &value) override;
		bool setVec2f(const byte coord_index, const size_t index, const Vec2f &value) override;
		bool setVec3f(const byte coord_index, const size_t index, const Vec3f &value) override;
		bool setVec4f(const byte coord_index, const size_t index, const Vec4f &value) override;
		bool setVec1f(const byte coord_index, const size_t index, const Vec1f &value, const float relative_tolerance) override;
		bool setVec2f(const byte coord_index, const size_t index, const Vec2f &value, const float relative_tolerance) override;
		bool setVec3f(const byte coord_index, const size_t index, const Vec3f &value, const float relative_tolerance) override;
		bool setVec4f(const byte coord_index, const size_t index, const Vec4f &value, const float relative_tolerance) override;
		bool setVec1f(const size_t index, const Vec1f &value) override;
		bool setVec2f(const size_t index, const Vec2f &value) override;
		bool setVec3f(const size_t index, const Vec3f &value) override;
		bool setVec4f(const size_t index, const Vec4f &value) override;
		bool setVec1f(const size_t index, const Vec1f &value, const float relative_tolerance) override;
		bool setVec2f(const size_t index, const Vec2f &value, const float relative_tolerance) override;
		bool setVec3f(const size_t index, const Vec3f &value, const float relative_tolerance) override;
		bool setVec4f(const size_t index, const Vec4f &value, const float relative_tolerance) override;
		bool setVec1i(const byte coord_index, const size_t index, const Vec1i &value) override;
		bool setVec2i(const byte coord_index, const size_t index, const Vec2i &value) override;
		bool setVec3i(const byte coord_index, const size_t index, const Vec3i &value) override;
		bool setVec4i(const byte coord_index, const size_t index, const Vec4i &value) override;
		bool setVec1i(const byte coord_index, const size_t index, const Vec1i &value, const float relative_tolerance) override;
		bool setVec2i(const byte coord_index, const size_t index, const Vec2i &value, const float relative_tolerance) override;
		bool setVec3i(const byte coord_index, const size_t index, const Vec3i &value, const float relative_tolerance) override;
		bool setVec4i(const byte coord_index, const size_t index, const Vec4i &value, const float relative_tolerance) override;
		bool setVec1i(const size_t index, const Vec1i &value) override;
		bool setVec2i(const size_t index, const Vec2i &value) override;
		bool setVec3i(const size_t index, const Vec3i &value) override;
		bool setVec4i(const size_t index, const Vec4i &value) override;
		bool setVec1i(const size_t index, const Vec1i &value, const float relative_tolerance) override;
		bool setVec2i(const size_t index, const Vec2i &value, const float relative_tolerance) override;
		bool setVec3i(const size_t index, const Vec3i &value, const float relative_tolerance) override;
		bool setVec4i(const size_t index, const Vec4i &value, const float relative_tolerance) override;

		// IVertexArray vertices
		IVertex *AddVertex(IPolygon *polygon = nullptr) override;
		IVertex *AddVertex(const size_t before, IPolygon *polygon = nullptr) override;
		bool DeleteVertex(const size_t index) override;
		bool DeleteVertex(IVertex *vertex) override;
		bool DeleteVertices() override;

		// IVertexArray polygons
		IPolygon *AddPolygon() override;
		IPolygon *AddPolygon(const size_t before) override;
		bool DeletePolygon(const size_t index) override;
		bool DeletePolygon(IPolygon *value) override;
		bool DeletePolygons() override;

		// IVertexArray helpers
		bool Clear() override;
	};
}