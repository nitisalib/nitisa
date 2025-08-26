// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	bool DrawBlockShadow(IRenderer *renderer, const RectF &rect, const RectF &radiuses, const Color &color, const PointF &shift, const int radius)
	{
		if (rect.is_valid() && !rect.is_zero() && !radiuses.has_negative() && radius >= 1 && color.A > 0)
		{
			ITexture *shadow{ renderer->CreateTexture(ntl::Round<int>(rect.width()) + 2 * radius, ntl::Round<int>(rect.height()) + 2 * radius, 1, TextureFormat::RGBA, true) };
			if (shadow)
			{
				float f_radius{ (float)radius };
				{
					CStoreTarget s_target{ renderer };
					renderer
						->ActivateTarget(shadow)
						->Clear(Color{ 0, 0, 0, 0 });
					if (radiuses.has_positive())
					{
						BlockColors colors{
							Color{ 0, 0, 0, 0 },
							Color{ 0, 0, 0, 0 },
							Color{ 0, 0, 0, 0 },
							Color{ 0, 0, 0, 0 },
							color,
							Color{ 0, 0, 0, 0 }
						};
						renderer->DrawBlock(RectF{ f_radius, f_radius, rect.width() + f_radius, rect.height() + f_radius }, RectF{ 0, 0, 0, 0 }, radiuses, colors);
					}
					else
						renderer->DrawRectangle(RectF{ f_radius, f_radius, rect.width() + f_radius, rect.height() + f_radius }, color);
					renderer->BlurImage(shadow, radius, BlurType::Gaussian);
				}
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(shift.X - f_radius + rect.Left, shift.Y - f_radius + rect.Top, 0))
					->DrawImage(shadow, 1);
				shadow->Release();
				return true;
			}
		}
		return false;
	}

	bool DrawSimpleBackground(
		IRenderer *renderer,
		const RectF &rect,
		const RectF &borders,
		const RectF &radiuses,
		const BorderColor &border_colors,
		const Color &background_color,
		Gradient &background_gradient)
	{
		bool result{ false };
		if (rect.is_valid() && !rect.is_zero())
		{
			if (borders.has_positive() || radiuses.has_positive())
			{
				Block b{ rect, borders, radiuses, PointLocation::Inside };
				if (border_colors.Left.A > 0 || border_colors.Top.A > 0 || border_colors.Right.A > 0 || border_colors.Bottom.A > 0 || background_color.A > 0)
				{
					renderer->DrawBlock(rect, borders, radiuses, BlockColors{ border_colors.Left, border_colors.Top, border_colors.Right, border_colors.Bottom, background_color, Color{ 0, 0, 0, 0 } });
					result = true;
				}
				if (background_gradient.getPointCount() >= 2)
				{
					CStoreBlock s_block{ renderer };
					renderer
						->ActivateBlock(&b)
						->DrawGradient(b.Rect, background_gradient);
					result = true;
				}
			}
			else
			{
				if (background_gradient.getPointCount() >= 2)
				{
					renderer->DrawGradient(rect, background_gradient);
					result = true;
				}
				else if (background_color.A > 0)
				{
					renderer->DrawRectangle(rect, background_color);
					result = true;
				}
			}
		}
		return result;
	}

	bool DrawDoubleBackground(
		IRenderer *renderer,
		const RectF &rect,
		const RectF &outer_borders,
		const RectF &inner_borders,
		const RectF &radiuses,
		const BorderColor &outer_border_colors,
		const BorderColor &inner_border_colors,
		const Color &background_color,
		Gradient &background_gradient)
	{
		bool has_outer{ outer_borders.has_positive() };
		bool has_inner{ inner_borders.has_positive() };
		if (has_outer && has_inner)
		{
			bool result{ false };
			if (rect.is_valid() && !rect.is_zero())
			{
				// Outer border
				Block b{ rect, AddElements(outer_borders, inner_borders), radiuses, PointLocation::Inside };
				if (outer_border_colors.Left.A > 0 || outer_border_colors.Top.A > 0 || outer_border_colors.Right.A > 0 || outer_border_colors.Bottom.A > 0)
				{
					renderer->DrawBlock(b.Rect, b.Border, b.Radius, BlockColors{ outer_border_colors.Left, outer_border_colors.Top, outer_border_colors.Right,
						outer_border_colors.Bottom, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } });
					result = true;
				}
				// Inner border and background color
				b.Border = inner_borders;
				b.Rect.Left += outer_borders.Left;
				b.Rect.Top += outer_borders.Top;
				b.Rect.Right -= outer_borders.Right;
				b.Rect.Bottom -= outer_borders.Bottom;
				if (b.Rect.is_valid() && !b.Rect.is_zero() && (inner_border_colors.Left.A > 0 || inner_border_colors.Top.A > 0 || inner_border_colors.Right.A > 0 ||
					inner_border_colors.Bottom.A > 0 || background_color.A > 0))
				{
					renderer->DrawBlock(b.Rect, b.Border, b.Radius, BlockColors{ inner_border_colors.Left, inner_border_colors.Top, inner_border_colors.Right,
						inner_border_colors.Bottom, background_color });
					result = true;
				}
				// Background gradient
				if (background_gradient.getPointCount() >= 2)
				{
					b.Rect = rect;
					b.Border = AddElements(outer_borders, inner_borders);
					CStoreBlock s_block{ renderer };
					renderer
						->ActivateBlock(&b)
						->DrawGradient(rect, background_gradient);
					result = true;
				}
			}
			return result;
		}
		return DrawSimpleBackground(renderer, rect, has_outer ? outer_borders : inner_borders, radiuses, has_outer ? outer_border_colors : inner_border_colors, background_color, background_gradient);
	}

	bool DrawTripleBackground(
		IRenderer *renderer,
		const RectF &rect,
		const RectF &outer_borders,
		const RectF &middle_borders,
		const RectF &inner_borders,
		const RectF &radiuses,
		const BorderColor &outer_border_colors,
		const BorderColor &middle_border_colors,
		const BorderColor &inner_border_colors,
		const Color &background_color,
		Gradient &background_gradient)
	{
		bool has_outer{ outer_borders.has_positive() };
		bool has_middle{ middle_borders.has_positive() };
		bool has_inner{ inner_borders.has_positive() };
		if (!has_outer || !has_middle || !has_inner)
		{
			if (!has_outer)
				return DrawDoubleBackground(renderer, rect, middle_borders, inner_borders, radiuses, middle_border_colors, inner_border_colors, background_color, background_gradient);
			if (!has_middle)
				return DrawDoubleBackground(renderer, rect, outer_borders, inner_borders, radiuses, outer_border_colors, inner_border_colors, background_color, background_gradient);
			return DrawDoubleBackground(renderer, rect, outer_borders, middle_borders, radiuses, outer_border_colors, middle_border_colors, background_color, background_gradient);
		}
		if (rect.is_valid() && !rect.is_zero())
		{
			bool result{ false };
			Block b{ rect, AddElements(outer_borders, middle_borders, inner_borders), radiuses, PointLocation::Inside };
			BlockColors colors{ outer_border_colors.Left, outer_border_colors.Top, outer_border_colors.Right, outer_border_colors.Bottom, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
			if (outer_border_colors.Left.A > 0 || outer_border_colors.Top.A > 0 || outer_border_colors.Right.A > 0 || outer_border_colors.Bottom.A > 0)
			{
				renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
				result = true;
			}

			b.Border = AddElements(middle_borders, inner_borders);
			b.Rect.Left += outer_borders.Left;
			b.Rect.Top += outer_borders.Top;
			b.Rect.Right -= outer_borders.Right;
			b.Rect.Bottom -= outer_borders.Bottom;
			if (b.Rect.is_valid() && !b.Rect.is_zero() && (middle_border_colors.Left.A > 0 || middle_border_colors.Top.A > 0 || middle_border_colors.Right.A > 0 ||
				middle_border_colors.Bottom.A > 0))
			{
				colors[0] = middle_border_colors.Left;
				colors[1] = middle_border_colors.Top;
				colors[2] = middle_border_colors.Right;
				colors[3] = middle_border_colors.Bottom;
				renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
				result = true;
			}

			b.Border = inner_borders;
			b.Rect.Left += middle_borders.Left;
			b.Rect.Top += middle_borders.Top;
			b.Rect.Right -= middle_borders.Right;
			b.Rect.Bottom -= middle_borders.Bottom;
			if (b.Rect.is_valid() && !b.Rect.is_zero() && (inner_border_colors.Left.A > 0 || inner_border_colors.Top.A > 0 || inner_border_colors.Right.A > 0 ||
				inner_border_colors.Bottom.A > 0 || background_color.A > 0))
			{
				colors[0] = inner_border_colors.Left;
				colors[1] = inner_border_colors.Top;
				colors[2] = inner_border_colors.Right;
				colors[3] = inner_border_colors.Bottom;
				colors[4] = background_color;
				renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
				result = true;
			}

			if (background_gradient.getPointCount() >= 2)
			{
				b.Rect = rect;
				b.Border = AddElements(outer_borders, middle_borders, inner_borders);
				CStoreBlock s_block{ renderer };
				renderer
					->ActivateBlock(&b)
					->DrawGradient(rect, background_gradient);
				result = true;
			}
			return result;
		}
		return false;
	}

	bool DrawTripleSharpBackground(
		IRenderer *renderer,
		const RectF &rect,
		const RectF &outer_borders,
		const RectF &middle_borders,
		const RectF &inner_borders,
		const RectF &radiuses,
		const BorderColor &outer_border_colors,
		const BorderColor &middle_border_colors,
		const BorderColor &inner_border_colors,
		const Color &background_color,
		Gradient &background_gradient)
	{
		bool has_outer{ outer_borders.has_positive() };
		bool has_middle{ middle_borders.has_positive() };
		bool has_inner{ inner_borders.has_positive() };
		if (!has_outer || !has_middle || !has_inner)
		{
			if (!has_outer)
				return DrawDoubleBackground(renderer, rect, middle_borders, inner_borders, radiuses, middle_border_colors, inner_border_colors, background_color, background_gradient);
			if (!has_middle)
				return DrawDoubleBackground(renderer, rect, outer_borders, inner_borders, radiuses, outer_border_colors, inner_border_colors, background_color, background_gradient);
			return DrawDoubleBackground(renderer, rect, outer_borders, middle_borders, radiuses, outer_border_colors, middle_border_colors, background_color, background_gradient);
		}
		if (rect.is_valid() && !rect.is_zero())
		{
			bool result{ false };
			Block clip_b{ rect, outer_borders, radiuses, PointLocation::Inside };
			bool clip_required{ radiuses.has_positive() };
			Block b{ rect, AddElements(outer_borders, middle_borders, inner_borders), radiuses, PointLocation::Inside };
			BlockColors colors{ outer_border_colors.Left, outer_border_colors.Top, outer_border_colors.Right, outer_border_colors.Bottom, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };

			if (outer_border_colors.Left.A > 0 || outer_border_colors.Top.A > 0 || outer_border_colors.Right.A > 0 || outer_border_colors.Bottom.A > 0)
			{
				renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
				result = true;
			}

			ITexture *clip{ nullptr };
			b.Border = AddElements(middle_borders, inner_borders);
			b.Radius = RectF{ 0, 0, 0, 0 };
			b.Rect.Left += outer_borders.Left;
			b.Rect.Top += outer_borders.Top;
			b.Rect.Right -= outer_borders.Right;
			b.Rect.Bottom -= outer_borders.Bottom;
			if (b.Rect.is_valid() && !b.Rect.is_zero() && (middle_border_colors.Left.A > 0 || middle_border_colors.Top.A > 0 || middle_border_colors.Right.A > 0 ||
				middle_border_colors.Bottom.A > 0))
			{
				colors[0] = middle_border_colors.Left;
				colors[1] = middle_border_colors.Top;
				colors[2] = middle_border_colors.Right;
				colors[3] = middle_border_colors.Bottom;
				if (clip_required)
				{
					clip = renderer->CreateTexture(ntl::Round<int>(rect.width()), ntl::Round<int>(rect.height()), 1, TextureFormat::RGBA, true);
					if (clip)
					{
						{
							CStoreTarget s_target{ renderer };
							renderer->ActivateTarget(clip);
							renderer->Clear(Color{ 0, 0, 0, 0 });
							renderer->DrawBlock(RectF{ b.Rect.Left - rect.Left, b.Rect.Top - rect.Top, b.Rect.Right - rect.Left, b.Rect.Bottom - rect.Top }, b.Border, b.Radius, colors);
						}
						CStoreBlock s_block{ renderer };
						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer
							->ActivateBlock(&clip_b)
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(rect.Left, rect.Top, 0))
							->DrawImage(clip, 1);
						result = true;
					}
				}
				else
				{
					renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
					result = true;
				}
			}

			b.Border = inner_borders;
			b.Rect.Left += middle_borders.Left;
			b.Rect.Top += middle_borders.Top;
			b.Rect.Right -= middle_borders.Right;
			b.Rect.Bottom -= middle_borders.Bottom;
			if (b.Rect.is_valid() && !b.Rect.is_zero() && (inner_border_colors.Left.A > 0 || inner_border_colors.Top.A > 0 || inner_border_colors.Right.A > 0 ||
				inner_border_colors.Bottom.A > 0 || background_color.A > 0))
			{
				colors[0] = inner_border_colors.Left;
				colors[1] = inner_border_colors.Top;
				colors[2] = inner_border_colors.Right;
				colors[3] = inner_border_colors.Bottom;
				colors[4] = background_color;
				if (clip_required)
				{
					if (clip)
					{
						{
							CStoreTarget s_target{ renderer };
							renderer->ActivateTarget(clip);
							renderer->Clear(Color{ 0, 0, 0, 0 });
							renderer->DrawBlock(RectF{ b.Rect.Left - rect.Left, b.Rect.Top - rect.Top, b.Rect.Right - rect.Left, b.Rect.Bottom - rect.Top }, b.Border, b.Radius, colors);
						}
						CStoreBlock s_block{ renderer };
						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer
							->ActivateBlock(&clip_b)
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(rect.Left, rect.Top, 0))
							->DrawImage(clip, 1);
						clip->Release();
						result = true;
					}
				}
				else
				{
					renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
					result = true;
				}
			}

			if (background_gradient.getPointCount() >= 2)
			{
				b.Rect = rect;
				b.Border = AddElements(outer_borders, middle_borders, inner_borders);
				b.Radius = radiuses;
				CStoreBlock s_block{ renderer };
				renderer
					->ActivateBlock(&b)
					->DrawGradient(rect, background_gradient);
				result = true;
			}
			return result;
		}
		return false;
	}

	bool DrawTextShadow(
		IRenderer *renderer,
		IPlatformFont *pf,
		const float distance,
		const Mat4f &matrix,
		const RectF &client,
		const PointF &position,
		const String &text,
		const Color &color,
		const PointF &shift,
		const int radius)
	{
		if (!text.empty() && color.A > 0 && client.is_valid() && !client.is_zero())
		{
			float f_radius{ (float)radius };
			PointF size{ pf->getStringSize(text, distance) };
			PointF shadow_position{ position.X + shift.X, position.Y + shift.Y }; // Where to draw text to avoid using shadow shift
			RectF shadow_rect{ shadow_position.X - f_radius, shadow_position.Y - f_radius, shadow_position.X + size.X + f_radius, shadow_position.Y + size.Y + f_radius }; // Entire shadow rectangle
			RectF client_ext{ client.Left - f_radius, client.Top - f_radius, client.Right + f_radius, client.Bottom + f_radius }; // Client rectangle extended by shadow radius
			RectF min_shadow_rect{ shadow_rect * client_ext }; // Minimal size shadow rectangle
			if (!min_shadow_rect.is_zero())
			{
				PointF text_position{ f_radius - min_shadow_rect.Left + shadow_rect.Left, f_radius - min_shadow_rect.Top + shadow_rect.Top }; // Text position in minimal shadow rectangle
				PointF shadow_image_position{ shadow_position.X + min_shadow_rect.Left - shadow_rect.Left - f_radius, shadow_position.Y + min_shadow_rect.Top - shadow_rect.Top - f_radius }; // Minimal shadow rectangle position on control
				ITexture *shadow{ renderer->CreateTexture(ntl::Round<int>(min_shadow_rect.width()), ntl::Round<int>(min_shadow_rect.height()), 1, TextureFormat::RGBA, true) };
				if (shadow)
				{
					CStorePrimitiveMatrix s_matrix{ renderer };
					{
						CStoreTarget s_target{ renderer };
						renderer
							->ActivateTarget(shadow)
							->Clear(Color{ 0, 0, 0, 0 })
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(text_position.X, text_position.Y, 0))
							->DrawText(text, pf, distance, color)
							->BlurImage(shadow, radius, BlurType::Gaussian);
					}
					renderer
						->ActivatePrimitiveMatrix(matrix * ntl::Mat4Translate<float>(shadow_image_position.X, shadow_image_position.Y, 0))
						->DrawImage(shadow, 1);
					shadow->Release();
					return true;
				}
			}
		}
		return false;
	}

	bool DrawFrame(
		IRenderer *renderer,
		const RectF &rect,
		const RectF &outer_borders,
		const RectF &middle_borders,
		const RectF &inner_borders,
		const RectF &radiuses,
		const BorderColor &outer_border_colors,
		const BorderColor &middle_border_colors,
		const BorderColor &inner_border_colors,
		Gradient &middle_gradient,
		const Color &background_color,
		Gradient &background_gradient)
	{
		if (!middle_borders.has_positive() || middle_gradient.getPointCount() < 2)
			return DrawTripleSharpBackground(renderer,rect, outer_borders, middle_borders, inner_borders, radiuses, outer_border_colors, middle_border_colors, inner_border_colors,
				background_color, background_gradient);
		if (rect.is_valid() && !rect.is_zero())
		{
			Block clip_b{ rect, outer_borders, radiuses, PointLocation::Inside };
			bool clip_required{ radiuses.has_positive() };
			Block b{ rect, AddElements(outer_borders, middle_borders, inner_borders), radiuses, PointLocation::Inside };
			BlockColors colors{ outer_border_colors.Left, outer_border_colors.Top, outer_border_colors.Right, outer_border_colors.Bottom, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };

			if (outer_border_colors.Left.A > 0 || outer_border_colors.Top.A > 0 || outer_border_colors.Right.A > 0 || outer_border_colors.Bottom.A > 0)
				renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);

			{
				CStoreBlock s_block{ renderer };
				renderer
					->ActivateBlock(&clip_b)
					->DrawGradient(rect, middle_gradient);
			}

			b.Border = inner_borders;
			b.Radius = RectF{ 0, 0, 0, 0 };
			b.Rect.Left += outer_borders.Left + middle_borders.Left;
			b.Rect.Top += outer_borders.Top + middle_borders.Top;
			b.Rect.Right -= outer_borders.Right + middle_borders.Right;
			b.Rect.Bottom -= outer_borders.Bottom + middle_borders.Bottom;
			if (b.Rect.is_valid() && !b.Rect.is_zero() && (inner_border_colors.Left.A > 0 || inner_border_colors.Top.A > 0 || inner_border_colors.Right.A > 0 ||
				inner_border_colors.Bottom.A > 0 || background_color.A > 0))
			{
				colors[0] = inner_border_colors.Left;
				colors[1] = inner_border_colors.Top;
				colors[2] = inner_border_colors.Right;
				colors[3] = inner_border_colors.Bottom;
				colors[4] = background_color;
				if (clip_required)
				{
					ITexture *clip{ renderer->CreateTexture(ntl::Round<int>(rect.width()), ntl::Round<int>(rect.height()), 1, TextureFormat::RGBA, true) };
					if (clip)
					{
						{
							CStoreTarget s_target{ renderer };
							renderer->ActivateTarget(clip);
							renderer->Clear(Color{ 0, 0, 0, 0 });
							renderer->DrawBlock(RectF{ b.Rect.Left - rect.Left, b.Rect.Top - rect.Top, b.Rect.Right - rect.Left, b.Rect.Bottom - rect.Top }, b.Border, b.Radius, colors);
						}
						CStoreBlock s_block{ renderer };
						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer
							->ActivateBlock(&clip_b)
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(rect.Left, rect.Top, 0))
							->DrawImage(clip, 1);
						clip->Release();
					}
				}
				else
					renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
			}

			if (background_gradient.getPointCount() >= 2)
			{
				b.Rect = rect;
				b.Border = AddElements(outer_borders, middle_borders, inner_borders);
				b.Radius = radiuses;
				CStoreBlock s_block{ renderer };
				renderer
					->ActivateBlock(&b)
					->DrawGradient(rect, background_gradient);
			}
			return true;
		}
		return false;
	}

	bool DrawBezierCurve(IRenderer *renderer, const PointF &p1, const PointF &p2, const PointF &cp1, const PointF &cp2, const Color &color, const float width, const float dT)
	{
		if (ntl::IsLessOrEqual<float>(width, 0) || IsEqual(p1, p2))
			return false;
		if (ntl::IsEqual<float>(width, 1))
		{
			RectF bound{ ntl::Min<float>(p1.X, p2.X, cp1.X, cp2.X), ntl::Min<float>(p1.Y, p2.Y, cp1.Y, cp2.Y), ntl::Max<float>(p1.X, p2.X, cp1.X, cp2.X), ntl::Max<float>(p1.Y, p2.Y, cp1.Y, cp2.Y) };
			float dt{ (dT <= 0) ? (1.0f / (bound.width() + bound.height())) : dT }, ct{ 0 }, t1, t;
			PointF last{ p1 }, p, pl{ p2 };
			do
			{
				ct += dt;
				t = ntl::Min<float>(1.0f, ct);
				t1 = 1 - t;
				p.X = t1 * t1 * t1 * p1.X + 3 * t * t1 * t1 * cp1.X + 3 * t * t * t1 * cp2.X + t * t * t * p2.X;
				p.Y = t1 * t1 * t1 * p1.Y + 3 * t * t1 * t1 * cp1.Y + 3 * t * t * t1 * cp2.Y + t * t * t * p2.Y;
				if (IsNotEqual(p, last) || IsEqual(p, pl))
				{
					renderer->DrawLine(last, p, color);
					last = p;
				}
			} while (ct < 1);
			return true;
		}
		RectF bound{ ntl::Min<float>(p1.X, p2.X, cp1.X, cp2.X), ntl::Min<float>(p1.Y, p2.Y, cp1.Y, cp2.Y), ntl::Max<float>(p1.X, p2.X, cp1.X, cp2.X), ntl::Max<float>(p1.Y, p2.Y, cp1.Y, cp2.Y) };
		float dt{ (dT <= 0) ? (1.0f / (bound.width() + bound.height())) : dT }, ct{ 0 }, t1, hw{ width * 0.5f }, t;
		Vec3f n, n_last, tangent{ 3 * (cp1.X - p1.X), 3 * (cp1.Y - p1.Y), 0 }, z{ 0, 0, 1 }, v_last{ p1.X, p1.Y, 0 }, v, v1, v2, v3, v4;
		n_last = tangent ^ z;
		ntl::Normalize<float>(n_last);
		PointF last{ p1 }, p, pl{ p2 };
		std::vector<std::vector<PointF>> polygons;
		do
		{
			ct += dt;
			t = ntl::Min<float>(1.0f, ct);
			t1 = 1 - t;
			v.X = t1 * t1 * t1 * p1.X + 3 * t * t1 * t1 * cp1.X + 3 * t * t * t1 * cp2.X + t * t * t * p2.X;
			v.Y = t1 * t1 * t1 * p1.Y + 3 * t * t1 * t1 * cp1.Y + 3 * t * t * t1 * cp2.Y + t * t * t * p2.Y;
			p.X = v.X;
			p.Y = v.Y;
			if (IsNotEqual(p, last) || IsEqual(p, pl))
			{
				v.Z = 0;
				tangent = Vec3f{ 
					3 * (-t1 * t1 * p1.X + t1 * (1 - 3 * t) * cp1.X + t * (2 - 3 * t) * cp2.X + t * t * p2.X),
					3 * (-t1 * t1 * p1.Y + t1 * (1 - 3 * t) * cp1.Y + t * (2 - 3 * t) * cp2.Y + t * t * p2.Y),
					0
				};
				n = tangent ^ z;
				ntl::Normalize<float>(n);

				v1 = v_last + n_last * hw;
				v2 = v + n * hw;
				v3 = v - n * hw;
				v4 = v_last - n_last * hw;

				polygons.push_back({ PointF{ v1.X, v1.Y }, PointF{ v2.X, v2.Y }, PointF{ v3.X, v3.Y }, PointF{ v4.X, v4.Y } });

				last = p;
				n_last = n;
				v_last = v;
			}
					
		} while (ct < 1);
		if (polygons.size() > 0)
		{
			renderer->DrawPolygons(polygons, color);
			return true;
		}
		return false;
	}

	RectF AddShadow(const RectF &rect, const Color &color, const PointF &shift, const int radius)
	{
		if (color.A > 0)
		{
			RectF result{ rect };
			float f_radius{ (float)radius };
			if (shift.X > 0)
				result.Right += shift.X;
			else
				result.Left += shift.X;
			if (shift.Y > 0)
				result.Bottom += shift.Y;
			else
				result.Top += shift.Y;
			result.Left -= f_radius;
			result.Top -= f_radius;
			result.Right += f_radius;
			result.Bottom += f_radius;
			return result;
		}
		return rect;
	}

	PointF DispOnCanvas(const Color &shadow_color, const PointF &shadow_shift, const int shadow_radius)
	{
		if (shadow_color.A > 0)
		{
			PointF disp{ (float)shadow_radius, (float)shadow_radius };
			if (shadow_shift.X < 0)
				disp.X -= shadow_shift.X;
			else
				disp.X = ntl::Max<float>(0.0f, disp.X - shadow_shift.X);
			if (shadow_shift.Y < 0)
				disp.Y -= shadow_shift.Y;
			else
				disp.Y = ntl::Max<float>(0.0f, disp.Y - shadow_shift.Y);
			return disp;
		}
		return PointF{ 0, 0 };
	}

	// Source: http://scaledinnovation.com/analytics/splines/aboutSplines.html
	void Bezier(const PointF &prev, const PointF &point, const PointF &next, const float tension, PointF &cp_prev, PointF &cp_next)
	{
		float sa, sb;
		if (IsEqual(prev, point) && IsEqual(next, point))
		{
			sa = 0;
			sb = 0;
		}
		else
		{
			float dx1{ point.X - prev.X }, dy1{ point.Y - prev.Y }, dx2{ next.X - point.X }, dy2{ next.Y - point.Y };
			float d01{ std::sqrt(dx1 * dx1 + dy1 * dy1) };
			float d12{ std::sqrt(dx2 * dx2 + dy2 * dy2) };
			sa = d01 / (d01 + d12);
			sb = d12 / (d01 + d12);
		}
		float fa{ tension * sa };
		float fb{ tension * sb };
		cp_prev.X = point.X - fa * (next.X - prev.X);
		cp_prev.Y = point.Y - fa * (next.Y - prev.Y);
		cp_next.X = point.X + fb * (next.X - prev.X);
		cp_next.Y = point.Y + fb * (next.Y - prev.Y);
	}

	void BezierSubdivide_r(
		const PointF &p1,
		const PointF &p2,
		const PointF &p3,
		const PointF &p4,
		const int level,
		std::vector<PointF> &points,
		const int curve_recursion_limit,
		const float distance_tolerance,
		const float angle_tolerance,
		const float cusp_limit,
		const float curve_angle_tolerance,
		const float curve_collinearity_tolerance)
	{
		if (level > curve_recursion_limit)
			return;
		PointF p12{ (p1.X + p2.X) / 2, (p1.Y + p2.Y) / 2 };
		PointF p23{ (p2.X + p3.X) / 2, (p2.Y + p3.Y) / 2 };
		PointF p34{ (p3.X + p4.X) / 2, (p3.Y + p4.Y) / 2 };
		PointF p123{ (p12.X + p23.X) / 2, (p12.Y + p23.Y) / 2 };
		PointF p234{ (p23.X + p34.X) / 2, (p23.Y + p34.Y) / 2 };
		PointF p1234{ (p123.X + p234.X) / 2, (p123.Y + p234.Y) / 2 };
		if (level > 0)
		{
			float dx{ p4.X - p1.X };
			float dy{ p4.Y - p1.Y };
			float d2{ ntl::Abs<float>(((p2.X - p4.X) * dy - (p2.Y - p4.Y) * dx)) };
			float d3{ ntl::Abs<float>(((p3.X - p4.X) * dy - (p3.Y - p4.Y) * dx)) };
			float da1, da2;
			if (d2 > curve_collinearity_tolerance && d3 > curve_collinearity_tolerance)
			{
				if ((d2 + d3) * (d2 + d3) <= distance_tolerance * (dx * dx + dy * dy))
				{
					if (angle_tolerance < curve_angle_tolerance)
					{
						points.push_back(p1234);
						return;
					}
					float a23{ std::atan2(p3.Y - p2.Y, p3.X - p2.X) };
					da1 = ntl::Abs<float>(a23 - std::atan2(p2.Y - p1.Y, p2.X - p1.X));
					da2 = ntl::Abs<float>(std::atan2(p4.Y - p3.Y, p4.X - p3.X) - a23);
					if (da1 >= ntl::Pi<float>)
						da1 = ntl::DoublePi<float> -da1;
					if (da2 >= ntl::Pi<float>)
						da2 = ntl::DoublePi<float> -da2;
					if (da1 + da2 < angle_tolerance)
					{
						points.push_back(p1234);
						return;
					}
					if (ntl::IsNotEqual<float>(cusp_limit, 0))
					{
						if (da1 > cusp_limit)
						{
							points.push_back(p2);
							return;
						}
						if (da2 > cusp_limit)
						{
							points.push_back(p3);
							return;
						}
					}
				}
			}
			else
			{
				if (d2 > curve_collinearity_tolerance)
				{
					if (d2 * d2 <= distance_tolerance * (dx * dx + dy * dy))
					{
						if (angle_tolerance < curve_angle_tolerance)
						{
							points.push_back(p1234);
							return;
						}
						da1 = ntl::Abs<float>(std::atan2(p3.Y - p2.Y, p3.X - p2.X) - std::atan2(p2.Y - p1.Y, p2.X - p1.X));
						if (da1 >= ntl::Pi<float>)
							da1 = ntl::DoublePi<float> -da1;
						if (da1 < angle_tolerance)
						{
							points.push_back(p2);
							points.push_back(p3);
							return;
						}
						if (ntl::IsNotEqual<float>(cusp_limit, 0) && da1 > cusp_limit)
						{
							points.push_back(p2);
							return;
						}
					}
				}
				else
					if (d3 > curve_collinearity_tolerance)
					{
						if (d3 * d3 <= distance_tolerance * (dx * dx + dy * dy))
						{
							if (angle_tolerance < curve_angle_tolerance)
							{
								points.push_back(p1234);
								return;
							}
							da1 = ntl::Abs<float>(std::atan2(p4.Y - p3.Y, p4.X - p3.X) - std::atan2(p3.Y - p2.Y, p3.X - p2.X));
							if (da1 >= ntl::Pi<float>)
								da1 = ntl::DoublePi<float> -da1;
							if (da1 < angle_tolerance)
							{
								points.push_back(p2);
								points.push_back(p3);
								return;
							}
							if (ntl::IsNotEqual<float>(cusp_limit, 0) && da1 > cusp_limit)
							{
								points.push_back(p3);
								return;
							}
						}
					}
					else
					{
						dx = p1234.X - (p1.X + p4.X) / 2;
						dy = p1234.Y - (p1.Y + p4.Y) / 2;
						if (dx * dx + dy * dy <= distance_tolerance)
						{
							points.push_back(p1234);
							return;
						}
					}
			}
		}
		BezierSubdivide_r(p1, p12, p123, p1234, level + 1, points, curve_recursion_limit, distance_tolerance, angle_tolerance, cusp_limit, curve_angle_tolerance, curve_collinearity_tolerance);
		BezierSubdivide_r(p1234, p234, p34, p4, level + 1, points, curve_recursion_limit, distance_tolerance, angle_tolerance, cusp_limit, curve_angle_tolerance, curve_collinearity_tolerance);
	}

	// http://www.antigrain.com/research/adaptive_bezier/index.html
	void BezierSubdivide(
		const PointF &p1,
		const PointF &p2,
		const PointF &p3,
		const PointF &p4,
		std::vector<PointF> &points,
		const int curve_recursion_limit,
		const float distance_tolerance,
		const float angle_tolerance,
		const float cusp_limit,
		const float curve_angle_tolerance,
		const float curve_collinearity_tolerance)
	{
		BezierSubdivide_r(p1, p2, p3, p4, 0, points, curve_recursion_limit, distance_tolerance, angle_tolerance, cusp_limit, curve_angle_tolerance, curve_collinearity_tolerance);
	}

	bool MakeThickPath(
		const std::vector<PointF> &path,
		const bool loop,
		const float width,
		const bool middle,
		std::vector<std::pair<PointF, PointF>> &points)
	{
		if (path.size() < 2 || ntl::IsEqual<float>(width, 0) || (loop && path.size() < 3))
			return false;
		points.resize(path.size());
		static const Vec3f z{ 0, 0, 1 };
		Vec3f n, v_curr, v_prev, v_next, v, a1, a2, a3, a4, b1, b2, b3, b4, a21, a34, b21, b34, qa1, qa2, qb1, qb2;
		float w_pos{ middle ? (ntl::Abs<float>(width) / 2) : ((width > 0) ? width : 0) };
		float w_neg{ middle ? (ntl::Abs<float>(width) / 2) : ((width > 0) ? 0 : ntl::Abs<float>(width)) };
		float da, db;
		for (size_t i = 0; i < path.size(); i++)
		{
			v_curr = Vec3f{ path[i].X, path[i].Y, 0 };
			if (i == 0)
			{
				if (!loop)
				{
					v_next = Vec3f{ path[i + 1].X, path[i + 1].Y, 0 };
					n = v_next - v_curr;
					n ^= z;
					ntl::Normalize<float>(n);
					v = v_curr + n * w_pos;
					points[i].first = PointF{ v.X, v.Y };
					v = v_curr - n * w_neg;
					points[i].second = PointF{ v.X, v.Y };
					continue;
				}
				v_prev = Vec3f{ path[path.size() - 1].X, path[path.size() - 1].Y, 0 };
			}
			else
				v_prev = Vec3f{ path[i - 1].X, path[i - 1].Y, 0 };
			if (i == path.size() - 1)
			{
				if (!loop)
				{
					v_prev = Vec3f{ path[i - 1].X, path[i - 1].Y, 0 };
					n = v_curr - v_prev;
					n ^= z;
					ntl::Normalize<float>(n);
					v = v_curr + n * w_pos;
					points[i].first = PointF{ v.X, v.Y };
					v = v_curr - n * w_neg;
					points[i].second = PointF{ v.X, v.Y };
					continue;
				}
				v_next = Vec3f{ path[0].X, path[0].Y, 0 };
			}
			else
				v_next = Vec3f{ path[i + 1].X, path[i + 1].Y, 0 };

			n = v_curr - v_prev;
			n ^= z;
			ntl::Normalize<float>(n);
			a1 = v_prev + n * w_pos;
			a2 = v_curr + n * w_pos;
			b1 = v_prev - n * w_neg;
			b2 = v_curr - n * w_neg;

			n = v_next - v_curr;
			n ^= z;
			ntl::Normalize<float>(n);
			a3 = v_curr + n * w_pos;
			a4 = v_next + n * w_pos;
			b3 = v_curr - n * w_neg;
			b4 = v_next - n * w_neg;

			if (ntl::IsEqual<float>(a2, a3) || ntl::IsEqual<float>(b2, b3))
			{
				points[i].first = PointF{ a2.X, a2.Y };
				points[i].second = PointF{ b2.X, b2.Y };
				continue;
			}
			a21 = a2 - a1;
			a34 = a3 - a4;
			b21 = b2 - b1;
			b34 = b3 - b4;
			qa1 = ntl::Normalized<float>(a21);
			qa2 = ntl::Normalized<float>(a34);
			qb1 = ntl::Normalized<float>(b21);
			qb2 = ntl::Normalized<float>(b34);
			da = qa1.Y * qa2.X - qa1.X * qa2.Y;
			db = qb1.Y * qb2.X - qb1.X * qb2.Y;
			if (ntl::IsZero<float>(da) || ntl::IsZero<float>(db) || (ntl::IsZero<float>(qa1.X) && ntl::IsZero<float>(qa2.X)) || (ntl::IsZero<float>(qb1.X) && ntl::IsZero<float>(qb2.X)))
			{
				points[i].first = PointF{ a2.X, a2.Y };
				points[i].second = PointF{ b2.X, b2.Y };
				continue;
			}
			points[i].first.X = (a1.X * qa1.Y * qa2.X + (a4.Y - a1.Y) * qa1.X * qa2.X - a4.X * qa1.X * qa2.Y) / da;
			if (ntl::IsZero<float>(qa1.X))
				points[i].first.Y = ((points[i].first.X - a4.X) * qa2.Y) / qa2.X + a4.Y;
			else
				points[i].first.Y = ((points[i].first.X - a1.X) * qa1.Y) / qa1.X + a1.Y;
			points[i].second.X = (b1.X * qb1.Y * qb2.X + (b4.Y - b1.Y) * qb1.X * qb2.X - b4.X * qb1.X * qb2.Y) / db;
			if (ntl::IsZero<float>(qb1.X))
				points[i].second.Y = ((points[i].second.X - b4.X) * qb2.Y) / qb2.X + b4.Y;
			else
				points[i].second.Y = ((points[i].second.X - b1.X) * qb1.Y) / qb1.X + b1.Y;
		}
		return true;
	}
}