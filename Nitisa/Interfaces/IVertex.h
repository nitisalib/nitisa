// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Math/Vec2f.h"
#include "../Math/Vec3f.h"
#include "../Math/Vec4f.h"
#include "IReleasable.h"

namespace nitisa
{
	class IPolygon;
	class IVertexArray;

	class IVertex : public virtual IReleasable
	{
	protected:
		IVertex() = default;
		~IVertex() = default;
		IVertex(const IVertex &other) = delete;
		IVertex(IVertex &&other) = delete;
		IVertex &operator=(const IVertex &other) = delete;
		IVertex &operator=(IVertex &&other) = delete;
	protected:
		IVertexArray *m_pVA;
		size_t m_iVAIndex;
		IPolygon *m_pPolygon;
	public:
		IVertexArray* const &VA{ m_pVA }; // Parent vertex array
		size_t const &VAIndex{ m_iVAIndex }; // Index in parent vertex array
		IPolygon* const &Polygon{ m_pPolygon }; // Parent polygon

		// Getters of named properties. Whether property exist depends on vertex format of parent vertex array. If it doesn't, return nullptr
		virtual const Vec2f *getTextureCoords() const = 0;
		virtual const Vec2f *getBitmaskCoords() const = 0;
		virtual const Vec2f *getNormalCoords() const = 0;
		virtual const Vec2f *getBumpCoords() const = 0;
		virtual const Vec2f *getPosition2D() const = 0;
		virtual const Vec3f *getPosition3D() const = 0;
		virtual const Vec4f *getPosition4D() const = 0;
		virtual const Vec3f *getNormal() const = 0;
		virtual const Vec4f *getColor() const = 0;

		// Getters of named properties. Whether property exist depends on vertex format of parent vertex array. If it doesn't, return def value
		virtual Vec2f getTextureCoords(const Vec2f &def) const = 0;
		virtual Vec2f getBitmaskCoords(const Vec2f &def) const = 0;
		virtual Vec2f getNormalCoords(const Vec2f &def) const = 0;
		virtual Vec2f getBumpCoords(const Vec2f &def) const = 0;
		virtual Vec2f getPosition2D(const Vec2f &def) const = 0;
		virtual Vec3f getPosition3D(const Vec3f &def) const = 0;
		virtual Vec4f getPosition4D(const Vec4f &def) const = 0;
		virtual Vec3f getNormal(const Vec3f &def) const = 0;
		virtual Vec4f getColor(const Vec4f &def) const = 0;

		// Setters for named properties
		virtual bool setTextureCoords(const Vec2f &value) = 0;
		virtual bool setBitmaskCoords(const Vec2f &value) = 0;
		virtual bool setNormalCoords(const Vec2f &value) = 0;
		virtual bool setBumpCoords(const Vec2f &value) = 0;
		virtual bool setPosition2D(const Vec2f &value) = 0;
		virtual bool setPosition3D(const Vec3f &value) = 0;
		virtual bool setPosition4D(const Vec4f &value) = 0;
		virtual bool setNormal(const Vec3f &value) = 0;
		virtual bool setColor(const Vec4f &value) = 0;
		virtual bool setTextureCoords(const Vec2f &value, const float relative_tolerance) = 0;
		virtual bool setBitmaskCoords(const Vec2f &value, const float relative_tolerance) = 0;
		virtual bool setNormalCoords(const Vec2f &value, const float relative_tolerance) = 0;
		virtual bool setBumpCoords(const Vec2f &value, const float relative_tolerance) = 0;
		virtual bool setPosition2D(const Vec2f &value, const float relative_tolerance) = 0;
		virtual bool setPosition3D(const Vec3f &value, const float relative_tolerance) = 0;
		virtual bool setPosition4D(const Vec4f &value, const float relative_tolerance) = 0;
		virtual bool setNormal(const Vec3f &value, const float relative_tolerance) = 0;
		virtual bool setColor(const Vec4f &value, const float relative_tolerance) = 0;

		// Setters for names properties. No result of setting is available
		virtual IVertex *putTextureCoords(const Vec2f &value) = 0;
		virtual IVertex *putBitmaskCoords(const Vec2f &value) = 0;
		virtual IVertex *putNormalCoords(const Vec2f &value) = 0;
		virtual IVertex *putBumpCoords(const Vec2f &value) = 0;
		virtual IVertex *putPosition2D(const Vec2f &value) = 0;
		virtual IVertex *putPosition3D(const Vec3f &value) = 0;
		virtual IVertex *putPosition4D(const Vec4f &value) = 0;
		virtual IVertex *putNormal(const Vec3f &value) = 0;
		virtual IVertex *putColor(const Vec4f &value) = 0;
		virtual IVertex *putTextureCoords(const Vec2f &value, const float relative_tolerance) = 0;
		virtual IVertex *putBitmaskCoords(const Vec2f &value, const float relative_tolerance) = 0;
		virtual IVertex *putNormalCoords(const Vec2f &value, const float relative_tolerance) = 0;
		virtual IVertex *putBumpCoords(const Vec2f &value, const float relative_tolerance) = 0;
		virtual IVertex *putPosition2D(const Vec2f &value, const float relative_tolerance) = 0;
		virtual IVertex *putPosition3D(const Vec3f &value, const float relative_tolerance) = 0;
		virtual IVertex *putPosition4D(const Vec4f &value, const float relative_tolerance) = 0;
		virtual IVertex *putNormal(const Vec3f &value, const float relative_tolerance) = 0;
		virtual IVertex *putColor(const Vec4f &value, const float relative_tolerance) = 0;

		// Cloning methods
		virtual bool CloneTo(IVertex *target) const = 0;
		virtual bool CloneFrom(IVertex *source) = 0;
		virtual bool CloneFrom(IVertex *source, const float k) = 0;
		virtual bool CloneFrom(IVertex *source1, IVertex *source2, const float k1, const float k2) = 0;
	};
}